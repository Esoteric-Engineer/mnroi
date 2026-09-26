typedef unsigned long u32;
typedef unsigned char u8;

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

static struct Cell* DLAddFront(struct Cell* list, struct Cell* cell)
{
    cell->next = list;
    cell->prev = 0;
    if (list) {
        list->prev = cell;
    }
    return cell;
}

static struct Cell* DLExtract(struct Cell* list, struct Cell* cell)
{
    if (cell->next) {
        cell->next->prev = cell->prev;
    }
    if (cell->prev == 0) {
        return cell->next;
    }
    cell->prev->next = cell->next;
    return list;
}

void* OSAllocFromHeap(int heap, unsigned long size)
{
    struct HeapDesc* hd;
    struct Cell* cell;
    struct Cell* newCell;
    long leftoverSize;

    hd = &HeapArray[heap];
    size += 0x20;
    size = (size + 0x1F) & 0xFFFFFFE0;

    for (cell = hd->free; cell != 0; cell = cell->next) {
        if ((signed)size <= (signed)cell->size) {
            break;
        }
    }

    if (cell == 0) {
        return 0;
    }

    leftoverSize = cell->size - size;
    if (leftoverSize < 0x40U) {
        hd->free = DLExtract(hd->free, cell);
    } else {
        cell->size = size;
        newCell = (void*)((u8*)cell + size);
        newCell->size = leftoverSize;
        newCell->prev = cell->prev;
        newCell->next = cell->next;
        if (newCell->next != 0) {
            newCell->next->prev = newCell;
        }
        if (newCell->prev != 0) {
            newCell->prev->next = newCell;
        } else {
            hd->free = newCell;
        }
    }

    hd->allocated = DLAddFront(hd->allocated, cell);
    return (u8*)cell + 0x20;
}
