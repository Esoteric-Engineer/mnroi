typedef unsigned char u8;
typedef long s32;
typedef unsigned long u32;

typedef struct DSPTaskInfo {
    u32 pad[0x50 / 4];
} DSPTaskInfo;

typedef struct CARDControl {
    u8 pad0[0x30];
    DSPTaskInfo task;
    void* workArea;
    u8 pad1[0x110 - 0x84];
} CARDControl;

extern CARDControl __CARDBlock[2];

extern void DSPSendMailToDSP(u32 mail);
extern u32 DSPCheckMailToDSP(void);

void InitCallback(void* _task)
{
    s32 chan;
    CARDControl* card;
    DSPTaskInfo* task;
    void* param;

    task = _task;
    for (chan = 0; chan < 2; ++chan) {
        card = &__CARDBlock[chan];
        if ((DSPTaskInfo*)&card->task == task)
            break;
    }

    param = card->workArea;

    DSPSendMailToDSP(0xFF000000);
    while (DSPCheckMailToDSP())
        ;

    DSPSendMailToDSP((u32)param);
    while (DSPCheckMailToDSP())
        ;
}
