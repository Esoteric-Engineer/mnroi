// Constructor (guessed class Obj8F) of an object set through three setters, then a lookup in lbl_8066D854 (docs/versus.md section 5, row 2).

extern "C" void fn_8045A524(void *self, int v);
extern "C" void fn_8045A574(void *self, int v);
extern "C" void fn_8045A5B8(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D854[8];
extern char lbl_8066BBA8[8];

class Obj8F
{
public:
    Obj8F(register int a, register int b, register int c);
};

Obj8F::Obj8F(register int a, register int b, register int c)
{
    int r;
    fn_8045A524(this, a);
    fn_8045A574(this, b);
    fn_8045A5B8(this, c);
    r = fn_802465B0(lbl_8066D854, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D854, lbl_8066BBA8);
        r = fn_802465B0(lbl_8066D854, (char *)this + 4, this);
    }
}
