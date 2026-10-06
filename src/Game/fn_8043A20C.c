// Slot buffer allocate (size argument); docs/versus.md, row 8.
extern char lbl_80486C18[0x13];
extern int lbl_8066B7FC;
extern void *fn_801AC9EC(int size, char *file, int line, int a, int b, int c);

void fn_8043A20C(register char *self, register int size)
{
    *(void **)(self + 0x4) = fn_801AC9EC(size, lbl_80486C18, 0x69, 2, 0x40, 0);
    *(int *)(self + 0x8) = size;
    lbl_8066B7FC += size;
}
