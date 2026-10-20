// Block frees through the heap object: 0xC-byte block and 4-byte element array (docs/versus.md, row 8).

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

extern "C" {
void fn_804419D8(register void *p)
{
    fn_802E29A8()->release(p, 0xC, 0x14);
}

void fn_80441A4C(register void *p, register int count, register int align)
{
    Heap &heap = *fn_802E29A8();

    heap.release(p, count * 4, align);
}
}
