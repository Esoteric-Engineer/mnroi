// The system monitor's inline functions (docs/core.md row 18).

inline int sn_return_decl(int a) { return a; }

struct Clock {
    char pad[0x3C];
    int pause;
};

struct Obj4 {
    int f0;
    int f4;
};

struct Mon {
    char pad[0x7C];
    int f7C;
};

struct CSysLock {
    int f0;
};

extern "C" {
extern int lbl_8066BB00;
void fn_801AF12C(register CSysLock *self);
void __builtin_delete(void *p);

void fn_80466828(register Clock *self)
{
    self->pause = 1;
}

void fn_80466850(register Clock *self)
{
    self->pause = 0;
}

int fn_80466878(register Obj4 *self)
{
    return self->f4;
}

int fn_804668A4(void)
{
    return lbl_8066BB00;
}

__asm__(".text\n\t.globl _._8CSysLock\n\t.type _._8CSysLock,@function\n_._8CSysLock:");
void fn_804668CC(register CSysLock *self, register int inChrg)
{
    fn_801AF12C(self);
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}
__asm__(".size _._8CSysLock, 0x54");

CSysLock *fn_80466920(register CSysLock *self)
{
    self->f0 = 0;
    return self;
}

int fn_80466950(register Mon *self)
{
    return self->f7C;
}
}
