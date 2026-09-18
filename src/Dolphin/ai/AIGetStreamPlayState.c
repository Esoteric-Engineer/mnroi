int AIGetStreamPlayState(void)
{
    return *(unsigned int*)0xCC006C00 & 1;
}
