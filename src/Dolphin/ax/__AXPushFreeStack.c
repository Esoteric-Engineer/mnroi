typedef struct AXVPB {
    struct AXVPB* next;
    void* pad4[2];
    unsigned long priority;
} AXVPB;

extern AXVPB* lbl_8064F228[];

void __AXPushFreeStack(AXVPB* p)
{
    p->next = lbl_8064F228[0];
    lbl_8064F228[0] = p;
    p->priority = 0;
}
