// Block frees through the heap object: 0xC-byte block, 2-, 4- and 12-byte element arrays, and the raw free
// (docs/versus.md, row 8).

inline int sn_return_decl(int a)
{
    return a;
}

class Heap
{
public:
    char data[0x3C]; // the vptr follows at +0x3C
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void release(void *p, int size, int align); // vtable +0x30
};

extern "C" Heap *fn_802E29A8();

struct Arr
{
    int data; // +0x0
    int n;    // +0x4
    int cap;  // +0x8
};

extern "C" {
void fn_80440BD4(register void *p)
{
    fn_802E29A8()->release(p, 0xC, 0x14);
}

void fn_80440C48(register void *p, register int count, register int align)
{
    Heap &heap = *fn_802E29A8();

    heap.release(p, count * 2, align);
}

void fn_80440CD4(register void *p, register int count, register int align)
{
    Heap &heap = *fn_802E29A8();

    heap.release(p, count * 4, align);
}

int fn_80440D60(register Arr *self)
{
    return self->cap & 0x3FFFFFFF;
}

void fn_80440D90(register void *p, register int count, register int align)
{
    Heap &heap = *fn_802E29A8();

    heap.release(p, count * 12, align);
}

void fn_80440E18(register void *p, register int size, register int align)
{
    Heap &heap = *fn_802E29A8();

    heap.release(p, size, align);
}
}
