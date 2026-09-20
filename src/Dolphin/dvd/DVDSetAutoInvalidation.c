typedef int BOOL;

extern BOOL lbl_8066C414;

BOOL DVDSetAutoInvalidation(BOOL autoInval) {
    BOOL prev;

    prev = lbl_8066C414;
    lbl_8066C414 = autoInval;
    return prev;
}
