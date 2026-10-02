void* __CARDGetDirBlock(char* card)
{
    return *(void**)(card + 0x84);
}
