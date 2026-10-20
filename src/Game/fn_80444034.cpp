// Implementation object behind the handle of fn_80443E9C: base constructor, vptr, owner, name copy.
// Class names are guesses.

extern "C" char lbl_804F4C80[];
extern "C" void *fn_8042A400(void *self, void *owner, int key);

struct Name
{
    int a;
    int b;
};

class Base
{
public:
    int x; // +0x0; the real constructor (__4Base) also stores its own vptr at +0x4
    Base();
};

class Impl : public Base
{
public:
    const void *vptr; // +0x4
    void *owner;      // +0x8
    Name name;        // +0xC
    Name *result;     // +0x14
    Impl(void *owner, const void *name);
};

Impl::Impl(register void *owner, register const void *name)
    : vptr(lbl_804F4C80), owner(owner), name(*(const Name *)name),
      result((Name *)fn_8042A400(this, owner, ((const Name *)name)->a))
{
}
