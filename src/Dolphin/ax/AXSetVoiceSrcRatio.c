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

// Unreferenced here: the rest of AXVPB.c's .sdata2 pool.
// Kept alive by force_active above.
const float AXVPBTwoPiConst = 6.2831854820251465f;
const float AXVPBPoolConst1 = 32000.0f;
const float AXVPBPoolConst2 = 2.0f;
const float AXVPBPoolConst3 = 1.0f;
const float AXVPBPoolConst4 = 0.0f;
const float AXVPBPoolConst5 = 1.75f;
const float AXVPBPoolConst6 = 0.0f;
const float AXVPBPoolConst7 = 2.125f;
const float AXVPBPoolConst8 = 0.0f;
const float AXVPBPoolConst9 = 32768.0f;
const float AXVPBPoolConst10 = 0.0f;
const float AXVPBPoolConst11 = 176.0f;
const float AXVPBPoolConst12 = 0.0f;
