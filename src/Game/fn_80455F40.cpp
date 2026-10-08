// Constructor (guessed class Obj90) of an object set through four setters, then a lookup in lbl_8066D8EC (docs/versus.md section 5, row 2).

extern "C" void fn_8045C33C(void *self, int v);
extern "C" void fn_8045C38C(void *self, int v);
extern "C" void fn_8045C3D0(void *self, int v);
extern "C" void fn_8045C414(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D8EC[8];
extern char lbl_8066BC38[8];

class Obj90
{
public:
    Obj90(register int a, register int b, register int c, register int d);
};

Obj90::Obj90(register int a, register int b, register int c, register int d)
{
    int r;
    fn_8045C33C(this, a);
    fn_8045C38C(this, b);
    fn_8045C3D0(this, c);
    fn_8045C414(this, d);
    r = fn_802465B0(lbl_8066D8EC, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D8EC, lbl_8066BC38);
        r = fn_802465B0(lbl_8066D8EC, (char *)this + 4, this);
    }
}
