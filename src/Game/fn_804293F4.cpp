// The callback handles' Impl constructors, destructors, copy constructors, get and invoke (docs/core.md row 19, section 4.4).
// Class names are guesses, shared with Game/fn_80428314.cpp.

extern "C" void fn_8042A350(void *impl);
extern "C" void fn_8042A37C(void *impl);
extern "C" void __builtin_delete(void *p);

extern "C" char lbl_804F2DE0[];
extern "C" char lbl_804F2DF8[];
extern "C" char lbl_804F2E10[];
extern "C" char lbl_804F2E28[];
extern "C" char lbl_804F2E40[];
extern "C" char lbl_804F2E58[];
extern "C" char lbl_804F2E80[];
extern "C" char lbl_804F2EA8[];
extern "C" char lbl_804F2ED0[];
extern "C" char lbl_804F2EF8[];
extern "C" char lbl_804F2F20[];

struct Name
{
    int a;
    int b;
};

extern "C" Name *fn_8042A400(void *self, void *owner, int key);

class OtherBase
{
public:
    int x;
    OtherBase() __asm__("fn_8042A4C8");
};

class Base
{
public:
    int x;
    Base();
};

class CueBase
{
public:
    int x;
    CueBase();
};

class BaseG
{
public:
    int x;
    BaseG() __asm__("fn_8042A66C");
};

class BaseD
{
public:
    int x;
    BaseD() __asm__("fn_8042A6F8");
};

#define IMPL(Cls, B)                                                                               \
    class Cls : public B                                                                           \
    {                                                                                              \
    public:                                                                                        \
        const void *vptr;                                                                          \
        void *owner;                                                                               \
        Name name;                                                                                 \
        const Name *result;                                                                        \
        Cls(void *owner, const Name *name);                                                        \
        Cls(void *owner, const int *name);                                                         \
    };

IMPL(ImplC, OtherBase)
IMPL(ImplA, Base)
IMPL(CueImpl, CueBase)
IMPL(ImplG, BaseG)
IMPL(ImplD, BaseD)

#define IMPL_CTOR(sym, Cls, Arg, vt)                                                               \
    __asm__(".text\n\t.globl " #sym "\n\t.type " #sym ",@function\n" #sym ":");                    \
    Cls::Cls(register void *owner, register const Arg *name)                                       \
        : vptr(vt), owner(owner), name(*(const Name *)name),                                       \
          result(fn_8042A400(this, owner, *(const int *)name))                                     \
    {                                                                                              \
    }                                                                                              \
    __asm__(".size " #sym ", 0x7C");

// The Impl as the handles see it.
class ImplVT
{
public:
    int unk0;
    virtual void v0();
    virtual int get();          // +0x10
    virtual void invoke(int a); // +0x18
};

struct Handle
{
    ImplVT *impl;
    const void *vptr;
};

#define HANDLE(dtor, cdtor, copy, getter, vt)                                                          \
    __asm__(".text\n\t.globl " #dtor "\n\t.type " #dtor ",@function\n" #dtor ":");                 \
    extern "C" void cdtor(register Handle *self, register int inChrg)                          \
    {                                                                                              \
        self->vptr = vt;                                                                           \
        fn_8042A37C(self->impl);                                                                   \
        if (inChrg & 1) {                                                                          \
            __builtin_delete(self);                                                                \
        } else {                                                                                   \
        }                                                                                          \
    }                                                                                              \
    __asm__(".size " #dtor ", 0x60");                                                              \
                                                                                                   \
    extern "C" Handle *copy(register Handle *self, register const Handle *other)                   \
    {                                                                                              \
        self->vptr = vt;                                                                           \
        fn_8042A350(other->impl);                                                                  \
        self->impl = other->impl;                                                                  \
        return self;                                                                               \
    }                                                                                              \
                                                                                                   \
    extern "C" int getter(register Handle *self)                                                    \
    {                                                                                              \
        return self->impl->get();                                                                  \
    }

IMPL_CTOR(fn_804293F4, ImplC, Name, lbl_804F2F20)
HANDLE(_._7HandleC, fn_80429470, fn_804294D0, fn_80429528, lbl_804F2E40)
IMPL_CTOR(fn_80429598, ImplA, Name, lbl_804F2EF8)
HANDLE(_._7HandleA, fn_80429614, fn_80429674, fn_804296CC, lbl_804F2E28)
IMPL_CTOR(fn_8042973C, CueImpl, Name, lbl_804F2ED0)
HANDLE(_._3Cue, fn_804297B8, fn_80429818, fn_80429870, lbl_804F2E10)
IMPL_CTOR(fn_804298E0, ImplG, Name, lbl_804F2EA8)
HANDLE(_._7HandleG, fn_8042995C, fn_804299BC, fn_80429A14, lbl_804F2DF8)
IMPL_CTOR(fn_80429A84, ImplD, Name, lbl_804F2E80)
HANDLE(_._7HandleD, fn_80429B00, fn_80429B60, fn_80429BB8, lbl_804F2DE0)
IMPL_CTOR(fn_80429C28, ImplA, int, lbl_804F2E58)

extern "C" void fn_80429CA4(register Handle *self, register int a)
{
    self->impl->invoke(a);
}
