// Readers of the 0x18-byte entry table at lbl_8066C63C+0x1C (field meanings guessed from use).
typedef struct Entry
{
    float f0;  // +0x0
    int i4;    // +0x4
    int i8;    // +0x8
    int iC;    // +0xC
    int i10;   // +0x10
    int i14;   // +0x14
} Entry;

typedef struct Table
{
    char pad[0x1C];
    Entry e[1]; // +0x1C
} Table;

extern const float lbl_8048E49C[]; // 0.0f
extern Table *lbl_8066C63C;
extern int lbl_8066C638;

int fn_80447A7C(register int index)
{
    return lbl_8066C63C != 0 ? lbl_8066C63C->e[index].iC == lbl_8066C638 : 0;
}

int fn_80447AD8(register int index, register int flag)
{
    if (flag)
    {
        return lbl_8066C63C != 0 ? lbl_8066C63C->e[index].i10 : 0;
    }
    else
    {
        return lbl_8066C63C != 0 ? lbl_8066C63C->e[index].i8 : 0;
    }
}

int fn_80447B60(register int index, register int flag)
{
    if (flag)
    {
        return lbl_8066C63C != 0 ? lbl_8066C63C->e[index].iC : 0;
    }
    else
    {
        return lbl_8066C63C != 0 ? lbl_8066C63C->e[index].i4 : 0;
    }
}

float fn_80447BE8(register int index)
{
    return lbl_8066C63C != 0 ? lbl_8066C63C->e[index].f0 : lbl_8048E49C[0];
}
