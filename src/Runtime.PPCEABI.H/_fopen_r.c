extern void* __sfp(void* reent);
extern int fn_80178F54(void* reent, const char* mode, int* flags);
extern int fn_80178E48(void* reent, const char* file, int flags, int perm);
extern void* __sread;
extern void* __swrite;
extern void* __sseek;
extern void* __sclose;
extern int _fseek_r(void* reent, void* fp, int offset, int whence);

// _fopen_r(reent, file, mode): open a FILE, install the stdio callbacks, seek to end for append.
asm void* _fopen_r(void* reent, const char* file, const char* mode)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x20(r1)
    mflr    r0
    stmw    r29, 0x14(r1)
    stw     r0, 0x24(r1)
    mr      r30, r4
    mr      r31, r3
    mr      r4, r5
    addi    r5, r1, 8
    bl      fn_80178F54
    mr.     r29, r3
    li      r3, 0
    beq     done
    mr      r3, r31
    bl      __sfp
    mr.     r31, r3
    bne     have_fp
    li      r3, 0
    b       done
have_fp:
    lhz     r0, 0xc(r31)
    mr      r4, r30
    lwz     r3, 0x5c(r31)
    li      r6, 0x1b6
    rlwinm  r0, r0, 0, 30, 30
    sth     r0, 0xc(r31)
    lwz     r5, 8(r1)
    bl      fn_80178E48
    mr.     r3, r3
    bge     opened
    li      r0, 0
    li      r3, 0
    sth     r0, 0xc(r31)
    b       done
opened:
    lis     r9, __sread@ha
    lis     r11, __swrite@ha
    lis     r10, __sseek@ha
    lis     r8, __sclose@ha
    addi    r9, r9, __sread@l
    addi    r11, r11, __swrite@l
    addi    r10, r10, __sseek@l
    addi    r8, r8, __sclose@l
    sth     r3, 0xe(r31)
    andi.   r0, r29, 0x100
    stw     r9, 0x20(r31)
    stw     r11, 0x24(r31)
    stw     r10, 0x28(r31)
    stw     r8, 0x2c(r31)
    sth     r29, 0xc(r31)
    stw     r31, 0x1c(r31)
    beq     no_append
    mr      r3, r31
    li      r4, 0
    li      r5, 2
    bl      _fseek_r
no_append:
    mr      r3, r31
done:
    lwz     r0, 0x24(r1)
    mtlr    r0
    lmw     r29, 0x14(r1)
    addi    r1, r1, 0x20
    blr
    // clang-format on
}
