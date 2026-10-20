// c:/Clash/mainline/Code/Game/handlers/mainmenu.cpp
//
// Built at -O0; the whole file is 0x801070FC-0x80107244, docs/versus.md section 2.

extern "C" {
void fn_80435238(void *obj, int mode);

// Handler registration (APT script name, function, source file, line); the object is an empty class in the original.
void *fn_8044C35C(void *reg, const char *name, void *func, const char *file, int line);
}

extern char lbl_80572330[];

// Literals still owned by the auto-generated .rodata.
extern char lbl_80490EF0[]; // "clashMainMenu_MenuSelect"
extern char lbl_80490F0C[]; // this file's path

void clashMainMenu_MenuSelect(int selection)
{
    switch (selection) {
    case 0:
        fn_80435238(lbl_80572330, 2);
        break;
    case 1:
        fn_80435238(lbl_80572330, 1);
        break;
    case 2:
    case 3:
    case 4:
    default:
        break;
    }
}

// Emits no code. A top-level `return <parameter>;` makes cc1plus drop the function-end branch pair for every later function in the unit.
inline int sn_return_decl(int a) { return a; }

static char sReg_clashMainMenu_MenuSelect;

// 65535 is GCC 2.95's default init priority.
static void __static_initialization_and_destruction_0(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            fn_8044C35C(&sReg_clashMainMenu_MenuSelect, lbl_80490EF0, (void *)clashMainMenu_MenuSelect, lbl_80490F0C, 47);
        } else {
        }
    }
}

void fn_80107208(void)
{
    __static_initialization_and_destruction_0(1, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_80107208;
