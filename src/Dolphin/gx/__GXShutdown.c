typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long long s64;
typedef s64 OSTime;

typedef struct {
    u8 pad0[0x5AA];
    u8 unk5AA;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;
extern volatile u16* __cpReg;
extern u16* __memReg;

extern u32 lbl_8066F458;
extern OSTime lbl_8066F460;
extern u32 lbl_8066F468;

extern OSTime OSGetTime(void);
extern void* GXSetBreakPtCallback(void* cb);
extern void* GXSetDrawSyncCallback(void* cb);
extern void* GXSetDrawDoneCallback(void* cb);
extern void PPCSync(void);
extern void __GXAbort(void);

volatile u32 GXWGFifo : 0xCC008000;

#pragma peephole off
static inline u32 __GXReadMEMCounterU32(u32 regAddrL, u32 regAddrH)
{
    volatile u16* pH = (volatile u16*)__memReg + regAddrH;
    volatile u16* pL = (volatile u16*)__memReg + regAddrL;
    u32 ctrH0;
    u32 ctrH1;
    u32 ctrL;

    ctrH0 = *pH;
    while (1) {
        ctrH1 = ctrH0;
        ctrH0 = *pH;
        ctrL = *pL;
        if (ctrH0 == ctrH1) {
            break;
        }
    }
    return (ctrH0 << 16) | ctrL;
}

u32 __GXShutdown(int final)
{
    OSTime newTime;
    u32 newPeCount;

    if (!final) {
        if (!lbl_8066F468) {
            lbl_8066F458 = __GXReadMEMCounterU32(0x28, 0x27);
            lbl_8066F460 = OSGetTime();
            lbl_8066F468 = 1;
            return 0;
        }
        newTime = OSGetTime();
        newPeCount = __GXReadMEMCounterU32(0x28, 0x27);
        if (newTime - lbl_8066F460 < 10) {
            return 0;
        }
        if (newPeCount != lbl_8066F458) {
            lbl_8066F460 = newTime;
            lbl_8066F458 = newPeCount;
            return 0;
        }
    } else {
        GXSetBreakPtCallback(0);
        GXSetDrawSyncCallback(0);
        GXSetDrawDoneCallback(0);
        GXWGFifo = 0;
        GXWGFifo = 0;
        GXWGFifo = 0;
        GXWGFifo = 0;
        GXWGFifo = 0;
        GXWGFifo = 0;
        GXWGFifo = 0;
        GXWGFifo = 0;
        PPCSync();
        __cpReg[1] = 0;
        __cpReg[2] = 3;
        __GXData->unk5AA = 1;
        __GXAbort();
    }
    return 1;
}
