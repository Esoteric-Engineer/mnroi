// Flag and float accessors on objects of unknown class (see docs/versus.md section 5, row 8).

typedef struct Inner
{
    float pad[4];
    float x, y, z; // +0x10
} Inner;

extern int fn_80435340(int handle);
extern int fn_802E85B4(void *self);

float fn_80434E0C(register char *self)
{
    return *(float *)(self + 0x4);
}

int fn_80434E38(register char *self)
{
    return fn_80435340(*(int *)(self + 0x30));
}

void *fn_80434E7C(register char *self)
{
    return self + 0x34;
}

void *fn_80434EA8(register void *self)
{
    return self;
}

int fn_80434ED0(register void *self)
{
    register int r = fn_802E85B4(self);
    return r;
}

unsigned int fn_80434F14(register char *self)
{
    return ((*(unsigned int *)(self + 0x4) >> 9) ^ 1) & 1;
}

unsigned int fn_80434F4C(register char *self)
{
    return *(unsigned int *)(self + 0x4) & 0x1;
}

unsigned int fn_80434F7C(register char *self)
{
    return *(unsigned int *)(self + 0x4) & 0x40;
}

unsigned int fn_80434FAC(register char *self)
{
    return *(unsigned int *)(self + 0x4) & 0x80;
}

unsigned int fn_80434FDC(register char *self)
{
    return *(unsigned int *)(self + 0x4) & 0x100;
}

unsigned int fn_8043500C(register char *self)
{
    return *(unsigned int *)(self + 0x4) & 0x10000;
}

int fn_8043503C(register void *self)
{
    return !fn_8043500C(self);
}

unsigned int fn_8043508C(register char *self)
{
    return *(unsigned int *)(self + 0x4) & 0x20000;
}

unsigned int fn_804350BC(register char *self)
{
    return *(unsigned int *)(self + 0x4) & 0x40000;
}

unsigned int fn_804350EC(register char *self)
{
    return *(unsigned int *)(self + 0x4) & 0x80000;
}

unsigned int fn_8043511C(register char *self)
{
    return *(unsigned int *)(self + 0x4) & 0x100000;
}

unsigned int fn_8043514C(register char *self)
{
    return *(unsigned int *)(self + 0x4) & 0x200000;
}

float fn_8043517C(register char *self)
{
    return (*(Inner **)(self + 0x2A0))->x;
}

float fn_804351AC(register char *self)
{
    return (*(Inner **)(self + 0x2A0))->y;
}

float fn_804351DC(register char *self)
{
    return (*(Inner **)(self + 0x2A0))->z;
}

float fn_8043520C(register char *self)
{
    return *(float *)(self + 0x90);
}
