// Projectile hit on an actor (guess): deflect, absorb or hand on to fn_8002FD50 (PLAYER 0x81 + n, 0xBD); docs/versus.md row 20.
// The unit owns .rodata 0x8048AF88-0x8048AFC8; its first word is fn_8009FF54's 30.0f.

__asm__(".section .rodata\n\t.globl lbl_8048AF88\nlbl_8048AF88:\n\t.float 30.0\n\t.text"); // 8-aligns the claim: fn_8009FF54's, read through extern_pool

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
