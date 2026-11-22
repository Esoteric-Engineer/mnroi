// CTask's inline functions (docs/core.md row 18, section 4.7).

inline int sn_return_decl(int a) { return a; }

struct CTask {
    unsigned char flags;
};

extern "C" {
unsigned char fn_8046859C(register CTask *self)
{
    return self->flags & 1;
}

int fn_804685D0(register CTask *self)
{
    return fn_8046859C(self) && (unsigned char)(self->flags & 2);
}
}
