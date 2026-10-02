typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef void (*GXBreakPtCallback)(void);

typedef struct OSContext {
    char pad[0x2C8];
} OSContext;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x8];
    u32 cpEnable;
    u32 cpStatus;
} __GXDataStruct;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))
#define GET_REG_FIELD(reg, size, shift) \
    ((int)((reg) >> (shift)) & ((1 << (size)) - 1))

extern __GXDataStruct* const __GXData;
extern volatile u16* __cpReg;

u32 __GXOverflowCount;
GXBreakPtCallback BreakPointCB;
u32 GXOverflowSuspendInProgress;
u8 CPGPLinked;
u32 __GXCurrentThread;
u32 GPFifo;
u32 CPUFifo;

extern void OSResumeThread(u32 thread);
extern void OSSuspendThread(u32 thread);
extern void OSClearContext(OSContext* ctx);
extern void OSSetCurrentContext(OSContext* ctx);
extern void __GXWriteFifoIntEnable(u8 a, u8 b);
extern void __GXWriteFifoIntReset(u8 a, u8 b);

static inline void GXOverflowHandler(short interrupt, OSContext* context)
{
    __GXOverflowCount++;
    __GXWriteFifoIntEnable(0, 1);
    __GXWriteFifoIntReset(1, 0);
    GXOverflowSuspendInProgress = 1;
    OSSuspendThread(__GXCurrentThread);
}

static inline void GXUnderflowHandler(short interrupt, OSContext* context)
{
    OSResumeThread(__GXCurrentThread);
    GXOverflowSuspendInProgress = 0;
    __GXWriteFifoIntReset(1, 1);
    __GXWriteFifoIntEnable(1, 0);
}

static inline void GXBreakPointHandler(short interrupt, OSContext* context)
{
    OSContext exceptionContext;

    SET_REG_FIELD(__GXData->cpEnable, 1, 5, 0);
    __cpReg[1] = __GXData->cpEnable;
    if (BreakPointCB != 0) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        BreakPointCB();
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

void GXCPInterruptHandler(short interrupt, OSContext* context)
{
    __GXData->cpStatus = __cpReg[0];
    if (GET_REG_FIELD(__GXData->cpEnable, 1, 3) && GET_REG_FIELD(__GXData->cpStatus, 1, 1)) {
        GXUnderflowHandler(interrupt, context);
    }
    if (GET_REG_FIELD(__GXData->cpEnable, 1, 2) && GET_REG_FIELD(__GXData->cpStatus, 1, 0)) {
        GXOverflowHandler(interrupt, context);
    }
    if (GET_REG_FIELD(__GXData->cpEnable, 1, 5) && GET_REG_FIELD(__GXData->cpStatus, 1, 4)) {
        GXBreakPointHandler(interrupt, context);
    }
}
