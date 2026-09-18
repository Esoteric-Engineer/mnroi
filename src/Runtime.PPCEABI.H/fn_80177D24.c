typedef struct {
    unsigned char* ptr;
    int cnt;
} FileBuf;

extern void fn_80177CF8(unsigned char* dst, unsigned char* src, int n);
extern int fn_80177E24(FileBuf* stream);

asm int fn_80177D24(unsigned char* dst, unsigned int size, unsigned int nmemb, FileBuf* stream)
{
    // clang-format off
    nofralloc
    stwu    r1, -40(r1)
    mflr    r0
    stmw    r25, 12(r1)
    stw     r0, 44(r1)
    mr      r27, r4
    mr      r26, r5
    mr      r30, r6
    mullw.  r28, r26, r27
    bne     total_nonzero
    li      r3, 0
    b       epilogue
partial:
    subf    r3, r28, r25
    divwu   r3, r3, r27
    b       epilogue
total_nonzero:
    lwz     r0, 4(r30)
    cmpwi   r0, 0
    bge     cnt_ok
    li      r0, 0
    stw     r0, 4(r30)
cnt_ok:
    lwz     r31, 4(r30)
    mr      r29, r3
    mr      r25, r28
    cmplw   r28, r31
    ble     final_chunk
loop:
    lwz     r4, 0(r30)
    mr      r3, r29
    mr      r5, r31
    subf    r28, r31, r28
    bl      fn_80177CF8
    add     r29, r29, r31
    lwz     r0, 0(r30)
    mr      r3, r30
    add     r0, r0, r31
    stw     r0, 0(r30)
    bl      fn_80177E24
    cmpwi   r3, 0
    bne     partial
    lwz     r31, 4(r30)
    cmplw   r28, r31
    bgt     loop
final_chunk:
    lwz     r4, 0(r30)
    mr      r3, r29
    mr      r5, r28
    bl      fn_80177CF8
    lwz     r9, 4(r30)
    mr      r3, r26
    lwz     r0, 0(r30)
    subf    r9, r28, r9
    add     r0, r0, r28
    stw     r9, 4(r30)
    stw     r0, 0(r30)
epilogue:
    lwz     r0, 44(r1)
    mtlr    r0
    lmw     r25, 12(r1)
    addi    r1, r1, 40
    blr
    // clang-format on
}
