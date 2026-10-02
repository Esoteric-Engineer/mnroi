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

void* ArenaEnd;
void* ArenaStart;
int NumHeaps;
struct HeapDesc* HeapArray;

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

// OSCheckHeap/OSDumpHeap's OSReport format strings; both functions are dead-stripped (unreferenced), so only their string literals survive in the original.
#pragma force_active on
char lbl_804DCE00[36] = "OSCheckHeap: Failed HeapArray in %d";
char lbl_804DCE24[55] = "OSCheckHeap: Failed 0 <= heap && heap < NumHeaps in %d";
char lbl_804DCE5C[40] = "OSCheckHeap: Failed 0 <= hd->size in %d";
char lbl_804DCE84[79] = "OSCheckHeap: Failed hd->allocated == NULL || hd->allocated->prev == NULL in %d";
char lbl_804DCED4[62] = "OSCheckHeap: Failed InRange(cell, ArenaStart, ArenaEnd) in %d";
char lbl_804DCF14[55] = "OSCheckHeap: Failed OFFSET(cell, ALIGNMENT) == 0 in %d";
char lbl_804DCF4C[73] = "OSCheckHeap: Failed cell->next == NULL || cell->next->prev == cell in %d";
char lbl_804DCF98[51] = "OSCheckHeap: Failed MINOBJSIZE <= cell->size in %d";
char lbl_804DCFCC[61] = "OSCheckHeap: Failed OFFSET(cell->size, ALIGNMENT) == 0 in %d";
char lbl_804DD00C[57] = "OSCheckHeap: Failed 0 < total && total <= hd->size in %d";
char lbl_804DD048[69] = "OSCheckHeap: Failed hd->free == NULL || hd->free->prev == NULL in %d";
char lbl_804DD090[95] = "OSCheckHeap: Failed cell->next == NULL || (char*) cell + cell->size < (char*) cell->next in %d";
char lbl_804DD0F0[44] = "OSCheckHeap: Failed total == hd->size in %d";
char lbl_804DD11C[18] = "\nOSDumpHeap(%d):\n";
char lbl_804DD130[18] = "--------Inactive\n";
char lbl_804DD144[26] = "addr\tsize\t\tend\tprev\tnext\n";
char lbl_804DD160[19] = "--------Allocated\n";
char lbl_804DD174[16] = "%x\t%d\t%x\t%x\t%x\n";
char lbl_804DD184[14] = "--------Free\n";
#pragma force_active reset
