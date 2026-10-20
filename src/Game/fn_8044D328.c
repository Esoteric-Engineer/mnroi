// Leaf accessors and fill loops on the roster tables lbl_804CBE94, lbl_804CB328, lbl_804CBEB8, lbl_804CB14C; see docs/versus.md section 5, row 2.

extern int lbl_804CBE94[];

typedef struct Obj
{
    char unk0[0xC];
    int tbl[0x6A]; // +0xC, indexed by idx
    int idx;       // +0x1B4
} Obj;

// 0x44-byte records with a word at +0x40.
typedef struct Rec
{
    char unk0[0x40];
    int val; // +0x40
} Rec;

extern Rec lbl_804CB328[];
extern Rec lbl_804CBEB8[];
extern Rec lbl_804CB14C[];

char *fn_8044D328(register char *self)
{
    return self + 0x2C0;
}

int fn_8044D354(register Obj *self)
{
    return self->tbl[self->idx];
}

void fn_8044D390(register char *self, register int v)
{
    *(int *)(self + 0x1A8) = v;
}

int fn_8044D3B8(register int i)
{
    return lbl_804CBE94[i];
}

void fn_8044D3F4(register int v)
{
    int i;
    i = 0;
    while (i <= 8) {
        lbl_804CBE94[i] = v;
        i++;
    }
}

int fn_8044D454(register int i)
{
    return lbl_804CB328[i].val;
}

void fn_8044D490(register int v)
{
    int i;
    i = 0;
    while (i <= 0x2A) {
        lbl_804CB328[i].val = v;
        i++;
    }
}

int fn_8044D4F0(register int i)
{
    return lbl_804CBEB8[i].val;
}

void fn_8044D52C(register int v)
{
    int i;
    i = 0;
    while (i <= 0x18) {
        lbl_804CBEB8[i].val = v;
        i++;
    }
}

Rec *fn_8044D58C(register int i)
{
    return &lbl_804CB14C[i];
}

int fn_8044D5C4(register int i)
{
    return lbl_804CB14C[i].val;
}

extern void fn_8044D90C(char *slot, int v);

// Sets the word at +0x80 of slot idx; the slots are 0xB0 bytes from +0x10.
void fn_8044D600(register char *self, register int idx, register int v)
{
    fn_8044D90C(self + (idx * 0xB0 + 0x10), v);
}

int fn_8044D650(register int c, register int *out)
{
    if (c > 0x2F && c <= 0x39) {
        *out = c - 0x30;
        return 1;
    } else {
        return 0;
    }
}
