typedef unsigned int u32;

typedef struct ARQRequest {
    struct ARQRequest* next;
    u32 owner;
    u32 type;
    u32 priority;
    u32 source;
    u32 dest;
    u32 length;
    void (*callback)(u32);
} ARQRequest;

extern ARQRequest* __ARQRequestQueueHi;
extern ARQRequest* __ARQRequestTailHi;
extern ARQRequest* __ARQRequestQueueLo;
extern ARQRequest* __ARQRequestTailLo;
extern ARQRequest* lbl_8066F9E8;
extern ARQRequest* lbl_8066F9EC;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);

void ARQRemoveRequest(ARQRequest* request) {
    int level;
    ARQRequest* tmp;

    level = OSDisableInterrupts();

    lbl_8066F9E8 = 0;
    lbl_8066F9EC = 0;
    for (tmp = __ARQRequestQueueHi; tmp; tmp = tmp->next) {
        if (tmp != request) {
            if (lbl_8066F9E8 == 0) {
                lbl_8066F9E8 = tmp;
                lbl_8066F9EC = tmp;
            } else {
                lbl_8066F9EC->next = tmp;
                lbl_8066F9EC = tmp;
            }
        }
    }
    __ARQRequestQueueHi = lbl_8066F9E8;
    __ARQRequestTailHi = lbl_8066F9EC;

    lbl_8066F9E8 = 0;
    lbl_8066F9EC = 0;
    for (tmp = __ARQRequestQueueLo; tmp; tmp = tmp->next) {
        if (tmp != request) {
            if (lbl_8066F9E8 == 0) {
                lbl_8066F9E8 = tmp;
                lbl_8066F9EC = tmp;
            } else {
                lbl_8066F9EC->next = tmp;
                lbl_8066F9EC = tmp;
            }
        }
    }
    __ARQRequestQueueLo = lbl_8066F9E8;
    __ARQRequestTailLo = lbl_8066F9EC;

    OSRestoreInterrupts(level);
}
