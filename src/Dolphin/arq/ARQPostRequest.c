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
extern ARQRequest* lbl_8066F9F0;
extern ARQRequest* lbl_8066F9F4;
extern void (*lbl_8066F9F8)(u32);

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern void ARStartDMA(u32 type, u32 mainmem, u32 aram, u32 length);
extern void __ARQServiceQueueLo(void);
extern void __ARQCallbackHack(u32 unused);

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
        if (lbl_8066F9E0) {
            lbl_8066F9E4->next = request;
        } else {
            lbl_8066F9E0 = request;
        }
        lbl_8066F9E4 = request;
        break;
    case 1:
        if (lbl_8066F9D8) {
            lbl_8066F9DC->next = request;
        } else {
            lbl_8066F9D8 = request;
        }
        lbl_8066F9DC = request;
        break;
    }
    if (lbl_8066F9F0 == 0 && lbl_8066F9F4 == 0) {
        __ARQPopTaskQueueHi();
        if (lbl_8066F9F0 == 0) {
            __ARQServiceQueueLo();
        }
    }
    OSRestoreInterrupts(level);
}
