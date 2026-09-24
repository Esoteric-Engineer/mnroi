typedef unsigned long u32;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern u32 CurrTvMode;

// VIConfigure's OSReport strings (VIConfigure is still unsplit asm).
// They share VI.c's .data with this function's jump table, which sits 4-mod-8, so the unit has to claim from the 8-aligned start of the strings.
// VIConfigure reaches them off the lbl_804D2880 pool base, not by symbol, so keep them from being stripped.
#pragma force_active on
char lbl_804D2AE0[] = "***************************************\n";
char lbl_804D2B0C[] = " ! ! ! C A U T I O N ! ! !             \n";
char lbl_804D2B38[] = "This TV format \"DEBUG_PAL\" is only for \n";
char lbl_804D2B64[] = "temporary solution until PAL DAC board \n";
char lbl_804D2B90[] = "is available. Please do NOT use this   \n";
char lbl_804D2BBC[] = "mode in real games!!!                  \n";
char lbl_804D2BE8[] = "VIConfigure(): Tried to change mode from (%d) to (%d), which is forbidden\n";
#pragma force_active reset

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
