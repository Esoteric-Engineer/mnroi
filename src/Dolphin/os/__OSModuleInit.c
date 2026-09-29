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

#pragma force_active on
char lbl_804D1258[] = "OSLink: unknown relocation type %3d\n";
char lbl_804D1280[] = "OSUnlink: unknown relocation type %3d\n";
#pragma force_active reset
