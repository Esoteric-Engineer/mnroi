// Two constructors of Vector[4] + two Vectors; the second adds a member built by fn_8042EA08. Class names are guesses.

extern "C" void *fn_8042EA08(void *self);

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

class Xform
{
public:
    Vector m[4]; // +0x0
    Vector a;    // +0x40
    Vector b;    // +0x50
    Xform();
};

class XformEx
{
public:
    Vector m[4]; // +0x0
    Vector a;    // +0x40
    Vector b;    // +0x50
    char c[0x10]; // +0x60, unknown
    char d[0x10]; // +0x70, built by fn_8042EA08
    XformEx();
};

Xform::Xform() {}

XformEx::XformEx()
{
    fn_8042EA08((char *)this + 0x70);
}
