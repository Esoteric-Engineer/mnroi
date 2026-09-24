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
volatile u32 __PIRegs[0x20] : 0xCC003000;
extern u16* __memReg;

extern void* GXGetGPFifo(void);
extern OSTime OSGetTime(void);

#define GX_GET_MEM_REG(offset) (*(volatile u16*)((__memReg) + (offset)))

static inline void __GXAbortWait(u32 clocks)
{
    OSTime time0;
    OSTime time1;

    time0 = OSGetTime();
    do {
        time1 = OSGetTime();
    } while (time1 - time0 <= (clocks / 4));
}

static inline u32 __GXReadMEMCounterU32(u32 regAddrL, u32 regAddrH)
{
    u32 ctrH0;
    u32 ctrH1;
    u32 ctrL;

    ctrH0 = GX_GET_MEM_REG(regAddrH);
    while (1) {
        ctrH1 = ctrH0;
        ctrL = GX_GET_MEM_REG(regAddrL);
        ctrH0 = GX_GET_MEM_REG(regAddrH);

        if (ctrH0 == ctrH1) {
            break;
        }
    }

    return (ctrH0 << 16) | ctrL;
}

void __GXAbort(void)
{
    u32 prev;
    u32 cur;
    u32 old;

    if (__GXData->unk5AA != 0 && GXGetGPFifo() != 0) {
        prev = __GXReadMEMCounterU32(0x28, 0x27);
        do {
            __GXAbortWait(32);
            cur = __GXReadMEMCounterU32(0x28, 0x27);
            old = prev;
            prev = cur;
        } while (cur != old);
    }
    __PIRegs[6] = 1;
    __GXAbortWait(200);
    __PIRegs[6] = 0;
    __GXAbortWait(20);
}
