typedef unsigned long u32;

extern void* memset(void* dst, int c, u32 n);
extern u32 strlen(const char* s);
extern char* strcpy(char* dst, const char* src);

int PackArgs(void* addr, int argc, char* argv[])
{
    int numArgs;
    char* ptr;
    char** newArgv;
    u32 n;
    memset(addr, 0, 0x2000);
    if (argc == 0) {
        ((u32*)addr)[2] = 0;
    } else {
        numArgs = argc;
        ptr = (char*)addr + 0x2000;
        while (--argc >= 0) {
            ptr -= strlen(argv[argc]) + 1;
            strcpy(ptr, argv[argc]);
            argv[argc] = (char*)(ptr - (char*)addr);
        }

        newArgv = (char**)((char*)addr + ((ptr - (char*)addr) & ~3));
        newArgv -= numArgs + 1;
        for (n = 0; n < numArgs + 1; n++) {
            newArgv[n] = argv[n];
        }
        newArgv[-1] = (char*)numArgs;
        ((u32*)addr)[2] = (char*)(newArgv - 1) - (char*)addr;
    }
    return 1;
}
