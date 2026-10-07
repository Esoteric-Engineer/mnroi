// Forwarder through the actor's sub-object handle, then two constructors (docs/versus.md, row 8).
// Class names are guesses. The pool 0x804873B4 is read through extern_pool.

extern "C" {
void *fn_8032A228(void *self);
void *fn_80435340(void *self);
int fn_8043CA98(void *self);

int fn_8043C1EC(register void *self)
{
    return fn_8043CA98(fn_80435340(fn_8032A228(self)));
}
}

extern "C" void fn_80434988(void *self);
extern "C" void fn_8043B954(void *self);
extern "C" void fn_804363B8(void *self);
extern "C" void fn_8043C84C(void *self);

class Extent
{
public:
    float lo; // +0x0
    float hi; // +0x4
    Extent();
};

Extent::Extent()
{
    lo = 0.0f;
    hi = 0.0f;
    fn_80434988((char *)this + 0x10);
    fn_8043B954((char *)this + 0x20);
    fn_804363B8((char *)this + 0x10);
    fn_8043C84C((char *)this + 0x20);
}

class Byte1
{
public:
    char value;
    Byte1() __asm__("fn_8043C620");
};

class ByteSet
{
public:
    char pad[0x10];
    Byte1 first[3]; // +0x10
    Byte1 second[3]; // +0x13
    Byte1 a; // +0x16
    Byte1 b; // +0x17
    Byte1 c; // +0x18
    Byte1 d; // +0x19
    ByteSet();
};

ByteSet::ByteSet()
{
}
