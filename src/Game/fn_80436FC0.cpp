// Constructor of a second Vector holder; the class name is a guess (docs/versus.md, row 8).

extern "C" void __6Vector(void *self);

class VectorHolderB
{
public:
    VectorHolderB();
};

VectorHolderB::VectorHolderB()
{
    __6Vector((char *)this + 0x10);
}
