typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;
typedef float f32;
typedef int BOOL;

typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;

typedef struct FatalBlock {
    GXColor fg;
    GXColor bg;
    char* msg;
    u32 pad;
    long long context[0x2C8 / 8];
} FatalBlock;

typedef struct OSFontHeader {
    u16 fontType;
    u16 firstChar;
    u16 lastChar;
    u16 invalChar;
    u16 ascent;
    u16 descent;
    u16 width;
    u16 leading;
    u16 cellWidth;
    u16 cellHeight;
    u32 sheetSize;
    u16 sheetFormat;
    u16 sheetColumn;
    u16 sheetRow;
    u16 sheetWidth;
    u16 sheetHeight;
    u16 widthTable;
    u32 sheetImage;
    u32 sheetFullSize;
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} OSFontHeader;

extern FatalBlock lbl_8064EF50;
extern char lbl_8066CEB0[4];

extern BOOL OSEnableInterrupts(void);
extern BOOL OSDisableInterrupts(void);
extern u32 strlen(const char* s);
extern void* memmove(void* dst, const void* src, u32 n);
extern void* OSAllocFromArenaLo(u32 size, u32 align);
extern void* OSGetArenaLo(void);
extern u32 OSLoadFont(OSFontHeader* fontData, void* tempBuffer);
extern void VISetNextFrameBuffer(void* fb);
extern void ConfigureVideo(u16 fbWidth, u16 xfbHeight);
extern void VIFlush(void);
extern u32 VIGetRetraceCount(void);
extern void VISetBlack(BOOL black);
extern void DCFlushRange(void* addr, u32 nBytes);
extern void OSReport(const char* msg, ...);
extern void PPCHalt(void);
extern void ScreenReport(void* xfb, u16 xfbW, u16 xfbH, GXColor yuv, s32 x, s32 y, s32 leading, char* string);

#pragma fp_contract off

static inline void ScreenClear(void* xfb, u16 xfbW, u16 xfbH, GXColor yuv)
{
    int i;
    int j;
    u8* ptr;

    ptr = xfb;
    for (i = 0; i < xfbH; i++) {
        for (j = 0; j < xfbW; j += 2) {
            *ptr++ = yuv.r;
            *ptr++ = yuv.g;
            *ptr++ = yuv.r;
            *ptr++ = yuv.b;
        }
    }
}

static inline GXColor RGB2YUV(GXColor rgb)
{
    f32 Y;
    f32 Cb;
    f32 Cr;
    GXColor yuv;

    Y = 0.5f + (16.0f + ((0.098f * (f32)rgb.b) + ((0.257f * (f32)rgb.r) + (0.504f * (f32)rgb.g))));
    Cb = 0.5f + (128.0f + ((0.439f * (f32)rgb.b) + ((-0.148f * (f32)rgb.r) - (0.291f * (f32)rgb.g))));
    Cr = 0.5f + (128.0f + (((0.439f * (f32)rgb.r) - (0.368f * (f32)rgb.g)) - (0.071f * (f32)rgb.b)));

    yuv.r = (Y > 235.0f) ? 235.0f : (Y < 16.0f) ? 16.0f : Y;
    yuv.g = (Cb > 240.0f) ? 240.0f : (Cb < 16.0f) ? 16.0f : Cb;
    yuv.b = (Cr > 240.0f) ? 240.0f : (Cr < 16.0f) ? 16.0f : Cr;
    yuv.a = 0;

    return yuv;
}

#pragma force_active on

void Halt(void)
{
    u32 count;
    OSFontHeader* fontData;
    void* xfb;
    u32 len;
    FatalBlock* fp;

    fp = &lbl_8064EF50;
    OSEnableInterrupts();
    len = strlen(fp->msg) + 1;
    fp->msg = memmove(OSAllocFromArenaLo(len, 32), fp->msg, len);

    fontData = OSAllocFromArenaLo(0xA1004, 32);
    OSLoadFont(fontData, OSGetArenaLo());

    xfb = OSAllocFromArenaLo(0x96000, 32);
    ScreenClear(xfb, 640, 480, RGB2YUV(fp->bg));
    VISetNextFrameBuffer(xfb);
    ConfigureVideo(640, 480);
    VIFlush();

    count = VIGetRetraceCount();
    do {
    } while ((s32)(VIGetRetraceCount() - count) < 2);

    ScreenReport(xfb, 640, 480, RGB2YUV(fp->fg), 48, 100, fontData->leading, fp->msg);
    DCFlushRange(xfb, 0x96000);
    VISetBlack(0);
    VIFlush();

    count = VIGetRetraceCount();
    do {
    } while ((s32)(VIGetRetraceCount() - count) < 1);

    OSDisableInterrupts();
    OSReport(lbl_8066CEB0, fp->msg);
    PPCHalt();
}
