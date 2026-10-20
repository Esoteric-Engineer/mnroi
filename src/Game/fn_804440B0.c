// Virtual-call forwarders of the handle class (fn_80443E9C): vtable slot 2 and slot 2 of the other overload.
// Vtable entries are 8 bytes (delta, index, pfn); see docs/matching_notes.md. Names are guesses.

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

void fn_804440B0(register Handle *h, register int a, register int b, register int c)
{
    register VEntry *e;

    e = h->impl->vptr + 3;
    ((void (*)(void *, int, int, int))e->pfn)((char *)h->impl + e->delta, a, b, c);
}

void fn_8044412C(register Handle *h, register int a, register int b)
{
    register VEntry *e;

    e = h->impl->vptr + 3;
    ((void (*)(void *, int, int))e->pfn)((char *)h->impl + e->delta, a, b);
}
