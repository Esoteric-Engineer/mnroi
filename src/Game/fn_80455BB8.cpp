// Constructor (guessed class Obj8U) of an object set through three setters, then a lookup in lbl_8066D8CC (docs/versus.md section 5, row 2).

extern "C" void fn_8045BCEC(void *self, int v);
extern "C" void fn_8045BD3C(void *self, int v);
extern "C" void fn_8045BD80(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D8CC[8];
extern char lbl_8066BC18[8];

class Obj8U
{
public:
    Obj8U(register int a, register int b, register int c);
};

Obj8U::Obj8U(register int a, register int b, register int c)
{
    int r;
    fn_8045BCEC(this, a);
    fn_8045BD3C(this, b);
    fn_8045BD80(this, c);
    r = fn_802465B0(lbl_8066D8CC, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D8CC, lbl_8066BC18);
        r = fn_802465B0(lbl_8066D8CC, (char *)this + 4, this);
    }
}
