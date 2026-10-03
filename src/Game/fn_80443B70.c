// Player-slot accessors: the chosen entity name and the in-use flag.
// The slot array is G+0x10, stride 0xB0.

// A player slot in the game-state object. Only the fields these three use are known.
typedef struct Slot
{
    int player;        // +0x00 player index
    char entity[0x20]; // +0x04 chosen character's entity name
    char unk24[0x10];
    int flags;         // +0x34 bit 0: slot in use
} Slot;

extern char *strncpy(char *dst, const char *src, int n);

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
