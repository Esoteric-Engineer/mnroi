// Streamer: start the load of a cutscene file; docs/versus.md, row 8.
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
