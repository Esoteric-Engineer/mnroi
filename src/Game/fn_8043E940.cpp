// Allocate for 0x25-aligned blocks through the heap object (docs/versus.md, row 8).

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
    virtual void *allocate(int size, int align); // vtable +0x28
};

extern "C" Heap *fn_802E29A8();

struct Block
{
    char pad[4];
    unsigned short size; // +0x4
};

extern "C" Block *fn_8043E940(register int size)
{
    Block *p = (Block *)fn_802E29A8()->allocate(size, 0x25);
    p->size = size;
    return p;
}
