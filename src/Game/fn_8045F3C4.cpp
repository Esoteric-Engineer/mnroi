// Base constructor of ImplE (fn_8045E6AC.cpp): base constructor, then the vptr at +0x4. Names are guesses.
extern "C" char lbl_804F5990[];

class Root
{
public:
    int x; // +0x0
    Root() __asm__("fn_8042A744");
};

class BaseE : public Root
{
public:
    const void *vptr; // +0x4
    BaseE();
};

BaseE::BaseE() : vptr(lbl_804F5990)
{
}
