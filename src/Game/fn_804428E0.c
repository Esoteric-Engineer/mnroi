// A clamping setter on a player slot (G+0x10, stride 0xB0), then the leaf accessors on the .nvb
// tuning record and on the object that owns those records (whose flags at +0x1AC are a different
// object from actor+0x1AC). Layout and field meanings are in docs/characters.md section 4.

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
    char unk320[0x20];
    char list340[3][0x20];
    char list3A0[3][0x20];
    char list400[3][0x20];
    int unk460;
    int unk464;
    float unk468;
    int unk46C;
    int unk470;
    int unk474;
    unsigned char unk478;
    unsigned char unk479;
    unsigned char unk47A;
    unsigned char count340;
    unsigned char count3A0;
    unsigned char count400;
    char unk47E[2];
    int unk480[4];
    char unk490[0x14];
    char unk4A4[9][0x20];
    int unk5C4;
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

void fn_80442BC0(register NameTable *t, register int a, register int b, register int c, register int d)
{
    t->unk480[0] = a;
    t->unk480[1] = b;
    t->unk480[2] = c;
    t->unk480[3] = d;
}

int fn_80442C00(register NameTable *t, register int index)
{
    return t->unk480[index];
}

void fn_80442C3C(register NameTable *t, register char *name)
{
    strncpy(t->unk240, name, 0x20);
    t->unk240[0x1F] = '\0';
}

void fn_80442C8C(register NameTable *t, register char *name)
{
    if (t->count340 <= 2) {
        strncpy(t->list340[t->count340], name, 0x20);
        t->list340[t->count340][0x1F] = '\0';
        t->count340++;
    }
}

void fn_80442D24(register NameTable *t, register char *name)
{
    if (t->count3A0 <= 2) {
        strncpy(t->list3A0[t->count3A0], name, 0x20);
        t->list3A0[t->count3A0][0x1F] = '\0';
        t->count3A0++;
    }
}

void fn_80442DBC(register NameTable *t, register char *name)
{
    if (t->count400 <= 2) {
        strncpy(t->list400[t->count400], name, 0x20);
        t->list400[t->count400][0x1F] = '\0';
        t->count400++;
    }
}

void fn_80442E54(register NameTable *t, register int value)
{
    t->unk464 = value;
}

int fn_80442E7C(register NameTable *t)
{
    return t->unk460;
}

void fn_80442EA8(register NameTable *t, register int value)
{
    t->unk460 = value;
}

void fn_80442ED0(register NameTable *t, register float value)
{
    t->unk468 = value;
}

void fn_80442EF8(register NameTable *t, register int value)
{
    t->unk46C = value;
}

void fn_80442F20(register NameTable *t, register int value)
{
    t->unk470 = value;
}

void fn_80442F48(register NameTable *t, register int value)
{
    t->unk474 = value;
}

void fn_80442F70(register NameTable *t, register int value)
{
    t->unk5C4 = value;
}

void fn_80442F98(register NameTable *t, register int value)
{
    t->unk478 = value;
}

int fn_80442FC4(register NameTable *t)
{
    return t->unk478;
}

void fn_80442FF4(register NameTable *t, register int value)
{
    t->unk479 = value;
}

int fn_80443020(register NameTable *t)
{
    return t->unk479;
}

void fn_80443050(register NameTable *t, register int value)
{
    t->unk47A = value;
}

int fn_8044307C(register NameTable *t)
{
    return t->unk47A;
}

void fn_804430AC(register NameTable *t, register char *name)
{
    strncpy(t->unk320, name, 0x20);
    t->unk320[0x1F] = '\0';
}

void fn_804430FC(register NameTable *t, register char *n0, register char *n1, register char *n2,
                 register char *n3, register char *n4, register char *n5, register char *n6,
                 register char *n7, register char *n8)
{
    strncpy(t->unk4A4[0], n0, 0x20);
    t->unk4A4[0][0x1F] = '\0';
    strncpy(t->unk4A4[1], n1, 0x20);
    t->unk4A4[1][0x1F] = '\0';
    strncpy(t->unk4A4[2], n2, 0x20);
    t->unk4A4[2][0x1F] = '\0';
    strncpy(t->unk4A4[3], n3, 0x20);
    t->unk4A4[3][0x1F] = '\0';
    strncpy(t->unk4A4[4], n4, 0x20);
    t->unk4A4[4][0x1F] = '\0';
    strncpy(t->unk4A4[5], n5, 0x20);
    t->unk4A4[5][0x1F] = '\0';
    strncpy(t->unk4A4[6], n6, 0x20);
    t->unk4A4[6][0x1F] = '\0';
    strncpy(t->unk4A4[7], n7, 0x20);
    t->unk4A4[7][0x1F] = '\0';
    strncpy(t->unk4A4[8], n8, 0x20);
    t->unk4A4[8][0x1F] = '\0';
}

int fn_8044324C(register NameTable *t, register int enable)
{
    if (enable) {
        return t->unk464 |= 0x4000;
    } else {
        return t->unk464 &= ~0x4000;
    }
}

void fn_804432AC(register NameTable *t)
{
    t->unk464 |= 0x8000;
}

int fn_804432D8(register NameTable *t)
{
    return t->unk464 & 0x4000;
}

int fn_80443308(register NameTable *t)
{
    return t->unk464 & 0x2;
}

int fn_80443338(register NameTable *t)
{
    return t->unk464 & 0x4;
}

int fn_80443368(register NameTable *t)
{
    return t->unk464 & 0x10;
}

int fn_80443398(register NameTable *t)
{
    return t->unk464 & 0x200;
}

int fn_804433C8(register NameTable *t)
{
    return t->unk464 & 0x8;
}

int fn_804433F8(register NameTable *t)
{
    return t->unk464 & 0x20;
}

int fn_80443428(register NameTable *t)
{
    return t->unk464 & 0x100;
}

int fn_80443458(register NameTable *t)
{
    return t->unk464 & 0x800;
}

int fn_80443488(register NameTable *t)
{
    return t->unk464 & 0x80;
}

typedef struct Flags1AC
{
    char unk0[0x1AC];
    int flags; // +0x1AC
} Flags1AC;

int fn_804434B8(register Flags1AC *o)
{
    return o->flags & 0x1;
}

int fn_804434E8(register Flags1AC *o)
{
    return o->flags & 0x10;
}

void fn_80443518(register Flags1AC *o, register int bits)
{
    o->flags |= bits;
}

void fn_80443548(register Flags1AC *o, register int bits)
{
    o->flags &= ~bits;
}

void fn_8044357C(register Flags1AC *o, register int value)
{
    o->flags = value;
}

int fn_804435A4(register Flags1AC *o)
{
    return o->flags;
}

typedef struct Record44
{
    char unk0[0x40];
    int unk40; // +0x40
} Record44;

extern int lbl_804CBE94[];
extern Record44 lbl_804CB328[];
extern Record44 lbl_804CBEB8[];

void fn_804435D0(register int index, register int value)
{
    lbl_804CBE94[index] = value;
}

void fn_80443608(register int index, register int value)
{
    lbl_804CB328[index].unk40 = value;
}

void fn_80443640(register int index, register int value)
{
    lbl_804CBEB8[index].unk40 = value;
}

// One roster entry; the full layout is in docs/characters.md section 2.
typedef struct CharacterRecord
{
    char unk0[0x48];
    int unlocked; // +0x48
} CharacterRecord;

extern CharacterRecord *fn_80431CCC(register int index, register int remap, register int alt);

CharacterRecord *fn_80443678(register int index, register int remap, register int alt)
{
    register CharacterRecord *tmp = fn_80431CCC(index, remap, alt);
    CharacterRecord *rec = tmp;

    return rec;
}
