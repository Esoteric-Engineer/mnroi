// Vec4/quaternion helpers; the 0.0f pool is read through extern_pool (docs/versus.md section 5, row 8).

extern float *fn_804352C8(void *self, int i);
extern float fn_8043B638(float x);
extern float fn_8043C648(float x);
extern void fn_8043632C(void *dst, void *src);
extern void fn_80436610(void *self);
extern void fn_80438398(void *out, void *a);
extern void *fn_8043C814(void *self, int i);
extern void *fn_80434988(void *self);
extern void fn_8043C8E0(void *self, void *a);
extern void fn_8032A230(void *buf, void *self, ...);
extern int fn_80436294(void *self);
extern void *fn_80317950(void *self);
extern int fn_8043CA10(void *a, int *b);
extern void fn_80317B2C(void *self, int v);
extern void fn_803299DC(int a, void *self);
extern void fn_80325C78(int a, void *self, int v);
extern void __builtin_delete(void *p);

extern char lbl_804DC280[];
extern char lbl_804F3D20[];
extern int lbl_8066B834;
extern int lbl_8066B838;
extern int lbl_8066B840;

float fn_8043BDC0(register void *self)
{
    float x = fn_8043B638(*fn_804352C8(self, 3));
    x = fn_8043C648(x);
    x = 2.0f * x;
    return x;
}

void fn_8043BE40(register void *self, register void *out)
{
    fn_8043632C(out, self);
    fn_80436610(out);
    if (*fn_804352C8(self, 3) < 0.0f) {
        fn_80438398(out, out);
    }
}

void *fn_8043BEB8(register void *self, register int i)
{
    return fn_8043C814(self, i);
}

char *fn_8043BF04(void)
{
    return lbl_804DC280;
}

void *fn_8043BF2C(register char *self)
{
    fn_80434988(self);
    fn_80434988(self + 0x10);
    return self;
}

void fn_8043BF78(register char *self, register void *a)
{
    fn_8043C8E0(self + 0x14, a);
}

char *fn_8043BFBC(register char *self)
{
    *(char **)(self + 0x10) = lbl_804F3D20;
    return self;
}

void fn_8043BFF0(register char *self, register int inChrg)
{
    *(char **)(self + 0x10) = lbl_804F3D20;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

int fn_8043C048(register int *self)
{
    return *self;
}

int fn_8043C074(register void *self)
{
    char tmp[8];

    fn_8032A230(tmp, self);
    return fn_80436294(tmp);
}

void fn_8043C0C8(register void *self)
{
    if (self != 0) {
        if (fn_8043CA10(fn_80317950(self), &lbl_8066B838) == -1) {
            fn_80317B2C(self, lbl_8066B838);
        }
    }
}

void fn_8043C134(register void *self, register int flag)
{
    if (flag) {
        fn_803299DC(lbl_8066B840, self);
    } else {
        fn_803299DC(lbl_8066B834, self);
    }
}

void fn_8043C18C(register void *self, register int flag)
{
    if (flag) {
        fn_80325C78(lbl_8066B840, self, 1);
    } else {
        fn_80325C78(lbl_8066B834, self, 1);
    }
}
