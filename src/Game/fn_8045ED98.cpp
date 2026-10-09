// HandleE::get forwards to the implementation's virtual slot 1 (class name is a guess; see fn_8045E6AC.cpp).

inline int sn_return_decl(int a) { return a; }

class HandleEImplVT
{
public:
    int unk0; // +0x0, the vptr follows at +0x4
    virtual void v0();
    virtual int v1();
};

class HandleE
{
public:
    HandleEImplVT *impl; // +0x0, the vptr follows at +0x4
    virtual ~HandleE();
    int get();
};

int HandleE::get()
{
    return impl->v1();
}
