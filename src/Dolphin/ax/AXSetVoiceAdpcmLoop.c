typedef struct {
    unsigned char pad[0x1C];
    unsigned long sync;
    unsigned char pad2[0x1EC - 0x20];
    unsigned short adpcmLoop[3];
} AXVPB;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);

void AXSetVoiceAdpcmLoop(AXVPB* p, unsigned short* src)
{
    int old;
    unsigned short* dst = p->adpcmLoop;

    old = OSDisableInterrupts();
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    p->sync |= 0x100000;
    OSRestoreInterrupts(old);
}
