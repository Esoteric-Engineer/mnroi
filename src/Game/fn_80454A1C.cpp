// Constructor (guessed class Obj8D) of an object set through six setters, then a lookup in lbl_8066D844 (docs/versus.md section 5, row 2).

extern "C" void fn_8045A234(void *self, int v);
extern "C" void fn_8045A284(void *self, int v);
extern "C" void fn_8045A2CC(void *self, int v);
extern "C" void fn_8045A310(void *self, int v);
extern "C" void fn_8045A354(void *self, int v);
extern "C" void fn_8045A398(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D844[8];
extern char lbl_8066BB98[8];

class Obj8D
{
public:
    Obj8D(register int a, register int b, register int c, register int d, register int e, register int f);
};

Obj8D::Obj8D(register int a, register int b, register int c, register int d, register int e, register int f)
{
    int r;
    fn_8045A234(this, a);
    fn_8045A284(this, b);
    fn_8045A2CC(this, c);
    fn_8045A310(this, d);
    fn_8045A354(this, e);
    fn_8045A398(this, f);
    r = fn_802465B0(lbl_8066D844, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D844, lbl_8066BB98);
        r = fn_802465B0(lbl_8066D844, (char *)this + 4, this);
    }
}
