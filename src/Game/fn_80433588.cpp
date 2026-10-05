// Link wrappers that forward to the implementation's virtual slots (names are guesses; docs/versus.md section 5).

inline int sn_return_decl(int a) { return a; }

// Link's implementation as the wrappers see it: the same object as LinkImpl below, with its virtual slots declared.
class LinkImplVT
{
public:
    int unk0; // +0x0, the vptr follows at +0x4
    virtual void v0();
    virtual int v1();
    virtual void v2();
};

class Link
{
public:
    LinkImplVT *impl; // +0x0, the vptr follows at +0x4
    virtual ~Link();
    void release();
    int get();
};

void Link::release()
{
    impl->v2();
}

int Link::get()
{
    return impl->v1();
}

extern "C" void *fn_80165158(void *owner, int size);

extern "C" void *fn_8043365C(register int size, register void *owner)
{
    return fn_80165158(owner, size);
}

extern "C" int fn_804336A8(register char *self)
{
    return *(int *)(self + 0x4C);
}

extern "C" char lbl_804F31D0[];
extern "C" char lbl_804F31A8[];
extern "C" char lbl_804F3180[];
extern "C" void *fn_8042A400(void *self, void *owner, int key);

struct Name
{
    int a;
    int b;
};

class LinkBase
{
public:
    int x; // +0x0; the real constructor also stores its own vptr at +0x4
    LinkBase();
};

class LinkImpl : public LinkBase
{
public:
    const void *vptr; // +0x4
    void *owner;      // +0x8
    Name name;        // +0xC
    Name *result;     // +0x14
    LinkImpl(void *owner, const void *name);
};

LinkImpl::LinkImpl(register void *owner, register const void *name)
    : vptr(lbl_804F31D0), owner(owner), name(*(const Name *)name),
      result((Name *)fn_8042A400(this, owner, ((const Name *)name)->a))
{
}

class LinkImplB : public LinkBase
{
public:
    const void *vptr; // +0x4
    void *owner;      // +0x8
    Name name;        // +0xC
    Name *result;     // +0x14
    LinkImplB(void *owner, const int *name);
};

LinkImplB::LinkImplB(register void *owner, register const int *name)
    : vptr(lbl_804F31A8), owner(owner), name(*(const Name *)name),
      result((Name *)fn_8042A400(this, owner, ((const Name *)name)->a))
{
}

class CueBase
{
public:
    int x; // +0x0; the real constructor also stores its own vptr at +0x4
    CueBase();
};

class CueImpl : public CueBase
{
public:
    const void *vptr; // +0x4
    int name;         // +0x8
    int *result;      // +0xC
    CueImpl(const int *name);
};

CueImpl::CueImpl(register const int *name)
    : vptr(lbl_804F3180), name(*name), result((int *)fn_8042A400(this, 0, *name))
{
}
