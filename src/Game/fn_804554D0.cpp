// Constructor (guessed class Obj8N) of an object set through seven setters, then a lookup in lbl_8066D88C (docs/versus.md section 5, row 2).

extern "C" void fn_8045B020(void *self, int v);
extern "C" void fn_8045B070(void *self, int v);
extern "C" void fn_8045B0B8(void *self, int v);
extern "C" void fn_8045B0FC(void *self, int v);
extern "C" void fn_8045B140(void *self, int v);
extern "C" void fn_8045B184(void *self, int v);
extern "C" void fn_8045B1C8(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D88C[8];
extern char lbl_8066BBE0[8];

class Obj8N
{
public:
    Obj8N(register int a, register int b, register int c, register int d, register int e, register int f, register int g);
};

Obj8N::Obj8N(register int a, register int b, register int c, register int d, register int e, register int f, register int g)
{
    int r;
    fn_8045B020(this, a);
    fn_8045B070(this, b);
    fn_8045B0B8(this, c);
    fn_8045B0FC(this, d);
    fn_8045B140(this, e);
    fn_8045B184(this, f);
    fn_8045B1C8(this, g);
    r = fn_802465B0(lbl_8066D88C, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D88C, lbl_8066BBE0);
        r = fn_802465B0(lbl_8066D88C, (char *)this + 4, this);
    }
}
