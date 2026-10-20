// Free of an element array of 4-byte elements through the heap object (docs/versus.md, row 8).

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

extern "C" void fn_804408F8(register void *p, register int count, register int align)
{
    Heap &heap = *fn_802E29A8();

    heap.release(p, count * 4, align);
}
