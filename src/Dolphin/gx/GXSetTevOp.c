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

extern __GXDataStruct* const __GXData;

// Four 5-word TEV environment tables laid out back to back, indexed by GXTevMode:
// - color/stage0 at +0
// - color/other stages at +20
// - alpha/stage0 at +40
// - alpha/other at +60
// The byte offsets are what the original applies to the base pointer; a 2D array or a struct of arrays makes MWCC share `base + mode * 4` between the two pointers instead.
u32 TevOpTables[20] = {
    0xc008f8af, 0xc008a89f, 0xc008ac8f, 0xc008fff8, 0xc008fffa,
    0xc008f80f, 0xc008089f, 0xc0080c8f, 0xc008fff8, 0xc008fff0,
    0xc108f2f0, 0xc108ffd0, 0xc108f2f0, 0xc108ffc0, 0xc108ffd0,
    0xc108f070, 0xc108ff80, 0xc108f070, 0xc108ffc0, 0xc108ff80,
};

// Read by GXSetTevOrder (TU boundary crossed: GXSetTevOrder.c externs this).
int c2r[9] = { 0, 1, 0, 1, 0, 1, 7, 5, 6 };

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

void GXSetTevOp(int id, int mode)
{
    u32* color;
    u32* alpha;
    u32 reg;
    u8* base = (u8*)TevOpTables;

    if (id == 0) {
        color = (u32*)base + mode;
        alpha = (u32*)(base + 40) + mode;
    } else {
        color = (u32*)(base + 20) + mode;
        alpha = (u32*)(base + 60) + mode;
    }

    reg = __GXData->tevc[id];
    reg = (reg & 0xFF000000) | (*color & 0x00FFFFFF);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    __GXData->tevc[id] = reg;

    reg = __GXData->teva[id];
    reg = (reg & 0xFF00000F) | (*alpha & 0x00FFFFF0);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = reg;
    __GXData->teva[id] = reg;
    __GXData->bpSentNot = 0;
}
