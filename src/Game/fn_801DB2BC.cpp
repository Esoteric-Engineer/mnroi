// The NYC Streets classes cNYCStreets_DaredevilBoss, cNYCStreetsMP_SegmentControl, cNYCStreets_ThingBoss and cNYCStreets_TorchBoss (docs/story.md row 15).
// Pool read from 0x804A00D8 (extern_pool).

inline int sn_return_decl(int a) { return a; }

struct cScript {
    char d[0x24];
    char *vptr; // +0x24
};

struct Ref8 {
    int unk0;
    int value; // +0x4
};

struct cNYCStreets_DaredevilBoss : cScript { // 0x98
    Ref8 boss;     // +0x28
    Ref8 player;   // +0x30
    Ref8 r38[3];   // +0x38
    Ref8 target;   // +0x50, param 3
    Ref8 r58[2];   // +0x58
    char pad68[0xC];
    int f74;       // +0x74
    int f78;       // +0x78
    int f7C;       // +0x7C
    int f80;       // +0x80
    int done;      // +0x84
    int bossHit;   // +0x88, a kind-8 hit over 90000 on the boss
    int playerHit; // +0x8C, the same on the player
    int f90;       // +0x90
    float scale;   // +0x94
    cNYCStreets_DaredevilBoss() __asm__("fn_8046AFDC");
};

struct cNYCStreetsMP_SegmentControl : cScript { // 0x28
    cNYCStreetsMP_SegmentControl() __asm__("fn_8046B090");
};

struct cNYCStreets_ThingBoss : cScript { // 0x60
    Ref8 boss;     // +0x28, param 0
    Ref8 r30;      // +0x30, param 1
    Ref8 player;   // +0x38
    int f40;       // +0x40
    int armored;   // +0x44
    int f48;       // +0x48
    int bossHit;   // +0x4C
    int playerHit; // +0x50
    int done;      // +0x54
    float health;  // +0x58
    float limit;   // +0x5C
    cNYCStreets_ThingBoss() __asm__("fn_8046B0DC");
};

struct cNYCStreets_TorchBoss : cScript { // 0x44
    Ref8 boss;     // +0x28
    Ref8 player;   // +0x30
    int done;      // +0x38
    int bossHit;   // +0x3C
    int playerHit; // +0x40
    cNYCStreets_TorchBoss() __asm__("fn_8046B154");
};

extern char lbl_805526EC[];
extern char lbl_8057230C[];
extern int lbl_8066C71C;
extern int lbl_8066C724;

extern "C" {

int stricmp(const char *a, const char *b);
int fn_800797D4(cScript *self);
unsigned int fn_800791C8(cScript *self, unsigned int i);
void fn_8007D404(cScript *self, float seconds, int kind, float a, float b, float c, float d, int e);
int fn_8007D7C4(cScript *self, unsigned char kind);
int fn_8007D8B0(cScript *self);
int fn_8007CF00(cScript *script, int handle, int value);
int fn_80080B34();
int fn_804425F8(void *ev);
void fn_8046B638(void *ev, int x);
void fn_8046B680(void *ev, int x);
void fn_8046B6C8(void *ev, int x);
void fn_8046B710(void *ev, int x);
int fn_800809CC(void *ev);
void *fn_80085928(void *p);
void fn_800CD6C4(void *c, int on);
void fn_80082AFC(void *ev, int h, int owner, int kind, float a, float b, float c, float d);
void fn_80082720(void *ev, int h);
void fn_80082F30(void *ev);
float fn_8007C244(void *ev);
float fn_8007C0AC(void *ev);
float fn_8007B8F8(int h);
void fn_8007B998(int h, float v);
void fn_8007AA8C(int h, int target);
void fn_8007A4FC(int h);
void fn_8007B288(int h);
void fn_8007B2E8(int h, int which, float v);
void fn_8007B540(int h, int on, int b);
void fn_8007BA24(int h, int state);
void fn_80081C68();
void fn_80081C94();
void fn_80081CC4();
int fn_80081B40(int h);
int fn_80081A54(int h);
void fn_80081918(int h);
void fn_800816A0(int h);
int fn_80081BD4(int h);
void fn_8043323C(void *p, int on);

void fn_801DB884(cNYCStreets_DaredevilBoss *self);
void fn_801DB954(cNYCStreets_DaredevilBoss *self);
void fn_801DBA04(cNYCStreets_DaredevilBoss *self);
void fn_801DBACC(cNYCStreets_DaredevilBoss *self);
void fn_801DBB3C(cNYCStreets_DaredevilBoss *self);
unsigned int fn_801DCF18(cNYCStreets_DaredevilBoss *self);
unsigned int fn_801DCF60(cNYCStreets_DaredevilBoss *self);
unsigned int fn_801DCFA8(cNYCStreets_DaredevilBoss *self);
unsigned int fn_801DD044(cNYCStreetsMP_SegmentControl *self);
void fn_801DC210(cNYCStreets_ThingBoss *self);
void fn_801DC264(cNYCStreets_ThingBoss *self);
void fn_801DC438(cNYCStreets_ThingBoss *self);
void fn_801DC644(cNYCStreets_ThingBoss *self);
void fn_801DC6EC(cNYCStreets_ThingBoss *self);
void fn_801DC780(cNYCStreets_ThingBoss *self);
void fn_801DC7E8(cNYCStreets_ThingBoss *self);
unsigned int fn_801DD0E0(cNYCStreets_ThingBoss *self);
unsigned int fn_801DD128(cNYCStreets_ThingBoss *self);
unsigned int fn_801DD170(cNYCStreets_ThingBoss *self);
void fn_801DCC30(cNYCStreets_TorchBoss *self);
void fn_801DCCE0(cNYCStreets_TorchBoss *self);
void fn_801DCDA0(cNYCStreets_TorchBoss *self);
void fn_801DCE10(cNYCStreets_TorchBoss *self);
unsigned int fn_801DD20C(cNYCStreets_TorchBoss *self);
unsigned int fn_801DD254(cNYCStreets_TorchBoss *self);

void fn_801DB2BC(register cNYCStreets_DaredevilBoss *self) // slot 5
{
    fn_8046B710(&self->boss, fn_800797D4(self));
    fn_8046B710(&self->player, fn_80080B34());
    fn_8007CF00(self, fn_804425F8(&self->player), 0);
    fn_8046B710(&self->target, fn_801DCF18(self));
    self->f74 = 0;
    self->f7C = 0;
    self->f90 = 0;
    self->f78 = 0;
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
    self->scale = fn_8007B8F8(fn_804425F8(&self->boss));
}

float fn_801DB3B4(register cNYCStreets_DaredevilBoss *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    return damage;
}

void fn_801DB3FC(register cNYCStreets_DaredevilBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 46:
        fn_801DB954(self);
        break;
    case 47:
        fn_801DBA04(self);
        break;
    case 48:
        fn_801DBACC(self);
        break;
    case 49:
        fn_801DBB3C(self);
        break;
    case 20:
        fn_801DB884(self);
        break;
    }
}

int fn_801DB4CC(register cNYCStreets_DaredevilBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
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

void fn_801DB5C0(register cNYCStreets_DaredevilBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
{
    if (self->done) {
        if (h != fn_804425F8(&self->player))
            return;
        return;
    }
    fn_8007D7C4(self, 20);
    self->done = 1;
    lbl_8066C724 = 1;
    fn_80081C68();
    fn_80081C94();
    fn_80081CC4();
    fn_80081B40(fn_804425F8(&self->boss));
    if (h == fn_804425F8(&self->boss)) {
        fn_80081A54(fn_804425F8(&self->player));
        if (self->bossHit == 0)
            fn_801DB954(self);
        else
            fn_801DBA04(self);
    } else if (h == fn_804425F8(&self->player)) {
        if (self->playerHit == 0)
            fn_801DBACC(self);
        else
            fn_801DBB3C(self);
    }
}

float fn_801DB714(register cNYCStreets_DaredevilBoss *self, int h, int node, int value) // slot 37
{
    if (self->f74 == 1 && self->f7C == 1) {
        Ref8 r;

        self->f7C = 0;
        fn_8007B998(fn_804425F8(&self->boss), self->scale * 2.0f);
        fn_80082720(&self->boss, fn_80080B34());
        fn_8007AA8C(fn_804425F8(&self->boss), fn_80080B34());
        fn_8046B638(&r, fn_804425F8(&self->boss));
        if (fn_800809CC(&r))
            fn_800CD6C4(fn_80085928((void *)fn_800809CC(&r)), 1);
        fn_8007D404(self, 6.0f, 20, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
    return -1.0f;
}

void fn_801DB884(register cNYCStreets_DaredevilBoss *self)
{
    Ref8 r;

    self->f74 = 0;
    fn_8007D8B0(self);
    fn_8007A4FC(fn_804425F8(&self->boss));
    fn_8007B998(fn_804425F8(&self->boss), self->scale);
    fn_8046B638(&r, fn_804425F8(&self->boss));
    if (fn_800809CC(&r))
        fn_800CD6C4(fn_80085928((void *)fn_800809CC(&r)), 0);
}

void fn_801DB954(register cNYCStreets_DaredevilBoss *self)
{
    fn_8007D404(self, 2.0f, 47, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_8057230C, 1);
}

void fn_801DBA04(register cNYCStreets_DaredevilBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->player));
    lbl_8066C71C = fn_804425F8(&self->player);
    fn_8046B6C8(&ev, fn_801DCF60(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801DBACC(register cNYCStreets_DaredevilBoss *self)
{
    fn_8007D404(self, 2.0f, 49, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801DBB3C(register cNYCStreets_DaredevilBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    lbl_8066C71C = fn_804425F8(&self->boss);
    fn_8046B6C8(&ev, fn_801DCFA8(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801DBC04(register cNYCStreetsMP_SegmentControl *self) // slot 5
{
    if (stricmp(lbl_805526EC, "NYCStreets_MP") == 0 || stricmp(lbl_805526EC, "IronMan_B1") == 0
        || stricmp(lbl_805526EC, "Daredevil_SAC") == 0 || stricmp(lbl_805526EC, "Daredevil_B2") == 0) {
        Ref8 ev;

        fn_8046B680(&ev, 0);
        fn_8046B710(&ev, fn_801DD044(self));
        fn_80082AFC(&ev, fn_801DD044(self), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
    }
}

void fn_801DBD30(register cNYCStreets_ThingBoss *self) // slot 5
{
    fn_8046B710(&self->player, fn_80080B34());
    fn_8046B710(&self->boss, fn_801DD0E0(self));
    fn_8007CF00(self, fn_804425F8(&self->player), 0);
    fn_8007CF00(self, fn_804425F8(&self->boss), 0);
    fn_8046B710(&self->r30, fn_801DD128(self));
    self->f40 = 0;
    self->armored = 0;
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
    self->health = fn_8007C244(&self->boss);
    self->limit = self->health * 0.35f;
    fn_801DC264(self);
}

void fn_801DBE50(register cNYCStreets_ThingBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_801DC210(self);
        break;
    case 40:
        fn_801DC644(self);
        break;
    case 45:
        fn_801DC6EC(self);
        break;
    case 50:
        fn_801DC780(self);
        break;
    case 55:
        fn_801DC7E8(self);
        break;
    }
}

float fn_801DBF2C(register cNYCStreets_ThingBoss *self, int h, int other, int kind, int b, float damage, int c, int value) // slot 21
{
    if (h != fn_804425F8(&self->boss))
        return damage;
    fn_8007D404(self, 0.25f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    return damage;
}

int fn_801DBFE4(register cNYCStreets_ThingBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
{
    fn_8007D7C4(self, 10);
    if (h == fn_804425F8(&self->boss)) {
        if (damage > 90000.0f && kind == 8)
            self->bossHit = 1;
        return 1;
    } else if (h == fn_80080B34()) {
        if (damage > 90000.0f && kind == 8)
            self->playerHit = 1;
        return 1;
    } else {
    }
    return 1;
}

void fn_801DC0D8(register cNYCStreets_ThingBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
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
            fn_801DC644(self);
        else
            fn_801DC6EC(self);
    } else if (h == fn_80080B34()) {
        if (self->playerHit == 0)
            fn_801DC780(self);
        else
            fn_801DC7E8(self);
        return;
    }
}

void fn_801DC210(register cNYCStreets_ThingBoss *self)
{
    if (fn_8007C0AC(&self->boss) < self->limit)
        fn_801DC438(self);
}

void fn_801DC264(register cNYCStreets_ThingBoss *self)
{
    fn_8007B288(fn_804425F8(&self->boss));
    fn_8007B2E8(fn_804425F8(&self->boss), 0, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 1, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 2, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 3, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 4, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 5, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 7, 0.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 8, 0.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 9, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 10, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 11, 95.0f);
}

void fn_801DC438(register cNYCStreets_ThingBoss *self)
{
    if (self->armored != 0)
        return;
    self->armored = 1;
    fn_8007B288(fn_804425F8(&self->boss));
    fn_8007B2E8(fn_804425F8(&self->boss), 0, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 1, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 2, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 3, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 4, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 5, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 7, 50.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 8, 5.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 9, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 10, 95.0f);
    fn_8007B2E8(fn_804425F8(&self->boss), 11, 95.0f);
    fn_8007B540(fn_804425F8(&self->boss), 1, 0);
}

void fn_801DC644(register cNYCStreets_ThingBoss *self)
{
    fn_8007D404(self, 2.0f, 45, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_8057230C, 1);
}

void fn_801DC6EC(register cNYCStreets_ThingBoss *self)
{
    fn_80081918(fn_80080B34());
    fn_80082AFC(&self->r30, fn_804425F8(&self->r30), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801DC780(register cNYCStreets_ThingBoss *self)
{
    fn_8007D404(self, 2.0f, 55, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801DC7E8(register cNYCStreets_ThingBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    fn_8046B6C8(&ev, fn_801DD170(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801DC894(register cNYCStreets_TorchBoss *self) // slot 4
{
    fn_8046B710(&self->boss, fn_800797D4(self));
    fn_8007BA24(fn_800797D4(self), 4);
    fn_8046B710(&self->player, fn_80080B34());
    fn_8007CF00(self, fn_804425F8(&self->player), 0);
    self->done = 0;
    self->bossHit = 0;
    self->playerHit = 0;
}

int fn_801DC948(register cNYCStreets_TorchBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 20
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

void fn_801DCA34(register cNYCStreets_TorchBoss *self, int h, int other, int kind, int b, float damage, int value) // slot 22
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
            fn_801DCC30(self);
        else
            fn_801DCCE0(self);
    } else if (h == fn_804425F8(&self->player)) {
        if (self->playerHit == 0)
            fn_801DCDA0(self);
        else
            fn_801DCE10(self);
    }
}

void fn_801DCB74(register cNYCStreets_TorchBoss *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 1:
        fn_801DCC30(self);
        break;
    case 2:
        fn_801DCCE0(self);
        break;
    case 3:
        fn_801DCDA0(self);
        break;
    case 4:
        fn_801DCE10(self);
        break;
    }
}

void fn_801DCC30(register cNYCStreets_TorchBoss *self)
{
    fn_8007D404(self, 2.0f, 2, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_800816A0(fn_804425F8(&self->boss));
    fn_80081BD4(fn_804425F8(&self->boss));
    fn_8043323C(lbl_8057230C, 1);
}

void fn_801DCCE0(register cNYCStreets_TorchBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->player));
    fn_80082F30(&self->boss);
    fn_8046B6C8(&ev, fn_801DD20C(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801DCDA0(register cNYCStreets_TorchBoss *self)
{
    fn_8007D404(self, 2.0f, 4, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void fn_801DCE10(register cNYCStreets_TorchBoss *self)
{
    Ref8 ev;

    fn_80081918(fn_804425F8(&self->boss));
    fn_8046B6C8(&ev, fn_801DD254(self));
    fn_80082AFC(&ev, fn_804425F8(&ev), fn_800797D4(self), 0, 0.0f, 0.0f, 0.0f, 0.0f);
}

}

inline int sn_return_decl2(int a) { return a; }

extern "C" {

cScript *fn_801DCEC4(register cNYCStreets_DaredevilBoss *self)
{
    return new cNYCStreets_DaredevilBoss;
}

unsigned int fn_801DCF18(register cNYCStreets_DaredevilBoss *self)
{
    return fn_800791C8(self, 3);
}

unsigned int fn_801DCF60(register cNYCStreets_DaredevilBoss *self)
{
    return fn_800791C8(self, 6);
}

unsigned int fn_801DCFA8(register cNYCStreets_DaredevilBoss *self)
{
    return fn_800791C8(self, 7);
}

cScript *fn_801DCFF0(register cNYCStreetsMP_SegmentControl *self)
{
    return new cNYCStreetsMP_SegmentControl;
}

unsigned int fn_801DD044(register cNYCStreetsMP_SegmentControl *self)
{
    return fn_800791C8(self, 0);
}

cScript *fn_801DD08C(register cNYCStreets_ThingBoss *self)
{
    return new cNYCStreets_ThingBoss;
}

unsigned int fn_801DD0E0(register cNYCStreets_ThingBoss *self)
{
    return fn_800791C8(self, 0);
}

unsigned int fn_801DD128(register cNYCStreets_ThingBoss *self)
{
    return fn_800791C8(self, 1);
}

unsigned int fn_801DD170(register cNYCStreets_ThingBoss *self)
{
    return fn_800791C8(self, 2);
}

cScript *fn_801DD1B8(register cNYCStreets_TorchBoss *self)
{
    return new cNYCStreets_TorchBoss;
}

unsigned int fn_801DD20C(register cNYCStreets_TorchBoss *self)
{
    return fn_800791C8(self, 0);
}

unsigned int fn_801DD254(register cNYCStreets_TorchBoss *self)
{
    return fn_800791C8(self, 1);
}

}
