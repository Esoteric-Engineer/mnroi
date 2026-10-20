// APT native-registration helpers for handlers taking an int and returning a String (docs/versus.md section 5, row 2).

class String {
public:
    String(const char *s);
    String();
    ~String();
    char data[0x4C];
} __attribute__((aligned(8)));

struct Tag { // one-byte dispatch tag; the thunks copy it into r29 and ignore it
    unsigned char v;
};

struct NativeEntry {
    const char *name;
    void *thunk;
    void *func;
};

extern NativeEntry lbl_805663A4[]; // bss
extern int lbl_8066D6FC;           // sbss, entry count
extern "C" void fn_8044B4EC(const char *file, int line);
extern "C" void *fn_8044AA54(int self, int index);
extern "C" int fn_8044C1B4(const String &self);
extern "C" String fn_8044F1D4(String s);

// Emits no code; a top-level `return <parameter>;` makes cc1plus drop the function-end branch pair (docs/prodg.md).
inline int sn_return_decl(int a) { return a; }

extern "C" {
String fn_8044ECE4(register int a, register String (*func)(int), register Tag *tag)
{
    register Tag c __asm__("r29") = *tag;
    return fn_8044F1D4(func(fn_8044C1B4(String((const char *)fn_8044AA54(a, 0)))));
}

String fn_8044ED8C(register int a, register String (*func)(int))
{
    register int z __asm__("r0") = 0;
    register unsigned char zero __asm__("r9") = 0;
    Tag tag;
    tag.v = zero;
    return fn_8044ECE4(a, func, &tag);
}

String fn_8044EDEC(register int a, register String (*func)(int))
{
    return fn_8044ED8C(a, func);
}

void *fn_8044EE3C(register void *self, register const char *name, register void *func, register const char *file, register int line)
{
    if (lbl_8066D6FC <= 0x170) {
        lbl_805663A4[lbl_8066D6FC].thunk = (void *)fn_8044EDEC;
        lbl_805663A4[lbl_8066D6FC].func = func;
        lbl_805663A4[lbl_8066D6FC].name = name;
        fn_8044B4EC(file, line);
    }
    lbl_8066D6FC++;
    return self;
}
}
