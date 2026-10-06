// Constructors of the 0x50-byte element, its 64-element holder, the 0x40-byte Mat4 copy and the (1,0,0,0) Vec4 (docs/versus.md, row 8).

extern "C" void fn_8042D7B0(void *self);

class Element
{
public:
    char data[0x50];
    Element();
};

Element::Element()
{
    fn_8042D7B0(this);
}

class Root
{
public:
    char data[0xB0]; // +0x0, constructed by fn_8042D7B0
    Root() __asm__("fn_8042D7B0");
};

class ElementSet : public Root
{
public:
    Element elements[64]; // +0xB0
    ElementSet();
};

ElementSet::ElementSet()
{
}

extern "C" void *memcpy(void *dst, const void *src, unsigned int n);

class Mat4
{
public:
    float m[16];
    Mat4(const Mat4 &src);
};

Mat4::Mat4(register const Mat4 &src)
{
    memcpy(this, &src, 0x40);
}

class Vec4
{
public:
    float x; // +0x0
    float y; // +0x4
    float z; // +0x8
    float w; // +0xC
    Vec4();
};

Vec4::Vec4()
{
    x = 1.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
}

extern "C" void __6Vector(void *self);

class Marker
{
public:
    char pad0[0x40];
    int handle; // +0x40
    float delay; // +0x44
    char pad1[0x8];
    float scale; // +0x50
    Marker();
};

Marker::Marker()
{
    fn_8042D7B0(this);
    __6Vector((char *)this + 0x60);
    __6Vector((char *)this + 0x70);
    handle = 0;
    delay = 0.0f;
    scale = 30.0f;
}
