// Constructor (guessed class Obj8W) of an object set through four setters, then a lookup in lbl_8066D8D4 (docs/versus.md section 5, row 2).

extern "C" void fn_8045BDFC(void *self, int v);
extern "C" void fn_8045BE4C(void *self, int v);
extern "C" void fn_8045BE90(void *self, int v);
extern "C" void fn_8045BED4(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D8D4[8];
extern char lbl_8066BC20[8];

class Obj8W
{
public:
    Obj8W(register int a, register int b, register int c, register int d);
};

Obj8W::Obj8W(register int a, register int b, register int c, register int d)
{
    int r;
    fn_8045BDFC(this, a);
    fn_8045BE4C(this, b);
    fn_8045BE90(this, c);
    fn_8045BED4(this, d);
    r = fn_802465B0(lbl_8066D8D4, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D8D4, lbl_8066BC20);
        r = fn_802465B0(lbl_8066D8D4, (char *)this + 4, this);
    }
}
