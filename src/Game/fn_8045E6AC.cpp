// Constructor of a list-derived class (docs/versus.md section 5, row 2); class names are guesses.
class List
{
public:
    List(int n, float f) __asm__("fn_801B5BA8");
};

class ListA : public List
{
public:
    ListA();
};

ListA::ListA() : List(4, 1.0f)
{
}

extern "C" void fn_801B5C74(void *self, int flag);
extern "C" void __builtin_delete(void *p);

// ListA destructor, hand-written C shape (matching_notes.md)
extern "C" void fn_8045E6F8(register void *self, register int inChrg)
{
    fn_801B5C74(self, 2);
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

class ListB : public ListA
{
public:
    ListB();
};

ListB::ListB()
{
}

// ListB destructor: forwards to ListA's with the in-charge flag
extern "C" void fn_8045E790(register void *self, register int inChrg)
{
    fn_8045E6F8(self, inChrg);
}

class ListC : public ListB
{
public:
    char pad[0x20];
    int n; // +0x24
    ListC(register int v);
};

ListC::ListC(register int v) : n(v)
{
}

// ListC destructor
extern "C" void fn_8045E818(register void *self, register int inChrg)
{
    fn_8045E790(self, inChrg);
}

// Getters on a class of unknown identity (name guessed)
class Host
{
public:
    char pad0[0x2DC];
    int a; // +0x2DC
    char pad1[0x2B4];
    int b; // +0x594
    int Get2DC();
    int Get594();
};

int Host::Get2DC()
{
    return a;
}

int Host::Get594()
{
    return b;
}

// Registers an entry on the list at +0x24 (same shape as fn_80433198, over a derived entry class)
extern "C" void fn_80165118(void *);
extern "C" void *fn_801B6040(void *list, void *entry);
extern "C" void fn_80165138(void *);
extern "C" void *fn_804336A8(void *);
extern "C" void *fn_8043365C(int size, void *owner);
extern "C" void *fn_8045EBBC(void *) __asm__("__10ListEntryB");
extern "C" void fn_80164544(void *list, void *entry, void *self, int b);

struct Owner
{
    char pad[0x24];
    void *list; // +0x24
};

struct NewEntry
{
    char pad[0x10];
    int value; // +0x10
};

extern "C" void fn_8045E8B0(register Owner *self, register int a, register int b)
{
    fn_80165118(fn_804336A8(self->list));
    NewEntry *e = (NewEntry *)fn_8045EBBC(fn_8043365C(0x14, fn_804336A8(self->list)));
    e->value = a;
    fn_80164544(self->list, e, self, b);
    fn_80165138(fn_804336A8(self->list));
}

// HandleD/HandleE (guessed names): handle constructors like HandleA (Game/fn_80457688.cpp), over the not yet claimed impl constructors.
extern char lbl_804F2DE0[];
extern char lbl_804F58B8[];

extern "C" void *fn_8042A400(void *self, void *owner, int key);
extern char lbl_804F5920[];
extern char lbl_804F58F8[];

class BaseD
{
public:
    int x; // +0x0; the base constructor also stores its own vptr at +0x4
    BaseD() __asm__("fn_8042A6F8");
};

class BaseE
{
public:
    int x; // +0x0
    BaseE();
};

class ImplD : public BaseD
{
public:
    const void *vptr; // +0x4
    int name;         // +0x8; callback
    void *result;     // +0xC
    ImplD(register const void *name);
};

class ImplE : public BaseE
{
public:
    const void *vptr; // +0x4
    int name;         // +0x8; callback
    void *result;     // +0xC
    ImplE(register const void *name);
};

class HandleD
{
public:
    ImplD *impl;      // +0x0
    const void *vptr; // +0x4
    HandleD(register const void *name);
};

HandleD::HandleD(register const void *name)
{
    vptr = lbl_804F2DE0;
    impl = new ImplD(name);
}

class HandleE
{
public:
    ImplE *impl;      // +0x0
    const void *vptr; // +0x4
    HandleE(register const void *name);
    HandleE(const HandleE &other);
    ~HandleE();
    int get();
};

HandleE::HandleE(register const void *name)
{
    vptr = lbl_804F58B8;
    impl = new ImplE(name);
}

// Pushes a new {HandleE copy, HandleE::get()} entry onto the list (same shape as fn_80432EE8); the by-value handle is destroyed here.
struct HandleEntry
{
    HandleE *handle; // +0x0
    int value;       // +0x4
};

void fn_8045EA24(register void *list, HandleE arg)
{
    HandleEntry *e = new HandleEntry;
    register HandleEntry *q = e;
    q->handle = new HandleE(arg);
    e->value = arg.get();
    fn_801B6040(list, e);
}

// HandleF (guessed name): the same pair over another handle class.
extern char lbl_804F58A0[];

class ImplF
{
public:
    char data[0x10];
    ImplF(register const void *name);
};

class HandleF
{
public:
    ImplF *impl;      // +0x0
    const void *vptr; // +0x4
    HandleF(register const void *name);
    HandleF(const HandleF &other);
    ~HandleF();
    int get();
};

HandleF::HandleF(register const void *name)
{
    vptr = lbl_804F58A0;
    impl = new ImplF(name);
}

struct HandleFEntry
{
    HandleF *handle; // +0x0
    int value;       // +0x4
};

void fn_8045EB24(register void *list, HandleF arg)
{
    HandleFEntry *e = new HandleFEntry;
    register HandleFEntry *q = e;
    q->handle = new HandleF(arg);
    e->value = arg.get();
    fn_801B6040(list, e);
}

// Entry constructor over EntryBase (as ListEntry in Game/fn_80433588.cpp); name guessed.
extern char lbl_804F5948[];

class EntryBase
{
public:
    void *x[3]; // +0x0
    EntryBase();
};

class ListEntryB : public EntryBase
{
public:
    const void *vptr; // +0xC
    ListEntryB();
};

ListEntryB::ListEntryB() : vptr(lbl_804F5948) {}

ImplD::ImplD(register const void *name)
    : vptr(lbl_804F5920), name(*(const int *)name), result(fn_8042A400(this, 0, *(const int *)name))
{
}

ImplE::ImplE(register const void *name)
    : vptr(lbl_804F58F8), name(*(const int *)name), result(fn_8042A400(this, 0, *(const int *)name))
{
}
