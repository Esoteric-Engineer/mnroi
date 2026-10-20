// Queries the handle at +0x8; on success stores its second field to *out and returns 1 (docs/versus.md section 5, row 2).
extern void fn_8024D258(void);
extern void fn_8024D298(void);
extern int fn_8024EF78(int handle, int *info);

int fn_80457558(register int *self, register int *out)
{
    int info[4];
    int r;

    *out = -1;
    if (self[2] != 0) {
        fn_8024D258();
        r = fn_8024EF78(self[2], info);
        fn_8024D298();
        if (r >= 0 && info[0] == 2) {
            *out = info[1];
            return 1;
        }
    }
    return 0;
}
