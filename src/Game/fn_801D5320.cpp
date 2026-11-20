// The Grand Central classes cGrandCentral_VenomBoss, _OhmBoss, _HazmatBoss, _MagnetoBoss and _RockBomb (docs/story.md row 18).
// Pool read from 0x8049FE74 (extern_pool).

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

struct Mat {
    float m[16];
    Mat() __asm__("fn_8042D7B0");
};

struct SObjData {
    char pad0[0x198];
};

struct SObj : SObjData { // vptr at +0x198
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(Vector *at, int a); // +0x30
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

struct ArcData {
    char pad0[0xc8];
};

struct Arc : ArcData { // what fn_803A20D8 returns; vptr at +0xC8
    V6(v0, v1, v2, v3, v4, v5) V6(v6, v7, v8, v9, v10, v11) V6(v12, v13, v14, v15, v16, v17)
    V6(v18, v19, v20, v21, v22, v23) V6(v24, v25, v26, v27, v28, v29)
    virtual void v30();
    virtual void v31(int h); // +0x100
    V6(v32, v33, v34, v35, v36, v37) V6(v38, v39, v40, v41, v42, v43)
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(int a, int b); // +0x188
    virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
    virtual void v54(); // +0x1B8
};

struct cGrandCentral_VenomBoss : cScript { // 0x60
    Ref8 boss;      // +0x28, param 0
    Ref8 r30;       // +0x30
    Ref8 player;    // +0x38
    int f40;        // +0x40
    int armored;    // +0x44
    int f48;        // +0x48
    int done;       // +0x4C
    int bossHit;    // +0x50
    int playerHit;  // +0x54
    float f58;      // +0x58
    float limit;    // +0x5C
    cGrandCentral_VenomBoss() __asm__("fn_8046B1C0");
};

struct cGrandCentral_OhmBoss : cScript { // 0xFC
    Ref8 boss;      // +0x28
    Ref8 player;    // +0x30
    Ref8 r38;       // +0x38, param 0
    Ref8 r40;       // +0x40, param 1
    Ref8 r48;       // +0x48
    Ref8 r50;       // +0x50, param 3
    Ref8 r58;       // +0x58, param 4
    Ref8 r60;       // +0x60, param 5
    Ref8 r68;       // +0x68, param 6
    Ref8 r70;       // +0x70, param 13
    Ref8 r78;       // +0x78, param 14
    int f80;        // +0x80
    int f84;        // +0x84
    int f88;        // +0x88
    int f8C;        // +0x8C
    int f90;        // +0x90
    int f94;        // +0x94
    int charging;   // +0x98
    int f9C;        // +0x9C
    int fA0;        // +0xA0
    int done;       // +0xA4
    int bossHit;    // +0xA8
    int playerHit;  // +0xAC
    Mat mB0;        // +0xB0
    Arc *arc[3];    // +0xF0
    cGrandCentral_OhmBoss() __asm__("fn_8046B238");
};

struct cGrandCentral_HazmatBoss : cScript { // 0x5C
    Ref8 boss;      // +0x28
    Ref8 r30;       // +0x30, param 0
    Ref8 r38;       // +0x38, param 1
    Ref8 r40;       // +0x40
    int armored;    // +0x48
    int f4C;        // +0x4C
    int done;       // +0x50
    int bossHit;    // +0x54
    int playerHit;  // +0x58
    cGrandCentral_HazmatBoss() __asm__("fn_8046B324");
};

struct cGrandCentral_MagnetoBoss : cScript { // 0xD0
    Ref8 boss;      // +0x28
    Ref8 player;    // +0x30
    Ref8 r38;       // +0x38, param 12
    Ref8 r40;       // +0x40, param 0
    Ref8 r48;       // +0x48, param 1
    Ref8 r50;       // +0x50, param 4
    Ref8 r58;       // +0x58, param 2
    Ref8 r60;       // +0x60, param 3
    Ref8 r68[6];    // +0x68, params 6-11
    int zone;       // +0x98
    int f9C;        // +0x9C
    int phase;      // +0xA0
    float fA4;      // +0xA4
    int fA8;        // +0xA8
    int fAC;        // +0xAC
    int fB0;        // +0xB0
    int fB4;        // +0xB4
    int fB8;        // +0xB8
    int fBC;        // +0xBC
    int fC0;        // +0xC0
    int done;       // +0xC4
    int bossHit;    // +0xC8
    int playerHit;  // +0xCC
    cGrandCentral_MagnetoBoss() __asm__("fn_8046B3A4");
};

struct cGrandCentral_RockBomb : cScript { // 0xA0
    Ref8 obj;       // +0x28
    Ref8 r30;       // +0x30
    Ref8 r38;       // +0x38
    char pad40[0x10];
    Vector target;  // +0x50
    Mat m60;        // +0x60
    cGrandCentral_RockBomb() __asm__("fn_8046B4A0");
};

extern char lbl_80552110[];
extern char lbl_80572278[];
extern char lbl_8057230C[];
extern char lbl_80593DD0[];
extern char lbl_8064AA80[];
extern int lbl_8066C71C;
extern int lbl_8066C724;

extern "C" {

int fn_800797D4(cScript *self);
unsigned int fn_800791C8(cScript *self, unsigned int i);
void fn_8007D404(cScript *self, float seconds, int kind, float a, float b, float c, float d, int e);
int fn_8007D7C4(cScript *self, unsigned char kind);
int fn_8007D8B0(cScript *self);
int fn_8007CF00(cScript *script, int handle, int value);
int fn_80080B34();
int fn_804425F8(void *ev);
void fn_8046B5A8(void *ev, int x);
void fn_8046B5F0(void *ev, int x);
void fn_8046B638(void *ev, int x);
void fn_8046B6C8(void *ev, int x);
void fn_8046B710(void *ev, int x);
void fn_8046B838(void *g, int x);
int fn_80080A44(void *ev);
int fn_800809CC(void *ev);
int fn_8007C034(void *ev);
int fn_80081E6CI(void *ev) __asm__("fn_80081E6C");
SObj *fn_80081E6C(void *ev);
SObj *fn_80080EFC(void *ev);
int fn_80086D24(int p);
int fn_80085EEC(int actor);
int fn_8009B04C(int actor);
void fn_800864F4(int actor, int a);
SBody *fn_800B24AC(SObj &o);
HkRef fn_80317960(SBodyBase &body);
void fn_8006645C(SObj *o, int a);
void fn_80066604(SObj *o);
void fn_80066794(SObj *o, int v);
void *fn_800B1724(SObj *o);
void fn_80065CB0(SObj *o, Vector *v);
void fn_80065D60(SObj *o, Vector *v);
int fn_80393B28(int actor, Arc *a);
void fn_80393938(int actor, Arc *a, int flag);
Arc *fn_803A20D8(char *tbl, char *name, int actor, int b, int c, int d, int e, float f);
void fn_80082AFC(void *ev, int h, int owner, int kind, float a, float b, float c, float d);
void fn_80082440(void *ev, Vector *out);
void fn_800826A8(void *ev, Mat *m);
void fn_800825D0(void *ev, Mat *m);
void fn_80082E90(void *ev, char *name, int a, int b);
void fn_80082E24(void *ev, char *name);
void fn_80083428(void *ev, char *name);
void fn_800820A0(void *ev, int a);
void fn_80082014(void *ev, int v);
void fn_80081F8C(void *ev, int v);
void fn_80080928(void *ev, int a);
int fn_80082190(void *ev, char *name);
int fn_800803DC(void *ev, int id, float f);
void fn_800810DC(void *ev, float f, int a, int b, int c, int d);
float fn_8007C594(void *ev, float dmg, int type, int kind, int src, unsigned int flags);
void fn_800838E0(Vector *at);
float fn_8007C0AC(void *ev);
float fn_8007C244(void *ev);
float fn_8007C3EC(void *ev);
void fn_8007C454(void *ev, float v);
void fn_8007A448(int h);
void fn_8007A4FC(int h);
void fn_8007A738(int h, Vector *to);
void fn_8007B288(int h);
void fn_8007B2E8(int h, int which, float v);
void fn_8007B540(int h, int on, int b);
void fn_8007B618(int h, int on);
void fn_8007BCC8(int h, int on);
void fn_8007BD7C(int h);
int fn_8007BEA8(int h);
float fn_804290F8(void *a, void *b);
void fn_80429038(Vector *out, void *a, void *b);
float fn_8042EC54(Vector *v);
float fn_8042FE6C(Vector *v);
float *fn_8042FB28(Vector *v);
void fn_80435530(Vector *v, float s);
void fn_801BEBBC(Vector *out, void *m, Vector *in);
int fn_801BCB08(Vector *a, Vector *b, float f1, float f2, float *o1, float *o2);
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

void fn_801D5894(cGrandCentral_VenomBoss *self);
void fn_801D58F4(cGrandCentral_VenomBoss *self);
void fn_801D5AEC(cGrandCentral_VenomBoss *self);
void fn_801D5D58(cGrandCentral_VenomBoss *self);
void fn_801D5E00(cGrandCentral_VenomBoss *self);
void fn_801D5EC0(cGrandCentral_VenomBoss *self);
void fn_801D5F28(cGrandCentral_VenomBoss *self);
unsigned int fn_801DA8FC(cGrandCentral_VenomBoss *self);
unsigned int fn_801DA944(cGrandCentral_VenomBoss *self);
unsigned int fn_801DA98C(cGrandCentral_VenomBoss *self);
void fn_801D728C(cGrandCentral_OhmBoss *self);
void fn_801D74E8(cGrandCentral_OhmBoss *self);
void fn_801D7598(cGrandCentral_OhmBoss *self);
void fn_801D764C(cGrandCentral_OhmBoss *self);
void fn_801D76BC(cGrandCentral_OhmBoss *self);
unsigned int fn_801DAA28(cGrandCentral_OhmBoss *self);
unsigned int fn_801DAA70(cGrandCentral_OhmBoss *self);
unsigned int fn_801DAAB8(cGrandCentral_OhmBoss *self);
unsigned int fn_801DAB00(cGrandCentral_OhmBoss *self);
unsigned int fn_801DAB48(cGrandCentral_OhmBoss *self);
unsigned int fn_801DAB90(cGrandCentral_OhmBoss *self);
unsigned int fn_801DABD8(cGrandCentral_OhmBoss *self);
unsigned int fn_801DAC20(cGrandCentral_OhmBoss *self);
unsigned int fn_801DAC68(cGrandCentral_OhmBoss *self);
unsigned int fn_801DACB0(cGrandCentral_OhmBoss *self);
void fn_801D8100(cGrandCentral_HazmatBoss *self);
void fn_801D8248(cGrandCentral_HazmatBoss *self);
void fn_801D82F8(cGrandCentral_HazmatBoss *self);
void fn_801D8394(cGrandCentral_HazmatBoss *self);
void fn_801D8404(cGrandCentral_HazmatBoss *self);
unsigned int fn_801DAD4C(cGrandCentral_HazmatBoss *self);
unsigned int fn_801DAD94(cGrandCentral_HazmatBoss *self);
unsigned int fn_801DADDC(cGrandCentral_HazmatBoss *self);
void fn_801D9230(cGrandCentral_MagnetoBoss *self);
void fn_801D95E4(cGrandCentral_MagnetoBoss *self);
void fn_801D9708(cGrandCentral_MagnetoBoss *self);
void fn_801D98F0(cGrandCentral_MagnetoBoss *self);
void fn_801D99A0(cGrandCentral_MagnetoBoss *self);
void fn_801D9A68(cGrandCentral_MagnetoBoss *self);
void fn_801D9AD8(cGrandCentral_MagnetoBoss *self);
unsigned int fn_801DAE78(cGrandCentral_MagnetoBoss *self);
unsigned int fn_801DAEC0(cGrandCentral_MagnetoBoss *self);
unsigned int fn_801DAF08(cGrandCentral_MagnetoBoss *self);
unsigned int fn_801DAF50(cGrandCentral_MagnetoBoss *self);
unsigned int fn_801DAF98(cGrandCentral_MagnetoBoss *self);
unsigned int fn_801DAFE0(cGrandCentral_MagnetoBoss *self);
unsigned int fn_801DB028(cGrandCentral_MagnetoBoss *self);
unsigned int fn_801DB070(cGrandCentral_MagnetoBoss *self);
unsigned int fn_801DB0B8(cGrandCentral_MagnetoBoss *self);
unsigned int fn_801DB100(cGrandCentral_MagnetoBoss *self);
unsigned int fn_801DB148(cGrandCentral_MagnetoBoss *self);
unsigned int fn_801DB190(cGrandCentral_MagnetoBoss *self);
unsigned int fn_801DB1D8(cGrandCentral_MagnetoBoss *self);
void fn_801DA1E8(cGrandCentral_RockBomb *self);
void fn_801DA2B0(cGrandCentral_RockBomb *self);
unsigned int fn_801DB274(cGrandCentral_RockBomb *self);

void fn_801D5320(register cGrandCentral_VenomBoss *self) // slot 5
{
    fn_8046B710(&self->boss, fn_801DA8FC(self));
    fn_8007CF00(self, fn_804425F8(&self->boss), 0);
    self->f40 = 0;
    self->armored = 0;
    self->f58 = fn_8007C244(&self->boss);
    self->limit = self->f58 / 10.0f;
    self->limit = self->limit * 5.0f;
    self->f58 = self->f58 * 7.0f;
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
    fn_8046B710(&self->player, fn_80080B34());
    fn_8007CF00(self, fn_804425F8(&self->player), 0);
    fn_801D58F4(self);
}

void fn_801D5444(register cGrandCentral_VenomBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_801D5894(self);
        break;
    case 70:
        fn_801D5D58(self);
        break;
    case 71:
        fn_801D5E00(self);
        break;
    case 72:
        fn_801D5EC0(self);
        break;
    case 73:
        fn_801D5F28(self);
        break;
    }
}

float fn_801D5514(register cGrandCentral_VenomBoss *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    fn_8007D404(self, 0.25f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    return damage;
}

void fn_801D55A4(register cGrandCentral_VenomBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
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
            fn_801D5D58(self);
        else
            fn_801D5E00(self);
    } else if (h == fn_804425F8(&self->player)) {
        if (self->playerHit == 0)
            fn_801D5EC0(self);
        else
            fn_801D5F28(self);
    }
    return;
}

int fn_801D56E8(register cGrandCentral_VenomBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    Ref8 r;

    if (h == fn_804425F8(&self->boss)) {
        fn_8046B638(&r, fn_80080B34());
        if (fn_800809CC(&r) && fn_80086D24(fn_800809CC(&r)))
            return 0;
        if (damage > 90000.0f && kind == 8)
            self->bossHit = 1;
        return 1;
    } else if (h == fn_804425F8(&self->player)) {
        fn_8046B638(&r, fn_804425F8(&self->boss));
        if (fn_800809CC(&r) && fn_80086D24(fn_800809CC(&r)))
            return 0;
        if (damage > 90000.0f && kind == 8) {
            self->playerHit = 1;
            return 1;
        }
    }
    return 1;
}

void fn_801D5894(register cGrandCentral_VenomBoss *self)
{
    float hp = fn_8007C0AC(&self->boss);

    if (hp < self->limit) {
        fn_801D5AEC(self);
        return;
    }
}

void fn_801D58F4(register cGrandCentral_VenomBoss *self)
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

void fn_801D5AEC(register cGrandCentral_VenomBoss *self)
{
    int actor = fn_8007C034(&self->boss);

    if (!actor)
        return;
    if (self->armored || fn_80085EEC(actor))
        return;
    self->armored = 1;
    fn_8007B288(fn_804425F8(&self->boss));
    fn_8007B2E8(fn_804425F8(&self->boss), 0, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 1, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 2, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 3, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 4, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 5, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 6, 65.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 7, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 8, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 9, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 10, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 11, 95.0f);
    fn_8007B540(fn_804425F8(&self->boss), 1, 0);
}

void fn_801D5D58(register cGrandCentral_VenomBoss *self)
{
    fn_8007D404(self, 2.0f, 71, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_8057230C, 1);
}

void fn_801D5E00(register cGrandCentral_VenomBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->player));
    lbl_8066C71C = fn_804425F8(&self->player);
    fn_8046B6C8(&ev, fn_801DA98C(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801D5EC0(register cGrandCentral_VenomBoss *self)
{
    fn_8007D404(self, 2.0f, 73, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801D5F28(register cGrandCentral_VenomBoss *self)
{
    Ref8 ev;

    fn_800816A0(fn_804425F8(&self->boss));
    lbl_8066C71C = fn_804425F8(&self->boss);
    fn_8046B6C8(&ev, fn_801DA944(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801D5FE8(register cGrandCentral_OhmBoss *self) // slot 4
{
    self->f80 = 0;
    self->charging = 0;
    self->f88 = 0;
    self->f9C = 0;
    self->f84 = 0;
    self->f8C = 0;
    self->f94 = 0;
    self->f90 = 0;
    self->fA0 = 0;
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
    fn_8046B710(&self->boss, fn_800797D4(self));
    fn_8046B710(&self->r38, fn_801DAA28(self));
    fn_8046B710(&self->r70, fn_801DAC68(self));
    fn_8046B710(&self->r78, fn_801DACB0(self));
    fn_8007CF00(self, fn_804425F8(&self->r38), 0);
    fn_8046B710(&self->r50, fn_801DAAB8(self));
    fn_8046B710(&self->r40, fn_801DAA70(self));
    fn_800826A8(&self->boss, &self->mB0);
    fn_8046B710(&self->r58, fn_801DAB00(self));
    fn_8046B710(&self->r60, fn_801DAB48(self));
    fn_8046B710(&self->r68, fn_801DAB90(self));
    fn_8046B710(&self->player, fn_80080B34());
    fn_8007CF00(self, fn_804425F8(&self->player), 0);
}

void fn_801D61E0(register cGrandCentral_OhmBoss *self) // slot 5
{
    fn_8046B838(lbl_80552110, 1);
}

void fn_801D6220(register cGrandCentral_OhmBoss *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (kind == 0) {
        self->f90 = 2;
        self->f94 = 2;
        fn_801D728C(self);
        if (self->charging == 0)
            fn_8007D404(self, 0.1f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    } else if (kind == 17) {
        if (self->f94 == 1) {
            self->f94 = 2;
            self->f90 = 1;
            fn_8007D404(self, 0.1f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            fn_80083428(&self->boss, "gcJohmCharge");
        } else if (self->f94 == 0) {
            self->f94 = 1;
            fn_8007D404(self, 0.1f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            fn_80082E24(&self->boss, "gcJohmCharge");
            return;
        }
    }
}

float fn_801D63B8(register cGrandCentral_OhmBoss *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h == fn_804425F8(&self->r38) && self->f88 == 1)
        return damage;
    return damage;
}

void fn_801D6444(register cGrandCentral_OhmBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    int actor;
    float hp;

    switch (kind) {
    case 70:
        fn_801D74E8(self);
        break;
    case 71:
        fn_801D7598(self);
        break;
    case 72:
        fn_801D764C(self);
        break;
    case 73:
        fn_801D76BC(self);
        break;
    case 20:
        if (self->charging == 1) {
            actor = fn_8007C034(&self->boss);
            if (self->arc[0]) {
                if (actor && fn_80393B28(actor, self->arc[0]))
                    self->arc[0]->v54();
                else
                    self->arc[0] = 0;
            }
            if (self->arc[1]) {
                if (actor && fn_80393B28(actor, self->arc[1]))
                    self->arc[1]->v54();
                else
                    self->arc[1] = 0;
            }
            if (self->arc[2]) {
                if (actor && fn_80393B28(actor, self->arc[2]))
                    self->arc[2]->v54();
                else
                    self->arc[2] = 0;
            }
            self->charging = 0;
            fn_80083428(&self->boss, "gcJohmCharge");
        }
        if (self->f94 == 2 && self->done == 0)
            fn_8007D404(self, 10.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 10:
        self->charging = 1;
        actor = fn_80081E6CI(&self->boss);
        if (actor) {
            self->arc[0] = fn_803A20D8(lbl_8064AA80, "lightningArc", actor, 0, 0, 0, 0, 0.0f);
            self->arc[1] = fn_803A20D8(lbl_8064AA80, "lightningArc", actor, 0, 0, 0, 0, 0.0f);
            self->arc[2] = fn_803A20D8(lbl_8064AA80, "lightningArc", actor, 0, 0, 0, 0, 0.0f);
            if (self->arc[0]) {
                self->arc[0]->v48(0x15, 1);
                self->arc[0]->v31(fn_804425F8(&self->r58));
                fn_80393938(actor, self->arc[0], 1);
            }
            if (self->arc[1]) {
                self->arc[1]->v48(0x15, 0);
                self->arc[1]->v31(fn_804425F8(&self->r60));
                fn_80393938(actor, self->arc[1], 1);
            }
            if (self->arc[2]) {
                self->arc[2]->v48(0x47, 7);
                self->arc[2]->v31(fn_804425F8(&self->r68));
                fn_80393938(actor, self->arc[2], 1);
            }
        }
        fn_80082E24(&self->boss, "gcJohmCharge");
        hp = fn_8007C3EC(&self->boss);
        hp = hp + 50.0f;
        fn_8007C454(&self->boss, hp);
        if (self->f94 == 2)
            fn_8007D404(self, 3.0f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 50:
        actor = fn_8007C034(&self->boss);
        if (actor)
            fn_800864F4(actor, 0);
        fn_8007A4FC(fn_804425F8(&self->boss));
        break;
    case 35:
        break;
    case 60:
        break;
    }
}

int fn_801D6AB4(register cGrandCentral_OhmBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    Ref8 r;
    int actor;

    if (h == fn_804425F8(&self->boss)) {
        fn_8046B638(&r, fn_80080B34());
        if (fn_800809CC(&r) && fn_80086D24(fn_800809CC(&r)))
            return 0;
        if (damage > 90000.0f && kind == 8)
            self->bossHit = 1;
        return 1;
    } else if (h == fn_804425F8(&self->player)) {
        if (damage > 90000.0f && kind == 8) {
            fn_8046B638(&r, fn_804425F8(&self->boss));
            if (fn_800809CC(&r) && fn_80086D24(fn_800809CC(&r)))
                return 0;
            self->playerHit = 1;
            return 1;
        } else {
            fn_8007D8B0(self);
            if (self->charging == 1) {
                self->charging = 0;
                actor = fn_8007C034(&self->boss);
                if (self->arc[0]) {
                    if (actor && fn_80393B28(actor, self->arc[0]))
                        self->arc[0]->v54();
                    else
                        self->arc[0] = 0;
                }
                if (self->arc[1]) {
                    if (actor && fn_80393B28(actor, self->arc[1]))
                        self->arc[1]->v54();
                    else
                        self->arc[1] = 0;
                }
                if (self->arc[2]) {
                    if (actor && fn_80393B28(actor, self->arc[2]))
                        self->arc[2]->v54();
                    else
                        self->arc[2] = 0;
                }
                return 0;
            }
            fn_8046B638(&r, fn_804425F8(&self->boss));
            if (fn_800809CC(&r) && fn_80086D24(fn_800809CC(&r)))
                return 0;
        }
    }
    return 1;
}

void fn_801D6E58(register cGrandCentral_OhmBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (h == fn_804425F8(&self->r38)) {
        fn_8007B540(fn_804425F8(&self->boss), 0, 0);
        fn_8007B2E8(fn_804425F8(&self->boss), 1, 50.0f);
        if (fn_800809CC(&self->player) && !fn_80085EEC(fn_800809CC(&self->player)))
            fn_8007D8B0(self);
        self->f88 = 0;
        fn_80083428(&self->r38, "gcclockFX");
        fn_80083428(&self->boss, "gcJohmCharge");
        if (self->charging == 1) {
            self->charging = 0;
            self->arc[0]->v54();
            self->arc[1]->v54();
            self->arc[2]->v54();
        }
        fn_8007A4FC(fn_804425F8(&self->boss));
        return;
    }
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
            fn_801D74E8(self);
        else
            fn_801D7598(self);
    } else if (h == fn_804425F8(&self->player)) {
        if (self->playerHit == 0)
            fn_801D764C(self);
        else
            fn_801D76BC(self);
    }
}

void fn_801D7140(register cGrandCentral_OhmBoss *self, int h, int a, int stage, int c, int value) // slot 29
{
    if (h != fn_804425F8(&self->r38))
        return;
    Vector at;
    fn_80082440(&self->r38, &at);
    fn_800838E0(&at);
    Ref8 r;
    if (self->f8C == 0) {
        self->f8C = 1;
        fn_8046B5F0(&r, fn_801DAC68(self));
        fn_800810DC(&r, 100.0f, 3, 0, 0, 0);
        return;
    } else if (self->f8C == 1) {
        self->f8C = 2;
        fn_8046B5F0(&r, fn_801DACB0(self));
        fn_800810DC(&r, 100.0f, 3, 0, 0, 0);
        return;
    }
}

void fn_801D728C(register cGrandCentral_OhmBoss *self)
{
    self->f84 = 1;
    self->f88 = 1;
    fn_8007D404(self, 5.0f, 50, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_80082E24(&self->r38, "gcclockFX");
    fn_8007B288(fn_804425F8(&self->boss));
    fn_8007B2E8(fn_804425F8(&self->boss), 0, 90.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 1, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 2, 10.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 3, 25.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 4, 40.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 5, 25.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 6, 100.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 7, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 8, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 9, 80.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 10, 60.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 11, 90.0f);
}

void fn_801D74E8(register cGrandCentral_OhmBoss *self)
{
    fn_8007D404(self, 2.0f, 71, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_80572278, 1);
}

void fn_801D7598(register cGrandCentral_OhmBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->player));
    fn_8046B6C8(&ev, fn_801DABD8(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801D764C(register cGrandCentral_OhmBoss *self)
{
    fn_8007D404(self, 2.0f, 73, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801D76BC(register cGrandCentral_OhmBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    fn_8046B6C8(&ev, fn_801DAC20(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801D7770(register cGrandCentral_HazmatBoss *self) // slot 4
{
    Ref8 p;

    self->armored = 0;
    self->f4C = 0;
    fn_8046B710(&self->boss, fn_800797D4(self));
    fn_8046B710(&self->r30, fn_801DAD4C(self));
    fn_8046B710(&self->r38, fn_801DAD94(self));
    fn_8046B5A8(&p, fn_80080B34());
    fn_8007CF00(self, fn_804425F8(&p), 0);
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
}

void fn_801D7854(register cGrandCentral_HazmatBoss *self) // slot 5
{
    fn_8046B838(lbl_80552110, 1);
    fn_8007B2E8(fn_804425F8(&self->boss), 5, 20.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 6, 80.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 10, 80.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 11, 80.0f);
}

void fn_801D792C(register cGrandCentral_HazmatBoss *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (self->f4C == 0) {
        self->f4C = 1;
        fn_8007D404(self, 1.0f, 40, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        fn_8007D404(self, 2.0f, 15, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        fn_8007D404(self, 7.0f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
}

float fn_801D7A40(register cGrandCentral_HazmatBoss *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h != fn_804425F8(&self->boss))
        return damage;
    float ratio = fn_8007C0AC(&self->boss) / fn_8007C244(&self->boss);
    if (ratio <= 0.33f && self->armored == 0) {
        self->armored = 1;
        fn_801D8100(self);
        return 0.0f;
    }
    return damage;
}

void fn_801D7B30(register cGrandCentral_HazmatBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_80082AFC(&self->r30, fn_804425F8(&self->r30), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 30:
        fn_80082AFC(&self->r30, fn_804425F8(&self->r30), fn_800797D4(self), 7, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 15:
        fn_80082AFC(&self->r38, fn_804425F8(&self->r38), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 20:
        fn_80082AFC(&self->r38, fn_804425F8(&self->r38), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 40: {
        Ref8 p;

        fn_8046B638(&p, fn_80080B34());
        fn_8007C594(&p, 1.0f, 4, 0, 0, 2);
        fn_8007D404(self, 1.0f, 40, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
    case 42:
        fn_801D8248(self);
        break;
    case 44:
        fn_801D82F8(self);
        break;
    case 46:
        fn_801D8394(self);
        break;
    case 48:
        fn_801D8404(self);
        break;
    }
}

int fn_801D7E04(register cGrandCentral_HazmatBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    Ref8 r;

    fn_8007D7C4(self, 40);
    if (h == fn_804425F8(&self->boss)) {
        fn_8046B638(&r, fn_80080B34());
        if (fn_800809CC(&r) && fn_80086D24(fn_800809CC(&r)))
            return 0;
        if (damage > 90000.0f && kind == 8)
            self->bossHit = 1;
        return 1;
    } else if (h == fn_80080B34()) {
        fn_8046B638(&r, fn_804425F8(&self->boss));
        if (fn_800809CC(&r) && fn_80086D24(fn_800809CC(&r)))
            return 0;
        if (damage > 90000.0f && kind == 8)
            self->playerHit = 1;
        return 1;
    } else {
    }
    return 1;
}

void fn_801D7FC0(register cGrandCentral_HazmatBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (self->done) {
        if (h != fn_80080B34())
            return;
        return;
    }
    self->done = 1;
    fn_8007D7C4(self, 40);
    lbl_8066C724 = 1;
    fn_80081C68();
    fn_80081C94();
    fn_80081CC4();
    fn_80081B40(fn_804425F8(&self->boss));
    if (h == fn_804425F8(&self->boss)) {
        fn_80081A54(fn_80080B34());
        if (self->bossHit == 0)
            fn_801D8248(self);
        else
            fn_801D82F8(self);
    } else if (h == fn_80080B34()) {
        if (self->playerHit == 0)
            fn_801D8394(self);
        else
            fn_801D8404(self);
    } else {
    }
}

void fn_801D8100(register cGrandCentral_HazmatBoss *self)
{
    fn_8007B540(fn_804425F8(&self->boss), 1, 0);
    fn_8007B288(fn_804425F8(&self->boss));
    fn_8007B2E8(fn_804425F8(&self->boss), 0, 80.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 1, 20.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 5, 80.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 6, 20.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 10, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 11, 80.0f);
}

void fn_801D8248(register cGrandCentral_HazmatBoss *self)
{
    fn_8007D404(self, 2.0f, 44, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_8057230C, 1);
}

void fn_801D82F8(register cGrandCentral_HazmatBoss *self)
{
    fn_80081918(fn_80080B34());
    fn_80082AFC(&self->r30, fn_804425F8(&self->r30), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801D8394(register cGrandCentral_HazmatBoss *self)
{
    fn_8007D404(self, 2.0f, 48, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801D8404(register cGrandCentral_HazmatBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    fn_8046B6C8(&ev, fn_801DADDC(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801D84B8(register cGrandCentral_MagnetoBoss *self) // slot 4
{
    self->fB8 = 0;
    self->fC0 = 0;
    self->zone = 0;
    self->fB4 = 0;
    self->f9C = 1;
    self->phase = 0;
    self->fBC = 0;
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
    fn_8046B710(&self->boss, fn_800797D4(self));
    fn_8046B710(&self->player, fn_80080B34());
    fn_8007CF00(self, fn_804425F8(&self->player), 0);
    fn_8046B710(&self->r58, fn_801DAF08(self));
    fn_8046B710(&self->r60, fn_801DAF50(self));
    fn_8046B710(&self->r48, fn_801DAEC0(self));
    fn_8046B710(&self->r40, fn_801DAE78(self));
    fn_8046B710(&self->r50, fn_801DAF98(self));
    fn_8046B710(&self->r38, fn_801DB190(self));
    fn_8007CF00(self, fn_804425F8(&self->r58), 0);
    fn_8007CF00(self, fn_804425F8(&self->r60), 0);
    fn_8046B710(&self->r68[0], fn_801DAFE0(self));
    fn_8046B710(&self->r68[1], fn_801DB028(self));
    fn_8046B710(&self->r68[2], fn_801DB070(self));
    fn_8046B710(&self->r68[3], fn_801DB0B8(self));
    fn_8046B710(&self->r68[4], fn_801DB100(self));
    fn_8046B710(&self->r68[5], fn_801DB148(self));
}

void fn_801D8724(register cGrandCentral_MagnetoBoss *self) // slot 5
{
    self->f9C = 1;
}

void fn_801D8754(register cGrandCentral_MagnetoBoss *self, int h, int other, int value) // slot 14
{
    Ref8 o;

    fn_8046B638(&o, other);
    if (!fn_80080A44(&o))
        return;
    if (h == fn_804425F8(&self->r58))
        self->zone = 2;
    else if (h == fn_804425F8(&self->r60))
        self->zone = 3;
}

void fn_801D8810(register cGrandCentral_MagnetoBoss *self, int h, int other, int value) // slot 15
{
}

float fn_801D8844(register cGrandCentral_MagnetoBoss *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h == fn_804425F8(&self->boss) && self->fB4 == 1) {
        fn_801D9230(self);
        return damage;
    }
    float ratio = (fn_8007C0AC(&self->boss) - damage) / fn_8007C244(&self->boss);
    if (ratio < 0.2f && self->phase == 3 && self->fB4 == 0) {
        self->phase = 4;
        self->fBC = 1;
        self->fA4 = -0.5f;
        fn_8007B2E8(fn_804425F8(&self->boss), 0, 100.0f);
        fn_8007B2E8(fn_804425F8(&self->boss), 7, 100.0f);
        fn_8007B2E8(fn_804425F8(&self->boss), 11, 100.0f);
        return damage;
    } else if (ratio < 0.4f && self->phase == 2 && self->fB4 == 0) {
        self->phase = 3;
        self->fBC = 1;
        self->fA4 = 0.0f;
        fn_8007B2E8(fn_804425F8(&self->boss), 0, 100.0f);
        fn_8007B2E8(fn_804425F8(&self->boss), 7, 100.0f);
        fn_8007B2E8(fn_804425F8(&self->boss), 11, 100.0f);
        return damage;
    } else if (ratio < 0.6f && self->phase == 1 && self->fB4 == 0) {
        self->phase = 2;
        self->fBC = 1;
        self->fA4 = 0.5f;
        fn_8007B2E8(fn_804425F8(&self->boss), 0, 100.0f);
        fn_8007B2E8(fn_804425F8(&self->boss), 7, 100.0f);
        fn_8007B2E8(fn_804425F8(&self->boss), 11, 100.0f);
        return damage;
    } else if (ratio < 0.8f && self->phase == 0 && self->fB4 == 0) {
        self->phase = 1;
        self->fBC = 1;
        self->fA4 = 1.0f;
        fn_8007B2E8(fn_804425F8(&self->boss), 0, 100.0f);
        fn_8007B2E8(fn_804425F8(&self->boss), 7, 100.0f);
        fn_8007B2E8(fn_804425F8(&self->boss), 11, 100.0f);
        return damage;
    }
    if (h == fn_804425F8(&self->player) && self->fBC == 1 && fn_8007BEA8(fn_804425F8(&self->player))) {
        self->fBC = 0;
        self->fB4 = 1;
        fn_8007A448(fn_804425F8(&self->boss));
        fn_801D95E4(self);
    }
    return damage;
}

void fn_801D8C98(register cGrandCentral_MagnetoBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_801D9230(self);
        break;
    case 20:
        fn_801D9708(self);
        break;
    case 30:
        fn_80082AFC(&self->r68[0], fn_804425F8(&self->r68[0]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 31:
        fn_80082AFC(&self->r68[1], fn_804425F8(&self->r68[1]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 32:
        fn_80082AFC(&self->r68[2], fn_804425F8(&self->r68[2]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 33:
        fn_80082AFC(&self->r68[3], fn_804425F8(&self->r68[3]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 34:
        fn_80082AFC(&self->r68[4], fn_804425F8(&self->r68[4]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 35:
        fn_80082AFC(&self->r68[5], fn_804425F8(&self->r68[5]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 40: {
        Ref8 ev;

        fn_8046B6C8(&ev, fn_801DB190(self));
        fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    }
    case 50: {
        Ref8 ev;

        fn_8046B6C8(&ev, fn_801DB190(self));
        fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 7, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    }
    case 60:
        fn_801D98F0(self);
        break;
    case 61:
        fn_801D99A0(self);
        break;
    case 62:
        fn_801D9A68(self);
        break;
    case 63:
        fn_801D9AD8(self);
        break;
    }
}

float fn_801D90D0(register cGrandCentral_MagnetoBoss *self, int h, int node, int value) // slot 37
{
    if (h != fn_804425F8(&self->boss))
        return -1.0f;
    if (self->f9C == 1) {
        self->fB4 = 0;
        fn_8007A4FC(fn_804425F8(&self->boss));
    } else if ((self->f9C == 2 || self->f9C == 3) && self->fB4 == 1) {
        fn_8007B618(fn_804425F8(&self->boss), 1);
        fn_8007BCC8(fn_804425F8(&self->boss), 1);
        fn_8007D404(self, self->fA4 * 6.0f + 6.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        fn_801D9708(self);
    }
    return -1.0f;
}

void fn_801D9230(register cGrandCentral_MagnetoBoss *self)
{
    fn_8007D8B0(self);
    self->fB4 = 0;
    fn_8007B618(fn_804425F8(&self->boss), 0);
    fn_8007BD7C(fn_804425F8(&self->boss));
    fn_8007A4FC(fn_804425F8(&self->boss));
    fn_8007B288(fn_804425F8(&self->boss));
}

int fn_801D92DC(register cGrandCentral_MagnetoBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    Ref8 r;

    if (h == fn_804425F8(&self->boss)) {
        fn_8046B638(&r, fn_80080B34());
        if (fn_800809CC(&r) && fn_80086D24(fn_800809CC(&r)))
            return 0;
        if (damage > 90000.0f && kind == 8)
            self->bossHit = 1;
        return 1;
    } else if (h == fn_804425F8(&self->player)) {
        fn_8046B638(&r, fn_804425F8(&self->boss));
        if (fn_800809CC(&r) && fn_80086D24(fn_800809CC(&r)))
            return 0;
        if (damage > 90000.0f && kind == 8) {
            self->playerHit = 1;
            return 1;
        }
    }
    return 1;
}

void fn_801D9490(register cGrandCentral_MagnetoBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (self->done) {
        if (h != fn_804425F8(&self->player))
            return;
        return;
    }
    fn_8007D7C4(self, 10);
    self->done = 1;
    lbl_8066C724 = 1;
    fn_80081C68();
    fn_80081C94();
    fn_80081CC4();
    fn_80081B40(fn_804425F8(&self->boss));
    if (h == fn_804425F8(&self->boss)) {
        fn_80081A54(fn_804425F8(&self->player));
        if (self->bossHit == 0)
            fn_801D98F0(self);
        else
            fn_801D99A0(self);
    } else if (h == fn_804425F8(&self->player)) {
        if (self->playerHit == 0)
            fn_801D9A68(self);
        else
            fn_801D9AD8(self);
    }
}

void fn_801D95E4(register cGrandCentral_MagnetoBoss *self)
{
    Vector at;
    Vector a;
    Vector b;

    fn_80082440(&self->r48, &a);
    fn_80082440(&self->r40, &b);
    fn_80082440(&self->boss, &at);
    float da = fn_804290F8(&at, &a);
    float db = fn_804290F8(&at, &b);
    if (da < db) {
        fn_8007A738(fn_804425F8(&self->boss), &a);
        self->f9C = 2;
    } else {
        fn_8007A738(fn_804425F8(&self->boss), &b);
        self->f9C = 3;
    }
}

void fn_801D9708(register cGrandCentral_MagnetoBoss *self)
{
    fn_800803DC(&self->boss, 30, 30.0f);
    fn_8007D404(self, self->fA4 + 1.0f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007D404(self, self->fA4 + 2.0f, 31, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007D404(self, self->fA4 + 3.0f, 32, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007D404(self, self->fA4 + 4.0f, 33, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007D404(self, self->fA4 + 5.0f, 34, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007D404(self, self->fA4 + 6.0f, 35, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801D98F0(register cGrandCentral_MagnetoBoss *self)
{
    fn_8007D404(self, 2.0f, 61, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_8057230C, 1);
}

void fn_801D99A0(register cGrandCentral_MagnetoBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->player));
    lbl_8066C71C = fn_804425F8(&self->player);
    fn_8046B6C8(&ev, fn_801DB1D8(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801D9A68(register cGrandCentral_MagnetoBoss *self)
{
    fn_8007D404(self, 2.0f, 63, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801D9AD8(register cGrandCentral_MagnetoBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    lbl_8066C71C = fn_804425F8(&self->boss);
    fn_8046B6C8(&ev, fn_801DB190(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801D9BA0(register cGrandCentral_RockBomb *self) // slot 4
{
    fn_8046B710(&self->obj, fn_800797D4(self));
    fn_8007CF00(self, fn_801DB274(self), 0);
}

void fn_801D9C10(register cGrandCentral_RockBomb *self) // slot 5
{
    fn_800826A8(&self->obj, &self->m60);
    SObj *o = fn_80081E6C(&self->obj);
    if (!o || !fn_800B24AC(*o) || fn_80317960(*fn_800B24AC(*o)).fn_80436294())
        return;
    fn_8006645C(o, 1);
    fn_80066604(o);
    fn_800820A0(&self->obj, 0);
    fn_80081F8C(&self->obj, 2);
}

void fn_801D9D04(register cGrandCentral_RockBomb *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_800820A0(&self->obj, 1);
        fn_80080928(&self->obj, 1);
        break;
    case 40:
        fn_801DA1E8(self);
        break;
    case 50: {
        fn_800820A0(&self->obj, 0);
        fn_80080928(&self->obj, 0);
        Vector at;
        fn_80082440(&self->obj, &at);
        SObj *o = fn_80080EFC(&self->obj);
        if (!o || !fn_800B24AC(*o) || fn_80317960(*fn_800B24AC(*o)).fn_80436294())
            return;
        fn_80066604(o);
        fn_800838E0(&at);
        fn_80082E90(&self->obj, "dirtExpRcks", 0xff, 0xff);
        fn_80082190(&self->obj, "asBoulderSmash");
        fn_80081F8C(&self->obj, 2);
        fn_801DA1E8(self);
        break;
    }
    }
}

void fn_801D9EC8(register cGrandCentral_RockBomb *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    fn_801DA2B0(self);
    fn_8007D404(self, 0.25f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801D9F60(register cGrandCentral_RockBomb *self, int h, int other, int value) // slot 15
{
    if (h == fn_801DB274(self) && other == fn_800797D4(self))
        fn_801DA1E8(self);
}

void fn_801D9FDC(register cGrandCentral_RockBomb *self, int h, int other, int a, int b, int value) // slot 27
{
    Ref8 p;

    fn_8046B5A8(&p, fn_80080B34());
    if (other == fn_80080B34()) {
        fn_8007C594(&p, 20.0f, 0, 0, 0, 0);
        int actor = fn_8007C034(&p);
        if (actor && fn_8009B04C(actor) != 0x6c)
            fn_800803DC(&p, 0x6c, 30.0f);
        fn_8007D404(self, 0.01f, 50, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        return;
    }
    Vector a1;
    Vector a2;
    fn_80082440(&p, &a1);
    fn_80082440(&self->obj, &a2);
    float dist = fn_804290F8(&a1, &a2);
    if (dist < 2.0) {
        fn_8007C594(&p, 10.0f, 0, 0, 0, 0);
        fn_800803DC(&p, 0x69, 30.0f);
    }
    fn_8007D404(self, 0.01f, 50, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801DA1E8(register cGrandCentral_RockBomb *self)
{
    Ref8 r;

    fn_80081F8C(&self->obj, 2);
    fn_800825D0(&self->obj, &self->m60);
    fn_80080928(&self->obj, 0);
    fn_800820A0(&self->obj, 0);
    fn_8046B5F0(&r, fn_800797D4(self));
    SObj *o = fn_80080EFC(&r);
    if (!o)
        return;
    fn_8006645C(o, 1);
    fn_80066604(o);
}

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define INRANGE(x, lo, hi) ((x) >= (lo) ? (x) <= (hi) : 0)

void fn_801DA2B0(register cGrandCentral_RockBomb *self)
{
    Vector pos;
    fn_80082440(&self->obj, &pos);
    Mat m;
    fn_800826A8(&self->obj, &m);
    fn_800825D0(&self->obj, &m);
    fn_80082014(&self->obj, 2);
    Ref8 r;
    fn_8046B5F0(&r, fn_800797D4(self));
    SObj *o1 = fn_80080EFC(&r);
    if (o1) {
        fn_8006645C(o1, 0);
        fn_80066794(o1, 1);
    }
    fn_80082190(&self->obj, "asBoulderSmash");
    fn_800838E0(&pos);
    SObj *o = fn_80081E6C(&self->obj);
    if (!o || !fn_800B24AC(*o) || fn_80317960(*fn_800B24AC(*o)).fn_80436294())
        return;
    Ref8 p;
    fn_8046B638(&p, fn_80080B34());
    SObj *pl = fn_80081E6C(&p);
    if (!pl)
        return;
    pl->v5(&self->target, 0);
    fn_8006645C(o, 0);
    Vector d;
    fn_80429038(&d, &self->target, fn_800B1724(o));
    float len = fn_8042EC54(&d);
    float t = len / 2.0f;
    t = t >= 40.0f ? (t <= 70.0f ? t : 70.0f) : 40.0f;
    float a;
    float b;
    if (!fn_801BCB08(&pos, &self->target, t, 20.0f, &a, &b))
        a = b = 45.0f;
    float lo = -70.0f;
    float hi = 50.0f;
    float ang;
    if (INRANGE(a, lo, hi)) {
        if (INRANGE(b, lo, hi))
            ang = ABS(a) > ABS(b) ? a : b;
        else
            ang = a;
    } else {
        if (INRANGE(b, lo, hi))
            ang = b;
        else
            ang = 45.0f;
    }
    float f = fn_8042FE6C(&d);
    Vector rot;
    fn_8042FB28(&rot)[0] = ang;
    fn_8042FB28(&rot)[2] = f;
    fn_8042FB28(&rot)[1] = 0.0f;
    fn_801BEBBC(&d, lbl_80593DD0, &rot);
    fn_80435530(&d, t);
    fn_80065CB0(o, &d);
    Vector spin;
    spin.x = fn_80171F8C() * 4.656612873077392578125e-10f * 20.0f - 10.0f;
    spin.y = fn_80171F8C() * 4.656612873077392578125e-10f * 20.0f - 10.0f;
    spin.z = fn_80171F8C() * 4.656612873077392578125e-10f * 20.0f - 10.0f;
    fn_80065D60(o, &spin);
}

}

inline int sn_return_decl2(int a) { return a; }

extern "C" {

cScript *fn_801DA8A8(register cGrandCentral_VenomBoss *self)
{
    return new cGrandCentral_VenomBoss;
}

unsigned int fn_801DA8FC(register cGrandCentral_VenomBoss *self) { return fn_800791C8(self, 0); }
unsigned int fn_801DA944(register cGrandCentral_VenomBoss *self) { return fn_800791C8(self, 1); }
unsigned int fn_801DA98C(register cGrandCentral_VenomBoss *self) { return fn_800791C8(self, 2); }

cScript *fn_801DA9D4(register cGrandCentral_OhmBoss *self)
{
    return new cGrandCentral_OhmBoss;
}

unsigned int fn_801DAA28(register cGrandCentral_OhmBoss *self) { return fn_800791C8(self, 0); }
unsigned int fn_801DAA70(register cGrandCentral_OhmBoss *self) { return fn_800791C8(self, 1); }
unsigned int fn_801DAAB8(register cGrandCentral_OhmBoss *self) { return fn_800791C8(self, 3); }
unsigned int fn_801DAB00(register cGrandCentral_OhmBoss *self) { return fn_800791C8(self, 4); }
unsigned int fn_801DAB48(register cGrandCentral_OhmBoss *self) { return fn_800791C8(self, 5); }
unsigned int fn_801DAB90(register cGrandCentral_OhmBoss *self) { return fn_800791C8(self, 6); }
unsigned int fn_801DABD8(register cGrandCentral_OhmBoss *self) { return fn_800791C8(self, 10); }
unsigned int fn_801DAC20(register cGrandCentral_OhmBoss *self) { return fn_800791C8(self, 11); }
unsigned int fn_801DAC68(register cGrandCentral_OhmBoss *self) { return fn_800791C8(self, 13); }
unsigned int fn_801DACB0(register cGrandCentral_OhmBoss *self) { return fn_800791C8(self, 14); }

cScript *fn_801DACF8(register cGrandCentral_HazmatBoss *self)
{
    return new cGrandCentral_HazmatBoss;
}

unsigned int fn_801DAD4C(register cGrandCentral_HazmatBoss *self) { return fn_800791C8(self, 0); }
unsigned int fn_801DAD94(register cGrandCentral_HazmatBoss *self) { return fn_800791C8(self, 1); }
unsigned int fn_801DADDC(register cGrandCentral_HazmatBoss *self) { return fn_800791C8(self, 2); }

cScript *fn_801DAE24(register cGrandCentral_MagnetoBoss *self)
{
    return new cGrandCentral_MagnetoBoss;
}

unsigned int fn_801DAE78(register cGrandCentral_MagnetoBoss *self) { return fn_800791C8(self, 0); }
unsigned int fn_801DAEC0(register cGrandCentral_MagnetoBoss *self) { return fn_800791C8(self, 1); }
unsigned int fn_801DAF08(register cGrandCentral_MagnetoBoss *self) { return fn_800791C8(self, 2); }
unsigned int fn_801DAF50(register cGrandCentral_MagnetoBoss *self) { return fn_800791C8(self, 3); }
unsigned int fn_801DAF98(register cGrandCentral_MagnetoBoss *self) { return fn_800791C8(self, 4); }
unsigned int fn_801DAFE0(register cGrandCentral_MagnetoBoss *self) { return fn_800791C8(self, 6); }
unsigned int fn_801DB028(register cGrandCentral_MagnetoBoss *self) { return fn_800791C8(self, 7); }
unsigned int fn_801DB070(register cGrandCentral_MagnetoBoss *self) { return fn_800791C8(self, 8); }
unsigned int fn_801DB0B8(register cGrandCentral_MagnetoBoss *self) { return fn_800791C8(self, 9); }
unsigned int fn_801DB100(register cGrandCentral_MagnetoBoss *self) { return fn_800791C8(self, 10); }
unsigned int fn_801DB148(register cGrandCentral_MagnetoBoss *self) { return fn_800791C8(self, 11); }
unsigned int fn_801DB190(register cGrandCentral_MagnetoBoss *self) { return fn_800791C8(self, 12); }
unsigned int fn_801DB1D8(register cGrandCentral_MagnetoBoss *self) { return fn_800791C8(self, 14); }

cScript *fn_801DB220(register cGrandCentral_RockBomb *self)
{
    return new cGrandCentral_RockBomb;
}

unsigned int fn_801DB274(register cGrandCentral_RockBomb *self) { return fn_800791C8(self, 0); }

}
