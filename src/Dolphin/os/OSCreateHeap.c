typedef unsigned long u32;

struct Cell {
    struct Cell* prev;
    struct Cell* next;
    long size;
};

struct HeapDesc {
    long size;
    struct Cell* free;
    struct Cell* allocated;
};

extern struct HeapDesc* HeapArray;
extern int NumHeaps;

int OSCreateHeap(void* start, void* end)
{
    int heap;
    struct HeapDesc* hd;
    struct Cell* cell;

    start = (void*)(((u32)start + 0x1FU) & ~((32) - 1));
    end = (void*)(((u32)end) & ~((32) - 1));

    for (heap = 0; heap < NumHeaps; heap++) {
        hd = &HeapArray[heap];
        if (hd->size < 0) {
            hd->size = (u32)end - (u32)start;
            cell = start;
            cell->prev = 0;
            cell->next = 0;
            cell->size = hd->size;
            hd->free = cell;
            hd->allocated = 0;
            return heap;
        }
    }
    return -1;
}
