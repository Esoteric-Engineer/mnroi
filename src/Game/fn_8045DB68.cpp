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

// Loads the music bank "<dir>/<name>.mpf" and starts its streams (the .mus files), then sets the music volume.
extern "C" int sprintf(char *dst, const char *fmt, ...);
extern "C" void *fn_801A89C0(char *path, unsigned *size, const char *tag, int a, int b);
extern "C" int fn_80266134(void *buf);
extern "C" void fn_8011931C(char *a, char *b);
extern "C" int fn_8026A57C(unsigned id, char *path, int a);
extern "C" void fn_8026A5EC(unsigned id, int a, float f);
extern "C" int fn_8026A758(unsigned id, char *path, int a);
extern "C" void fn_8026A7CC(unsigned id);
extern "C" int fn_80264968(unsigned id, int a);
extern "C" int fn_801192D4(int a);
extern "C" void fn_80119B20(int v);
extern "C" int fn_8010E280(void);
extern "C" unsigned int fn_8010C7EC(void *obj, int a, int b);
extern "C" void fn_8024D258(void);
extern "C" void fn_8024D298(void);
extern "C" void fn_8026B0A0(int a, int b);
extern "C" void fn_802654BC(int a);
extern "C" void fn_8026633C(int a);
extern "C" void fn_80264D20(unsigned id, int a);
extern "C" void fn_801ACC0C(void *p);

extern char lbl_80497B14[], lbl_80497B20[], lbl_80497B2C[], lbl_80497B3C[], lbl_80497B50[];
extern char lbl_8066D808[8];
extern int lbl_8066BDD0, lbl_8066BDD4;

struct MusicBank
{
    const char *dir;  // +0x0
    const char *name; // +0x4
    int hasSecond;    // +0x8
    int hasOverlay;   // +0xC
    void *data;       // +0x10
    unsigned size;    // +0x14
};

extern "C" void fn_8045E354(register MusicBank *self)
{
    char buf[0x80];
    int a;
    char pathA[0x80];
    int b;
    char pathB[0x80];
    unsigned c;

    if (self->data) {
        return;
    }
    sprintf(buf, lbl_80497B14, self->dir, self->name);
    self->data = fn_801A89C0(buf, &self->size, lbl_80497B20, 2, 0x10);
    lbl_8066BDD4 += self->size;
    a = fn_80266134(self->data);
    sprintf(buf, lbl_80497B2C, self->dir);
    fn_8011931C(buf, pathA);
    a = fn_8026A57C(0x11000001, pathA, 500);
    if (a >= 0) {
        fn_8026A5EC(0x11000001, 3, 2.0f);
    }
    if (self->hasSecond) {
        b = fn_80266134(self->data);
        sprintf(buf, lbl_80497B3C, self->dir);
        fn_8011931C(buf, pathB);
        b = fn_8026A57C(0x11000004, pathB, 500);
        if (b >= 0) {
            fn_8026A5EC(0x11000004, 3, 2.0f);
        }
    }
    if (self->hasOverlay) {
        sprintf(buf, lbl_80497B50, self->dir);
        fn_8011931C(buf, pathA);
        a = fn_8026A758(0x11000002, pathA, 2);
        if (a >= 0) {
            fn_8026A7CC(0x11000002);
        }
        a = fn_80264968(0x11000002, 0);
    }
    b = fn_801192D4(1);
    fn_80119B20(b);
    c = fn_8010C7EC(lbl_8066D808, 1, fn_8010E280() ? 0x12d : 0x12c);
    c = c * b / 127;
    if (lbl_8066BDD0 == 0) {
        c = 0;
    }
    fn_8024D258();
    fn_8026B0A0(-1, (char)c);
    fn_8024D298();
}

// Stops the bank's streams and frees the .mpf buffer.
extern "C" void fn_8045E618(register MusicBank *self)
{
    fn_8024D258();
    fn_802654BC(-1);
    fn_8024D298();
    if (self->data == 0) {
        return;
    }
    if (self->hasOverlay) {
        fn_80264D20(0x11000002, 0);
    }
    fn_8026633C(-1);
    fn_801ACC0C(self->data);
    self->data = 0;
    lbl_8066BDD4 -= self->size;
}
