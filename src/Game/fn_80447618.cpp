// Derived constructor: base (fn_804479B0), own vptr, member at +0x90. Names are guesses.
extern "C" char *fn_80434DB4(char *self);
extern "C" char lbl_804F32A8[];

class Obj
{
public:
    char mats[0x80]; // +0x0
    int a;           // +0x80
    int b;           // +0x84
    const void *vptr; // +0x88
    Obj();
};

class ObjEx : public Obj
{
public:
    char pad[4];
    char sub[8]; // +0x90
    ObjEx();
};

ObjEx::ObjEx()
{
    vptr = lbl_804F32A8;
    fn_80434DB4((char *)this + 0x90);
}
