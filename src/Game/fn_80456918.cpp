// Constructor (guessed class Obj105) of an object set through one setter, then a lookup in lbl_8066D94C (docs/versus.md section 5, row 2).

extern "C" void fn_8045CF88(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D94C[8];
extern char lbl_8066BC80[8];

class Obj105
{
public:
    Obj105(register int a);
};

Obj105::Obj105(register int a)
{
    int r;
    fn_8045CF88(this, a);
    r = fn_802465B0(lbl_8066D94C, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D94C, lbl_8066BC80);
        r = fn_802465B0(lbl_8066D94C, (char *)this + 4, this);
    }
}
