// OwnedCueImpl virtual slots 1 and 2 (vtable lbl_804F3360); docs/versus.md, row 8. Class names are guesses.

struct Name
{
    int a;
    int b;
};

struct Pmf // a member-function pointer: delta, index, function
{
    short delta;
    short index;
    void *pfn;
};

class CueBase
{
public:
    int x; // +0x0; the real constructor also stores its own vptr at +0x4
};

class OwnedCueImpl : public CueBase
{
public:
    const void *vptr; // +0x4
    void *owner;      // +0x8
    Pmf name;         // +0xC
    Name *result;     // +0x14
    Name *getResult();
    void invoke(int arg);
};

Name *OwnedCueImpl::getResult()
{
    return result;
}

void OwnedCueImpl::invoke(register int arg)
{
    ((void (*)(void *, int))name.pfn)((char *)owner + name.delta, arg);
    return;
}
