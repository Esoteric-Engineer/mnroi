extern void* lbl_8066C3B0;
extern void vfprintf(void);

asm int vprintf(const char* fmt, void* args)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x8(r1)
    mflr    r0
    stw     r0, 0xc(r1)
    lwz     r9, lbl_8066C3B0
    mr      r0, r3
    mr      r5, r4
    lwz     r3, 0x8(r9)
    mr      r4, r0
    bl      vfprintf
    lwz     r0, 0xc(r1)
    mtlr    r0
    addi    r1, r1, 0x8
    blr
    // clang-format on
}
