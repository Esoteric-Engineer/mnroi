typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct {
    u32 mode0;
    u32 mode1;
    u32 image0;
    u32 image3;
    void* userData;
    int fmt;
    u32 tlutName;
    u16 loadCnt;
    u8 loadFmt;
    u8 flags;
} GXTexObj;

typedef struct {
    u32 image1;
    u32 image2;
} GXTexRegion;

typedef struct {
    u32 loadTlut1;
    u32 tlut;
} GXTlutRegionInt;

typedef int GXTexMapID;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared; the rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[1224];
    GXTlutRegionInt* (*tlutRegionCallback)(u32);
    u8 pad2[68];
    u32 tImage0[8];
    u32 tMode0[8];
    u8 pad3[88];
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

#define SET_REG_FIELD(reg, size, shift, val)                                  \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift),                    \
                          (32 - (shift) - (size)), (31 - (shift)))

#define GX_WRITE_RAS_REG(value) \
    do {                        \
        GXWGFifo.u8 = 0x61;     \
        GXWGFifo.u32 = (value); \
    } while (0)

extern u8 GXTexMode0Ids[8];
extern u8 GXTexMode1Ids[8];
extern u8 GXTexImage0Ids[8];
extern u8 GXTexImage1Ids[8];
extern u8 GXTexImage2Ids[8];
extern u8 GXTexImage3Ids[8];
extern u8 GXTexTlutIds[8];

void GXLoadTexObjPreLoaded(GXTexObj* t, GXTexRegion* r, GXTexMapID id)
{
    GXTlutRegionInt* tlr;
    __GXDataStruct* gx;

    SET_REG_FIELD(t->mode0, 8, 24, GXTexMode0Ids[id]);
    SET_REG_FIELD(t->mode1, 8, 24, GXTexMode1Ids[id]);
    SET_REG_FIELD(t->image0, 8, 24, GXTexImage0Ids[id]);
    SET_REG_FIELD(r->image1, 8, 24, GXTexImage1Ids[id]);
    SET_REG_FIELD(r->image2, 8, 24, GXTexImage2Ids[id]);
    SET_REG_FIELD(t->image3, 8, 24, GXTexImage3Ids[id]);

    GX_WRITE_RAS_REG(t->mode0);
    GX_WRITE_RAS_REG(t->mode1);
    GX_WRITE_RAS_REG(t->image0);
    GX_WRITE_RAS_REG(r->image1);
    GX_WRITE_RAS_REG(r->image2);
    GX_WRITE_RAS_REG(t->image3);

    if (!(t->flags & 2)) {
        tlr = __GXData->tlutRegionCallback(t->tlutName);
        SET_REG_FIELD(tlr->tlut, 8, 24, GXTexTlutIds[id]);
        GX_WRITE_RAS_REG(tlr->tlut);
    }
    gx = __GXData;
    gx->tImage0[id] = t->image0;
    gx->tMode0[id] = t->mode0;
    gx->dirtyState |= 1;
    gx->bpSentNot = 0;
}
