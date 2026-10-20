// Sets the handle at +0x4 to the stopped state or to self[3] (docs/versus.md section 5, row 2).
extern void fn_8024D258(void);
extern void fn_8024D298(void);
extern void fn_8024EA48(int handle, int a, int v);
extern void fn_8024EECC(int handle, int flags);
extern void fn_8024F244(int handle, int a, float f);

void fn_804575EC(register int *self, register int stop)
{
    if (self[2] == 0) {
        return;
    }
    if (stop != 0) {
        fn_8024D258();
        fn_8024F244(self[1], -1, 0.0f);
        fn_8024EECC(self[1], 0);
        fn_8024D298();
    } else {
        fn_8024D258();
        fn_8024EA48(self[1], 1, self[3]);
        fn_8024EECC(self[1], 0x1000);
        fn_8024D298();
    }
}
