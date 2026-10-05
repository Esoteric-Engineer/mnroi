// clashVenue_StartLevel(String): NonMatching, docs/nonmatching.md (the by-value String's destructor).
class String {
public:
    char data[0x4C];
    ~String();
    const char *c_str() __asm__("fn_804496C8");
};

extern "C" {
char *strncpy(char *dst, const char *src, int n);
void fn_8012D400(int a);
void fn_80432AF8(void *level);
}

struct GameState {
    char unk0[0x5BB];
    char venueNameEnd; // +0x5BB
    char unk5BC[0x60];
    int unk61C; // +0x61C
};
extern GameState lbl_80552110;
extern char lbl_8052F060[]; // level object
extern char lbl_805526AC[]; // G+0x59C, the level name

inline int sn_return_decl(int a) { return a; }

void clashVenue_StartLevel(String name)
{
    strncpy(lbl_805526AC, name.c_str(), 0x20);
    lbl_80552110.venueNameEnd = 0;
    fn_8012D400(0);
    lbl_80552110.unk61C = 1;
    fn_80432AF8(lbl_8052F060);
}
