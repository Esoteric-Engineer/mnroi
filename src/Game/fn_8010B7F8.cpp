// clashMission_StartLevel(String): story-mode level start. On BrooklynBridge with no versus role it spawns "plr_thing" for player 0.
class String {
public:
    char data[0x4C];
    ~String();
    const char *c_str() __asm__("fn_804496C8");
};

extern "C" {
char *strncpy(char *dst, const char *src, int n);
int stricmp(const char *a, const char *b);
void fn_8012D400(int a);
void fn_80432AF8(void *level);
int fn_80432844(void *g);
int fn_80432870(void *g);
void fn_800944C0(void *g, void *record, int player);
int fn_8011CA74();
void fn_8011ED0C(int a);
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
extern char lbl_80491B78[]; // "BrooklynBridge"
extern char lbl_80491B88[]; // "plr_thing"

inline int sn_return_decl(int a) { return a; }

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
