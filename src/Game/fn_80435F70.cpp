// Constructors of a link to a bounds object and of a two-Vector segment; the class names are guesses (docs/versus.md, row 8).

extern "C" void __6Vector(void *self);
extern "C" void fn_80426A2C(void *self);

class BoundsLink
{
public:
    BoundsLink();
};

BoundsLink::BoundsLink()
{
    fn_80426A2C((char *)this + 0x10);
}

class Segment
{
public:
    Segment();
};

Segment::Segment()
{
    __6Vector(this);
    __6Vector((char *)this + 0x10);
}
