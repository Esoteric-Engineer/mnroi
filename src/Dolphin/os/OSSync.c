typedef unsigned long u32;

extern void* memcpy(void* dest, const void* src, u32 n);
extern void DCFlushRangeNoSync(void* addr, u32 nBytes);
extern void ICInvalidateRange(void* addr, u32 nBytes);

void __OSSystemCallVectorStart();
void __OSSystemCallVectorEnd();

static asm void SystemCallVector(void)
{
    // clang-format off
entry __OSSystemCallVectorStart
    nofralloc
    mfspr r9, HID0
    ori   r10, r9, 8
    mtspr HID0, r10
    isync
    sync
    mtspr HID0, r9
    rfi
entry __OSSystemCallVectorEnd
    nop
    // clang-format on
}

void __OSInitSystemCall(void)
{
    void* addr = (void*)(0xC00 | 0x80000000);

    memcpy(addr, __OSSystemCallVectorStart,
           (u32)&__OSSystemCallVectorEnd - (u32)&__OSSystemCallVectorStart);
    DCFlushRangeNoSync(addr, 0x100);
    __sync();
    ICInvalidateRange(addr, 0x100);
}
