typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef void (*GXDrawDoneCallback)(void);

typedef struct OSContext {
    char pad[0x2C8];
} OSContext;

extern volatile u16* __peReg;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

extern GXDrawDoneCallback DrawDoneCB;
extern u8 DrawDone;
extern char FinishQueue[8];

extern void OSClearContext(OSContext* ctx);
extern void OSSetCurrentContext(OSContext* ctx);
extern void OSWakeupThread(void* queue);

void GXFinishInterruptHandler(int interrupt, OSContext* context)
{
    OSContext exceptionContext;
    u32 reg;

    reg = __peReg[5];
    SET_REG_FIELD(reg, 1, 3, 1);
    __peReg[5] = reg;
    DrawDone = 1;
    if (DrawDoneCB != 0) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        DrawDoneCB();
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
    OSWakeupThread(FinishQueue);
}
