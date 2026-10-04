// GameFlow::OnPadInserted (the method behind OnPadInserted__FUs): drops the player whose pad came back;
// fn_800B4F50 clears the unplugged list. A .c unit: the file is pair-less C++, so `this` is a register first parameter.

typedef struct GameFlow
{
    char unk0[4];
    int unk4;                  // +0x4
    int unk8;                  // +0x8
    int unkC;                  // +0xC
    int unk10;                 // +0x10
    int unk14;                 // +0x14
    char unk18[4];
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
extern int fn_800531AC(void);
extern int fn_80430024(int a);
extern int fn_8042D4CC(void);
extern int fn_8042D52C(int a);
extern int fn_80121E38(int a);
extern int fn_80432BC4(void);
extern int fn_804460BC(int a);

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

void fn_800B4F50(register GameFlow *this)
{
    int i;

    this->unk4 = 0;
    this->numUnplugged = 0;
    for (i = 0; i < 2; i++) {
        this->unplugged[i] = -1;
    }
}

int fn_800B4FC0(register GameFlow *this)
{
    int found = 0;
    int result = this->unkC;

    if (fn_800531AC()) {
        found = fn_80430024(fn_800531AC());
    }
    if (fn_8042D52C(fn_8042D4CC()) != 0 || fn_80121E38(fn_80122228()) != 0 || fn_80123298(fn_80122228()) != 0
        || (found != 0 && (this->unk1C & 3) == 0)) {
        result = 0;
    } else if (fn_804329E0(lbl_8052F060) == 0) {
        if (fn_804460BC(fn_80432BC4())) {
            result = 0;
        }
    } else {
        if (fn_804329E0(lbl_8052F060)) {
            if (this->unk14 != 0) {
                result = 1;
            }
        }
    }
    return result;
}
