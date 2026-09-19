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
extern GXDrawSyncCallback lbl_8066F490;

extern void lbl_8017C728(OSContext* ctx);
extern void fn_8017C530(OSContext* ctx);

void GXTokenInterruptHandler(int interrupt, OSContext* context)
{
    u16 token;
    OSContext exceptionContext;
    u32 reg;

    token = __peReg[7];
    if (lbl_8066F490 != 0) {
        lbl_8017C728(&exceptionContext);
        fn_8017C530(&exceptionContext);
        lbl_8066F490(token);
        lbl_8017C728(&exceptionContext);
        fn_8017C530(context);
    }
    reg = __peReg[5];
    SET_REG_FIELD(reg, 1, 2, 1);
    __peReg[5] = reg;
}
