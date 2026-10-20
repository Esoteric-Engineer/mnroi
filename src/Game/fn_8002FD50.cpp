// Applies a hit to an actor: scales the damage by the difficulty tables and resistances, takes it from health (+0x31C) and armour (+0x32C), runs the hit reactions named by the flags, and returns the damage dealt (0 when the hit is blocked). docs/versus.md row 28.

inline int sn_return_decl(int a) { return a; }

struct Ent {
    int pad;
};

struct EObj {
    char pad0[0x3AC];
};

struct Act;

struct Obj : EObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13();
    virtual void s14(Ent *src, int kind, int type, float dmg, int a, int b, unsigned int flags, int c); // +0x78
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
    virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32();
    virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
    virtual void s37(int state, int a, int b, float f, int c, int d, int e, int g); // +0x130
};

struct ActBase : Ent {
    char d[0x194];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
    virtual void s29(Ent *src, int kind, int type, float dmg, int a, int b, unsigned int flags, float f, int c, int d, int e); // +0xF0
    virtual void s30(Ent *src, int kind, int type, float dmg, int a, int b, unsigned int flags, float f, int c); // +0xF8
};

struct Act : ActBase {
    char pad19C[0x31C - 0x19C];
    float f31C; // health
    char pad320[0x32C - 0x320];
    float f32C; // armour
    char pad330[0x3DC - 0x330];
    Obj *f3DC;
};

extern int lbl_8066B9A0;
extern void *lbl_8066C6C8;
extern const float lbl_80485CDC[3]; // per fn_80085A5C of the actor hit
extern const float lbl_80485CE8[3]; // per fn_80085A5C of the attacker

extern "C" {
int fn_800B0C1C(void *e);
Act *fn_800B14C8(void *e);
Obj *fn_80085954(void *p);
unsigned int fn_800CC514(void *c);
int fn_800CCA08(void *c);
int fn_8008627C(void *a);
int fn_800B0C58(void *e);
Act *fn_800B14A0(void *e);
void *fn_800B1724(void *e);
int fn_80031434(void *a, int b, unsigned int c, int d, int e, int f);
int fn_80085F4C(void *a);
int fn_8008582C(void *a);
int fn_80085EEC(void *a);
int fn_800B0DA0(void *e);
Act *fn_800B14F0(void *e);
Ent *fn_8009ACC0(Ent &a);
int fn_800861EC(void *a);
int fn_80085A5C(void *a);
float fn_80086C80(void *a, unsigned char i);
int fn_80171F8C();
float fn_8007E698(void *a, Ent *src, int kind, int type, float dmg, int c);
int fn_80095608(void *a);
int fn_80085D3C(void *a);
float fn_80433D20(void *p, int id, int z);
int fn_80433D70(void *p, int id, int z);
void fn_800D9A74(void *a, Ent *src, float dmg, float armour, float health, int type, float resist, int kind);
float fn_80086640(void *a);
void fn_80030930(void *a, Ent *src, int kind, int type, float dmg, int b, int c, unsigned int flags, int d, float f);
int fn_800CD0EC(EObj &c);
int fn_80031248(void *a, int b, int c, int d, int e);
void fn_80041588(void *a, Ent *src, int kind);
void *fn_80085AF0(void *a);
void *fn_8042E83C(void *p);
void fn_8003DBF0(void *p, int id, float f, int z);
}

extern "C" float fn_8002FD50(register Act *self, Ent *src, int kind, int type, float dmg, int p20, int p24, unsigned int flags, int p2C,
                             float f30, int *blocked, int pBC, int pC0, int pC4)
{
    float f34 = self->f31C;
    float f38 = dmg;
    float f3C = 1.0f;
    if (fn_800B0C1C(self)) {
        Act *f40 = fn_800B14C8(self);
        Obj *f44 = fn_80085954(f40);
        if (fn_800CC514(f44) & 0x20000000)
            return 0.0f;
        if (fn_800CCA08(f44)) {
            if (fn_8008627C(f40) && kind == 1 && src && fn_800B0C58(src))
                fn_80031434(fn_800B14A0(src), (int)fn_800B1724(f40), 1, 1, 0, 0);
            if (!(flags & 2))
                return 0.0f;
        }
    }
    if (fn_80085F4C(self) || (!fn_8008582C(self) && lbl_8066B9A0)) {
        if (blocked)
            *blocked = 1;
        return 0.0f;
    }
    if (self->f31C < 1.0f && fn_80085EEC(self)) {
        self->s30(src, kind, type, f38, p20, p24, flags, f30, p2C);
        return 0.0f;
    }
    if (!fn_800B0C1C(self) && src && fn_800B0DA0(src)) {
        Ent *f44 = fn_8009ACC0(*fn_800B14F0(src));
        if (f44 == self && !fn_800861EC(fn_800B14A0(f44)))
            f38 *= 0.1f;
    }
    if (fn_800B0C1C(self))
        f38 *= lbl_80485CDC[fn_80085A5C(fn_800B14C8(self))];
    if (src && fn_800B0C1C(src))
        f38 *= lbl_80485CE8[fn_80085A5C(fn_800B14C8(src))];
    if (!(flags & 0x20)) {
        f3C = fn_80086C80(self, type);
        f38 *= f3C;
        if (blocked && f3C < 1.0f && (float)fn_80171F8C() * 4.656612873077393e-10f > f3C * 0.5f)
            *blocked = 1;
    }
    f38 = fn_8007E698(self, src, kind, type, f38, p2C);
    if (f38 <= 0.0f) {
        if (blocked)
            *blocked = 1;
        return 0.0f;
    }
    float f48 = self->f31C;
    float f4C = self->f32C;
    if (fn_80095608(self) || fn_80085D3C(self)) {
        if (!(flags & 1) || !fn_80085D3C(self))
            self->f31C -= fn_80433D20(lbl_8066C6C8, 3, 0) * f38;
        self->f32C -= f38;
        if (self->f32C < 0.0f) {
            self->f31C += self->f32C;
            self->f32C = 0.0f;
        }
        fn_800D9A74(self, src, dmg, f4C - self->f32C, f48 - self->f31C, type, f3C, kind);
    } else {
        self->f31C -= f38;
        fn_800D9A74(self, src, dmg, 0.0f, f48 - self->f31C, type, f3C, kind);
    }
    if ((flags & 0x8000) && fn_800B0C58(src)) {
        fn_800B14A0(src)->f31C += f38 * 0.3f;
        if (fn_800B14A0(src)->f31C > fn_80086640(fn_800B14A0(src)))
            fn_800B14A0(src)->f31C = fn_80086640(fn_800B14A0(src));
    }
    if (self->f31C < 1.0f) {
        fn_80030930(self, src, kind, type, f38, p20, p24, flags, p2C, f30);
        return 0.0f;
    }
    if (fn_800B0C1C(self) && fn_800B14C8(self)->f3DC)
        fn_800B14C8(self)->f3DC->s14(src, kind, type, f38, p20, p24, flags, p2C);
    self->s29(src, kind, type, f38, p20, p24, flags, f30, p2C, pC0, pC4);
    if (flags & 0x1F00) {
        if (!fn_800CD0EC(*fn_80085954(self))) {
            float f50 = f38 * 0.02f;
            f50 = f50 >= 0.8f ? (f50 <= 1.0f ? f50 : 1.0f) : 0.8f;
            int f44 = 1;
            if (flags & 0x100)
                f44 = fn_80031434(self, p20, flags, flags & 0x40, flags & 0x10, pBC);
            else if (flags & 0x800)
                fn_80085954(self)->s37(0x7F, p20, 1, 1.0f, 0, 0, 0, 0);
            else if (flags & 0x200)
                f44 = fn_80031248(self, p20, flags & 0x40, flags & 0x10, pBC);
            else if (flags & 0x400)
                fn_80085954(self)->s37(0x72, p20, 1, 1.0f, 0, 0, 0, 0);
            else if (flags & 0x1000)
                fn_80085954(self)->s37(0x69, p20, 1, 1.0f, 0, 0, 0, 0);
            fn_80041588(self, src, kind);
        }
    }
    if ((flags & 0x2000) && src && fn_800B0C58(src) && fn_80085AF0(fn_800B14A0(src)) && fn_8042E83C(fn_80085AF0(fn_800B14A0(src))))
        fn_8003DBF0(fn_8042E83C(fn_80085AF0(fn_800B14A0(src))), fn_80433D70(lbl_8066C6C8, 0x2C, 0), fn_80433D20(lbl_8066C6C8, 0x2F, 0), 1);
    return f38;
}
