// Block free and empty stubs of the array family (docs/versus.md, row 8).

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
void fn_804409E8(register void *p)
{
    fn_802E29A8()->release(p, 0xC, 0x14);
}

void fn_80440A5C(register int a, register int b, register int c, register int d, register int e)
{
}

void fn_80440A8C(register int a, register int b, register int c, register int d, register int e)
{
}

void fn_80440ABC(register int a, register int b, register int c, register int d)
{
}

void fn_80440AE8(register int a)
{
}

void fn_80440B08(register int a, register int b, register int c, register int d, register int e)
{
}
}
