// Constructor (guessed class Obj8B) of an object set through eight setters, then a lookup in lbl_8066D834 (docs/versus.md section 5, row 2).

extern "C" void fn_80459E74(void *self, int v);
extern "C" void fn_80459EC4(void *self, int v);
extern "C" void fn_80459F0C(void *self, int v);
extern "C" void fn_80459F50(void *self, int v);
extern "C" void fn_80459F94(void *self, int v);
extern "C" void fn_80459FD8(void *self, int v);
extern "C" void fn_8045A01C(void *self, int v);
extern "C" void fn_8045A060(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D834[8];
extern char lbl_8066BB88[8];

class Obj8B
{
public:
    Obj8B(register int a, register int b, register int c, register int d, register int e, register int f, register int g, register int h);
};

Obj8B::Obj8B(register int a, register int b, register int c, register int d, register int e, register int f, register int g, register int h)
{
    int r;
    fn_80459E74(this, a);
    fn_80459EC4(this, b);
    fn_80459F0C(this, c);
    fn_80459F50(this, d);
    fn_80459F94(this, e);
    fn_80459FD8(this, f);
    fn_8045A01C(this, g);
    fn_8045A060(this, h);
    r = fn_802465B0(lbl_8066D834, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D834, lbl_8066BB88);
        r = fn_802465B0(lbl_8066D834, (char *)this + 4, this);
    }
}
