// HandleE's copy constructor (class name is a guess; see fn_8045E6AC.cpp).
extern "C" char lbl_804F58B8[];
extern "C" void fn_8042A350(void *impl);

class HandleE
{
public:
    void *impl;       // +0x0
    const void *vptr; // +0x4
    HandleE(const HandleE &other);
};

HandleE::HandleE(register const HandleE &other)
{
    vptr = lbl_804F58B8;
    fn_8042A350(other.impl);
    impl = other.impl;
}
