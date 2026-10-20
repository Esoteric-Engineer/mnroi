// c:/Clash/mainline/Code/Game/handlers/characterselect.cpp
//
// Built at -O0; the whole file is 0x801037B0-0x801040F4, docs/versus.md section 5.
// The static initializer is hand-written (matching_notes.md) and owns the three handler-registration objects in .sbss.

// APT script variables, engine classes shared with the other handler files. The names are guesses; the layouts and the symbols come from the code.
class AptRef {
public:
    AptRef operator[](int index);              // fn_8044B5B0
    void operator=(char *const &value);        // fn_8044B694
    void operator=(const int &value);          // fn_8044B758

private:
    void *object; // +0x0
    char *name;   // +0x4 property
    int index;    // +0x8 element, -1 for the property itself
};

class AptObject {
public:
    AptObject();                               // fn_8044B608
    AptObject(const AptObject &other);         // fn_8044B568
    ~AptObject();                              // fn_8044B510
    AptRef operator[](const char *name);       // fn_80102E60

private:
    void *unk0; // +0x0
    int unk4;   // +0x4
};

// Roster fields (src/Game/fn_8044B1D4.c). The stats are s8, and `char` is what emits the call sites' `mr r0, r3`.
extern "C" {
char *fn_8044B1D4(int index, int remap, int alt); // hero name key
char fn_8044B234(int index, int remap, int alt);  // intel
char fn_8044B298(int index, int remap, int alt);  // strength
char fn_8044B2FC(int index, int remap, int alt);  // speed
char fn_8044B360(int index, int remap, int alt);  // durability
char fn_8044B3C4(int index, int remap, int alt);  // energy
char fn_8044B428(int index, int remap, int alt);  // skill
int fn_8044B48C(int index, int remap, int alt);   // unlocked

// Last-selection module (docs/versus.md 4.2).
int fn_80131800();
int fn_80131850();
int fn_801318A0();
int fn_801318F0();
int fn_80131974(int slot);
int fn_80131A34(int slot);
int fn_80131AF4(int slot);
int fn_80131BB4(int slot);
void fn_80131E1C(); // reset

// Handler registration (APT script name, function, source file, line); the objects are empty classes in the original.
void *fn_8044AF58(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044B11C(void *reg, const char *name, void *func, const char *file, int line);
}

// Literals still owned by the auto-generated .rodata.
extern char lbl_80490108[]; // "aHeroName"
extern char lbl_80490114[]; // "aIntel"
extern char lbl_8049011C[]; // "aStr"
extern char lbl_80490124[]; // "aSpd"
extern char lbl_8049012C[]; // "aDur"
extern char lbl_80490134[]; // "aEng"
extern char lbl_8049013C[]; // "aSkl"
extern char lbl_80490144[]; // "aIsUnLocked1"
extern char lbl_80490154[]; // "aIsUnLocked2"
extern char lbl_80490164[]; // "nCombatType"
extern char lbl_80490170[]; // "nMatchType"
extern char lbl_8049017C[]; // "nDiffLevel"
extern char lbl_80490188[]; // "nTimeLimit"
extern char lbl_80490194[]; // "nCharId0"
extern char lbl_804901A0[]; // "nCharId1"
extern char lbl_804901AC[]; // "nCharLive0"
extern char lbl_804901B8[]; // "nCharLive1"
extern char lbl_804901C4[]; // "nCusType0"
extern char lbl_804901D0[]; // "nCusType1"
extern char lbl_804901DC[]; // "nController0"
extern char lbl_804901EC[]; // "nController1"
extern char lbl_804901FC[]; // "bValid"
extern char lbl_80490218[]; // "clashCharSelect_GetCharList"
extern char lbl_80490234[]; // this file's path
extern char lbl_80490270[]; // "clashCharSelect_GetPrevCharList"
extern char lbl_80490290[]; // "clashCharSelect_ResetCharList"

// Emits no code. A top-level `return <parameter>;` makes cc1plus drop the function-end branch pair for every later function in the unit.
// The original file got that from a constructor or inline function in a header, which this stands in for.
inline int sn_return_decl(int a) { return a; }

AptObject clashCharSelect_GetCharList()
{
    AptObject list;
    int i;

    for (i = 1; i <= 18; i++) {
        list[lbl_80490108][i - 1] = fn_8044B1D4(i, 1, 0);
        list[lbl_80490114][i - 1] = fn_8044B234(i, 1, 0);
        list[lbl_8049011C][i - 1] = fn_8044B298(i, 1, 0);
        list[lbl_80490124][i - 1] = fn_8044B2FC(i, 1, 0);
        list[lbl_8049012C][i - 1] = fn_8044B360(i, 1, 0);
        list[lbl_80490134][i - 1] = fn_8044B3C4(i, 1, 0);
        list[lbl_8049013C][i - 1] = fn_8044B428(i, 1, 0);
        list[lbl_80490144][i - 1] = fn_8044B48C(i, 1, 0);
        list[lbl_80490154][i - 1] = fn_8044B48C(i, 1, 1);
    }

    return list;
}

AptObject clashCharSelect_GetPrevCharList()
{
    AptObject list;
    int valid = 1;
    int cur = -1;

    cur = fn_80131800();
    if (cur < 0) valid = 0;
    list[lbl_80490164] = cur;
    cur = fn_80131850();
    if (cur < 0) valid = 0;
    list[lbl_80490170] = cur;
    cur = fn_801318A0();
    if (cur < 0) valid = 0;
    list[lbl_8049017C] = cur;
    cur = fn_801318F0();
    if (cur < 0) valid = 0;
    list[lbl_80490188] = cur;
    cur = fn_80131974(0);
    if (cur < 0) valid = 0;
    list[lbl_80490194] = cur;
    cur = fn_80131974(1);
    if (cur < 0) valid = 0;
    list[lbl_804901A0] = cur;
    cur = fn_80131A34(0);
    if (cur < 0) valid = 0;
    list[lbl_804901AC] = cur;
    cur = fn_80131A34(1);
    if (cur < 0) valid = 0;
    list[lbl_804901B8] = cur;
    cur = fn_80131AF4(0);
    if (cur < 0) valid = 0;
    list[lbl_804901C4] = cur;
    cur = fn_80131AF4(1);
    if (cur < 0) valid = 0;
    list[lbl_804901D0] = cur;
    list[lbl_804901DC] = fn_80131BB4(0);
    list[lbl_804901EC] = fn_80131BB4(1);
    list[lbl_804901FC] = valid;

    return list;
}

void fn_80103FC4()
{
    fn_80131E1C();
}

static char sGetCharListReg;
static char sGetPrevCharListReg;
static short sResetCharListReg;

// 65535 is GCC 2.95's default init priority.
void __static_initialization_and_destruction_0(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            fn_8044AF58(&sGetCharListReg, lbl_80490218, (void *)clashCharSelect_GetCharList, lbl_80490234, 41);
            fn_8044AF58(&sGetPrevCharListReg, lbl_80490270, (void *)clashCharSelect_GetPrevCharList, lbl_80490234, 95);
            fn_8044B11C(&sResetCharListReg, lbl_80490290, (void *)fn_80103FC4, lbl_80490234, 100);
        } else {
        }
    }
}

void fn_801040B8(void)
{
    __static_initialization_and_destruction_0(1, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_801040B8;
