// KVList's and KSList's inline functions (docs/core.md row 18).

inline int sn_return_decl(int a) { return a; }

struct KV;

struct NewKV {
    char *key;
};

extern "C" {
void fn_801B5170(register KV *self, int inChrg);

__asm__(".text\n\t.globl _._5Sub24\n\t.type _._5Sub24,@function\n_._5Sub24:");
void fn_80467428(register KV *self, register int inChrg)
{
    fn_801B5170(self, inChrg);
}
__asm__(".size _._5Sub24, 0x40");

char *fn_80467468(register NewKV *self)
{
    return self->key;
}
}
