// The Brooklyn Bridge classes cBrooklynBridge_heliCrash, cBB_ArenaShutoff, cBrooklynBridge_ArenaBarrier, _AftershockBoss, _VM2_Start, _SegmentControl,
// _BruteFight, _WolverineSAC, _RockBomb, _FlameWall, _HazmatBoss and _AltStormBoss (docs/story.md row 20).
// Pool read from 0x8049F858 (extern_pool).

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

struct cBrooklynBridge_heliCrash : cScript { // 0x48
    Ref8 heli;      // +0x28
    Ref8 r30[3];    // +0x30, params 0-2
    cBrooklynBridge_heliCrash() __asm__("fn_8046A068");
};

struct cBB_ArenaShutoff : cScript { // 0x28
    cBB_ArenaShutoff() __asm__("fn_8046A0E4");
};

struct cBrooklynBridge_ArenaBarrier : cScript { // 0x34
    int active;     // +0x28
    Ref8 obj;       // +0x2C
    cBrooklynBridge_ArenaBarrier() __asm__("fn_8046A130");
};

struct cBrooklynBridge_AftershockBoss : cScript { // 0x144
    Ref8 boss;      // +0x28
    Ref8 player;    // +0x30
    Ref8 r38;       // +0x38, param 0
    Ref8 r40;       // +0x40, param 1
    Ref8 r48;       // +0x48, param 4
    Ref8 r50;       // +0x50, param 2
    Ref8 r58;       // +0x58, param 3
    Ref8 r60[6];    // +0x60, params 6-11
    int zone;       // +0x90
    int f94;        // +0x94
    int phase;      // +0x98
    float f9C;      // +0x9C
    char padA0[8];
    int fA8;        // +0xA8
    int fAC;        // +0xAC
    int fB0;        // +0xB0
    int fB4;        // +0xB4
    int done;       // +0xB8
    int bossHit;    // +0xBC
    int playerHit;  // +0xC0
    Mat mC4;        // +0xC4
    Mat m104;       // +0x104
    cBrooklynBridge_AftershockBoss() __asm__("fn_8046A188");
};

struct cBrooklynBridge_VM2_Start : cScript { // 0x80
    Ref8 r28[9];    // +0x28, params 0-8
    int f70[4];     // +0x70
    cBrooklynBridge_VM2_Start() __asm__("fn_8046A290");
};

struct cBrooklynBridge_SegmentControl : cScript { // 0x2C
    int started;    // +0x28
    cBrooklynBridge_SegmentControl() __asm__("fn_8046A348");
};

struct cBrooklynBridge_BruteFight : cScript { // 0x2C
    int done;       // +0x28
    cBrooklynBridge_BruteFight() __asm__("fn_8046A394");
};

struct cBrooklynBridge_WolverineSAC : cScript { // 0x54
    Ref8 boss;      // +0x28, param 0
    Ref8 r30;       // +0x30, param 1
    int stage1;     // +0x38
    int stage2;     // +0x3C
    int bossHit;    // +0x40
    int playerHit;  // +0x44
    int done;       // +0x48
    float limit1;   // +0x4C
    float limit2;   // +0x50
    cBrooklynBridge_WolverineSAC() __asm__("fn_8046A3E0");
};

struct cBrooklynBridge_RockBomb : cScript { // 0xA0
    Ref8 obj;       // +0x28
    Ref8 shock;     // +0x30, the actor named AFTERSHOCK
    Ref8 r38;       // +0x38
    char pad40[0x10];
    Vector target;  // +0x50
    Mat m60;        // +0x60
    cBrooklynBridge_RockBomb() __asm__("fn_8046A448");
};

struct cBrooklynBridge_FlameWall : cScript { // 0x34
    int f28;        // +0x28
    Ref8 obj;       // +0x2C
    cBrooklynBridge_FlameWall() __asm__("fn_8046A4D8");
};

struct cBrooklynBridge_HazmatBoss : cScript { // 0x44
    Ref8 boss;      // +0x28
    Ref8 player;    // +0x30
    int done;       // +0x38
    int bossHit;    // +0x3C
    int playerHit;  // +0x40
    cBrooklynBridge_HazmatBoss() __asm__("fn_8046A530");
};

struct cBrooklynBridge_AltStormBoss : cScript { // 0x44
    Ref8 boss;      // +0x28
    Ref8 player;    // +0x30
    int done;       // +0x38
    int bossHit;    // +0x3C
    int playerHit;  // +0x40
    cBrooklynBridge_AltStormBoss() __asm__("fn_8046A59C");
};


extern "C" int stricmp(const char *a, const char *b);
extern char lbl_805526EC[];
extern char lbl_80593DD0[];
extern char lbl_80593BE8[];
extern unsigned int lbl_8066C720;
extern char lbl_80552110[];
extern char lbl_80572278[];
extern char lbl_8057230C[];
extern int lbl_8066C71C;
extern int lbl_8066C724;

extern "C" {

void fn_80065CB0(SObj *o, Vector *v);
void fn_80065D60(SObj *o, Vector *v);
void fn_8006645C(SObj *o, int a);
void fn_80066604(SObj *o);
void fn_80066794(SObj *o, int v);
unsigned int fn_800791C8(cScript *self, unsigned int i);
int fn_800797D4(cScript *self);
void fn_8007A448(int h);
void fn_8007A4FC(int h);
void fn_8007A738(int h, Vector *to);
void fn_8007B288(int h);
void fn_8007B2E8(int h, int which, float v);
void fn_8007B540(int h, int on, int b);
void fn_8007B618(int h, int on);
void fn_8007BA24(int h, int state);
void fn_8007BAA0(int h);
void fn_8007BB24(int h);
int fn_8007BEA8(int h);
int fn_8007C034(void *ev);
float fn_8007C0AC(void *ev);
float fn_8007C114(void *ev, float v);
float fn_8007C244(void *ev);
float fn_8007C2AC(void *ev);
void fn_8007C314(void *ev, float v);
float fn_8007C3EC(void *ev);
void fn_8007C454(void *ev, float v);
void fn_8007C740(void *ev, int id, int a, int b, float f, int c);
int fn_8007CF00(cScript *script, int handle, int value);
void fn_8007D404(cScript *self, float seconds, int kind, float a, float b, float c, float d, int e);
int fn_8007D7C4(cScript *self, unsigned char kind);
int fn_8007D8B0(cScript *self);
void fn_80080928(void *ev, int a);
int fn_800809CC(void *ev);
int fn_80080A44(void *ev);
int fn_80080B34();
SObj *fn_80080EFC(void *ev);
void fn_800816A0(int h);
void fn_80081918(int h);
int fn_80081A54(int h);
int fn_80081B40(int h);
int fn_80081BD4(int h);
void fn_80081C68();
void fn_80081C94();
void fn_80081CC4();
SObj *fn_80081E6C(void *ev);
void fn_80081F8C(void *ev, int v);
void fn_80082014(void *ev, int v);
void fn_800820A0(void *ev, int a);
void fn_80082124(void *ev);
int fn_80082190(void *ev, char *name);
void fn_80082440(void *ev, Vector *out);
void fn_800825D0(void *ev, Mat *m);
void fn_800826A8(void *ev, Mat *m);
void fn_80082A44(void *ev, int node, float speed, int a);
void fn_80082AFC(void *ev, int h, int owner, int kind, float a, float b, float c, float d);
void fn_80082E24(void *ev, char *name);
void fn_80082E90(void *ev, char *name, int a, int b);
void fn_80082F30(void *ev);
void fn_80082FA4(void *ev);
void fn_80083428(void *ev, char *name);
int fn_80083734(char *name);
void fn_800838E0(Vector *at);
void fn_80083EE8(unsigned int ms, float strength, int c);
int fn_80085EEC(int a);
void fn_80086410(int a);
void fn_8008643C(int a);
int fn_80086D24(int p);
int fn_8009B04C(int actor);
void *fn_800B1724(SObj *o);
SBody *fn_800B24AC(SObj &o);
void fn_801337F0(int a, int b);
void fn_80133838(int a);
int fn_80171F8C();
int fn_801BCB08(Vector *a, Vector *b, float f1, float f2, float *o1, float *o2);
void fn_801BEBBC(Vector *out, void *m, Vector *in);
HkRef fn_80317960(SBodyBase &body);
int fn_80393D0C(SObj *o, char *name, int a, int b);
void fn_80429038(Vector *out, void *a, void *b);
float fn_804290F8(void *a, void *b);
float *fn_8042DC3C(void *m, int row, int col);
float fn_8042EC54(Vector *v);
unsigned int fn_8042EFF8(void *clock);
float *fn_8042FB28(Vector *v);
float fn_8042FE6C(Vector *v);
void fn_8043323C(void *p, int on);
void fn_80435530(Vector *v, float s);
int fn_804425F8(void *ev);
void fn_8046B530(void *ev);
void fn_8046B5A8(void *ev, int x);
void fn_8046B5F0(void *ev, int x);
void fn_8046B638(void *ev, int x);
void fn_8046B680(void *ev, int x);
void fn_8046B6C8(void *ev, int x);
void fn_8046B710(void *ev, int x);
void fn_8046B838(void *g, int x);
void fn_8046BBA0(void *ev, int x);
void fn_8046BBE8();
void fn_8046BC0C();

void fn_801CBB00(cBrooklynBridge_AftershockBoss *self);
void fn_801CBBB4(cBrooklynBridge_AftershockBoss *self);
void fn_801CBCF8(cBrooklynBridge_AftershockBoss *self);
void fn_801CBF80(cBrooklynBridge_AftershockBoss *self);
void fn_801CC030(cBrooklynBridge_AftershockBoss *self);
void fn_801CC0E4(cBrooklynBridge_AftershockBoss *self);
void fn_801CC154(cBrooklynBridge_AftershockBoss *self);
void fn_801CCDC8(cBrooklynBridge_VM2_Start *self);
void fn_801CD288(cBrooklynBridge_SegmentControl *self);
void fn_801CD49C(cBrooklynBridge_SegmentControl *self);
void fn_801CD6D4(cBrooklynBridge_SegmentControl *self);
void fn_801CD77C(cBrooklynBridge_SegmentControl *self);
void fn_801CDD08(cBrooklynBridge_BruteFight *self);
void fn_801CDDB0(cBrooklynBridge_BruteFight *self);
void fn_801CE3E8(cBrooklynBridge_WolverineSAC *self);
void fn_801CE47C(cBrooklynBridge_WolverineSAC *self);
void fn_801CE664(cBrooklynBridge_WolverineSAC *self);
void fn_801CE86C(cBrooklynBridge_WolverineSAC *self);
void fn_801CE914(cBrooklynBridge_WolverineSAC *self);
void fn_801CE9C0(cBrooklynBridge_WolverineSAC *self);
void fn_801CEA28(cBrooklynBridge_WolverineSAC *self);
void fn_801CF094(cBrooklynBridge_RockBomb *self);
void fn_801CF15C(cBrooklynBridge_RockBomb *self);
void fn_801D00F0(cBrooklynBridge_HazmatBoss *self);
void fn_801D01A0(cBrooklynBridge_HazmatBoss *self);
void fn_801D0254(cBrooklynBridge_HazmatBoss *self);
void fn_801D02C4(cBrooklynBridge_HazmatBoss *self);
void fn_801D07EC(cBrooklynBridge_AltStormBoss *self);
void fn_801D08B4(cBrooklynBridge_AltStormBoss *self);
void fn_801D0968(cBrooklynBridge_AltStormBoss *self);
void fn_801D09D8(cBrooklynBridge_AltStormBoss *self);
unsigned int fn_801D0AE0(cBrooklynBridge_heliCrash *self);
unsigned int fn_801D0B28(cBrooklynBridge_heliCrash *self);
unsigned int fn_801D0B70(cBrooklynBridge_heliCrash *self);
unsigned int fn_801D0C0C(cBB_ArenaShutoff *self);
unsigned int fn_801D0C54(cBB_ArenaShutoff *self);
unsigned int fn_801D0C9C(cBB_ArenaShutoff *self);
unsigned int fn_801D0D8C(cBrooklynBridge_AftershockBoss *self);
unsigned int fn_801D0DD4(cBrooklynBridge_AftershockBoss *self);
unsigned int fn_801D0E1C(cBrooklynBridge_AftershockBoss *self);
unsigned int fn_801D0E64(cBrooklynBridge_AftershockBoss *self);
unsigned int fn_801D0EAC(cBrooklynBridge_AftershockBoss *self);
unsigned int fn_801D0EF4(cBrooklynBridge_AftershockBoss *self);
unsigned int fn_801D0F3C(cBrooklynBridge_AftershockBoss *self);
unsigned int fn_801D0F84(cBrooklynBridge_AftershockBoss *self);
unsigned int fn_801D0FCC(cBrooklynBridge_AftershockBoss *self);
unsigned int fn_801D1014(cBrooklynBridge_AftershockBoss *self);
unsigned int fn_801D105C(cBrooklynBridge_AftershockBoss *self);
unsigned int fn_801D10A4(cBrooklynBridge_AftershockBoss *self);
unsigned int fn_801D10EC(cBrooklynBridge_AftershockBoss *self);
unsigned int fn_801D1188(cBrooklynBridge_VM2_Start *self);
unsigned int fn_801D11D0(cBrooklynBridge_VM2_Start *self);
unsigned int fn_801D1218(cBrooklynBridge_VM2_Start *self);
unsigned int fn_801D1260(cBrooklynBridge_VM2_Start *self);
unsigned int fn_801D12A8(cBrooklynBridge_VM2_Start *self);
unsigned int fn_801D12F0(cBrooklynBridge_VM2_Start *self);
unsigned int fn_801D1338(cBrooklynBridge_VM2_Start *self);
unsigned int fn_801D1380(cBrooklynBridge_VM2_Start *self);
unsigned int fn_801D13C8(cBrooklynBridge_VM2_Start *self);
unsigned int fn_801D1464(cBrooklynBridge_SegmentControl *self);
unsigned int fn_801D14AC(cBrooklynBridge_SegmentControl *self);
unsigned int fn_801D14F4(cBrooklynBridge_SegmentControl *self);
unsigned int fn_801D153C(cBrooklynBridge_SegmentControl *self);
unsigned int fn_801D1584(cBrooklynBridge_SegmentControl *self);
unsigned int fn_801D15CC(cBrooklynBridge_SegmentControl *self);
unsigned int fn_801D1614(cBrooklynBridge_SegmentControl *self);
unsigned int fn_801D165C(cBrooklynBridge_SegmentControl *self);
unsigned int fn_801D16A4(cBrooklynBridge_SegmentControl *self);
unsigned int fn_801D1740(cBrooklynBridge_BruteFight *self);
unsigned int fn_801D17DC(cBrooklynBridge_WolverineSAC *self);
unsigned int fn_801D1824(cBrooklynBridge_WolverineSAC *self);
unsigned int fn_801D186C(cBrooklynBridge_WolverineSAC *self);
unsigned int fn_801D1908(cBrooklynBridge_RockBomb *self);
unsigned int fn_801D19A4(cBrooklynBridge_FlameWall *self);
unsigned int fn_801D19EC(cBrooklynBridge_FlameWall *self);
unsigned int fn_801D1A88(cBrooklynBridge_HazmatBoss *self);
unsigned int fn_801D1AD0(cBrooklynBridge_HazmatBoss *self);
unsigned int fn_801D1B6C(cBrooklynBridge_AltStormBoss *self);
unsigned int fn_801D1BB4(cBrooklynBridge_AltStormBoss *self);

void fn_801CA72C(register cBrooklynBridge_heliCrash *self) // slot 4
{
    fn_8046B710(&self->heli, fn_800797D4(self));
    fn_80082F30(&self->heli);
}

void fn_801CA784(register cBrooklynBridge_heliCrash *self, int a, int b, int kind, float c, float d, float e, float f, int value) // slot 23
{
    SObj *o;

    fn_80082FA4(&self->heli);
    o = fn_80081E6C(&self->heli);
    if (o)
        fn_80393D0C(o, "fireHuge", 0xff, 0xff);
    fn_80082A44(&self->heli, 1, 20.0f, 0);
}

void fn_801CA834(register cBrooklynBridge_heliCrash *self, int h, int other, int value) // slot 25
{
    if (h == fn_804425F8(&self->heli)) {
        fn_80082190(&self->heli, "exp_large");
        fn_8046B710(&self->r30[0], fn_801D0AE0(self));
        fn_8046B710(&self->r30[1], fn_801D0B28(self));
        fn_8046B710(&self->r30[2], fn_801D0B70(self));
        fn_80082190(&self->r30[0], "exp_MediumFake");
        fn_80082190(&self->r30[1], "exp_MediumFake");
        fn_80082190(&self->r30[2], "exp_MediumFake");
        Vector at;
        fn_80082440(&self->heli, &at);
        fn_80083EE8(2000, 0.25f, 1);
        fn_80082124(&self->heli);
    }
}

void fn_801CA970(register cBB_ArenaShutoff *self, int a, int b, int kind, float c, float d, float e, float f, int value) // slot 23
{
    Ref8 p;
    Ref8 r;

    fn_8046B638(&p, fn_80080B34());
    fn_8046B6C8(&r, fn_801D0C0C(self));
    Mat m;
    fn_800826A8(&r, &m);
    fn_800825D0(&p, &m);
    Ref8 e1;
    Ref8 e2;
    fn_8046B6C8(&e1, fn_801D0C54(self));
    fn_8046B6C8(&e2, fn_801D0C9C(self));
    fn_80082AFC(&e1, fn_801D0C54(self), fn_800797D4(self), 0, 1.0f, 0.0f, 0.0f, 0.0f);
    fn_80082AFC(&e2, fn_801D0C9C(self), fn_800797D4(self), 0, 1.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801CAB00(register cBrooklynBridge_ArenaBarrier *self) // slot 5
{
    self->active = 1;
    fn_8046B710(&self->obj, fn_800797D4(self));
    fn_800820A0(&self->obj, 0);
    fn_80081F8C(&self->obj, 2);
}

void fn_801CAB74(register cBrooklynBridge_ArenaBarrier *self, int a, int b, int kind, float c, float d, float e, float f, int value) // slot 23
{
    switch (kind) {
    case 0:
        fn_800820A0(&self->obj, 1);
        fn_80082014(&self->obj, 2);
        break;
    case 4:
        self->active = 0;
        break;
    }
}

float fn_801CAC14(register cBrooklynBridge_ArenaBarrier *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (self->active == 1)
        return -1.0f;
    else
        return damage;
}

void fn_801CAC80(register cBrooklynBridge_AftershockBoss *self) // slot 4
{
    self->zone = 0;
    self->f94 = 1;
    self->phase = 0;
    self->fAC = 0;
    self->fB4 = 0;
    self->fA8 = 0;
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
    fn_8046B710(&self->boss, fn_800797D4(self));
    fn_8046B710(&self->player, fn_80080B34());
    fn_8007CF00(self, fn_804425F8(&self->player), 0);
    fn_8046B710(&self->r50, fn_801D0E1C(self));
    fn_8046B710(&self->r58, fn_801D0E64(self));
    fn_8046B710(&self->r40, fn_801D0DD4(self));
    fn_800826A8(&self->r40, &self->mC4);
    fn_8046B710(&self->r38, fn_801D0D8C(self));
    fn_800826A8(&self->r38, &self->m104);
    fn_8046B710(&self->r48, fn_801D0EAC(self));
    fn_8007CF00(self, fn_804425F8(&self->r50), 0);
    fn_8007CF00(self, fn_804425F8(&self->r58), 0);
    fn_8046B710(&self->r60[0], fn_801D0F3C(self));
    fn_8046B710(&self->r60[1], fn_801D0F84(self));
    fn_8046B710(&self->r60[2], fn_801D0FCC(self));
    fn_8046B710(&self->r60[3], fn_801D1014(self));
    fn_8046B710(&self->r60[4], fn_801D105C(self));
    fn_8046B710(&self->r60[5], fn_801D10A4(self));
}

void fn_801CAEF0(register cBrooklynBridge_AftershockBoss *self) // slot 5
{
    self->f94 = 1;
    fn_8046B838(lbl_80552110, 1);
}

void fn_801CAF40(register cBrooklynBridge_AftershockBoss *self, int h, int other, int value) // slot 14
{
    Ref8 o;

    fn_8046B638(&o, other);
    if (!fn_80080A44(&o))
        return;
    if (h == fn_804425F8(&self->r50))
        self->zone = 2;
    else if (h == fn_804425F8(&self->r58))
        self->zone = 3;
}

float fn_801CAFFC(register cBrooklynBridge_AftershockBoss *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h == fn_804425F8(&self->boss)) {
        float ratio = (fn_8007C0AC(&self->boss) - damage) / fn_8007C244(&self->boss);
        if (ratio < 0.2f && self->phase == 3 && self->fA8 == 0 && self->fB4 == 0) {
            self->phase = 4;
            self->f9C = 0.0f;
            fn_801CBB00(self);
            return damage;
        } else if (ratio < 0.4f && self->phase == 2 && self->fA8 == 0 && self->fB4 == 0) {
            self->phase = 3;
            self->f9C = 0.5f;
            fn_801CBB00(self);
            return damage;
        } else if (ratio < 0.6f && self->phase == 1 && self->fA8 == 0 && self->fB4 == 0) {
            self->phase = 2;
            self->f9C = 1.0f;
            fn_801CBB00(self);
            return damage;
        } else if (ratio < 0.8f && self->phase == 0 && self->fA8 == 0 && self->fB4 == 0) {
            self->phase = 1;
            self->f9C = 1.5f;
            fn_801CBB00(self);
            return damage;
        }
    }
    if (h == fn_804425F8(&self->player) && self->fB4 == 1 && fn_8007BEA8(fn_804425F8(&self->player))) {
        self->fB4 = 0;
        fn_801CBBB4(self);
        return damage;
    }
    return damage;
}

int fn_801CB29C(register cBrooklynBridge_AftershockBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
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

void fn_801CB448(register cBrooklynBridge_AftershockBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
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
            fn_801CBF80(self);
        else
            fn_801CC030(self);
    } else if (h == fn_804425F8(&self->player)) {
        if (self->playerHit == 0)
            fn_801CC0E4(self);
        else
            fn_801CC154(self);
    }
}

void fn_801CB588(register cBrooklynBridge_AftershockBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 46:
        fn_801CBF80(self);
        break;
    case 47:
        fn_801CC030(self);
        break;
    case 48:
        fn_801CC0E4(self);
        break;
    case 49:
        fn_801CC154(self);
        break;
    case 10:
        fn_8007B618(fn_804425F8(&self->boss), 0);
        fn_8007BB24(fn_804425F8(&self->boss));
        fn_8007B288(fn_804425F8(&self->boss));
        self->fA8 = 0;
        fn_8007A4FC(fn_804425F8(&self->boss));
        self->f94 = 1;
        break;
    case 20:
        fn_801CBCF8(self);
        break;
    case 30:
        fn_80082AFC(&self->r60[0], fn_804425F8(&self->r60[0]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 31:
        fn_80082AFC(&self->r60[1], fn_804425F8(&self->r60[1]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 32:
        fn_80082AFC(&self->r60[2], fn_804425F8(&self->r60[2]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 33:
        fn_80082AFC(&self->r60[3], fn_804425F8(&self->r60[3]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 34:
        fn_80082AFC(&self->r60[4], fn_804425F8(&self->r60[4]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 35:
        fn_80082AFC(&self->r60[5], fn_804425F8(&self->r60[5]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 40: {
        Ref8 ev;

        fn_8046B6C8(&ev, fn_801D0EF4(self));
        fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    }
    case 45: {
        Ref8 ev;

        fn_8046B6C8(&ev, fn_801D10EC(self));
        fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 7, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    }
    }
}

float fn_801CBA2C(register cBrooklynBridge_AftershockBoss *self, int h, int node, int value) // slot 37
{
    if (h != fn_804425F8(&self->boss))
        return -1.0f;
    if (self->fA8 == 1) {
        if (self->f94 == 3)
            fn_800825D0(&self->boss, &self->m104);
        if (self->f94 == 2)
            fn_800825D0(&self->boss, &self->mC4);
        self->fB0 = 0;
        fn_801CBCF8(self);
    }
    return -1.0f;
}

void fn_801CBB00(register cBrooklynBridge_AftershockBoss *self)
{
    self->fB4 = 1;
    self->fA8 = 1;
    fn_8007B2E8(fn_804425F8(&self->boss), 0, 100.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 7, 100.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 11, 100.0f);
}

void fn_801CBBB4(register cBrooklynBridge_AftershockBoss *self)
{
    self->fB0 = 1;
    fn_8007A448(fn_804425F8(&self->boss));
    Vector at;
    Vector a;
    Vector b;

    fn_80082440(&self->r40, &a);
    fn_80082440(&self->r38, &b);
    fn_80082440(&self->boss, &at);
    float da = fn_804290F8(&at, &a);
    float db = fn_804290F8(&at, &b);
    if (da < db) {
        fn_8007A738(fn_804425F8(&self->boss), &a);
        self->f94 = 2;
    } else {
        fn_8007A738(fn_804425F8(&self->boss), &b);
        self->f94 = 3;
    }
}

void fn_801CBCF8(register cBrooklynBridge_AftershockBoss *self)
{
    float hp = fn_8007C3EC(&self->boss);

    if (hp < 25.0f)
        fn_8007C454(&self->boss, 25.0f);
    fn_8007B618(fn_804425F8(&self->boss), 1);
    fn_8007BAA0(fn_804425F8(&self->boss));
    float t = self->f9C + 5.0f;
    fn_8007D404(self, t, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007D404(self, self->f9C + 0.0f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007D404(self, self->f9C + 1.0f, 31, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007D404(self, self->f9C + 2.0f, 32, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007D404(self, self->f9C + 3.0f, 33, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007D404(self, self->f9C + 4.0f, 34, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007D404(self, self->f9C + 5.0f, 35, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801CBF80(register cBrooklynBridge_AftershockBoss *self)
{
    fn_8007D404(self, 2.0f, 47, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_80572278, 1);
}

void fn_801CC030(register cBrooklynBridge_AftershockBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->player));
    fn_8046B6C8(&ev, fn_801D0EF4(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801CC0E4(register cBrooklynBridge_AftershockBoss *self)
{
    fn_8007D404(self, 2.0f, 49, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801CC154(register cBrooklynBridge_AftershockBoss *self)
{
    fn_800816A0(fn_804425F8(&self->boss));
    Ref8 ev;

    fn_8046B6C8(&ev, fn_801D10EC(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 7, 0.0f, 0.0f, 0.0f, 0.0f);
}


void fn_801CC208(register cBrooklynBridge_VM2_Start *self) // slot 5
{
    fn_8046B710(&self->r28[0], fn_801D1188(self));
    fn_8046B710(&self->r28[1], fn_801D11D0(self));
    fn_8046B710(&self->r28[2], fn_801D1218(self));
    fn_8046B710(&self->r28[3], fn_801D1260(self));
    fn_8046B710(&self->r28[4], fn_801D12A8(self));
    fn_8046B710(&self->r28[5], fn_801D12F0(self));
    fn_8046B710(&self->r28[6], fn_801D1338(self));
    fn_8046B710(&self->r28[7], fn_801D1380(self));
    fn_8046B710(&self->r28[8], fn_801D13C8(self));
    self->f70[0] = 1;
    self->f70[1] = 1;
    self->f70[2] = 1;
    self->f70[3] = 1;
}

void fn_801CC35C(register cBrooklynBridge_VM2_Start *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 30:
        fn_80082AFC(&self->r28[4], fn_804425F8(&self->r28[4]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 40:
        fn_80082AFC(&self->r28[5], fn_804425F8(&self->r28[5]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 50:
        fn_80082AFC(&self->r28[6], fn_804425F8(&self->r28[6]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 60:
        fn_80082AFC(&self->r28[7], fn_804425F8(&self->r28[7]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 70: {
        Ref8 p;

        fn_8046B638(&p, fn_80080B34());
    }
    }
}

void fn_801CC568(register cBrooklynBridge_VM2_Start *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (other == fn_80080B34()) {
        if (h == fn_804425F8(&self->r28[0])) {
            self->f70[0] = 0;
            fn_80082AFC(&self->r28[8], fn_804425F8(&self->r28[8]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            fn_80082AFC(&self->r28[4], fn_804425F8(&self->r28[4]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            fn_8007D404(self, 7.5f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            fn_801CCDC8(self);
        }
        if (h == fn_804425F8(&self->r28[1])) {
            self->f70[1] = 0;
            fn_80082AFC(&self->r28[8], fn_804425F8(&self->r28[8]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            fn_80082AFC(&self->r28[5], fn_804425F8(&self->r28[4]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            fn_8007D404(self, 7.5f, 40, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            fn_801CCDC8(self);
        }
        if (h == fn_804425F8(&self->r28[2])) {
            self->f70[2] = 0;
            fn_80082AFC(&self->r28[8], fn_804425F8(&self->r28[8]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            fn_80082AFC(&self->r28[6], fn_804425F8(&self->r28[4]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            fn_8007D404(self, 7.5f, 50, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            fn_801CCDC8(self);
        }
        if (h == fn_804425F8(&self->r28[3])) {
            self->f70[3] = 0;
            fn_80082AFC(&self->r28[8], fn_804425F8(&self->r28[8]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            fn_80082AFC(&self->r28[7], fn_804425F8(&self->r28[4]), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            fn_8007D404(self, 7.5f, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            fn_801CCDC8(self);
        }
        return;
    } else {
        return;
    }
}

void fn_801CCA08(register cBrooklynBridge_VM2_Start *self, int a, int b, int kind, float x, float y, float z, float w) // slot 24
{
    if ((unsigned int)y == fn_804425F8(&self->r28[0])) {
        fn_8046B710(&self->r28[0], (unsigned int)x);
        fn_8007CF00(self, fn_804425F8(&self->r28[0]), 0);
    } else if ((unsigned int)y == fn_804425F8(&self->r28[1])) {
        fn_8046B710(&self->r28[1], (unsigned int)x);
        fn_8007CF00(self, fn_804425F8(&self->r28[1]), 0);
    } else if ((unsigned int)y == fn_804425F8(&self->r28[2])) {
        fn_8046B710(&self->r28[2], (unsigned int)x);
        fn_8007CF00(self, fn_804425F8(&self->r28[2]), 0);
    } else if ((unsigned int)y == fn_804425F8(&self->r28[3])) {
        fn_8046B710(&self->r28[3], (unsigned int)x);
        fn_8007CF00(self, fn_804425F8(&self->r28[3]), 0);
    }
}

void fn_801CCDC8(register cBrooklynBridge_VM2_Start *self)
{
    Ref8 p;

    fn_8046B638(&p, fn_80080B34());
    float max = fn_8007C244(&p);
    float add = max / 4.0f;
    fn_80082E90(&p, "venomRecharge", 0xff, 0xff);
    fn_8007C114(&p, fn_8007C0AC(&p) + add);
    fn_8007C314(&p, fn_8007C2AC(&p) + add);
    fn_8007D404(self, 3.0f, 70, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}


void fn_801CCEC8(register cBrooklynBridge_SegmentControl *self) // slot 5
{
    self->started = 0;
    if (stricmp(lbl_805526EC, "Thing_1") == 0) {
        fn_8007D404(self, 0.1f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        fn_801CD6D4(self);
    } else {
        fn_801CD77C(self);
        fn_801CD6D4(self);
    }
    if (stricmp(lbl_805526EC, "BrooklynBridge_MP") == 0) {
        Ref8 ev;

        fn_8046B530(&ev);
        fn_8046B710(&ev, fn_801D16A4(self));
        fn_80082AFC(&ev, fn_801D16A4(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        fn_8046B710(&ev, fn_801D165C(self));
        fn_80082AFC(&ev, fn_801D165C(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    }
}

void fn_801CD06C(register cBrooklynBridge_SegmentControl *self, int a, int b, int kind, float c, float d, float e, float f, int value) // slot 23
{
    if (self->started == 0) {
        self->started = 1;
        fn_8007D8B0(self);
        fn_801CD288(self);
    }
}

void fn_801CD0E8(register cBrooklynBridge_SegmentControl *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_801CD288(self);
        break;
    case 20:
        fn_801CD49C(self);
        break;
    case 25:
        fn_801CD6D4(self);
        break;
    case 30: {
        Ref8 ev;

        fn_8046B680(&ev, 0);
        fn_8046B710(&ev, fn_801D153C(self));
        fn_80082AFC(&ev, fn_801D153C(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        fn_8046B710(&ev, fn_801D1584(self));
        fn_80082AFC(&ev, fn_801D1584(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        fn_801CD6D4(self);
    }
    }
}

void fn_801CD288(register cBrooklynBridge_SegmentControl *self)
{
    Ref8 ev;

    fn_8046B680(&ev, 0);
    fn_8046B710(&ev, fn_801D1464(self));
    fn_80082AFC(&ev, fn_801D1464(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    fn_8046B710(&ev, fn_801D14AC(self));
    fn_80082AFC(&ev, fn_801D14AC(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    fn_8046B710(&ev, fn_801D14F4(self));
    fn_80082AFC(&ev, fn_801D14F4(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    fn_801CD6D4(self);
    fn_8007D404(self, 3.0f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8046B710(&ev, fn_801D15CC(self));
    fn_80082AFC(&ev, fn_801D15CC(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801CD49C(register cBrooklynBridge_SegmentControl *self)
{
    Ref8 ev;

    fn_8046B680(&ev, 0);
    fn_8046B710(&ev, fn_801D14AC(self));
    fn_80082AFC(&ev, fn_801D14AC(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    fn_8046B710(&ev, fn_801D14F4(self));
    fn_80082AFC(&ev, fn_801D14F4(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    fn_8046B710(&ev, fn_801D153C(self));
    fn_80082AFC(&ev, fn_801D153C(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    fn_8046B710(&ev, fn_801D1584(self));
    fn_80082AFC(&ev, fn_801D1584(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    fn_8046B710(&ev, fn_801D15CC(self));
    fn_80082AFC(&ev, fn_801D15CC(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801CD6D4(register cBrooklynBridge_SegmentControl *self)
{
    Ref8 ev;

    fn_8046B680(&ev, 0);
    fn_8046B710(&ev, fn_801D1614(self));
    fn_80082AFC(&ev, fn_801D1614(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801CD77C(register cBrooklynBridge_SegmentControl *self)
{
    Ref8 ev;

    fn_8046B680(&ev, 0);
    fn_8046B710(&ev, fn_801D1464(self));
    fn_80082AFC(&ev, fn_801D1464(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}


void fn_801CD824(register cBrooklynBridge_BruteFight *self) // slot 5
{
    Ref8 me;
    int ai;

    fn_8046B5A8(&me, fn_800797D4(self));
    fn_8007A448(fn_800797D4(self));
    fn_80081F8C(&me, 2);
    fn_8046BBE8();
    ai = fn_8007C034(&me);
    if (ai)
        fn_80086410(ai);
    self->done = 0;
}

float fn_801CD8C4(register cBrooklynBridge_BruteFight *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    Ref8 me;

    fn_8046B5A8(&me, fn_800797D4(self));
    if (h != fn_804425F8(&me))
        return damage;
    Ref8 p;
    int a;

    fn_8046B638(&p, fn_80080B34());
    a = fn_800809CC(&p);
    if (!a || fn_80085EEC(a))
        return -1.0f;
    if (fn_8007C0AC(&me) - damage < 1.0f) {
        Ref8 m;

        fn_8046B5A8(&m, fn_800797D4(self));
        if (self->done)
            return damage;
        self->done = 1;
        lbl_8066C724 = 1;
        fn_80081C68();
        fn_80081C94();
        fn_80081CC4();
        fn_80081B40(fn_804425F8(&m));
        if (h == fn_804425F8(&m)) {
            fn_80081A54(fn_80080B34());
            fn_801CDD08(self);
        }
        return -1.0f;
    }
    return damage;
}

int fn_801CDA8C(register cBrooklynBridge_BruteFight *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    Ref8 me;

    fn_8046B5A8(&me, fn_800797D4(self));
    if (h != fn_800797D4(self))
        return 1;
    if (self->done)
        return 0;
    self->done = 1;
    lbl_8066C724 = 1;
    fn_80081C68();
    fn_80081C94();
    fn_80081CC4();
    fn_80081B40(fn_804425F8(&me));
    if (h == fn_804425F8(&me)) {
        fn_80081A54(fn_80080B34());
        fn_801CDD08(self);
    }
    return 0;
}

void fn_801CDB94(register cBrooklynBridge_BruteFight *self, int a, int b, int kind, float c, float d, float e, float f, int value) // slot 23
{
    Ref8 me;

    fn_8046B5A8(&me, fn_800797D4(self));
    if (c == 1.0f) {
        fn_80082014(&me, 2);
    } else if (d == 1.0f) {
        fn_8007A4FC(fn_804425F8(&me));
        fn_8046BC0C();
        int ai = fn_8007C034(&me);
        if (ai)
            fn_8008643C(ai);
    }
}

void fn_801CDC80(register cBrooklynBridge_BruteFight *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_801CDD08(self);
        break;
    case 15:
        fn_801CDDB0(self);
        break;
    }
}

void fn_801CDD08(register cBrooklynBridge_BruteFight *self)
{
    fn_8007D404(self, 3.0f, 15, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_800797D4(self));
    fn_80081BD4(fn_800797D4(self));
    fn_8043323C(lbl_8057230C, 1);
}

void fn_801CDDB0(register cBrooklynBridge_BruteFight *self)
{
    Ref8 ev;

    fn_80081918(fn_80080B34());
    fn_8046B6C8(&ev, fn_801D1740(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 2.0f, 0.0f, 0.0f, 0.0f);
}


void fn_801CDE5C(register cBrooklynBridge_WolverineSAC *self) // slot 5
{
    fn_8046B710(&self->boss, fn_801D17DC(self));
    fn_8007CF00(self, fn_804425F8(&self->boss), 0);
    fn_8007CF00(self, fn_80080B34(), 0);
    fn_8046B710(&self->r30, fn_801D1824(self));
    self->stage1 = 0;
    self->stage2 = 0;
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
    float t = fn_8007C244(&self->boss) / 10.0f;
    self->limit1 = t * 7.5f;
    self->limit2 = t * 4.0f;
}

void fn_801CDF74(register cBrooklynBridge_WolverineSAC *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_801CE3E8(self);
        break;
    case 20:
        fn_801CE86C(self);
        break;
    case 25:
        fn_801CE914(self);
        break;
    case 30:
        fn_801CE9C0(self);
        break;
    case 35:
        fn_801CEA28(self);
        break;
    }
}

float fn_801CE044(register cBrooklynBridge_WolverineSAC *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h != fn_804425F8(&self->boss))
        return damage;
    fn_8007D404(self, 0.25f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    return damage;
}

int fn_801CE0FC(register cBrooklynBridge_WolverineSAC *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    Ref8 r;

    fn_8007D7C4(self, 10);
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

void fn_801CE2B0(register cBrooklynBridge_WolverineSAC *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (self->done) {
        if (h != fn_80080B34())
            return;
        return;
    }
    self->done = 1;
    fn_8007D7C4(self, 10);
    lbl_8066C724 = 1;
    fn_80081C68();
    fn_80081C94();
    fn_80081CC4();
    fn_80081B40(fn_804425F8(&self->boss));
    if (h == fn_804425F8(&self->boss)) {
        fn_80081A54(fn_80080B34());
        if (self->bossHit == 0)
            fn_801CE86C(self);
        else
            fn_801CE914(self);
    } else if (h == fn_80080B34()) {
        if (self->playerHit == 0)
            fn_801CE9C0(self);
        else
            fn_801CEA28(self);
        return;
    }
}

void fn_801CE3E8(register cBrooklynBridge_WolverineSAC *self)
{
    if (fn_8007C0AC(&self->boss) < self->limit2 && self->stage2 == 0)
        fn_801CE664(self);
    else if (fn_8007C0AC(&self->boss) < self->limit1 && self->stage1 == 0)
        fn_801CE47C(self);
}

void fn_801CE47C(register cBrooklynBridge_WolverineSAC *self)
{
    self->stage1 = 1;
    fn_8007B2E8(fn_804425F8(&self->boss), 0, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 1, 30.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 2, 30.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 3, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 4, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 5, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 6, 0.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 7, 80.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 8, 70.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 9, 80.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 10, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 11, 95.0f);
}

void fn_801CE664(register cBrooklynBridge_WolverineSAC *self)
{
    self->stage2 = 1;
    fn_8007B2E8(fn_804425F8(&self->boss), 0, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 1, 10.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 2, 10.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 3, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 4, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 5, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 6, 0.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 7, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 8, 25.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 9, 25.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 10, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 11, 95.0f);
    fn_8007B540(fn_804425F8(&self->boss), 1, 0);
}

void fn_801CE86C(register cBrooklynBridge_WolverineSAC *self)
{
    fn_8007D404(self, 2.0f, 25, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_8057230C, 1);
}

void fn_801CE914(register cBrooklynBridge_WolverineSAC *self)
{
    fn_80082F30(&self->boss);
    fn_80081918(fn_80080B34());
    lbl_8066C71C = fn_80080B34();
    fn_80082AFC(&self->r30, fn_804425F8(&self->r30), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801CE9C0(register cBrooklynBridge_WolverineSAC *self)
{
    fn_8007D404(self, 2.0f, 35, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801CEA28(register cBrooklynBridge_WolverineSAC *self)
{
    Ref8 p;
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    fn_8046B638(&p, fn_80080B34());
    fn_80082F30(&p);
    lbl_8066C71C = fn_804425F8(&self->boss);
    fn_8046B6C8(&ev, fn_801D186C(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}


void fn_801CEB10(register cBrooklynBridge_RockBomb *self) // slot 4
{
    fn_8046B710(&self->obj, fn_800797D4(self));
    fn_8046B710(&self->shock, fn_80083734("AFTERSHOCK"));
    fn_8007CF00(self, fn_801D1908(self), 0);
}

void fn_801CEB98(register cBrooklynBridge_RockBomb *self) // slot 5
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

void fn_801CEC84(register cBrooklynBridge_RockBomb *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_800820A0(&self->obj, 1);
        fn_80080928(&self->obj, 1);
        break;
    case 40:
        fn_801CF094(self);
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
        fn_80082E90(&self->obj, "asBoulderSmash", 0xff, 0xff);
        fn_80081F8C(&self->obj, 2);
        fn_801CF094(self);
        break;
    }
    }
}

void fn_801CEE34(register cBrooklynBridge_RockBomb *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    fn_801CF15C(self);
    fn_8007D404(self, 0.25f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801CEECC(register cBrooklynBridge_RockBomb *self, int h, int other, int value) // slot 15
{
    if (h == fn_801D1908(self) && other == fn_800797D4(self))
        fn_801CF094(self);
}

void fn_801CEF48(register cBrooklynBridge_RockBomb *self, int h, int other, int a, int b, int value) // slot 27
{
    Ref8 p;

    fn_8046B5A8(&p, fn_80080B34());
    if (other == fn_804425F8(&p)) {
        int actor = fn_8007C034(&p);
        if (actor && fn_8009B04C(actor) != 0x7f)
            fn_8007C740(&p, 0x7f, 0, 0, 1.0f, 0);
        fn_8007D404(self, 0.01f, 50, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        return;
    }
    fn_8007D404(self, 0.01f, 50, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801CF094(register cBrooklynBridge_RockBomb *self)
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

void fn_801CF15C(register cBrooklynBridge_RockBomb *self)
{
    Vector pos;
    fn_80082440(&self->shock, &pos);
    Mat m;
    fn_800826A8(&self->shock, &m);
    *fn_8042DC3C(&m, 3, 2) += 2.0f;
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
    self->target.y -= 1.0f;
    fn_8006645C(o, 0);
    Vector d;
    fn_80429038(&d, &self->target, fn_800B1724(o));
    float len = fn_8042EC54(&d);
    float t = len / 0.5f;
    t = t >= 10.0f ? (t <= 100.0f ? t : 100.0f) : 10.0f;
    float a;
    float b;
    if (!fn_801BCB08(&pos, &self->target, t, 20.0f, &a, &b))
        a = b = 45.0f;
    float lo = -5.0f;
    float hi = 70.0f;
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


void fn_801CF798(register cBrooklynBridge_FlameWall *self) // slot 5
{
    fn_8046B710(&self->obj, fn_800797D4(self));
    fn_8007D404(self, fn_80171F8C() * 4.656612873077392578125e-10f * 10.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    lbl_8066C720 = 1000;
}

void fn_801CF86C(register cBrooklynBridge_FlameWall *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    Ref8 ev;

    switch (kind) {
    case 10:
        if (fn_8042EFF8(lbl_80593BE8) < lbl_8066C720) {
            fn_8007D404(self, fn_80171F8C() * 4.656612873077392578125e-10f * 5.0f + 10.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            return;
        }
        fn_801337F0(fn_801D19A4(self), 0);
        fn_80082E24(&self->obj, "bbFirePillarWarn");
        fn_8007D404(self, 3.0f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        lbl_8066C720 = fn_8042EFF8(lbl_80593BE8) + 8000;
        break;
    case 20:
        if (fn_801D19EC(self)) {
            fn_8046B6C8(&ev, fn_801D19EC(self));
            fn_80082AFC(&ev, fn_801D19EC(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        }
        fn_80083428(&self->obj, "bbFirePillarWarn");
        fn_80082E24(&self->obj, "bbFirePillarGush");
        fn_80082E24(&self->obj, "bbFirePillarOn");
        fn_8046BBA0(&ev, fn_801D19A4(self));
        fn_80082AFC(&ev, fn_801D19A4(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        fn_8007D404(self, 5.0f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 30:
        fn_80133838(fn_801D19A4(self));
        fn_80083428(&self->obj, "bbFirePillarOn");
        fn_8046BBA0(&ev, fn_801D19A4(self));
        fn_80082AFC(&ev, fn_801D19A4(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        fn_8007D404(self, fn_80171F8C() * 4.656612873077392578125e-10f * 5.0f + 10.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
}


void fn_801CFC94(register cBrooklynBridge_HazmatBoss *self) // slot 4
{
    fn_8046B710(&self->boss, fn_800797D4(self));
    fn_8046B710(&self->player, fn_80080B34());
    fn_8007CF00(self, fn_804425F8(&self->player), 0);
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
}

int fn_801CFD38(register cBrooklynBridge_HazmatBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
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

void fn_801CFEEC(register cBrooklynBridge_HazmatBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
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
            fn_801D00F0(self);
        else
            fn_801D01A0(self);
    } else if (h == fn_804425F8(&self->player)) {
        if (self->playerHit == 0)
            fn_801D0254(self);
        else
            fn_801D02C4(self);
    }
}

void fn_801D0034(register cBrooklynBridge_HazmatBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 1:
        fn_801D00F0(self);
        break;
    case 2:
        fn_801D01A0(self);
        break;
    case 3:
        fn_801D0254(self);
        break;
    case 4:
        fn_801D02C4(self);
        break;
    }
}

void fn_801D00F0(register cBrooklynBridge_HazmatBoss *self)
{
    fn_8007D404(self, 2.0f, 2, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_8057230C, 1);
}

void fn_801D01A0(register cBrooklynBridge_HazmatBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->player));
    fn_8046B6C8(&ev, fn_801D1A88(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801D0254(register cBrooklynBridge_HazmatBoss *self)
{
    fn_8007D404(self, 2.0f, 4, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801D02C4(register cBrooklynBridge_HazmatBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    fn_8046B6C8(&ev, fn_801D1AD0(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801D0378(register cBrooklynBridge_AltStormBoss *self) // slot 4
{
    fn_8046B710(&self->boss, fn_800797D4(self));
    fn_8007BA24(fn_800797D4(self), 4);
    fn_8046B710(&self->player, fn_80080B34());
    fn_8007CF00(self, fn_804425F8(&self->player), 0);
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
}

int fn_801D0434(register cBrooklynBridge_AltStormBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
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

void fn_801D05E8(register cBrooklynBridge_AltStormBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
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
            fn_801D07EC(self);
        else
            fn_801D08B4(self);
    } else if (h == fn_804425F8(&self->player)) {
        if (self->playerHit == 0)
            fn_801D0968(self);
        else
            fn_801D09D8(self);
    }
}

void fn_801D0730(register cBrooklynBridge_AltStormBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 1:
        fn_801D07EC(self);
        break;
    case 2:
        fn_801D08B4(self);
        break;
    case 3:
        fn_801D0968(self);
        break;
    case 4:
        fn_801D09D8(self);
        break;
    }
}

void fn_801D07EC(register cBrooklynBridge_AltStormBoss *self)
{
    fn_8007D404(self, 2.0f, 2, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_80081918(fn_804425F8(&self->player));
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_8057230C, 1);
}

void fn_801D08B4(register cBrooklynBridge_AltStormBoss *self)
{
    Ref8 ev;

    fn_800816A0(fn_804425F8(&self->player));
    fn_8046B6C8(&ev, fn_801D1B6C(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801D0968(register cBrooklynBridge_AltStormBoss *self)
{
    fn_8007D404(self, 2.0f, 4, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801D09D8(register cBrooklynBridge_AltStormBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    fn_8046B6C8(&ev, fn_801D1BB4(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

inline int sn_return_decl2(int a) { return a; }

cScript *fn_801D0A8C(register cBrooklynBridge_heliCrash *self)
{
    return new cBrooklynBridge_heliCrash;
}

unsigned int fn_801D0AE0(register cBrooklynBridge_heliCrash *self) { return fn_800791C8(self, 0); }
unsigned int fn_801D0B28(register cBrooklynBridge_heliCrash *self) { return fn_800791C8(self, 1); }
unsigned int fn_801D0B70(register cBrooklynBridge_heliCrash *self) { return fn_800791C8(self, 2); }

cScript *fn_801D0BB8(register cBB_ArenaShutoff *self)
{
    return new cBB_ArenaShutoff;
}

unsigned int fn_801D0C0C(register cBB_ArenaShutoff *self) { return fn_800791C8(self, 0); }
unsigned int fn_801D0C54(register cBB_ArenaShutoff *self) { return fn_800791C8(self, 1); }
unsigned int fn_801D0C9C(register cBB_ArenaShutoff *self) { return fn_800791C8(self, 2); }

cScript *fn_801D0CE4(register cBrooklynBridge_ArenaBarrier *self)
{
    return new cBrooklynBridge_ArenaBarrier;
}


cScript *fn_801D0D38(register cBrooklynBridge_AftershockBoss *self)
{
    return new cBrooklynBridge_AftershockBoss;
}

unsigned int fn_801D0D8C(register cBrooklynBridge_AftershockBoss *self) { return fn_800791C8(self, 0); }
unsigned int fn_801D0DD4(register cBrooklynBridge_AftershockBoss *self) { return fn_800791C8(self, 1); }
unsigned int fn_801D0E1C(register cBrooklynBridge_AftershockBoss *self) { return fn_800791C8(self, 2); }
unsigned int fn_801D0E64(register cBrooklynBridge_AftershockBoss *self) { return fn_800791C8(self, 3); }
unsigned int fn_801D0EAC(register cBrooklynBridge_AftershockBoss *self) { return fn_800791C8(self, 4); }
unsigned int fn_801D0EF4(register cBrooklynBridge_AftershockBoss *self) { return fn_800791C8(self, 5); }
unsigned int fn_801D0F3C(register cBrooklynBridge_AftershockBoss *self) { return fn_800791C8(self, 6); }
unsigned int fn_801D0F84(register cBrooklynBridge_AftershockBoss *self) { return fn_800791C8(self, 7); }
unsigned int fn_801D0FCC(register cBrooklynBridge_AftershockBoss *self) { return fn_800791C8(self, 8); }
unsigned int fn_801D1014(register cBrooklynBridge_AftershockBoss *self) { return fn_800791C8(self, 9); }
unsigned int fn_801D105C(register cBrooklynBridge_AftershockBoss *self) { return fn_800791C8(self, 10); }
unsigned int fn_801D10A4(register cBrooklynBridge_AftershockBoss *self) { return fn_800791C8(self, 11); }
unsigned int fn_801D10EC(register cBrooklynBridge_AftershockBoss *self) { return fn_800791C8(self, 12); }

cScript *fn_801D1134(register cBrooklynBridge_VM2_Start *self)
{
    return new cBrooklynBridge_VM2_Start;
}

unsigned int fn_801D1188(register cBrooklynBridge_VM2_Start *self) { return fn_800791C8(self, 0); }
unsigned int fn_801D11D0(register cBrooklynBridge_VM2_Start *self) { return fn_800791C8(self, 1); }
unsigned int fn_801D1218(register cBrooklynBridge_VM2_Start *self) { return fn_800791C8(self, 2); }
unsigned int fn_801D1260(register cBrooklynBridge_VM2_Start *self) { return fn_800791C8(self, 3); }
unsigned int fn_801D12A8(register cBrooklynBridge_VM2_Start *self) { return fn_800791C8(self, 4); }
unsigned int fn_801D12F0(register cBrooklynBridge_VM2_Start *self) { return fn_800791C8(self, 5); }
unsigned int fn_801D1338(register cBrooklynBridge_VM2_Start *self) { return fn_800791C8(self, 6); }
unsigned int fn_801D1380(register cBrooklynBridge_VM2_Start *self) { return fn_800791C8(self, 7); }
unsigned int fn_801D13C8(register cBrooklynBridge_VM2_Start *self) { return fn_800791C8(self, 8); }

cScript *fn_801D1410(register cBrooklynBridge_SegmentControl *self)
{
    return new cBrooklynBridge_SegmentControl;
}

unsigned int fn_801D1464(register cBrooklynBridge_SegmentControl *self) { return fn_800791C8(self, 0); }
unsigned int fn_801D14AC(register cBrooklynBridge_SegmentControl *self) { return fn_800791C8(self, 3); }
unsigned int fn_801D14F4(register cBrooklynBridge_SegmentControl *self) { return fn_800791C8(self, 4); }
unsigned int fn_801D153C(register cBrooklynBridge_SegmentControl *self) { return fn_800791C8(self, 5); }
unsigned int fn_801D1584(register cBrooklynBridge_SegmentControl *self) { return fn_800791C8(self, 6); }
unsigned int fn_801D15CC(register cBrooklynBridge_SegmentControl *self) { return fn_800791C8(self, 7); }
unsigned int fn_801D1614(register cBrooklynBridge_SegmentControl *self) { return fn_800791C8(self, 8); }
unsigned int fn_801D165C(register cBrooklynBridge_SegmentControl *self) { return fn_800791C8(self, 10); }
unsigned int fn_801D16A4(register cBrooklynBridge_SegmentControl *self) { return fn_800791C8(self, 11); }

cScript *fn_801D16EC(register cBrooklynBridge_BruteFight *self)
{
    return new cBrooklynBridge_BruteFight;
}

unsigned int fn_801D1740(register cBrooklynBridge_BruteFight *self) { return fn_800791C8(self, 0); }

cScript *fn_801D1788(register cBrooklynBridge_WolverineSAC *self)
{
    return new cBrooklynBridge_WolverineSAC;
}

unsigned int fn_801D17DC(register cBrooklynBridge_WolverineSAC *self) { return fn_800791C8(self, 0); }
unsigned int fn_801D1824(register cBrooklynBridge_WolverineSAC *self) { return fn_800791C8(self, 1); }
unsigned int fn_801D186C(register cBrooklynBridge_WolverineSAC *self) { return fn_800791C8(self, 2); }

cScript *fn_801D18B4(register cBrooklynBridge_RockBomb *self)
{
    return new cBrooklynBridge_RockBomb;
}

unsigned int fn_801D1908(register cBrooklynBridge_RockBomb *self) { return fn_800791C8(self, 0); }

cScript *fn_801D1950(register cBrooklynBridge_FlameWall *self)
{
    return new cBrooklynBridge_FlameWall;
}

unsigned int fn_801D19A4(register cBrooklynBridge_FlameWall *self) { return fn_800791C8(self, 0); }
unsigned int fn_801D19EC(register cBrooklynBridge_FlameWall *self) { return fn_800791C8(self, 1); }

cScript *fn_801D1A34(register cBrooklynBridge_HazmatBoss *self)
{
    return new cBrooklynBridge_HazmatBoss;
}

unsigned int fn_801D1A88(register cBrooklynBridge_HazmatBoss *self) { return fn_800791C8(self, 0); }
unsigned int fn_801D1AD0(register cBrooklynBridge_HazmatBoss *self) { return fn_800791C8(self, 1); }

cScript *fn_801D1B18(register cBrooklynBridge_AltStormBoss *self)
{
    return new cBrooklynBridge_AltStormBoss;
}

unsigned int fn_801D1B6C(register cBrooklynBridge_AltStormBoss *self) { return fn_800791C8(self, 0); }
unsigned int fn_801D1BB4(register cBrooklynBridge_AltStormBoss *self) { return fn_800791C8(self, 1); }

}
