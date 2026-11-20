// The Power Plant classes cPowerPlant_HumanTorchSAC, _ElektraSAC, _IronMan_3, _Venom_3, _CoilToggle and _CoilArc (docs/story.md row 21).
// Pool read from 0x804A0458 (extern_pool).

inline int sn_return_decl(int a) { return a; }

#define V6(a, b, c, d, e, f) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f();

struct cScript {
    char d[0x24];
    char *vptr; // +0x24
};

struct Ref8 {
    int unk0;
    int value; // +0x4
};

struct Vector {
    float x, y, z, w;
    Vector();
} __attribute__((aligned(8)));

struct SObjData {
    char pad0[0x198];
};

struct SObj : SObjData { // vptr at +0x198
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(Vector *at, int a); // +0x30
};


class ScriptObj
{
public:
    char d[0x3ac];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36();
    virtual int s37(int a, Vector *at, int c, float f, int d, int e, int g, int h); // +0x130
};

struct ArcData {
    char pad0[0xc8];
};

struct Arc : ArcData { // what fn_803A20D8 returns; vptr at +0xC8
    V6(v0, v1, v2, v3, v4, v5) V6(v6, v7, v8, v9, v10, v11) V6(v12, v13, v14, v15, v16, v17)
    V6(v18, v19, v20, v21, v22, v23) V6(v24, v25, v26, v27, v28, v29)
    virtual void v30();
    virtual void v31(int h); // +0x100
    V6(v32, v33, v34, v35, v36, v37) V6(v38, v39, v40, v41, v42, v43) V6(v44, v45, v46, v47, v48, v49)
    virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
    virtual void v54(); // +0x1B8
};

struct Slot {
    char pad0[0x20];
    float dist; // +0x20
    char pad24[0xC];
} __attribute__((aligned(8)));

struct Query { // 0x1850
    char pad0[0x40];
    Slot slot[0x80]; // +0x40
    unsigned int count; // +0x1840
    int pad1844;
    unsigned int mask; // +0x1848
    int pad184c;
};

struct cPowerPlant_HumanTorchSAC : cScript { // 0x60
    Ref8 boss;      // +0x28, param 0
    Ref8 r30;       // +0x30, param 1
    Ref8 r38;       // +0x38, param 2
    char pad40[8];
    int f48;        // +0x48
    int armored;    // +0x4C
    int f50;        // +0x50
    int done;       // +0x54
    float health;   // +0x58
    float limit;    // +0x5C
    cPowerPlant_HumanTorchSAC() __asm__("fn_80469C6C");
};

struct cPowerPlant_ElektraSAC : cScript { // 0x54
    Ref8 boss;      // +0x28
    Ref8 player;    // +0x30
    Ref8 r38;       // +0x38, param 0
    int f40;        // +0x40
    int done;       // +0x44
    int bossHit;    // +0x48
    int playerHit;  // +0x4C
    int armored;    // +0x50
    cPowerPlant_ElektraSAC() __asm__("fn_80469CF0");
};

struct cPowerPlant_IronMan_3 : cScript { // 0xDC
    Ref8 boss;      // +0x28
    Ref8 r30[10];   // +0x30, params 0-9
    int active;     // +0x80
    int f84;        // +0x84
    int f88;        // +0x88
    int f8C;        // +0x8C
    int f90;        // +0x90
    int f94;        // +0x94
    int f98;        // +0x98
    int f9C;        // +0x9C
    int fA0;        // +0xA0
    int fA4;        // +0xA4
    int done;       // +0xA8
    int state;      // +0xAC
    float fB0;      // +0xB0
    float fB4;      // +0xB4
    float fB8;      // +0xB8
    float fBC;      // +0xBC
    float fC0;      // +0xC0
    float fC4;      // +0xC4
    float fC8;      // +0xC8
    float fCC;      // +0xCC
    float fD0;      // +0xD0
    float fD4;      // +0xD4
    float fD8;      // +0xD8
    cPowerPlant_IronMan_3() __asm__("fn_80469D68");
};

struct cPowerPlant_Venom_3 : cScript { // 0x134
    Ref8 boss;      // +0x28
    Ref8 r30[13];   // +0x30, params 0-12
    Ref8 r98;       // +0x98
    Ref8 rA0;       // +0xA0, param 13
    Ref8 rA8;       // +0xA8, param 14
    Ref8 rB0;       // +0xB0, param 15
    float fB8;      // +0xB8
    float fBC;      // +0xBC
    float fC0;      // +0xC0
    float fC4;      // +0xC4
    float fC8;      // +0xC8
    float fCC;      // +0xCC
    float fD0;      // +0xD0
    int mode;       // +0xD4
    int zone;       // +0xD8
    int prevZone;   // +0xDC
    int count;      // +0xE0
    int fE4;        // +0xE4
    int fE8;        // +0xE8
    int fEC;        // +0xEC
    int fF0;        // +0xF0
    int done;       // +0xF4
    int a[5];       // +0xF8
    int b[5];       // +0x10C
    int c[5];       // +0x120
    cPowerPlant_Venom_3() __asm__("fn_80469E3C");
};

struct cPowerPlant_CoilToggle : cScript { // 0x40
    int hit;        // +0x28
    int on;         // +0x2C
    Vector pos;     // +0x30
    cPowerPlant_CoilToggle() __asm__("fn_80469F64");
};

struct cPowerPlant_CoilArc : cScript { // 0x88
    Ref8 coil[8];   // +0x28, params 0-7
    int idle[8];    // +0x68
    cPowerPlant_CoilArc() __asm__("fn_80469FBC");
};



extern char lbl_80572278[];
extern char lbl_8057230C[];
extern int lbl_8066C71C;
extern int lbl_8066C724;
extern char lbl_8064AA80[];

extern "C" {

void fn_8004E4B4(Query *q, void *pos, float r, void *world);
void fn_8004E9C8(Query *q);
unsigned int fn_800791C8(cScript *self, unsigned int i);
int fn_800797D4(cScript *self);
void fn_8007A448(int h);
void fn_8007A4FC(int h);
void fn_8007A738(int h, Vector *to);
void fn_8007B288(int h);
void fn_8007B2E8(int h, int which, float v);
void fn_8007B540(int h, int on, int b);
void fn_8007B618(int h, int on);
float fn_8007B8F8(int h);
void fn_8007BAA0(int h);
void fn_8007BB24(int h);
float fn_8007C0AC(void *ev);
float fn_8007C244(void *ev);
float fn_8007C2AC(void *ev);
void fn_8007C314(void *ev, float v);
float fn_8007C3EC(void *ev);
void fn_8007C454(void *ev, float v);
float fn_8007C52C(void *ev);
float fn_8007C594(void *ev, float dmg, int type, int kind, int src, unsigned int flags);
void fn_8007C6D0(void *ev, float v);
int fn_8007CF00(cScript *script, int handle, int value);
void fn_8007D404(cScript *self, float seconds, int kind, float a, float b, float c, float d, int e);
int fn_8007D7C4(cScript *self, unsigned char kind);
int fn_800809CC(void *ev);
int fn_80080B34();
SObj *fn_80080EFC(void *ev);
void *fn_80081274(void *ev);
void fn_800816A0(int h);
void fn_80081918(int h);
int fn_80081A54(int h);
int fn_80081B40(int h);
int fn_80081BD4(int h);
void fn_80081C68();
void fn_80081C94();
void fn_80081CC4();
SObj *fn_80081E6C(void *ev);
void fn_80082440(void *ev, Vector *out);
void fn_80082AFC(void *ev, int h, int owner, int kind, float a, float b, float c, float d);
void fn_80082BB0(void *ev, char *name, int h);
void fn_80082E24(void *ev, char *name);
void fn_80083428(void *ev, char *name);
ScriptObj *fn_80085954(int actor);
int fn_800B13D8(int e);
int fn_80171F8C();
void fn_80393938(SObj *o, Arc *a, int flag);
Arc *fn_80393A60(SObj *o, char *name, int a);
Arc *fn_803A20D8(char *tbl, char *name, SObj *o, int b, int c, int d, int e, float f);
float *fn_8042FB28(Vector *v);
void fn_8043323C(void *p, int on);
int fn_80434C2C(Slot *s);
void fn_80434C88(Query *q);
void fn_80434CDC(Query *q, int bit);
void fn_80434D18(Query *q, void *ignore);
int fn_8043536C(Slot *s);
int fn_804425F8(void *ev);
void fn_8046B5F0(void *ev, int x);
void fn_8046B638(void *ev, int x);
void fn_8046B6C8(void *ev, int x);
void fn_8046B710(void *ev, int x);
void fn_8046B860(void *g, int x);
int fn_8046C160(void *ev);
void fn_8046C1E8(void *ev, int x);

void fn_801DD694(cPowerPlant_HumanTorchSAC *self);
void fn_801DD6F4(cPowerPlant_HumanTorchSAC *self);
void fn_801DD8EC(cPowerPlant_HumanTorchSAC *self);
void fn_801DDB14(cPowerPlant_HumanTorchSAC *self);
void fn_801DDBBC(cPowerPlant_HumanTorchSAC *self);
void fn_801DDC5C(cPowerPlant_HumanTorchSAC *self);
void fn_801DDCC4(cPowerPlant_HumanTorchSAC *self);
void fn_801DE308(cPowerPlant_ElektraSAC *self);
void fn_801DE500(cPowerPlant_ElektraSAC *self);
void fn_801DE718(cPowerPlant_ElektraSAC *self);
void fn_801DE7C0(cPowerPlant_ElektraSAC *self);
void fn_801DE86C(cPowerPlant_ElektraSAC *self);
void fn_801DE8D4(cPowerPlant_ElektraSAC *self);
void fn_801DFDCC(cPowerPlant_IronMan_3 *self);
void fn_801DFED8(cPowerPlant_IronMan_3 *self);
void fn_801E0004(cPowerPlant_IronMan_3 *self);
void fn_801E00EC(cPowerPlant_IronMan_3 *self);
void fn_801E01EC(cPowerPlant_IronMan_3 *self);
void fn_801E0294(cPowerPlant_IronMan_3 *self);
void fn_801E0328(cPowerPlant_IronMan_3 *self);
void fn_801E0390(cPowerPlant_IronMan_3 *self);
void fn_801E19F8(cPowerPlant_Venom_3 *self);
void fn_801E1A94(cPowerPlant_Venom_3 *self);
void fn_801E1B7C(cPowerPlant_Venom_3 *self);
void fn_801E1C58(cPowerPlant_Venom_3 *self);
void fn_801E1D0C(cPowerPlant_Venom_3 *self);
void fn_801E1EF4(cPowerPlant_Venom_3 *self);
void fn_801E22C4(cPowerPlant_Venom_3 *self);
void fn_801E2374(cPowerPlant_Venom_3 *self);
void fn_801E2410(cPowerPlant_Venom_3 *self);
void fn_801E2480(cPowerPlant_Venom_3 *self);
void fn_801E27FC(cPowerPlant_CoilToggle *self, int on);
int fn_801E365C(cPowerPlant_CoilArc *self, int from, int to);
int fn_801E37AC(cPowerPlant_CoilArc *self, int h);
void fn_801E3A24(cPowerPlant_CoilArc *self, int h);
unsigned int fn_801E3B48(cPowerPlant_HumanTorchSAC *self);
unsigned int fn_801E3B90(cPowerPlant_HumanTorchSAC *self);
unsigned int fn_801E3BD8(cPowerPlant_HumanTorchSAC *self);
unsigned int fn_801E3C74(cPowerPlant_ElektraSAC *self);
unsigned int fn_801E3CBC(cPowerPlant_ElektraSAC *self);
unsigned int fn_801E3D58(cPowerPlant_IronMan_3 *self);
unsigned int fn_801E3DA0(cPowerPlant_IronMan_3 *self);
unsigned int fn_801E3DE8(cPowerPlant_IronMan_3 *self);
unsigned int fn_801E3E30(cPowerPlant_IronMan_3 *self);
unsigned int fn_801E3E78(cPowerPlant_IronMan_3 *self);
unsigned int fn_801E3EC0(cPowerPlant_IronMan_3 *self);
unsigned int fn_801E3F08(cPowerPlant_IronMan_3 *self);
unsigned int fn_801E3F50(cPowerPlant_IronMan_3 *self);
unsigned int fn_801E3F98(cPowerPlant_IronMan_3 *self);
unsigned int fn_801E3FE0(cPowerPlant_IronMan_3 *self);
unsigned int fn_801E407C(cPowerPlant_Venom_3 *self);
unsigned int fn_801E40C4(cPowerPlant_Venom_3 *self);
unsigned int fn_801E410C(cPowerPlant_Venom_3 *self);
unsigned int fn_801E4154(cPowerPlant_Venom_3 *self);
unsigned int fn_801E419C(cPowerPlant_Venom_3 *self);
unsigned int fn_801E41E4(cPowerPlant_Venom_3 *self);
unsigned int fn_801E422C(cPowerPlant_Venom_3 *self);
unsigned int fn_801E4274(cPowerPlant_Venom_3 *self);
unsigned int fn_801E42BC(cPowerPlant_Venom_3 *self);
unsigned int fn_801E4304(cPowerPlant_Venom_3 *self);
unsigned int fn_801E434C(cPowerPlant_Venom_3 *self);
unsigned int fn_801E4394(cPowerPlant_Venom_3 *self);
unsigned int fn_801E43DC(cPowerPlant_Venom_3 *self);
unsigned int fn_801E4424(cPowerPlant_Venom_3 *self);
unsigned int fn_801E446C(cPowerPlant_Venom_3 *self);
unsigned int fn_801E44B4(cPowerPlant_Venom_3 *self);
int fn_801E4550(cPowerPlant_CoilToggle *self);
unsigned int fn_801E4594(cPowerPlant_CoilToggle *self);
unsigned int fn_801E4630(cPowerPlant_CoilArc *self);
unsigned int fn_801E4678(cPowerPlant_CoilArc *self);
unsigned int fn_801E46C0(cPowerPlant_CoilArc *self);
unsigned int fn_801E4708(cPowerPlant_CoilArc *self);
unsigned int fn_801E4750(cPowerPlant_CoilArc *self);
unsigned int fn_801E4798(cPowerPlant_CoilArc *self);
unsigned int fn_801E47E0(cPowerPlant_CoilArc *self);
unsigned int fn_801E4828(cPowerPlant_CoilArc *self);

void fn_801DD29C(register cPowerPlant_HumanTorchSAC *self) // slot 5
{
    fn_8046B710(&self->boss, fn_801E3B48(self));
    fn_8007CF00(self, fn_804425F8(&self->boss), 0);
    fn_8007CF00(self, fn_80080B34(), 0);
    fn_8046B710(&self->r30, fn_801E3B90(self));
    fn_8046B710(&self->r38, fn_801E3BD8(self));
    self->f48 = 0;
    self->armored = 0;
    self->done = 0;
    self->health = fn_8007C244(&self->boss);
    self->limit = self->health * 0.35f;
    fn_801DD6F4(self);
}

void fn_801DD3A0(register cPowerPlant_HumanTorchSAC *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_801DD694(self);
        break;
    case 72:
        fn_801DDB14(self);
        break;
    case 74:
        fn_801DDBBC(self);
        break;
    case 76:
        fn_801DDC5C(self);
        break;
    case 78:
        fn_801DDCC4(self);
        break;
    }
}

float fn_801DD470(register cPowerPlant_HumanTorchSAC *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h == fn_804425F8(&self->boss))
        fn_8007D404(self, 0.25f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    return damage;
}

int fn_801DD51C(register cPowerPlant_HumanTorchSAC *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    fn_8007D7C4(self, 10);
    return 1;
}

void fn_801DD578(register cPowerPlant_HumanTorchSAC *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (h == fn_80080B34() || h == fn_804425F8(&self->boss)) {
        if (self->done && h != fn_80080B34())
            return;
        self->done = 1;
        fn_8007D7C4(self, 10);
        fn_80081C68();
        fn_80081C94();
        fn_80081CC4();
        fn_80081B40(fn_804425F8(&self->boss));
        if (h == fn_804425F8(&self->boss)) {
            fn_80081A54(fn_80080B34());
            fn_801DDB14(self);
        } else
            fn_801DDC5C(self);
    }
    return;
}

void fn_801DD694(register cPowerPlant_HumanTorchSAC *self)
{
    float hp = fn_8007C0AC(&self->boss);

    if (hp < self->limit) {
        fn_801DD8EC(self);
        return;
    }
}

void fn_801DD6F4(register cPowerPlant_HumanTorchSAC *self)
{
    fn_8007B288(fn_804425F8(&self->boss));
    fn_8007B2E8(fn_804425F8(&self->boss), 0, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 1, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 2, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 3, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 4, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 5, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 6, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 7, 0.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 8, 0.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 9, 0.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 10, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 11, 95.0f);
}

void fn_801DD8EC(register cPowerPlant_HumanTorchSAC *self)
{
    self->f48 = 1;
    self->armored = 1;
    fn_8007B288(fn_804425F8(&self->boss));
    fn_8007B2E8(fn_804425F8(&self->boss), 0, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 1, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 2, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 3, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 4, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 5, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 6, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 7, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 8, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 9, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 10, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 11, 95.0f);
    fn_8007B540(fn_804425F8(&self->boss), 1, 0);
}

void fn_801DDB14(register cPowerPlant_HumanTorchSAC *self)
{
    fn_8007D404(self, 2.0f, 74, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8046B860(lbl_8057230C, 1);
}

void fn_801DDBBC(register cPowerPlant_HumanTorchSAC *self)
{
    fn_80081918(fn_80080B34());
    lbl_8066C71C = fn_80080B34();
    fn_80082AFC(&self->r30, fn_804425F8(&self->r30), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801DDC5C(register cPowerPlant_HumanTorchSAC *self)
{
    fn_8007D404(self, 2.0f, 78, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801DDCC4(register cPowerPlant_HumanTorchSAC *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    lbl_8066C71C = fn_804425F8(&self->boss);
    fn_8046B6C8(&ev, fn_801E3BD8(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 7, 0.0f, 0.0f, 0.0f, 0.0f);
}


void fn_801DDD84(register cPowerPlant_ElektraSAC *self) // slot 5
{
    fn_8046B710(&self->boss, fn_800797D4(self));
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
    fn_8046B710(&self->player, fn_80080B34());
    fn_8007CF00(self, fn_804425F8(&self->player), 0);
    fn_8046B710(&self->r38, fn_801E3C74(self));
    self->armored = 0;
    self->f40 = 0;
    fn_801DE308(self);
}

void fn_801DDE54(register cPowerPlant_ElektraSAC *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 30: {
        Ref8 ev;

        fn_8046B6C8(&ev, fn_801E3C74(self));
        fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    }
    case 40: {
        Ref8 ev;

        fn_8046B6C8(&ev, fn_801E3C74(self));
        fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 7, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    }
    case 81:
        fn_801DE718(self);
        break;
    case 82:
        fn_801DE7C0(self);
        break;
    case 83:
        fn_801DE86C(self);
        break;
    case 84:
        fn_801DE8D4(self);
        break;
    }
}

float fn_801DE008(register cPowerPlant_ElektraSAC *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h == fn_804425F8(&self->boss)) {
        float ratio = fn_8007C0AC(&self->boss) / fn_8007C244(&self->boss);

        if (ratio < 0.5f && self->armored == 0) {
            self->armored = 1;
            fn_801DE500(self);
        }
    }
    return damage;
}

int fn_801DE0DC(register cPowerPlant_ElektraSAC *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    if (h == fn_804425F8(&self->boss)) {
        if (damage > 90000.0f && kind == 8)
            self->bossHit = 1;
        return 1;
    } else if (h == fn_804425F8(&self->player)) {
        if (damage > 90000.0f && kind == 8) {
            self->playerHit = 1;
            return 1;
        }
    }
    return 1;
}

void fn_801DE1C8(register cPowerPlant_ElektraSAC *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (self->done) {
        if (h != fn_804425F8(&self->player))
            return;
        return;
    }
    self->done = 1;
    lbl_8066C724 = 1;
    fn_80081C68();
    fn_80081C94();
    fn_80081CC4();
    fn_80081B40(fn_804425F8(&self->boss));
    if (h == fn_804425F8(&self->boss)) {
        fn_80081A54(fn_804425F8(&self->player));
        if (self->bossHit == 0)
            fn_801DE718(self);
        else
            fn_801DE7C0(self);
    } else if (h == fn_804425F8(&self->player)) {
        if (self->playerHit == 0)
            fn_801DE86C(self);
        else
            fn_801DE8D4(self);
    }
}

void fn_801DE308(register cPowerPlant_ElektraSAC *self)
{
    fn_8007B288(fn_804425F8(&self->boss));
    fn_8007B2E8(fn_804425F8(&self->boss), 0, 100.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 1, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 2, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 3, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 4, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 5, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 6, 100.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 7, 0.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 8, 0.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 9, 0.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 10, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 11, 95.0f);
}

void fn_801DE500(register cPowerPlant_ElektraSAC *self)
{
    fn_8007B288(fn_804425F8(&self->boss));
    fn_8007B2E8(fn_804425F8(&self->boss), 0, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 1, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 2, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 3, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 4, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 5, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 6, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 7, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 8, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 9, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 10, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 11, 95.0f);
    fn_8007B540(fn_804425F8(&self->boss), 1, 0);
}

void fn_801DE718(register cPowerPlant_ElektraSAC *self)
{
    fn_8007D404(self, 2.0f, 82, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_8057230C, 1);
}

void fn_801DE7C0(register cPowerPlant_ElektraSAC *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->player));
    fn_8046B6C8(&ev, fn_801E3CBC(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801DE86C(register cPowerPlant_ElektraSAC *self)
{
    fn_8007D404(self, 2.0f, 84, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801DE8D4(register cPowerPlant_ElektraSAC *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    fn_8046B6C8(&ev, fn_801E3C74(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}


void fn_801DE980(register cPowerPlant_IronMan_3 *self) // slot 5
{
    fn_8046B710(&self->boss, fn_800797D4(self));
    fn_8046B710(&self->r30[0], fn_801E3D58(self));
    fn_8046B710(&self->r30[1], fn_801E3DA0(self));
    fn_8046B710(&self->r30[2], fn_801E3DE8(self));
    fn_8046B710(&self->r30[3], fn_801E3E30(self));
    fn_8046B710(&self->r30[4], fn_801E3E78(self));
    fn_8046B710(&self->r30[5], fn_801E3EC0(self));
    fn_8046B710(&self->r30[6], fn_801E3F08(self));
    fn_8046B710(&self->r30[7], fn_801E3F50(self));
    fn_8046B710(&self->r30[8], fn_801E3F98(self));
    fn_8046B710(&self->r30[9], fn_801E3FE0(self));
    fn_8007CF00(self, fn_804425F8(&self->r30[2]), 0);
    fn_8007CF00(self, fn_804425F8(&self->r30[4]), 0);
    fn_8007CF00(self, fn_804425F8(&self->r30[5]), 0);
    fn_8007CF00(self, fn_804425F8(&self->r30[6]), 0);
    fn_8007CF00(self, fn_80080B34(), 0);
    self->done = 0;
    self->active = 0;
    self->f84 = 0;
    self->f88 = 0;
    self->f8C = 0;
    self->f90 = 0;
    self->f94 = 0;
    self->f98 = 0;
    self->f9C = 0;
    self->fA0 = 0;
    self->fA4 = 0;
    self->state = 0;
    self->fB8 = 0.0f;
    self->fD4 = 0.25f;
    self->fB0 = 0.1f;
    self->fB4 = 1.0f;
    self->fCC = 5.0f;
    self->fD8 = 15.0f;
    self->fD0 = 2.0f;
    self->fBC = fn_8007B8F8(fn_804425F8(&self->boss));
    self->fC0 = self->fBC * 10.0f;
    self->fC4 = fn_8007B8F8(fn_804425F8(&self->boss));
    self->fC8 = self->fBC * 10.0f;
    self->active = 1;
    fn_8007A448(fn_804425F8(&self->boss));
    fn_8007D404(self, 2.0f, 100, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801DECF0(register cPowerPlant_IronMan_3 *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    float ratio;

    switch (kind) {
    case 10:
        ratio = fn_8007C0AC(&self->boss) / fn_8007C244(&self->boss);
        if (ratio < 0.5f && self->active == 1 && self->f8C == 0 && self->f90 == 0) {
            fn_801DFED8(self);
            break;
        }
        if (self->f90 == 1 || self->f94 == 1)
            fn_801E00EC(self);
        if (self->state == 0)
            fn_801E00EC(self);
        break;
    case 20:
        ratio = fn_8007C3EC(&self->boss) / fn_8007C52C(&self->boss);
        if (ratio < 0.25f && self->active == 1 && self->f8C == 0 && self->f90 == 0) {
            fn_801DFED8(self);
            break;
        }
        fn_8007D404(self, self->fB4, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 50:
        self->f8C = 0;
        break;
    case 60:
        if (self->f88) {
            Ref8 p;

            fn_8046B638(&p, fn_80080B34());
            fn_8007C594(&p, 10.0f, 4, 0, 0, 2);
            Vector at;
            fn_80082440(&self->r30[2], &at);
            if (fn_800809CC(&p))
                fn_80085954(fn_800809CC(&p))->s37(0x6c, &at, 1, 1.0f, 0, 0, 1, 0);
            fn_8007D404(self, self->fD4, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
        break;
    case 70:
        if (self->f84) {
            fn_8007C6D0(&self->boss, 5.0f);
            if (fn_8007C52C(&self->boss) > fn_8007C3EC(&self->boss))
                fn_8007C454(&self->boss, fn_8007C3EC(&self->boss) + 5.0f);
            if (fn_8007C244(&self->boss) > fn_8007C2AC(&self->boss))
                fn_8007C314(&self->boss, fn_8007C2AC(&self->boss) + 5.0f);
            fn_8007D404(self, self->fD4, 70, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
        break;
    case 80:
        fn_801E00EC(self);
        break;
    case 90:
        if (self->f94 == 1 && self->f84 == 1) {
            if (fn_8007C0AC(&self->boss) >= fn_8007C244(&self->boss)) {
                if (fn_8007C3EC(&self->boss) >= fn_8007C52C(&self->boss)) {
                    fn_801E00EC(self);
                    break;
                }
                fn_8007D404(self, self->fD4, 90, 0.0f, 0.0f, 0.0f, 0.0f, 0);
                break;
            }
            fn_8007D404(self, self->fD4, 90, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            break;
        }
        break;
    case 95:
        break;
    case 85:
        fn_80082AFC(&self->r30[3], fn_801E3E30(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 75:
        fn_801DFDCC(self);
        break;
    case 52:
        fn_801E01EC(self);
        break;
    case 54:
        fn_801E0294(self);
        break;
    case 56:
        fn_801E0328(self);
        break;
    case 58:
        fn_801E0390(self);
        break;
    case 100: {
        if (self->fA4)
            return;
        Ref8 r1;
        Ref8 r2;
        Ref8 r3;

        fn_8046B5F0(&r1, fn_804425F8(&self->r30[4]));
        fn_8046B5F0(&r2, fn_804425F8(&self->r30[5]));
        fn_8046B5F0(&r3, fn_804425F8(&self->r30[6]));
        if (!fn_80080EFC(&r1))
            self->f98 = 1;
        if (!fn_80080EFC(&r2))
            self->f9C = 1;
        if (!fn_80080EFC(&r3))
            self->fA0 = 1;
        if (self->f98 && self->f9C && self->fA0) {
            self->fA4 = 1;
            fn_8007D7C4(self, 75);
            fn_8007D404(self, 2.0f, 75, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        } else
            fn_8007D404(self, 2.0f, 100, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
        break;
    }
    }
}

float fn_801DF4BC(register cPowerPlant_IronMan_3 *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h == fn_804425F8(&self->boss))
        fn_8007D404(self, self->fB0, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    return damage;
}

int fn_801DF564(register cPowerPlant_IronMan_3 *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    fn_8007D7C4(self, 10);
    fn_8007D7C4(self, 20);
    fn_8007D7C4(self, 90);
    fn_8007D7C4(self, 60);
    fn_8007D7C4(self, 70);
    return 1;
}

void fn_801DF5F0(register cPowerPlant_IronMan_3 *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (h == fn_80080B34() || h == fn_804425F8(&self->boss)) {
        if (self->done && h != fn_80080B34())
            return;
        self->done = 1;
        fn_8007D7C4(self, 10);
        fn_8007D7C4(self, 20);
        fn_8007D7C4(self, 90);
        fn_8007D7C4(self, 60);
        fn_8007D7C4(self, 70);
        fn_80081C68();
        fn_80081C94();
        fn_80081CC4();
        fn_80081B40(fn_804425F8(&self->boss));
        if (h == fn_804425F8(&self->boss)) {
            fn_80081A54(fn_80080B34());
            fn_801E01EC(self);
        } else
            fn_801E0328(self);
    }
    if (h == fn_804425F8(&self->r30[4]))
        self->f98 = 1;
    if (h == fn_804425F8(&self->r30[5]))
        self->f9C = 1;
    if (h == fn_804425F8(&self->r30[6]))
        self->fA0 = 1;
    if (self->f98 == 1 && self->f9C == 1 && self->fA0 == 1 && self->fA4 == 0) {
        fn_8007D7C4(self, 100);
        fn_8007D404(self, 2.0f, 75, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
    return;
}

void fn_801DF81C(register cPowerPlant_IronMan_3 *self, int h, int other, int value) // slot 18
{
    if (h == fn_804425F8(&self->r30[4]))
        self->f98 = 1;
    if (h == fn_804425F8(&self->r30[5]))
        self->f9C = 1;
    if (h == fn_804425F8(&self->r30[6]))
        self->fA0 = 1;
    if (self->f98 == 1 && self->f9C == 1 && self->fA0 == 1 && self->fA4 == 0) {
        fn_8007D7C4(self, 100);
        fn_8007D404(self, 2.0f, 75, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
    return;
}

void fn_801DF93C(register cPowerPlant_IronMan_3 *self, int h, int other, int value) // slot 14
{
    if (h == fn_804425F8(&self->r30[2])) {
        if (other == fn_804425F8(&self->boss) && self->active == 1 && self->f84 == 0) {
            self->f84 = 1;
            if (self->f90 == 0) {
                float a = fn_8007C0AC(&self->boss) / fn_8007C244(&self->boss);
                float b = fn_8007C3EC(&self->boss) / fn_8007C52C(&self->boss);

                if (a < 0.75f || b < 0.75f)
                    fn_801DFED8(self);
            }
        }
        Ref8 p;

        fn_8046B638(&p, fn_80080B34());
        if (other == fn_804425F8(&p) && self->active == 1 && self->f88 == 0) {
            self->f88 = 1;
            Ref8 q;

            fn_8046B638(&q, fn_80080B34());
            fn_8007C594(&q, 10.0f, 4, 0, 0, 2);
            Vector at;
            fn_80082440(&self->r30[2], &at);
            if (fn_800809CC(&q))
                fn_80085954(fn_800809CC(&q))->s37(0x6c, &at, 1, 1.0f, 0, 0, 1, 0);
            fn_8007D404(self, self->fD4, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
    }
}

void fn_801DFBD8(register cPowerPlant_IronMan_3 *self, int h, int other, int value) // slot 15
{
    if (h == fn_804425F8(&self->r30[2])) {
        if (other == fn_804425F8(&self->boss)) {
            self->f84 = 0;
            fn_801E00EC(self);
        }
        Ref8 p;

        fn_8046B638(&p, fn_80080B34());
        if (other == fn_804425F8(&p))
            self->f88 = 0;
    }
}

float fn_801DFC98(register cPowerPlant_IronMan_3 *self, int h, int node, int value) // slot 37
{
    if (h == fn_804425F8(&self->boss) && self->f90 == 1) {
        fn_8007D7C4(self, 20);
        fn_8007D7C4(self, 80);
        self->f90 = 0;
        self->f94 = 1;
        fn_801E0004(self);
    }
    return -1.0f;
}

void fn_801DFD38(register cPowerPlant_IronMan_3 *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (self->state == 0)
        fn_8007D404(self, 2.0f, 80, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801DFDCC(register cPowerPlant_IronMan_3 *self)
{
    fn_8007D7C4(self, 100);
    self->fA4 = 1;
    if (self->active == 1) {
        fn_8007D404(self, 2.0f, 85, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        fn_80082AFC(&self->r30[8], fn_801E3F98(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    fn_8007D7C4(self, 20);
    fn_801E00EC(self);
    self->active = 0;
    self->f84 = 0;
    self->f88 = 0;
    self->state = 5;
}

void fn_801DFED8(register cPowerPlant_IronMan_3 *self)
{
    fn_8007A4FC(fn_804425F8(&self->boss));
    Vector at;

    fn_80082440(&self->r30[1], &at);
    fn_8007D7C4(self, 20);
    fn_8007D7C4(self, 10);
    fn_8007D404(self, self->fD8, 80, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007D404(self, self->fCC, 50, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    self->f8C = 1;
    self->f90 = 1;
    self->state = 2;
    fn_8007A448(fn_804425F8(&self->boss));
    fn_8007A738(fn_804425F8(&self->boss), &at);
}

void fn_801E0004(register cPowerPlant_IronMan_3 *self)
{
    fn_8007B618(fn_804425F8(&self->boss), 1);
    fn_80082E24(&self->boss, "ppMegCharge");
    fn_8007D404(self, self->fD4, 70, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007BAA0(fn_804425F8(&self->boss));
    fn_8007D404(self, self->fD4, 90, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    self->state = 3;
}

void fn_801E00EC(register cPowerPlant_IronMan_3 *self)
{
    fn_8007A4FC(fn_804425F8(&self->boss));
    fn_8007BB24(fn_804425F8(&self->boss));
    fn_8007B618(fn_804425F8(&self->boss), 0);
    fn_80083428(&self->boss, "ppMegCharge");
    fn_8007D7C4(self, 80);
    self->f94 = 0;
    self->f90 = 0;
    self->state = 1;
    fn_8007D7C4(self, 20);
    if (self->active == 1)
        fn_8007D404(self, self->fB4, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801E01EC(register cPowerPlant_IronMan_3 *self)
{
    fn_8007D404(self, 3.0f, 54, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8046B860(lbl_8057230C, 1);
}

void fn_801E0294(register cPowerPlant_IronMan_3 *self)
{
    fn_80081918(fn_80080B34());
    fn_80082AFC(&self->r30[0], fn_804425F8(&self->r30[0]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801E0328(register cPowerPlant_IronMan_3 *self)
{
    fn_8007D404(self, 2.0f, 58, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801E0390(register cPowerPlant_IronMan_3 *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    fn_8046B6C8(&ev, fn_801E3FE0(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}


void fn_801E043C(register cPowerPlant_Venom_3 *self) // slot 5
{
    fn_8046B710(&self->boss, fn_800797D4(self));
    fn_8046B710(&self->r30[0], fn_801E407C(self));
    fn_8046B710(&self->rB0, fn_801E44B4(self));
    fn_8046B710(&self->r30[1], fn_801E40C4(self));
    fn_8046B710(&self->r30[2], fn_801E410C(self));
    fn_8046B710(&self->r30[3], fn_801E4154(self));
    fn_8046B710(&self->r30[4], fn_801E419C(self));
    fn_8046B710(&self->r30[5], fn_801E41E4(self));
    fn_8046B710(&self->r30[6], fn_801E422C(self));
    fn_8046B710(&self->r30[7], fn_801E4274(self));
    fn_8046B710(&self->r30[8], fn_801E42BC(self));
    fn_8046B710(&self->r30[9], fn_801E4304(self));
    fn_8046B710(&self->r30[10], fn_801E434C(self));
    fn_8046B710(&self->r30[11], fn_801E4394(self));
    fn_8046B710(&self->r30[12], fn_801E43DC(self));
    fn_8046B710(&self->rA0, fn_801E4424(self));
    fn_8046B710(&self->rA8, fn_801E446C(self));
    fn_8007CF00(self, fn_804425F8(&self->boss), 0);
    fn_8007CF00(self, fn_804425F8(&self->r30[2]), 0);
    fn_8007CF00(self, fn_804425F8(&self->r30[6]), 0);
    fn_8007CF00(self, fn_804425F8(&self->r30[10]), 0);
    fn_8007CF00(self, fn_80080B34(), 0);
    self->fC0 = 0.5f;
    self->fC4 = -1.0f;
    self->fBC = 10.0f;
    self->fB8 = 3.0f;
    self->fC8 = 0.25f;
    self->fCC = 10.0f;
    self->fD0 = 1.0f;
    self->mode = 0;
    self->zone = 0;
    self->prevZone = 0;
    self->count = 0;
    self->fE4 = 0;
    self->fE8 = 0;
    self->fF0 = 0;
    self->fEC = 0;
    self->a[0] = 0;
    self->b[0] = 0;
    self->c[0] = 0;
    self->a[1] = 0;
    self->b[1] = 0;
    self->c[1] = 0;
    self->a[2] = 0;
    self->b[2] = 0;
    self->c[2] = 0;
    self->a[3] = 0;
    self->b[3] = 0;
    self->c[3] = 0;
    self->a[4] = 0;
    self->b[4] = 0;
    self->c[4] = 0;
    self->done = 0;
    fn_8007D404(self, self->fB8, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801E0828(register cPowerPlant_Venom_3 *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10: {
        float hp = fn_8007C0AC(&self->boss) / fn_8007C244(&self->boss);
        float ar = fn_8007C3EC(&self->boss) / fn_8007C52C(&self->boss);

        if (hp <= self->fC0 || ar <= self->fC4) {
            self->fE8 = 1;
            if (self->mode != 2) {
                if (self->a[1] == 1 || self->b[1] == 1 || self->c[1] == 1) {
                    if (self->a[1] == 1 && self->a[4] == 0 && self->zone == 1) {
                        fn_8046B710(&self->r98, fn_804425F8(&self->r30[1]));
                        fn_801E1A94(self);
                    }
                    if (self->b[1] == 1 && self->b[4] == 0 && self->zone == 2) {
                        fn_8046B710(&self->r98, fn_804425F8(&self->r30[5]));
                        fn_801E1A94(self);
                    }
                    if (self->c[1] == 1 && self->c[4] == 0 && self->zone == 3) {
                        fn_8046B710(&self->r98, fn_804425F8(&self->r30[9]));
                        fn_801E1A94(self);
                    }
                } else {
                    fn_801E1C58(self);
                    fn_801E1A94(self);
                }
            }
        }
        fn_8007D404(self, self->fB8, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
    case 20:
        fn_801E19F8(self);
        break;
    case 30: {
        float hp = fn_8007C0AC(&self->boss) / fn_8007C244(&self->boss);
        float ar = fn_8007C3EC(&self->boss) / fn_8007C52C(&self->boss);

        if (self->count <= 16) {
            fn_8007C6D0(&self->boss, 1.25f);
            if (fn_8007C52C(&self->boss) >= fn_8007C3EC(&self->boss))
                fn_8007C454(&self->boss, fn_8007C3EC(&self->boss) + 1.25f);
            if (fn_8007C244(&self->boss) >= fn_8007C2AC(&self->boss))
                fn_8007C314(&self->boss, fn_8007C2AC(&self->boss) + 1.25f);
            self->count++;
            fn_8007D404(self, self->fC8, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        } else {
            self->count = 0;
            self->fE8 = 0;
            if (self->zone == 1) {
                self->a[4] = 1;
                float r = fn_80171F8C() * 4.656612873077392578125e-10f;

                if (r <= 0.5) {
                    self->prevZone = 1;
                    self->zone = 2;
                } else {
                    self->prevZone = 1;
                    self->zone = 3;
                }
                fn_801E1D0C(self);
            } else if (self->zone == 2) {
                self->b[4] = 1;
                if (self->c[4] == 0) {
                    self->prevZone = 2;
                    self->zone = 3;
                } else
                    self->zone = 0;
                fn_801E1D0C(self);
            } else if (self->zone == 3) {
                self->c[4] = 1;
                if (self->b[4] == 0) {
                    self->prevZone = 3;
                    self->zone = 2;
                } else
                    self->zone = 0;
                fn_801E1D0C(self);
            }
            fn_801E19F8(self);
        }
        break;
    }
    case 50:
        fn_801E19F8(self);
        break;
    case 60: {
        Ref8 p;

        fn_8046B638(&p, fn_80080B34());
        if (self->a[2] == 1 && self->a[0] == 1) {
            fn_8007C594(&p, 10.0f, 2, 0, 0, 2);
            fn_8007D404(self, self->fC8, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
        if (self->b[2] == 1 && self->b[0] == 1) {
            fn_8007C594(&p, 10.0f, 2, 0, 0, 2);
            fn_8007D404(self, self->fC8, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
        if (self->c[2] == 1 && self->c[0] == 1) {
            fn_8007C594(&p, 10.0f, 2, 0, 0, 2);
            fn_8007D404(self, self->fC8, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
        break;
    }
    case 70:
        self->prevZone = self->zone;
        fn_801E1D0C(self);
        fn_801E1EF4(self);
        fn_8007D404(self, self->fC8, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 72:
        fn_801E22C4(self);
        break;
    case 74:
        fn_801E2374(self);
        break;
    case 76:
        fn_801E2410(self);
        break;
    case 78:
        fn_801E2480(self);
        break;
    }
}

float fn_801E0F98(register cPowerPlant_Venom_3 *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h == fn_804425F8(&self->boss))
        fn_8007D404(self, 0.1f, 50, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    return damage;
}

int fn_801E1044(register cPowerPlant_Venom_3 *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    if (h == fn_804425F8(&self->boss) || h == fn_80080B34()) {
        fn_8007D7C4(self, 60);
        fn_8007D7C4(self, 50);
        fn_8007D7C4(self, 30);
        fn_8007D7C4(self, 10);
        fn_8007D7C4(self, 20);
    }
    return 1;
}

void fn_801E1104(register cPowerPlant_Venom_3 *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (h == fn_804425F8(&self->boss) || h == fn_80080B34()) {
        if (self->done == 1 && h != fn_80080B34())
            return;
        self->done = 1;
        fn_8007D7C4(self, 60);
        fn_8007D7C4(self, 50);
        fn_8007D7C4(self, 30);
        fn_8007D7C4(self, 10);
        fn_8007D7C4(self, 20);
        fn_80081C68();
        fn_80081C94();
        fn_80081CC4();
        fn_80081B40(fn_804425F8(&self->boss));
        if (h == fn_804425F8(&self->boss)) {
            fn_80081A54(fn_80080B34());
            fn_801E22C4(self);
        } else
            fn_801E2410(self);
    }
    return;
}

void fn_801E1250(register cPowerPlant_Venom_3 *self, int h, int other, int value) // slot 14
{
    if (h == fn_804425F8(&self->r30[2])) {
        if (other == fn_804425F8(&self->boss)) {
            self->a[1] = 1;
            self->b[1] = 0;
            self->c[1] = 0;
            if (self->mode == 0 && self->a[4] == 0) {
                float hp = fn_8007C0AC(&self->boss) / fn_8007C244(&self->boss);
                float ar = fn_8007C3EC(&self->boss) / fn_8007C52C(&self->boss);

                if (hp <= self->fC0 || ar <= self->fC4) {
                    fn_8007D7C4(self, 20);
                    fn_8046B710(&self->r98, fn_804425F8(&self->r30[1]));
                    fn_801E1A94(self);
                }
            }
        }
        if (other == fn_80080B34()) {
            self->a[2] = 1;
            self->b[2] = 0;
            self->c[2] = 0;
            if (self->a[0] == 1)
                fn_8007D404(self, self->fC8, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
    }
    if (h == fn_804425F8(&self->r30[6])) {
        if (other == fn_804425F8(&self->boss)) {
            self->a[1] = 0;
            self->b[1] = 1;
            self->c[1] = 0;
            if (self->mode == 0 && self->b[4] == 0 && self->a[4] == 1) {
                float hp = fn_8007C0AC(&self->boss) / fn_8007C244(&self->boss);
                float ar = fn_8007C3EC(&self->boss) / fn_8007C52C(&self->boss);

                if (hp <= self->fC0 || ar <= self->fC4) {
                    fn_8007D7C4(self, 20);
                    fn_8046B710(&self->r98, fn_804425F8(&self->r30[5]));
                    fn_801E1A94(self);
                }
            }
        }
        if (other == fn_80080B34()) {
            self->a[2] = 0;
            self->b[2] = 1;
            self->c[2] = 0;
            if (self->b[0] == 1)
                fn_8007D404(self, self->fC8, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
    }
    if (h == fn_804425F8(&self->r30[10])) {
        if (other == fn_804425F8(&self->boss)) {
            self->a[1] = 0;
            self->b[1] = 0;
            self->c[1] = 1;
            if (self->mode == 0 && self->c[4] == 0 && self->a[4] == 1) {
                float hp = fn_8007C0AC(&self->boss) / fn_8007C244(&self->boss);
                float ar = fn_8007C3EC(&self->boss) / fn_8007C52C(&self->boss);

                if (hp <= self->fC0 || ar <= self->fC4) {
                    fn_8007D7C4(self, 20);
                    fn_8046B710(&self->r98, fn_804425F8(&self->r30[9]));
                    fn_801E1A94(self);
                }
            }
        }
        if (other == fn_80080B34()) {
            self->a[2] = 0;
            self->b[2] = 0;
            self->c[2] = 1;
            if (self->c[0] == 1)
                fn_8007D404(self, self->fC8, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
    }
}

void fn_801E1738(register cPowerPlant_Venom_3 *self, int h, int other, int value) // slot 15
{
    if (h == fn_804425F8(&self->r30[2])) {
        if (other == fn_804425F8(&self->boss))
            self->a[1] = 0;
        if (other == fn_80080B34())
            self->a[2] = 0;
    }
    if (h == fn_804425F8(&self->r30[6])) {
        if (other == fn_804425F8(&self->boss))
            self->b[1] = 0;
        if (other == fn_80080B34())
            self->b[2] = 0;
    }
    if (h == fn_804425F8(&self->r30[10])) {
        if (other == fn_804425F8(&self->boss))
            self->c[1] = 0;
        if (other == fn_80080B34())
            self->c[2] = 0;
    }
}

float fn_801E1888(register cPowerPlant_Venom_3 *self, int h, int node, int value) // slot 37
{
    if (self->mode == 1) {
        fn_8007D7C4(self, 20);
        if (self->a[1] == 1 || self->b[1] == 1 || self->c[1] == 1)
            fn_801E1B7C(self);
    }
    return -1.0f;
}

void fn_801E1918(register cPowerPlant_Venom_3 *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (b == fn_804425F8(&self->rA0) || b == fn_804425F8(&self->rA8)) {
        if (self->fEC == 0) {
            self->fEC = 1;
            self->zone = 1;
            fn_801E1EF4(self);
        }
        if (self->fF0 == 0 && b == fn_804425F8(&self->rA8))
            self->fF0 = 1;
    }
}

void fn_801E19F8(register cPowerPlant_Venom_3 *self)
{
    self->mode = 0;
    fn_8007D7C4(self, 20);
    fn_8007D7C4(self, 30);
    fn_8007B618(fn_804425F8(&self->boss), 0);
    fn_8007A4FC(fn_804425F8(&self->boss));
    fn_8007BB24(fn_804425F8(&self->boss));
}

void fn_801E1A94(register cPowerPlant_Venom_3 *self)
{
    if (self->zone == 0) {
        fn_801E19F8(self);
        return;
    }
    self->mode = 1;
    fn_8007A4FC(fn_804425F8(&self->boss));
    Vector at;

    fn_80082440(&self->r98, &at);
    fn_8007D404(self, self->fBC, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007A448(fn_804425F8(&self->boss));
    fn_8007A738(fn_804425F8(&self->boss), &at);
}

void fn_801E1B7C(register cPowerPlant_Venom_3 *self)
{
    self->mode = 2;
    fn_8007D7C4(self, 20);
    fn_8007A4FC(fn_804425F8(&self->boss));
    fn_8007B618(fn_804425F8(&self->boss), 1);
    fn_8007A448(fn_804425F8(&self->boss));
    fn_8007BAA0(fn_804425F8(&self->boss));
    fn_8007D404(self, self->fD0, 70, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801E1C58(register cPowerPlant_Venom_3 *self)
{
    if (self->zone == 1)
        fn_8046B710(&self->r98, fn_804425F8(&self->r30[1]));
    if (self->zone == 2)
        fn_8046B710(&self->r98, fn_804425F8(&self->r30[5]));
    if (self->zone == 3)
        fn_8046B710(&self->r98, fn_804425F8(&self->r30[9]));
}

void fn_801E1D0C(register cPowerPlant_Venom_3 *self)
{
    if (self->prevZone != self->zone) {
        switch (self->prevZone) {
        case 0:
            break;
        case 1:
            self->a[0] = 0;
            fn_80082AFC(&self->r30[3], fn_804425F8(&self->r30[3]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            if (self->a[2] == 1)
                fn_8007D7C4(self, 60);
            break;
        case 2:
            self->b[0] = 0;
            fn_80082AFC(&self->r30[7], fn_804425F8(&self->r30[7]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            if (self->b[2] == 1)
                fn_8007D7C4(self, 60);
            break;
        case 3:
            self->c[0] = 0;
            fn_80082AFC(&self->r30[11], fn_804425F8(&self->r30[11]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            if (self->c[2] == 1)
                fn_8007D7C4(self, 60);
            break;
        }
    }
}

void fn_801E1EF4(register cPowerPlant_Venom_3 *self)
{
    switch (self->zone) {
    case 0:
        break;
    case 1:
        if (self->a[0] == 0 && self->a[4] == 0) {
            if (self->a[3] == 0) {
                fn_80082AFC(&self->r30[4], fn_804425F8(&self->r30[4]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
                self->a[3] = 1;
            }
            fn_80082AFC(&self->r30[3], fn_804425F8(&self->r30[3]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            self->a[0] = 1;
            if (self->a[2] == 1)
                fn_8007D404(self, self->fC8, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
        break;
    case 2:
        if (self->b[0] == 0 && self->b[4] == 0) {
            if (self->b[3] == 0) {
                fn_80082AFC(&self->r30[8], fn_804425F8(&self->r30[8]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
                self->b[3] = 1;
            }
            fn_80082AFC(&self->r30[7], fn_804425F8(&self->r30[7]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            self->b[0] = 1;
            if (self->b[2] == 1)
                fn_8007D404(self, self->fC8, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
        break;
    case 3:
        if (self->c[0] == 0 && self->c[4] == 0) {
            if (self->c[3] == 0) {
                fn_80082AFC(&self->r30[12], fn_804425F8(&self->r30[12]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
                self->c[3] = 1;
            }
            fn_80082AFC(&self->r30[11], fn_804425F8(&self->r30[11]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            self->c[0] = 1;
            if (self->c[2] == 1)
                fn_8007D404(self, self->fC8, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
        break;
    }
}

void fn_801E22C4(register cPowerPlant_Venom_3 *self)
{
    fn_8007D404(self, 3.0f, 74, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_80572278, 1);
}

void fn_801E2374(register cPowerPlant_Venom_3 *self)
{
    fn_80081918(fn_80080B34());
    fn_80082AFC(&self->r30[0], fn_804425F8(&self->r30[0]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801E2410(register cPowerPlant_Venom_3 *self)
{
    fn_8007D404(self, 2.0f, 78, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801E2480(register cPowerPlant_Venom_3 *self)
{
    fn_80081918(fn_804425F8(&self->boss));
    fn_80082AFC(&self->rB0, fn_804425F8(&self->rB0), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}


void fn_801E2524(register cPowerPlant_CoilToggle *self) // slot 3
{
    self->hit = 0;
    self->on = 0;
}

void fn_801E255C(register cPowerPlant_CoilToggle *self) // slot 4
{
    Ref8 ev;

    fn_8046B6C8(&ev, fn_801E4550(self));
    fn_80082440(&ev, &self->pos);
}

void fn_801E25BC(register cPowerPlant_CoilToggle *self, int h, int other, int value) // slot 18
{
    if (h == fn_800797D4(self))
        self->hit = 1;
}

float fn_801E2620(register cPowerPlant_CoilToggle *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h != fn_800797D4(self) || self->hit != 0)
        return damage;
    Ref8 ev;

    fn_8046B6C8(&ev, fn_801E4550(self));
    Vector at;
    fn_80082440(&ev, &at);
    if (fn_8042FB28(&at) != fn_8042FB28(&self->pos))
        self->hit = 1;
    return damage;
}

void fn_801E2718(register cPowerPlant_CoilToggle *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (h == fn_800797D4(self))
        self->hit = 1;
}

void fn_801E2780(register cPowerPlant_CoilToggle *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (self->hit != 0)
        return;
    fn_801E27FC(self, !self->on);
}

void fn_801E27FC(register cPowerPlant_CoilToggle *self, int on)
{
    Ref8 ev;

    fn_8046B5F0(&ev, fn_801E4550(self));
    if (on) {
        if (fn_801E4594(self)) {
            fn_80082E24(&ev, "ppCoreArc");
            fn_80082BB0(&ev, "ppCoreArc", fn_801E4594(self));
        }
    } else {
        if (fn_801E4594(self))
            fn_80083428(&ev, "ppCoreArc");
    }
    self->on = on;
}

void fn_801E28D8(register cPowerPlant_CoilArc *self) // slot 3
{
    self->idle[0] = 1;
    self->idle[1] = 1;
    self->idle[2] = 1;
    self->idle[3] = 1;
    self->idle[4] = 1;
    self->idle[5] = 1;
    self->idle[6] = 1;
    self->idle[7] = 1;
}

void fn_801E2938(register cPowerPlant_CoilArc *self) // slot 4
{
    if (fn_801E4630(self)) {
        fn_8007CF00(self, fn_801E4630(self), 0);
        fn_8046B710(&self->coil[0], fn_801E4630(self));
        fn_8007D404(self, fn_80171F8C() * 4.656612873077392578125e-10f * 15.0f + 10.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, fn_801E4630(self));
    }
    if (fn_801E4678(self)) {
        fn_8007CF00(self, fn_801E4678(self), 0);
        fn_8046B710(&self->coil[1], fn_801E4678(self));
        fn_8007D404(self, fn_80171F8C() * 4.656612873077392578125e-10f * 15.0f + 10.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, fn_801E4678(self));
    }
    if (fn_801E46C0(self)) {
        fn_8007CF00(self, fn_801E46C0(self), 0);
        fn_8046B710(&self->coil[2], fn_801E46C0(self));
        fn_8007D404(self, fn_80171F8C() * 4.656612873077392578125e-10f * 15.0f + 10.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, fn_801E46C0(self));
    }
    if (fn_801E4708(self)) {
        fn_8007CF00(self, fn_801E4708(self), 0);
        fn_8046B710(&self->coil[3], fn_801E4708(self));
        fn_8007D404(self, fn_80171F8C() * 4.656612873077392578125e-10f * 15.0f + 10.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, fn_801E4708(self));
    }
    if (fn_801E4750(self)) {
        fn_8007CF00(self, fn_801E4750(self), 0);
        fn_8046B710(&self->coil[4], fn_801E4750(self));
        fn_8007D404(self, fn_80171F8C() * 4.656612873077392578125e-10f * 15.0f + 10.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, fn_801E4750(self));
    }
    if (fn_801E4798(self)) {
        fn_8007CF00(self, fn_801E4798(self), 0);
        fn_8046B710(&self->coil[5], fn_801E4798(self));
        fn_8007D404(self, fn_80171F8C() * 4.656612873077392578125e-10f * 15.0f + 10.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, fn_801E4798(self));
    }
    if (fn_801E47E0(self)) {
        fn_8007CF00(self, fn_801E47E0(self), 0);
        fn_8046B710(&self->coil[6], fn_801E47E0(self));
        fn_8007D404(self, fn_80171F8C() * 4.656612873077392578125e-10f * 15.0f + 10.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, fn_801E47E0(self));
    }
    if (fn_801E4828(self)) {
        fn_8007CF00(self, fn_801E4828(self), 0);
        fn_8046B710(&self->coil[7], fn_801E4828(self));
        fn_8007D404(self, fn_80171F8C() * 4.656612873077392578125e-10f * 15.0f + 10.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, fn_801E4828(self));
    }
}

void fn_801E3050(register cPowerPlant_CoilArc *self, int h, int other, int value) // slot 18
{
    fn_801E3A24(self, h);
    if (h == fn_804425F8(&self->coil[0]))
        self->idle[0] = 0;
    else if (h == fn_804425F8(&self->coil[1]))
        self->idle[1] = 0;
    else if (h == fn_804425F8(&self->coil[2]))
        self->idle[2] = 0;
    else if (h == fn_804425F8(&self->coil[3]))
        self->idle[3] = 0;
    else if (h == fn_804425F8(&self->coil[4]))
        self->idle[4] = 0;
    else if (h == fn_804425F8(&self->coil[5]))
        self->idle[5] = 0;
    else if (h == fn_804425F8(&self->coil[6]))
        self->idle[6] = 0;
    else if (h == fn_804425F8(&self->coil[7]))
        self->idle[7] = 0;
}

void fn_801E31D4(register cPowerPlant_CoilArc *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    fn_801E3A24(self, h);
    if (h == fn_804425F8(&self->coil[0]))
        self->idle[0] = 0;
    else if (h == fn_804425F8(&self->coil[1]))
        self->idle[1] = 0;
    else if (h == fn_804425F8(&self->coil[2]))
        self->idle[2] = 0;
    else if (h == fn_804425F8(&self->coil[3]))
        self->idle[3] = 0;
    else if (h == fn_804425F8(&self->coil[4]))
        self->idle[4] = 0;
    else if (h == fn_804425F8(&self->coil[5]))
        self->idle[5] = 0;
    else if (h == fn_804425F8(&self->coil[6]))
        self->idle[6] = 0;
    else if (h == fn_804425F8(&self->coil[7]))
        self->idle[7] = 0;
}

void fn_801E3364(register cPowerPlant_CoilArc *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10: {
        if ((e == fn_801E4630(self) && self->idle[0] == 0) || (e == fn_801E4678(self) && self->idle[1] == 0)
            || (e == fn_801E46C0(self) && self->idle[2] == 0) || (e == fn_801E4708(self) && self->idle[3] == 0)
            || (e == fn_801E4750(self) && self->idle[4] == 0) || (e == fn_801E4798(self) && self->idle[5] == 0)
            || (e == fn_801E47E0(self) && self->idle[6] == 0) || (e == fn_801E4828(self) && self->idle[7] == 0))
            return;
        int target = fn_801E37AC(self, e);

        if (!target)
            fn_8007D404(self, 2.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, e);
        if (fn_801E365C(self, e, target))
            fn_8007D404(self, 1.5f, 20, 0.0f, 0.0f, 0.0f, 0.0f, e);
        break;
    }
    case 20:
        fn_801E3A24(self, e);
        fn_8007D404(self, fn_80171F8C() * 4.656612873077392578125e-10f * 10.0f + 10.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, e);
        break;
    }
}

int fn_801E365C(register cPowerPlant_CoilArc *self, int from, int to)
{
    if (!from || !to)
        return 0;
    Ref8 a;
    Ref8 b;

    fn_8046B6C8(&a, from);
    fn_8046B6C8(&b, to);
    SObj *o = fn_80081E6C(&a);
    if (o) {
        Arc *arc = fn_803A20D8(lbl_8064AA80, "ppCoreArc", o, 0, 0, 0, 0, 0.0f);

        if (arc) {
            arc->v31(fn_804425F8(&b));
            fn_80393938(o, arc, 1);
            return 1;
        }
    }
    return 0;
}

int fn_801E37AC(register cPowerPlant_CoilArc *self, int h)
{
    Query q;

    fn_8004E9C8(&q);
    fn_80434C88(&q);
    fn_80434CDC(&q, 2);
    Ref8 ev;
    fn_8046B6C8(&ev, h);
    fn_80434D18(&q, fn_80081E6C(&ev));
    Vector at;
    fn_80082440(&ev, &at);
    Ref8 r;
    fn_8046C1E8(&r, fn_8046C160(&ev));
    if (!fn_80081274(&r))
        return 0;
    fn_8004E4B4(&q, &at, 7.0f, fn_80081274(&r));
    if (q.count == 0)
        return 0;
    Slot *s;
    int e;
    unsigned int i;

    i = fn_80171F8C() * 4.656612873077392578125e-10f * q.count;
    i = i <? q.count - 1;
    s = &q.slot[i];
    if (!s || !fn_8043536C(s))
        return 0;
    e = fn_80434C2C(s);
    return fn_800B13D8(e);
}

void fn_801E3A24(register cPowerPlant_CoilArc *self, int h)
{
    Ref8 ev;

    fn_8046B6C8(&ev, h);
    SObj *o = fn_80081E6C(&ev);
    if (!o)
        return;
    Arc *arc = fn_80393A60(o, "ppCoreArc", 0);
    if (!arc)
        return;
    arc->v54();
}

inline int sn_return_decl2(int a) { return a; }

cScript *fn_801E3AF4(register cPowerPlant_HumanTorchSAC *self)
{
    return new cPowerPlant_HumanTorchSAC;
}

unsigned int fn_801E3B48(register cPowerPlant_HumanTorchSAC *self) { return fn_800791C8(self, 0); }
unsigned int fn_801E3B90(register cPowerPlant_HumanTorchSAC *self) { return fn_800791C8(self, 1); }
unsigned int fn_801E3BD8(register cPowerPlant_HumanTorchSAC *self) { return fn_800791C8(self, 2); }

cScript *fn_801E3C20(register cPowerPlant_ElektraSAC *self)
{
    return new cPowerPlant_ElektraSAC;
}

unsigned int fn_801E3C74(register cPowerPlant_ElektraSAC *self) { return fn_800791C8(self, 0); }
unsigned int fn_801E3CBC(register cPowerPlant_ElektraSAC *self) { return fn_800791C8(self, 1); }

cScript *fn_801E3D04(register cPowerPlant_IronMan_3 *self)
{
    return new cPowerPlant_IronMan_3;
}

unsigned int fn_801E3D58(register cPowerPlant_IronMan_3 *self) { return fn_800791C8(self, 0); }
unsigned int fn_801E3DA0(register cPowerPlant_IronMan_3 *self) { return fn_800791C8(self, 1); }
unsigned int fn_801E3DE8(register cPowerPlant_IronMan_3 *self) { return fn_800791C8(self, 2); }
unsigned int fn_801E3E30(register cPowerPlant_IronMan_3 *self) { return fn_800791C8(self, 3); }
unsigned int fn_801E3E78(register cPowerPlant_IronMan_3 *self) { return fn_800791C8(self, 4); }
unsigned int fn_801E3EC0(register cPowerPlant_IronMan_3 *self) { return fn_800791C8(self, 5); }
unsigned int fn_801E3F08(register cPowerPlant_IronMan_3 *self) { return fn_800791C8(self, 6); }
unsigned int fn_801E3F50(register cPowerPlant_IronMan_3 *self) { return fn_800791C8(self, 7); }
unsigned int fn_801E3F98(register cPowerPlant_IronMan_3 *self) { return fn_800791C8(self, 8); }
unsigned int fn_801E3FE0(register cPowerPlant_IronMan_3 *self) { return fn_800791C8(self, 9); }

cScript *fn_801E4028(register cPowerPlant_Venom_3 *self)
{
    return new cPowerPlant_Venom_3;
}

unsigned int fn_801E407C(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 0); }
unsigned int fn_801E40C4(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 1); }
unsigned int fn_801E410C(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 2); }
unsigned int fn_801E4154(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 3); }
unsigned int fn_801E419C(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 4); }
unsigned int fn_801E41E4(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 5); }
unsigned int fn_801E422C(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 6); }
unsigned int fn_801E4274(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 7); }
unsigned int fn_801E42BC(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 8); }
unsigned int fn_801E4304(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 9); }
unsigned int fn_801E434C(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 10); }
unsigned int fn_801E4394(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 11); }
unsigned int fn_801E43DC(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 12); }
unsigned int fn_801E4424(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 13); }
unsigned int fn_801E446C(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 14); }
unsigned int fn_801E44B4(register cPowerPlant_Venom_3 *self) { return fn_800791C8(self, 15); }

cScript *fn_801E44FC(register cPowerPlant_CoilToggle *self)
{
    return new cPowerPlant_CoilToggle;
}


int fn_801E4550(register cPowerPlant_CoilToggle *self) { return fn_800797D4(self); }
unsigned int fn_801E4594(register cPowerPlant_CoilToggle *self) { return fn_800791C8(self, 0); }

cScript *fn_801E45DC(register cPowerPlant_CoilArc *self)
{
    return new cPowerPlant_CoilArc;
}

unsigned int fn_801E4630(register cPowerPlant_CoilArc *self) { return fn_800791C8(self, 0); }
unsigned int fn_801E4678(register cPowerPlant_CoilArc *self) { return fn_800791C8(self, 1); }
unsigned int fn_801E46C0(register cPowerPlant_CoilArc *self) { return fn_800791C8(self, 2); }
unsigned int fn_801E4708(register cPowerPlant_CoilArc *self) { return fn_800791C8(self, 3); }
unsigned int fn_801E4750(register cPowerPlant_CoilArc *self) { return fn_800791C8(self, 4); }
unsigned int fn_801E4798(register cPowerPlant_CoilArc *self) { return fn_800791C8(self, 5); }
unsigned int fn_801E47E0(register cPowerPlant_CoilArc *self) { return fn_800791C8(self, 6); }
unsigned int fn_801E4828(register cPowerPlant_CoilArc *self) { return fn_800791C8(self, 7); }

}
