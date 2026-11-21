// The Roekel Facility classes cRoekelFacility_StormBoss, _ThingBoss, _RockBomb, _BlastDoor, _RoekelBoss, _PlasmaMine and _Lasers (docs/story.md row 19).
// Pool read from 0x804A06A8 (extern_pool).

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

struct SObj {
    int unk0;
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

struct Scene {
    char pad0[0x130];
    int head; // +0x130
};

struct cRoekelFacility_StormBoss : cScript { // 0xA8
    Ref8 boss;      // +0x28
    Ref8 player;    // +0x30
    Ref8 r38;       // +0x38, param 0
    Ref8 core;      // +0x40
    int f48;        // +0x48
    int f4C;        // +0x4C
    int f50;        // +0x50
    int f54;        // +0x54
    int f58;        // +0x58
    int done;       // +0x5C
    int bossHit;    // +0x60
    int playerHit;  // +0x64
    Mat m68;        // +0x68
    cRoekelFacility_StormBoss() __asm__("fn_8046AB7C");
};

struct cRoekelFacility_ThingBoss : cScript { // 0x130
    Ref8 boss;      // +0x28
    Ref8 player;    // +0x30
    Ref8 r38[12];   // +0x38, params 0-11
    Ref8 r98;       // +0x98, param 14
    Ref8 core;      // +0xA0
    int fA8;        // +0xA8
    int phase;      // +0xAC
    int fB0;        // +0xB0
    int fB4;        // +0xB4
    int fB8;        // +0xB8
    int fBC;        // +0xBC
    int fC0;        // +0xC0
    int done;       // +0xC4
    int bossHit;    // +0xC8
    int playerHit;  // +0xCC
    Vector vD0;     // +0xD0
    Vector target;  // +0xE0
    Mat mF0;        // +0xF0
    cRoekelFacility_ThingBoss() __asm__("fn_8046AC0C");
};

struct cRoekelFacility_RockBomb : cScript { // 0xA0
    Ref8 obj;       // +0x28
    Ref8 thing;     // +0x30
    char pad38[8];
    Vector aim;     // +0x40
    Mat m50;        // +0x50
    int dust;       // +0x90
    char pad94[0xC];
    cRoekelFacility_RockBomb() __asm__("fn_8046AD44");
};

struct cRoekelFacility_BlastDoor : cScript { // 0x40
    Ref8 door;      // +0x28
    int open;       // +0x30
    int done;       // +0x34
    int f38;        // +0x38
    int ms;         // +0x3C
    cRoekelFacility_BlastDoor() __asm__("fn_8046ADC8");
};

struct cRoekelFacility_RoekelBoss : cScript { // 0x110
    Ref8 boss;      // +0x28
    Ref8 r30;       // +0x30
    Ref8 r38;       // +0x38
    Ref8 player;    // +0x40
    Ref8 r48;       // +0x48, param 0
    Ref8 r50;       // +0x50, param 1
    Ref8 r58;       // +0x58, param 2
    Ref8 core;      // +0x60
    Mat m68;        // +0x68
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
    int fD0;        // +0xD0
    char padD4[0xC];
    Vector vE0;     // +0xE0
    Vector vF0;     // +0xF0
    char pad100[0x10];
    cRoekelFacility_RoekelBoss() __asm__("fn_8046AE24");
};

struct cRoekelFacility_PlasmaMine : cScript { // 0x70
    Ref8 mine;      // +0x28
    Ref8 r30;       // +0x30, param 1
    Ref8 player;    // +0x38
    int armed;      // +0x40
    int sparks;     // +0x44
    char pad48[8];
    Vector pos;     // +0x50
    Vector at;      // +0x60
    cRoekelFacility_PlasmaMine() __asm__("fn_8046AF04");
};

struct cRoekelFacility_Lasers : cScript { // 0x30
    int count;      // +0x28
    float delay;    // +0x2C
    cRoekelFacility_Lasers() __asm__("fn_8046AF90");
};

extern char lbl_8052F060[];
extern char lbl_80552110[];
extern char lbl_80572278[];
extern char lbl_8057230C[];
extern int lbl_8066C71C;
extern int lbl_8066C724;

extern "C" {

int Script_GetOwner(cScript *self);
unsigned int Script_GetParamUInt(cScript *self, unsigned int i);
int Script_GetParamInt(cScript *self, unsigned int i);
char *Script_GetParamString(cScript *self, unsigned int i);
void Script_QueueMessage(cScript *self, float seconds, int kind, float a, float b, float c, float d, int e);
void Script_QueueMessageMs(cScript *self, int ms, int kind, float a, float b, float c, float d, int e);
int Script_CancelMessages(cScript *self, unsigned char kind);
int fn_8007D8B0(cScript *self);
int Script_LinkEntity(cScript *script, int handle, int value);
int fn_80080B34();
int fn_804425F8(void *ev);
void fn_8046B5A8(void *ev, int x);
void fn_8046B5F0(void *ev, int x);
void fn_8046B6C8(void *ev, int x);
void fn_8046B710(void *ev, int x);
void fn_8046B838(void *g, int x);
int fn_8007C034(void *ev);
SObj *fn_80081E6C(void *ev);
SObj *fn_80080EFC(void *ev);
int fn_8009B04C(int actor);
SBody *fn_800B24AC(SObj &o);
HkRef fn_80317960(SBodyBase &body);
void fn_8006645C(SObj *o, int a);
void fn_80066604(SObj *o);
void fn_80066794(SObj *o, int v);
int fn_80393D0C(SObj *o, char *name, int a, int b);
void *fn_80085928(void *p);
void fn_800CD6C4(void *c, int on);
void Script_TriggerEntity(void *ev, int h, int owner, int kind, float a, float b, float c, float d);
void fn_80082440(void *ev, Vector *out);
void fn_800824AC(void *ev, Vector *at);
void fn_800826A8(void *ev, Mat *m);
void fn_800825D0(void *ev, Mat *m);
void fn_80082E90(void *ev, char *name, int a, int b);
void fn_800820A0(void *ev, int a);
void fn_80082014(void *ev, int v);
void fn_80081F8C(void *ev, int v);
void fn_80080928(void *ev, int a);
void fn_80082124(void *ev);
void fn_80082F30(void *ev);
int fn_80082190(void *ev, char *name);
int fn_8008046C(void *ev, int id, float f);
int fn_80080358(void *ev, int id);
void fn_800810DC(void *ev, float f, int a, int b, int c, int d);
float fn_8007C594(void *ev, float dmg, int type, int kind, int src, unsigned int flags);
void fn_8007C740(void *ev, int id, int a, int b, float f, int c);
void fn_800838E0(Vector *at);
int fn_80083734(char *name);
float fn_8007C0AC(void *ev);
float fn_8007C244(void *ev);
float fn_8007C2AC(void *ev);
float fn_8007C3EC(void *ev);
float fn_8007C52C(void *ev);
void fn_8007C454(void *ev, float v);
void fn_8007C6D0(void *ev, float v);
void fn_8007A448(int h);
void fn_8007A4FC(int h);
void fn_8007A738(int h, Vector *to);
void fn_8007B0EC(int h, int a, int b, int c);
void fn_8007B288(int h);
void fn_8007B2E8(int h, int which, float v);
void fn_8007B618(int h, int on);
void fn_8007BA24(int h, int state);
void fn_8007BAA0(int h);
void fn_8007BB24(int h);
void fn_8007BCC8(int h, int on);
void fn_8007BD7C(int h);
int fn_8007BEA8(int h);
void fn_8007BF40(int h, int a, int value, int b);
float fn_804290F8(void *a, void *b);
int fn_80171F8C();
Scene *fn_80430050(void *p);
int fn_800B0C58(int node);
int fn_800B14A0(int node);
int fn_8008582C(int id);
int fn_800B13D8(int node);
int fn_800B1AC4(int node);
void fn_80081C68();
void fn_80081C94();
void fn_80081CC4();
int fn_80081B40(int h);
int fn_80081A54(int h);
void fn_80081918(int h);
void fn_800816A0(int h);
int fn_80081BD4(int h);
void fn_8043323C(void *p, int on);

void fn_801E5088(cRoekelFacility_StormBoss *self);
void fn_801E5260(cRoekelFacility_StormBoss *self);
void fn_801E5358(cRoekelFacility_StormBoss *self);
void fn_801E5408(cRoekelFacility_StormBoss *self);
void fn_801E54D0(cRoekelFacility_StormBoss *self);
void fn_801E5540(cRoekelFacility_StormBoss *self);
unsigned int fn_801E9AC0(cRoekelFacility_StormBoss *self);
unsigned int fn_801E9B08(cRoekelFacility_StormBoss *self);
unsigned int fn_801E9B50(cRoekelFacility_StormBoss *self);
void fn_801E61C8(cRoekelFacility_ThingBoss *self);
void fn_801E63E8(cRoekelFacility_ThingBoss *self);
void fn_801E6544(cRoekelFacility_ThingBoss *self);
void fn_801E6CF8(cRoekelFacility_ThingBoss *self);
void fn_801E6DA8(cRoekelFacility_ThingBoss *self);
void fn_801E6FCC(cRoekelFacility_ThingBoss *self);
void fn_801E703C(cRoekelFacility_ThingBoss *self);
unsigned int fn_801E9BEC(cRoekelFacility_ThingBoss *self);
unsigned int fn_801E9C34(cRoekelFacility_ThingBoss *self);
unsigned int fn_801E9C7C(cRoekelFacility_ThingBoss *self);
unsigned int fn_801E9CC4(cRoekelFacility_ThingBoss *self);
unsigned int fn_801E9D0C(cRoekelFacility_ThingBoss *self);
unsigned int fn_801E9D54(cRoekelFacility_ThingBoss *self);
unsigned int fn_801E9D9C(cRoekelFacility_ThingBoss *self);
unsigned int fn_801E9DE4(cRoekelFacility_ThingBoss *self);
unsigned int fn_801E9E2C(cRoekelFacility_ThingBoss *self);
unsigned int fn_801E9E74(cRoekelFacility_ThingBoss *self);
unsigned int fn_801E9EBC(cRoekelFacility_ThingBoss *self);
unsigned int fn_801E9F04(cRoekelFacility_ThingBoss *self);
unsigned int fn_801E9F4C(cRoekelFacility_ThingBoss *self);
unsigned int fn_801E9F94(cRoekelFacility_ThingBoss *self);
unsigned int fn_801E9FDC(cRoekelFacility_ThingBoss *self);
unsigned int fn_801EA024(cRoekelFacility_ThingBoss *self);
unsigned int fn_801EA06C(cRoekelFacility_ThingBoss *self);
unsigned int fn_801EA0B4(cRoekelFacility_ThingBoss *self);
unsigned int fn_801EA0FC(cRoekelFacility_ThingBoss *self);
void fn_801E7824(cRoekelFacility_RockBomb *self);
int fn_801EA1EC(cRoekelFacility_BlastDoor *self);
int fn_801EA234(cRoekelFacility_BlastDoor *self);
void fn_801E856C(cRoekelFacility_RoekelBoss *self);
void fn_801E872C(cRoekelFacility_RoekelBoss *self);
void fn_801E8970(cRoekelFacility_RoekelBoss *self);
void fn_801E8AC8(cRoekelFacility_RoekelBoss *self);
void fn_801E8B7C(cRoekelFacility_RoekelBoss *self);
void fn_801E8BEC(cRoekelFacility_RoekelBoss *self);
unsigned int fn_801EA2D0(cRoekelFacility_RoekelBoss *self);
unsigned int fn_801EA318(cRoekelFacility_RoekelBoss *self);
unsigned int fn_801EA360(cRoekelFacility_RoekelBoss *self);
unsigned int fn_801EA3A8(cRoekelFacility_RoekelBoss *self);
unsigned int fn_801EA3F0(cRoekelFacility_RoekelBoss *self);
void fn_801E8FEC(cRoekelFacility_PlasmaMine *self);
void fn_801E90B0(cRoekelFacility_PlasmaMine *self);
unsigned int fn_801EA48C(cRoekelFacility_PlasmaMine *self);
int fn_801E975C(cRoekelFacility_Lasers *self);
void fn_801E99A0(cRoekelFacility_Lasers *self, int value);
int fn_801EA528(cRoekelFacility_Lasers *self);
char *fn_801EA570(cRoekelFacility_Lasers *self);
unsigned int fn_801EA5B8(cRoekelFacility_Lasers *self);
unsigned int fn_801EA600(cRoekelFacility_Lasers *self);
unsigned int fn_801EA648(cRoekelFacility_Lasers *self);
unsigned int fn_801EA690(cRoekelFacility_Lasers *self);
unsigned int fn_801EA6D8(cRoekelFacility_Lasers *self);
unsigned int fn_801EA720(cRoekelFacility_Lasers *self);
unsigned int fn_801EA768(cRoekelFacility_Lasers *self);
unsigned int fn_801EA7B0(cRoekelFacility_Lasers *self);
unsigned int fn_801EA7F8(cRoekelFacility_Lasers *self);
unsigned int fn_801EA840(cRoekelFacility_Lasers *self);
unsigned int fn_801EA888(cRoekelFacility_Lasers *self);
unsigned int fn_801EA8D0(cRoekelFacility_Lasers *self);
unsigned int fn_801EA918(cRoekelFacility_Lasers *self);
unsigned int fn_801EA960(cRoekelFacility_Lasers *self);
unsigned int fn_801EA9A8(cRoekelFacility_Lasers *self);
unsigned int fn_801EA9F0(cRoekelFacility_Lasers *self);

void fn_801E4870(register cRoekelFacility_StormBoss *self) // slot 4
{
    fn_8046B710(&self->boss, Script_GetOwner(self));
    fn_8046B710(&self->player, fn_80080B34());
    Script_LinkEntity(self, fn_804425F8(&self->player), 0);
    fn_8046B710(&self->r38, fn_801E9AC0(self));
    fn_800826A8(&self->r38, &self->m68);
    self->f48 = 0;
    self->f4C = 0;
    self->f50 = 0;
    self->f54 = 0;
    self->f58 = 0;
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
}

void fn_801E4964(register cRoekelFacility_StormBoss *self) // slot 5
{
}

float fn_801E4984(register cRoekelFacility_StormBoss *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h == fn_804425F8(&self->boss)) {
        if (self->f4C == 0 && self->f50 == 0 && self->f58 == 0 && self->f48 == 0) {
            float ratio = fn_8007C3EC(&self->boss) / fn_8007C52C(&self->boss);

            if (ratio < 0.5f) {
                fn_8007B2E8(fn_804425F8(&self->boss), 10, 100.0f);
                fn_8007B2E8(fn_804425F8(&self->boss), 11, 100.0f);
                fn_8007B2E8(fn_804425F8(&self->boss), 0, 100.0f);
                self->f4C = 1;
                return damage;
            }
        } else if (self->f48 == 1) {
            fn_801E5260(self);
            return -1.0f;
        } else if (self->f50 == 1) {
            self->f50 = 0;
            fn_801E5260(self);
            return -1.0f;
        }
    } else if (h == fn_804425F8(&self->player) && self->f4C == 1) {
        self->f4C = 0;
        self->f50 = 1;
        fn_801E5088(self);
        return damage;
    }
    return damage;
}

void fn_801E4B8C(register cRoekelFacility_StormBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    Ref8 ev;
    float x;
    float hp;
    float max;

    switch (kind) {
    case 46:
        fn_801E5358(self);
        break;
    case 47:
        fn_801E5408(self);
        break;
    case 48:
        fn_801E54D0(self);
        break;
    case 49:
        fn_801E5540(self);
        break;
    case 10:
        fn_801E5260(self);
        break;
    case 30:
        self->f58 = 0;
        break;
    case 20:
        fn_8046B6C8(&ev, fn_801E9B08(self));
        Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 25:
        fn_8046B6C8(&ev, fn_801E9B08(self));
        Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), 7, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 40:
        hp = fn_8007C0AC(&self->boss);
        max = fn_8007C2AC(&self->boss);
        x = fn_8007C3EC(&self->boss);
        if (x < fn_8007C52C(&self->boss)) {
            x = x + 10.0f;
            fn_8007C454(&self->boss, x);
        }
        Script_QueueMessage(self, 1.0f, 40, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
}

int fn_801E4E40(register cRoekelFacility_StormBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
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

void fn_801E4F34(register cRoekelFacility_StormBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (self->done) {
        if (h != fn_804425F8(&self->player))
            return;
        return;
    }
    Script_CancelMessages(self, 10);
    self->done = 1;
    lbl_8066C724 = 1;
    fn_80081C68();
    fn_80081C94();
    fn_80081CC4();
    fn_80081B40(fn_804425F8(&self->boss));
    if (h == fn_804425F8(&self->boss)) {
        fn_80081A54(fn_804425F8(&self->player));
        if (self->bossHit == 0)
            fn_801E5358(self);
        else
            fn_801E5408(self);
    } else if (h == fn_804425F8(&self->player)) {
        if (self->playerHit == 0)
            fn_801E54D0(self);
        else
            fn_801E5540(self);
    }
}

void fn_801E5088(register cRoekelFacility_StormBoss *self)
{
    fn_8007A448(fn_804425F8(&self->boss));
    Vector at;
    fn_80082440(&self->r38, &at);
    fn_8007A738(fn_804425F8(&self->boss), &at);
    return;
}

float fn_801E5110(register cRoekelFacility_StormBoss *self, int h, int node, int value) // slot 37
{
    if (self->f50 == 1) {
        fn_800825D0(&self->boss, &self->m68);
        self->f50 = 0;
        self->f48 = 1;
        fn_8007B618(fn_804425F8(&self->boss), 1);
        fn_8007BCC8(fn_804425F8(&self->boss), 1);
        fn_8046B710(&self->core, fn_80082190(&self->r38, "pwrplantsupcorefx"));
        Script_QueueMessage(self, 8.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 1.0f, 40, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
    return -1.0f;
}

void fn_801E5260(register cRoekelFacility_StormBoss *self)
{
    fn_8007D8B0(self);
    self->f48 = 0;
    fn_80082124(&self->core);
    fn_8007B618(fn_804425F8(&self->boss), 0);
    fn_8007BD7C(fn_804425F8(&self->boss));
    fn_8007A4FC(fn_804425F8(&self->boss));
    fn_8007B288(fn_804425F8(&self->boss));
    Script_QueueMessage(self, 10.0f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    self->f58 = 1;
}

void fn_801E5358(register cRoekelFacility_StormBoss *self)
{
    Script_QueueMessage(self, 2.0f, 47, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_8057230C, 1);
}

void fn_801E5408(register cRoekelFacility_StormBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->player));
    lbl_8066C71C = fn_804425F8(&self->player);
    fn_8046B6C8(&ev, fn_801E9B08(self));
    Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801E54D0(register cRoekelFacility_StormBoss *self)
{
    Script_QueueMessage(self, 2.0f, 49, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801E5540(register cRoekelFacility_StormBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    lbl_8066C71C = fn_804425F8(&self->boss);
    fn_8046B6C8(&ev, fn_801E9B50(self));
    Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), 7, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801E5608(register cRoekelFacility_ThingBoss *self) // slot 4
{
    self->fA8 = 0;
    self->phase = 0;
    self->fB0 = 0;
    self->fB4 = 0;
    self->fB8 = 0;
    self->fBC = 0;
    self->fC0 = 0;
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
}

void fn_801E5680(register cRoekelFacility_ThingBoss *self) // slot 5
{
    fn_8046B710(&self->boss, Script_GetOwner(self));
    fn_8046B710(&self->player, fn_80080B34());
    Script_LinkEntity(self, fn_804425F8(&self->player), 0);
    fn_8046B710(&self->r98, fn_801E9FDC(self));
    fn_800826A8(&self->r98, &self->mF0);
    fn_8046B710(&self->r38[0], fn_801E9BEC(self));
    fn_8046B710(&self->r38[1], fn_801E9C34(self));
    fn_8046B710(&self->r38[2], fn_801E9C7C(self));
    fn_8046B710(&self->r38[3], fn_801E9CC4(self));
    fn_8046B710(&self->r38[4], fn_801E9D0C(self));
    fn_8046B710(&self->r38[5], fn_801E9D54(self));
    fn_8046B710(&self->r38[6], fn_801E9D9C(self));
    fn_8046B710(&self->r38[7], fn_801E9DE4(self));
    fn_8046B710(&self->r38[8], fn_801E9E2C(self));
    fn_8046B710(&self->r38[9], fn_801E9E74(self));
    fn_8046B710(&self->r38[10], fn_801E9EBC(self));
    fn_8046B710(&self->r38[11], fn_801E9F04(self));
    fn_8046B838(lbl_80552110, 1);
    Script_QueueMessage(self, 20.0f, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

float fn_801E58D4(register cRoekelFacility_ThingBoss *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (self->done == 1)
        return 0.0f;
    if (h == fn_804425F8(&self->boss) && self->fB0 == 1)
        fn_801E63E8(self);
    if (h == fn_804425F8(&self->player) && self->fB8 == 1 && fn_8007BEA8(fn_804425F8(&self->player))) {
        fn_8007D8B0(self);
        self->fB8 = 0;
        self->fB0 = 1;
        fn_8007A448(fn_804425F8(&self->boss));
        fn_801E61C8(self);
    }
    return damage;
}

#define THING_LINK(i) Script_TriggerEntity(&self->r38[i], fn_804425F8(&self->r38[i]), Script_GetOwner(self), 0, self->target.x, self->target.y, self->target.z, 0.0f)

void fn_801E59F8(register cRoekelFacility_ThingBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 46:
        fn_801E6CF8(self);
        break;
    case 47:
        fn_801E6DA8(self);
        break;
    case 48:
        fn_801E6FCC(self);
        break;
    case 49:
        fn_801E703C(self);
        break;
    case 26:
        fn_8007C6D0(&self->boss, 5.0f);
        Script_QueueMessage(self, 1.0f, 26, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 1:
        self->fB8 = 1;
        break;
    case 10:
        fn_801E63E8(self);
        break;
    case 15:
        fn_801E6544(self);
        break;
    case 30:
        THING_LINK(0);
        break;
    case 31:
        THING_LINK(1);
        break;
    case 32:
        THING_LINK(2);
        break;
    case 33:
        THING_LINK(3);
        break;
    case 34:
        THING_LINK(4);
        break;
    case 35:
        THING_LINK(5);
        break;
    case 36:
        THING_LINK(6);
        break;
    case 37:
        THING_LINK(7);
        break;
    case 38:
        THING_LINK(8);
        break;
    case 39:
        THING_LINK(9);
        break;
    case 40:
        THING_LINK(10);
        break;
    case 41:
        THING_LINK(11);
        break;
    }
}

int fn_801E5F68(register cRoekelFacility_ThingBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
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

void fn_801E605C(register cRoekelFacility_ThingBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (self->done) {
        if (h != fn_804425F8(&self->player))
            return;
        return;
    }
    Script_CancelMessages(self, 10);
    Script_CancelMessages(self, 15);
    Script_CancelMessages(self, 1);
    self->done = 1;
    lbl_8066C724 = 1;
    fn_80081C68();
    fn_80081C94();
    fn_80081CC4();
    fn_80081B40(fn_804425F8(&self->boss));
    if (h == fn_804425F8(&self->boss)) {
        fn_80081A54(fn_804425F8(&self->player));
        if (self->bossHit == 0)
            fn_801E6CF8(self);
        else
            fn_801E6DA8(self);
    } else if (h == fn_804425F8(&self->player)) {
        if (self->playerHit == 0)
            fn_801E6FCC(self);
        else
            fn_801E703C(self);
    }
}

void fn_801E61C8(register cRoekelFacility_ThingBoss *self)
{
    self->fC0 = 1;
    Vector at;
    fn_80082440(&self->r98, &at);
    fn_8007A738(fn_804425F8(&self->boss), &at);
}

float fn_801E623C(register cRoekelFacility_ThingBoss *self, int h, int node, int value) // slot 37
{
    if (self->fC0 == 1) {
        fn_8007D8B0(self);
        self->fC0 = 0;
        fn_800825D0(&self->boss, &self->mF0);
        if (self->fBC == 0) {
            Ref8 ev;

            self->fBC = 1;
            fn_8046B6C8(&ev, fn_801EA024(self));
            Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        }
        fn_8046B710(&self->core, fn_80082190(&self->r98, "pwrplantsupcorefx"));
        Script_QueueMessage(self, 1.0f, 26, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        if (fn_8007C034(&self->boss))
            fn_800CD6C4(fn_80085928((void *)fn_8007C034(&self->boss)), 1);
        fn_801E6544(self);
    }
    return -1.0f;
}

void fn_801E63E8(register cRoekelFacility_ThingBoss *self)
{
    fn_8007D8B0(self);
    fn_80082124(&self->core);
    if (self->fBC == 1) {
        Ref8 ev;

        fn_8046B6C8(&ev, fn_801EA024(self));
        Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    if (fn_8007C034(&self->boss))
        fn_800CD6C4(fn_80085928((void *)fn_8007C034(&self->boss)), 0);
    fn_8007A4FC(fn_804425F8(&self->boss));
    self->fB8 = 0;
    Script_QueueMessage(self, 20.0f, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    self->fB0 = 0;
}

void fn_801E6544(register cRoekelFacility_ThingBoss *self)
{
    Ref8 p;

    fn_8007B0EC(fn_804425F8(&self->boss), 0x2f, 0, 1);
    fn_8046B5A8(&p, fn_80080B34());
    fn_80082440(&p, &self->target);
    if (self->phase == 3) {
        Script_QueueMessage(self, 1.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        self->phase = 0;
        return;
    } else if (self->phase == 2) {
        Script_QueueMessage(self, 1.5f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 2.0f, 31, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 2.5f, 32, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 3.0f, 33, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 3.5f, 34, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 4.0f, 35, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 4.5f, 36, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 5.0f, 37, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 5.5f, 38, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 6.0f, 39, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 6.5f, 40, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 7.5f, 15, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        self->phase = 3;
        return;
    } else if (self->phase == 1) {
        Script_QueueMessage(self, 1.5f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 2.0f, 31, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 2.5f, 32, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 3.0f, 33, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 3.5f, 34, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 4.0f, 35, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 4.5f, 36, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 5.0f, 37, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 5.5f, 38, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 6.5f, 15, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        self->phase = 2;
        return;
    } else if (self->phase == 0) {
        Script_QueueMessage(self, 1.5f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 2.0f, 31, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 2.5f, 32, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 3.0f, 33, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 3.5f, 34, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 4.0f, 35, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 4.5f, 36, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        Script_QueueMessage(self, 5.5f, 15, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        self->phase = 1;
        return;
    }
}

void fn_801E6CF8(register cRoekelFacility_ThingBoss *self)
{
    Script_QueueMessage(self, 2.0f, 47, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_80572278, 1);
}

void fn_801E6DA8(register cRoekelFacility_ThingBoss *self)
{
    Ref8 a;
    Ref8 b;
    Ref8 c;
    Ref8 d;

    fn_80081918(fn_804425F8(&self->player));
    fn_8046B6C8(&a, fn_801EA06C(self));
    Script_TriggerEntity(&a, fn_804425F8(&a), Script_GetOwner(self), 7, 0.0f, 0.0f, 0.0f, 0.0f);
    fn_8046B6C8(&b, fn_801EA0B4(self));
    Script_TriggerEntity(&b, fn_804425F8(&b), Script_GetOwner(self), 7, 0.0f, 0.0f, 0.0f, 0.0f);
    fn_8046B6C8(&c, fn_801EA0FC(self));
    Script_TriggerEntity(&c, fn_804425F8(&c), Script_GetOwner(self), 7, 0.0f, 0.0f, 0.0f, 0.0f);
    fn_80082F30(&a);
    fn_80082F30(&b);
    fn_80082F30(&c);
    fn_8046B6C8(&d, fn_801E9F4C(self));
    Script_TriggerEntity(&d, fn_804425F8(&d), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801E6FCC(register cRoekelFacility_ThingBoss *self)
{
    Script_QueueMessage(self, 2.0f, 49, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801E703C(register cRoekelFacility_ThingBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    fn_8046B6C8(&ev, fn_801E9F94(self));
    Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801E70F0(register cRoekelFacility_RockBomb *self) // slot 4
{
    fn_8046B710(&self->obj, Script_GetOwner(self));
    fn_8046B710(&self->thing, fn_80083734("THING"));
}

void fn_801E7164(register cRoekelFacility_RockBomb *self) // slot 5
{
    fn_800826A8(&self->obj, &self->m50);
    SObj *o = fn_80081E6C(&self->obj);
    if (!o || !fn_800B24AC(*o) || fn_80317960(*fn_800B24AC(*o)).fn_80436294())
        return;
    fn_8006645C(o, 1);
    fn_800820A0(&self->obj, 0);
    fn_80081F8C(&self->obj, 2);
}

void fn_801E7250(register cRoekelFacility_RockBomb *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 60:
        fn_800820A0(&self->obj, 1);
        fn_80080928(&self->obj, 1);
        break;
    case 40:
        fn_801E7824(self);
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
        fn_80082190(&self->obj, "swav_MedGray");
        self->dust = fn_80393D0C(o, "dirtExpRcks", 0xff, 0xff);
        Vector pos;
        Ref8 p;
        fn_8046B5A8(&p, fn_80080B34());
        fn_80082440(&p, &pos);
        float dist = fn_804290F8(&pos, &at);
        if (dist < 5.0) {
            fn_8007C594(&p, 10.0f, 0, 0, 0, 0);
            int actor = fn_8007C034(&p);
            if (actor && fn_8009B04C(actor) != 0x6c)
                fn_8007C740(&p, 0x6c, 0, 0, 1.0f, 0);
        }
        fn_80081F8C(&self->obj, 2);
        fn_801E7824(self);
        break;
    }
    }
}

void fn_801E7504(register cRoekelFacility_RockBomb *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    self->aim.x = x;
    self->aim.y = y;
    self->aim.z = z;
    self->aim.x = self->aim.x + (fn_80171F8C() * 4.656612873077392578125e-10f * 4.0f - 2.0f);
    self->aim.y = self->aim.y + (fn_80171F8C() * 4.656612873077392578125e-10f * 4.0f - 2.0f);
    self->aim.z = self->aim.z + 10.0f;
    fn_800824AC(&self->obj, &self->aim);
    fn_80082014(&self->obj, 2);
    Ref8 r;
    fn_8046B5F0(&r, Script_GetOwner(self));
    SObj *o = fn_80080EFC(&r);
    if (o) {
        fn_8006645C(o, 0);
        fn_80066794(o, 1);
    }
    Script_QueueMessage(self, 0.25f, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801E76F0(register cRoekelFacility_RockBomb *self, int h, int other, int a, int b, int value) // slot 27
{
    Ref8 p;

    fn_8046B5A8(&p, fn_80080B34());
    if (other == fn_804425F8(&p)) {
        fn_8007C594(&p, 20.0f, 0, 0, 0, 0);
        int actor = fn_8007C034(&p);
        if (actor && fn_8009B04C(actor) != 0x6c)
            fn_8007C740(&p, 0x6c, 0, 0, 1.0f, 0);
    }
    Script_QueueMessage(self, 0.01f, 50, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801E7824(register cRoekelFacility_RockBomb *self)
{
    Ref8 r;

    fn_80081F8C(&self->obj, 2);
    fn_800825D0(&self->obj, &self->m50);
    fn_80080928(&self->obj, 0);
    fn_800820A0(&self->obj, 0);
    fn_8046B5F0(&r, Script_GetOwner(self));
    SObj *o = fn_80080EFC(&r);
    if (!o)
        return;
    fn_8006645C(o, 1);
    fn_80066604(o);
}

void fn_801E78EC(register cRoekelFacility_BlastDoor *self) // slot 4
{
    fn_8046B710(&self->door, Script_GetOwner(self));
    self->done = 0;
    self->f38 = 0;
}

void fn_801E7950(register cRoekelFacility_BlastDoor *self) // slot 5
{
    if (fn_801EA1EC(self)) {
        self->open = 1;
        fn_8008046C(&self->door, 0x17, 300.0f);
        fn_800820A0(&self->door, 0);
    } else
        self->open = 0;
    if (fn_801EA234(self))
        self->f38 = 1;
}

void fn_801E79F4(register cRoekelFacility_BlastDoor *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (self->done == 1)
        return;
    if (kind == 17) {
        self->done = 1;
        fn_800810DC(&self->door, 300.0f, 0, 0, 0, 0);
        return;
    }
    if (self->open == 0) {
        self->open = 1;
        self->ms = fn_8008046C(&self->door, 0x17, 30.0f);
        fn_80080358(&self->door, 0x31);
        if (self->ms > 0)
            Script_QueueMessageMs(self, self->ms, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        return;
    } else if (self->open == 1) {
        self->open = 0;
        self->ms = fn_8008046C(&self->door, 0x16, 30.0f);
        fn_80080358(&self->door, 0x32);
        if (self->ms > 0)
            Script_QueueMessageMs(self, self->ms, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        return;
    }
}

void fn_801E7BAC(register cRoekelFacility_BlastDoor *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        if (self->open == 1) {
            fn_800820A0(&self->door, 0);
            break;
        } else if (self->open == 0) {
            fn_800820A0(&self->door, 1);
            break;
        }
    }
}

float fn_801E7C58(register cRoekelFacility_BlastDoor *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (self->f38 == 1)
        return -1.0f;
    return damage;
}

void fn_801E7CB8(register cRoekelFacility_BlastDoor *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    self->done = 1;
    Vector at;
    fn_80082440(&self->door, &at);
    fn_800838E0(&at);
    fn_80082190(&self->door, "exp_largeFake");
    fn_80082190(&self->door, "swav_BigGray");
}

void fn_801E7D5C(register cRoekelFacility_RoekelBoss *self) // slot 4
{
    self->fAC = 0;
    self->fB4 = 0;
    self->fB8 = 0;
    self->fB0 = 0;
    self->fBC = 0;
    self->fC0 = 0;
    self->fD0 = 1;
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
}

void fn_801E7DCC(register cRoekelFacility_RoekelBoss *self) // slot 5
{
    fn_8046B710(&self->boss, Script_GetOwner(self));
    fn_8007BA24(Script_GetOwner(self), 4);
    fn_8046B710(&self->player, fn_80080B34());
    Script_LinkEntity(self, fn_804425F8(&self->player), 0);
    fn_8046B710(&self->r48, fn_801EA2D0(self));
    fn_800826A8(&self->r48, &self->m68);
    fn_8046B710(&self->r50, fn_801EA318(self));
    fn_8046B710(&self->r58, fn_801EA360(self));
    fn_8046B838(lbl_80552110, 1);
}

int fn_801E7EE0(register cRoekelFacility_RoekelBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
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

float fn_801E7FCC(register cRoekelFacility_RoekelBoss *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (self->fB8 == 1)
        return -1.0f;
    if (h == fn_804425F8(&self->boss)) {
        if (self->fB4 == 1 && self->fC0 == 0) {
            Script_QueueMessage(self, 0.0f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            return damage;
        } else if (self->fB4 == 0 && self->fC0 == 0 && self->fD0 == 1) {
            float r = fn_8007C0AC(&self->boss) / fn_8007C244(&self->boss) - damage;

            if (r < 0.7f) {
                self->fB4 = 1;
                self->fC0 = 1;
                self->fBC = 1;
                fn_8007B2E8(fn_804425F8(&self->boss), 0, 100.0f);
                fn_8007B2E8(fn_804425F8(&self->boss), 7, 100.0f);
                fn_8007B2E8(fn_804425F8(&self->boss), 11, 100.0f);
            }
        }
    }
    if (h == fn_804425F8(&self->player) && self->fBC == 1 && fn_8007BEA8(fn_804425F8(&self->player))) {
        self->fBC = 0;
        fn_8007A448(fn_804425F8(&self->boss));
        fn_801E856C(self);
        return damage;
    }
    return damage;
}

void fn_801E822C(register cRoekelFacility_RoekelBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    float x;
    float hp;
    float max;

    switch (kind) {
    case 46:
        fn_801E8970(self);
        break;
    case 47:
        fn_801E8AC8(self);
        break;
    case 48:
        fn_801E8B7C(self);
        break;
    case 49:
        fn_801E8BEC(self);
        break;
    case 10:
        break;
    case 15:
        break;
    case 20:
        fn_8007BB24(fn_804425F8(&self->boss));
        fn_80082124(&self->core);
        fn_8007D8B0(self);
        self->fB4 = 0;
        self->fBC = 0;
        fn_8007A4FC(fn_804425F8(&self->boss));
        Script_TriggerEntity(&self->r50, fn_804425F8(&self->r50), Script_GetOwner(self), 18, 0.0f, 0.0f, 0.0f, 0.0f);
        Script_TriggerEntity(&self->r58, fn_804425F8(&self->r58), Script_GetOwner(self), 18, 0.0f, 0.0f, 0.0f, 0.0f);
        fn_8007B288(fn_804425F8(&self->boss));
        self->fD0 = 0;
        Script_QueueMessage(self, 20.0f, 50, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 40:
        break;
    case 30:
        hp = fn_8007C0AC(&self->boss);
        max = fn_8007C2AC(&self->boss);
        x = fn_8007C3EC(&self->boss);
        fn_8007C6D0(&self->boss, 5.0f);
        if (x < fn_8007C52C(&self->boss)) {
            x = x + 60.0f;
            fn_8007C454(&self->boss, x);
        }
        Script_QueueMessage(self, 1.0f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 50:
        self->fD0 = 1;
        break;
    }
}

void fn_801E856C(register cRoekelFacility_RoekelBoss *self)
{
    self->fC0 = 1;
    Vector at;
    fn_80082440(&self->r48, &at);
    fn_8007A738(fn_804425F8(&self->boss), &at);
}

float fn_801E85E0(register cRoekelFacility_RoekelBoss *self, int h, int node, int value) // slot 37
{
    if (h != fn_804425F8(&self->boss))
        return -1.0f;
    fn_800825D0(&self->boss, &self->m68);
    self->fC0 = 0;
    fn_8007BAA0(fn_804425F8(&self->boss));
    fn_8046B710(&self->core, fn_80082190(&self->r48, "pwrplantsupcorefx"));
    fn_801E872C(self);
    Script_QueueMessage(self, 6.0f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    Script_QueueMessage(self, 1.0f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    return -1.0f;
}

void fn_801E872C(register cRoekelFacility_RoekelBoss *self)
{
    float f = 0.5f;

    Script_TriggerEntity(&self->r50, fn_804425F8(&self->r50), Script_GetOwner(self), 0, f, 0.0f, 0.0f, 0.0f);
    Script_TriggerEntity(&self->r58, fn_804425F8(&self->r58), Script_GetOwner(self), 0, f, 0.0f, 0.0f, 0.0f);
}

void fn_801E8810(register cRoekelFacility_RoekelBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (self->done) {
        if (h != fn_804425F8(&self->player))
            return;
        return;
    }
    Script_CancelMessages(self, 20);
    Script_CancelMessages(self, 30);
    self->done = 1;
    lbl_8066C724 = 1;
    fn_80081C68();
    fn_80081C94();
    fn_80081CC4();
    fn_80081B40(fn_804425F8(&self->boss));
    if (h == fn_804425F8(&self->boss)) {
        fn_80081A54(fn_804425F8(&self->player));
        if (self->bossHit == 0)
            fn_801E8970(self);
        else
            fn_801E8AC8(self);
    } else if (h == fn_804425F8(&self->player)) {
        if (self->playerHit == 0)
            fn_801E8B7C(self);
        else
            fn_801E8BEC(self);
    }
}

void fn_801E8970(register cRoekelFacility_RoekelBoss *self)
{
    Script_TriggerEntity(&self->r50, fn_804425F8(&self->r50), Script_GetOwner(self), 18, 0.0f, 0.0f, 0.0f, 0.0f);
    Script_TriggerEntity(&self->r58, fn_804425F8(&self->r58), Script_GetOwner(self), 18, 0.0f, 0.0f, 0.0f, 0.0f);
    Script_QueueMessage(self, 2.0f, 47, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_80572278, 1);
}

void fn_801E8AC8(register cRoekelFacility_RoekelBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->player));
    fn_8046B6C8(&ev, fn_801EA3A8(self));
    Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801E8B7C(register cRoekelFacility_RoekelBoss *self)
{
    Script_QueueMessage(self, 2.0f, 49, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801E8BEC(register cRoekelFacility_RoekelBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    fn_8046B6C8(&ev, fn_801EA3F0(self));
    Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

}

inline int sn_return_decl2(int a) { return a; }

extern "C" {

void fn_801E8CA0(register cRoekelFacility_PlasmaMine *self) // slot 4
{
    self->armed = 0;
    self->sparks = 0;
}

void fn_801E8CD0(register cRoekelFacility_PlasmaMine *self) // slot 5
{
    fn_8046B710(&self->mine, Script_GetOwner(self));
    fn_8046B710(&self->player, fn_80080B34());
    fn_80082440(&self->mine, &self->pos);
    fn_8046B710(&self->r30, fn_801EA48C(self));
    Script_LinkEntity(self, fn_804425F8(&self->r30), 0);
}

void fn_801E8D84(register cRoekelFacility_PlasmaMine *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 20:
        fn_801E90B0(self);
        break;
    case 30:
        if (self->sparks <= 14) {
            fn_80082190(&self->mine, "sprk_elecA");
            float t = fn_80171F8C() * 4.656612873077392578125e-10f * 0.25f + 0.1f;
            Script_QueueMessage(self, t, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            self->sparks++;
        }
        break;
    }
}

void fn_801E8EB8(register cRoekelFacility_PlasmaMine *self, int h, int other, int value) // slot 14
{
    if (h == fn_804425F8(&self->r30) && self->armed == 0)
        self->armed = 1;
}

void fn_801E8F2C(register cRoekelFacility_PlasmaMine *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    fn_801E8FEC(self);
}

float fn_801E8F8C(register cRoekelFacility_PlasmaMine *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    fn_801E8FEC(self);
    return damage;
}

void fn_801E8FEC(register cRoekelFacility_PlasmaMine *self)
{
    fn_8007D8B0(self);
    self->armed = 1;
    fn_80082190(&self->mine, "sprk_elecA");
    Script_QueueMessage(self, 4.0f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    Script_QueueMessage(self, 0.2f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801E90B0(register cRoekelFacility_PlasmaMine *self)
{
    fn_80082190(&self->mine, "exp_largeFake");
    fn_80082190(&self->mine, "swav_BigGray");
    fn_800838E0(&self->pos);
    fn_80082F30(&self->mine);
    fn_80082440(&self->player, &self->at);
    float dist = fn_804290F8(&self->pos, &self->at);
    if (dist < 8.0)
        fn_8007C594(&self->player, 40.0f, 2, 0, 0, 0);
}

void fn_801E918C(register cRoekelFacility_Lasers *self) // slot 5
{
    self->delay = 10.0f;
    self->count = fn_801E975C(self);
    if (fn_801EA528(self) != 0)
        return;
    if (self->count > 0)
        Script_QueueMessage(self, 0.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801E9234(register cRoekelFacility_Lasers *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 0:
        if (fn_801EA528(self) != 1)
            return;
        if (x > 0.0f)
            self->delay = x;
        if (self->count > 0)
            Script_QueueMessage(self, 0.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 17:
        self->delay = self->delay * 0.75f;
        break;
    case 18:
        fn_8007D8B0(self);
        break;
    }
}

void fn_801E9358(register cRoekelFacility_Lasers *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    Ref8 ev;

    fn_8046B5F0(&ev, 0);
    switch (kind) {
    case 10: {
        int n = (int)(fn_80171F8C() * 4.656612873077392578125e-10f * (float)self->count);

        switch (n) {
        case 0:
            fn_8046B710(&ev, fn_801EA5B8(self));
            break;
        case 1:
            fn_8046B710(&ev, fn_801EA600(self));
            break;
        case 2:
            fn_8046B710(&ev, fn_801EA648(self));
            break;
        case 3:
            fn_8046B710(&ev, fn_801EA690(self));
            break;
        case 4:
            fn_8046B710(&ev, fn_801EA6D8(self));
            break;
        case 5:
            fn_8046B710(&ev, fn_801EA720(self));
            break;
        case 6:
            fn_8046B710(&ev, fn_801EA768(self));
            break;
        case 7:
            fn_8046B710(&ev, fn_801EA7B0(self));
            break;
        case 8:
            fn_8046B710(&ev, fn_801EA7F8(self));
            break;
        case 9:
            fn_8046B710(&ev, fn_801EA840(self));
            break;
        case 10:
            fn_8046B710(&ev, fn_801EA888(self));
            break;
        case 11:
            fn_8046B710(&ev, fn_801EA8D0(self));
            break;
        case 12:
            fn_8046B710(&ev, fn_801EA918(self));
            break;
        case 13:
            fn_8046B710(&ev, fn_801EA960(self));
            break;
        case 14:
            fn_8046B710(&ev, fn_801EA9A8(self));
            break;
        case 15:
            fn_8046B710(&ev, fn_801EA9F0(self));
            break;
        }
        fn_801E99A0(self, fn_804425F8(&ev));
        fn_80082E90(&ev, fn_801EA570(self), 0xff, 0xff);
        Script_QueueMessage(self, self->delay, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
    }
}

int fn_801E975C(register cRoekelFacility_Lasers *self)
{
    int n = 0;

    if (fn_801EA5B8(self))
        n++;
    if (fn_801EA600(self))
        n++;
    if (fn_801EA648(self))
        n++;
    if (fn_801EA690(self))
        n++;
    if (fn_801EA6D8(self))
        n++;
    if (fn_801EA720(self))
        n++;
    if (fn_801EA768(self))
        n++;
    if (fn_801EA7B0(self))
        n++;
    if (fn_801EA7F8(self))
        n++;
    if (fn_801EA840(self))
        n++;
    if (fn_801EA888(self))
        n++;
    if (fn_801EA8D0(self))
        n++;
    if (fn_801EA918(self))
        n++;
    if (fn_801EA960(self))
        n++;
    if (fn_801EA9A8(self))
        n++;
    if (fn_801EA9F0(self))
        n++;
    return n;
}

void fn_801E99A0(register cRoekelFacility_Lasers *self, int value)
{
    register Scene *scene = fn_80430050(lbl_8052F060);
    int e;

    for (e = scene->head; e; e = fn_800B1AC4(e)) {
        if (!fn_800B0C58(e) || !fn_8008582C(fn_800B14A0(e)))
            continue;
        fn_8007BF40(fn_800B13D8(e), 2, value, 0);
    }
}

cScript *fn_801E9A6C(register cRoekelFacility_StormBoss *self)
{
    return new cRoekelFacility_StormBoss;
}

unsigned int fn_801E9AC0(register cRoekelFacility_StormBoss *self) { return Script_GetParamUInt(self, 0); }
unsigned int fn_801E9B08(register cRoekelFacility_StormBoss *self) { return Script_GetParamUInt(self, 1); }
unsigned int fn_801E9B50(register cRoekelFacility_StormBoss *self) { return Script_GetParamUInt(self, 2); }

cScript *fn_801E9B98(register cRoekelFacility_ThingBoss *self)
{
    return new cRoekelFacility_ThingBoss;
}

unsigned int fn_801E9BEC(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 0); }
unsigned int fn_801E9C34(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 1); }
unsigned int fn_801E9C7C(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 2); }
unsigned int fn_801E9CC4(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 3); }
unsigned int fn_801E9D0C(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 4); }
unsigned int fn_801E9D54(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 5); }
unsigned int fn_801E9D9C(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 6); }
unsigned int fn_801E9DE4(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 7); }
unsigned int fn_801E9E2C(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 8); }
unsigned int fn_801E9E74(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 9); }
unsigned int fn_801E9EBC(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 10); }
unsigned int fn_801E9F04(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 11); }
unsigned int fn_801E9F4C(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 12); }
unsigned int fn_801E9F94(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 13); }
unsigned int fn_801E9FDC(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 14); }
unsigned int fn_801EA024(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 15); }
unsigned int fn_801EA06C(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 16); }
unsigned int fn_801EA0B4(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 17); }
unsigned int fn_801EA0FC(register cRoekelFacility_ThingBoss *self) { return Script_GetParamUInt(self, 18); }

cScript *fn_801EA144(register cRoekelFacility_RockBomb *self)
{
    return new cRoekelFacility_RockBomb;
}

cScript *fn_801EA198(register cRoekelFacility_BlastDoor *self)
{
    return new cRoekelFacility_BlastDoor;
}

int fn_801EA1EC(register cRoekelFacility_BlastDoor *self) { return Script_GetParamInt(self, 0); }
int fn_801EA234(register cRoekelFacility_BlastDoor *self) { return Script_GetParamInt(self, 1); }

cScript *fn_801EA27C(register cRoekelFacility_RoekelBoss *self)
{
    return new cRoekelFacility_RoekelBoss;
}

unsigned int fn_801EA2D0(register cRoekelFacility_RoekelBoss *self) { return Script_GetParamUInt(self, 0); }
unsigned int fn_801EA318(register cRoekelFacility_RoekelBoss *self) { return Script_GetParamUInt(self, 1); }
unsigned int fn_801EA360(register cRoekelFacility_RoekelBoss *self) { return Script_GetParamUInt(self, 2); }
unsigned int fn_801EA3A8(register cRoekelFacility_RoekelBoss *self) { return Script_GetParamUInt(self, 3); }
unsigned int fn_801EA3F0(register cRoekelFacility_RoekelBoss *self) { return Script_GetParamUInt(self, 4); }

cScript *fn_801EA438(register cRoekelFacility_PlasmaMine *self)
{
    return new cRoekelFacility_PlasmaMine;
}

unsigned int fn_801EA48C(register cRoekelFacility_PlasmaMine *self) { return Script_GetParamUInt(self, 1); }

cScript *fn_801EA4D4(register cRoekelFacility_Lasers *self)
{
    return new cRoekelFacility_Lasers;
}

int fn_801EA528(register cRoekelFacility_Lasers *self) { return Script_GetParamInt(self, 0); }
char *fn_801EA570(register cRoekelFacility_Lasers *self) { return Script_GetParamString(self, 1); }
unsigned int fn_801EA5B8(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 2); }
unsigned int fn_801EA600(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 3); }
unsigned int fn_801EA648(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 4); }
unsigned int fn_801EA690(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 5); }
unsigned int fn_801EA6D8(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 6); }
unsigned int fn_801EA720(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 7); }
unsigned int fn_801EA768(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 8); }
unsigned int fn_801EA7B0(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 9); }
unsigned int fn_801EA7F8(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 10); }
unsigned int fn_801EA840(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 11); }
unsigned int fn_801EA888(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 12); }
unsigned int fn_801EA8D0(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 13); }
unsigned int fn_801EA918(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 14); }
unsigned int fn_801EA960(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 15); }
unsigned int fn_801EA9A8(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 16); }
unsigned int fn_801EA9F0(register cRoekelFacility_Lasers *self) { return Script_GetParamUInt(self, 17); }

}
