// Forwards to fn_80126B68 on the member at +0x8 (docs/versus.md section 5).
extern void fn_80126B68(void *);

void fn_8045FA74(register char *self)
{
    fn_80126B68(self + 0x8);
}
