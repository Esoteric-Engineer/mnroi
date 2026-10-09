// Menu-object accessors and roster-table lookups; see docs/versus.md section 5, row 2.

typedef struct Rec
{
    char unk0[0x40];
    int val; // +0x40
} Rec;

typedef struct Menu
{
    char unk0[0xC];
    void *names; // +0xC
} Menu;

extern Rec lbl_804CB14C[];
extern Rec lbl_804CB328[];
extern Rec lbl_804CBEB8[];
extern int lbl_804CB0FC[];

extern int fn_804432D8(void *names);
extern char *strstr(const char *haystack, const char *needle);

char *fn_8044EEF4(register char *self)
{
    return self + 0x2E0;
}

int fn_8044EF20(register Menu *self)
{
    return fn_804432D8(self->names) == 0;
}

int fn_8044EF70(register char *self)
{
    return *(unsigned int *)(self + 0x1AC) & 0x4;
}

int fn_8044EFA0(register char *self)
{
    return *(unsigned int *)(self + 0x1AC) & 0x8;
}

int fn_8044EFD0(register char *self)
{
    return *(unsigned int *)(self + 0x1AC) & 0x200;
}

Rec *fn_8044F000(register int i)
{
    return &lbl_804CB328[i];
}

Rec *fn_8044F038(register int i)
{
    return &lbl_804CBEB8[i];
}

int fn_8044F070(register int value, register int search, register int unused)
{
    int i;
    if (search) {
        i = 0;
        while (i <= 0x13) {
            if (lbl_804CB0FC[i] == value) {
                return i;
            }
            i++;
        }
        return 0;
    }
    return value;
}

int fn_8044F104(register char *text)
{
    int i;
    i = 0;
    while (i <= 6) {
        if (strstr(text, (char *)&lbl_804CB14C[i])) {
            return i;
        }
        i++;
    }
    return -1;
}

Rec *fn_8044F19C(register int i)
{
    return &((Rec *)((char *)lbl_804CB14C + 0x20))[i];
}
