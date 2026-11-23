// The global clock's millisecond time and elapsed time (docs/core.md row 19).

extern "C" long long OSGetTime(void);

inline int sn_return_decl(int a) { return a; }

struct LowMem
{
    char unk0[0xF8];
    unsigned int busClock; // +0xF8
};

extern "C" int fn_8042D324(register void *self)
{
    return OSGetTime() / (((LowMem *)0x80000000)->busClock / 4 / 1000);
}

extern "C" int fn_8042D3B0(register void *self, register int since)
{
    return OSGetTime() / (((LowMem *)0x80000000)->busClock / 4 / 1000) - since;
}
