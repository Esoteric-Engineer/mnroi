// Vector built from four packed shorts (x, y, z over the unsigned w).
class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
    Vector(const short *packed);
} __attribute__((aligned(8)));

Vector::Vector(register const short *packed)
{
    Vector v;
    v.x = (float)packed[0] / (float)(unsigned short)packed[3];
    v.y = (float)packed[1] / (float)(unsigned short)packed[3];
    v.z = (float)packed[2] / (float)(unsigned short)packed[3];
    *this = v;
}
