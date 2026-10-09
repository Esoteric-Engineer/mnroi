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
extern "C" void fn_80165138(void *);
extern "C" void *fn_804336A8(void *);
extern "C" void *fn_8043365C(int size, void *owner);
extern "C" void *fn_8045EBBC(void *) __asm__("fn_8045EBBC");
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
