// Destructor, getResult and invoke of ImplF, ImplE and ImplD (guessed names; constructors in fn_8045EE08.cpp, fn_8045E6AC.cpp).
inline int sn_return_decl(int a) { return a; }

extern char lbl_804F58D0[];
extern char lbl_804F58F8[];
extern char lbl_804F5920[];

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

class ImplE
{
public:
    char pad[0x4]; // +0x0, the base's word
    const void *vptr; // +0x4
    int name;         // +0x8; callback
    void *result;     // +0xC
    void *getResult();
    void invoke(int a, float f);
};

extern "C" void fn_8045F384(void *self, int inChrg);

extern "C" void fn_8045F064(register ImplE *self, register int inChrg)
{
    self->vptr = lbl_804F58F8;
    fn_8045F384(self, inChrg);
}

void *ImplE::getResult()
{
    return result;
}

void ImplE::invoke(register int a, register float f)
{
    ((void (*)(int, float))name)(a, f);
    return;
}

class ImplD
{
public:
    char pad[0x4]; // +0x0, the base's word
    const void *vptr; // +0x4
    int name;         // +0x8; callback
    void *result;     // +0xC
    void *getResult();
    void invoke(int a, int b, int c);
};

extern "C" void fn_8042A6B8(void *self, int inChrg);

extern "C" void fn_8045F13C(register ImplD *self, register int inChrg)
{
    self->vptr = lbl_804F5920;
    fn_8042A6B8(self, inChrg);
}

void *ImplD::getResult()
{
    return result;
}

void ImplD::invoke(register int a, register int b, register int c)
{
    ((void (*)(int, int, int))name)(a, b, c);
    return;
}
