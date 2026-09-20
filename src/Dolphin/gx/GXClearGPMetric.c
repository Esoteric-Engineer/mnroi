typedef unsigned short u16;
typedef unsigned long u32;

extern volatile u16* __cpReg;

void GXClearGPMetric(void)
{
    u32 reg;

    reg = 4;
    __cpReg[2] = reg;
}
