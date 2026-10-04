// GameFlow::OnPadInserted (the method behind OnPadInserted__FUs): drops the player whose pad came back.
// A .c unit: the file is pair-less C++, so `this` is a register first parameter.

typedef struct GameFlow
{
    char unk0[4];
    int unk4;                  // +0x4
    int unk8;                  // +0x8
    char unkC[0x10];
    unsigned char unk1C;       // +0x1C
    char unk1D[0x267];
    int numUnplugged;          // +0x284
    int unplugged[2];          // +0x288
} GameFlow;

extern char lbl_80552110[]; // the game-state object G
extern char lbl_8052F060[]; // the level/world object

extern int fn_804329E0(char *level);
extern int fn_804427FC(char *g);
extern char *fn_804427D0(char *g);
extern int fn_80442624(char *slot);
extern unsigned int fn_8043B31C(char *slot);
extern int fn_80094A9C(char *g);
extern int fn_80126DF0(void);
extern void fn_801021F4(int port);
extern int fn_8012D4AC(int a);
extern int fn_8012D63C(int port);
extern int fn_80122228(void);
extern int fn_80123298(int a);
extern int fn_800B4FC0(GameFlow *flow);

void fn_800B4CF8(register GameFlow *this, unsigned short port)
{
    int found = 0;
    int player = -1;

    if (fn_804329E0(lbl_8052F060) == 0) {
        if (fn_80126DF0()) {
            fn_801021F4(port);
        }
        if ((fn_8012D4AC(0) < 0 && fn_8012D4AC(1) < 0) || fn_80123298(fn_80122228())) {
            player = fn_8012D63C(port);
            if (player < 0) {
                player = 0;
            }
            found = 1;
        }
    } else {
        int flag = 0;
        if (flag != 0 || ((this->unk1C & 3) == 0 && this->unk8 == 0) || fn_800B4FC0(this) == 0) {
            if (fn_804427FC(lbl_80552110)) {
                do {
                    if (fn_80442624(fn_804427D0(lbl_80552110)) == port) {
                        player = fn_8043B31C(fn_804427D0(lbl_80552110));
                        found = 1;
                        break;
                    }
                } while (fn_80094A9C(lbl_80552110));
            }
        }
    }

    if (found) {
        if (player == this->unplugged[0]) {
            this->unplugged[0] = this->unplugged[1];
            this->unplugged[1] = -1;
            this->numUnplugged--;
        } else if (player == this->unplugged[1]) {
            this->unplugged[1] = -1;
            this->numUnplugged--;
        }
        if (this->numUnplugged == 0) {
            this->unk4 = 0;
        }
    }
}
