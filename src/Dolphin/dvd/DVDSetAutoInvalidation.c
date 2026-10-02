typedef int BOOL;

extern BOOL autoInvalidation;

BOOL DVDSetAutoInvalidation(BOOL autoInval) {
    BOOL prev;

    prev = autoInvalidation;
    autoInvalidation = autoInval;
    return prev;
}
