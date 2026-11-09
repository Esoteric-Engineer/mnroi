// A rotation key's value: its packed shorts as a quaternion.

class Vec4
{
public:
    float x, y, z, w;
};

struct Packed {
    short v[4];
};

struct Key {
    float frame;
    Packed packed; // +0x4
};

inline int sn_return_decl(int a) { return a; }

extern "C" {
Vec4 fn_80465C9C(Packed *self);

Vec4 fn_80465960(register Key *self)
{
    return fn_80465C9C(&self->packed);
}
}
