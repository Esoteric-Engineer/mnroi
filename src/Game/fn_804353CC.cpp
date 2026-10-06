// Constructor of an object with a Vector at +0x20 (class name guessed).

extern "C" void __6Vector(void *self);

class Locator
{
public:
    Locator();
};

Locator::Locator()
{
    __6Vector((char *)this + 0x20);
}
