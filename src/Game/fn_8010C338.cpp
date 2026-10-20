// c:/Clash/mainline/Code/Game/handlers/venuetable.cpp: the static initializer (0x8010C338), which sets the four screen-edge floats and registers the six handlers (docs/versus.md section 1).
//
// Hand-written like Game/fn_8010611C.cpp (matching_notes.md); the registration objects are empty classes in the original.

class String {
public:
    char data[0x4C];
    ~String();
};

class AptObject {
public:
    ~AptObject();
    void *unk0;
    int unk4;
};

AptObject clashVenue_GetVenueList();
void clashVenue_StartLevel(String name);
void clashVenue_ChooseOption(int option);
int clashVenue_GetNumOptions();
String clashVenue_GetOptionBitmap(int option);
String clashVenue_GetOptionText(int option);

extern "C" {
void *fn_8044AF58(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044BBC8(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044BF9C(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044C35C(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044EE3C(void *reg, const char *name, void *func, const char *file, int line);
}

extern float lbl_8066BB5C; // sdata
extern float lbl_8066BB60; // sdata

// Literals still owned by the auto-generated .rodata.
extern char lbl_80491F60[]; // this file's path
extern char lbl_80491F48[]; // "clashVenue_GetVenueList"
extern char lbl_80491F94[]; // "clashVenue_StartLevel"
extern char lbl_80491FAC[]; // "clashVenue_ChooseOption"
extern char lbl_80491FC4[]; // "clashVenue_GetNumOptions"
extern char lbl_80491FE0[]; // "clashVenue_GetOptionBitmap"
extern char lbl_80491FFC[]; // "clashVenue_GetOptionText"

// Emits no code. A top-level `return <parameter>;` makes cc1plus drop the function-end branch pair for every later function in the unit.
inline int sn_return_decl(int a) { return a; }

static float sVenueScreenLeft;
static float sVenueScreenRight;
static float sVenueScreenTop;
static float sVenueScreenBottom;

static char sReg_clashVenue_GetVenueList;
static char sReg_clashVenue_StartLevel;
static char sReg_clashVenue_ChooseOption;
static char sReg_clashVenue_GetNumOptions;
static char sReg_clashVenue_GetOptionBitmap;
static char sReg_clashVenue_GetOptionText;

// 65535 is GCC 2.95's default init priority.
void VenueStaticInit(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            sVenueScreenLeft = 320.0f - lbl_8066BB5C * 0.5f;
            sVenueScreenRight = sVenueScreenLeft + lbl_8066BB5C * 0.5f;
            sVenueScreenTop = 240.0f - lbl_8066BB60 * 0.5f;
            sVenueScreenBottom = lbl_8066BB60 * 0.5f + sVenueScreenTop - 12.0f;
            fn_8044AF58(&sReg_clashVenue_GetVenueList, lbl_80491F48, (void *)clashVenue_GetVenueList, lbl_80491F60, 45);
            fn_8044BF9C(&sReg_clashVenue_StartLevel, lbl_80491F94, (void *)clashVenue_StartLevel, lbl_80491F60, 64);
            fn_8044C35C(&sReg_clashVenue_ChooseOption, lbl_80491FAC, (void *)clashVenue_ChooseOption, lbl_80491F60, 97);
            fn_8044BBC8(&sReg_clashVenue_GetNumOptions, lbl_80491FC4, (void *)clashVenue_GetNumOptions, lbl_80491F60, 104);
            fn_8044EE3C(&sReg_clashVenue_GetOptionBitmap, lbl_80491FE0, (void *)clashVenue_GetOptionBitmap, lbl_80491F60, 122);
            fn_8044EE3C(&sReg_clashVenue_GetOptionText, lbl_80491FFC, (void *)clashVenue_GetOptionText, lbl_80491F60, 140);
        } else {
        }
    }
}

void fn_8010C4EC(void)
{
    VenueStaticInit(1, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_8010C4EC;
