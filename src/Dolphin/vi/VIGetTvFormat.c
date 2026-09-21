typedef unsigned long u32;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern u32 CurrTvMode;

u32 VIGetTvFormat(void)
{
    int enabled;
    u32 result;

    enabled = OSDisableInterrupts();

    switch (CurrTvMode) {
    case 0:
    case 3:
    case 6:
        result = 0;
        break;
    case 1:
    case 4:
        result = 1;
        break;
    case 2:
    case 5:
        result = CurrTvMode;
        break;
    }

    OSRestoreInterrupts(enabled);
    return result;
}
