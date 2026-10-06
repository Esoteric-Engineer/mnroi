// Streamer buffer free; docs/versus.md, row 8.
extern int lbl_8066B7FC;
extern void fn_801ACC0C(void *p);

void fn_80439E3C(register char *self)
{
    if (*(void **)(self + 0x30) != 0) {
        fn_801ACC0C(*(void **)(self + 0x30));
        *(void **)(self + 0x30) = 0;
        lbl_8066B7FC -= 0x72A8;
    }
}
