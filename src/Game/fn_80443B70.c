// Player-slot accessors, plus two on the game-state object itself.
// The slot array is G+0x10, stride 0xB0.

// A player slot in the game-state object. Only the fields these use are known.
typedef struct Slot
{
    int player;        // +0x00 player index
    char entity[0x20]; // +0x04 chosen character's entity name
    char unk24[0x10];
    int flags;         // +0x34 bit 0: slot in use
    int unk38;
    int unk3C;
    float unk40;
    char unk44[0x6C]; // the slot is 0xB0 bytes
} Slot;

typedef struct GameState
{
    char unk0[0x10];
    Slot slots[8]; // +0x10
    char unk590[0x22C];
    int unk7BC;
} GameState;

extern char *strncpy(char *dst, const char *src, int n);
extern void fn_804428E0(Slot *slot, int value);

void fn_80443B70(register Slot *slot, register char *name, register int player)
{
    strncpy(slot->entity, name, 0x20);
    slot->entity[0x1F] = '\0';
    slot->player = player;
}

char *fn_80443BC8(register Slot *slot)
{
    return slot->entity;
}

int fn_80443BF4(register Slot *slot)
{
    return slot->flags & 1;
}

void fn_80443C24(register Slot *slot, register int value)
{
    slot->unk38 = value;
}

void fn_80443C4C(register Slot *slot, register int value)
{
    slot->unk3C = value;
}

float fn_80443C74(register Slot *slot)
{
    return slot->unk40;
}

int fn_80443CA0(register GameState *g)
{
    return g->unk7BC;
}

void fn_80443CCC(register GameState *g, register int player, register int value)
{
    fn_804428E0(&g->slots[player], value);
}
