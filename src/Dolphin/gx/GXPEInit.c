typedef unsigned short u16;
typedef unsigned long u32;

extern volatile u16* __peReg;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

extern char FinishQueue[8];

extern void __OSSetInterruptHandler(int interrupt, void* handler);
extern void __OSUnmaskInterrupts(u32 mask);
extern void OSInitThreadQueue(void* queue);
extern void GXTokenInterruptHandler(int interrupt, void* context);
extern void GXFinishInterruptHandler(int interrupt, void* context);

void __GXPEInit(void)
{
    u32 reg;

    __OSSetInterruptHandler(0x12, GXTokenInterruptHandler);
    __OSSetInterruptHandler(0x13, GXFinishInterruptHandler);
    OSInitThreadQueue(FinishQueue);
    __OSUnmaskInterrupts(0x2000);
    __OSUnmaskInterrupts(0x1000);
    reg = __peReg[5];
    SET_REG_FIELD(reg, 1, 2, 1);
    SET_REG_FIELD(reg, 1, 3, 1);
    SET_REG_FIELD(reg, 1, 0, 1);
    SET_REG_FIELD(reg, 1, 1, 1);
    __peReg[5] = reg;
}
