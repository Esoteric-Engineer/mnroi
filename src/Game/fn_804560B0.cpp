// Constructor (guessed class Obj92) of an object set through four setters, then a lookup in lbl_8066D8F4 (docs/versus.md section 5, row 2).

extern "C" void fn_8045C4D4(void *self, int v);
extern "C" void fn_8045C524(void *self, int v);
extern "C" void fn_8045C568(void *self, int v);
extern "C" void fn_8045C5AC(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D8F4[8];
extern char lbl_8066BC40[8];

class Obj92
{
public:
    Obj92(register int a, register int b, register int c, register int d);
};

Obj92::Obj92(register int a, register int b, register int c, register int d)
{
    int r;
    fn_8045C4D4(this, a);
    fn_8045C524(this, b);
    fn_8045C568(this, c);
    fn_8045C5AC(this, d);
    r = fn_802465B0(lbl_8066D8F4, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D8F4, lbl_8066BC40);
        r = fn_802465B0(lbl_8066D8F4, (char *)this + 4, this);
    }
}
