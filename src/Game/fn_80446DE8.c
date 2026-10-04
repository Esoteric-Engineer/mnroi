// Vec4 add (fn_80446FD8), the list walk that fans a call out through vtable slot 2 (fn_80447040), and small
// accessors; the object layout is only partly known.
extern void __6Vector(void *v);
extern const float lbl_8048CD54[]; // 0.0f

void fn_80446DE8(register char *self, register float v)
{
    *(float *)(self + 0x170) = v;
}

char *fn_80446E10(register char *self)
{
    __6Vector(self + 0x10);
    __6Vector(self + 0x20);
    *(unsigned short *)(self + 0x68) = 0;
    *(int *)(self + 0x8) = 0;
    *(unsigned short *)(self + 0x60) = 0;
    *(float *)(self + 0x64) = lbl_8048CD54[0];
    *(unsigned char *)(self + 0x6A) = 0;
    return self;
}

int fn_80446E8C(register char *self)
{
    return *(int *)(self + 0x510);
}

int fn_80446EB8(register char *self)
{
    return *(int *)(self + 0x568);
}

char *fn_80446EE4(register char *self)
{
    return self + 0x570;
}

typedef struct VEntry
{
    short delta;
    short index;
    void *pfn;
} VEntry;

typedef struct Impl
{
    int x;
    VEntry *vptr; // +0x4
} Impl;

extern void fn_80447040(Impl **h, int a, float s);
extern void *fn_801B5D3C(void *list, int i);
extern int fn_801B6A44(void *list);

void fn_80446F10(register void *list, register int a, register float s)
{
    int *item;
    int i;

    for (i = 0; i < fn_801B6A44(list); i++)
    {
        item = fn_801B5D3C(list, i);
        fn_80447040((Impl **)*item, a, s);
    }
}

int fn_80446FA8(register char *self)
{
    return *(unsigned int *)(self + 0x20) & 0x10000;
}

void fn_80446FD8(register float *a, register float *b, register float *c)
{
    a[0] = b[0] + c[0];
    a[1] = b[1] + c[1];
    a[2] = b[2] + c[2];
    a[3] = b[3] + c[3];
}

void fn_80447040(register Impl **h, register int a, register float s)
{
    register VEntry *e;

    e = (*h)->vptr + 3;
    ((void (*)(void *, int, float))e->pfn)((char *)*h + e->delta, a, s);
}

typedef struct Axis
{
    void *owner;
    void *owner2; // +0x4
    short mode;   // +0x8
} Axis;

extern void fn_8044655C(Axis *self, float v, float w);
extern int fn_801991FC(void *owner);

// Like fn_8044667C, with a second owner at +0x4; 0 if either owner is rejected.
int fn_804470BC(register Axis *self, register void *a, register void *b, register float v, register float w, register int mode)
{
    self->mode = mode;
    if (a != 0)
    {
        if (fn_80446FA8(a) == 0)
        {
            if (fn_801991FC(a) == 0)
                return 0;
        }
    }
    if (b != 0)
    {
        if (fn_80446FA8(b) == 0)
        {
            if (fn_801991FC(b) == 0)
                return 0;
        }
    }
    self->owner = a;
    self->owner2 = b;
    fn_8044655C(self, v, w);
    return 1;
}

char *fn_804471A8(register char *self)
{
    return self + 0x10;
}

extern int fn_80435340(int x);

int fn_804471D4(register char *self)
{
    return fn_80435340(*(int *)(self + 0x30));
}

extern float *fn_8042FB28(void *p);
extern void fn_80436100(float *v, void *m);

void fn_80447218(register char *self, register void *m, register int a, register int b, register int c, register float *min, register float *max)
{
    float v[4];

    __6Vector(v);
    if (a)
        v[0] = fn_8042FB28(self + 0x10)[0];
    else
        v[0] = fn_8042FB28(self)[0];
    if (b)
        v[1] = fn_8042FB28(self + 0x10)[1];
    else
        v[1] = fn_8042FB28(self)[1];
    if (c)
        v[2] = fn_8042FB28(self + 0x10)[2];
    else
        v[2] = fn_8042FB28(self)[2];
    fn_80436100(v, m);
    if (v[2] < *min)
        *min = v[2];
    if (v[2] > *max)
        *max = v[2];
}

int fn_8044734C(register char *self)
{
    return *(int *)(self + 0x2B0);
}
