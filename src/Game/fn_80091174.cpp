// GameState (G, lbl_80552110) constructor: slots 0 and 1 default to plr_wolverine. Fields: docs/versus.md section 4.1.

extern "C" char lbl_8048A314[]; // "plr_wolverine"
extern "C" unsigned char lbl_8066B928;
extern "C" void fn_80443B70(void *slot, const char *name, int player);

class PlayerSlot
{
public:
    char unk0[0xB0];
    PlayerSlot() __asm__("fn_80095BEC");
};

class GameState
{
public:
    int unk0;
    char unk4[0xC];
    PlayerSlot slots[8]; // +0x10
    int numPlayers;      // +0x590
    int unk594;
    int curIndex;        // +0x598
    char unk59C[0x80];
    int unk61C;
    int unk620;
    int unk624;
    int unk628;
    int unk62C;
    int unk630;
    int unk634;
    int unk638;
    int unk63C;
    int unk640;
    char unk644[0x104];
    int unk748;
    int unk74C;
    PlayerSlot *cursor; // +0x750
    int unk754;
    int unk758;
    int timerMode;      // +0x75C
    int unk760;
    int timeLimit;      // +0x764
    int unk768;
    char unk76C[0x1C];
    int unk788;
    char unk78C[0x30];
    int unk7BC;
    GameState();
};

GameState::GameState()
{
    numPlayers = 1;
    unk594 = 0;
    unk754 = -1;
    unk748 = -1;
    unk74C = 0;
    cursor = 0;
    curIndex = 0;
    unk61C = 0;
    unk620 = 0;
    unk624 = 0;
    unk628 = 0;
    unk62C = 0;
    unk630 = 0;
    unk634 = 0;
    unk638 = 0;
    unk63C = 0;
    unk640 = -1;
    timeLimit = 300000;
    unk768 = 0;
    unk788 = 0;
    timerMode = 3;
    fn_80443B70(&slots[0], lbl_8048A314, 0);
    fn_80443B70(&slots[1], lbl_8048A314, 1);
    unk0 = 0;
    lbl_8066B928 = 0xFF;
    unk7BC = 0;
}
