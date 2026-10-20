// Constructor (guessed class Obj103) of an object set through one setter, then a lookup in lbl_8066D944 (docs/versus.md section 5, row 2).

extern "C" void fn_8045CF0C(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D944[8];
extern char lbl_8066BC78[8];

class Obj103
{
public:
    Obj103(register int a);
};

Obj103::Obj103(register int a)
{
    int r;
    fn_8045CF0C(this, a);
    r = fn_802465B0(lbl_8066D944, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D944, lbl_8066BC78);
        r = fn_802465B0(lbl_8066D944, (char *)this + 4, this);
    }
}
