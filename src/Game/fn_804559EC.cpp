// Constructor (guessed class Obj8S) of an object set through four setters, then a lookup in lbl_8066D8B4 (docs/versus.md section 5, row 2).

extern "C" void fn_8045B964(void *self, int v);
extern "C" void fn_8045B9B4(void *self, int v);
extern "C" void fn_8045B9FC(void *self, int v);
extern "C" void fn_8045BA40(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D8B4[8];
extern char lbl_8066BC08[8];

class Obj8S
{
public:
    Obj8S(register int a, register int b, register int c, register int d);
};

Obj8S::Obj8S(register int a, register int b, register int c, register int d)
{
    int r;
    fn_8045B964(this, a);
    fn_8045B9B4(this, b);
    fn_8045B9FC(this, c);
    fn_8045BA40(this, d);
    r = fn_802465B0(lbl_8066D8B4, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D8B4, lbl_8066BC08);
        r = fn_802465B0(lbl_8066D8B4, (char *)this + 4, this);
    }
}
