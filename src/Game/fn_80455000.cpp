// Constructor (guessed class Obj8J) of an object set through five setters, then a lookup in lbl_8066D86C (docs/versus.md section 5, row 2).

extern "C" void fn_8045A9B0(void *self, int v);
extern "C" void fn_8045AA00(void *self, int v);
extern "C" void fn_8045AA48(void *self, int v);
extern "C" void fn_8045AA8C(void *self, int v);
extern "C" void fn_8045AAD0(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D86C[8];
extern char lbl_8066BBC0[8];

class Obj8J
{
public:
    Obj8J(register int a, register int b, register int c, register int d, register int e);
};

Obj8J::Obj8J(register int a, register int b, register int c, register int d, register int e)
{
    int r;
    fn_8045A9B0(this, a);
    fn_8045AA00(this, b);
    fn_8045AA48(this, c);
    fn_8045AA8C(this, d);
    fn_8045AAD0(this, e);
    r = fn_802465B0(lbl_8066D86C, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D86C, lbl_8066BBC0);
        r = fn_802465B0(lbl_8066D86C, (char *)this + 4, this);
    }
}
