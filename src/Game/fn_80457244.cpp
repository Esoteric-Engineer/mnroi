// Constructor (guessed class Obj122) of an 8-byte handle object: four setters, then a lookup in lbl_8066D9F4 (docs/versus.md section 5, row 2).

extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern "C" void fn_8045D82C(void *self, int v);
extern "C" void fn_8045D87C(void *self, int v);
extern "C" void fn_8045D8C4(void *self, int v);
extern "C" void fn_8045D908(void *self, int v);
extern char lbl_8066D9F4[8];
extern char lbl_8066BCD0[8];

class Obj122
{
public:
    Obj122(register int a, register int b, register int c, register int d);
};

Obj122::Obj122(register int a, register int b, register int c, register int d)
{
    int r;
    fn_8045D82C(this, a);
    fn_8045D87C(this, b);
    fn_8045D8C4(this, c);
    fn_8045D908(this, d);
    r = fn_802465B0(lbl_8066D9F4, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D9F4, lbl_8066BCD0);
        r = fn_802465B0(lbl_8066D9F4, (char *)this + 4, this);
    }
}
