// AptRef::operator=(const unsigned &): store a value through the int-to-String builders fn_8044F5A4/fn_8044F614 (docs/versus.md section 5, row 2).

class AptRef {
public:
    void operator=(const unsigned &value);

    void *object; // +0x0
    char *name;   // +0x4
    int index;    // +0x8
};

extern "C" void *fn_8044B8B0(void *object);
extern "C" int fn_80102F10(void *object, char *name);
extern "C" int fn_8010329C(void *object, char *name);
extern "C" void fn_80102FD0(void *object, int slot, int index);
extern "C" void fn_8044F5A4(void *self, const char *b, int c);
extern "C" void fn_8044F614(void *self, int a, const char *b, int c);

// Emits no code; a top-level `return <parameter>;` makes cc1plus drop the function-end branch pair (docs/prodg.md).
inline int sn_return_decl(int a) { return a; }

void AptRef::operator=(register const unsigned &value)
{
    if (index < 0)
    {
        fn_8044F5A4(fn_8044B8B0(object), name, value);
    }
    else
    {
        int slot = fn_80102F10(object, name);
        if (slot < 0)
        {
            slot = fn_8010329C(object, name);
        }
        fn_8044F614(fn_8044B8B0(object), index, name, value);
        fn_80102FD0(object, slot, index);
    }
}
