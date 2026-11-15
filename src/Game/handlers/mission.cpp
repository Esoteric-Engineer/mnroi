// c:/Clash/mainline/Code/Game/handlers/mission.cpp
//
// Built at -O0; story-mode mission handlers, docs/story.md row 1.

class AptRef {
public:
    AptRef operator[](int index);       // fn_8044B5B0
    void operator=(char *const &value); // fn_8044B694
    void operator=(const int &value);   // fn_8044B758
    void operator=(const long &value) __asm__("fn_8044EB5C");
    // Names are ours (matching_notes.md).
    void SetLit5(char (&value)[5]) __asm__("fn_8044F238");
    void SetLit25(char (&value)[25]) __asm__("fn_8044F2FC");
    void SetLit1(char (&value)[1]) __asm__("fn_8044EC20");

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

class String {
public:
    char data[0x4C];
    String(const char *s) __asm__("__6StringPCc");
    ~String();
    const char *c_str() __asm__("fn_804496C8");
};

extern "C" {
int fn_80087C78(void *chron);
int fn_8042D444(void *chron);
void *fn_804326B4(void *chron);
char *fn_8044EEF4(void *obj);
char fn_8044F104(char *text);
void *fn_80088280(void *chron, int index);
void *fn_8008816C(void *chron, int index);
void *fn_80088374(void *chron, int index);
int fn_80442FC4(void *rec);
int fn_8044F070(int value, int search, int unused);
char *fn_804426AC(void *rec);
char *fn_8044E9A8(void *rec);
long fn_80442E7C(void *rec);
int fn_804432D8(void *rec);
int fn_8044EF70(void *chron);
int fn_8044EFA0(void *chron);
int fn_8044EFD0(void *chron);
int fn_80443338(void *rec);
int fn_80443368(void *rec);
int fn_804434E8(void *chron);
void *fn_80088078(void *chron);
void *fn_80087E40(void *chron);
void *fn_80087F40(void *chron);
void fn_8008856C(void *chron, int index, int flag);
}

extern char lbl_8054ED80[]; // chronicle

// Literals still owned by the auto-generated .rodata.
extern char lbl_80491A70[]; // ""
extern char lbl_80491A8C[]; // "bMissionSacrifice"
extern char lbl_80491AA0[]; // "sLastMission"
extern char lbl_80491AB0[]; // "aMissionName"
extern char lbl_80491AC0[]; // "NONE"
extern char lbl_80491AC8[]; // "aMissionDesc"
extern char lbl_80491AD8[]; // "aMissionCharId"
extern char lbl_80491AE8[]; // "aMissionCharDone"
extern char lbl_80491AFC[]; // "aMissionSid"
extern char lbl_80491B08[]; // "aMissionPid"
extern char lbl_80491B14[]; // "~kT_ALLMISSIONSCOMPLETED"
extern char lbl_80491B30[]; // "pid"
extern char lbl_80491B34[]; // "sid"
extern char lbl_80491B38[]; // "charId"
extern char lbl_80491B40[]; // "missionName"
extern char lbl_80491B4C[]; // "bFlag"

// Emits no code; clears the function-end branch pair for later functions (docs/prodg.md).
inline int sn_return_decl(int a) { return a; }

AptObject clashMission_GetMissionList()
{
    AptObject list;
    unsigned total = fn_80087C78(lbl_8054ED80);
    int row = 0;

    list[lbl_80491A8C] = fn_8042D444(lbl_8054ED80) != 0;
    void *cur = fn_804326B4(lbl_8054ED80);
    int last = fn_8044F104(fn_8044EEF4(cur));
    list[lbl_80491AA0] = last;

    for (int i = 0; i <= 3; i++) {
        void *rec = fn_80088280(lbl_8054ED80, i);
        list[lbl_80491AB0][i].SetLit5(*(char (*)[5])lbl_80491AC0);
        list[lbl_80491AC8][i].SetLit5(*(char (*)[5])lbl_80491AC0);
        list[lbl_80491AD8][i] = -1;
        list[lbl_80491AE8][i] = 1;
        list[lbl_80491AFC][i] = -1;
        list[lbl_80491B08][i] = -1;
        void *scripted = 0;
        if (fn_8042D444(lbl_8054ED80)) {
            scripted = fn_80088374(lbl_8054ED80, i);
        } else {
            scripted = fn_8008816C(lbl_8054ED80, i);
        }
        if (scripted) {
            int k = fn_8044F070(fn_80442FC4(scripted), 1, 0) - 1;
            if (k >= 0 && k <= 20) {
                list[lbl_80491AD8][row] = fn_8044F070(fn_80442FC4(scripted), 1, 0) - 1;
                list[lbl_80491AB0][row] = fn_804426AC(scripted);
                list[lbl_80491AC8][row] = fn_8044E9A8(scripted);
                list[lbl_80491AE8][row] = 0;
                list[lbl_80491AFC][row] = i;
                list[lbl_80491B08][row] = fn_80442E7C(scripted);
            }
            row++;
        } else if (rec) {
            list[lbl_80491AB0][row].SetLit25(*(char (*)[25])lbl_80491B14);
            list[lbl_80491AC8][row].SetLit1(*(char (*)[1])lbl_80491A70);
            list[lbl_80491AD8][row] = fn_8044F070(fn_80442FC4(rec), 1, 0) - 1;
            list[lbl_80491AE8][row] = fn_804432D8(rec) != 0;
            row++;
        }
    }

    return list;
}

AptObject clashMission_SetUpSpecialMission()
{
    AptObject info;
    void *rec = fn_804326B4(lbl_8054ED80);
    int special = (fn_8044EFD0(lbl_8054ED80) || fn_8044EFA0(lbl_8054ED80) || fn_8044EF70(lbl_8054ED80) || fn_804434E8(lbl_8054ED80)
        || (!fn_804432D8(rec) && (fn_80443338(rec) || fn_80443368(rec)))) ? 1 : 0;

    if (special && !fn_8042D444(lbl_8054ED80)) {
        void *mid = 0;
        if (fn_804434E8(lbl_8054ED80) || fn_8044EFD0(lbl_8054ED80)) {
            mid = fn_80088078(lbl_8054ED80);
        } else if (fn_80443338(rec) || fn_80443368(rec)) {
            mid = rec;
        } else if (fn_8044EFA0(lbl_8054ED80)) {
            mid = fn_80087E40(lbl_8054ED80);
        } else {
            mid = fn_80087F40(lbl_8054ED80);
        }
        fn_8008856C(lbl_8054ED80, fn_80442E7C(mid), 0);
        info[lbl_80491B30] = fn_80442E7C(mid);
        info[lbl_80491B34] = 0;
        info[lbl_80491B38] = fn_8044F070(fn_80442FC4(mid), 1, 0) - 1;
        info[lbl_80491B40] = fn_804426AC(mid);
        info[lbl_80491B4C] = special;
    } else {
        info[lbl_80491B34] = 0;
        info[lbl_80491B38] = 0;
        info[lbl_80491B40].SetLit5(*(char (*)[5])lbl_80491AC0);
        info[lbl_80491B4C] = 0;
    }

    return info;
}

extern "C" {
void fn_8012D400(int a);
int fn_8011CA74();
void fn_8011ED0C(int a);
void fn_8011ED50(int a);
void fn_80432AF8(void *level);
void fn_8002D9C4(void *level);
void fn_800876D4(void *chron);
int fn_8044EF20(void *chron);
void *fn_804332C4(void *chron, int index);
int fn_80443458(void *rec);
int fn_80443488(void *rec);
int fn_804433C8(void *rec);
int fn_80433E08(void *rec);
int fn_804433F8(void *rec);
void fn_80087938(void *chron, long id);
}

extern char lbl_8052F060[]; // level object

void clashMission_Start()
{
    fn_8012D400(0);
    fn_8011ED0C(fn_8011CA74());
    fn_80432AF8(lbl_8052F060);
}

int Mission_GetCharId()
{
    void *rec = fn_804326B4(lbl_8054ED80);
    return fn_8044F070(fn_80442FC4(rec), 1, 0) - 1;
}

void clashMission_StartNewGame()
{
    fn_800876D4(lbl_8054ED80);
    fn_8012D400(0);
    fn_8011ED0C(fn_8011CA74());
    fn_80432AF8(lbl_8052F060);
}

int clashMission_IsFirstTimeIn()
{
    register int r __asm__("r0");
    if (fn_8044EF20(lbl_8054ED80)) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}

int clashMission_IsBack2MissionAllow()
{
    void *cur = fn_804326B4(lbl_8054ED80);
    void *first = fn_804332C4(lbl_8054ED80, 0);
    if (cur == first) {
        return 0;
    }
    if (fn_80443338(cur) || fn_80443368(cur) || fn_80443458(cur) || fn_80443488(cur)) {
        return 0;
    }
    return 1;
}

int clashMission_IsEndOfGame()
{
    if (fn_8044EFD0(lbl_8054ED80)) {
        return 1;
    }
    return 0;
}

void clashMission_CompleteMission(int index)
{
    fn_8011ED50(fn_8011CA74());
    void *rec = 0;
    if (fn_8042D444(lbl_8054ED80)) {
        rec = fn_80088374(lbl_8054ED80, index);
    } else {
        rec = fn_8008816C(lbl_8054ED80, index);
    }
    fn_8008856C(lbl_8054ED80, fn_80442E7C(rec), 0);
    if (fn_804433C8(rec) || fn_80433E08(rec) || fn_804433F8(rec)) {
        fn_8002D9C4(lbl_8052F060);
        fn_8012D400(0);
    } else {
        fn_80087938(lbl_8054ED80, fn_80442E7C(rec));
    }
}

extern "C" {
int fn_80442C00(void *rec, unsigned char slot);
int fn_8044D4F0(int id);
int fn_8044D454(int id);
int fn_8044D5C4(int id);
int fn_8044B48C(int id, int a, int b);
char *fn_8044F038(int id);
char *fn_8044F000(int id);
char *fn_8044F19C(int id);
char *fn_8044B1D4(int id, int a, int b);
void fn_800877F4(void *chron, void *rec);
}

extern char lbl_80491B54[]; // "aRewardType"
extern char lbl_80491B60[]; // "aRewardName"
extern char lbl_80491B6C[]; // "numReward"

AptObject clashMission_GetRewardInfo()
{
    AptObject info;
    void *rec = fn_804326B4(lbl_8054ED80);
    int count = 0;

    if (fn_8044EFD0(lbl_8054ED80) || fn_804432D8(rec)) {
        for (int i = 0; i <= 3; i++) {
            int id = fn_80442C00(rec, i);
            int unused = 0;
            if (id > 99999) {
                continue;
            }
            if (id > 9999) {
                if (fn_8044D4F0(id - 10000)) {
                    continue;
                }
                info[lbl_80491B54][count] = 3;
                info[lbl_80491B60][count] = fn_8044F038(id - 10000);
            } else if (id > 999) {
                if (fn_8044D454(id - 1000)) {
                    continue;
                }
                info[lbl_80491B54][count] = 2;
                info[lbl_80491B60][count] = fn_8044F000(id - 1000);
            } else if (id > 99) {
                if (fn_8044D5C4(id - 100)) {
                    continue;
                }
                info[lbl_80491B54][count] = 1;
                info[lbl_80491B60][count] = fn_8044F19C(id - 100);
            } else if (id >= 0) {
                if (fn_8044B48C(id, 0, 0)) {
                    continue;
                }
                info[lbl_80491B54][count] = 0;
                info[lbl_80491B60][count] = fn_8044B1D4(id, 0, 0);
            } else {
                continue;
            }
            count++;
        }
        fn_800877F4(lbl_8054ED80, rec);
    }

    info[lbl_80491B6C] = count;
    return info;
}

extern "C" {
char *strncpy(char *dst, const char *src, int n);
int stricmp(const char *a, const char *b);
int fn_80432844(void *g);
int fn_80432870(void *g);
void fn_800944C0(void *g, void *record, int player);
int fn_80431D84(void *chron);
const char *fn_8043265C(void *rec);
const char *fn_8044D328(void *rec);
int fn_80128E98(const char *fmt, ...);
int fn_80130718();
}

struct GameState {
    char unk0[0x5BB];
    char venueNameEnd; // +0x5BB
    char unk5BC[0x60];
    int unk61C; // +0x61C
};
extern GameState lbl_80552110;
extern char lbl_805526AC[]; // G+0x59C, the level name
extern char lbl_80491B78[]; // "BrooklynBridge"
extern char lbl_80491B88[]; // "plr_thing"
extern char lbl_80491B94[]; // "ERROR"
extern char lbl_80491B9C[]; // "clashMission_DebugChooseMission( %d )"

// On BrooklynBridge with no versus role, spawns "plr_thing" for player 0.
void clashMission_StartLevel(String name)
{
    strncpy(lbl_805526AC, name.c_str(), 0x20);
    lbl_80552110.venueNameEnd = 0;
    fn_8012D400(0);
    if (!fn_80432844(&lbl_80552110) && !fn_80432870(&lbl_80552110) && stricmp(lbl_805526AC, lbl_80491B78) == 0) {
        fn_800944C0(&lbl_80552110, lbl_80491B88, 0);
    }
    lbl_80552110.unk61C = 1;
    fn_8011ED0C(fn_8011CA74());
    fn_80432AF8(lbl_8052F060);
}

int clashMission_DebugNumMissions()
{
    return fn_80431D84(lbl_8054ED80);
}

String clashMission_DebugMissionName(int index)
{
    void *rec = 0;
    rec = fn_804332C4(lbl_8054ED80, index);
    if (rec) {
        const char *name = fn_8043265C(rec);
        return String(name);
    }
    return String(lbl_80491B94);
}

void clashMission_DebugChooseMission(int index)
{
    fn_80128E98(lbl_80491B9C, index);
    void *rec = 0;
    rec = fn_804332C4(lbl_8054ED80, index);
    if (rec) {
        const char *name = fn_8044D328(rec);
        long id = fn_80442E7C(rec);
        fn_8008856C(lbl_8054ED80, fn_80442E7C(rec), 0);
        fn_8012D400(0);
        fn_80432AF8(lbl_8052F060);
    }
}

int clashMission_IsStoryMode()
{
    return fn_80130718();
}

String clashMission_GetObjective()
{
    void *rec = 0;
    rec = fn_804326B4(lbl_8054ED80);
    if (rec) {
        char *text = fn_8044E9A8(rec);
        return String(text);
    }
    return String(lbl_80491B94);
}

extern "C" {
void *fn_8044AF58(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044B11C(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044BBC8(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044BD90(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044BF9C(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044C35C(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044EE3C(void *reg, const char *name, void *func, const char *file, int line);
}

extern float lbl_8066BB4C; // sdata
extern float lbl_8066BB50; // sdata

extern char lbl_80491BF4[]; // this file's path
extern char lbl_80491BD8[]; // "clashMission_GetMissionList"
extern char lbl_80491C28[];
extern char lbl_80491C4C[];
extern char lbl_80491C60[];
extern char lbl_80491C74[];
extern char lbl_80491C90[];
extern char lbl_80491CAC[];
extern char lbl_80491CD0[];
extern char lbl_80491CEC[];
extern char lbl_80491D0C[];
extern char lbl_80491D28[];
extern char lbl_80491D40[];
extern char lbl_80491D60[];
extern char lbl_80491D80[];
extern char lbl_80491DA0[];
extern char lbl_80491DBC[]; // "clashMission_GetObjective"

static float sMissionScreenLeft;
static float sMissionScreenRight;
static float sMissionScreenTop;
static float sMissionScreenBottom;

static char sReg_clashMission_GetMissionList;
static char sReg_clashMission_SetUpSpecialMission;
static char sReg_clashMission_Start;
static char sReg_Mission_GetCharId;
static char sReg_clashMission_StartNewGame;
static char sReg_clashMission_IsFirstTimeIn;
static char sReg_clashMission_IsBack2MissionAllow;
static char sReg_clashMission_IsEndOfGame;
static char sReg_clashMission_CompleteMission;
static char sReg_clashMission_GetRewardInfo;
static char sReg_clashMission_StartLevel;
static char sReg_clashMission_DebugNumMissions;
static char sReg_clashMission_DebugMissionName;
static char sReg_clashMission_DebugChooseMission;
static char sReg_clashMission_IsStoryMode;
static char sReg_clashMission_GetObjective;

static void __static_initialization_and_destruction_0(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            sMissionScreenLeft = 320.0f - lbl_8066BB4C * 0.5f;
            sMissionScreenRight = sMissionScreenLeft + lbl_8066BB4C * 0.5f;
            sMissionScreenTop = 240.0f - lbl_8066BB50 * 0.5f;
            sMissionScreenBottom = lbl_8066BB50 * 0.5f + sMissionScreenTop - 12.0f;
            fn_8044AF58(&sReg_clashMission_GetMissionList, lbl_80491BD8, (void *)clashMission_GetMissionList, lbl_80491BF4, 101);
            fn_8044AF58(&sReg_clashMission_SetUpSpecialMission, lbl_80491C28, (void *)clashMission_SetUpSpecialMission, lbl_80491BF4, 150);
            fn_8044B11C(&sReg_clashMission_Start, lbl_80491C4C, (void *)clashMission_Start, lbl_80491BF4, 157);
            fn_8044BBC8(&sReg_Mission_GetCharId, lbl_80491C60, (void *)Mission_GetCharId, lbl_80491BF4, 164);
            fn_8044B11C(&sReg_clashMission_StartNewGame, lbl_80491C74, (void *)clashMission_StartNewGame, lbl_80491BF4, 173);
            fn_8044BBC8(&sReg_clashMission_IsFirstTimeIn, lbl_80491C90, (void *)clashMission_IsFirstTimeIn, lbl_80491BF4, 179);
            fn_8044BBC8(&sReg_clashMission_IsBack2MissionAllow, lbl_80491CAC, (void *)clashMission_IsBack2MissionAllow, lbl_80491BF4, 197);
            fn_8044BBC8(&sReg_clashMission_IsEndOfGame, lbl_80491CD0, (void *)clashMission_IsEndOfGame, lbl_80491BF4, 206);
            fn_8044C35C(&sReg_clashMission_CompleteMission, lbl_80491CEC, (void *)clashMission_CompleteMission, lbl_80491BF4, 232);
            fn_8044AF58(&sReg_clashMission_GetRewardInfo, lbl_80491D0C, (void *)clashMission_GetRewardInfo, lbl_80491BF4, 295);
            fn_8044BF9C(&sReg_clashMission_StartLevel, lbl_80491D28, (void *)clashMission_StartLevel, lbl_80491BF4, 317);
            fn_8044BBC8(&sReg_clashMission_DebugNumMissions, lbl_80491D40, (void *)clashMission_DebugNumMissions, lbl_80491BF4, 324);
            fn_8044EE3C(&sReg_clashMission_DebugMissionName, lbl_80491D60, (void *)clashMission_DebugMissionName, lbl_80491BF4, 340);
            fn_8044C35C(&sReg_clashMission_DebugChooseMission, lbl_80491D80, (void *)clashMission_DebugChooseMission, lbl_80491BF4, 367);
            fn_8044BBC8(&sReg_clashMission_IsStoryMode, lbl_80491DA0, (void *)clashMission_IsStoryMode, lbl_80491BF4, 372);
            fn_8044BD90(&sReg_clashMission_GetObjective, lbl_80491DBC, (void *)clashMission_GetObjective, lbl_80491BF4, 387);
        } else {
        }
    }
}

void fn_8010BE9C(void)
{
    __static_initialization_and_destruction_0(1, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_8010BE9C;
