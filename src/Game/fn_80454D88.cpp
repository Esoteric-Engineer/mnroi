// Constructor (guessed class Obj8H) of an object set through six setters, then a lookup in lbl_8066D85C (docs/versus.md section 5, row 2).

extern "C" void fn_8045A634(void *self, int v);
extern "C" void fn_8045A684(void *self, int v);
extern "C" void fn_8045A6CC(void *self, int v);
extern "C" void fn_8045A710(void *self, int v);
extern "C" void fn_8045A754(void *self, int v);
extern "C" void fn_8045A798(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D85C[8];
extern char lbl_8066BBB0[8];

class Obj8H
{
public:
    Obj8H(register int a, register int b, register int c, register int d, register int e, register int f);
};

Obj8H::Obj8H(register int a, register int b, register int c, register int d, register int e, register int f)
{
    int r;
    fn_8045A634(this, a);
    fn_8045A684(this, b);
    fn_8045A6CC(this, c);
    fn_8045A710(this, d);
    fn_8045A754(this, e);
    fn_8045A798(this, f);
    r = fn_802465B0(lbl_8066D85C, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D85C, lbl_8066BBB0);
        r = fn_802465B0(lbl_8066D85C, (char *)this + 4, this);
    }
}
