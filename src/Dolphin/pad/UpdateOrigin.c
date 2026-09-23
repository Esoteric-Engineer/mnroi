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

extern u32 lbl_8066C4A0;
extern u32 lbl_8066C4A4;
extern PADStatus lbl_8057D570[];

void UpdateOrigin(int chan)
{
    PADStatus* origin;
    u32 chanBit;

    chanBit = 0x80000000 >> chan;
    origin = &lbl_8057D570[chan];
    switch (lbl_8066C4A4 & 0x700u) {
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

    if ((lbl_8066C4A0 & chanBit) != 0 && origin->stickX > 64 && (SIGetType(chan) & 0xFFFF0000) == 0x09000000) {
        origin->stickX = 0;
    }
}
