extern void fn_8016A078(void);
extern void fn_8016C148(void);

asm void fn_8016C094(void)
{
    // clang-format off
    nofralloc
    mfspr   r5, 18
    rlwinm. r5, r5, 10, 31, 31
    beq     L_8016C0F4
    stw     r0, 0(r4)
    stw     r1, 4(r4)
    stw     r2, 8(r4)
    stmw    r6, 0x18(r4)
    mfspr   r0, 913
    stw     r0, 0x1A8(r4)
    mfspr   r0, 914
    stw     r0, 0x1AC(r4)
    mfspr   r0, 915
    stw     r0, 0x1B0(r4)
    mfspr   r0, 916
    stw     r0, 0x1B4(r4)
    mfspr   r0, 917
    stw     r0, 0x1B8(r4)
    mfspr   r0, 918
    stw     r0, 0x1BC(r4)
    mfspr   r0, 919
    stw     r0, 0x1C0(r4)
    mfspr   r5, 18
    mfspr   r6, 19
    b       fn_8016C148
L_8016C0F4:
    lwz     r3, 0x80(r4)
    mtcrf   255, r3
    lwz     r3, 0x84(r4)
    mtlr    r3
    lwz     r3, 0x88(r4)
    mtctr   r3
    lwz     r3, 0x8C(r4)
    mtspr   1, r3
    lwz     r3, 0x198(r4)
    mtspr   26, r3
    lwz     r3, 0x19C(r4)
    mtspr   27, r3
    lwz     r3, 0xC(r4)
    lwz     r5, 0x14(r4)
    lwz     r4, 0x10(r4)
    b       fn_8016A078
    // clang-format on
}
