// Capacity getter, teardown of owned storage and the block free for the array family at 0x80440148
// (docs/versus.md, row 8).

struct Arr
{
    int data; // +0x0
    int n;    // +0x4
    int cap;  // +0x8
};

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
extern "C" void fn_804408F8(int data, int cap, int elemSize);

extern "C" {
int fn_80440148(register Arr *self)
{
    return self->cap & 0x3FFFFFFF;
}

void fn_80440180(register Arr *self)
{
    if ((self->cap & 0x80000000) == 0)
        fn_804408F8(self->data, fn_80440148(self), 0x14);
}

void fn_804401E4(register void *p)
{
    fn_802E29A8()->release(p, 0xC, 0x14);
}
}
