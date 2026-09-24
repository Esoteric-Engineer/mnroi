extern void _vfprintf_r(void);
extern void _vfiprintf_r(void);

asm int vfprintf(void* fp, const char* fmt, void* ap)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x8(r1)
    mflr    r0
    stw     r0, 0xc(r1)
    mr      r11, r4
    mr      r6, r5
    lbz     r0, 0(r11)
    mr      r4, r3
    mr      r9, r11
    cmpwi   r0, 0
    beq     endscan
scan:
    lbz     r0, 0(r9)
    cmpwi   r0, 0x25
    bne     next
    lbz     r0, 1(r9)
    cmpwi   r0, 0
    beq     next
    lbzu    r0, 1(r9)
    lwz     r3, 0x5c(r4)
    b       spec
spec_loop:
    lbzu    r0, 1(r9)
spec:
    extsb   r0, r0
    cmpwi   r0, 0x40
    bgt     spec_done
    lbz     r0, 1(r9)
    cmpwi   r0, 0
    bne     spec_loop
spec_done:
    lbz     r0, 0(r9)
    extsb   r0, r0
    cmpwi   r0, 0x4c
    beq     isfloat
    bgt     above_L
    cmpwi   r0, 0x45
    beq     isfloat
    cmpwi   r0, 0x47
    beq     isfloat
    b       next
above_L:
    cmpwi   r0, 0x67
    bgt     next
    cmpwi   r0, 0x65
    blt     next
isfloat:
    mr      r5, r11
    bl      _vfprintf_r
    b       done
next:
    lbzu    r0, 1(r9)
    cmpwi   r0, 0
    bne     scan
endscan:
    lwz     r3, 0x5c(r4)
    mr      r5, r11
    crclr   6
    bl      _vfiprintf_r
done:
    lwz     r0, 0xc(r1)
    mtlr    r0
    addi    r1, r1, 0x8
    blr
    // clang-format on
}
