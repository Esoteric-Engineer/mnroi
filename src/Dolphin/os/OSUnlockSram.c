typedef int BOOL;

extern void fn_8017F2E4(BOOL commit, unsigned long offset);

void __OSUnlockSram(BOOL commit)
{
    fn_8017F2E4(commit, 0);
}

void __OSUnlockSramEx(BOOL commit)
{
    fn_8017F2E4(commit, 0x14);
}
