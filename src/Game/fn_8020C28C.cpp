// The region classes cRegionDamage, cRegionTrigger, cRegionSound, cRegionSuck, cRegionDefend and
// cRegionLightProbeSwap, with their parameter accessors (docs/story.md row 10).
// Pool read from 0x804A1BA0 (extern_pool).

inline int sn_return_decl(int a) { return a; }

struct cScript {
    char d[0x24];
    char *vptr; // +0x24
};

struct cScriptV { // cScript's virtual slots, for calls on self
    char d[0x24];
    virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13();
    virtual void s14(int h, int other, int value);
};

struct Ref8 {
    int unk0;
    int value; // +0x4
    Ref8() __asm__("fn_8046B530");
    void set(int v) __asm__("fn_8046B710");
    int handle() __asm__("fn_804425F8");
};

struct cRegionDamage : cScript { // 0x5C
    int unk28; // +0x28
    int unk2C; // +0x2C
    int fired; // +0x30
    int unk34; // +0x34
    int unk38; // +0x38
    int unk3C; // +0x3C
    int unk40; // +0x40
    int unk44; // +0x44
    int unk48; // +0x48
    int unk4C; // +0x4C
    int unk50; // +0x50
    Ref8 unk54; // +0x54
    cRegionDamage() __asm__("fn_80468BA0");
};

struct Vector {
    float x, y, z, w;
    Vector();
} __attribute__((aligned(8)));

struct EObj {
    char pad0[0x3AC];
};

struct Obj : EObj { // what fn_80085954 returns
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int a); // +0x30
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36();
    virtual void s37(int state, Vector *at, int b, float f, int c, int d, int e, int g); // +0x130
};

struct Act : Obj {};

struct cRegionTrigger : cScript { // 0x38
    int unk28; // +0x28
    int unk2C; // +0x2C
    int unk30; // +0x30
    int unk34; // +0x34
    cRegionTrigger() __asm__("fn_80468BF8");
};

struct cRegionSound : cScript { // 0x28
    cRegionSound() __asm__("fn_80468C44");
};

struct SuckBase {
    virtual ~SuckBase();
};

struct IntArray {
    int *data;        // +0x0
    int n;            // +0x4
    unsigned int cap; // +0x8
};

struct Suck : SuckBase { // 0x1C, cRegionSuck's pull object; name a guess
    IntArray list;  // +0x4, entity handles
    float strength; // +0x10
    int owner;      // +0x14
    int mode;       // +0x18, pull toward (0) or away from the path
    Suck(int owner, float strength) __asm__("fn_80210CF8");
    ~Suck();
};

struct cRegionSuck : cScript { // 0x30
    Suck *obj; // +0x28
    int unk2C; // +0x2C
    cRegionSuck() __asm__("fn_80468C90");
};

struct cRegionDefend : cScript { // 0x5C
    int count;           // +0x28
    char pad2C[0x10];
    unsigned int ids[8]; // +0x3C
    cRegionDefend() __asm__("fn_80468CDC");
};

struct cRegionLightProbeSwap : cScript { // 0x2C
    int on; // +0x28
    cRegionLightProbeSwap() __asm__("fn_80468D28");
};

struct Ent {
    int pad;
};

struct PathNode { // 0x30
    char pad0[0x10];
    Vector pos; // +0x10
    char pad20[0x10];
};

struct Path {
    char pad0[0x144];
    unsigned int count; // +0x144
    PathNode *nodes;    // +0x148
};

struct Scene {
    char pad0[0x130];
    int head; // +0x130
};

extern char lbl_80552110[]; // the game-state object G
extern char lbl_80571FA0[];
extern int lbl_8066C724;
extern char lbl_8054ED80[]; // the clashsp.nsc chronicle
extern char lbl_8057230C[];
extern char lbl_80572278[];
extern char lbl_805526EC[];
extern char lbl_8052F060[];
extern void *lbl_8066B834;
extern char lbl_805028D8[]; // Suck's vtable

extern "C" {
int fn_800797D4(cScript *self);
void fn_8007D404(cScript *self, float seconds, int kind, float a, float b, float c, float d, int e);
void fn_8046B710(Ref8 *self, int value);
void fn_8046B638(void *ev, int x);
int fn_8046CBB8(void *ev);
int fn_8046C96C(void *ev);
int fn_800809CC(void *ev);
int fn_80080A44(void *ev);
void fn_80082E90(void *ev, char *name, int a, int b);
unsigned int fn_8021057C(cRegionDamage *self);
int fn_80210234(cRegionDamage *self);
float fn_8021027C(cRegionDamage *self);
float fn_802102C4(cRegionDamage *self);
int fn_80210404(cRegionDamage *self);
int fn_8021044C(cRegionDamage *self);
float fn_802101EC(cRegionDamage *self);
int fn_802103BC(cRegionDamage *self);
int fn_80210524(cRegionDamage *self);
void fn_8020D31C(cRegionDamage *self, int x, int y);
void fn_801337F0(int a, int b);
void fn_8007B0AC(int a);
int fn_80426AB0(void *g);
int fn_80432844(void *g);
int fn_80432870(void *g);
int fn_80443D44(void *g, int player);
int fn_8043B31C(int x);
void fn_8046B838(void *g, int x);
void fn_80081918(int x);
int fn_80085AF0(int actor);
int fn_80085EEC(int actor);
int fn_80085F1C(int actor);
int fn_80085954(int actor);
int fn_80085928(int actor);
int fn_80085D3C(int actor);
void fn_80086CDC(int actor, int on);
int fn_800CD064(int x);
int fn_800CE1B0(int x);
int fn_800CC70C(int x);
int fn_800C9FD0(int x);
int fn_800CD0EC(int x);
int fn_800CDA20(int x);
void fn_800F9754(int x);
int fn_800B14C8(int x);
int fn_800B0C1C(int x);
int fn_800B13D8(int actor);
int fn_80171F8C(void);
void fn_800528EC(void);
char *fn_800ACD20(int actor, int id);
void fn_800578E4(char *cut, cRegionDamage *self, int b, int actor, int flags, int c, int d);
void fn_80432DF8(void *x);
void fn_800964D0(int x);
int stricmp(const char *a, const char *b);
char *fn_8021061C(cRegionDamage *self);
int fn_802105C4(cRegionDamage *self);
int fn_80210494(cRegionDamage *self);
void fn_8020E058(cRegionDamage *self);
void fn_8020D104(cRegionDamage *self);
void fn_80083428(void *ev, char *name);
void fn_8046B5A8(void *ev, int x);
void fn_80082F30(void *ev);
float fn_8007C594(void *ev, float dmg, int type, int kind, int src, unsigned int flags);
void fn_80133838(int a);
void fn_80114CC0(int a);
int fn_80080B34();
int fn_800817DC(int x);
void fn_800816A0(int x);
void fn_80081AD0(int x);
void *fn_804326B4(void *list);
int fn_80433E38(void *rec);
void fn_8043323C(void *list, int flag);
void fn_8046BBA0(void *ev, int x);
void fn_8046B680(void *ev, int x);
int fn_802104DC(cRegionDamage *self);
int fn_8021030C(cRegionDamage *self);
int fn_80210364(cRegionDamage *self);
int fn_800827D0(void *ev, int owner);
int fn_8046C8FC(void *ev);
unsigned int fn_8046C898(void *ev);
int fn_8009AC68(int actor);
void fn_8010E1B4(int actor);
int fn_8007C6D0(void *ev, float v);
int fn_8007C740(void *ev, int a, int b, Vector *pos, float f, int d);
void fn_80082E24(void *ev, char *name);
int fn_804425F8(Ref8 *p);
int fn_80080300(void *ev);
int fn_8009AD80(int actor);
void fn_80083018(Ref8 *p, char *name, int a, int b);
int fn_80080358(void *ev, int id);
void fn_80082440(void *ev, Vector *out);
int fn_80081190(void *ev);
int fn_80081E6C(void *ev);
int fn_800A4B1C(int a, int b, Vector *out);
Vector *fn_800B1724(int actor);
void fn_80429090(Vector *out, Vector *a, Vector *b, float s);
int fn_8008291C(void *ev, int i, Vector *out, Vector *out2, int b);
float fn_804290F8(Vector *a, Vector *b);
float *fn_8042FB28(Vector *v);
void fn_804354F4(float *dst, Vector *src);
Scene &fn_80430050(void *p);
int fn_800B1AC4(int node);
void fn_8046B6C8(void *ev, int x);
int fn_8046BD30(void *ev);
int fn_8007C034(void *ev);
int fn_80210AE4(cRegionTrigger *self);
int fn_80210BBC(cRegionTrigger *self);
int fn_80210664(cRegionTrigger *self);
int fn_80210A0C(cRegionTrigger *self);
int fn_80210A9C(cRegionTrigger *self);
float fn_80210B2C(cRegionTrigger *self);
int fn_80210A54(cRegionTrigger *self);
int fn_80210B74(cRegionTrigger *self);
int fn_800839B0(Vector *v);
void fn_8020EA3C(cRegionTrigger *self, int h, int kind);
void fn_80082AFC(void *ev, int h, int owner, int kind, float a, float b, float c, float d);
int fn_802106AC(cRegionTrigger *self);
int fn_802106F4(cRegionTrigger *self);
int fn_8021073C(cRegionTrigger *self);
int fn_80210784(cRegionTrigger *self);
int fn_802107CC(cRegionTrigger *self);
int fn_80210814(cRegionTrigger *self);
int fn_8021085C(cRegionTrigger *self);
int fn_802108A4(cRegionTrigger *self);
float fn_802108EC(cRegionTrigger *self);
float fn_80210934(cRegionTrigger *self);
float fn_8021097C(cRegionTrigger *self);
float fn_802109C4(cRegionTrigger *self);
char *fn_80210CB0(cRegionSound *self);
int fn_80210C68(cRegionSound *self);
unsigned int strlen(const char *s);
void fn_80081E08(int a);
void fn_80081E4C(char *name);
int fn_80081E28();
char *fn_80083FB8();
float fn_80210EE0(cRegionSuck *self);
int fn_80210E30(cRegionSuck *self);
int fn_80210F80(cRegionSuck *self);
int fn_80210F28(cRegionSuck *self);
void fn_8020F5DC(cRegionSuck *self);
void fn_8020F7D8(Suck *obj, int id);
void fn_80329B50(void *mgr, Suck *obj);
Ent &fn_800ACFA8R(int id) __asm__("fn_800ACFA8");
Ent *fn_800ACFA8(int id);
int fn_800B0C58(Ent *e);
int fn_800B14A0(Ent *e);
int fn_80085D6C(int actor);
void fn_8020F848(Suck *obj, int id);
int fn_80210E88(cRegionSuck *self);
int fn_80210FD8(cRegionSuck *self);
int fn_80210D70(Suck *obj);
void fn_8020F76C(cRegionSuck *self);
void *fn_80210DB0(Suck *obj);
int fn_8046D734(IntArray *a);
int *fn_8046D768(IntArray *a, int i);
void fn_80329AEC(void *mgr, Suck *obj);
int fn_8046D7AC(IntArray *a, const int *key);
void fn_8046D83C(IntArray *a, const int *v);
void fn_8046D8C8(IntArray *a, int i);
void fn_8042DC84(Vector *out, Vector *v);
Path *fn_800ACFA8P(int id) __asm__("fn_800ACFA8");
void fn_8020F8C0(Suck *self, Vector *pos, Path *path, Vector *out);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_80434040(Vector *v);
void fn_80435530(Vector *v, float s);
void fn_80066DC4(Ent *e, Vector *v, int a, int b, int c);
Vector *fn_800B1724E(Ent *e) __asm__("fn_800B1724");
int fn_802110C8(cRegionDefend *self);
unsigned int fn_80211120(cRegionDefend *self);
unsigned int fn_80211168(cRegionDefend *self);
unsigned int fn_802111B0(cRegionDefend *self);
unsigned int fn_802111F8(cRegionDefend *self);
int fn_80211240(cRegionDefend *self);
int fn_80211084(cRegionDefend *self);
void fn_8020FF40(cRegionDefend *self, int on);
void fn_80082AFCR(Ref8 *ev, int h, int owner, int kind, float a, float b, float c, float d) __asm__("fn_80082AFC");
void fn_8007B01C(unsigned int id, int a);
void fn_8007B064(unsigned int id, int a);
char *fn_802112EC(cRegionLightProbeSwap *self);
void fn_80081654(char *name, int a);
void fn_80081610(int a);
unsigned int fn_800791C8(cScript *self, unsigned int i);
int fn_80079068(cScript *self, unsigned int i);
float fn_8007935C(cScript *self, unsigned int i);
char *fn_800794FC(cScript *self, unsigned int i);
void fn_8046D92C(void *self);
void fn_8046D9B8(IntArray *self);
void fn_80030930(int id, int a, int b, int c, float f1, int d, int e, int f, int g, float f2);

cScript *fn_8020C28C(register cRegionDamage *self)
{
    return new cRegionDamage;
}

void fn_8020C2E0(register cRegionDamage *self) // slot 3
{
    self->unk2C = 0;
    self->fired = 0;
    self->unk34 = 0;
    self->unk38 = 0;
    self->unk3C = 0;
    self->unk40 = 0;
    self->unk44 = 0;
    self->unk48 = 0;
    self->unk4C = 0;
    self->unk50 = 0;
    lbl_8066C724 = 0;
}

void fn_8020C358(register cRegionDamage *self) // slot 31
{
    self->fired = 0;
}

void fn_8020C380(register cRegionDamage *self) // slot 5
{
    fn_8046B710(&self->unk54, fn_8021057C(self));
    if (fn_80210234(self)) {
        self->unk28 = 1;
        if (fn_8021027C(self) != 0.0f)
            fn_8007D404(self, fn_8021027C(self), 0x14, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        if (fn_80210404(self) == 1)
            fn_801337F0(fn_800797D4(self), 0);
        else if (fn_80210404(self) == 2)
            fn_8007B0AC(fn_800797D4(self));
        return;
    } else {
        self->unk28 = 0;
    }
    if (fn_802102C4(self) != 0.0f)
        fn_8007D404(self, fn_802102C4(self), 0xa, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_8020C508(register cRegionDamage *self, int a, int id, int c) // slot 14
{
    char ev[8];

    fn_8046B638(ev, id);
    if (!fn_8046CBB8(ev))
        return;
    if (fn_8021044C(self) > 0 && !fn_8046C96C(ev)) {
        int actor = fn_800809CC(ev);
        if (!actor)
            return;
        if (fn_8021044C(self) == 2 && !fn_80080A44(ev))
            return;
        if (fn_80426AB0(lbl_80552110) && lbl_8066C724) {
            fn_80081918(id);
            return;
        }
        if (fn_80432844(lbl_80552110) || fn_80432870(lbl_80552110)) {
            if (fn_80085AF0(actor)) {
                int other = fn_80443D44(lbl_80552110, 1 - fn_8043B31C(fn_80085AF0(actor)));
                if (other) {
                    if (fn_80085EEC(other) || fn_80085F1C(other))
                        return;
                }
            }
        }
        fn_80086CDC(actor, 1);
        if (fn_80085EEC(actor))
            return;
        int x = fn_80085954(actor);
        if (x && fn_800CD064(x) && fn_800CE1B0(x) && !fn_800CC70C(x)) {
            int rider = fn_800B14C8(fn_800C9FD0(x));
            if (rider && fn_800B0C1C(rider) && fn_80085928(rider) && fn_800CD0EC(fn_80085928(rider))) {
                if ((fn_80426AB0(lbl_80552110) && fn_80085D3C(rider)) || fn_80085AF0(rider)) {
                    fn_80086CDC(actor, 0);
                    self->unk4C = fn_800B13D8(actor);
                    actor = rider;
                    fn_80086CDC(actor, 1);
                }
            }
        }
        if (self->fired)
            return;
        self->fired = 1;
        if (self->unk4C)
            fn_80081918(self->unk4C);
        if (fn_80426AB0(lbl_80552110)) {
            int flags = 0x200210;
            float r = fn_80171F8C() * 4.6566128730773926e-10f;
            if (r < 0.33f)
                flags |= 0x80;
            else if (r < 0.66f)
                flags |= 0x100;
            int y = fn_80085928(actor);
            if (y && fn_800CDA20(y))
                fn_800F9754(y);
            fn_800528EC();
            fn_800578E4(fn_800ACD20(actor, 0xdc), self, 0, actor, flags, 0, 999);
            fn_80432DF8(lbl_80571FA0);
            self->unk48 = fn_800B13D8(actor);
            fn_8046B838(lbl_80552110, 0);
        } else {
            if (fn_80085AF0(fn_800809CC(ev)))
                fn_800964D0(fn_80085AF0(actor));
        }
    } else {
        if (fn_80080A44(ev)) {
            self->unk2C = 1;
            if (self->unk40 == 0)
                self->unk40 = id;
            else if (self->unk44 == 0)
                self->unk44 = id;
        }
        if (self->unk28 == 0)
            return;
        if (fn_802101EC(self) > 0.0f || (fn_802101EC(self) < 0.0f && fn_80210524(self))) {
            if (fn_802103BC(self) == 5)
                fn_80082E90(ev, "tripwireDamFX", 0xff, 0xff);
            fn_8020D31C(self, id, 0);
        }
    }
}

void fn_8020CAD0(register cRegionDamage *self, int a, int id, int c) // slot 15
{
    char ev[8];

    if (fn_8021044C(self))
        return;
    fn_8046B638(ev, id);
    if (!fn_8046CBB8(ev))
        return;
    if (fn_80080A44(ev)) {
        if (id == self->unk40) {
            self->unk38 = 0;
            self->unk40 = 0;
        } else if (id == self->unk44) {
            self->unk3C = 0;
            self->unk44 = 0;
        }
        if (self->unk40 == 0 && self->unk44 == 0)
            self->unk2C = 0;
        if (stricmp(fn_8021061C(self), "") && stricmp(fn_8021061C(self), "Invalid Param"))
            fn_80083428(ev, fn_8021061C(self));
    }
}

void fn_8020CC38(register cRegionDamage *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 0:
    case 2:
        self->unk28 = !self->unk28;
        if (self->unk28 == 1 && fn_80210404(self) == 1)
            fn_801337F0(fn_800797D4(self), 0);
        else if (self->unk28 == 0 && fn_80210404(self) == 1)
            fn_80133838(fn_800797D4(self));
        fn_8020E058(self);
        if (self->unk28 && self->unk2C)
            fn_8020D31C(self, self->unk40, 0);
        break;
    case 7:
        self->unk28 = 0;
        if (fn_80210404(self) == 1)
            fn_80133838(fn_800797D4(self));
        if (fn_80210494(self) > 0)
            fn_80114CC0(fn_800797D4(self));
        break;
    }
}

void fn_8020CDD0(register cRegionDamage *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    char ev[8];

    switch (kind) {
    case 0x1e:
        if (self->unk28) {
            fn_8020D31C(self, (int)a, 1);
        } else if (self->unk2C) {
            if (stricmp(fn_8021061C(self), "") && stricmp(fn_8021061C(self), "Invalid Param")) {
                fn_8046B5A8(ev, 0);
                if (self->unk40) {
                    self->unk38 = 0;
                    fn_8046B710((Ref8 *)ev, self->unk40);
                    fn_80083428(ev, fn_8021061C(self));
                } else if (self->unk44) {
                    self->unk3C = 0;
                    fn_8046B710((Ref8 *)ev, self->unk44);
                    fn_80083428(ev, fn_8021061C(self));
                }
            }
        }
        break;
    case 0x28:
        fn_8046B5A8(ev, e);
        fn_8007C594(ev, 9999.0f, 0, 0, 0, 0);
        break;
    case 10:
        fn_8007D404(self, fn_8021027C(self) + 0.1f, 0x14, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        self->unk28 = 1;
        if (self->unk2C)
            fn_8020D31C(self, fn_80080B34(), 0);
        break;
    case 0x14:
        fn_8007D404(self, fn_802102C4(self) + 0.1f, 0xa, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        self->unk28 = 0;
        break;
    }
}

void fn_8020D090(register cRegionDamage *self, int a, int kind, int c, float x, float y, float z) // slot 51
{
    switch (kind) {
    case 3:
    case 4:
        fn_8020D104(self);
        break;
    }
}

void fn_8020D104(register cRegionDamage *self)
{
    char tmp[8];

    if ((fn_80426AB0(lbl_80552110) != 0 && fn_802105C4(self) == 0) || (fn_802105C4(self) != 0 && self->unk48 == fn_80080B34())) {
        if (fn_80432870(lbl_80552110) != 0 || fn_80432844(lbl_80552110) != 0) {
            if (fn_800817DC(self->unk48) == 0) {
                fn_800816A0(self->unk48);
            }
        } else {
            fn_800816A0(self->unk48);
        }
        fn_80081AD0(self->unk48);
    } else if (fn_802105C4(self) != 0) {
        fn_8046B5A8(tmp, self->unk50);
        fn_80082F30(tmp);
    }
}

void fn_8020D228(register cRegionDamage *self, float t, unsigned int event, int c) // slot 54
{
    char ev[8];

    if (fn_802105C4(self) && self->unk48 != fn_80080B34())
        return;
    fn_8046B638(ev, self->unk48);
    if (fn_80080A44(ev))
        fn_8043323C(lbl_8057230C, 0);
    else if (fn_80433E38(fn_804326B4(lbl_8054ED80)))
        fn_8043323C(lbl_80572278, 1);
    else
        fn_8043323C(lbl_8057230C, 1);
}

void fn_8020D31C(register cRegionDamage *self, int id, int y)
{
    if (id == 0 && fn_80426AB0(lbl_80552110))
        return;
    char ev1[8];
    fn_8046B638(ev1, id);
    char ev2[8];
    fn_8046B638(ev2, self->unk44);
    char ev3[8];
    fn_8046BBA0(ev3, fn_800797D4(self));
    if (fn_802104DC(self) && fn_80080A44(ev1))
        return;
    if (y) {
        if ((id && !fn_800827D0(ev1, fn_800797D4(self))) || fn_8046C8FC(ev1))
            id = 0;
        if ((self->unk44 && !fn_800827D0(ev2, fn_800797D4(self))) || fn_8046C8FC(ev2))
            self->unk44 = 0;
        if (id == 0 && self->unk44 == 0)
            return;
    }
    float dmg = 0.0f;
    if (fn_802101EC(self) > 0.0f) {
        if (id) {
            if (fn_802105C4(self) && !self->unk34) {
                self->unk34 = 1;
                self->unk50 = id;
                char ev[8];
                fn_8046B638(ev, id);
                int actor = fn_800809CC(ev);
                if (!actor)
                    return;
                int flags = 0x200210;
                float r = fn_80171F8C() * 4.6566128730773926e-10f;
                if (r < 0.33f)
                    flags |= 0x80;
                else if (r < 0.66f)
                    flags |= 0x100;
                int veh = fn_80085928(actor);
                if (veh && fn_800CDA20(veh))
                    fn_800F9754(veh);
                int body = fn_8009AC68(actor);
                fn_800528EC();
                if (body == 0)
                    fn_800578E4("ro_male_1.cut", self, 0, actor, flags, 0, 999);
                else if (body == 2)
                    fn_800578E4("ro_brute_1.cut", self, 0, actor, flags, 0, 999);
                fn_800816A0(fn_80080B34());
            } else if (id != self->unk50) {
                dmg = fn_8007C594(ev1, fn_802101EC(self), fn_802103BC(self), 0, 0, 2);
            }
        }
        if (!fn_80426AB0(lbl_80552110) && self->unk44)
            fn_8007C594(ev2, fn_802101EC(self), fn_802103BC(self), 0, 0, 2);
    } else {
        if (id) {
            char ev[8];
            fn_8046B638(ev, id);
            int actor = fn_800809CC(ev);
            fn_8010E1B4(actor);
            fn_8007C6D0(ev1, fn_802101EC(self) < 0.0f ? -fn_802101EC(self) : fn_802101EC(self));
        }
        if (!fn_80426AB0(lbl_80552110) && self->unk44)
            fn_8007C6D0(ev2, fn_802101EC(self) < 0.0f ? -fn_802101EC(self) : fn_802101EC(self));
        if (stricmp(fn_8021061C(self), "") && stricmp(fn_8021061C(self), "Invalid Param")) {
            if (id && !self->unk38) {
                self->unk38 = 1;
                fn_80082E24(ev1, fn_8021061C(self));
            }
            if (self->unk44 && !self->unk3C) {
                self->unk3C = 1;
                fn_80082E24(ev2, fn_8021061C(self));
            }
        }
    }
    if (fn_802103BC(self) == 3) {
        fn_80082E90(ev1, "nycNRGWallDamFX", 0xff, 0xff);
        char ev[8];
        fn_8046B680(ev, fn_804425F8(&self->unk54));
        if (fn_80080300(ev) && fn_8009AD80(fn_80080300(ev)))
            fn_80083018(&self->unk54, "aerogelHit", 0xff, 0xff);
        else
            fn_80083018(&self->unk54, "ffRoekelHit", 0xff, 0xff);
    }
    if (dmg > 0.0f)
        fn_80080358(ev3, 0x88);
    if (fn_802103BC(self) == 2)
        fn_80082E90(ev1, "victimBurnStd", 0xff, 0xff);
    Vector pos;
    Vector dir;
    fn_80082440(ev3, &pos);
    if (fn_80080A44(ev1) || fn_8021030C(self)) {
        int kind = fn_80210494(self);
        int from = fn_80081190(ev3);
        int to = fn_80081E6C(ev1);
        if (kind > 0 && !fn_80210364(self)) {
            if (from && to && fn_800A4B1C(from, to, &dir))
                fn_80429090(&pos, fn_800B1724(to), &dir, -1.0f);
        } else if (kind > 0) {
            if (fn_800809CC(ev1) && fn_80080A44(ev1) && (!stricmp(lbl_805526EC, "Ironman_1") || !stricmp(lbl_805526EC, "Venom_1"))) {
                int x = fn_80085954(fn_800809CC(ev1));
                if (x && fn_800CD064(x) && fn_800CE1B0(x)) {
                    ((Act *)fn_80085954(fn_800809CC(ev1)))->s5(2);
                    if (fn_800C9FD0(x) && fn_800B0C1C(fn_800C9FD0(x))) {
                        int rider = fn_800B14C8(fn_800C9FD0(x));
                        ((Act *)fn_80085954(rider))->s5(2);
                        fn_80030930(rider, 0, 0, 0, 9999.0f, 0, 0, 0, 1, 0.0f);
                    }
                }
            } else if (fn_8046C898(ev3) > 1) {
                Vector a;
                Vector b;
                if (from && to && fn_8008291C(ev3, 1, &a, 0, 0) && fn_8008291C(ev3, 2, &b, 0, 0)) {
                    if (fn_804290F8(fn_800B1724(to), &a) < fn_804290F8(fn_800B1724(to), &b))
                        fn_804354F4(fn_8042FB28(&pos), &b);
                    else
                        fn_804354F4(fn_8042FB28(&pos), &a);
                }
            }
        }
        switch (kind) {
        case 0:
            break;
        case 1:
            if (id)
                fn_8007C740(ev1, 0x72, 1, &pos, 1.0f, 1);
            if (self->unk44)
                fn_8007C740(ev2, 0x72, 1, &pos, 1.0f, 1);
            break;
        case 2:
            if (id)
                fn_8007C740(ev1, 0x6c, 1, &pos, 1.0f, 1);
            if (self->unk44)
                fn_8007C740(ev2, 0x6c, 1, &pos, 1.0f, 1);
            break;
        case 3:
            if (id)
                fn_8007C740(ev1, 0x6f, 1, &pos, 1.0f, 1);
            if (self->unk44)
                fn_8007C740(ev2, 0x6f, 1, &pos, 1.0f, 1);
            break;
        }
    }
    fn_8007D404(self, 0.25f, 0x1e, (float)(unsigned int)id, 0.0f, 0.0f, 0.0f, 0);
}

void fn_8020E058(register cRegionDamage *self)
{
    int node;
    char ev[8];

    fn_8046B638(ev, 0);
    for (node = fn_80430050(lbl_8052F060).head; node; node = fn_800B1AC4(node)) {
        fn_8046B710((Ref8 *)ev, fn_800B13D8(node));
        if (fn_800809CC(ev) && fn_8046C96C(ev) && fn_800827D0(ev, fn_800797D4(self))) {
            Vector pos;
            char owner[8];
            fn_8046B6C8(owner, fn_800797D4(self));
            fn_80082440(owner, &pos);
            ((Obj *)fn_80085954(fn_800809CC(ev)))->s37(0x6f, &pos, 1, 1.0f, 0, 0, 1, 0);
            fn_8007D404(self, 0.5f, 0x28, 0.0f, 0.0f, 0.0f, 0.0f, fn_804425F8((Ref8 *)ev));
        }
    }
}

inline int sn_return_decl2(int a) { return a; }

cScript *fn_8020E248(register cRegionTrigger *self)
{
    return new cRegionTrigger;
}

void fn_8020E29C(register cRegionTrigger *self) // slot 3
{
    self->unk28 = 0;
    self->unk30 = 0;
    self->unk34 = 0;
}

void fn_8020E2D4(register cRegionTrigger *self) // slot 4
{
    if (fn_80210AE4(self))
        self->unk2C = 0;
    else
        self->unk2C = 1;
}

void fn_8020E32C(register cRegionTrigger *self, int a, int id, int c) // slot 14
{
    char ev[8];

    fn_8046B638(ev, id);
    if (fn_80080A44(ev))
        self->unk30 = 1;
    if (!self->unk2C)
        return;
    if (fn_80210BBC(self))
        return;
    int h = fn_80081E6C(ev);
    if (!h)
        return;
    if (fn_80210664(self) == 0 && (fn_80080A44(ev) || !fn_8046BD30(ev)))
        return;
    if (fn_80210664(self) == 1 && !fn_80080A44(ev))
        return;
    if (fn_80210664(self) == 2 && !fn_8046BD30(ev))
        return;
    int actor = fn_8007C034(ev);
    if (fn_80085EEC(actor))
        return;
    if (!fn_80210A0C(self))
        return;
    if (fn_80210A9C(self)) {
        if (self->unk28)
            return;
        else
            self->unk28 = 1;
    }
    fn_8007D404(self, fn_80210B2C(self), 0xa, 0.0f, 0.0f, 0.0f, 0.0f, id);
}

void fn_8020E544(register cRegionTrigger *self, int a, int id, int c) // slot 15
{
    char ev[8];

    fn_8046B638(ev, id);
    if (fn_80080A44(ev))
        self->unk30 = 0;
    if (!self->unk2C)
        return;
    if (fn_80210BBC(self) && !fn_80080A44(ev))
        return;
    if (fn_80210664(self) == 0 && (fn_80080A44(ev) || !fn_8046BD30(ev)))
        return;
    if (fn_80210664(self) == 1 && !fn_80080A44(ev))
        return;
    if (fn_80210664(self) == 2 && !fn_8046BD30(ev))
        return;
    if (!fn_80210A54(self))
        return;
    if (fn_80210A9C(self)) {
        if (self->unk28)
            return;
        else
            self->unk28 = 1;
    }
    char owner[8];
    fn_8046B6C8(owner, a);
    Vector p1;
    Vector p2;
    fn_8008291C(owner, 1, &p2, &p1, 0);
    if (!fn_80210BBC(self)) {
        fn_8007D404(self, fn_80210B2C(self), 0x14, 0.0f, 0.0f, 0.0f, 0.0f, id);
    } else if (!self->unk34 && fn_800839B0(&p1)) {
        self->unk34 = 1;
        fn_8007D404(self, fn_80210B2C(self), 0x14, 0.0f, 0.0f, 0.0f, 0.0f, id);
    } else if (self->unk34 && !fn_800839B0(&p1)) {
        self->unk34 = 0;
        fn_8007D404(self, fn_80210B2C(self), 0x14, 0.0f, 0.0f, 0.0f, 0.0f, id);
    }
}

void fn_8020E864(register cRegionTrigger *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 0:
    case 13:
        if (!self->unk2C)
            self->unk2C = 1;
        else
            self->unk2C = 0;
        if (self->unk30)
            ((cScriptV *)self)->s14(fn_800797D4(self), fn_80080B34(), 0);
        break;
    case 7:
        self->unk2C = 0;
        break;
    }
}

void fn_8020E970(register cRegionTrigger *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    if (fn_80210B74(self) == 13) {
        if (kind == 10)
            fn_8020EA3C(self, e, 2);
        else if (kind == 20)
            fn_8020EA3C(self, e, 3);
    } else {
        fn_8020EA3C(self, e, fn_80210B74(self));
    }
}

#define SEND_TARGET(get)                                                                              \
    if (get(self)) {                                                                                  \
        fn_8046B710((Ref8 *)ev, get(self));                                                           \
        fn_80082AFC(ev, h, fn_800797D4(self), kind, fn_802108EC(self), fn_80210934(self), fn_8021097C(self), \
                    fn_802109C4(self));                                                               \
    }

void fn_8020EA3C(register cRegionTrigger *self, int h, int kind)
{
    char ev[8];

    fn_8046B6C8(ev, h);
    SEND_TARGET(fn_802106AC)
    SEND_TARGET(fn_802106F4)
    SEND_TARGET(fn_8021073C)
    SEND_TARGET(fn_80210784)
    SEND_TARGET(fn_802107CC)
    SEND_TARGET(fn_80210814)
    SEND_TARGET(fn_8021085C)
    SEND_TARGET(fn_802108A4)
}

void fn_8020EF44(register cRegionSound *self, int a, int id, int c) // slot 14
{
    char ev[8];

    fn_8046B638(ev, id);
    if (!fn_80080A44(ev))
        return;
    char *name = fn_80210CB0(self);
    if (fn_80210C68(self) >= 0)
        fn_80081E08(fn_80210C68(self));
    if (name && strlen(name))
        fn_80081E4C(name);
}

void fn_8020F014(register cRegionSound *self, int a, int id, int c) // slot 15
{
    char ev[8];

    fn_8046B638(ev, id);
    if (!fn_80080A44(ev))
        return;
    char *name = fn_80210CB0(self);
    if (fn_80210C68(self) >= 0)
        fn_80081E08(fn_80081E28());
    if (name && strlen(name))
        fn_80081E4C(fn_80083FB8());
}

void fn_8020F0E8(register cRegionSuck *self) // slot 3
{
    self->obj = new Suck(fn_800797D4(self), fn_80210EE0(self));
    self->unk2C = 0;
}

void fn_8020F164(register cRegionSuck *self) // slot 4
{
    if (!self->obj)
        return;
    if (fn_80210E30(self))
        fn_8020F5DC(self);
}

void fn_8020F1C8(register cRegionSuck *self) // slot 6
{
    if (self->obj) {
        if (self->unk2C)
            fn_80329B50(lbl_8066B834, self->obj);
        delete self->obj;
        self->obj = 0;
    }
}

void fn_8020F274(register cRegionSuck *self, int a, int id, int c) // slot 14
{
    if (!self->obj)
        return;
    if (fn_80210F80(self)) {
        Ent &e = fn_800ACFA8R(id);
        if (&e && fn_800B0C58(&e))
            return;
    }
    if (self->unk2C && fn_80210F28(self)) {
        Ent *e = fn_800ACFA8(id);
        if (e && fn_800B0C58(e) && fn_80085D6C(fn_800B14A0(e))) {
            Ent *o = fn_800ACFA8(fn_800797D4(self));
            if (o)
                fn_80030930(fn_800B14A0(e), (int)o, 3, 0, 0.0f, 0, 0, 0, 1, 0.0f);
        }
    }
    fn_8020F7D8(self->obj, id);
}

void fn_8020F3F4(register cRegionSuck *self, int a, int id, int c) // slot 15
{
    if (!self->obj)
        return;
    fn_8020F848(self->obj, id);
}

void fn_8020F454(register cRegionSuck *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (!self->obj)
        return;
    switch (kind) {
    case 0:
        if (fn_80210E88(self)) {
            if (self->unk2C)
                fn_8020F76C(self);
            else
                fn_8020F5DC(self);
        }
        if (fn_80210FD8(self))
            fn_80210D70(self->obj);
        break;
    case 999:
        fn_8020F5DC(self);
        fn_8007D404(self, x, 0xa, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
}

void fn_8020F568(register cRegionSuck *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_8020F76C(self);
        break;
    }
}

void fn_8020F5DC(register cRegionSuck *self)
{
    if (!self->obj)
        return;
    if (self->unk2C)
        return;
    if (fn_80210F28(self)) {
        Ent *o = fn_800ACFA8(fn_800797D4(self));
        IntArray *list = (IntArray *)fn_80210DB0(self->obj);
        Ent *e;
        int i;
        for (i = 0; i < fn_8046D734(list); i++) {
            e = fn_800ACFA8(*fn_8046D768(list, i));
            if (!e)
                continue;
            if (!fn_800B0C58(e))
                continue;
            if (o && fn_80085D6C(fn_800B14A0(e)))
                fn_80030930(fn_800B14A0(e), (int)o, 3, 0, 0.0f, 0, 0, 0, 1, 0.0f);
        }
    }
    fn_80329AEC(lbl_8066B834, self->obj);
    self->unk2C = 1;
}

void fn_8020F76C(register cRegionSuck *self)
{
    if (!self->obj)
        return;
    if (!self->unk2C)
        return;
    fn_80329B50(lbl_8066B834, self->obj);
    self->unk2C = 0;
}

void fn_8020F7D8(register Suck *self, int id)
{
    if (fn_8046D7AC(&self->list, &id) != -1)
        return;
    fn_8046D83C(&self->list, &id);
}

void fn_8020F848(register Suck *self, int id)
{
    int i = fn_8046D7AC(&self->list, &id);
    if (i == -1)
        return;
    fn_8046D8C8(&self->list, i);
}

void fn_8020F8C0(register Suck *self, Vector *pos, Path *path, Vector *out)
{
    float d;
    float bestD;
    unsigned short best;
    unsigned short i;

    best = 1;
    for (i = 1; i < path->count; i++) {
        d = fn_804290F8(pos, &path->nodes[i].pos);
        if (i == 1 || d < bestD) {
            bestD = d;
            best = i;
        }
    }
    fn_8042DC84(out, &path->nodes[best].pos);
}

void fn_8020F9D0(register Suck *self, int a, int b)
{
    Path *path = fn_800ACFA8P(self->owner);
    Ent *e;

    if (!path || !path->count)
        return;
    Vector pull;
    Vector at;
    int i;
    for (i = 0; i < fn_8046D734(&self->list); i++) {
        e = fn_800ACFA8(*fn_8046D768(&self->list, i));
        if (!e)
            continue;
        fn_8020F8C0(self, fn_800B1724E(e), path, &at);
        if (!self->mode)
            fn_80429038(&pull, &at, fn_800B1724E(e));
        else
            fn_80429038(&pull, fn_800B1724E(e), &at);
        fn_80435530(&pull, self->strength / fn_80434040(&pull));
        fn_80066DC4(e, &pull, 0, 1, 0);
    }
}

void fn_8020FB88(register cRegionDefend *self) // slot 3
{
    self->count = 0;
}

#define DEFEND_SEND(i)                                                                              \
    if (self->ids[i]) {                                                                             \
        ev.set(self->ids[i]);                                                                       \
        fn_80082AFCR(&ev, ev.handle(), fn_800797D4(self), 999, 0.0f, 0.0f, 0.0f, 0.0f);            \
    }

void fn_8020FBB8(register cRegionDefend *self) // slot 5
{
    if (!fn_802110C8(self))
        return;
    self->ids[0] = fn_80211120(self);
    self->ids[1] = fn_80211168(self);
    self->ids[2] = fn_802111B0(self);
    self->ids[3] = fn_802111F8(self);
    if (!fn_80211240(self)) {
        fn_8020FF40(self, 1);
        return;
    }
    Ref8 ev;
    DEFEND_SEND(0)
    DEFEND_SEND(1)
    DEFEND_SEND(2)
    DEFEND_SEND(3)
}

void fn_8020FE04(register cRegionDefend *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 0:
        fn_8020FF40(self, 1);
        break;
    case 7:
        fn_8020FF40(self, 0);
        break;
    case 999:
        if (self->count <= 7) {
            self->ids[self->count] = (unsigned int)x;
            self->count++;
            fn_8020FF40(self, 1);
        }
        break;
    }
}

void fn_8020FF40(register cRegionDefend *self, int on)
{
    int i;

    for (i = 0; i <= 7; i++) {
        if (!self->ids[i])
            break;
        if (on)
            fn_8007B01C(self->ids[i], fn_80211084(self));
        else
            fn_8007B064(self->ids[i], fn_80211084(self));
    }
}

void fn_80210024(register cRegionLightProbeSwap *self) // slot 4
{
    self->on = 0;
    fn_80081654(fn_802112EC(self), 5);
}

void fn_8021007C(register cRegionLightProbeSwap *self, int a, int id, int c) // slot 15
{
    char ev[8];

    fn_8046B638(ev, id);
    if (!fn_80080A44(ev))
        return;
    char owner[8];
    fn_8046B6C8(owner, a);
    Vector p1;
    Vector p2;
    fn_8008291C(owner, 1, &p2, &p1, 0);
    if (fn_800839B0(&p1))
        fn_80081610(5);
    else
        fn_80081610(0);
}

void fn_80210164(register cRegionLightProbeSwap *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (!self->on) {
        self->on = 1;
        fn_80081610(5);
    } else {
        self->on = 0;
        fn_80081610(0);
    }
}

inline int sn_return_decl3(int a) { return a; }

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

PARAM(float, cRegionDamage, fn_802101EC, fn_8007935C, 0)
PARAM(int, cRegionDamage, fn_80210234, fn_80079068, 1)
PARAM(float, cRegionDamage, fn_8021027C, fn_8007935C, 2)
PARAM(float, cRegionDamage, fn_802102C4, fn_8007935C, 3)
FLAG(cRegionDamage, fn_8021030C, fn_80079068, 4)
FLAG(cRegionDamage, fn_80210364, fn_80079068, 5)
PARAM(int, cRegionDamage, fn_802103BC, fn_80079068, 6)
PARAM(int, cRegionDamage, fn_80210404, fn_80079068, 7)
PARAM(int, cRegionDamage, fn_8021044C, fn_80079068, 8)
PARAM(int, cRegionDamage, fn_80210494, fn_80079068, 9)
PARAM(int, cRegionDamage, fn_802104DC, fn_80079068, 10)
FLAG(cRegionDamage, fn_80210524, fn_80079068, 11)
PARAM(unsigned int, cRegionDamage, fn_8021057C, fn_800791C8, 12)
FLAG(cRegionDamage, fn_802105C4, fn_80079068, 13)
PARAM(char *, cRegionDamage, fn_8021061C, fn_800794FC, 14)

PARAM(int, cRegionTrigger, fn_80210664, fn_80079068, 0)
PARAM(int, cRegionTrigger, fn_802106AC, fn_800791C8, 1)
PARAM(int, cRegionTrigger, fn_802106F4, fn_800791C8, 2)
PARAM(int, cRegionTrigger, fn_8021073C, fn_800791C8, 3)
PARAM(int, cRegionTrigger, fn_80210784, fn_800791C8, 4)
PARAM(int, cRegionTrigger, fn_802107CC, fn_800791C8, 5)
PARAM(int, cRegionTrigger, fn_80210814, fn_800791C8, 6)
PARAM(int, cRegionTrigger, fn_8021085C, fn_800791C8, 7)
PARAM(int, cRegionTrigger, fn_802108A4, fn_800791C8, 8)
PARAM(float, cRegionTrigger, fn_802108EC, fn_8007935C, 9)
PARAM(float, cRegionTrigger, fn_80210934, fn_8007935C, 10)
PARAM(float, cRegionTrigger, fn_8021097C, fn_8007935C, 11)
PARAM(float, cRegionTrigger, fn_802109C4, fn_8007935C, 12)
PARAM(int, cRegionTrigger, fn_80210A0C, fn_80079068, 13)
PARAM(int, cRegionTrigger, fn_80210A54, fn_80079068, 14)
PARAM(int, cRegionTrigger, fn_80210A9C, fn_80079068, 15)
PARAM(int, cRegionTrigger, fn_80210AE4, fn_80079068, 16)
PARAM(float, cRegionTrigger, fn_80210B2C, fn_8007935C, 17)
PARAM(int, cRegionTrigger, fn_80210B74, fn_80079068, 18)
FLAG(cRegionTrigger, fn_80210BBC, fn_80079068, 19)

cScript *fn_80210C14(register cRegionSound *self)
{
    return new cRegionSound;
}

PARAM(int, cRegionSound, fn_80210C68, fn_80079068, 0)
PARAM(char *, cRegionSound, fn_80210CB0, fn_800794FC, 1)

Suck *fn_80210CF8(register Suck *self, register int owner, register float strength)
{
    fn_8046D92C(self);
    *(char **)self = lbl_805028D8;
    fn_8046D9B8(&self->list);
    self->owner = owner;
    self->strength = strength;
    self->mode = 0;
    return self;
}

int fn_80210D70(register Suck *self)
{
    return self->mode = !self->mode;
}

void *fn_80210DB0(register Suck *self)
{
    return &self->list;
}

cScript *fn_80210DDC(register cRegionSuck *self)
{
    return new cRegionSuck;
}

FLAG(cRegionSuck, fn_80210E30, fn_80079068, 0)
FLAG(cRegionSuck, fn_80210E88, fn_80079068, 1)
PARAM(float, cRegionSuck, fn_80210EE0, fn_8007935C, 2)
FLAG(cRegionSuck, fn_80210F28, fn_80079068, 3)
FLAG(cRegionSuck, fn_80210F80, fn_80079068, 4)
FLAG(cRegionSuck, fn_80210FD8, fn_80079068, 5)

cScript *fn_80211030(register cRegionDefend *self)
{
    return new cRegionDefend;
}

int fn_80211084(register cRegionDefend *self)
{
    return fn_800797D4(self);
}

FLAG(cRegionDefend, fn_802110C8, fn_80079068, 0)
PARAM(unsigned int, cRegionDefend, fn_80211120, fn_800791C8, 1)
PARAM(unsigned int, cRegionDefend, fn_80211168, fn_800791C8, 2)
PARAM(unsigned int, cRegionDefend, fn_802111B0, fn_800791C8, 3)
PARAM(unsigned int, cRegionDefend, fn_802111F8, fn_800791C8, 4)
FLAG(cRegionDefend, fn_80211240, fn_800791C8, 5)

cScript *fn_80211298(register cRegionLightProbeSwap *self)
{
    return new cRegionLightProbeSwap;
}

PARAM(char *, cRegionLightProbeSwap, fn_802112EC, fn_800794FC, 0)
}
