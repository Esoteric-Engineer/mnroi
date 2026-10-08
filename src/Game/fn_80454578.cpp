// Level constructor (guessed name): one 0-10 value at +0x4, then a lookup in lbl_8066D824 (docs/versus.md section 5, row 2).

extern "C" void fn_80459DC0(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D824[8];
extern char lbl_8066BB78[8];

class Level
{
public:
    Level(register int a);
};

Level::Level(register int a)
{
    int h;
    fn_80459DC0(this, a);
    h = fn_802465B0(lbl_8066D824, (char *)this + 4, this);
    if (h < 0) {
        fn_80245CBC(lbl_8066D824, lbl_8066BB78);
        h = fn_802465B0(lbl_8066D824, (char *)this + 4, this);
    }
}
