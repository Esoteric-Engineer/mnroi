// Handle helpers: temp-object forwarder, two-slot selectors and small accessors (docs/versus.md, row 8).
// Names are guesses.

typedef struct Pair
{
    int a;
    int b;
} Pair;

extern int lbl_8066B838;
extern int fn_800B13D8(void *p);
extern void fn_8043D8A0(Pair *out, int a);
extern void fn_8032A318(void *self, int a, Pair v);
extern int fn_80436754(int a);
extern int fn_804367A8(int a);
extern const void *fn_804367A8_ptr(int a) __asm__("fn_804367A8");
extern int fn_8043F760(int a);
extern int fn_80436900(int a);
extern void *fn_80317950(void *self);
extern int fn_8043CA10(void *a, int *b);
extern void fn_80317BE8(void *self, int v);

void fn_8043E254(register void *self, register void *p)
{
    Pair tmp;

    fn_8043D8A0(&tmp, p ? fn_800B13D8(p) : 0);
    fn_8032A318(self, 0, tmp);
}

int fn_8043E2D4(register int *self, register int second)
{
    register int v;

    if (second)
        v = fn_804367A8(fn_80436754(self[1]));
    else
        v = fn_804367A8(fn_80436754(self[0]));
    return v;
}

int fn_8043E34C(register int *self, register int second)
{
    register int v;

    if (second)
        v = fn_8043F760(self[1]);
    else
        v = fn_8043F760(self[0]);
    return v;
}

int fn_8043E3AC(register int *self, register int second)
{
    return second ? self[1] : self[0];
}

int fn_8043E3EC(register int *self, register int second)
{
    int t;

    if (second)
        t = self[3];
    else
        t = self[2];
    return fn_80436900(t);
}

int fn_8043E450(register int *self, register int second)
{
    void *t;

    if (second)
        t = fn_804367A8_ptr(fn_80436754(self[1]));
    else
        t = fn_804367A8_ptr(fn_80436754(self[0]));
    return fn_80436900((int)t);
}

void fn_8043E4D4(register void *self)
{
    if (self != 0) {
        if (fn_8043CA10(fn_80317950(self), &lbl_8066B838) != -1) {
            fn_80317BE8(self, lbl_8066B838);
        }
    }
}
