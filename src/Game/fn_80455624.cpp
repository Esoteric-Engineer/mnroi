// Constructor (guessed class Obj8O) of an object set through five setters, then a lookup in lbl_8066D894 (docs/versus.md section 5, row 2).

extern "C" void fn_8045B244(void *self, int v);
extern "C" void fn_8045B294(void *self, int v);
extern "C" void fn_8045B2DC(void *self, int v);
extern "C" void fn_8045B320(void *self, int v);
extern "C" void fn_8045B364(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D894[8];
extern char lbl_8066BBE8[8];

class Obj8O
{
public:
    Obj8O(register int a, register int b, register int c, register int d, register int e);
};

Obj8O::Obj8O(register int a, register int b, register int c, register int d, register int e)
{
    int r;
    fn_8045B244(this, a);
    fn_8045B294(this, b);
    fn_8045B2DC(this, c);
    fn_8045B320(this, d);
    fn_8045B364(this, e);
    r = fn_802465B0(lbl_8066D894, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D894, lbl_8066BBE8);
        r = fn_802465B0(lbl_8066D894, (char *)this + 4, this);
    }
}
