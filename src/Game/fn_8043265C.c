// Leaf accessors on small engine objects (docs/versus.md section 4.1).
// Built at -O0, pair-less.

extern int fn_80431DB0(char *self);
extern int fn_804332C4(char *self, int v);

char *fn_8043265C(register char *self)
{
    return self + 0x280;
}

char *fn_80432688(register char *self)
{
    return self + 0x260;
}

int fn_804326B4(register char *self)
{
    return fn_804332C4(self, fn_80431DB0(self));
}

typedef struct Entry
{
    int value; // +0x0
    char unk4[0x14];
} Entry;

typedef struct EntryTable
{
    char unk0[0x20];
    Entry entries[1]; // +0x20
} EntryTable;

extern EntryTable *lbl_8066C63C;
extern int lbl_8066C638;

int fn_80432708(register int index)
{
    return lbl_8066C63C != 0 ? lbl_8066C63C->entries[index].value == lbl_8066C638 : 0;
}

typedef struct Obj
{
    char unk0[0x20];
    Entry entries[15]; // +0x20
    char unk188[0x14];
} Obj;

extern Obj lbl_805932A0[];
extern int fn_80433314(Obj *obj);

int fn_80432764(register int index, register unsigned short *out)
{
    unsigned short i = 0;
    while (i <= 3)
    {
        if (fn_80433314(&lbl_805932A0[i]) != 0)
        {
            if (lbl_805932A0[i].entries[index].value == lbl_8066C638)
            {
                if (out != 0)
                    *out = i;
                return 1;
            }
        }
        i = i + 1;
    }
    return 0;
}

int fn_80432844(register char *g)
{
    return *(int *)(g + 0x770);
}

int fn_80432870(register char *g)
{
    return *(int *)(g + 0x774);
}

extern int fn_80433340(char *self);
extern int fn_80433394(char *self);
extern int fn_804333CC(char *self);

int fn_8043289C(register char *self)
{
    return fn_80433340(self);
}

int fn_804328E0(register char *self)
{
    return fn_80433394(self);
}

int fn_80432924(register char *self)
{
    return fn_804333CC(self);
}

int fn_80432968(register unsigned int *self)
{
    return *self & 0x80;
}

void fn_80432998(register char *self)
{
}

void fn_804329B8(register int *self, register int v)
{
    *self = v;
}

int fn_804329E0(register char *self)
{
    return *(int *)(self + 0x8);
}

int fn_80432A0C(register char *self)
{
    return *(int *)(self + 0x68);
}

void fn_80432A38(register char *self, register int v)
{
    *(int *)(self + 0x10) = v;
}

int fn_80432A60(register char *self)
{
    return *(int *)(self + 0x64);
}

int fn_80432A8C(register char *self)
{
    register int result = 0;
    if (fn_80432A60(self) == 3 || fn_80432A60(self) == 4)
        result = 1;
    return result;
}

void fn_80432AF8(register char *self)
{
    *(int *)(self + 0x5C) = 7;
}

int fn_80432B20(register char *self)
{
    return *(int *)(self + 0x0);
}
