typedef struct AXVPB {
    struct AXVPB* next;
    struct AXVPB* prev;
    void* pad8;
    unsigned long priority;
} AXVPB;

extern AXVPB* lbl_8064F228[];
extern AXVPB* lbl_8064F2A8[];

void __AXRemoveFromStack(AXVPB* p)
{
    unsigned long pri = p->priority;
    AXVPB** head = &lbl_8064F228[pri];
    AXVPB** tail = &lbl_8064F2A8[pri];

    if (*head == *tail) {
        *tail = 0;
        *head = 0;
        return;
    }
    if (p == *head) {
        *head = p->next;
        (*head)->prev = 0;
    } else if (p == *tail) {
        *tail = p->prev;
        (*tail)->next = 0;
    } else {
        AXVPB* prev = p->prev;
        AXVPB* next = p->next;
        prev->next = next;
        next->prev = prev;
    }
}
