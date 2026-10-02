typedef unsigned long u32;
typedef long s32;
typedef unsigned char u8;
typedef void (*EXICallback)(s32, void*);

extern int EXIImm(s32 chan, void* buf, s32 len, u32 type, EXICallback callback);
extern int EXISync(s32 chan);

#pragma scheduling off

int EXIImmEx(s32 chan, void* buf, s32 len, u32 mode)
{
    s32 xLen;

    while (len) {
        xLen = (len < 4) ? len : 4;
        if (EXIImm(chan, buf, xLen, mode, 0) == 0) {
            return 0;
        }
        if (EXISync(chan) == 0) {
            return 0;
        }
        ((u8*)buf) += xLen;
        len -= xLen;
    }
    return 1;
}
