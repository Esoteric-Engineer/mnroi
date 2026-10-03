// c:/Clash/mainline/Code/Game/handlers/characterselect.cpp
//
// Built at -O0. The whole file is 0x801037B0-0x801040F4, three handlers (docs/versus.md).
// NonMatching: two extra unreachable branches at the end, from the C++ by-value return that no bundled ProDG release reproduces.

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
