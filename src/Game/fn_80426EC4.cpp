// Color's constructor, alpha first (docs/core.md row 1).

class Color
{
public:
    unsigned char a;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    Color(unsigned char a, unsigned char r, unsigned char g, unsigned char b);
};

Color::Color(register unsigned char a, register unsigned char r, register unsigned char g, register unsigned char b)
{
    this->a = a;
    this->r = r;
    this->g = g;
    this->b = b;
}
