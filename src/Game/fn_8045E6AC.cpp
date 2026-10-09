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
