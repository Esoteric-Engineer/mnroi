// APT native-registration helpers for handlers taking an int parsed from a String and returning nothing (docs/versus.md section 5, row 2).

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
extern "C" char *fn_8044A4F4(register const String *self);
extern "C" char *fn_8044A554(register const String *self);
extern "C" char fn_80449210(void);
extern "C" int fn_8044D650(int c, int *out);

// Emits no code; a top-level `return <parameter>;` makes cc1plus drop the function-end branch pair (docs/prodg.md).
inline int sn_return_decl(int a) { return a; }

extern "C" {
int fn_8044C054(register const String *self)
{
    int result = 0;
    int sign = 1;
    char *p = fn_8044A4F4(self);
    if (fn_80449210() == *p) {
        p++;
        sign = -1;
    }
    for (; p != fn_8044A554(self); p++) {
        int digit = 0;
        if (fn_8044D650(*p, &digit)) {
            result = result * 10;
            result = result + digit;
        } else {
            return 0;
        }
    }
    return result * sign;
}

int fn_8044C16C(const String &self, register Tag *tag)
{
    return fn_8044C054(&self);
}

int fn_8044C1B4(const String &self)
{
    int *p = 0;
    Tag tag;
    {
        register int z __asm__("r0") = 0;
        register unsigned char zero __asm__("r9") = 0;
        tag.v = zero;
    }
    return fn_8044C16C(self, &tag);
}

String fn_8044C214(register int a, register void (*func)(int), register Tag *tag)
{
    register Tag c __asm__("r29") = *tag;
    func(fn_8044C1B4(String((const char *)fn_8044AA54(a, 0))));
    return String();
}

String fn_8044C2AC(register int a, register void (*func)(int))
{
    register int z __asm__("r0") = 0;
    register unsigned char zero __asm__("r9") = 0;
    Tag tag;
    tag.v = zero;
    return fn_8044C214(a, func, &tag);
}

String fn_8044C30C(register int a, register void (*func)(int))
{
    return fn_8044C2AC(a, func);
}

void *fn_8044C35C(register void *self, register const char *name, register void *func, register const char *file, register int line)
{
    if (lbl_8066D6FC <= 0x170) {
        lbl_805663A4[lbl_8066D6FC].thunk = (void *)fn_8044C30C;
        lbl_805663A4[lbl_8066D6FC].func = func;
        lbl_805663A4[lbl_8066D6FC].name = name;
        fn_8044B4EC(file, line);
    }
    lbl_8066D6FC++;
    return self;
}
}
