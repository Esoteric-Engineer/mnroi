// Implementation behind HandleF: base constructor, vptr, key, lookup (as ImplD/ImplE in fn_8045E6AC.cpp). Class names are guesses.
extern "C" void *fn_8042A400(void *self, void *owner, int key);
extern char lbl_804F58D0[];

class BaseF
{
public:
    int x; // +0x0; the base constructor also stores its own vptr at +0x4
    BaseF();
};

class ImplF : public BaseF
{
public:
    const void *vptr; // +0x4
    int name;         // +0x8; callback
    void *result;     // +0xC
    ImplF(register const void *name);
};

ImplF::ImplF(register const void *name)
    : vptr(lbl_804F58D0), name(*(const int *)name), result(fn_8042A400(this, 0, *(const int *)name))
{
}
