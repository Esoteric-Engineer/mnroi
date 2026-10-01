typedef unsigned short u16;
typedef unsigned long u32;
typedef void (*GXDrawSyncCallback)(u16 token);

typedef struct OSContext {
    char pad[0x2C8];
} OSContext;

extern volatile u16* __peReg;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))
extern GXDrawSyncCallback TokenCB;

extern void OSClearContext(OSContext* ctx);
extern void OSSetCurrentContext(OSContext* ctx);

void GXTokenInterruptHandler(int interrupt, OSContext* context)
{
    u16 token;
    OSContext exceptionContext;
    u32 reg;

    token = __peReg[7];
    if (TokenCB != 0) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        TokenCB(token);
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
    reg = __peReg[5];
    SET_REG_FIELD(reg, 1, 2, 1);
    __peReg[5] = reg;
}
