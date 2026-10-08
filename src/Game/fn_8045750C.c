// Releases the handle at +0x4 if the flag at +0x8 is set (docs/versus.md section 5, row 2).
extern void fn_8024E508(int handle);

void fn_8045750C(register int *self)
{
    if (self[2] != 0) {
        fn_8024E508(self[1]);
        self[2] = 0;
    }
}
