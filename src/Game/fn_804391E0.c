// Streamer's destructor (hand-written C: the flag stays in a register) and a teardown that releases its buffers; docs/versus.md, row 8.
extern void fn_80439E3C(void *self);
extern void fn_80439D88(void *self);
extern void fn_80439C24(void *slot);
extern void fn_80439F7C(void *self);
extern void fn_80439F10(void *self);

void fn_804391E0(register void *self, register int inChrg)
{
    fn_80439E3C(self);
    if (inChrg & 1)
        fn_80439D88(self);
}

void fn_80439230(register char *self)
{
    unsigned i;
    for (i = 0; i <= 1; i++)
        fn_80439C24(self + (i * 0x14 + 0x34));
    fn_80439F7C(self);
    fn_80439F10(self);
    *(int *)(self + 0x6C) = 1;
    *(int *)(self + 0x74) = 0;
}
