typedef unsigned long u32;
typedef long s32;

u32 lbl_8066F4BC;
u32 lbl_8066F4B8;
u32 lbl_8066F4B4;
u32 lbl_8066F4B0;

extern s32 EXIGetID(s32 chan, u32 dev, s32* id);
extern int ProbeBarnacle(s32 chan, u32 dev, s32* revision);

void __OSEnableBarnacle(s32 chan, u32 dev)
{
    s32 id;

    if (!EXIGetID(chan, dev, &id)) {
        return;
    }

    switch (id) {
    case 0x00000004:
    case 0x00000008:
    case 0x00000010:
    case 0x00000020:
    case 0x01010000:
    case 0x01020000:
    case 0x02020000:
    case 0x03010000:
    case 0x04020100:
    case 0x04020200:
    case 0x04020300:
    case 0x04220000:
    case 0x04040404:
    case 0x04060000:
    case 0x04120000:
    case 0x04130000:
    case 0x80000004:
    case 0x80000008:
    case 0x80000010:
    case 0x80000020:
    case 0xFFFFFFFF:
        break;
    default:
        if (ProbeBarnacle(chan, dev, &id)) {
            lbl_8066F4B0 = chan;
            lbl_8066F4B4 = dev;
            lbl_8066F4B8 = lbl_8066F4BC = 0xA5FF005A;
            break;
        }
    }
}
