// Constructor (guessed class Obj98) of an object set through four setters, then a lookup in lbl_8066D92C (docs/versus.md section 5, row 2).

extern "C" void fn_8045CB5C(void *self, int v);
extern "C" void fn_8045CBAC(void *self, int v);
extern "C" void fn_8045CBF4(void *self, int v);
extern "C" void fn_8045CC38(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D92C[8];
extern char lbl_8066BC60[8];

class Obj98
{
public:
    Obj98(register int a, register int b, register int c, register int d);
};

Obj98::Obj98(register int a, register int b, register int c, register int d)
{
    int r;
    fn_8045CB5C(this, a);
    fn_8045CBAC(this, b);
    fn_8045CBF4(this, c);
    fn_8045CC38(this, d);
    r = fn_802465B0(lbl_8066D92C, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D92C, lbl_8066BC60);
        r = fn_802465B0(lbl_8066D92C, (char *)this + 4, this);
    }
}
