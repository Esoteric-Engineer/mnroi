// Cue-vtable handle constructor over a 0x18-byte implementation (fn_8043A0A4), and the Attr descriptor chain; class names are guesses.

extern "C" char lbl_804F2E10[];

class OwnedCueImpl
{
public:
    char data[0x18];
    OwnedCueImpl(void *owner, const int *name);
};

class OwnedCue
{
public:
    OwnedCueImpl *impl; // +0x0
    const void *vptr;   // +0x4
    OwnedCue(void *owner, const int *name);
};

OwnedCue::OwnedCue(register void *owner, register const int *name)
{
    vptr = lbl_804F2E10;
    impl = new OwnedCueImpl(owner, name);
}

class Attr
{
public:
    int a;                    // +0x0
    const void *b;            // +0x4
    mutable const Attr *link; // +0x8
    Attr(register int a, register int b);
    Attr(register int a, register const char *b);
    const Attr &chain(register const Attr &next) const;
};

Attr::Attr(register int a_, register int b_)
    : a(a_), b((const void *)b_), link(0)
{
}

Attr::Attr(register int a_, register const char *b_)
    : a(a_), b(b_), link(0)
{
}

const Attr &Attr::chain(register const Attr &next) const
{
    next.link = this;
    return next;
}

class Slot
{
public:
    int w0; // +0x0
    int w1; // +0x4
    int w2; // +0x8
    int w3; // +0xC
    int w4; // +0x10
    Slot();
};

Slot::Slot()
{
    w0 = 0;
    w1 = 0;
    w2 = 0;
    w3 = 0;
    w4 = 0;
}

extern "C" void fn_8043A348(void *);
extern "C" void fn_8043A278(void *);

extern "C" void fn_80439C24(register Slot *self)
{
    fn_8043A348(self);
    fn_8043A278(self);
}

extern "C" int fn_80243F94(int);
extern "C" void fn_8023E98C(void);
extern "C" int fn_80243FFC(int, int *, int *);

extern "C" int fn_80439C64(register int *self, register int unused)
{
    int status;
    int result;
    int extra;
    while (1)
    {
        status = fn_80243F94(*self);
        switch (status)
        {
        case 0:
            fn_8023E98C();
            break;
        case 1:
            status = fn_80243FFC(*self, &extra, &result);
            *self = 0;
            return result;
        case -1:
            break;
        }
    }
}

extern "C" void fn_8043A20C(void *, int);
extern "C" void fn_8043A2DC(void *, int);

extern "C" void fn_80439D2C(register Slot *self, register int arg)
{
    fn_8043A278(self);
    fn_8043A20C(self, arg);
    fn_8043A2DC(self, arg);
}
