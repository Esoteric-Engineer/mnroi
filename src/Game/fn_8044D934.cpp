// Listener entry (guessed name) registered by fn_8044D84C; EntryBase and its vtable pair are in Game/fn_80433588.cpp. Also the C-string String front and a Listener-list callback.

extern "C" char lbl_804F5798[];

class EntryBase
{
public:
    void *x[3]; // +0x0; the real constructor also stores its own vptr at +0xC
    EntryBase();
};

class Listener : public EntryBase
{
public:
    const void *vptr; // +0xC
    Listener();
};

Listener::Listener() : vptr(lbl_804F5798) {}

extern "C" void fn_80433CF0(register void *self, register int inChrg);

extern "C" void fn_8044D980(register void *self, register int inChrg)
{
    fn_80433CF0(self, 0);
}

extern "C" void fn_80432DF8(void *obj);

extern "C" void fn_8044D9C0(register void **self)
{
    fn_80432DF8(*self);
}

struct Tag
{
};

class String
{
public:
    char data[0x4C];
    String(const char *s);
    ~String();
} __attribute__((aligned(8)));

extern "C" String fn_8044AA94(register const char *s);

extern "C" String fn_8044D9F8(const char *const &s, Tag)
{
    return fn_8044AA94(s);
}

struct TagV
{
    unsigned char v;
};

extern "C" String fn_8044D9F8_v(const char *const &s, const TagV &) __asm__("fn_8044D9F8");

extern "C" String fn_8044DA48(const char *const &s)
{
    int *p = 0;
    {
        register int z __asm__("r0") = 0;
        register unsigned char zero __asm__("r9") = 0;
        TagV tag;
        tag.v = zero;
        return fn_8044D9F8_v(s, tag);
    }
}
