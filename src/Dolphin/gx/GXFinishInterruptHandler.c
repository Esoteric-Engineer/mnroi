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

extern GXDrawDoneCallback lbl_8066F494;
extern u8 lbl_8066F498;
extern char lbl_8066F49C[8];

extern void OSClearContext(OSContext* ctx);
extern void OSSetCurrentContext(OSContext* ctx);
extern void fn_80180CE8(void* queue);

void GXFinishInterruptHandler(int interrupt, OSContext* context)
{
    OSContext exceptionContext;
    u32 reg;

    reg = __peReg[5];
    SET_REG_FIELD(reg, 1, 3, 1);
    __peReg[5] = reg;
    lbl_8066F498 = 1;
    if (lbl_8066F494 != 0) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        lbl_8066F494();
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
    fn_80180CE8(lbl_8066F49C);
}
