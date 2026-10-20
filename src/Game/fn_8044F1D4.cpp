// APT registrar helpers for handlers taking an int (docs/versus.md section 5, row 2): the by-value String converter and AptRef int setters, then the int-to-String front.

class String {
public:
    String(const char *s);
    String(const String &other);
    String();
    ~String();
    char data[0x4C];
} __attribute__((aligned(8)));

struct Tag {
};

struct TagV {
    unsigned char v;
};

struct AptRef {
    void *object; // +0x0
    char *name;   // +0x4
    int index;    // +0x8
};

extern "C" void fn_804494AC(String *self);
extern "C" void *fn_8044B8B0(void *object);
extern "C" int fn_80102F10(void *object, char *name);
extern "C" int fn_8010329C(void *object, char *name);
extern "C" void fn_80102FD0(void *object, int slot, int index);
extern "C" void fn_8044DB94(void *self, const char *b, int c);
extern "C" void fn_8044DC04(void *self, int a, const char *b, int c);
String IntToString(int v);

// Emits no code; a top-level `return <parameter>;` makes cc1plus drop the function-end branch pair (docs/prodg.md).
inline int sn_return_decl(int a) { return a; }

extern "C" {
String fn_8044F1D4(String s)
{
    fn_804494AC(&s);
    return s;
}

void fn_8044F238(register AptRef *self, register int value)
{
    if (self->index < 0) {
        fn_8044DB94(fn_8044B8B0(self->object), self->name, value);
    } else {
        int slot = fn_80102F10(self->object, self->name);
        if (slot < 0) {
            slot = fn_8010329C(self->object, self->name);
        }
        fn_8044DC04(fn_8044B8B0(self->object), self->index, self->name, value);
        fn_80102FD0(self->object, slot, self->index);
    }
}

void fn_8044F2FC(register AptRef *self, register int value)
{
    if (self->index < 0) {
        fn_8044DB94(fn_8044B8B0(self->object), self->name, value);
    } else {
        int slot = fn_80102F10(self->object, self->name);
        if (slot < 0) {
            slot = fn_8010329C(self->object, self->name);
        }
        fn_8044DC04(fn_8044B8B0(self->object), self->index, self->name, value);
        fn_80102FD0(self->object, slot, self->index);
    }
}

String fn_8044F3C0(register int v)
{
    return IntToString(v);
}

String fn_8044F408(const int &p, Tag)
{
    return fn_8044F3C0(p);
}

}

extern "C" String fn_8044F408_v(const int &p, const TagV &) __asm__("fn_8044F408");

extern "C" String fn_8044F458(const int &p)
{
    int *q = 0;
    {
        register int z __asm__("r0") = 0;
        register unsigned char zero __asm__("r9") = 0;
        TagV tag;
        tag.v = zero;
        return fn_8044F408_v(p, tag);
    }
}
