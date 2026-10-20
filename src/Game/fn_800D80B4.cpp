// fn_800D875C is the per-frame step that picks the PLAYER clip and chases the target (fields 0xD2, 0xD4, 0xD, 0xE, 0x14);
// fn_800D7CDC enters the flight state (fields 0x65, 0x66, 0xC9); fn_800D80B4 steers the effect handle and drift value, fn_800D84BC moves the actor by the stick vector.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Handle {
    char d[0xC8];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17(float a, float b);
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55(); virtual void s56();
    virtual void s57();
};

struct Tgt : Ent {
    char d[0x194];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(Vector *v, int z);
};

struct Obj {
    char pad0[0x10];
    unsigned int flags; // +0x10
    char pad14[0x18 - 0x14];
    unsigned int f18;
    char pad1C[0xDC - 0x1C];
    float fDC;
    char padE0[0x3A0 - 0xE0];
    Handle *h; // +0x3A0
    char pad3A4[0x409 - 0x3A4];
    char b409;
    char b40a;
    char b40b;
    char b40c;
    int f410;
    char pad414[0x488 - 0x414];
    float f488;
    char pad48C[0x514 - 0x48C];
    float f514;
    char pad518[0x534 - 0x518];
    void *p534;
    char pad538[0x950 - 0x538];
    float f950;
};

struct Mdl {
    char pad0[0xB0];
    char *p; // +0xB0
};

extern char lbl_80593BE8[];

extern "C" {
PEnt *Entity_GetActor(void *self);
float fn_800B1884(Ent &actor, int id);
void *fn_800B1724(Ent &actor);
int fn_80085300(void *actor, void *node, float a, float b, float *out);
int fn_800CC60C(void *self);
void *fn_80085980(void *actor);
void *fn_804420AC(void *p);
void fn_8014BB4C(void *p, Vector *v);
void fn_80067050(Ent &actor, Vector *v);
int fn_800CC148(void *self, int id);
int fn_80133630();
Handle *fn_80393B28(Ent &actor, Handle *h);
void fn_80114D70(void *p, int v);
int fn_800664C0(Ent &actor);
float fn_80426A84(void *p);
float fn_800D9308(float a, float b, float c);
void fn_80065CB0(Ent &actor, Vector *v);
float fn_800CC1D4(void *self, int id, Vector *v);
int fn_800CC2E0(void *self);
int fn_800CC338(void *self);
Vector *fn_800B1750(Ent &actor);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_800B9D64(void *self, Vector *v, float f, int z);
void fn_800BEAC0(void *self, int v);
void fn_800C7BEC(void *self);
int fn_800CC76C(void *self);
void fn_800C8098(void *self);
Tgt *fn_800C9FD0(void *self);
Tgt *fn_80134870(void *a);
float fn_804290F8(void *a, void *b);
void fn_8005A828(Ent &actor, void *p);
void fn_800BE638(void *self);
int fn_800CC0BC(void *self, int id);
int fn_800E9AF8(void *self, float a, float b, float c, int d, int e);
int fn_80097CE8(Ent &actor, int a, int mode, float speed, void *set, float blend, float f);
void fn_800BD2D0(void *self, int handle);
void fn_800BD3A8(void *self, int handle);
void fn_800F1644(void *self);
void fn_80066604(Ent &actor);
void fn_800DDCB4(void *self, int a, int b);
Vector *fn_800B17A8(Ent &actor);
PEnt *fn_800CD9B0(void *self);
void fn_800CD514(void *self, int v);
void fn_800CD3F4(void *self, int v);
void fn_80065AF8(Ent &actor, int a, int b);
void fn_8009AEC8(Ent &actor, int v);
void fn_8006645C(Ent &actor, int a);
void fn_8006668C(Ent &actor, float v);
Mdl *fn_8009AD80(Ent &actor);
int fn_8044667C(void *axis, void *owner, float v, float w, int mode);
int fn_800CE204(void *self);
void fn_800C85C8(void *self, int a, int b);
void fn_800C9208(void *self);
int fn_800ACD20(Ent &actor, int id);
Handle *fn_80393D0C(Ent &actor, int id, int a, int b);
int fn_800B13D8(Ent &actor);
void *fn_80114950(int a, int id);
char *fn_8009AF80(Ent &actor);
void *fn_8009AE00(Ent &actor);
void *fn_8008FCEC(void *set, int a, int b, float f);
int fn_804470BC(void *self, void *a, void *b, float v, float w, int mode);
}

extern "C" int fn_800D7CDC(register Obj *self, int unused)
{
    int f0c = 0x21;
    PEnt &f10 = *fn_800CD9B0(self);
    self->f18 &= ~0x1000000;
    fn_800CD514(self, 1);
    fn_800CD3F4(self, 1);
    fn_80065AF8(*Entity_GetActor(self), 0, 0);
    fn_8009AEC8(*Entity_GetActor(self), 0);
    fn_8006645C(*Entity_GetActor(self), 0);
    self->flags = 0;
    fn_80097CE8(*Entity_GetActor(self), 4, 1, 30.0f, 0, 7.5f, -1.0f);
    self->f514 = fn_800B1884(*Entity_GetActor(self), 0xC9);
    fn_8006668C(*Entity_GetActor(self), 0.0f);
    self->f488 = 0.0f;
    fn_8044667C(fn_8009AD80(*Entity_GetActor(self))->p + 0x94, 0, 0.0f, 0.0f, 0);
    Vector v18;
    fn_80067050(*Entity_GetActor(self), &v18);
    self->fDC = v18.z;
    self->fDC = self->fDC >= -4.0f ? (self->fDC <= 16.0f ? self->fDC : 16.0f) : -4.0f;
    if (fn_800CE204(self))
        fn_800C85C8(self, 0, 0);
    fn_800C9208(self);
    self->h = fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0x65), 0xFF, 0xFF);
    if (self->h)
        self->h->s56();
    self->p534 = fn_80114950(fn_800B13D8(*Entity_GetActor(self)), 0x34);
    fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0x66), 0xFF, 0xFF);
    fn_804470BC(fn_8009AF80(*Entity_GetActor(self)) + 0x104, fn_8008FCEC(fn_8009AE00(*Entity_GetActor(self)), 0x132, 0, -1.0f),
                fn_8008FCEC(fn_8009AE00(*Entity_GetActor(self)), 0x133, 0, -1.0f), 0.0f, 0.0f, 0);
    return 1;
}

extern "C" int fn_800D80B4(register Obj *self)
{
    Vector v8;
    float f18 = 0.5f;
    Vector v20;
    float f30 = 0.0f;
    float f34 = -fn_800B1884(*Entity_GetActor(self), 0x28);
    float f38 = fn_800B1884(*Entity_GetActor(self), 0x27);
    float f3C = fn_800B1884(*Entity_GetActor(self), 0x2A);
    float f40;
    int f44 = fn_80085300(Entity_GetActor(self), fn_800B1724(*Entity_GetActor(self)), 0.7f, 10.0f, &f40);
    if (f44) {
        self->f950 = f40;
    } else {
        if (fn_800CC60C(self)) {
            Vector v48;
            fn_8014BB4C(fn_804420AC(fn_80085980(Entity_GetActor(self))), &v48);
        }
        self->f950 = -1.0f;
    }
    fn_80067050(*Entity_GetActor(self), &v20);
    float f58 = 0.0f;
    if (fn_800CC148(self, 9) || (fn_800CC60C(self) && fn_80133630())) {
        if (fn_800CC148(self, 0x10)) {
            f30 = f38;
            f58 = 1.0f;
        } else {
            f30 = 0.0f;
            f58 = 0.5f;
        }
    } else {
        f30 = f34;
        f58 = 0.0f;
    }
    self->h = fn_80393B28(*Entity_GetActor(self), self->h);
    if (self->h) {
        self->h->s17(f58, -1.0f);
        fn_80114D70(self->p534, (int)(f58 * 1000.0f));
    }
    if (fn_800664C0(*Entity_GetActor(self)))
        f30 = 0.0f;
    self->fDC = fn_800D9308(self->fDC, f30, fn_80426A84(lbl_80593BE8) * fn_800B1884(*Entity_GetActor(self), 0x40));
    self->fDC = self->fDC >= -4.0f ? (self->fDC <= 16.0f ? self->fDC : 16.0f) : -4.0f;
    v20.z = self->fDC;
    if (!fn_800664C0(*Entity_GetActor(self)))
        fn_80065CB0(*Entity_GetActor(self), &v20);
    return 0;
}

extern "C" int fn_800D84BC(register Obj *self)
{
    Vector v8;
    float f18 = fn_800CC1D4(self, 0, &v8);
    Vector v20;
    int f30;
    float f34 = fn_800B1884(*Entity_GetActor(self), 0xC9);
    f30 = fn_800D80B4(self);
    if (fn_800CC2E0(self))
        return f30;
    fn_80067050(*Entity_GetActor(self), &v20);
    float f38 = v20.z;
    Vector v40;
    Vector v50;
    if (fn_800CC338(self))
        f18 = 0.0f;
    if (f18 < 0.1f)
        f18 = 0.0f;
    f18 = f18 >= 0.0f ? (f18 <= 1.0f ? f18 : 1.0f) : 0.0f;
    float f60 = fn_8042EBF4(&v8, fn_800B1750(*Entity_GetActor(self)));
    f60 = f60 > 0.0f ? f60 : 0.0f;
    v40.x = v8.x * f34 * f60 * f18;
    v40.y = v8.y * f34 * f60 * f18;
    v40.z = v20.z;
    if (f60 < 1.0f)
        fn_800B9D64(self, &v8, fn_800B1884(*Entity_GetActor(self), 0x42), 0);
    if (!fn_800664C0(*Entity_GetActor(self)))
        fn_80065CB0(*Entity_GetActor(self), &v40);
    return f30;
}

extern "C" void fn_800D875C(register Obj *self)
{
    int f8;
    int fc = -1;
    fn_800BEAC0(self, 0);
    float f10 = fn_800B1884(*Entity_GetActor(self), 0x29) * fn_80426A84(lbl_80593BE8);
    fn_800C7BEC(self);
    if (fn_800CC76C(self)) {
        fn_800C8098(self);
        return;
    }
    f8 = fn_800D84BC(self);
    Tgt *f14 = fn_800C9FD0(self);
    if (!f14)
        f14 = fn_80134870(fn_80085980(Entity_GetActor(self)));
    float f18;
    int f1c;
    if (fn_800CC2E0(self)) {
        if (f14) {
            f18 = fn_804290F8(fn_800B1724(*f14), fn_800B1724(*Entity_GetActor(self)));
            if (f18 >= fn_800B1884(*Entity_GetActor(self), 0xD2))
                fn_8005A828(*Entity_GetActor(self), fn_800B1724(*f14));
        }
        fn_800BE638(self);
        return;
    }
    if (fn_800CC0BC(self, 1)) {
        f1c = fn_800E9AF8(self, fn_800B1884(*Entity_GetActor(self), 0xE), fn_800B1884(*Entity_GetActor(self), 0xD),
                          fn_800B1884(*Entity_GetActor(self), 0x14), 0, 0);
        fc = fn_80097CE8(*Entity_GetActor(self), 0x63, 0, 30.0f, 0, 7.5f, -1.0f);
        self->b40a = 0;
        self->b409 = 0;
        self->b40b = 1;
        self->b40c = 0x15;
        self->f410 = 0xCA;
        if (fc > 0) {
            fn_800BD2D0(self, fc);
            fn_800BD3A8(self, fc);
            self->h = fn_80393B28(*Entity_GetActor(self), self->h);
            if (self->h) {
                self->h->s54();
                self->h = 0;
            }
        } else {
            fn_800F1644(self);
        }
        return;
    }
    if (fn_800CC0BC(self, 2)) {
        Vector v20;
        f1c = 0x27;
        if (f14) {
            f14->s5(&v20, 0);
            fn_8005A828(*Entity_GetActor(self), &v20);
        }
        fn_80066604(*Entity_GetActor(self));
        fn_800DDCB4(self, f1c, 0);
    }
    f18 = 3.4028235e38f;
    if (f14)
        f18 = fn_804290F8(fn_800B1724(*f14), fn_800B1724(*Entity_GetActor(self)));
    if (f18 >= fn_800B1884(*Entity_GetActor(self), 0xD2)) {
        if (f18 <= fn_800B1884(*Entity_GetActor(self), 0xD4)) {
            if (fn_800CC148(self, 0xB)) {
                f1c = 4;
                Vector v20;
                float f30 = fn_800CC1D4(self, 0, &v20);
                float f34 = fn_8042EBF4(&v20, fn_800B17A8(*Entity_GetActor(self)));
                if (f34 < 0.0f)
                    f1c = 0x16;
                else
                    f1c = 0x17;
                unsigned int f38 = fn_80097CE8(*Entity_GetActor(self), f1c, 0, 30.0f, 0, 7.5f, -1.0f);
                fn_800BD2D0(self, f38);
                self->flags |= 1;
            }
        }
    }
}
