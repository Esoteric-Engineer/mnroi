// APT native-registration helpers for handlers returning AptObject or String: a call thunk, its forwarder, and the constructor that appends {name, thunk, handler} to the table at lbl_805663A4 (docs/versus.md section 5, row 2).

class AptObject {
public:
    AptObject(const AptObject &other); // fn_8044B568
    AptObject clone(void); // fn_8044B64C, guessed name
    ~AptObject();                // fn_8044B510
    void *unk0;
    int unk4;
};

class String {
public:
    String();  // 0x804498C8
    ~String(); // 0x80449298
    char data[0x4C];
} __attribute__((aligned(8)));

struct Tag { // one-byte dispatch tag; the thunks copy it into r28 and ignore it
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

// Emits no code. A top-level `return <parameter>;` makes cc1plus drop the function-end branch pair for every later function in the unit.
inline int sn_return_decl(int a) { return a; }

extern "C" {
AptObject fn_8044AE3C(register int a, register AptObject (*func)(void), register Tag *tag)
{
    register Tag c __asm__("r28") = *tag;
    AptObject tmp = func();
    return tmp.clone();
}

AptObject fn_8044AEA8(register int a, register AptObject (*func)(void))
{
    register int z __asm__("r0") = 0;
    register unsigned char zero __asm__("r9") = 0;
    Tag tag;
    tag.v = zero;
    return fn_8044AE3C(a, func, &tag);
}

AptObject fn_8044AF08(register int a, register AptObject (*func)(void))
{
    return fn_8044AEA8(a, func);
}

void *fn_8044AF58(register void *self, register const char *name, register void *func, register const char *file, register int line)
{
    if (lbl_8066D6FC <= 0x170) {
        lbl_805663A4[lbl_8066D6FC].thunk = (void *)fn_8044AF08;
        lbl_805663A4[lbl_8066D6FC].func = func;
        lbl_805663A4[lbl_8066D6FC].name = name;
        fn_8044B4EC(file, line);
    }
    lbl_8066D6FC++;
    return self;
}

String fn_8044B010(register int a, register void (*func)(void), register Tag *tag)
{
    register Tag c __asm__("r28") = *tag;
    func();
    return String();
}

String fn_8044B06C(register int a, register void (*func)(void))
{
    register int z __asm__("r0") = 0;
    register unsigned char zero __asm__("r9") = 0;
    Tag tag;
    tag.v = zero;
    return fn_8044B010(a, func, &tag);
}

String fn_8044B0CC(register int a, register void (*func)(void))
{
    return fn_8044B06C(a, func);
}

void *fn_8044B11C(register void *self, register const char *name, register void *func, register const char *file, register int line)
{
    if (lbl_8066D6FC <= 0x170) {
        lbl_805663A4[lbl_8066D6FC].thunk = (void *)fn_8044B0CC;
        lbl_805663A4[lbl_8066D6FC].func = func;
        lbl_805663A4[lbl_8066D6FC].name = name;
        fn_8044B4EC(file, line);
    }
    lbl_8066D6FC++;
    return self;
}
}
