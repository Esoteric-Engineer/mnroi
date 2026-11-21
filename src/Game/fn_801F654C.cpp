// cCutscenePlay (docs/story.md row 13). Pool read from 0x804A0C88 (extern_pool).

inline int sn_return_decl(int a) { return a; }

struct cScript {
    char d[0x24];
    char *vptr; // +0x24
};

struct Ref8 {
    int unk0;
    int value; // +0x4
};

struct Placement {
    char d[0x40];
    Placement();
};

struct SObjData {
    char pad0[0x198];
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

struct SCtlData {
    char pad0[0x3ac];
};

struct SCtl : SCtlData { // what fn_80085928 returns; vptr at +0x3AC
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual int v22(); // +0xB8
};

struct Ent;

struct Scene {
    char pad0[0x130];
    Ent *first; // +0x130
};

struct cCutscenePlay : cScript { // 0x108
    int linked[0x20];    // +0x28, the handles fn_80081574 / fn_80081528 fill
    int hidden[0x10];    // +0xA8
    int nLinked;         // +0xE8
    int nHidden;         // +0xEC
    int done;            // +0xF0
    int unkF4;           // +0xF4
    int sent;            // +0xF8
    int played;          // +0xFC
    int unk100;          // +0x100
    unsigned int unk104; // +0x104
    cCutscenePlay() __asm__("fn_80468974");
};

extern int lbl_8066B644;
extern int lbl_8066C71C;
extern unsigned int lbl_8066C7DC;
extern char lbl_805723F4[];
extern char lbl_80572278[];
extern char lbl_8054ED80[]; // the clashsp.nsc chronicle
extern char lbl_805526EC[];
extern char lbl_8052F060[];

extern "C" {

int Script_GetOwner(cScript *self);
int Script_GetParamInt(cScript *self, unsigned int i);
unsigned int Script_GetParamUInt(cScript *self, unsigned int i);
float Script_GetParamFloat(cScript *self, unsigned int i);
char *Script_GetParamString(cScript *self, unsigned int i);
void Script_QueueMessage(cScript *self, float seconds, int kind, float a, float b, float c, float d, int e);
void fn_8046CA94(int value);
void fn_8046B638(Ref8 *ev, int h);
void fn_8046B6C8(Ref8 *ev, int h);
void fn_8046B5A8(Ref8 *ev, int h);
void fn_8046B710(Ref8 *ev, int h);
void fn_8046B680(Ref8 *ev, int h);
int fn_804425F8(Ref8 *ev);
int fn_80080A44(Ref8 *ev);
int fn_80080B34();
SActor *fn_800809CC(Ref8 *ev);
int fn_80081E6C(Ref8 *ev);
void fn_80081F8C(Ref8 *ev, int v);
void fn_80082014(Ref8 *ev, int v);
void fn_80082720(Ref8 *ev, int v);
void Script_TriggerEntity(Ref8 *ev, int h, int owner, int kind, float a, float b, float c, float d);
void fn_80082FA4(Ref8 *ev);
void fn_80082F30(Ref8 *ev);
void fn_80082124(Ref8 *ev);
void fn_800826A8(Ref8 *ev, void *pos);
void fn_800825D0(Ref8 *ev, void *pos);
int fn_80083734(const char *name);
void fn_800816A0(int h);
void fn_800815C0(const char *name, cCutscenePlay *self);
void fn_80081AD0(int x);
int fn_80081574(int *out, int max);
int fn_80081528(int *out, int max);
void fn_80435238(void *p, int v);
void fn_8043323C(void *p, int on);
void fn_800528EC();
void fn_800578E4(char *cut, cCutscenePlay *self, int b, int actor, int flags, int c, int d);
void fn_80058A98(char *cut);
void fn_80058A48(char *cut, int i, int b);
void *fn_80427400();
int fn_8042D584(void *p);
void *fn_804326B4(void *list);
int fn_80433E08(void *p);
Scene *fn_80430050(void *p);
Ent *fn_800B1AC4(Ent *e);
int fn_800B0C58(Ent *e);
int fn_800B13D8(Ent *e);
int fn_800B1138(Ent *e);
void fn_800AFFD4(Ent *e, int on);
void fn_8042D7B0(void *p);
SCtl *fn_80085928(void *p);
void *fn_800B1724(int h);
int fn_80048EBC(int a, void *pos, int b, int c, int d, float f, Placement *out);
int fn_800489BC(Placement *p);
int strnicmp(const char *a, const char *b, int n);
int stricmp(const char *a, const char *b);

void fn_801F6B30(cCutscenePlay *self);
void fn_801F6FB8(cCutscenePlay *self);
void fn_801F712C(cCutscenePlay *self, int event);
void fn_801F76B4(cCutscenePlay *self, int h, int value);
void fn_801F7758(cCutscenePlay *self);
void fn_801F7A90(cCutscenePlay *self);
void fn_801F7C68(cCutscenePlay *self);

char * fn_801FA698(cCutscenePlay *self);
int fn_801FA6E0(cCutscenePlay *self);
int fn_801FA728(cCutscenePlay *self);
int fn_801FA770(cCutscenePlay *self);
int fn_801FA7B8(cCutscenePlay *self);
int fn_801FA800(cCutscenePlay *self);
unsigned int fn_801FA848(cCutscenePlay *self);
int fn_801FA890(cCutscenePlay *self);
unsigned int fn_801FA8D8(cCutscenePlay *self);
int fn_801FA920(cCutscenePlay *self);
unsigned int fn_801FA968(cCutscenePlay *self);
int fn_801FA9B0(cCutscenePlay *self);
int fn_801FA9F8(cCutscenePlay *self);
unsigned int fn_801FAA40(cCutscenePlay *self);
int fn_801FAA88(cCutscenePlay *self);
int fn_801FAAD0(cCutscenePlay *self);
unsigned int fn_801FAB18(cCutscenePlay *self);
int fn_801FAB60(cCutscenePlay *self);
int fn_801FABA8(cCutscenePlay *self);
unsigned int fn_801FABF0(cCutscenePlay *self);
int fn_801FAC38(cCutscenePlay *self);
int fn_801FAC80(cCutscenePlay *self);
unsigned int fn_801FACC8(cCutscenePlay *self);
int fn_801FAD10(cCutscenePlay *self);
int fn_801FAD58(cCutscenePlay *self);
unsigned int fn_801FADA0(cCutscenePlay *self);
int fn_801FADE8(cCutscenePlay *self);
int fn_801FAE30(cCutscenePlay *self);
unsigned int fn_801FAE78(cCutscenePlay *self);
int fn_801FAEC0(cCutscenePlay *self);
int fn_801FAF08(cCutscenePlay *self);
unsigned int fn_801FAF50(cCutscenePlay *self);
int fn_801FAF98(cCutscenePlay *self);
int fn_801FAFE0(cCutscenePlay *self);
unsigned int fn_801FB028(cCutscenePlay *self);
int fn_801FB070(cCutscenePlay *self);
int fn_801FB0B8(cCutscenePlay *self);
unsigned int fn_801FB100(cCutscenePlay *self);
int fn_801FB148(cCutscenePlay *self);
int fn_801FB190(cCutscenePlay *self);
unsigned int fn_801FB1D8(cCutscenePlay *self);
int fn_801FB220(cCutscenePlay *self);
int fn_801FB268(cCutscenePlay *self);
unsigned int fn_801FB2B0(cCutscenePlay *self);
int fn_801FB2F8(cCutscenePlay *self);
int fn_801FB340(cCutscenePlay *self);
unsigned int fn_801FB388(cCutscenePlay *self);
int fn_801FB3D0(cCutscenePlay *self);
int fn_801FB418(cCutscenePlay *self);
unsigned int fn_801FB460(cCutscenePlay *self);
int fn_801FB4A8(cCutscenePlay *self);
int fn_801FB4F0(cCutscenePlay *self);
unsigned int fn_801FB538(cCutscenePlay *self);
int fn_801FB580(cCutscenePlay *self);
int fn_801FB5C8(cCutscenePlay *self);
unsigned int fn_801FB610(cCutscenePlay *self);
int fn_801FB658(cCutscenePlay *self);
int fn_801FB6A0(cCutscenePlay *self);
unsigned int fn_801FB6E8(cCutscenePlay *self);
int fn_801FB730(cCutscenePlay *self);
int fn_801FB778(cCutscenePlay *self);
unsigned int fn_801FB7C0(cCutscenePlay *self);
int fn_801FB808(cCutscenePlay *self);
int fn_801FB850(cCutscenePlay *self);
unsigned int fn_801FB898(cCutscenePlay *self);
int fn_801FB8E0(cCutscenePlay *self);
int fn_801FB928(cCutscenePlay *self);
unsigned int fn_801FB970(cCutscenePlay *self);
int fn_801FB9B8(cCutscenePlay *self);
unsigned int fn_801FBA00(cCutscenePlay *self);
int fn_801FBA48(cCutscenePlay *self);
int fn_801FBAA0(cCutscenePlay *self);
unsigned int fn_801FBAE8(cCutscenePlay *self);
int fn_801FBB30(cCutscenePlay *self);
float fn_801FBB78(cCutscenePlay *self);
int fn_801FBBC0(cCutscenePlay *self);
int fn_801FBC08(cCutscenePlay *self);
char * fn_801FBC50(cCutscenePlay *self);
int fn_801FBC98(cCutscenePlay *self);
int fn_801FBCE0(cCutscenePlay *self);
int fn_801FBD38(cCutscenePlay *self);

cScript *fn_801F654C(register cCutscenePlay *self)
{
    return new cCutscenePlay;
}

void fn_801F65A0(register cCutscenePlay *self) // slot 3
{
    self->done = 0;
    self->unkF4 = 0;
    self->sent = 0;
    self->played = 0;
    self->nHidden = 0;
    self->unk104 = 0;
}

void fn_801F65F0(register cCutscenePlay *self) // slot 5
{
    fn_801F7C68(self);
    if (fn_801FA728(self) && self->done == 0) {
        fn_8046CA94(0x1e);
        Script_QueueMessage(self, 0.1f, 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
}

void fn_801F6688(register cCutscenePlay *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (x > 0.0f)
        self->unk104 = x;
    if (self->done == 0) {
        if (fn_801FBB78(self) == 0.0f)
            fn_801F6B30(self);
        else if (fn_801FBB78(self) > 0.0f)
            Script_QueueMessage(self, fn_801FBB78(self), 0x1e, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
}

void fn_801F67DC(register cCutscenePlay *self, int h, int other, int value) // slot 14
{
    Ref8 ev;

    if (self->done == 0) {
        fn_8046B638(&ev, other);
        if (fn_80080A44(&ev))
            fn_801F6B30(self);
    }
}

void fn_801F6854(register cCutscenePlay *self, unsigned char kind, float a, float b, float c, float d, int value) // slot 8
{
    switch (kind) {
    case 10:
        fn_801F6B30(self);
        break;
    case 20:
        fn_801F7758(self);
        break;
    case 30:
        fn_801F6B30(self);
        break;
    case 40:
        fn_80435238(lbl_805723F4, fn_801FBC08(self));
        break;
    }
}

void fn_801F6924(register cCutscenePlay *self, int a, float b, int event, int c) // slot 53
{
    fn_801F712C(self, event);
}

void fn_801F6978(register cCutscenePlay *self, float a, int event, int c) // slot 54
{
    if (event == 0x309)
        fn_8043323C(lbl_80572278, 1);
    fn_801F712C(self, event);
}

void fn_801F69E4(register cCutscenePlay *self, int a, int kind, int c, float x, float y, float z) // slot 51
{
    Ref8 ev;

    switch (kind) {
    case 8:
        if (fn_801FBAA0(self) == a) {
            self->sent = 1;
            fn_8046B6C8(&ev, fn_801FBAE8(self));
            Script_TriggerEntity(&ev, fn_801FBAE8(self), Script_GetOwner(self), fn_801FBB30(self), 0.0f, 0.0f, 0.0f, 0.0f);
        }
        break;
    case 3:
    case 4:
        if (self->sent == 0)
            fn_801F7758(self);
        break;
    case 10:
    case 11:
        fn_801F7758(self);
        break;
    }
}

void fn_801F6B30(register cCutscenePlay *self)
{
    Ref8 player;
    int flags;
    int actor;
    Ref8 ev;

    if (!lbl_8066B644)
        return;
    fn_8046B638(&player, fn_80080B34());
    if (fn_801FBA00(self))
        fn_801F7A90(self);
    if (fn_801FBD38(self))
        fn_800816A0(fn_80080B34());
    if (fn_801FBA48(self))
        fn_80081F8C(&player, 2);
    if (fn_801FA8D8(self))
        fn_80082720(&player, fn_801FA8D8(self));
    if (fn_801FA800(self))
        fn_801F6FB8(self);
    if (fn_801FBBC0(self) > 0)
        fn_80435238(lbl_805723F4, fn_801FBBC0(self));
    if (fn_801FA770(self) == 1) {
        flags = 0;
        if (fn_801FBCE0(self))
            flags = 0x8000000;
        if (strnicmp(fn_801FA698(self), "MA_NYC_M2_A", 11) == 0 || strnicmp(fn_801FA698(self), "NY_WV1_B", 8) == 0)
            flags |= 0x10000000;
        actor = 0;
        if (stricmp(fn_801FBC50(self), "") && stricmp(fn_801FBC50(self), "Invalid Param") && fn_801FBC98(self)) {
            fn_8046B6C8(&ev, fn_80083734(fn_801FBC50(self)));
            if (fn_801FBC98(self) == 1)
                flags |= 0x10000;
            else if (fn_801FBC98(self) == 2)
                flags |= 0x20000;
            actor = fn_80081E6C(&ev);
        }
        fn_800528EC();
        if (strnicmp(fn_801FA698(self), "nycs_sp2_1", 10) == 0
            && (fn_8042D584(fn_80427400()) == 1 || fn_8042D584(fn_80427400()) == 4 || fn_8042D584(fn_80427400()) == 2))
            fn_801F7758(self);
        else
            fn_800578E4(fn_801FA698(self), self, 0, actor, flags, 0, 999);
        fn_80058A98(fn_801FA698(self));
    } else if (fn_801FA770(self) == 2) {
        if (strnicmp(fn_801FA698(self), "mov_2_5", 7) == 0) {
            if (fn_8042D584(fn_80427400()) == 1)
                fn_800815C0("MOV_2_5_FR", self);
            else if (fn_8042D584(fn_80427400()) == 4)
                fn_800815C0("MOV_2_5_IT", self);
            else
                fn_800815C0("MOV_2_5", self);
        } else
            fn_800815C0(fn_801FA698(self), self);
    }
    self->played = 1;
    if (fn_801FA6E0(self))
        self->done = 1;
}

void fn_801F6FB8(register cCutscenePlay *self)
{
    Scene *scene;
    Ent *next;
    Ent *e;
    int found;
    int i;

    self->nLinked = fn_80081574(self->linked, 0x20);
    scene = fn_80430050(lbl_8052F060);
    for (e = scene->first; e; e = next) {
        found = 0;
        next = fn_800B1AC4(e);
        if (!fn_800B0C58(e))
            continue;
        for (i = 0; i < self->nLinked; i++)
            if (fn_800B13D8(e) == self->linked[i])
                found = 1;
        if (!found && !fn_800B1138(e)) {
            self->hidden[self->nHidden++] = fn_800B13D8(e);
            fn_800AFFD4(e, 1);
        }
    }
}

#define EVENT(id, h, value)                                    \
    if (event == id(self))                                     \
        fn_801F76B4(self, h(self), value(self));

void fn_801F712C(register cCutscenePlay *self, int event)
{
    EVENT(fn_801FA920, fn_801FA968, fn_801FA9B0)
    else EVENT(fn_801FA9F8, fn_801FAA40, fn_801FAA88)
    else EVENT(fn_801FAAD0, fn_801FAB18, fn_801FAB60)
    else EVENT(fn_801FABA8, fn_801FABF0, fn_801FAC38)
    else EVENT(fn_801FAC80, fn_801FACC8, fn_801FAD10)
    else EVENT(fn_801FAD58, fn_801FADA0, fn_801FADE8)
    else EVENT(fn_801FAE30, fn_801FAE78, fn_801FAEC0)
    else EVENT(fn_801FAF08, fn_801FAF50, fn_801FAF98)
    else EVENT(fn_801FAFE0, fn_801FB028, fn_801FB070)
    else EVENT(fn_801FB0B8, fn_801FB100, fn_801FB148)
    else EVENT(fn_801FB190, fn_801FB1D8, fn_801FB220)
    else EVENT(fn_801FB268, fn_801FB2B0, fn_801FB2F8)
    else EVENT(fn_801FB340, fn_801FB388, fn_801FB3D0)
    else EVENT(fn_801FB418, fn_801FB460, fn_801FB4A8)
    else EVENT(fn_801FB4F0, fn_801FB538, fn_801FB580)
    else EVENT(fn_801FB5C8, fn_801FB610, fn_801FB658)
    else EVENT(fn_801FB6A0, fn_801FB6E8, fn_801FB730)
    else EVENT(fn_801FB778, fn_801FB7C0, fn_801FB808)
    else EVENT(fn_801FB850, fn_801FB898, fn_801FB8E0)
    else EVENT(fn_801FB928, fn_801FB970, fn_801FB9B8)
}

void fn_801F76B4(register cCutscenePlay *self, int h, int value)
{
    Ref8 ev;

    fn_8046B6C8(&ev, h);
    Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), value, 0.0f, 0.0f, 0.0f, 0.0f);
}

void fn_801F7758(register cCutscenePlay *self)
{
    Ref8 player;
    int i;
    Ref8 ev;

    fn_8046B638(&player, fn_80080B34());
    if (fn_801FBA48(self))
        fn_80082014(&player, 2);
    if (fn_801FA800(self))
        for (i = 0; i < self->nHidden; i++) {
            fn_8046B5A8(&ev, self->hidden[i]);
            fn_80082FA4(&ev);
        }
    if (strnicmp(fn_801FA698(self), "bb_2", 4) == 0) {
        fn_8046B6C8(&ev, fn_80083734("brute"));
        fn_80081F8C(&ev, 2);
    }
    if (lbl_8066C71C && fn_80433E08(fn_804326B4(lbl_8054ED80))) {
        fn_80081AD0(lbl_8066C71C);
        lbl_8066C71C = 0;
    }
    if (fn_801FA848(self)) {
        fn_8046B6C8(&ev, fn_801FA848(self));
        Script_TriggerEntity(&ev, fn_804425F8(&ev), Script_GetOwner(self), fn_801FA890(self), 0.0f, 0.0f, 0.0f, 0.0f);
    }
    if (fn_801FBC08(self) > 0)
        Script_QueueMessage(self, 0.33f, 0x28, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    if (fn_801FA7B8(self) && fn_801FA770(self) == 1) {
        self->nLinked = fn_80081528(self->linked, 0x20);
        fn_8046B638(&ev, 0);
        for (i = 0; i < self->nLinked; i++) {
            fn_8046B710(&ev, self->linked[i]);
            if (!fn_80080A44(&ev))
                fn_80082F30(&ev);
        }
    }
    if (self->unk104 && fn_801FA770(self) == 1)
        lbl_8066C7DC = self->unk104;
}

void fn_801F7A90(register cCutscenePlay *self)
{
    Ref8 player;
    Ref8 target;
    char pos[0x40];

    fn_8046B638(&player, fn_80080B34());
    fn_8046B6C8(&target, fn_801FBA00(self));
    fn_8042D7B0(pos);
    fn_800826A8(&target, pos);
    Placement at;
    int cam = fn_80085928(fn_800809CC(&player))->v22();
    if (cam) {
        Ref8 ev;
        if (fn_80048EBC(cam, fn_800B1724(fn_80081E6C(&target)), 0, 0, fn_800809CC(&player)->v21(), -0.11f, &at)
            && fn_800489BC(&at)) {
            fn_8046B680(&ev, fn_800489BC(&at));
            fn_80082124(&ev);
        }
    }
    fn_800825D0(&player, pos);
}

void fn_801F7C68(register cCutscenePlay *self)
{
    if (self->played)
        return;
    if (strnicmp(lbl_805526EC, "thing_1", 7) == 0) {
        if (strnicmp(fn_801FA698(self), "sp_hc_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "bb_th1_arenaopen", 16) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "bb_1-5", 6) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
        else if (strnicmp(fn_801FA698(self), "bb_2", 4) == 0)
            fn_80058A48(fn_801FA698(self), 3, 0);
    } else if (strnicmp(lbl_805526EC, "thing_2", 7) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_bb_cam_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "th_m2_bb_a", 10) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "storm_1", 7) == 0) {
        if (strnicmp(fn_801FA698(self), "bb_st1_a", 8) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "sp_sf_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "bb_st1_b", 8) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
    } else if (strnicmp(lbl_805526EC, "storm_3", 7) == 0) {
        if (strnicmp(fn_801FA698(self), "bb_20", 5) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
    } else if (strnicmp(lbl_805526EC, "wolverine_b1", 12) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_bb_cam_3", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_wl_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "thing_b1", 8) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_bb_cam_3", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_th_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "venom_2", 7) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_bb_cam_3", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_vn_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "sp_bc_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
    } else if (strnicmp(lbl_805526EC, "wolverine_sac", 13) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_bb_cam_3", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_ml_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "daredevil_b1", 12) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_bb_cam_3", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_dd_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "humantorch_b2", 13) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_bb_cam_2", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_ht_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "daredevil_2", 11) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_gc_cam_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_dd_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "sp_hb_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
        else if (strnicmp(fn_801FA698(self), "dd_m2_gcs_a", 11) == 0)
            fn_80058A48(fn_801FA698(self), 3, 0);
    } else if (strnicmp(lbl_805526EC, "humantorch_1", 12) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_ht_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "ht_gcs_m1_a", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "ht_gcs_m1_b", 11) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
    } else if (strnicmp(lbl_805526EC, "storm_b1", 8) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_gc_cam_2", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_st_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "daredevil_3", 11) == 0) {
        if (strnicmp(fn_801FA698(self), "GCS_15", 6) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_jo_ext_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "ironman_b2", 10) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_gc_cam_3", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_im_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "magneto_3", 9) == 0) {
        if (strnicmp(fn_801FA698(self), "gc_44", 5) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_bh_ext_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "spiderman_1", 11) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_pp_cam_3", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_sp_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "magneto_1", 9) == 0) {
        if (strnicmp(fn_801FA698(self), "PP_MG1_1", 8) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
    } else if (strnicmp(lbl_805526EC, "venom_3", 7) == 0) {
        if (strnicmp(fn_801FA698(self), "pp_26", 5) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "vn_pp_m3_a", 10) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "ironman_3", 9) == 0) {
        if (strnicmp(fn_801FA698(self), "pp_39", 5) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "im_pp_m3_a", 10) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "im_pp_m3_b", 10) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
        else if (strnicmp(fn_801FA698(self), "mp_ml_ext_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 3, 0);
    } else if (strnicmp(lbl_805526EC, "defcon_2", 8) == 0) {
        if (strnicmp(fn_801FA698(self), "dc_m2_rl_a", 10) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "dc_m2_rl_b", 10) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "dc_m2_rl_c", 10) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
        else if (strnicmp(fn_801FA698(self), "mp_end_win_3", 12) == 0)
            fn_80058A48(fn_801FA698(self), 3, 0);
    } else if (strnicmp(lbl_805526EC, "defcon_3", 8) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_dc_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
    } else if (strnicmp(lbl_805526EC, "defcon_4", 8) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_rk_ext_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
    } else if (strnicmp(lbl_805526EC, "humantorch_2", 12) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_ht_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
    } else if (strnicmp(lbl_805526EC, "storm_sac", 9) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_rtf_cam_1", 12) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_a_wl_int_1", 13) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "mp_st_ext_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
        else if (strnicmp(fn_801FA698(self), "mp_a_wl_ext_1", 13) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
    } else if (strnicmp(lbl_805526EC, "daredevil_1", 11) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_db_cam_2", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_dd_int_2", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "dd_m1_db_a", 10) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
    } else if (strnicmp(lbl_805526EC, "ironman_2", 9) == 0) {
        if (strnicmp(fn_801FA698(self), "db_im2", 6) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "db_im2_a", 8) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "elektra_2", 9) == 0) {
        if (strnicmp(fn_801FA698(self), "db_ek2_1", 8) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "db_ek2_2", 8) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "elektra_3", 9) == 0) {
        if (strnicmp(fn_801FA698(self), "db_7", 4) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_a_dd_ext_1", 13) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "storm_b2", 8) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_db_cam_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_st_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "spiderman_3", 11) == 0) {
        if (strnicmp(fn_801FA698(self), "db_30", 5) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "db_34", 5) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "mp_a_vn_ext_1", 13) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "venom_b2", 8) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_db_cam_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_vn_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "wolverine_2", 11) == 0) {
        if (strnicmp(fn_801FA698(self), "am_im1_1", 8) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "am_wv2_aright", 13) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "am_wv2_aleft", 12) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "sp_af_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
    } else if (strnicmp(lbl_805526EC, "storm_2", 7) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_st_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
    } else if (strnicmp(lbl_805526EC, "venom_1", 7) == 0) {
        if (strnicmp(fn_801FA698(self), "am_vn1", 6) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
    } else if (strnicmp(lbl_805526EC, "ironman_1", 9) == 0) {
        if (strnicmp(fn_801FA698(self), "am_im1_1", 8) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_im_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "im_am_m1_a", 10) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
    } else if (strnicmp(lbl_805526EC, "ironman_sac", 11) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_rk_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_im_ext_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "mp_rk_ext_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "elektra_b1", 10) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_am_cam_2", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_el_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "elektra_b2", 10) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_el_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
    } else if (strnicmp(lbl_805526EC, "thing_3", 7) == 0) {
        if (strnicmp(fn_801FA698(self), "el_m1_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_th_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "nycs_th3_1", 10) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
        else if (strnicmp(fn_801FA698(self), "ny_th3_a", 8) == 0)
            fn_80058A48(fn_801FA698(self), 3, 0);
        else if (strnicmp(fn_801FA698(self), "ny_th3_c", 8) == 0)
            fn_80058A48(fn_801FA698(self), 4, 0);
    } else if (strnicmp(lbl_805526EC, "wolverine_1", 11) == 0) {
        if (strnicmp(fn_801FA698(self), "ny_wv1_a", 8) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "ny_wv1_b", 8) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "elektra_1", 9) == 0) {
        if (strnicmp(fn_801FA698(self), "el_m1_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_el_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "sp_hg_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
    } else if (strnicmp(lbl_805526EC, "spiderman_2", 11) == 0) {
        if (strnicmp(fn_801FA698(self), "nycs_sp2_1", 10) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "sm_nyc_m2_b", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "sp_gf_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
        else if (strnicmp(fn_801FA698(self), "sm_nyc_m2_c", 11) == 0)
            fn_80058A48(fn_801FA698(self), 3, 0);
    } else if (strnicmp(lbl_805526EC, "magneto_2", 9) == 0) {
        if (strnicmp(fn_801FA698(self), "mg_m2_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "ma_nyc_m2_a", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "mp_end_win_3", 12) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
    } else if (strnicmp(lbl_805526EC, "thing_b2", 8) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_th_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_nycs_cam_2", 13) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "venom_b1", 8) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_nycs_cam_3", 13) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_vn_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "humantorch_b1", 13) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_nycs_cam_2", 13) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_ht_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "spiderman_b2", 12) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_gc_cam_3", 11) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_sp_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
    } else if (strnicmp(lbl_805526EC, "ironman_b1", 10) == 0) {
        if (strnicmp(fn_801FA698(self), "mp_nycs_cam_1", 13) == 0)
            fn_80058A48(fn_801FA698(self), 0, 0);
        else if (strnicmp(fn_801FA698(self), "mp_im_int_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 1, 0);
        else if (strnicmp(fn_801FA698(self), "mp_im_ext_1", 11) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
        else if (strnicmp(fn_801FA698(self), "mp_a_ht_ext_1", 13) == 0)
            fn_80058A48(fn_801FA698(self), 2, 0);
    }
}

inline int sn_return_decl2(int a) { return a; }

#define PARAM(T, name, reader, i)       \
    T name(register cCutscenePlay *self) \
    {                                   \
        return reader(self, i);         \
    }
#define FLAG(name, reader, i)              \
    int name(register cCutscenePlay *self) \
    {                                      \
        return reader(self, i) != 0;       \
    }

PARAM(char *, fn_801FA698, Script_GetParamString, 0)
PARAM(int, fn_801FA6E0, Script_GetParamInt, 1)
PARAM(int, fn_801FA728, Script_GetParamInt, 2)
PARAM(int, fn_801FA770, Script_GetParamInt, 3)
PARAM(int, fn_801FA7B8, Script_GetParamInt, 4)
PARAM(int, fn_801FA800, Script_GetParamInt, 6)
PARAM(unsigned int, fn_801FA848, Script_GetParamUInt, 7)
PARAM(int, fn_801FA890, Script_GetParamInt, 8)
PARAM(unsigned int, fn_801FA8D8, Script_GetParamUInt, 10)
PARAM(int, fn_801FA920, Script_GetParamInt, 11)
PARAM(unsigned int, fn_801FA968, Script_GetParamUInt, 12)
PARAM(int, fn_801FA9B0, Script_GetParamInt, 13)
PARAM(int, fn_801FA9F8, Script_GetParamInt, 14)
PARAM(unsigned int, fn_801FAA40, Script_GetParamUInt, 15)
PARAM(int, fn_801FAA88, Script_GetParamInt, 16)
PARAM(int, fn_801FAAD0, Script_GetParamInt, 17)
PARAM(unsigned int, fn_801FAB18, Script_GetParamUInt, 18)
PARAM(int, fn_801FAB60, Script_GetParamInt, 19)
PARAM(int, fn_801FABA8, Script_GetParamInt, 20)
PARAM(unsigned int, fn_801FABF0, Script_GetParamUInt, 21)
PARAM(int, fn_801FAC38, Script_GetParamInt, 22)
PARAM(int, fn_801FAC80, Script_GetParamInt, 23)
PARAM(unsigned int, fn_801FACC8, Script_GetParamUInt, 24)
PARAM(int, fn_801FAD10, Script_GetParamInt, 25)
PARAM(int, fn_801FAD58, Script_GetParamInt, 26)
PARAM(unsigned int, fn_801FADA0, Script_GetParamUInt, 27)
PARAM(int, fn_801FADE8, Script_GetParamInt, 28)
PARAM(int, fn_801FAE30, Script_GetParamInt, 29)
PARAM(unsigned int, fn_801FAE78, Script_GetParamUInt, 30)
PARAM(int, fn_801FAEC0, Script_GetParamInt, 31)
PARAM(int, fn_801FAF08, Script_GetParamInt, 32)
PARAM(unsigned int, fn_801FAF50, Script_GetParamUInt, 33)
PARAM(int, fn_801FAF98, Script_GetParamInt, 34)
PARAM(int, fn_801FAFE0, Script_GetParamInt, 35)
PARAM(unsigned int, fn_801FB028, Script_GetParamUInt, 36)
PARAM(int, fn_801FB070, Script_GetParamInt, 37)
PARAM(int, fn_801FB0B8, Script_GetParamInt, 38)
PARAM(unsigned int, fn_801FB100, Script_GetParamUInt, 39)
PARAM(int, fn_801FB148, Script_GetParamInt, 40)
PARAM(int, fn_801FB190, Script_GetParamInt, 41)
PARAM(unsigned int, fn_801FB1D8, Script_GetParamUInt, 42)
PARAM(int, fn_801FB220, Script_GetParamInt, 43)
PARAM(int, fn_801FB268, Script_GetParamInt, 44)
PARAM(unsigned int, fn_801FB2B0, Script_GetParamUInt, 45)
PARAM(int, fn_801FB2F8, Script_GetParamInt, 46)
PARAM(int, fn_801FB340, Script_GetParamInt, 47)
PARAM(unsigned int, fn_801FB388, Script_GetParamUInt, 48)
PARAM(int, fn_801FB3D0, Script_GetParamInt, 49)
PARAM(int, fn_801FB418, Script_GetParamInt, 50)
PARAM(unsigned int, fn_801FB460, Script_GetParamUInt, 51)
PARAM(int, fn_801FB4A8, Script_GetParamInt, 52)
PARAM(int, fn_801FB4F0, Script_GetParamInt, 53)
PARAM(unsigned int, fn_801FB538, Script_GetParamUInt, 54)
PARAM(int, fn_801FB580, Script_GetParamInt, 55)
PARAM(int, fn_801FB5C8, Script_GetParamInt, 56)
PARAM(unsigned int, fn_801FB610, Script_GetParamUInt, 57)
PARAM(int, fn_801FB658, Script_GetParamInt, 58)
PARAM(int, fn_801FB6A0, Script_GetParamInt, 59)
PARAM(unsigned int, fn_801FB6E8, Script_GetParamUInt, 60)
PARAM(int, fn_801FB730, Script_GetParamInt, 61)
PARAM(int, fn_801FB778, Script_GetParamInt, 62)
PARAM(unsigned int, fn_801FB7C0, Script_GetParamUInt, 63)
PARAM(int, fn_801FB808, Script_GetParamInt, 64)
PARAM(int, fn_801FB850, Script_GetParamInt, 65)
PARAM(unsigned int, fn_801FB898, Script_GetParamUInt, 66)
PARAM(int, fn_801FB8E0, Script_GetParamInt, 67)
PARAM(int, fn_801FB928, Script_GetParamInt, 68)
PARAM(unsigned int, fn_801FB970, Script_GetParamUInt, 69)
PARAM(int, fn_801FB9B8, Script_GetParamInt, 70)
PARAM(unsigned int, fn_801FBA00, Script_GetParamUInt, 71)
FLAG(fn_801FBA48, Script_GetParamInt, 72)
PARAM(int, fn_801FBAA0, Script_GetParamInt, 73)
PARAM(unsigned int, fn_801FBAE8, Script_GetParamUInt, 74)
PARAM(int, fn_801FBB30, Script_GetParamInt, 75)
PARAM(float, fn_801FBB78, Script_GetParamFloat, 76)
PARAM(int, fn_801FBBC0, Script_GetParamInt, 77)
PARAM(int, fn_801FBC08, Script_GetParamInt, 78)
PARAM(char *, fn_801FBC50, Script_GetParamString, 79)
PARAM(int, fn_801FBC98, Script_GetParamInt, 80)
FLAG(fn_801FBCE0, Script_GetParamInt, 81)
FLAG(fn_801FBD38, Script_GetParamInt, 82)
}
