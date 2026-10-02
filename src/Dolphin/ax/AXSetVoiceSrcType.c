#pragma force_active on

typedef struct {
    unsigned char pad[0x1C];
    unsigned long sync;
    unsigned char pad2[0x138 - 0x20];
    unsigned char src[0x10];
} AXVPB;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);

void AXSetVoiceSrcType(AXVPB* p, unsigned long type)
{
    int old;
    unsigned short* src;

    old = OSDisableInterrupts();
    src = (unsigned short*)p->src;
    switch (type) {
    case 0:
        src[4] = 2;
        break;
    case 1:
        src[4] = 1;
        break;
    case 2:
        src[4] = 0;
        src[5] = 0;
        break;
    case 3:
        src[4] = 0;
        src[5] = 1;
        break;
    case 4:
        src[4] = 0;
        src[5] = 2;
        break;
    }
    p->sync |= 1;
    OSRestoreInterrupts(old);
}
