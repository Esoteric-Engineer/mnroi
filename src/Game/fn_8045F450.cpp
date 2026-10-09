// Base constructor of ImplF (fn_8045EE08.cpp): base constructor, then the vptr at +0x4. Names are guesses.
extern "C" char lbl_804F5968[];

class Root
{
public:
    int x; // +0x0
    Root() __asm__("fn_8042A744");
};

class BaseF : public Root
{
public:
    const void *vptr; // +0x4
    BaseF();
};

BaseF::BaseF() : vptr(lbl_804F5968)
{
}
