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

extern ARQRequest* lbl_8066F9D8;
extern ARQRequest* lbl_8066F9DC;
extern ARQRequest* lbl_8066F9E0;
extern ARQRequest* lbl_8066F9E4;
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
    for (tmp = lbl_8066F9D8; tmp; tmp = tmp->next) {
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
    lbl_8066F9D8 = lbl_8066F9E8;
    lbl_8066F9DC = lbl_8066F9EC;

    lbl_8066F9E8 = 0;
    lbl_8066F9EC = 0;
    for (tmp = lbl_8066F9E0; tmp; tmp = tmp->next) {
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
    lbl_8066F9E0 = lbl_8066F9E8;
    lbl_8066F9E4 = lbl_8066F9EC;

    OSRestoreInterrupts(level);
}
