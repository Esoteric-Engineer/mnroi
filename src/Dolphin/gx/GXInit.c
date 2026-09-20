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

typedef struct {
    u8 r, g, b, a;
} GXColor;

// Only the fields __GXInitGX reads are named.
typedef struct {
    u32 viTVmode;
    u16 fbWidth;
    u16 efbHeight;
    u16 xfbHeight;
    u16 viXOrigin;
    u16 viYOrigin;
    u16 viWidth;
    u16 viHeight;
    u32 xFBmode;
    u8 field_rendering;
    u8 aa;
    u8 sample_pattern[12][2];
    u8 vfilter[7];
} GXRenderModeObj;

typedef struct {
    u8 dummy[0x20];
} GXTexObj;

// Raw .data blocks in this translation unit's area, not yet given real names.
extern u8 lbl_804D3340[];
extern u8 lbl_804D35E8[];
extern u8 lbl_804D3648[];
extern u8 lbl_804D369C[];
extern u8 lbl_804D36F0[];

extern int VIGetTvFormat(void);
extern void GXSetCopyClear(GXColor clear_clr, u32 clear_z);
extern void GXSetTexCoordGen2(int dst, int func, int src, int mtx, int normalize, int postmtx);
extern void GXSetNumTexGens(u8 nTexGens);
extern void GXClearVtxDesc(void);
extern void GXInvalidateVtxCache(void);
extern void GXSetArray(int attr, void* base, u8 stride);
extern void GXSetVtxAttrFmtv(int fmt, void* vat);
extern void GXSetLineWidth(u8 width, int offsets);
extern void GXSetPointSize(u8 size, int offsets);
extern void GXEnableTexOffsets(int coord, u8 line, u8 point);
extern void GXLoadPosMtxImm(f32 mtx[3][4], u32 id);
extern void GXLoadNrmMtxImm(f32 mtx[3][4], u32 id);
extern void GXSetCurrentMtx(u32 id);
extern void GXLoadTexMtxImm(f32 mtx[3][4], u32 id, int type);
extern void GXSetViewport(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz);
extern void GXSetProjectionv(f32* ptr);
extern void GXSetCoPlanar(u8 enable);
extern void GXSetCullMode(int mode);
extern void GXSetClipMode(int mode);
extern void GXSetScissor(u32 left, u32 top, u32 wd, u32 ht);
extern void GXSetScissorBoxOffset(int x, int y);
extern void GXSetNumChans(u8 nChans);
extern void GXSetChanCtrl(int chan, u8 enable, int amb_src, int mat_src, u32 light_mask, int diff_fn, int attn_fn);
extern void GXSetChanAmbColor(int chan, GXColor amb_color);
extern void GXSetChanMatColor(int chan, GXColor mat_color);
extern void GXInvalidateTexAll(void);
extern void GXSetTexRegionCallback(void* cb);
extern void GXSetTlutRegionCallback(void* cb);
extern void GXInitTexObj(GXTexObj* obj, void* image, u16 width, u16 height, int format, int wrap_s, int wrap_t, u8 mipmap);
extern void GXLoadTexObj(GXTexObj* obj, int map);
extern void GXSetTevOrder(int stage, int coord, int map, int color);
extern void GXSetNumTevStages(u8 nStages);
extern void GXSetTevOp(int stage, int mode);
extern void GXSetAlphaCompare(int comp0, u8 ref0, int op, int comp1, u8 ref1);
extern void GXSetZTexture(int op, int fmt, u32 bias);
extern void GXSetTevKColorSel(int stage, int sel);
extern void GXSetTevKAlphaSel(int stage, int sel);
extern void GXSetTevSwapMode(int stage, int ras_sel, int tex_sel);
extern void GXSetTevSwapModeTable(int table, int red, int green, int blue, int alpha);
extern void GXSetTevDirect(int stage);
extern void GXSetNumIndStages(u8 nIndStages);
extern void GXSetIndTexCoordScale(int stage, int scale_s, int scale_t);
extern void GXSetFog(int type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color);
extern void GXSetFogRangeAdj(u8 enable, u16 center, void* table);
extern void GXSetBlendMode(int type, int src_factor, int dst_factor, int op);
extern void GXSetColorUpdate(u8 update_enable);
extern void GXSetAlphaUpdate(u8 update_enable);
extern void GXSetZMode(u8 compare_enable, int func, u8 update_enable);
extern void GXSetZCompLoc(u8 before_tex);
extern void GXSetDither(u8 dither);
extern void GXSetDstAlpha(u8 enable, u8 alpha);
extern void GXSetPixelFmt(int pix_fmt, int z_fmt);
extern void GXSetFieldMask(u8 odd_mask, u8 even_mask);
extern void GXSetFieldMode(u8 field_mode, u32 half_aspect_ratio);
extern void GXSetDispCopySrc(u16 left, u16 top, u16 wd, u16 ht);
extern void GXSetDispCopyDst(u16 wd, u16 ht);
extern void GXSetDispCopyYScale(f32 vscale);
extern void GXSetCopyClamp(int clamp);
extern void GXSetCopyFilter(u8 aa, u8 sample_pattern[12][2], u8 vf, u8 vfilter[7]);
extern void GXSetDispCopyGamma(int gamma);
extern void GXSetDispCopyFrame2Field(int mode);
extern void GXClearBoundingBox(void);
extern void GXPokeColorUpdate(u8 update_enable);
extern void GXPokeAlphaUpdate(u8 update_enable);
extern void GXPokeDither(u8 dither);
extern void GXPokeBlendMode(int type, int src_factor, int dst_factor, int op);
extern void GXPokeAlphaMode(int func, u8 threshold);
extern void GXPokeAlphaRead(int mode);
extern void GXPokeDstAlpha(u8 enable, u8 alpha);
extern void GXPokeZMode(u8 compare_enable, int func, u8 update_enable);
extern void GXSetGPMetric(int perf0, int perf1);
extern void GXClearGPMetric(void);
extern void __GXDefaultTexRegionCallback(void);
extern void __GXDefaultTlutRegionCallback(void);

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

extern u8 lbl_8057D630[];
__GXDataStruct* const __GXData = (__GXDataStruct*)lbl_8057D630;
#define gx __GXData

extern char* __GXVersion;
extern GXFifoObj FifoObj;
extern u32 GXTexRegionAddrTable[6][8];
extern u32 resetFuncRegistered;

// OSResetFunctionInfo; only its address is taken here.
extern u8 GXResetFuncInfo[0x10];


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
    gx->zScale = 16777216.0f;
    gx->zOffset = 0.0f;
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

void __GXInitGX(void)
{
    GXRenderModeObj* rmode;
    GXTexObj texObj;
    f32 identity_mtx[3][4];
    u8* tbl = lbl_804D3340;
    GXColor clear = {64, 64, 64, 255};
    GXColor black = {0, 0, 0, 0};
    GXColor white = {255, 255, 255, 255};
    u32 i;

    switch (VIGetTvFormat()) {
    case 0:
        rmode = (GXRenderModeObj*)lbl_804D35E8;
        break;
    case 1:
        rmode = (GXRenderModeObj*)lbl_804D369C;
        break;
    case 5:
        rmode = (GXRenderModeObj*)lbl_804D36F0;
        break;
    case 2:
        rmode = (GXRenderModeObj*)lbl_804D3648;
        break;
    default:
        rmode = (GXRenderModeObj*)lbl_804D35E8;
        break;
    }
    GXSetCopyClear(clear, 0xFFFFFF);
    GXSetTexCoordGen2(0, 1, 4, 60, 0, 125);
    GXSetTexCoordGen2(1, 1, 5, 60, 0, 125);
    GXSetTexCoordGen2(2, 1, 6, 60, 0, 125);
    GXSetTexCoordGen2(3, 1, 7, 60, 0, 125);
    GXSetTexCoordGen2(4, 1, 8, 60, 0, 125);
    GXSetTexCoordGen2(5, 1, 9, 60, 0, 125);
    GXSetTexCoordGen2(6, 1, 10, 60, 0, 125);
    GXSetTexCoordGen2(7, 1, 11, 60, 0, 125);
    GXSetNumTexGens(1);
    GXClearVtxDesc();
    GXInvalidateVtxCache();
    for (i = 9; i <= 24; i++) {
        GXSetArray(i, gx, 0);
    }
    for (i = 0; i < 8; i++) {
        GXSetVtxAttrFmtv(i, tbl + 0x80);
    }
    GXSetLineWidth(6, 0);
    GXSetPointSize(6, 0);
    GXEnableTexOffsets(0, 0, 0);
    GXEnableTexOffsets(1, 0, 0);
    GXEnableTexOffsets(2, 0, 0);
    GXEnableTexOffsets(3, 0, 0);
    GXEnableTexOffsets(4, 0, 0);
    GXEnableTexOffsets(5, 0, 0);
    GXEnableTexOffsets(6, 0, 0);
    GXEnableTexOffsets(7, 0, 0);
    identity_mtx[0][0] = 1.0f;
    identity_mtx[0][1] = 0.0f;
    identity_mtx[0][2] = 0.0f;
    identity_mtx[0][3] = 0.0f;
    identity_mtx[1][0] = 0.0f;
    identity_mtx[1][1] = 1.0f;
    identity_mtx[1][2] = 0.0f;
    identity_mtx[1][3] = 0.0f;
    identity_mtx[2][0] = 0.0f;
    identity_mtx[2][1] = 0.0f;
    identity_mtx[2][2] = 1.0f;
    identity_mtx[2][3] = 0.0f;
    GXLoadPosMtxImm(identity_mtx, 0);
    GXLoadNrmMtxImm(identity_mtx, 0);
    GXSetCurrentMtx(0);
    GXLoadTexMtxImm(identity_mtx, 60, 0);
    GXLoadTexMtxImm(identity_mtx, 125, 0);
    GXSetViewport(0.0f, 0.0f, rmode->fbWidth, rmode->xfbHeight, 0.0f, 1.0f);
    GXSetProjectionv((f32*)(tbl + 0x150));
    GXSetCoPlanar(0);
    GXSetCullMode(2);
    GXSetClipMode(0);
    GXSetScissor(0, 0, rmode->fbWidth, rmode->efbHeight);
    GXSetScissorBoxOffset(0, 0);
    GXSetNumChans(0);
    GXSetChanCtrl(4, 0, 0, 1, 0, 0, 2);
    GXSetChanAmbColor(4, black);
    GXSetChanMatColor(4, white);
    GXSetChanCtrl(5, 0, 0, 1, 0, 0, 2);
    GXSetChanAmbColor(5, black);
    GXSetChanMatColor(5, white);
    GXInvalidateTexAll();
    GXSetTexRegionCallback(__GXDefaultTexRegionCallback);
    GXSetTlutRegionCallback(__GXDefaultTlutRegionCallback);
    GXInitTexObj(&texObj, tbl + 0x60, 4, 4, 3, 0, 0, 0);
    GXLoadTexObj(&texObj, 0);
    GXLoadTexObj(&texObj, 1);
    GXLoadTexObj(&texObj, 2);
    GXLoadTexObj(&texObj, 3);
    GXLoadTexObj(&texObj, 4);
    GXLoadTexObj(&texObj, 5);
    GXLoadTexObj(&texObj, 6);
    GXLoadTexObj(&texObj, 7);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevOrder(1, 1, 1, 4);
    GXSetTevOrder(2, 2, 2, 4);
    GXSetTevOrder(3, 3, 3, 4);
    GXSetTevOrder(4, 4, 4, 4);
    GXSetTevOrder(5, 5, 5, 4);
    GXSetTevOrder(6, 6, 6, 4);
    GXSetTevOrder(7, 7, 7, 4);
    GXSetTevOrder(8, 255, 255, 255);
    GXSetTevOrder(9, 255, 255, 255);
    GXSetTevOrder(10, 255, 255, 255);
    GXSetTevOrder(11, 255, 255, 255);
    GXSetTevOrder(12, 255, 255, 255);
    GXSetTevOrder(13, 255, 255, 255);
    GXSetTevOrder(14, 255, 255, 255);
    GXSetTevOrder(15, 255, 255, 255);
    GXSetNumTevStages(1);
    GXSetTevOp(0, 3);
    GXSetAlphaCompare(7, 0, 0, 7, 0);
    GXSetZTexture(0, 17, 0);
    for (i = 0; i < 16; i++) {
        GXSetTevKColorSel(i, 6);
        GXSetTevKAlphaSel(i, 0);
        GXSetTevSwapMode(i, 0, 0);
    }
    GXSetTevSwapModeTable(0, 0, 1, 2, 3);
    GXSetTevSwapModeTable(1, 0, 0, 0, 3);
    GXSetTevSwapModeTable(2, 1, 1, 1, 3);
    GXSetTevSwapModeTable(3, 2, 2, 2, 3);
    for (i = 0; i < 16; i++) {
        GXSetTevDirect(i);
    }
    GXSetNumIndStages(0);
    GXSetIndTexCoordScale(0, 0, 0);
    GXSetIndTexCoordScale(1, 0, 0);
    GXSetIndTexCoordScale(2, 0, 0);
    GXSetIndTexCoordScale(3, 0, 0);
    GXSetFog(0, 0.0f, 1.0f, 0.1f, 1.0f, black);
    GXSetFogRangeAdj(0, 0, 0);
    GXSetBlendMode(0, 4, 5, 0);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(1);
    GXSetZMode(1, 3, 1);
    GXSetZCompLoc(1);
    GXSetDither(1);
    GXSetDstAlpha(0, 0);
    GXSetPixelFmt(0, 0);
    GXSetFieldMask(1, 1);
    GXSetFieldMode(rmode->field_rendering, (rmode->viHeight == 2 * rmode->xfbHeight) ? 1 : 0);
    GXSetDispCopySrc(0, 0, rmode->fbWidth, rmode->efbHeight);
    GXSetDispCopyDst(rmode->fbWidth, rmode->efbHeight);
    GXSetDispCopyYScale((f32)rmode->xfbHeight / (f32)rmode->efbHeight);
    GXSetCopyClamp(3);
    GXSetCopyFilter(rmode->aa, rmode->sample_pattern, 1, rmode->vfilter);
    GXSetDispCopyGamma(0);
    GXSetDispCopyFrame2Field(0);
    GXClearBoundingBox();
    GXPokeColorUpdate(1);
    GXPokeAlphaUpdate(1);
    GXPokeDither(0);
    GXPokeBlendMode(0, 0, 1, 15);
    GXPokeAlphaMode(7, 0);
    GXPokeAlphaRead(1);
    GXPokeDstAlpha(0, 0);
    GXPokeZMode(1, 7, 1);
    GXSetGPMetric(35, 22);
    GXClearGPMetric();
}
