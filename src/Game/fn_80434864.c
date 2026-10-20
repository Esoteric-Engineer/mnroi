// Small G/vector accessors; the .rodata float pool is read through extern_pool.

typedef struct Table
{
    char pad[0xC];
    float f[8][2]; // +0xC, indexed [a][b]
} Table;

extern Table *lbl_8066C63C;
extern void *fn_8042FF2C(int p);

void fn_80434864(register char *self, register int flag)
{
    if (flag)
        *(unsigned int *)(self + 0x4) |= 0x800000;
}

float fn_8043489C(register int a, register int b)
{
    return lbl_8066C63C ? lbl_8066C63C->f[a][b] : 0.0f;
}

int fn_80434900(register char *self)
{
    return *(int *)(self + 0x590);
}

void *fn_8043492C(register char *self)
{
    if (*(int *)(self + 0x750)) {
        return fn_8042FF2C(*(int *)(self + 0x750));
    } else {
        return 0;
    }
}

void *fn_80434988(register void *a)
{
    return a;
}

void fn_804349B0(register float *out, register float *a, register float *b)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
    out[3] = a[3] - b[3];
}

extern float *fn_804352C8(void *v, int i);
extern void fn_80435300(void *self, float x, float y, float z, float w);

void fn_80434A18(register void *self, register void *a, register void *b)
{
    float x, y, z;
    register float rx, ry, rz;
    rx = *fn_804352C8(a, 1) * *fn_804352C8(b, 2) - *fn_804352C8(a, 2) * *fn_804352C8(b, 1);
    x = rx;
    ry = *fn_804352C8(a, 2) * *fn_804352C8(b, 0) - *fn_804352C8(a, 0) * *fn_804352C8(b, 2);
    y = ry;
    rz = *fn_804352C8(a, 0) * *fn_804352C8(b, 1) - *fn_804352C8(a, 1) * *fn_804352C8(b, 0);
    z = rz;
    fn_80435300(self, x, y, z, 0.0f);
}
