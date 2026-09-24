volatile unsigned int __SIRegs[0x100] : 0xCC006400;
volatile unsigned short __VIRegs[59] : 0xCC002000;

#define SI_STATUS_IDX 14
#define SI_COMCSR_TCINT_MASK (1u << 31)
#define SI_ERROR_BUSY 0x0080
#define VI_CLOCK_SEL 54

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern unsigned int Type[4];
extern long long __OSGetSystemTime(void);
extern void OSSetAlarm(void);
extern unsigned int VIGetTvFormat(void); // dtk auto-detected identity for fn_8018992C
extern void OSReport(const char* msg, ...); // dtk auto-detected identity for fn_8017CB7C
extern unsigned int SamplingRate; // unclaimed .sbss object, dtk auto-detected the real name
extern unsigned char XYNTSC[0x98]; // XYNTSC[12] table; XYPAL[12] (+0x30) and the "unknown TV format" error string (+0x60) are plain-offset siblings in the same unclaimed .data blob

typedef struct SIControl
{
    long chan;
    unsigned int poll;
    unsigned int inputBytes;
    void* input;
    void* callback;
} SIControl;

extern SIControl Si;
extern unsigned char lbl_804D1B78[]; // .data object right before Si; compiler's lis/addi base reaches Si's fields at offsets 68-84

// Core transfer engine:
//  - bails if a transfer is pending (Si.chan != -1)
//  - acknowledges the channel's status bits
//  - records the request in Si
//  - copies the output words into the SI I/O buffer
//  - composes SICOMCSR on a stack slot and writes it to kick the transfer
// Written as asm: 8x-unrolled output copy loop with a separately-scheduled remainder loop, plus byte-wise rlwimi bitfield stores on a stack slot -- too risky to reproduce from C.
asm int __SITransfer(long chan, void* output, unsigned int outputBytes, void* input,
                     unsigned int inputBytes, void* callback)
{
    // clang-format off
    nofralloc
    mflr    r0
    lis     r9, lbl_804D1B78@ha
    stw     r0, 4(r1)
    stwu    r1, -72(r1)
    stmw    r25, 44(r1)
    addi    r26, r3, 0
    addi    r27, r4, 0
    addi    r28, r5, 0
    addi    r29, r6, 0
    addi    r30, r7, 0
    addi    r31, r8, 0
    addi    r25, r9, lbl_804D1B78@l
    bl      OSDisableInterrupts
    lwz     r0, 68(r25)
    cmpwi   r0, -1
    beq     L801820FC
    bl      OSRestoreInterrupts
    li      r3, 0
    b       L801822A8
L801820FC:
    lis     r6, -13312
    slwi    r0, r26, 3
    lwz     r7, 25656(r6)
    lis     r4, 3840
    sraw    r0, r4, r0
    and     r7, r7, r0
    stw     r7, 25656(r6)
    addi    r0, r28, 3
    srwi    r4, r0, 2
    stw     r26, 68(r25)
    cmplwi  r4, 0
    li      r5, 0
    stw     r31, 84(r25)
    stw     r30, 76(r25)
    stw     r29, 80(r25)
    ble     L801821DC
    cmplwi  r4, 8
    addi    r7, r4, -8
    ble     L80182290
    addi    r0, r7, 7
    srwi    r0, r0, 3
    cmplwi  r7, 0
    mtctr   r0
    addi    r7, r27, 0
    addi    r6, r6, 25600
    ble     L80182290
L80182164:
    lwz     r0, 0(r7)
    addi    r5, r5, 8
    stw     r0, 128(r6)
    lwz     r0, 4(r7)
    stw     r0, 132(r6)
    lwz     r0, 8(r7)
    stw     r0, 136(r6)
    lwz     r0, 12(r7)
    stw     r0, 140(r6)
    lwz     r0, 16(r7)
    stw     r0, 144(r6)
    lwz     r0, 20(r7)
    stw     r0, 148(r6)
    lwz     r0, 24(r7)
    stw     r0, 152(r6)
    lwz     r0, 28(r7)
    addi    r7, r7, 32
    stw     r0, 156(r6)
    addi    r6, r6, 32
    bdnz    L80182164
    b       L80182290
L801821B8:
    subf    r0, r5, r4
    cmplw   r5, r4
    mtctr   r0
    bge     L801821DC
L801821C8:
    lwz     r0, 0(r6)
    addi    r6, r6, 4
    stw     r0, 128(r7)
    addi    r7, r7, 4
    bdnz    L801821C8
L801821DC:
    lis     r4, -13312
    addi    r6, r4, 25600
    lwzu    r0, 52(r6)
    li      r4, 1
    stw     r0, 36(r1)
    cmplwi  r31, 0
    lbz     r0, 36(r1)
    rlwimi  r0, r4, 7, 24, 24
    stb     r0, 36(r1)
    beq     L80182208
    b       L8018220C
L80182208:
    li      r4, 0
L8018220C:
    lbz     r0, 36(r1)
    rlwimi  r0, r4, 6, 25, 25
    cmplwi  r28, 128
    stb     r0, 36(r1)
    bne     L80182228
    li      r0, 0
    b       L8018222C
L80182228:
    mr      r0, r28
L8018222C:
    rlwinm  r4, r0, 0, 24, 31
    lbz     r0, 37(r1)
    rlwimi  r0, r4, 0, 25, 31
    cmplwi  r30, 128
    stb     r0, 37(r1)
    bne     L8018224C
    li      r0, 0
    b       L80182250
L8018224C:
    mr      r0, r30
L80182250:
    rlwinm  r4, r0, 0, 24, 31
    lbz     r0, 38(r1)
    rlwimi  r0, r4, 0, 25, 31
    stb     r0, 38(r1)
    li      r4, 1
    lbz     r0, 39(r1)
    rlwimi  r0, r26, 1, 29, 30
    stb     r0, 39(r1)
    lbz     r0, 39(r1)
    rlwimi  r0, r4, 0, 31, 31
    stb     r0, 39(r1)
    lwz     r0, 36(r1)
    stw     r0, 0(r6)
    bl      OSRestoreInterrupts
    li      r3, 1
    b       L801822A8
L80182290:
    lis     r6, -13312
    slwi    r0, r5, 2
    addi    r7, r6, 25600
    add     r6, r27, r0
    add     r7, r7, r0
    b       L801821B8
L801822A8:
    lmw     r25, 44(r1)
    lwz     r0, 76(r1)
    addi    r1, r1, 72
    mtlr    r0
    blr
    // clang-format on
}

#pragma peephole on // see docs/matching_notes.md: asm disables peephole for the rest of the TU

unsigned int SIGetStatus(int chan)
{
    int enabled;
    unsigned int sr;
    int chanShift;

    enabled = OSDisableInterrupts();
    sr = __SIRegs[SI_STATUS_IDX];
    chanShift = (3 - chan) * 8;
    sr >>= chanShift;

    if ((sr & 8) != 0)
    {
        if ((Type[chan] & SI_ERROR_BUSY) == 0)
        {
            Type[chan] = 8;
        }
    }

    OSRestoreInterrupts(enabled);
    return sr;
}

void SISetCommand(long chan, unsigned int command)
{
    __SIRegs[chan * 3] = command;
}

void SITransferCommands(void)
{
    __SIRegs[SI_STATUS_IDX] = SI_COMCSR_TCINT_MASK;
}

unsigned int SISetXY(unsigned int x, unsigned int y)
{
    unsigned int poll;
    int enabled;

    poll = x << 0x10;
    poll |= y << 8;
    enabled = OSDisableInterrupts();
    Si.poll &= 0xFC0000FF;
    Si.poll |= poll;
    poll = Si.poll;
    __SIRegs[0x30 / 4] = poll;
    OSRestoreInterrupts(enabled);
    return poll;
}

unsigned int SIEnablePolling(unsigned int poll)
{
    int enabled;
    unsigned int en;

    if (poll == 0)
    {
        return Si.poll;
    }

    enabled = OSDisableInterrupts();
    poll = poll >> 24;
    en = poll & 0xF0;
    poll &= ((en >> 4) | 0x03FFFFF0);
    poll &= 0xFC0000FF;

    Si.poll &= ~(en >> 4);
    Si.poll |= poll;
    poll = Si.poll;
    SITransferCommands();
    __SIRegs[0x30 / 4] = poll;
    OSRestoreInterrupts(enabled);
    return poll;
}

unsigned int SIDisablePolling(unsigned int poll)
{
    int enabled;

    if (poll == 0)
    {
        return Si.poll;
    }

    enabled = OSDisableInterrupts();
    poll = poll >> 24;
    poll &= 0xF0;
    poll = Si.poll & ~poll;
    __SIRegs[0x30 / 4] = poll;
    Si.poll = poll;
    OSRestoreInterrupts(enabled);
    return poll;
}

extern unsigned char Packet[]; // shared static blob; InputBufferValid/InputBuffer live at offsets +432/+448 within it

// Inlines SIGetStatus's own body (interrupt guard included).
// InputBufferValid/InputBuffer areaddressed via one shared base register with large literal displacements.
// Awkward to reproduce from plain C array/struct declarations, so transliterated directly instead.
asm int SIGetResponseRaw(int chan)
{
    // clang-format off
    nofralloc
    mflr    r0
    lis     r4, Packet@ha
    stw     r0, 4(r1)
    stwu    r1, -40(r1)
    stw     r31, 36(r1)
    addi    r31, r4, Packet@l
    stw     r30, 32(r1)
    addi    r30, r3, 0
    stw     r29, 28(r1)
    bl      OSDisableInterrupts
    lis     r4, -13312
    subfic  r0, r30, 3
    lwz     r29, 25656(r4)
    slwi    r0, r0, 3
    srw     r29, r29, r0
    rlwinm. r0, r29, 0, 28, 28
    beq     L80182538
    lis     r4, Type@ha
    slwi    r5, r30, 2
    addi    r0, r4, Type@l
    add     r4, r0, r5
    lwz     r0, 0(r4)
    rlwinm. r0, r0, 0, 24, 24
    bne     L80182538
    li      r0, 8
    stw     r0, 0(r4)
L80182538:
    bl      OSRestoreInterrupts
    rlwinm. r0, r29, 0, 26, 26
    beq     L80182584
    mulli   r4, r30, 12
    lis     r3, -13312
    addi    r0, r3, 25600
    add     r3, r0, r4
    slwi    r4, r30, 3
    lwz     r0, 4(r3)
    add     r6, r31, r4
    stw     r0, 448(r6)
    slwi    r0, r30, 2
    add     r4, r31, r0
    lwz     r5, 8(r3)
    li      r0, 1
    li      r3, 1
    stw     r5, 452(r6)
    stw     r0, 432(r4)
    b       L80182588
L80182584:
    li      r3, 0
L80182588:
    lwz     r0, 44(r1)
    lwz     r31, 36(r1)
    lwz     r30, 32(r1)
    lwz     r29, 28(r1)
    addi    r1, r1, 40
    mtlr    r0
    blr
    // clang-format on
}

// Same shape as SIGetResponseRaw (inlined directly into this caller), but with a real `bl` to SIGetStatus this time.
asm int SIGetResponse(int chan, void* data)
{
    // clang-format off
    nofralloc
    mflr    r0
    lis     r5, Packet@ha
    stw     r0, 4(r1)
    stwu    r1, -40(r1)
    stmw    r27, 20(r1)
    addi    r29, r3, 0
    addi    r30, r4, 0
    addi    r28, r5, Packet@l
    bl      OSDisableInterrupts
    addi    r31, r3, 0
    addi    r3, r29, 0
    bl      SIGetStatus
    rlwinm. r0, r3, 0, 26, 26
    beq     L80182614
    mulli   r4, r29, 12
    lis     r3, -13312
    addi    r0, r3, 25600
    add     r4, r0, r4
    slwi    r3, r29, 3
    lwz     r0, 4(r4)
    add     r5, r28, r3
    stw     r0, 448(r5)
    slwi    r0, r29, 2
    add     r3, r28, r0
    lwz     r4, 8(r4)
    li      r0, 1
    stw     r4, 452(r5)
    stw     r0, 432(r3)
L80182614:
    slwi    r0, r29, 2
    add     r3, r28, r0
    lwz     r27, 432(r3)
    li      r0, 0
    cmpwi   r27, 0
    stw     r0, 432(r3)
    beq     L80182648
    slwi    r0, r29, 3
    add     r3, r28, r0
    lwz     r0, 448(r3)
    stw     r0, 0(r30)
    lwz     r0, 452(r3)
    stw     r0, 4(r30)
L80182648:
    mr      r3, r31
    bl      OSRestoreInterrupts
    mr      r3, r27
    lmw     r27, 20(r1)
    lwz     r0, 44(r1)
    addi    r1, r1, 40
    mtlr    r0
    blr
    // clang-format on
}

extern unsigned char Alarm[]; // Alarm[4] (OSAlarm, sizeof 0x28), exactly fills this blob

// chan = alarm - Alarm (pointer difference / sizeof(OSAlarm), via magic-constant division), then dispatches Packet[chan] to __SITransfer if still pending.
// `context` is unused, matching the original. Same shared-base-register shape as SIGetResponseRaw, transliterated directly.
asm void AlarmHandler(void* alarm, void* context)
{
    // clang-format off
    nofralloc
    mflr    r0
    lis     r4, Alarm@ha
    stw     r0, 4(r1)
    addi    r0, r4, Alarm@l
    lis     r4, 26214
    subf    r0, r0, r3
    stwu    r1, -32(r1)
    addi    r3, r4, 26215
    mulhw   r0, r3, r0
    stw     r31, 28(r1)
    srawi   r0, r0, 4
    srwi    r3, r0, 31
    add     r0, r0, r3
    lis     r3, Packet@ha
    slwi    r4, r0, 5
    addi    r0, r3, Packet@l
    add     r31, r0, r4
    lwz     r3, 0(r31)
    cmpwi   r3, -1
    beq     L801826E0
    lwz     r4, 4(r31)
    lwz     r5, 8(r31)
    lwz     r6, 12(r31)
    lwz     r7, 16(r31)
    lwz     r8, 20(r31)
    bl      __SITransfer
    cmpwi   r3, 0
    beq     L801826E0
    li      r0, -1
    stw     r0, 0(r31)
L801826E0:
    lwz     r0, 36(r1)
    lwz     r31, 28(r1)
    addi    r1, r1, 32
    mtlr    r0
    blr
    // clang-format on
}

// Public entry point: rejects if a transfer is already pending for this channel or Si is mid-transfer.
// If `delay` puts the fire time in the future, schedules an OSAlarm (via OSSetAlarm) instead of transferring immediately; either way records the request in Packet[chan] for AlarmHandler to pick up later.
asm int SITransfer(long chan, void* output, unsigned int outputBytes, void* input,
                    unsigned int inputBytes, void* callback, long long delay)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 4(r1)
    stwu    r1, -96(r1)
    stmw    r19, 44(r1)
    addi    r24, r3, 0
    lis     r3, Packet@ha
    addi    r23, r3, Packet@l
    slwi    r0, r24, 5
    addi    r25, r4, 0
    addi    r26, r5, 0
    addi    r27, r6, 0
    addi    r28, r7, 0
    addi    r29, r8, 0
    addi    r31, r9, 0
    addi    r30, r10, 0
    add     r22, r23, r0
    bl      OSDisableInterrupts
    lwz     r0, 0(r22)
    addi    r21, r3, 0
    cmpwi   r0, -1
    bne     L80182758
    lis     r3, Si@ha
    lwz     r0, Si@l(r3)
    cmpw    r0, r24
    bne     L80182768
L80182758:
    mr      r3, r21
    bl      OSRestoreInterrupts
    li      r3, 0
    b       L8018284C
L80182768:
    bl      __OSGetSystemTime
    li      r0, 0
    xor     r5, r30, r0
    xor     r0, r31, r0
    or.     r0, r5, r0
    bne     L8018278C
    addi    r19, r4, 0
    addi    r20, r3, 0
    b       L801827A4
L8018278C:
    slwi    r0, r24, 3
    add     r6, r23, r0
    lwz     r5, 324(r6)
    lwz     r0, 320(r6)
    addc    r19, r30, r5
    adde    r20, r31, r0
L801827A4:
    xoris   r6, r3, 32768
    xoris   r5, r20, 32768
    subfc   r0, r19, r4
    subfe   r5, r5, r6
    subfe   r5, r6, r6
    neg.    r5, r5
    beq     L801827EC
    mulli   r0, r24, 40
    subfc   r30, r4, r19
    subfe   r31, r3, r20
    lis     r4, AlarmHandler@ha
    add     r3, r23, r0
    addi    r7, r4, AlarmHandler@l
    addi    r6, r30, 0
    addi    r5, r31, 0
    addi    r3, r3, 128
    bl      OSSetAlarm
    b       L80182820
L801827EC:
    addi    r3, r24, 0
    addi    r4, r25, 0
    addi    r5, r26, 0
    addi    r6, r27, 0
    addi    r7, r28, 0
    addi    r8, r29, 0
    bl      __SITransfer
    cmpwi   r3, 0
    beq     L80182820
    mr      r3, r21
    bl      OSRestoreInterrupts
    li      r3, 1
    b       L8018284C
L80182820:
    stw     r24, 0(r22)
    mr      r3, r21
    stw     r25, 4(r22)
    stw     r26, 8(r22)
    stw     r27, 12(r22)
    stw     r28, 16(r22)
    stw     r29, 20(r22)
    stw     r19, 28(r22)
    stw     r20, 24(r22)
    bl      OSRestoreInterrupts
    li      r3, 1
L8018284C:
    lmw     r19, 44(r1)
    lwz     r0, 100(r1)
    addi    r1, r1, 96
    mtlr    r0
    blr
    // clang-format on
}

extern void OSSetWirelessID(long chan, unsigned int id);
extern unsigned int OSGetWirelessID(long chan);
extern unsigned int lbl_8066F288;                     // likely __PADFixBits, file-scope

// `context` is unused, same as AlarmHandler.
// Clears then re-sets Type[chan]'s SI_ERROR_BUSY bit with the new error, timestamps TypeTime[chan], and either reports the type straight to the registered per-channel callbacks (inlined twice at its two call sites) or, on a wireless-ID mismatch, kicks off a 3-byte fixup SITransfer with itself as the completion callback.
asm void GetTypeCallback(int chan, unsigned int error, void* context)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 4(r1)
    stwu    r1, -48(r1)
    stmw    r26, 24(r1)
    addi    r27, r3, 0
    lis     r3, Type@ha
    addi    r0, r3, Type@l
    slwi    r29, r27, 2
    add     r30, r0, r29
    lis     r3, Packet@ha
    addi    r26, r4, 0
    addi    r31, r3, Packet@l
    lwz     r0, 0(r30)
    rlwinm  r0, r0, 0, 25, 23
    stw     r0, 0(r30)
    lwz     r0, 0(r30)
    or      r0, r0, r26
    stw     r0, 0(r30)
    bl      __OSGetSystemTime
    slwi    r0, r27, 3
    add     r5, r31, r0
    stw     r4, 292(r5)
    lis     r4, -32768
    clrlwi. r0, r26, 28
    stw     r3, 288(r5)
    srw     r4, r4, r27
    lwz     r3, lbl_8066F288
    lwz     r28, 0(r30)
    andc    r0, r3, r4
    stw     r0, lbl_8066F288
    and     r26, r3, r4
    bne     L80182900
    rlwinm  r3, r28, 0, 3, 4
    addis   r0, r3, -2048
    cmplwi  r0, 0
    bne     L80182900
    clrrwi. r0, r28, 31
    beq     L80182900
    rlwinm. r0, r28, 0, 5, 5
    beq     L80182958
L80182900:
    addi    r3, r27, 0
    li      r4, 0
    bl      OSSetWirelessID
    slwi    r0, r27, 4
    lwz     r30, 0(r30)
    add     r31, r31, r0
    li      r29, 0
    addi    r28, r29, 0
    addi    r31, r31, 352
L80182924:
    lwz     r12, 0(r31)
    cmplwi  r12, 0
    beq     L80182944
    stw     r28, 0(r31)
    mtlr    r12
    addi    r3, r27, 0
    addi    r4, r30, 0
    blrl
L80182944:
    addi    r29, r29, 1
    cmpwi   r29, 4
    addi    r31, r31, 4
    blt     L80182924
    b       L80182AE4
L80182958:
    mr      r3, r27
    bl      OSGetWirelessID
    cmpwi   r26, 0
    rlwinm  r26, r3, 8, 8, 23
    beq     L801829BC
    rlwinm. r0, r26, 0, 11, 11
    beq     L801829BC
    lis     r3, 208
    addi    r0, r3, -256
    and     r0, r26, r0
    oris    r0, r0, 19984
    add     r4, r31, r29
    stwu    r0, 496(r4)
    li      r0, 128
    lis     r3, GetTypeCallback@ha
    stw     r0, 0(r30)
    addi    r8, r3, GetTypeCallback@l
    addi    r3, r27, 0
    addi    r6, r30, 0
    li      r5, 3
    li      r7, 3
    li      r10, 0
    li      r9, 0
    bl      SITransfer
    b       L80182AE4
L801829BC:
    rlwinm. r0, r28, 0, 11, 11
    beq     L80182A30
    lis     r3, 208
    addi    r3, r3, -256
    and     r0, r26, r3
    and     r3, r28, r3
    cmplw   r0, r3
    beq     L80182A9C
    rlwinm. r0, r26, 0, 11, 11
    bne     L801829F4
    oris    r26, r3, 16
    addi    r3, r27, 0
    rlwinm  r4, r26, 24, 16, 31
    bl      OSSetWirelessID
L801829F4:
    oris    r0, r26, 19968
    add     r4, r31, r29
    stwu    r0, 496(r4)
    li      r0, 128
    lis     r3, GetTypeCallback@ha
    stw     r0, 0(r30)
    addi    r8, r3, GetTypeCallback@l
    addi    r3, r27, 0
    addi    r6, r30, 0
    li      r5, 3
    li      r7, 3
    li      r10, 0
    li      r9, 0
    bl      SITransfer
    b       L80182AE4
L80182A30:
    rlwinm. r0, r28, 0, 1, 1
    beq     L80182A90
    lis     r3, 208
    addi    r0, r3, -256
    and     r28, r28, r0
    oris    r28, r28, 16
    addi    r3, r27, 0
    rlwinm  r4, r28, 24, 16, 31
    bl      OSSetWirelessID
    oris    r0, r28, 19968
    add     r4, r31, r29
    stwu    r0, 496(r4)
    li      r0, 128
    lis     r3, GetTypeCallback@ha
    stw     r0, 0(r30)
    addi    r8, r3, GetTypeCallback@l
    addi    r3, r27, 0
    addi    r6, r30, 0
    li      r5, 3
    li      r7, 3
    li      r10, 0
    li      r9, 0
    bl      SITransfer
    b       L80182AE4
L80182A90:
    addi    r3, r27, 0
    li      r4, 0
    bl      OSSetWirelessID
L80182A9C:
    slwi    r0, r27, 4
    lwz     r30, 0(r30)
    add     r31, r31, r0
    li      r29, 0
    addi    r28, r29, 0
    addi    r31, r31, 352
L80182AB4:
    lwz     r12, 0(r31)
    cmplwi  r12, 0
    beq     L80182AD4
    stw     r28, 0(r31)
    mtlr    r12
    addi    r3, r27, 0
    addi    r4, r30, 0
    blrl
L80182AD4:
    addi    r29, r29, 1
    cmpwi   r29, 4
    addi    r31, r31, 4
    blt     L80182AB4
L80182AE4:
    lmw     r26, 24(r1)
    lwz     r0, 52(r1)
    addi    r1, r1, 48
    mtlr    r0
    blr
    // clang-format on
}

extern long long TypeTime[4]; // .bss object right after Alarm[4], own dtk-detected symbol

extern unsigned int SIGetType_cmdTypeAndStatus; // SIGetType's function-local static; dtk's mangled name (cmdTypeAndStatus$371) has an invalid `$`, hand-renamed here instead

// Public poll-status/probe entry point.
// Returns the cached Type[chan] if it's still fresh enough, else marks it busy and kicks off a 1-byte type probe SITransfer with GetTypeCallback as the completion callback.
// Written as asm: plain C put the 64-bit `diff` subtraction's halves in different registers than the original.
asm unsigned int SIGetType(int chan)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 4(r1)
    stwu    r1, -40(r1)
    stmw    r27, 20(r1)
    mr      r27, r3
    bl      OSDisableInterrupts
    lis     r4, Type@ha
    slwi    r5, r27, 2
    addi    r0, r4, Type@l
    add     r30, r0, r5
    lwz     r28, 0(r30)
    mr      r29, r3
    bl      __OSGetSystemTime
    lis     r5, TypeTime@ha
    slwi    r6, r27, 3
    addi    r0, r5, TypeTime@l
    add     r31, r0, r6
    lwz     r6, 4(r31)
    lis     r5, Si@ha
    addi    r5, r5, Si@l
    lwz     r0, 0(r31)
    subfc   r4, r6, r4
    subfe   r0, r0, r3
    lwz     r6, 4(r5)
    li      r5, 128
    sraw    r3, r5, r27
    and.    r3, r6, r3
    beq     L80182B98
    cmplwi  r28, 8
    beq     L80182B8C
    bl      __OSGetSystemTime
    stw     r4, 4(r31)
    stw     r3, 0(r31)
    mr      r3, r29
    bl      OSRestoreInterrupts
    mr      r3, r28
    b       L80182CA8
L80182B8C:
    stw     r5, 0(r30)
    li      r28, 128
    b       L80182C48
L80182B98:
    lis     r3, -32768
    lwz     r6, 248(r3)
    lis     r5, 4194
    addi    r5, r5, 19923
    srwi    r6, r6, 2
    mulhwu  r5, r5, r6
    srwi    r5, r5, 6
    mulli   r7, r5, 50
    li      r3, 0
    xoris   r6, r3, 32768
    xoris   r5, r0, 32768
    subfc   r3, r4, r7
    subfe   r5, r5, r6
    subfe   r5, r6, r6
    neg.    r5, r5
    bne     L80182BF0
    cmplwi  r28, 8
    beq     L80182BF0
    mr      r3, r29
    bl      OSRestoreInterrupts
    mr      r3, r28
    b       L80182CA8
L80182BF0:
    lis     r3, -32768
    lwz     r6, 248(r3)
    lis     r5, 4194
    addi    r5, r5, 19923
    srwi    r6, r6, 2
    mulhwu  r5, r5, r6
    srwi    r5, r5, 6
    mulli   r6, r5, 75
    li      r3, 0
    xoris   r5, r3, 32768
    xoris   r3, r0, 32768
    subfc   r0, r4, r6
    subfe   r3, r3, r5
    subfe   r3, r5, r5
    neg.    r3, r3
    bne     L80182C3C
    li      r0, 128
    stw     r0, 0(r30)
    b       L80182C48
L80182C3C:
    li      r0, 128
    stw     r0, 0(r30)
    li      r28, 128
L80182C48:
    bl      __OSGetSystemTime
    stw     r4, 4(r31)
    lis     r4, 17180
    lis     r5, GetTypeCallback@ha
    stw     r3, 0(r31)
    lis     r3, -32768
    addi    r8, r5, GetTypeCallback@l
    lwz     r0, 248(r3)
    addi    r4, r4, -8573
    addi    r3, r27, 0
    srwi    r0, r0, 2
    mulhwu  r0, r4, r0
    srwi    r0, r0, 15
    mulli   r0, r0, 65
    srwi    r10, r0, 3
    addi    r6, r30, 0
    la      r4, SIGetType_cmdTypeAndStatus
    li      r5, 1
    li      r7, 3
    li      r9, 0
    bl      SITransfer
    mr      r3, r29
    bl      OSRestoreInterrupts
    mr      r3, r28
L80182CA8:
    lmw     r27, 20(r1)
    lwz     r0, 44(r1)
    addi    r1, r1, 40
    mtlr    r0
    blr
    // clang-format on
}

extern unsigned char TypeCallback[]; // TypeCallback[4][4], own dtk-detected .bss symbol

// Calls SIGetType(chan) first; if the result is still busy (Type[chan] & SI_ERROR_BUSY), registers `callback` in the first free (or matching) slot of TypeCallback[chan][0..3], otherwise invokes `callback(chan, type)` immediately via mtlr/blrl.
// Written as asm: the 4-iteration registration loop is fully unrolled into four straight-line copies, including one unreachable trailing `b` at L80182DB4 (dead code from the unrolled tail).
asm unsigned int SIGetTypeAsync(int chan, void* callback)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 4(r1)
    stwu    r1, -32(r1)
    stw     r31, 28(r1)
    addi    r31, r4, 0
    stw     r30, 24(r1)
    stw     r29, 20(r1)
    stw     r28, 16(r1)
    addi    r28, r3, 0
    bl      OSDisableInterrupts
    addi    r30, r3, 0
    addi    r3, r28, 0
    bl      SIGetType
    lis     r4, Type@ha
    slwi    r5, r28, 2
    addi    r0, r4, Type@l
    add     r4, r0, r5
    lwz     r0, 0(r4)
    addi    r29, r3, 0
    rlwinm. r0, r0, 0, 24, 24
    beq     L80182DB8
    lis     r3, TypeCallback@ha
    slwi    r4, r28, 4
    addi    r0, r3, TypeCallback@l
    add     r4, r0, r4
    lwz     r0, 0(r4)
    li      r5, 0
    cmplw   r0, r31
    beq     L80182DCC
    cmplwi  r0, 0
    bne     L80182D44
    slwi    r0, r5, 2
    stwx    r31, r4, r0
    b       L80182DCC
L80182D44:
    addi    r3, r4, 4
    lwz     r0, 4(r4)
    li      r5, 1
    cmplw   r0, r31
    beq     L80182DCC
    cmplwi  r0, 0
    bne     L80182D6C
    slwi    r0, r5, 2
    stwx    r31, r4, r0
    b       L80182DCC
L80182D6C:
    lwzu    r0, 4(r3)
    li      r5, 2
    cmplw   r0, r31
    beq     L80182DCC
    cmplwi  r0, 0
    bne     L80182D90
    slwi    r0, r5, 2
    stwx    r31, r4, r0
    b       L80182DCC
L80182D90:
    lwz     r0, 4(r3)
    li      r5, 3
    cmplw   r0, r31
    beq     L80182DCC
    cmplwi  r0, 0
    bne     L80182DCC
    slwi    r0, r5, 2
    stwx    r31, r4, r0
    b       L80182DCC
L80182DB4:
    b       L80182DCC
L80182DB8:
    addi    r12, r31, 0
    mtlr    r12
    addi    r3, r28, 0
    addi    r4, r29, 0
    blrl
L80182DCC:
    mr      r3, r30
    bl      OSRestoreInterrupts
    mr      r3, r29
    lwz     r0, 36(r1)
    lwz     r31, 28(r1)
    lwz     r30, 24(r1)
    lwz     r29, 20(r1)
    lwz     r28, 16(r1)
    addi    r1, r1, 32
    mtlr    r0
    blr
    // clang-format on
}

#pragma peephole on

unsigned int SIDecodeType(unsigned int type)
{
    unsigned int error;

    error = type & 0xFF;
    type &= ~0xFF;

    if (error & 8) {
        return 8;
    }

    if (error & 0x47) {
        return 0x40;
    }

    if (error != 0) {
        return SI_ERROR_BUSY;
    }

    if ((type & 0x18000000) == 0) {
        switch (type & 0xFFFF0000) {
            case 0x10000:
            case 0x20000:
            case 0x40000:
            case 0x2000000:
            case 0x5000000:
                return type & 0xFFFF0000;
            default:
                return 0x40;
        }
    }

    if ((type & 0x18000000) != 0x08000000) {
        return 0x40;
    }

    switch (type & 0xFFFF0000) {
        case 0x8000000:
        case 0x9000000:
            return type & 0xFFFF0000;
    }

    if ((type & 0xFFE00000) == 0x8200000) {
        return 0x8200000;
    }

    if ((type & 0x80000000) != 0 && (type & 0x4000000) == 0) {
        if ((type & 0x8B100000) == 0x8B100000) {
            return 0x8B100000;
        }

        if ((type & 0x2000000) == 0) {
            return 0x88000000;
        }
    }

    if ((type & 0x9000000) == 0x9000000) {
        return 0x9000000;
    }

    return 0x40;
}

unsigned int SIProbe(int chan)
{
    return SIDecodeType(SIGetType(chan));
}

// Clamps msec to 11, disables interrupts, records SamplingRate, then picks the XYNTSC or XYPAL
// 12-entry table (or defaults to XYNTSC plus an OSReport warning and msec=0) based on
// VIGetTvFormat()'s result, and calls SISetXY with the [msec] entry's line (doubled if
// progressive-scan, per __VIRegs' clock-select bit) and count.
// Same shared-base-register shape as this file's other blob-touching functions.
asm void SISetSamplingRate(unsigned int msec)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 4(r1)
    stwu    r1, -32(r1)
    stw     r31, 28(r1)
    stw     r30, 24(r1)
    stw     r29, 20(r1)
    addi    r29, r3, 0
    cmplwi  r29, 11
    lis     r3, XYNTSC@ha
    addi    r31, r3, XYNTSC@l
    ble     L80182F98
    li      r29, 11
L80182F98:
    bl      OSDisableInterrupts
    stw     r29, SamplingRate
    mr      r30, r3
    bl      VIGetTvFormat
    cmpwi   r3, 2
    beq     L80182FD0
    bge     L80182FC4
    cmpwi   r3, 0
    beq     L80182FD0
    bge     L80182FD8
    b       L80182FE0
L80182FC4:
    cmpwi   r3, 5
    beq     L80182FD0
    b       L80182FE0
L80182FD0:
    mr      r4, r31
    b       L80182FF4
L80182FD8:
    addi    r4, r31, 48
    b       L80182FF4
L80182FE0:
    addi    r3, r31, 96
    crclr   4*cr1+eq
    bl      OSReport
    li      r29, 0
    addi    r4, r31, 0
L80182FF4:
    lis     r3, -13312
    lhz     r0, 8300(r3)
    rlwinm. r0, r0, 0, 31, 31
    beq     L8018300C
    li      r5, 2
    b       L80183010
L8018300C:
    li      r5, 1
L80183010:
    slwi    r3, r29, 2
    lhzx    r0, r4, r3
    add     r3, r4, r3
    lbz     r4, 2(r3)
    mullw   r3, r5, r0
    bl      SISetXY
    mr      r3, r30
    bl      OSRestoreInterrupts
    lwz     r0, 36(r1)
    lwz     r31, 28(r1)
    lwz     r30, 24(r1)
    lwz     r29, 20(r1)
    addi    r1, r1, 32
    mtlr    r0
    blr
    // clang-format on
}

// Re-applies the last-recorded SamplingRate.
asm void SIRefreshSamplingRate(void)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 4(r1)
    stwu    r1, -8(r1)
    lwz     r3, SamplingRate
    bl      SISetSamplingRate
    lwz     r0, 12(r1)
    addi    r1, r1, 8
    mtlr    r0
    blr
    // clang-format on
}
