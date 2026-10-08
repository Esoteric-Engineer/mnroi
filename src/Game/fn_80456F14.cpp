// Constructor (guessed class Obj117) of an 8-byte handle object: a lookup in lbl_8066D9DC (docs/versus.md section 5, row 2).

extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D9DC[8];
extern char lbl_8066BCB8[8];

class Obj117
{
public:
    Obj117();
};

Obj117::Obj117()
{
    int r;
    r = fn_802465B0(lbl_8066D9DC, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D9DC, lbl_8066BCB8);
        r = fn_802465B0(lbl_8066D9DC, (char *)this + 4, this);
    }
}
