typedef struct {
    long cmd;
    void* addr;
    unsigned long length;
    unsigned long offset;
    void (*callback)(unsigned long);
} DVDCommand;

extern DVDCommand CommandList[3];
extern long NextCommandNumber;

extern void __DVDLowSetWAType(unsigned long type, unsigned long location);
extern void OSInitAlarm(void);

void __DVDInitWA(void)
{
    NextCommandNumber = 0;
    CommandList[0].cmd = -1;
    __DVDLowSetWAType(0, 0);
    OSInitAlarm();
}
