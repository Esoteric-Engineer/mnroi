// The actor and AI script classes, their clones and parameter accessors (docs/story.md row 11).
// Pool read from 0x804A09B4 (extern_pool).

inline int sn_return_decl(int a) { return a; }

struct cScript {
    char d[0x24];
    char *vptr; // +0x24
};

struct Vector {
    float x, y, z, w;
    Vector();
} __attribute__((aligned(8)));

struct cScriptV { // cScript's virtual slots, for calls on self
    char d[0x24];
    virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13(); virtual void s14(int h, int other, int value); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(int a, int b, int kind, float x, float y, float z, float w, int value); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30();
    virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
    virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42();
    virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46();
    virtual int s47(int h, int value);
};

struct Ref8 {
    int unk0;
    int value; // +0x4
};

struct SObj {
    int unk0;
    void fn_800B1FA8(int v) __asm__("fn_800B1FA8");
};

struct SActor : SObj {
    int pad;
};

struct cPathnodeToggle : cScript { // 0x2C
    int on; // +0x28
    cPathnodeToggle() __asm__("fn_80469548");
};

struct cActorMoveToPos : cScript { // 0x70
    unsigned int count; // +0x28
    unsigned int stage; // +0x2C
    Vector v30;         // +0x30
    Vector v40;         // +0x40
    Vector v50;         // +0x50
    Vector v60;         // +0x60
    cActorMoveToPos() __asm__("fn_80469594");
};

struct cActorWalk : cScript { // 0x40
    int node;   // +0x28
    int dir;    // +0x2C
    int loop;   // +0x30
    int done;   // +0x34
    Ref8 actor; // +0x38
    cActorWalk() __asm__("fn_80469610");
};

struct cActorAIPause : cScript { // 0x30
    int paused; // +0x28
    int unk2C;  // +0x2C
    cActorAIPause() __asm__("fn_8046966C");
};

struct cActorControlState : cScript { // 0x28
    cActorControlState() __asm__("fn_804696B8");
};

struct cSpawnPeon : cScript { // 0xA0
    int unk28;       // +0x28
    int unk2C;       // +0x2C
    int unk30;       // +0x30
    int unk34;       // +0x34
    Ref8 actor;      // +0x38
    Ref8 unk40;      // +0x40
    int unk48;       // +0x48
    int count;       // +0x4C
    int max;         // +0x50, at most 10
    int unk54;       // +0x54
    int unk58;       // +0x58
    int peons[10];   // +0x5C
    unsigned int unk84; // +0x84
    int unk88;       // +0x88
    int unk8C;       // +0x8C
    Vector pos;      // +0x90
    cSpawnPeon() __asm__("fn_80469704");
};

struct cSpawnGroup : cScript { // 0x78
    Ref8 spawners[8]; // +0x28
    int count;        // +0x68
    int unk6C;        // +0x6C
    int unk70;        // +0x70
    int unk74;        // +0x74
    cSpawnGroup() __asm__("fn_80469778");
};

struct cSpawnController : cScript { // 0xA0
    int wave;       // +0x28
    int unk2C;      // +0x2C
    int count;      // +0x30
    int unk34;      // +0x34
    int unk38;      // +0x38
    int unk3C;      // +0x3C
    int fired[10];  // +0x40
    int unk68;      // +0x68
    int unk6C[10];  // +0x6C
    int unk94;      // +0x94
    int unk98;      // +0x98
    int unk9C;      // +0x9C
    cSpawnController() __asm__("fn_80469824");
};

struct cActorPlayPath : cScript { // 0x28
    cActorPlayPath() __asm__("fn_80469870");
};

struct cAIRangedAttacker : cScript { // 0x88
    Ref8 actor;         // +0x28
    Ref8 targets[5];    // +0x30
    int inRange[5];     // +0x58
    int unk6C;          // +0x6C
    int active;         // +0x70
    int unk74;          // +0x74
    int unk78;          // +0x78
    int unk7C;          // +0x7C
    int unk80;          // +0x80
    int effect;         // +0x84
    cAIRangedAttacker() __asm__("fn_804698BC");
};

struct cBossRingOut : cScript { // 0x28
    cBossRingOut() __asm__("fn_80469954");
};

struct cActorSetHealth : cScript { // 0x2C
    int done; // +0x28
    cActorSetHealth() __asm__("fn_804699A0");
};

struct cPlayerBonusMissions : cScript { // 0x30
    int count;   // +0x28
    int stopped; // +0x2C
    cPlayerBonusMissions() __asm__("fn_804699EC");
};

struct cGlobalPeonCounter : cScript { // 0x2C
    int unk28; // +0x28
    cGlobalPeonCounter() __asm__("fn_80469A38");
};

struct cAITeleportationToggle : cScript { // 0x2C
    int on; // +0x28
    cAITeleportationToggle() __asm__("fn_80469A84");
};

struct cAIEnemyVictoryScene : cScript { // 0x34
    int done;   // +0x28
    Ref8 unk2C; // +0x2C
    cAIEnemyVictoryScene() __asm__("fn_80469AD0");
};

struct cTemporaryAIPossession : cScript { // 0x30
    Ref8 actor; // +0x28
    cTemporaryAIPossession() __asm__("fn_80469B2C");
};

struct cAISetTeleportDistance : cScript { // 0x28
    cAISetTeleportDistance() __asm__("fn_80469B88");
};

struct VBase {
    char pad0[0x198];
};

struct VObj : VBase { // what fn_80081E6C returns
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18();
    virtual void s19(); // +0xA0
};

extern int lbl_8066C728; // peons killed
extern int lbl_8066C72C;
extern int lbl_8066C730;

extern "C" {
int fn_800797D4(cScript *self);
void fn_8046BBA0(void *ev, int x);
void fn_8046B5A8(void *ev, int x);
void fn_8046B6C8(void *ev, int x);
int fn_804425F8(void *ev);
unsigned int fn_8046C898(void *ev);
void fn_80081208(void *ev, int on);
int fn_8008291C(void *ev, int i, Vector *out, Vector *out2, int b);
int fn_80082440(void *ev, Vector *out);
void fn_80082F30(void *ev);
void fn_80082FA4(void *ev);
void fn_8007A448(int h);
void fn_8007A4FC(int h);
void fn_8007A738(int h, Vector *to);
void fn_8007BE0C(int h, int on);
int fn_801F3394(cPathnodeToggle *self);
void fn_8046B710(Ref8 *self, int value);
void fn_8007A5DC(int h);
void fn_8007A658(int h);
void fn_8007A818(int h, int node);
void fn_8007D8B0(cScript *self);
void fn_8007D404(cScript *self, float seconds, int kind, float a, float b, float c, float d, int e);
int fn_801F36E0(cActorWalk *self);
int fn_801F3724(cActorWalk *self);
int fn_801F376C(cActorWalk *self);
int fn_801F37B4(cActorWalk *self);
float fn_801F380C(cActorWalk *self);
int fn_801F3854(cActorWalk *self);
int fn_801F38AC(cActorWalk *self);
void fn_801EB508(cActorWalk *self, int node);
int fn_801F3958(cActorAIPause *self);
int fn_801F399C(cActorAIPause *self);
int fn_801F39E4(cActorAIPause *self);
int fn_801F3A3C(cActorAIPause *self);
int fn_801F3AE8(cActorControlState *self);
int fn_801F3B2C(cActorControlState *self);
int fn_801F3B74(cActorControlState *self);
int fn_801F3BBC(cActorControlState *self);
void fn_8046B638(void *ev, int x);
int fn_800809CC(void *ev);
int fn_8007C034(void *ev);
void fn_80082014(void *ev, int a);
void fn_800820A0(void *ev, int a);
int fn_80082E90(void *ev, char *name, int a, int b);
void fn_8008643C(int actor);
void fn_8006645C(int actor, int a);
int fn_800861EC(int actor);
void fn_8007BA24(int h, int state);
void fn_8007B0EC(int h, int a, int b, int c);
int fn_80171F8C(void);
void fn_80082AFC(void *ev, int h, int owner, int kind, float a, float b, float c, float d);
int fn_801F3C58(cSpawnPeon *self);
int fn_801F3CE4(cSpawnPeon *self);
int fn_801F3D2C(cSpawnPeon *self);
int fn_801F3DBC(cSpawnPeon *self);
unsigned int fn_801F3E14(cSpawnPeon *self);
int fn_801F3E5C(cSpawnPeon *self);
float fn_801F3EA4(cSpawnPeon *self);
unsigned int fn_801F3F34(cSpawnPeon *self);
unsigned int fn_801F3EEC(cSpawnPeon *self);
unsigned int fn_801F3F7C(cSpawnPeon *self);
int fn_801F3FC4(cSpawnPeon *self);
unsigned int fn_801F400C(cSpawnPeon *self);
unsigned int fn_80081EC4(void *ev);
void fn_8046B680(void *ev, int x);
int fn_80080B34();
int fn_80080300(void *ev);
int fn_8009AC94(int actor);
int fn_8009B04C(int actor);
void fn_80131724(int a, int b);
SActor *fn_8007C034S(void *ev) __asm__("fn_8007C034");
void fn_801ED3A4(cSpawnPeon *self, unsigned int n);
void fn_801EDEB8(cSpawnPeon *self, int h);
unsigned int fn_801F3D74(cSpawnPeon *self);
int fn_801F440C(cSpawnPeon *self);
int fn_80081E6C(void *ev);
int fn_8046C8FC(void *ev);
float fn_804290F8(Vector *a, Vector *b);
void fn_8007AC68(int h, int target, int c);
int fn_8007CF00(cScript *script, int handle, int value);
void fn_8007A958(int h, int target);
void fn_8046B5F0(void *ev, int x);
int fn_80080EFC(void *ev);
int fn_800A3F14(int actor);
void fn_8006645CR(SObj &o, int a) __asm__("fn_8006645C");
char *fn_801F3C9C(cSpawnPeon *self);
char *fn_801F4464(cSpawnPeon *self);
int fn_801F4054(cSpawnPeon *self);
void fn_801EDBAC(cSpawnPeon *self, unsigned int h);
unsigned int fn_80082190(Ref8 *at, char *name);
int stricmp(const char *a, const char *b);
char *strncpy(char *dst, const char *src, unsigned int n);
void fn_800486C4(int peon);
void fn_80086410(int actor);
int fn_80393D0C(int peon, char *name, int a, int b);
void fn_8007B2E8(unsigned int h, int i, float v);
void fn_80082720(void *ev, int h);
void fn_8007AA8C(int h, int target);
float fn_801F40AC(cSpawnPeon *self);
float fn_801F40F4(cSpawnPeon *self);
float fn_801F413C(cSpawnPeon *self);
float fn_801F4184(cSpawnPeon *self);
float fn_801F41CC(cSpawnPeon *self);
float fn_801F4214(cSpawnPeon *self);
float fn_801F425C(cSpawnPeon *self);
float fn_801F42A4(cSpawnPeon *self);
float fn_801F42EC(cSpawnPeon *self);
float fn_801F4334(cSpawnPeon *self);
float fn_801F437C(cSpawnPeon *self);
float fn_801F43C4(cSpawnPeon *self);
unsigned int fn_801F4500(cSpawnGroup *self);
unsigned int fn_801F4548(cSpawnGroup *self);
unsigned int fn_801F4590(cSpawnGroup *self);
unsigned int fn_801F45D8(cSpawnGroup *self);
unsigned int fn_801F4620(cSpawnGroup *self);
unsigned int fn_801F4668(cSpawnGroup *self);
unsigned int fn_801F46B0(cSpawnGroup *self);
unsigned int fn_801F46F8(cSpawnGroup *self);
int fn_801F4740(cSpawnGroup *self);
int fn_801F4798(cSpawnGroup *self);
void fn_801EE73C(cSpawnGroup *self, unsigned int i, int on, int kind);
int fn_80080A44(void *ev);
int fn_801F4844(cSpawnController *self);
void fn_801F07EC(cSpawnController *self);
int fn_801EFE8C(cSpawnController *self, int wave, int b, unsigned int h);
unsigned int fn_801F492C(cSpawnController *self);
int fn_801F4974(cSpawnController *self);
unsigned int fn_801F4A04(cSpawnController *self);
int fn_801F4A4C(cSpawnController *self);
unsigned int fn_801F4ADC(cSpawnController *self);
int fn_801F4B24(cSpawnController *self);
unsigned int fn_801F4BB4(cSpawnController *self);
int fn_801F4BFC(cSpawnController *self);
unsigned int fn_801F4C8C(cSpawnController *self);
int fn_801F4CD4(cSpawnController *self);
unsigned int fn_801F4D64(cSpawnController *self);
int fn_801F4DAC(cSpawnController *self);
unsigned int fn_801F4E3C(cSpawnController *self);
int fn_801F4E84(cSpawnController *self);
unsigned int fn_801F4F14(cSpawnController *self);
int fn_801F4F5C(cSpawnController *self);
unsigned int fn_801F4FEC(cSpawnController *self);
int fn_801F5034(cSpawnController *self);
unsigned int fn_801F50C4(cSpawnController *self);
int fn_801F510C(cSpawnController *self);
unsigned int fn_801F489C(cSpawnController *self);
int fn_801F48E4(cSpawnController *self);
void fn_801F06BC(cSpawnController *self);
unsigned int fn_801F0C60(cSpawnController *self, int wave);
void fn_8007D4F4(cScript *self, int ms, int kind, float a, float b, float c, float d, int e);
int fn_801F49BC(cSpawnController *self);
int fn_801F4A94(cSpawnController *self);
int fn_801F4B6C(cSpawnController *self);
int fn_801F4C44(cSpawnController *self);
int fn_801F4D1C(cSpawnController *self);
int fn_801F4DF4(cSpawnController *self);
int fn_801F4ECC(cSpawnController *self);
int fn_801F4FA4(cSpawnController *self);
int fn_801F507C(cSpawnController *self);
int fn_801F5154(cSpawnController *self);
int fn_801F54C0(cActorPlayPath *self);
int fn_801F5508(cActorPlayPath *self);
int fn_801F5550(cActorPlayPath *self);
int fn_801F111C(cActorPlayPath *self);
void fn_80080F74(void *ev, int flags);
void fn_800804FC(void *ev);
int fn_800803DC(void *ev, int id, float f);
void fn_8046B530(void *ev);
unsigned int fn_801F519C(cSpawnController *self);
unsigned int fn_801F51E4(cSpawnController *self);
unsigned int fn_801F522C(cSpawnController *self);
unsigned int fn_801F5274(cSpawnController *self);
unsigned int fn_801F52BC(cSpawnController *self);
unsigned int fn_801F5304(cSpawnController *self);
unsigned int fn_801F534C(cSpawnController *self);
unsigned int fn_801F5394(cSpawnController *self);
unsigned int fn_801F53DC(cSpawnController *self);
unsigned int fn_801F5424(cSpawnController *self);
int fn_801F3430(cActorMoveToPos *self);
int fn_801F3474(cActorMoveToPos *self);
int fn_801F34CC(cActorMoveToPos *self);
unsigned int fn_801F3524(cActorMoveToPos *self);
unsigned int fn_801F356C(cActorMoveToPos *self);
unsigned int fn_801F35B4(cActorMoveToPos *self);
int fn_801F35FC(cActorMoveToPos *self);
int fn_801F3644(cActorMoveToPos *self);
void fn_8007B4D8(int h, int v);
void fn_8007B6E4(int h, int a, int b, int c);
int fn_8007D7C4(cScript *self, unsigned char kind);
void *fn_800ACFA8(int h);
int fn_8007AD0C(int h, int what, int at);
unsigned int fn_801F55FC(cAIRangedAttacker *self);
unsigned int fn_801F5644(cAIRangedAttacker *self);
unsigned int fn_801F568C(cAIRangedAttacker *self);
unsigned int fn_801F56D4(cAIRangedAttacker *self);
unsigned int fn_801F571C(cAIRangedAttacker *self);
unsigned int fn_801F5764(cAIRangedAttacker *self);
int fn_801F57AC(cAIRangedAttacker *self);
int fn_801F57F4(cAIRangedAttacker *self);
int fn_801F583C(cAIRangedAttacker *self);
int fn_801F5884(cAIRangedAttacker *self);
int fn_801F58CC(cAIRangedAttacker *self);
int fn_801F5914(cAIRangedAttacker *self);
void fn_801F1DF4(cAIRangedAttacker *self);
void fn_801F1F08(cAIRangedAttacker *self);
void fn_80133948(int h);
int fn_8046BD30(void *ev);
void fn_8007B8CC(int h, int v);
void fn_8007B7FC(int h, int v);
float fn_8007C3EC(void *ev);
float fn_8007C52C(void *ev);
float fn_8007C594(void *ev, float dmg, int type, int kind, int src, unsigned int flags);
float fn_8007C114(void *ev, float v);
float fn_8007C244(void *ev);
float fn_8007C2AC(void *ev);
float fn_8007C314(void *ev, float v);
float fn_801F5A04(cActorSetHealth *self);
unsigned int fn_801F5A4C(cActorSetHealth *self);
int fn_801F5A94(cActorSetHealth *self);
int fn_801F5AEC(cActorSetHealth *self);
float fn_801F5B44(cActorSetHealth *self);
int fn_801F5B8C(cActorSetHealth *self);
void fn_801F25B4(cActorSetHealth *self);
void fn_8046BBE8();
void fn_800863AC(int actor, int flags);
void fn_8007B998(int h, float v);
void fn_80131768(void);
void fn_801317A0(void);
void fn_80081470(char *name);
void fn_80435238(void *p, int v);
void fn_80083A90(void);
void fn_8046C9F0(int h);
int fn_8046C96C(void *ev);
extern char lbl_805723F4[];
extern char lbl_8057220C[];
int fn_801F5C28(cPlayerBonusMissions *self);
int fn_801F5C80(cPlayerBonusMissions *self);
int fn_801F5CC8(cPlayerBonusMissions *self);
int fn_801F5D10(cPlayerBonusMissions *self);
float fn_801F5D68(cPlayerBonusMissions *self);
unsigned int fn_801F5DB0(cPlayerBonusMissions *self);
int fn_801F5DF8(cPlayerBonusMissions *self);
int fn_801F5E40(cPlayerBonusMissions *self);
int fn_801F5E88(cPlayerBonusMissions *self);
int fn_801F5EE0(cPlayerBonusMissions *self);
void fn_8007B6A4(int on);
void fn_8007B77C(float v);
void fn_8007B7BC(float v);
void fn_80070228(int actor, int b, float f, int c, int d, int e);
int fn_801F5FD0(cAITeleportationToggle *self);
float fn_801F6028(cAITeleportationToggle *self);
int fn_801F60C4(cAIEnemyVictoryScene *self);
unsigned int fn_801F6170(cTemporaryAIPossession *self);
float fn_801F61B8(cTemporaryAIPossession *self);
float fn_801F6254(cAISetTeleportDistance *self);
float fn_801F629C(cAISetTeleportDistance *self);
unsigned int fn_800791C8(cScript *self, unsigned int i);
int fn_80079068(cScript *self, unsigned int i);
float fn_8007935C(cScript *self, unsigned int i);
char *fn_800794FC(cScript *self, unsigned int i);

cScript *fn_801EAA38(register cPathnodeToggle *self)
{
    return new cPathnodeToggle;
}

void fn_801EAA8C(register cPathnodeToggle *self) // slot 3
{
    self->on = 1;
}

void fn_801EAAB4(register cPathnodeToggle *self) // slot 4
{
    char ev[8];

    fn_8046BBA0(ev, fn_800797D4(self));
    if (!fn_801F3394(self) || !self->on) {
        self->on = 0;
        fn_80081208(ev, 0);
    }
}

void fn_801EAB34(register cPathnodeToggle *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    char ev[8];

    fn_8046BBA0(ev, fn_800797D4(self));
    if (self->on)
        fn_80081208(ev, 0);
    else
        fn_80081208(ev, 1);
    self->on = !self->on;
}

void fn_801EABE4(register cActorMoveToPos *self) // slot 5
{
    self->stage = 0;
    fn_8007A448(fn_801F3430(self));
    if (fn_801F35FC(self)) {
        char ev[8];
        fn_8046B5A8(ev, fn_801F3430(self));
        fn_8007BE0C(fn_804425F8(ev), 1);
    }
    char p0[8];
    fn_8046B6C8(p0, fn_801F3430(self));
    char p1[8];
    fn_8046B6C8(p1, fn_801F3524(self));
    char p2[8];
    fn_8046B6C8(p2, fn_801F356C(self));
    char p3[8];
    fn_8046B6C8(p3, fn_801F35B4(self));
    if (fn_801F3474(self)) {
        char ev[8];
        fn_8046B5A8(ev, fn_801F3430(self));
        self->count = fn_8046C898(ev);
        fn_8008291C(ev, 0, &self->v30, 0, 0);
        fn_8008291C(ev, 1, &self->v40, 0, 0);
        fn_8008291C(ev, 2, &self->v50, 0, 0);
        fn_8008291C(ev, 3, &self->v60, 0, 0);
    } else {
        fn_80082440(p0, &self->v30);
        fn_80082440(p1, &self->v40);
        fn_80082440(p2, &self->v50);
        fn_80082440(p3, &self->v60);
    }
    if (!fn_801F34CC(self)) {
        fn_8007A738(fn_801F3430(self), &self->v40);
        self->stage = 1;
    }
    if (fn_801F3644(self)) {
        char ev[8];
        fn_8046B5A8(ev, fn_801F3430(self));
        fn_80082F30(ev);
    }
}

float fn_801EAE68(register cActorMoveToPos *self, int h, int word, int value) // slot 37
{
    switch (self->stage) {
    case 0:
        break;
    case 1:
        fn_8007A738(fn_801F3430(self), &self->v50);
        self->stage = 2;
        break;
    case 2:
        fn_8007A738(fn_801F3430(self), &self->v60);
        self->stage = 3;
        break;
    case 3:
        fn_8007A4FC(fn_801F3430(self));
        break;
    }
    return -1.0f;
}

void fn_801EAF4C(register cActorMoveToPos *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (fn_801F34CC(self)) {
        if (fn_801F3644(self)) {
            char ev[8];
            fn_8046B5A8(ev, fn_801F3430(self));
            fn_80082FA4(ev);
        }
        fn_8007A738(fn_801F3430(self), &self->v40);
        self->stage = 1;
    }
}

void fn_801EB018(register cActorWalk *self) // slot 3
{
    self->node = 0;
    self->dir = 0;
    self->loop = 0;
    self->done = 0;
}

void fn_801EB060(register cActorWalk *self) // slot 5
{
    fn_8046B710(&self->actor, fn_801F36E0(self));
    if (fn_801F3724(self) == 0)
        fn_8007A448(fn_804425F8(&self->actor));
    else if (fn_801F3724(self) == 1)
        fn_8007A5DC(fn_804425F8(&self->actor));
    self->loop = fn_801F37B4(self);
    if (!fn_8046C898(&self->actor))
        return;
    if (!fn_801F376C(self))
        fn_8007A818(fn_804425F8(&self->actor), 1);
}

float fn_801EB16C(register cActorWalk *self, int h, int node, int value) // slot 37
{
    if (h != fn_804425F8(&self->actor))
        return -1.0f;
    if (self->done)
        return -1.0f;
    self->node = node;
    if (self->node == (int)fn_8046C898(&self->actor) - 1) {
        if (self->loop)
            self->dir = 1;
    } else if (self->node == 0 && self->dir) {
        self->dir = 0;
    }
    if (fn_801F38AC(self)) {
        fn_8007D8B0(self);
        char ev[8];
        fn_8046B5A8(ev, fn_800797D4(self));
        fn_80082F30(ev);
        return -1.0f;
    }
    if (fn_801F380C(self) > 0.0f) {
        fn_8007D404(self, fn_801F380C(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        return -1.0f;
    }
    fn_801EB508(self, self->node);
    return -1.0f;
}

void fn_801EB320(register cActorWalk *self, int h, int x, int value) // slot 43
{
    switch (x) {
    case 0:
        self->done = 1;
        break;
    }
}

void fn_801EB370(register cActorWalk *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 0:
    case 7:
        if (fn_801F3854(self)) {
            if (fn_801F3724(self) == 0)
                fn_8007A4FC(fn_804425F8(&self->actor));
            else if (fn_801F3724(self) == 1)
                fn_8007A658(fn_804425F8(&self->actor));
            self->done = 1;
            return;
        }
        if (fn_801F376C(self) == 1)
            fn_8007A818(fn_804425F8(&self->actor), 1);
        break;
    }
}

void fn_801EB490(register cActorWalk *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_801EB508(self, self->node);
        break;
    }
}

void fn_801EB508(register cActorWalk *self, int node)
{
    if (!self->dir)
        fn_8007A818(fn_804425F8(&self->actor), node + 1);
    else
        fn_8007A818(fn_804425F8(&self->actor), node - 1);
}

void fn_801EB59C(register cActorAIPause *self) // slot 3
{
    self->paused = 0;
    self->unk2C = 0;
}

void fn_801EB5D4(register cActorAIPause *self) // slot 5
{
    char ev[8];

    fn_8046B5A8(ev, fn_801F3958(self));
    if (fn_801F3A3C(self)) {
        fn_80082F30(ev);
        return;
    }
    if (!fn_801F399C(self) || fn_801F399C(self) == 2) {
        fn_8007A448(fn_801F3958(self));
        self->paused = 1;
    }
    if (fn_801F39E4(self)) {
        fn_80082F30(ev);
        self->unk2C = 1;
    }
}

void fn_801EB6B0(register cActorAIPause *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    char ev[8];

    fn_8046B5A8(ev, fn_801F3958(self));
    if (x == 1.0f || kind == 5) {
        if (self->unk2C == 1) {
            fn_80082FA4(ev);
            self->unk2C = 0;
        } else if (self->unk2C == 0) {
            fn_80082F30(ev);
            self->unk2C = 1;
        }
    }
    if (y == 1.0f || kind == 6) {
        if (fn_801F399C(self) == 1 && !self->paused) {
            fn_8007A448(fn_801F3958(self));
            self->paused = 1;
        } else if (self->paused) {
            fn_8007A4FC(fn_801F3958(self));
            self->paused = 0;
        }
    }
    if (kind == 0x11) {
    }
}

float fn_801EB824(register cActorAIPause *self, int h, int other, int a, int b, float dmg, int c, int value) // slot 21
{
    if (fn_801F399C(self) == 2 && h == fn_801F3958(self)) {
        fn_8007A4FC(fn_801F3958(self));
        self->paused = 0;
    }
    return dmg;
}

void fn_801EB8C4(register cActorAIPause *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10: {
        char ev[8];
        fn_8046B5A8(ev, fn_801F3958(self));
        fn_8007A4FC(fn_801F3958(self));
        fn_80082014(ev, 2);
        fn_800820A0(ev, 1);
        int actor = fn_8007C034(ev);
        if (actor) {
            fn_8008643C(actor);
            fn_8006645C(actor, 0);
        }
        char hit[8];
        fn_8046B638(hit, fn_804425F8(ev));
        if (fn_800809CC(hit) && fn_800861EC(fn_800809CC(hit)))
            fn_80082E90(ev, "flyerTeleport", 0xff, 0xff);
        else
            fn_80082E90(ev, "peonTeleport", 0xff, 0xff);
        break;
    }
    }
}

void fn_801EBA4C(register cActorControlState *self) // slot 5
{
    if (fn_801F3BBC(self) > 0) {
        if (fn_801F3BBC(self) == 1)
            fn_8007BA24(fn_800797D4(self), 0);
        else if (fn_801F3BBC(self) == 2)
            fn_8007BA24(fn_800797D4(self), 1);
        else if (fn_801F3BBC(self) == 3)
            fn_8007BA24(fn_800797D4(self), 2);
        else if (fn_801F3BBC(self) == 4)
            fn_8007BA24(fn_800797D4(self), 3);
        else if (fn_801F3BBC(self) == 5)
            fn_8007BA24(fn_800797D4(self), 4);
        return;
    }
    if (!fn_801F3B74(self)) {
        char ev[8];
        fn_8046B5A8(ev, fn_800797D4(self));
        fn_8007A448(fn_804425F8(ev));
        fn_8007B0EC(fn_801F3AE8(self), fn_801F3B2C(self), 0, 1);
    }
}

void fn_801EBBF4(register cActorControlState *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 0:
        if (fn_801F3B74(self) == 1) {
            char ev[8];
            fn_8046B5A8(ev, fn_800797D4(self));
            fn_8007A448(fn_804425F8(ev));
            fn_8007B0EC(fn_801F3AE8(self), fn_801F3B2C(self), 0, 1);
        }
        break;
    case 7: {
        char ev[8];
        fn_8046B5A8(ev, fn_800797D4(self));
        fn_8007A4FC(fn_804425F8(ev));
        break;
    }
    }
}

void fn_801EBD14(register cSpawnPeon *self) // slot 3
{
    self->unk28 = 1;
    self->unk2C = 0;
    self->unk30 = 0;
    self->unk34 = 0;
    self->unk48 = 0;
    self->count = 0;
    self->unk8C = 0;
    self->peons[0] = 0;
    self->peons[1] = 0;
    self->peons[2] = 0;
    self->peons[3] = 0;
    self->peons[4] = 0;
    self->peons[5] = 0;
    self->peons[6] = 0;
    self->peons[7] = 0;
    self->peons[8] = 0;
    self->peons[9] = 0;
    self->max = 0;
    self->unk54 = 0;
    self->unk58 = 0;
    self->unk88 = 0;
    self->unk84 = 0;
}

void fn_801EBDEC(register cSpawnPeon *self) // slot 5
{
    fn_8046B710(&self->actor, fn_801F3C58(self));
    self->max = fn_801F3CE4(self);
    if (self->max > 10)
        self->max = 10;
    if (fn_801F3F34(self)) {
        char ev[8];
        fn_8046B6C8(ev, fn_801F3F34(self));
        fn_80082440(ev, &self->pos);
    }
    if (!fn_801F3DBC(self)) {
        self->unk2C = 1;
        if (fn_801F3EA4(self) < 0.0f)
            fn_8007D404(self, fn_80171F8C() * 4.6566128730773926e-10f * fn_801F3EA4(self) * -1.0f, 0x14, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        else
            fn_8007D404(self, fn_801F3EA4(self), 0x14, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
}

int fn_801EBFA4(register cSpawnPeon *self, int h, int value) // slot 47
{
    if (self->count < fn_801F3D2C(self)) {
        fn_8007D404(self, fn_801F3EA4(self) < 0.0f ? -fn_801F3EA4(self) : fn_801F3EA4(self), 0x14, (float)(unsigned int)h, 0.0f, 0.0f, 0.0f, 0);
    } else if (self->unk54 == fn_801F3D2C(self) && !self->unk34) {
        char ev[8];
        fn_8046B6C8(ev, fn_801F3E14(self));
        fn_80082AFC(ev, fn_804425F8(ev), fn_800797D4(self), fn_801F3E5C(self), 0.0f, 0.0f, 0.0f, 0.0f);
        self->unk34 = 1;
    }
    return 1;
}

void fn_801EC148(register cSpawnPeon *self, int h, int other, int a, int b, float dmg, int value) // slot 22
{
    char ev[8];

    fn_8046B5A8(ev, h);
    unsigned int flags = fn_80081EC4(ev);
    int special = 0;
    if (flags & 0x2000000)
        special = 1;
    if (fn_801F3D2C(self) == 1 && !special)
        fn_8007D404(self, 4.0f, 0x32, 0.0f, 0.0f, 0.0f, 0.0f, h);
    if (h == fn_801F3F7C(self)) {
        if (fn_801F3FC4(self) == 0)
            fn_8007A4FC(fn_804425F8(&self->unk40));
        else if (fn_801F3FC4(self) == 1)
            fn_8007A658(fn_804425F8(&self->unk40));
        return;
    }
    if (fn_8007C034(ev)) {
        self->unk54++;
        if (self->unk54 == fn_801F3D2C(self) && !self->unk34) {
            char done[8];
            fn_8046B6C8(done, fn_801F3E14(self));
            fn_80082AFC(done, fn_804425F8(done), fn_800797D4(self), fn_801F3E5C(self), 0.0f, 0.0f, 0.0f, 0.0f);
            self->unk34 = 1;
        }
        if (fn_801F400C(self)) {
            int kind = 3;
            char killer[8];
            fn_8046B680(killer, other);
            if (dmg > 500.0f) {
                kind = 0;
            } else if (other == fn_80080B34() || (fn_80080300(killer) && fn_8009AC94(fn_80080300(killer)) == fn_80080B34())) {
                char e[8];
                fn_8046B5A8(e, other);
                int actor = fn_8007C034(e);
                if (actor) {
                    if (fn_8009B04C(actor) == 0x33 || fn_8009B04C(actor) == 0x36 || fn_8009B04C(actor) == 0x5d || a == 3)
                        kind = 1;
                    else if (fn_8009B04C(actor) == 0xba)
                        kind = 2;
                    else if (a == 7)
                        kind = 1;
                } else if (1) {
                    a = 3;
                    kind = 1;
                } else {
                    kind = 3;
                }
            } else if (a == 7 && other != h) {
                char e[8];
                fn_8046B680(e, other);
                if (fn_80080300(e) && fn_8009AC94(fn_80080300(e)) == fn_80080B34())
                    kind = 1;
                else
                    kind = 4;
            } else {
                kind = 4;
            }
            char report[8];
            fn_8046B6C8(report, fn_801F400C(self));
            fn_80082AFC(report, fn_804425F8(report), fn_800797D4(self), 0xc, (float)kind, 0.0f, 0.0f, 0.0f);
        }
        fn_8007C034S(ev)->fn_800B1FA8(0xfa0);
        char died[8];
        fn_8046B6C8(died, fn_801F3EEC(self));
        fn_80082AFC(died, fn_804425F8(died), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        lbl_8066C728++;
        if (lbl_8066C730)
            fn_80131724(lbl_8066C728, lbl_8066C72C);
    }
}

void fn_801EC6D4(register cSpawnPeon *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 50:
        ((cScriptV *)self)->s47(e, 0);
        break;
    case 20:
        if (self->unk28) {
            if (self->unk48 < self->max || a != 0.0f)
                fn_801ED3A4(self, (unsigned int)a);
            if (self->unk48 < self->max)
                fn_8007D404(self, 5.0f, 0x14, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        } else if (self->unk58 <= 4) {
            fn_8007D404(self, 5.0f, 0x14, a, 0.0f, 0.0f, 0.0f, 0);
            self->unk58++;
        } else {
            self->count++;
            self->unk54++;
            if (self->unk54 == fn_801F3D2C(self) && !self->unk34) {
                char done[8];
                fn_8046B6C8(done, fn_801F3E14(self));
                fn_80082AFC(done, fn_804425F8(done), fn_800797D4(self), fn_801F3E5C(self), 0.0f, 0.0f, 0.0f, 0.0f);
                self->unk34 = 1;
            }
            if (fn_801F400C(self)) {
                int kind = 4;
                char report[8];
                fn_8046B6C8(report, fn_801F400C(self));
                fn_80082AFC(report, fn_804425F8(report), fn_800797D4(self), 0xc, (float)kind, 0.0f, 0.0f, 0.0f);
            }
            char died[8];
            fn_8046B6C8(died, fn_801F3EEC(self));
            fn_80082AFC(died, fn_804425F8(died), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            self->unk58 = 0;
        }
        break;
    case 40: {
        if (!self->unk8C || !fn_804425F8(&self->unk40))
            return;
        int h = fn_80081E6C(&self->unk40);
        if (!h)
            return;
        self->unk28 = 1;
        fn_8006645C(h, 0);
        int actor = fn_8007C034(&self->unk40);
        if (actor)
            fn_8008643C(actor);
        if (fn_801F3F34(self)) {
            char ev[8];
            fn_8046B6C8(ev, fn_801F3F34(self));
            Vector p;
            if (fn_80081E6C(ev) && !fn_8046C8FC(ev) && fn_80082440(ev, &p)) {
                float dist = fn_804290F8(&self->pos, &p);
                if (dist < 2.5f)
                    fn_8007AC68(fn_804425F8(&self->unk40), fn_804425F8(ev), 0);
            }
        }
        if (fn_801F3D74(self)) {
            Vector p;
            char ev[8];
            fn_8046B6C8(ev, fn_801F3D74(self));
            fn_80082440(ev, &p);
            fn_8007A738(fn_804425F8(&self->unk40), &p);
        } else {
            if (fn_801F3FC4(self) == 0)
                fn_8007A4FC(fn_804425F8(&self->unk40));
            else if (fn_801F3FC4(self) == 1)
                fn_8007A658(fn_804425F8(&self->unk40));
            if (fn_801F440C(self))
                fn_801EDEB8(self, fn_804425F8(&self->unk40));
            fn_8046B710(&self->unk40, 0);
        }
        break;
    }
    }
}

float fn_801ECD2C(register cSpawnPeon *self, int h, int word, int value) // slot 37
{
    if (h != fn_804425F8(&self->unk40))
        return -1.0f;
    if (fn_801F3F7C(self)) {
        char target[8];
        fn_8046B6C8(target, fn_801F3F7C(self));
        Vector at;
        Vector to;
        fn_8007CF00(self, fn_801F3F7C(self), 0);
        fn_80082440(&self->unk40, &at);
        fn_80082440(target, &to);
        char ev[8];
        fn_8046B638(ev, h);
        if (fn_804290F8(&to, &at) <= 8.0f || (fn_800809CC(ev) && fn_800861EC(fn_800809CC(ev))))
            fn_8007A958(fn_804425F8(&self->unk40), fn_804425F8(target));
    } else if (fn_801F440C(self)) {
        fn_801EDEB8(self, fn_804425F8(&self->unk40));
    } else {
        if (fn_801F3FC4(self) == 0)
            fn_8007A4FC(fn_804425F8(&self->unk40));
        else if (fn_801F3FC4(self) == 1)
            fn_8007A658(fn_804425F8(&self->unk40));
        fn_8046B710(&self->unk40, 0);
    }
    return -1.0f;
}

void fn_801ECF7C(register cSpawnPeon *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 4:
        self->unk28 = !self->unk28;
        break;
    case 0:
    case 2:
        if (!self->unk2C && fn_801F3DBC(self)) {
            if (fn_801F3EA4(self) < 0.0f)
                fn_8007D404(self, fn_80171F8C() * 4.6566128730773926e-10f * fn_801F3EA4(self) * -1.0f, 0x14, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            else
                fn_8007D404(self, fn_801F3EA4(self), 0x14, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            self->unk2C = 1;
        }
        break;
    case 7:
        self->unk28 = 0;
        break;
    case 999:
        switch ((int)w) {
        case 0:
            self->unk88 = b;
            break;
        case 999:
            self->unk28 = 1;
            self->count = 0;
            self->unk54 = 0;
            self->unk48 = 0;
            fn_8007D8B0(self);
            fn_8007D404(self, 1.5f, 0x14, (float)self->unk84, 0.0f, 0.0f, 0.0f, 0);
            break;
        }
        break;
    }
}

float fn_801ED204(register cSpawnPeon *self, int h, int other, int a, int b, float dmg, int c, int value) // slot 21
{
    if (h == fn_801F3F7C(self))
        return dmg;
    if (fn_801F3F7C(self) && !self->unk30) {
        self->unk30 = 1;
        char ev[8];
        fn_8046B5F0(ev, fn_801F3F7C(self));
        if (fn_80080EFC(ev) && !fn_800A3F14(fn_80080EFC(ev)))
            return dmg;
        else if (fn_801F3FC4(self) == 0)
            fn_8007A4FC(h);
        else if (fn_801F3FC4(self) == 1)
            fn_8007A658(h);
    }
    if (fn_801F440C(self)) {
        char ev[8];
        fn_8046B638(ev, h);
        if (fn_8007C034(ev))
            fn_8006645CR(*fn_8007C034S(ev), 0);
    }
    return dmg;
}

void fn_801ED3A4(register cSpawnPeon *self, unsigned int h)
{
    if (self->count >= fn_801F3D2C(self)) {
        fn_8007D8B0(self);
        return;
    }
    char ev[8];
    fn_8046B5A8(ev, 0);
    int peon;
    if (h == 0 && self->unk48 < self->max) {
        if (fn_801F3C9C(self))
            h = fn_80082190(&self->actor, fn_801F3C9C(self));
        if (h == 0) {
            self->count++;
            self->unk54++;
            if (self->unk54 == fn_801F3D2C(self) && !self->unk34) {
                char done[8];
                fn_8046B6C8(done, fn_801F3E14(self));
                fn_80082AFC(done, fn_804425F8(done), fn_800797D4(self), fn_801F3E5C(self), 0.0f, 0.0f, 0.0f, 0.0f);
                self->unk34 = 1;
            }
            if (fn_801F400C(self)) {
                int kind = 4;
                char report[8];
                fn_8046B6C8(report, fn_801F400C(self));
                fn_80082AFC(report, fn_804425F8(report), fn_800797D4(self), 0xc, (float)kind, 0.0f, 0.0f, 0.0f);
            }
            char died[8];
            fn_8046B6C8(died, fn_801F3EEC(self));
            fn_80082AFC(died, fn_804425F8(died), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
            return;
        }
        lbl_8066C72C++;
        if (lbl_8066C730)
            fn_80131724(lbl_8066C728, lbl_8066C72C);
        self->unk84 = h;
        if (self->unk88) {
            char e[8];
            fn_8046B6C8(e, self->unk88);
            fn_80082AFC(e, self->unk88, fn_800797D4(self), 999, (float)h, 0.0f, 0.0f, 0.0f);
        }
        switch (self->unk48) {
        case 0:
            self->peons[0] = h;
            break;
        case 1:
            self->peons[1] = h;
            break;
        case 2:
            self->peons[2] = h;
            break;
        case 3:
            self->peons[3] = h;
            break;
        case 4:
            self->peons[4] = h;
            break;
        case 5:
            self->peons[5] = h;
            break;
        case 6:
            self->peons[6] = h;
            break;
        case 7:
            self->peons[7] = h;
            break;
        case 8:
            self->peons[8] = h;
            break;
        case 9:
            self->peons[9] = h;
            break;
        }
        if (fn_801F3FC4(self) == 0)
            fn_8007A448(h);
        else if (fn_801F3FC4(self) == 1)
            fn_8007A5DC(h);
        fn_8046B710((Ref8 *)ev, h);
        peon = fn_80081E6C(ev);
        if (peon)
            fn_8006645C(peon, 1);
        if (peon && stricmp(fn_801F4464(self), "") && stricmp(fn_801F4464(self), "Invalid Param")) {
            strncpy((char *)peon + 0xdc, fn_801F4464(self), 0x20);
            fn_800486C4(peon);
        }
        int actor = fn_8007C034(ev);
        if (actor)
            fn_80086410(actor);
        char e[8];
        fn_8046B638(e, fn_804425F8(ev));
        if (peon) {
            if (fn_800861EC(fn_800809CC(e)))
                self->unk8C = fn_80393D0C(peon, "flyerTeleport", 0xff, 0xff);
            else
                self->unk8C = fn_80393D0C(peon, "peonTeleport", 0xff, 0xff);
        }
        fn_8046B710(&self->unk40, h);
        fn_8007CF00(self, h, 0);
        self->unk48++;
    }
    char e[8];
    fn_8046B5A8(e, h);
    if (fn_8046C8FC(e)) {
        fn_80082FA4(e);
        if (fn_801F3FC4(self) == 0)
            fn_8007A448(h);
        else if (fn_801F3FC4(self) == 1)
            fn_8007A5DC(h);
        fn_8046B710((Ref8 *)ev, h);
        peon = fn_80081E6C(e);
        fn_8006645C(peon, 1);
        int actor = fn_8007C034(ev);
        if (actor)
            fn_80086410(actor);
        char hit[8];
        fn_8046B638(hit, fn_804425F8(ev));
        if (fn_800861EC(fn_800809CC(hit)))
            self->unk8C = fn_80393D0C(peon, "flyerTeleport", 0xff, 0xff);
        else
            self->unk8C = fn_80393D0C(peon, "peonTeleport", 0xff, 0xff);
        fn_8046B710(&self->unk40, h);
    }
    self->unk28 = 0;
    self->count++;
    fn_8007D404(self, 2.0f, 0x28, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    if (fn_801F4054(self))
        fn_801EDBAC(self, h);
}

#define SET_STAT(get, i)              \
    if (get(self) >= 0.0f)            \
        fn_8007B2E8(h, i, get(self));

void fn_801EDBAC(register cSpawnPeon *self, unsigned int h)
{
    SET_STAT(fn_801F40AC, 0)
    SET_STAT(fn_801F40F4, 1)
    SET_STAT(fn_801F413C, 2)
    SET_STAT(fn_801F4184, 3)
    SET_STAT(fn_801F41CC, 4)
    SET_STAT(fn_801F4214, 5)
    SET_STAT(fn_801F425C, 6)
    SET_STAT(fn_801F42A4, 7)
    SET_STAT(fn_801F42EC, 8)
    SET_STAT(fn_801F4334, 9)
    SET_STAT(fn_801F437C, 10)
    SET_STAT(fn_801F43C4, 11)
}

void fn_801EDEB8(register cSpawnPeon *self, int h)
{
    char ev[8];

    fn_8046B638(ev, h);
    fn_80082720(ev, fn_80080B34());
    if (fn_8007C034(ev))
        fn_8006645CR(*fn_8007C034S(ev), 1);
    fn_8007AA8C(h, fn_80080B34());
}

void fn_801EDF64(register cSpawnGroup *self) // slot 3
{
    self->count = 0;
    self->unk6C = 0;
    self->unk70 = 0;
    self->unk74 = 0;
}

#define ADD_SPAWNER(get, i)                         \
    if (get(self)) {                                \
        self->count++;                              \
        fn_8007CF00(self, get(self), 0);            \
        fn_8046B710(&self->spawners[i], get(self)); \
    }

void fn_801EDFAC(register cSpawnGroup *self) // slot 4
{
    ADD_SPAWNER(fn_801F4500, 0)
    ADD_SPAWNER(fn_801F4548, 1)
    ADD_SPAWNER(fn_801F4590, 2)
    ADD_SPAWNER(fn_801F45D8, 3)
    ADD_SPAWNER(fn_801F4620, 4)
    ADD_SPAWNER(fn_801F4668, 5)
    ADD_SPAWNER(fn_801F46B0, 6)
    ADD_SPAWNER(fn_801F46F8, 7)
    if (fn_801F4740(self))
        self->unk70 = 1;
}

void fn_801EE2C0(register cSpawnGroup *self, int h, int other, int value) // slot 14
{
    char ev[8];

    fn_8046B638(ev, other);
    if (!fn_80080A44(ev))
        return;
    self->unk74 = 1;
    if (!self->unk70)
        return;
    if (self->unk6C)
        return;
    int i;
    for (i = 0; i < self->count; i++)
        fn_801EE73C(self, i, 1, 0);
}

void fn_801EE398(register cSpawnGroup *self, int h, int other, int value) // slot 15
{
    char ev[8];

    fn_8046B638(ev, other);
    if (!fn_80080A44(ev))
        return;
    self->unk74 = 0;
}

void fn_801EE410(register cSpawnGroup *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (b == fn_800797D4(self))
        return;
    switch (kind) {
    case 7:
        self->unk6C = 1;
        for (int i = 0; i < self->count; i++)
            fn_801EE73C(self, i, 1, 7);
        break;
    case 4:
        self->unk70 = !self->unk70;
        if (self->unk70 && self->unk74) {
            char ev[8];
            fn_8046B6C8(ev, b);
            fn_80082AFC(ev, b, fn_800797D4(self), 999, 0.0f, 0.0f, 0.0f, 999.0f);
            for (int i = 0; i < self->count; i++)
                fn_801EE73C(self, i, 1, 0);
        }
        break;
    case 2:
        if (!fn_801F4798(self)) {
            char ev[8];
            fn_8046B6C8(ev, (unsigned int)x);
            fn_80082AFC(ev, fn_804425F8(ev), fn_800797D4(self), 999, 0.0f, 0.0f, 0.0f, 888.0f);
            ((cScriptV *)self)->s14(fn_800797D4(self), fn_80080B34(), 0);
        }
        break;
    case 999:
        if ((int)w != 999)
            return;
        for (int i = 0; i < self->count; i++)
            fn_801EE73C(self, i, 1, 999);
        break;
    }
}

#define SPAWNER_SEND(i)                                                                                         \
    case i:                                                                                                     \
        fn_80082AFC(&self->spawners[i], fn_804425F8(&self->spawners[i]), fn_800797D4(self), kind, on ? 1.0f : 0.0f, \
                    0.0f, 0.0f, 999.0f);                                                                        \
        break;

void fn_801EE73C(register cSpawnGroup *self, unsigned int i, int on, int kind)
{
    switch (i) {
    SPAWNER_SEND(0)
    SPAWNER_SEND(1)
    SPAWNER_SEND(2)
    SPAWNER_SEND(3)
    SPAWNER_SEND(4)
    SPAWNER_SEND(5)
    SPAWNER_SEND(6)
    SPAWNER_SEND(7)
    }
}

void fn_801EEB6C(register cSpawnController *self) // slot 3
{
    self->wave = 1;
    self->unk2C = 0;
    self->count = 0;
    self->unk3C = 0;
    self->unk98 = 0;
    self->unk38 = 0;
    self->fired[0] = 0;
    self->fired[1] = 0;
    self->fired[2] = 0;
    self->fired[3] = 0;
    self->fired[4] = 0;
    self->fired[5] = 0;
    self->fired[6] = 0;
    self->fired[7] = 0;
    self->fired[8] = 0;
    self->fired[9] = 0;
    self->unk6C[0] = 0;
    self->unk6C[1] = 0;
    self->unk6C[2] = 0;
    self->unk6C[3] = 0;
    self->unk6C[4] = 0;
    self->unk6C[5] = 0;
    self->unk6C[6] = 0;
    self->unk6C[7] = 0;
    self->unk6C[8] = 0;
    self->unk6C[9] = 0;
    self->unk34 = 0;
    self->unk9C = 0;
    self->unk68 = 0;
    self->unk94 = 0;
}

#define LINK_SPAWNER(get)                  \
    if (fn_8007CF00(self, get(self), 0)) \
        self->count++;

void fn_801EEC84(register cSpawnController *self) // slot 4
{
    LINK_SPAWNER(fn_801F492C)
    LINK_SPAWNER(fn_801F4A04)
    LINK_SPAWNER(fn_801F4ADC)
    LINK_SPAWNER(fn_801F4BB4)
    LINK_SPAWNER(fn_801F4C8C)
    LINK_SPAWNER(fn_801F4D64)
    LINK_SPAWNER(fn_801F4E3C)
    LINK_SPAWNER(fn_801F4F14)
    LINK_SPAWNER(fn_801F4FEC)
    LINK_SPAWNER(fn_801F50C4)
    if (self->count == 1)
        self->unk2C = 1;
    fn_801F07EC(self);
    if (fn_801F4844(self))
        self->unk68 = 1;
}

#define FIRE_SPAWNER(getH, getWave, i)                                                          \
    if (getH(self) == h && getWave(self) == self->wave && !self->fired[i]) {                    \
        fn_801EFE8C(self, self->wave, 0, getH(self));                                           \
        self->fired[i] = 1;                                                                     \
    }

void fn_801EEEFC(register cSpawnController *self, int h, int other, int value) // slot 14
{
    char ev[8];

    fn_8046B638(ev, other);
    if (!fn_80080A44(ev))
        return;
    self->unk98 = h;
    FIRE_SPAWNER(fn_801F492C, fn_801F4974, 0)
    else FIRE_SPAWNER(fn_801F4A04, fn_801F4A4C, 1)
    else FIRE_SPAWNER(fn_801F4ADC, fn_801F4B24, 2)
    else FIRE_SPAWNER(fn_801F4BB4, fn_801F4BFC, 3)
    else FIRE_SPAWNER(fn_801F4C8C, fn_801F4CD4, 4)
    else FIRE_SPAWNER(fn_801F4D64, fn_801F4DAC, 5)
    else FIRE_SPAWNER(fn_801F4E3C, fn_801F4E84, 6)
    else FIRE_SPAWNER(fn_801F4F14, fn_801F4F5C, 7)
    else FIRE_SPAWNER(fn_801F4FEC, fn_801F5034, 8)
    else FIRE_SPAWNER(fn_801F50C4, fn_801F510C, 9)
}

void fn_801EF380(register cSpawnController *self, int h, int other, int value) // slot 15
{
    self->unk98 = 0;
}

#define WAVE_REPORT(n, get)                                                                          \
    case n:                                                                                          \
        if (self->unk34 == self->unk6C[n - 1]) {                                                     \
            fn_801F06BC(self);                                                                       \
            if (get(self)) {                                                                         \
                fn_8046B710((Ref8 *)ev, get(self));                                                  \
                fn_80082AFC(ev, get(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);            \
            }                                                                                        \
        }                                                                                            \
        break;

void fn_801EF3BC(register cSpawnController *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (b == fn_800797D4(self))
        return;
    char ev[8];
    fn_8046B530(ev);
    switch (kind) {
    case 0:
        self->unk34++;
        int n;
        if (!self->unk2C)
            n = 1;
        else
            n = self->unk2C;
        switch (n) {
        WAVE_REPORT(1, fn_801F519C)
        WAVE_REPORT(2, fn_801F51E4)
        WAVE_REPORT(3, fn_801F522C)
        WAVE_REPORT(4, fn_801F5274)
        WAVE_REPORT(5, fn_801F52BC)
        WAVE_REPORT(6, fn_801F5304)
        WAVE_REPORT(7, fn_801F534C)
        WAVE_REPORT(8, fn_801F5394)
        WAVE_REPORT(9, fn_801F53DC)
        WAVE_REPORT(10, fn_801F5424)
        }
        break;
    case 999:
        if ((int)w == 999) {
            self->unk98 = b;
            return;
        } else if ((int)w == 888) {
            ((cScriptV *)self)->s14(self->unk9C, fn_80080B34(), 0);
        }
        break;
    case 7:
        if (self->unk2C == self->count) {
            char e[8];
            fn_8046B6C8(e, fn_801F489C(self));
            fn_80082AFC(e, fn_804425F8(e), fn_800797D4(self), fn_801F48E4(self), 0.0f, 0.0f, 0.0f, 0.0f);
            return;
        }
        int r = fn_801EFE8C(self, self->wave, 0, 0);
        self->unk3C = 0;
        if (!self->unk38) {
            self->unk38 = 1;
            self->unk2C += r;
        }
        self->wave++;
        self->unk2C += fn_801EFE8C(self, self->wave, 1, 0);
        fn_8007D404(self, 60.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
}

void fn_801EFCFC(register cSpawnController *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10: {
        self->unk9C = fn_801F0C60(self, self->wave);
        char ev[8];
        fn_8046B6C8(ev, self->unk9C);
        fn_80082AFC(ev, fn_804425F8(ev), fn_800797D4(self), 2, (float)(unsigned int)fn_800797D4(self), 0.0f, 0.0f, 0.0f);
        break;
    }
    case 20: {
        char ev[8];
        fn_8046B6C8(ev, fn_801F492C(self));
        fn_80082AFC(ev, fn_804425F8(ev), fn_800797D4(self), 999, 0.0f, 0.0f, 0.0f, 999.0f);
        self->unk34 = 0;
        break;
    }
    }
}

#define WAVE_SEND(getH, getWave)                                                                                  \
    if (getWave(self) == wave && getH(self) != skip) {                                                            \
        fn_8046B710((Ref8 *)ev, getH(self));                                                                      \
        fn_80082AFC(ev, fn_804425F8(ev), fn_800797D4(self), on ? 4 : 7, 0.0f, 0.0f, 0.0f, 0.0f);                   \
        n++;                                                                                                      \
    }

int fn_801EFE8C(register cSpawnController *self, int wave, int on, unsigned int skip)
{
    int n = 0;
    char ev[8];

    fn_8046B530(ev);
    if (!self->unk3C && !on && skip)
        self->unk3C = 1;
    WAVE_SEND(fn_801F492C, fn_801F4974)
    WAVE_SEND(fn_801F4A04, fn_801F4A4C)
    WAVE_SEND(fn_801F4ADC, fn_801F4B24)
    WAVE_SEND(fn_801F4BB4, fn_801F4BFC)
    WAVE_SEND(fn_801F4C8C, fn_801F4CD4)
    WAVE_SEND(fn_801F4D64, fn_801F4DAC)
    WAVE_SEND(fn_801F4E3C, fn_801F4E84)
    WAVE_SEND(fn_801F4F14, fn_801F4F5C)
    WAVE_SEND(fn_801F4FEC, fn_801F5034)
    WAVE_SEND(fn_801F50C4, fn_801F510C)
    return n;
}

void fn_801F06BC(register cSpawnController *self)
{
    if (self->unk68) {
        fn_8007D4F4(self, 5000, 0x14, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        return;
    }
    ((cScriptV *)self)->s23(fn_800797D4(self), 0, 7, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    if (self->unk98)
        ((cScriptV *)self)->s14(self->unk98, fn_80080B34(), 0);
    self->unk34 = 0;
}

#define WAVE_THRESHOLD(i, getH, getWave, getCount)            \
    case i:                                                   \
        if (!getH(self) || last == getWave(self)) {           \
            self->unk6C[i] = self->unk6C[i - 1];              \
            break;                                            \
        }                                                     \
        last = getWave(self);                                 \
        self->unk6C[i] = getCount(self);                      \
        break;

void fn_801F07EC(register cSpawnController *self)
{
    unsigned int last = 0;
    int i;

    for (i = 0; i <= 9; i++) {
        switch (i) {
        case 0:
            if (!fn_801F492C(self) || last == fn_801F4974(self))
                break;
            last = fn_801F4974(self);
            self->unk6C[0] = fn_801F49BC(self);
            break;
        WAVE_THRESHOLD(1, fn_801F4A04, fn_801F4A4C, fn_801F4A94)
        WAVE_THRESHOLD(2, fn_801F4ADC, fn_801F4B24, fn_801F4B6C)
        WAVE_THRESHOLD(3, fn_801F4BB4, fn_801F4BFC, fn_801F4C44)
        WAVE_THRESHOLD(4, fn_801F4C8C, fn_801F4CD4, fn_801F4D1C)
        WAVE_THRESHOLD(5, fn_801F4D64, fn_801F4DAC, fn_801F4DF4)
        WAVE_THRESHOLD(6, fn_801F4E3C, fn_801F4E84, fn_801F4ECC)
        WAVE_THRESHOLD(7, fn_801F4F14, fn_801F4F5C, fn_801F4FA4)
        WAVE_THRESHOLD(8, fn_801F4FEC, fn_801F5034, fn_801F507C)
        WAVE_THRESHOLD(9, fn_801F50C4, fn_801F510C, fn_801F5154)
        }
    }
}

unsigned int fn_801F0C60(register cSpawnController *self, int wave)
{
    if (fn_801F4974(self) == self->wave)
        return fn_801F492C(self);
    else if (fn_801F4974(self) == self->wave) // sic: the first spawner's wave again
        return fn_801F4A04(self);
    else if (fn_801F4B24(self) == self->wave)
        return fn_801F4ADC(self);
    else if (fn_801F4BFC(self) == self->wave)
        return fn_801F4BB4(self);
    else if (fn_801F4CD4(self) == self->wave)
        return fn_801F4C8C(self);
    else if (fn_801F4DAC(self) == self->wave)
        return fn_801F4D64(self);
    else if (fn_801F4E84(self) == self->wave)
        return fn_801F4E3C(self);
    else if (fn_801F4F5C(self) == self->wave)
        return fn_801F4F14(self);
    else if (fn_801F5034(self) == self->wave)
        return fn_801F4FEC(self);
    else if (fn_801F510C(self) == self->wave)
        return fn_801F50C4(self);
    else
        return 0;
}

void fn_801F0E84(register cActorPlayPath *self) // slot 4
{
    if (fn_801F5508(self))
        return;
    ((cScriptV *)self)->s23(fn_800797D4(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801F0F48(register cActorPlayPath *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    char ev[8];
    fn_8046B5A8(ev, fn_800797D4(self));
    char path[8];
    fn_8046B5F0(path, fn_800797D4(self));
    fn_80080F74(path, 0x1000);
    int ms = fn_801F111C(self);
    if (fn_801F5550(self) && ms > 0)
        fn_8007D4F4(self, ms, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801F104C(register cActorPlayPath *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10: {
        int ms = fn_801F111C(self);
        if (fn_801F5550(self) && ms > 0)
            fn_8007D4F4(self, ms, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
    }
}

int fn_801F111C(register cActorPlayPath *self)
{
    char ev[8];

    fn_8046B5A8(ev, fn_800797D4(self));
    if (fn_801F5550(self)) {
        fn_800804FC(ev);
        ((VObj *)fn_80081E6C(ev))->s19();
    }
    switch (fn_801F54C0(self)) {
    case 0:
        return fn_800803DC(ev, 0x158, 30.0f);
        break;
    case 1:
        return fn_800803DC(ev, 0x159, 30.0f);
        break;
    case 2:
        return fn_800803DC(ev, 0x15a, 30.0f);
        break;
    case 3:
        return fn_800803DC(ev, 0x15b, 30.0f);
        break;
    case 4:
        return fn_800803DC(ev, 0x15c, 30.0f);
        break;
    }
    return 0;
}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x804A0AF0-0x804A0B14

inline int sn_return_decl2(int a) { return a; }

void fn_801F12C4(register cAIRangedAttacker *self) // slot 5
{
    fn_8046B710(&self->actor, fn_800797D4(self));
    fn_8007A448(fn_804425F8(&self->actor));
    fn_8007B4D8(fn_804425F8(&self->actor), 4);
    fn_8007B6E4(fn_804425F8(&self->actor), 0, 0, 0);
    self->inRange[0] = 0;
    self->inRange[1] = 0;
    self->inRange[2] = 0;
    self->inRange[3] = 0;
    self->inRange[4] = 0;
    self->effect = 0;
    self->unk78 = 0;
    self->unk7C = 0;
    self->unk80 = 0;
    self->unk6C = 0;
    if (fn_801F57F4(self))
        self->active = 1;
    else
        self->active = 0;
    fn_8007CF00(self, fn_801F55FC(self), 0);
    if (fn_801F5644(self)) {
        fn_8046B710(&self->targets[0], fn_801F5644(self));
        self->inRange[0] = 1;
    }
    if (fn_801F568C(self)) {
        fn_8046B710(&self->targets[1], fn_801F568C(self));
        self->inRange[1] = 1;
    }
    if (fn_801F56D4(self)) {
        fn_8046B710(&self->targets[2], fn_801F56D4(self));
        self->inRange[2] = 1;
    }
    if (fn_801F571C(self)) {
        fn_8046B710(&self->targets[3], fn_801F571C(self));
        self->inRange[3] = 1;
    }
    if (fn_801F5764(self)) {
        fn_8046B710(&self->targets[4], fn_801F5764(self));
        self->inRange[4] = 1;
    }
    if (fn_801F58CC(self))
        fn_80082F30(&self->actor);
}

void fn_801F1534(register cAIRangedAttacker *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 0:
        if (self->unk7C == 1)
            return;
        self->unk7C = 1;
        if (fn_801F58CC(self)) {
            fn_80082FA4(&self->actor);
            if (fn_8007C034(&self->actor))
                self->effect = fn_80082E90(&self->actor, "peonTeleport", 0xff, 0xff);
        }
        if (fn_801F5884(self)) {
            fn_8007A448(fn_804425F8(&self->actor));
            fn_80082720(&self->actor, fn_80080B34());
            if (fn_8007C034(&self->actor))
                fn_8006645CR(*fn_8007C034S(&self->actor), 1);
            fn_8007AA8C(fn_804425F8(&self->actor), fn_80080B34());
        }
        if (fn_801F5914(self))
            fn_8007D404(self, 3.0f, 13, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 6:
        if (!self->unk6C) {
            self->unk6C = 1;
            if (fn_801F57AC(self))
                fn_8007A818(fn_800797D4(self), self->unk80 + 1);
            else
                fn_8007D404(self, 0.25f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
        break;
    case 7:
        fn_8007D8B0(self);
        fn_8007A4FC(fn_800797D4(self));
        break;
    }
}

float fn_801F17C0(register cAIRangedAttacker *self, int h, int other, int a, int b, float dmg, int c, int value) // slot 21
{
    if (self->active == 1) {
    } else {
        fn_8007D8B0(self);
        fn_8007A4FC(fn_800797D4(self));
    }
    return dmg;
}

void fn_801F1844(register cAIRangedAttacker *self, int h, int other, int value) // slot 14
{
    if (other == fn_804425F8(&self->targets[0]))
        self->inRange[0] = 1;
    else if (other == fn_804425F8(&self->targets[1]))
        self->inRange[1] = 1;
    else if (other == fn_804425F8(&self->targets[2]))
        self->inRange[2] = 1;
    else if (other == fn_804425F8(&self->targets[3]))
        self->inRange[3] = 1;
    else if (other == fn_804425F8(&self->targets[4]))
        self->inRange[4] = 1;
}

void fn_801F1944(register cAIRangedAttacker *self, int h, int other, int value) // slot 15
{
    if (other == fn_804425F8(&self->targets[0]))
        self->inRange[0] = 0;
    else if (other == fn_804425F8(&self->targets[1]))
        self->inRange[1] = 0;
    else if (other == fn_804425F8(&self->targets[2]))
        self->inRange[2] = 0;
    else if (other == fn_804425F8(&self->targets[3]))
        self->inRange[3] = 0;
    else if (other == fn_804425F8(&self->targets[4]))
        self->inRange[4] = 0;
}

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

void fn_801F1A44(register cAIRangedAttacker *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    fn_8007D7C4(self, 11);
    fn_8007D7C4(self, 10);
    fn_8007D7C4(self, 12);
    switch (kind) {
    case 13: {
        Vector at;
        Vector to;
        char ev[8];
        fn_8046B638(ev, fn_80080B34());
        fn_80082440(&self->actor, &at);
        fn_80082440(ev, &to);
        float dist = fn_804290F8(&to, &at);
        if (ABS(dist) <= 5.0f) {
            fn_8007D8B0(self);
            if (fn_8007C034(&self->actor))
                fn_8006645CR(*fn_8007C034S(&self->actor), 0);
            fn_8007A4FC(fn_804425F8(&self->actor));
        } else
            fn_8007D404(self, 1.0f, 13, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
    case 10:
        fn_8007D404(self, 0.25f, 11, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 11:
        fn_801F1F08(self);
        break;
    case 12:
        fn_801F1DF4(self);
        if (self->inRange[0] || self->inRange[1] || self->inRange[2] || self->inRange[3] || self->inRange[4])
            fn_8007D404(self, 0.25f, 11, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        else {
            fn_8007B0EC(fn_804425F8(&self->actor), 0x14a, 0, 0);
            fn_8007D404(self, 8.0f, 12, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
        break;
    }
}

void fn_801F1D78(register cAIRangedAttacker *self, int h, int other, int value) // slot 38
{
    fn_8007D404(self, 2.0f, 11, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801F1DF4(register cAIRangedAttacker *self)
{
    if (!fn_800ACFA8(fn_804425F8(&self->targets[0])))
        self->inRange[0] = 0;
    if (!fn_800ACFA8(fn_804425F8(&self->targets[1])))
        self->inRange[1] = 0;
    if (!fn_800ACFA8(fn_804425F8(&self->targets[2])))
        self->inRange[2] = 0;
    if (!fn_800ACFA8(fn_804425F8(&self->targets[3])))
        self->inRange[3] = 0;
    if (!fn_800ACFA8(fn_804425F8(&self->targets[4])))
        self->inRange[4] = 0;
}

void fn_801F1F08(register cAIRangedAttacker *self)
{
    fn_801F1DF4(self);
    if (self->inRange[0] == 1) {
        fn_8007AD0C(fn_804425F8(&self->actor), fn_804425F8(&self->targets[0]), fn_80080B34());
        return;
    } else if (self->inRange[1] == 1) {
        fn_8007AD0C(fn_804425F8(&self->actor), fn_804425F8(&self->targets[1]), fn_80080B34());
        return;
    } else if (self->inRange[2] == 1) {
        fn_8007AD0C(fn_804425F8(&self->actor), fn_804425F8(&self->targets[2]), fn_80080B34());
        return;
    } else if (self->inRange[3] == 1) {
        fn_8007AD0C(fn_804425F8(&self->actor), fn_804425F8(&self->targets[3]), fn_80080B34());
        return;
    } else if (self->inRange[4] == 1) {
        fn_8007AD0C(fn_804425F8(&self->actor), fn_804425F8(&self->targets[4]), fn_80080B34());
        return;
    } else if (fn_801F583C(self) == 1) {
        fn_8007B0EC(fn_804425F8(&self->actor), 0x13d, 0, 1);
        fn_8007D404(self, 8.0f, 12, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    } else {
        fn_8007D8B0(self);
        self->active = 0;
        fn_8007A4FC(fn_804425F8(&self->actor));
    }
}

void fn_801F2160(register cAIRangedAttacker *self, int h, int other, int a, int b, float dmg, int value) // slot 22
{
    if (h == fn_804425F8(&self->actor)) {
        fn_8007D8B0(self);
        fn_8007A4FC(h);
    }
}

void fn_801F21DC(register cBossRingOut *self) // slot 5
{
    fn_80133948(fn_800797D4(self));
}

void fn_801F2228(register cBossRingOut *self, int h, int other, int value) // slot 15
{
    char ev[8];
    fn_8046B638(ev, other);
    if (fn_80080A44(ev) || !fn_8046BD30(ev))
        return;
    fn_8007B8CC(fn_804425F8(ev), h);
}

void fn_801F22D0(register cBossRingOut *self, int h, int other, int value) // slot 14
{
    char ev[8];
    fn_8046B638(ev, other);
    if (fn_80080A44(ev) || !fn_8046BD30(ev))
        return;
    float health = fn_8007C3EC(ev) / fn_8007C52C(ev);
    if (health < 0.15f)
        return;
    fn_8007B7FC(fn_804425F8(ev), h);
}

void fn_801F23C0(register cActorSetHealth *self) // slot 4
{
    self->done = 0;
    if (!fn_801F5B8C(self) || !fn_801F5B8C(self)) {
        self->done = 1;
        fn_801F25B4(self);
    }
}

void fn_801F243C(register cActorSetHealth *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10: {
        char ev[8];
        fn_8046B5A8(ev, fn_80080B34());
        fn_8007C594(ev, 15.0f, 0, 0, 0, 2);
        fn_8007D404(self, 5.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
    }
}

void fn_801F251C(register cActorSetHealth *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (fn_801F5B8C(self) == 1 && !self->done) {
        self->done = 1;
        fn_801F25B4(self);
        return;
    } else
        fn_8007D8B0(self);
}

void fn_801F25B4(register cActorSetHealth *self)
{
    char ev[8];

    fn_8046B5A8(ev, 0);
    if (fn_801F5A4C(self))
        fn_8046B710((Ref8 *)ev, fn_801F5A4C(self));
    else if (fn_801F5A94(self)) {
        fn_8046B710((Ref8 *)ev, fn_80080B34());
        if (fn_801F5AEC(self)) {
            fn_8007D404(self, fn_801F5B44(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            return;
        }
    } else
        fn_8046B710((Ref8 *)ev, fn_800797D4(self));
    fn_8007C114(ev, fn_801F5A04(self) * fn_8007C244(ev));
    fn_8007C314(ev, fn_801F5A04(self) * fn_8007C2AC(ev));
}

void fn_801F271C(register cPlayerBonusMissions *self) // slot 3
{
    self->count = 0;
    self->stopped = 0;
}

void fn_801F2754(register cPlayerBonusMissions *self) // slot 4
{
    char ev[8];

    if (fn_801F5E88(self)) {
        fn_8046BBE8();
        return;
    }
    if (fn_801F5C28(self))
        fn_8007CF00(self, fn_80080B34(), 0);
    fn_8046B5A8(ev, fn_80080B34());
    if (fn_801F5D10(self))
        fn_800863AC(fn_8007C034(ev), 0x20000);
    if (fn_801F5D68(self) != 0.0f)
        fn_8007B998(fn_804425F8(ev), fn_801F5D68(self));
    if (fn_801F5CC8(self) > 0) {
        fn_80131724(0, fn_801F5CC8(self));
        fn_80131768();
    }
}

float fn_801F2884(register cPlayerBonusMissions *self, int h, int other, int a, int b, float dmg, int c, int value) // slot 21
{
    if (h != fn_80080B34() || fn_801F5E88(self))
        return dmg;
    fn_80081470("damage");
    return dmg;
}

void fn_801F2920(register cPlayerBonusMissions *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 12:
        if (fn_801F5C80(self) == (int)x || fn_801F5C80(self) == 4 || (fn_801F5C80(self) == 3 && (int)x != 4)) {
            if (self->count < fn_801F5CC8(self)) {
                fn_80131724(++self->count, fn_801F5CC8(self));
                if (!fn_801F5C80(self) && fn_801F5EE0(self) > 0)
                    fn_80435238(lbl_805723F4, fn_801F5EE0(self));
            }
            if (self->count == fn_801F5CC8(self) && !self->stopped && fn_801F5DB0(self)) {
                fn_801317A0();
                char ev[8];
                fn_8046B6C8(ev, fn_801F5DB0(self));
                fn_80082AFC(ev, fn_804425F8(ev), fn_800797D4(self), fn_801F5DF8(self), 0.0f, 0.0f, 0.0f, 0.0f);
            }
        }
        break;
    case 7:
        self->stopped = 1;
        if (fn_801F5E40(self))
            fn_80083A90();
        break;
    }
}

void fn_801F2B64(register cGlobalPeonCounter *self) // slot 4
{
    fn_8046C9F0(fn_800797D4(self));
}

void fn_801F2BB0(register cGlobalPeonCounter *self) // slot 5
{
}

void fn_801F2BD8(register cGlobalPeonCounter *self, int h, int other, int a, int b, float dmg, int value) // slot 22
{
    char ev[8];
    fn_8046B5A8(ev, h);
    if (!fn_8046C96C(ev))
        return;
    fn_80435238(lbl_8057220C, h);
}

void fn_801F2C64(register cGlobalPeonCounter *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 999:
        break;
    }
}

void fn_801F2CC0(register cAITeleportationToggle *self) // slot 4
{
    if (fn_801F5FD0(self)) {
        fn_8007B6A4(1);
        self->on = 1;
    } else {
        fn_8007B6A4(0);
        self->on = 0;
    }
    if (fn_801F6028(self) > 0.0f)
        fn_8007B77C(fn_801F6028(self));
}

void fn_801F2D60(register cAITeleportationToggle *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 4:
        self->on = !self->on;
        fn_8007B6A4(self->on);
        break;
    }
}

void fn_801F2DE8(register cAIEnemyVictoryScene *self) // slot 5
{
    char ev[8];

    fn_8046B638(ev, fn_80080B34());
    fn_8007CF00(self, fn_804425F8(ev), 0);
    self->done = 0;
}

void fn_801F2E58(register cAIEnemyVictoryScene *self, int h, int other, int a, int b, float dmg, int value) // slot 22
{
}

int fn_801F2E98(register cAIEnemyVictoryScene *self, int h, int other, int a, int b, float dmg, int value) // slot 20
{
    if (h == fn_80080B34() && !self->done) {
        self->done = 1;
        char ev[8];
        fn_8046B638(ev, fn_80080B34());
        fn_8007D8B0(self);
        fn_8007A448(fn_804425F8(ev));
        fn_80070228(fn_8007C034(ev), 0, 0.0f, 0, 0, 0);
        fn_8007D404(self, 3.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        return 0;
    }
    return 1;
}

void fn_801F2FC0(register cAIEnemyVictoryScene *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10: {
        char ev[8];
        fn_8046B6C8(ev, fn_801F60C4(self));
        fn_80082AFC(ev, fn_804425F8(ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    }
}

void fn_801F3098(register cTemporaryAIPossession *self) // slot 5
{
    fn_8046B710(&self->actor, fn_801F6170(self));
    fn_8007CF00(self, fn_804425F8(&self->actor), 0);
}

void fn_801F310C(register cTemporaryAIPossession *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    fn_8007A448(fn_804425F8(&self->actor));
    fn_8007D404(self, fn_801F61B8(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801F31BC(register cTemporaryAIPossession *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_8007A4FC(fn_804425F8(&self->actor));
        break;
    }
}

float fn_801F3240(register cTemporaryAIPossession *self, int h, int other, int a, int b, float dmg, int c, int value) // slot 21
{
    fn_8007D7C4(self, 10);
    fn_8007A4FC(fn_804425F8(&self->actor));
    return dmg;
}

void fn_801F32BC(register cAISetTeleportDistance *self, int h, int other, int value) // slot 14
{
    if (fn_801F6254(self) > 0.0f)
        fn_8007B7BC(fn_801F6254(self));
}

void fn_801F3328(register cAISetTeleportDistance *self, int h, int other, int value) // slot 15
{
    if (fn_801F629C(self) > 0.0f)
        fn_8007B7BC(fn_801F629C(self));
}

#define PARAM(T, cls, name, reader, i) \
    T name(register cls *self)         \
    {                                  \
        return reader(self, i);        \
    }
#define FLAG(cls, name, reader, i)       \
    int name(register cls *self)         \
    {                                    \
        return reader(self, i) != 0;     \
    }

PARAM(int, cPathnodeToggle, fn_801F3394, fn_80079068, 0)

cScript *fn_801F33DC(register cActorMoveToPos *self)
{
    return new cActorMoveToPos;
}

int fn_801F3430(register cActorMoveToPos *self)
{
    return fn_800797D4(self);
}

FLAG(cActorMoveToPos, fn_801F3474, fn_80079068, 0)
FLAG(cActorMoveToPos, fn_801F34CC, fn_80079068, 1)
PARAM(unsigned int, cActorMoveToPos, fn_801F3524, fn_800791C8, 2)
PARAM(unsigned int, cActorMoveToPos, fn_801F356C, fn_800791C8, 3)
PARAM(unsigned int, cActorMoveToPos, fn_801F35B4, fn_800791C8, 4)
PARAM(int, cActorMoveToPos, fn_801F35FC, fn_80079068, 5)
PARAM(int, cActorMoveToPos, fn_801F3644, fn_80079068, 6)

cScript *fn_801F368C(register cActorWalk *self)
{
    return new cActorWalk;
}

int fn_801F36E0(register cActorWalk *self)
{
    return fn_800797D4(self);
}

PARAM(int, cActorWalk, fn_801F3724, fn_80079068, 0)
PARAM(int, cActorWalk, fn_801F376C, fn_80079068, 1)
FLAG(cActorWalk, fn_801F37B4, fn_80079068, 2)
PARAM(float, cActorWalk, fn_801F380C, fn_8007935C, 3)
FLAG(cActorWalk, fn_801F3854, fn_80079068, 4)
FLAG(cActorWalk, fn_801F38AC, fn_80079068, 5)

cScript *fn_801F3904(register cActorAIPause *self)
{
    return new cActorAIPause;
}

int fn_801F3958(register cActorAIPause *self)
{
    return fn_800797D4(self);
}

PARAM(int, cActorAIPause, fn_801F399C, fn_80079068, 0)
FLAG(cActorAIPause, fn_801F39E4, fn_80079068, 1)
FLAG(cActorAIPause, fn_801F3A3C, fn_80079068, 2)

cScript *fn_801F3A94(register cActorControlState *self)
{
    return new cActorControlState;
}

int fn_801F3AE8(register cActorControlState *self)
{
    return fn_800797D4(self);
}

PARAM(int, cActorControlState, fn_801F3B2C, fn_80079068, 0)
PARAM(int, cActorControlState, fn_801F3B74, fn_80079068, 2)
PARAM(int, cActorControlState, fn_801F3BBC, fn_80079068, 3)

cScript *fn_801F3C04(register cSpawnPeon *self)
{
    return new cSpawnPeon;
}

int fn_801F3C58(register cSpawnPeon *self)
{
    return fn_800797D4(self);
}

PARAM(char *, cSpawnPeon, fn_801F3C9C, fn_800794FC, 0)
PARAM(int, cSpawnPeon, fn_801F3CE4, fn_80079068, 1)
PARAM(int, cSpawnPeon, fn_801F3D2C, fn_80079068, 2)
PARAM(unsigned int, cSpawnPeon, fn_801F3D74, fn_800791C8, 3)
FLAG(cSpawnPeon, fn_801F3DBC, fn_80079068, 4)
PARAM(unsigned int, cSpawnPeon, fn_801F3E14, fn_800791C8, 5)
PARAM(int, cSpawnPeon, fn_801F3E5C, fn_80079068, 6)
PARAM(float, cSpawnPeon, fn_801F3EA4, fn_8007935C, 7)
PARAM(unsigned int, cSpawnPeon, fn_801F3EEC, fn_800791C8, 8)
PARAM(unsigned int, cSpawnPeon, fn_801F3F34, fn_800791C8, 9)
PARAM(unsigned int, cSpawnPeon, fn_801F3F7C, fn_800791C8, 10)
PARAM(int, cSpawnPeon, fn_801F3FC4, fn_80079068, 11)
PARAM(unsigned int, cSpawnPeon, fn_801F400C, fn_800791C8, 12)
FLAG(cSpawnPeon, fn_801F4054, fn_80079068, 13)
PARAM(float, cSpawnPeon, fn_801F40AC, fn_8007935C, 14)
PARAM(float, cSpawnPeon, fn_801F40F4, fn_8007935C, 15)
PARAM(float, cSpawnPeon, fn_801F413C, fn_8007935C, 16)
PARAM(float, cSpawnPeon, fn_801F4184, fn_8007935C, 17)
PARAM(float, cSpawnPeon, fn_801F41CC, fn_8007935C, 18)
PARAM(float, cSpawnPeon, fn_801F4214, fn_8007935C, 19)
PARAM(float, cSpawnPeon, fn_801F425C, fn_8007935C, 20)
PARAM(float, cSpawnPeon, fn_801F42A4, fn_8007935C, 21)
PARAM(float, cSpawnPeon, fn_801F42EC, fn_8007935C, 22)
PARAM(float, cSpawnPeon, fn_801F4334, fn_8007935C, 23)
PARAM(float, cSpawnPeon, fn_801F437C, fn_8007935C, 24)
PARAM(float, cSpawnPeon, fn_801F43C4, fn_8007935C, 25)
FLAG(cSpawnPeon, fn_801F440C, fn_80079068, 26)
PARAM(char *, cSpawnPeon, fn_801F4464, fn_800794FC, 27)

cScript *fn_801F44AC(register cSpawnGroup *self)
{
    return new cSpawnGroup;
}

PARAM(unsigned int, cSpawnGroup, fn_801F4500, fn_800791C8, 0)
PARAM(unsigned int, cSpawnGroup, fn_801F4548, fn_800791C8, 1)
PARAM(unsigned int, cSpawnGroup, fn_801F4590, fn_800791C8, 2)
PARAM(unsigned int, cSpawnGroup, fn_801F45D8, fn_800791C8, 3)
PARAM(unsigned int, cSpawnGroup, fn_801F4620, fn_800791C8, 4)
PARAM(unsigned int, cSpawnGroup, fn_801F4668, fn_800791C8, 5)
PARAM(unsigned int, cSpawnGroup, fn_801F46B0, fn_800791C8, 6)
PARAM(unsigned int, cSpawnGroup, fn_801F46F8, fn_800791C8, 7)
FLAG(cSpawnGroup, fn_801F4740, fn_80079068, 8)
FLAG(cSpawnGroup, fn_801F4798, fn_80079068, 9)

cScript *fn_801F47F0(register cSpawnController *self)
{
    return new cSpawnController;
}

FLAG(cSpawnController, fn_801F4844, fn_80079068, 0)
PARAM(unsigned int, cSpawnController, fn_801F489C, fn_800791C8, 1)
PARAM(int, cSpawnController, fn_801F48E4, fn_80079068, 2)
PARAM(unsigned int, cSpawnController, fn_801F492C, fn_800791C8, 3)
PARAM(int, cSpawnController, fn_801F4974, fn_80079068, 4)
PARAM(int, cSpawnController, fn_801F49BC, fn_80079068, 5)
PARAM(unsigned int, cSpawnController, fn_801F4A04, fn_800791C8, 6)
PARAM(int, cSpawnController, fn_801F4A4C, fn_80079068, 7)
PARAM(int, cSpawnController, fn_801F4A94, fn_80079068, 8)
PARAM(unsigned int, cSpawnController, fn_801F4ADC, fn_800791C8, 9)
PARAM(int, cSpawnController, fn_801F4B24, fn_80079068, 10)
PARAM(int, cSpawnController, fn_801F4B6C, fn_80079068, 11)
PARAM(unsigned int, cSpawnController, fn_801F4BB4, fn_800791C8, 12)
PARAM(int, cSpawnController, fn_801F4BFC, fn_80079068, 13)
PARAM(int, cSpawnController, fn_801F4C44, fn_80079068, 14)
PARAM(unsigned int, cSpawnController, fn_801F4C8C, fn_800791C8, 15)
PARAM(int, cSpawnController, fn_801F4CD4, fn_80079068, 16)
PARAM(int, cSpawnController, fn_801F4D1C, fn_80079068, 17)
PARAM(unsigned int, cSpawnController, fn_801F4D64, fn_800791C8, 18)
PARAM(int, cSpawnController, fn_801F4DAC, fn_80079068, 19)
PARAM(int, cSpawnController, fn_801F4DF4, fn_80079068, 20)
PARAM(unsigned int, cSpawnController, fn_801F4E3C, fn_800791C8, 21)
PARAM(int, cSpawnController, fn_801F4E84, fn_80079068, 22)
PARAM(int, cSpawnController, fn_801F4ECC, fn_80079068, 23)
PARAM(unsigned int, cSpawnController, fn_801F4F14, fn_800791C8, 24)
PARAM(int, cSpawnController, fn_801F4F5C, fn_80079068, 25)
PARAM(int, cSpawnController, fn_801F4FA4, fn_80079068, 26)
PARAM(unsigned int, cSpawnController, fn_801F4FEC, fn_800791C8, 27)
PARAM(int, cSpawnController, fn_801F5034, fn_80079068, 28)
PARAM(int, cSpawnController, fn_801F507C, fn_80079068, 29)
PARAM(unsigned int, cSpawnController, fn_801F50C4, fn_800791C8, 30)
PARAM(int, cSpawnController, fn_801F510C, fn_80079068, 31)
PARAM(int, cSpawnController, fn_801F5154, fn_80079068, 32)
PARAM(unsigned int, cSpawnController, fn_801F519C, fn_800791C8, 34)
PARAM(unsigned int, cSpawnController, fn_801F51E4, fn_800791C8, 35)
PARAM(unsigned int, cSpawnController, fn_801F522C, fn_800791C8, 36)
PARAM(unsigned int, cSpawnController, fn_801F5274, fn_800791C8, 37)
PARAM(unsigned int, cSpawnController, fn_801F52BC, fn_800791C8, 38)
PARAM(unsigned int, cSpawnController, fn_801F5304, fn_800791C8, 39)
PARAM(unsigned int, cSpawnController, fn_801F534C, fn_800791C8, 40)
PARAM(unsigned int, cSpawnController, fn_801F5394, fn_800791C8, 41)
PARAM(unsigned int, cSpawnController, fn_801F53DC, fn_800791C8, 42)
PARAM(unsigned int, cSpawnController, fn_801F5424, fn_800791C8, 43)

cScript *fn_801F546C(register cActorPlayPath *self)
{
    return new cActorPlayPath;
}

PARAM(int, cActorPlayPath, fn_801F54C0, fn_80079068, 0)
PARAM(int, cActorPlayPath, fn_801F5508, fn_80079068, 2)
FLAG(cActorPlayPath, fn_801F5550, fn_80079068, 3)

cScript *fn_801F55A8(register cAIRangedAttacker *self)
{
    return new cAIRangedAttacker;
}

PARAM(unsigned int, cAIRangedAttacker, fn_801F55FC, fn_800791C8, 0)
PARAM(unsigned int, cAIRangedAttacker, fn_801F5644, fn_800791C8, 1)
PARAM(unsigned int, cAIRangedAttacker, fn_801F568C, fn_800791C8, 2)
PARAM(unsigned int, cAIRangedAttacker, fn_801F56D4, fn_800791C8, 3)
PARAM(unsigned int, cAIRangedAttacker, fn_801F571C, fn_800791C8, 4)
PARAM(unsigned int, cAIRangedAttacker, fn_801F5764, fn_800791C8, 5)
PARAM(int, cAIRangedAttacker, fn_801F57AC, fn_80079068, 6)
PARAM(int, cAIRangedAttacker, fn_801F57F4, fn_80079068, 7)
PARAM(int, cAIRangedAttacker, fn_801F583C, fn_80079068, 8)
PARAM(int, cAIRangedAttacker, fn_801F5884, fn_80079068, 9)
PARAM(int, cAIRangedAttacker, fn_801F58CC, fn_80079068, 10)
PARAM(int, cAIRangedAttacker, fn_801F5914, fn_80079068, 11)

cScript *fn_801F595C(register cBossRingOut *self)
{
    return new cBossRingOut;
}


cScript *fn_801F59B0(register cActorSetHealth *self)
{
    return new cActorSetHealth;
}

PARAM(float, cActorSetHealth, fn_801F5A04, fn_8007935C, 0)
PARAM(unsigned int, cActorSetHealth, fn_801F5A4C, fn_800791C8, 1)
FLAG(cActorSetHealth, fn_801F5A94, fn_80079068, 2)
FLAG(cActorSetHealth, fn_801F5AEC, fn_80079068, 3)
PARAM(float, cActorSetHealth, fn_801F5B44, fn_8007935C, 4)
PARAM(int, cActorSetHealth, fn_801F5B8C, fn_80079068, 5)

cScript *fn_801F5BD4(register cPlayerBonusMissions *self)
{
    return new cPlayerBonusMissions;
}

FLAG(cPlayerBonusMissions, fn_801F5C28, fn_80079068, 0)
PARAM(int, cPlayerBonusMissions, fn_801F5C80, fn_80079068, 1)
PARAM(int, cPlayerBonusMissions, fn_801F5CC8, fn_80079068, 2)
FLAG(cPlayerBonusMissions, fn_801F5D10, fn_80079068, 3)
PARAM(float, cPlayerBonusMissions, fn_801F5D68, fn_8007935C, 4)
PARAM(unsigned int, cPlayerBonusMissions, fn_801F5DB0, fn_800791C8, 5)
PARAM(int, cPlayerBonusMissions, fn_801F5DF8, fn_80079068, 6)
PARAM(int, cPlayerBonusMissions, fn_801F5E40, fn_80079068, 7)
FLAG(cPlayerBonusMissions, fn_801F5E88, fn_80079068, 8)
PARAM(int, cPlayerBonusMissions, fn_801F5EE0, fn_80079068, 9)

cScript *fn_801F5F28(register cGlobalPeonCounter *self)
{
    return new cGlobalPeonCounter;
}


cScript *fn_801F5F7C(register cAITeleportationToggle *self)
{
    return new cAITeleportationToggle;
}

FLAG(cAITeleportationToggle, fn_801F5FD0, fn_80079068, 0)
PARAM(float, cAITeleportationToggle, fn_801F6028, fn_8007935C, 1)

cScript *fn_801F6070(register cAIEnemyVictoryScene *self)
{
    return new cAIEnemyVictoryScene;
}

FLAG(cAIEnemyVictoryScene, fn_801F60C4, fn_800791C8, 0)

cScript *fn_801F611C(register cTemporaryAIPossession *self)
{
    return new cTemporaryAIPossession;
}

PARAM(unsigned int, cTemporaryAIPossession, fn_801F6170, fn_800791C8, 0)
PARAM(float, cTemporaryAIPossession, fn_801F61B8, fn_8007935C, 1)

cScript *fn_801F6200(register cAISetTeleportDistance *self)
{
    return new cTemporaryAIPossession; // sic, docs/story.md section 4.2
}

PARAM(float, cAISetTeleportDistance, fn_801F6254, fn_8007935C, 0)
PARAM(float, cAISetTeleportDistance, fn_801F629C, fn_8007935C, 1)
}
