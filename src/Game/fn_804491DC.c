// String class helpers: digit to char, '-', length, char address; destructor; length setters.
typedef struct
{
    int length;       // +0x0
    int shown;        // +0x4
    char inline_[0x40]; // +0x8
    char *data;       // +0x48
} String;

extern int fn_80449CAC(void *self);
extern void fn_80449CE8(char *buf);
extern void fn_80449D20(void *self);
extern char *fn_80449D58(int n);

char fn_804491DC(register int digit)
{
    return digit + 0x30;
}

char fn_80449210(void)
{
    return 0x2D;
}

int fn_80449234(register String *self)
{
    return self->length;
}

char *fn_80449260(register String *self, register int idx)
{
    goto body;
body:
    return self->data + idx;
}

// String's destructor, hand-written C; the label gives it the mangled name its C++ callers need (docs/matching_notes.md).
__asm__(".text\n\t.globl _._6String\n\t.type _._6String,@function\n_._6String:");

void fn_80449298(register String *self, register int inChrg)
{
    if (!fn_80449CAC(self))
    {
        fn_80449CE8(self->data);
    }
    if (inChrg & 1)
    {
        fn_80449D20(self);
    }
}

__asm__(".size _._6String, 0x64");

void *fn_804492FC(register String *self, register int v)
{
    self->length = v;
    self->shown = v;
    return self;
}

char *fn_80449330(register int n)
{
    return fn_80449D58(n + 1);
}

void fn_80449378(register String *self, register int v)
{
    self->shown = v;
}
