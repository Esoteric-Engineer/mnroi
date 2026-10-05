// Whether an entry of the table at lbl_8066C63C has a positive value (fn_80447A7C.c has the layout).
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

extern Table *lbl_8066C63C;

int fn_80445F70(register int index)
{
    if (lbl_8066C63C != 0 && lbl_8066C63C->e[index].f0 > 0.0f)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
