// Constructor (guessed class Obj107) of an object set through one setter, then a lookup in lbl_8066D954 (docs/versus.md section 5, row 2).

extern "C" void fn_8045D004(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D954[8];
extern char lbl_8066BC88[8];

class Obj107
{
public:
    Obj107(register int a);
};

Obj107::Obj107(register int a)
{
    int r;
    fn_8045D004(this, a);
    r = fn_802465B0(lbl_8066D954, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D954, lbl_8066BC88);
        r = fn_802465B0(lbl_8066D954, (char *)this + 4, this);
    }
}
