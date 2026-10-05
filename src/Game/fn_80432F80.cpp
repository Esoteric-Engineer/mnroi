// Two more handle constructors: Link with a second implementation (fn_80433750, 0x18 bytes) and Cue (vtable lbl_804F2E10), which allocates a 0x10-byte one (fn_804337CC). Class names are guesses.

extern "C" char lbl_804F3148[];
extern "C" char lbl_804F2E10[];

inline int sn_return_decl(int a) { return a; }

class LinkImplB
{
public:
    char data[0x18];
    LinkImplB(void *owner, const int *name);
};

class Link
{
public:
    void *impl;       // +0x0
    const void *vptr; // +0x4
    Link(void *owner, const int *name);
};

Link::Link(register void *owner, register const int *name)
{
    vptr = lbl_804F3148;
    impl = new LinkImplB(owner, name);
}

class CueImpl
{
public:
    char data[0x10];
    CueImpl(const int *name);
};

class Cue
{
public:
    CueImpl *impl;    // +0x0
    const void *vptr; // +0x4
    Cue(const int *name);
};

Cue::Cue(register const int *name)
{
    vptr = lbl_804F2E10;
    impl = new CueImpl(name);
}
