// Constructor (guessed class Obj8L) of an object set through five setters, then a lookup in lbl_8066D87C (docs/versus.md section 5, row 2).

extern "C" void fn_8045ACA4(void *self, int v);
extern "C" void fn_8045ACF4(void *self, int v);
extern "C" void fn_8045AD3C(void *self, int v);
extern "C" void fn_8045AD80(void *self, int v);
extern "C" void fn_8045ADC4(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D87C[8];
extern char lbl_8066BBD0[8];

class Obj8L
{
public:
    Obj8L(register int a, register int b, register int c, register int d, register int e);
};

Obj8L::Obj8L(register int a, register int b, register int c, register int d, register int e)
{
    int r;
    fn_8045ACA4(this, a);
    fn_8045ACF4(this, b);
    fn_8045AD3C(this, c);
    fn_8045AD80(this, d);
    fn_8045ADC4(this, e);
    r = fn_802465B0(lbl_8066D87C, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D87C, lbl_8066BBD0);
        r = fn_802465B0(lbl_8066D87C, (char *)this + 4, this);
    }
}
