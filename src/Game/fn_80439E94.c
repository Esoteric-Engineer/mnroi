// Streamer: start (fn_80439E94), close (fn_80439F10) and teardown wait (fn_80439F7C); docs/versus.md, row 8.
extern void *fn_80241DD0(register char *path, int a, int b, void *arg);
extern void fn_80241C58(void *h, void *cb);
extern void fn_80051F04(void);

void fn_80439E94(register char *self, register char *path)
{
    if (*(int *)(self + 0x6C) != 0) {
        *(int *)(self + 0x6C) = 0;
        *(int *)(self + 0x70) = 0;
        *(void **)(self + 0x4) = fn_80241DD0(path, 1, 0x64, self);
        fn_80241C58(*(void **)(self + 0x4), fn_80051F04);
    }
}

extern void *fn_80241E60(void *h, int a, int b);
extern void fn_80051FC4(void);

void fn_80439F10(register char *self)
{
    void *h;
    if (*(void **)(self + 0x28) != 0) {
        h = fn_80241E60(*(void **)(self + 0x28), 0x64, 0);
        fn_80241C58(h, fn_80051FC4);
        *(void **)(self + 0x28) = 0;
    }
}

extern void fn_80241A2C(void *h);
extern int fn_80244120(void *h);
extern int fn_80243F94(void *h);
extern void fn_8023E98C(void);
extern int fn_8023E5E4(void *queue, void *self);
extern char lbl_805431EC[], lbl_80543208[], lbl_80543224[], lbl_80543240[];

void fn_80439F7C(register char *self)
{
    int r;
    if (*(void **)(self + 0x4) != 0) {
        fn_80241A2C(*(void **)(self + 0x4));
        *(void **)(self + 0x4) = 0;
    }
    if (*(void **)(self + 0x8) != 0) {
        r = fn_80244120(*(void **)(self + 0x8));
        while (fn_80243F94(*(void **)(self + 0x8)) == 0)
            fn_8023E98C();
        *(void **)(self + 0x8) = 0;
    }
    if (*(int *)(self + 0x6C) == 0) {
        while (*(int *)(self + 0x70) == 0)
            fn_8023E98C();
    }
    if (fn_8023E5E4(lbl_805431EC, self) || fn_8023E5E4(lbl_80543208, self) ||
        fn_8023E5E4(lbl_80543224, self) || fn_8023E5E4(lbl_80543240, self))
        ;
}
