// Constructor (guessed class Obj8M) of an object set through six setters, then a lookup in lbl_8066D884 (docs/versus.md section 5, row 2).

extern "C" void fn_8045AE40(void *self, int v);
extern "C" void fn_8045AE90(void *self, int v);
extern "C" void fn_8045AED8(void *self, int v);
extern "C" void fn_8045AF1C(void *self, int v);
extern "C" void fn_8045AF60(void *self, int v);
extern "C" void fn_8045AFA4(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D884[8];
extern char lbl_8066BBD8[8];

class Obj8M
{
public:
    Obj8M(register int a, register int b, register int c, register int d, register int e, register int f);
};

Obj8M::Obj8M(register int a, register int b, register int c, register int d, register int e, register int f)
{
    int r;
    fn_8045AE40(this, a);
    fn_8045AE90(this, b);
    fn_8045AED8(this, c);
    fn_8045AF1C(this, d);
    fn_8045AF60(this, e);
    fn_8045AFA4(this, f);
    r = fn_802465B0(lbl_8066D884, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D884, lbl_8066BBD8);
        r = fn_802465B0(lbl_8066D884, (char *)this + 4, this);
    }
}
