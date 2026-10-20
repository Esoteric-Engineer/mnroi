// AptObject-to-String converter for the APT registrars (docs/versus.md section 5, row 2).

class AptObject {
public:
    AptObject(const AptObject &other);
    ~AptObject();
    void *unk0;
    int unk4;
};

class String {
public:
    String(const char *s);
    String(const String &other);
    String();
    ~String();
    char data[0x4C];
} __attribute__((aligned(8)));

extern "C" String fn_80103080(const AptObject &o);
extern "C" void fn_804494AC(String *self);

// Emits no code; a top-level `return <parameter>;` makes cc1plus drop the function-end branch pair (docs/prodg.md).
inline int sn_return_decl(int a) { return a; }

extern "C" String fn_8044D6A0(register const AptObject &o)
{
    return fn_80103080(o);
}

extern "C" String fn_8044D6E8(String s)
{
    fn_804494AC(&s);
    return s;
}
