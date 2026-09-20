typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
} GXFifoObj;

volatile GXFifoObj GXWGFifo : 0xCC008000;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x2];
    u16 bpSentNot;
    u8 pad1[0x1CC];
    u32 cmode0;
    u8 pad2[4];
    u32 zmode;
    u32 peCtrl;
    u32 cpDispSrc;
    u32 cpDispSize;
    u32 cpDispStride;
    u32 cpDisp;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXCopyDisp(void* dest, u8 clear)
{
    u32 reg;
    u32 phyAddr;
    u32 tempPeCtrl;
    u8 changePeCtrl;
    __GXDataStruct* gx;

    if (clear) {
        gx = __GXData;
        reg = gx->zmode;
        SET_REG_FIELD(reg, 1, 0, 1);
        SET_REG_FIELD(reg, 3, 1, 7);
        GXWGFifo.u8 = 0x61;
        GXWGFifo.u32 = reg;

        reg = gx->cmode0;
        SET_REG_FIELD(reg, 1, 0, 0);
        SET_REG_FIELD(reg, 1, 1, 0);
        GXWGFifo.u8 = 0x61;
        GXWGFifo.u32 = reg;
    }
    changePeCtrl = 0;
    if ((clear || (__GXData->peCtrl & 7) == 3) && ((__GXData->peCtrl >> 6) & 1) == 1) {
        changePeCtrl = 1;
        tempPeCtrl = __GXData->peCtrl;
        SET_REG_FIELD(tempPeCtrl, 1, 6, 0);
        GXWGFifo.u8 = 0x61;
        GXWGFifo.u32 = tempPeCtrl;
    }
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = __GXData->cpDispSrc;
    gx = __GXData;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = gx->cpDispSize;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = gx->cpDispStride;

    phyAddr = (u32)dest & 0x3FFFFFFF;
    reg = 0;
    SET_REG_FIELD(reg, 21, 0, phyAddr >> 5);
    SET_REG_FIELD(reg, 8, 24, 0x4B);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;

    SET_REG_FIELD(gx->cpDisp, 1, 11, clear);
    SET_REG_FIELD(gx->cpDisp, 1, 14, 1);
    SET_REG_FIELD(gx->cpDisp, 8, 24, 0x52);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = gx->cpDisp;

    if (clear) {
        GXWGFifo.u8 = 0x61;
        GXWGFifo.u32 = gx->zmode;
        GXWGFifo.u8 = 0x61;
        GXWGFifo.u32 = gx->cmode0;
    }
    if (changePeCtrl) {
        GXWGFifo.u8 = 0x61;
        GXWGFifo.u32 = __GXData->peCtrl;
    }
    __GXData->bpSentNot = 0;
}
