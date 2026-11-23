// The constructors of a two-Vec2 class and of an 8-point, 6-plane class (docs/core.md row 19). Class names are placeholders.

inline int sn_return_decl(int a) { return a; }

class Vec2
{
public:
    float x;
    float y;
    Vec2() __asm__("fn_80426A2C");
};

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

class CornerPlane
{
public:
    float v[4];
    CornerPlane() __asm__("fn_8042F72C");
};

class Rect2
{
public:
    Vec2 a;
    Vec2 b;
    Rect2();
};

class Corners
{
public:
    Vector points[8];
    CornerPlane planes[6]; // +0x80
    Corners();
};

__asm__(".text\n\t.globl fn_8042EA08\n\t.type fn_8042EA08,@function\nfn_8042EA08:");
Rect2::Rect2()
{
}
__asm__(".size fn_8042EA08, 0x4C");

__asm__(".text\n\t.globl fn_8042EA54\n\t.type fn_8042EA54,@function\nfn_8042EA54:");
Corners::Corners()
{
}
__asm__(".size fn_8042EA54, 0xB8");
