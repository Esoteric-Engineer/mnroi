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

extern DSPTaskInfo* __DSP_first_task;
extern DSPTaskInfo* lbl_8066FB00; /* __DSP_last_task */
extern DSPTaskInfo* lbl_8066FB08; /* __DSP_curr_task */
extern DSPTaskInfo* lbl_8066FAF8; /* __DSP_rude_task */
extern int lbl_8066FAF4;          /* __DSP_rude_task_pending */

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
    if ((lbl_8066FB08->flags & (1 << (31 - 0x1E))) && (mail + 0x232F0000) == 2)
        mail = 0xDCD10003;

    switch (mail) {
    case 0xDCD10000:
        lbl_8066FB08->state = 1;
        if (lbl_8066FB08->init_cb != 0)
            lbl_8066FB08->init_cb(lbl_8066FB08);
        break;
    case 0xDCD10001:
        lbl_8066FB08->state = 1;
        if (lbl_8066FB08->res_cb != 0)
            lbl_8066FB08->res_cb(lbl_8066FB08);
        break;
    case 0xDCD10002:
        if (lbl_8066FAF4) {
            if (lbl_8066FB08 == lbl_8066FAF8) {
                DSPSendMailToDSP(0xCDD10003);
                while (DSPCheckMailToDSP() != 0)
                    ;
                lbl_8066FAF8 = 0;
                lbl_8066FAF4 = 0;
                if (lbl_8066FB08->res_cb != 0)
                    lbl_8066FB08->res_cb(lbl_8066FB08);
            } else {
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP() != 0)
                    ;
                __DSP_exec_task(lbl_8066FB08, lbl_8066FAF8);
                lbl_8066FB08->state = 2;
                lbl_8066FB08 = lbl_8066FAF8;
                lbl_8066FAF8 = 0;
                lbl_8066FAF4 = 0;
            }
        } else {
            if (lbl_8066FB08->next == 0) {
                if (lbl_8066FB08 == __DSP_first_task) {
                    DSPSendMailToDSP(0xCDD10003);
                    while (DSPCheckMailToDSP() != 0)
                        ;
                    if (lbl_8066FB08->res_cb != 0)
                        lbl_8066FB08->res_cb(lbl_8066FB08);
                } else {
                    DSPSendMailToDSP(0xCDD10001);
                    while (DSPCheckMailToDSP() != 0)
                        ;
                    __DSP_exec_task(lbl_8066FB08, __DSP_first_task);
                    lbl_8066FB08->state = 2;
                    lbl_8066FB08 = __DSP_first_task;
                }
            } else {
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP() != 0)
                    ;
                __DSP_exec_task(lbl_8066FB08, lbl_8066FB08->next);
                lbl_8066FB08->state = 2;
                lbl_8066FB08 = lbl_8066FB08->next;
            }
        }
        break;
    case 0xDCD10003:
        if (lbl_8066FAF4) {
            if (lbl_8066FB08->done_cb != 0)
                lbl_8066FB08->done_cb(lbl_8066FB08);
            DSPSendMailToDSP(0xCDD10001);
            while (DSPCheckMailToDSP() != 0)
                ;
            __DSP_exec_task(0, lbl_8066FAF8);
            __DSP_remove_task(lbl_8066FB08);
            lbl_8066FB08 = lbl_8066FAF8;
            lbl_8066FAF8 = 0;
            lbl_8066FAF4 = 0;
        } else {
            if (lbl_8066FB08->next == 0) {
                if (lbl_8066FB08 == __DSP_first_task) {
                    if (lbl_8066FB08->done_cb != 0)
                        lbl_8066FB08->done_cb(lbl_8066FB08);
                    DSPSendMailToDSP(0xCDD10002);
                    while (DSPCheckMailToDSP() != 0)
                        ;
                    lbl_8066FB08->state = 3;
                    __DSP_remove_task(lbl_8066FB08);
                } else {
                    if (lbl_8066FB08->done_cb != 0)
                        lbl_8066FB08->done_cb(lbl_8066FB08);
                    DSPSendMailToDSP(0xCDD10001);
                    while (DSPCheckMailToDSP() != 0)
                        ;
                    lbl_8066FB08->state = 3;
                    __DSP_exec_task(0, __DSP_first_task);
                    lbl_8066FB08 = __DSP_first_task;
                    __DSP_remove_task(lbl_8066FB00);
                }
            } else {
                if (lbl_8066FB08->done_cb != 0)
                    lbl_8066FB08->done_cb(lbl_8066FB08);
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP() != 0)
                    ;
                lbl_8066FB08->state = 3;
                __DSP_exec_task(0, lbl_8066FB08->next);
                lbl_8066FB08 = lbl_8066FB08->next;
                __DSP_remove_task(lbl_8066FB08->prev);
            }
        }
        break;
    case 0xDCD10004:
        if (lbl_8066FB08->req_cb != 0)
            lbl_8066FB08->req_cb(lbl_8066FB08);
        break;
    }

    OSClearContext((OSContext*)ctx);
    OSSetCurrentContext(context);
}
