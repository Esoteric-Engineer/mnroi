typedef unsigned long u32;

struct HeapDesc {
    long size;
    void* free;
    void* allocated;
};

extern struct HeapDesc* HeapArray;
extern int NumHeaps;
extern void* ArenaStart;
extern void* ArenaEnd;
extern int __OSCurrHeap;

void* OSInitAlloc(void* arenaStart, void* arenaEnd, int maxHeaps)
{
    unsigned long arraySize;
    int i;
    struct HeapDesc* hd;

    arraySize = maxHeaps * sizeof(struct HeapDesc);
    HeapArray = arenaStart;
    NumHeaps = maxHeaps;

    for (i = 0; i < NumHeaps; i++) {
        hd = &HeapArray[i];
        hd->size = -1;
        hd->free = hd->allocated = 0;
    }
    __OSCurrHeap = -1;
    arenaStart = (void*)((u32)((char*)HeapArray + arraySize));
    arenaStart = (void*)(((u32)arenaStart + 0x1F) & 0xFFFFFFE0);
    ArenaStart = arenaStart;
    ArenaEnd = (void*)((u32)arenaEnd & 0xFFFFFFE0);
    return arenaStart;
}
