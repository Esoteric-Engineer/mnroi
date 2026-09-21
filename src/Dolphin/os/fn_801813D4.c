#pragma peephole off

extern void (*lbl_804DCD84[])(void);
extern void (*lbl_804DCD8C[])(void);
extern void _ExitProcess(void);

void fn_801813F4(void);

void fn_801813D4(void)
{
    fn_801813F4();
}

void fn_801813F4(void)
{
    void (**p)(void) = lbl_804DCD84;
    while (*p != 0) {
        (*p)();
        p++;
    }
}

static inline void runList(void (**list)(void))
{
    void (**p)(void) = list;
    while (*p != 0) {
        (*p)();
        p++;
    }
}

void fn_80181448(void)
{
    void (**p)(void) = lbl_804DCD8C;
    runList(p);
    _ExitProcess();
    (void)p;
}
