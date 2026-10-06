// Builds the shape pair and placement for a body from its actor and hands them to a handle object (class names guessed; docs/versus.md, row 8).

inline int sn_return_decl(int a)
{
    return a;
}

struct Obj
{
    int get8() __asm__("fn_80436728");
};
struct Sub : Obj
{
    int pad;
};
extern "C" Sub *fn_8032A228(void *actor);
extern "C" void *fn_80437378(void *body);
extern "C" void *fn_804370E8(void *self);
extern "C" void *fn_80437110(void *self);
extern "C" int fn_80435340(Obj *h);
extern "C" int fn_80436294(void *self);
extern "C" void fn_8004B4D8(void *a, void *b, int c);
class Quat;
extern "C" void fn_8037E388(void *out, int h, const Quat &q);
extern "C" char lbl_8053F7E0[];

class ShapeDataPair
{
public:
    char d[0x30];
    ShapeDataPair();
};

class ShapeData
{
public:
    char d[0x20];
    ShapeData();
};

struct Result
{
    int a;
    int b;
};

class Quat
{
public:
    char d[0x10];
    Quat(void *v) __asm__("fn_804362D4");
};

class Placement
{
public:
    char d[0x40];
    Placement(void *a, void *b, void *c, int d, int e);
};

class Handle
{
public:
    virtual void v0();
    virtual void v1();
    virtual int v2();
    virtual void v3();
    virtual void v4();
    virtual Result v5(void *a, void *b, ...);
    virtual void v6(void *a, Obj &b, void *c);
};

class Body
{
public:
    char data[0x88];
    virtual void v0(void *p);
    virtual void v1();
    virtual int v2();
};

extern "C" void fn_80437B60(register void *self, register Body *body, register int flag)
{
    ShapeDataPair pair;
    fn_8037E388((char *)&pair, fn_8032A228(self)->get8(), Quat(fn_804370E8(fn_80437378(body))));
    fn_8037E388((char *)&pair + 0x10, fn_8032A228(self)->get8(), Quat(fn_80437110(fn_80437378(body))));
    if (body->v2() && ((Handle *)fn_80435340(fn_8032A228(self)))->v2() == 0x18)
    {
        fn_8004B4D8(lbl_8053F7E0, body, 1);
        ((Handle *)fn_80435340(fn_8032A228(self)))->v6(&pair, *fn_8032A228(self), lbl_8053F7E0);
    }
    else
    {
        ShapeData sd;
        Result res = ((Handle *)fn_80435340(fn_8032A228(self)))->v5(&pair, &sd);
        if (fn_80436294(&res))
        {
            Placement pl(fn_8032A228(self), fn_80437378(body), &sd, flag, -1);
            body->v0(&pl);
        }
    }
}
