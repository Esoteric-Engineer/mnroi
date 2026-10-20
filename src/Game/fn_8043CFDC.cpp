// Byte1(char) constructor and the heap allocate/free pair for 0x12-aligned blocks (docs/versus.md, row 8).

class Byte1
{
public:
    char value;
    Byte1(register char v);
};

Byte1::Byte1(register char v)
{
    value = v;
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
    virtual void release(void *p, int size, int align); // vtable +0x30
};

extern "C" Heap *fn_802E29A8();

struct Block
{
    char pad[4];
    unsigned short size; // +0x4
};

extern "C" {
Block *fn_8043D010(register int size)
{
    Block *p = (Block *)fn_802E29A8()->allocate(size, 0x12);
    p->size = size;
    return p;
}

void fn_8043D09C(register Block *p)
{
    Block *blk = p;
    fn_802E29A8()->release(p, blk->size, 0x12);
}
}
