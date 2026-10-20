// Constructor (guessed class Obj8E) of an object set through three setters, then a lookup in lbl_8066D84C (docs/versus.md section 5, row 2).

extern "C" void fn_8045A414(void *self, int v);
extern "C" void fn_8045A464(void *self, int v);
extern "C" void fn_8045A4A8(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D84C[8];
extern char lbl_8066BBA0[8];

class Obj8E
{
public:
    Obj8E(register int a, register int b, register int c);
};

Obj8E::Obj8E(register int a, register int b, register int c)
{
    int r;
    fn_8045A414(this, a);
    fn_8045A464(this, b);
    fn_8045A4A8(this, c);
    r = fn_802465B0(lbl_8066D84C, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D84C, lbl_8066BBA0);
        r = fn_802465B0(lbl_8066D84C, (char *)this + 4, this);
    }
}
