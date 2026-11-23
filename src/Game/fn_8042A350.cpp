// The callback Impls' reference-counted bases (docs/core.md row 19, section 4.4).
// Class names are guesses.

inline int sn_return_decl(int a) { return a; }

extern "C" void __builtin_delete(void *p);

extern "C" char lbl_804F2F48[];
extern "C" char lbl_804F2F70[];
extern "C" char lbl_804F2F98[];
extern "C" char lbl_804F2FC0[];
extern "C" char lbl_804F2FE8[];
extern "C" char lbl_804F3010[];

class RefBase
{
public:
    int ref;
    virtual ~RefBase();
};

struct Raw
{
    int ref;
    const void *vptr;
};

extern "C" void fn_8042A350(register Raw *self)
{
    self->ref++;
}

extern "C" void fn_8042A37C(register RefBase *self)
{
    self->ref--;
    if (self->ref == 0) {
        delete self;
    }
}

extern "C" int fn_8042A400(register void *self, register int owner, register int key)
{
    return owner % 0x10000 << 16 | key % 0x10000;
}

extern "C" Raw *fn_8042A744(Raw *self);
extern "C" void fn_8042A780(Raw *self, int inChrg);

#define ALIAS(sym) __asm__(".text\n\t.globl " #sym "\n\t.type " #sym ",@function\n" #sym ":");
#define SIZE(sym, n) __asm__(".size " #sym ", " #n);

#define DTOR(dtor)                                                                                 \
    extern "C" void dtor(register Raw *self, register int inChrg)                                  \
    {                                                                                              \
        fn_8042A780(self, inChrg);                                                                 \
    }

#define CTOR(ctor, vt)                                                                             \
    extern "C" Raw *ctor(register Raw *self)                                                       \
    {                                                                                              \
        fn_8042A744(self);                                                                         \
        self->vptr = vt;                                                                           \
        return self;                                                                               \
    }

DTOR(fn_8042A488)
CTOR(fn_8042A4C8, lbl_804F2FE8)
DTOR(fn_8042A514)
ALIAS(__4Base)
CTOR(fn_8042A554, lbl_804F2FC0)
SIZE(__4Base, 0x4C)
DTOR(fn_8042A5A0)
ALIAS(__7CueBase)
CTOR(fn_8042A5E0, lbl_804F2F98)
SIZE(__7CueBase, 0x4C)
DTOR(fn_8042A62C)
CTOR(fn_8042A66C, lbl_804F2F70)
DTOR(fn_8042A6B8)
CTOR(fn_8042A6F8, lbl_804F2F48)

extern "C" Raw *fn_8042A744(register Raw *self)
{
    self->vptr = lbl_804F3010;
    self->ref = 1;
    return self;
}

extern "C" void fn_8042A780(register Raw *self, register int inChrg)
{
    self->vptr = lbl_804F3010;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}
