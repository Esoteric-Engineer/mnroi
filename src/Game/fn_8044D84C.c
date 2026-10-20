// Registers a 0x10-byte listener (constructor fn_8044D934) on the object at +0x24; see docs/versus.md section 5, row 2.

extern void *fn_804336A8(void *obj);
extern void fn_80165118(void *obj);
extern void fn_80165138(void *obj);
extern void *fn_8043365C(int size, void *heap);
extern const void *fn_8044D934(void *self) __asm__("__8Listener");
extern void fn_80164544(void *obj, void *listener, void *owner, void *arg);

void fn_8044D84C(register char *self, register void *arg)
{
    void *listener;
    fn_80165118(fn_804336A8(*(void **)(self + 0x24)));
    listener = fn_8044D934(fn_8043365C(0x10, fn_804336A8(*(void **)(self + 0x24))));
    fn_80164544(*(void **)(self + 0x24), listener, self, arg);
    fn_80165138(fn_804336A8(*(void **)(self + 0x24)));
}

void fn_8044D8E4(register char *self, register int v)
{
    *(int *)(self + 0x100) = v;
}

void fn_8044D90C(register char *self, register int v)
{
    *(int *)(self + 0x80) = v;
}
