typedef struct OSModuleQueue {
    void* head;
    void* tail;
} OSModuleQueue;

OSModuleQueue __OSModuleInfoList : 0x800030C8;
void* __OSStringTable : 0x800030D0;

void __OSModuleInit(void)
{
    __OSModuleInfoList.tail = 0;
    __OSModuleInfoList.head = 0;
    __OSStringTable = 0;
}
