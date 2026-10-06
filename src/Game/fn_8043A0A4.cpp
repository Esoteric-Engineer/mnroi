// OwnedCueImpl constructor (Cue implementation behind fn_80439AB4); docs/versus.md, row 8. Class names are guesses.

extern "C" char lbl_804F3360[];
extern "C" void *fn_8042A400(void *self, void *owner, int key);

struct Name
{
    int a;
    int b;
};

class CueBase
{
public:
    int x; // +0x0; the real constructor (__7CueBase) also stores its own vptr at +0x4
    CueBase();
};

class OwnedCueImpl : public CueBase
{
public:
    const void *vptr; // +0x4
    void *owner;      // +0x8
    Name name;        // +0xC
    Name *result;     // +0x14
    OwnedCueImpl(void *owner, const int *name);
};

OwnedCueImpl::OwnedCueImpl(register void *owner, register const int *name)
    : vptr(lbl_804F3360), owner(owner), name(*(const Name *)name),
      result((Name *)fn_8042A400(this, owner, name[0]))
{
}
