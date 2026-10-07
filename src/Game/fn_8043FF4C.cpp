// Frees of an 0xC-byte block (0x14-aligned) and of a sized block (0x24-aligned) through the heap object
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

struct Block
{
    char pad[4];
    unsigned short size; // +0x4
};

extern "C" {
void fn_8043FF4C(register void *p)
{
    fn_802E29A8()->release(p, 0xC, 0x14);
}

void fn_8043FFC0(register Block *p)
{
    Block *blk = p;
    fn_802E29A8()->release(p, blk->size, 0x24);
}
}
