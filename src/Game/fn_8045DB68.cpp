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

// Clamp setters on the settings object (see Game/fn_804580CC.cpp).
struct Setting
{
    int pad0[3];
    int fC;  // +0xC
    int f10; // +0x10
    int f14; // +0x14
};

extern "C" void fn_8045DEFC(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 40) {
        v = 40;
    }
    self->fC = v;
}

extern "C" void fn_8045DF40(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045DF84(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 19) {
        v = 19;
    }
    self->f10 = v;
}

extern "C" void fn_8045DFC8(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045E00C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 40) {
        v = 40;
    }
    self->f10 = v;
}

extern "C" void fn_8045E050(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045E094(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 19) {
        v = 19;
    }
    self->f10 = v;
}

extern "C" void fn_8045E0D8(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045E11C(register Setting *self, register int v)
{
    if (v < 1) {
        v = 1;
    } else if (v > 7) {
        v = 7;
    }
    self->f10 = v;
}

extern "C" void fn_8045E160(register Setting *self, register int v)
{
    if (v < 1) {
        v = 1;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f14 = v;
}

extern "C" void fn_8045E1A4(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045E1E8(register Setting *self, register int v)
{
    if (v < 1) {
        v = 1;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f10 = v;
}

extern "C" void fn_8045E22C(register Setting *self, register int v)
{
    if (v < 1) {
        v = 1;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f10 = v;
}

extern char lbl_804F5868[];
extern "C" void __builtin_delete(void *p);

class Sink
{
public:
    const void *vptr; // +0x0
    Sink();
};

Sink::Sink() : vptr(lbl_804F5868)
{
}

extern "C" void fn_8045E2A4(register Sink *self, register int inChrg)
{
    self->vptr = lbl_804F5868;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

class Pair2
{
public:
    const char *a; // +0x0
    const char *b; // +0x4
    int c;         // +0x8
    int d;         // +0xC
    int e;         // +0x10
    int f;         // +0x14
    Pair2(register const char *a, register const char *b, register int c, register int d);
};

Pair2::Pair2(register const char *a, register const char *b, register int c, register int d)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    e = 0;
    f = 0;
}
