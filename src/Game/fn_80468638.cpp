// stdVar's inline functions (docs/core.md row 18).

inline int sn_return_decl(int a) { return a; }

struct Var {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
};

struct Kind {
    int kind;
};

extern "C" {
Var *fn_80468638(register Var *self)
{
    self->f0 = 0;
    self->f4 = 0;
    self->f8 = 0;
    self->fC = 0;
    self->f10 = 0;
    return self;
}

Kind *fn_80468688(register Kind *self)
{
    self->kind = 3;
    return self;
}
}
