// Initialisers for a small record (ints at +0x0-0xC, floats at +0x10-0x18, vec at +0x20) and two float pairs.
extern void fn_8042DC84(void *dst, void *src);
extern const float lbl_8048E4C0[]; // 0.0f
extern const float lbl_8048E4C4[]; // 0.0f

void fn_80447C84(register char *self, register int a, register int b, register int c, register int d,
                 register float x, register float y, register float z, register void *vec)
{
    *(int *)(self + 0x0) = a;
    *(int *)(self + 0x4) = b;
    *(int *)(self + 0x8) = c;
    *(int *)(self + 0xC) = d;
    *(float *)(self + 0x10) = x;
    *(float *)(self + 0x14) = y;
    *(float *)(self + 0x18) = z;
    fn_8042DC84(self + 0x20, vec);
}

void fn_80447D18(register char *self)
{
    *(unsigned char *)(self + 0x0) = 0;
    *(unsigned char *)(self + 0x1) = 0;
    *(unsigned char *)(self + 0x2) = 0;
    *(unsigned char *)(self + 0x3) = 0;
    *(int *)(self + 0x4) = 0;
    *(int *)(self + 0x8) = 0;
    *(int *)(self + 0xC) = 0;
    *(int *)(self + 0x10) = 0;
    *(float *)(self + 0x14) = lbl_8048E4C0[0];
}

void fn_80447D84(register float *self)
{
    self[0] = lbl_8048E4C4[0];
    self[1] = lbl_8048E4C4[0];
}
