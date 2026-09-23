typedef unsigned long u32;
typedef long s32;
typedef unsigned char u8;
typedef void (*EXICallback)(s32, void*);

extern int fn_80193F48(s32 chan, void* buf, s32 len, u32 type, EXICallback callback);
extern int fn_80194330(s32 chan);

#pragma scheduling off

int EXIImmEx(s32 chan, void* buf, s32 len, u32 mode)
{
    s32 xLen;

    while (len) {
        xLen = (len < 4) ? len : 4;
        if (fn_80193F48(chan, buf, xLen, mode, 0) == 0) {
            return 0;
        }
        if (fn_80194330(chan) == 0) {
            return 0;
        }
        ((u8*)buf) += xLen;
        len -= xLen;
    }
    return 1;
}
