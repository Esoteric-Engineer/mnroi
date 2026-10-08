// Constructor (guessed class Obj108) of an object set through one setter, then a lookup in lbl_8066D95C (docs/versus.md section 5, row 2).

extern "C" void fn_8045D080(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D95C[8];
extern char lbl_8066BC90[8];

class Obj108
{
public:
    Obj108(register int a);
};

Obj108::Obj108(register int a)
{
    int r;
    fn_8045D080(this, a);
    r = fn_802465B0(lbl_8066D95C, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D95C, lbl_8066BC90);
        r = fn_802465B0(lbl_8066D95C, (char *)this + 4, this);
    }
}
