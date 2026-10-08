// Constructor (guessed class Obj120) of an 8-byte handle object: a lookup in lbl_8066D9EC (docs/versus.md section 5, row 2).

extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D9EC[8];
extern char lbl_8066BCC8[8];

class Obj120
{
public:
    Obj120();
};

Obj120::Obj120()
{
    int r;
    r = fn_802465B0(lbl_8066D9EC, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D9EC, lbl_8066BCC8);
        r = fn_802465B0(lbl_8066D9EC, (char *)this + 4, this);
    }
}
