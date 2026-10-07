// Empty stub that the APT registrars call with the file name and line, then AptObject's destructor and copy constructor (docs/versus.md section 5, row 2).
extern void __builtin_delete(void *p);
extern void fn_8044B84C(void *self, int inChrg);
extern void fn_8044B8F8(void *self, void *other);

void fn_8044B4EC(register const char *file, register int line)
{
}

// AptObject's destructor, hand-written C; the label gives it the mangled name its C++ callers need (docs/matching_notes.md).
__asm__(".text\n\t.globl _._9AptObject\n\t.type _._9AptObject,@function\n_._9AptObject:");

void fn_8044B510(register void *self, register int inChrg)
{
    fn_8044B84C(self, 2);
    if (inChrg & 1)
    {
        __builtin_delete(self);
    }
    else
    {
    }
}

__asm__(".size _._9AptObject, 0x58");

void *__9AptObjectRC9AptObject(register void *self, register void *other)
{
    fn_8044B8F8(self, other);
    return self;
}
