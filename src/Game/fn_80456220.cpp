// Constructor (guessed class Obj93) of an object set through four setters, then a lookup in lbl_8066D90C (docs/versus.md section 5, row 2).

extern "C" void fn_8045C66C(void *self, int v);
extern "C" void fn_8045C6BC(void *self, int v);
extern "C" void fn_8045C704(void *self, int v);
extern "C" void fn_8045C748(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D90C[8];
extern char lbl_8066BC48[8];

class Obj93
{
public:
    Obj93(register int a, register int b, register int c, register int d);
};

Obj93::Obj93(register int a, register int b, register int c, register int d)
{
    int r;
    fn_8045C66C(this, a);
    fn_8045C6BC(this, b);
    fn_8045C704(this, c);
    fn_8045C748(this, d);
    r = fn_802465B0(lbl_8066D90C, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D90C, lbl_8066BC48);
        r = fn_802465B0(lbl_8066D90C, (char *)this + 4, this);
    }
}
