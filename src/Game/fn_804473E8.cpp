// Vector subclass built from the packed shorts at +0x4 of a record (the base is fn_80447830). Class names are guesses.
class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector(const short *packed);
} __attribute__((aligned(8)));

class Dir : public Vector
{
public:
    Dir(const void *record);
};

Dir::Dir(register const void *record) : Vector((const short *)((const char *)record + 4))
{
}
