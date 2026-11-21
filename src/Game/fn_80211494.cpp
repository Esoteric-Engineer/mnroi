// The mission classes cEndMission, cHelpText and cCountDown (docs/story.md row 8).
// Pool read from 0x804A1DC0 (extern_pool).

struct cScript {
    char d[0x24];
    char *vptr; // +0x24
};

struct cEndMission : cScript { // 0x28
    cEndMission() __asm__("fn_80468B08");
};

struct Text { // 0x48
    char d[0x48];
    Text(const char *s, float x, float y, unsigned int color, int flags) __asm__("fn_800FE714");
};

struct cHelpText : cScript { // 0x38
    Text *text;         // +0x28
    unsigned int count; // +0x2C, times shown
    int shown;          // +0x30
    int done;           // +0x34
    cHelpText() __asm__("fn_802116B0");
};

extern char lbl_80593E10[]; // list of live cHelpText
extern char lbl_80503350[]; // cHelpText vtable
extern char lbl_8052F060[];
extern char lbl_80572514[];
extern char lbl_8057E430[];
extern float lbl_8066C76C; // text x
extern float lbl_8066C770; // text y
extern const float lbl_806707F0;
extern const float lbl_806707F4;

struct cCountDown : cScript { // 0x34
    int ms;      // +0x28
    int started; // +0x2C
    int unk30;   // +0x30
    cCountDown() __asm__("fn_80468B54");
};

struct Vec2 {
    float x, y;
};

struct PadState {
    char pad[0x7E];
    unsigned short buttons; // +0x7E
};
extern char lbl_8057229C[];
extern char lbl_8057230C[];
extern char lbl_80572278[];
extern int lbl_8066C724;

extern "C" {

int fn_80080B34();
void fn_8046B638(void *ev, int x);
int fn_800809CC(void *ev);
int fn_80085EEC(int actor);
char *fn_8021245C(cEndMission *self);
int stricmp(const char *a, const char *b);
void fn_8043323C(void *p, int on);
void fn_80081438();
void fn_80081470(char *name);
void fn_8002DB78(void *p);
void fn_80081C68();
void fn_80441FAC(cScript *self);
void fn_8007975C(cScript *self, int inChrg);
void fn_801B6040(void *list, void *e);
void fn_801B6768(void *list, void *e);
int fn_801B6A44(void *list);
cHelpText *fn_801B5D3C(void *list, int i);
void fn_8042AC7C(Text *text, unsigned int color);
void fn_8042AC20(Text *text, float x, float y);
void fn_800FEB38(Text *text, int a, int b, float c, int d, int e, int f, int g);
void fn_80426DF0(Text *text);
void Script_LinkEntity(cScript *self, int handle, int value);
void fn_80100C08(Text *text, int a);
void fn_8042E894(Text *text, int a);
char *fn_802124A4(cHelpText *self);
int fn_800FC3DC(char *name);
void fn_80100CAC(Text *text, int a);
int fn_800FE284(int a);
void fn_80426E88(Text *text, int a);
void fn_80101188(Text *text, float a);
void fn_80426D90(Text *text);
void Script_QueueMessage(cScript *self, float seconds, int kind, float a, float b, float c, float d, int e);
void fn_800FE7E0(Text *text, int inChrg);
float fn_80212540(cCountDown *self);
int fn_80212588(cCountDown *self);
void fn_80131654();
void fn_80131688();
void fn_801316BC(int ms);
void fn_8007D8B0(cScript *self);
void fn_8046B5A8(void *ev, int x);
void fn_8046B6C8(void *ev, int x);
unsigned int fn_802125E0(cCountDown *self);
int fn_8007C034(void *ev);
void fn_80086410(int actor);
void fn_80428EEC(void *p, int v);
void fn_801B5BA8(void *list, int capacity, float grow);
void fn_801B5C74(void *list, int inChrg);
char *Script_GetParamString(cScript *self, unsigned int i);
float Script_GetParamFloat(cScript *self, unsigned int i);
int Script_GetParamInt(cScript *self, unsigned int i);
unsigned int Script_GetParamUInt(cScript *self, unsigned int i);
int fn_804425F8(void *ev);
int Script_GetOwner(cScript *self);
int fn_80212628(cCountDown *self);
void Script_TriggerEntity(void *ev, int a, int b, int c, float d, float e, float f, float g);

void fn_80211494(register cEndMission *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    lbl_8066C724 = 1;
    switch (kind) {
    case 0:
    case 13: {
        char ev[8];

        fn_8046B638(ev, fn_80080B34());
        if (!fn_80085EEC(fn_800809CC(ev))) {
            if (stricmp(fn_8021245C(self), "NOW") == 0)
                fn_8043323C(lbl_8057229C, 1);
            else
                fn_80081438();
        }
        break;
    }
    case 7:
        if (stricmp(fn_8021245C(self), "NOW") == 0)
            fn_8043323C(lbl_8057229C, 0);
        else
            fn_80081470(fn_8021245C(self));
        break;
    case 17:
        fn_8002DB78(lbl_8052F060);
        break;
    case 18:
        fn_8043323C(lbl_8057230C, 1);
        fn_80081C68();
        break;
    case 19:
        fn_8043323C(lbl_80572278, 1);
        break;
    }
}

cScript *fn_80211654(register cHelpText *self)
{
    return new cHelpText;
}

cHelpText *fn_802116B0(register cHelpText *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80503350;
    self->text = 0;
    fn_801B6040(lbl_80593E10, self);
    return self;
}

void fn_80211714(register cHelpText *self, int inChrg)
{
    self->vptr = lbl_80503350;
    fn_801B6768(lbl_80593E10, self);
    fn_8007975C(self, inChrg);
}

}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // "Go back, fool!", 170.0f, 390.0f

extern "C" {

void fn_80211770()
{
    int offset = (((PadState *)lbl_8057E430)->buttons & 4) ? 0x6B : 0;
    int i;

    for (i = 0; i < fn_801B6A44(lbl_80593E10); i++) {
        Text *&text = fn_801B5D3C(lbl_80593E10, i)->text;

        if (text) {
            int j;

            fn_8042AC7C(text, 0xFF000000);
            for (j = 0; j <= 1; j++) {
                int k = j * 2 - 1;
                float dx = k * lbl_806707F0;
                float dy = k * lbl_806707F4;

                fn_8042AC20(text, lbl_8066C76C + dx + offset, lbl_8066C770 + dy);
                fn_800FEB38(text, 0, 0xC, 0.0f, 0, -1, 0, 0);
            }
            fn_8042AC7C(text, 0xFFD6AB3A);
            fn_8042AC20(text, offset + lbl_8066C76C, lbl_8066C770);
            fn_800FEB38(text, 0, 0xC, 0.0f, 0, -1, 0, 0);
        }
    }
}

void fn_802119E8()
{
    int i;

    for (i = 0; i < fn_801B6A44(lbl_80593E10); i++) {
        Text *&text = fn_801B5D3C(lbl_80593E10, i)->text;

        if (text)
            fn_80426DF0(text);
    }
}

void fn_80211A84(Vec2 *pos)
{
    lbl_8066C76C = pos->x;
    lbl_8066C770 = pos->y;
}

void fn_80211ABC(register cHelpText *self) // slot 3
{
    self->shown = 0;
    self->done = 0;
    self->text = 0;
    self->count = 0;
}

void fn_80211AFC(register cHelpText *self) // slot 4
{
    Script_LinkEntity(self, fn_80080B34(), 0);
    if (self->text == 0) {
        self->text = new Text("THIS IS HELP TEXT.", lbl_8066C76C, lbl_8066C770, 0xFFD6AB3A, 0x200);
        if (self->text) {
            fn_80426DF0(self->text);
            fn_80100C08(self->text, 0);
            fn_8042E894(self->text, 200);
        }
    }
}

void fn_80211BB4(register cHelpText *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (self->done || self->count > 1)
        return;
    self->count++;
    if (!self->shown) {
        if (self->text) {
            fn_80100CAC(self->text, fn_800FC3DC(fn_802124A4(self)));
            fn_80426E88(self->text, fn_800FE284(1));
            fn_80101188(self->text, 20.0f);
            fn_80426D90(self->text);
            self->shown = 1;
            Script_QueueMessage(self, 120.0f, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
    } else if (self->text) {
        fn_80426DF0(self->text);
        self->shown = 0;
    }
}

void fn_80211CFC(register cHelpText *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    if (!self->shown)
        return;
    if (self->text) {
        fn_80426DF0(self->text);
        self->shown = 0;
        self->done = 1;
    }
}

void fn_80211D7C(register cHelpText *self) // slot 6
{
    if (self->text) {
        if (self->text)
            fn_800FE7E0(self->text, 3);
        else {
        }
        self->text = 0;
    }
}

void fn_80211DDC(register cHelpText *self, int h, int other, int c, int d, float e, int value) // slot 22
{
    if (h == fn_80080B34() && self->text)
        fn_80426DF0(self->text);
}

void fn_80211E4C(register cCountDown *self) // slot 5
{
    self->started = 0;
    self->unk30 = 0;
    self->ms = (unsigned int)fn_80212540(self) * 1000;
    if (fn_80212540(self) <= 0.0f)
        return;
    if (!fn_80212588(self)) {
        fn_80131688();
        fn_801316BC(self->ms);
        return;
    }
    self->started = 1;
    fn_80131654();
    fn_801316BC(self->ms);
    Script_QueueMessage(self, 1.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    Script_LinkEntity(self, fn_80080B34(), 0);
}

void fn_80211F90(register cCountDown *self, int h, int other, int c, int d, float e, int value) // slot 22
{
    if (h == fn_80080B34()) {
        fn_80131688();
        fn_8007D8B0(self);
    }
}

void fn_80211FF8(register cCountDown *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    switch (kind) {
    case 0:
        if (fn_80212540(self) <= 0.0f)
            return;
        self->started = 1;
        fn_80131654();
        fn_801316BC(self->ms);
        Script_QueueMessage(self, 1.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 7:
        fn_80131688();
        fn_8007D8B0(self);
        break;
    case 999:
        if (self->started && !self->unk30) {
            fn_8007D8B0(self);
            self->unk30 = 1;
            self->started = !self->started;
        } else if (self->unk30) {
            Script_QueueMessage(self, 0.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            self->started = !self->started;
        }
        break;
    }
}

void fn_8021219C(register cCountDown *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        self->ms -= 1000;
        fn_801316BC(self->ms);
        fn_80428EEC(lbl_80572514, self->ms);
        if (self->ms == 0) {
            char ev[8];

            fn_8046B5A8(ev, fn_80080B34());
            if (fn_802125E0(self) && fn_8007C034(ev) && !fn_80085EEC(fn_8007C034(ev))) {
                char target[8];

                fn_80086410(fn_8007C034(ev));
                fn_8046B6C8(target, fn_802125E0(self));
                Script_TriggerEntity(target, fn_804425F8(target), Script_GetOwner(self), fn_80212628(self), 0.0f, 0.0f, 0.0f, 0.0f);
            } else {
                fn_80081470("TOOMUCHTIME");
            }
        } else {
            Script_QueueMessage(self, 1.0f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        }
        break;
    }
}

void fn_80212380(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize)
            fn_801B5BA8(lbl_80593E10, 8, 1.0f);
        else
            fn_801B5C74(lbl_80593E10, 2);
    }
}

}

inline int sn_return_decl(int a) { return a; }

extern "C" {

cScript *fn_80212408(register cEndMission *self)
{
    return new cEndMission;
}

char *fn_8021245C(register cEndMission *self)
{
    return Script_GetParamString(self, 0);
}

char *fn_802124A4(register cHelpText *self)
{
    return Script_GetParamString(self, 0);
}

cScript *fn_802124EC(register cCountDown *self)
{
    return new cCountDown;
}

float fn_80212540(register cCountDown *self)
{
    return Script_GetParamFloat(self, 0);
}

int fn_80212588(register cCountDown *self)
{
    return Script_GetParamInt(self, 1) != 0;
}

unsigned int fn_802125E0(register cCountDown *self)
{
    return Script_GetParamUInt(self, 2);
}

int fn_80212628(register cCountDown *self)
{
    return Script_GetParamInt(self, 3);
}

}

inline void sn_label_decl() { clear:; }

extern "C" {

void fn_80212670(void)
{
    fn_80212380(1, 65535);
}

void fn_802126B4(void)
{
    fn_80212380(0, 65535);
}

}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_80212670;
static void (*const sDtorEntry)(void) __attribute__((section(".dtors"))) = fn_802126B4;
