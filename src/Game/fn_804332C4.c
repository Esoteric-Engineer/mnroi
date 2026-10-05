// Small accessors on a pointer array (count +0x8, data +0xC) and on G's current slot; docs/versus.md section 4.1.

typedef struct PtrArray
{
    int unk0;
    int unk4;
    unsigned int count; // +0x8
    void *data[1];      // +0xC
} PtrArray;

typedef struct Slot
{
    char unk0[0xB0];
} Slot;

typedef struct GameState
{
    char unk0[0x10];
    Slot slots[8]; // +0x10
    char unk590[0x8];
    int curIndex; // +0x598 index into slots
} GameState;

extern void *fn_8042E83C(Slot *slot);
extern void *fn_8042FF2C(Slot *slot); // slot+0x28, the slot's actor

void *fn_804332C4(register PtrArray *array, register unsigned int index)
{
    if (index < array->count) {
        return array->data[index];
    }
    return 0;
}

int fn_80433314(register int *self)
{
    return *self;
}

void *fn_80433340(register GameState *g)
{
    return fn_8042E83C(&g->slots[g->curIndex]);
}

Slot *fn_80433394(register GameState *g)
{
    return &g->slots[g->curIndex];
}

void *fn_804333CC(register GameState *g)
{
    return fn_8042FF2C(&g->slots[g->curIndex]);
}
