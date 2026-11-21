// The chronicle file: the clashsp.nsc/clashmp.nsc tables, their NameTable records, mission start and the .nsc parser; docs/story.md row 2.
// The parser's keyword-to-field map is in docs/characters.md section 4.
// Owns .rodata 0x80488798-0x80488984, the two tables' .bss and the two .sdata flags.

typedef struct NameTable
{
    char unk0[0x20];
    char unk20[0x200];
    char unk220[0x20];
    char unk240[0x20];
    char unk260[0x20];
    char unk280[0x20];
    char unk2A0[0x20];
    char unk2C0[0x20];
    char unk2E0[0x20];
    char unk300[0x20];
    char unk320[0x20];
    char list340[3][0x20];
    char list3A0[3][0x20];
    char list400[3][0x20];
    int unk460;
    int unk464;
    float unk468;
    int unk46C;
    int unk470;
    int unk474;
    unsigned char unk478;
    unsigned char unk479;
    unsigned char unk47A;
    unsigned char count340;
    unsigned char count3A0;
    unsigned char count400;
    char unk47E[2];
    int unk480[4];
    char unk490[0x14];
    char unk4A4[9][0x20];
    int unk5C4;

    NameTable();
} NameTable;

typedef struct ScriptTable
{
    unsigned int profileId;   // +0x0
    unsigned int gameType;    // +0x4
    int count;                // +0x8
    NameTable *records[100];  // +0xC
    unsigned int unk19C;      // its low byte is a character id
    unsigned char unk1A0[4];  // character slots
    int unk1A4;               // current record
    int unk1A8;
    int unk1AC;
    void *unk1B0;             // the master script
    int unk1B4;
} ScriptTable;

struct GameState
{
    char pad0[0x5BB];
    char levelEnd;   // +0x5BB, ends lbl_805526AC
    char pad5BC[0x1F];
    char end5DB;     // +0x5DB, ends lbl_805526CC
    char pad5DC[0x1F];
    char end5FB;     // +0x5FB, ends lbl_805526EC
};

extern "C" {

extern void *memset(void *dst, int c, unsigned n);
extern void __builtin_delete(void *p);

extern void fn_801ACE74(const char *name);
extern int fn_800887AC(register ScriptTable *table, const char *path);
extern int fn_80087938(ScriptTable *table, int index);
extern void Script_Destroy(void *script);

extern int fn_80433E08(NameTable *rec);
extern int fn_80443398(NameTable *rec);
extern void *fn_80443678(int index, int remap, int alt);
extern void *fn_804425CC(ScriptTable *table);
extern void fn_8044324C(NameTable *rec, int a);
extern int fn_80442C00(NameTable *rec, unsigned char slot);
extern void fn_804435D0(int index, int a);
extern void fn_80443640(int index, int a);
extern void fn_80443608(int index, int a);
extern void fn_8044374C(int index, int a);
extern void fn_804436D4(int index, int unlocked, int remap);
extern NameTable *fn_804332C4(ScriptTable *table, int index);
extern NameTable *fn_804326B4(ScriptTable *table);
extern unsigned int fn_80431D84(ScriptTable *table);
extern int fn_804432D8(NameTable *rec);
extern unsigned int fn_80442E7C(NameTable *rec);
extern unsigned char fn_80442FC4(NameTable *rec);
extern unsigned char fn_80443020(NameTable *rec);
extern unsigned char fn_8044307C(NameTable *rec);
extern int fn_80443308(NameTable *rec);
extern int fn_80443338(NameTable *rec);
extern int fn_80443368(NameTable *rec);
extern int fn_804433C8(NameTable *rec);
extern int fn_804433F8(NameTable *rec);
extern int fn_80443428(NameTable *rec);
extern int fn_80443488(NameTable *rec);
extern void fn_804432AC(NameTable *rec);
extern int fn_804434B8(ScriptTable *table);
extern int fn_804435A4(ScriptTable *table);
extern void fn_80443518(ScriptTable *table, int flag);
extern void fn_80443548(ScriptTable *table, int flag);
extern void fn_8044357C(ScriptTable *table, int flag);
extern int fn_80443458(NameTable *rec);
extern char *fn_80442A54(NameTable *rec);
extern char *fn_8043265C(NameTable *rec);
extern char *fn_80432688(NameTable *rec);
extern void *Script_Create(char *name, int a);
extern int stricmp(const char *a, const char *b);
extern int sscanf(const char *str, const char *fmt, ...);
extern int sprintf(char *dst, const char *fmt, ...);
extern int strcmp(const char *a, const char *b);
extern int strspn(const char *s, const char *accept);
extern char *strlwr(char *s);
extern int atoi(const char *s);
extern double atof(const char *s);
extern void *fn_801A8368(const char *name, const char *mode, int flags); // open a text file
extern void fn_801A875C(void *file);
extern int fn_801A8C08(char *buf, int size, void *file);                 // read one line
extern int fn_801A8C84(void *file);                                      // at end of file
extern void fn_801A953C(void *file);
extern void fn_801B738C(char *name);
extern void fn_80442918(NameTable *rec, char *name);
extern void fn_80442964(NameTable *rec, char *name);
extern void fn_804429B4(NameTable *rec, char *name);
extern void fn_80442A04(NameTable *rec, char *name);
extern void fn_80442A80(NameTable *rec, char *name);
extern void fn_80442AD0(NameTable *rec, char *name);
extern void fn_80442B20(NameTable *rec, char *name);
extern void fn_80442B70(NameTable *rec, char *name);
extern void fn_80442BC0(NameTable *rec, int a, int b, int c, int d);
extern void fn_80442C3C(NameTable *rec, char *name);
extern void fn_80442C8C(NameTable *rec, char *name);
extern void fn_80442D24(NameTable *rec, char *name);
extern void fn_80442DBC(NameTable *rec, char *name);
extern void fn_80442E54(NameTable *rec, int value);
extern void fn_80442EA8(NameTable *rec, int value);
extern void fn_80442ED0(NameTable *rec, float value);
extern void fn_80442EF8(NameTable *rec, int value);
extern void fn_80442F20(NameTable *rec, int value);
extern void fn_80442F48(NameTable *rec, int value);
extern void fn_80442F70(NameTable *rec, int value);
extern void fn_80442F98(NameTable *rec, int value);
extern void fn_80442FF4(NameTable *rec, int value);
extern void fn_80443050(NameTable *rec, int value);
extern void fn_804430AC(NameTable *rec, char *name);
extern void fn_804430FC(NameTable *rec, char *n0, char *n1, char *n2, char *n3, char *n4, char *n5,
                        char *n6, char *n7, char *n8);
extern char *strncpy(char *dst, const char *src, unsigned int n);

extern GameState lbl_80552110;
extern char lbl_805526AC[];
extern char lbl_805526CC[];
extern char lbl_805526EC[];

extern int fn_8042D444(ScriptTable *table);
extern int fn_804434E8(ScriptTable *table);

void fn_800872C4(register NameTable *rec);
void fn_80087580(register ScriptTable *table);
void fn_80087658(register ScriptTable *table);
void fn_800876D4(register ScriptTable *table);
int fn_80087CF8(register ScriptTable *table, unsigned char ch);
int fn_80087D8C(register ScriptTable *table, unsigned char ch);
int fn_8008856C(register ScriptTable *table, int index, int flag);
int fn_80431DB0(ScriptTable *table); // table->unk1A4

}

inline int sn_return_decl(int a) { return a; }

int lbl_8066B8D0 = 0; // tables loaded
int lbl_8066B8D4 = 0;
ScriptTable lbl_8054ED80; // clashsp.nsc
ScriptTable lbl_8054EF38; // clashmp.nsc

extern "C" int fn_80087040(void)
{
    if (lbl_8066B8D0) {
        return 0;
    }
    fn_80087658(&lbl_8054ED80);
    fn_801ACE74("GAME:CHRONS");
    fn_800887AC(&lbl_8054ED80, "clashsp.nsc");
    fn_801ACE74("\0"); // not "", which would pool with the parser's
    fn_80087658(&lbl_8054EF38);
    fn_801ACE74("GAME:CHRONS");
    fn_800887AC(&lbl_8054EF38, "clashmp.nsc");
    fn_801ACE74("\0");
    lbl_8066B8D0 = 1;
    return 1;
}

extern "C" int fn_80087100(void)
{
    lbl_8066B8D4 = 1;
    return 1;
}

extern "C" void fn_8008712C(void)
{
    lbl_8066B8D4 = 0;
}

extern "C" int fn_80087150(const char *path)
{
    fn_80087580(&lbl_8054ED80);
    return fn_800887AC(&lbl_8054ED80, path);
}

extern "C" int fn_800871A8(void)
{
    return fn_80087150("clashsp.nsc");
}

NameTable::NameTable()
{
    fn_800872C4(this);
}

extern "C" void fn_8008722C(register NameTable *rec, int inChrg)
{
    if (inChrg & 1) {
        __builtin_delete(rec);
    } else {
    }
}

extern "C" void fn_8008727C(register NameTable *rec)
{
    if (rec) {
        fn_8008722C(rec, 3);
    } else {
    }
}

extern "C" void fn_800872C4(register NameTable *rec)
{
    int i;
    int j;

    rec->unk0[0] = 0;
    rec->unk20[0] = 0;
    rec->unk260[0] = 0;
    rec->unk280[0] = 0;
    rec->unk2A0[0] = 0;
    rec->unk2E0[0] = 0;
    rec->unk300[0] = 0;
    rec->unk320[0] = 0;
    rec->unk478 = 0;
    rec->unk479 = 0;
    rec->unk464 = 0;
    rec->unk468 = 0.0f;
    rec->unk46C = 10000;
    rec->unk5C4 = 2;
    rec->unk470 = 10;
    rec->unk474 = 5000;
    for (i = 0; i < 4; i++) {
        rec->unk480[i] = -1;
    }
    for (j = 0; j < 9; j++) {
        rec->unk4A4[j][0] = 0;
    }
    rec->count400 = 0;
    rec->count3A0 = 0;
    rec->count340 = 0;
    memset(rec->unk490, 0, 0x10);
}

extern "C" void *fn_80087424(register NameTable *rec)
{
    if (fn_80433E08(rec)) {
        if (fn_80443398(rec)) {
            return fn_80443678(rec->unk47A, 0, 1);
        } else {
            return fn_80443678(rec->unk47A, 0, 0);
        }
    } else {
        return fn_80443678(rec->unk478, 0, 0);
    }
}

extern "C" ScriptTable *fn_800874F0(register ScriptTable *table)
{
    fn_80087658(table);
    return table;
}

extern "C" void fn_80087530(register ScriptTable *table, int inChrg)
{
    if (inChrg & 1) {
        __builtin_delete(table);
    } else {
    }
}

extern "C" void fn_80087580(register ScriptTable *table)
{
    unsigned int i;

    for (i = 0; i < table->count; i++) {
        if (table->records[i]) {
            fn_8008727C(table->records[i]);
            table->records[i] = 0;
        }
    }
    if (fn_804425CC(table)) {
        Script_Destroy(fn_804425CC(table));
        table->unk1B0 = 0;
    }
}

extern "C" void fn_80087658(register ScriptTable *table)
{
    table->profileId = 0;
    table->gameType = 0;
    table->unk1A4 = 0;
    table->count = 0;
    table->unk1B4 = 0;
    memset(table->records, 0, 0x190);
    table->unk1B0 = 0;
    fn_800876D4(table);
}

extern "C" void fn_800876D4(register ScriptTable *table)
{
    int i;

    memset(table->unk1A0, 0, 4);
    table->unk1A0[0] = 10;
    table->unk19C = 0;
    table->unk1AC = 1;
    for (i = 0; i < 100; i++) {
        if (table->records[i]) {
            fn_8044324C(table->records[i], 0);
        }
    }
    if (table->count) {
        fn_8008856C(table, 0, 0);
    }
}

extern "C" int fn_800877AC(register ScriptTable *table)
{
    return fn_80087938(table, table->unk1A4);
}

extern "C" void fn_800877F4(register ScriptTable *table, NameTable *rec)
{
    int i;
    int id;

    for (i = 0; i < 4; i++) {
        id = fn_80442C00(rec, i);
        if (id < 0) {
            continue;
        }
        if (id > 99999) {
            fn_804435D0(id - 100000, 1);
        } else if (id > 9999) {
            fn_80443640(id - 10000, 1);
        } else if (id > 999) {
            fn_80443608(id - 1000, 1);
        } else if (id > 99) {
            fn_8044374C(id - 100, 1);
        } else if (id >= 0) {
            fn_804436D4(id, 1, 0);
        } else {
        }
    }
}

extern "C" int fn_80087938(register ScriptTable *table, int index)
{
    NameTable *rec = fn_804332C4(table, index);

    if (!rec || fn_804432D8(rec)) {
        return 0;
    }
    if (table->unk1AC & 0x40) {
        fn_80443548(table, 4);
        fn_80443548(table, 0x40);
    }
    if (table->unk1AC & 0x80) {
        fn_80443548(table, 0x10);
        fn_80443548(table, 0x80);
    }
    if (table->unk1AC & 0x100) {
        fn_80443548(table, 8);
        fn_80443548(table, 0x100);
    }
    table->unk1B4 = fn_80442E7C(rec);
    if (fn_80433E08(rec)) {
        fn_80087CF8(table, fn_80442FC4(rec));
        fn_80087D8C(table, table->unk19C);
        fn_80443548(table, 2);
    }
    if (fn_80443338(rec)) {
        fn_80087CF8(table, fn_80442FC4(rec));
        fn_80087D8C(table, fn_80443020(rec));
        fn_80443548(table, 8);
    }
    if (fn_80443368(rec)) {
        fn_80087CF8(table, fn_8044307C(rec));
        fn_80087D8C(table, table->unk19C);
        fn_80443548(table, 4);
    }
    if (fn_80443428(rec)) {
        fn_80443548(table, 1);
        fn_80443518(table, 0x10);
    }
    if (fn_80443308(rec)) {
        fn_80443548(table, 1);
        fn_80443518(table, 2);
    }
    if (fn_804433C8(rec)) {
        fn_80443548(table, 1);
        fn_80443518(table, 8);
    }
    if (fn_804433F8(rec)) {
        fn_80443548(table, 1);
        fn_8044357C(table, 4);
    }
    if (fn_804434B8(table)) {
        if (fn_80443020(rec)) {
            fn_80087D8C(table, fn_80443020(rec));
        }
        fn_8044357C(table, 1);
    }
    if (!fn_804435A4(table)) {
        fn_8044357C(table, 1);
    }
    if (fn_80443488(rec)) {
        fn_804432AC(rec);
        fn_80443518(table, 0x200);
    } else {
        fn_8044324C(rec, 1);
    }
    return 1;
}

extern "C" int fn_80087C78(register ScriptTable *table)
{
    int n = 0;
    unsigned int i;

    for (i = 0; i < 4; i++) {
        if (table->unk1A0[i]) {
            n++;
        }
    }
    return n;
}

extern "C" int fn_80087CF8(register ScriptTable *table, unsigned char ch)
{
    unsigned int i;

    for (i = 0; i < 4; i++) {
        if (table->unk1A0[i] == ch) {
            table->unk1A0[i] = 0;
            return 1;
        }
    }
    return 0;
}

extern "C" int fn_80087D8C(register ScriptTable *table, unsigned char ch)
{
    unsigned int i;

    for (i = 0; i < 4; i++) {
        if (table->unk1A0[i] == 0) {
            table->unk1A0[i] = ch;
            return 1;
        }
    }
    fn_804436D4(ch, 1, 0);
    return 0;
}

extern "C" NameTable *fn_80087E40(register ScriptTable *table)
{
    NameTable *cur = fn_804326B4(&lbl_8054ED80);
    int unused = 0;
    unsigned int i;

    fn_80443518(table, 0x100);
    for (i = 0; i < fn_80431D84(table); i++) {
        if (!fn_80443338(table->records[i])) {
            continue;
        }
        if (fn_804432D8(table->records[i])) {
            continue;
        }
        return table->records[i];
    }
    return 0;
}

extern "C" NameTable *fn_80087F40(register ScriptTable *table)
{
    NameTable *cur = fn_804326B4(&lbl_8054ED80);
    int ch = 0;
    unsigned int i;

    ch = fn_80443020(cur);
    fn_80443518(table, 0x40);
    for (i = 0; i < fn_80431D84(table); i++) {
        if (fn_8044307C(table->records[i]) != ch) {
            continue;
        }
        if (fn_804432D8(table->records[i])) {
            continue;
        }
        if (fn_80443368(table->records[i])) {
            return table->records[i];
        }
    }
    return 0;
}

extern "C" NameTable *fn_80088078(register ScriptTable *table)
{
    NameTable *cur = fn_804326B4(&lbl_8054ED80);
    unsigned int i;

    fn_80443518(table, 0x80);
    for (i = table->unk1A4; i < fn_80431D84(table); i++) {
        if (fn_804432D8(table->records[i])) {
            continue;
        }
        if (fn_80443458(table->records[i])) {
            return table->records[i];
        }
    }
    return 0;
}

extern "C" NameTable *fn_8008816C(register ScriptTable *table, int slot)
{
    unsigned int i;

    for (i = 0; i < fn_80431D84(table); i++) {
        if (fn_80442FC4(table->records[i]) != table->unk1A0[slot]) {
            continue;
        }
        if (fn_804432D8(table->records[i])) {
            continue;
        }
        if (fn_80433E08(table->records[i])) {
            continue;
        }
        return table->records[i];
    }
    return 0;
}

extern "C" NameTable *fn_80088280(register ScriptTable *table, int slot)
{
    NameTable *found = 0;
    unsigned int i;

    for (i = 0; i < fn_80431D84(table); i++) {
        if (fn_80442FC4(table->records[i]) != table->unk1A0[slot]) {
            continue;
        }
        if (fn_80433E08(table->records[i])) {
            continue;
        }
        found = table->records[i];
    }
    return found;
}

extern "C" NameTable *fn_80088374(register ScriptTable *table, int slot)
{
    unsigned int i;

    if (!table->unk1A0[slot]) {
        return 0;
    }
    for (i = 0; i < fn_80431D84(table); i++) {
        if (fn_80442FC4(table->records[i]) != table->unk1A0[slot]) {
            continue;
        }
        if (fn_804432D8(table->records[i])) {
            continue;
        }
        if (fn_80433E08(table->records[i])) {
            return table->records[i];
        }
    }
    return 0;
}

extern "C" int fn_800884A4(register ScriptTable *table, const char *name, int flag)
{
    unsigned int i;
    NameTable *rec;

    for (i = 0; i < fn_80431D84(table); i++) {
        rec = fn_804332C4(table, i);
        if (stricmp(name, fn_8043265C(rec)) == 0) {
            return fn_8008856C(table, i, flag);
        }
    }
    return 0;
}

extern "C" int fn_8008856C(register ScriptTable *table, int index, int flag)
{
    NameTable *rec = fn_804332C4(table, index);

    if (fn_804425CC(table)) {
        Script_Destroy(fn_804425CC(table));
        table->unk1B0 = 0;
    }
    if (*fn_80442A54(rec) != 0) {
        table->unk1B0 = Script_Create(fn_80442A54(rec), 1);
    }
    table->unk1A4 = index;
    strncpy(lbl_805526EC, fn_8043265C(rec), 0x20);
    lbl_80552110.end5FB = 0;
    strncpy(lbl_805526AC, fn_80432688(rec), 0x20);
    lbl_80552110.levelEnd = 0;
    strncpy(lbl_805526CC, fn_8043265C(rec), 0x20);
    lbl_80552110.end5DB = 0;
    if (fn_80433E08(rec) || fn_80443368(rec)) {
        return 1;
    }
    if (fn_80443308(rec) || fn_804433F8(rec)) {
        table->unk19C = fn_80443020(rec);
    } else {
        table->unk19C = 0;
    }
    return 1;
}

extern "C" void fn_80088740(register ScriptTable *table, void *actor, int flag)
{
    int unused = 0;
    NameTable *rec = fn_804332C4(table, fn_80431DB0(table));

    if (!flag) {
    }
}

extern "C" int fn_800887AC(register ScriptTable *table, const char *path)
{
    void *file;
    char line[0x200];
    int lineNo = 0;
    unsigned int n; // the sscanf count; unsigned, which is what makes the > tests cmplwi
    char key[0x40];
    char p1[0x40];
    char p2[0x40];
    char p3[0x40];
    char p4[0x40];
    char p5[0x40];
    char p6[0x40];
    char p7[0x40];
    char p8[0x40];
    char p9[0x40];
    int open = 0;
    NameTable *rec = 0;
    int rewards[4];
    unsigned int value;

    file = fn_801A8368(path, "rt", 9);
    if (file == 0) {
        return 0;
    }

    table->unk1A4 = 0;
    table->count = 0;
    fn_801A953C(file);

    while (!fn_801A8C84(file)) {
        lineNo++;
        if (fn_801A8C08(line, 0x1FF, file) == 0) {
            break;
        }
        if (line[0] == ';' || line[0] == '#' || (line[0] == '/' && line[1] == '/')) {
            continue;
        }
        if (strspn(line, " \r\t\n")) {
            continue;
        }
        if (line[0] == '\0') {
            continue;
        }

        sscanf(line, "%s", key);
        strlwr(key);

        if (strcmp(key, "profileid") == 0) {
            n = sscanf(line, "%s %s", key, p1);
            if (n == 2) {
                table->profileId = atoi(p1);
                if (table->profileId > 5) {
                    table->profileId = 0;
                }
            } else {
            }
        } else if (strcmp(key, "gametype") == 0) {
            n = sscanf(line, "%s %s", key, p1);
            if (n == 2) {
                table->gameType = atoi(p1);
            } else {
            }
        } else if (strcmp(key, "mission") == 0) {
            if (open) {
            }
            n = sscanf(line, "%s %s %s %s %s", key, p1, p2, p3, p4);
            if (n > 2) {
                rec = new NameTable;
                fn_80442918(rec, p1);
                fn_80442A04(rec, p2);
                fn_804429B4(rec, p3);
                if (n > 4) {
                    fn_80442A80(rec, p4);
                }
                open = 1;
            } else {
            }
        } else if (strcmp(key, "description") == 0) {
            if (open) {
                n = sscanf(line, "%s %s\n", key, p1);
                fn_80442964(rec, p1);
            }
        } else if (strcmp(key, "rewards") == 0) {
            if (open) {
                n = sscanf(line, "%s %d %d %d %d\n", key, &rewards[0], &rewards[1], &rewards[2],
                           &rewards[3]);
                fn_80442BC0(rec, rewards[0], rewards[1], rewards[2], rewards[3]);
            }
        } else if (strcmp(key, "endmission") == 0) {
            if (open) {
                fn_80442EA8(rec, table->count);
                table->records[table->count++] = rec;
                rec = 0;
                open = 0;
            } else {
            }
        } else if (strcmp(key, "loadscreen") == 0) {
            n = sscanf(line, "%s %s %s", key, p1, p2);
            if (n <= 1) {
            } else {
                fn_80442B20(rec, p1);
                if (n == 3) {
                    fn_80442AD0(rec, p2);
                } else {
                    fn_80442AD0(rec, p1);
                }
            }
        } else if (strcmp(key, "loadtext") == 0) {
            n = sscanf(line, "%s %s", key, p1);
            if (n == 2) {
                fn_80442B70(rec, p1);
            } else {
            }
        } else if (strcmp(key, "intro") == 0) {
            n = sscanf(line, "%s %s", key, p1);
            if (n == 2) {
                fn_80442C8C(rec, p1);
            } else {
            }
        } else if (strcmp(key, "fail") == 0) {
            n = sscanf(line, "%s %s", key, p1);
            if (n == 2) {
                fn_80442DBC(rec, p1);
            } else {
            }
        } else if (strcmp(key, "extro") == 0) {
            n = sscanf(line, "%s %s", key, p1);
            if (n == 2) {
                fn_80442D24(rec, p1);
            } else {
            }
        } else if (strcmp(key, "objective") == 0) {
            n = sscanf(line, "%s %s %s", key, p1, p2);
            if (n <= 1) {
            } else {
                fn_80442B70(rec, p1);
                if (n == 3) {
                    fn_80442C3C(rec, p2);
                }
            }
        } else if (strcmp(key, "character") == 0) {
            if (sscanf(line, "%s %d", key, &value) == 2 && value <= 19) {
                fn_80442F98(rec, (unsigned char)value);
            }
        } else if (strcmp(key, "unlockchar") == 0) {
            if (sscanf(line, "%s %d", key, &value) == 2 && value <= 18) {
                fn_80442FF4(rec, (unsigned char)value);
            }
        } else if (strcmp(key, "sacrifice") == 0) {
            if (sscanf(line, "%s %d", key, &value) == 2 && value <= 19) {
                fn_80443050(rec, (unsigned char)value);
            }
        } else if (strcmp(key, "soundbanks") == 0) {
            n = sscanf(line, "%s %s %s %s %s %s %s %s %s %s", key, p1, p2, p3, p4, p5, p6, p7, p8,
                       p9);
            if (n <= 1) {
            } else {
                char none[1] = "";

                fn_804430FC(rec, p1, n > 2 ? p2 : none, n > 3 ? p3 : none, n > 4 ? p4 : none,
                            n > 5 ? p5 : none, n > 6 ? p6 : none, n > 7 ? p7 : none,
                            n > 8 ? p8 : none, n > 9 ? p9 : none);
            }
        } else if (strcmp(key, "teleportdist") == 0) {
            n = sscanf(line, "%s %s", key, p1);
            if (n == 2) {
                fn_80442ED0(rec, atof(p1));
            } else {
            }
        } else if (strcmp(key, "teleportdelay") == 0) {
            n = sscanf(line, "%s %s", key, p1);
            if (n == 2) {
                fn_80442EF8(rec, atoi(p1));
            } else {
            }
        } else if (strcmp(key, "maxblessed") == 0) {
            n = sscanf(line, "%s %s", key, p1);
            if (n == 2) {
                fn_80442F70(rec, atoi(p1));
            } else {
            }
        } else if (strcmp(key, "precutscene") == 0) {
        } else if (strcmp(key, "postcutscene") == 0) {
        } else if (strcmp(key, "unlocked") == 0) {
        } else if (strcmp(key, "unlock") == 0) {
        } else if (strcmp(key, "flags") == 0) {
            if (sscanf(line, "%s %d", key, &value) == 2) {
                fn_80442E54(rec, (unsigned short)value);
            }
        } else if (strcmp(key, "boss") == 0) {
            n = sscanf(line, "%s %s %s", key, p1, p2);
            if (n == 2) {
                fn_801B738C(p1);
                sprintf(p3, "plr_%s", p1);
                fn_804430AC(rec, p3);
            } else if (n == 3) {
                fn_801B738C(p2);
                sprintf(p3, "plr_alt%s", p2);
                fn_804430AC(rec, p3);
            } else {
            }
        } else if (strcmp(key, "replayfrequency") == 0) {
            n = sscanf(line, "%s %s", key, p1);
            if (n == 2) {
                fn_80442F20(rec, atoi(p1));
            } else {
            }
        } else if (strcmp(key, "replaydelay") == 0) {
            n = sscanf(line, "%s %s", key, p1);
            if (n == 2) {
                fn_80442F48(rec, atoi(p1));
            } else {
            }
        } else {
        }
    }

    fn_801A875C(file);
    return 0;
}

extern "C" void fn_80089710(int slot)
{
    NameTable *rec = fn_804326B4(&lbl_8054ED80);

    if (rec && !fn_804432D8(rec) && (fn_80443338(rec) || fn_80443368(rec) || fn_80443458(rec))) {
        return;
    }
    if (fn_8042D444(&lbl_8054ED80)) {
        rec = fn_80088374(&lbl_8054ED80, slot);
    } else if (fn_804434E8(&lbl_8054ED80)) {
        rec = fn_80088078(&lbl_8054ED80);
    } else {
        rec = fn_8008816C(&lbl_8054ED80, slot);
    }
    fn_8008856C(&lbl_8054ED80, fn_80442E7C(rec), 0);
}

extern "C" void fn_80089854(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            fn_800874F0(&lbl_8054ED80);
            fn_800874F0(&lbl_8054EF38);
        } else {
            fn_80087530(&lbl_8054EF38, 2);
            fn_80087530(&lbl_8054ED80, 2);
        }
    }
}

extern "C" void fn_800898E4(void)
{
    fn_80089854(1, 65535);
}

extern "C" void fn_80089920(void)
{
    fn_80089854(0, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_800898E4;
static void (*const sDtorEntry)(void) __attribute__((section(".dtors"))) = fn_80089920;
