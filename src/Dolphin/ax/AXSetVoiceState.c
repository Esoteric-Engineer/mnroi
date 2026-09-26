typedef struct {
    unsigned char pad[0x1C];
    unsigned long sync;
    unsigned long depop;
    unsigned char pad2[0x146 - 0x24];
    unsigned short state;
} AXVPB;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);

void AXSetVoiceState(AXVPB* p, unsigned short state)
{
    int old = OSDisableInterrupts();

    p->state = state;
    p->sync |= 4;
    if (state == 0) {
        p->depop = 1;
    }
    OSRestoreInterrupts(old);
}
