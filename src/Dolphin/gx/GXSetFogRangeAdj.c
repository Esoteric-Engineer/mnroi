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
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

typedef struct {
    u16 r[10];
} GXFogAdjTable;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetFogRangeAdj(u8 enable, u16 center, GXFogAdjTable* table)
{
    u32 i;
    u32 range_adj;
    u32 range_c;

    if (enable) {
        for (i = 0; i < 10; i += 2) {
            range_adj = 0;
            SET_REG_FIELD(range_adj, 12, 0, table->r[i]);
            SET_REG_FIELD(range_adj, 12, 12, table->r[i + 1]);
            SET_REG_FIELD(range_adj, 8, 24, (i >> 1) + 0xE9);
            GXWGFifo.u8 = 0x61;
            GXWGFifo.u32 = range_adj;
        }
    }
    range_c = 0;
    SET_REG_FIELD(range_c, 10, 0, center + 342);
    SET_REG_FIELD(range_c, 1, 10, enable);
    SET_REG_FIELD(range_c, 8, 24, 0xE8);
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = range_c;
    __GXData->bpSentNot = 0;
}
