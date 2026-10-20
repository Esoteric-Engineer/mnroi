// Constructor (guessed class Obj8Q) of an object set through six setters, then a lookup in lbl_8066D8A4 (docs/versus.md section 5, row 2).

extern "C" void fn_8045B5A8(void *self, int v);
extern "C" void fn_8045B5F8(void *self, int v);
extern "C" void fn_8045B640(void *self, int v);
extern "C" void fn_8045B684(void *self, int v);
extern "C" void fn_8045B6C8(void *self, int v);
extern "C" void fn_8045B70C(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D8A4[8];
extern char lbl_8066BBF8[8];

class Obj8Q
{
public:
    Obj8Q(register int a, register int b, register int c, register int d, register int e, register int f);
};

Obj8Q::Obj8Q(register int a, register int b, register int c, register int d, register int e, register int f)
{
    int r;
    fn_8045B5A8(this, a);
    fn_8045B5F8(this, b);
    fn_8045B640(this, c);
    fn_8045B684(this, d);
    fn_8045B6C8(this, e);
    fn_8045B70C(this, f);
    r = fn_802465B0(lbl_8066D8A4, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D8A4, lbl_8066BBF8);
        r = fn_802465B0(lbl_8066D8A4, (char *)this + 4, this);
    }
}
