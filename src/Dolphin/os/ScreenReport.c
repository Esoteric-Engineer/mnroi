typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed char s8;
typedef long s32;

typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;

extern char* OSGetFontTexel(char* string, void* image, s32 pos, s32 stride, s32* width);

void ScreenReport(void* xfb, u16 xfbW, u16 xfbH, GXColor yuv, s32 x, s32 y, s32 leading, char* string)
{
    u8* ptr;
    s32 width;
    u32 i;
    u32 j;
    u32 image[72];
    u32 k;
    u32 l;
    u8 Y;
    u32 pixel;
    s32 col;

loop_1:
    if (xfbH - 24 >= y) {
        ptr = (u8*)xfb + ((x + (y * xfbW)) * 2);
        col = x;

        while ((s8)*string != 0) {
            if ((s8)*string == '\n') {
                string++;
                y += leading;
                goto loop_1;
            }

            if (xfbW - 48 < col) {
                y += leading;
                goto loop_1;
            }

            for (i = 0; i < 24; i++) {
                j = (i & 7) + ((i >> 3) * 24);
                image[j + 0] = 0;
                image[j + 8] = 0;
                image[j + 16] = 0;
            }

            string = OSGetFontTexel(string, image, 0, 6, &width);

            for (i = 0; i < 24; i++) {
                j = (i & 7) + ((i >> 3) * 24);

                for (k = 0; k < 24; k++) {
                    l = j + (k & 0xFFFFFFF8);

                    Y = (image[l] >> ((7 - (k & 7)) * 4)) & 0xF;
                    if (Y != 0) {
                        Y = (((yuv.r * (Y * 0xEF)) / 255) / 15) + 0x10;
                        pixel = k + (i * xfbW);
                        ptr[pixel * 2] = Y;

                        if ((col + k) & 1) {
                            ptr[(pixel * 2) - 1] = yuv.g;
                            ptr[(pixel * 2) + 1] = yuv.b;
                        } else {
                            ptr[(pixel * 2) - 1] = yuv.b;
                            ptr[(pixel * 2) + 1] = yuv.g;
                        }
                    }
                }
            }

            ptr += width * 2;
            col += width;
        }
    }
}
