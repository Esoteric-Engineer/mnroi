// Virtual-call forwarder of the handle class (vtable slot 2, one argument); see docs/versus.md section 5. Names are guesses.

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
