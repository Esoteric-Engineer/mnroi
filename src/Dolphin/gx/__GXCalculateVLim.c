typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed long s32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared; the rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[4];
    u16 vNum;
    u16 vLim;
    u8 pad1[0x14 - 8];
    u32 vcdLo;
    u32 vcdHi;
    u32 vatA[8];
} __GXDataStruct;

extern __GXDataStruct* __GXData;

#define GET_REG_FIELD(reg, size, shift) (((reg) >> (shift)) & ((1 << (size)) - 1))

void __GXCalculateVLim(void)
{
    static u8 tbl1[] = { 0, 4, 1, 2 };
    static u8 tbl2[] = { 0, 8, 1, 2 };
    static u8 tbl3[] = { 0, 12, 1, 2 };
    u32 vlm;
    s32 b;
    u32 vl;
    u32 vh;

    if (__GXData->vNum != 0) {
        vl = __GXData->vcdLo;
        vh = __GXData->vcdHi;
        vlm = GET_REG_FIELD(vl, 1, 0);
        vlm += (u8)GET_REG_FIELD(vl, 1, 1);
        vlm += (u8)GET_REG_FIELD(vl, 1, 2);
        vlm += (u8)GET_REG_FIELD(vl, 1, 3);
        vlm += (u8)GET_REG_FIELD(vl, 1, 4);
        vlm += (u8)GET_REG_FIELD(vl, 1, 5);
        vlm += (u8)GET_REG_FIELD(vl, 1, 6);
        vlm += (u8)GET_REG_FIELD(vl, 1, 7);
        vlm += (u8)GET_REG_FIELD(vl, 1, 8);

        vlm += tbl3[(u8)GET_REG_FIELD(vl, 2, 9)];
        b = __GXData->vatA[0];
        b = (b & 0x200) >> 9;
        vlm += tbl3[(u8)GET_REG_FIELD(vl, 2, 11)] * (b == 1 ? 3 : 1);
        vlm += tbl1[(u8)GET_REG_FIELD(vl, 2, 13)];
        vlm += tbl1[(u8)GET_REG_FIELD(vl, 2, 15)];

        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 0)];
        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 2)];
        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 4)];
        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 6)];
        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 8)];
        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 10)];
        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 12)];
        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 14)];
        __GXData->vLim = vlm;
    }
}
