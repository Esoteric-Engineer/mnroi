typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct {
    u32 tlut;
    u32 loadTlut0;
    u16 numEntries;
} GXTlutObj;

typedef struct {
    u32 loadTlut1;
    GXTlutObj tlutObj;
} GXTlutRegion;

// Real Dolphin SDK global GX state (gx). Only the field this function touches is declared; the rest is padding to keep its offset correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[1224];
    GXTlutRegion* (*tlutRegionCallback)(u32);
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

extern void __GXFlushTextureState(void);

void GXLoadTlut(GXTlutObj* tlut_obj, u32 tlut_name)
{
    GXTlutRegion* r;
    u32 tlut_offset;

    r = __GXData->tlutRegionCallback(tlut_name);
    __GXFlushTextureState();
    GX_WRITE_RAS_REG(tlut_obj->loadTlut0);
    GX_WRITE_RAS_REG(r->loadTlut1);
    __GXFlushTextureState();
    tlut_offset = r->loadTlut1 & 0x3FF;
    SET_REG_FIELD(tlut_obj->tlut, 10, 0, tlut_offset);
    r->tlutObj = *tlut_obj;
}
