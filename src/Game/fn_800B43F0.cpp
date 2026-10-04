// GameFlow's constructor, the first function of the source file that ends at 0x800B5BC4.
// The class and its fields are in docs/versus.md section 6.
// This unit owns the .rodata pool at 0x8048BD3C-0x8048BD44.

class GameFlow
{
public:
    float f0;               // +0x0
    int unk4;               // +0x4
    int unk8;               // +0x8
    int unkC;               // +0xC
    char unk10[0x4];
    int unk14;              // +0x14
    float f18;              // +0x18
    unsigned char flags1C;  // +0x1C, single-bit flags
    char unk1D[0x3];
    unsigned int command;   // +0x20
    int unk24;              // +0x24
    int pendingScreen;      // +0x28
    char levelName[0x100];  // +0x2C
    int unk12C;             // +0x12C
    int unk130;             // +0x130
    int unk134;             // +0x134
    void *unk138;           // +0x138
    int unk13C;             // +0x13C
    int unk140;             // +0x140
    int unk144;             // +0x144
    int unk148;             // +0x148
    char unk14C[0x4];
    int unk150;             // +0x150
    int unk154;             // +0x154
    int unk158;             // +0x158
    int unk15C;             // +0x15C
    int unk160;             // +0x160
    int unk164;             // +0x164
    int unk168;             // +0x168
    int unk16C;             // +0x16C
    int unk170;             // +0x170
    int unk174;             // +0x174
    int unk178;             // +0x178
    char unk17C[0x4];
    int unk180;             // +0x180
    float f184;             // +0x184
    float f188;             // +0x188
    char unk18C[0x10];      // +0x18C, a member object with an empty constructor (fn_80430728)
    int unk19C;             // +0x19C
    int history[5];         // +0x1A0, most recent command first
    int unk1B4;             // +0x1B4
    int unk1B8;             // +0x1B8
    int unk1BC;             // +0x1BC
    int unk1C0;             // +0x1C0
    char unk1C4[0x4];
    int unk1C8;             // +0x1C8
    int unk1CC;             // +0x1CC
    int unk1D0;             // +0x1D0
    int unk1D4;             // +0x1D4
    int unk1D8;             // +0x1D8
    int unk1DC;             // +0x1DC
    int unk1E0;             // +0x1E0
    int color1E4;           // +0x1E4
    int color1E8;           // +0x1E8
    int color1EC;           // +0x1EC
    int color1F0;           // +0x1F0
    unsigned char unk1F4;   // +0x1F4
    char unk1F5[0x3];
    int unk1F8[0x22];       // +0x1F8
    int unk280;             // +0x280
    int unk284;             // +0x284
    int unk288[2];          // +0x288
    int unk290;             // +0x290

    GameFlow();
    void ClearCommandHistory();
};

extern "C" {
extern void *fn_80430728(void *p); // the +0x18C member's constructor
}

GameFlow::GameFlow()
{
    int i;

    fn_80430728((char *)this + 0x18C);
    unk290 = 0;
    unk168 = 1;
    f0 = -1.0f;
    unk134 = 0;
    unk4 = 0;
    unk8 = 0;
    f18 = -1.0f;
    unk1C0 = 0;
    unk180 = 0xFF;
    f184 = 0.0f;
    f188 = 0.0f;
    unk130 = 0;
    unk1F4 = 0xFF;
    unk144 = 0;
    unk148 = 1;
    unk1C8 = 0;
    unk1CC = 0;
    unk1D4 = 0;
    unk1D0 = 0;
    flags1C = 4;
    command = 0;
    unk1B4 = 0;
    unk1B8 = 0;
    unk1BC = 0;
    pendingScreen = 0;
    unk19C = 0;
    levelName[0] = 0;
    unk16C = 0;
    unk170 = 0;
    unk174 = 0;
    unk178 = 0;
    unk1D8 = 0;
    color1E4 = 0xFFE0E0E0;
    color1E8 = 0xFF008080;
    color1EC = 0x8000E0E0;
    color1F0 = 0x80008080;
    unk1DC = 0;
    unk140 = 0;
    unk13C = 1;
    unk15C = 0;
    unk1E0 = 0;
    unk24 = 0;
    unk284 = 0;
    unk280 = 0;
    unk160 = 0;
    unk164 = 0;
    unkC = 1;
    unk14 = 0;
    unk138 = 0;
    unk150 = 0;
    unk154 = 0;
    i = 0;
    while (i <= 1) {
        unk288[i] = -1;
        i++;
    }
    ClearCommandHistory();
}
