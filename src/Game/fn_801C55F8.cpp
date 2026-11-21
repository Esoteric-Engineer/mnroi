// The Avengers Mansion classes cAvengersMansion_ParadoxBoss, _IM1_Start, _IronManSAC and _HideSkirt (docs/story.md row 17).
// Pool read from 0x8049F618 (extern_pool).

inline int sn_return_decl(int a) { return a; }

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

struct Mat {
    float m[16];
    Mat() __asm__("fn_8042D7B0");
};

struct SObjData {
    char pad0[0x198];
};

struct SObj : SObjData { // vptr at +0x198
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20();
    virtual int v21(); // +0xB0
};

struct SActor : SObj {
    int pad;
};

struct HkRef { // 4 bytes, returned by value
    int v;
    int fn_80436294() __asm__("fn_80436294");
};

struct SBodyBase {
    int unk0;
};

struct SBody : SBodyBase { // what fn_800B24AC returns
    int pad;
};

struct SCtlData {
    char pad0[0x3ac];
};

struct SCtl : SCtlData { // what fn_80085928 returns; vptr at +0x3AC
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual int v22(); // +0xB8
};

struct EObj {
    char pad0[0x3ac];
};

struct EBase : EObj { // vptr at +0x3AC
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int state); // +0x30
};

struct Obj : EBase { // what fn_80085954 returns
    int pad;
};

struct cAvengersMansion_ParadoxBoss : cScript { // 0xDC
    Ref8 player;    // +0x28
    Ref8 boss;      // +0x30, the entity named PARADOX
    Ref8 pt[11];    // +0x38, params 0-10
    Ref8 barrel;    // +0x90
    Ref8 r98;       // +0x98, param 11
    int zone;       // +0xA0, set by slot 14
    int fA4;        // +0xA4
    int teleports;  // +0xA8
    int fAC;        // +0xAC
    int phase;      // +0xB0
    int fB4;        // +0xB4
    int fB8;        // +0xB8
    int fBC;        // +0xBC
    int fC0;        // +0xC0
    int fC4;        // +0xC4
    int fC8;        // +0xC8
    int done;       // +0xCC
    int bossHit;    // +0xD0
    int playerHit;  // +0xD4
    int fD8;        // +0xD8
    cAvengersMansion_ParadoxBoss() __asm__("fn_8046A608");
};

struct cAvengersMansion_IM1_Start : cScript { // 0xE0
    Ref8 r28;       // +0x28, param 0
    Ref8 r30;       // +0x30, param 1
    Ref8 r38[2];    // +0x38
    Ref8 r48[4];    // +0x48, params 2-5
    Ref8 r68[8];    // +0x68
    Ref8 rA8[4];    // +0xA8, params 6-9
    Ref8 rC8;       // +0xC8, param 10
    int fD0;        // +0xD0
    int fD4;        // +0xD4
    int fD8;        // +0xD8
    int fDC;        // +0xDC
    cAvengersMansion_IM1_Start() __asm__("fn_8046A710");
};

struct cAvengersMansion_IronManSAC : cScript { // 0xA0
    Ref8 boss;      // +0x28
    Ref8 r30;       // +0x30, param 0
    Ref8 r38;       // +0x38, param 1
    Ref8 r40;       // +0x40
    Ref8 r48;       // +0x48, param 2
    Ref8 r50;       // +0x50, param 3
    Ref8 r58;       // +0x58, param 4
    int f60;        // +0x60
    int f64;        // +0x64
    int f68;        // +0x68
    int f6C;        // +0x6C
    int f70;        // +0x70
    int done;       // +0x74
    int f78;        // +0x78
    int state;      // +0x7C
    int f80;        // +0x80
    float f84;      // +0x84
    float f88;      // +0x88
    float f8C;      // +0x8C
    float f90;      // +0x90
    float f94;      // +0x94
    float f98;      // +0x98
    float charge;   // +0x9C
    cAvengersMansion_IronManSAC() __asm__("fn_8046A868");
};

struct cAvengersMansion_HideSkirt : cScript { // 0x28
    cAvengersMansion_HideSkirt() __asm__("fn_8046A90C");
};

extern char lbl_80552110[];
extern char lbl_805526EC[];
extern char lbl_80572278[];
extern char lbl_8057230C[];
extern int lbl_8066C71C;
extern int lbl_8066C724;

extern "C" {

int stricmp(const char *a, const char *b);
int Script_GetOwner(cScript *self);
unsigned int Script_GetParamUInt(cScript *self, unsigned int i);
void Script_QueueMessage(cScript *self, float seconds, int kind, float a, float b, float c, float d, int e);
int Script_CancelMessages(cScript *self, unsigned char kind);
int fn_8007D8B0(cScript *self);
int Script_LinkEntity(cScript *script, int handle, int value);
int fn_80080B34();
int fn_804425F8(void *ev);
void fn_8046B638(void *ev, int x);
void fn_8046B6C8(void *ev, int x);
void fn_8046B710(void *ev, int x);
void fn_8046B838(void *g, int x);
void fn_8046B860(void *g, int x);
int fn_80080A44(void *ev);
SActor *fn_800809CC(void *ev);
int fn_8007C034(void *ev);
SActor *fn_8007C034S(void *ev) __asm__("fn_8007C034");
SCtl *fn_80085928(void *p);
Obj *fn_80085954(int actor);
void fn_800CD6C4(void *c, int on);
void fn_800CD754(void *c, int on);
int fn_800CD0EC(void *c);
int fn_800CD21C(void *c);
int fn_8009AFC8(SObj &a);
SBody *fn_800B24AC(SObj &o);
HkRef fn_80317960(SBodyBase &body);
void fn_8006645C(SObj *o, int a);
void fn_8006645CR(SObj &o, int a) __asm__("fn_8006645C");
void fn_80066604(SObj *o);
void fn_8006668C(SObj &o, float v);
int fn_80097CE8(SObj &actor, int a, int mode, float speed, void *set, float blend, float f);
void fn_800F9754(EBase &e);
void fn_8008643C(int actor);
void fn_80086410(int actor);
void Script_TriggerEntity(void *ev, int h, int owner, int kind, float a, float b, float c, float d);
void fn_80082720(void *ev, int h);
void fn_80082F30(void *ev);
void fn_80082440(void *ev, Vector *out);
void fn_800826A8(void *ev, Mat *m);
void fn_800825D0(void *ev, Mat *m);
void fn_80082E90(void *ev, char *name, int a, int b);
void fn_80082E24(void *ev, char *name);
void fn_80083428(void *ev, char *name);
void fn_800820A0(void *ev, int a);
void fn_80082014(void *ev, int v);
void fn_80081F8C(void *ev, int v);
int fn_80082190(void *ev, char *name);
void fn_80082254(char *name, Vector *at, int a);
int fn_800803DC(void *ev, int id, float f);
int fn_80083734(char *name);
void fn_800814B0(char *name, cScript *self, int a);
float fn_8007C0AC(void *ev);
float fn_8007C244(void *ev);
float fn_8007C2AC(void *ev);
void fn_8007C314(void *ev, float v);
void fn_8007C6D0(void *ev, float v);
float fn_8007C3EC(void *ev);
float fn_8007C52C(void *ev);
void fn_8007AA8C(int h, int target);
void fn_8007ABE8(int h, int target);
void fn_8007AB50(int h);
void fn_8007AC68(int h, int target, int c);
void fn_8007A448(int h);
void fn_8007A4FC(int h);
void fn_8007A738(int h, Vector *to);
void fn_8007B288(int h);
void fn_8007B4D8(int h, int v);
int fn_8007BEA8(int h);
int fn_80048EBC(int body, Vector *pos, int a, int b, int c, float f, int d);
int fn_80171F8C();
void fn_80081C68();
void fn_80081C94();
void fn_80081CC4();
int fn_80081B40(int h);
int fn_80081A54(int h);
void fn_80081918(int h);
void fn_800816A0(int h);
int fn_80081BD4(int h);
void fn_8043323C(void *p, int on);

void fn_801C5E0C(cAvengersMansion_ParadoxBoss *self);
void fn_801C6D4C(cAvengersMansion_ParadoxBoss *self, int n);
void fn_801C739C(cAvengersMansion_ParadoxBoss *self, Vector *at);
int fn_801C7400(cAvengersMansion_ParadoxBoss *self, Vector *at);
void fn_801C77DC(cAvengersMansion_ParadoxBoss *self);
void fn_801C78A0(cAvengersMansion_ParadoxBoss *self);
void fn_801C7964(cAvengersMansion_ParadoxBoss *self);
void fn_801C79E8(cAvengersMansion_ParadoxBoss *self);
void fn_801C7AAC(cAvengersMansion_ParadoxBoss *self);
unsigned int fn_801C9D30(cAvengersMansion_ParadoxBoss *self);
unsigned int fn_801C9D78(cAvengersMansion_ParadoxBoss *self);
unsigned int fn_801C9DC0(cAvengersMansion_ParadoxBoss *self);
unsigned int fn_801C9E08(cAvengersMansion_ParadoxBoss *self);
unsigned int fn_801C9E50(cAvengersMansion_ParadoxBoss *self);
unsigned int fn_801C9E98(cAvengersMansion_ParadoxBoss *self);
unsigned int fn_801C9EE0(cAvengersMansion_ParadoxBoss *self);
unsigned int fn_801C9F28(cAvengersMansion_ParadoxBoss *self);
unsigned int fn_801C9F70(cAvengersMansion_ParadoxBoss *self);
unsigned int fn_801C9FB8(cAvengersMansion_ParadoxBoss *self);
unsigned int fn_801CA000(cAvengersMansion_ParadoxBoss *self);
unsigned int fn_801CA048(cAvengersMansion_ParadoxBoss *self);
unsigned int fn_801CA090(cAvengersMansion_ParadoxBoss *self);
unsigned int fn_801CA0D8(cAvengersMansion_ParadoxBoss *self);
void fn_801C8564(cAvengersMansion_IM1_Start *self);
void fn_801C86B0(cAvengersMansion_IM1_Start *self);
unsigned int fn_801CA174(cAvengersMansion_IM1_Start *self);
unsigned int fn_801CA1BC(cAvengersMansion_IM1_Start *self);
unsigned int fn_801CA204(cAvengersMansion_IM1_Start *self);
unsigned int fn_801CA24C(cAvengersMansion_IM1_Start *self);
unsigned int fn_801CA294(cAvengersMansion_IM1_Start *self);
unsigned int fn_801CA2DC(cAvengersMansion_IM1_Start *self);
unsigned int fn_801CA324(cAvengersMansion_IM1_Start *self);
unsigned int fn_801CA36C(cAvengersMansion_IM1_Start *self);
unsigned int fn_801CA3B4(cAvengersMansion_IM1_Start *self);
unsigned int fn_801CA3FC(cAvengersMansion_IM1_Start *self);
unsigned int fn_801CA444(cAvengersMansion_IM1_Start *self);
void fn_801C94D4(cAvengersMansion_IronManSAC *self);
void fn_801C95F0(cAvengersMansion_IronManSAC *self);
void fn_801C96C8(cAvengersMansion_IronManSAC *self);
void fn_801C9790(cAvengersMansion_IronManSAC *self);
void fn_801C98A4(cAvengersMansion_IronManSAC *self);
void fn_801C9948(cAvengersMansion_IronManSAC *self);
void fn_801C99F0(cAvengersMansion_IronManSAC *self);
void fn_801C9A90(cAvengersMansion_IronManSAC *self);
void fn_801C9AF8(cAvengersMansion_IronManSAC *self);
unsigned int fn_801CA4E0(cAvengersMansion_IronManSAC *self);
unsigned int fn_801CA528(cAvengersMansion_IronManSAC *self);
unsigned int fn_801CA570(cAvengersMansion_IronManSAC *self);
unsigned int fn_801CA5B8(cAvengersMansion_IronManSAC *self);
unsigned int fn_801CA600(cAvengersMansion_IronManSAC *self);
unsigned int fn_801CA69C(cAvengersMansion_HideSkirt *self);
unsigned int fn_801CA6E4(cAvengersMansion_HideSkirt *self);

void fn_801C55F8(register cAvengersMansion_ParadoxBoss *self) // slot 4
{
    fn_8046B710(&self->boss, fn_80083734("PARADOX"));
    fn_8046B710(&self->pt[0], fn_801C9D30(self));
    fn_8046B710(&self->pt[1], fn_801C9D78(self));
    fn_8046B710(&self->pt[2], fn_801C9DC0(self));
    fn_8046B710(&self->pt[3], fn_801C9E08(self));
    fn_8046B710(&self->pt[4], fn_801C9E50(self));
    fn_8046B710(&self->pt[5], fn_801C9E98(self));
    fn_8046B710(&self->pt[6], fn_801C9EE0(self));
    fn_8046B710(&self->pt[7], fn_801C9F28(self));
    fn_8046B710(&self->pt[8], fn_801C9F70(self));
    fn_8046B710(&self->pt[9], fn_801C9FB8(self));
    fn_8046B710(&self->pt[10], fn_801CA000(self));
    fn_8046B710(&self->r98, fn_801CA048(self));
    Script_LinkEntity(self, fn_804425F8(&self->boss), 0);
    Script_LinkEntity(self, fn_804425F8(&self->pt[2]), 0);
    Script_LinkEntity(self, fn_804425F8(&self->pt[4]), 0);
    Script_LinkEntity(self, fn_804425F8(&self->pt[6]), 0);
    Script_LinkEntity(self, fn_804425F8(&self->pt[8]), 0);
    Script_LinkEntity(self, fn_804425F8(&self->pt[10]), 0);
    self->zone = 0;
    self->fB4 = 0;
    self->fC0 = 0;
    self->fC4 = 0;
    self->fC8 = 0;
    self->fD8 = 0;
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
    fn_8046B710(&self->player, fn_80080B34());
    Script_LinkEntity(self, fn_804425F8(&self->player), 0);
    self->fA4 = 4;
    self->teleports = 0;
    self->fAC = 0;
    self->phase = 0;
    self->fB8 = 0;
    self->fBC = 0;
    fn_8046B838(lbl_80552110, 1);
}

void fn_801C5918(register cAvengersMansion_ParadoxBoss *self, int h, int other, int value) // slot 14
{
    Ref8 o;

    fn_8046B638(&o, other);
    if (!fn_80080A44(&o))
        return;
    if (h == fn_804425F8(&self->pt[4]))
        self->zone = 1;
    if (h == fn_804425F8(&self->pt[6]))
        self->zone = 2;
    if (h == fn_804425F8(&self->pt[8]))
        self->zone = 3;
    if (h == fn_804425F8(&self->pt[10]))
        self->zone = 4;
    if (h == fn_804425F8(&self->pt[2])) {
        self->zone = 5;
        self->fBC = 1;
        if (self->fB4)
            Script_QueueMessage(self, 10.0f, 85, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
}

void fn_801C5A80(register cAvengersMansion_ParadoxBoss *self, int h, int other, int value) // slot 15
{
    Ref8 o;

    fn_8046B638(&o, other);
    if (!fn_80080A44(&o))
        return;
    self->zone = 0;
    if (h == fn_804425F8(&self->pt[2])) {
        self->fBC = 0;
        Script_CancelMessages(self, 30);
    }
}

float fn_801C5B20(register cAvengersMansion_ParadoxBoss *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h != fn_804425F8(&self->boss))
        return damage;
    if (self->fC4)
        return 0.0f;
    if (self->fC0)
        return 0.0f;
    float left = fn_8007C0AC(&self->boss) - damage;
    if (self->fB4) {
        if (fn_8007C034(&self->boss) == 0)
            return 0.0f;
        if (fn_800CD0EC(fn_80085928((void *)fn_8007C034(&self->boss))) || fn_800CD21C(fn_80085928((void *)fn_8007C034(&self->boss)))
            || fn_8009AFC8(*fn_8007C034S(&self->boss)) == 0x158)
            Script_QueueMessage(self, 2.0f, 86, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        else
            fn_801C5E0C(self);
        return 0.0f;
    }
    if (self->fC0)
        return 0.0f;
    float ratio = fn_8007C0AC(&self->boss) / fn_8007C244(&self->boss);
    if (ratio < 0.25f && self->phase == 2) {
        self->phase++;
        fn_801C6D4C(self, 1);
        return 0.0f;
    } else if (ratio < 0.5f && self->phase == 1) {
        self->phase++;
        fn_801C6D4C(self, 1);
        return 0.0f;
    } else if (ratio < 0.75f && self->phase == 0) {
        self->phase++;
        fn_801C7AAC(self);
        return 0.0f;
    }
    return damage;
}

void fn_801C5E0C(register cAvengersMansion_ParadoxBoss *self)
{
    fn_8007D8B0(self);
    Mat m;
    fn_800826A8(&self->pt[0], &m);
    fn_8006645CR(*fn_8007C034S(&self->boss), 0);
    fn_800820A0(&self->boss, 1);
    fn_8007A4FC(fn_804425F8(&self->boss));
    self->fB8 = 0;
    self->teleports = 0;
    self->fAC = 0;
    self->fB4 = 0;
    self->fC0 = 0;
    if (fn_8007C034(&self->boss)) {
        fn_800CD6C4(fn_80085928((void *)fn_8007C034(&self->boss)), 0);
        fn_800CD754(fn_80085928((void *)fn_8007C034(&self->boss)), 0);
        fn_80085954(fn_8007C034(&self->boss))->s5(2);
        fn_80082014(&self->boss, 2);
    }
    fn_80082E90(&self->boss, "winkTeleportIn", 0xff, 0xff);
    fn_800825D0(&self->boss, &m);
    Script_QueueMessage(self, 0.1f, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

int fn_801C5FF8(register cAvengersMansion_ParadoxBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    if (h == fn_804425F8(&self->boss)) {
        if (damage > 90000.0f && kind == 8) {
            self->bossHit = 1;
            return 1;
        }
    } else if (h == fn_804425F8(&self->player)) {
        if (damage > 90000.0f && kind == 8) {
            self->playerHit = 1;
            return 1;
        }
    }
    return 1;
}

void fn_801C60E4(register cAvengersMansion_ParadoxBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_801C6D4C(self, e);
        break;
    case 20:
        fn_8007A4FC(fn_804425F8(&self->boss));
        self->teleports = 0;
        fn_8007A448(fn_804425F8(&self->boss));
        fn_801C6D4C(self, 1);
        break;
    case 30:
        self->fBC = 1;
        fn_801C6D4C(self, 5);
        break;
    case 50: {
        Ref8 ev;

        fn_8046B6C8(&ev, fn_801CA090(self));
        Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    }
    case 80: {
        Ref8 ev;

        fn_8046B6C8(&ev, fn_801CA0D8(self));
        Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), 7, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    }
    case 45:
        if (fn_8007C034(&self->boss)) {
            fn_800CD6C4(fn_80085928((void *)fn_8007C034(&self->boss)), 1);
            fn_800CD754(fn_80085928((void *)fn_8007C034(&self->boss)), 1);
        }
        fn_8007ABE8(fn_804425F8(&self->boss), fn_80080B34());
        fn_8007AB50(fn_804425F8(&self->boss));
        Script_QueueMessage(self, 2.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, (int)a);
        break;
    case 60:
        fn_80082E90(&self->boss, "winkTeleportIn", 0xff, 0xff);
        break;
    case 40: {
        Ref8 ev;
        Vector pos;
        fn_8046B6C8(&ev, e);
        Mat m;
        fn_800826A8(&ev, &m);
        fn_80082440(&ev, &pos);
        fn_801C739C(self, &pos);
        if (fn_801C7400(self, &pos) == 0)
            return;
        fn_800825D0(&self->boss, &m);
        SObj *o = (SObj *)fn_8007C034(&self->boss);
        if (!o || !fn_800B24AC(*o) || fn_80317960(*fn_800B24AC(*o)).fn_80436294())
            return;
        fn_8006645C(o, 0);
        fn_800820A0(&self->boss, 1);
        if (fn_8007C034(&self->boss))
            fn_80082014(&self->boss, 2);
        fn_8008643C(fn_8007C034(&self->boss));
        if (self->teleports > self->fA4) {
            self->fB4 = 1;
            self->fC0 = 0;
            self->teleports = 0;
            if (fn_8007C034(&self->boss)) {
                fn_800CD6C4(fn_80085928((void *)fn_8007C034(&self->boss)), 1);
                fn_800CD754(fn_80085928((void *)fn_8007C034(&self->boss)), 1);
                fn_80085954(fn_8007C034(&self->boss))->s5(2);
                fn_80097CE8(*fn_8007C034S(&self->boss), 0x158, 0, 30.0f, 0, 7.5f, -1.0f);
                fn_8006668C(*fn_8007C034S(&self->boss), 250.0f);
            }
            Script_QueueMessage(self, 30.0f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            return;
        } else if (fn_804425F8(&self->barrel)) {
            fn_8007AC68(fn_804425F8(&self->boss), fn_804425F8(&self->barrel), 1);
            Script_QueueMessage(self, 1.0f, 45, a + 1.0f, 0.0f, 0.0f, 0.0f, 0);
        } else
            Script_QueueMessage(self, 2.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, e + 1);
        Script_QueueMessage(self, 0.1f, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
    case 70:
        fn_800803DC(&self->boss, 0x158, 30.0f);
        Script_QueueMessage(self, 1.0f, 70, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 81:
        fn_801C77DC(self);
        break;
    case 82:
        fn_801C78A0(self);
        break;
    case 83:
        fn_801C7964(self);
        break;
    case 84:
        fn_801C79E8(self);
        break;
    case 85:
        fn_8007D8B0(self);
        self->fC0 = 0;
        if (fn_8007C034(&self->boss)) {
            fn_800CD6C4(fn_80085928((void *)fn_8007C034(&self->boss)), 0);
            fn_800CD754(fn_80085928((void *)fn_8007C034(&self->boss)), 0);
        }
        fn_801C5E0C(self);
        break;
    case 90:
        fn_801C6D4C(self, 1);
        break;
    case 91:
        fn_801C7AAC(self);
        break;
    case 86:
        if (fn_8007C034(&self->boss) == 0)
            return;
        if (fn_800CD0EC(fn_80085928((void *)fn_8007C034(&self->boss))) || fn_800CD21C(fn_80085928((void *)fn_8007C034(&self->boss))))
            Script_QueueMessage(self, 0.25f, 86, 0.0f, 0.0f, 0.0f, 0.0f, e);
        else if (e)
            fn_801C6D4C(self, e);
        else
            fn_801C5E0C(self);
        break;
    }
}

void fn_801C6A60(register cAvengersMansion_ParadoxBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
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
            fn_801C77DC(self);
        else
            fn_801C78A0(self);
    } else if (h == fn_804425F8(&self->player)) {
        if (self->playerHit == 0)
            fn_801C7964(self);
        else
            fn_801C79E8(self);
    }
}

void fn_801C6BA8(register cAvengersMansion_ParadoxBoss *self, float t, unsigned int event, int c) // slot 54
{
    if (event == 0) {
        self->fC8 = 1;
        if (self->zone == 1) {
            self->teleports++;
            fn_801C6D4C(self, 2);
        } else
            fn_801C6D4C(self, 1);
    }
}

void fn_801C6C34(register cAvengersMansion_ParadoxBoss *self, int a, int kind, int c, float x, float y, float z) // slot 51
{
    switch (kind) {
    case 3:
    case 4:
        if (self->fC8 == 0) {
            if (self->zone == 1) {
                self->teleports++;
                fn_801C6D4C(self, 2);
            } else
                fn_801C6D4C(self, 1);
        }
    }
}

void fn_801C6CDC(register cAvengersMansion_ParadoxBoss *self, int h, int other, int value) // slot 30
{
    if (h == fn_804425F8(&self->boss)) {
        fn_8007D8B0(self);
        self->fD8 = 1;
    }
}

void fn_801C6D4C(register cAvengersMansion_ParadoxBoss *self, int n)
{
    if (!fn_8007C034(&self->boss) || !fn_800B24AC(*fn_8007C034S(&self->boss))
        || fn_80317960(*fn_800B24AC(*fn_8007C034S(&self->boss))).fn_80436294())
        return;
    if (self->fD8) {
        if (fn_804425F8(&self->barrel))
            fn_80082F30(&self->barrel);
        fn_8007D8B0(self);
        return;
    }
    if (fn_800CD0EC(fn_80085928((void *)fn_8007C034(&self->boss))) || fn_800CD21C(fn_80085928((void *)fn_8007C034(&self->boss)))) {
        Script_QueueMessage(self, 1.0f, 86, 0.0f, 0.0f, 0.0f, 0.0f, n);
        return;
    }
    fn_80085954(fn_8007C034(&self->boss))->s5(2);
    self->fAC = n;
    if (n == 1) {
        self->fC0 = 1;
        self->fB4 = 0;
    }
    self->teleports++;
    if (n != 5) {
        fn_800803DC(&self->boss, 0xc5, 30.0f);
        fn_800CD6C4(fn_80085928((void *)fn_8007C034(&self->boss)), 1);
        fn_800CD754(fn_80085928((void *)fn_8007C034(&self->boss)), 1);
    }
    fn_80082E90(&self->boss, "winkTeleportIn", 0xff, 0xff);
    fn_800F9754(*fn_80085954(fn_8007C034(&self->boss)));
    fn_800820A0(&self->boss, 0);
    fn_80081F8C(&self->boss, 2);
    SObj *o = (SObj *)fn_8007C034(&self->boss);
    if (o) {
        fn_8006645C(o, 1);
        fn_80066604(o);
    }
    fn_80086410(fn_8007C034(&self->boss));
    fn_8007B4D8(fn_804425F8(&self->boss), 4);
    if (self->fB8 == 0) {
        self->fB8 = 1;
        fn_8007A448(fn_804425F8(&self->boss));
    }
    switch (n) {
    case 1:
        Script_QueueMessage(self, 1.0f, 40, n, 0.0f, 0.0f, 0.0f, fn_804425F8(&self->pt[3]));
        break;
    case 2:
        Script_QueueMessage(self, 1.0f, 40, n, 0.0f, 0.0f, 0.0f, fn_804425F8(&self->pt[5]));
        break;
    case 3:
        Script_QueueMessage(self, 1.0f, 40, n, 0.0f, 0.0f, 0.0f, fn_804425F8(&self->pt[7]));
        break;
    case 4:
        Script_QueueMessage(self, 1.0f, 40, n, 0.0f, 0.0f, 0.0f, fn_804425F8(&self->pt[9]));
        break;
    case 5:
        Script_QueueMessage(self, 1.0f, 40, n, 0.0f, 0.0f, 0.0f, fn_804425F8(&self->pt[1]));
        break;
    }
    if (n <= 4) {
        Ref8 ev;

        fn_8046B6C8(&ev, Script_GetOwner(self));
        fn_8046B710(&self->barrel, fn_80082190(&ev, "prp_barrel_explode"));
    }
}

void fn_801C739C(register cAvengersMansion_ParadoxBoss *self, Vector *at)
{
    fn_80082254("swav_BigGray", at, 0);
    fn_80082254("exp_telportForce", at, 0);
}

int fn_801C7400(register cAvengersMansion_ParadoxBoss *self, Vector *at)
{
    Ref8 p;

    fn_8046B638(&p, fn_80080B34());
    int body = 0;
    if (fn_800809CC(&p))
        body = fn_80085928(fn_800809CC(&p))->v22();
    else
        return 0;
    if (body == 0)
        return 0;
    if (fn_80048EBC(body, at, 0, 0, fn_800809CC(&p)->v21(), -0.11f, 0) || self->zone == self->fAC) {
        self->teleports++;
        switch (self->fAC) {
        case 1:
            Script_QueueMessage(self, 1.0f, 40, ++self->fAC, 0.0f, 0.0f, 0.0f, fn_804425F8(&self->pt[5]));
            break;
        case 2:
            Script_QueueMessage(self, 1.0f, 40, ++self->fAC, 0.0f, 0.0f, 0.0f, fn_804425F8(&self->pt[7]));
            break;
        case 3:
            Script_QueueMessage(self, 1.0f, 40, ++self->fAC, 0.0f, 0.0f, 0.0f, fn_804425F8(&self->pt[9]));
            break;
        case 4:
            Script_QueueMessage(self, 1.0f, 40, ++self->fAC, 0.0f, 0.0f, 0.0f, fn_804425F8(&self->pt[1]));
            break;
        case 5:
            fn_801C5E0C(self);
            break;
        default:
            fn_801C5E0C(self);
            break;
        }
        return 0;
    }
    return 1;
}

}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.text"); // 300.0f

extern "C" {

void fn_801C77DC(register cAvengersMansion_ParadoxBoss *self)
{
    fn_8007D8B0(self);
    fn_80082F30(&self->barrel);
    Script_QueueMessage(self, 2.0f, 82, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_80572278, 1);
}

void fn_801C78A0(register cAvengersMansion_ParadoxBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->player));
    fn_80082014(&self->boss, 2);
    fn_8046B6C8(&ev, fn_801CA090(self));
    Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801C7964(register cAvengersMansion_ParadoxBoss *self)
{
    fn_8007D8B0(self);
    fn_80082F30(&self->barrel);
    Script_QueueMessage(self, 2.0f, 84, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801C79E8(register cAvengersMansion_ParadoxBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    fn_80082014(&self->boss, 2);
    fn_8046B6C8(&ev, fn_801CA0D8(self));
    Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801C7AAC(register cAvengersMansion_ParadoxBoss *self)
{
    if (fn_8007C034(&self->boss) == 0)
        return;
    if (fn_800CD0EC(fn_80085928((void *)fn_8007C034(&self->boss))) || fn_800CD21C(fn_80085928((void *)fn_8007C034(&self->boss)))) {
        Script_QueueMessage(self, 2.0f, 91, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        return;
    }
    if (self->zone == 1) {
        fn_80085954(fn_8007C034(&self->boss))->s5(2);
        fn_800814B0("AM_WV3_WK_Ledge2.cut", self, 0);
    } else {
        fn_80085954(fn_8007C034(&self->boss))->s5(2);
        fn_800814B0("AM_WV3_WK_Ledge1.cut", self, 0);
    }
}

void fn_801C7C80(register cAvengersMansion_IM1_Start *self) // slot 4
{
    fn_8046B710(&self->r28, fn_801CA174(self));
    Script_LinkEntity(self, fn_804425F8(&self->r28), 0);
    fn_8046B710(&self->r30, fn_801CA1BC(self));
    Script_LinkEntity(self, fn_804425F8(&self->r30), 0);
    fn_8046B710(&self->r48[0], fn_801CA204(self));
    Script_LinkEntity(self, fn_804425F8(&self->r48[0]), 0);
    fn_8046B710(&self->r48[1], fn_801CA24C(self));
    Script_LinkEntity(self, fn_804425F8(&self->r48[1]), 0);
    fn_8046B710(&self->r48[2], fn_801CA294(self));
    Script_LinkEntity(self, fn_804425F8(&self->r48[2]), 0);
    fn_8046B710(&self->r48[3], fn_801CA2DC(self));
    Script_LinkEntity(self, fn_804425F8(&self->r48[3]), 0);
    fn_8046B710(&self->rA8[0], fn_801CA324(self));
    Script_LinkEntity(self, fn_804425F8(&self->rA8[0]), 0);
    fn_8046B710(&self->rA8[1], fn_801CA36C(self));
    Script_LinkEntity(self, fn_804425F8(&self->rA8[1]), 0);
    fn_8046B710(&self->rA8[2], fn_801CA3B4(self));
    Script_LinkEntity(self, fn_804425F8(&self->rA8[2]), 0);
    fn_8046B710(&self->rA8[3], fn_801CA3FC(self));
    Script_LinkEntity(self, fn_804425F8(&self->rA8[3]), 0);
    fn_8046B710(&self->rC8, fn_801CA444(self));
    self->fD0 = 0;
    self->fD4 = 0;
    self->fD8 = 0;
    self->fDC = 0;
}

void fn_801C7F4C(register cAvengersMansion_IM1_Start *self, int h, int other, int value) // slot 14
{
    Ref8 o;

    fn_8046B638(&o, other);
    if (!fn_80080A44(&o))
        return;
    if (h == fn_804425F8(&self->rA8[0])) {
        if (self->fD4 == 0)
            fn_801C8564(self);
        return;
    }
    if (h == fn_804425F8(&self->rA8[1])) {
        if (self->fD0 == 0)
            fn_801C86B0(self);
        return;
    }
    if (h == fn_804425F8(&self->rA8[2])) {
        if (self->fD0 == 0)
            fn_801C8564(self);
        return;
    }
    if (h == fn_804425F8(&self->rA8[3])) {
        if (self->fD4 == 0)
            fn_801C86B0(self);
        return;
    }
}

void fn_801C808C(register cAvengersMansion_IM1_Start *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_801C8564(self);
        break;
    case 20:
        fn_801C86B0(self);
        break;
    }
}

float fn_801C8114(register cAvengersMansion_IM1_Start *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h == fn_804425F8(&self->r48[0]) || h == fn_804425F8(&self->r48[1]))
        fn_801C8564(self);
    else if (h == fn_804425F8(&self->r48[2]) || h == fn_804425F8(&self->r48[3]))
        fn_801C86B0(self);
    return damage;
}

void fn_801C81F8(register cAvengersMansion_IM1_Start *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (h == fn_804425F8(&self->r48[0]) || h == fn_804425F8(&self->r48[1]) || h == fn_804425F8(&self->r48[2])
        || h == fn_804425F8(&self->r48[3]))
        return;
    if (h == fn_804425F8(&self->r28)) {
        self->fD8 = 1;
        Script_CancelMessages(self, 20);
        Script_QueueMessage(self, 3.0f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        if (self->fD8 && self->fDC)
            Script_TriggerEntity(&self->rC8, fn_804425F8(&self->rC8), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    } else if (h == fn_804425F8(&self->r30)) {
        self->fDC = 1;
        Script_CancelMessages(self, 10);
        Script_QueueMessage(self, 3.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        if (self->fD8 && self->fDC)
            Script_TriggerEntity(&self->rC8, fn_804425F8(&self->rC8), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    } else {
        if (self->fD0 == 0 && self->fD4 == 0) {
            float r = fn_80171F8C() * 4.656612873077392578125e-10f;

            if (r < 0.5) {
                Script_CancelMessages(self, 10);
                Script_QueueMessage(self, 3.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            } else {
                Script_CancelMessages(self, 20);
                Script_QueueMessage(self, 3.0f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            }
        }
        return;
    }
}

void fn_801C8564(register cAvengersMansion_IM1_Start *self)
{
    if (self->fD0 == 0) {
        self->fD0 = 1;
        Script_CancelMessages(self, 10);
        Script_TriggerEntity(&self->r28, fn_804425F8(&self->r28), Script_GetOwner(self), 0, 0.0f, 1.0f, 0.0f, 0.0f);
        Script_TriggerEntity(&self->r48[0], fn_804425F8(&self->r48[0]), Script_GetOwner(self), 0, 0.0f, 1.0f, 0.0f, 0.0f);
        Script_TriggerEntity(&self->r48[1], fn_804425F8(&self->r48[1]), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    }
}

void fn_801C86B0(register cAvengersMansion_IM1_Start *self)
{
    if (self->fD4 == 0) {
        self->fD4 = 1;
        Script_CancelMessages(self, 20);
        Script_TriggerEntity(&self->r30, fn_804425F8(&self->r30), Script_GetOwner(self), 0, 0.0f, 1.0f, 0.0f, 0.0f);
        Script_TriggerEntity(&self->r48[2], fn_804425F8(&self->r48[2]), Script_GetOwner(self), 0, 0.0f, 1.0f, 0.0f, 0.0f);
        Script_TriggerEntity(&self->r48[3], fn_804425F8(&self->r48[3]), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    }
}

void fn_801C87FC(register cAvengersMansion_IronManSAC *self) // slot 5
{
    fn_8046B710(&self->boss, Script_GetOwner(self));
    fn_8007A448(fn_804425F8(&self->boss));
    Script_LinkEntity(self, fn_80080B34(), 0);
    fn_8046B710(&self->r30, fn_801CA4E0(self));
    fn_8046B710(&self->r38, fn_801CA528(self));
    fn_8046B710(&self->r48, fn_801CA570(self));
    fn_8046B710(&self->r50, fn_801CA5B8(self));
    fn_8046B710(&self->r58, fn_801CA600(self));
    self->f60 = 0;
    self->f64 = 0;
    self->f68 = 0;
    self->f6C = 0;
    self->f70 = 0;
    self->done = 0;
    self->f78 = 0;
    self->state = 1;
    self->f80 = 0;
    self->f84 = 0.1f;
    self->f88 = 1.0f;
    self->f8C = 2.0f;
    self->f90 = 2.0f;
    self->f94 = 15.0f;
    self->f98 = 10.0f;
    self->charge = 0.0f;
}

void fn_801C89A0(register cAvengersMansion_IronManSAC *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    float ratio;

    switch (kind) {
    case 10:
        ratio = fn_8007C0AC(&self->boss) / fn_8007C244(&self->boss);
        if (ratio < 0.75f && self->f80 == 0 && self->f6C == 0) {
            self->f6C = 1;
            fn_801C96C8(self);
        }
        if (ratio < 0.5f && self->f80 == 1 && self->f6C == 0) {
            self->f6C = 1;
            fn_801C96C8(self);
        }
        if (ratio < 0.25f && self->f80 == 2 && self->f6C == 0) {
            self->f6C = 1;
            fn_801C96C8(self);
        }
        break;
    case 15:
        ratio = fn_8007C3EC(&self->boss) / fn_8007C52C(&self->boss);
        if (ratio < 0.25f)
            fn_801C95F0(self);
        else
            Script_QueueMessage(self, self->f88, 15, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 20:
        Script_TriggerEntity(&self->r30, fn_804425F8(&self->r30), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 30:
        self->charge += 0.2f;
        if (self->charge < 4.0f) {
            fn_801C98A4(self);
            Script_QueueMessage(self, 0.2f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        } else {
            fn_80083428(&self->boss, "ppMegCharge");
            if (self->f78 == 1) {
                self->f78 = 0;
                Script_TriggerEntity(&self->r58, fn_804425F8(&self->r58), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            }
            self->f80++;
            self->f6C = 0;
            fn_801C94D4(self);
        }
        break;
    case 40:
        if (self->state == 3 && self->f64 == 0) {
            fn_801C95F0(self);
            Script_QueueMessage(self, self->f98, 70, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
        break;
    case 50:
        if (self->state == 3 && self->f64 == 1)
            fn_801C9790(self);
        break;
    case 60:
        fn_801C94D4(self);
        break;
    case 70:
        if (self->f6C == 1)
            fn_801C96C8(self);
        break;
    case 72:
        fn_801C9948(self);
        break;
    case 74:
        fn_801C99F0(self);
        break;
    case 76:
        fn_801C9A90(self);
        break;
    case 78:
        fn_801C9AF8(self);
        break;
    }
}

float fn_801C8E28(register cAvengersMansion_IronManSAC *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h == fn_804425F8(&self->boss)) {
        if (self->state == 1) {
            Script_CancelMessages(self, 15);
            Script_CancelMessages(self, 60);
            fn_801C95F0(self);
        }
        if (self->state == 2)
            Script_QueueMessage(self, self->f84, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        if (self->state == 3) {
            Script_CancelMessages(self, 40);
            fn_801C95F0(self);
            Script_QueueMessage(self, self->f98, 70, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
        if (self->state == 4) {
            Script_CancelMessages(self, 30);
            if (self->charge > 1.0f) {
                self->f80++;
                self->f6C = 0;
            } else
                Script_QueueMessage(self, self->f98, 70, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            fn_80083428(&self->boss, "ppMegCharge");
            if (self->f78 == 1) {
                self->f78 = 0;
                Script_TriggerEntity(&self->r58, fn_804425F8(&self->r58), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            }
            fn_801C95F0(self);
        }
    }
    if (h == fn_80080B34() && self->f6C == 1 && self->state == 2 && fn_8007BEA8(fn_80080B34())) {
        Script_CancelMessages(self, 70);
        fn_801C96C8(self);
    }
    return damage;
}

float fn_801C90B4(register cAvengersMansion_IronManSAC *self, int h, int node, int value) // slot 37
{
    if (self->state == 3 && self->f60 == 1) {
        Script_CancelMessages(self, 40);
        self->f64 = 1;
        Script_QueueMessage(self, self->f90, 50, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
    return -1.0f;
}

int fn_801C915C(register cAvengersMansion_IronManSAC *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    Script_CancelMessages(self, 10);
    Script_CancelMessages(self, 15);
    Script_CancelMessages(self, 70);
    Script_CancelMessages(self, 30);
    Script_CancelMessages(self, 50);
    fn_80083428(&self->boss, "ppMegCharge");
    if (self->f78 == 1) {
        self->f78 = 0;
        Script_TriggerEntity(&self->r58, fn_804425F8(&self->r58), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    return 1;
}

void fn_801C9264(register cAvengersMansion_IronManSAC *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (h == fn_80080B34() || h == fn_804425F8(&self->boss)) {
        if (self->done && h != fn_80080B34())
            return;
        self->done = 1;
        Script_CancelMessages(self, 10);
        Script_CancelMessages(self, 15);
        Script_CancelMessages(self, 70);
        Script_CancelMessages(self, 30);
        Script_CancelMessages(self, 50);
        fn_80083428(&self->boss, "ppMegCharge");
        if (self->f78 == 1) {
            self->f78 = 0;
            Script_TriggerEntity(&self->r58, fn_804425F8(&self->r58), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        }
        fn_80081C68();
        fn_80081C94();
        fn_80081CC4();
        fn_80081B40(fn_804425F8(&self->boss));
        if (h == fn_804425F8(&self->boss)) {
            fn_80081A54(fn_80080B34());
            fn_801C9948(self);
        } else
            fn_801C9A90(self);
    }
    return;
}

void fn_801C942C(register cAvengersMansion_IronManSAC *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (b == fn_804425F8(&self->r48))
        Script_QueueMessage(self, 2.0f, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    return;
}

void fn_801C94D4(register cAvengersMansion_IronManSAC *self)
{
    Ref8 r;

    fn_801C95F0(self);
    self->state = 1;
    fn_80082720(&self->boss, fn_80080B34());
    fn_8007A448(fn_804425F8(&self->boss));
    fn_8007AA8C(fn_804425F8(&self->boss), fn_80080B34());
    fn_8046B638(&r, fn_804425F8(&self->boss));
    if (fn_800809CC(&r))
        fn_800CD6C4(fn_80085928(fn_800809CC(&r)), 1);
    Script_QueueMessage(self, self->f88, 15, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801C95F0(register cAvengersMansion_IronManSAC *self)
{
    Ref8 r;

    self->state = 2;
    self->charge = 0.0f;
    self->f60 = 0;
    self->f64 = 0;
    fn_8007A4FC(fn_804425F8(&self->boss));
    fn_8007B288(fn_804425F8(&self->boss));
    fn_8046B638(&r, fn_804425F8(&self->boss));
    if (fn_800809CC(&r))
        fn_800CD6C4(fn_80085928(fn_800809CC(&r)), 0);
}

void fn_801C96C8(register cAvengersMansion_IronManSAC *self)
{
    fn_801C95F0(self);
    self->state = 3;
    Vector at;
    fn_80082440(&self->r38, &at);
    fn_8007A448(fn_804425F8(&self->boss));
    fn_8007A738(fn_804425F8(&self->boss), &at);
    self->f60 = 1;
    Script_QueueMessage(self, self->f94, 40, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801C9790(register cAvengersMansion_IronManSAC *self)
{
    fn_801C95F0(self);
    self->state = 4;
    fn_80082E24(&self->boss, "ppMegCharge");
    if (self->f78 == 0) {
        self->f78 = 1;
        Script_TriggerEntity(&self->r58, fn_804425F8(&self->r58), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    fn_8007A448(fn_804425F8(&self->boss));
    fn_801C98A4(self);
    Script_QueueMessage(self, 0.2f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801C98A4(register cAvengersMansion_IronManSAC *self)
{
    fn_8007C6D0(&self->boss, 1.0f);
    if (fn_8007C244(&self->boss) >= fn_8007C2AC(&self->boss))
        fn_8007C314(&self->boss, fn_8007C2AC(&self->boss) + 1.0f);
}

void fn_801C9948(register cAvengersMansion_IronManSAC *self)
{
    Script_QueueMessage(self, 2.0f, 74, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8046B860(lbl_8057230C, 1);
}

void fn_801C99F0(register cAvengersMansion_IronManSAC *self)
{
    fn_80081918(fn_80080B34());
    lbl_8066C71C = fn_80080B34();
    Script_TriggerEntity(&self->r30, fn_804425F8(&self->r30), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801C9A90(register cAvengersMansion_IronManSAC *self)
{
    Script_QueueMessage(self, 2.0f, 78, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801C9AF8(register cAvengersMansion_IronManSAC *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    lbl_8066C71C = fn_804425F8(&self->boss);
    fn_8046B6C8(&ev, fn_801CA5B8(self));
    Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801C9BB8(register cAvengersMansion_HideSkirt *self) // slot 5
{
    if (stricmp(lbl_805526EC, "Wolverine_3") == 0) {
        Ref8 a;
        Ref8 b;

        fn_8046B6C8(&a, fn_801CA69C(self));
        fn_8046B6C8(&b, fn_801CA6E4(self));
        Script_TriggerEntity(&a, fn_804425F8(&a), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        Script_TriggerEntity(&b, fn_804425F8(&b), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    }
}

cScript *fn_801C9CDC(register cAvengersMansion_ParadoxBoss *self)
{
    return new cAvengersMansion_ParadoxBoss;
}

unsigned int fn_801C9D30(register cAvengersMansion_ParadoxBoss *self) { return Script_GetParamUInt(self, 0); }
unsigned int fn_801C9D78(register cAvengersMansion_ParadoxBoss *self) { return Script_GetParamUInt(self, 1); }
unsigned int fn_801C9DC0(register cAvengersMansion_ParadoxBoss *self) { return Script_GetParamUInt(self, 2); }
unsigned int fn_801C9E08(register cAvengersMansion_ParadoxBoss *self) { return Script_GetParamUInt(self, 3); }
unsigned int fn_801C9E50(register cAvengersMansion_ParadoxBoss *self) { return Script_GetParamUInt(self, 4); }
unsigned int fn_801C9E98(register cAvengersMansion_ParadoxBoss *self) { return Script_GetParamUInt(self, 5); }
unsigned int fn_801C9EE0(register cAvengersMansion_ParadoxBoss *self) { return Script_GetParamUInt(self, 6); }
unsigned int fn_801C9F28(register cAvengersMansion_ParadoxBoss *self) { return Script_GetParamUInt(self, 7); }
unsigned int fn_801C9F70(register cAvengersMansion_ParadoxBoss *self) { return Script_GetParamUInt(self, 8); }
unsigned int fn_801C9FB8(register cAvengersMansion_ParadoxBoss *self) { return Script_GetParamUInt(self, 9); }
unsigned int fn_801CA000(register cAvengersMansion_ParadoxBoss *self) { return Script_GetParamUInt(self, 10); }
unsigned int fn_801CA048(register cAvengersMansion_ParadoxBoss *self) { return Script_GetParamUInt(self, 11); }
unsigned int fn_801CA090(register cAvengersMansion_ParadoxBoss *self) { return Script_GetParamUInt(self, 12); }
unsigned int fn_801CA0D8(register cAvengersMansion_ParadoxBoss *self) { return Script_GetParamUInt(self, 13); }

cScript *fn_801CA120(register cAvengersMansion_IM1_Start *self)
{
    return new cAvengersMansion_IM1_Start;
}

unsigned int fn_801CA174(register cAvengersMansion_IM1_Start *self) { return Script_GetParamUInt(self, 0); }
unsigned int fn_801CA1BC(register cAvengersMansion_IM1_Start *self) { return Script_GetParamUInt(self, 1); }
unsigned int fn_801CA204(register cAvengersMansion_IM1_Start *self) { return Script_GetParamUInt(self, 2); }
unsigned int fn_801CA24C(register cAvengersMansion_IM1_Start *self) { return Script_GetParamUInt(self, 3); }
unsigned int fn_801CA294(register cAvengersMansion_IM1_Start *self) { return Script_GetParamUInt(self, 4); }
unsigned int fn_801CA2DC(register cAvengersMansion_IM1_Start *self) { return Script_GetParamUInt(self, 5); }
unsigned int fn_801CA324(register cAvengersMansion_IM1_Start *self) { return Script_GetParamUInt(self, 6); }
unsigned int fn_801CA36C(register cAvengersMansion_IM1_Start *self) { return Script_GetParamUInt(self, 7); }
unsigned int fn_801CA3B4(register cAvengersMansion_IM1_Start *self) { return Script_GetParamUInt(self, 8); }
unsigned int fn_801CA3FC(register cAvengersMansion_IM1_Start *self) { return Script_GetParamUInt(self, 9); }
unsigned int fn_801CA444(register cAvengersMansion_IM1_Start *self) { return Script_GetParamUInt(self, 10); }

cScript *fn_801CA48C(register cAvengersMansion_IronManSAC *self)
{
    return new cAvengersMansion_IronManSAC;
}

unsigned int fn_801CA4E0(register cAvengersMansion_IronManSAC *self) { return Script_GetParamUInt(self, 0); }
unsigned int fn_801CA528(register cAvengersMansion_IronManSAC *self) { return Script_GetParamUInt(self, 1); }
unsigned int fn_801CA570(register cAvengersMansion_IronManSAC *self) { return Script_GetParamUInt(self, 2); }
unsigned int fn_801CA5B8(register cAvengersMansion_IronManSAC *self) { return Script_GetParamUInt(self, 3); }
unsigned int fn_801CA600(register cAvengersMansion_IronManSAC *self) { return Script_GetParamUInt(self, 4); }

cScript *fn_801CA648(register cAvengersMansion_HideSkirt *self)
{
    return new cAvengersMansion_HideSkirt;
}

unsigned int fn_801CA69C(register cAvengersMansion_HideSkirt *self) { return Script_GetParamUInt(self, 0); }
unsigned int fn_801CA6E4(register cAvengersMansion_HideSkirt *self) { return Script_GetParamUInt(self, 1); }

}
