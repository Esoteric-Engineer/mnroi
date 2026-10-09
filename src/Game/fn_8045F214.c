// Virtual-call forwarder of the handle class (vtable slot 2, one argument), its list loop fn_8045F280 and wrapper; see docs/versus.md section 5.
// Names are guesses.

typedef struct VEntry
{
    short delta;
    short index;
    void *pfn;
} VEntry;

typedef struct Impl
{
    int x;
    VEntry *vptr; // +0x4
} Impl;

typedef struct Handle
{
    Impl *impl; // +0x0
} Handle;

void fn_8045F214(register Handle *h, register int a)
{
    register VEntry *e;

    e = h->impl->vptr + 3;
    ((void (*)(void *, int))e->pfn)((char *)h->impl + e->delta, a);
}

extern int fn_801B6A44(void *list);
extern void *fn_801B5D3C(void *list, int index);

void fn_8045F280(register void *list, register int a)
{
    Handle **e;
    int i = 0;
    while (i < fn_801B6A44(list)) {
        e = (Handle **)fn_801B5D3C(list, i);
        fn_8045F214(*e, a);
        i++;
    }
}

typedef struct Owner
{
    void *list; // +0x0
    int pad[3];
    int a; // +0x10
} Owner;

void fn_8045F308(register Owner *self)
{
    fn_8045F280(self->list, self->a);
}
