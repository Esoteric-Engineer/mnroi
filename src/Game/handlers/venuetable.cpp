// c:/Clash/mainline/Code/Game/handlers/venuetable.cpp
//
// Built at -O0; clashVenue_GetVenueList (0x8010BED8). The file's other handlers are in the Game/fn_8010*.cpp units.

// APT script variables, engine classes shared with the other handler files (see Game/handlers/characterselect.cpp).
class AptRef {
public:
    AptRef operator[](int index);              // fn_8044B5B0
    void operator=(char *const &value);        // fn_8044B694
    void operator=(const int &value);          // fn_8044B758
    void operator=(const unsigned int &value); // fn_8044F6BC

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

// Venue table, 0x44-byte entries at lbl_804CB14C: name at +0x20, unlocked flag at +0x40.
extern "C" {
char *fn_8044F19C(int index);
unsigned int fn_8044D5C4(int index);
}

extern char lbl_80491EE8[]; // "aVenueName"
extern char lbl_80491EF4[]; // "aVenueUnLock"

// Emits no code. A top-level `return <parameter>;` makes cc1plus drop the function-end branch pair for every later function in the unit.
inline int sn_return_decl(int a) { return a; }

AptObject clashVenue_GetVenueList()
{
    AptObject list;
    int i;

    for (i = 0; i <= 6; i++) {
        list[lbl_80491EE8][i] = fn_8044F19C(i);
        list[lbl_80491EF4][i] = fn_8044D5C4(i);
    }

    return list;
}
