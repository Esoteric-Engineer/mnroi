// c:/Clash/mainline/Code/Game/handlers/control.cpp, from Global_StopFEStream (0x8010513C); see Game/fn_80104E88.cpp.

// APT script variables, engine classes shared with the other handler files (see Game/handlers/characterselect.cpp).
class AptRef {
public:
    AptRef operator[](int index);
    void operator=(char *const &value);
    void operator=(const int &value);

private:
    void *object;
    char *name;
    int index;
};

class AptObject {
public:
    AptObject();                       // fn_8044B608
    AptObject(const AptObject &other); // fn_8044B568
    ~AptObject();                      // fn_8044B510
    AptRef operator[](const char *name);

private:
    void *unk0;
    int unk4;
};

// 0x2C-byte movie request; the class name is a guess.
class Movie {
public:
    Movie(); // fn_8043AB4C
    ~Movie(); // fn_8043ABD0

    int unk0, unk4, unk8, unkC;
    int id; // +0x10
    int unk14, unk18, unk1C, unk20, unk24;
    char unk28;
};

struct Table;
extern Table *lbl_8066C63C;
extern char lbl_80552920[]; // GameFlow instance

extern "C" {
void fn_8010FAE8();
void fn_801281D0();
void *fn_80427400();
int fn_8042D584(void *locale);
void fn_8044D824(void *flow, int on);
void fn_801AA570(int pad);
int fn_80433314(Table *table);
void fn_80131B54(int player, int pad);
void fn_8012D578(int pad, int ctrl);
void *fn_80432BC4();
void fn_80166654(void *x, void *movie);
void fn_80166D9C(void *x);
void fn_80166D6C(void *x);
void fn_80166C74(void *x);
void fn_804316B0(int a);
void fn_80431728(int a);
void fn_8044D490(int a);
void fn_8044D52C(int a);
void fn_8044D3F4(int a);
int fn_8044D3B8(int index);
int fn_8044D454(int index);
int fn_8044D4F0(int index);
void fn_8044D7A4(void *flow, int pauser);
void fn_800B7918(void *flow);
void SetCommand__8GameFlowi(void *self, int command);
void SetCommandBlocking__8GameFlowi(void *self, int command);
void *fn_8044D354(void *table);
int fn_80442E7C(void *obj);
void fn_8008856C(void *table, int index, int a);
void fn_8012D400(int a);
void *fn_8044D7CC(void *flow);
void fn_8044D84C(void *timer, int a);
void fn_80164828(void *timer);
void fn_8012D708(int on);
}
extern char lbl_8054ED80[]; // .nsc script table
extern char lbl_805723A4[];
extern char lbl_80571E04[];

extern char lbl_8049059C[]; // "aUnLock"


void Global_StopFEStream()
{
    fn_8010FAE8();
    fn_801281D0();
}

int Locale_GetLanguage()
{
    return fn_8042D584(fn_80427400());
}

void Control_EnableBackgroundDraw(int on)
{
    fn_8044D824(lbl_80552920, on);
}

// Emits no code. The original file got this from a constructor in a header that sits between Control_EnableBackgroundDraw and Control_StartScreenFunction.
inline int sn_return_decl(int a) { return a; }

AptObject Control_StartScreenFunction(int screen)
{
    AptObject list;

    if (screen == 0) {
        screen = 6;
    }
    return list;
}

int Control_GetControllerStatus(int pad)
{
    int result = 0;
    Table *saved;

    if (pad > 3 || pad < 0) {
        return 0;
    }

    saved = lbl_8066C63C;
    fn_801AA570((unsigned short)pad);
    if (fn_80433314(lbl_8066C63C)) {
        result = 1;
    }
    lbl_8066C63C = saved;
    return result;
}

void Control_BindController(int pad, int ctrl)
{
    fn_80131B54(ctrl, pad);
    fn_8012D578(pad, ctrl);
}

void Movie_Play(int id)
{
    Movie movie;
    char unused[0x38];

    movie.id = id;
    fn_80166654(fn_80432BC4(), &movie);
    fn_80166D9C(fn_80432BC4());
}

void Movie_Stop()
{
    fn_80166D6C(fn_80432BC4());
    fn_80166C74(fn_80432BC4());
}

void Cheat_UnlockAll()
{
    fn_804316B0(1);
    fn_80431728(1);
    fn_8044D490(1);
    fn_8044D52C(1);
    fn_8044D3F4(1);
}

AptObject Reward_GetTrailerInfo()
{
    AptObject list;
    int i;

    for (i = 0; i <= 8; i++) {
        list[lbl_8049059C][i] = fn_8044D3B8(i) == 1;
    }
    return list;
}

AptObject Reward_GetCardsInfo()
{
    AptObject list;
    int i;

    for (i = 0; i <= 0x2a; i++) {
        list[lbl_8049059C][i] = fn_8044D454(i) == 1;
    }
    return list;
}

int Reward_GetNumCards()
{
    int count = 0;
    int i;

    for (i = 0; i <= 0x2a; i++) {
        if (fn_8044D454(i) == 1) {
            count++;
        }
    }
    return count;
}

AptObject Reward_GetComicsInfo()
{
    AptObject list;
    int i;

    for (i = 0; i <= 0x18; i++) {
        list[lbl_8049059C][i] = fn_8044D4F0(i) == 1;
    }
    return list;
}

int Reward_GetNumComics()
{
    int count = 0;
    int i;

    for (i = 0; i <= 0x18; i++) {
        if (fn_8044D4F0(i) == 1) {
            count++;
        }
    }
    if (count > 0x12) {
        return 0x12;
    }
    return count;
}

void PauseMenu_SetSFXLevel(int level)
{
}

void PauseMenu_SetMusicLevel(int level)
{
}

void PauseMenu_SetSpeechLevel(int level)
{
}

void PauseMenu_ReturnToGame()
{
    SetCommand__8GameFlowi(lbl_80552920, 0x43);
    fn_8012D400(0);
}

void PauseMenu_Quit()
{
    SetCommandBlocking__8GameFlowi(lbl_80552920, 0x4a);
    fn_8012D400(0);
    fn_8008856C(lbl_8054ED80, fn_80442E7C(fn_8044D354(lbl_8054ED80)), 0);
}

void *PauseMenu_GetLastPauser()
{
    return fn_8044D7CC(lbl_80552920);
}

int PauseMenu_OnlineTimeLeft()
{
    return -1;
}

int PauseMenu_OnlineCount()
{
    return -1;
}

int PauseMenu_OnlineCountLimit()
{
    return -1;
}

void clashPauseMenu_Exit2Game()
{
    fn_800B7918(lbl_80552920);
}

void clashPauseMenu_SelectItem(int item, int pauser)
{
    fn_8044D7A4(lbl_80552920, pauser);
    switch (item) {
    case 0:
        SetCommand__8GameFlowi(lbl_80552920, 0x43);
        break;
    case 1:
        SetCommand__8GameFlowi(lbl_80552920, 0x46);
        break;
    case 2:
        SetCommandBlocking__8GameFlowi(lbl_80552920, 0x4a);
        break;
    case 3:
        SetCommand__8GameFlowi(lbl_80552920, 0x50);
        break;
    case 4:
        SetCommand__8GameFlowi(lbl_80552920, 0x51);
        break;
    case 5:
        SetCommand__8GameFlowi(lbl_80552920, 0x52);
        break;
    case 6:
        SetCommand__8GameFlowi(lbl_80552920, 0x55);
        break;
    case 7:
        SetCommand__8GameFlowi(lbl_80552920, 0x53);
        break;
    case 8:
        SetCommand__8GameFlowi(lbl_80552920, 0x54);
        break;
    }
    fn_8012D400(0);
}

void Timer_Delay(int ms)
{
    fn_8044D84C(lbl_805723A4, ms);
}

void Timer_Stop()
{
    fn_80164828(lbl_80571E04);
}

void AttractMode_Enable(int on)
{
    fn_8012D708(on);
}
