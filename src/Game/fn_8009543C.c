// Debug command: puts the named character in player slot `id` (0-4) and returns its actor, 0 on a bad id or name.
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

extern void *fn_800FD5FC(const char *name, int flag);
extern void fn_8009613C(Slot *slot, void *tmpl);
extern void *fn_8042FF2C(Slot *slot); // slot+0x28, the slot's actor

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
