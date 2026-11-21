// Two-float vector: the empty constructor and a setter (docs/core.md row 1).

class Vec2
{
public:
    float x; // +0x0
    float y; // +0x4
    Vec2();
};

__asm__(".text\n\t.globl fn_80426A2C\n\t.type fn_80426A2C,@function\nfn_80426A2C:");
Vec2::Vec2()
{
}
__asm__(".size fn_80426A2C, 0x28");

extern "C" void fn_80426A54(register Vec2 *v, register float x, register float y)
{
    v->x = x;
    v->y = y;
}
