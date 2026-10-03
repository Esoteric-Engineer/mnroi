// Three leaf accessors: one on a .data table of 0x44-byte records, two on objects that only these functions touch.
// fn_804436D4 before them is unmatched (docs/nonmatching.md), which is why this run is its own unit.

typedef struct Record44
{
    char unk0[0x40];
    int unk40; // +0x40
} Record44;

// dtk types this as a 0xF-byte string; it is really Record44[7], ending where lbl_804CB328 starts.
extern Record44 lbl_804CB14C[];

void fn_8044374C(register int index, register int value)
{
    lbl_804CB14C[index].unk40 = value;
}

typedef struct Unk44C
{
    char unk0[0x44C];
    int unk44C;
} Unk44C;

int fn_80443784(register Unk44C *o)
{
    return o->unk44C;
}

typedef struct Unk150
{
    char unk0[0x150];
    int unk150;
} Unk150;

void fn_804437B0(register Unk150 *o, register int value)
{
    o->unk150 = value;
}
