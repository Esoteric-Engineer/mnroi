// Constructor (guessed class Obj8I) of an object set through five setters, then a lookup in lbl_8066D864 (docs/versus.md section 5, row 2).

extern "C" void fn_8045A814(void *self, int v);
extern "C" void fn_8045A864(void *self, int v);
extern "C" void fn_8045A8AC(void *self, int v);
extern "C" void fn_8045A8F0(void *self, int v);
extern "C" void fn_8045A934(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D864[8];
extern char lbl_8066BBB8[8];

class Obj8I
{
public:
    Obj8I(register int a, register int b, register int c, register int d, register int e);
};

Obj8I::Obj8I(register int a, register int b, register int c, register int d, register int e)
{
    int r;
    fn_8045A814(this, a);
    fn_8045A864(this, b);
    fn_8045A8AC(this, c);
    fn_8045A8F0(this, d);
    fn_8045A934(this, e);
    r = fn_802465B0(lbl_8066D864, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D864, lbl_8066BBB8);
        r = fn_802465B0(lbl_8066D864, (char *)this + 4, this);
    }
}
