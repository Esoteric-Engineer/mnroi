// Allocate for 0x26-aligned blocks, a word getter and a vptr constructor (docs/versus.md, row 8).

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
extern "C" char lbl_804F42F8[];

struct Block
{
    char pad[4];
    unsigned short size; // +0x4
};

struct Holder
{
    const void *vptr; // +0x0
    int unk4;         // +0x4
    int word;         // +0x8
};

extern "C" {
Block *fn_8043DD6C(register int size)
{
    Block *p = (Block *)fn_802E29A8()->allocate(size, 0x26);
    p->size = size;
    return p;
}

int fn_8043DDF8(register Holder *self)
{
    return self->word;
}

Holder *fn_8043DE24(register Holder *self)
{
    self->vptr = lbl_804F42F8;
    return self;
}
}
