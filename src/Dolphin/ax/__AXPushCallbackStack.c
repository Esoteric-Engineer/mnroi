typedef struct AXVPB {
    void* pad0[2];
    struct AXVPB* next;
} AXVPB;

extern AXVPB* lbl_8066FA08;

void __AXPushCallbackStack(AXVPB* p)
{
    p->next = lbl_8066FA08;
    lbl_8066FA08 = p;
}
