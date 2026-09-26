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
extern ARQRequest* lbl_8066F9F0;
extern ARQRequest* lbl_8066F9F4;
extern void (*lbl_8066F9F8)(u32);
extern void (*lbl_8066F9FC)(u32);

extern void ARStartDMA(u32 type, u32 mainmem, u32 aram, u32 length);
extern void __ARQServiceQueueLo(void);

inline void __ARQPopTaskQueueHi(void) {
    if (lbl_8066F9D8) {
        if (lbl_8066F9D8->type == 0) {
            ARStartDMA(lbl_8066F9D8->type, lbl_8066F9D8->source, lbl_8066F9D8->dest, lbl_8066F9D8->length);
        } else {
            ARStartDMA(lbl_8066F9D8->type, lbl_8066F9D8->dest, lbl_8066F9D8->source, lbl_8066F9D8->length);
        }
        lbl_8066F9F8 = lbl_8066F9D8->callback;
        lbl_8066F9F0 = lbl_8066F9D8;
        lbl_8066F9D8 = lbl_8066F9D8->next;
    }
}

void __ARQInterruptServiceRoutine(void) {
    if (lbl_8066F9F8) {
        lbl_8066F9F8((u32)lbl_8066F9F0);
        lbl_8066F9F0 = 0;
        lbl_8066F9F8 = 0;
    } else if (lbl_8066F9FC) {
        lbl_8066F9FC((u32)lbl_8066F9F4);
        lbl_8066F9F4 = 0;
        lbl_8066F9FC = 0;
    }
    __ARQPopTaskQueueHi();
    if (lbl_8066F9F0 == 0) {
        __ARQServiceQueueLo();
    }
}
