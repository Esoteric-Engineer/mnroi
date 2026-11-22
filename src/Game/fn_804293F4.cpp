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
    short delta;
    short index;
    void (*fn)();
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

#define IMPL(Cls, B, Params)                                                                             \
    class Cls : public B                                                                           \
    {                                                                                              \
    public:                                                                                        \
        const void *vptr;                                                                          \
        void *owner;                                                                               \
        Name name;                                                                                 \
        const Name *result;                                                                        \
        Cls(void *owner, const Name *name);                                                        \
        Cls(void *owner, const int *name);                                                         \
        const Name *get();                                                                         \
        void call Params;                                                                          \
    };

IMPL(ImplC, OtherBase, (int a, int b))
IMPL(ImplA, Base, (int a))
IMPL(ImplAi, Base, (int a))
IMPL(CueImpl, CueBase, (int a))
IMPL(ImplG, BaseG, (int a, int b))
IMPL(ImplD, BaseD, (int a, int b, int c))

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
IMPL_CTOR(fn_80429C28, ImplAi, int, lbl_804F2E58)

extern "C" void fn_80429CA4(register Handle *self, register int a)
{
    self->impl->invoke(a);
}

extern "C" void fn_8042A488(void *self, int inChrg);
extern "C" void fn_8042A514(void *self, int inChrg);
extern "C" void fn_8042A5A0(void *self, int inChrg);
extern "C" void fn_8042A62C(void *self, int inChrg);
extern "C" void fn_8042A6B8(void *self, int inChrg);

#define ALIAS(sym) __asm__(".text\n\t.globl " #sym "\n\t.type " #sym ",@function\n" #sym ":");
#define SIZE(sym, n) __asm__(".size " #sym ", " #n);

#define IMPL_BODY(Cls, vt, base, dtor, getter)                                                     \
    inline int sn_return_##dtor(int a) { return a; }                                               \
    extern "C" void dtor(register Cls *self, register int inChrg)                                  \
    {                                                                                              \
        self->vptr = vt;                                                                           \
        base(self, inChrg);                                                                        \
    }                                                                                              \
                                                                                                   \
    inline void sn_label_##getter() { clear:; }                                                    \
    ALIAS(getter)                                                                                  \
    const Name *Cls::get()                                                                         \
    {                                                                                              \
        return result;                                                                             \
    }                                                                                              \
    SIZE(getter, 0x34)

#define CALL(Cls, sym, size, Params, Types, Args)                                                  \
    ALIAS(sym)                                                                                     \
    void Cls::call Params                                                                          \
    {                                                                                              \
        ((void(*) Types)name.fn)((char *)owner + name.delta, Args);                                \
        return;                                                                                    \
    }                                                                                              \
    SIZE(sym, size)

#define P1 (register int a)
#define P2 (register int a, register int b)
#define P3 (register int a, register int b, register int c)
#define T1 (void *, int)
#define T2 (void *, int, int)
#define T3 (void *, int, int, int)
#define A1 a
#define A2 a, b
#define A3 a, b, c

IMPL_BODY(ImplAi, lbl_804F2E58, fn_8042A514, fn_80429D10, fn_80429D5C)
CALL(ImplAi, fn_80429D90, 0x6C, P1, T1, A1)
IMPL_BODY(ImplD, lbl_804F2E80, fn_8042A6B8, fn_80429DFC, fn_80429E48)
CALL(ImplD, fn_80429E7C, 0x7C, P3, T3, A3)
IMPL_BODY(ImplG, lbl_804F2EA8, fn_8042A62C, fn_80429EF8, fn_80429F44)
CALL(ImplG, fn_80429F78, 0x74, P2, T2, A2)
IMPL_BODY(CueImpl, lbl_804F2ED0, fn_8042A5A0, fn_80429FEC, fn_8042A038)
CALL(CueImpl, fn_8042A06C, 0x6C, P1, T1, A1)
IMPL_BODY(ImplA, lbl_804F2EF8, fn_8042A514, fn_8042A0D8, fn_8042A124)
CALL(ImplA, fn_8042A158, 0x6C, P1, T1, A1)
IMPL_BODY(ImplC, lbl_804F2F20, fn_8042A488, fn_8042A1C4, fn_8042A210)
CALL(ImplC, fn_8042A244, 0x74, P2, T2, A2)
