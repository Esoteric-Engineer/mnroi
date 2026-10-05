// c:/Clash/mainline/Code/Game/handlers/control.cpp, from Control_EnableControllerCheck (0x80104504); see Game/handlers/control.cpp.

extern "C" {
void fn_80432D00(void *self, int on);

// Last-selection module (docs/versus.md 4.2) and the game-state setters.
void fn_801317D8(int matchType);
void fn_80131828(int timed);
void fn_801318C8(int seconds);
int fn_801318A0();
void fn_804317F4(void *g, int role);
void fn_8043181C(void *g, int role);
void fn_80431844(void *g, int count);
void *fn_804317BC(void *g, int slot);
void fn_80431788(void *slot);
void fn_80443CCC(void *g, int player, int value);
void fn_80131918(int player, int charId);
void fn_801319D4(int player, int live);
void fn_80131A94(int player, int cusType);
void fn_8044D600(void *g, int player, int live);
void *fn_80443678(int index, int remap, int alt);
void fn_800944C0(void *g, void *record, int player);
int fn_8044D5C4(void *venue);
const char *fn_8044D58C(void *venue);
void fn_8044D390(void *table, void *venue);
int fn_80431D84(void *table);
void *fn_804332C4(void *table, int index);
const char *fn_8044D328(void *obj);
int fn_80442E7C(void *obj);
void fn_8008856C(void *table, int index, int a);
char *strncpy(char *dst, const char *src, int n);
int strcmp(const char *a, const char *b);
void *fn_8042D4CC();
void fn_8044D8E4(void *x, int a);
void fn_80015960(void *x, int mode, int a);
void fn_800876D4(void *table);
void fn_80089710(int a);
void *fn_804326B4(void *table);
int fn_80442FC4(void *obj);
void fn_8012D400(int a);
void fn_80432AF8(void *level);
int fn_80131DAC();
int fn_80131DE4();
void *fn_80427400();
void fn_8012EC9C(void *lang);
void *fn_80122228();
void fn_80123D60(void *x);
void SetCommand__8GameFlowi(void *self, int command);
void SetCommandBlocking__8GameFlowi(void *self, int command);
}

// Game-state object G (docs/versus.md 4.1).
struct GameState {
    char unk0[0x5BB];
    char venueNameEnd; // +0x5BB
    char unk5BC[0x60];
    int unk61C; // +0x61C
    char unk620[0x13C];
    int timerMode; // +0x75C
    char unk760[0x4];
    int timeLimitMs; // +0x764
};
extern GameState lbl_80552110;
extern char lbl_80552920[]; // GameFlow instance
extern char lbl_8052F060[]; // level object
extern char lbl_805526AC[]; // G+0x59C, the level name
extern char lbl_80490528[]; // default level name
extern char lbl_8054ED80[]; // .nsc script table
extern char lbl_8054EF38[]; // name table

// Emits no code. A top-level `return <parameter>;` makes cc1plus drop the function-end branch pair for every later function in the unit.
inline int sn_return_decl(int a) { return a; }

void Control_EnableControllerCheck(int on)
{
    if (on == 1) {
        fn_80432D00(lbl_80552920, 1);
    } else {
        fn_80432D00(lbl_80552920, 0);
    }
}

void Control_SetMatchInfo(int matchType, int timed, int unused, int seconds)
{
    fn_801317D8(matchType);
    fn_80131828(timed);
    fn_801318C8(seconds);

    switch (matchType) {
    case 0:
        fn_8043181C(&lbl_80552110, 0);
        fn_804317F4(&lbl_80552110, 1);
        fn_80431844(&lbl_80552110, 2);
        break;
    case 1:
        fn_804317F4(&lbl_80552110, 0);
        fn_80431844(&lbl_80552110, 2);
        fn_8043181C(&lbl_80552110, 1);
        fn_80431788(fn_804317BC(&lbl_80552110, 1));
        break;
    case 2:
        lbl_80552110.unk61C = 1;
        fn_8043181C(&lbl_80552110, 0);
        break;
    }

    if (timed == 0) {
        lbl_80552110.timerMode = 2;
    } else {
        lbl_80552110.timerMode = 1;
        lbl_80552110.timeLimitMs = seconds * 1000;
    }

    fn_80443CCC(&lbl_80552110, 0, fn_801318A0());
    fn_80443CCC(&lbl_80552110, 1, fn_801318A0());
}

void Control_SetSelectInfo(int charId0, int live0, int cusType0, int charId1, int live1, int cusType1, void *venue)
{
    int index0 = charId0 + 1 > 0 ? (charId0 + 1 > 0x12 ? 0x12 : charId0 + 1) : 1;
    int index1 = charId1 + 1 > 0 ? (charId1 + 1 > 0x12 ? 0x12 : charId1 + 1) : 1;
    void *obj;
    int i;
    const char *name;
    int id;

    fn_80131918(0, charId0);
    fn_80131918(1, charId1);
    fn_80131A94(0, cusType0);
    fn_80131A94(1, cusType1);
    fn_801319D4(0, live0);
    fn_801319D4(1, live1);

    if (lbl_80552110.timerMode == 2) {
        fn_8044D600(&lbl_80552110, 0, live0);
        fn_8044D600(&lbl_80552110, 1, live1);
    } else {
        fn_8044D600(&lbl_80552110, 0, 1);
        fn_8044D600(&lbl_80552110, 1, 1);
    }

    fn_800944C0(&lbl_80552110, fn_80443678(index0, 1, cusType0), 0);
    fn_800944C0(&lbl_80552110, fn_80443678(index1, 1, cusType1), 1);

    if (!fn_8044D5C4(venue)) {
        return;
    }

    obj = 0;
    if (fn_8044D5C4(venue)) {
        strncpy(lbl_805526AC, fn_8044D58C(venue), 0x20);
        lbl_80552110.venueNameEnd = 0;
    } else {
        strncpy(lbl_805526AC, lbl_80490528, 0x20);
        lbl_80552110.venueNameEnd = 0;
    }

    fn_8044D390(lbl_8054ED80, venue);
    for (i = 0; i < fn_80431D84(lbl_8054EF38); i++) {
        obj = fn_804332C4(lbl_8054EF38, i);
        if (obj) {
            name = fn_8044D328(obj);
            if (strcmp(name, fn_8044D58C(venue)) == 0) {
                id = fn_80442E7C(obj);
                fn_8008856C(lbl_8054EF38, id, 0);
                break;
            }
        }
    }
}

void Control_StartLoad()
{
    fn_8044D8E4(fn_8042D4CC(), 0);
}

void Control_StartProgressBar(int a, int b)
{
    void *obj;

    if (b == 0) {
        fn_80015960(fn_8042D4CC(), 0, a);
    } else {
        if (a < 0) {
            fn_800876D4(lbl_8054ED80);
        } else {
            fn_80089710(a);
        }
        obj = fn_804326B4(lbl_8054ED80);
        fn_80015960(fn_8042D4CC(), 1, fn_80442FC4(obj));
    }
    fn_8044D8E4(fn_8042D4CC(), 0);
}

void Control_StartGame()
{
    fn_8012D400(0);
    fn_80432AF8(lbl_8052F060);
}

void Control_EndOfMatch(int result)
{
    switch (result) {
    case 0:
        SetCommand__8GameFlowi(lbl_80552920, 0x46);
        break;
    case 1:
        SetCommandBlocking__8GameFlowi(lbl_80552920, 2);
        break;
    case 2:
        SetCommandBlocking__8GameFlowi(lbl_80552920, 1);
        break;
    }
    fn_8012D400(0);
}

void Control_EndOfMission(int result)
{
    switch (result) {
    case 0:
        SetCommand__8GameFlowi(lbl_80552920, 0x45);
        break;
    case 1:
        SetCommandBlocking__8GameFlowi(lbl_80552920, 8);
        break;
    case 2:
        SetCommandBlocking__8GameFlowi(lbl_80552920, 1);
        break;
    }
    fn_8012D400(0);
}

int Control_GetNewUnlockable()
{
    return fn_80131DAC();
}

int Control_GetNewUnlockableID()
{
    return fn_80131DE4();
}

void Control_ToggleLanguage()
{
    void *lang;

    return;
    lang = fn_80427400();
    fn_8012EC9C(lang);
    fn_80123D60(fn_80122228());
}
