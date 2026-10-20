// Constructors of three objects that hold Vectors; the class names are guesses (docs/versus.md, row 8).

extern "C" void __6Vector(void *self);
extern "C" void fn_8042D7B0(void *self);

class Locator
{
public:
    Locator();
};

Locator::Locator()
{
    __6Vector((char *)this + 0x20);
}

class Pose
{
public:
    Pose();
};

Pose::Pose()
{
    fn_8042D7B0((char *)this + 0x10);
    __6Vector((char *)this + 0x50);
    __6Vector((char *)this + 0x60);
}

class VectorPair
{
public:
    VectorPair();
};

VectorPair::VectorPair()
{
    __6Vector(this);
    __6Vector((char *)this + 0x10);
}
