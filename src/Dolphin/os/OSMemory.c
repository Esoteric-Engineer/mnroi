typedef int BOOL;
typedef unsigned int u32;

volatile unsigned short __MEMRegs[64] : 0xCC004000;

extern void __OSMaskInterrupts(u32 mask);

BOOL OnReset(BOOL final)
{
    if (final) {
        __MEMRegs[8] = 0xFF;
        __OSMaskInterrupts(0xF0000000);
    }
    return 1;
}

typedef unsigned short u16;
typedef void (*OSErrorHandler)(u16 error, void* context, ...);

extern OSErrorHandler __OSErrorTable[17];
extern void __OSUnhandledException(u16 error, void* context, u32 cause, u32 addr);

void MEMIntrruptHandler(short interrupt, void* ctx)
{
    u32 cause = __MEMRegs[0xF];
    u32 addr = ((__MEMRegs[0x12] & 0x3FF) << 16) | __MEMRegs[0x11];
    __MEMRegs[0x10] = 0;

    if (__OSErrorTable[15]) {
        __OSErrorTable[15](15, ctx, cause, addr);
        return;
    }

    __OSUnhandledException(15, ctx, cause, addr);
}

asm void Config24MB(void)
{
    nofralloc

    li r7, 0
    lis r4, 0x0000
    addi r4, r4, 0x0002
    lis r3, 0x8000
    addi r3, r3, 0x01FF
    lis r6, 0x0100
    addi r6, r6, 0x0002
    lis r5, 0x8100
    addi r5, r5, 0x00FF
    isync
    mtdbatu 0, r7
    mtdbatl 0, r4
    mtdbatu 0, r3
    isync
    mtibatu 0, r7
    mtibatl 0, r4
    mtibatu 0, r3
    isync
    mtdbatu 2, r7
    mtdbatl 2, r6
    mtdbatu 2, r5
    isync
    mtibatu 2, r7
    mtibatl 2, r6
    mtibatu 2, r5
    isync
    mfmsr r3
    ori r3, r3, 0x30
    mtspr 0x1b, r3
    mflr r3
    mtspr 0x1a, r3
    rfi
}

asm void Config48MB(void)
{
    nofralloc

    li r7, 0
    lis r4, 0x0000
    addi r4, r4, 0x0002
    lis r3, 0x8000
    addi r3, r3, 0x03FF
    lis r6, 0x0200
    addi r6, r6, 0x0002
    lis r5, 0x8200
    addi r5, r5, 0x01FF
    isync
    mtdbatu 0, r7
    mtdbatl 0, r4
    mtdbatu 0, r3
    isync
    mtibatu 0, r7
    mtibatl 0, r4
    mtibatu 0, r3
    isync
    mtdbatu 2, r7
    mtdbatl 2, r6
    mtdbatu 2, r5
    isync
    mtibatu 2, r7
    mtibatl 2, r6
    mtibatu 2, r5
    isync
    mfmsr r3
    ori r3, r3, 0x30
    mtspr 0x1b, r3
    mflr r3
    mtspr 0x1a, r3
    rfi
}
