typedef int BOOL;

extern int CARDUnmount(int chan);

BOOL OnReset_8040B478(BOOL f)
{
    if (!f) {
        if (CARDUnmount(0) == -1 || CARDUnmount(1) == -1) {
            return 0;
        }
    }

    return 1;
}
