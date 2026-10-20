// Constructor (guessed class Obj95) of an object set through five setters, then a lookup in lbl_8066D91C (docs/versus.md section 5, row 2).

extern "C" void fn_8045C7C4(void *self, int v);
extern "C" void fn_8045C814(void *self, int v);
extern "C" void fn_8045C85C(void *self, int v);
extern "C" void fn_8045C8A0(void *self, int v);
extern "C" void fn_8045C8E4(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D91C[8];
extern char lbl_8066BC50[8];

class Obj95
{
public:
    Obj95(register int a, register int b, register int c, register int d, register int e);
};

Obj95::Obj95(register int a, register int b, register int c, register int d, register int e)
{
    int r;
    fn_8045C7C4(this, a);
    fn_8045C814(this, b);
    fn_8045C85C(this, c);
    fn_8045C8A0(this, d);
    fn_8045C8E4(this, e);
    r = fn_802465B0(lbl_8066D91C, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D91C, lbl_8066BC50);
        r = fn_802465B0(lbl_8066D91C, (char *)this + 4, this);
    }
}
