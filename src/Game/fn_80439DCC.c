// cCutPlayer buffer allocate; docs/versus.md, row 8.
extern char lbl_80486C78[0x19];
extern int lbl_8066B7FC;
extern void *fn_801AC9EC(int size, char *file, int line, int a, int b, int c);

void fn_80439DCC(register char *self)
{
    if (*(void **)(self + 0x30) == 0) {
        *(void **)(self + 0x30) = fn_801AC9EC(0x72A8, lbl_80486C78, 0x127, 2, 0x40, 0);
        lbl_8066B7FC += 0x72A8;
    }
}
