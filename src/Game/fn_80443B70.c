// Accessors on unrelated objects: a random-name table, an actor factor block, the game-state player slots (G+0x10, stride 0xB0) and two one-offs.
// Field meanings are in docs/versus.md and docs/characters.md.

// The object fn_8009AD80 returns for an actor. Only these four factors are known.
typedef struct Factors
{
    char unk0[0x48];
    float unk48;
    char unk4C[0x8];
    float unk54;
    float unk58;
    float unk5C;
} Factors;

float fn_804439E8(register Factors *f)
{
    return f->unk48 * f->unk54 * f->unk58 * f->unk5C;
}

// The table at fn_804326B4(lbl_8054EF38): three name lists, each with its own count.
typedef struct NameTable
{
    char unk0[0x340];
    char list0[3][0x20]; // +0x340
    char list1[3][0x20]; // +0x3A0
    char list2[3][0x20]; // +0x400
    char unk460[0x1B];
    unsigned char count0; // +0x47B
    unsigned char count1;
    unsigned char count2;
} NameTable;

char *fn_80443A2C(register NameTable *t, register int index)
{
    return t->list0[index];
}

char *fn_80443A68(register NameTable *t, register int index)
{
    return t->list1[index];
}

char *fn_80443AA4(register NameTable *t, register int index)
{
    return t->list2[index];
}

int fn_80443AE0(register NameTable *t)
{
    return t->count0;
}

int fn_80443B10(register NameTable *t)
{
    return t->count1;
}

int fn_80443B40(register NameTable *t)
{
    return t->count2;
}

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
    Slot slots[8];  // +0x10
    int numPlayers; // +0x590 active slot count
    char unk594[0x4];
    int curIndex; // +0x598 index into slots
    char unk59C[0x1A8];
    Slot *curSlot; // +0x744 &slots[curIndex]
    char unk748[0x74];
    int unk7BC;
} GameState;

extern char *strncpy(char *dst, const char *src, int n);
extern void fn_804428E0(Slot *slot, int value);
extern void *fn_8042FF2C(Slot *slot); // slot+0x28, the slot's actor

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

void fn_80443D1C(register GameState *g, register int index)
{
    g->curIndex = index;
}

void *fn_80443D44(register GameState *g, register int player)
{
    if (player < 0 || player >= g->numPlayers) {
        return 0;
    } else {
        return fn_8042FF2C(&g->slots[player]);
    }
}

int fn_80443DBC(register GameState *g)
{
    g->curSlot = &g->slots[g->curIndex];
    return 1;
}

// Not a Slot: fn_80095EAC passes its own +0x68 pointer. Only this field is known.
typedef struct Unk68
{
    char unk0[0x44];
    int unk44;
} Unk68;

void fn_80443DF8(register Unk68 *obj, register int value)
{
    obj->unk44 = value;
}

// A seed passed by pointer; callers build one on the stack and draw from it.
typedef struct Random
{
    int seed;
} Random;

extern float fn_8042CE28(unsigned int value); // unsigned int -> float
extern const float lbl_8048A514[]; // 1/2^31, in the 0x8009xxxx file's literal pool

float fn_80443E20(register Random *r)
{
    float value = fn_8042CE28(r->seed & 0x7FFFFFFF) * lbl_8048A514[0];
    r->seed = r->seed * 0x19660D + 0x3C6EF35F;
    return value;
}
