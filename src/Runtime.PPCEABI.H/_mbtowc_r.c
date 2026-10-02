extern int strlen(const char* s);
extern int strcmp(const char* a, const char* b);

#pragma section R ".rodata.1"
__declspec(section ".rodata.1") const char SjisLocaleName[] = "C-SJIS";
__declspec(section ".rodata.1") const char EucjpLocaleName[] = "C-EUCJP";
__declspec(section ".rodata.1") const char JisLocaleName[] = "C-JIS";

// JIS_STATE/JIS_ACTION are int-sized enums, 12 states x 9 JIS_CHAR_TYPE columns; rows 10-11 are unused padding.
static long JIS_state_table[12][9] = {
    {1, 10, 10, 10, 10, 10, 10, 10, 10},
    {10, 2, 10, 10, 10, 10, 10, 10, 10},
    {10, 10, 10, 3, 3, 10, 10, 10, 10},
    {6, 4, 4, 4, 4, 4, 11, 4, 11},
    {11, 5, 5, 5, 5, 5, 11, 5, 11},
    {8, 10, 10, 10, 10, 10, 11, 10, 10},
    {11, 11, 7, 11, 11, 11, 11, 11, 11},
    {11, 11, 11, 11, 0, 0, 11, 11, 11},
    {11, 11, 9, 11, 11, 11, 11, 11, 11},
    {11, 11, 11, 11, 10, 10, 11, 11, 11},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
};

static long JIS_action_table[12][9] = {
    {5, 0, 0, 0, 0, 0, 6, 0, 0},
    {0, 5, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 4, 4, 0, 0, 0, 0},
    {5, 5, 5, 5, 5, 5, 7, 5, 7},
    {7, 5, 5, 5, 5, 5, 7, 5, 7},
    {5, 2, 2, 2, 2, 2, 7, 2, 2},
    {7, 7, 5, 7, 7, 7, 7, 7, 7},
    {7, 7, 7, 7, 5, 5, 7, 7, 7},
    {7, 7, 5, 7, 7, 7, 7, 7, 7},
    {7, 7, 7, 7, 1, 1, 7, 7, 7},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
};

// _mbtowc_r(reent, pwc, s, n, state):
// Newlib multibyte-to-wchar. Dispatches on the locale name (C-SJIS / C-EUCJP / C-JIS) and falls back to a plain byte copy.
asm int _mbtowc_r(void* reent, unsigned short* pwc, const char* s, unsigned long n, void* state)
{
    // clang-format off
    nofralloc
    stwu r1, -0x28(r1)
    mflr r0
    mfcr r12
    stmw r27, 0x14(r1)
    stw r0, 0x2c(r1)
    stw r12, 0x10(r1)
    mr r30, r3
    mr r31, r5
    mr r27, r6
    mr r29, r7
    mr. r28, r4
    bne L_80171308
    addi r28, r1, 0x8
L_80171308:
    cmpwi cr4, r31, 0x0
    beq cr4, L_8017131C
    cmpwi r27, 0x0
    li r3, -0x1
    beq L_801715E4
L_8017131C:
    lwz r3, 0x34(r30)
    cmpwi r3, 0x0
    beq L_801715BC
    bl strlen
    cmplwi r3, 0x1
    ble L_801715BC
    lwz r3, 0x34(r30)
    lis r4, SjisLocaleName@ha
    addi r4, r4, SjisLocaleName@l
    bl strcmp
    cmpwi r3, 0x0
    bne L_8017139C
    lbz r10, 0x0(r31)
    clrlwi r9, r10, 24
    beq cr4, L_801715E0
    subi r0, r9, 0x81
    cmplwi r0, 0x1e
    ble L_80171370
    subi r0, r9, 0xe0
    cmplwi r0, 0xf
    bgt L_801715BC
L_80171370:
    lbz r5, 0x1(r31)
    cmplwi r27, 0x1
    clrlwi r11, r5, 24
    ble L_801715B4
    subi r0, r11, 0x40
    cmplwi r0, 0x3e
    ble L_801713E8
    subi r0, r11, 0x80
    cmplwi r0, 0x7c
    ble L_801713E8
    b L_801715B4
L_8017139C:
    lwz r3, 0x34(r30)
    lis r4, EucjpLocaleName@ha
    addi r4, r4, EucjpLocaleName@l
    bl strcmp
    cmpwi r3, 0x0
    bne L_801713FC
    lbz r10, 0x0(r31)
    clrlwi r9, r10, 24
    beq cr4, L_801715E0
    subi r0, r9, 0xa1
    cmplwi r0, 0x5d
    bgt L_801715BC
    lbz r5, 0x1(r31)
    cmplwi r27, 0x1
    clrlwi r11, r5, 24
    ble L_801715B4
    subi r0, r11, 0xa1
    cmplwi r0, 0x5d
    bgt L_801715B4
L_801713E8:
    slwi r0, r10, 8
    li r3, 0x2
    or r0, r5, r0
    sth r0, 0x0(r28)
    b L_801715E4
L_801713FC:
    lwz r3, 0x34(r30)
    lis r4, JisLocaleName@ha
    addi r4, r4, JisLocaleName@l
    bl strcmp
    cmpwi r3, 0x0
    bne L_801715BC
    bne cr4, L_80171424
    stw r31, 0x0(r29)
    li r3, 0x1
    b L_801715E4
L_80171424:
    lwz r0, 0x0(r29)
    li r6, 0x0
    cmpwi r0, 0x0
    beq L_80171438
    li r6, 0x3
L_80171438:
    li r3, 0x0
    mr r8, r31
    cmplw r3, r27
    bge L_801715B4
    lis r9, JIS_action_table@ha
    lis r11, JIS_state_table@ha
    addi r5, r9, JIS_action_table@l
    addi r11, r11, JIS_state_table@l
    li r7, 0x0
    li r4, 0x1
L_80171460:
    lbzx r9, r31, r3
    cmpwi r9, 0x28
    beq L_801714D0
    bgt L_80171494
    cmpwi r9, 0x1b
    beq L_801714B8
    bgt L_80171488
    cmpwi r9, 0x0
    beq L_801714E8
    b L_801714F0
L_80171488:
    cmpwi r9, 0x24
    beq L_801714C0
    b L_801714F0
L_80171494:
    cmpwi r9, 0x42
    beq L_801714D8
    bgt L_801714AC
    cmpwi r9, 0x40
    beq L_801714C8
    b L_801714F0
L_801714AC:
    cmpwi r9, 0x4a
    beq L_801714E0
    b L_801714F0
L_801714B8:
    li r10, 0x0
    b L_80171504
L_801714C0:
    li r10, 0x1
    b L_80171504
L_801714C8:
    li r10, 0x3
    b L_80171504
L_801714D0:
    li r10, 0x2
    b L_80171504
L_801714D8:
    li r10, 0x4
    b L_80171504
L_801714E0:
    li r10, 0x5
    b L_80171504
L_801714E8:
    li r10, 0x6
    b L_80171504
L_801714F0:
    subi r0, r9, 0x21
    li r10, 0x8
    cmplwi r0, 0x5d
    bgt L_80171504
    li r10, 0x7
L_80171504:
    mulli r9, r6, 0x24
    slwi r0, r10, 2
    add r0, r0, r9
    lwzx r9, r5, r0
    lwzx r6, r11, r0
    cmplwi r9, 0x4
    bgt L_8017153C
    cmplwi r9, 0x3
    bge L_801715A0
    cmpwi r9, 0x1
    beq L_80171570
    cmplwi r9, 0x1
    bgt L_8017157C
    b L_8017155C
L_8017153C:
    cmpwi r9, 0x6
    beq L_80171550
    cmplwi r9, 0x6
    blt L_801715A8
    b L_801715B4
L_80171550:
    stw r7, 0x0(r29)
    sth r7, 0x0(r28)
    b L_801715E4
L_8017155C:
    stw r7, 0x0(r29)
    addi r3, r3, 0x1
    lbz r0, 0x0(r8)
    sth r0, 0x0(r28)
    b L_801715E4
L_80171570:
    stw r7, 0x0(r29)
    addi r3, r3, 0x1
    b L_80171588
L_8017157C:
    stw r4, 0x0(r29)
    subf r3, r31, r8
    addi r3, r3, 0x2
L_80171588:
    lbz r0, 0x0(r8)
    lbz r9, 0x1(r8)
    slwi r0, r0, 8
    add r9, r9, r0
    sth r9, 0x0(r28)
    b L_801715E4
L_801715A0:
    add r9, r31, r3
    addi r8, r9, 0x1
L_801715A8:
    addi r3, r3, 0x1
    cmplw r3, r27
    blt L_80171460
L_801715B4:
    li r3, -0x1
    b L_801715E4
L_801715BC:
    beq cr4, L_801715E0
    lbz r9, 0x0(r31)
    li r3, 0x0
    sth r9, 0x0(r28)
    lbz r0, 0x0(r31)
    cmpwi r0, 0x0
    beq L_801715E4
    li r3, 0x1
    b L_801715E4
L_801715E0:
    li r3, 0x0
L_801715E4:
    lwz r0, 0x2c(r1)
    lwz r12, 0x10(r1)
    mtlr r0
    lmw r27, 0x14(r1)
    mtcrf 8, r12
    addi r1, r1, 0x28
    blr
    // clang-format on
}
