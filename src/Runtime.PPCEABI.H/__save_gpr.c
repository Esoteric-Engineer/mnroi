void _savegpr_14(void);
void _savegpr_15(void);
void _savegpr_16(void);
void _savegpr_17(void);
void _savegpr_18(void);
void _savegpr_19(void);
void _savegpr_20(void);
void _savegpr_21(void);
void _savegpr_22(void);
void _savegpr_23(void);
void _savegpr_24(void);
void _savegpr_25(void);
void _savegpr_26(void);
void _savegpr_27(void);
void _savegpr_28(void);
void _savegpr_29(void);
void _savegpr_30(void);
void _savegpr_31(void);

asm void __save_gpr(void)
{
    // clang-format off
    nofralloc
    entry _savegpr_14
    stw r14, -72(r11)
    entry _savegpr_15
    stw r15, -68(r11)
    entry _savegpr_16
    stw r16, -64(r11)
    entry _savegpr_17
    stw r17, -60(r11)
    entry _savegpr_18
    stw r18, -56(r11)
    entry _savegpr_19
    stw r19, -52(r11)
    entry _savegpr_20
    stw r20, -48(r11)
    entry _savegpr_21
    stw r21, -44(r11)
    entry _savegpr_22
    stw r22, -40(r11)
    entry _savegpr_23
    stw r23, -36(r11)
    entry _savegpr_24
    stw r24, -32(r11)
    entry _savegpr_25
    stw r25, -28(r11)
    entry _savegpr_26
    stw r26, -24(r11)
    entry _savegpr_27
    stw r27, -20(r11)
    entry _savegpr_28
    stw r28, -16(r11)
    entry _savegpr_29
    stw r29, -12(r11)
    entry _savegpr_30
    stw r30, -8(r11)
    entry _savegpr_31
    stw r31, -4(r11)
    blr
    // clang-format on
}
