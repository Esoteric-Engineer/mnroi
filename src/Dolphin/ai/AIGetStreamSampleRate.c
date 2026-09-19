unsigned int AIGetStreamSampleRate(void)
{
    return (*(unsigned int*)0xCC006C00 >> 1) & 1;
}
