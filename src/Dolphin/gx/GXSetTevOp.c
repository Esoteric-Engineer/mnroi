typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[0x12C];
    u32 tevc[16];
    u32 teva[16];
} __GXDataStruct;

extern __GXDataStruct* __GXData;

// Combined color (10 words) and alpha (10 words) TEV environment tables.
// The first 5 entries of each are for stage 0, the last 5 for later stages.
extern u32 lbl_804D32A0[];

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

void GXSetTevOp(int id, int mode)
{
    __GXDataStruct* gx;
    u32* base = lbl_804D32A0;
    u32* color;
    u32* alpha;
    u32 reg;

    if (id == 0) {
        color = &base[mode];
        alpha = &base[mode + 10];
    } else {
        color = &base[mode + 5];
        alpha = &base[mode + 15];
    }

    gx = __GXData;
    reg = gx->tevc[id];
    reg = (reg & 0xFF000000) | (*color & 0x00FFFFFF);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    gx->tevc[id] = reg;

    reg = gx->teva[id];
    reg = (reg & 0xFF00000F) | (*alpha & 0x00FFFFF0);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    gx->teva[id] = reg;
    gx->bpSentNot = 0;
}
