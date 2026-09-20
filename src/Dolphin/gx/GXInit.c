typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef float f32;

typedef struct {
    u32 image1;
    u32 image2;
    u32 sizes;
    u8 is32bMipmap;
    u8 isCached;
} GXTexRegion;

typedef struct {
    u32 tmemAddr;
    u32 unk4;
    u32 unk8;
    u32 unkC;
} GXTlutRegion;

// The 0x80-byte FIFO descriptor GXInit hands to the FIFO setters and returns.
typedef struct {
    u8 dummy[0x80];
} GXFifoObj;

// The CPU-side write port of the GP FIFO.
typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXWGFifoObj;

volatile GXWGFifoObj GXWGFifo : 0xCC008000;

u32 __OSBusClock : 0x800000F8;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x7C];
    u32 lpSize;
    u8 pad1[0x38];
    u32 suTs0[8];
    u32 suTs1[8];
    u32 suScis0;
    u32 suScis1;
    u32 tref[8];
    u32 iref;
    u32 bpMask;
    u8 pad2[0x8];
    u32 tevc[16];
    u32 teva[16];
    u32 tevKsel[8];
    u32 cmode0;
    u32 cmode1;
    u32 zmode;
    u32 peCtrl;
    u8 pad3[0x1C];
    u32 cpTex;
    u8 pad4[0x4];
    u32 genMode;
    GXTexRegion TexRegions[8];
    GXTexRegion TexRegionsCI[8];
    GXTexRegion TexRegionsMip[8];
    GXTlutRegion TlutRegions[20];
    u8 pad5[0x44];
    f32 zOffset;
    f32 zScale;
    u8 pad6[0x40];
    u32 texmapId[16];
    u32 tcsManEnab;
    u32 tevTcEnab;
    u8 pad7[0x8];
    u32 perfSel;
    u8 inDispList;
    u8 dlSaveContext;
    u8 unk5AA;
    u8 dirtyVAT;
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;
#define gx __GXData

extern char* __GXVersion;
extern GXFifoObj FifoObj;
extern u32 GXTexRegionAddrTable[6][8];
extern u32 resetFuncRegistered;

// OSResetFunctionInfo; only its address is taken here.
extern u8 GXResetFuncInfo[0x10];

// 16777216.0f and 0.0f, shared with the rest of the SDK's .sdata2 literal pool.
extern const f32 GXInitZScaleConst;
extern const f32 GXInitZOffsetConst;

extern u16* __cpReg;
extern u16* __peReg;
extern u32* __piReg;
extern u16* __memReg;

extern void OSRegisterVersion(const char* version);
extern void OSRegisterResetFunction(void* info);
extern u32 PPCMfhid2(void);
extern void PPCMthid2(u32 value);
extern void PPCMtwpar(void* addr);
extern void GXSetMisc(int token, u32 val);
extern void __GXFifoInit(void);
extern void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size);
extern void GXSetCPUFifo(GXFifoObj* fifo);
extern void GXSetGPFifo(GXFifoObj* fifo);
extern void __GXPEInit(void);
extern void __GXFlushTextureState(void);
extern void __GXInitRevisionBits(void);
extern void GXInitTexCacheRegion(GXTexRegion* region, u8 is_32b_mipmap, u32 tmem_even,
                                 int size_even, u32 tmem_odd, int size_odd);
extern void GXInitTlutRegion(GXTlutRegion* region, u32 tmem_addr, u32 tlut_size);
extern void __GXSetIndirectMask(u32 mask);
extern void __GXSetTmemConfig(u32 config);
extern void __GXInitGX(void);

#define OSPhysicalToUncached(paddr) ((void*)((u32)(paddr) + 0xC0000000))
#define OSUncachedToPhysical(caddr) ((void*)((u32)(caddr)-0xC0000000))

#define GXFIFO_ADDR 0xCC008000

// Writes `val` into a `size`-bit field at bit `shift` of `reg`.
// Uses the CodeWarrior __rlwimi intrinsic, which emits exactly one rlwimi instruction (the plain-C mask/shift form emits extra masking).
#define SET_REG_FIELD(reg, size, shift, val)                                   \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift),                     \
                          (32 - (shift) - (size)), (31 - (shift)))

// The original keeps the redundant `b <next instruction>` branches at every loop head and
// separate cmplwi compares, both of which the peephole pass would otherwise fold away.
#pragma peephole off

static inline void EnableWriteGatherPipe(void)
{
    u32 hid2 = PPCMfhid2();

    PPCMtwpar(OSUncachedToPhysical(GXFIFO_ADDR));
    hid2 |= 0x40000000;
    PPCMthid2(hid2);
}

GXFifoObj* GXInit(void* base, u32 size)
{
    GXFifoObj* fifoObj;
    u32 i;
    u32 reg;
    u32 freqBase;

    fifoObj = &FifoObj;
    OSRegisterVersion(__GXVersion);

    gx->inDispList = 0;
    gx->dlSaveContext = 1;
    gx->unk5AA = 1;
    gx->tcsManEnab = 0;
    gx->tevTcEnab = 0;
    GXSetMisc(1, 0);

    __piReg = (u32*)OSPhysicalToUncached(0x0C003000);
    __cpReg = (u16*)OSPhysicalToUncached(0x0C000000);
    __peReg = (u16*)OSPhysicalToUncached(0x0C001000);
    __memReg = (u16*)OSPhysicalToUncached(0x0C004000);

    __GXFifoInit();
    GXInitFifoBase(fifoObj, base, size);
    GXSetCPUFifo(fifoObj);
    GXSetGPFifo(fifoObj);

    if (!resetFuncRegistered) {
        OSRegisterResetFunction(&GXResetFuncInfo);
        resetFuncRegistered = 1;
    }

    __GXPEInit();
    EnableWriteGatherPipe();

    gx->genMode = 0;
    SET_REG_FIELD(gx->genMode, 8, 24, 0);
    gx->bpMask = 255;
    SET_REG_FIELD(gx->bpMask, 8, 24, 0x0F);
    gx->lpSize = 0;
    SET_REG_FIELD(gx->lpSize, 8, 24, 0x22);

    for (i = 0; i < 16; i++) {
        gx->tevc[i] = 0;
        gx->teva[i] = 0;
        gx->tref[i / 2] = 0;
        gx->texmapId[i] = 0xFF;
        SET_REG_FIELD(gx->tevc[i], 8, 24, 0xC0 + i * 2);
        SET_REG_FIELD(gx->teva[i], 8, 24, 0xC1 + i * 2);
        SET_REG_FIELD(gx->tevKsel[i / 2], 8, 24, 0xF6 + i / 2);
        SET_REG_FIELD(gx->tref[i / 2], 8, 24, 0x28 + i / 2);
    }

    gx->iref = 0;
    SET_REG_FIELD(gx->iref, 8, 24, 0x27);

    for (i = 0; i < 8; i++) {
        gx->suTs0[i] = 0;
        gx->suTs1[i] = 0;
        SET_REG_FIELD(gx->suTs0[i], 8, 24, 0x30 + i * 2);
        SET_REG_FIELD(gx->suTs1[i], 8, 24, 0x31 + i * 2);
    }

    SET_REG_FIELD(gx->suScis0, 8, 24, 0x20);
    SET_REG_FIELD(gx->suScis1, 8, 24, 0x21);
    SET_REG_FIELD(gx->cmode0, 8, 24, 0x41);
    SET_REG_FIELD(gx->cmode1, 8, 24, 0x42);
    SET_REG_FIELD(gx->zmode, 8, 24, 0x40);
    SET_REG_FIELD(gx->peCtrl, 8, 24, 0x43);
    SET_REG_FIELD(gx->cpTex, 2, 7, 0);
    gx->zScale = GXInitZScaleConst;
    gx->zOffset = GXInitZOffsetConst;
    gx->dirtyState = 0;
    gx->dirtyVAT = 0;

    freqBase = __OSBusClock / 500;
    __GXFlushTextureState();
    reg = (freqBase >> 11) | 0x400 | 0x69000000;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;

    __GXFlushTextureState();
    reg = (freqBase / 0x1080) | 0x200 | 0x46000000;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;

    __GXInitRevisionBits();

    for (i = 0; i < 8; i++) {
        GXInitTexCacheRegion(&gx->TexRegions[i], 0, GXTexRegionAddrTable[0][i], 0,
                             GXTexRegionAddrTable[1][i], 0);
        GXInitTexCacheRegion(&gx->TexRegionsCI[i], 0, GXTexRegionAddrTable[2][i], 0,
                             GXTexRegionAddrTable[3][i], 0);
        GXInitTexCacheRegion(&gx->TexRegionsMip[i], 1, GXTexRegionAddrTable[4][i], 0,
                             GXTexRegionAddrTable[5][i], 0);
    }
    for (i = 0; i < 16; i++) {
        GXInitTlutRegion(&gx->TlutRegions[i], 0xC0000 + i * 0x2000, 16);
    }
    for (i = 0; i < 4; i++) {
        GXInitTlutRegion(&gx->TlutRegions[i + 16], 0xE0000 + i * 0x8000, 64);
    }

    __cpReg[3] = 0;
    SET_REG_FIELD(gx->perfSel, 4, 4, 0);
    GXWGFifo.u8 = 8;
    GXWGFifo.u8 = 32;
    GXWGFifo.u32 = gx->perfSel;
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = 0x1006;
    GXWGFifo.u32 = 0;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = 0x23000000;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = 0x24000000;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = 0x67000000;

    __GXSetIndirectMask(0);
    __GXSetTmemConfig(2);
    __GXInitGX();
    return fifoObj;
}
