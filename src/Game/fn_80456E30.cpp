// Constructor (guessed class Obj115) of the 8-byte handle object: a lookup in lbl_8066D9D4 (docs/versus.md section 5, row 2).

extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D9D4[8];
extern char lbl_8066BCB0[8];

class Obj115
{
public:
    Obj115();
};

Obj115::Obj115()
{
    int r;
    r = fn_802465B0(lbl_8066D9D4, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D9D4, lbl_8066BCB0);
        r = fn_802465B0(lbl_8066D9D4, (char *)this + 4, this);
    }
}
