typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef float f32;

typedef struct {
    u8 r, g, b, a;
} GXColor;

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

extern const f32 lbl_80670710; // 0.0f
extern const f32 lbl_80670714; // 1.0f
extern const f32 lbl_80670718; // 0.5f
extern const double lbl_80670720; // 1.0
extern const f32 lbl_80670728; // 2.0f
extern const double lbl_80670730; // 0.5
extern const f32 lbl_80670738; // 8.388638e6f

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetFog(u32 type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color)
{
    u32 fogclr = 0;
    u32 fog0 = 0;
    u32 fog1 = 0;
    u32 fog2 = 0;
    u32 fog3 = 0;
    f32 A;
    f32 B;
    f32 C;
    f32 B_mant;
    f32 a;
    f32 c;
    u32 B_expn;
    u32 b_m;
    u32 b_s;
    u32 a_hex;
    u32 c_hex;
    u32 ortho = (type >> 3) & 1;
    u32 fmt = type & 7;

    if (ortho) {
        if (farz == nearz || endz == startz) {
            a = lbl_80670710;
            c = lbl_80670710;
        } else {
            f32 tmp = lbl_80670714 / (endz - startz);
            a = tmp * (farz - nearz);
            c = tmp * (startz - nearz);
        }
    } else {
        if (farz == nearz || endz == startz) {
            A = C = lbl_80670710;
            B = lbl_80670718;
        } else {
            A = (farz * nearz) / ((farz - nearz) * (endz - startz));
            B = farz / (farz - nearz);
            C = startz / (endz - startz);
        }

        B_mant = B;
        B_expn = 0;
        while (B_mant > lbl_80670720) {
            B_mant *= lbl_80670718;
            B_expn++;
        }
        while (B_mant > lbl_80670710 && B_mant < lbl_80670730) {
            B_mant *= lbl_80670728;
            B_expn--;
        }

        a = A / (f32)(1 << (B_expn + 1));
        b_m = lbl_80670738 * B_mant;
        b_s = B_expn + 1;
        c = C;

        SET_REG_FIELD(fog1, 24, 0, b_m);
        SET_REG_FIELD(fog2, 5, 0, b_s);
        SET_REG_FIELD(fog1, 8, 24, 0xEF);
        SET_REG_FIELD(fog2, 8, 24, 0xF0);
    }

    a_hex = *(u32*)&a;
    c_hex = *(u32*)&c;

    SET_REG_FIELD(fog0, 11, 0, (a_hex >> 12) & 0x7FF);
    SET_REG_FIELD(fog0, 8, 11, (a_hex >> 23) & 0xFF);
    SET_REG_FIELD(fog0, 1, 19, (a_hex >> 31));
    SET_REG_FIELD(fog0, 8, 24, 0xEE);

    SET_REG_FIELD(fog3, 11, 0, (c_hex >> 12) & 0x7FF);
    SET_REG_FIELD(fog3, 8, 11, (c_hex >> 23) & 0xFF);
    SET_REG_FIELD(fog3, 1, 19, (c_hex >> 31));
    SET_REG_FIELD(fog3, 1, 20, ortho);
    SET_REG_FIELD(fog3, 3, 21, fmt);
    SET_REG_FIELD(fog3, 8, 24, 0xF1);

    SET_REG_FIELD(fogclr, 24, 0, *(u32*)&color >> 8);
    SET_REG_FIELD(fogclr, 8, 24, 0xF2);

    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = fog0;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = fog1;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = fog2;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = fog3;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = fogclr;
    __GXData->bpSentNot = 0;
}
