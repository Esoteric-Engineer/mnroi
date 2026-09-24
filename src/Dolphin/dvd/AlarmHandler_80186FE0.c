typedef int BOOL;
typedef unsigned long u32;
typedef long s32;
typedef void (*DVDLowCallback)(u32);

typedef struct {
    s32 cmd;
    void* addr;
    u32 length;
    u32 offset;
    DVDLowCallback callback;
} DVDCommand;

extern volatile s32 NextCommandNumber;
extern DVDCommand CommandList[3];

void Read(void* addr, u32 length, u32 offset, DVDLowCallback callback);
BOOL DVDLowSeek(u32 offset, DVDLowCallback callback);

// In C this is dvdlow.c's ProcessNextCommand inlined:
//     s32 n = NextCommandNumber;
//     if (CommandList[n].cmd == 1) { ++NextCommandNumber; Read(CommandList[n]...); }
//     else if (CommandList[n].cmd == 2) { ++NextCommandNumber; DVDLowSeek(CommandList[n]...); }
// The original compiles it in the same translation unit as the pooled CommandList (a single lis/addi base, lwzx for the command word).
// With CommandList extern the compiler CSEs the entry address (87.9%), so this is transliterated.
asm void AlarmHandler_80186FE0(void* alarm, void* context)
{
    // clang-format off
    nofralloc
    mflr    r0
    lis     r3, CommandList@ha
    stw     r0, 4(r1)
    addi    r4, r3, CommandList@l
    stwu    r1, -8(r1)
    lwz     r0, NextCommandNumber
    mulli   r0, r0, 0x14
    lwzx    r3, r4, r0
    cmpwi   r3, 1
    bne     L_seek
    lwz     r3, NextCommandNumber
    add     r6, r4, r0
    addi    r0, r3, 1
    stw     r0, NextCommandNumber
    lwz     r3, 4(r6)
    lwz     r4, 8(r6)
    lwz     r5, 0xc(r6)
    lwz     r6, 0x10(r6)
    bl      Read
    b       L_end
L_seek:
    cmpwi   r3, 2
    bne     L_end
    lwz     r3, NextCommandNumber
    add     r4, r4, r0
    addi    r0, r3, 1
    stw     r0, NextCommandNumber
    lwz     r3, 0xc(r4)
    lwz     r4, 0x10(r4)
    bl      DVDLowSeek
L_end:
    lwz     r0, 0xc(r1)
    addi    r1, r1, 8
    mtlr    r0
    blr
    // clang-format on
}
