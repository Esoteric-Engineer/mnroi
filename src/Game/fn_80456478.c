// Setter on a handle object: clamps the value to 0-3 into +0x18 (docs/versus.md section 5, row 2).
typedef struct Obj
{
    char unk0[0x18];
    int unk18;
} Obj;

void fn_80456478(register Obj *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 3) {
        v = 3;
    }
    self->unk18 = v;
}
