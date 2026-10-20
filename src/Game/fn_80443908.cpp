// Accessors on two globals: a counter object, and lbl_80593BE8, which holds two
// fn_80443E20 seeds (+0x4, +0x8) and a loading flag at +0x5C.
// C++, not C: the unit's tail branch pairs are the cc1plus function end (docs/prodg.md).

typedef struct Counter
{
    int count; // +0x00
} Counter;

typedef struct Globals
{
    char unk0[0x4];
    int seed1; // +0x04
    int seed2; // +0x08
    char unk0C[0x50];
    int loading; // +0x5C
} Globals;

extern "C" {

void fn_80443908(register Counter *c)
{
    c->count++;
}

int fn_8044393C(register Globals *g)
{
    return g->seed1;
}

int fn_80443970(register Globals *g)
{
    return g->seed2;
}

int fn_804439A4(register Globals *g)
{
    return g->loading > 0;
}

}
