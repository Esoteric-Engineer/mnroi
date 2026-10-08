// Constructor (guessed class Obj8) of the 8-byte object the handler at 0x8010D220 allocates: lookup in lbl_8066D82C (docs/versus.md section 5, row 2).

extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D82C[8];
extern char lbl_8066BB80[8];

class Obj8
{
public:
    Obj8();
};

Obj8::Obj8()
{
    int h;
    h = fn_802465B0(lbl_8066D82C, (char *)this + 4, this);
    if (h < 0) {
        fn_80245CBC(lbl_8066D82C, lbl_8066BB80);
        h = fn_802465B0(lbl_8066D82C, (char *)this + 4, this);
    }
}
