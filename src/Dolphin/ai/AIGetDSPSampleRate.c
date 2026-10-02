unsigned int AIGetDSPSampleRate(void)
{
    return ((*(unsigned int*)0xCC006C00 >> 6) & 1) ^ 1;
}
