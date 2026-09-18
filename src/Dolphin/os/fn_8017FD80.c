typedef unsigned short u16;

typedef struct OSThread
{
    unsigned char context[712];
    u16 state;
} OSThread;

int OSIsThreadTerminated(OSThread* thread)
{
    return (thread->state == 8 || thread->state == 0) ? 1 : 0;
}
