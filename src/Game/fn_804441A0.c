// Small methods of the handle-class family after fn_804440B0; class names and layouts are guesses.

extern char lbl_804F4C80[];
extern const float lbl_8048AAA4[]; // another unit's .rodata pool
extern const float lbl_8048A830[]; // 0.0f, in another unit's .rodata pool

extern void fn_8042A514(void *self, void *name);
extern void fn_80428FA8(void *v, float x, float y, float z);
extern void fn_800ACA34(void *self, int a);
extern void fn_804443E8(void *self, int a);
extern int fn_800B0C58(void *p);
extern void *fn_800B14A0(void *p);
extern int fn_80085E8C(void *p);
extern int fn_80444544(char *p);
extern int fn_80426AB0(void *g);
extern int fn_80444CA4(char *p);
extern char *fn_80430050(void *p);
extern void fn_80435FB4(void *p) __asm__("__7Segment");
extern int lbl_8066B664;
extern char lbl_8052F060[];
extern char lbl_80552110[]; // G

typedef struct GameState
{
    char pad[0x640];
    int field640;
} GameState;

void fn_804441A0(register char *self, register void *name)
{
    *(char **)(self + 4) = lbl_804F4C80;
    fn_8042A514(self, name);
}

int fn_804441EC(register char *self)
{
    return *(int *)(self + 0x14);
}

void fn_80444218(register char *self, register int a)
{
    ((void (*)(void *, int))(*(void **)(self + 0x10)))(*(char **)(self + 8) + *(short *)(self + 0xC), a);
    return;
}

void fn_8044427C(register void *self, register int a)
{
    fn_804443E8(self, a);
}

float fn_804442BC(register char *self, register float x)
{
    return *(float *)(self + 0x28) / x;
}

void fn_804442F0(register char *self, register float s)
{
    fn_80428FA8(self + 0x20, s, s, s);
    if (s != lbl_8048A830[0])
        *(unsigned int *)(self + 4) |= 0x800;
    else
        *(unsigned int *)(self + 4) &= ~0x800;
}

int fn_80444370(register char *self, register char slot)
{
    if (*(int *)(self + 0xE8) != -1)
        return slot == *(int *)(self + 0xE8);
    if ((1 << slot) & *(unsigned int *)(self + 0x40))
        return 0;
    return 1;
}

void fn_804443E8(register void *self, register int a)
{
    fn_800ACA34(self, a);
}

float fn_80444428(register char *self)
{
    return *(float *)(self + 0x2C);
}

int fn_80444454(register void *p)
{
    if (lbl_8066B664 == 0)
        return 0;
    if (!fn_800B0C58(p) || !fn_80085E8C(fn_800B14A0(p)))
        return 0;
    if (fn_80444544(lbl_8052F060))
        return 1;
    if (fn_80426AB0(lbl_80552110)) {
        return ((GameState *)lbl_80552110)->field640 != -1;
    } else {
        return 1;
    }
}

int fn_80444544(register char *self)
{
    return *(int *)(self + 0x3D0);
}

int fn_80444570(register char *self)
{
    return *(unsigned short *)(self + 4) & 0x10;
}

int fn_804445A4(register char *self)
{
    return *(unsigned short *)(self + 4) & 0x200;
}

int fn_804445D8(register char *self)
{
    return *(unsigned short *)(self + 4) & 0x400;
}

char *fn_8044460C(register char *self)
{
    return self + 0x10;
}

void fn_80444638(register char *self, register int on)
{
    if (on)
        *(unsigned short *)(self + 4) |= 0x1000;
    else
        *(unsigned short *)(self + 4) &= ~0x1000;
}

char *fn_80444688(register char *self)
{
    return self + 0x10;
}

void fn_804446B4(register char *self, register void *p)
{
    if (p)
        *(short *)(self + 0x20) = fn_80444CA4(p);
    else
        *(short *)(self + 0x20) = -1;
}

int fn_80444710(register char *self)
{
    return *(unsigned char *)(self + 0x22);
}

int fn_80444740(register char *self)
{
    return *(unsigned char *)(self + 0x2A);
}

char *fn_80444770(register char *self, register int index)
{
    return *(char **)(fn_80430050(lbl_8052F060) + 0x158) + (*(unsigned short *)(self + 0x28) + index) * 0x30;
}

int fn_804447D4(register char *self)
{
    return *(unsigned short *)(self + 0x2C) & 0x70;
}

int fn_80444808(register char *self)
{
    return *(unsigned short *)(self + 0x2C) & 0x80;
}

int fn_8044483C(register char *self)
{
    return *(unsigned short *)(self + 0x2C) & 0x1000;
}

void fn_80444870(register char *self, register int on)
{
    if (on)
        *(unsigned short *)(self + 0x2C) |= 0x400;
    else
        *(unsigned short *)(self + 0x2C) &= ~0x400;
}

void fn_804448C0(register char *self)
{
    *(int *)self = 0;
    *(short *)(self + 0x44) = 0;
    *(int *)(self + 0x50) = 0;
    *(float *)(self + 0x48) = lbl_8048AAA4[0];
}

char *fn_80444904(register char *self, register char *owner)
{
    register char *entry;
    if (owner)
        entry = *(unsigned short *)self * 0x60 + *(char **)(owner + 0x154);
    else
        entry = *(unsigned short *)self * 0x60 + *(char **)(fn_80430050(lbl_8052F060) + 0x154);
    return entry;
}

char *fn_80444984(register char *self, register char *owner)
{
    register char *entry;
    if (owner)
        entry = *(unsigned short *)(self + 2) * 0x60 + *(char **)(owner + 0x154);
    else
        entry = *(unsigned short *)(self + 2) * 0x60 + *(char **)(fn_80430050(lbl_8052F060) + 0x154);
    return entry;
}

char *fn_80444A04(register char *self, register char *owner)
{
    return fn_80444688(fn_80444904(self, owner));
}

extern int fn_80444D6C(char *self);
extern int fn_80444CD0(char *self);
extern int fn_80444D04(char *self);
extern int fn_80444D38(char *self);
extern int fn_80444DE0(char *self);
extern int fn_80444DA0(char *self);
extern int fn_80444E48(char *self);
extern int fn_80444E7C(char *self);
extern int fn_80444E14(char *self);

int fn_80444A5C(register char *self, register int mask)
{
    if (!(mask & 0x2000000) && fn_80444D6C(self))
        return 0;
    if ((mask & 0x40000) && fn_80444570(self))
        return 0;
    if ((mask & 0x100000) && fn_80444CD0(self))
        return 0;
    if (!(mask & 0x200000) && fn_80444D04(self))
        return 0;
    if (!(mask & 0x400000) && fn_804445A4(self))
        return 0;
    if (!(mask & 0x800000) && fn_804445D8(self))
        return 0;
    if (!(mask & 0x1000000) && fn_80444D38(self))
        return 0;
    return 1;
}

int fn_80444BB0(register char *self, register int mask)
{
    if (fn_80444DE0(self))
        return 0;
    if (fn_80444DA0(self))
        return 1;
    if (fn_80444808(self))
    {
        if (!fn_80444E48(self))
            return 1;
        if (!(mask & 0x80000) && fn_80444E7C(self))
            return 1;
    }
    if (fn_80444E14(self) && (mask & 0x200000))
        return 1;
    return 0;
}

int fn_80444CA4(register char *self)
{
    return *(int *)(self + 8);
}

int fn_80444CD0(register char *self)
{
    return (unsigned short)(*(unsigned short *)(self + 4) & 0x80);
}

int fn_80444D04(register char *self)
{
    return (unsigned short)(*(unsigned short *)(self + 4) & 0x100);
}

int fn_80444D38(register char *self)
{
    return (unsigned short)(*(unsigned short *)(self + 4) & 0x800);
}

int fn_80444D6C(register char *self)
{
    return (unsigned short)(*(unsigned short *)(self + 4) & 0x1000);
}

int fn_80444DA0(register char *self)
{
    return !(unsigned short)(*(unsigned short *)(self + 0x2C) & 0x3FF0);
}

int fn_80444DE0(register char *self)
{
    return (unsigned short)(*(unsigned short *)(self + 0x2C) & 0x400);
}

int fn_80444E14(register char *self)
{
    return (unsigned short)(*(unsigned short *)(self + 0x2C) & 0x2000);
}

int fn_80444E48(register char *self)
{
    return (unsigned short)(*(unsigned short *)(self + 0x2C) & 0x4);
}

int fn_80444E7C(register char *self)
{
    register int result = 0;
    if (*(unsigned short *)(self + 0x24) != 0xFFFF || *(unsigned short *)(self + 0x26) != 0xFFFF)
        result = 1;
    return result;
}

void fn_80444EE0(register void *self, register int a)
{
    fn_8044427C(self, a);
}

extern void fn_8038C0C0(void *self, int a, int b, int c, float f, int d, int e, int g, int h, int flag);

void fn_80444F20(register char *self, register int a, register int b, register int c, register float f, register int d, register int e, register int g, register int h, register unsigned char flag)
{
    fn_8038C0C0(self + 0x610, a, b, c, f, d, e, g, h, flag);
}

extern void fn_8042DC84(void *self, int a);
extern void fn_801B6768(void *self, int a);
extern void fn_80445590(float *m, float *angles);

void fn_80444FB4(register char *self, register int a)
{
    fn_8042DC84(self + 0x20, a);
    *(int *)(self + 4) |= 0x800;
}

char *fn_80445004(register char *self)
{
    return (*(int *)(self + 4) & 0x800) ? self + 0x20 : 0;
}

void fn_80445048(register char *self)
{
    *(int *)(self + 0x40) = 0xD00;
    *(int *)(self + 0xE8) = -1;
}

void fn_80445078(register void *self, register int a)
{
    fn_8044427C(self, a);
}

void fn_804450B8(register void *self, register int a)
{
    fn_804443E8(self, a);
}

void fn_804450F8(register char *self, register int a)
{
    fn_801B6768(self + 0x324, a);
}

void fn_8044513C(register void *self, register int a)
{
    fn_80445590((float *)self, (float *)a);
}

#define SWAP32(i) p[i] = (p[i] >> 24) | ((p[i] >> 8) & 0xFF00) | ((p[i] & 0xFF00) << 8) | (p[i] << 24)

void fn_8044517C(register unsigned int *p)
{
    SWAP32(0);
    SWAP32(1);
    SWAP32(2);
    SWAP32(3);
    SWAP32(4);
    SWAP32(5);
    SWAP32(6);
    SWAP32(7);
    SWAP32(8);
    SWAP32(9);
    SWAP32(10);
    SWAP32(11);
    SWAP32(12);
    SWAP32(13);
    SWAP32(14);
    SWAP32(15);
}

int fn_8044551C(register char *self)
{
    return *(int *)(self + 4) & 0x400;
}

extern void __6Vector(void *v);

char *fn_8044554C(register char *self)
{
    __6Vector(self + 0x30);
    return self;
}

extern const double lbl_8048B678[]; // degrees to radians
extern const float lbl_8048B680[]; // 0.0f
extern const float lbl_8048B684[]; // 1.0f
extern double sin(double x);
extern double cos(double x);

// Builds a 4x4 rotation matrix from the three angles in degrees.
void fn_80445590(register float *m, register float *angles)
{
    float ca, sa, cc, sc, cb, sb, t0, t1, t2, t3;
    sa = sin(angles[0] * lbl_8048B678[0]);
    ca = cos(angles[0] * lbl_8048B678[0]);
    sc = sin(angles[2] * lbl_8048B678[0]);
    cc = cos(angles[2] * lbl_8048B678[0]);
    sb = sin(angles[1] * lbl_8048B678[0]);
    cb = cos(angles[1] * lbl_8048B678[0]);
    t0 = sa * sc;
    t1 = sa * cc;
    t2 = ca * sc;
    t3 = ca * cc;
    m[0] = cb * cc;
    m[1] = cb * sc;
    m[2] = -sb;
    m[3] = lbl_8048B680[0];
    m[4] = sb * t1 - t2;
    m[5] = sb * t0 + t3;
    m[6] = cb * sa;
    m[7] = lbl_8048B680[0];
    m[8] = sb * t3 + t0;
    m[9] = sb * t2 - t1;
    m[10] = ca * cb;
    m[11] = lbl_8048B680[0];
    m[12] = lbl_8048B680[0];
    m[13] = lbl_8048B680[0];
    m[14] = lbl_8048B680[0];
    m[15] = lbl_8048B684[0];
}

extern int lbl_8066B9D0;
extern int fn_8043798C(void *p);
extern void fn_804426D4(void *p);
extern void fn_80442700(void *p);

void fn_804457F4(register void *self)
{
    if (++lbl_8066B9D0 == 0)
        lbl_8066B9D0 = 1;
}

void fn_80445834(register char *self)
{
    if (fn_8043798C(self))
        *(unsigned int *)self |= 8;
    else
        *(unsigned int *)self &= ~8;
}

void fn_80445894(register char *self)
{
    if (*(unsigned int *)self & 8)
        fn_804426D4(self);
    else
        fn_80442700(self);
}

void fn_804458E8(register void *self, register int a)
{
    fn_8044427C(self, a);
}

void fn_80445928(register float *dst, register float *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
}

void fn_8044596C(register float *dst, register float *a, register float *b, register float t)
{
    dst[0] = a[0] + (b[0] - a[0]) * t;
    dst[1] = a[1] + (b[1] - a[1]) * t;
    dst[2] = a[2] + (b[2] - a[2]) * t;
    dst[3] = a[3] + (b[3] - a[3]) * t;
}

char *fn_80445A08(register char *self)
{
    return self + 0x10;
}

int fn_80445A34(register char *self)
{
    return *(int *)(self + 0xC);
}

void fn_80445A60(register char *self, register int a)
{
    *(int *)(self + 0xC) = a;
}

void fn_80445A88(register char *self, register int a)
{
    if (a)
        *(unsigned int *)self &= ~4;
    else
        *(unsigned int *)self |= 4;
}

int fn_80445AD0(register char *self)
{
    return ((*(unsigned int *)self >> 2) ^ 1) & 1;
}

typedef struct Entry
{
    char pad[8];
    int v[7];
} Entry; // 0x24 bytes, indexed through +0x24 of the owner

void *fn_80445B08(register void *self)
{
    return self;
}

char *fn_80445B30(register char *self)
{
    return self + 0x40;
}

int fn_80445B5C(register void *self)
{
    return 0;
}

void fn_80445B84(register void *self, register int a)
{
}

int fn_80445BA8(register void *self)
{
    return 1;
}

void fn_80445BD0(register char *self, register int a)
{
    *(int *)(self + 0x64) = a;
}

void fn_80445BF8(register char *self, register float *v)
{
    *(float *)(self + 0x30) = *(float *)(self + 0x30) + v[0];
    *(float *)(self + 0x34) = *(float *)(self + 0x34) + v[1];
    *(float *)(self + 0x38) = *(float *)(self + 0x38) + v[2];
}

int fn_80445C4C(register char *self, register int a, register int b)
{
    return (*(Entry **)(self + 0x24))[a].v[b];
}

void *fn_80445C98(register char *self)
{
    fn_80435FB4(self + 0x10);
    return self;
}

void fn_80445CDC(register int *self, register int a)
{
    *self = a;
}

void fn_80445D04(register void *self, register int a, register int b)
{
}
