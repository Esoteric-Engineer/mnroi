typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct OSContext OSContext;

typedef struct DSPTaskInfo {
    volatile u32 state;
    volatile u32 priority;
    volatile u32 flags;
    u32 pad[7];
    void (*init_cb)(struct DSPTaskInfo*);
    void (*res_cb)(struct DSPTaskInfo*);
    void (*done_cb)(struct DSPTaskInfo*);
    void (*req_cb)(struct DSPTaskInfo*);
    struct DSPTaskInfo* next;
    struct DSPTaskInfo* prev;
} DSPTaskInfo;

volatile u16 __DSPRegs[0x200] : 0xCC005000;

#pragma force_active on
static int t0;
static int t1;
static int t2;
#pragma force_active off

DSPTaskInfo* __DSP_curr_task;
DSPTaskInfo* __DSP_first_task;
DSPTaskInfo* __DSP_last_task;
DSPTaskInfo* __DSP_tmp_task;
DSPTaskInfo* __DSP_rude_task;
int __DSP_rude_task_pending;

extern void OSClearContext(OSContext* context);
extern void OSSetCurrentContext(OSContext* context);
extern u32 DSPCheckMailFromDSP(void);
extern u32 DSPReadMailFromDSP(void);
extern void DSPSendMailToDSP(u32 mail);
extern u32 DSPCheckMailToDSP(void);
extern void __DSP_exec_task(DSPTaskInfo* curr, DSPTaskInfo* next);
extern void __DSP_remove_task(DSPTaskInfo* task);

void __DSPHandler(int interrupt, OSContext* context)
{
    u8 ctx[0x2D0];
    u16 tmp;
    u32 mail;

    tmp = __DSPRegs[5];
    tmp = (tmp & ~0x28) | 0x80;
    __DSPRegs[5] = tmp;

    OSClearContext((OSContext*)ctx);
    OSSetCurrentContext((OSContext*)ctx);

    while (DSPCheckMailFromDSP() == 0)
        ;

    mail = DSPReadMailFromDSP();
    if ((__DSP_curr_task->flags & (1 << (31 - 0x1E))) && (mail + 0x232F0000) == 2)
        mail = 0xDCD10003;

    switch (mail) {
    case 0xDCD10000:
        __DSP_curr_task->state = 1;
        if (__DSP_curr_task->init_cb != 0)
            __DSP_curr_task->init_cb(__DSP_curr_task);
        break;
    case 0xDCD10001:
        __DSP_curr_task->state = 1;
        if (__DSP_curr_task->res_cb != 0)
            __DSP_curr_task->res_cb(__DSP_curr_task);
        break;
    case 0xDCD10002:
        if (__DSP_rude_task_pending) {
            if (__DSP_curr_task == __DSP_rude_task) {
                DSPSendMailToDSP(0xCDD10003);
                while (DSPCheckMailToDSP() != 0)
                    ;
                __DSP_rude_task = 0;
                __DSP_rude_task_pending = 0;
                if (__DSP_curr_task->res_cb != 0)
                    __DSP_curr_task->res_cb(__DSP_curr_task);
            } else {
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP() != 0)
                    ;
                __DSP_exec_task(__DSP_curr_task, __DSP_rude_task);
                __DSP_curr_task->state = 2;
                __DSP_curr_task = __DSP_rude_task;
                __DSP_rude_task = 0;
                __DSP_rude_task_pending = 0;
            }
        } else {
            if (__DSP_curr_task->next == 0) {
                if (__DSP_curr_task == __DSP_first_task) {
                    DSPSendMailToDSP(0xCDD10003);
                    while (DSPCheckMailToDSP() != 0)
                        ;
                    if (__DSP_curr_task->res_cb != 0)
                        __DSP_curr_task->res_cb(__DSP_curr_task);
                } else {
                    DSPSendMailToDSP(0xCDD10001);
                    while (DSPCheckMailToDSP() != 0)
                        ;
                    __DSP_exec_task(__DSP_curr_task, __DSP_first_task);
                    __DSP_curr_task->state = 2;
                    __DSP_curr_task = __DSP_first_task;
                }
            } else {
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP() != 0)
                    ;
                __DSP_exec_task(__DSP_curr_task, __DSP_curr_task->next);
                __DSP_curr_task->state = 2;
                __DSP_curr_task = __DSP_curr_task->next;
            }
        }
        break;
    case 0xDCD10003:
        if (__DSP_rude_task_pending) {
            if (__DSP_curr_task->done_cb != 0)
                __DSP_curr_task->done_cb(__DSP_curr_task);
            DSPSendMailToDSP(0xCDD10001);
            while (DSPCheckMailToDSP() != 0)
                ;
            __DSP_exec_task(0, __DSP_rude_task);
            __DSP_remove_task(__DSP_curr_task);
            __DSP_curr_task = __DSP_rude_task;
            __DSP_rude_task = 0;
            __DSP_rude_task_pending = 0;
        } else {
            if (__DSP_curr_task->next == 0) {
                if (__DSP_curr_task == __DSP_first_task) {
                    if (__DSP_curr_task->done_cb != 0)
                        __DSP_curr_task->done_cb(__DSP_curr_task);
                    DSPSendMailToDSP(0xCDD10002);
                    while (DSPCheckMailToDSP() != 0)
                        ;
                    __DSP_curr_task->state = 3;
                    __DSP_remove_task(__DSP_curr_task);
                } else {
                    if (__DSP_curr_task->done_cb != 0)
                        __DSP_curr_task->done_cb(__DSP_curr_task);
                    DSPSendMailToDSP(0xCDD10001);
                    while (DSPCheckMailToDSP() != 0)
                        ;
                    __DSP_curr_task->state = 3;
                    __DSP_exec_task(0, __DSP_first_task);
                    __DSP_curr_task = __DSP_first_task;
                    __DSP_remove_task(__DSP_last_task);
                }
            } else {
                if (__DSP_curr_task->done_cb != 0)
                    __DSP_curr_task->done_cb(__DSP_curr_task);
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP() != 0)
                    ;
                __DSP_curr_task->state = 3;
                __DSP_exec_task(0, __DSP_curr_task->next);
                __DSP_curr_task = __DSP_curr_task->next;
                __DSP_remove_task(__DSP_curr_task->prev);
            }
        }
        break;
    case 0xDCD10004:
        if (__DSP_curr_task->req_cb != 0)
            __DSP_curr_task->req_cb(__DSP_curr_task);
        break;
    }

    OSClearContext((OSContext*)ctx);
    OSSetCurrentContext(context);
}
