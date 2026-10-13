// A three-argument vtable slot that forwards only its second argument to fn_80121160 (docs/versus.md section 5, row 18).
extern void fn_80121160(void *target);

void fn_8045FBB0(register void *unused, register void *target, register void *extra)
{
    fn_80121160(target);
}
