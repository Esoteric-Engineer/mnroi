// Four packed shorts (x, y, z over the unsigned w) unpacked into a Vector, returned by value. Class names are guesses.
class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

class Packed
{
public:
    short v[4];
    Vector unpack();
};

inline int sn_return_decl(int a) { return a; }

Vector Packed::unpack()
{
    Vector r;
    r.x = (float)v[0] / (float)(unsigned short)v[3];
    r.y = (float)v[1] / (float)(unsigned short)v[3];
    r.z = (float)v[2] / (float)(unsigned short)v[3];
    return r;
}
