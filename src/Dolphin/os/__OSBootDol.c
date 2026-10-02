#pragma peephole off
typedef unsigned long u32;

extern void OSGetSaveRegion(void** start, void** end);
extern int sprintf(char* s, const char* format, ...);
extern void* OSAllocFromArenaLo(u32 size, u32 align);
extern void __OSBootDolSimple(u32 doloffset, u32 restartCode, void* regionStart, void* regionEnd, int argsUseDefault, int argc, char** argv);

void __OSBootDol(u32 doloffset, u32 restartCode, const char** argv)
{
    char offsetString[16];
    void* regionStart;
    void* regionEnd;
    int i;
    int argc;
    char** newArgv;

    OSGetSaveRegion(&regionStart, &regionEnd);
    sprintf(offsetString, "%d", doloffset);

    argc = 0;
    if (argv) {
        while (argv[argc]) {
            argc++;
        }
    }
    argc++;

    newArgv = (char**)OSAllocFromArenaLo((argc + 1) * 4, 1);
    newArgv[0] = offsetString;
    for (i = 1; i < argc; i++) {
        newArgv[i] = (char*)argv[i - 1];
    }

    __OSBootDolSimple(-1, restartCode, regionStart, regionEnd, 0, argc, newArgv);
}
