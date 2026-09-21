typedef struct FILE FILE;

extern FILE* lbl_8066C3B0;
extern FILE* fn_80178568(FILE* file, const char* name, const char* mode);

asm FILE* fopen(const char* name, const char* mode)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    mr      r0, r3
    mr      r5, r4
    lwz     r3, lbl_8066C3B0
    mr      r4, r0
    bl      fn_80178568
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
