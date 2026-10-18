// Per-frame update of a charge/hold state on an actor (PLAYER fields 31, 193, 221); docs/versus.md row 20.

inline int sn_return_decl(int a) { return a; }

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
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
};

struct GState {
    char pad0[0x768];
    int f768; // +0x768
};

struct Actor {
    char pad0[0x2FC];
    void *f2FC;
    char pad1[4];
    unsigned int flags; // +0x304
    char pad2[0x24];
    float f32C; // +0x32C
    char pad3[4];
    float f334; // +0x334
    unsigned int f338; // +0x338
    char pad4[0x88];
    float f3C4; // +0x3C4
    float f3C8; // +0x3C8
    float f3CC; // +0x3CC
};

extern char lbl_80593BE8[];
extern char lbl_80572154[];
extern GState lbl_80552110;

extern "C" {
float fn_80426A84(void *g);
unsigned int fn_8042EFF8(void *g);
float fn_800B1884(void *e, int id);
int fn_800B18EC(void *e, int id);
float fn_80086730(void *a);
float fn_8008677C(void *a);
void fn_800849EC(void *a, float f);
int fn_80086908(void *a);
int fn_80086890(void *a);
void fn_800868C0(void *a, int v);
int fn_800ACD20(void *a, int id);
Handle *fn_80393D0C(void *a, int id, int x, int y);
Handle *fn_80393A60(void *a, int id, int x);
int fn_8008600C(void *a);
void *fn_80085954(void *a);
int fn_800CCA88(void *p);
float fn_80086614(void *a);
float fn_80086640(void *a);
void fn_80084958(void *a, float f);
float fn_80086704(void *a);
int fn_80085EEC(void *a);
void fn_80030930(void *a, int b, int c, int d, float f1, int e, int f, int g, int h, float f2);
int fn_80086B1C(void *a);
void fn_8009E230(void *a);
int fn_80086B9C(void *a);
int fn_80086BCC(void *a);
void fn_80086A2C(void *a, float f);
float fn_80086A00(void *a);
int fn_80086B6C(void *a);
void fn_8009E09C(void *a);
int fn_8043B31C(void *p);
void fn_80428EEC(void *p, int v);
int fn_80085D3C(void *a);
void *fn_80085AF0(void *a);
int fn_8043B2C8(void *p);
void fn_8009E144(void *a);
}

extern "C" void fn_8009D818(register Actor *self)
{
    float dt = fn_80426A84(lbl_80593BE8);
    unsigned int frame = fn_8042EFF8(lbl_80593BE8);
    float limit = fn_800B1884(self, 0xDE);
    if (fn_80086730(self) < fn_8008677C(self))
        fn_800849EC(self, fn_80086730(self) + self->f3CC * dt);
    if (!fn_80086908(self) && !fn_80086890(self) && fn_80086730(self) < limit) {
        fn_800868C0(self, 1);
        Handle *h = fn_80393D0C(self, fn_800ACD20(self, 0xDD), 0xFF, 0xFF);
        if (h)
            h->s56();
    } else if (fn_80086890(self) && fn_80086730(self) >= limit) {
        fn_800868C0(self, 0);
        Handle *h = fn_80393A60(self, fn_800ACD20(self, 0xDD), 0);
        if (h)
            h->s54();
    }
    if (fn_8008600C(self)) {
        register void *s = fn_80085954(self);
        if (!fn_800CCA88(s) && fn_80086614(self) >= 0.0f) {
            if (fn_80086614(self) < fn_80086640(self) || self->f3C4 < 0.0f) {
                if (fn_80086730(self) >= fn_800B1884(self, 0x1F)) {
                    fn_80084958(self, fn_80086614(self) + self->f3C4 * dt);
                    if (self->f3C4 < 0.0f && fn_80086614(self) < fn_80086704(self))
                        self->f32C = fn_80086614(self);
                    if (fn_80086614(self) <= 0.0f && !fn_80085EEC(self)) {
                        fn_80030930(self, 0, 0, 0, 0.0f, 0, 0, 0, 1, 0.0f);
                        return;
                    }
                }
            }
        }
    }
    if (fn_80086704(self) < fn_80086614(self) && !(self->flags & 0x20000))
        self->f32C = fn_80086704(self) + self->f3C8 * dt;
    unsigned int elapsed = lbl_80552110.f768 - self->f338;
    if (fn_80086B1C(self)) {
        if ((float)frame > (float)elapsed + self->f334)
            fn_8009E230(self);
    } else if (fn_80086B9C(self)) {
        if (fn_80086BCC(self)) {
        } else {
            fn_80086A2C(self, dt * -50.0f);
            if (fn_80086A00(self) <= 0.0f)
                self->flags &= ~0x4000;
        }
    } else if (fn_80086B6C(self)) {
        if (!fn_80086BCC(self)) {
            if ((float)frame > (float)elapsed + self->f334) {
                fn_8009E09C(self);
                self->flags &= ~0x10000000;
            } else if ((float)frame > ((float)elapsed + self->f334) - (float)fn_800B18EC(self, 0xC0) * 0.25f) {
                if (!(self->flags & 0x10000000)) {
                    if (self->f2FC)
                        fn_80428EEC(lbl_80572154, fn_8043B31C(self->f2FC));
                    else if (fn_80085D3C(self))
                        fn_80428EEC(lbl_80572154, 1);
                    self->flags |= 0x10000000;
                }
            }
        }
    } else {
        if (fn_80086BCC(self) || fn_80086A00(self) >= 100.0f) {
            if (fn_80085AF0(self) && !fn_8043B2C8(fn_80085AF0(self))) {
            } else
                fn_8009E144(self);
        } else
            fn_80086A2C(self, -fn_800B1884(self, 0xC1) * dt);
    }
}
