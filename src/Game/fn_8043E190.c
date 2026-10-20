// Entry-array accessor, forwarder and constructor of the classes around fn_8043DB70 (docs/versus.md, row 8).

typedef struct Entry
{
    char pad[0x30];
} Entry;

extern void fn_8043FC00(void *p, int a);
extern void fn_80434988(void *p);
extern void fn_8043B914(void *p);

Entry *fn_8043E190(register Entry *self, register int i)
{
    return &self[i];
}

void fn_8043E1C4(register void *self, register int a)
{
    fn_8043FC00(self, a);
}

char *fn_8043E204(register char *self)
{
    fn_80434988(self + 0x20);
    fn_8043B914(self + 0x30);
    return self;
}
