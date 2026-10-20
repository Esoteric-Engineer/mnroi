// Small polymorphic classes: constructors, destructors and empty methods (docs/versus.md, row 8).

extern char lbl_804F4350[], lbl_804F4318[];
extern void __builtin_delete(void *p);

char **fn_8043DB70(register char **self)
{
    *self = lbl_804F4350;
    return self;
}

void fn_8043DBA4(register int a, register int b)
{
}

void fn_8043DBC8(register char **self, register int inChrg)
{
    *self = lbl_804F4350;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

char **fn_8043DC20(register char **self)
{
    return self;
}

char **fn_8043DC48(register char **self)
{
    *self = lbl_804F4318;
    return self;
}

void fn_8043DC7C(register int a, register int b)
{
}
