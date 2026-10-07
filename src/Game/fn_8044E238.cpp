// APT native-registration helpers for handlers taking six ints parsed from Strings and returning nothing (docs/versus.md section 5, row 2).

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

// Emits no code; a top-level `return <parameter>;` makes cc1plus drop the function-end branch pair (docs/prodg.md).
inline int sn_return_decl(int a) { return a; }

extern "C" {
String fn_8044E238(register int a, register void (*func)(int, int, int, int, int, int), register Tag *tag)
{
    register Tag c __asm__("r29") = *tag;
    func(fn_8044C1B4(String((const char *)fn_8044AA54(a, 0))),
         fn_8044C1B4(String((const char *)fn_8044AA54(a, 1))),
         fn_8044C1B4(String((const char *)fn_8044AA54(a, 2))),
         fn_8044C1B4(String((const char *)fn_8044AA54(a, 3))),
         fn_8044C1B4(String((const char *)fn_8044AA54(a, 4))),
         fn_8044C1B4(String((const char *)fn_8044AA54(a, 5))));
    return String();
}

String fn_8044E438(register int a, register void (*func)(int, int, int, int, int, int))
{
    register int z __asm__("r0") = 0;
    register unsigned char zero __asm__("r9") = 0;
    Tag tag;
    tag.v = zero;
    return fn_8044E238(a, func, &tag);
}

String fn_8044E498(register int a, register void (*func)(int, int, int, int, int, int))
{
    return fn_8044E438(a, func);
}

void *fn_8044E4E8(register void *self, register const char *name, register void *func, register const char *file, register int line)
{
    if (lbl_8066D6FC <= 0x170) {
        lbl_805663A4[lbl_8066D6FC].thunk = (void *)fn_8044E498;
        lbl_805663A4[lbl_8066D6FC].func = func;
        lbl_805663A4[lbl_8066D6FC].name = name;
        fn_8044B4EC(file, line);
    }
    lbl_8066D6FC++;
    return self;
}
}
