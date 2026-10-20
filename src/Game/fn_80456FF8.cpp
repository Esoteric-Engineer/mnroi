// Constructor (guessed class Obj118) of the 8-byte handle object: four setters, then a lookup in lbl_8066D9E4 (docs/versus.md section 5, row 2).

extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern "C" void fn_8045D69C(void *self, int v);
extern "C" void fn_8045D6EC(void *self, int v);
extern "C" void fn_8045D734(void *self, int v);
extern "C" void fn_8045D778(void *self, int v);
extern char lbl_8066D9E4[8];
extern char lbl_8066BCC0[8];

class Obj118
{
public:
    Obj118(register int a, register int b, register int c, register int d);
};

Obj118::Obj118(register int a, register int b, register int c, register int d)
{
    int r;
    fn_8045D69C(this, a);
    fn_8045D6EC(this, b);
    fn_8045D734(this, c);
    fn_8045D778(this, d);
    r = fn_802465B0(lbl_8066D9E4, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D9E4, lbl_8066BCC0);
        r = fn_802465B0(lbl_8066D9E4, (char *)this + 4, this);
    }
}
