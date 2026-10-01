typedef unsigned int u32;
typedef signed char s8;
typedef unsigned char u8;

typedef struct PADStatus {
    unsigned short button;
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
    u8 triggerLeft;
    u8 triggerRight;
    u8 analogA;
    u8 analogB;
    s8 err;
} PADStatus;

extern u32 SIGetType(int chan);
extern void SPEC2_MakeStatus(int chan, PADStatus* status, u32* data);

extern char lbl_804D2C50[];
extern PADStatus Origin[];

char* __PADVersion = lbl_804D2C50;
long ResettingChan = 0x20;
u32 XPatchBits = 0xF0000000;
u32 AnalogMode = 0x300;
unsigned long Spec = 5;
void (*MakeStatus)(int chan, PADStatus* status, u32* data) = SPEC2_MakeStatus;
unsigned long CmdReadOrigin = 0x41000000;
unsigned long CmdCalibrate = 0x42000000;

void UpdateOrigin(int chan)
{
    PADStatus* origin;
    u32 chanBit;

    chanBit = 0x80000000 >> chan;
    origin = &Origin[chan];
    switch (AnalogMode & 0x700u) {
    case 0x000u:
    case 0x500u:
    case 0x600u:
    case 0x700u:
        origin->triggerLeft &= ~15;
        origin->triggerRight &= ~15;
        origin->analogA &= ~15;
        origin->analogB &= ~15;
        break;
    case 0x100u:
        origin->substickX &= ~15;
        origin->substickY &= ~15;
        origin->analogA &= ~15;
        origin->analogB &= ~15;
        break;
    case 0x200u:
        origin->substickX &= ~15;
        origin->substickY &= ~15;
        origin->triggerLeft &= ~15;
        origin->triggerRight &= ~15;
        break;
    case 0x300u:
        break;
    case 0x400u:
        break;
    }

    origin->stickX -= 128;
    origin->stickY -= 128;
    origin->substickX -= 128;
    origin->substickY -= 128;

    if ((XPatchBits & chanBit) != 0 && origin->stickX > 64 && (SIGetType(chan) & 0xFFFF0000) == 0x09000000) {
        origin->stickX = 0;
    }
}
