typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;

typedef enum {
    VI_INTERLACE,
    VI_NON_INTERLACE,
    VI_PROGRESSIVE
} VIScanMode;

typedef enum {
    VI_NTSC,
    VI_PAL,
    VI_MPAL,
    VI_DEBUG,
    VI_DEBUG_PAL,
    VI_EURGB60
} VITVFormat;

typedef enum {
    VI_XFBMODE_SF,
    VI_XFBMODE_DF
} VIXFBMode;

#define VI_TVMODE(format, mode) (((format) << 2) + (mode))

#define VI_TVMODE_NTSC_INT      VI_TVMODE(VI_NTSC, VI_INTERLACE)
#define VI_TVMODE_NTSC_PROG     VI_TVMODE(VI_NTSC, VI_PROGRESSIVE)
#define VI_TVMODE_PAL_INT       VI_TVMODE(VI_PAL, VI_INTERLACE)
#define VI_TVMODE_EURGB60_INT   VI_TVMODE(VI_EURGB60, VI_INTERLACE)

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

volatile u16 __VIRegs[59] : 0xCC002000;

extern s32 VIGetTvFormat(void);
extern void VIConfigure(GXRenderModeObj* rm);
extern void VIConfigurePan(u16 xOrg, u16 yOrg, u16 width, u16 height);

void ConfigureVideo(u16 fbWidth, u16 xfbHeight)
{
    GXRenderModeObj rmode;

    rmode.fbWidth = fbWidth;
    rmode.efbHeight = 480;
    rmode.xfbHeight = xfbHeight;
    rmode.viXOrigin = (720 - 640) / 2;
    rmode.viWidth = 640;
    rmode.viHeight = xfbHeight;

    switch (VIGetTvFormat()) {
    case VI_NTSC:
    case VI_MPAL:
        if (__VIRegs[54] & 1) {
            rmode.viTVmode = VI_TVMODE_NTSC_PROG;
            rmode.viYOrigin = 0;
            rmode.xFBmode = VI_XFBMODE_SF;
        } else {
            rmode.viTVmode = VI_TVMODE_NTSC_INT;
            rmode.viYOrigin = 0;
            rmode.xFBmode = VI_XFBMODE_DF;
        }
        break;
    case VI_EURGB60:
        rmode.viTVmode = VI_TVMODE_EURGB60_INT;
        rmode.viYOrigin = 0;
        rmode.xFBmode = VI_XFBMODE_DF;
        break;
    case VI_PAL:
        rmode.viTVmode = VI_TVMODE_PAL_INT;
        rmode.viYOrigin = (574 - 480) / 2;
        rmode.xFBmode = VI_XFBMODE_DF;
        break;
    }

    VIConfigure(&rmode);
    VIConfigurePan(0, 0, 640, 480);
}
