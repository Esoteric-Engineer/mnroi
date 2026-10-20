// Hit on an actor (guess): fn_8009FF54 dispatches on the target's kind to fn_800A0488 (projectile: deflect, absorb or hand on to
// fn_8002FD50, PLAYER 0x81 + n, 0xBD), fn_800A0B48 or fn_8009E998. Type-ID use: docs/characters.md section 5.
// The unit owns .rodata 0x8048AF88-0x8048AFD8.

inline int sn_return_decl(int a) { return a; }

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Obj {
    char pad0[0x290];
    unsigned int flags; // +0x290
    char pad1[4];
    float f298;
};

struct Byte91 { // actor+0x91, returned by value
    signed char v;
    bool test() __asm__("fn_80436294");
};

struct Body {
    Byte91 byte91() __asm__("fn_80317960");
};

struct PBody : Body { // matching_notes 46
    int pad;
};

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Target {
    char pad0[0x198];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
    virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
    virtual void s55(); virtual void s56();
    virtual int s57(float a); // vtable +0x1D0
};

struct EObj {
    char d[0x3AC];
    int mb() __asm__("fn_800CC9D8");
    int kind() __asm__("fn_800CC6DC");
};

struct ESub : EObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36();
    virtual void play(int id, void *at, int flag, float speed, int a, int b, int c, int d); // vtable +0x130
};

extern void *lbl_8066C6C8; // the GLOBALS record
extern int lbl_8066F060;
extern char lbl_8064AA80[];

extern "C" {
ESub *fn_80085954(void *actor);
void *fn_800B1724(Ent &actor);
void *fn_800B1750(Ent &actor);
void fn_80429038(Vector *out, Vector *a, void *b);
void fn_8042F76C(Vector *v);
float fn_8042EBF4(void *a, Vector *b);
int fn_800B18EC(void *actor, int id);
float fn_800B1884(Ent &actor, int id);
void fn_800E673C(void *self, int a, int b, void *c, Vector *d, void *e, unsigned char flags, unsigned char f2);
void fn_800E8628(void *self, int v);
void fn_800E8508(void *self, int v);
void fn_800D98B0(void *actor, float a, float b, int c);
void fn_800D9408(void *actor, void *src, char *msg, int a, int b);
float fn_80433D20(void *record, int id, int slot);
void fn_80086818(void *actor, float f);
void fn_800D97D0(void *actor, void *a, void *b, float f);
void *fn_8009ACC0(void *p);
int fn_800B0C1C(void *c);
void *fn_800B14C8(void *c);
PEnt *fn_800B14C8P(void *c) __asm__("fn_800B14C8");
int fn_800CD21C(void *p);
int fn_8009B04C(void *actor);
int fn_800A0E94(void *p);
int fn_800CC82C(void *p);
void fn_8002FD50(void *a, void *b, int c, int d, float f, Vector *g, void *h, int i, int j, float k, int *l, int m, int n, int o);
void fn_80086A2C(void *p, float f);
void *fn_80085AF0(void *p);
void fn_80130F88(void *a, void *b);
void *memset(void *p, int c, unsigned int n);
int fn_800B0C58(void *a);
void *fn_800B14A0(void *a);
void *fn_800B1478(void *a);
void *fn_800B14F0(void *a);
void *fn_800B1568(void *a);
int fn_80085EEC(void *p);
int fn_80085EBC(void *p);
int fn_800B13D8(void *a);
int fn_80095608(void *p);
int fn_800B0F0C(void *a);
void fn_80099F7C(void *p, int a, int b);
int fn_800B0BEC(void *a);
int fn_800B2234(void *a);
int fn_8010CDCC(void *self, int event, void *target, int a3, int a4, int a5, int a6);
int fn_800A0E04(void *self);
int fn_800A0DD4(void *self);
int fn_800A0F84(void *self);
int fn_800A10A4(void *self);
void fn_8009F010(void *self, void *v);
void fn_800AE398(void *self, int a, int b);
void fn_8009FD04(void *self, void *a, Vector *c, void *d);
void fn_8009E998(void *self, void *p, int two, int e, float f1, Vector *c, void *d, float f2);
PBody *fn_800B24AC(void *a);
void *fn_80318EB4(PBody *p);
void fn_80434BA4(Vector *out, void *v);
void fn_8042FDBC(Vector *out, void *v, float f);
void fn_80435530(Vector *v, float f);
float fn_800B24D8(void *a);
void fn_80069254(void *a, Vector *c, void *d, float f, Vector *v, int flag);
void fn_800A2F94(void *a, void *b, int c, int d, float f, Vector *g, void *h, float k, int l);
void fn_800A140C(void *a, void *b, Vector *c, void *d, float f);
int fn_800664C0(void *a);
void fn_80066DC4(void *a, Vector *v, int b, int c, int d);
void fn_80066794(void *a, int v);
void fn_803A0B74(void *table, int a, int b, void *c, Vector *d, void *e);
int fn_800A0488(void *a0, void *a1, int a2, void *a3, Vector *a4, void *a5, float f6, int a7, int a8, float f9, int s0, int s1, int s2, int *s3);
void fn_800A09C0(void *self, void *a, Vector *c, void *d, float f2, int two, int f, int flag);
int fn_800A0B48(void *self, void *p, int type, void *x, Vector *c, void *d, float f1, int two, int e, float f2, int f, int g, int i);
}

extern "C" int fn_8009FF54(Obj *self, void *p, int type, int b, void *a, Vector *c, void *d, float f1, int two, float f2, int e, int f, int g, int h, int i, int *out)
{
    int result = 1;
    if (fn_800B0C58(a) && fn_80085EEC(fn_800B14A0(a)) && !fn_80085EBC(fn_800B14A0(a)))
        return 0;
    if (fn_800B13D8(a) == b)
        return 0;
    if (p && fn_80095608(p) && fn_800B0F0C(a))
        fn_80099F7C(fn_800B1568(a), 2, 1);
    int wasOff = 0;
    int turnedOn = 0;
    register void *t; // function scope, so it keeps r30 and the && temp takes r29
    switch (fn_800B0BEC(a)) {
    case 0:
    case 7:
        wasOff = fn_80085EEC(fn_800B14A0(a)) == 0;
        result = fn_800A0488(self, p, type, fn_800B14A0(a), c, d, f1, two, e, f2, f, g, i, out);
        turnedOn = wasOff && fn_80085EEC(fn_800B14A0(a));
        break;
    case 2:
    case 8:
        result = fn_800A0B48(self, p, type, fn_800B1478(a), c, d, f1, two, e, f2, f, g, i);
        break;
    case 4:
        fn_8009E998(fn_800B14F0(a), p, two, e, f1, c, d, f2);
        break;
    default:
        return 0;
    }
    if (!fn_800B2234(a))
        fn_800A09C0(self, a, c, d, f2, two, f, turnedOn);
    if (self && result) {
        self->flags |= 0x800;
        fn_8010CDCC(self, 9, a, h, (int)(self->f298 * 30.0f), 0, 0);
        if (fn_800A0E04(self) || (fn_800A0DD4(self) && fn_800B0C58(a)))
            fn_8009F010(self, 0);
        if (!fn_800A0F84(self))
            fn_800AE398(self, 0, 0);
        fn_8009FD04(self, a, c, d);
    } else if (fn_800B0C58(a)) {
        lbl_8066F060 = 3;
        t = fn_800B14A0(a);
        fn_8010CDCC(t, 14, 0, h, (int)(self->f298 * 30.0f), 0, 0);
        if (out && *out && fn_800A10A4(self)) {
            if (fn_800A0E04(self) || (fn_800A0DD4(self) && fn_800B0C58(a)))
                fn_8009F010(self, 0);
            if (!fn_800A0F84(self))
                fn_800AE398(self, 0, 0);
            *out = 0;
            return 1;
        }
    }
    return result;
}

extern "C" int fn_800A0488(void *a0, void *a1, int a2, void *a3, Vector *a4, void *a5, float f6, int a7, int a8, float f9, int s0, int s1, int s2, int *s3)
{
    float f40 = 0.0f;
    int res = 0;
    int b48 = 0;
    int b4c = 0;
    ESub *p50 = fn_80085954(a3);

    if (p50->mb())
        b48 = 1;
    if (p50->kind() == 0x16)
        b4c = 1;
    if (b48) {
        if (b4c) {
            res = 1;
        } else if (!(s0 & 2)) {
            Vector v;
            fn_80429038(&v, a4, fn_800B1724(*(Ent *)a3));
            v.z = 0.0f;
            fn_8042F76C(&v);
            float d = fn_8042EBF4(fn_800B1750(*(Ent *)a3), &v);
            float lim = 0.3f;
            if (d < lim) {
                res = 0;
            } else if ((float)fn_800B18EC(a3, a8 + 0x81) < f6) {
                fn_800E673C(p50, 2, a8, a1, a4, a5, 0x20, 0);
                fn_800E8628(p50, 0x6F);
                res = 1;
            } else {
                res = 1;
            }
        }
    }
    if (res) {
        fn_800D98B0(a3, f6, (float)fn_800B18EC(a3, a8 + 0x81), b4c);
        fn_800D9408(a3, a0, "Removed projectile explosion", 0, -1);
        fn_80086818(a3, fn_80433D20(lbl_8066C6C8, 4, 0));
        if (!b4c) {
            fn_800E8508(p50, 0x79);
            return 1;
        } else {
            *s3 = 1;
            return 0;
        }
    } else {
        fn_800D97D0(a3, a0, a1, f6);
        s0 |= 0x10;
        void *p70 = 0;
        if (a0 && fn_8009ACC0(a0) && fn_800B0C1C(fn_8009ACC0(a0))) {
            p70 = fn_800B14C8(fn_8009ACC0(a0));
            if (fn_800CD21C(p50) && fn_8009B04C(a3) != 0x72 && fn_8009B04C(p70) == 0x3B
                && !((Target *)a3)->s57(0.15f)) {
                p50->play(0x7F, fn_800B1724(*(Ent *)p70), 1, 1.0f, 0, 0, 0, 0);
            }
        }
        if (!fn_800A0E94(a0) && !fn_800CC82C(p50))
            fn_8002FD50(a3, a0 ? a0 : a1, a7, a8, f6, a4, a5, s0, s1, f9, s3, 0, 0xFF, 0xFF);
        if (p70) {
            fn_80086A2C(p70, fn_800B1884(*fn_800B14C8P(fn_8009ACC0(a0)), 0xBD));
            fn_80130F88(fn_80085AF0(p70), a3);
        }
        return 1;
    }
}

extern "C" void fn_800A09C0(void *self, void *a, Vector *c, void *d, float f2, int two, int f, int flag)
{
    Vector v;
    if (self && fn_800B24AC(self))
        fn_80434BA4(&v, fn_80318EB4(fn_800B24AC(self)));
    else
        fn_8042FDBC(&v, d, f2);
    if (flag) {
        if (two == 2) {
            memset(&v, 0, 0x10);
        } else {
            fn_80435530(&v, 7.0f);
            v.z += 2.0f * fn_800B24D8(a);
        }
    }
    if (v.x != 0.0f || v.y != 0.0f || v.z != 0.0f)
        fn_80069254(a, c, d, 100.0f, &v, flag);
}

extern "C" int fn_800A0B48(void *self, void *p, int type, void *x, Vector *c, void *d, float f1, int two, int e, float f2, int f, int g, int i)
{
    if (g == 1) {
        fn_800A2F94(x, self ? self : p, two, e, f1, c, d, f2, 0);
        fn_800A140C(x, self ? self : p, c, d, f2);
    }
    if (f2 > 0.0f && fn_800B24AC(x) && !fn_800B2234(x) && !fn_800664C0(x)) {
        if (!fn_800B24AC(x)->byte91().test()) {
            Vector v;
            if (self && fn_800B24AC(self))
                fn_80434BA4(&v, fn_80318EB4(fn_800B24AC(self)));
            else
                fn_8042FDBC(&v, d, f2);
            fn_80066DC4(x, &v, 0, 0, 0);
            fn_80066794(x, 1);
        }
    }
    if (!self && !(i & 2))
        fn_803A0B74(lbl_8064AA80, 1, 0, x, c, d);
    return 1;
}
