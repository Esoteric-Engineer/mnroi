// Implementation objects behind HandleA/B/C (docs/versus.md section 5, row 2): base constructor, vptr, key, lookup. Class names are guesses.
extern "C" void *fn_8042A400(void *self, void *owner, int key);

extern char lbl_804F5808[], lbl_804F57E0[], lbl_804F57B8[];

class Base
{
public:
    int x; // +0x0; the real constructor (__4Base) also stores its own vptr at +0x4
    Base();
};

class LinkBase
{
public:
    int x; // +0x0
    LinkBase();
};

class OtherBase
{
public:
    int x; // +0x0
    OtherBase() __asm__("fn_8042A4C8");
};

class ImplA : public Base
{
public:
    const void *vptr; // +0x4
    int name;         // +0x8; callback
    void *result;     // +0xC
    ImplA(register const void *name);
    void *getResult();
    void invoke(int a);
};

ImplA::ImplA(register const void *name)
    : vptr(lbl_804F5808), name(*(const int *)name), result(fn_8042A400(this, 0, *(const int *)name))
{
}

class ImplB : public LinkBase
{
public:
    const void *vptr; // +0x4
    int name;         // +0x8; callback
    void *result;     // +0xC
    ImplB(register const void *name);
    void *getResult();
    void invoke();
};

ImplB::ImplB(register const void *name)
    : vptr(lbl_804F57E0), name(*(const int *)name), result(fn_8042A400(this, 0, *(const int *)name))
{
}

class ImplC : public OtherBase
{
public:
    const void *vptr; // +0x4
    int name;         // +0x8; callback
    void *result;     // +0xC
    ImplC(register const void *name);
    void *getResult();
    void invoke(int a, int b);
};

ImplC::ImplC(register const void *name)
    : vptr(lbl_804F57B8), name(*(const int *)name), result(fn_8042A400(this, 0, *(const int *)name))
{
}

// Destructors: reset the vptr, then run the base's.
extern "C" void fn_8042A488(void *self, int inChrg);
extern "C" void fn_80433C30(void *self, int inChrg);
extern "C" void fn_8042A514(void *self, int inChrg);

extern "C" void fn_8045DCAC(register ImplC *self, register int inChrg)
{
    self->vptr = lbl_804F57B8;
    fn_8042A488(self, inChrg);
}

void *ImplC::getResult()
{
    return result;
}

void ImplC::invoke(register int a, register int b)
{
    ((void (*)(int, int))name)(a, b);
    return;
}

extern "C" void fn_8045DD7C(register ImplB *self, register int inChrg)
{
    self->vptr = lbl_804F57E0;
    fn_80433C30(self, inChrg);
}

void *ImplB::getResult()
{
    return result;
}

void ImplB::invoke()
{
    ((void (*)())name)();
    return;
}

extern "C" void fn_8045DE34(register ImplA *self, register int inChrg)
{
    self->vptr = lbl_804F5808;
    fn_8042A514(self, inChrg);
}

void *ImplA::getResult()
{
    return result;
}

void ImplA::invoke(register int a)
{
    ((void (*)(int))name)(a);
    return;
}
