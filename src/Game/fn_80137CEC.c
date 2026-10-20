// AI profile name to index over lbl_804CF8E8 (stricmp); an unlisted name gives 0, AI_DEFAULT. docs/characters.md section 3.

extern char *lbl_804CF8E8[];
int stricmp(const char *a, const char *b);

int fn_80137CEC(char *name)
{
    int i;

    for (i = 0; lbl_804CF8E8[i] != 0; i++) {
        if (stricmp(lbl_804CF8E8[i], name) == 0) {
            return i;
        }
    }
    return 0;
}
