typedef struct AXVPB {
    void* pad0[3];
    unsigned long priority;
    void (*callback)(struct AXVPB*);
} AXVPB;

extern AXVPB* __AXPopCallbackStack(void);
extern void __AXRemoveFromStack(AXVPB* p);
extern void __AXPushFreeStack(AXVPB* p);

void __AXServiceCallbackStack(void)
{
    AXVPB* p = __AXPopCallbackStack();

    while (p != 0) {
        if (p->priority != 0) {
            if (p->callback != 0) {
                p->callback(p);
            }
            __AXRemoveFromStack(p);
            __AXPushFreeStack(p);
        }
        p = __AXPopCallbackStack();
    }
}
