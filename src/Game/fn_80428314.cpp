// The list-wrapper handles' constructors, add, remove and for-each (docs/core.md row 9, section 4.4).
// Class names are guesses; the shapes are the Link family's (Game/fn_80432EE8.cpp).

extern "C" void *fn_801B5D3C(void *list, int index);
extern "C" void *fn_801B6040(void *list, void *entry);
extern "C" void fn_801B6768(void *list, void *entry);
extern "C" int fn_801B6A44(void *list);
extern "C" void fn_80429CA4(void *handle, int arg);

extern "C" char lbl_804F2DE0[];
extern "C" char lbl_804F2DF8[];
extern "C" char lbl_804F2E10[];
extern "C" char lbl_804F2E28[];
extern "C" char lbl_804F2E40[];

inline int sn_return_decl(int a) { return a; }

template <class T> struct Entry
{
    T *link;
    int value;
};

struct Raw
{
    void *impl;
    const void *vptr;
};

class ImplC
{
public:
    char data[0x18];
    ImplC(void *owner, const void *name) __asm__("fn_804293F4");
};

class ImplA
{
public:
    char data[0x18];
    ImplA(void *owner, const void *name) __asm__("fn_80429598");
    ImplA(void *owner, const int *name) __asm__("fn_80429C28");
};

class CueImpl
{
public:
    char data[0x18];
    CueImpl(void *owner, const void *name) __asm__("fn_8042973C");
};

class ImplG
{
public:
    char data[0x18];
    ImplG(void *owner, const void *name) __asm__("fn_804298E0");
};

class ImplD
{
public:
    char data[0x18];
    ImplD(void *owner, const void *name) __asm__("fn_80429A84");
};

class HandleC
{
public:
    ImplC *impl;
    HandleC(const HandleC &other) __asm__("fn_804294D0");
    virtual ~HandleC();
    int get() __asm__("fn_80429528");
};

class HandleA
{
public:
    ImplA *impl;
    HandleA(const HandleA &other) __asm__("fn_80429674");
    virtual ~HandleA();
    int get() __asm__("fn_804296CC");
};

class Cue
{
public:
    CueImpl *impl;
    Cue(const Cue &other) __asm__("fn_80429818");
    virtual ~Cue();
    int get() __asm__("fn_80429870");
};

class HandleG
{
public:
    ImplG *impl;
    HandleG(const HandleG &other) __asm__("fn_804299BC");
    virtual ~HandleG();
    int get() __asm__("fn_80429A14");
};

class HandleD
{
public:
    ImplD *impl;
    HandleD(const HandleD &other) __asm__("fn_80429B60");
    virtual ~HandleD();
    int get() __asm__("fn_80429BB8");
};

extern "C" Raw *fn_80428314(register Raw *self, register void *owner, register const void *name)
{
    self->vptr = lbl_804F2E40;
    self->impl = new ImplC(owner, name);
    return self;
}

extern "C" void fn_80428384(register void *list, HandleC arg)
{
    Entry<HandleC> *e = new Entry<HandleC>;
    register Entry<HandleC> *q = e;
    q->link = new HandleC(arg);
    e->value = arg.get();
    fn_801B6040(list, e);
}

extern "C" Raw *fn_8042841C(register Raw *self, register void *owner, register const void *name)
{
    self->vptr = lbl_804F2E28;
    self->impl = new ImplA(owner, name);
    return self;
}

extern "C" void fn_8042848C(register void *list, HandleA arg)
{
    Entry<HandleA> *e = new Entry<HandleA>;
    register Entry<HandleA> *q = e;
    q->link = new HandleA(arg);
    e->value = arg.get();
    fn_801B6040(list, e);
}

extern "C" Raw *fn_80428524(register Raw *self, register void *owner, register const void *name)
{
    self->vptr = lbl_804F2E10;
    self->impl = new CueImpl(owner, name);
    return self;
}

extern "C" void fn_80428594(register void *list, Cue arg)
{
    Entry<Cue> *e = new Entry<Cue>;
    register Entry<Cue> *q = e;
    q->link = new Cue(arg);
    e->value = arg.get();
    fn_801B6040(list, e);
}

extern "C" Raw *fn_8042862C(register Raw *self, register void *owner, register const void *name)
{
    self->vptr = lbl_804F2DF8;
    self->impl = new ImplG(owner, name);
    return self;
}

extern "C" void fn_8042869C(register void *list, HandleG arg)
{
    Entry<HandleG> *e = new Entry<HandleG>;
    register Entry<HandleG> *q = e;
    q->link = new HandleG(arg);
    e->value = arg.get();
    fn_801B6040(list, e);
}

extern "C" Raw *fn_80428734(register Raw *self, register void *owner, register const void *name)
{
    self->vptr = lbl_804F2DE0;
    self->impl = new ImplD(owner, name);
    return self;
}

extern "C" void fn_804287A4(register void *list, HandleD arg)
{
    Entry<HandleD> *e = new Entry<HandleD>;
    register Entry<HandleD> *q = e;
    q->link = new HandleD(arg);
    e->value = arg.get();
    fn_801B6040(list, e);
}

extern "C" Raw *fn_8042883C(register Raw *self, register void *owner, register const int *name)
{
    self->vptr = lbl_804F2E28;
    self->impl = new ImplA(owner, name);
    return self;
}

extern "C" void fn_804288AC(register void *list, HandleA arg)
{
    int key = arg.get();
    Entry<HandleA> *e = (Entry<HandleA> *)fn_801B5D3C(list, 0);
    int i = 0;
    while (i < fn_801B6A44(list)) {
        e = (Entry<HandleA> *)fn_801B5D3C(list, i);
        if (e->value == key) {
            break;
        }
        i++;
    }
    if (e == 0) {
        return;
    }
    HandleA *link = e->link;
    fn_801B6768(list, e);
    delete e;
    HandleA *dead = link;
    delete dead;
}

extern "C" void fn_804289EC(register void *list, HandleD arg)
{
    int key = arg.get();
    Entry<HandleD> *e = (Entry<HandleD> *)fn_801B5D3C(list, 0);
    int i = 0;
    while (i < fn_801B6A44(list)) {
        e = (Entry<HandleD> *)fn_801B5D3C(list, i);
        if (e->value == key) {
            break;
        }
        i++;
    }
    if (e == 0) {
        return;
    }
    HandleD *link = e->link;
    fn_801B6768(list, e);
    delete e;
    HandleD *dead = link;
    delete dead;
}

extern "C" void fn_80428B2C(register void *list, HandleG arg)
{
    int key = arg.get();
    Entry<HandleG> *e = (Entry<HandleG> *)fn_801B5D3C(list, 0);
    int i = 0;
    while (i < fn_801B6A44(list)) {
        e = (Entry<HandleG> *)fn_801B5D3C(list, i);
        if (e->value == key) {
            break;
        }
        i++;
    }
    if (e == 0) {
        return;
    }
    HandleG *link = e->link;
    fn_801B6768(list, e);
    delete e;
    HandleG *dead = link;
    delete dead;
}

extern "C" void fn_80428C6C(register void *list, Cue arg)
{
    int key = arg.get();
    Entry<Cue> *e = (Entry<Cue> *)fn_801B5D3C(list, 0);
    int i = 0;
    while (i < fn_801B6A44(list)) {
        e = (Entry<Cue> *)fn_801B5D3C(list, i);
        if (e->value == key) {
            break;
        }
        i++;
    }
    if (e == 0) {
        return;
    }
    Cue *link = e->link;
    fn_801B6768(list, e);
    delete e;
    Cue *dead = link;
    delete dead;
}

extern "C" void fn_80428DAC(register void *list, HandleC arg)
{
    int key = arg.get();
    Entry<HandleC> *e = (Entry<HandleC> *)fn_801B5D3C(list, 0);
    int i = 0;
    while (i < fn_801B6A44(list)) {
        e = (Entry<HandleC> *)fn_801B5D3C(list, i);
        if (e->value == key) {
            break;
        }
        i++;
    }
    if (e == 0) {
        return;
    }
    HandleC *link = e->link;
    fn_801B6768(list, e);
    delete e;
    HandleC *dead = link;
    delete dead;
}

extern "C" void fn_80428EEC(register void *list, register int arg)
{
    Entry<void> *e;
    int i = 0;
    while (i < fn_801B6A44(list)) {
        e = (Entry<void> *)fn_801B5D3C(list, i);
        fn_80429CA4(e->link, arg);
        i++;
    }
}
