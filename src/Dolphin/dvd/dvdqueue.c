typedef unsigned int u32;

typedef struct DVDQueue
{
    struct DVDQueue* next;
    struct DVDQueue* prev;
} DVDQueue;

int OSDisableInterrupts(void);
void OSRestoreInterrupts(int level);

DVDQueue WaitingQueue[4];

void __DVDClearWaitingQueue(void)
{
    u32 i;
    DVDQueue* q;

    for (i = 0; i < 4; i++)
    {
        q = &WaitingQueue[i];
        q->next = q;
        q->prev = q;
    }
}

int __DVDPushWaitingQueue(long prio, DVDQueue* block)
{
    int enabled = OSDisableInterrupts();
    DVDQueue* q = &WaitingQueue[prio];

    q->prev->next = block;
    block->prev = q->prev;
    block->next = q;
    q->prev = block;
    OSRestoreInterrupts(enabled);
    return 1;
}

DVDQueue* __DVDPopWaitingQueue(void)
{
    u32 i;
    int enabled;
    DVDQueue* q;

    enabled = OSDisableInterrupts();
    for (i = 0; i < 4; i++)
    {
        q = &WaitingQueue[i];
        if (q->next != q)
        {
            DVDQueue* tmp;
            OSRestoreInterrupts(enabled);
            enabled = OSDisableInterrupts();
            q = &WaitingQueue[i];
            tmp = q->next;
            q->next = tmp->next;
            tmp->next->prev = q;
            OSRestoreInterrupts(enabled);
            tmp->next = 0;
            tmp->prev = 0;
            return tmp;
        }
    }
    OSRestoreInterrupts(enabled);
    return 0;
}

int __DVDCheckWaitingQueue(void)
{
    u32 i;
    int enabled;
    DVDQueue* q;

    enabled = OSDisableInterrupts();
    for (i = 0; i < 4; i++)
    {
        q = &WaitingQueue[i];
        if (q->next != q)
        {
            OSRestoreInterrupts(enabled);
            return 1;
        }
    }
    OSRestoreInterrupts(enabled);
    return 0;
}

int __DVDDequeueWaitingQueue(DVDQueue* block)
{
    int enabled = OSDisableInterrupts();
    DVDQueue* prev = block->prev;
    DVDQueue* next = block->next;

    if (prev == 0 || next == 0)
    {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    prev->next = next;
    next->prev = prev;
    OSRestoreInterrupts(enabled);
    return 1;
}

// DVDDumpWaitingQueue's command-name table; dead-stripped (the function itself is unreferenced).
#pragma force_active on
char lbl_8066C430[4] = "";
char lbl_8066C434[5] = "READ";
char lbl_8066C43C[5] = "SEEK";
char lbl_804D22B0[12] = "CHANGE_DISK";
char lbl_8066C444[7] = "BSREAD";
char lbl_8066C44C[7] = "READID";
char lbl_804D22BC[11] = "INITSTREAM";
char lbl_804D22C8[13] = "CANCELSTREAM";
char lbl_804D22D8[19] = "STOP_STREAM_AT_END";
char lbl_804D22EC[20] = "REQUEST_AUDIO_ERROR";
char lbl_804D2300[18] = "REQUEST_PLAY_ADDR";
char lbl_804D2314[19] = "REQUEST_START_ADDR";
char lbl_804D2328[15] = "REQUEST_LENGTH";
char lbl_804D2338[20] = "AUDIO_BUFFER_CONFIG";
char lbl_8066C454[8] = "INQUIRY";
char lbl_804D234C[15] = "BS_CHANGE_DISK";

char* DVDCommandNames[16] = {
    lbl_8066C430, lbl_8066C434, lbl_8066C43C, lbl_804D22B0,
    lbl_8066C444, lbl_8066C44C, lbl_804D22BC, lbl_804D22C8,
    lbl_804D22D8, lbl_804D22EC, lbl_804D2300, lbl_804D2314,
    lbl_804D2328, lbl_804D2338, lbl_8066C454, lbl_804D234C,
};

// DVDDumpWaitingQueue's own OSReport format strings; same dead-stripped status.
char lbl_804D239C[36] = "==== DVD Waiting Queue Status ====\n";
char lbl_804D23C0[15] = "< Queue #%d > ";
char lbl_8066C45C[6] = "None\n";
char lbl_8066C464[2] = "\n";
char lbl_804D23D0[21] = "0x%08x: Command: %s ";
char lbl_804D23E8[43] = "Disk offset: %d, Length: %d, Addr: 0x%08x\n";
#pragma force_active reset
