// In-match HUD setup: loads hud<LANG>.2/.1 and binds each player's images; see docs/versus.md section 4.4.
// Owns .rodata 0x804829C8-0x80482B00 (the four PMF constants first); fn_80017BC4 is renamed _._6TexRef.

inline int sn_return_decl(int a) { return a; }

class Color
{
public:
    unsigned char a, r, g, b;
};

class Vec2
{
public:
    float x; // +0x0
    float y; // +0x4
    Vec2() __asm__("fn_80426A2C");
};

class Text
{
public:
    char pad[0x80];
    void fn_800FE5A0(int n) __asm__("fn_800FE5A0");
    void fn_80100CAC(const char *s) __asm__("fn_80100CAC");
    int fn_80426E88(int font) __asm__("fn_80426E88");
    void fn_80101188(float h) __asm__("fn_80101188");
    unsigned int fn_80100514(float s) __asm__("fn_80100514");
    unsigned int fn_8010065C() __asm__("fn_8010065C");
    void fn_8042711C(float x, float y) __asm__("fn_8042711C");
    void fn_8042714C(float s) __asm__("fn_8042714C");
    void fn_80100C08(int a) __asm__("fn_80100C08");
    void fn_804270BC(Color *c) __asm__("fn_804270BC");
    void fn_804270E8(Vec2 *v) __asm__("fn_804270E8");
};

class Image
{
public:
    char pad[0x18];
    int f18; // +0x18
    Image() __asm__("fn_804271E4");
};

class HudPlayer
{
public:
    char pad[0x8BB0];
    HudPlayer() __asm__("fn_8000FBB0");
    ~HudPlayer();
};

class TexRef
{
public:
    void *impl; // +0x0, vptr at +0x4
    TexRef(void *&tex, const char *name) __asm__("fn_80017B60");
    virtual ~TexRef();
};

class Hud;
typedef void (Hud::*HudFn)();

class Hud
{
public:
    HudFn f0;              // +0x0
    HudFn f8;              // +0x8
    Text texts[3];         // +0x10
    char bar[0x170];       // +0x190
    char f300[0x1C];       // +0x300
    char f31C[0x24];       // +0x31C
    char res[0x10];        // +0x340
    int count;             // +0x350
    HudPlayer *players;    // +0x354
    void **f358;           // +0x358
    int f35C;              // +0x35C
    char f360[0x3660];     // +0x360
    char f39C0[0x2D0];     // +0x39C0
    int f3C90;             // +0x3C90
    int f3C94;             // +0x3C94
    Image *images;         // +0x3C98
    Image *barImages;      // +0x3C9C
    Image overlays[13];    // +0x3CA0
    char f3E0C[0x1C];      // +0x3E0C
    int f3E28;             // +0x3E28
    Vec2 timePos;          // +0x3E2C
    Vec2 counterPos;       // +0x3E34
    int f3E3C;             // +0x3E3C
    int f3E40;             // +0x3E40
    Text timeMin;          // +0x3E44
    Text timeSec;          // +0x3EC4
    Text timeColon;        // +0x3F44
    char f3FC4[0x1C];      // +0x3FC4
    char f3FE0[0x24];      // +0x3FE0
    int f4004;             // +0x4004
    int f4008;             // +0x4008
    int f400C;             // +0x400C
    char deathBar[0x170];  // +0x4010
    float f4180;           // +0x4180
    float f4184;           // +0x4184
    int f4188;             // +0x4188
    int versus;             // +0x418C

    void fn_8000700C() __asm__("fn_8000700C");
    void fn_80007E30() __asm__("fn_80007E30");
    void fn_80006E5C() __asm__("fn_80006E5C");
    void fn_80007BE8() __asm__("fn_80007BE8");
};

struct Screen
{
    char pad[0x78];
    unsigned short width;  // +0x78
    unsigned short height; // +0x7A
};

struct PadState
{
    char pad[0x7E];
    unsigned short buttons; // +0x7E
};

extern "C" {
int fn_8000394C(register Hud *self);
const char *fn_801311C0(int player);
const char *fn_80130EF8();
void fn_80005B48(Hud *self, const char *name, int slot);
void fn_80007624(Hud *self);
void fn_80007678(Hud *self);
void fn_80017F34(void *res);
int fn_8013086C();
int fn_801308C0();
void fn_80004FA8(Hud *self);
int fn_80427400();
const char *fn_8012EB48(int lang);
int sprintf(char *buf, const char *fmt, ...);
int strcmp(const char *a, const char *b);
void *memset(void *p, int c, unsigned int n);
void fn_80017E3C(void *res, const char *name, int a, int b);
void fn_800061CC(Hud *self);
void fn_8000DF18(void *obj, void *res);
void fn_800059A8(Hud *self, const char *name, Image *image);
void fn_8000E298(void *obj, Image *images);
char *fn_80131060(int player);
void fn_801B738C(char *name);
void fn_8001384C(void *obj, void *res);
Vec2 fn_8000C274(void *res, const char *name, int a, int b, int c);
int fn_800FE284(int index);
void fn_80009B04(void *obj, Color *c);
void fn_80211A84(Vec2 *v);
void *fn_80017FB0(void *res, const char *name);
void fn_8000C474(void **tex, float *a, float *b, float *c, float *d);
void fn_80009FE4(void *bar, TexRef *s, float x, float y, float a, float b, float c, float d, int e, int f);
void fn_8000A214(void *bar, Color *c);
void fn_8000A1E4(void *bar);
void fn_800077C4(Hud *self, int flag);
}

extern Screen *lbl_8066F590;
extern char *lbl_804BFA00[];
extern char *lbl_804BF980[];
extern char *lbl_8066B504[];
extern int lbl_8066C660;
extern char lbl_8057E430[];
extern const int lbl_8066FB70;
extern const signed char lbl_8066FB74;
extern const signed char lbl_8066FB75;
extern const signed char lbl_8066FB77;
extern float lbl_8066D1CC;
extern Color lbl_8066D01C;
extern Color lbl_8066D004;
extern Color lbl_8066D03C;
extern Color lbl_8066D040;

extern "C" void fn_80003808(register Hud *self)
{
    if (fn_8000394C(self)) {
        const char *name0 = fn_801311C0(0);
        const char *name1 = self->versus ? fn_801311C0(1) : fn_80130EF8();
        fn_80005B48(self, name0, 0);
        fn_80005B48(self, name1, 1);
        if (self->versus) {
            self->f8 = &Hud::fn_8000700C;
            self->f0 = &Hud::fn_80007E30;
            fn_80007624(self);
        } else {
            fn_80005B48(self, "Unknown Peon Name", 2);
            self->f8 = &Hud::fn_80006E5C;
            self->f0 = &Hud::fn_80007BE8;
            fn_80007678(self);
        }
        fn_80017F34(self->res);
        self->f3C94 = 0;
    }
}

// fn_8000805C (still asm) reads four of fn_8000394C's pooled strings at offsets from here.
__asm__(".section .rodata\n\t.globl lbl_804829FC\nlbl_804829FC:\n\t.text");

extern "C" int fn_8000394C(register Hud *self)
{
    char buf[128];
    int lang;
    char *suffix;
    int i;
    int p;

    self->f4184 = lbl_8066F590->width;
    self->f4180 = lbl_8066F590->height;
    self->versus = fn_8013086C() || fn_801308C0();
    if (self->players || self->images || self->barImages || self->f358) {
    }
    self->count = self->versus ? 2 : 3;
    self->f358 = new void *[self->count];
    self->players = new HudPlayer[self->count];
    self->images = new Image[self->count * 32];
    self->barImages = new Image[self->count * 2];
    memset(self->images, 0, self->count * 32 * sizeof(Image));
    memset(self->barImages, 0, self->count * 2 * sizeof(Image));
    memset(self->overlays, 0, sizeof(self->overlays));
    fn_80004FA8(self);

    lang = fn_80427400();
    suffix = (char *)fn_8012EB48(lang);
    sprintf(buf, "hud%s.2", suffix);
    lbl_8066C660 = 0;
    fn_80017E3C(self->res, buf, 1, 1);
    lbl_8066C660 = 1;
    fn_800061CC(self);
    fn_8000DF18(self->f39C0, self->res);
    for (i = 0; i <= 12; i++) {
        self->overlays[i].f18 = 0;
        fn_800059A8(self, lbl_804BFA00[i], &self->overlays[i]);
    }
    fn_8000E298(self->f39C0, self->overlays);
    lbl_8066C660 = 0;
    fn_80017F34(self->res);

    sprintf(buf, "hud%s.1", suffix);
    fn_80017E3C(self->res, buf, 1, 1);
    lbl_8066C660 = 1;
    for (p = 0; p < self->count; p++) {
        int j;
        for (j = 0; j <= 31; j++) {
            int idx = p * 32 + j;
            self->images[idx].f18 = 0;
            if (!strcmp(lbl_804BF980[j], "healthBar")) {
                sprintf(buf, "tex_%s_%d", lbl_804BF980[j], p / 2 + 1);
            } else if (!strcmp(lbl_804BF980[j], "portrait")) {
                sprintf(buf, "%s", fn_80131060(p));
                fn_801B738C(buf);
            } else if (!strcmp(lbl_804BF980[j], "portraitRage")) {
                sprintf(buf, "%s_rage", fn_80131060(p));
                fn_801B738C(buf);
            } else {
                sprintf(buf, "tex_%s", lbl_804BF980[j]);
            }
            fn_800059A8(self, buf, &self->images[idx]);
        }
        int k;
        for (k = 0; k <= 1; k++) {
            int idx = p * 2 + k;
            self->barImages[idx].f18 = 0;
            sprintf(buf, "tex_%s_%d", lbl_8066B504[k], p / 2 + 1);
            fn_800059A8(self, buf, &self->barImages[idx]);
        }
    }
    fn_8001384C(self->f360, self->res);

    int xoff = (((PadState *)lbl_8057E430)->buttons & 4) ? lbl_8066FB70 : 0;
    if (self->versus) {
        self->timePos = fn_8000C274(self->res, "text_time", 0, 0, 0);
    } else {
        self->timePos = fn_8000C274(self->res, "text_timeStory", 0, 0, 0);
        self->timePos.x -= xoff / 2;
    }
    self->timeMin.fn_800FE5A0(3);
    self->timeSec.fn_800FE5A0(3);
    self->timeColon.fn_800FE5A0(2);
    self->timeMin.fn_80100CAC("44");
    self->timeSec.fn_80100CAC("44");
    self->timeColon.fn_80100CAC(":");
    self->timeMin.fn_80426E88(fn_800FE284(1));
    self->timeSec.fn_80426E88(fn_800FE284(1));
    self->timeColon.fn_80426E88(fn_800FE284(1));
    self->timeMin.fn_80101188(lbl_8066FB74);
    self->timeSec.fn_80101188(lbl_8066FB75);
    self->timeColon.fn_80101188(lbl_8066FB75);
    float x = self->timePos.x - (self->timeMin.fn_80100514(0.0f) + self->timeColon.fn_80100514(0.0f)
                                 + lbl_8066D1CC * 4.0f + self->timeSec.fn_80100514(0.0f)) / 2.0f;
    self->timeMin.fn_8042711C(x, self->timePos.y - (self->timeMin.fn_8010065C() >> 1));
    x += self->timeMin.fn_80100514(0.0f) + (lbl_8066D1CC + lbl_8066D1CC);
    self->timeColon.fn_8042711C(x, self->timePos.y - (self->timeColon.fn_8010065C() >> 1));
    x += self->timeColon.fn_80100514(0.0f) + (lbl_8066D1CC + lbl_8066D1CC);
    self->timeSec.fn_8042711C(x, self->timePos.y - (self->timeSec.fn_8010065C() >> 1));
    fn_80009B04(self->f3FC4, &lbl_8066D01C);
    self->f4004 = 99;
    self->f4188 = 1;
    self->f3C90 = 1;
    self->f3C94 = 0;

    Vec2 help = fn_8000C274(self->res, "text_help", 0, 0, 0);
    help.x -= xoff;
    fn_80211A84(&help);
    int n;
    for (n = 0; n <= 2; n++) {
        self->texts[n].fn_800FE5A0(3);
        self->texts[n].fn_80426E88(fn_800FE284(1));
        self->texts[n].fn_80101188(lbl_8066FB77);
        self->texts[n].fn_8042714C(0.01f);
        self->texts[n].fn_80100CAC("00");
    }
    self->texts[1].fn_80100CAC("/");
    self->counterPos = fn_8000C274(self->res, "text_counter", 0, 0, 0);
    Vec2 c = self->counterPos;
    c.x += xoff / 2;
    self->texts[0].fn_80100C08(2);
    self->texts[0].fn_804270BC(&lbl_8066D03C);
    self->texts[0].fn_8042711C(c.x - self->texts[1].fn_80100514(0.0f) - (self->texts[0].fn_80100514(0.0f) >> 1), c.y);
    self->texts[1].fn_80100C08(2);
    self->texts[1].fn_804270BC(&lbl_8066D040);
    self->texts[1].fn_804270E8(&c);
    self->texts[2].fn_80100C08(2);
    self->texts[2].fn_804270BC(&lbl_8066D03C);
    self->texts[2].fn_8042711C(self->texts[1].fn_80100514(0.0f) + c.x + (self->texts[0].fn_80100514(0.0f) >> 1), c.y);

    void *tex;
    {
        float a, b, c2, d;
        tex = fn_80017FB0(self->res, "tex_counterBar");
        fn_8000C474(&tex, &a, &b, &c2, &d);
        TexRef s(tex, "tex_counterBar");
        Vec2 pos = fn_8000C274(self->res, "pos_counterBar", 0, 0, 0);
        const float px = pos.x + xoff;
        const float py = pos.y;
        fn_80009FE4(self->bar, &s, px, py, a, b, c2, d, 0, 0);
        fn_8000A214(self->bar, &lbl_8066D01C);
        fn_800077C4(self, 0);
    }
    {
        float a, b, c2, d;
        tex = fn_80017FB0(self->res, "tex_deathBar");
        fn_8000C474(&tex, &a, &b, &c2, &d);
        TexRef s(tex, "tex_deathBar");
        Vec2 pos = fn_8000C274(self->res, "pos_deathBar", 0, 0, 0);
        const float px = pos.x + xoff / 2;
        const float py = pos.y;
        fn_80009FE4(self->deathBar, &s, px, py, a, b, c2, d, 0, 0);
        fn_8000A214(self->deathBar, &lbl_8066D004);
        fn_8000A1E4(self->deathBar);
    }
    lbl_8066C660 = 0;
    return self->f4188;
}
