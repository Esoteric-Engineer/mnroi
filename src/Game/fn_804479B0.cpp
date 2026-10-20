// Constructor of the object with two 0x40-byte matrices and a vptr at +0x88 (fn_80447434's accessors). Names are guesses.
extern "C" char *fn_80446A74(char *self);
extern "C" char lbl_804F3338[];

class Obj
{
public:
    char mats[0x80]; // +0x0
    int a;           // +0x80
    int b;           // +0x84
    const void *vptr; // +0x88
    Obj();
};

Obj::Obj() : vptr(lbl_804F3338)
{
    fn_80446A74((char *)this);
    fn_80446A74((char *)this + 0x40);
    b = 0;
    a = 0;
}
