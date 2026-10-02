typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[0x1D0];
    u32 cmode1;
    u32 zmode;
    u32 peCtrl;
    u8 pad2[0x24];
    u32 genMode;
    u8 pad3[0x3A4];
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetPixelFmt(int pix_fmt, u32 z_fmt)
{
    u32 newPeCtrl;
    u32 oldPeCtrl;
    u8 aa;
    static u32 p2f[8] = { 0, 1, 2, 3, 4, 4, 4, 5 };

    oldPeCtrl = __GXData->peCtrl;
    SET_REG_FIELD(__GXData->peCtrl, 3, 0, p2f[pix_fmt]);
    SET_REG_FIELD(__GXData->peCtrl, 3, 3, z_fmt);
    newPeCtrl = __GXData->peCtrl;
    if (oldPeCtrl != newPeCtrl) {
        GXWGFifo.u8 = 0x61;
        GXWGFifo.u32 = newPeCtrl;
        if (pix_fmt == 2)
            aa = 1;
        else
            aa = 0;
        SET_REG_FIELD(__GXData->genMode, 1, 9, aa);
        __GXData->dirtyState |= 4;
    }
    if (p2f[pix_fmt] == 4) {
        SET_REG_FIELD(__GXData->cmode1, 2, 9, (pix_fmt - 4) & 0x3);
        SET_REG_FIELD(__GXData->cmode1, 8, 24, 0x42);
        GXWGFifo.u8 = 0x61;
        GXWGFifo.u32 = __GXData->cmode1;
    }
    __GXData->bpSentNot = 0;
}
