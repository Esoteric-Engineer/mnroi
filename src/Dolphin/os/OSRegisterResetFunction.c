typedef unsigned long u32;
typedef unsigned char BOOL;

typedef BOOL (*OSResetFunction)(BOOL final);

typedef struct OSResetFunctionInfo OSResetFunctionInfo;
struct OSResetFunctionInfo {
    OSResetFunction func;
    u32 priority;
    OSResetFunctionInfo* next;
    OSResetFunctionInfo* prev;
};

struct OSResetFunctionQueue {
    OSResetFunctionInfo* head;
    OSResetFunctionInfo* tail;
};

u32 bootThisDol;
struct OSResetFunctionQueue ResetFunctionQueue;

void OSRegisterResetFunction(OSResetFunctionInfo* info)
{
    OSResetFunctionInfo* next;
    OSResetFunctionInfo* prev;

    for (next = ResetFunctionQueue.head; next && (next->priority <= info->priority); next = next->next)
        ;

    if (next == 0) {
        prev = ResetFunctionQueue.tail;
        if (prev == 0) {
            ResetFunctionQueue.head = info;
        } else {
            prev->next = info;
        }
        info->prev = prev;
        info->next = 0;
        ResetFunctionQueue.tail = info;
    } else {
        info->next = next;
        prev = next->prev;
        next->prev = info;
        info->prev = prev;
        if (prev == 0) {
            ResetFunctionQueue.head = info;
        } else {
            prev->next = info;
        }
    }
}
