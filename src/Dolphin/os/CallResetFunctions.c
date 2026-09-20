typedef unsigned long u32;
typedef int BOOL;

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

extern struct OSResetFunctionQueue ResetFunctionQueue;
extern BOOL fn_8017F668(void);

BOOL CallResetFunctions(BOOL final)
{
    OSResetFunctionInfo* info;
    BOOL err = 0;
    u32 last = 0;

    for (info = ResetFunctionQueue.head; info; info = info->next) {
        if (err != 0 && last != info->priority) {
            break;
        }
        err |= !info->func(final);
        last = info->priority;
    }
    err |= !fn_8017F668();
    if (err) {
        return 0;
    }
    return 1;
}
