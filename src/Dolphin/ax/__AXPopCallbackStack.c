typedef struct AXVPB {
    void* pad0[2];
    struct AXVPB* next;
} AXVPB;

extern AXVPB* lbl_8066FA08;

AXVPB* __AXPopCallbackStack(void)
{
    AXVPB* p = lbl_8066FA08;

    if (p != 0) {
        lbl_8066FA08 = p->next;
    }
    return p;
}
