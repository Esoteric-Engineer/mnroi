typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x1E0];
    u32 cpDispSrc;
    u32 cpDispSize;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetDispCopySrc(u16 left, u16 top, u16 wd, u16 ht)
{
    __GXData->cpDispSrc = 0;
    SET_REG_FIELD(__GXData->cpDispSrc, 10, 0, left);
    SET_REG_FIELD(__GXData->cpDispSrc, 10, 10, top);
    SET_REG_FIELD(__GXData->cpDispSrc, 8, 24, 0x49);

    __GXData->cpDispSize = 0;
    SET_REG_FIELD(__GXData->cpDispSize, 10, 0, wd - 1);
    SET_REG_FIELD(__GXData->cpDispSize, 10, 10, ht - 1);
    SET_REG_FIELD(__GXData->cpDispSize, 8, 24, 0x4A);
}

// GXFrameBuf.c's render modes (GXInit reads these four by address).
// Each is followed by unreferenced bytes left over from the SDK's other unused render mode objects.
// Copied verbatim instead of being given a semantic shape.
typedef enum {
    VI_XFBMODE_SF,
    VI_XFBMODE_DF
} VIXFBMode;

typedef struct _GXRenderModeObj {
    u32 viTVmode;
    u16 fbWidth;
    u16 efbHeight;
    u16 xfbHeight;
    u16 viXOrigin;
    u16 viYOrigin;
    u16 viWidth;
    u16 viHeight;
    VIXFBMode xFBmode;
    u8 field_rendering;
    u8 aa;
    u8 sample_pattern[12][2];
    u8 vfilter[7];
} GXRenderModeObj;

GXRenderModeObj GXNtsc480IntDf = {
    0, 640, 480, 480, 40, 0, 640, 480, VI_XFBMODE_DF, 0, 0,
    { {6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6} },
    { 8, 8, 10, 12, 10, 8, 8 }
};

#pragma force_active on
u8 lbl_804D3624[0x24] = {
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#pragma force_active reset

GXRenderModeObj GXMpal480IntDf = {
    8, 640, 480, 480, 40, 0, 640, 480, VI_XFBMODE_DF, 0, 0,
    { {6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6} },
    { 8, 8, 10, 12, 10, 8, 8 }
};

#pragma force_active on
u8 lbl_804D3684[0x18] = {
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#pragma force_active reset

GXRenderModeObj GXPal528IntDf = {
    4, 640, 528, 528, 40, 23, 640, 528, VI_XFBMODE_DF, 0, 0,
    { {6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6} },
    { 8, 8, 10, 12, 10, 8, 8 }
};

#pragma force_active on
u8 lbl_804D36D8[0x18] = {
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#pragma force_active reset

GXRenderModeObj GXEurgb60Hz480IntDf = {
    20, 640, 480, 480, 40, 0, 640, 480, VI_XFBMODE_DF, 0, 0,
    { {6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6} },
    { 8, 8, 10, 12, 10, 8, 8 }
};

#pragma force_active on
u8 lbl_804D372C[0xC] = {
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#pragma force_active reset
