extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int enabled);

extern volatile unsigned long WorkAroundType;
extern unsigned long WorkAroundSeekLocation;

void __DVDLowSetWAType(unsigned long type, unsigned long location)
{
    int enabled = OSDisableInterrupts();
    WorkAroundType = type;
    WorkAroundSeekLocation = location;
    OSRestoreInterrupts(enabled);
}
