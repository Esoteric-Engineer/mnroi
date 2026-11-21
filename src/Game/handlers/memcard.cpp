// c:/Clash/mainline/Code/Game/handlers/memcard.cpp
//
// Built at -O0; memory-card and settings handlers over the save profile, docs/story.md row 23. Owns .rodata 0x80491960-0x80491970.

class AptRef {
public:
    void operator=(char *const &value); // fn_8044B694
    void operator=(const int &value);   // fn_8044B758
    void operator=(const long &value) __asm__("fn_8044EB5C");
    // Names are ours (matching_notes.md).
    void SetLit2(char (&value)[2]) __asm__("fn_8044E9D4");
    void SetLit50(char (&value)[50]) __asm__("fn_8044EA98");
    void SetLit1(char (&value)[1]) __asm__("fn_8044EC20");

private:
    void *object; // +0x0
    char *name;   // +0x4 property
    int index;    // +0x8 element, -1 for the property itself
};

class AptObject {
public:
    AptObject();                         // fn_8044B608
    AptObject(const AptObject &other);   // fn_8044B568
    ~AptObject();                        // fn_8044B510
    AptRef operator[](const char *name); // fn_80102E60

private:
    void *unk0; // +0x0
    int unk4;   // +0x4
};

// fn_80122228's 0x5F48-byte singleton.
struct MemcardMgr {
    char unk0[0x70];
    int unk70;         // +0x70 overwrite-settings flag
    char unk74[0xCC];
    int unk140;        // +0x140 overwrite-savegame flag
};

struct Unk8011EE90 {
    char unk0[0x10];
    int unk10; // +0x10
};

struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

extern "C" {
void *memset(void *dst, int c, unsigned n);
char *strncpy(char *dst, const char *src, unsigned n);
int sprintf(char *dst, const char *fmt, ...);
long mktime(struct tm *t);
struct tm *fn_80172D78(const long *t); // localtime
char *fn_80172CC4(const struct tm *t); // asctime

void *Profile_Get();
MemcardMgr *fn_80122228();
Unk8011EE90 *fn_8011EE90();
void *fn_80427400();
void *fn_8044D354(void *chron);
char *fn_804426AC(void *rec);
char *fn_8044E9A8(void *rec);
long fn_80442E7C(void *rec);

void fn_801026A8();
void fn_801300B4();
void fn_801304E0();
void fn_8012FAA0(void *loc, char *out, int a, int b, int c);
void fn_8012FCE4(void *loc, char *out, int a, int b, int c);
char *fn_8012F32C(void *loc, const char *key);
void fn_8012F154(void *loc, char *text, char *out, int size, int flag);

int fn_8011CD30(void *p);
void fn_8011CD60(void *p, int on);
int fn_8011CD98(void *p);
int fn_8011CEA0(void *p);
int fn_8011CFA8(void *p);
void fn_8011CFD8(void *p, int on);
int fn_8011D090(void *p);
void fn_8011D0C0(void *p, int on);
int fn_8011D0F0(void *p);
void fn_8011D120(void *p, int value, int flag);
int fn_8011D43C(void *p);
void fn_8011D474(void *p, int value);
int fn_8011D4AC(void *p);
void fn_8011D4E4(void *p, int value);
int fn_8011D854(void *p);
int fn_8011D8A4(void *p);
int fn_8011D918(void *p);
int fn_8011D9F8(void *p);
int fn_8011DAA0(void *p);
int fn_8011DB78(void *p);
int fn_8011DA4C(void *p, int seconds);
int fn_8011DAF4(void *p, int seconds);
int fn_8011DBCC(void *p, int seconds);
void fn_8011E59C(void *p);
int fn_8011E9C4(void *p);
int fn_8011E9F8(void *p);
void fn_8011EA2C(void *p, int keep);
void fn_8011EB68(void *p);
void fn_8011EBF8(void *p);
void fn_8011ED0C(void *p);
void fn_8011ED50(void *p);

int fn_801223CC(void *m);
int fn_801223F8(void *m);
void fn_80122424(void *m, int on);
int fn_80122450(void *m);
int fn_801224D0(void *m);
void fn_801224FC(void *m, int on);
int fn_80122528(void *m);
int fn_80122580(void *m);
int fn_801230F0(void *m);
int fn_80123190(void *m);
int fn_801231E8(void *m);
void fn_801231BC(void *m, int on);
void fn_80123214(void *m, int on);
int fn_80123240(void *m);
void fn_8012326C(void *m, int on);
int fn_80123298(void *m);
void fn_801232C4(void *m, int on);
int fn_801232F0(void *m);
void fn_8012331C(void *m, int on);
void fn_801233CC(void *m, int value);
int fn_801233F8(void *m);
int fn_80123500(void *m);
int fn_8012352C(void *m);
void fn_80123558(void *m, int on);
void fn_801235B0(void *m, int on);
int fn_80123634(void *m);
int fn_801236E4(void *m);
int fn_8012373C(void *m);
void fn_80123768(void *m, int value);
int fn_801237EC(void *m);
void fn_80123818(void *m, int on);
int fn_80123844(void *m);
void fn_80123870(void *m, int on);
int fn_801238F4(void *m);
void fn_80123920(void *m, int on);
int fn_8012394C(void *m);
void fn_80123978(void *m, int on);
void fn_801239D0(void *m, int on);
int fn_80124250(void *m);
int fn_8012491C(void *m, int slot);
int fn_801249EC(void *m, int slot);
long fn_80124AA0(void *m, int slot);
char *fn_80124B18(void *m, int slot);
unsigned int fn_80124B58(void *m, int slot); // play time
char *fn_80124BD0(void *m, int slot);
int fn_80124C10(void *m, int slot);
char *fn_80124C88(void *m, int slot);
char *fn_80124CC8(void *m, int slot);
void fn_80124D8C(void *m, int mode);
void fn_80124E50(void *m, int a);
void fn_80125220(void *m);
void fn_80125428(void *m, int a, int b, int c);
}

extern char lbl_8054ED80[]; // chronicle
extern char lbl_805674F0[]; // 0x200-byte text buffer

// Literals still owned by the auto-generated .rodata.
extern char lbl_80491068[]; // "vibrate"
extern char lbl_80491070[]; // "1"
extern char lbl_80491074[]; // "0"
extern char lbl_80491078[]; // "music"
extern char lbl_80491080[]; // "sfx"
extern char lbl_80491084[]; // "difficulty"
extern char lbl_80491090[]; // "autosave"
extern char lbl_8049109C[]; // "widescreen"
extern char lbl_804910A8[]; // "audio"
extern char lbl_804910B0[]; // "lastsave"
extern char lbl_804910BC[]; // "timeplayed"
extern char lbl_804910C8[]; // "missionTitle"
extern char lbl_804910D8[]; // "missionDesc"
extern char lbl_804910E4[]; // "missionID"
extern char lbl_804910F0[]; // "%s"
extern char lbl_804910F4[]; // ""
extern char lbl_804910F8[]; // "kT_DAMAGEDGAME_NGC"

// Emits no code; clears the function-end branch pair for later functions (docs/prodg.md).
inline int sn_return_decl(int a) { return a; }

void clashMemcard_MemOption(int mode)
{
    fn_80124E50(fn_80122228(), 10);
    fn_8011EE90()->unk10 = 0;
    fn_80124D8C(fn_80122228(), mode);
}

void clashMemcard_DlgTest()
{
}

void clashMemcard_DlgTestEnd()
{
    fn_801026A8();
}

void clashMemCard_Operation(int a, int b, int c)
{
    fn_80125428(fn_80122228(), a, b, c);
}

void clashMemcard_SetSettings(int vibrate, int b, int c, int d, int autosave, int difficulty)
{
    if (vibrate == 1) {
        fn_8011CD60(Profile_Get(), 1);
    } else {
        fn_8011CD60(Profile_Get(), 0);
    }
    fn_8011D4E4(Profile_Get(), difficulty);
    if (autosave == 1) {
        fn_8011CFD8(Profile_Get(), 1);
    } else {
        fn_8011CFD8(Profile_Get(), 0);
    }
}

void clashMemcard_SetSettings7(int vibrate, int b, int c, int d, int autosave, int difficulty, int widescreen)
{
    if (vibrate == 1) {
        fn_8011CD60(Profile_Get(), 1);
    } else {
        fn_8011CD60(Profile_Get(), 0);
    }
    fn_8011D4E4(Profile_Get(), difficulty);
    if (autosave == 1) {
        fn_8011CFD8(Profile_Get(), 1);
    } else {
        fn_8011CFD8(Profile_Get(), 0);
    }
    if (widescreen == 1) {
        fn_8011D0C0(Profile_Get(), 1);
    } else {
        fn_8011D0C0(Profile_Get(), 0);
    }
}

void clashMemcard_SetAudioSetting(int mode)
{
    fn_8011D120(Profile_Get(), mode, 0);
}

AptObject clashMemcard_GetSettings()
{
    AptObject settings;
    if (fn_8011CD30(Profile_Get())) {
        settings[lbl_80491068].SetLit2(*(char (*)[2])lbl_80491070);
    } else {
        settings[lbl_80491068].SetLit2(*(char (*)[2])lbl_80491074);
    }
    settings[lbl_80491078] = fn_8011CD98(Profile_Get());
    settings[lbl_80491080] = fn_8011CEA0(Profile_Get());
    settings[lbl_80491084] = fn_8011D4AC(Profile_Get());
    if (fn_8011CFA8(Profile_Get()) || fn_801224D0(fn_80122228())) {
        settings[lbl_80491090].SetLit2(*(char (*)[2])lbl_80491070);
    } else {
        settings[lbl_80491090].SetLit2(*(char (*)[2])lbl_80491074);
    }
    return settings;
}

AptObject clashMemcard_GetSettings8()
{
    AptObject settings;
    if (fn_8011CD30(Profile_Get())) {
        settings[lbl_80491068].SetLit2(*(char (*)[2])lbl_80491070);
    } else {
        settings[lbl_80491068].SetLit2(*(char (*)[2])lbl_80491074);
    }
    settings[lbl_80491078] = fn_8011CD98(Profile_Get());
    settings[lbl_80491080] = fn_8011CEA0(Profile_Get());
    settings[lbl_80491084] = fn_8011D4AC(Profile_Get());
    if (fn_8011CFA8(Profile_Get()) || fn_801224D0(fn_80122228())) {
        settings[lbl_80491090].SetLit2(*(char (*)[2])lbl_80491070);
    } else {
        settings[lbl_80491090].SetLit2(*(char (*)[2])lbl_80491074);
    }
    if (fn_8011D090(Profile_Get())) {
        settings[lbl_8049109C].SetLit2(*(char (*)[2])lbl_80491070);
    } else {
        settings[lbl_8049109C].SetLit2(*(char (*)[2])lbl_80491074);
    }
    settings[lbl_804910A8] = fn_8011D0F0(Profile_Get());
    return settings;
}

void clashMemcard_DefaultSettings()
{
    fn_8011E59C(Profile_Get());
}

AptObject clashMemcard_GetCurrentGame()
{
    AptObject game;
    int year = fn_8011D854(Profile_Get()) - 2000;
    if (year < 0) {
        year = 0;
    }
    int month = fn_8011D8A4(Profile_Get());
    int day = fn_8011D918(Profile_Get());
    int hours = fn_8011D9F8(Profile_Get());
    int minutes = fn_8011DAA0(Profile_Get());
    int seconds = fn_8011DB78(Profile_Get());
    char date[50];
    char time[50];
    memset(date, 0, 50);
    memset(time, 0, 50);
    fn_8012FAA0(fn_80427400(), date, year, month, day);
    fn_8012FCE4(fn_80427400(), time, hours, minutes, seconds);
    game[lbl_804910B0].SetLit50(date);
    game[lbl_804910BC].SetLit50(time);
    game[lbl_804910C8] = fn_804426AC(fn_8044D354(lbl_8054ED80));
    game[lbl_804910D8] = fn_8044E9A8(fn_8044D354(lbl_8054ED80));
    game[lbl_804910E4] = fn_80442E7C(fn_8044D354(lbl_8054ED80));
    return game;
}

AptObject clashMemcard_GetFileInformation(int slot)
{
    AptObject info;
    register int size = 0x200;
    int year = 0;
    int month = 0;
    int day = 0;
    int unk = 0;
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    char text[56];
    long t;
    struct tm tm = { 0, 0, 0, 0, 0, 100 };
    t = mktime(&tm);
    t += fn_80124AA0(fn_80122228(), slot);
    tm = *fn_80172D78(&t);
    sprintf(text, lbl_804910F0, fn_80172CC4(&tm));
    year = tm.tm_year - 100;
    month = tm.tm_mon + 1;
    day = tm.tm_mday + 1;
    int played = fn_80124B58(fn_80122228(), slot);
    hours = fn_8011DA4C(Profile_Get(), played);
    minutes = fn_8011DAF4(Profile_Get(), played);
    seconds = fn_8011DBCC(Profile_Get(), played);
    info[lbl_804910B0].SetLit1(*(char (*)[1])lbl_804910F4);
    info[lbl_804910BC].SetLit1(*(char (*)[1])lbl_804910F4);
    info[lbl_804910E4] = -1;
    info[lbl_804910C8] = fn_80124C88(fn_80122228(), slot);
    info[lbl_804910D8] = fn_80124CC8(fn_80122228(), slot);
    if (fn_8012491C(fn_80122228(), slot)) {
        if (fn_801249EC(fn_80122228(), slot)) {
            fn_8012F154(fn_80427400(), fn_8012F32C(fn_80427400(), lbl_804910F8), lbl_805674F0, 0x200, 0);
            strncpy(fn_80124C88(fn_80122228(), slot), lbl_805674F0, 50);
            strncpy(fn_80124CC8(fn_80122228(), slot), lbl_805674F0, 50);
            info[lbl_804910C8] = fn_80124C88(fn_80122228(), slot);
            info[lbl_804910D8] = fn_80124CC8(fn_80122228(), slot);
            info[lbl_804910E4] = -2;
        } else {
            fn_8012FAA0(fn_80427400(), fn_80124B18(fn_80122228(), slot), year, month, day);
            fn_8012FCE4(fn_80427400(), fn_80124BD0(fn_80122228(), slot), hours, minutes, seconds);
            info[lbl_804910B0] = fn_80124B18(fn_80122228(), slot);
            info[lbl_804910BC] = fn_80124BD0(fn_80122228(), slot);
            if (!fn_8012F32C(fn_80427400(), fn_80124C88(fn_80122228(), slot))) {
                memset(lbl_805674F0, 0, 0x200);
                strncpy(fn_80124C88(fn_80122228(), slot), lbl_805674F0, 50);
                strncpy(fn_80124CC8(fn_80122228(), slot), lbl_805674F0, 50);
            } else {
                fn_8012F154(fn_80427400(), fn_8012F32C(fn_80427400(), fn_80124C88(fn_80122228(), slot)), lbl_805674F0, 0x200, 0);
                strncpy(fn_80124C88(fn_80122228(), slot), lbl_805674F0, 50);
                strncpy(fn_80124CC8(fn_80122228(), slot), lbl_805674F0, 50);
            }
            info[lbl_804910C8] = fn_80124C88(fn_80122228(), slot);
            info[lbl_804910D8] = fn_80124CC8(fn_80122228(), slot);
            info[lbl_804910E4] = fn_80124C10(fn_80122228(), slot);
        }
    }
    return info;
}

void clashMemcard_ResetStoryMode(int keep)
{
    fn_801300B4();
    fn_8011EA2C(Profile_Get(), keep);
    fn_801304E0();
}

void clashMemcard_PlayTimerStart()
{
    fn_8011ED0C(Profile_Get());
}

void clashMemcard_PlayTimerStop()
{
    fn_8011ED50(Profile_Get());
}

void clashMemcard_ResetBackupSettings()
{
    fn_8011EB68(Profile_Get());
}

void clashMemcard_ResetSettings()
{
    fn_8011EBF8(Profile_Get());
}

int clashMemcard_CheckSettings(int vibrate, int b, int c, int d, int autosave, int difficulty, int widescreen)
{
    int changed = 0;
    int vib = 0;
    if (vibrate == 1) {
        vib = 1;
    }
    int save = 0;
    if (autosave == 1) {
        save = 1;
    }
    int wide = 0;
    if (widescreen == 1) {
        wide = 1;
    }
    if (vib != fn_8011CD30(Profile_Get())) {
        changed = 1;
    }
    int newSave = save;
    int oldSave = fn_8011CFA8(Profile_Get());
    int check = fn_801224D0(fn_80122228());
    int e = fn_8011E9C4(Profile_Get());
    int f = fn_8011E9F8(Profile_Get());
    if (newSave == oldSave && check != f) {
        changed = 1;
    } else if (check != newSave && newSave == oldSave && e == f) {
        changed = 1;
    }
    if (difficulty != fn_8011D4AC(Profile_Get())) {
        changed = 1;
    }
    return changed;
}

int clashMemcard_CheckAudio(int mode)
{
    int changed = 0;
    if (mode != fn_8011D0F0(Profile_Get())) {
        changed = 1;
    }
    return changed;
}

int clashMemcard_IsHardDriveFull()
{
    int full = 0;
    return full;
}

void clashMemcard_XBOXFreeSpace()
{
    fn_80125220(fn_80122228());
}

int clashMemcard_GetStatus()
{
    return fn_80122528(fn_80122228());
}

int clashMemcard_GetTaskResult()
{
    return fn_80122580(fn_80122228());
}

int clashMemcard_GetSaveStatus()
{
    return fn_801230F0(fn_80122228());
}

int clashMemcard_GetSettingsExist()
{
    int r = 0;
    if (fn_80123190(fn_80122228())) {
        r = 1;
    }
    return r;
}

int clashMemcard_GetSettingsAutosaveOn()
{
    int r = 0;
    if (fn_801231E8(fn_80122228())) {
        r = 1;
    }
    return r;
}

int clashMemcard_GetAutosaveCheck()
{
    int r = 0;
    if (fn_801224D0(fn_80122228())) {
        r = 1;
    }
    return r;
}

void clashMemcard_SetAutosaveCheck(int on)
{
    fn_801224FC(fn_80122228(), 0);
    if (on == 1) {
        fn_801224FC(fn_80122228(), 1);
    }
}

int clashMemcard_IsJuiceOn()
{
    int r = 0;
    return r;
}

int clashMemcard_GetAutosavePrompt()
{
    int r = 0;
    if (fn_80123240(fn_80122228())) {
        r = 1;
    }
    return r;
}

void clashMemcard_ResetAutosavePrompt()
{
    fn_8012326C(fn_80122228(), 0);
}

int clashMemcard_GetContinueOverride()
{
    int r = 0;
    if (fn_801232F0(fn_80122228())) {
        r = 1;
    }
    return r;
}

void clashMemcard_SetAutosaveParam(int value)
{
    fn_8011D474(Profile_Get(), value);
}

int clashMemcard_GetPS2NoCardFlag()
{
    int r = 0;
    if (fn_801233F8(fn_80122228())) {
        r = 1;
    }
    return r;
}

void clashMemcard_SetLastSaveGameParam(int value)
{
    fn_8011D474(Profile_Get(), value);
}

int clashMemcard_GetOverwriteSettingsFlag()
{
    int r = 0;
    if (fn_80122228()->unk70) {
        r = 1;
    }
    return r;
}

void clashMemcard_SetOverwriteSettingsFlag(int on)
{
    fn_80122228()->unk70 = 0;
    if (on == 1) {
        fn_80122228()->unk70 = 1;
    }
}

int clashMemcard_GetOverwriteSavegameFlag()
{
    int r = 0;
    if (fn_80122228()->unk140) {
        r = 1;
    }
    return r;
}

void clashMemcard_SetOverwriteSavegameFlag(int on)
{
    fn_80122228()->unk140 = 0;
    if (on == 1) {
        fn_80122228()->unk140 = 1;
    }
}

int clashMemcard_GetOnlineBootFlowFlag()
{
    int r = 0;
    if (fn_80123500(fn_80122228())) {
        r = 1;
    }
    return r;
}

int clashMemcard_GetAutosaveOn()
{
    int r = 0;
    if (fn_80123298(fn_80122228())) {
        r = 1;
    }
    return r;
}

void clashMemcard_SetAutosaveOn(int on)
{
    fn_801232C4(fn_80122228(), 0);
    if (on == 1) {
        fn_801232C4(fn_80122228(), 1);
    }
}

int clashMemcard_IsHardDriveLow()
{
    return fn_801223CC(fn_80122228());
}

int clashMemcard_DynamicOverestimation()
{
    return fn_80124250(fn_80122228());
}

int clashMemcard_XBOXFreeBlocksFlag()
{
    int r = 0;
    if (fn_80122450(fn_80122228())) {
        r = 1;
    }
    return r;
}

int clashMemcard_GetCardRemoved()
{
    int r = 0;
    if (fn_8012352C(fn_80122228())) {
        r = 1;
    }
    return r;
}

void clashMemcard_SetCardRemoved(int on)
{
    fn_80123558(fn_80122228(), 0);
    if (on == 1) {
        fn_80123558(fn_80122228(), 1);
    }
}

void clashMemcard_CardRemoved_AutoOff()
{
    fn_8011CFD8(Profile_Get(), 0);
    fn_801224FC(fn_80122228(), 0);
    fn_801231BC(fn_80122228(), 0);
    fn_80123214(fn_80122228(), 0);
    fn_80123558(fn_80122228(), 0);
}

void clashMemcard_SetBootFlag(int on)
{
    fn_801235B0(fn_80122228(), 0);
    if (on == 1) {
        fn_801235B0(fn_80122228(), 1);
    }
}

int clashMemcard_GetXBOXCorruptSettings()
{
    int r = 0;
    if (fn_80123634(fn_80122228())) {
        r = 1;
    }
    return r;
}

int clashMemcard_GetNGCInsufContinue()
{
    int r = 0;
    if (fn_801236E4(fn_80122228())) {
        r = 1;
    }
    return r;
}

int clashMemcard_GetFilesPresent()
{
    int files = fn_801223F8(fn_80122228());
    return files;
}

void clashMemcard_ResetFilesPresent()
{
    int files = fn_801223F8(fn_80122228());
    if (files == 1 || files == 3 || files == 5 || files == 7 || files == 9) {
        fn_80122424(fn_80122228(), 1);
    } else {
        fn_80122424(fn_80122228(), 0);
    }
}

int clashMemcard_GetLastSaveIndex()
{
    int index = fn_8011D43C(Profile_Get());
    return index;
}

int clashMemcard_GetLastUserChoice()
{
    int choice = fn_8012373C(fn_80122228());
    return choice;
}

int clashMemcard_GetLastUserChoiceReset()
{
    int choice = fn_8012373C(fn_80122228());
    fn_80123768(fn_80122228(), -1);
    return choice;
}

void clashMemcard_ResetLastUserChoice()
{
    fn_80123768(fn_80122228(), -1);
}

int clashMemcard_GetNGCNoMsgBoxKill()
{
    int r = 0;
    if (fn_801237EC(fn_80122228())) {
        fn_80123818(fn_80122228(), 0);
        r = 1;
    }
    return r;
}

int clashMemcard_GetNoMsgBoxSpawn()
{
    int r = 0;
    if (fn_80123844(fn_80122228())) {
        r = 1;
    }
    return r;
}

void clashMemcard_SetNoMsgBoxSpawn(int on)
{
    fn_80123870(fn_80122228(), 0);
    if (on == 1) {
        fn_80123870(fn_80122228(), 1);
    }
}

int clashMemcard_GetNGCMonitorHalt()
{
    int r = 0;
    if (fn_801238F4(fn_80122228())) {
        r = 1;
    }
    return r;
}

void clashMemcard_SetNGCMonitorHalt(int on)
{
    fn_80123920(fn_80122228(), 0);
    if (on == 1) {
        fn_80123920(fn_80122228(), 1);
    }
}

int clashMemcard_GetNewGameCheckOn()
{
    int r = 0;
    if (fn_8012394C(fn_80122228())) {
        r = 1;
    }
    return r;
}

void clashMemcard_SetNewGameCheckOn(int on)
{
    fn_80123978(fn_80122228(), 0);
    if (on == 1) {
        fn_80123978(fn_80122228(), 1);
    }
}

void clashMemcard_SetContinueOverride(int on)
{
    fn_8012331C(fn_80122228(), 0);
    if (on == 1) {
        fn_8012331C(fn_80122228(), 1);
        fn_801239D0(fn_80122228(), 1);
    }
}

void clashMemcard_SetSkipChoice(int choice)
{
    fn_801233CC(fn_80122228(), choice);
}

extern "C" {
void *fn_8044AF58(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044B11C(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044BBC8(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044C35C(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044C9E4(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044D060(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044D270(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044E180(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044E4E8(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044E8F0(void *reg, const char *name, void *func, const char *file, int line);
}

extern float lbl_8066BB3C; // sdata
extern float lbl_8066BB40; // sdata

extern char lbl_80491138[]; // this file's path

extern char lbl_80491120[]; // "clashMemcard_MemOption"
extern char lbl_8049116C[]; // "clashMemcard_DlgTest"
extern char lbl_80491184[]; // "clashMemcard_DlgTestEnd"
extern char lbl_8049119C[]; // "clashMemCard_Operation"
extern char lbl_804911B4[]; // "clashMemcard_SetSettings"
extern char lbl_804911D0[]; // "clashMemcard_SetSettings7"
extern char lbl_804911EC[]; // "clashMemcard_SetAudioSetting"
extern char lbl_8049120C[]; // "clashMemcard_GetSettings"
extern char lbl_80491228[]; // "clashMemcard_GetSettings8"
extern char lbl_80491244[]; // "clashMemcard_DefaultSettings"
extern char lbl_80491264[]; // "clashMemcard_GetCurrentGame"
extern char lbl_80491280[]; // "clashMemcard_GetFileInformation"
extern char lbl_804912A0[]; // "clashMemcard_ResetStoryMode"
extern char lbl_804912BC[]; // "clashMemcard_PlayTimerStart"
extern char lbl_804912D8[]; // "clashMemcard_PlayTimerStop"
extern char lbl_804912F4[]; // "clashMemcard_ResetBackupSettings"
extern char lbl_80491318[]; // "clashMemcard_ResetSettings"
extern char lbl_80491334[]; // "clashMemcard_CheckSettings"
extern char lbl_80491350[]; // "clashMemcard_CheckAudio"
extern char lbl_80491368[]; // "clashMemcard_IsHardDriveFull"
extern char lbl_80491388[]; // "clashMemcard_XBOXFreeSpace"
extern char lbl_804913A4[]; // "clashMemcard_GetStatus"
extern char lbl_804913BC[]; // "clashMemcard_GetTaskResult"
extern char lbl_804913D8[]; // "clashMemcard_GetSaveStatus"
extern char lbl_804913F4[]; // "clashMemcard_GetSettingsExist"
extern char lbl_80491414[]; // "clashMemcard_GetSettingsAutosaveOn"
extern char lbl_80491438[]; // "clashMemcard_GetAutosaveCheck"
extern char lbl_80491458[]; // "clashMemcard_SetAutosaveCheck"
extern char lbl_80491478[]; // "clashMemcard_IsJuiceOn"
extern char lbl_80491490[]; // "clashMemcard_GetAutosavePrompt"
extern char lbl_804914B0[]; // "clashMemcard_ResetAutosavePrompt"
extern char lbl_804914D4[]; // "clashMemcard_GetContinueOverride"
extern char lbl_804914F8[]; // "clashMemcard_SetAutosaveParam"
extern char lbl_80491518[]; // "clashMemcard_GetPS2NoCardFlag"
extern char lbl_80491538[]; // "clashMemcard_SetLastSaveGameParam"
extern char lbl_8049155C[]; // "clashMemcard_GetOverwriteSettingsFlag"
extern char lbl_80491584[]; // "clashMemcard_SetOverwriteSettingsFlag"
extern char lbl_804915AC[]; // "clashMemcard_GetOverwriteSavegameFlag"
extern char lbl_804915D4[]; // "clashMemcard_SetOverwriteSavegameFlag"
extern char lbl_804915FC[]; // "clashMemcard_GetOnlineBootFlowFlag"
extern char lbl_80491620[]; // "clashMemcard_GetAutosaveOn"
extern char lbl_8049163C[]; // "clashMemcard_SetAutosaveOn"
extern char lbl_80491658[]; // "clashMemcard_IsHardDriveLow"
extern char lbl_80491674[]; // "clashMemcard_DynamicOverestimation"
extern char lbl_80491698[]; // "clashMemcard_XBOXFreeBlocksFlag"
extern char lbl_804916B8[]; // "clashMemcard_GetCardRemoved"
extern char lbl_804916D4[]; // "clashMemcard_SetCardRemoved"
extern char lbl_804916F0[]; // "clashMemcard_CardRemoved_AutoOff"
extern char lbl_80491714[]; // "clashMemcard_SetBootFlag"
extern char lbl_80491730[]; // "clashMemcard_GetXBOXCorruptSettings"
extern char lbl_80491754[]; // "clashMemcard_GetNGCInsufContinue"
extern char lbl_80491778[]; // "clashMemcard_GetFilesPresent"
extern char lbl_80491798[]; // "clashMemcard_ResetFilesPresent"
extern char lbl_804917B8[]; // "clashMemcard_GetLastSaveIndex"
extern char lbl_804917D8[]; // "clashMemcard_GetLastUserChoice"
extern char lbl_804917F8[]; // "clashMemcard_GetLastUserChoiceReset"
extern char lbl_8049181C[]; // "clashMemcard_ResetLastUserChoice"
extern char lbl_80491840[]; // "clashMemcard_GetNGCNoMsgBoxKill"
extern char lbl_80491860[]; // "clashMemcard_GetNoMsgBoxSpawn"
extern char lbl_80491880[]; // "clashMemcard_SetNoMsgBoxSpawn"
extern char lbl_804918A0[]; // "clashMemcard_GetNGCMonitorHalt"
extern char lbl_804918C0[]; // "clashMemcard_SetNGCMonitorHalt"
extern char lbl_804918E0[]; // "clashMemcard_GetNewGameCheckOn"
extern char lbl_80491900[]; // "clashMemcard_SetNewGameCheckOn"
extern char lbl_80491920[]; // "clashMemcard_SetContinueOverride"
extern char lbl_80491944[]; // "clashMemcard_SetSkipChoice"

static float sMemcardScreenLeft;
static float sMemcardScreenRight;
static float sMemcardScreenTop;
static float sMemcardScreenBottom;

static char sReg_clashMemcard_MemOption;
static char sReg_clashMemcard_DlgTest;
static char sReg_clashMemcard_DlgTestEnd;
static char sReg_clashMemCard_Operation;
static char sReg_clashMemcard_SetSettings;
static char sReg_clashMemcard_SetSettings7;
static char sReg_clashMemcard_SetAudioSetting;
static char sReg_clashMemcard_GetSettings;
static char sReg_clashMemcard_GetSettings8;
static char sReg_clashMemcard_DefaultSettings;
static char sReg_clashMemcard_GetCurrentGame;
static char sReg_clashMemcard_GetFileInformation;
static char sReg_clashMemcard_ResetStoryMode;
static char sReg_clashMemcard_PlayTimerStart;
static char sReg_clashMemcard_PlayTimerStop;
static char sReg_clashMemcard_ResetBackupSettings;
static char sReg_clashMemcard_ResetSettings;
static char sReg_clashMemcard_CheckSettings;
static char sReg_clashMemcard_CheckAudio;
static char sReg_clashMemcard_IsHardDriveFull;
static char sReg_clashMemcard_XBOXFreeSpace;
static char sReg_clashMemcard_GetStatus;
static char sReg_clashMemcard_GetTaskResult;
static char sReg_clashMemcard_GetSaveStatus;
static char sReg_clashMemcard_GetSettingsExist;
static char sReg_clashMemcard_GetSettingsAutosaveOn;
static char sReg_clashMemcard_GetAutosaveCheck;
static char sReg_clashMemcard_SetAutosaveCheck;
static char sReg_clashMemcard_IsJuiceOn;
static char sReg_clashMemcard_GetAutosavePrompt;
static char sReg_clashMemcard_ResetAutosavePrompt;
static char sReg_clashMemcard_GetContinueOverride;
static char sReg_clashMemcard_SetAutosaveParam;
static char sReg_clashMemcard_GetPS2NoCardFlag;
static char sReg_clashMemcard_SetLastSaveGameParam;
static char sReg_clashMemcard_GetOverwriteSettingsFlag;
static char sReg_clashMemcard_SetOverwriteSettingsFlag;
static char sReg_clashMemcard_GetOverwriteSavegameFlag;
static char sReg_clashMemcard_SetOverwriteSavegameFlag;
static char sReg_clashMemcard_GetOnlineBootFlowFlag;
static char sReg_clashMemcard_GetAutosaveOn;
static char sReg_clashMemcard_SetAutosaveOn;
static char sReg_clashMemcard_IsHardDriveLow;
static char sReg_clashMemcard_DynamicOverestimation;
static char sReg_clashMemcard_XBOXFreeBlocksFlag;
static char sReg_clashMemcard_GetCardRemoved;
static char sReg_clashMemcard_SetCardRemoved;
static char sReg_clashMemcard_CardRemoved_AutoOff;
static char sReg_clashMemcard_SetBootFlag;
static char sReg_clashMemcard_GetXBOXCorruptSettings;
static char sReg_clashMemcard_GetNGCInsufContinue;
static char sReg_clashMemcard_GetFilesPresent;
static char sReg_clashMemcard_ResetFilesPresent;
static char sReg_clashMemcard_GetLastSaveIndex;
static char sReg_clashMemcard_GetLastUserChoice;
static char sReg_clashMemcard_GetLastUserChoiceReset;
static char sReg_clashMemcard_ResetLastUserChoice;
static char sReg_clashMemcard_GetNGCNoMsgBoxKill;
static char sReg_clashMemcard_GetNoMsgBoxSpawn;
static char sReg_clashMemcard_SetNoMsgBoxSpawn;
static char sReg_clashMemcard_GetNGCMonitorHalt;
static char sReg_clashMemcard_SetNGCMonitorHalt;
static char sReg_clashMemcard_GetNewGameCheckOn;
static char sReg_clashMemcard_SetNewGameCheckOn;
static char sReg_clashMemcard_SetContinueOverride;
static char sReg_clashMemcard_SetSkipChoice;

static void __static_initialization_and_destruction_0(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            sMemcardScreenLeft = 320.0f - lbl_8066BB3C * 0.5f;
            sMemcardScreenRight = sMemcardScreenLeft + lbl_8066BB3C * 0.5f;
            sMemcardScreenTop = 240.0f - lbl_8066BB40 * 0.5f;
            sMemcardScreenBottom = lbl_8066BB40 * 0.5f + sMemcardScreenTop - 12.0f;
            fn_8044C35C(&sReg_clashMemcard_MemOption, lbl_80491120, (void *)clashMemcard_MemOption, lbl_80491138, 49);
            fn_8044B11C(&sReg_clashMemcard_DlgTest, lbl_8049116C, (void *)clashMemcard_DlgTest, lbl_80491138, 63);
            fn_8044B11C(&sReg_clashMemcard_DlgTestEnd, lbl_80491184, (void *)clashMemcard_DlgTestEnd, lbl_80491138, 68);
            fn_8044E180(&sReg_clashMemCard_Operation, lbl_8049119C, (void *)clashMemCard_Operation, lbl_80491138, 75);
            fn_8044E4E8(&sReg_clashMemcard_SetSettings, lbl_804911B4, (void *)clashMemcard_SetSettings, lbl_80491138, 101);
            fn_8044C9E4(&sReg_clashMemcard_SetSettings7, lbl_804911D0, (void *)clashMemcard_SetSettings7, lbl_80491138, 137);
            fn_8044C35C(&sReg_clashMemcard_SetAudioSetting, lbl_804911EC, (void *)clashMemcard_SetAudioSetting, lbl_80491138, 143);
            fn_8044AF58(&sReg_clashMemcard_GetSettings, lbl_8049120C, (void *)clashMemcard_GetSettings, lbl_80491138, 171);
            fn_8044AF58(&sReg_clashMemcard_GetSettings8, lbl_80491228, (void *)clashMemcard_GetSettings8, lbl_80491138, 212);
            fn_8044B11C(&sReg_clashMemcard_DefaultSettings, lbl_80491244, (void *)clashMemcard_DefaultSettings, lbl_80491138, 217);
            fn_8044AF58(&sReg_clashMemcard_GetCurrentGame, lbl_80491264, (void *)clashMemcard_GetCurrentGame, lbl_80491138, 251);
            fn_8044D060(&sReg_clashMemcard_GetFileInformation, lbl_80491280, (void *)clashMemcard_GetFileInformation, lbl_80491138, 339);
            fn_8044C35C(&sReg_clashMemcard_ResetStoryMode, lbl_804912A0, (void *)clashMemcard_ResetStoryMode, lbl_80491138, 350);
            fn_8044B11C(&sReg_clashMemcard_PlayTimerStart, lbl_804912BC, (void *)clashMemcard_PlayTimerStart, lbl_80491138, 356);
            fn_8044B11C(&sReg_clashMemcard_PlayTimerStop, lbl_804912D8, (void *)clashMemcard_PlayTimerStop, lbl_80491138, 361);
            fn_8044B11C(&sReg_clashMemcard_ResetBackupSettings, lbl_804912F4, (void *)clashMemcard_ResetBackupSettings, lbl_80491138, 366);
            fn_8044B11C(&sReg_clashMemcard_ResetSettings, lbl_80491318, (void *)clashMemcard_ResetSettings, lbl_80491138, 371);
            fn_8044E8F0(&sReg_clashMemcard_CheckSettings, lbl_80491334, (void *)clashMemcard_CheckSettings, lbl_80491138, 423);
            fn_8044D270(&sReg_clashMemcard_CheckAudio, lbl_80491350, (void *)clashMemcard_CheckAudio, lbl_80491138, 435);
            fn_8044BBC8(&sReg_clashMemcard_IsHardDriveFull, lbl_80491368, (void *)clashMemcard_IsHardDriveFull, lbl_80491138, 447);
            fn_8044B11C(&sReg_clashMemcard_XBOXFreeSpace, lbl_80491388, (void *)clashMemcard_XBOXFreeSpace, lbl_80491138, 452);
            fn_8044BBC8(&sReg_clashMemcard_GetStatus, lbl_804913A4, (void *)clashMemcard_GetStatus, lbl_80491138, 457);
            fn_8044BBC8(&sReg_clashMemcard_GetTaskResult, lbl_804913BC, (void *)clashMemcard_GetTaskResult, lbl_80491138, 462);
            fn_8044BBC8(&sReg_clashMemcard_GetSaveStatus, lbl_804913D8, (void *)clashMemcard_GetSaveStatus, lbl_80491138, 467);
            fn_8044BBC8(&sReg_clashMemcard_GetSettingsExist, lbl_804913F4, (void *)clashMemcard_GetSettingsExist, lbl_80491138, 477);
            fn_8044BBC8(&sReg_clashMemcard_GetSettingsAutosaveOn, lbl_80491414, (void *)clashMemcard_GetSettingsAutosaveOn, lbl_80491138, 487);
            fn_8044BBC8(&sReg_clashMemcard_GetAutosaveCheck, lbl_80491438, (void *)clashMemcard_GetAutosaveCheck, lbl_80491138, 497);
            fn_8044C35C(&sReg_clashMemcard_SetAutosaveCheck, lbl_80491458, (void *)clashMemcard_SetAutosaveCheck, lbl_80491138, 506);
            fn_8044BBC8(&sReg_clashMemcard_IsJuiceOn, lbl_80491478, (void *)clashMemcard_IsJuiceOn, lbl_80491138, 516);
            fn_8044BBC8(&sReg_clashMemcard_GetAutosavePrompt, lbl_80491490, (void *)clashMemcard_GetAutosavePrompt, lbl_80491138, 534);
            fn_8044B11C(&sReg_clashMemcard_ResetAutosavePrompt, lbl_804914B0, (void *)clashMemcard_ResetAutosavePrompt, lbl_80491138, 539);
            fn_8044BBC8(&sReg_clashMemcard_GetContinueOverride, lbl_804914D4, (void *)clashMemcard_GetContinueOverride, lbl_80491138, 550);
            fn_8044C35C(&sReg_clashMemcard_SetAutosaveParam, lbl_804914F8, (void *)clashMemcard_SetAutosaveParam, lbl_80491138, 555);
            fn_8044BBC8(&sReg_clashMemcard_GetPS2NoCardFlag, lbl_80491518, (void *)clashMemcard_GetPS2NoCardFlag, lbl_80491138, 566);
            fn_8044C35C(&sReg_clashMemcard_SetLastSaveGameParam, lbl_80491538, (void *)clashMemcard_SetLastSaveGameParam, lbl_80491138, 571);
            fn_8044BBC8(&sReg_clashMemcard_GetOverwriteSettingsFlag, lbl_8049155C, (void *)clashMemcard_GetOverwriteSettingsFlag, lbl_80491138, 582);
            fn_8044C35C(&sReg_clashMemcard_SetOverwriteSettingsFlag, lbl_80491584, (void *)clashMemcard_SetOverwriteSettingsFlag, lbl_80491138, 591);
            fn_8044BBC8(&sReg_clashMemcard_GetOverwriteSavegameFlag, lbl_804915AC, (void *)clashMemcard_GetOverwriteSavegameFlag, lbl_80491138, 602);
            fn_8044C35C(&sReg_clashMemcard_SetOverwriteSavegameFlag, lbl_804915D4, (void *)clashMemcard_SetOverwriteSavegameFlag, lbl_80491138, 611);
            fn_8044BBC8(&sReg_clashMemcard_GetOnlineBootFlowFlag, lbl_804915FC, (void *)clashMemcard_GetOnlineBootFlowFlag, lbl_80491138, 621);
            fn_8044BBC8(&sReg_clashMemcard_GetAutosaveOn, lbl_80491620, (void *)clashMemcard_GetAutosaveOn, lbl_80491138, 632);
            fn_8044C35C(&sReg_clashMemcard_SetAutosaveOn, lbl_8049163C, (void *)clashMemcard_SetAutosaveOn, lbl_80491138, 641);
            fn_8044BBC8(&sReg_clashMemcard_IsHardDriveLow, lbl_80491658, (void *)clashMemcard_IsHardDriveLow, lbl_80491138, 646);
            fn_8044BBC8(&sReg_clashMemcard_DynamicOverestimation, lbl_80491674, (void *)clashMemcard_DynamicOverestimation, lbl_80491138, 651);
            fn_8044BBC8(&sReg_clashMemcard_XBOXFreeBlocksFlag, lbl_80491698, (void *)clashMemcard_XBOXFreeBlocksFlag, lbl_80491138, 662);
            fn_8044BBC8(&sReg_clashMemcard_GetCardRemoved, lbl_804916B8, (void *)clashMemcard_GetCardRemoved, lbl_80491138, 673);
            fn_8044C35C(&sReg_clashMemcard_SetCardRemoved, lbl_804916D4, (void *)clashMemcard_SetCardRemoved, lbl_80491138, 682);
            fn_8044B11C(&sReg_clashMemcard_CardRemoved_AutoOff, lbl_804916F0, (void *)clashMemcard_CardRemoved_AutoOff, lbl_80491138, 692);
            fn_8044C35C(&sReg_clashMemcard_SetBootFlag, lbl_80491714, (void *)clashMemcard_SetBootFlag, lbl_80491138, 701);
            fn_8044BBC8(&sReg_clashMemcard_GetXBOXCorruptSettings, lbl_80491730, (void *)clashMemcard_GetXBOXCorruptSettings, lbl_80491138, 712);
            fn_8044BBC8(&sReg_clashMemcard_GetNGCInsufContinue, lbl_80491754, (void *)clashMemcard_GetNGCInsufContinue, lbl_80491138, 723);
            fn_8044BBC8(&sReg_clashMemcard_GetFilesPresent, lbl_80491778, (void *)clashMemcard_GetFilesPresent, lbl_80491138, 729);
            fn_8044B11C(&sReg_clashMemcard_ResetFilesPresent, lbl_80491798, (void *)clashMemcard_ResetFilesPresent, lbl_80491138, 743);
            fn_8044BBC8(&sReg_clashMemcard_GetLastSaveIndex, lbl_804917B8, (void *)clashMemcard_GetLastSaveIndex, lbl_80491138, 749);
            fn_8044BBC8(&sReg_clashMemcard_GetLastUserChoice, lbl_804917D8, (void *)clashMemcard_GetLastUserChoice, lbl_80491138, 755);
            fn_8044BBC8(&sReg_clashMemcard_GetLastUserChoiceReset, lbl_804917F8, (void *)clashMemcard_GetLastUserChoiceReset, lbl_80491138, 762);
            fn_8044B11C(&sReg_clashMemcard_ResetLastUserChoice, lbl_8049181C, (void *)clashMemcard_ResetLastUserChoice, lbl_80491138, 767);
            fn_8044BBC8(&sReg_clashMemcard_GetNGCNoMsgBoxKill, lbl_80491840, (void *)clashMemcard_GetNGCNoMsgBoxKill, lbl_80491138, 779);
            fn_8044BBC8(&sReg_clashMemcard_GetNoMsgBoxSpawn, lbl_80491860, (void *)clashMemcard_GetNoMsgBoxSpawn, lbl_80491138, 790);
            fn_8044C35C(&sReg_clashMemcard_SetNoMsgBoxSpawn, lbl_80491880, (void *)clashMemcard_SetNoMsgBoxSpawn, lbl_80491138, 799);
            fn_8044BBC8(&sReg_clashMemcard_GetNGCMonitorHalt, lbl_804918A0, (void *)clashMemcard_GetNGCMonitorHalt, lbl_80491138, 810);
            fn_8044C35C(&sReg_clashMemcard_SetNGCMonitorHalt, lbl_804918C0, (void *)clashMemcard_SetNGCMonitorHalt, lbl_80491138, 819);
            fn_8044BBC8(&sReg_clashMemcard_GetNewGameCheckOn, lbl_804918E0, (void *)clashMemcard_GetNewGameCheckOn, lbl_80491138, 830);
            fn_8044C35C(&sReg_clashMemcard_SetNewGameCheckOn, lbl_80491900, (void *)clashMemcard_SetNewGameCheckOn, lbl_80491138, 839);
            fn_8044C35C(&sReg_clashMemcard_SetContinueOverride, lbl_80491920, (void *)clashMemcard_SetContinueOverride, lbl_80491138, 849);
            fn_8044C35C(&sReg_clashMemcard_SetSkipChoice, lbl_80491944, (void *)clashMemcard_SetSkipChoice, lbl_80491138, 854);
        } else {
        }
    }
}

void fn_8010A40C(void)
{
    __static_initialization_and_destruction_0(1, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_8010A40C;
