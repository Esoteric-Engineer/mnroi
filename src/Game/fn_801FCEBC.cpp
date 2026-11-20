// The object, prop and trigger script classes, their clones and parameter accessors (docs/story.md row 12).
// Pool read from 0x804A1740 (extern_pool).

inline int sn_return_decl(int a) { return a; }

struct cScript {
    char d[0x24];
    char *vptr; // +0x24
};

struct cScriptV { // cScript's virtual slots, for calls on self
    char d[0x24];
    virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22();
    virtual void s23(int a, int b, int kind, float x, float y, float z, float w, int value); // +0xB8
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
    char pad0[0x50];
    char unk50[0x28];   // +0x50
    char unk78[0x44];   // +0x78
    char name[0x20];    // +0xBC
    char padDC[0x68];
    int unk144;         // +0x144, a count (cObjectMove reads it as its last node + 1)
    struct SPath *path; // +0x148
    char pad14C[0x4C];
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

struct SPath {
    char pad0[0x40];
    Vector a; // +0x40
    char pad50[0x20];
    Vector b; // +0x70
};

struct HkRef { // 4 bytes, returned by value
    int v;
    int fn_80436294() __asm__("fn_80436294");
};

struct HkVec {
    float v[4];
    HkVec(Vector *from) __asm__("fn_804362D4");
    HkVec(const HkVec &o);
};

struct SBodyBase {
    int unk0;
};

struct SBody : SBodyBase { // what fn_800B24AC returns
    int pad;
};

struct Placement {
    char d[0x40];
    Placement();
};

struct SWorld {
    char pad0[0x3a0];
    char *unk3A0; // +0x3A0
};

struct SHit {
    char pad0[0x18];
    float force; // +0x18
};

struct cObjectExplosion : cScript { // 0x28
    cObjectExplosion() __asm__("fn_80468D74");
};

struct cObjectSetCollision : cScript { // 0x38
    int on;    // +0x28
    int unk2C; // +0x2C
    int unk30; // +0x30, set when the object's flags have bit 1
    int count; // +0x34
    cObjectSetCollision() __asm__("fn_80468DC0");
};

struct cTriggerRelay : cScript { // 0x38
    float unk28; // +0x28
    float unk2C; // +0x2C
    float unk30; // +0x30
    float unk34; // +0x34
    cTriggerRelay() __asm__("fn_80468F3C");
};

struct cObjectMove : cScript { // 0x38
    int unk28;         // +0x28
    unsigned int node; // +0x2C
    int stop;          // +0x30
    int busy;          // +0x34
    cObjectMove() __asm__("fn_80468E0C");
};

struct cObjectRumbleShake : cScript { // 0x34
    float strength; // +0x28
    int rumble;     // +0x2C
    int shake;      // +0x30
    cObjectRumbleShake() __asm__("fn_80468E58");
};

struct cTimerTrigger : cScript { // 0x2C
    int running; // +0x28
    cTimerTrigger() __asm__("fn_80468EA4");
};

struct cTriggerOnAction : cScript { // 0x7C
    int count;      // +0x28
    int armed;      // +0x2C
    int done;       // +0x30
    int unk34;      // +0x34
    int linked[4];  // +0x38
    int hit[4];     // +0x48
    int fired;      // +0x58
    int handles[4]; // +0x5C
    int alt[4];     // +0x6C
    cTriggerOnAction() __asm__("fn_80468EF0");
};

struct cSetAnimFrame : cScript { // 0x2C
    float health; // +0x28
    cSetAnimFrame() __asm__("fn_80468F88");
};

struct cDebrisFall : cScript { // 0x34
    int count17; // +0x28, kind 17 messages
    int count18; // +0x2C
    int count19; // +0x30
    cDebrisFall() __asm__("fn_80468FD4");
};

struct cVehicleBreak : cScript { // 0x48
    Ref8 actor; // +0x28
    int armed;  // +0x30
    int unk34;  // +0x34
    int broken; // +0x38
    int unk3C;  // +0x3C
    int sound;  // +0x40
    int volume; // +0x44
    cVehicleBreak() __asm__("fn_80469020");
};

struct cVehicleBarrier : cScript { // 0x50
    char pad28[8];
    Vector unk30; // +0x30
    int hit;      // +0x40
    char pad44[0xC];
    cVehicleBarrier() __asm__("fn_8046907C");
};

struct cGenBreakProp : cScript { // 0x30
    int off;     // +0x28
    int hasName; // +0x2C
    cGenBreakProp() __asm__("fn_804690D4");
};

struct cDamagePropOnTrigger : cScript { // 0x4C
    int done[8]; // +0x28
    int count;   // +0x48
    cDamagePropOnTrigger() __asm__("fn_80469120");
};

struct cPortalControl : cScript { // 0x2C
    int on; // +0x28
    cPortalControl() __asm__("fn_8046916C");
};

struct cPropRespawn : cScript { // 0x30
    int enabled; // +0x28
    int ready;   // +0x2C
    cPropRespawn() __asm__("fn_804691B8");
};

struct cRemoveObjects : cScript { // 0x28
    cRemoveObjects() __asm__("fn_80469204");
};

struct cCrystalBreak : cScript { // 0x30
    int hit;    // +0x28
    int immune; // +0x2C
    cCrystalBreak() __asm__("fn_80469250");
};

struct cCrystalBreak_Phase2 : cScript { // 0x30
    int unk28;  // +0x28
    int immune; // +0x2C
    cCrystalBreak_Phase2() __asm__("fn_8046929C");
};

struct cCameraMPToggle : cScript { // 0x2C
    int on; // +0x28
    cCameraMPToggle() __asm__("fn_804692E8");
};

struct cLabConsole : cScript { // 0x2C
    int used; // +0x28
    cLabConsole() __asm__("fn_80469334");
};

struct cWieldableToggle : cScript { // 0x30
    int enabled; // +0x28
    int locked;  // +0x2C
    cWieldableToggle() __asm__("fn_80469380");
};

struct cReverseWallRenderToggle : cScript { // 0x28
    cReverseWallRenderToggle() __asm__("fn_804693CC");
};

struct cPropGroupFade : cScript { // 0x28
    cPropGroupFade() __asm__("fn_80469418");
};

struct cMP_MatchTrigger : cScript { // 0x28
    cMP_MatchTrigger() __asm__("fn_80469464");
};

struct cCameraSet : cScript { // 0x28
    cCameraSet() __asm__("fn_804694B0");
};

struct SObjList {
    char pad0[0x130];
    SObj *first; // +0x130
};

extern "C" {
int fn_800797D4(cScript *self);
void fn_8007D404(cScript *self, float seconds, int kind, float a, float b, float c, float d, int e);
int fn_80171F8C(void);
void fn_8046B6C8(void *ev, int x);
void fn_8046B680(void *ev, int x);
unsigned int fn_80082190(void *at, char *name);
int fn_80081F28(void *ev);
SObj *fn_80081E6C(void *ev);
int strnicmp(const char *a, const char *b, int n);
void fn_80066794(void *o, int on);
int fn_80080300(void *ev);
int fn_8009AD80(int actor);
void fn_800820A0(void *ev, int a);
void fn_80082014(void *ev, int a);
void fn_80081F8C(void *ev, int a);
int fn_80082E90(void *ev, char *name, int a, int b);
int fn_804425F8(void *ev);
void fn_80114CC0(int h);
float fn_80207BB4(cObjectExplosion *self);
float fn_80207BFC(cObjectExplosion *self);
int fn_80207C44(cObjectExplosion *self);
char *fn_80207C8C(cObjectExplosion *self);
int fn_80207CD4(cObjectSetCollision *self);
int fn_80207D1C(cObjectSetCollision *self);
float fn_80207D64(cObjectSetCollision *self);
float fn_80207DAC(cObjectSetCollision *self);
float fn_80207DF4(cObjectSetCollision *self);
int fn_80207E3C(cObjectSetCollision *self);
void fn_801FD788(cObjectSetCollision *self);
unsigned int fn_80208F64(cTriggerRelay *self);
float fn_80208FAC(cTriggerRelay *self);
char *fn_80208FF4(cTriggerRelay *self);
unsigned int fn_8020903C(cTriggerRelay *self);
float fn_80209084(cTriggerRelay *self);
char *fn_802090CC(cTriggerRelay *self);
unsigned int fn_80209114(cTriggerRelay *self);
float fn_8020915C(cTriggerRelay *self);
char *fn_802091A4(cTriggerRelay *self);
unsigned int fn_802091EC(cTriggerRelay *self);
float fn_80209234(cTriggerRelay *self);
char *fn_8020927C(cTriggerRelay *self);
unsigned int fn_802092C4(cTriggerRelay *self);
float fn_8020930C(cTriggerRelay *self);
char *fn_80209354(cTriggerRelay *self);
unsigned int fn_8020939C(cTriggerRelay *self);
float fn_802093E4(cTriggerRelay *self);
char *fn_8020942C(cTriggerRelay *self);
unsigned int fn_80209474(cTriggerRelay *self);
float fn_802094BC(cTriggerRelay *self);
char *fn_80209504(cTriggerRelay *self);
unsigned int fn_8020954C(cTriggerRelay *self);
float fn_80209594(cTriggerRelay *self);
char *fn_802095DC(cTriggerRelay *self);
unsigned int fn_80209624(cTriggerRelay *self);
float fn_8020966C(cTriggerRelay *self);
char *fn_802096B4(cTriggerRelay *self);
unsigned int fn_802096FC(cTriggerRelay *self);
float fn_80209744(cTriggerRelay *self);
char *fn_8020978C(cTriggerRelay *self);
unsigned int fn_802097D4(cTriggerRelay *self);
float fn_8020981C(cTriggerRelay *self);
char *fn_80209864(cTriggerRelay *self);
unsigned int fn_802098AC(cTriggerRelay *self);
float fn_802098F4(cTriggerRelay *self);
char *fn_8020993C(cTriggerRelay *self);
int fn_80209984(cTriggerRelay *self);
char *fn_802099CC(cTriggerRelay *self);
float fn_80209A14(cTriggerRelay *self);
int stricmp(const char *a, const char *b);
float fn_8008379C(char *s, int i);
int fn_80083734(char *name);
int fn_80207E94(cObjectMove *self);
float fn_80207EDC(cObjectMove *self);
float fn_80207F24(cObjectMove *self);
float fn_80207F6C(cObjectMove *self);
int fn_80207FB4(cObjectMove *self);
int fn_80207FFC(cObjectMove *self);
int fn_80208050(cObjectMove *self);
unsigned int fn_802080A4(cObjectMove *self);
unsigned int fn_802080EC(cObjectMove *self);
unsigned int fn_80208134(cObjectMove *self);
unsigned int fn_8020817C(cObjectMove *self);
int fn_802081C4(cObjectMove *self);
void fn_801FF210(cObjectMove *self, int on);
void fn_801FF2D4(cObjectMove *self, int node);
void fn_801FEFF4(cObjectMove *self, int h, int kind, float x, float y, float z, float w);
void fn_8046B530(void *ev);
void *fn_800B1CC8(void *e);
void fn_800A90F4(void *w);
void fn_800A916C(void *w);
void fn_80082A44(void *ev, int node, float speed, int a);
int fn_8020820C(cObjectRumbleShake *self);
float fn_80208264(cObjectRumbleShake *self);
float fn_802082AC(cObjectRumbleShake *self);
float fn_802082F4(cObjectRumbleShake *self);
int fn_8020833C(cObjectRumbleShake *self);
int fn_80208384(cObjectRumbleShake *self);
float fn_802083DC(cObjectRumbleShake *self);
float fn_80208424(cObjectRumbleShake *self);
float fn_8020846C(cObjectRumbleShake *self);
float fn_802084B4(cObjectRumbleShake *self);
float fn_802084FC(cObjectRumbleShake *self);
void fn_801FF7E4(cObjectRumbleShake *self);
void fn_801FF970(cObjectRumbleShake *self);
float fn_801FFA14(cObjectRumbleShake *self);
int fn_80080B34();
void fn_8046B638(void *ev, int x);
SActor *fn_8007C034S(void *ev) __asm__("fn_8007C034");
Vector *fn_800B1724(SObj *o);
Vector *fn_800B1724R(SObj &o) __asm__("fn_800B1724");
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_80434040(Vector *v);
int fn_80080ABC();
void fn_80083DE0(float a, float b, unsigned int ms, int c);
void fn_80083D78(float a, float b, unsigned int ms, int c, unsigned short pad);
void fn_80083EE8(unsigned int ms, float strength, int c);
void fn_8007D8B0(cScript *self);
float fn_80208544(cTimerTrigger *self);
float fn_8020858C(cTimerTrigger *self);
int fn_802085D4(cTimerTrigger *self);
unsigned int fn_8020861C(cTimerTrigger *self);
unsigned int fn_80208664(cTimerTrigger *self);
unsigned int fn_802086AC(cTimerTrigger *self);
unsigned int fn_802086F4(cTimerTrigger *self);
unsigned int fn_8020873C(cTimerTrigger *self);
unsigned int fn_80208784(cTimerTrigger *self);
unsigned int fn_802087CC(cTimerTrigger *self);
unsigned int fn_80208814(cTimerTrigger *self);
int fn_8020885C(cTimerTrigger *self);
void fn_801FFDA0(cTimerTrigger *self);
int fn_802088A4(cTriggerOnAction *self);
float fn_802088EC(cTriggerOnAction *self);
int fn_80208934(cTriggerOnAction *self);
int fn_8020897C(cTriggerOnAction *self);
int fn_802089C4(cTriggerOnAction *self);
int fn_80208A0C(cTriggerOnAction *self);
int fn_80208A54(cTriggerOnAction *self);
int fn_80208A9C(cTriggerOnAction *self);
unsigned int fn_80208AE4(cTriggerOnAction *self);
unsigned int fn_80208B2C(cTriggerOnAction *self);
unsigned int fn_80208B74(cTriggerOnAction *self);
unsigned int fn_80208BBC(cTriggerOnAction *self);
unsigned int fn_80208C04(cTriggerOnAction *self);
float fn_80208C4C(cTriggerOnAction *self);
unsigned int fn_80208C94(cTriggerOnAction *self);
float fn_80208CDC(cTriggerOnAction *self);
unsigned int fn_80208D24(cTriggerOnAction *self);
float fn_80208D6C(cTriggerOnAction *self);
unsigned int fn_80208DB4(cTriggerOnAction *self);
float fn_80208DFC(cTriggerOnAction *self);
int fn_80208E44(cTriggerOnAction *self);
int fn_80208E8C(cTriggerOnAction *self);
float fn_80208ED4(cTriggerOnAction *self);
int fn_80208F1C(cTriggerOnAction *self);
int fn_8007CF00(cScript *script, int handle, int value);
int fn_8007D070(cScript *script, int handle);
int fn_80201558(cTriggerOnAction *self, int h);
void fn_8020105C(cTriggerOnAction *self, int h);
void fn_802012CC(cTriggerOnAction *self);
int fn_800809CC(void *ev);
SActor *fn_800809CCS(void *ev) __asm__("fn_800809CC");
void *fn_800B14A0R(SObj &o) __asm__("fn_800B14A0");
float fn_80086730(void *actor);
void fn_8046B5F0(void *ev, int x);
int fn_80080EFC(void *ev);
void fn_800A3588(int actor, int other, float f, int a, int v, float g);
void fn_8046D4F8(void *ev, int h);
void *fn_800B1540(SObj *o);
float fn_800A4054(void *p);
float fn_80209A5C(cSetAnimFrame *self);
float fn_80209AA4(cSetAnimFrame *self);
float fn_80209AEC(cSetAnimFrame *self);
float fn_80209B34(cSetAnimFrame *self);
float fn_80209B7C(cSetAnimFrame *self);
float fn_80209BC4(cSetAnimFrame *self);
float fn_80209C0C(cSetAnimFrame *self);
float fn_80209C54(cSetAnimFrame *self);
float fn_8007C0AC(void *ev);
void fn_8008059C(void *ev, float frame);
void fn_8046B5A8(void *ev, int x);
char *fn_80209C9C(cDebrisFall *self);
int fn_80209CE4(cDebrisFall *self);
char *fn_80209D2C(cDebrisFall *self);
int fn_80209D74(cDebrisFall *self);
char *fn_80209DBC(cDebrisFall *self);
int fn_80209E04(cDebrisFall *self);
int fn_80209E4C(cDebrisFall *self);
int fn_80209EA4(cDebrisFall *self);
char *fn_80209EEC(cDebrisFall *self);
float fn_80209F34(cDebrisFall *self);
unsigned int fn_8042EFF8(void *g);
extern char lbl_80593BE8[];
extern unsigned int lbl_8066C720; // next time debris may fall
int strcmp(const char *a, const char *b);
void fn_800810DC(void *ev, float f, int a, int b, int c, int d);
int fn_80209FD0(cVehicleBreak *self);
unsigned int fn_8020A014(cVehicleBreak *self);
int fn_8020A05C(cVehicleBreak *self);
float fn_8020A0B4(cVehicleBreak *self);
float fn_8020A0FC(cVehicleBreak *self);
char *fn_8020A144(cVehicleBreak *self);
int fn_802031DC(cVehicleBreak *self, int a);
void fn_80202DDC(cVehicleBreak *self);
void fn_80202F38(cVehicleBreak *self);
void fn_8020311C(cVehicleBreak *self);
SObj *fn_80080300P(void *ev) __asm__("fn_80080300");
SWorld *fn_8043289C(void *g);
extern char lbl_80552110[]; // the game-state object
int fn_801B90A8(void *a, void *b, void *c);
int fn_8020A1E0(cVehicleBarrier *self);
unsigned int fn_8020A228(cVehicleBarrier *self);
unsigned int fn_8020A270(cVehicleBarrier *self);
unsigned int fn_8020A2B8(cVehicleBarrier *self);
unsigned int fn_8020A300(cVehicleBarrier *self);
void fn_802037B0(cVehicleBarrier *self);
void fn_80082124(void *ev);
int fn_8020A39C(cGenBreakProp *self);
int fn_8020A3F4(cGenBreakProp *self);
char *fn_8020A44C(cGenBreakProp *self);
unsigned int fn_8020A494(cGenBreakProp *self);
unsigned int fn_8020A4DC(cGenBreakProp *self);
unsigned int fn_8020A524(cGenBreakProp *self);
unsigned int fn_8020A56C(cGenBreakProp *self);
unsigned int fn_8020A5B4(cGenBreakProp *self);
unsigned int fn_8020A5FC(cGenBreakProp *self);
int fn_8020A644(cGenBreakProp *self);
float fn_8020A68C(cGenBreakProp *self);
char *fn_8020A6D4(cGenBreakProp *self);
int fn_8020A71C(cGenBreakProp *self);
void fn_8046CE70(void *ev, int h);
int fn_80080BA8(void *ev);
SActor *fn_80080BA8S(void *ev) __asm__("fn_80080BA8");
int fn_8009AC94R(SObj &a) __asm__("fn_8009AC94");
float fn_8020A7C8(cDamagePropOnTrigger *self);
float fn_8020A810(cDamagePropOnTrigger *self);
float fn_8020A858(cDamagePropOnTrigger *self);
unsigned int fn_8020A8A0(cDamagePropOnTrigger *self);
unsigned int fn_8020A8E8(cDamagePropOnTrigger *self);
unsigned int fn_8020A930(cDamagePropOnTrigger *self);
unsigned int fn_8020A978(cDamagePropOnTrigger *self);
unsigned int fn_8020A9C0(cDamagePropOnTrigger *self);
unsigned int fn_8020AA08(cDamagePropOnTrigger *self);
unsigned int fn_8020AA50(cDamagePropOnTrigger *self);
unsigned int fn_8020AA98(cDamagePropOnTrigger *self);
int fn_8020AAE0(cDamagePropOnTrigger *self);
unsigned int fn_80204560(cDamagePropOnTrigger *self);
int fn_8020486C(cDamagePropOnTrigger *self);
int fn_8020AB8C(cPortalControl *self);
unsigned int fn_8020ABE4(cPortalControl *self);
unsigned int fn_8020AC2C(cPortalControl *self);
unsigned int fn_8020AC74(cPortalControl *self);
unsigned int fn_8020ACBC(cPortalControl *self);
unsigned int fn_8020AD04(cPortalControl *self);
unsigned int fn_8020AD4C(cPortalControl *self);
unsigned int fn_8020AD94(cPortalControl *self);
unsigned int fn_8020ADDC(cPortalControl *self);
int fn_8020AE24(cPortalControl *self);
void fn_80204B1C(cPortalControl *self, int on);
void fn_80083B74(int owner, int h, int on);
float fn_8020AED0(cPropRespawn *self);
char *fn_8020AF18(cPropRespawn *self);
int fn_8020AF60(cPropRespawn *self);
int fn_8020AFB8(cPropRespawn *self);
int fn_8020B010(cPropRespawn *self);
int fn_80205B98(cPropRespawn *self, int force);
SActor *fn_80080EFCS(void *ev) __asm__("fn_80080EFC");
int fn_800B1138R(SObj &a) __asm__("fn_800B1138");
float fn_800A4080(int actor);
void fn_800806E0(void *ev, char *name, int a, float f, float g, float h, int b);
void fn_8006645CR(SObj &a, int b) __asm__("fn_8006645C");
void fn_80066DC4R(SObj &a, Vector *v, int b, int c, int d) __asm__("fn_80066DC4");
void fn_80066794R(SObj &a, int on) __asm__("fn_80066794");
extern char lbl_8052F060[];
SObjList &fn_80430050(void *w);
SObj *fn_800B1AC4(SObj *o);
int fn_800B13D8(SObj *o);
int fn_8009AC94P(SObj *o) __asm__("fn_8009AC94");
int fn_800B0CC0(SObj *o);
void *fn_800B1478(SObj *o);
int fn_800A46E8(void *b);
int fn_800489BC(Placement *p);
unsigned int fn_8020B0BC(cRemoveObjects *self);
unsigned int fn_8020B104(cRemoveObjects *self);
unsigned int fn_8020B14C(cRemoveObjects *self);
unsigned int fn_8020B194(cRemoveObjects *self);
unsigned int fn_8020B1DC(cRemoveObjects *self);
unsigned int fn_8020B224(cRemoveObjects *self);
unsigned int fn_8020B26C(cRemoveObjects *self);
int fn_8020B2B4(cRemoveObjects *self);
int fn_8020B2FC(cRemoveObjects *self);
void fn_802061C8(cRemoveObjects *self);
unsigned int fn_8020B398(cCrystalBreak *self);
int fn_8020B3DC(cCrystalBreak *self);
float fn_8020B434(cCrystalBreak *self);
int fn_80393D0C(SObj *o, char *name, int a, int b);
unsigned int fn_8009AC94U(SObj *o) __asm__("fn_8009AC94");
void fn_80083D08(int a, int b, int c, float x, float y, float z, float w);
void fn_80083230(void *ev, char *name);
int fn_8020B524(cCameraMPToggle *self);
void fn_8046B838(void *g, int on);
unsigned int fn_8020B5D0(cLabConsole *self);
unsigned int fn_8020B618(cLabConsole *self);
unsigned int fn_8020B660(cLabConsole *self);
void fn_80206E18(cLabConsole *self);
int fn_8020B6FC(cWieldableToggle *self);
int fn_8020B754(cWieldableToggle *self);
void fn_80080FF4(void *ev, int a);
void fn_80080F74(void *ev, int a);
int fn_8020B7F0(cReverseWallRenderToggle *self);
int fn_8046C160(void *ev);
void fn_8046C1E8(void *ev, int x);
int fn_80081338(void *ev);
void fn_800813AC(void *ev, int on);
unsigned int fn_8020B89C(cPropGroupFade *self);
unsigned int fn_8020B8E4(cPropGroupFade *self);
unsigned int fn_8020B92C(cPropGroupFade *self);
unsigned int fn_8020B974(cPropGroupFade *self);
unsigned int fn_8020B9BC(cPropGroupFade *self);
unsigned int fn_8020BA04(cPropGroupFade *self);
unsigned int fn_8020BA4C(cPropGroupFade *self);
unsigned int fn_8020BA94(cPropGroupFade *self);
unsigned int fn_8020BADC(cPropGroupFade *self);
unsigned int fn_8020BB24(cPropGroupFade *self);
void fn_8008065C(void *ev, int a);
int fn_8020BBC0(cMP_MatchTrigger *self);
int fn_8020BC08(cMP_MatchTrigger *self);
void fn_80207600(cMP_MatchTrigger *self);
unsigned int fn_8020BC50(cMP_MatchTrigger *self);
int fn_8020BC98(cMP_MatchTrigger *self);
unsigned int fn_8020BCE0(cMP_MatchTrigger *self);
int fn_8020BD28(cMP_MatchTrigger *self);
unsigned int fn_8020BD70(cMP_MatchTrigger *self);
int fn_8020BDB8(cMP_MatchTrigger *self);
unsigned int fn_8020BE00(cMP_MatchTrigger *self);
int fn_8020BE48(cMP_MatchTrigger *self);
unsigned int fn_8020BE90(cMP_MatchTrigger *self);
int fn_8020BED8(cMP_MatchTrigger *self);
unsigned int fn_8020BF20(cMP_MatchTrigger *self);
int fn_8020BF68(cMP_MatchTrigger *self);
unsigned int fn_8020BFB0(cMP_MatchTrigger *self);
int fn_8020BFF8(cMP_MatchTrigger *self);
unsigned int fn_8020C040(cMP_MatchTrigger *self);
int fn_8020C088(cMP_MatchTrigger *self);
unsigned int fn_8020C0D0(cMP_MatchTrigger *self);
int fn_8020C118(cMP_MatchTrigger *self);
unsigned int fn_8020C160(cMP_MatchTrigger *self);
int fn_8020C1A8(cMP_MatchTrigger *self);
float fn_8020C244(cCameraSet *self);
void fn_8007C830(float f);
unsigned int fn_800791C8(cScript *self, unsigned int i);
int fn_80079068(cScript *self, unsigned int i);
float fn_8007935C(cScript *self, unsigned int i);
char *fn_800794FC(cScript *self, unsigned int i);
int fn_80048DD0(SBody *body, Vector *pos, int a, int b, int c, float f, Placement *out);
void fn_80080928(void *ev, int a);
void fn_80082F30(void *ev);
void fn_80082FA4(void *ev);
int fn_80081074(void *ev);
int fn_8046C8FC(void *ev);
void fn_800A46A0(int actor, int a);
int fn_80114950(int h, int id);
void fn_80082440(void *ev, Vector *out);
void fn_800838E0(Vector *at);
void fn_800836A8(void *ev, char *name);
void fn_80083620(void *ev, char *name);
void fn_80114D70(int sound, int volume);
int fn_8043E450(void *a, int b);
int fn_800B2054(int a);
SBody *fn_800B24AC(SObj *o);
HkRef fn_80317960(SBodyBase &body);
void fn_80318F1C(SBodyBase *body, const HkVec &a, const HkVec &b);
void fn_80428FA8(Vector *v, float x, float y, float z);
void fn_8006645C(void *o, int a);
void fn_80065CB0(SObj *o, Vector *v);
void fn_8042F76C(Vector *v);
void fn_80435530(Vector *v, float f);
void fn_800A2B3C(int actor, int a, int b, int c, int d);
int fn_8007D7C4(cScript *self, unsigned char kind);
void fn_8046B710(Ref8 *self, int value);
void fn_80082AFC(void *ev, int h, int owner, int kind, float a, float b, float c, float d);
void fn_801FD8D8(cObjectSetCollision *self);

cScript *fn_801FCEBC(register cObjectExplosion *self)
{
    return new cObjectExplosion;
}

void fn_801FCF10(register cObjectExplosion *self) // slot 4
{
    if (!fn_80207C44(self))
        fn_8007D404(self, fn_80207BB4(self) + fn_80171F8C() * 4.656612873077392578125e-10f * fn_80207BFC(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801FCFE8(register cObjectExplosion *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    char ev[8];
    fn_8046B6C8(ev, fn_800797D4(self));
    switch (kind) {
    case 10:
        if (fn_80207C8C(self))
            fn_80082190(ev, fn_80207C8C(self));
        else
            fn_80082190(ev, "exp_large");
        fn_8007D404(self, fn_80207BB4(self) + fn_80171F8C() * 4.656612873077392578125e-10f * fn_80207BFC(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
}

void fn_801FD14C(register cObjectExplosion *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    char ev[8];
    fn_8046B6C8(ev, fn_800797D4(self));
    if (fn_80207C8C(self))
        fn_80082190(ev, fn_80207C8C(self));
    else
        fn_80082190(ev, "exp_large");
}

void fn_801FD208(register cObjectExplosion *self) // slot 7
{
    char ev[8];

    fn_8046B6C8(ev, fn_800797D4(self));
    fn_80082190(ev, "exp_large");
}

inline int sn_return_decl2(int a) { return a; }

cScript *fn_801FD268(register cObjectSetCollision *self)
{
    return new cObjectSetCollision;
}

void fn_801FD2BC(register cObjectSetCollision *self) // slot 3
{
    self->unk30 = 0;
    self->on = 1;
    self->unk2C = 0;
    self->count = 0;
}

void fn_801FD2FC(register cObjectSetCollision *self) // slot 5
{
    char ev[8];
    int flags;

    fn_8046B6C8(ev, fn_800797D4(self));
    flags = fn_80081F28(ev);
    if (flags & 2)
        self->unk30 = 1;
    if (self->unk2C && !self->on)
        fn_801FD8D8(self);
    if (!fn_80207D1C(self))
        fn_801FD8D8(self);
    fn_8007D404(self, fn_80207D64(self), 5, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801FD3E8(register cObjectSetCollision *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    char ev[8];
    fn_8046B6C8(ev, fn_800797D4(self));
    switch (kind) {
    case 2:
        self->count++;
        if (self->count > 1)
            return;
        fn_801FD8D8(self);
        break;
    case 3:
        if (self->count > 0)
            self->count--;
        if (self->count > 0)
            return;
        fn_801FD788(self);
        break;
    case 0:
    case 4:
        if (!self->on)
            fn_801FD788(self);
        else if (fn_80081E6C(ev) && (!strnicmp(fn_80081E6C(ev)->name, "prp_rl_energywall_stand", 0x17) || !strnicmp(fn_80081E6C(ev)->name, "prp_rl_forcefield", 0x11))) {
            fn_80066794(fn_80081E6C(ev), 1);
            fn_8007D404(self, 0.1f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        } else
            fn_801FD8D8(self);
        break;
    case 7:
        fn_801FD8D8(self);
        break;
    case 999:
        if (!self->on)
            fn_801FD788(self);
        else
            fn_801FD8D8(self);
        break;
        break;
    }
}

void fn_801FD63C(register cObjectSetCollision *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 5:
        if (!fn_80207CD4(self)) {
            if (fn_80207D1C(self))
                fn_8007D404(self, fn_80207DAC(self), 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            else
                fn_8007D404(self, fn_80207DF4(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
        break;
    case 20:
        fn_801FD8D8(self);
        break;
    case 10:
        fn_801FD788(self);
        break;
    }
}

void fn_801FD788(register cObjectSetCollision *self)
{
    char ev[8];

    fn_8046B680(ev, fn_800797D4(self));
    if (!fn_8009AD80(fn_80080300(ev)))
        return;
    fn_800820A0(ev, 1);
    if (fn_80207E3C(self) && !self->on)
        fn_80082E90(ev, "nrgWallOn", 0xff, 0xff);
    else if (!self->unk30)
        fn_80082014(ev, 2);
    self->on = 1;
    if (fn_80207DAC(self) == 0.0f)
        return;
    if (!fn_80207CD4(self))
        fn_8007D404(self, fn_80207DAC(self), 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801FD8D8(register cObjectSetCollision *self)
{
    char ev[8];

    fn_8046B680(ev, fn_800797D4(self));
    if (!fn_8009AD80(fn_80080300(ev)))
        return;
    fn_800820A0(ev, 0);
    if (fn_80207E3C(self) && self->on) {
        fn_80082E90(ev, "nrgWallOff", 0xff, 0xff);
        fn_80114CC0(fn_804425F8(ev));
    } else
        fn_80081F8C(ev, 2);
    self->on = 0;
    if (fn_80207DF4(self) == 0.0f)
        return;
    if (!fn_80207CD4(self))
        fn_8007D404(self, fn_80207DF4(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

inline int sn_return_decl3(int a) { return a; }

cScript *fn_801FDA30(register cTriggerRelay *self)
{
    return new cTriggerRelay;
}

void fn_801FDA84(register cTriggerRelay *self) // slot 3
{
    self->unk28 = self->unk2C = self->unk30 = self->unk34 = 0.0f;
}

#define RELAY_QUEUE(on, delay, i) \
    if (on(self))                 \
        fn_8007D404(self, delay(self), 0, 0.0f, 0.0f, 0.0f, 0.0f, i);

void fn_801FDABC(register cTriggerRelay *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    RELAY_QUEUE(fn_80208F64, fn_80208FAC, 1)
    RELAY_QUEUE(fn_8020903C, fn_80209084, 2)
    RELAY_QUEUE(fn_80209114, fn_8020915C, 3)
    RELAY_QUEUE(fn_802091EC, fn_80209234, 4)
    RELAY_QUEUE(fn_802092C4, fn_8020930C, 5)
    RELAY_QUEUE(fn_8020939C, fn_802093E4, 6)
    RELAY_QUEUE(fn_80209474, fn_802094BC, 7)
    RELAY_QUEUE(fn_8020954C, fn_80209594, 8)
    RELAY_QUEUE(fn_80209624, fn_8020966C, 9)
    RELAY_QUEUE(fn_802096FC, fn_80209744, 10)
    RELAY_QUEUE(fn_802097D4, fn_8020981C, 11)
    RELAY_QUEUE(fn_802098AC, fn_802098F4, 12)
    if (stricmp("", fn_802099CC(self)))
        fn_8007D404(self, fn_80209A14(self), 0, 0.0f, 0.0f, 0.0f, 0.0f, 13);
}

#define RELAY_SEND(i, out, vec)                                                                       \
    case i:                                                                                           \
        fn_8046B710((Ref8 *)ev, out(self));                                                           \
        fn_80082AFC(ev, out(self), fn_800797D4(self), fn_80209984(self), fn_8008379C(vec(self), 0),   \
                    fn_8008379C(vec(self), 1), fn_8008379C(vec(self), 2), fn_8008379C(vec(self), 3)); \
        break;

void fn_801FDF64(register cTriggerRelay *self, unsigned char kind, float a, float b, float c, float d, unsigned int e) // slot 8
{
    char ev[8];
    fn_8046B680(ev, 0);
    switch (e) {
    RELAY_SEND(1, fn_80208F64, fn_80208FF4)
    RELAY_SEND(2, fn_8020903C, fn_802090CC)
    RELAY_SEND(3, fn_80209114, fn_802091A4)
    RELAY_SEND(4, fn_802091EC, fn_8020927C)
    RELAY_SEND(5, fn_802092C4, fn_80209354)
    RELAY_SEND(6, fn_8020939C, fn_8020942C)
    RELAY_SEND(7, fn_80209474, fn_80209504)
    RELAY_SEND(8, fn_8020954C, fn_802095DC)
    RELAY_SEND(9, fn_80209624, fn_802096B4)
    RELAY_SEND(10, fn_802096FC, fn_8020978C)
    RELAY_SEND(11, fn_802097D4, fn_80209864)
    RELAY_SEND(12, fn_802098AC, fn_8020993C)
    case 13:
        fn_8046B710((Ref8 *)ev, fn_80083734(fn_802099CC(self)));
        fn_80082AFC(ev, fn_804425F8(ev), fn_800797D4(self), fn_80209984(self), 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    }
}

inline int sn_return_decl4(int a) { return a; }

cScript *fn_801FEB48(register cObjectMove *self)
{
    return new cObjectMove;
}

void fn_801FEB9C(register cObjectMove *self) // slot 3
{
    self->busy = 0;
    self->stop = 0;
    self->node = 0;
    self->unk28 = 0;
}

void fn_801FEBDC(register cObjectMove *self) // slot 4
{
    self->node = fn_80207E94(self);
    if (!fn_80208050(self)) {
        if (!fn_802081C4(self))
            fn_801FF210(self, 0);
    } else
        fn_8007D404(self, fn_80207EDC(self) + 1.0f, 0, (float)self->node, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801FECC0(register cObjectMove *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (self->busy)
        return;
    self->busy = 1;
    switch (kind) {
    case 0:
        fn_801FF2D4(self, fn_80207E94(self));
        break;
    case 1:
        self->stop = 1;
        fn_801FF2D4(self, (int)x);
        break;
    }
}

void fn_801FED90(register cObjectMove *self, int h, int node, int value) // slot 25
{
    if (node == fn_802081C4(self))
        fn_801FF210(self, 0);
    char ev[8];
    fn_8046B6C8(ev, fn_800797D4(self));
    if (h == fn_804425F8(ev)) {
        if (node == fn_80081E6C(ev)->unk144 - 1)
            self->node = 0;
        else if (node == 0)
            self->node = fn_80207E94(self);
        else
            self->node = node + 1;
        if (self->stop) {
            self->stop = 0;
            self->busy = 0;
            return;
        }
        fn_8007D404(self, fn_80207F6C(self), 0, (float)self->node, 0.0f, 0.0f, 0.0f, 0);
    }
}

void fn_801FEF0C(register cObjectMove *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    fn_801FF2D4(self, (int)a);
}

void fn_801FEF80(register cObjectMove *self, int h, int other, int value) // slot 14
{
    fn_801FEFF4(self, other, 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

#define MOVE_SEND(get)                                                         \
    if (get(self)) {                                                           \
        fn_8046B710((Ref8 *)ev, get(self));                                    \
        fn_80082AFC(ev, h, fn_800797D4(self), kind, x, 0.0f, 0.0f, 0.0f);      \
    }

void fn_801FEFF4(register cObjectMove *self, int h, int kind, float x, float y, float z, float w)
{
    char ev[8];
    fn_8046B530(ev);
    MOVE_SEND(fn_802080A4)
    MOVE_SEND(fn_802080EC)
    MOVE_SEND(fn_80208134)
    MOVE_SEND(fn_8020817C)
}

void fn_801FF210(register cObjectMove *self, int on)
{
    char ev[8];
    fn_8046B6C8(ev, fn_800797D4(self));
    if (on)
        fn_800A90F4(fn_800B1CC8(fn_80081E6C(ev)));
    else
        fn_800A916C(fn_800B1CC8(fn_80081E6C(ev)));
    self->unk28 = !on;
}

void fn_801FF2D4(register cObjectMove *self, int node)
{
    char ev[8];
    fn_8046B6C8(ev, fn_800797D4(self));
    if (!self->node && !fn_80207FB4(self))
        self->stop = 1;
    if (self->unk28)
        fn_801FF210(self, 1);
    self->node = node;
    fn_80082A44(ev, self->node, fn_80207F24(self), fn_80207FFC(self));
}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x804A1804-0x804A181C

inline int sn_return_decl5(int a) { return a; }

cScript *fn_801FF3AC(register cObjectRumbleShake *self)
{
    return new cObjectRumbleShake;
}

void fn_801FF400(register cObjectRumbleShake *self) // slot 4
{
    self->strength = fn_80208424(self);
    self->rumble = fn_8020820C(self);
    self->shake = fn_80208384(self);
    if (self->rumble || self->shake)
        fn_8007D404(self, fn_801FFA14(self), 0, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801FF4BC(register cObjectRumbleShake *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    char ev[8];
    fn_8046B6C8(ev, fn_800797D4(self));
    SObj *obj = fn_80081E6C(ev);
    char player[8];
    fn_8046B638(player, fn_80080B34());
    Vector delta;
    fn_80429038(&delta, fn_800B1724(obj), fn_800B1724R(*fn_8007C034S(player)));
    if (fn_80434040(&delta) > fn_802084FC(self))
        fn_8007D404(self, fn_801FFA14(self), 0, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    else {
        if (self->rumble)
            fn_801FF7E4(self);
        if (self->shake)
            fn_801FF970(self);
        fn_8007D404(self, fn_801FFA14(self), 0, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
}

void fn_801FF670(register cObjectRumbleShake *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (y > 0.0f)
        self->strength = y;
    switch (kind) {
    case 7:
        fn_8007D8B0(self);
        return;
        break;
    case 8:
        fn_801FF7E4(self);
        break;
    case 9:
        self->rumble = 1;
        break;
    case 10:
        fn_801FF970(self);
        break;
    case 11:
        self->shake = 1;
        break;
    case 0:
        fn_801FF7E4(self);
        fn_801FF970(self);
        break;
    case 4:
        self->rumble = 1;
        self->shake = 1;
        fn_8007D404(self, fn_801FFA14(self), 0, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
}

void fn_801FF7E4(register cObjectRumbleShake *self)
{
    if (fn_8020833C(self) == -1)
        fn_80083DE0(fn_80208264(self), fn_802082AC(self), (unsigned int)(fn_802082F4(self) * 1000.0f), 0);
    else {
        int pad = fn_80080ABC();
        fn_80083D78(fn_80208264(self), fn_802082AC(self), (unsigned int)(fn_802082F4(self) * 1000.0f), 0, pad);
    }
}

void fn_801FF970(register cObjectRumbleShake *self)
{
    fn_80083EE8((unsigned int)(fn_802083DC(self) * 1000.0f), self->strength, 1);
}

float fn_801FFA14(register cObjectRumbleShake *self)
{
    return fn_8020846C(self) + fn_80171F8C() * 4.656612873077392578125e-10f * fn_802084B4(self);
}

inline int sn_return_decl6(int a) { return a; }

cScript *fn_801FFAB4(register cTimerTrigger *self)
{
    return new cTimerTrigger;
}

void fn_801FFB08(register cTimerTrigger *self) // slot 3
{
    self->running = 0;
}

void fn_801FFB30(register cTimerTrigger *self) // slot 4
{
    if (!fn_8020885C(self)) {
        self->running = 1;
        fn_8007D404(self, fn_80208544(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
}

void fn_801FFBBC(register cTimerTrigger *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_801FFDA0(self);
        if (fn_8020858C(self) != 0.0f)
            fn_8007D404(self, fn_8020858C(self), 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 20:
        fn_801FFDA0(self);
        fn_8007D404(self, fn_80208544(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
}

void fn_801FFCE0(register cTimerTrigger *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (!self->running) {
        self->running = 1;
        fn_8007D404(self, fn_80208544(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    } else {
        self->running = 0;
        fn_8007D8B0(self);
    }
}

#define TIMER_SEND(get)                                                                       \
    if (get(self)) {                                                                          \
        fn_8046B710((Ref8 *)ev, get(self));                                                   \
        fn_80082AFC(ev, get(self), fn_800797D4(self), fn_802085D4(self), 0.0f, 0.0f, 0.0f, 0.0f); \
    }

void fn_801FFDA0(register cTimerTrigger *self)
{
    char ev[8];

    fn_8046B530(ev);
    TIMER_SEND(fn_8020861C)
    TIMER_SEND(fn_80208664)
    TIMER_SEND(fn_802086AC)
    TIMER_SEND(fn_802086F4)
    TIMER_SEND(fn_8020873C)
    TIMER_SEND(fn_80208784)
    TIMER_SEND(fn_802087CC)
    TIMER_SEND(fn_80208814)
}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x804A1864-0x804A1890

inline int sn_return_decl7(int a) { return a; }

cScript *fn_80200200(register cTriggerOnAction *self)
{
    return new cTriggerOnAction;
}

void fn_80200254(register cTriggerOnAction *self) // slot 3
{
    self->hit[0] = 0;
    self->hit[1] = 0;
    self->hit[2] = 0;
    self->hit[3] = 0;
    self->linked[0] = 0;
    self->linked[1] = 0;
    self->linked[2] = 0;
    self->linked[3] = 0;
    self->handles[0] = 0;
    self->handles[1] = 0;
    self->handles[2] = 0;
    self->handles[3] = 0;
    self->alt[0] = 0;
    self->alt[1] = 0;
    self->alt[2] = 0;
    self->alt[3] = 0;
    self->fired = 0;
    self->count = 0;
    self->armed = 1;
    self->done = 0;
}

void fn_80200314(register cTriggerOnAction *self) // slot 4
{
    if (fn_80208ED4(self) > 0.0)
        fn_8007D404(self, 0.5f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    if (!fn_8007CF00(self, fn_80208AE4(self), 0))
        self->hit[0] = 1;
    if (!fn_8007CF00(self, fn_80208B2C(self), 0))
        self->hit[1] = 1;
    if (!fn_8007CF00(self, fn_80208B74(self), 0))
        self->hit[2] = 1;
    if (!fn_8007CF00(self, fn_80208BBC(self), 0))
        self->hit[3] = 1;
    if (fn_80201558(self, fn_80208AE4(self))) {
        self->handles[0] = fn_80208AE4(self);
        self->linked[0] = 1;
        fn_8007D070(self, fn_80208AE4(self));
    }
    if (fn_80201558(self, fn_80208B2C(self))) {
        self->handles[1] = fn_80208B2C(self);
        self->linked[1] = 1;
        fn_8007D070(self, fn_80208B2C(self));
    }
    if (fn_80201558(self, fn_80208B74(self))) {
        self->handles[2] = fn_80208B74(self);
        self->linked[2] = 1;
        fn_8007D070(self, fn_80208B74(self));
    }
    if (fn_80201558(self, fn_80208BBC(self))) {
        self->handles[3] = fn_80208BBC(self);
        self->linked[3] = 1;
        fn_8007D070(self, fn_80208BBC(self));
    }
    if (fn_80208E8C(self)) {
        char ev[8];
        fn_8046B6C8(ev, fn_800797D4(self));
        fn_80082AFC(ev, fn_800797D4(self), fn_800797D4(self), fn_80208E44(self), fn_80208C4C(self), 0.0f, 0.0f, 0.0f);
    }
}

void fn_80200638(register cTriggerOnAction *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_802012CC(self);
        break;
    case 20: {
        char player[8];
        fn_8046B638(player, fn_80080B34());
        if (fn_800809CC(player) && fn_80086730(fn_800B14A0R(*fn_800809CCS(player))) < fn_80208ED4(self))
            fn_8020105C(self, 0);
        else
            fn_8007D404(self, 0.5f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
    case 30: {
        char ev[8];
        fn_8046B5F0(ev, e);
        int actor = fn_80080EFC(ev);
        if (actor)
            fn_800A3588(actor, 0, 9999.0f, 0, 0, 0.0f);
        break;
    }
    }
}

void fn_802007E0(register cTriggerOnAction *self, int h, int other, int a, int b, float dmg, int value) // slot 22
{
    if (!fn_80208934(self))
        return;
    if (!self->fired)
        fn_8020105C(self, h);
}

float fn_80200860(register cTriggerOnAction *self, int h, int other, int a, int b, float dmg, int c, int value) // slot 21
{
    if (self->fired)
        return 0.0f;
    char ev[8];
    fn_8046D4F8(ev, h);
    if (!fn_80081E6C(ev))
        return dmg;
    if (!self->fired && fn_80208934(self) == 2 && fn_800A4054(fn_800B1540(fn_80081E6C(ev))) < 10.0f) {
        self->fired = 1;
        fn_8020105C(self, h);
        fn_8007D404(self, 2.0f, 30, 0.0f, 0.0f, 0.0f, 0.0f, h);
        return 0.0f;
    }
    if (!fn_8020897C(self))
        return dmg;
    fn_8020105C(self, h);
    return dmg;
}

int fn_802009E0(register cTriggerOnAction *self, int h, int other, int value) // slot 17
{
    if (!fn_802089C4(self))
        return 0;
    fn_8020105C(self, h);
    return 0;
}

void fn_80200A4C(register cTriggerOnAction *self, int h, int other, int value) // slot 14
{
    if (!fn_80208A0C(self))
        return;
    fn_8020105C(self, h);
}

void fn_80200AAC(register cTriggerOnAction *self, int h, int other, int value) // slot 15
{
    if (!fn_80208A54(self))
        return;
    fn_8020105C(self, h);
}

void fn_80200B0C(register cTriggerOnAction *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 7:
        if (a == fn_800797D4(self))
            self->armed = 0;
        break;
    case 0:
        if (!self->armed)
            return;
        if (!fn_80208A9C(self))
            return;
        self->count++;
        if (self->count == fn_80208A9C(self))
            fn_8020105C(self, b);
        break;
    }
}

void fn_80200BFC(register cTriggerOnAction *self, int a, int b, int c, float x, float y, float z, float w) // slot 24
{
    if (!(self->linked[0] || self->linked[1] || self->linked[2] || self->linked[3]))
        return;
    if (!(unsigned int)y)
        return;
    if (self->handles[0] == (unsigned int)y) {
        self->alt[0] = (unsigned int)x;
        fn_8007CF00(self, self->alt[0], 0);
    }
    else if (self->handles[1] == (unsigned int)y) {
        self->alt[1] = (unsigned int)x;
        fn_8007CF00(self, self->alt[1], 0);
    }
    else if (self->handles[2] == (unsigned int)y) {
        self->alt[2] = (unsigned int)x;
        fn_8007CF00(self, self->alt[2], 0);
    }
    else if (self->handles[3] == (unsigned int)y) {
        self->alt[3] = (unsigned int)x;
        fn_8007CF00(self, self->alt[3], 0);
    }
}

void fn_80200FF4(register cTriggerOnAction *self, int h, int other, int value) // slot 18
{
    if (!fn_80208F1C(self))
        return;
    fn_8020105C(self, h);
}

void fn_8020105C(register cTriggerOnAction *self, int h)
{
    if (fn_802088A4(self) && self->done || !self->armed)
        return;
    if (fn_802088A4(self)) {
        if (h == fn_80208AE4(self) || h == self->alt[0])
            self->hit[0] = 1;
        else if (h == fn_80208B2C(self) || h == self->alt[1])
            self->hit[1] = 1;
        else if (h == fn_80208B74(self) || h == self->alt[2])
            self->hit[2] = 1;
        else if (h == fn_80208BBC(self) || h == self->alt[3])
            self->hit[3] = 1;
        if (self->hit[0] && self->hit[1] && self->hit[2] && self->hit[3]) {
            if (fn_802088EC(self) != 0.0f)
                fn_8007D404(self, fn_802088EC(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            else
                fn_802012CC(self);
            self->done = 1;
        }
    } else {
        if (fn_802088EC(self) != 0.0f)
            fn_8007D404(self, fn_802088EC(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        else
            fn_802012CC(self);
    }
}

#define ACTION_SEND(ev, get, value)                                                                         \
    if (get(self))                                                                                          \
        fn_80082AFC(ev, fn_804425F8(ev), fn_800797D4(self), fn_80208E44(self), value(self), 0.0f, 0.0f, 0.0f);

void fn_802012CC(register cTriggerOnAction *self)
{
    char e0[8];
    char e1[8];
    char e2[8];
    char e3[8];

    fn_8046B6C8(e0, fn_80208C04(self));
    fn_8046B6C8(e1, fn_80208C94(self));
    fn_8046B6C8(e2, fn_80208D24(self));
    fn_8046B6C8(e3, fn_80208DB4(self));
    ACTION_SEND(e0, fn_80208C04, fn_80208C4C)
    ACTION_SEND(e1, fn_80208C94, fn_80208CDC)
    ACTION_SEND(e2, fn_80208D24, fn_80208D6C)
    ACTION_SEND(e3, fn_80208DB4, fn_80208DFC)
}

int fn_80201558(register cTriggerOnAction *self, int h)
{
    char ev[8];
    fn_8046B6C8(ev, h);
    if (!fn_80081E6C(ev))
        return 0;
    if (!strnicmp(fn_80081E6C(ev)->name, "brk_rkcrystal", 0xd))
        return 1;
    else
        return 0;
}

inline int sn_return_decl8(int a) { return a; }

cScript *fn_8020160C(register cSetAnimFrame *self)
{
    return new cSetAnimFrame;
}

void fn_80201660(register cSetAnimFrame *self) // slot 4
{
    char ev[8];

    fn_8046B5A8(ev, fn_800797D4(self));
    self->health = fn_8007C0AC(ev);
}

void fn_802016B8(register cSetAnimFrame *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    char ev[8];
    fn_8046B5A8(ev, fn_800797D4(self));
    fn_8008059C(ev, x);
}

float fn_80201734(register cSetAnimFrame *self, int h, int other, int a, int b, float dmg, int c, int value) // slot 21
{
    char ev[8];
    fn_8046B5A8(ev, fn_800797D4(self));
    if (fn_8007C0AC(ev) < fn_80209C54(self))
        fn_8008059C(ev, fn_80209C0C(self));
    else if (fn_8007C0AC(ev) < fn_80209BC4(self))
        fn_8008059C(ev, fn_80209B7C(self));
    else if (fn_8007C0AC(ev) < fn_80209B34(self))
        fn_8008059C(ev, fn_80209AEC(self));
    else if (fn_8007C0AC(ev) < fn_80209AA4(self))
        fn_8008059C(ev, fn_80209A5C(self));
    return dmg;
}

inline int sn_return_decl9(int a) { return a; }

cScript *fn_802018BC(register cDebrisFall *self)
{
    return new cDebrisFall;
}

void fn_80201910(register cDebrisFall *self) // slot 3
{
    self->count17 = 0;
    self->count18 = 0;
    self->count19 = 0;
}

#define DEBRIS_COUNT(n, count, max)     \
    case n:                             \
        if (max(self) > 0) {            \
            self->count++;              \
            if (self->count > max(self)) \
                return;                 \
        }                               \
        break;

void fn_80201948(register cDebrisFall *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (fn_8042EFF8(lbl_80593BE8) < lbl_8066C720)
        return;
    lbl_8066C720 = fn_8042EFF8(lbl_80593BE8) + 2000;
    if (!fn_80209E4C(self)) {
        int n;
        int i;
        n = 2.0f * (fn_80171F8C() * 4.656612873077392578125e-10f) + 3.0f;
        for (i = 0; i < n; i++)
            fn_8007D404(self, fn_80171F8C() * 4.656612873077392578125e-10f + 0.5f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    } else {
        switch (kind) {
        DEBRIS_COUNT(17, count17, fn_80209CE4)
        DEBRIS_COUNT(18, count18, fn_80209D74)
        DEBRIS_COUNT(19, count19, fn_80209E04)
        case 0:
            if (fn_80209EA4(self)) {
                fn_8007D404(self, 0.0f, 5, 0.0f, 0.0f, 0.0f, 0.0f, 0);
                fn_8007D404(self, 1.5f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            } else
                fn_8007D404(self, 0.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            break;
        }
    }
}

#define DEBRIS_DROP(name)                                                 \
    fn_8046B710((Ref8 *)drop, fn_80082190(ev, name(self)));
#define DEBRIS_PUSH()                                                     \
    if (fn_80209F34(self) != 0.0f)                                        \
        fn_800810DC(drop, fn_80209F34(self), 0, 0, 0, 1);

void fn_80201CB0(register cDebrisFall *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    char ev[8];
    fn_8046B6C8(ev, fn_800797D4(self));
    float r = fn_80171F8C() * 4.656612873077392578125e-10f;
    switch (kind) {
    case 5:
        if (strcmp(fn_80209EEC(self), ""))
            fn_80082190(ev, fn_80209EEC(self));
        break;
    case 10: {
        char drop[8];
        fn_8046B5F0(drop, 0);
        if (r < 0.33)
            DEBRIS_DROP(fn_80209C9C)
        if (fn_80209F34(self) != 0.0f)
            fn_800810DC(drop, fn_80209F34(self), 0, 0, 0, 1);
        else if (r < 0.66)
            DEBRIS_DROP(fn_80209D2C)
        if (fn_80209F34(self) != 0.0f)
            fn_800810DC(drop, fn_80209F34(self), 0, 0, 0, 1);
        else
            DEBRIS_DROP(fn_80209DBC)
        DEBRIS_PUSH()
        break;
    }
    case 20: {
        char drop[8];
        fn_8046B5F0(drop, 0);
        switch ((int)a) {
        case 17:
            DEBRIS_DROP(fn_80209C9C)
            DEBRIS_PUSH()
            break;
        case 18:
            DEBRIS_DROP(fn_80209D2C)
            DEBRIS_PUSH()
            break;
        case 19:
            DEBRIS_DROP(fn_80209DBC)
            DEBRIS_PUSH()
            break;
        }
        break;
    }
    }
}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x804A1920-0x804A1938

void fn_8020214C(register cVehicleBreak *self) // slot 3
{
    fn_8046B710(&self->actor, fn_80209FD0(self));
    fn_80080928(&self->actor, 1);
    self->armed = 0;
    self->unk34 = 1;
    self->broken = 0;
    self->unk3C = 0;
    self->sound = 0;
    self->volume = 0;
}

void fn_802021E0(register cVehicleBreak *self) // slot 4
{
    if (fn_8020A05C(self))
        fn_80082F30(&self->actor);
}

void fn_80202238(register cVehicleBreak *self) // slot 31
{
    char ev[8];

    if (fn_8020A05C(self))
        return;
    fn_8046B5F0(ev, fn_800797D4(self));
    if (fn_80081074(ev) && fn_802031DC(self, 1)) {
        char e2[8];
        fn_8046B6C8(e2, fn_800797D4(self));
        if (fn_8046C8FC(e2))
            fn_80082FA4(e2);
    }
}

void fn_8020230C(register cVehicleBreak *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 0:
        if (fn_8020A05C(self))
            fn_80082FA4(&self->actor);
        break;
    case 17:
        fn_80202F38(self);
        break;
    case 18:
        fn_8020311C(self);
        break;
    case 16: {
        char ev[8];
        fn_8046B5F0(ev, fn_800797D4(self));
        fn_800810DC(ev, 10.0f, 0, 0, 0, 0);
        break;
    }
    }
}

float fn_80202418(register cVehicleBreak *self, int h, int other, int a, int b, float dmg, int c, int value) // slot 21
{
    if (!self->armed || self->broken)
        return dmg;
    self->armed = 0;
    if (other == 0 && a == 7)
        return 0.0f;
    if (self->unk34)
        return 0.0f;
    fn_8007D8B0(self);
    fn_8007D404(self, 0.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    return dmg;
}

void fn_8020251C(register cVehicleBreak *self, int h, int a, int b, int c, int d) // slot 29
{
    if (h != fn_804425F8(&self->actor))
        return;
    if (b + 1 == c)
        b = 3;
    switch ((unsigned int)b) {
    case 0:
    case 1: {
        if (self->unk3C)
            return;
        self->unk3C = 1;
        fn_8007D404(self, 1.0f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        fn_8007D404(self, 1.75f, 40, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        fn_8007D404(self, 3.0f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        fn_8007D404(self, 4.25f, 40, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        fn_80082E90(&self->actor, "windscreenSmash", 0x19, 0);
        fn_8007D404(self, 3.5f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        self->armed = 1;
        char ev[8];
        fn_8046B5F0(ev, fn_804425F8(&self->actor));
        fn_800A46A0(fn_80080EFC(ev), 1);
        self->sound = fn_80114950(fn_804425F8(&self->actor), 0x38);
        fn_8007D404(self, 0.0f, 70, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        fn_8007D404(self, 0.5f, 50, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        SObj *o = fn_80081E6C(&self->actor);
        if (o) {
            if (!stricmp("brk_db_watertower", o->name))
                fn_80082E90(&self->actor, "fireOilWrapHuge", 0xff, 0xff);
            else
                fn_80082E90(&self->actor, "fireHuge", 0xff, 0xff);
        }
        break;
    }
    }
}

#define BREAK_EFFECT()                                                                    \
    if (!stricmp("", fn_8020A144(self)) || !stricmp("Invalid Param", fn_8020A144(self)))  \
        fn_80082190(&self->actor, "exp_Car");                                             \
    else                                                                                  \
        fn_80082190(&self->actor, fn_8020A144(self));

void fn_8020285C(register cVehicleBreak *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    Vector pos;
    switch (kind) {
    case 10:
        BREAK_EFFECT()
        fn_80082190(&self->actor, "swav_BigGray");
        fn_80082440(&self->actor, &pos);
        fn_800838E0(&pos);
        fn_80202DDC(self);
        fn_8007D404(self, 1.0f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        fn_8007D7C4(self, 70);
        break;
    case 20:
        BREAK_EFFECT()
        fn_80082440(&self->actor, &pos);
        fn_800838E0(&pos);
        if (fn_8020A0B4(self) > 0.0f)
            fn_80082F30(&self->actor);
        else {
            self->broken = 1;
            char ev[8];
            fn_8046B5F0(ev, fn_800797D4(self));
            fn_800810DC(ev, 50000.0f, 0, 0, 0, 0);
        }
        break;
    case 30:
        fn_800836A8(&self->actor, "headlights");
        break;
    case 40:
        fn_80083620(&self->actor, "headlights");
        break;
    case 50:
        self->unk34 = 0;
        break;
    case 60:
        if (fn_802031DC(self, 0) && fn_8046C8FC(&self->actor))
            fn_80082FA4(&self->actor);
        break;
    case 70:
        if (self->sound <= 0)
            return;
        if (self->volume <= 1000) {
            self->volume += 28;
            fn_80114D70(self->sound, self->volume);
            fn_8007D404(self, 0.1f, 70, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        } else
            fn_80114D70(self->sound, 1000);
        break;
    }
}

int fn_80202C4C(register cVehicleBreak *self, int h, int value) // slot 47
{
    fn_8007D8B0(self);
    if (fn_8020A0B4(self) > 0.0f)
        fn_8007D404(self, fn_8020A0B4(self), 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    self->armed = 0;
    self->unk34 = 1;
    self->unk3C = 0;
    return 1;
}

void fn_80202D10(register cVehicleBreak *self, int h, int a, SHit *hit, int b, int c) // slot 27
{
    if (hit->force < 4.0f)
        return;
    int r = fn_8043E450(hit, b);
    if (r && !fn_800B2054(r))
        return;
    Vector pos;
    fn_80082440(&self->actor, &pos);
    fn_800838E0(&pos);
}

void fn_80202DDC(register cVehicleBreak *self)
{
    SObj *o = fn_80081E6C(&self->actor);
    if (!o || !fn_800B24AC(o) || fn_80317960(*fn_800B24AC(o)).fn_80436294())
        return;
    fn_8006645C(o, 0);
    Vector v;
    if (!fn_8020A014(self))
        fn_80428FA8(&v, 0.0f, 0.0f, 12.0f);
    else
        fn_80428FA8(&v, 0.0f, 0.0f, fn_8020A014(self));
    fn_80065CB0(o, &v);
}

void fn_80202F38(register cVehicleBreak *self)
{
    fn_80082190(&self->actor, "exp_largeFake");
    fn_80082190(&self->actor, "swav_BigGray");
    SObj *o = fn_80081E6C(&self->actor);
    if (!o || !fn_800B24AC(o) || fn_80317960(*fn_800B24AC(o)).fn_80436294())
        return;
    fn_8006645C(o, 0);
    Vector v;
    if ((unsigned int)o->unk144 <= 1)
        fn_80428FA8(&v, 0.0f, 0.0f, 1.0f);
    else
        fn_80429038(&v, &o->path->a, fn_800B1724(o));
    fn_8042F76C(&v);
    fn_80435530(&v, fn_8020A0FC(self));
    if ((unsigned int)o->unk144 > 2)
        fn_80318F1C(fn_800B24AC(o), HkVec(&v), HkVec(&o->path->b));
}

void fn_8020311C(register cVehicleBreak *self)
{
    if (fn_8020A05C(self))
        fn_80082FA4(&self->actor);
    char ev[8];
    fn_8046B5F0(ev, fn_800797D4(self));
    int actor = fn_80080EFC(ev);
    if (!actor)
        return;
    fn_800A2B3C(actor, 1, 0, 0, 0);
    fn_8006645C((void *)actor, 0);
    fn_80066794((void *)actor, 1);
}

int fn_802031DC(register cVehicleBreak *self, int force)
{
    char ev[8];
    fn_8046B680(ev, fn_800797D4(self));
    SObj *o = fn_80080300P(ev);
    if (!o)
        return 0;
    unsigned char seen = fn_801B90A8(fn_8043289C(lbl_80552110)->unk3A0 + 0x1d0, o->unk50, o->unk78);
    if (!seen || force) {
        Placement at;
        if (!fn_80048DD0(fn_800B24AC(o), fn_800B1724(o), 4, 0, o->v21(), -0.1f, &at))
            return 1;
    }
    fn_8007D404(self, 2.0f, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    return 0;
}

void fn_80203398(register cVehicleBarrier *self) // slot 4
{
    self->hit = 0;
    if (fn_8020A1E0(self) == 1) {
        char ev[8];
        fn_8046B6C8(ev, fn_800797D4(self));
        fn_80082F30(ev);
    }
}

void fn_8020340C(register cVehicleBarrier *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (fn_8020A1E0(self) == 1) {
        char ev[8];
        fn_8046B6C8(ev, fn_800797D4(self));
        fn_80082FA4(ev);
    }
}

#define SEND_ALL(ev, get, kind)                                                        \
    if (get(self)) {                                                                   \
        fn_8046B710((Ref8 *)ev, get(self));                                            \
        fn_80082AFC(ev, get(self), fn_800797D4(self), kind, 0.0f, 0.0f, 0.0f, 0.0f);   \
    }

void fn_802034A0(register cVehicleBarrier *self, int h, int other, int a, int b, float dmg, int value) // slot 22
{
    if (self->hit)
        return;
    self->hit = 1;
    char ev[8];
    fn_8046B530(ev);
    SEND_ALL(ev, fn_8020A228, 0)
    SEND_ALL(ev, fn_8020A270, 0)
    SEND_ALL(ev, fn_8020A2B8, 0)
    SEND_ALL(ev, fn_8020A300, 0)
    fn_802037B0(self);
}

void fn_8020371C(register cVehicleBarrier *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10: {
        char ev[8];
        fn_8046B530(ev);
        fn_8046B710((Ref8 *)ev, e);
        fn_80082124(ev);
        break;
    }
    }
}

void fn_802037B0(register cVehicleBarrier *self)
{
    char ev[8];

    fn_8046B680(ev, fn_800797D4(self));
    Vector pos;
    fn_80082440(ev, &pos);
    fn_800838E0(&pos);
}

void fn_80203828(register cGenBreakProp *self) // slot 3
{
    self->off = 0;
    self->hasName = 0;
}

void fn_80203860(register cGenBreakProp *self) // slot 4
{
    char ev[8];

    fn_8046B5F0(ev, fn_800797D4(self));
    if (fn_8020A68C(self) > 0.0f)
        fn_800810DC(ev, fn_8020A68C(self), 0, 0, 0, 1);
    else if (fn_8020A68C(self) < 0.0f && !fn_8020A71C(self))
        self->off = 1;
    if (fn_8020A39C(self))
        fn_80082F30(ev);
    if (stricmp("", fn_8020A6D4(self)))
        self->hasName = 1;
}

void fn_8020397C(register cGenBreakProp *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    char ev[8];
    fn_8046B5F0(ev, fn_800797D4(self));
    switch (kind) {
    case 0:
        if (fn_8020A39C(self))
            fn_80082FA4(ev);
        break;
    case 4:
        self->off = !self->off;
        break;
    case 16:
        fn_800810DC(ev, fn_8020A68C(self) * -1.0f, 0, 0, 0, 0);
        break;
    case 17: {
        int actor = fn_80080EFC(ev);
        if (!actor)
            return;
        fn_800A2B3C(actor, 1, 0, 0, 0);
        fn_8006645C((void *)actor, 0);
        fn_80066794((void *)actor, 1);
        break;
    }
    }
}

void fn_80203AF4(register cGenBreakProp *self, int h, int other, int a, int b, float dmg, int value) // slot 22
{
    char ev[8];
    fn_8046B6C8(ev, fn_800797D4(self));
    char out[8];
    fn_8046B530(out);
    if (fn_8020A3F4(self)) {
        Vector pos;
        fn_80082440(ev, &pos);
        fn_800838E0(&pos);
    }
    if (!stricmp("", fn_8020A44C(self)))
        fn_80082E90(ev, fn_8020A44C(self), 0xff, 0xff);
    SEND_ALL(out, fn_8020A494, fn_8020A644(self))
    SEND_ALL(out, fn_8020A4DC, fn_8020A644(self))
    SEND_ALL(out, fn_8020A524, fn_8020A644(self))
    SEND_ALL(out, fn_8020A56C, fn_8020A644(self))
    SEND_ALL(out, fn_8020A5B4, fn_8020A644(self))
    SEND_ALL(out, fn_8020A5FC, fn_8020A644(self))
}

float fn_80203F40(register cGenBreakProp *self, int h, int other, int a, int b, float dmg, int c, int value) // slot 21
{
    if (self->hasName) {
        char ev[8];
        fn_8046B5A8(ev, fn_80083734(fn_8020A6D4(self)));
        if (other == fn_804425F8(ev))
            return 0.0f;
        char by[8];
        fn_8046CE70(by, other);
        if (fn_80080BA8(by) && fn_8009AC94R(*fn_80080BA8S(by)) == fn_804425F8(ev))
            return 0.0f;
    }
    if (self->off)
        return 0.0f;
    else
        return dmg;
}

void fn_80204080(register cGenBreakProp *self, int h, int other, int value) // slot 16
{
    if (!fn_8020A71C(self))
        return;
    ((cScriptV *)self)->s23(fn_800797D4(self), fn_800797D4(self), 16, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_80204150(register cDamagePropOnTrigger *self) // slot 3
{
    self->done[0] = 0;
    self->done[1] = 0;
    self->done[2] = 0;
    self->done[3] = 0;
    self->done[4] = 0;
    self->done[5] = 0;
    self->done[6] = 0;
    self->done[7] = 0;
}

void fn_802041B8(register cDamagePropOnTrigger *self) // slot 5
{
    self->count = fn_8020486C(self);
    if (self->count > 0)
        fn_8007D404(self, fn_8020A810(self) + fn_80171F8C() * 4.656612873077392578125e-10f * fn_8020A858(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_802042A0(register cDamagePropOnTrigger *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    char ev[8];
    fn_8046B5F0(ev, fn_800797D4(self));
    fn_800810DC(ev, fn_8020A7C8(self), 0, 0, 0, 0);
}

void fn_80204340(register cDamagePropOnTrigger *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    unsigned int h = fn_80204560(self);
    switch (kind) {
    case 10:
        if (h) {
            char ev[8];
            fn_8046B5F0(ev, h);
            fn_800810DC(ev, fn_8020A7C8(self), 0, 0, 0, 0);
            if (fn_8020AAE0(self))
                fn_8007D8B0(self);
            else
                fn_8007D404(self, fn_8020A810(self) + fn_80171F8C() * 4.656612873077392578125e-10f * fn_8020A858(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        } else if (self->done[0] && self->done[1] && self->done[2] && self->done[3] && self->done[4] && self->done[5] && self->done[6] && self->done[7])
            fn_8007D8B0(self);
        else
            fn_8007D404(self, 5.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
}

#define PICK(i, get)                           \
    case i:                                    \
        if (get(self) && !self->done[i]) {     \
            self->done[i] = 1;                 \
            return get(self);                  \
        }                                      \
        break;

unsigned int fn_80204560(register cDamagePropOnTrigger *self)
{
    int pick = fn_80171F8C() * 4.656612873077392578125e-10f * self->count;
    switch (pick) {
    PICK(0, fn_8020A8A0)
    PICK(1, fn_8020A8E8)
    PICK(2, fn_8020A930)
    PICK(3, fn_8020A978)
    PICK(4, fn_8020A9C0)
    PICK(5, fn_8020AA08)
    PICK(6, fn_8020AA50)
    PICK(7, fn_8020AA98)
    }
    return 0;
}

#define COUNT(i, get)       \
    if (get(self))          \
        n++;                \
    else                    \
        self->done[i] = 1;

int fn_8020486C(register cDamagePropOnTrigger *self)
{
    int n = 0;
    COUNT(0, fn_8020A8A0)
    COUNT(1, fn_8020A8E8)
    COUNT(2, fn_8020A930)
    COUNT(3, fn_8020A978)
    COUNT(4, fn_8020A9C0)
    COUNT(5, fn_8020AA08)
    COUNT(6, fn_8020AA50)
    COUNT(7, fn_8020AA98)
    return n;
}

void fn_80204A10(register cPortalControl *self) // slot 3
{
    self->on = 1;
}

void fn_80204A38(register cPortalControl *self) // slot 4
{
    if (fn_8020AB8C(self))
        fn_80204B1C(self, 0);
}

void fn_80204A88(register cPortalControl *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 4:
        if (self->on)
            fn_80204B1C(self, 0);
        else
            fn_80204B1C(self, 1);
        break;
    }
}

#define PORTAL_SET(ev)                                          \
    if (on)                                                     \
        fn_800A90F4(fn_800B1CC8(fn_80081E6C(ev)));              \
    else                                                        \
        fn_800A916C(fn_800B1CC8(fn_80081E6C(ev)));
#define PORTAL(get)                                             \
    if (get(self)) {                                            \
        fn_8046B710((Ref8 *)ev, get(self));                     \
        if (fn_8020AE24(self))                                  \
            fn_80083B74(fn_800797D4(self), get(self), on);      \
        else                                                    \
            PORTAL_SET(ev)                                      \
    }

void fn_80204B1C(register cPortalControl *self, int on)
{
    char ev[8];
    fn_8046B530(ev);
    if (on)
        self->on = 1;
    else
        self->on = 0;
    fn_8046B710((Ref8 *)ev, fn_800797D4(self));
    if (!fn_8020AE24(self))
        PORTAL_SET(ev)
    PORTAL(fn_8020ABE4)
    PORTAL(fn_8020AC2C)
    PORTAL(fn_8020AC74)
    PORTAL(fn_8020ACBC)
    PORTAL(fn_8020AD04)
    PORTAL(fn_8020AD4C)
    PORTAL(fn_8020AD94)
    PORTAL(fn_8020ADDC)
}

void fn_8020524C(register cPropRespawn *self) // slot 3
{
    self->enabled = 1;
    self->ready = 0;
}

void fn_80205284(register cPropRespawn *self) // slot 5
{
    self->ready = 1;
    if (fn_8020AFB8(self) && (fn_8020B010(self) == 1 || fn_8020B010(self) == 1))
        fn_8007D404(self, fn_8020AED0(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    char ev[8];
    fn_8046B6C8(ev, fn_800797D4(self));
    if (fn_80081E6C(ev) && !strnicmp(fn_80081E6C(ev)->name, "prp_rl_mine", 0xb))
        fn_8007D404(self, 1.0f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_802053D8(register cPropRespawn *self) // slot 31
{
    char ev[8];

    if (!self->enabled || fn_8020AFB8(self))
        return;
    fn_8046B5F0(ev, fn_800797D4(self));
    if (fn_80081074(ev) && fn_80205B98(self, 1)) {
        char e2[8];
        fn_8046B6C8(e2, fn_800797D4(self));
        if (fn_8046C8FC(e2))
            fn_80082FA4(e2);
    }
}

int fn_802054BC(register cPropRespawn *self, int h, int value) // slot 47
{
    if (!self->enabled || !self->ready)
        return 1;
    if (fn_8020AED0(self) > 0.0f)
        fn_8007D404(self, fn_8020AED0(self) >= 5.0f ? (fn_8020AED0(self) <= 30.0f ? fn_8020AED0(self) : 30.0f) : 5.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    return 1;
}

void fn_802055DC(register cPropRespawn *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    if (!self->enabled)
        return;
    switch (kind) {
    case 10:
        if (fn_80205B98(self, 0)) {
            char ev[8];
            fn_8046B6C8(ev, fn_800797D4(self));
            fn_80082FA4(ev);
            if (stricmp("", fn_8020AF18(self)))
                fn_80082E90(ev, fn_8020AF18(self), 0xff, 0xff);
        }
        break;
    case 20: {
        char ev[8];
        fn_8046B5F0(ev, fn_800797D4(self));
        if (!fn_80080EFC(ev))
            return;
        if (fn_800B1138R(*fn_80080EFCS(ev))) {
            fn_8007D404(self, 1.0f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            return;
        }
        float health = fn_800A4054((void *)fn_80080EFC(ev)) / fn_800A4080(fn_80080EFC(ev));
        if (health <= 0.0f)
            return;
        if (health == 1.0f) {
            fn_8007D404(self, 1.0f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            return;
        }
        char light[8];
        fn_8046B680(light, fn_800797D4(self));
        fn_800806E0(light, "MineCoreLight", 0, 1.0f / health, 0.0f, 0.0f, -1);
        fn_8007D404(self, 1.0f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
    }
}

void fn_802058D0(register cPropRespawn *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 0:
        fn_8007D404(self, 0.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 18:
        fn_8007D404(self, 2.0f * (fn_80171F8C() * 4.656612873077392578125e-10f), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 7:
        fn_8007D8B0(self);
        self->enabled = 0;
        break;
    case 17: {
        char ev[8];
        fn_8046B5F0(ev, fn_800797D4(self));
        if (!fn_80080EFC(ev))
            return;
        fn_800A2B3C(fn_80080EFC(ev), 1, 0, 0, 0);
        fn_8006645CR(*fn_80080EFCS(ev), 0);
        Vector dir;
        Vector to;
        char src[8];
        fn_8046B6C8(src, b);
        fn_80082440(src, &to);
        Vector from;
        fn_80082440(ev, &from);
        fn_80429038(&dir, &from, &to);
        fn_8042F76C(&dir);
        fn_80435530(&dir, 5.0f);
        fn_80066DC4R(*fn_80080EFCS(ev), &dir, 1, 0, 0);
        fn_80066794R(*fn_80080EFCS(ev), 1);
        fn_8007D8B0(self);
        self->enabled = 0;
        break;
    }
    }
}

int fn_80205B98(register cPropRespawn *self, int force)
{
    int found = 0;
    char ev[8];
    fn_8046B680(ev, fn_800797D4(self));
    SObj *o = fn_80080300P(ev);
    if (!o)
        return 0;
    unsigned char seen = fn_801B90A8(fn_8043289C(lbl_80552110)->unk3A0 + 0x1d0, o->unk50, o->unk78);
    if (!seen || force || fn_8020AF60(self)) {
        Placement at;
        if (!fn_80048DD0(fn_800B24AC(o), fn_800B1724(o), 4, 0, o->v21(), -0.1f, &at)) {
            SObj *p;
            SObj *next;
            char e2[8];
            fn_8046B680(e2, 0);
            p = fn_80430050(lbl_8052F060).first;
            while (p) {
                next = fn_800B1AC4(p);
                fn_8046B710((Ref8 *)e2, fn_800B13D8(p));
                SObj *a = fn_80080300P(e2);
                if (a && (fn_8009AC94P(a) == fn_800797D4(self) || (fn_800B0CC0(a) && fn_800A46E8(fn_800B1478(a)) == fn_800797D4(self)))) {
                    p->v1();
                    found = 1;
                }
                p = next;
            }
            if (!found)
                return 1;
            else {
                fn_8007D404(self, 0.1f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
                return 0;
            }
        } else if (fn_800489BC(&at)) {
            char e2[8];
            fn_8046B680(e2, fn_800489BC(&at));
            SObj *a = fn_80080300P(e2);
            if (a && (fn_8009AC94P(a) == fn_800797D4(self) || (fn_800B0CC0(a) && fn_800A46E8(fn_800B1478(a)) == fn_800797D4(self))))
                fn_80082124(e2);
            fn_8007D404(self, 0.5f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            return 0;
        }
    }
    fn_8007D404(self, 2.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    return 0;
}

void fn_80205FFC(register cRemoveObjects *self) // slot 4
{
    if (!fn_8020B2FC(self))
        fn_802061C8(self);
}

void fn_80206050(register cRemoveObjects *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (fn_8020B2FC(self) == 1)
        fn_802061C8(self);
}

void fn_802060C4(register cRemoveObjects *self, int h, int other, int value) // slot 14
{
    if (fn_8020B2FC(self) == 3 && h == fn_800797D4(self))
        fn_802061C8(self);
}

float fn_8020613C(register cRemoveObjects *self, int h, int other, int a, int b, float dmg, int c, int value) // slot 21
{
    if (fn_8020B2FC(self) == 2 && h == fn_800797D4(self))
        fn_802061C8(self);
    return dmg;
}

#define REMOVE(get)                     \
    if (get(self)) {                    \
        fn_8046B710((Ref8 *)ev, get(self)); \
        if (!fn_8020B2B4(self))         \
            fn_80082124(ev);            \
        else                            \
            fn_80082F30(ev);            \
    }

void fn_802061C8(register cRemoveObjects *self)
{
    char ev[8];

    fn_8046B530(ev);
    REMOVE(fn_8020B0BC)
    REMOVE(fn_8020B104)
    REMOVE(fn_8020B14C)
    REMOVE(fn_8020B194)
    REMOVE(fn_8020B1DC)
    REMOVE(fn_8020B224)
    REMOVE(fn_8020B26C)
}

void fn_8020644C(register cCrystalBreak *self) // slot 3
{
    self->hit = 0;
    self->immune = 0;
}

void fn_8020647C(register cCrystalBreak *self) // slot 5
{
    if (fn_8020B3DC(self)) {
        char ev[8];
        fn_8046B5A8(ev, fn_8020B398(self));
        fn_80082A44(ev, 1, fn_8020B434(self), 0);
    }
}

void fn_802064F8(register cCrystalBreak *self, int h, int node, int value) // slot 25
{
    if (fn_8020B3DC(self)) {
        char ev[8];
        fn_8046B5A8(ev, fn_8020B398(self));
        fn_80082A44(ev, !node, fn_8020B434(self), 0);
    }
}

float fn_80206598(register cCrystalBreak *self, int h, int other, int a, int b, float dmg, int c, int value) // slot 21
{
    if (self->immune)
        return 0.0f;
    if (self->hit)
        return dmg;
    self->hit = 1;
    char ev[8];
    fn_8046B5A8(ev, fn_8020B398(self));
    fn_80393D0C(fn_80081E6C(ev), "ambientSpark", 0x19, 0);
    return dmg;
}

void fn_8020666C(register cCrystalBreak *self, int h, int a, int b, int c, int d) // slot 29
{
    char ev[8];
    fn_8046B5A8(ev, fn_8020B398(self));
    switch (b) {
    case 0:
        fn_80393D0C(fn_80081E6C(ev), "crystalSmoke", 0xff, 0xff);
        break;
    case 1: {
        fn_8007D404(self, 0.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        char e2[8];
        fn_8046B5F0(e2, fn_804425F8(ev));
        fn_800A46A0(fn_80080EFC(e2), 1);
        break;
    }
    }
}

void fn_80206790(register cCrystalBreak *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10: {
        char ev[8];
        fn_8046B6C8(ev, fn_8020B398(self));
        fn_800838E0(fn_800B1724(fn_80081E6C(ev)));
        fn_80082190(ev, "exp_LargeFake");
        fn_80082124(ev);
        break;
    }
    }
}

void fn_8020685C(register cCrystalBreak *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 0:
        self->immune = 1;
        break;
    }
}

void fn_802068C0(register cCrystalBreak_Phase2 *self, unsigned int h) // slot 12
{
    self->immune = 1;
    char ev[8];
    fn_8046B680(ev, h);
    if (!fn_80080300(ev))
        return;
    fn_80083D08(fn_800797D4(self), fn_800797D4(self), 0, h, fn_8009AC94U(fn_80080300P(ev)), 0.0f, 0.0f);
    char e2[8];
    fn_8046B6C8(e2, fn_8009AC94P(fn_80080300P(ev)));
    fn_800836A8(e2, "crystalGlow");
    fn_80083230(e2, "turlinDamFXCtrl");
    fn_8007D404(self, 1.5f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

float fn_80206A64(register cCrystalBreak_Phase2 *self, int h, int other, int a, int b, float dmg, int c, int value) // slot 21
{
    if (self->immune)
        return 0.0f;
    else
        return dmg;
}

void fn_80206AD0(register cCrystalBreak_Phase2 *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        self->immune = 0;
        break;
    }
}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.text"); // 0x804A1B34

void fn_80206B34(register cCameraMPToggle *self) // slot 5
{
    self->on = 0;
    if (fn_8020B524(self)) {
        fn_8046B838(lbl_80552110, 1);
        self->on = 1;
    }
}

void fn_80206BA0(register cCameraMPToggle *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 4:
        if (self->on)
            return;
        else {
            fn_8046B838(lbl_80552110, 1);
            self->on = 1;
        }
        break;
    }
}

void fn_80206C38(register cLabConsole *self) // slot 4
{
    self->used = 0;
    fn_8007CF00(self, fn_8020B5D0(self), 0);
    fn_8007CF00(self, fn_8020B618(self), 0);
    fn_8007CF00(self, fn_8020B660(self), 0);
}

void fn_80206CCC(register cLabConsole *self, int h, int other, int value) // slot 18
{
    if (self->used == 1)
        return;
    if (h == fn_8020B618(self) || h == fn_8020B660(self)) {
        self->used = 1;
        fn_80206E18(self);
    }
}

float fn_80206D64(register cLabConsole *self, int h, int other, int a, int b, float dmg, int c, int value) // slot 21
{
    if (self->used == 1)
        return dmg;
    if (h == fn_8020B618(self) || h == fn_8020B660(self)) {
        self->used = 1;
        fn_80206E18(self);
    }
    return dmg;
}

void fn_80206E18(register cLabConsole *self)
{
    char ev[8];

    fn_8046B5F0(ev, fn_8020B5D0(self));
    fn_800810DC(ev, 10.0f, 0, 0, 0, 0);
}

void fn_80206E80(register cWieldableToggle *self) // slot 5
{
    if (!fn_8020B6FC(self)) {
        self->enabled = 0;
        char ev[8];
        fn_8046B5F0(ev, fn_800797D4(self));
        fn_80080FF4(ev, 2);
    } else
        self->enabled = 1;
    if (fn_8020B754(self))
        self->locked = 1;
    else
        self->locked = 0;
}

float fn_80206F24(register cWieldableToggle *self, int h, int other, int a, int b, float dmg, int c, int value) // slot 21
{
    if (self->locked == 1)
        return -1.0f;
    else
        return dmg;
}

void fn_80206F88(register cWieldableToggle *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    char ev[8];
    fn_8046B5F0(ev, fn_800797D4(self));
    if (self->enabled == 1) {
        self->enabled = 0;
        fn_80080FF4(ev, 2);
    } else if (self->enabled == 0) {
        self->enabled = 1;
        fn_80080F74(ev, 2);
    }
}

void fn_80207040(register cWieldableToggle *self, int h, int other, int value) // slot 18
{
    if (self->enabled == 1 && self->locked == 1)
        self->locked = 0;
}

void fn_8020708C(register cReverseWallRenderToggle *self) // slot 4
{
    if (!fn_8020B7F0(self)) {
        char ev[8];
        fn_8046B6C8(ev, fn_800797D4(self));
        char wall[8];
        fn_8046C1E8(wall, fn_8046C160(ev));
        fn_800813AC(wall, 0);
    }
}

void fn_80207114(register cReverseWallRenderToggle *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 4: {
        char ev[8];
        fn_8046B6C8(ev, fn_800797D4(self));
        char wall[8];
        fn_8046C1E8(wall, fn_8046C160(ev));
        fn_800813AC(wall, !fn_80081338(wall));
        break;
    }
    }
}

void fn_802071E8(register cPropGroupFade *self) // slot 4
{
    fn_8007CF00(self, fn_8020B89C(self), 0);
    fn_8007CF00(self, fn_8020B8E4(self), 0);
    fn_8007CF00(self, fn_8020B92C(self), 0);
    fn_8007CF00(self, fn_8020B974(self), 0);
    fn_8007CF00(self, fn_8020B9BC(self), 0);
    fn_8007CF00(self, fn_8020BA04(self), 0);
    fn_8007CF00(self, fn_8020BA4C(self), 0);
    fn_8007CF00(self, fn_8020BA94(self), 0);
    fn_8007CF00(self, fn_8020BADC(self), 0);
    fn_8007CF00(self, fn_8020BB24(self), 0);
}

void fn_80207338(register cPropGroupFade *self, int h, int value) // slot 19
{
    char e0[8];
    char e1[8];
    char e2[8];
    char e3[8];
    char e4[8];
    char e5[8];
    char e6[8];
    char e7[8];
    char e8[8];
    char e9[8];

    fn_8046B680(e0, fn_8020B89C(self));
    fn_8046B680(e1, fn_8020B8E4(self));
    fn_8046B680(e2, fn_8020B92C(self));
    fn_8046B680(e3, fn_8020B974(self));
    fn_8046B680(e4, fn_8020B9BC(self));
    fn_8046B680(e5, fn_8020BA04(self));
    fn_8046B680(e6, fn_8020BA4C(self));
    fn_8046B680(e7, fn_8020BA94(self));
    fn_8046B680(e8, fn_8020BADC(self));
    fn_8046B680(e9, fn_8020BB24(self));
    fn_8008065C(e0, 1);
    fn_8008065C(e1, 1);
    fn_8008065C(e2, 1);
    fn_8008065C(e3, 1);
    fn_8008065C(e4, 1);
    fn_8008065C(e5, 1);
    fn_8008065C(e6, 1);
    fn_8008065C(e7, 1);
    fn_8008065C(e8, 1);
    fn_8008065C(e9, 1);
}

void fn_80207530(register cMP_MatchTrigger *self) // slot 5
{
}

void fn_80207558(register cMP_MatchTrigger *self) // slot 32
{
    if (fn_8020BBC0(self))
        fn_80207600(self);
}

void fn_802075AC(register cMP_MatchTrigger *self) // slot 33
{
    if (fn_8020BC08(self))
        fn_80207600(self);
}

#define MATCH_SEND(get, kind)                                                                   \
    if (get(self)) {                                                                            \
        fn_8046B710((Ref8 *)ev, get(self));                                                     \
        fn_80082AFC(ev, get(self), fn_800797D4(self), kind(self), 0.0f, 0.0f, 0.0f, 0.0f);      \
    }

void fn_80207600(register cMP_MatchTrigger *self)
{
    char ev[8];

    fn_8046B530(ev);
    MATCH_SEND(fn_8020BC50, fn_8020BC98)
    MATCH_SEND(fn_8020BCE0, fn_8020BD28)
    MATCH_SEND(fn_8020BD70, fn_8020BDB8)
    MATCH_SEND(fn_8020BE00, fn_8020BE48)
    MATCH_SEND(fn_8020BE90, fn_8020BED8)
    MATCH_SEND(fn_8020BF20, fn_8020BF68)
    MATCH_SEND(fn_8020BFB0, fn_8020BFF8)
    MATCH_SEND(fn_8020C040, fn_8020C088)
    MATCH_SEND(fn_8020C0D0, fn_8020C118)
    MATCH_SEND(fn_8020C160, fn_8020C1A8)
}

void fn_80207B68(register cCameraSet *self) // slot 4
{
    fn_8007C830(fn_8020C244(self));
}

inline int sn_return_decl10(int a) { return a; }

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
#define IS_ONE(cls, name, reader, i)     \
    int name(register cls *self)         \
    {                                    \
        return reader(self, i) == 1;     \
    }

PARAM(float, cObjectExplosion, fn_80207BB4, fn_8007935C, 0)
PARAM(float, cObjectExplosion, fn_80207BFC, fn_8007935C, 1)
PARAM(int, cObjectExplosion, fn_80207C44, fn_80079068, 2)
PARAM(char *, cObjectExplosion, fn_80207C8C, fn_800794FC, 3)
PARAM(int, cObjectSetCollision, fn_80207CD4, fn_80079068, 0)
PARAM(int, cObjectSetCollision, fn_80207D1C, fn_80079068, 1)
PARAM(float, cObjectSetCollision, fn_80207D64, fn_8007935C, 2)
PARAM(float, cObjectSetCollision, fn_80207DAC, fn_8007935C, 3)
PARAM(float, cObjectSetCollision, fn_80207DF4, fn_8007935C, 4)
FLAG(cObjectSetCollision, fn_80207E3C, fn_80079068, 5)
PARAM(int, cObjectMove, fn_80207E94, fn_80079068, 0)
PARAM(float, cObjectMove, fn_80207EDC, fn_8007935C, 1)
PARAM(float, cObjectMove, fn_80207F24, fn_8007935C, 2)
PARAM(float, cObjectMove, fn_80207F6C, fn_8007935C, 3)
PARAM(int, cObjectMove, fn_80207FB4, fn_80079068, 4)
IS_ONE(cObjectMove, fn_80207FFC, fn_80079068, 5)
IS_ONE(cObjectMove, fn_80208050, fn_80079068, 6)
PARAM(unsigned int, cObjectMove, fn_802080A4, fn_800791C8, 7)
PARAM(unsigned int, cObjectMove, fn_802080EC, fn_800791C8, 8)
PARAM(unsigned int, cObjectMove, fn_80208134, fn_800791C8, 9)
PARAM(unsigned int, cObjectMove, fn_8020817C, fn_800791C8, 10)
PARAM(int, cObjectMove, fn_802081C4, fn_80079068, 11)
FLAG(cObjectRumbleShake, fn_8020820C, fn_80079068, 0)
PARAM(float, cObjectRumbleShake, fn_80208264, fn_8007935C, 1)
PARAM(float, cObjectRumbleShake, fn_802082AC, fn_8007935C, 2)
PARAM(float, cObjectRumbleShake, fn_802082F4, fn_8007935C, 3)
PARAM(int, cObjectRumbleShake, fn_8020833C, fn_80079068, 4)
FLAG(cObjectRumbleShake, fn_80208384, fn_80079068, 5)
PARAM(float, cObjectRumbleShake, fn_802083DC, fn_8007935C, 6)
PARAM(float, cObjectRumbleShake, fn_80208424, fn_8007935C, 7)
PARAM(float, cObjectRumbleShake, fn_8020846C, fn_8007935C, 8)
PARAM(float, cObjectRumbleShake, fn_802084B4, fn_8007935C, 9)
PARAM(float, cObjectRumbleShake, fn_802084FC, fn_8007935C, 10)
PARAM(float, cTimerTrigger, fn_80208544, fn_8007935C, 0)
PARAM(float, cTimerTrigger, fn_8020858C, fn_8007935C, 1)
PARAM(int, cTimerTrigger, fn_802085D4, fn_80079068, 2)
PARAM(unsigned int, cTimerTrigger, fn_8020861C, fn_800791C8, 3)
PARAM(unsigned int, cTimerTrigger, fn_80208664, fn_800791C8, 4)
PARAM(unsigned int, cTimerTrigger, fn_802086AC, fn_800791C8, 5)
PARAM(unsigned int, cTimerTrigger, fn_802086F4, fn_800791C8, 6)
PARAM(unsigned int, cTimerTrigger, fn_8020873C, fn_800791C8, 7)
PARAM(unsigned int, cTimerTrigger, fn_80208784, fn_800791C8, 8)
PARAM(unsigned int, cTimerTrigger, fn_802087CC, fn_800791C8, 9)
PARAM(unsigned int, cTimerTrigger, fn_80208814, fn_800791C8, 10)
PARAM(int, cTimerTrigger, fn_8020885C, fn_80079068, 11)
PARAM(int, cTriggerOnAction, fn_802088A4, fn_80079068, 0)
PARAM(float, cTriggerOnAction, fn_802088EC, fn_8007935C, 1)
PARAM(int, cTriggerOnAction, fn_80208934, fn_80079068, 2)
PARAM(int, cTriggerOnAction, fn_8020897C, fn_80079068, 3)
PARAM(int, cTriggerOnAction, fn_802089C4, fn_80079068, 4)
PARAM(int, cTriggerOnAction, fn_80208A0C, fn_80079068, 5)
PARAM(int, cTriggerOnAction, fn_80208A54, fn_80079068, 6)
PARAM(int, cTriggerOnAction, fn_80208A9C, fn_80079068, 7)
PARAM(unsigned int, cTriggerOnAction, fn_80208AE4, fn_800791C8, 8)
PARAM(unsigned int, cTriggerOnAction, fn_80208B2C, fn_800791C8, 9)
PARAM(unsigned int, cTriggerOnAction, fn_80208B74, fn_800791C8, 10)
PARAM(unsigned int, cTriggerOnAction, fn_80208BBC, fn_800791C8, 11)
PARAM(unsigned int, cTriggerOnAction, fn_80208C04, fn_800791C8, 12)
PARAM(float, cTriggerOnAction, fn_80208C4C, fn_8007935C, 13)
PARAM(unsigned int, cTriggerOnAction, fn_80208C94, fn_800791C8, 14)
PARAM(float, cTriggerOnAction, fn_80208CDC, fn_8007935C, 15)
PARAM(unsigned int, cTriggerOnAction, fn_80208D24, fn_800791C8, 16)
PARAM(float, cTriggerOnAction, fn_80208D6C, fn_8007935C, 17)
PARAM(unsigned int, cTriggerOnAction, fn_80208DB4, fn_800791C8, 18)
PARAM(float, cTriggerOnAction, fn_80208DFC, fn_8007935C, 19)
PARAM(int, cTriggerOnAction, fn_80208E44, fn_80079068, 20)
PARAM(int, cTriggerOnAction, fn_80208E8C, fn_80079068, 21)
PARAM(float, cTriggerOnAction, fn_80208ED4, fn_8007935C, 22)
PARAM(int, cTriggerOnAction, fn_80208F1C, fn_80079068, 23)
PARAM(unsigned int, cTriggerRelay, fn_80208F64, fn_800791C8, 0)
PARAM(float, cTriggerRelay, fn_80208FAC, fn_8007935C, 1)
PARAM(char *, cTriggerRelay, fn_80208FF4, fn_800794FC, 2)
PARAM(unsigned int, cTriggerRelay, fn_8020903C, fn_800791C8, 3)
PARAM(float, cTriggerRelay, fn_80209084, fn_8007935C, 4)
PARAM(char *, cTriggerRelay, fn_802090CC, fn_800794FC, 5)
PARAM(unsigned int, cTriggerRelay, fn_80209114, fn_800791C8, 6)
PARAM(float, cTriggerRelay, fn_8020915C, fn_8007935C, 7)
PARAM(char *, cTriggerRelay, fn_802091A4, fn_800794FC, 8)
PARAM(unsigned int, cTriggerRelay, fn_802091EC, fn_800791C8, 9)
PARAM(float, cTriggerRelay, fn_80209234, fn_8007935C, 10)
PARAM(char *, cTriggerRelay, fn_8020927C, fn_800794FC, 11)
PARAM(unsigned int, cTriggerRelay, fn_802092C4, fn_800791C8, 12)
PARAM(float, cTriggerRelay, fn_8020930C, fn_8007935C, 13)
PARAM(char *, cTriggerRelay, fn_80209354, fn_800794FC, 14)
PARAM(unsigned int, cTriggerRelay, fn_8020939C, fn_800791C8, 15)
PARAM(float, cTriggerRelay, fn_802093E4, fn_8007935C, 16)
PARAM(char *, cTriggerRelay, fn_8020942C, fn_800794FC, 17)
PARAM(unsigned int, cTriggerRelay, fn_80209474, fn_800791C8, 18)
PARAM(float, cTriggerRelay, fn_802094BC, fn_8007935C, 19)
PARAM(char *, cTriggerRelay, fn_80209504, fn_800794FC, 20)
PARAM(unsigned int, cTriggerRelay, fn_8020954C, fn_800791C8, 21)
PARAM(float, cTriggerRelay, fn_80209594, fn_8007935C, 22)
PARAM(char *, cTriggerRelay, fn_802095DC, fn_800794FC, 23)
PARAM(unsigned int, cTriggerRelay, fn_80209624, fn_800791C8, 24)
PARAM(float, cTriggerRelay, fn_8020966C, fn_8007935C, 25)
PARAM(char *, cTriggerRelay, fn_802096B4, fn_800794FC, 26)
PARAM(unsigned int, cTriggerRelay, fn_802096FC, fn_800791C8, 27)
PARAM(float, cTriggerRelay, fn_80209744, fn_8007935C, 28)
PARAM(char *, cTriggerRelay, fn_8020978C, fn_800794FC, 29)
PARAM(unsigned int, cTriggerRelay, fn_802097D4, fn_800791C8, 30)
PARAM(float, cTriggerRelay, fn_8020981C, fn_8007935C, 31)
PARAM(char *, cTriggerRelay, fn_80209864, fn_800794FC, 32)
PARAM(unsigned int, cTriggerRelay, fn_802098AC, fn_800791C8, 33)
PARAM(float, cTriggerRelay, fn_802098F4, fn_8007935C, 34)
PARAM(char *, cTriggerRelay, fn_8020993C, fn_800794FC, 35)
PARAM(int, cTriggerRelay, fn_80209984, fn_80079068, 36)
PARAM(char *, cTriggerRelay, fn_802099CC, fn_800794FC, 37)
PARAM(float, cTriggerRelay, fn_80209A14, fn_8007935C, 38)
PARAM(float, cSetAnimFrame, fn_80209A5C, fn_8007935C, 1)
PARAM(float, cSetAnimFrame, fn_80209AA4, fn_8007935C, 2)
PARAM(float, cSetAnimFrame, fn_80209AEC, fn_8007935C, 3)
PARAM(float, cSetAnimFrame, fn_80209B34, fn_8007935C, 4)
PARAM(float, cSetAnimFrame, fn_80209B7C, fn_8007935C, 5)
PARAM(float, cSetAnimFrame, fn_80209BC4, fn_8007935C, 6)
PARAM(float, cSetAnimFrame, fn_80209C0C, fn_8007935C, 7)
PARAM(float, cSetAnimFrame, fn_80209C54, fn_8007935C, 8)
PARAM(char *, cDebrisFall, fn_80209C9C, fn_800794FC, 0)
PARAM(int, cDebrisFall, fn_80209CE4, fn_80079068, 1)
PARAM(char *, cDebrisFall, fn_80209D2C, fn_800794FC, 2)
PARAM(int, cDebrisFall, fn_80209D74, fn_80079068, 3)
PARAM(char *, cDebrisFall, fn_80209DBC, fn_800794FC, 4)
PARAM(int, cDebrisFall, fn_80209E04, fn_80079068, 5)
FLAG(cDebrisFall, fn_80209E4C, fn_80079068, 6)
PARAM(int, cDebrisFall, fn_80209EA4, fn_80079068, 7)
PARAM(char *, cDebrisFall, fn_80209EEC, fn_800794FC, 8)
PARAM(float, cDebrisFall, fn_80209F34, fn_8007935C, 9)

cScript *fn_80209F7C(register cVehicleBreak *self)
{
    return new cVehicleBreak;
}


int fn_80209FD0(register cVehicleBreak *self)
{
    return fn_800797D4(self);
}

PARAM(unsigned int, cVehicleBreak, fn_8020A014, fn_80079068, 0)
FLAG(cVehicleBreak, fn_8020A05C, fn_80079068, 1)
PARAM(float, cVehicleBreak, fn_8020A0B4, fn_8007935C, 2)
PARAM(float, cVehicleBreak, fn_8020A0FC, fn_8007935C, 3)
PARAM(char *, cVehicleBreak, fn_8020A144, fn_800794FC, 4)

cScript *fn_8020A18C(register cVehicleBarrier *self)
{
    return new cVehicleBarrier;
}

PARAM(int, cVehicleBarrier, fn_8020A1E0, fn_80079068, 0)
PARAM(unsigned int, cVehicleBarrier, fn_8020A228, fn_800791C8, 1)
PARAM(unsigned int, cVehicleBarrier, fn_8020A270, fn_800791C8, 2)
PARAM(unsigned int, cVehicleBarrier, fn_8020A2B8, fn_800791C8, 3)
PARAM(unsigned int, cVehicleBarrier, fn_8020A300, fn_800791C8, 4)

cScript *fn_8020A348(register cGenBreakProp *self)
{
    return new cGenBreakProp;
}

FLAG(cGenBreakProp, fn_8020A39C, fn_80079068, 0)
FLAG(cGenBreakProp, fn_8020A3F4, fn_80079068, 1)
PARAM(char *, cGenBreakProp, fn_8020A44C, fn_800794FC, 2)
PARAM(unsigned int, cGenBreakProp, fn_8020A494, fn_800791C8, 3)
PARAM(unsigned int, cGenBreakProp, fn_8020A4DC, fn_800791C8, 4)
PARAM(unsigned int, cGenBreakProp, fn_8020A524, fn_800791C8, 5)
PARAM(unsigned int, cGenBreakProp, fn_8020A56C, fn_800791C8, 6)
PARAM(unsigned int, cGenBreakProp, fn_8020A5B4, fn_800791C8, 7)
PARAM(unsigned int, cGenBreakProp, fn_8020A5FC, fn_800791C8, 8)
PARAM(int, cGenBreakProp, fn_8020A644, fn_80079068, 9)
PARAM(float, cGenBreakProp, fn_8020A68C, fn_8007935C, 10)
PARAM(char *, cGenBreakProp, fn_8020A6D4, fn_800794FC, 11)
FLAG(cGenBreakProp, fn_8020A71C, fn_80079068, 12)

cScript *fn_8020A774(register cDamagePropOnTrigger *self)
{
    return new cDamagePropOnTrigger;
}

PARAM(float, cDamagePropOnTrigger, fn_8020A7C8, fn_8007935C, 0)
PARAM(float, cDamagePropOnTrigger, fn_8020A810, fn_8007935C, 1)
PARAM(float, cDamagePropOnTrigger, fn_8020A858, fn_8007935C, 2)
PARAM(unsigned int, cDamagePropOnTrigger, fn_8020A8A0, fn_800791C8, 3)
PARAM(unsigned int, cDamagePropOnTrigger, fn_8020A8E8, fn_800791C8, 4)
PARAM(unsigned int, cDamagePropOnTrigger, fn_8020A930, fn_800791C8, 5)
PARAM(unsigned int, cDamagePropOnTrigger, fn_8020A978, fn_800791C8, 6)
PARAM(unsigned int, cDamagePropOnTrigger, fn_8020A9C0, fn_800791C8, 7)
PARAM(unsigned int, cDamagePropOnTrigger, fn_8020AA08, fn_800791C8, 8)
PARAM(unsigned int, cDamagePropOnTrigger, fn_8020AA50, fn_800791C8, 9)
PARAM(unsigned int, cDamagePropOnTrigger, fn_8020AA98, fn_800791C8, 10)
FLAG(cDamagePropOnTrigger, fn_8020AAE0, fn_80079068, 11)

cScript *fn_8020AB38(register cPortalControl *self)
{
    return new cPortalControl;
}

FLAG(cPortalControl, fn_8020AB8C, fn_80079068, 0)
PARAM(unsigned int, cPortalControl, fn_8020ABE4, fn_800791C8, 1)
PARAM(unsigned int, cPortalControl, fn_8020AC2C, fn_800791C8, 2)
PARAM(unsigned int, cPortalControl, fn_8020AC74, fn_800791C8, 3)
PARAM(unsigned int, cPortalControl, fn_8020ACBC, fn_800791C8, 4)
PARAM(unsigned int, cPortalControl, fn_8020AD04, fn_800791C8, 5)
PARAM(unsigned int, cPortalControl, fn_8020AD4C, fn_800791C8, 6)
PARAM(unsigned int, cPortalControl, fn_8020AD94, fn_800791C8, 7)
PARAM(unsigned int, cPortalControl, fn_8020ADDC, fn_800791C8, 8)
FLAG(cPortalControl, fn_8020AE24, fn_80079068, 9)

cScript *fn_8020AE7C(register cPropRespawn *self)
{
    return new cPropRespawn;
}

PARAM(float, cPropRespawn, fn_8020AED0, fn_8007935C, 0)
PARAM(char *, cPropRespawn, fn_8020AF18, fn_800794FC, 1)
FLAG(cPropRespawn, fn_8020AF60, fn_80079068, 2)
FLAG(cPropRespawn, fn_8020AFB8, fn_80079068, 3)
FLAG(cPropRespawn, fn_8020B010, fn_80079068, 4)

cScript *fn_8020B068(register cRemoveObjects *self)
{
    return new cRemoveObjects;
}

PARAM(unsigned int, cRemoveObjects, fn_8020B0BC, fn_800791C8, 0)
PARAM(unsigned int, cRemoveObjects, fn_8020B104, fn_800791C8, 1)
PARAM(unsigned int, cRemoveObjects, fn_8020B14C, fn_800791C8, 2)
PARAM(unsigned int, cRemoveObjects, fn_8020B194, fn_800791C8, 3)
PARAM(unsigned int, cRemoveObjects, fn_8020B1DC, fn_800791C8, 4)
PARAM(unsigned int, cRemoveObjects, fn_8020B224, fn_800791C8, 5)
PARAM(unsigned int, cRemoveObjects, fn_8020B26C, fn_800791C8, 6)
PARAM(int, cRemoveObjects, fn_8020B2B4, fn_80079068, 7)
PARAM(int, cRemoveObjects, fn_8020B2FC, fn_80079068, 8)

cScript *fn_8020B344(register cCrystalBreak *self)
{
    return new cCrystalBreak;
}


unsigned int fn_8020B398(register cCrystalBreak *self)
{
    return fn_800797D4(self);
}

FLAG(cCrystalBreak, fn_8020B3DC, fn_80079068, 0)
PARAM(float, cCrystalBreak, fn_8020B434, fn_8007935C, 1)

cScript *fn_8020B47C(register cCrystalBreak_Phase2 *self)
{
    return new cCrystalBreak_Phase2;
}

cScript *fn_8020B4D0(register cCameraMPToggle *self)
{
    return new cCameraMPToggle;
}

FLAG(cCameraMPToggle, fn_8020B524, fn_80079068, 0)

cScript *fn_8020B57C(register cLabConsole *self)
{
    return new cLabConsole;
}

PARAM(unsigned int, cLabConsole, fn_8020B5D0, fn_800791C8, 0)
PARAM(unsigned int, cLabConsole, fn_8020B618, fn_800791C8, 1)
PARAM(unsigned int, cLabConsole, fn_8020B660, fn_800791C8, 2)

cScript *fn_8020B6A8(register cWieldableToggle *self)
{
    return new cWieldableToggle;
}

FLAG(cWieldableToggle, fn_8020B6FC, fn_80079068, 0)
PARAM(int, cWieldableToggle, fn_8020B754, fn_80079068, 1)

cScript *fn_8020B79C(register cReverseWallRenderToggle *self)
{
    return new cReverseWallRenderToggle;
}

FLAG(cReverseWallRenderToggle, fn_8020B7F0, fn_80079068, 0)

cScript *fn_8020B848(register cPropGroupFade *self)
{
    return new cPropGroupFade;
}

PARAM(unsigned int, cPropGroupFade, fn_8020B89C, fn_800791C8, 0)
PARAM(unsigned int, cPropGroupFade, fn_8020B8E4, fn_800791C8, 1)
PARAM(unsigned int, cPropGroupFade, fn_8020B92C, fn_800791C8, 2)
PARAM(unsigned int, cPropGroupFade, fn_8020B974, fn_800791C8, 3)
PARAM(unsigned int, cPropGroupFade, fn_8020B9BC, fn_800791C8, 4)
PARAM(unsigned int, cPropGroupFade, fn_8020BA04, fn_800791C8, 5)
PARAM(unsigned int, cPropGroupFade, fn_8020BA4C, fn_800791C8, 6)
PARAM(unsigned int, cPropGroupFade, fn_8020BA94, fn_800791C8, 7)
PARAM(unsigned int, cPropGroupFade, fn_8020BADC, fn_800791C8, 8)
PARAM(unsigned int, cPropGroupFade, fn_8020BB24, fn_800791C8, 9)

cScript *fn_8020BB6C(register cMP_MatchTrigger *self)
{
    return new cMP_MatchTrigger;
}

PARAM(int, cMP_MatchTrigger, fn_8020BBC0, fn_80079068, 0)
PARAM(int, cMP_MatchTrigger, fn_8020BC08, fn_80079068, 1)
PARAM(unsigned int, cMP_MatchTrigger, fn_8020BC50, fn_800791C8, 2)
PARAM(int, cMP_MatchTrigger, fn_8020BC98, fn_80079068, 3)
PARAM(unsigned int, cMP_MatchTrigger, fn_8020BCE0, fn_800791C8, 4)
PARAM(int, cMP_MatchTrigger, fn_8020BD28, fn_80079068, 5)
PARAM(unsigned int, cMP_MatchTrigger, fn_8020BD70, fn_800791C8, 6)
PARAM(int, cMP_MatchTrigger, fn_8020BDB8, fn_80079068, 7)
PARAM(unsigned int, cMP_MatchTrigger, fn_8020BE00, fn_800791C8, 8)
PARAM(int, cMP_MatchTrigger, fn_8020BE48, fn_80079068, 9)
PARAM(unsigned int, cMP_MatchTrigger, fn_8020BE90, fn_800791C8, 10)
PARAM(int, cMP_MatchTrigger, fn_8020BED8, fn_80079068, 11)
PARAM(unsigned int, cMP_MatchTrigger, fn_8020BF20, fn_800791C8, 12)
PARAM(int, cMP_MatchTrigger, fn_8020BF68, fn_80079068, 13)
PARAM(unsigned int, cMP_MatchTrigger, fn_8020BFB0, fn_800791C8, 14)
PARAM(int, cMP_MatchTrigger, fn_8020BFF8, fn_80079068, 15)
PARAM(unsigned int, cMP_MatchTrigger, fn_8020C040, fn_800791C8, 16)
PARAM(int, cMP_MatchTrigger, fn_8020C088, fn_80079068, 17)
PARAM(unsigned int, cMP_MatchTrigger, fn_8020C0D0, fn_800791C8, 18)
PARAM(int, cMP_MatchTrigger, fn_8020C118, fn_80079068, 19)
PARAM(unsigned int, cMP_MatchTrigger, fn_8020C160, fn_800791C8, 20)
PARAM(int, cMP_MatchTrigger, fn_8020C1A8, fn_80079068, 21)

cScript *fn_8020C1F0(register cCameraSet *self)
{
    return new cCameraSet;
}

PARAM(float, cCameraSet, fn_8020C244, fn_8007935C, 0)
}
