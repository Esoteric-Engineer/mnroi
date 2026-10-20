// The command-line parser: a strtok loop over the options; docs/versus.md section 5, row 9c.
// The -mp/-vs/-timed arms fill G's role and timer fields (docs/versus.md section 4.1).

struct State {
    char pad0[0x5BB];
    char levelEnd;   // +0x5BB
    char pad1[0x1F];
    char sceneEnd;   // +0x5DB
    char pad2[0x1F];
    char missionEnd; // +0x5FB
    char pad3[0x1F];
    char chronEnd;   // +0x61B
    int levelSet;    // +0x61C
    int sceneSet;    // +0x620
    int missionSet;  // +0x624
    int mpMissionSet; // +0x628
    int chronSet;    // +0x62C
    char pad4[0x75C - 0x630];
    int timerMode;   // +0x75C
    char pad5[4];
    int timerMs;     // +0x764
};

struct Options {
    char pad0[0x74];
    short height;    // +0x74
    short width;     // +0x76
    char pad1[4];
    char depth;      // +0x7C
};

extern State lbl_80552110;
extern Options lbl_8057E430;
extern char lbl_8052EB18[];
extern char lbl_805526AC[];
extern char lbl_805526CC[];
extern char lbl_805526EC[];
extern char lbl_8055270C[];
extern char lbl_8066D568[8];
extern char lbl_8052F060[];
extern char lbl_80552920[];
extern int lbl_8066B668;
extern int lbl_8066D57C;
extern int lbl_8066D580;
extern int lbl_8066B63C;
extern int lbl_8066B8CC;
extern int lbl_8066B640;
extern int lbl_8066B644;
extern int lbl_8066C640;
extern int lbl_8066B69C;
extern int lbl_8066B664;

extern "C" {
char *strtok(char *s, const char *delim);
int stricmp(const char *a, const char *b);
char *strncpy(char *dst, const char *src, int n);
int atoi(const char *s);
double atof(const char *s);

void fn_804319B4(void *f, int on);
void fn_80431A8C(void *f, int on);
void fn_80431AD4(void *f, int on);
void fn_80431A44(void *f, int on);
void fn_804315C0(void *o, int on);
void fn_80431570(void *o, int on);
void fn_80431610(void *o, int on);
void fn_80431298(void *o, float v);
void fn_80431480(void *o, int v);
void fn_804314B0(void *o, float v);
void fn_804314E0(void *o, float v);
void fn_80431510(void *o, float v);
void fn_80431540(void *o, float v);
void fn_804313B0(void *o, int on);
void fn_80431310(void *o, int on);
void fn_80431400(void *o, int v);
void fn_80431440(void *o, int v);
void fn_80431360(void *o, int on);
void fn_80431660(void *o, int on);
void fn_800944C0(void *g, void *record, int player);
void fn_80431BF4(void *f, int on);
void fn_80431C3C(void *f, int on);
void fn_80431C84(void *f, int on);
void fn_80431B64(void *f, int on);
void fn_80431B1C(void *f, int on);
void fn_80431BAC(void *f, int on);
void fn_8002F9D0(void *list, char *name);
void fn_804317F4(void *g, int role);
void fn_8043181C(void *g, int role);
void fn_80431844(void *g, int count);
void *fn_804317BC(void *g, int slot);
void fn_80431788(void *slot);
void fn_8043186C(void *g, int v);
void fn_804316B0(int on);
void fn_80431728(int on);
void fn_80131878(int v);

void fn_80028BAC(char *cmdline)
{
    char *tok;
    unsigned int n;

    tok = strtok(cmdline, " \t");
    while (tok) {
        if (stricmp(tok, "-makecache") == 0 || stricmp(tok, "/makecache") == 0) {
            fn_804319B4(lbl_8066D568, 1);
        } else if (stricmp(tok, "-lvlreslog") == 0 || stricmp(tok, "/lvlreslog") == 0) {
            fn_80431A8C(lbl_8066D568, 1);
        } else if (stricmp(tok, "-reslog") == 0 || stricmp(tok, "/reslog") == 0) {
            fn_80431AD4(lbl_8066D568, 1);
        } else if (stricmp(tok, "-nophysics") == 0 || stricmp(tok, "/nophysics") == 0) {
            fn_80431A44(lbl_8066D568, 1);
        } else if (stricmp(tok, "-novsync") == 0 || stricmp(tok, "/novsync") == 0) {
            fn_804315C0(&lbl_8057E430, 1);
        } else if (stricmp(tok, "-vsync") == 0 || stricmp(tok, "/vsync") == 0) {
            fn_804315C0(&lbl_8057E430, 0);
        } else if (stricmp(tok, "-nofog") == 0 || stricmp(tok, "/nofog") == 0) {
            fn_80431570(&lbl_8057E430, 0);
        } else if (stricmp(tok, "-nogamma") == 0 || stricmp(tok, "/nogamma") == 0) {
            fn_80431610(&lbl_8057E430, 1);
        } else if (stricmp(tok, "-gamma") == 0 || stricmp(tok, "/gamma") == 0) {
            tok = strtok(0, " \t");
            if (tok) {
                fn_80431298(&lbl_8057E430, atof(tok));
            }
        } else if (stricmp(tok, "-user") == 0 || stricmp(tok, "/user") == 0) {
            tok = strtok(0, " \t");
            if (tok) {
                strncpy(lbl_8052EB18, tok, 0x80);
                lbl_8052EB18[0x7F] = 0;
            }
        } else if (stricmp(tok, "-level") == 0 || stricmp(tok, "/level") == 0) {
            tok = strtok(0, " \t");
            if (tok) {
                strncpy(lbl_805526AC, tok, 0x20);
                lbl_80552110.levelEnd = 0;
                lbl_80552110.levelSet = 1;
                lbl_8066B668 = 1;
            }
        } else if (stricmp(tok, "-scene") == 0 || stricmp(tok, "/scene") == 0) {
            tok = strtok(0, " \t");
            if (tok) {
                strncpy(lbl_805526CC, tok, 0x20);
                lbl_80552110.sceneEnd = 0;
                lbl_80552110.sceneSet = 1;
            }
        } else if (stricmp(tok, "-mission") == 0 || stricmp(tok, "/mission") == 0) {
            tok = strtok(0, " \t");
            if (tok) {
                strncpy(lbl_805526EC, tok, 0x20);
                lbl_80552110.missionEnd = 0;
                lbl_80552110.missionSet = 1;
                lbl_8066B668 = 1;
            }
        } else if (stricmp(tok, "-soak") == 0 || stricmp(tok, "/soak") == 0) {
        } else if (stricmp(tok, "-mpmission") == 0 || stricmp(tok, "/mpmission") == 0) {
            tok = strtok(0, " \t");
            if (tok) {
                strncpy(lbl_805526EC, tok, 0x20);
                lbl_80552110.missionEnd = 0;
                lbl_80552110.mpMissionSet = 1;
                lbl_8066B668 = 1;
            }
        } else if (stricmp(tok, "-menu3d") == 0 || stricmp(tok, "/menu3d") == 0) {
            lbl_8066D57C = 0;
        } else if (stricmp(tok, "-turtle") == 0 || stricmp(tok, "/turtle") == 0) {
            lbl_8066D580 = 1;
        } else if (stricmp(tok, "-chron") == 0 || stricmp(tok, "/chron") == 0) {
            tok = strtok(0, " \t");
            if (tok) {
                strncpy(lbl_8055270C, tok, 0x20);
                lbl_80552110.chronEnd = 0;
                lbl_80552110.chronSet = 1;
            }
        } else if (stricmp(tok, "-size") == 0 || stricmp(tok, "/size") == 0) {
            tok = strtok(0, " \r\t\n");
            if (tok) {
                lbl_8057E430.width = atoi(tok);
                tok = strtok(0, " \r\t\n");
                if (tok) {
                    lbl_8057E430.height = atoi(tok);
                }
            }
        } else if (stricmp(tok, "-depth") == 0 || stricmp(tok, "/depth") == 0) {
            tok = strtok(0, " \r\t\n");
            if (tok) {
                lbl_8057E430.depth = atoi(tok);
            }
        } else if (stricmp(tok, "-shadowDetail") == 0 || stricmp(tok, "/shadowDetail") == 0) {
            tok = strtok(0, " \r\t\n");
            if (tok) {
                fn_80431480(&lbl_8057E430, atoi(tok));
            }
            tok = strtok(0, " \r\t\n");
            if (tok) {
                fn_804314B0(&lbl_8057E430, atof(tok));
            }
            tok = strtok(0, " \r\t\n");
            if (tok) {
                fn_804314E0(&lbl_8057E430, atof(tok));
            }
            tok = strtok(0, " \r\t\n");
            if (tok) {
                fn_80431510(&lbl_8057E430, atof(tok));
            }
            tok = strtok(0, " \r\t\n");
            if (tok) {
                fn_80431540(&lbl_8057E430, atof(tok));
            }
        } else if (stricmp(tok, "-vertexLight") == 0 || stricmp(tok, "/vertexLight") == 0) {
            fn_804313B0(&lbl_8057E430, 1);
        } else if (stricmp(tok, "-zbuffer") == 0 || stricmp(tok, "/zbuffer") == 0) {
            fn_80431310(&lbl_8057E430, 0);
        } else if (stricmp(tok, "-nosound") == 0 || stricmp(tok, "/nosound") == 0) {
            lbl_8066B63C = 0;
        } else if (stricmp(tok, "-freepsi") == 0 || stricmp(tok, "/freepsi") == 0) {
            lbl_8066B8CC = 1;
        } else if (stricmp(tok, "-nocutscenes") == 0 || stricmp(tok, "/nocutscenes") == 0) {
            lbl_8066B640 = 0;
        } else if (stricmp(tok, "-noingamecutscenes") == 0 || stricmp(tok, "/noingamecutscenes") == 0) {
            lbl_8066B644 = 0;
        } else if (stricmp(tok, "-maxmip") == 0 || stricmp(tok, "/maxmip") == 0) {
            tok = strtok(0, " \r\t\n");
            if (tok) {
                fn_80431400(&lbl_8057E430, atoi(tok));
            }
        } else if (stricmp(tok, "-skipmip") == 0 || stricmp(tok, "/skipmip") == 0) {
            tok = strtok(0, " \r\t\n");
            if (tok) {
                fn_80431440(&lbl_8057E430, atoi(tok));
            }
        } else if (stricmp(tok, "-player") == 0 || stricmp(tok, "/player") == 0) {
            tok = strtok(0, " \r\t\n");
            if (tok) {
                fn_800944C0(&lbl_80552110, tok, 0);
            }
        } else if (stricmp(tok, "-?") == 0 || stricmp(tok, "/?") == 0) {
            goto done;
        } else if (stricmp(tok, "-norumble") == 0) {
            lbl_8066C640 = 0;
        } else if (stricmp(tok, "-smoketest") == 0) {
            fn_80431BF4(lbl_8066D568, 1);
        } else if (stricmp(tok, "-smoketestmemleak") == 0) {
            fn_80431C3C(lbl_8066D568, 1);
        } else if (stricmp(tok, "-smoketestscreengrab") == 0) {
            fn_80431C84(lbl_8066D568, 1);
        } else if (stricmp(tok, "-unlock") == 0 || stricmp(tok, "/unlock") == 0) {
            lbl_8066B69C = 1;
        } else if (stricmp(tok, "-noBundles") == 0 || stricmp(tok, "/noBundles") == 0) {
            lbl_8066B664 = 0;
        } else if (stricmp(tok, "-noTextures") == 0 || stricmp(tok, "/noTextures") == 0) {
            fn_80431360(&lbl_8057E430, 0);
        } else if (stricmp(tok, "-showConsole") == 0) {
            fn_80431B64(lbl_8066D568, 0);
            fn_80431B1C(lbl_8066D568, 1);
        } else if (stricmp(tok, "-addthing") == 0) {
            tok = strtok(0, " \t");
            while (tok) {
                fn_8002F9D0(lbl_8052F060, tok);
                tok = strtok(0, " \t");
            }
            return;
        } else if (stricmp(tok, "-mp") == 0) {
            fn_804317F4(&lbl_80552110, 1);
            fn_80431844(&lbl_80552110, 2);
            tok = strtok(0, " \r\t\n");
            if (tok) {
                fn_800944C0(&lbl_80552110, tok, 1);
            }
        } else if (stricmp(tok, "-vs") == 0) {
            fn_8043181C(&lbl_80552110, 1);
            fn_80431844(&lbl_80552110, 2);
            fn_80431788(fn_804317BC(&lbl_80552110, 1));
            tok = strtok(0, " \r\t\n");
            if (tok) {
                fn_800944C0(&lbl_80552110, tok, 1);
            }
        } else if (stricmp(tok, "-timed") == 0) {
            lbl_80552110.timerMode = 1;
            tok = strtok(0, " \r\t\n");
            if (tok) {
                lbl_80552110.timerMs = atoi(tok) * 1000;
            } else {
                lbl_80552110.timerMs = 60000;
            }
        } else if (stricmp(tok, "-noloadconsole") == 0) {
            fn_80431B64(lbl_8066D568, 1);
        } else if (stricmp(tok, "-loadconsole") == 0) {
            fn_80431B64(lbl_8066D568, 0);
        } else if (stricmp(tok, "-memsweep") == 0) {
            fn_80431BAC(lbl_8066D568, 1);
        } else if (stricmp(tok, "-demomode") == 0) {
            tok = strtok(0, " \r\t\n");
            if (tok) {
                n = atoi(tok);
                if (n <= 6) {
                    fn_8043186C(lbl_80552920, n);
                }
            }
        } else if (stricmp(tok, "-enablecheats") == 0) {
            fn_804316B0(1);
            fn_80431728(1);
        } else if (stricmp(tok, "-difficulty") == 0) {
            tok = strtok(0, " \r\t\n");
            if (tok) {
                n = atoi(tok);
                if (n <= 2) {
                    fn_80131878(n);
                }
            }
        } else if (stricmp(tok, "-warn") == 0) {
            fn_80431660(&lbl_8057E430, 1);
        } else if (stricmp(tok, "-enableAITeleport") == 0) {
        } else {
            goto done;
        }
        tok = strtok(0, " \t");
    }
    return;
done: // `goto` reproduces the two exits that land ahead of the trailing pair (docs/matching_notes.md)
    return;
}
}
