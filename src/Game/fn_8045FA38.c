// Forwards to fn_80126B30 on the member at +0x8 (docs/versus.md section 5).
extern void fn_80126B30(void *);

void fn_8045FA38(register char *self)
{
    fn_80126B30(self + 0x8);
}
