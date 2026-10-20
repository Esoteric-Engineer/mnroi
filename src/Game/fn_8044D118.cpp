// APT native-registration helpers for handlers taking an int parsed from a String and returning an int, converted to a String (docs/versus.md section 5, row 2).

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
extern "C" int fn_8044C1B4(const String &s);
extern "C" String fn_8044BA70(const int &value);

// Emits no code; a top-level `return <parameter>;` makes cc1plus drop the function-end branch pair (docs/prodg.md).
inline int sn_return_decl(int a) { return a; }

extern "C" {
String fn_8044D118(register int a, register int (*func)(int), register Tag *tag)
{
    register Tag c __asm__("r29") = *tag;
    return fn_8044BA70(func(fn_8044C1B4(String((const char *)fn_8044AA54(a, 0)))));
}

String fn_8044D1C0(register int a, register int (*func)(int))
{
    register int z __asm__("r0") = 0;
    register unsigned char zero __asm__("r9") = 0;
    Tag tag;
    tag.v = zero;
    return fn_8044D118(a, func, &tag);
}

String fn_8044D220(register int a, register int (*func)(int))
{
    return fn_8044D1C0(a, func);
}

void *fn_8044D270(register void *self, register const char *name, register void *func, register const char *file, register int line)
{
    if (lbl_8066D6FC <= 0x170) {
        lbl_805663A4[lbl_8066D6FC].thunk = (void *)fn_8044D220;
        lbl_805663A4[lbl_8066D6FC].func = func;
        lbl_805663A4[lbl_8066D6FC].name = name;
        fn_8044B4EC(file, line);
    }
    lbl_8066D6FC++;
    return self;
}
}
