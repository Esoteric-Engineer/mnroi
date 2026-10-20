// c:/Clash/mainline/Code/Game/handlers/venuetable.cpp, from clashVenue_ChooseOption (0x8010C090); see Game/handlers/venuetable.cpp.

// 0x4C-byte string; String(const char *) (0x804493A0) builds one from a literal.
class String {
public:
    char data[0x4C];
    String(const char *s) __asm__("__6StringPCc");
};

extern "C" {
int fn_80128E98(const char *fmt, ...);
void *fn_804332C4(void *table, int index);
const char *fn_8044D328(void *venue);
int fn_80442E7C(void *venue);
const char *fn_804426AC(void *venue);
void fn_8008856C(void *table, int index, int a);
char *strncpy(char *dst, const char *src, int n);
void fn_8012D400(int a);
void fn_80432AF8(void *level);
int fn_80431D84(void *table);
}

struct GameState {
    char unk0[0x5FB];
    char venueNameEnd; // +0x5FB
    char unk5FC[0x160];
    int timerMode; // +0x75C
};
extern GameState lbl_80552110;
extern char lbl_8052F060[]; // level object
extern char lbl_805526EC[]; // G+0x5DC, the venue name buffer
extern char lbl_8054EF38[]; // name table
extern char lbl_80491F04[]; // "clashVenue_ChooseOption( %d )"
extern char lbl_80491F24[]; // "dflt"
extern char lbl_80491F2C[]; // "--INVALID--"

// Emits no code. A top-level `return <parameter>;` makes cc1plus drop the function-end branch pair for every later function in the unit.
inline int sn_return_decl(int a) { return a; }

void clashVenue_ChooseOption(int option)
{
    void *venue;
    const char *name;
    int id;

    fn_80128E98(lbl_80491F04, option);
    venue = 0;
    venue = fn_804332C4(lbl_8054EF38, option - 1);
    if (venue) {
        name = fn_8044D328(venue);
        id = fn_80442E7C(venue);
        fn_8008856C(lbl_8054EF38, id, 0);
        fn_80128E98(lbl_80491F04, option);
        lbl_80552110.timerMode = 2;
        strncpy(lbl_805526EC, fn_804426AC(venue), 0x20);
        lbl_80552110.venueNameEnd = 0;
        fn_8012D400(0);
        fn_80432AF8(lbl_8052F060);
    }
}

int clashVenue_GetNumOptions()
{
    return fn_80431D84(lbl_8054EF38);
}

String clashVenue_GetOptionBitmap(int option)
{
    void *venue = 0;
    const char *name;

    venue = fn_804332C4(lbl_8054EF38, option - 1);
    if (venue) {
        name = fn_8044D328(venue);
        return String(name);
    }
    return String(lbl_80491F24);
}

String clashVenue_GetOptionText(int option)
{
    void *venue = 0;
    const char *name;

    venue = fn_804332C4(lbl_8054EF38, option - 1);
    if (venue) {
        name = fn_804426AC(venue);
        return String(name);
    }
    return String(lbl_80491F2C);
}
