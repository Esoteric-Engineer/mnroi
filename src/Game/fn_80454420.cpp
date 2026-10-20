// Levels constructor (guessed name): three 0-100 values at +0x4..+0xC, then a lookup in lbl_8066D81C (docs/versus.md section 5, row 2).

extern "C" void fn_80459CBC(void *self, int v);
extern "C" void fn_80459D00(void *self, int v);
extern "C" void fn_80459D44(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D81C[8];
extern char lbl_8066BB70[8];

class Levels
{
public:
    Levels(register int a, register int b, register int c);
};

Levels::Levels(register int a, register int b, register int c)
{
    int h;
    fn_80459CBC(this, a);
    fn_80459D00(this, b);
    fn_80459D44(this, c);
    h = fn_802465B0(lbl_8066D81C, (char *)this + 4, this);
    if (h < 0) {
        fn_80245CBC(lbl_8066D81C, lbl_8066BB70);
        h = fn_802465B0(lbl_8066D81C, (char *)this + 4, this);
    }
}
