typedef unsigned char u8;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);

volatile u8 __gUnknown800030E3 : 0x800030E3;

BOOL __PADDisableRecalibration(BOOL disable)
{
    BOOL enabled;
    BOOL prev;

    enabled = OSDisableInterrupts();
    prev = (__gUnknown800030E3 & 0x40) ? 1 : 0;
    __gUnknown800030E3 &= ~0x40;

    if (disable) {
        __gUnknown800030E3 |= 0x40;
    }

    OSRestoreInterrupts(enabled);
    return prev;
}
