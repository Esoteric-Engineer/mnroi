typedef struct OSContext OSContext;

extern void OSClearContext(OSContext* context);

asm void OSInitContext(register OSContext* context, register unsigned long pc, register unsigned long newsp)
{
    // clang-format off
    nofralloc
    stw     pc, 0x198(context)
    stw     newsp, 0x4(context)
    li      r11, 0
    ori     r11, r11, 0x9032
    stw     r11, 0x19C(context)
    li      r0, 0
    stw     r0, 0x80(context)
    stw     r0, 0x8C(context)
    stw     r2, 0x8(context)
    stw     r13, 0x34(context)
    stw     r0, 0xc(context)
    stw     r0, 0x10(context)
    stw     r0, 0x14(context)
    stw     r0, 0x18(context)
    stw     r0, 0x1c(context)
    stw     r0, 0x20(context)
    stw     r0, 0x24(context)
    stw     r0, 0x28(context)
    stw     r0, 0x2c(context)
    stw     r0, 0x30(context)
    stw     r0, 56(context)
    stw     r0, 60(context)
    stw     r0, 64(context)
    stw     r0, 68(context)
    stw     r0, 72(context)
    stw     r0, 76(context)
    stw     r0, 80(context)
    stw     r0, 84(context)
    stw     r0, 88(context)
    stw     r0, 92(context)
    stw     r0, 96(context)
    stw     r0, 100(context)
    stw     r0, 104(context)
    stw     r0, 108(context)
    stw     r0, 112(context)
    stw     r0, 116(context)
    stw     r0, 120(context)
    stw     r0, 124(context)
    stw     r0, 0x1A4(context)
    stw     r0, 0x1A8(context)
    stw     r0, 0x1AC(context)
    stw     r0, 0x1B0(context)
    stw     r0, 0x1B4(context)
    stw     r0, 0x1B8(context)
    stw     r0, 0x1BC(context)
    stw     r0, 0x1C0(context)
    b       OSClearContext
    // clang-format on
}
