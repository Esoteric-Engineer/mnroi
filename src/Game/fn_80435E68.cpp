// Constructors of a Vector holder and of a shape over its base; the class names are guesses (docs/versus.md, row 8).

extern "C" void __6Vector(void *self);
extern "C" void fn_80434988(void *self);
extern "C" char lbl_804F3240[];

class VectorHolder
{
public:
    VectorHolder();
};

VectorHolder::VectorHolder()
{
    __6Vector((char *)this + 0x10);
}

class ShapeBase
{
public:
    int x; // +0x0, the vptr follows at +0x4
    ShapeBase();
};

class Shape : public ShapeBase
{
public:
    const void *vptr; // +0x4
    Shape();
};

Shape::Shape() : vptr(lbl_804F3240)
{
    fn_80434988((char *)this + 0x20);
    fn_80434988((char *)this + 0x30);
    fn_80434988((char *)this + 0x50);
}
