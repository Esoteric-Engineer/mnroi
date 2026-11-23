// A Vec2's float array (docs/core.md row 19).

inline int sn_return_decl(int a) { return a; }

struct Vec2
{
    float v[2];
};

extern "C" float *fn_8042E7E4(register Vec2 *self)
{
    return (float *)self;
}
