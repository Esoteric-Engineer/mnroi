typedef struct {
    char pad0[14];
    short f14;
    char pad16[76];
    void* f92;
} FileHandle;

extern int _close_r(void* device, short flag);

asm int __sclose(FileHandle* stream)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    lha     r4, 14(r3)
    lwz     r3, 92(r3)
    bl      _close_r
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
