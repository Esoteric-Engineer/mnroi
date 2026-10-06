// Streamer destructor, teardown, update method and cutscene-load helpers (hand-written C: the flag stays in a register); docs/versus.md, row 8.
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

extern char lbl_80543208[], lbl_80543224[], lbl_80543240[];
extern void fn_80439390(char *self);
extern void fn_80439464(char *self);
extern void fn_80439778(void *self, int flag);
extern void fn_804394C0(char *self);
extern void fn_8023E98C(void);
extern int fn_8023E5E4(void *queue, void *self);

void fn_804392C0(register char *self)
{
    if (*(int *)(self + 0x6C) != 0)
        fn_80439390(self);
    while (*(int *)(self + 0x70) == 0)
        fn_8023E98C();
    if (fn_8023E5E4(lbl_80543208, self) != 0)
        fn_80439464(self);
    if (fn_8023E5E4(lbl_80543224, self) != 0)
        fn_80439778(self, 1);
    if (fn_8023E5E4(lbl_80543240, self) != 0)
        fn_804394C0(self);
}

extern int sprintf(char *s, const char *format, ...);
extern char lbl_80486C94[0xD], lbl_80486CA4[], lbl_80486CA8[];
extern char lbl_805431EC[];
extern void fn_801B4094(char *s, const char *ext);
extern unsigned fn_8023FD34(int arg);
extern char *fn_801A7C30(void);
extern void fn_8023E3D4(void *queue, void *self);
extern void fn_80439E94(void *self, char *path);

void fn_80439390(register char *self)
{
    char name[0x80];
    unsigned size;
    char path[0x80];

    sprintf(name, lbl_80486C94, self + 0xC);
    fn_801B4094(name, lbl_80486CA4);
    size = fn_8023FD34(0);
    if (size <= 0x72A7)
        return;
    sprintf(path, lbl_80486CA8, fn_801A7C30(), name);
    if (*(int *)(self + 0x28) != 0)
        return;
    fn_8023E3D4(lbl_805431EC, self);
    fn_80439E94(self, path);
}

struct StreamBuf {
    char pad0[8];
    unsigned a; // +0x8
    unsigned b; // +0xC
    char pad1[0x18C - 0x10];
    int *tbl; // +0x18C
};
extern int fn_80243EC0(int a, int b, void *c, int d);
extern void fn_80439D2C(void *slot, int v);

void fn_80439464(register char *self)
{
    *(int *)(self + 0x8) = fn_80243EC0(*(int *)(self + 0x28), 0, *(void **)(self + 0x30), 0x72A8);
    fn_8023E3D4(lbl_80543224, self);
}

#define STREAM_BUF (*(struct StreamBuf **)(self + 0x30))

void fn_804394C0(register char *self)
{
    *(int *)(self + 0x2C) = (int)((int *)((char *)&((int *)0)[STREAM_BUF->a] + (STREAM_BUF->b * 0x90 + 0x198)) + STREAM_BUF->a);
    fn_80439D2C(self + 0x34, STREAM_BUF->tbl[0]);
}

int fn_80439544(register char *self)
{
    unsigned i;
    int v;
    if (*(int *)(self + 0x74) == 0)
        return 0;
    *(int *)(self + 0x5C) = 0;
    *(int *)(self + 0x60) = 1;
    for (i = 1; i <= 1; i++) {
        if (*(unsigned *)(self + 0x60) >= STREAM_BUF->a)
            break;
        v = STREAM_BUF->tbl[*(unsigned *)(self + 0x60)];
        fn_80439D2C(self + (i * 0x14 + 0x34), v);
        (*(unsigned *)(self + 0x60))++;
    }
    return 1;
}

extern void fn_804396F8(char *self);

void fn_80439628(register char *self)
{
    register unsigned *tmp = &STREAM_BUF->a;
    unsigned *count = tmp;
    unsigned slot;
    int v;
    if (*(unsigned *)(self + 0x60) < *count) {
        slot = *(unsigned *)(self + 0x5C) & 1;
        v = STREAM_BUF->tbl[(*(unsigned *)(self + 0x60))++];
        fn_80439D2C(self + (slot * 0x14 + 0x34), v);
    }
    (*(unsigned *)(self + 0x5C))++;
    if (*(unsigned *)(self + 0x5C) < *count)
        fn_804396F8(self);
}
