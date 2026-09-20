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

#define ROUNDUP(x, a) (((unsigned long)(x) + (a)-1) & ~((a)-1))

void* OSAllocFromArenaLo(unsigned long size, unsigned long align)
{
    void* ptr;
    unsigned char* arenaLo;
    arenaLo = __OSArenaLo;
    ptr = (void*)ROUNDUP(arenaLo, align);
    arenaLo = (unsigned char*)ptr + size;
    arenaLo = (unsigned char*)ROUNDUP(arenaLo, align);
    __OSArenaLo = arenaLo;
    return ptr;
}
