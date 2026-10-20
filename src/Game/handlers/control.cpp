// c:/Clash/mainline/Code/Game/handlers/control.cpp
//
// Built at -O0; the first twelve handlers (0x801040F4-0x801044B0). Control_ChangeScreen, which takes a String by value, is Game/fn_801044B0.cpp, and the file continues in Game/fn_80104504.cpp.

// 0x4C-byte string; String(const char *) (0x804493A0) builds one from a literal.
class String {
public:
    char data[0x4C];
    String(const char *s) __asm__("__6StringPCc");
};

extern "C" {
int fn_8043A71C(void *self);
int fn_8044D74C(void *self);
int fn_8044D778(void *self);
int fn_8044D7F8(void *self);
}

extern char lbl_80552920[]; // GameFlow instance
extern char lbl_8057E430[];
extern const char *lbl_804CD318[];
extern char lbl_80490460[]; // "0"
extern char lbl_80490464[]; // "1"
extern char lbl_8049051C[]; // "none"
extern char lbl_80490524[]; // "NGC"

// Emits no code. A top-level `return <parameter>;` makes cc1plus drop the function-end branch pair for every later function in the unit.
inline int sn_return_decl(int a) { return a; }

int gPALMode()
{
    if (fn_8043A71C(lbl_8057E430)) {
        return 1;
    }
    return 0;
}

int gWidescreenMode()
{
    return 0;
}

int gDemoLaunchInto()
{
    return fn_8044D778(lbl_80552920);
}

String gDebugEnable()
{
    return String(lbl_80490460);
}

int gArtistBuild()
{
    if (fn_8044D74C(lbl_80552920) > 3) {
        return fn_8044D74C(lbl_80552920) - 3;
    }
    return 0;
}

int gFranchise()
{
    return fn_8044D74C(lbl_80552920) == 1;
}

int gE3Demo()
{
    return fn_8044D74C(lbl_80552920) == 2;
}

int gMagazineDemo()
{
    return fn_8044D74C(lbl_80552920) == 3;
}

int gIsOnline()
{
    return 0;
}

String gInGame()
{
    return String(lbl_80490464);
}

String gBEDisplayScreen()
{
    int screen = fn_8044D7F8(lbl_80552920);
    return String(lbl_804CD318[screen]);
    return String(lbl_8049051C);
}

String gPlatform()
{
    return String(lbl_80490524);
    return String(lbl_80490460);
}
