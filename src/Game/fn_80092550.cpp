// Resets every slot's actor for a new round and plays PLAYER field 202 (the teleport effect) on it.
// Owns the .rodata pool 0x8048A354-0x8048A368.

class Player
{
public:
    char pad0[0x78];
    int unk78;  // +0x78
    char pad7C[0x4];
    int unk80;  // +0x80
    int unk84;  // +0x84
};

class Actor
{
public:
    char pad0[0x30];
    unsigned flags;  // +0x30
    char pad34[0x264];
    float unk298;    // +0x298
    float unk29C;    // +0x29C
    char pad2A0[0x5C];
    Player *player;  // +0x2FC
};

class Frame
{
public:
    char pad0[0x130];
    Actor *list;  // +0x130
};

class Global
{
public:
    char pad0[0x28];
    int unk28;  // +0x28
};

class GameState
{
public:
    char pad0[0x590];
    int numPlayers;  // +0x590
    char pad594[0x1C8];
    int timerMode;   // +0x75C
    int phase;       // +0x760
};

extern "C" {
extern char lbl_8052F060[];
extern char lbl_80571FC4[];
extern char lbl_8057200C[];
extern char lbl_80593BE8[];
extern GameState lbl_80552110;
extern Global *lbl_8066D650;
extern int lbl_8066B700;

int fn_8009404C(GameState *g);
Frame *fn_80430050(void *p);
void fn_800528EC();
void fn_80092A84(GameState *g);
Actor *fn_80443D44(GameState *g, int player);
void fn_803934E4(Actor *a, int v);
void fn_80095504(GameState *g, Actor *a, Frame *f, int i, int x, int y);
void fn_80086CDC(Actor *a, int v);
int fn_80085EEC(Actor *a);
int fn_8043B31C(Player *p);
int fn_80086B1C(Actor *a);
void fn_8009E230(Actor *a);
int fn_80086B6C(Actor *a);
void fn_8009E09C(Actor *a);
void fn_80086AAC(Actor *a, float v);
void fn_8008643C(Actor *a);
void fn_80031048(Actor *a, float x, float y, int b, int c);
void fn_80428EEC(void *p, int v);
float fn_80086614(Actor *a);
float fn_80086640(Actor *a);
Actor *fn_80085928(Actor *a);
int fn_800CDA20(Actor *a);
void fn_800F9754(Actor *a);
void fn_800CD4CC(Actor *a, int v);
void fn_800CD5EC(Actor *a, int v);
void fn_800CC540(Actor *a);
int fn_800ACD20(Actor *a, int id);
void *fn_80393D0C(Actor *a, int id, int x, int y);
int fn_8042EFF8(void *p);
Actor *fn_800B1AC4(Actor *a);
int fn_800B0CC0(Actor *a);
Actor *fn_800B24AC(Actor *a);
int fn_800B1D48(Actor *a);
void *fn_80318EB4(Actor *a);
float fn_8043BA58(void *p);
int fn_800B10D8(Actor *a);
void fn_800AFFD4(Actor *a, int v);
void fn_800AE398(Actor *a, int x, int y);
float fn_800A40AC(Actor *a);
void fn_80132D50();
void fn_8007FE68();
}

extern "C" void fn_80092550(register GameState *self, int unused)
{
    Frame *frame;
    unsigned int i;
    Actor *actor;
    float t;
    Actor *p;
    Actor *q;
    Actor *r;

    if (fn_8009404C(self) != 0)
        return;
    if (self->phase != 6 && self->phase != 10)
        return;
    frame = fn_80430050(lbl_8052F060);
    fn_800528EC();
    fn_80092A84(self);
    for (i = 0; i < self->numPlayers; i++) {
        actor = fn_80443D44(self, i);
        fn_803934E4(actor, 1);
        fn_80095504(self, actor, frame, i, 0, 0);
        actor->flags &= ~2;
        actor->flags &= ~0x200;
        fn_80086CDC(actor, 0);
        if (fn_80085EEC(actor) != 0 || lbl_8066D650->unk28 == fn_8043B31C(actor->player)) {
            if (fn_80086B1C(actor) != 0)
                fn_8009E230(actor);
            if (fn_80086B6C(actor) != 0)
                fn_8009E09C(actor);
            fn_80086AAC(actor, 0.0f);
            fn_8008643C(actor);
            fn_80031048(actor, 1.0f, 1.0f, 0, 1);
            if (self->timerMode == 2 && actor->player->unk80 - actor->player->unk78 == 1)
                fn_80428EEC(lbl_80571FC4, fn_8043B31C(actor->player));
        } else {
            t = fn_80086614(actor) / fn_80086640(actor) + 0.2f >= 0.0f
                    ? (fn_80086614(actor) / fn_80086640(actor) + 0.2f <= fn_80086640(actor)
                           ? fn_80086614(actor) / fn_80086640(actor) + 0.2f
                           : fn_80086640(actor))
                    : 0.0f;
            fn_80031048(actor, t, 1.0f, 0, 0);
            fn_8008643C(actor);
        }
        p = fn_80085928(actor);
        if (p != 0 && fn_800CDA20(p) != 0)
            fn_800F9754(p);
        if (p != 0) {
            fn_800CD4CC(p, 0);
            fn_800CD5EC(p, 0);
            fn_800CC540(p);
        }
        fn_80393D0C(actor, fn_800ACD20(actor, 0xCA), 0xFF, 0xFF);
        actor->player->unk84 = fn_8042EFF8(lbl_80593BE8) + 1000;
    }
    for (p = frame->list; p != 0; p = actor) {
        actor = fn_800B1AC4(p);
        if (fn_800B0CC0(p) == 0)
            continue;
        q = p;
        r = fn_800B24AC(q);
        if (r != 0 && fn_800B1D48(q) == 3 && fn_8043BA58(fn_80318EB4(r)) > 9.0f) {
            if (fn_800B10D8(q) != 0)
                fn_800AFFD4(q, 1);
            else
                fn_800AE398(q, 0, 0);
        } else if (q->unk29C > 0.0f && fn_800A40AC(q) < 0.55f) {
            q->unk298 = q->unk29C * 0.55f;
        }
    }
    fn_80132D50();
    fn_8007FE68();
    lbl_8066D650->unk28 = -1;
    fn_80428EEC(lbl_8057200C, 0);
    lbl_80552110.phase = 4;
    lbl_8066B700 = 0;
}
