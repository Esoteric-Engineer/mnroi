extern void* __OSArenaHi;
extern void* __OSArenaLo;

void* OSGetArenaHi(void)
{
    return __OSArenaHi;
}

void* OSGetArenaLo(void)
{
    return __OSArenaLo;
}

void OSSetArenaHi(void* hi)
{
    __OSArenaHi = hi;
}

void OSSetArenaLo(void* lo)
{
    __OSArenaLo = lo;
}
