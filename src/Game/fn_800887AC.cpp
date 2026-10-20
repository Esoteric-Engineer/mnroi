// The .nsc mission/arena script parser: one keyword per line into a NameTable, which it appends to the script table's records[].
// The keyword-to-field map is in docs/characters.md section 4.
// Owns the .rodata string pool at 0x804887C4-0x80488984.
// `new NameTable` is what renamed fn_801ACED4 to __builtin_new and fn_800871EC to __9NameTable.
// Every empty if/else arm below is a release-stripped diagnostic, not a mistake.

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
    char unk19C[8];
    int unk1A4;
} ScriptTable;

extern "C" {

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

}

inline int sn_return_decl(int a) { return a; }

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
