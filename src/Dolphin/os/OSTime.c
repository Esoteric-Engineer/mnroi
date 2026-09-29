typedef unsigned long u32;

asm long long OSGetTime(void)
{
    // clang-format off
    nofralloc
loop:
    mftbu   r3
    mftb    r4
    mftbu   r5
    cmpw    r3, r5
    bne     loop
    blr
    // clang-format on
}

asm u32 OSGetTick(void)
{
    // clang-format off
    nofralloc
    mftb r3
    blr
    // clang-format on
}

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);

long long __OSGetSystemTime(void)
{
    int enabled;
    long long* timeAdjustAddr = (long long*)0x800030D8;
    long long result;

    enabled = OSDisableInterrupts();
    result = OSGetTime() + *timeAdjustAddr;
    OSRestoreInterrupts(enabled);
    return result;
}

long long fn_80180FDC(long long ticks)
{
    int enabled;
    long long* timeAdjustAddr = (long long*)0x800030D8;
    long long result;

    enabled = OSDisableInterrupts();
    result = *timeAdjustAddr + ticks;
    OSRestoreInterrupts(enabled);
    return result;
}

typedef struct OSCalendarTime
{
    int sec;
    int min;
    int hour;
    int mday;
    int mon;
    int year;
    int wday;
    int yday;
    int msec;
    int usec;
} OSCalendarTime;

int YearDays[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
int LeapYearDays[12] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};

// Written as asm: leaf/no-stack, with magic-number divisions (/7, /365, /4, /100, /400) and two inlined static helpers (IsLeapYear, GetLeapDays) that need the compiler's exact choices.
asm void GetDates(int days, OSCalendarTime* td)
{
    // clang-format off
    nofralloc
    lis     r5, -28087
    addi    r0, r5, 9363
    addi    r7, r3, 6
    mulhw   r6, r0, r7
    lis     r5, -19571
    addi    r0, r5, -1615
    mulhw   r0, r0, r3
    add     r5, r6, r7
    srawi   r5, r5, 2
    srwi    r6, r5, 31
    add     r5, r5, r6
    add     r0, r0, r3
    mulli   r6, r5, 7
    srawi   r0, r0, 8
    srwi    r5, r0, 31
    add     r5, r0, r5
    subf    r0, r6, r7
    mulli   r11, r5, 365
    stw     r0, 24(r4)
    b       L80181084
L80181084:
    lis     r6, 20972
    addi    r10, r6, -31457
    b       L80181090
L80181090:
    b       L8018109C
L80181094:
    addi    r11, r11, -365
    addi    r5, r5, -1
L8018109C:
    cmpwi   r5, 1
    bge     L801810AC
    li      r0, 0
    b       L801810E0
L801810AC:
    addi    r0, r5, -1
    mulhw   r0, r10, r0
    srawi   r8, r0, 7
    srawi   r6, r0, 5
    addi    r0, r5, 3
    srwi    r7, r6, 31
    srawi   r0, r0, 2
    srwi    r9, r8, 31
    add     r6, r6, r7
    addze   r0, r0
    add     r7, r8, r9
    subf    r0, r6, r0
    add     r0, r7, r0
L801810E0:
    add     r0, r11, r0
    cmpw    r3, r0
    blt     L80181094
    srawi   r6, r5, 2
    stw     r5, 20(r4)
    addze   r6, r6
    slwi    r6, r6, 2
    subfc   r6, r6, r5
    subf    r0, r0, r3
    cmpwi   r6, 0
    stw     r0, 28(r4)
    li      r7, 1
    li      r8, 0
    bne     L80181144
    lis     r3, 20972
    addi    r3, r3, -31457
    mulhw   r3, r3, r5
    srawi   r3, r3, 5
    srwi    r6, r3, 31
    add     r3, r3, r6
    mulli   r3, r3, 100
    subf    r3, r3, r5
    cmpwi   r3, 0
    beq     L80181144
    mr      r8, r7
L80181144:
    cmpwi   r8, 0
    bne     L80181178
    lis     r3, 20972
    addi    r3, r3, -31457
    mulhw   r3, r3, r5
    srawi   r3, r3, 7
    srwi    r6, r3, 31
    add     r3, r3, r6
    mulli   r3, r3, 400
    subf    r3, r3, r5
    cmpwi   r3, 0
    beq     L80181178
    li      r7, 0
L80181178:
    cmpwi   r7, 0
    beq     L8018118C
    lis     r3, LeapYearDays@ha
    addi    r6, r3, LeapYearDays@l
    b       L80181194
L8018118C:
    lis     r3, YearDays@ha
    addi    r6, r3, YearDays@l
L80181194:
    li      r7, 12
    li      r3, 48
    b       L801811A0
L801811A0:
    b       L801811A4
L801811A4:
    addi    r3, r3, -4
    lwzx    r5, r6, r3
    addi    r7, r7, -1
    cmpw    r0, r5
    blt     L801811A4
    stw     r7, 16(r4)
    lwzx    r3, r6, r3
    subf    r3, r3, r0
    addi    r0, r3, 1
    stw     r0, 12(r4)
    blr
    // clang-format on
}

extern void __div2i(void);
extern void __mod2i(void);

// Written as asm: plain C common-subexpression-eliminates the repeated OSTicksToSeconds(ticks) call, one __div2i short of the original, which recomputes it.
asm void OSTicksToCalendarTime(long long ticks, OSCalendarTime* td)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 4(r1)
    stwu    r1, -56(r1)
    stmw    r25, 28(r1)
    mr      r29, r3
    mr      r30, r4
    mr      r31, r5
    lis     r27, -32768
    lwz     r0, 248(r27)
    mr      r3, r29
    mr      r4, r30
    srwi    r6, r0, 2
    li      r5, 0
    bl      __mod2i
    mr      r26, r3
    li      r5, 0
    mr      r25, r4
    xoris   r4, r26, 32768
    xoris   r3, r5, 32768
    subfc   r0, r5, r25
    subfe   r3, r3, r4
    subfe   r3, r4, r4
    neg     r3, r3
    cmpwi   r3, 0
    beq     L80181244
    lwz     r0, 248(r27)
    srwi    r0, r0, 2
    addc    r25, r25, r0
    adde    r26, r26, r5
L80181244:
    li      r4, 8
    mullw   r3, r26, r4
    mulhwu  r0, r25, r4
    lis     r27, -32768
    lwz     r6, 248(r27)
    lis     r5, 17180
    addi    r5, r5, -8573
    srwi    r6, r6, 2
    mulhwu  r5, r5, r6
    srwi    r6, r5, 15
    li      r28, 0
    add     r3, r3, r0
    mullw   r0, r25, r28
    mullw   r4, r25, r4
    add     r3, r3, r0
    li      r5, 0
    bl      __div2i
    li      r5, 0
    li      r6, 1000
    bl      __mod2i
    stw     r4, 36(r31)
    lis     r3, 4194
    addi    r5, r3, 19923
    lwz     r0, 248(r27)
    mr      r3, r26
    mr      r4, r25
    srwi    r0, r0, 2
    mulhwu  r0, r5, r0
    srwi    r6, r0, 6
    li      r5, 0
    bl      __div2i
    li      r5, 0
    li      r6, 1000
    bl      __mod2i
    stw     r4, 32(r31)
    subfc   r30, r25, r30
    subfe   r29, r26, r29
    lwz     r0, 248(r27)
    lis     r5, 1
    addi    r25, r5, 20864
    mr      r3, r29
    srwi    r6, r0, 2
    mr      r4, r30
    li      r5, 0
    bl      __div2i
    mr      r6, r25
    li      r5, 0
    bl      __div2i
    lis     r5, 11
    lwz     r0, 248(r27)
    addi    r5, r5, 9589
    addc    r26, r4, r5
    srwi    r6, r0, 2
    adde    r0, r3, r28
    mr      r3, r29
    mr      r4, r30
    li      r5, 0
    bl      __div2i
    mr      r6, r25
    li      r5, 0
    bl      __mod2i
    mr      r27, r4
    cmpwi   r27, 0
    bge     L80181350
    addis   r27, r27, 1
    addi    r26, r26, -1
    addi    r27, r27, 20864
L80181350:
    mr      r3, r26
    mr      r4, r31
    bl      GetDates
    lis     r3, -30583
    addi    r5, r3, -30583
    mulhw   r0, r5, r27
    add     r4, r0, r27
    srawi   r0, r4, 5
    srwi    r3, r0, 31
    add     r7, r0, r3
    mulhw   r0, r5, r7
    add     r0, r0, r7
    srawi   r5, r0, 5
    srawi   r0, r0, 5
    srwi    r3, r0, 31
    add     r3, r0, r3
    srawi   r0, r4, 5
    srwi    r6, r5, 31
    mulli   r4, r3, 60
    srwi    r3, r0, 31
    add     r5, r5, r6
    add     r0, r0, r3
    stw     r5, 8(r31)
    mulli   r0, r0, 60
    subf    r3, r4, r7
    stw     r3, 4(r31)
    subf    r0, r0, r27
    stw     r0, 0(r31)
    lmw     r25, 28(r1)
    lwz     r0, 60(r1)
    addi    r1, r1, 56
    mtlr    r0
    blr
    // clang-format on
}
