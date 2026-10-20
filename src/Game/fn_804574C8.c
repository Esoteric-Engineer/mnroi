// Calls fn_8045D984(self, v, 1) (docs/versus.md section 5, row 2).
extern void fn_8045D984(void *self, int v, int flag);

void fn_804574C8(register void *self, register int v)
{
    fn_8045D984(self, v, 1);
}
