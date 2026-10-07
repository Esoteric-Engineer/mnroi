// Broadcast through vtable slots 2 and 1 when fn_8032A0F8 accepts the argument (docs/versus.md, row 8).

inline int sn_return_decl(int a)
{
    return a;
}

class Target
{
public:
    virtual void slot0();
    virtual void slot1(int a); // vtable +0x10
    virtual void slot2(int a); // vtable +0x18
};

extern "C" {
int fn_8032A0F8(int a);

void fn_8043DCA0(register Target *self, register int a)
{
    if (fn_8032A0F8(a)) {
        self->slot2(a);
        self->slot1(a);
    }
}

void fn_8043DD48(register int a, register int b)
{
}
}
