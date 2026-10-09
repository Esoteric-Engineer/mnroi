// ImplF's destructor and methods (class name is a guess; see fn_8045EE08.cpp and the ImplA methods in fn_8045DB68.cpp).
inline int sn_return_decl(int a) { return a; }

extern char lbl_804F58D0[];

class ImplF
{
public:
    char pad[0x4]; // +0x0, the base's word
    const void *vptr; // +0x4
    int name;         // +0x8; callback
    void *result;     // +0xC
    void *getResult();
    void invoke(int a);
};

// Destructor: resets the vptr, then runs the base's.
extern "C" void fn_8045F410(void *self, int inChrg);

extern "C" void fn_8045EF9C(register ImplF *self, register int inChrg)
{
    self->vptr = lbl_804F58D0;
    fn_8045F410(self, inChrg);
}

void *ImplF::getResult()
{
    return result;
}

void ImplF::invoke(register int a)
{
    ((void (*)(int))name)(a);
    return;
}
