typedef struct {
    char pad0[14];
    short f14;
    char pad16[76];
    void* f92;
} FileHandle;

extern int fn_80178D48(void* device, short flag);

asm int fn_80178D20(FileHandle* stream)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    lha     r4, 14(r3)
    lwz     r3, 92(r3)
    bl      fn_80178D48
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
