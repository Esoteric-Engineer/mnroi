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

inline static void __fini_cpp(void)
{
    void (**destructor)(void);
    for (destructor = lbl_804DCD8C; *destructor; destructor++) {
        (*destructor)();
    }
}

void fn_80181448(int status)
{
    __fini_cpp();
    _ExitProcess();
}
