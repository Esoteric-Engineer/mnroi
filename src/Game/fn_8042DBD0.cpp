// The constructor of a class with a Vec2 member (docs/core.md row 19). Class name is a placeholder.

inline int sn_return_decl(int a) { return a; }

class Vec2
{
public:
    float x;
    float y;
    Vec2() __asm__("fn_80426A2C");
};

class Vec2Owner
{
public:
    char pad[0x14];
    Vec2 v;
    Vec2Owner();
};

__asm__(".text\n\t.globl fn_8042DBD0\n\t.type fn_8042DBD0,@function\nfn_8042DBD0:");
Vec2Owner::Vec2Owner()
{
}
__asm__(".size fn_8042DBD0, 0x44");
