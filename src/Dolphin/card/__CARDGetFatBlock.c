void* __CARDGetFatBlock(char* card)
{
    return *(void**)(card + 0x88);
}
