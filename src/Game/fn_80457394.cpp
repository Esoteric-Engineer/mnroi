// Constructor (guessed class Obj123) of a 0x14-byte handle object: loads a resource and creates a handle over it (docs/versus.md section 5, row 2).

extern "C" void fn_8024CD34(void *p);
extern "C" int fn_80119398(void *table, int size, void *attr);
extern "C" int fn_8024E400(void *p, int a, int b, int c, int d);
extern char lbl_804974C0[];
extern char lbl_80568DF0[0x10];

class Attr
{
public:
    int a;                    // +0x0
    const void *b;            // +0x4
    mutable const Attr *link; // +0x8
    Attr(register int a, register const char *b);
};

class Obj123
{
public:
    int res;  // +0x0
    int h;    // +0x4
    int w8;   // +0x8
    int wC;   // +0xC
    int w10;  // +0x10
    Obj123();
};

Obj123::Obj123()
{
    char buf[0x18];
    w8 = 0;
    wC = 0x1000;
    fn_8024CD34(buf);
    Attr attr(1, lbl_804974C0);
    res = fn_80119398(lbl_80568DF0, 0x30000, &attr);
    h = fn_8024E400(buf, 10, 150, res, 0x30000);
}
