typedef int BOOL;

extern int fn_8040D4AC(int chan);

BOOL OnReset_8040B478(BOOL f)
{
    if (!f) {
        if (fn_8040D4AC(0) == -1 || fn_8040D4AC(1) == -1) {
            return 0;
        }
    }

    return 1;
}
