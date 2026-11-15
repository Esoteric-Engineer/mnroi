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
