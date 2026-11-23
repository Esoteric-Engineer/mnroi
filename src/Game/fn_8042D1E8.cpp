// The two-argument callback handles' for-each and invoke (docs/core.md row 19, section 4.4).

extern "C" void *fn_801B5D3C(void *list, int index);
extern "C" int fn_801B6A44(void *list);

class ImplVT
{
public:
    int unk0;
    virtual void v0();
    virtual int get();
    virtual void invoke(int a, int b); // +0x18
};

struct Handle
{
    ImplVT *impl;
    const void *vptr;
};

struct Entry
{
    Handle *link;
    int value;
};

extern "C" void fn_8042D280(Handle *self, int a, int b);

extern "C" void fn_8042D1E8(register void *list, register int a, register int b)
{
    Entry *e;
    int i = 0;
    while (i < fn_801B6A44(list)) {
        e = (Entry *)fn_801B5D3C(list, i);
        fn_8042D280(e->link, a, b);
        i++;
    }
}

extern "C" void fn_8042D280(register Handle *self, register int a, register int b)
{
    self->impl->invoke(a, b);
}
