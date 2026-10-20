// A 0xC-byte key's value: the packed shorts at +0x4 unpacked into a Vector, returned by value. Class names are guesses.
class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(8)));

class Packed
{
public:
    short v[4];
    Vector unpack();
};

class Key
{
public:
    float time;
    Packed packed; // +0x4
    Vector value();
};

inline int sn_return_decl(int a) { return a; }

Vector Key::value()
{
    return packed.unpack();
}
