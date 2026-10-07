// Pair-less accessors and forwarders on unidentified objects (docs/versus.md, row 8).

typedef struct Obj
{
    int unk0; // +0x0
    int word; // +0x4
} Obj;

extern void *fn_8043F78C(void *p);
extern void fn_8043F7B8(void *p, int a);
extern void fn_8043F7E8(void *p, int a);

int fn_8043D82C(register Obj *self)
{
    return self->word;
}

void *fn_8043D858(register char *self)
{
    return fn_8043F78C(self + 0x14);
}

void *fn_8043D8A0(register void *self, register int a)
{
    fn_8043F7B8(self, a);
    return self;
}

void *fn_8043D8E8(register void *self, register int a)
{
    fn_8043F7E8(self, a);
    return self;
}

float fn_8043D930(register float *self)
{
    return self[1];
}

float fn_8043D95C(register float *self)
{
    return self[2];
}

void fn_8043D988(register float *self, register float v)
{
    self[1] = v;
}
