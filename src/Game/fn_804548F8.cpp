// Constructor (guessed class Obj8C) of an object set through four setters, then a lookup in lbl_8066D83C (docs/versus.md section 5, row 2).

extern "C" void fn_8045A0DC(void *self, int v);
extern "C" void fn_8045A12C(void *self, int v);
extern "C" void fn_8045A174(void *self, int v);
extern "C" void fn_8045A1B8(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D83C[8];
extern char lbl_8066BB90[8];

class Obj8C
{
public:
    Obj8C(register int a, register int b, register int c, register int d);
};

Obj8C::Obj8C(register int a, register int b, register int c, register int d)
{
    int r;
    fn_8045A0DC(this, a);
    fn_8045A12C(this, b);
    fn_8045A174(this, c);
    fn_8045A1B8(this, d);
    r = fn_802465B0(lbl_8066D83C, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D83C, lbl_8066BB90);
        r = fn_802465B0(lbl_8066D83C, (char *)this + 4, this);
    }
}
