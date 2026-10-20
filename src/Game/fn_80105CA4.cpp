// Cheat_Enable(String); the by-value String is destroyed here, through _._6String (Game/fn_804491DC.c).
class String {
public:
    char data[0x4C];
    String(const char *s) __asm__("__6StringPCc");
    ~String();
    const char *c_str() __asm__("fn_804496C8");
};

// 0x204-byte cheat table entries at lbl_804CD344 (17 of them).
struct Cheat {
    char code[0x100];
    char message[0x100];
    int enabled; // +0x200
};

extern "C" {
int stricmp(const char *a, const char *b);
void fn_804316B0(int a);
void fn_80431728(int a);
void fn_8044D490(int a);
void fn_8044D52C(int a);
void fn_8044D3F4(int a);
void *fn_80122228();
void fn_80125428(void *a, int b, int c, int d);
void fn_80443640(int index, int a);
void fn_80443608(int index, int a);
}

struct CheatText {
    char message[0x204];
};

extern Cheat lbl_804CD344[];
extern CheatText lbl_804CD444[]; // the same table's messages, +0x100 into each entry
extern char lbl_804905A4[]; // "~k_INCORRECTPASSWORD"

inline int sn_return_decl(int a) { return a; }

String Cheat_Enable(String code)
{
    int index = -1;
    int i;
    int j;
    int k;

    for (i = 0; i <= 0x10; i++) {
        if (stricmp(code.c_str(), lbl_804CD344[i].code) == 0 && lbl_804CD344[i].enabled) {
            index = i;
            break;
        }
    }

    switch (index) {
    case 0:
    case 11:
        fn_804316B0(1);
        fn_80431728(1);
        fn_8044D490(1);
        fn_8044D52C(1);
        fn_8044D3F4(1);
        break;
    case 1:
        fn_804316B0(0);
        fn_80431728(0);
        fn_8044D490(0);
        fn_8044D52C(0);
        fn_8044D3F4(0);
        break;
    case 2:
        fn_804316B0(1);
        break;
    case 3:
        fn_804316B0(0);
        break;
    case 4:
        fn_80431728(1);
        break;
    case 5:
        fn_80431728(0);
        break;
    case 6:
        fn_8044D490(1);
        break;
    case 7:
        fn_8044D490(0);
        break;
    case 8:
        fn_8044D52C(1);
        break;
    case 9:
        fn_8044D52C(0);
        break;
    case 10:
        fn_80125428(fn_80122228(), 0x10, 1, 0);
        break;
    case 12:
        for (j = 0; j <= 8; j++) {
            fn_80443640(j, 1);
        }
        break;
    case 13:
        for (k = 9; k <= 0x12; k++) {
            fn_80443640(k, 1);
        }
        break;
    case 14:
        fn_80443608(0x28, 1);
        break;
    case 15:
        fn_80443608(0x29, 1);
        break;
    case 16:
        fn_80443608(0x2a, 1);
        break;
    }

    if (index >= 0 && index <= 0x10) {
        return String(lbl_804CD444[index].message);
    } else {
        return String(lbl_804905A4);
    }
}
