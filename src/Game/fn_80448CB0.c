// String fill constructor (len bytes of ch); NonMatching, see docs/nonmatching.md.
extern void *fn_804492FC(void *self, int len);
extern char *fn_80449330(int len);
extern void fn_80449378(void *self, int len);

typedef struct Str
{
    int len;       // +0x0
    int cap;       // +0x4
    char buf[0x40]; // +0x8
    char *data;    // +0x48
} Str;

Str *fn_80448CB0(register Str *self, register int len, register int ch)
{
    int i;
    fn_804492FC(self, len);
    {
        register char *a;
        register char *b;
        register int n;
        a = self->buf;
        b = self->buf;
        n = 0x3F;
    }
    self->data = self->buf;
    if (self->len > 0x3F)
    {
        self->data = fn_80449330(self->len);
    }
    if (self->len > 0)
    {
        i = 0;
        while (i < self->len)
        {
            self->data[i] = ch;
            i++;
        }
    }
    self->data[self->len] = 0;
    fn_80449378(self, self->len);
    return self;
}
