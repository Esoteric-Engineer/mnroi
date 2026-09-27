typedef unsigned char u8;
typedef unsigned short u16;
typedef long s32;
typedef unsigned long u32;
typedef int BOOL;

typedef struct CARDControl {
    BOOL attached;
    s32 result;
    u16 size;
    u16 pad0A;
    s32 sectorSize;
    unsigned char pad10[0x24 - 0x10];
    s32 mountStep;
    unsigned char pad28[0x110 - 0x28];
} CARDControl;

extern CARDControl __CARDBlock[2];
extern s32 lbl_804F2BD8[8];
extern u8 __gUnknown800030E3 : 0x800030E3;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern s32 EXIProbeEx(s32 chan);
extern u32 EXIGetState(s32 chan);
extern BOOL EXIGetID(s32 chan, u32 dev, u32* id);
extern s32 IsCard(u32 id);

s32 CARDProbeEx(s32 chan, s32* memSize, s32* sectorSize)
{
    u32 id;
    CARDControl* card;
    BOOL enabled;
    s32 result;
    s32 probe;

    if (chan < 0 || 2 <= chan) {
        return -128;
    }

    if (__gUnknown800030E3 & 0x80) {
        return -3;
    }

    card = &__CARDBlock[chan];
    enabled = OSDisableInterrupts();
    probe = EXIProbeEx(chan);
    if (probe == -1) {
        result = -3;
    } else if (probe == 0) {
        result = -1;
    } else if (card->attached) {
        if (card->mountStep < 1) {
            result = -1;
        } else {
            if (memSize) {
                *memSize = card->size;
            }
            if (sectorSize) {
                *sectorSize = card->sectorSize;
            }
            result = 0;
        }
    } else if (EXIGetState(chan) & 8) {
        result = -2;
    } else if (!EXIGetID(chan, 0, &id)) {
        result = -1;
    } else if (IsCard(id)) {
        if (memSize) {
            *memSize = (s32)(id & 0xFC);
        }
        if (sectorSize) {
            *sectorSize = lbl_804F2BD8[(id & 0x3800) >> 11];
        }
        result = 0;
    } else {
        result = -2;
    }

    OSRestoreInterrupts(enabled);
    return result;
}
