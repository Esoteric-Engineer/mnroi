unsigned long lbl_8066CE98 = 0x4000;

unsigned long lbl_8066F95C;
void* lbl_8066F958;
unsigned long lbl_8066F954;
unsigned long lbl_8066F950;
unsigned long lbl_8066F94C;
unsigned long lbl_8066F948;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int enabled);
extern unsigned long OSGetArenaHi(void);
extern unsigned long OSGetArenaLo(void);
extern void PPCHalt(void);
extern void VMBASEInit(void* swapPageCallback);
extern void __VMAllocVirtualToARAMLUT(void);
extern void __VMAllocARAMToVirtualLUT(void);
extern void __VMAllocMRAMSwapSpace(void);
extern void __VMSwapPageIn(void);
void _savegpr_27(void);
void _restgpr_27(void);

// One-time VM init:
// Records the MRAM swap size (and its page count >>12), ARAM base and ARAM size, PPCHalts on a dead arena or an out-of-range argument, then starts VMBASE on the swap-in handler.
// GCC output, so asm.
asm void VMInit(unsigned long mramSize, unsigned long aramBase, unsigned long aramSize)
{
    // clang-format off
    nofralloc
    stwu    r1, -0x20(r1)
    mflr    r0
    stw     r0, 0x24(r1)
    addi    r11, r1, 0x20
    bl      _savegpr_27
    lwz     r0, lbl_8066F95C
    mr      r27, r3
    mr      r28, r4
    mr      r29, r5
    cmpwi   r0, 0
    bne     L_80400A94
    bl      OSDisableInterrupts
    srwi    r0, r27, 12
    li      r4, 1
    stw     r4, lbl_8066F95C
    mr      r30, r3
    stw     r28, lbl_8066CE98
    stw     r29, lbl_8066F950
    stw     r27, lbl_8066F948
    stw     r0, lbl_8066F954
    bl      OSGetArenaHi
    mr      r31, r3
    bl      OSGetArenaLo
    cmplw   r3, r31
    bne     L_80400A30
    bl      PPCHalt
    b       L_80400A74
L_80400A30:
    cmplwi  r28, 0x4000
    bge     L_80400A40
    bl      PPCHalt
    b       L_80400A74
L_80400A40:
    clrlwi. r0, r28, 31
    beq     L_80400A50
    bl      PPCHalt
    b       L_80400A74
L_80400A50:
    lis     r3, 0x100
    subi    r0, r3, 0x4000
    cmplw   r29, r0
    ble     L_80400A68
    bl      PPCHalt
    b       L_80400A74
L_80400A68:
    cmplw   r27, r3
    ble     L_80400A74
    bl      PPCHalt
L_80400A74:
    lis     r3, __VMSwapPageIn@ha
    addi    r3, r3, __VMSwapPageIn@l
    bl      VMBASEInit
    bl      __VMAllocVirtualToARAMLUT
    bl      __VMAllocARAMToVirtualLUT
    bl      __VMAllocMRAMSwapSpace
    mr      r3, r30
    bl      OSRestoreInterrupts
L_80400A94:
    addi    r11, r1, 0x20
    bl      _restgpr_27
    lwz     r0, 0x24(r1)
    mtlr    r0
    addi    r1, r1, 0x20
    blr
    // clang-format on
}
