// String::Escape-style pass: replaces each of "$&+=?%" in the string by its "%24"-style entry.
typedef struct
{
    int length;         // +0x0
    int shown;          // +0x4
    char inline_[0x40]; // +0x8
    char *data;         // +0x48
} String;

extern int fn_80449234(String *self);
extern char *fn_80449260(String *self, int idx);
extern void fn_80449298(void *self, int inChrg);
extern int fn_804493A0(void *self, const char *s);
typedef struct
{
    char c[6];
} Chars;
typedef struct
{
    char c[0x18];
} Names;
extern char lbl_80490048[];
extern Names lbl_8049004E;
extern const char *fn_80449BE4(void *self);
extern const char *fn_80449C48(void *self);
extern const char *fn_80449DFC(void *self, char **first, char **last);
extern void fn_80449EEC(void *self, char **a, char **b, char **c);

void fn_804494AC(register String *self)
{
    int a = 6;
    int b = 4;
    Chars chars = *(Chars *)lbl_80490048;
    Names names = lbl_8049004E;
    int i;
    int j;
    char tmp[0x50];
    char *t88;
    char *t8c;
    char *t90;
    char *t94;
    char *t98;
    i = 0;
    while (fn_80449BE4(self) + i < fn_80449C48(self))
    {
        j = 0;
        while (j <= 5)
        {
            if (i < fn_80449234(self) && *fn_80449260(self, i) == chars.c[j])
            {
                register char **p1;
                register char **p2;
                register char **p3;
                fn_804493A0(tmp, names.c + j * 4);
                t88 = fn_80449BE4(tmp);
                p1 = &t88;
                t8c = fn_80449C48(tmp);
                p2 = &t8c;
                t94 = fn_80449BE4(self) + i;
                p3 = &t94;
                t98 = fn_80449BE4(self) + i + 1;
                t90 = fn_80449DFC(self, p3, &t98);
                fn_80449EEC(self, p1, p2, &t90);
                i += 3;
                fn_80449298(tmp, 2);
            }
            j++;
        }
        i++;
    }
}

char *fn_804496C8(register String *self)
{
    return self->data;
}
