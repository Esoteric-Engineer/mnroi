// Constructor of an object with Vectors at +0x10 and +0x20 (class name guessed).

extern "C" void __6Vector(void *self);
extern "C" void fn_8043539C(void *self);

class Placement
{
public:
    Placement();
};

Placement::Placement()
{
    __6Vector((char *)this + 0x10);
    __6Vector((char *)this + 0x20);
    fn_8043539C(this);
}
