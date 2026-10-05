// Global_PlayFEStream(String): NonMatching, docs/nonmatching.md.
class String {
public:
    char data[0x4C];
    ~String();
    const char *c_str() __asm__("fn_804496C8");
};

extern "C" {
void fn_8012818C();
void fn_8010FAE8();
void *fn_80427400();
int fn_8042D584(void *locale);
char *strcpy(char *dst, const char *src);
int sprintf(char *dst, const char *fmt, ...);
void fn_8010FA58(const char *path);
}

extern char lbl_80490564[];
extern char lbl_8049056C[];
extern char lbl_80490574[];
extern char lbl_8049057C[];
extern char lbl_80490584[];

inline int sn_return_decl(int a) { return a; }

void Global_PlayFEStream(String name)
{
    char path[0x100];
    char lang[0x18];

    fn_8012818C();
    fn_8010FAE8();
    switch (fn_8042D584(fn_80427400())) {
    case 1:
        strcpy(lang, lbl_80490564);
        break;
    case 2:
        strcpy(lang, lbl_8049056C);
        break;
    case 4:
        strcpy(lang, lbl_80490574);
        break;
    case 0:
    default:
        strcpy(lang, lbl_8049057C);
        break;
    }
    sprintf(path, lbl_80490584, lang, name.c_str());
    fn_8010FA58(path);
}
