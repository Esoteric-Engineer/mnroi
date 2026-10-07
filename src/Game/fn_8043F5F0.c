// Destructors and constructors of the polymorphic classes around fn_8043F908 (docs/versus.md, row 8).
// Names are guesses.

extern char lbl_804F4510[], lbl_804F44F0[], lbl_804F44D0[], lbl_804F4400[], lbl_804F43E0[], lbl_804F43C0[];
extern char lbl_804F43A8[], lbl_804F4388[], lbl_804F4318[], lbl_8050A5B8[], lbl_804F4640[], lbl_804F4620[];
extern char lbl_8050A5A0[], lbl_804F4688[], lbl_804F4660[], lbl_804F4758[], lbl_804F47C8[], lbl_804F47A8[];
extern char lbl_804F4740[], lbl_804F4770[], lbl_804F47E8[];
extern void __builtin_delete(void *p);
extern void __6Holder(void *p);
extern void fn_80310490(void *p, int a);
extern void fn_8043FB58(void *p);
extern void fn_80440420(void *p, int a);
extern void fn_8043BB40(void *p, int a);
extern void fn_80440510(void *p);
extern void fn_80440578(void *p);
extern void fn_804405AC(void *p);
extern void fn_80440544(void *p);
extern void fn_803807D0(void *p);
char *fn_8043F908(register char *self);
extern void fn_8043DC48(void *p);
extern void fn_80440B38(void *p);

void fn_8043F5F0(register void *self, register int inChrg)
{
    fn_80310490(self, 0);
    if (inChrg & 1)
        fn_8043FB58(self);
}

void fn_8043F644(register char **self, register int inChrg)
{
    *self = lbl_804F4510;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

char **fn_8043F69C(register char **self)
{
    *self = lbl_804F4510;
    return self;
}

void *fn_8043F6D0(register void *self, register int a)
{
    fn_80440420(self, a);
    return self;
}

void *fn_8043F718(register void *self, register int a)
{
    fn_8043BB40(self, a);
    return self;
}

int fn_8043F760(register int *self)
{
    return self[0];
}

int fn_8043F78C(register int *self)
{
    return self[2];
}

void fn_8043F7B8(register long long *self, register int v)
{
    *self = v;
}

void fn_8043F7E8(register unsigned long long *self, register unsigned int v)
{
    *self = v;
}

int *fn_8043F818(register int *self)
{
    self[0] = 0;
    self[1] = 0;
    self[2] = 0x80000000;
    return self;
}

void fn_8043F858(register char **self, register int inChrg)
{
    *self = lbl_804F44F0;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

void fn_8043F8B0(register char **self, register int inChrg)
{
    *self = lbl_804F44D0;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

char *fn_8043F908(register char *self)
{
    __6Holder(self);
    fn_80440510(self + 0x8);
    fn_80440578(self + 0xC);
    fn_804405AC(self + 0x10);
    fn_80440544(self + 0x14);
    *(char **)(self + 0x8) = lbl_804F4400;
    *(char **)(self + 0xC) = lbl_804F43E0;
    *(char **)(self + 0x10) = lbl_804F43C0;
    *(char **)(self + 0x14) = lbl_804F43A8;
    *(char **)self = lbl_804F4388;
    return self;
}

void fn_8043F9B4(register char **self, register int inChrg)
{
    *self = lbl_804F4318;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

void fn_8043FA0C(register int a, register int b)
{
}

char *fn_8043FA30(register char *self)
{
    fn_803807D0(self);
    *(char **)(self + 0x8) = lbl_8050A5B8;
    *(char **)(self + 0xC) = lbl_804F4640;
    *(char **)(self + 0x10) = lbl_804F4620;
    *(char **)(self + 0x14) = lbl_8050A5A0;
    *(char **)(self + 0x18) = lbl_804F4688;
    *(char **)self = lbl_804F4660;
    return self;
}

char *fn_8043FAB8(register char *self)
{
    fn_8043F908(self);
    fn_8043DC48(self + 0x18);
    *(char **)(self + 0x8) = lbl_804F4758;
    *(char **)(self + 0xC) = lbl_804F47C8;
    *(char **)(self + 0x10) = lbl_804F47A8;
    *(char **)(self + 0x14) = lbl_804F4740;
    *(char **)(self + 0x18) = lbl_804F4770;
    *(char **)self = lbl_804F47E8;
    fn_80440B38(self + 0x1C);
    return self;
}
