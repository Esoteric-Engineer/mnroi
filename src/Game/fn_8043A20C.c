// Slot buffer allocate, free and read-start; docs/versus.md, row 8.
extern char lbl_80486C18[0x13];
extern int lbl_8066B7FC;
extern void *fn_801AC9EC(int size, char *file, int line, int a, int b, int c);
extern void fn_801ACC0C(void *p);
extern int fn_80243EC0(int a, int b, void *c, int d);

void fn_8043A20C(register char *self, register int size)
{
    *(void **)(self + 0x4) = fn_801AC9EC(size, lbl_80486C18, 0x69, 2, 0x40, 0);
    *(int *)(self + 0x8) = size;
    lbl_8066B7FC += size;
}

void fn_8043A278(register char *self)
{
    if (*(void **)(self + 0x4) != 0) {
        fn_801ACC0C(*(void **)(self + 0x4));
        *(void **)(self + 0x4) = 0;
        lbl_8066B7FC -= *(int *)(self + 0x8);
        *(int *)(self + 0x8) = 0;
    }
}

void fn_8043A2DC(register char *self, register int size)
{
    *(int *)(self + 0x0) = fn_80243EC0(**(int **)(self + 0xC), **(int **)(self + 0x10), *(void **)(self + 0x4), size);
    **(int **)(self + 0x10) = **(int **)(self + 0x10) + size;
}
