// Destructors, a forwarding method and a node factory of the polymorphic classes (docs/versus.md, row 8).
// Names are guesses.

extern char lbl_804F42D0[];
extern void __builtin_delete(void *p);
extern int fn_8031903C(int a);
extern void fn_80318FC4(int a, float v, void *p);
extern int fn_804405E0(void *list);
extern int *fn_8044060C(void *list, int i);
extern void *fn_8043DD6C(int size);
extern void *fn_8043E03C(void *p, int a, void *b);
extern void fn_80440648(void *p);
extern void fn_804406A4(void *p);
extern void fn_80440718(void *p);
extern void fn_80440774(void *p);

typedef struct Msg
{
    char pad[8];
    float value; // +0x8
} Msg;

typedef struct Owner
{
    char pad[0x18];
    int handle; // +0x18
} Owner;

void fn_8043FBDC(register int a, register int b)
{
}

void fn_8043FC00(register char **self, register int inChrg)
{
    *self = lbl_804F42D0;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

void fn_8043FC58(register Owner *self, register Msg *msg)
{
    if (fn_8031903C(self->handle) != 6)
        fn_80318FC4(self->handle, msg->value, (char *)self + 0x20);
}

void *fn_8043FCB4(register char *self, register void *list, register int unused)
{
    register int v;
    register void *p;

    if (fn_804405E0(list) > 0) {
        p = fn_8043DD6C(0x30);
        v = *fn_8044060C(list, 0);
        return fn_8043E03C(p, v, self + 0x20);
    } else {
        return 0;
    }
}

int fn_8043FD4C(register int *self)
{
    return self[2] & 0x3FFFFFFF;
}

void fn_8043FD7C(register void *self, register int inChrg)
{
    fn_80440648(self);
    if (inChrg & 1)
        fn_804406A4(self);
}

int fn_8043FDCC(register int *self)
{
    return self[2] & 0x3FFFFFFF;
}

void fn_8043FDFC(register void *self, register int inChrg)
{
    fn_80440718(self);
    if (inChrg & 1)
        fn_80440774(self);
}
