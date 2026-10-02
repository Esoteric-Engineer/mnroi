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
extern ARQRequest* __ARQRequestPendingHi;
extern ARQRequest* __ARQRequestPendingLo;
extern void (*__ARQCallbackHi)(u32);
extern void (*__ARQCallbackLo)(u32);

extern void ARStartDMA(u32 type, u32 mainmem, u32 aram, u32 length);
extern void __ARQServiceQueueLo(void);

inline void __ARQPopTaskQueueHi(void) {
    if (__ARQRequestQueueHi) {
        if (__ARQRequestQueueHi->type == 0) {
            ARStartDMA(__ARQRequestQueueHi->type, __ARQRequestQueueHi->source, __ARQRequestQueueHi->dest, __ARQRequestQueueHi->length);
        } else {
            ARStartDMA(__ARQRequestQueueHi->type, __ARQRequestQueueHi->dest, __ARQRequestQueueHi->source, __ARQRequestQueueHi->length);
        }
        __ARQCallbackHi = __ARQRequestQueueHi->callback;
        __ARQRequestPendingHi = __ARQRequestQueueHi;
        __ARQRequestQueueHi = __ARQRequestQueueHi->next;
    }
}

void __ARQInterruptServiceRoutine(void) {
    if (__ARQCallbackHi) {
        __ARQCallbackHi((u32)__ARQRequestPendingHi);
        __ARQRequestPendingHi = 0;
        __ARQCallbackHi = 0;
    } else if (__ARQCallbackLo) {
        __ARQCallbackLo((u32)__ARQRequestPendingLo);
        __ARQRequestPendingLo = 0;
        __ARQCallbackLo = 0;
    }
    __ARQPopTaskQueueHi();
    if (__ARQRequestPendingHi == 0) {
        __ARQServiceQueueLo();
    }
}
