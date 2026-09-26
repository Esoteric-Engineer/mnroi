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

extern ARQRequest* lbl_8066F9E0;
extern ARQRequest* lbl_8066F9F4;
extern void (*lbl_8066F9FC)(u32);
extern u32 lbl_8066FA00;

extern void ARStartDMA(u32 type, u32 mainmem, u32 aram, u32 length);

void __ARQServiceQueueLo(void) {
    if (lbl_8066F9F4 == 0 && lbl_8066F9E0) {
        lbl_8066F9F4 = lbl_8066F9E0;
        lbl_8066F9E0 = lbl_8066F9E0->next;
    }
    if (lbl_8066F9F4) {
        if (lbl_8066F9F4->length <= lbl_8066FA00) {
            if (lbl_8066F9F4->type == 0) {
                ARStartDMA(lbl_8066F9F4->type, lbl_8066F9F4->source, lbl_8066F9F4->dest, lbl_8066F9F4->length);
            } else {
                ARStartDMA(lbl_8066F9F4->type, lbl_8066F9F4->dest, lbl_8066F9F4->source, lbl_8066F9F4->length);
            }
            lbl_8066F9FC = lbl_8066F9F4->callback;
        } else if (lbl_8066F9F4->type == 0) {
            ARStartDMA(lbl_8066F9F4->type, lbl_8066F9F4->source, lbl_8066F9F4->dest, lbl_8066FA00);
        } else {
            ARStartDMA(lbl_8066F9F4->type, lbl_8066F9F4->dest, lbl_8066F9F4->source, lbl_8066FA00);
        }
        lbl_8066F9F4->length -= lbl_8066FA00;
        lbl_8066F9F4->source += lbl_8066FA00;
        lbl_8066F9F4->dest += lbl_8066FA00;
    }
}
