// Sets the value `v` on the handle at +0x4 between the fn_8024D258/fn_8024D298 pair, then stores it at +0xC (docs/versus.md section 5, row 2).
extern void fn_8024D258(void);
extern void fn_8024D298(void);
extern void fn_8024EA48(int handle, int a, int v);

void fn_80457478(register int *self, register int v)
{
    fn_8024D258();
    fn_8024EA48(self[1], 100, v);
    fn_8024D298();
    self[3] = v;
}
