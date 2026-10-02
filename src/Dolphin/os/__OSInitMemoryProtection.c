typedef int BOOL;
typedef unsigned int u32;
typedef unsigned short u16;

volatile u16 __MEMRegs[64] : 0xCC004000;
u32 __OSPhysicalMemSize : 0x80000028;
u32 __OSSimulatedMemSize : 0x800000F0;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern u32 __OSMaskInterrupts(u32 mask);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern void __OSSetInterruptHandler(short interrupt, void* handler);
extern void OSRegisterResetFunction(void* info);
extern void DCInvalidateRange(void* addr, u32 nBytes);
extern void RealMode(u32 config);
extern void Config24MB(void);
extern void Config48MB(void);
extern void MEMIntrruptHandler(short interrupt, void* ctx);
extern BOOL OnReset(BOOL final);

typedef struct OSResetFunctionInfo OSResetFunctionInfo;
struct OSResetFunctionInfo {
    BOOL (*func)(BOOL final);
    u32 priority;
    OSResetFunctionInfo* next;
    OSResetFunctionInfo* prev;
};

OSResetFunctionInfo ResetFunctionInfo_804D12A8 = {
    OnReset,
    0x7F,
};

#pragma peephole off
void __OSInitMemoryProtection(void)
{
    char padding[0x30];
    u32 simulatedSize;
    BOOL enabled;

    simulatedSize = __OSSimulatedMemSize;
    enabled = OSDisableInterrupts();

    __MEMRegs[16] = 0;
    __MEMRegs[8] = 0xFF;

    __OSMaskInterrupts(0xF0000000);
    __OSSetInterruptHandler(0, MEMIntrruptHandler);
    __OSSetInterruptHandler(1, MEMIntrruptHandler);
    __OSSetInterruptHandler(2, MEMIntrruptHandler);
    __OSSetInterruptHandler(3, MEMIntrruptHandler);
    __OSSetInterruptHandler(4, MEMIntrruptHandler);
    OSRegisterResetFunction(&ResetFunctionInfo_804D12A8);

    if (__OSSimulatedMemSize < __OSPhysicalMemSize && __OSSimulatedMemSize == 0x1800000) {
        DCInvalidateRange((void*)0x81800000, 0x1800000);
        __MEMRegs[20] = 2;
    }

    if (simulatedSize <= 0x1800000) {
        RealMode((u32)Config24MB);
    } else if (simulatedSize <= 0x3000000) {
        RealMode((u32)Config48MB);
    }

    __OSUnmaskInterrupts(0x8000000);
    OSRestoreInterrupts(enabled);
}
