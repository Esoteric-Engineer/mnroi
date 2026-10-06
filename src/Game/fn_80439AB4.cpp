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
