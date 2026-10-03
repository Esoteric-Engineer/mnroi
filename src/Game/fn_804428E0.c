// A clamping setter on a player slot (G+0x10, stride 0xB0), then string setters on the object whose three name lists Game/fn_80443B70.c's getters read.
// Field meanings are in docs/versus.md.

typedef struct Slot
{
    char unk0[0x64];
    int unk64;
} Slot;

void fn_804428E0(register Slot *slot, register unsigned int value)
{
    register unsigned int clamped = value;

    if (clamped > 2) {
        clamped = 2;
    }
    slot->unk64 = clamped;
}

typedef struct NameTable
{
    char unk0[0x20];
    char unk20[0x200];
    char unk220[0x20];
    char unk240[0x20];
    char unk260[0x20];
    char unk280[0x20];
    char unk2A0[0x20];
    char unk2C0[0x20];
    char unk2E0[0x20];
    char unk300[0x20];
} NameTable;

extern char *strncpy(char *dst, const char *src, int n);

void fn_80442918(register NameTable *t, register char *name)
{
    strncpy(t->unk0, name, 0x20);
    t->unk0[0x1F] = '\0';
}

void fn_80442964(register NameTable *t, register char *name)
{
    strncpy(t->unk20, name, 0x200);
    t->unk20[0x1FF] = '\0';
}

void fn_804429B4(register NameTable *t, register char *name)
{
    strncpy(t->unk280, name, 0x20);
    t->unk280[0x1F] = '\0';
}

void fn_80442A04(register NameTable *t, register char *name)
{
    strncpy(t->unk260, name, 0x20);
    t->unk260[0x1F] = '\0';
}

char *fn_80442A54(register NameTable *t)
{
    return t->unk2A0;
}

void fn_80442A80(register NameTable *t, register char *name)
{
    strncpy(t->unk2A0, name, 0x20);
    t->unk2A0[0x1F] = '\0';
}

void fn_80442AD0(register NameTable *t, register char *name)
{
    strncpy(t->unk2E0, name, 0x20);
    t->unk2E0[0x1F] = '\0';
}

void fn_80442B20(register NameTable *t, register char *name)
{
    strncpy(t->unk2C0, name, 0x20);
    t->unk2C0[0x1F] = '\0';
}

void fn_80442B70(register NameTable *t, register char *name)
{
    strncpy(t->unk300, name, 0x20);
    t->unk300[0x1F] = '\0';
}
