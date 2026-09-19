typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u16 vNumNot;
    u16 bpSentNot;
    u16 vNum;
    u8 pad0[0x5A9 - 0x6];
    u8 dlSaveContext;
    u8 unk5AA;
    u8 pad1[0x5AC - 0x5AB];
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

void GXSetMisc(int token, u32 val)
{
    switch (token) {
    case 1: {
        __GXDataStruct* gx = __GXData;
        gx->vNum = val;
        gx->vNumNot = !gx->vNum;
        gx->bpSentNot = 1;
        if (gx->vNum != 0) {
            gx->dirtyState |= 8;
        }
        break;
    }
    case 2:
        __GXData->dlSaveContext = (val > 0);
        break;
    case 3:
        __GXData->unk5AA = (val > 0);
        break;
    case 0:
    default:
        break;
    }
}
