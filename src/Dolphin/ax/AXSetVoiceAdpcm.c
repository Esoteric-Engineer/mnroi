typedef struct {
    unsigned short a[8][2];
    unsigned short gain;
    unsigned short pred_scale;
    unsigned short yn1;
    unsigned short yn2;
} AXPBADPCM;

typedef struct {
    unsigned char pad[0x1C];
    unsigned long sync;
    unsigned char pad2[0x1B6 - 0x20];
    AXPBADPCM adpcm;
} AXVPB;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);

void AXSetVoiceAdpcm(AXVPB* p, AXPBADPCM* src)
{
    int old;
    unsigned long* dst = (unsigned long*)&p->adpcm;
    unsigned long* s = (unsigned long*)src;

    old = OSDisableInterrupts();
    dst[0] = s[0];
    dst[1] = s[1];
    dst[2] = s[2];
    dst[3] = s[3];
    dst[4] = s[4];
    dst[5] = s[5];
    dst[6] = s[6];
    dst[7] = s[7];
    dst[8] = s[8];
    dst[9] = s[9];
    p->sync |= 0x20000;
    OSRestoreInterrupts(old);
}
