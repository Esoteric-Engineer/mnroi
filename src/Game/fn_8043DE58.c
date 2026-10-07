// Constructors, a destructor and small accessors of the classes around fn_8043DB70 (docs/versus.md, row 8).
// Names are guesses.

typedef struct Entry
{
    char pad[4];
    int word; // +0x4
    char tail[0x28];
} __attribute__((aligned(8))) Entry;

extern char lbl_804F42F8[], lbl_804F42D0[], lbl_804F4230[], lbl_804F4218[], lbl_804F41F8[];
extern char lbl_804F41D8[], lbl_804F41C0[], lbl_804F41A0[], lbl_804F4288[];
extern void __builtin_delete(void *p);
extern void __6Vector(void *p);
extern char **fn_8043DB70(char **p);
extern void fn_8043F908(void *p);
extern void fn_8043FAB8(void *p);
extern void fn_803800C4(void *p);
extern void fn_8043FA30(void *p);
extern void fn_80310558(void *p, int a, int b);
extern void fn_80434988(void *p);
extern void fn_8043632C(void *p, int src);

void fn_8043DE58(register char **self, register int inChrg)
{
    *self = lbl_804F42F8;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

char **fn_8043DEB0(register char **self)
{
    *self = lbl_804F42D0;
    return self;
}

char **fn_8043DEE4(register char **self)
{
    fn_8043DB70(self);
    *self = lbl_804F4230;
    return self;
}

char *fn_8043DF30(register char *self)
{
    fn_8043F908(self);
    *(char **)(self + 0x8) = lbl_804F4218;
    *(char **)(self + 0xC) = lbl_804F41F8;
    *(char **)(self + 0x10) = lbl_804F41D8;
    *(char **)(self + 0x14) = lbl_804F41C0;
    *(char **)self = lbl_804F41A0;
    fn_8043FAB8(self + 0x18);
    fn_803800C4(self + 0x40);
    fn_8043FA30(self + 0xDC);
    fn_8043FA30(self + 0x104);
    return self;
}

void fn_8043DFDC(register int *self, register char *owner)
{
    *self = (int)owner;
    self[1] = *(int *)(owner + 0x158);
    *(int **)(owner + 0x158) = self;
}

int fn_8043E010(register int *self)
{
    return self[3];
}

char *fn_8043E03C(register char *self, register int a, register int b)
{
    fn_80310558(self, a, 0);
    *(char **)self = lbl_804F4288;
    fn_80434988(self + 0x20);
    fn_8043632C(self + 0x20, b);
    return self;
}

void fn_8043E0B4(register int *self)
{
    self[1] = 0;
}

void fn_8043E0DC(register int *self)
{
    self[1] = 0;
}

char *fn_8043E104(register char *self)
{
    __6Vector(self + 0x10);
    return self;
}
