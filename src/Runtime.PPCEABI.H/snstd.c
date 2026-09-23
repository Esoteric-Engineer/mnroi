typedef struct {
    void* f0;
    void* f4;
    void* f8;
    short f12;
    short f14;
    void* f16;
    char pad20[4];
    void* f24;
    void* f28;
    void* f32;
    void* f36;
    void* f40;
    void* f44;
    char pad48[44];
    void* f92;
} FileHandle;

extern void __sread(void);
extern void __swrite(void);
extern void __sseek(void);
extern void __sclose(void);

asm void snstd(FileHandle* stream, short a1, short a2, void* device)
{
    // clang-format off
    nofralloc
    lis     r9, __sread@ha
    lis     r11, __swrite@ha
    lis     r10, __sseek@ha
    lis     r8, __sclose@ha
    li      r0, 0
    addi    r9, r9, __sread@l
    addi    r11, r11, __swrite@l
    addi    r10, r10, __sseek@l
    addi    r8, r8, __sclose@l
    stw     r6, 92(r3)
    sth     r4, 12(r3)
    sth     r5, 14(r3)
    stw     r0, 24(r3)
    stw     r9, 32(r3)
    stw     r11, 36(r3)
    stw     r10, 40(r3)
    stw     r8, 44(r3)
    stw     r0, 0(r3)
    stw     r0, 4(r3)
    stw     r0, 8(r3)
    stw     r0, 16(r3)
    stw     r3, 28(r3)
    blr
    // clang-format on
}
