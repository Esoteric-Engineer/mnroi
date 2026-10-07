// Word getter, 2D distance and small forwarders/constructors starting a file at 0x80441AD8 (docs/versus.md, row 8).

struct Obj
{
    char pad[0x40];
    int w40; // +0x40
};

extern "C" int fn_80441AD8(register Obj *self)
{
    return self->w40;
}

inline int sn_return_decl(int a)
{
    return a;
}

extern "C" {
double __ieee754_sqrt(double x);
int fn_8043BAA0(void *self, int i);
void fn_8043B9AC(void *p);
void fn_80434988(void *p);
void fn_8043F718(void *self, void *src);
void fn_8043632C(void *dst, void *src);

float fn_80441B0C(register float *a, register float *b)
{
    return __ieee754_sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]));
}

int fn_80441B98(register void *self, register int i)
{
    return fn_8043BAA0(self, i);
}

char *fn_80441BE4(register char *self, register char *src)
{
    fn_8043B9AC(self);
    fn_80434988(self + 0x30);
    fn_8043F718(self, src);
    fn_8043632C(self + 0x30, src + 0x30);
    return self;
}
}
