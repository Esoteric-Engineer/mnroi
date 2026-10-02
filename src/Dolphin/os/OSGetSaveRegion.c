void* SaveEnd;
void* SaveStart;

void OSGetSaveRegion(void** start, void** end)
{
    *start = SaveStart;
    *end = SaveEnd;
}
