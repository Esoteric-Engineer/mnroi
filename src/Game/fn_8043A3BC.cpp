// Element/ElementSet/Mat4/Vec4/Marker constructors and the small methods after them (docs/versus.md, row 8).
// Class names are guesses; the methods carry GCC 2.95 mangled symbol names. 0x8043A71C starts the next file.

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

class Handle
{
public:
    int target; // +0x0
    int isSet();
};

int Handle::isSet()
{
    register int r = 1;
    if (target == 0)
        r = 0;
    return r;
}

class Actor60
{
public:
    char pad[0x60];
    float x; // +0x60
    void clearX();
};

void Actor60::clearX()
{
    x = 0.0f;
}

class Actor1F0
{
public:
    char pad[0x1F0];
    char a[0x10]; // +0x1F0
    char b[0x10]; // +0x200
    void clear();
};

extern "C" void *memset(void *dst, int c, unsigned int n);

void Actor1F0::clear()
{
    memset(a, 0, 0x10);
    memset(b, 0, 0x10);
}

class Actor10
{
public:
    char pad[0x10];
    int value; // +0x10
    void setValue(register int v);
};

void Actor10::setValue(register int v)
{
    value = v;
}

class Matrix
{
public:
    char data[0x40];
    void assign(register const Matrix &src);
};

void Matrix::assign(register const Matrix &src)
{
    memcpy(this, &src, 0x40);
}

class Scratch
{
public:
    char data[0x40];
    Scratch() __asm__("fn_8042D7B0");
};

extern "C" void fn_8042DD30(Scratch *self, const void *src);
extern "C" void fn_8043AC1C(void *self, Scratch *s);

class Actor
{
public:
    void apply(register const void *src);
};

void Actor::apply(register const void *src)
{
    Scratch s;
    fn_8042DD30(&s, src);
    fn_8043AC1C(this, &s);
}
