// Streamer's slot refill step; docs/versus.md, row 8.
extern int fn_80439C64(void *slot, void *arg);
extern char *fn_80058284(void *a, int b, int c);

void fn_804396F8(register char *self)
{
    int r;
    void *v;
    r = fn_80439C64(self + ((*(unsigned *)(self + 0x5C) & 1) * 0x14 + 0x34), self + 0x5C);
    v = fn_80058284(*(void **)(self + 0x30), *(int *)((char *)(self + 0x38) + (*(unsigned *)(self + 0x5C) & 1) * 0x14), *(int *)(self + 0x5C));
}
