// fn_80095304: G method, pushes the CPU difficulty into slots 0 and 1 when G+0x774 is set (docs/versus.md section 5, row 25).
// fn_8009543C: debug command, puts the named character in player slot `id` (0-4) and returns its actor, 0 on a bad id or name.
// Slot and game-state fields: docs/versus.md section 4.

typedef struct Slot
{
    char unk0[0xB0];
} Slot;

typedef struct GameState
{
    char unk0[0x10];
    Slot slots[8]; // +0x10
} GameState;

typedef struct Frame
{
    char unk0[0x130];
    void *list; // +0x130 the first actor
} Frame;

extern GameState lbl_80552110;
extern char lbl_8052F060[]; // level object
extern Frame *fn_80430050(void *level);
extern int fn_800B13D8(void *actor);
extern void fn_800ACDE0(void *actor);
extern void *fn_800B1AC4(void *actor);
extern int fn_800B0C58(void *actor);
extern void *fn_800B14A0(void *actor);
extern int fn_80085AF0(void *x);
extern void fn_800AE398(void *actor, int a, int b);
extern int fn_80432870(GameState *g);
extern void fn_80443CCC(void *g, int player, int value);
extern int fn_801318A0(void);
extern void *fn_800FD5FC(const char *name, int flag);
extern void fn_8009613C(Slot *slot, void *tmpl);
extern void *fn_8042FF2C(Slot *slot); // slot+0x28, the slot's actor

void fn_80095304(register GameState *g)
{
    void *actor;
    void *next;

    if (fn_80430050(lbl_8052F060) != 0) {
        register Frame *frame = fn_80430050(lbl_8052F060);

        actor = frame->list;
        while (actor != 0) {
            if (fn_800B13D8(actor) == 0)
                fn_800ACDE0(actor);
            next = fn_800B1AC4(actor);
            if (fn_800B0C58(actor) != 0 && fn_80085AF0(fn_800B14A0(actor)) == 0)
                fn_800AE398(actor, 0, 0);
            actor = next;
        }
    }
    if (fn_80432870(g) != 0) {
        fn_80443CCC(&lbl_80552110, 0, fn_801318A0());
        fn_80443CCC(&lbl_80552110, 1, fn_801318A0());
    }
}

void *fn_8009543C(register GameState *g, int id, const char *name)
{
    void *tmpl;

    if (id < 0 ? 1 : id > 4) // not `||`: the DOL has a jump-to-jump on id < 0
        return 0;
    tmpl = fn_800FD5FC(name, 0);
    if (tmpl == 0)
        return 0;
    fn_8009613C(&g->slots[id], tmpl);
    return fn_8042FF2C(&g->slots[id]);
}
