#pragma force_active on

typedef struct {
    unsigned char pad[0x1C];
    unsigned long sync;
    unsigned char pad2[0x1DE - 0x20];
    unsigned short ratioHi;
    unsigned short ratioLo;
} AXVPB;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);

void AXSetVoiceSrcRatio(AXVPB* p, float ratio)
{
    unsigned long ratioBits;
    int old;

    old = OSDisableInterrupts();
    ratioBits = (unsigned long)(65536.0f * ratio);
    if ((unsigned long)(65536.0f * ratio) > 0x40000) {
        ratioBits = 0x40000;
    }
    p->ratioHi = ratioBits >> 16;
    p->ratioLo = ratioBits;
    p->sync |= 0x80000;
    OSRestoreInterrupts(old);
}
