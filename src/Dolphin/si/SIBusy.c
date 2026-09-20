typedef int BOOL;

typedef struct SIControl {
    long chan;
    unsigned int poll;
    unsigned int inputBytes;
    void* input;
    void* callback;
} SIControl;

extern SIControl Si;

BOOL SIBusy(void) {
    return (Si.chan != -1) ? 1 : 0;
}
