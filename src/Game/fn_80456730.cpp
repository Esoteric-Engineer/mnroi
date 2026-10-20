// Constructor (guessed class Obj101) of an object set through one setter, then a lookup in lbl_8066D93C (docs/versus.md section 5, row 2).

extern "C" void fn_8045CE90(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D93C[8];
extern char lbl_8066BC70[8];

class Obj101
{
public:
    Obj101(register int a);
};

Obj101::Obj101(register int a)
{
    int r;
    fn_8045CE90(this, a);
    r = fn_802465B0(lbl_8066D93C, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D93C, lbl_8066BC70);
        r = fn_802465B0(lbl_8066D93C, (char *)this + 4, this);
    }
}
