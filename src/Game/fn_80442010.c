// Leaf accessors on the game-state and name-table objects, plus a bit set; see docs/versus.md section 4.1.

extern int fn_800CD834(int value);

typedef struct BitSet
{
    unsigned int *words;
} BitSet;

// An object with float parameters at +0x598-0x5E0 and a bit set at +0x500; not G, whose +0x598 is an int.
typedef struct Obj
{
    char unk0[0x18];
    int unk18;
    char unk1C[0x4];
    int unk20;
    char unk24[0x4DC];
    BitSet bits; // +0x500
    int unk504;
    char unk508[0x24];
    int unk52C;
    int unk530;
    char unk534[0x64];
    float unk598;
    float unk59C;
    char unk5A0[0x10];
    float unk5B0;
    float unk5B4;
    float unk5B8;
    float unk5BC;
    char unk5C0[0x4];
    float unk5C4;
    float unk5C8;
    char unk5CC[0x8];
    float unk5D4;
    float unk5D8;
    float unk5DC;
    float unk5E0;
} Obj;

char *fn_80442010(register Obj *o)
{
    return (char *)o + 0x20;
}

int fn_8044203C(register Obj *o)
{
    return fn_800CD834(o->unk52C);
}

int fn_80442080(register Obj *o)
{
    return o->unk530;
}

char *fn_804420AC(register Obj *o)
{
    return (char *)o + 0x210;
}

char *fn_804420D8(register Obj *o)
{
    return (char *)o + 0xD0;
}

int fn_80442104(register Obj *o)
{
    return *(int *)((char *)o + 0x204);
}

void fn_8044243C(register BitSet *b, register unsigned int bit);
void fn_804424A0(register BitSet *b, register unsigned int bit);
int fn_80442508(register BitSet *b, register unsigned int bit);

void fn_80442130(register Obj *o, register unsigned int bit)
{
    fn_8044243C(&o->bits, bit);
}

void fn_80442174(register Obj *o, register unsigned int bit)
{
    fn_804424A0(&o->bits, bit);
}

int fn_804421B8(register Obj *o, register unsigned int bit)
{
    return fn_80442508(&o->bits, bit);
}

void fn_80442208(register Obj *o, register float v)
{
    o->unk598 = v;
}

void fn_80442230(register Obj *o, register float v)
{
    o->unk59C = v;
}

void fn_80442258(register Obj *o, register float v)
{
    o->unk5B0 = v;
}

void fn_80442280(register Obj *o, register float v)
{
    o->unk5B4 = v;
}

void fn_804422A8(register Obj *o, register float v)
{
    o->unk5B8 = v;
}

void fn_804422D0(register Obj *o, register float v)
{
    o->unk5BC = v;
}

void fn_804422F8(register Obj *o, register float v)
{
    o->unk5C4 = v;
}

void fn_80442320(register Obj *o, register float v)
{
    o->unk5C8 = v;
}

void fn_80442348(register Obj *o, register float v)
{
    o->unk5D4 = v;
}

void fn_80442370(register Obj *o, register float v)
{
    o->unk5D8 = v;
}

void fn_80442398(register Obj *o, register float v)
{
    o->unk5DC = v;
}

void fn_804423C0(register Obj *o, register float v)
{
    o->unk5E0 = v;
}

int fn_804423E8(register Obj *o)
{
    return o->unk18;
}

void fn_80442414(register Obj *o, register int v)
{
    o->unk20 = v;
}

void fn_8044243C(register BitSet *b, register unsigned int bit)
{
    b->words[bit >> 5] |= 1 << (bit & 31);
}

void fn_804424A0(register BitSet *b, register unsigned int bit)
{
    b->words[bit >> 5] &= ~(1 << (bit & 31));
}

int fn_80442508(register BitSet *b, register unsigned int bit)
{
    return (b->words[bit >> 5] & (1 << (bit & 31))) != 0;
}

void fn_8044256C(register void *a, register int b, ...)
{
}

int fn_804425CC(register int *p)
{
    return p[0x6C];
}

int fn_804425F8(register int *p)
{
    return p[1];
}

typedef struct Slot
{
    int unk0;
    char unk4[0x2C];
    int unk30;
    unsigned int flags; // +0x34
    char unk38[0x6];
    unsigned short port; // +0x3E
    char unk40[0x24];
    int unk64;
    char unk68[0x48];
} Slot;

unsigned int fn_80442624(register Slot *s)
{
    return s->port;
}

int fn_80442654(register int *p)
{
    return p[3];
}

int fn_80442680(register int *p)
{
    return p[1];
}

void *fn_804426AC(register void *p)
{
    return p;
}

void fn_804426D4(register unsigned int *p)
{
    *p |= 1;
}

void fn_80442700(register unsigned int *p)
{
    *p &= ~1;
}

int fn_8044272C(register Slot *s)
{
    register int result = 0;

    if (s != 0 && (s->flags & 2)) {
        result = 1;
    }
    return result;
}

unsigned int fn_80442774(register Slot *s)
{
    return s->flags & 4;
}

typedef struct Game
{
    char unk0[0x10];
    Slot slots[8]; // +0x10
    char unk590[0x8];
    int curIndex; // +0x598
    char unk59C[0x1B0];
    int unk74C;
    Slot *cursor; // +0x750
} Game;

int fn_804427A4(register Game *g)
{
    return g->unk74C;
}

Slot *fn_804427D0(register Game *g)
{
    return g->cursor;
}

int fn_804427FC(register Game *g)
{
    g->cursor = &g->slots[g->curIndex];
    return 1;
}

extern void fn_80467428(void *p, int v);
extern void fn_8044427C(void *p, int v);

void fn_80442838(register char *p, register int v)
{
    fn_80467428(p + 0x290, 2);
    fn_8044427C(p, v);
}

int fn_80442888(register Slot *s)
{
    return s->unk30;
}

int fn_804428B4(register Slot *s)
{
    return s->unk64;
}
