// Prop file: spawn and effect starts, the PROP_*/CONTAINER_* property handler, accessors (docs/story.md row 14).
// Owns .rodata 0x8048B2B0-0x8048B2F0; the debris-header tail after it stays unclaimed.

inline int sn_return_decl(int a) { return a; }

struct Actor {
    char pad0[0x2C];
    unsigned int flags; // +0x2C
    char pad30[0x170];
    int f1A0; // +0x1A0
    int f1A4; // +0x1A4
    char pad1A8[0xE8];
    int f290; // +0x290
    unsigned int f294; // +0x294
    float f298; // +0x298
    float f29C; // +0x29C
    float f2A0; // +0x2A0
    float f2A4; // +0x2A4
    float f2A8; // +0x2A8
    int f2AC; // +0x2AC
    char pad2B0[0x8];
    unsigned int f2B8; // +0x2B8
    char pad2BC[0x8];
    void *f2C4; // +0x2C4
    char pad2C8[0x8];
    int f2D0; // +0x2D0
    int f2D4; // +0x2D4
    int f2D8; // +0x2D8
};

struct Prop {
    unsigned int id;
    union {
        int i;
        float f;
        char s[0x20];
    } v;
};

extern int lbl_8066B9FC;
extern char lbl_805724F0[];

extern "C" {
int fn_800A3F14(Actor *self);
int fn_800A3F74(Actor *self);
int fn_800A3FA4(Actor *self);
unsigned int fn_8009ABC0(void *self);
int fn_8009ABEC(void *self);
int fn_8010CDCC(void *self, int event, void *target, int a3, int a4, int a5, int a6);
int fn_800B21A4(void *self);
void fn_80098710(void *self, void *other, float f, void *a, void *v);
int fn_80097CE8(void *self, int motion, int a, float speed, int c, float blend, float e);
void fn_8009A778(void *self);
int fn_800B10D8(void *self);
void fn_800AFFD4(void *self, int on);
void fn_800AE398(void *self, int a, int b);
void fn_80428EEC(void *x, int on);
void fn_8007E9F4(void *self, void *other, int a, int b, float f);

int fn_800A3588(register Actor *self, void *other, float f, void *a, void *v, float g)
{
    int saved = lbl_8066B9FC;

    if (fn_800A3F14(self)) {
        return 0;
    }

    self->f294 |= 1;
    fn_8010CDCC(self, 1, 0, fn_8009ABC0(self), 10, 0, 0);
    self->flags &= ~0x40;

    if (fn_800B21A4(self)) {
        fn_80098710(self, other, g, a, v);
    }

    if (fn_800A3F74(self)) {
        fn_80097CE8(self, 0xC0, 0, 30.0f, 0, 7.5f, -1.0f);
    } else if (!(self->f1A0 == 0 && self->f1A4 == 0)) {
        if (self->f294 & 0x100) {
            fn_8009A778(self);
            self->f1A0 = 0;
            self->f1A4 = 0;
        } else if (fn_800B10D8(self)) {
            fn_8009A778(self);
            fn_800AFFD4(self, 1);
        } else {
            fn_800AE398(self, 0, 0);
        }
    } else if (fn_800A3FA4(self)) {
        if (fn_800B10D8(self)) {
            fn_8009A778(self);
            fn_800AFFD4(self, 1);
        } else {
            fn_800AE398(self, 0, 0);
        }
    } else {
        fn_80097CE8(self, 0xC0, 0, 30.0f, 0, 7.5f, -1.0f);
    }

    if (fn_8009ABEC(self)) {
        fn_80428EEC(lbl_805724F0, fn_8009ABEC(self));
    }

    if (!fn_800A3F74(self)) {
        fn_8007E9F4(self, other, 0, 0, f);
    }

    return 1;
}

void fn_8003FE44(void *self, int a, int b);
void fn_80041FBC(int h, int other, float f, void *a, void *b);
int fn_800B13D8(void *self);
void *fn_803A20D8(char *tbl, int a, void *self, int b, int c, int d, int e, float f);
void fn_80393938(void *self, void *c, int flag);
int fn_8009AC94(void *self);
void *fn_800ACFA8(int handle);
}

extern char lbl_8064AA80[];

class EffectV {
public:
    char data[0xC8];
    virtual void v0(int);
    virtual void v1(int);
    virtual void v2(int);
    virtual void v3(int);
    virtual void v4(int);
    virtual void v5(int);
    virtual void v6(int);
    virtual void v7(int);
    virtual void v8(int);
    virtual void v9(int);
    virtual void v10(int);
    virtual void v11(int);
    virtual void v12(int);
    virtual void v13(int);
    virtual void v14(int);
    virtual void v15(int);
    virtual void v16(int);
    virtual void v17(int);
    virtual void v18(int);
    virtual void v19(int);
    virtual void v20(int);
    virtual void v21(int);
    virtual void v22(int);
    virtual void v23(int);
    virtual void v24(int);
    virtual void v25(int);
    virtual void v26(int);
    virtual void v27(int);
    virtual void v28(int);
    virtual void v29(int);
    virtual void v30(int);
    virtual void v31(int);
    virtual void v32(int);
    virtual void v33(int);
    virtual void v34(int);
    virtual void v35(int);
    virtual void v36(int);
    virtual void v37(int);
    virtual void v38(int);
    virtual void v39(int);
    virtual void v40(int);
    virtual void v41(int);
};

extern "C" int fn_800A3810(register Actor *self, int other, float f, void *a, void *b, int c)
{
    if (fn_800A3F14(self)) {
        return 0;
    }

    fn_8003FE44(self, 0, 0);
    if (c) {
        fn_80041FBC(fn_800B13D8(self), other, f, a, b);
    }

    if (self->f1A4) {
        void *fx = fn_803A20D8(lbl_8064AA80, 0, self, 0, self->f1A4, 0, 0, 0.0f);
        if (fx) {
            fn_80393938(self, fx, 1);
        }
        int h = fn_8009AC94(self);
        if (!h) {
            h = fn_800B13D8(self);
        }
        ((EffectV *)fx)->v41(h);
    }

    if (fn_8009ABEC(self)) {
        fn_80428EEC(lbl_805724F0, fn_8009ABEC(self));
    }

    if (!fn_800A3F74(self)) {
        fn_8007E9F4(self, fn_800ACFA8(other), 0, 0, f);
    }

    fn_8009A778(self);
    fn_800AFFD4(self, 1);
    return 1;
}

extern "C" {
int fn_803A1AC4(char *tbl, char *name);
void *fn_801A1A84(char *name);
}

// Applies one PROP_* or CONTAINER_* property (docs/characters.md section 3, kinds 11 and 13).
extern "C" int fn_800A39F4(register Actor *self, Prop *prop, int arg)
{
    switch (prop->id) {
    case 0x64:
        self->f290 = prop->v.i;
        break;
    case 0x65:
        self->f2B8 = prop->v.i;
        self->f2B8 = self->f2B8 > 6 ? 6 : self->f2B8;
        break;
    case 0x66:
        self->f2A8 = prop->v.f;
        break;
    case 0x68:
        self->f29C = self->f2A0 = self->f298 = (float)prop->v.i;
        if (self->f298 > 0.0f) {
            self->f294 |= 2;
        }
        break;
    case 0x69:
        self->f294 |= prop->v.i;
        break;
    case 0x71:
        self->f2D4 = fn_803A1AC4(lbl_8064AA80, prop->v.s);
        break;
    case 0x72:
        self->f2D8 = fn_803A1AC4(lbl_8064AA80, prop->v.s);
        break;
    case 0x73:
        self->f2C4 = fn_801A1A84(prop->v.s);
        break;
    case 0x77:
        self->f2A4 = (float)prop->v.i;
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_800A3C14(register void *self)
{
}

extern "C" {
void fn_8009A570(void *self, int a);
int fn_800A4130(Actor *self);
}

extern "C" void fn_800A3C3C(register Actor *self, int a)
{
    fn_8009A570(self, a);
    if (fn_800A4130(self) && self->f2A4 > 0.0f && self->f29C != self->f2A4) {
        self->f298 = self->f29C = self->f2A4;
    }
}

extern "C" void fn_800A3CC8(register void *self, void *a, int b)
{
}

extern "C" {
void fn_800B087C(void *self, void *a, int b);
int fn_800A3FD4(Actor *self);
void *fn_8043E450(void *self, int second);
void fn_8009A088(void *self, void *pair, int second);
int fn_800A42E0(Actor *self);
int fn_800A4340(Actor *self);
int fn_800A42B0(Actor *self);
void fn_80098D30(void *self, void *t, int b, void *c, int d, int e);
float fn_80099228(void *self, void *t, int b, void *c);
void fn_800A2F94(void *a, void *b, int c, int d, float f, void *g, void *h, float k, int l);
}

extern "C" void fn_800A3CF8(register Actor *self, void *a, int b)
{
    void *c;
    float f;

    fn_800B087C(self, a, b);
    if (!fn_800A3FD4(self)) {
        return;
    }
    c = fn_8043E450(a, b);
    fn_8009A088(self, a, b);
    if (!fn_800A42E0(self) || !fn_800A4340(self)) {
        fn_80098D30(self, a, b, c, fn_800A42E0(self), fn_800A4340(self));
    }
    if (fn_800A42B0(self)) {
        f = fn_80099228(self, a, b, c);
        if (f > 0.0f) {
            fn_800A2F94(self, 0, 7, 0, f, 0, 0, 0.0f, 0);
        }
    }
}

__asm__(".section .rodata\n\t.float 1.0\n\t.float 0.0\n\t.float 1.0\n\t.float 1.0\n\t.float 0.0\n\t.text"); // 0x8048B2D4-0x8048B2E8: orphan words no code loads

inline int sn_return_decl_2(int a) { return a; }

extern "C" int fn_800A3E54(register Actor *self)
{
    return self->f290;
}

extern "C" void fn_800A3E80(register Actor *self, register int bits)
{
    self->f290 |= bits;
}

extern "C" void fn_800A3EB0(register Actor *self, register int bits)
{
    self->f290 &= ~bits;
}

extern "C" int fn_800A3EE4(register Actor *self)
{
    return self->f294 & 0x2;
}

extern "C" int fn_800A3F14(register Actor *self)
{
    return self->f294 & 0x1;
}

extern "C" int fn_800A3F44(register Actor *self)
{
    return self->f294 & 0x10;
}

extern "C" int fn_800A3F74(register Actor *self)
{
    return self->f294 & 0x80;
}

extern "C" int fn_800A3FA4(register Actor *self)
{
    return self->f294 & 0x200;
}

extern "C" int fn_800A3FD4(register Actor *self)
{
    return fn_800A42B0(self) || !fn_800A42E0(self) || !fn_800A4340(self);
}

extern "C" float fn_800A4054(register Actor *self)
{
    return self->f298;
}

extern "C" float fn_800A4080(register Actor *self)
{
    return self->f29C;
}

extern "C" float fn_800A40AC(register Actor *self)
{
    if (self->f29C == 0.0f) {
        return 0.0f;
    }
    return self->f298 / self->f29C;
}

extern "C" int fn_800A4100(register Actor *self)
{
    return self->f290 & 0x8000;
}

extern "C" int fn_800A4130(register Actor *self)
{
    return self->f290 & 0x80000;
}

extern "C" int fn_800A4160(register Actor *self)
{
    return self->f290 & 0x100;
}

extern "C" int fn_800A4190(register Actor *self)
{
    return self->f290 & 0x2000;
}

extern "C" int fn_800A41C0(register Actor *self)
{
    return self->f290 & 0x200;
}

extern "C" int fn_800A41F0(register Actor *self)
{
    return self->f290 & 0x400;
}

extern "C" int fn_800A4220(register Actor *self)
{
    return self->f290 & 0x800;
}

extern "C" int fn_800A4250(register Actor *self)
{
    return self->f290 & 0x1000;
}

extern "C" int fn_800A4280(register Actor *self)
{
    return self->f290 & 0x10000;
}

extern "C" int fn_800A42B0(register Actor *self)
{
    return self->f290 & 0x800000;
}

extern "C" int fn_800A42E0(register Actor *self)
{
    return self->f290 & 0x1000000;
}

extern "C" int fn_800A4310(register Actor *self)
{
    return self->f290 & 0x400000;
}

extern "C" int fn_800A4340(register Actor *self)
{
    return self->f290 & 0x2000000;
}

extern "C" int fn_800A4370(register Actor *self)
{
    return self->f290 & 0x2;
}

extern "C" int fn_800A4408(Actor *self);
extern "C" int fn_800A4438(Actor *self);

extern "C" int fn_800A43A0(register Actor *self)
{
    return !fn_800A4408(self) && !fn_800A4438(self);
}

extern "C" int fn_800A4408(register Actor *self)
{
    return self->f290 & 0x4;
}

extern "C" int fn_800A4438(register Actor *self)
{
    return self->f290 & 0x8;
}

extern "C" int fn_800A4468(register Actor *self)
{
    return fn_800A4438(self) ? 2 : fn_800A4408(self) != 0;
}

extern "C" int fn_800A44D8(register Actor *self)
{
    return self->f290 & 0x8000000;
}

extern "C" int fn_800A4508(register Actor *self)
{
    return self->f290 & 0x40000000;
}

extern "C" int fn_800A4538(register Actor *self)
{
    return self->f290 & 0x80000000;
}

extern "C" int fn_800A4568(register Actor *self)
{
    return self->f290 & 0x40;
}

extern "C" int fn_800A4598(register Actor *self)
{
    return self->f290 & 0x10000000;
}

extern "C" void *fn_800A45C8(register Actor *self)
{
    return self->f2C4;
}

extern "C" unsigned int fn_800A45F4(register Actor *self)
{
    return self->f2B8;
}

extern "C" float fn_800A4620(register Actor *self)
{
    return self->f2A8;
}

extern "C" int fn_800A464C(register Actor *self)
{
    return self->f2AC;
}

extern "C" void fn_800A4678(register Actor *self, register int v)
{
    self->f2AC = v;
}

extern "C" void fn_800A46A0(register Actor *self, register int on)
{
    if (on) {
        self->f294 |= 0x10;
    } else {
        self->f294 &= ~0x10;
    }
}

extern "C" int fn_800A46E8(register Actor *self)
{
    return self->f2D0;
}

extern "C" void fn_800A4714(register Actor *self, register int v)
{
    self->f2D0 = v;
}

__asm__(".section .rodata\n\t.float 1.2\n\t.text"); // 0x8048B2EC: pads the claim to 8; no code loads it
