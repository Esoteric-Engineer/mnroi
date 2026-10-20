// AptRef::operator[](int) built through the three-word setter fn_804497E4, then AptObject's default constructor and clone (docs/versus.md section 2, section 5 row 2).

class AptObject {
public:
    AptObject();
    AptObject(void *object);
    AptObject(const AptObject &other); // fn_8044B568
    ~AptObject();                      // fn_8044B510
    AptObject clone(void);

    void *unk0; // +0x0
    int unk4;
};

class AptRef {
public:
    AptRef(void *object, char *name, int index) __asm__("fn_804497E4");
    AptRef operator[](int index);
    void operator=(char *const &value);
    void operator=(const int &value);

    void *object; // +0x0
    char *name;   // +0x4
    int index;    // +0x8
};

extern "C" void *fn_8044B81C(void *self, int value) __asm__("__9AptObjectPv");
extern "C" AptObject fn_80103080(AptObject *self);
extern "C" void *fn_8044B8B0(void *object);
extern "C" int fn_80102F10(void *object, char *name);
extern "C" int fn_8010329C(void *object, char *name);
extern "C" void fn_80102FD0(void *object, int slot, int index);
extern "C" void fn_8044AC7C(void *self, char *name, int value);
extern "C" void fn_8044ACEC(void *self, int index, char *name, int value);
extern "C" void fn_8044916C(void *self, char *name, int value);
extern "C" void fn_8044AD94(void *self, int index, char *name, int value);

// Emits no code; a top-level `return <parameter>;` makes cc1plus drop the function-end branch pair (docs/prodg.md).
inline int sn_return_decl(int a) { return a; }

AptRef AptRef::operator[](register int index)
{
    return AptRef(object, name, index);
}

AptObject::AptObject()
{
    fn_8044B81C(this, 0);
}

AptObject AptObject::clone(void)
{
    return fn_80103080(this);
}

void AptRef::operator=(register char *const &value)
{
    if (index < 0)
    {
        fn_8044AC7C(fn_8044B8B0(object), name, (int)value);
    }
    else
    {
        int slot = fn_80102F10(object, name);
        if (slot < 0)
        {
            slot = fn_8010329C(object, name);
        }
        fn_8044ACEC(fn_8044B8B0(object), index, name, (int)value);
        fn_80102FD0(object, slot, index);
    }
}

void AptRef::operator=(register const int &value)
{
    if (index < 0)
    {
        fn_8044916C(fn_8044B8B0(object), name, value);
    }
    else
    {
        int slot = fn_80102F10(object, name);
        if (slot < 0)
        {
            slot = fn_8010329C(object, name);
        }
        fn_8044AD94(fn_8044B8B0(object), index, name, value);
        fn_80102FD0(object, slot, index);
    }
}

AptObject::AptObject(register void *object) : unk0(object)
{
}
