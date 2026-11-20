// The Daily Bugle classes cDailyBugle_VenomBoss, cDailyBugle_SpidermanSac, cDailyBugle_LetterEffects and cDailyBugle_DaredevilBoss (docs/story.md row 16).
// Pool read from 0x8049FB40 (extern_pool).

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

struct Ent {
    int unk0;
};

struct Act : Ent {
    int pad;
};

struct cDailyBugle_VenomBoss : cScript { // 0xA8
    Ref8 boss;      // +0x28
    Ref8 player;    // +0x30
    Ref8 r38[4];    // +0x38, params 0-3
    Ref8 r58;       // +0x58, param 6
    Ref8 r60;       // +0x60, param 7
    int phase;      // +0x68
    float scale;    // +0x6C
    int f70;        // +0x70
    int f74;        // +0x74
    int f78;        // +0x78
    int f7C;        // +0x7C
    int f80;        // +0x80
    int used[4];    // +0x84, r38[i] spent
    int dead58;     // +0x94
    int dead60;     // +0x98
    int bossHit;    // +0x9C
    int playerHit;  // +0xA0
    int done;       // +0xA4
    cDailyBugle_VenomBoss() __asm__("fn_8046A958");
};

struct cDailyBugle_SpidermanSac : cScript { // 0x48
    Ref8 boss;      // +0x28
    Ref8 r30;       // +0x30, param 0
    int f38;        // +0x38
    int bossHit;    // +0x3C
    int playerHit;  // +0x40
    int done;       // +0x44
    cDailyBugle_SpidermanSac() __asm__("fn_8046AA0C");
};

struct cDailyBugle_LetterEffects : cScript { // 0x28
    cDailyBugle_LetterEffects() __asm__("fn_8046AA74");
};

struct cDailyBugle_DaredevilBoss : cScript { // 0xA4
    Ref8 boss;      // +0x28
    Ref8 r30[5];    // +0x30, params 0-4
    Ref8 chosen;    // +0x58
    Ref8 r60;       // +0x60, param 5
    Ref8 r68;       // +0x68, param 6
    int state;      // +0x70
    int f74;        // +0x74
    float delay;    // +0x78
    float delayMin; // +0x7C
    float delayMax; // +0x80
    float f84;      // +0x84
    float f88;      // +0x88
    float f8C;      // +0x8C
    int f90;        // +0x90
    int f94;        // +0x94
    int done;       // +0x98
    int bossHit;    // +0x9C
    int playerHit;  // +0xA0
    cDailyBugle_DaredevilBoss() __asm__("fn_8046AAC0");
};

extern char lbl_80552110[];
extern char lbl_80572278[];
extern char lbl_8057230C[];
extern int lbl_8066C724;

extern "C" {

int fn_800797D4(cScript *self);
unsigned int fn_800791C8(cScript *self, unsigned int i);
void fn_8007D404(cScript *self, float seconds, int kind, float a, float b, float c, float d, int e);
int fn_8007D7C4(cScript *self, unsigned char kind);
int fn_8007CF00(cScript *script, int handle, int value);
int fn_80080B34();
int fn_804425F8(void *ev);
void fn_8046B5A8(void *ev, int x);
void fn_8046B5F0(void *ev, int x);
void fn_8046B638(void *ev, int x);
void fn_8046B6C8(void *ev, int x);
void fn_8046B710(void *ev, int x);
int fn_8046BD30(void *ev);
void fn_8046B838(void *g, int x);
int fn_800809CC(void *ev);
int fn_80086D24(int p);
void *fn_80085928(void *p);
void fn_800CD6C4(void *c, int on);
void fn_80082AFC(void *ev, int h, int owner, int kind, float a, float b, float c, float d);
void fn_80082720(void *ev, int h);
void fn_80082F30(void *ev);
void fn_80082440(void *ev, Vector *out);
void fn_80083018(void *ev, char *name, int a, int b);
void fn_800810DC(void *ev, float f, int a, int b, int c, int d);
int fn_8007C034(void *ev);
float fn_8007C244(void *ev);
float fn_8007C0AC(void *ev);
float fn_8007C3EC(void *ev);
float fn_8007C52C(void *ev);
float fn_8007B8F8(int h);
void fn_8007B998(int h, float v);
void fn_8007AA8C(int h, int target);
void fn_8007AE94(int h, int a, int b);
void fn_8007A448(int h);
void fn_8007A4FC(int h);
void fn_8007A738(int h, Vector *to);
void fn_8007B288(int h);
void fn_8007B2E8(int h, int which, float v);
int fn_8007BEA8(int h);
void fn_8007BBB4(int h);
void fn_8007BC38(int h);
void fn_80081C68();
void fn_80081C94();
void fn_80081CC4();
int fn_80081B40(int h);
int fn_80081A54(int h);
void fn_80081918(int h);
void fn_800816A0(int h);
int fn_80081BD4(int h);
void fn_8043323C(void *p, int on);
int fn_8009B04C(int actor);
float fn_804290F8(void *a, void *b);
int fn_80171F8C();
Act *fn_80085954(int actor);
int fn_800CDA20(Ent &e);
int fn_800CD9B0(Ent &e);
int fn_800B1590(int p);
void fn_800F880C(Ent &e, int p, int a, int b);

void fn_801D26F0(cDailyBugle_VenomBoss *self);
void fn_801D2848(cDailyBugle_VenomBoss *self);
void fn_801D29E8(cDailyBugle_VenomBoss *self);
void fn_801D2A98(cDailyBugle_VenomBoss *self);
void fn_801D2B5C(cDailyBugle_VenomBoss *self);
void fn_801D2BCC(cDailyBugle_VenomBoss *self);
unsigned int fn_801D4D14(cDailyBugle_VenomBoss *self);
unsigned int fn_801D4D5C(cDailyBugle_VenomBoss *self);
unsigned int fn_801D4DA4(cDailyBugle_VenomBoss *self);
unsigned int fn_801D4DEC(cDailyBugle_VenomBoss *self);
unsigned int fn_801D4E34(cDailyBugle_VenomBoss *self);
unsigned int fn_801D4E7C(cDailyBugle_VenomBoss *self);
unsigned int fn_801D4EC4(cDailyBugle_VenomBoss *self);
unsigned int fn_801D4F0C(cDailyBugle_VenomBoss *self);
void fn_801D3354(cDailyBugle_SpidermanSac *self);
void fn_801D3404(cDailyBugle_SpidermanSac *self);
void fn_801D34A0(cDailyBugle_SpidermanSac *self);
void fn_801D3510(cDailyBugle_SpidermanSac *self);
unsigned int fn_801D4FA8(cDailyBugle_SpidermanSac *self);
unsigned int fn_801D4FF0(cDailyBugle_SpidermanSac *self);
unsigned int fn_801D508C(cDailyBugle_LetterEffects *self);
void fn_801D4520(cDailyBugle_DaredevilBoss *self);
void fn_801D45BC(cDailyBugle_DaredevilBoss *self);
void fn_801D4738(cDailyBugle_DaredevilBoss *self);
void fn_801D4860(cDailyBugle_DaredevilBoss *self);
void fn_801D49D8(cDailyBugle_DaredevilBoss *self);
void fn_801D4A80(cDailyBugle_DaredevilBoss *self);
void fn_801D4B28(cDailyBugle_DaredevilBoss *self);
void fn_801D4BBC(cDailyBugle_DaredevilBoss *self);
void fn_801D4C24(cDailyBugle_DaredevilBoss *self);
unsigned int fn_801D5128(cDailyBugle_DaredevilBoss *self);
unsigned int fn_801D5170(cDailyBugle_DaredevilBoss *self);
unsigned int fn_801D51B8(cDailyBugle_DaredevilBoss *self);
unsigned int fn_801D5200(cDailyBugle_DaredevilBoss *self);
unsigned int fn_801D5248(cDailyBugle_DaredevilBoss *self);
unsigned int fn_801D5290(cDailyBugle_DaredevilBoss *self);
unsigned int fn_801D52D8(cDailyBugle_DaredevilBoss *self);

void fn_801D1BFC(register cDailyBugle_VenomBoss *self) // slot 4
{
    self->phase = 0;
    self->f78 = 0;
    self->f80 = 0;
    self->f7C = 0;
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
    fn_8046B710(&self->boss, fn_800797D4(self));
    fn_8046B710(&self->player, fn_80080B34());
    fn_8007CF00(self, fn_804425F8(&self->player), 0);
    fn_8046B710(&self->r38[0], fn_801D4D14(self));
    fn_8046B710(&self->r38[1], fn_801D4D5C(self));
    fn_8046B710(&self->r38[2], fn_801D4DA4(self));
    fn_8046B710(&self->r38[3], fn_801D4DEC(self));
    fn_8046B710(&self->r58, fn_801D4EC4(self));
    fn_8046B710(&self->r60, fn_801D4F0C(self));
    fn_8007CF00(self, fn_804425F8(&self->r38[0]), 0);
    fn_8007CF00(self, fn_804425F8(&self->r38[1]), 0);
    fn_8007CF00(self, fn_804425F8(&self->r38[2]), 0);
    fn_8007CF00(self, fn_804425F8(&self->r38[3]), 0);
    fn_8007CF00(self, fn_804425F8(&self->r58), 0);
    fn_8007CF00(self, fn_804425F8(&self->r60), 0);
    self->used[0] = 0;
    self->used[1] = 0;
    self->used[2] = 0;
    self->used[3] = 0;
    self->dead58 = 0;
    self->dead60 = 0;
}

void fn_801D1E50(register cDailyBugle_VenomBoss *self) // slot 5
{
    fn_8046B838(lbl_80552110, 1);
    self->scale = fn_8007B8F8(fn_804425F8(&self->boss));
    fn_8007B2E8(fn_804425F8(&self->boss), 6, 50.0f);
}

float fn_801D1ED4(register cDailyBugle_VenomBoss *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h == fn_804425F8(&self->boss) && self->f78 == 0) {
        float ratio = fn_8007C0AC(&self->boss) / fn_8007C244(&self->boss);

        if (ratio < 0.4f && self->phase == 1) {
            self->f78 = 1;
            fn_801D26F0(self);
            self->phase = 2;
            self->f80 = 1;
            return damage;
        } else if (ratio < 0.7f && self->phase == 0) {
            self->f78 = 1;
            fn_801D26F0(self);
            self->phase = 1;
            self->f80 = 1;
            return damage;
        }
    } else if (h == fn_804425F8(&self->player) && self->f80 && self->f78 && fn_8007BEA8(fn_804425F8(&self->player))) {
        self->f80 = 0;
        if (self->dead58 == 0) {
            fn_8007A448(fn_804425F8(&self->boss));
            fn_8007AE94(fn_804425F8(&self->boss), fn_804425F8(&self->r58), fn_80080B34());
            return damage;
        } else if (self->dead60 == 0) {
            fn_8007A448(fn_804425F8(&self->boss));
            fn_8007AE94(fn_804425F8(&self->boss), fn_804425F8(&self->r60), fn_80080B34());
            return damage;
        }
    }
    return damage;
}

void fn_801D2158(register cDailyBugle_VenomBoss *self, int h, int other, int value) // slot 38
{
    fn_8007A4FC(fn_804425F8(&self->boss));
}

void fn_801D21AC(register cDailyBugle_VenomBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 40:
        self->f78 = 0;
        fn_8007B998(fn_804425F8(&self->boss), self->scale);
        fn_8007B288(fn_804425F8(&self->boss));
        fn_8007B2E8(fn_804425F8(&self->boss), 6, 50.0f);
        break;
    case 10:
        fn_8007A4FC(fn_804425F8(&self->boss));
        break;
    case 50:
        fn_801D29E8(self);
        break;
    case 60:
        fn_801D2A98(self);
        break;
    case 70:
        fn_801D2B5C(self);
        break;
    case 80:
        fn_801D2BCC(self);
        break;
    }
}

int fn_801D2300(register cDailyBugle_VenomBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    Ref8 r;

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

void fn_801D24B0(register cDailyBugle_VenomBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    Ref8 ev;

    if (h == fn_804425F8(&self->r38[0]))
        self->used[0] = 1;
    else if (h == fn_804425F8(&self->r38[1]))
        self->used[1] = 1;
    else if (h == fn_804425F8(&self->r38[2]))
        self->used[2] = 1;
    else if (h == fn_804425F8(&self->r38[3]))
        self->used[3] = 1;
    else if (h == fn_801D4EC4(self))
        self->dead58 = 1;
    else if (h == fn_801D4F0C(self))
        self->dead60 = 1;
    fn_8046B6C8(&ev, h);
    if (fn_8046BD30(&ev) == 0)
        return;
    if (self->done) {
        if (h != fn_80080B34())
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
        fn_80081A54(fn_80080B34());
        if (self->bossHit == 0)
            fn_801D29E8(self);
        else
            fn_801D2A98(self);
    } else if (h == fn_80080B34()) {
        if (self->playerHit == 0)
            fn_801D2B5C(self);
        else
            fn_801D2BCC(self);
    }
}

void fn_801D26F0(register cDailyBugle_VenomBoss *self)
{
    fn_801D2848(self);
    fn_8007B2E8(fn_804425F8(&self->boss), 9, 100.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 5, 20.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 6, 20.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 2, 80.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 11, 80.0f);
    fn_8007B998(fn_804425F8(&self->boss), self->scale * 2.0f);
    fn_8007D404(self, 30.0f, 40, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801D2848(register cDailyBugle_VenomBoss *self)
{
    Ref8 r;

    fn_8046B5F0(&r, 0);
    if (self->used[1] == 0) {
        fn_8046B710(&r, fn_804425F8(&self->r38[1]));
        fn_800810DC(&r, 200.0f, 0, 0, 0, 0);
        self->used[1] = 1;
        return;
    } else if (self->used[2] == 0) {
        fn_8046B710(&r, fn_804425F8(&self->r38[2]));
        fn_800810DC(&r, 200.0f, 0, 0, 0, 0);
        self->used[2] = 1;
        return;
    } else if (self->used[3] == 0) {
        fn_8046B710(&r, fn_804425F8(&self->r38[3]));
        fn_800810DC(&r, 200.0f, 0, 0, 0, 0);
        self->used[3] = 1;
        return;
    } else if (self->used[0] == 0) {
        fn_8046B710(&r, fn_804425F8(&self->r38[0]));
        fn_800810DC(&r, 200.0f, 0, 0, 0, 0);
        self->used[0] = 1;
        return;
    }
}

void fn_801D29E8(register cDailyBugle_VenomBoss *self)
{
    fn_8007D404(self, 3.0f, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_80572278, 1);
}

void fn_801D2A98(register cDailyBugle_VenomBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_80080B34());
    fn_8046B6C8(&ev, fn_801D4E34(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    fn_80082F30(&self->boss);
    fn_80082F30(&self->player);
}

void fn_801D2B5C(register cDailyBugle_VenomBoss *self)
{
    fn_8007D404(self, 2.0f, 80, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801D2BCC(register cDailyBugle_VenomBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    fn_8046B6C8(&ev, fn_801D4E7C(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801D2C80(register cDailyBugle_SpidermanSac *self) // slot 5
{
    fn_8046B710(&self->r30, fn_801D4FA8(self));
    fn_8046B710(&self->boss, fn_800797D4(self));
    fn_8007CF00(self, fn_80080B34(), 0);
    self->f38 = 0;
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
    fn_8007B998(fn_804425F8(&self->boss), 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 0, 10.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 1, 10.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 2, 10.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 3, 10.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 4, 10.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 5, 10.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 6, 75.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 7, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 8, 10.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 9, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 10, 100.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 11, 75.0f);
}

float fn_801D2EF8(register cDailyBugle_SpidermanSac *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h == fn_80080B34())
        return damage;
    if (fn_8007C0AC(&self->boss) / fn_8007C244(&self->boss) < 0.5f)
        fn_8007B288(fn_804425F8(&self->boss));
    return damage;
}

int fn_801D2FC4(register cDailyBugle_SpidermanSac *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    Ref8 r;

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

void fn_801D316C(register cDailyBugle_SpidermanSac *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (self->done) {
        if (h != fn_80080B34())
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
        fn_80081A54(fn_80080B34());
        if (self->bossHit == 0)
            fn_801D3354(self);
        else
            fn_801D3404(self);
    } else if (h == fn_80080B34()) {
        if (self->playerHit == 0)
            fn_801D34A0(self);
        else
            fn_801D3510(self);
        return;
    }
}

void fn_801D3298(register cDailyBugle_SpidermanSac *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 30:
        fn_801D3354(self);
        break;
    case 35:
        fn_801D3404(self);
        break;
    case 40:
        fn_801D34A0(self);
        break;
    case 45:
        fn_801D3510(self);
        break;
    }
}

void fn_801D3354(register cDailyBugle_SpidermanSac *self)
{
    fn_8007D404(self, 2.0f, 35, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_8057230C, 1);
}

void fn_801D3404(register cDailyBugle_SpidermanSac *self)
{
    fn_80081918(fn_80080B34());
    fn_80082AFC(&self->r30, fn_804425F8(&self->r30), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801D34A0(register cDailyBugle_SpidermanSac *self)
{
    fn_8007D404(self, 2.0f, 45, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801D3510(register cDailyBugle_SpidermanSac *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    fn_8046B6C8(&ev, fn_801D4FF0(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801D35C4(register cDailyBugle_LetterEffects *self, int h, int a, int stage, int b, int value) // slot 29
{
    Ref8 ev;

    fn_8046B6C8(&ev, fn_800797D4(self));
    switch (stage) {
    case 1: {
        Ref8 t;

        fn_8046B6C8(&t, fn_801D508C(self));
        fn_80082AFC(&t, fn_804425F8(&t), fn_800797D4(self), 999, 1.0f, 0.0f, 0.0f, 0.0f);
    }
    case 0:
        fn_80083018(&ev, "elecLetterSprks", 27, 0);
        fn_80083018(&ev, "elecLetterSprks", 27, 1);
        fn_80083018(&ev, "elecLetterSprks", 27, 2);
        break;
    }
}

}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 1.0f, 0.0f

extern "C" {

void fn_801D370C(register cDailyBugle_DaredevilBoss *self) // slot 5
{
    fn_8007CF00(self, fn_80080B34(), 0);
    fn_8046B710(&self->boss, fn_800797D4(self));
    self->f90 = 0;
    self->f94 = 0;
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
    self->f74 = 0;
    self->state = 0;
    self->delay = 0.0f;
    self->delayMin = 10.0f;
    self->delayMax = 20.0f;
    self->f84 = 10.0f;
    self->f88 = 15.0f;
    self->f8C = 0.25f;
    fn_8046B710(&self->r60, fn_801D5290(self));
    fn_8046B710(&self->r68, fn_801D52D8(self));
    fn_8046B710(&self->r30[0], fn_801D5128(self));
    fn_8046B710(&self->r30[1], fn_801D5170(self));
    fn_8046B710(&self->r30[2], fn_801D51B8(self));
    fn_8046B710(&self->r30[3], fn_801D5200(self));
    fn_8046B710(&self->r30[4], fn_801D5248(self));
}

void fn_801D38BC(register cDailyBugle_DaredevilBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    float ratio;
    Ref8 p;
    int actor;

    switch (kind) {
    case 10:
        fn_80082AFC(&self->r60, fn_804425F8(&self->r60), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 20:
        ratio = fn_8007C3EC(&self->boss) / fn_8007C52C(&self->boss);
        if (ratio < 0.5f) {
            fn_8046B5A8(&p, fn_80080B34());
            actor = fn_8007C034(&p);
            if (actor) {
                if (fn_8009B04C(actor) == 0x19)
                    fn_801D4738(self);
                else
                    fn_801D4860(self);
            }
        } else
            fn_801D4738(self);
        break;
    case 30:
        if (self->state != 2)
            fn_801D49D8(self);
        break;
    case 40:
        fn_801D4738(self);
        break;
    case 50:
        fn_8046B5A8(&p, fn_80080B34());
        actor = fn_8007C034(&p);
        if (actor && fn_8009B04C(actor) == 0x19) {
            fn_801D4738(self);
            break;
        }
        ratio = fn_8007C3EC(&self->boss) / fn_8007C52C(&self->boss);
        if (ratio < 0.2f) {
            if (self->f74 != 1) {
                Ref8 r;

                fn_8007A4FC(fn_804425F8(&self->boss));
                fn_8046B638(&r, fn_804425F8(&self->boss));
                if (fn_800809CC(&r))
                    fn_800CD6C4(fn_80085928((void *)fn_800809CC(&r)), 0);
                self->f74 = 1;
                fn_8007A448(fn_804425F8(&self->boss));
                fn_80082720(&self->boss, fn_80080B34());
                fn_8007BBB4(fn_804425F8(&self->boss));
            }
        } else if (ratio > 0.75f) {
            fn_801D4738(self);
            break;
        } else {
            Ref8 q;

            fn_8046B638(&q, fn_80080B34());
            Vector from;
            Vector to;
            fn_80082440(&self->boss, &from);
            fn_80082440(&q, &to);
            float dist = fn_804290F8(&from, &to);
            if (dist < 10.0f) {
                if (self->f74 != 2) {
                    fn_8007A4FC(fn_804425F8(&self->boss));
                    fn_8007BC38(fn_804425F8(&self->boss));
                    self->f74 = 2;
                    fn_8007A448(fn_804425F8(&self->boss));
                    fn_80082720(&self->boss, fn_80080B34());
                    fn_8007AA8C(fn_804425F8(&self->boss), fn_80080B34());
                    Ref8 r;
                    fn_8046B638(&r, fn_804425F8(&self->boss));
                    if (fn_800809CC(&r))
                        fn_800CD6C4(fn_80085928((void *)fn_800809CC(&r)), 1);
                }
            } else if (self->f74 != 1) {
                fn_8007A4FC(fn_804425F8(&self->boss));
                Ref8 r;
                fn_8046B638(&r, fn_804425F8(&self->boss));
                if (fn_800809CC(&r))
                    fn_800CD6C4(fn_80085928((void *)fn_800809CC(&r)), 0);
                self->f74 = 1;
                fn_8007A448(fn_804425F8(&self->boss));
                fn_80082720(&self->boss, fn_80080B34());
                fn_8007BBB4(fn_804425F8(&self->boss));
            }
        }
        fn_8007D404(self, self->f8C, 50, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 60:
        fn_801D4738(self);
        break;
    case 62:
        fn_801D4A80(self);
        break;
    case 64:
        fn_801D4B28(self);
        break;
    case 66:
        fn_801D4BBC(self);
        break;
    case 68:
        fn_801D4C24(self);
        break;
    }
}

float fn_801D3F1C(register cDailyBugle_DaredevilBoss *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h == fn_804425F8(&self->boss)) {
        if (self->state == 0) {
        } else if (self->state == 1)
            fn_801D4738(self);
        else if (self->state == 2)
            fn_801D4738(self);
    } else if (h == fn_80080B34()) {
        float ratio = fn_8007C3EC(&self->boss) / fn_8007C52C(&self->boss);

        if (self->state == 0 && ratio < 0.25f && fn_8007BEA8(fn_80080B34())) {
            fn_8007D7C4(self, 50);
            fn_8007D7C4(self, 60);
            fn_8007D7C4(self, 20);
            fn_8007D7C4(self, 30);
            fn_801D4520(self);
            fn_8007D404(self, 0.25f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
    }
    return damage;
}

float fn_801D40C0(register cDailyBugle_DaredevilBoss *self, int h, int node, int value) // slot 37
{
    fn_8007D7C4(self, 30);
    if (self->state != 2)
        fn_801D49D8(self);
    return -1.0f;
}

int fn_801D4128(register cDailyBugle_DaredevilBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    Ref8 r;

    fn_8007D7C4(self, 50);
    fn_8007D7C4(self, 30);
    fn_8007D7C4(self, 20);
    fn_8007D7C4(self, 40);
    fn_8007D7C4(self, 60);
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

void fn_801D430C(register cDailyBugle_DaredevilBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (self->done) {
        if (h != fn_80080B34())
            return;
        return;
    }
    self->done = 1;
    fn_8007D7C4(self, 50);
    fn_8007D7C4(self, 30);
    fn_8007D7C4(self, 20);
    fn_8007D7C4(self, 40);
    fn_8007D7C4(self, 60);
    lbl_8066C724 = 1;
    fn_80081C68();
    fn_80081C94();
    fn_80081CC4();
    fn_80081B40(fn_804425F8(&self->boss));
    if (h == fn_804425F8(&self->boss)) {
        fn_80081A54(fn_80080B34());
        if (self->bossHit == 0)
            fn_801D4A80(self);
        else
            fn_801D4B28(self);
    } else if (h == fn_80080B34()) {
        if (self->playerHit == 0)
            fn_801D4BBC(self);
        else
            fn_801D4C24(self);
        return;
    }
}

void fn_801D4474(register cDailyBugle_DaredevilBoss *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (self->f90 == 0 && self->f94 == 0 && self->state == 0)
        fn_8007D404(self, 2.0f, 40, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801D4520(register cDailyBugle_DaredevilBoss *self)
{
    float r = fn_80171F8C() * 4.656612873077392578125e-10f;
    float range = self->delayMax - self->delayMin;
    float off = r * range;

    self->delay = self->delayMin + off;
}

void fn_801D45BC(register cDailyBugle_DaredevilBoss *self)
{
    float r = fn_80171F8C() * 4.656612873077392578125e-10f;

    if (r < 0.2)
        fn_8046B710(&self->chosen, fn_804425F8(&self->r30[0]));
    else if (r < 0.4)
        fn_8046B710(&self->chosen, fn_804425F8(&self->r30[1]));
    else if (r < 0.6)
        fn_8046B710(&self->chosen, fn_804425F8(&self->r30[2]));
    else if (r < 0.8)
        fn_8046B710(&self->chosen, fn_804425F8(&self->r30[3]));
    else
        fn_8046B710(&self->chosen, fn_804425F8(&self->r30[4]));
}

void fn_801D4738(register cDailyBugle_DaredevilBoss *self)
{
    Ref8 r;

    self->state = 0;
    fn_8007D7C4(self, 50);
    fn_8007D7C4(self, 60);
    fn_8007D7C4(self, 20);
    fn_8007D7C4(self, 30);
    fn_8007BC38(fn_804425F8(&self->boss));
    fn_8007A4FC(fn_804425F8(&self->boss));
    fn_801D4520(self);
    fn_8007D404(self, self->delay, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8046B638(&r, fn_804425F8(&self->boss));
    if (fn_800809CC(&r))
        fn_800CD6C4(fn_80085928((void *)fn_800809CC(&r)), 0);
}

void fn_801D4860(register cDailyBugle_DaredevilBoss *self)
{
    int actor = fn_8007C034(&self->boss);

    if (actor) {
        if (fn_800CDA20(*fn_80085954(actor))) {
            int target = fn_800B1590(fn_800CD9B0(*fn_80085954(actor)));

            if (target)
                fn_800F880C(*fn_80085954(actor), target, 0, 0);
        }
    }
    self->state = 1;
    fn_801D45BC(self);
    fn_8007A4FC(fn_804425F8(&self->boss));
    Vector to;
    fn_80082440(&self->chosen, &to);
    fn_8007D404(self, self->f84, 30, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007A448(fn_804425F8(&self->boss));
    fn_8007A738(fn_804425F8(&self->boss), &to);
}

void fn_801D49D8(register cDailyBugle_DaredevilBoss *self)
{
    self->f74 = 0;
    self->state = 2;
    fn_8007D404(self, self->f8C, 50, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8007D404(self, self->f88, 60, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801D4A80(register cDailyBugle_DaredevilBoss *self)
{
    fn_8007D404(self, 3.0f, 64, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_80572278, 1);
}

void fn_801D4B28(register cDailyBugle_DaredevilBoss *self)
{
    fn_80081918(fn_80080B34());
    fn_80082AFC(&self->r60, fn_804425F8(&self->r60), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801D4BBC(register cDailyBugle_DaredevilBoss *self)
{
    fn_8007D404(self, 2.0f, 68, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801D4C24(register cDailyBugle_DaredevilBoss *self)
{
    fn_80081918(fn_804425F8(&self->boss));
    fn_80082AFC(&self->r68, fn_804425F8(&self->r68), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

cScript *fn_801D4CC0(register cDailyBugle_VenomBoss *self)
{
    return new cDailyBugle_VenomBoss;
}

unsigned int fn_801D4D14(register cDailyBugle_VenomBoss *self)
{
    return fn_800791C8(self, 0);
}

unsigned int fn_801D4D5C(register cDailyBugle_VenomBoss *self)
{
    return fn_800791C8(self, 1);
}

unsigned int fn_801D4DA4(register cDailyBugle_VenomBoss *self)
{
    return fn_800791C8(self, 2);
}

unsigned int fn_801D4DEC(register cDailyBugle_VenomBoss *self)
{
    return fn_800791C8(self, 3);
}

unsigned int fn_801D4E34(register cDailyBugle_VenomBoss *self)
{
    return fn_800791C8(self, 4);
}

unsigned int fn_801D4E7C(register cDailyBugle_VenomBoss *self)
{
    return fn_800791C8(self, 5);
}

unsigned int fn_801D4EC4(register cDailyBugle_VenomBoss *self)
{
    return fn_800791C8(self, 6);
}

unsigned int fn_801D4F0C(register cDailyBugle_VenomBoss *self)
{
    return fn_800791C8(self, 7);
}

cScript *fn_801D4F54(register cDailyBugle_SpidermanSac *self)
{
    return new cDailyBugle_SpidermanSac;
}

unsigned int fn_801D4FA8(register cDailyBugle_SpidermanSac *self)
{
    return fn_800791C8(self, 0);
}

unsigned int fn_801D4FF0(register cDailyBugle_SpidermanSac *self)
{
    return fn_800791C8(self, 1);
}

cScript *fn_801D5038(register cDailyBugle_LetterEffects *self)
{
    return new cDailyBugle_LetterEffects;
}

unsigned int fn_801D508C(register cDailyBugle_LetterEffects *self)
{
    return fn_800791C8(self, 0);
}

cScript *fn_801D50D4(register cDailyBugle_DaredevilBoss *self)
{
    return new cDailyBugle_DaredevilBoss;
}

unsigned int fn_801D5128(register cDailyBugle_DaredevilBoss *self)
{
    return fn_800791C8(self, 0);
}

unsigned int fn_801D5170(register cDailyBugle_DaredevilBoss *self)
{
    return fn_800791C8(self, 1);
}

unsigned int fn_801D51B8(register cDailyBugle_DaredevilBoss *self)
{
    return fn_800791C8(self, 2);
}

unsigned int fn_801D5200(register cDailyBugle_DaredevilBoss *self)
{
    return fn_800791C8(self, 3);
}

unsigned int fn_801D5248(register cDailyBugle_DaredevilBoss *self)
{
    return fn_800791C8(self, 4);
}

unsigned int fn_801D5290(register cDailyBugle_DaredevilBoss *self)
{
    return fn_800791C8(self, 5);
}

unsigned int fn_801D52D8(register cDailyBugle_DaredevilBoss *self)
{
    return fn_800791C8(self, 6);
}

}
