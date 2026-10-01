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

// Reverse declaration order in .sbss: this puts __ARQRequestQueueHi first and lays the rest of arq.c's .sbss out ascending from there.
int __ARQ_init_flag;
u32 __ARQChunkSize;
void (*__ARQCallbackLo)(u32);
void (*__ARQCallbackHi)(u32);
ARQRequest* __ARQRequestPendingLo;
ARQRequest* __ARQRequestPendingHi;
ARQRequest* lbl_8066F9EC;
ARQRequest* lbl_8066F9E8;
ARQRequest* __ARQRequestTailLo;
ARQRequest* __ARQRequestQueueLo;
ARQRequest* __ARQRequestTailHi;
ARQRequest* __ARQRequestQueueHi;

extern void ARStartDMA(u32 type, u32 mainmem, u32 aram, u32 length);

void __ARQServiceQueueLo(void) {
    if (__ARQRequestPendingLo == 0 && __ARQRequestQueueLo) {
        __ARQRequestPendingLo = __ARQRequestQueueLo;
        __ARQRequestQueueLo = __ARQRequestQueueLo->next;
    }
    if (__ARQRequestPendingLo) {
        if (__ARQRequestPendingLo->length <= __ARQChunkSize) {
            if (__ARQRequestPendingLo->type == 0) {
                ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->source, __ARQRequestPendingLo->dest, __ARQRequestPendingLo->length);
            } else {
                ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->dest, __ARQRequestPendingLo->source, __ARQRequestPendingLo->length);
            }
            __ARQCallbackLo = __ARQRequestPendingLo->callback;
        } else if (__ARQRequestPendingLo->type == 0) {
            ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->source, __ARQRequestPendingLo->dest, __ARQChunkSize);
        } else {
            ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->dest, __ARQRequestPendingLo->source, __ARQChunkSize);
        }
        __ARQRequestPendingLo->length -= __ARQChunkSize;
        __ARQRequestPendingLo->source += __ARQChunkSize;
        __ARQRequestPendingLo->dest += __ARQChunkSize;
    }
}
