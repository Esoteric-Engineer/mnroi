typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x2];
    u16 bpSentNot;
    u8 pad1[0xB0 - 0x4];
    u32 color[2];
} __GXDataStruct;

extern __GXDataStruct* __GXData;

void GXSetChanMatColor(int chan, u32* color)
{
    __GXDataStruct* gx;
    u32 reg;
    u32 idx;

    switch (chan) {
    case 0:
        reg = __GXData->color[0];
        reg = (u32)__rlwimi((int)reg, (int)*color, 0, 0, 23);
        idx = 0;
        break;
    case 1:
        reg = __GXData->color[1];
        reg = (u32)__rlwimi((int)reg, (int)*color, 0, 0, 23);
        idx = 1;
        break;
    case 2:
        reg = __GXData->color[0];
        reg = (u32)__rlwimi((int)reg, (int)((u8*)color)[3], 0, 24, 31);
        idx = 0;
        break;
    case 3:
        reg = __GXData->color[1];
        reg = (u32)__rlwimi((int)reg, (int)((u8*)color)[3], 0, 24, 31);
        idx = 1;
        break;
    case 4:
        reg = *color;
        idx = 0;
        break;
    case 5:
        reg = *color;
        idx = 1;
        break;
    default:
        return;
    }

    gx = __GXData;
    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = idx + 0x100C;
    GXWGFifo.u32 = reg;
    gx->bpSentNot = 1;
    gx->color[idx] = reg;
}
