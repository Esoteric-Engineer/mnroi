// Constructor of a shape's data holder; the class name is a guess (docs/versus.md, row 8).

extern "C" void fn_80434988(void *self);
extern "C" void fn_804384D8(void *self);

class ShapeData
{
public:
    ShapeData();
};

ShapeData::ShapeData()
{
    fn_80434988(this);
    fn_804384D8(this);
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

extern "C" void fn_80436DD0(register void *p)
{
    fn_802E29A8()->release(p, 8, 0x1C);
}

class ShapeBase
{
public:
    float x;           // +0x0
    const void *vptr;  // +0x4
    ShapeBase();
};

extern "C" char lbl_804F3318[];

extern "C" void fn_80436E44(register ShapeBase *self)
{
    self->x = 3.4028235e38f; // FLT_MAX
}

ShapeBase::ShapeBase() : vptr(lbl_804F3318)
{
    fn_80436E44(this);
}
