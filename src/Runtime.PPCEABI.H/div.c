typedef struct {
    int quot;
    int rem;
} div_t;

asm div_t div(int numer, int denom)
{
    // clang-format off
    nofralloc
    divw    r9, r4, r5
    cmpwi   r4, 0
    mullw   r0, r9, r5
    mr      r11, r9
    subf    r12, r0, r4
    blt     negNumer
    cmpwi   r12, 0
    bge     store
    addi    r11, r11, 1
    subf    r12, r5, r12
    b       store
negNumer:
    cmpwi   r12, 0
    ble     store
    addi    r11, r11, -1
    add     r12, r12, r5
store:
    stw     r11, 0(r3)
    stw     r12, 4(r3)
    blr
    // clang-format on
}
