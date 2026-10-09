// HandleF's copy constructor (class name is a guess; see fn_8045E6AC.cpp).
extern "C" char lbl_804F58A0[];
extern "C" void fn_8042A350(void *impl);

class HandleF
{
public:
    void *impl;       // +0x0
    const void *vptr; // +0x4
    HandleF(const HandleF &other);
};

HandleF::HandleF(register const HandleF &other)
{
    vptr = lbl_804F58A0;
    fn_8042A350(other.impl);
    impl = other.impl;
}
