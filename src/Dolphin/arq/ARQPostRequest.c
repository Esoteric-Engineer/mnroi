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
extern ARQRequest* __ARQRequestPendingHi;
extern ARQRequest* __ARQRequestPendingLo;
extern void (*__ARQCallbackHi)(u32);

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern void ARStartDMA(u32 type, u32 mainmem, u32 aram, u32 length);
extern void __ARQServiceQueueLo(void);
extern void __ARQCallbackHack(u32 unused);

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

void ARQPostRequest(ARQRequest* request, u32 owner, u32 type, u32 priority, u32 source, u32 dest, u32 length,
                    void (*callback)(u32)) {
    int level;

    request->next = 0;
    request->owner = owner;
    request->type = type;
    request->source = source;
    request->dest = dest;
    request->length = length;
    if (callback) {
        request->callback = callback;
    } else {
        request->callback = __ARQCallbackHack;
    }
    level = OSDisableInterrupts();
    switch (priority) {
    case 0:
        if (__ARQRequestQueueLo) {
            __ARQRequestTailLo->next = request;
        } else {
            __ARQRequestQueueLo = request;
        }
        __ARQRequestTailLo = request;
        break;
    case 1:
        if (__ARQRequestQueueHi) {
            __ARQRequestTailHi->next = request;
        } else {
            __ARQRequestQueueHi = request;
        }
        __ARQRequestTailHi = request;
        break;
    }
    if (__ARQRequestPendingHi == 0 && __ARQRequestPendingLo == 0) {
        __ARQPopTaskQueueHi();
        if (__ARQRequestPendingHi == 0) {
            __ARQServiceQueueLo();
        }
    }
    OSRestoreInterrupts(level);
}
