// Constructor (guessed class Obj8K) of an object set through four setters, then a lookup in lbl_8066D874 (docs/versus.md section 5, row 2).

extern "C" void fn_8045AB4C(void *self, int v);
extern "C" void fn_8045AB9C(void *self, int v);
extern "C" void fn_8045ABE4(void *self, int v);
extern "C" void fn_8045AC28(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D874[8];
extern char lbl_8066BBC8[8];

class Obj8K
{
public:
    Obj8K(register int a, register int b, register int c, register int d);
};

Obj8K::Obj8K(register int a, register int b, register int c, register int d)
{
    int r;
    fn_8045AB4C(this, a);
    fn_8045AB9C(this, b);
    fn_8045ABE4(this, c);
    fn_8045AC28(this, d);
    r = fn_802465B0(lbl_8066D874, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D874, lbl_8066BBC8);
        r = fn_802465B0(lbl_8066D874, (char *)this + 4, this);
    }
}
