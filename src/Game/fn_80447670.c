// Accessors and setters on the 0x70-byte object whose reset is fn_80446E10.
extern const float lbl_8048DE6C[]; // 0.0f

extern void fn_8042DC84(void *dst, void *src);
extern void fn_80429038(void *a, void *b, void *c);
extern float fn_8042EC54(void *v);
extern int fn_800F4560(void *a, int b);
extern void fn_800F45EC(void *a, int b);

void fn_80447670(register char *self, register void *a, register void *b)
{
    fn_8042DC84(self, a);
    fn_8042DC84(self + 0x10, b);
    fn_80429038(self + 0x20, self + 0x10, self);
    *(float *)(self + 0x30) = fn_8042EC54(self + 0x20);
}

int fn_804476F0(register char *self)
{
    return (unsigned short)(*(unsigned short *)(self + 0x68) & 1);
}

int fn_80447724(register char *self)
{
    return !*(int *)(self + 0x8);
}

void fn_8044775C(register char *self)
{
    *(unsigned short *)(self + 0x68) = 1;
    *(int *)(self + 0x8) = 0;
    *(unsigned short *)(self + 0x60) = 0;
    *(float *)(self + 0x64) = lbl_8048DE6C[0];
    *(unsigned char *)(self + 0x6A) = 0;
}

void fn_804477A8(register char *self)
{
    *(unsigned short *)(self + 0x68) = *(unsigned short *)(self + 0x68) & ~1;
}

void fn_804477D8(register void *self, register int x)
{
    if (!fn_800F4560(self, x))
        fn_800F45EC(self, x);
}
