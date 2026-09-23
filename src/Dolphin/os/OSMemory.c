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
