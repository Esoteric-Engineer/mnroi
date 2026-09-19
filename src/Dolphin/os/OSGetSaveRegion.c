extern void* SaveStart;
extern void* SaveEnd;

void OSGetSaveRegion(void** start, void** end)
{
    *start = SaveStart;
    *end = SaveEnd;
}
