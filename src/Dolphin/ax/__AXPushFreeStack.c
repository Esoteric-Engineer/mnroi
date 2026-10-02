typedef struct AXVPB {
    struct AXVPB* next;
    void* pad4[2];
    unsigned long priority;
} AXVPB;

extern AXVPB* __AXStackHead[];

void __AXPushFreeStack(AXVPB* p)
{
    p->next = __AXStackHead[0];
    __AXStackHead[0] = p;
    p->priority = 0;
}
