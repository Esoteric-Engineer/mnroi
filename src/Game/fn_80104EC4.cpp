// Global_PlayUISound(String); the by-value String is destroyed here, through _._6String (Game/fn_804491DC.c).
class String {
public:
    char data[0x4C];
    ~String();
    int eq(const char *s) __asm__("fn_8044B9E8");
};

extern "C" {
void *fn_80432BC4();
int fn_804460BC(void *x);
void fn_80115308(int a, int b, int c);
}

extern char lbl_80490538[];
extern char lbl_80490554[];

inline int sn_return_decl(int a) { return a; }

void Global_PlayUISound(String name)
{
    if (fn_804460BC(fn_80432BC4())) {
        return;
    }
    if (name.eq(lbl_80490538)) {
        fn_80115308(0x12c, 0x70, 0);
    } else if (name.eq(lbl_80490554)) {
        fn_80115308(0x12c, 0x70, 1);
    }
}
