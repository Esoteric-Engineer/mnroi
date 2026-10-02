typedef struct {
    unsigned char pad[0x1C];
    unsigned long sync;
    unsigned char pad2[0x1A6 - 0x20];
    unsigned char pb[0x38];
} AXVPB;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);

void AXSetVoiceAddr(AXVPB* p, unsigned long* addr)
{
    int old;
    unsigned long* dst = (unsigned long*)p->pb;

    old = OSDisableInterrupts();
    dst[0] = addr[0];
    dst[1] = addr[1];
    dst[2] = addr[2];
    dst[3] = addr[3];

    switch (((unsigned short*)addr)[1]) {
    case 0:
        break;
    case 10:
        dst[4] = 0;
        dst[5] = 0;
        dst[6] = 0;
        dst[7] = 0;
        dst[8] = 0;
        dst[9] = 0;
        dst[10] = 0;
        dst[11] = 0;
        dst[12] = 0x08000000;
        dst[13] = 0;
        break;
    case 25:
        dst[4] = 0;
        dst[5] = 0;
        dst[6] = 0;
        dst[7] = 0;
        dst[8] = 0;
        dst[9] = 0;
        dst[10] = 0;
        dst[11] = 0;
        dst[12] = 0x01000000;
        dst[13] = 0;
        break;
    }

    p->sync &= 0xFFFE1FFF;
    p->sync |= 0x21000;
    OSRestoreInterrupts(old);
}
