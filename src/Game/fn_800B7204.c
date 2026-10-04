// GameFlow's per-command methods, the bodies RunCommand dispatches to.
// A .c unit: the file is pair-less C++, so `this` is a register first parameter.
// It owns the .rodata pool at 0x8048BF44-0x8048BF64, and renamed fn_800B8594 / fn_800B8660 to GameFlowCmdStaticInit / GameFlowCmdGlobalInit.

typedef struct GameFlow
{
    char unk0[0x20];
    unsigned int command;      // +0x20
    int unk24;                 // +0x24
    char unk28[0x104];
    void *unk12C;              // +0x12C
    int unk130;                // +0x130
    char unk134[0xC];
    int unk140;                // +0x140
    int unk144;                // +0x144
    char unk148[0x14];
    int unk15C;                // +0x15C
    char unk160[0x54];
    int unk1B4;                // +0x1B4
    int unk1B8;                // +0x1B8
    int unk1BC;                // +0x1BC
    char unk1C0[0x4];
    int unk1C4;                // +0x1C4
    char unk1C8[0x2C];
    unsigned char unk1F4;      // +0x1F4
} GameFlow;

extern void *lbl_8066B690;
extern void *lbl_8066B694;
extern void *lbl_8066B698;
extern char lbl_80552110[];   // the game-state object G (docs/versus.md section 4.1)
extern char lbl_805526AC[]; // G + 0x59C, the level name; dtk named it separately
extern char lbl_8054ED80[];   // the .nsc script table
extern char lbl_8052F060[];   // the level/world object
extern char lbl_80571EA4[];
extern char lbl_80593BE8[];   // the globals object of Game/fn_80443908.cpp

extern void fn_8002B27C(void *p, unsigned int index);
extern int fn_8002ABCC(void *p);
extern int fn_8002B2C4(void *p, unsigned int index, int a);
extern int SetCommand__8GameFlowi(GameFlow *p, int command);
extern void OpenScreen__8GameFlowii(GameFlow *p, int screen, int keep);
extern int Stub6CFC__8GameFlowiPv(GameFlow *p, int index, void *table);
extern void *fn_801B5D3C(void *p, int index);
extern void fn_8002A58C(char *p);
extern void fn_8002A5D8(char *p);
extern void fn_8002A7D0(char *p);
extern void fn_8002A984(char *p);
extern void *fn_804332C4(char *table, int index);
extern int fn_804329E0(char *level);
extern int fn_80431DB0(char *table);
extern int fn_80431DDC(GameFlow *p);
extern int fn_80431E08(char *level);
extern char *fn_80432688(void *rec);
extern void fn_8002D7A8(char *level, char *name, int a, int b, int c, int d);
extern void fn_8002C690(char *level, char *name, int a, int b);
extern void fn_8002CB7C(char *level, char *name, int a, int b, int c);
extern void fn_8008856C(char *table, int index, int a);
extern void fn_800949FC(char *g, int a);
extern void fn_801AF754(char *globals);
extern void fn_8002F884(char *level, int a);
extern void fn_8043323C(char *p, int a);
extern void BeginLoad__8GameFlow(GameFlow *p);
extern void EndLoad__8GameFlow(GameFlow *p);
extern void fn_80128C3C(const char *name);
extern void fn_8043AB30(void);
extern void fn_801127E0(void);
extern int fn_80430050(char *level);
extern void fn_8002D760(char *level, int a);
extern void fn_8002DBD0(char *level);
extern void fn_8002CA58(char *level);
extern void fn_804317F4(char *g, int a);
extern void fn_8043181C(char *g, int a);
extern void fn_8002A418(void);
extern void fn_8002A354(void);
extern int fn_801B6A44(void *p);
extern void fn_8002FA70(char *level);
extern void fn_804463F8(GameFlow *p);
extern void fn_80446094(GameFlow *p, int a);
extern int fn_8042D444(char *table);
extern int fn_804323B4(void *p);
extern void fn_804323E4(void *p, int a);
extern int fn_8043233C(void *p);
extern void fn_8043236C(void *p, int a);
extern int fn_80446290(void *p);
extern void fn_804462C0(void *p, int a);
extern int fn_80446308(void *p);
extern void fn_80446338(void *p, int a);
extern int fn_804322C0(void *p);
extern void fn_804322F0(void *p, int a);
extern void fn_80446380(void *p);
extern void fn_8002B04C(void *p, char *buf);
extern int fn_8043242C(void *p);
extern void fn_8002AA5C(void *p, unsigned int index);
extern void fn_8002B0A0(void *p, char *buf);
extern void fn_804463C0(char *p, int a);
extern void fn_800871A8(void);
extern void fn_8043206C(void *p);

extern float lbl_8066BA38; // .sdata, screen width
extern float lbl_8066BA3C; // .sdata, screen height

// 0x8066D6BC-0x8066D6CC: the same screen-derived rectangle Game/fn_800B7094.c builds, off a
// second width/height pair.
float lbl_8066D6BC __attribute__((section(".sbss")));
float lbl_8066D6C0 __attribute__((section(".sbss")));
float lbl_8066D6C4 __attribute__((section(".sbss")));
float lbl_8066D6C8 __attribute__((section(".sbss")));
extern int GetHistory__8GameFlowUc(GameFlow *p, unsigned char index);

void fn_800B7204(register GameFlow *this)
{
    if (lbl_8066B690) {
        fn_8002B27C(lbl_8066B690, this->command - 0x34);
        fn_8002ABCC(lbl_8066B690);
    }
    SetCommand__8GameFlowi(this, 0x40);
}

void fn_800B7268(register GameFlow *this)
{
    this->unk1F4 = this->command - 0x2F;
    SetCommand__8GameFlowi(this, 0x18);
}

void fn_800B72B4(register GameFlow *this)
{
    int found = 0;
    unsigned int i;

    if (lbl_8066B690) {
        i = 0;
        while (i <= 4) {
            if (fn_8002B2C4(lbl_8066B690, i, 0)) {
                found = 1;
            }
            i++;
        }
    }

    if (found) {
        OpenScreen__8GameFlowii(this, 0x1C, 1);
        SetCommand__8GameFlowi(this, 0);
    } else if (GetHistory__8GameFlowUc(this, 1) == 8) {
        this->unk1B4 = this->unk1B8;
        this->unk1B8 = 0x10;
        SetCommand__8GameFlowi(this, 0x28);
    } else {
        this->unk1B4 = this->unk1B8;
        this->unk1B8 = 0x10;
        SetCommand__8GameFlowi(this, 8);
    }
}

void fn_800B73C4(register GameFlow *this)
{
    int index = this->command - 0x561;

    if (Stub6CFC__8GameFlowiPv(this, index, lbl_805526AC) == 0) {
        SetCommand__8GameFlowi(this, 0);
    } else {
        SetCommand__8GameFlowi(this, 0x18);
    }
}

void fn_800B743C(register GameFlow *this)
{
    char *p;

    this->unk1C4 = this->command - 0x35F;
    p = fn_801B5D3C(lbl_8066B698, this->unk1C4);

    if (lbl_8066B690 == 0) {
        fn_8002A58C(p);
    } else {
        fn_8002A5D8(p);
    }

    fn_8002A984(p);
    SetCommand__8GameFlowi(this, this->unk1BC);
    this->unk1BC = 0;
}

void fn_800B74C4(register GameFlow *this)
{
    this->unk1C4 = this->command - 0x460;
    this->unk1B4 = this->unk1B8;
    SetCommand__8GameFlowi(this, 0xA);
}

void fn_800B7514(register GameFlow *this)
{
    char *p = fn_801B5D3C(lbl_8066B698, this->unk1C4);

    if (p) {
        fn_8002A7D0(p);
    }

    SetCommand__8GameFlowi(this, GetHistory__8GameFlowUc(this, 3));
}

void fn_800B7584(register GameFlow *this)
{
    this->unk24 = this->command - 0x25E;
    this->unk12C = fn_804332C4(lbl_8054ED80, this->unk24);
    lbl_80552110[0x59C] = 0;

    if (this->unk12C == 0) {
        SetCommand__8GameFlowi(this, 0x19);
    } else if (GetHistory__8GameFlowUc(this, 1) == 0x4B ||
               GetHistory__8GameFlowUc(this, 2) == 0x4B) {
        SetCommand__8GameFlowi(this, 0x18);
    } else {
        SetCommand__8GameFlowi(this, 9);
    }
}

void fn_800B7654(register GameFlow *this)
{
    this->unk140 = 1;
    this->unk15C = 0;

    if (this->unk1F4 != 0xFF) {
        SetCommand__8GameFlowi(this, 0x1A);
    } else {
        SetCommand__8GameFlowi(this, 0x14);
    }
}

void fn_800B76C0(register GameFlow *this)
{
    this->unk140 = 1;
    this->unk15C = 0;

    if (lbl_80552110[0x59C]) {
        if (fn_804329E0(lbl_8052F060)) {
            fn_8002D7A8(lbl_8052F060, lbl_805526AC, 8, 0, 0, 0);
        } else {
            fn_8002C690(lbl_8052F060, lbl_805526AC, 0, 0x1008);
        }
    } else {
        fn_8008856C(lbl_8054ED80, this->unk24, 1);

        if (fn_80431E08(lbl_8052F060) == 0 || fn_80431DDC(this) != 0) {
            fn_8002C690(lbl_8052F060,
                        fn_80432688(fn_804332C4(lbl_8054ED80, fn_80431DB0(lbl_8054ED80))),
                        0, 0x1008);
        } else {
            fn_8002CB7C(lbl_8052F060,
                        fn_80432688(fn_804332C4(lbl_8054ED80, fn_80431DB0(lbl_8054ED80))),
                        0, 0, 8);
        }

        fn_800949FC(lbl_80552110, 0);
    }

    fn_801AF754(lbl_80593BE8);
    fn_8002F884(lbl_8052F060, 5);
    SetCommand__8GameFlowi(this, 0x1B);
    this->unk130 = 0;
}

void fn_800B7894(register GameFlow *this)
{
    fn_8043323C(lbl_80571EA4, 1);
    BeginLoad__8GameFlow(this);
    fn_801AF754(lbl_80593BE8);
    fn_8002F884(lbl_8052F060, 5);
    SetCommand__8GameFlowi(this, 0x40);
    fn_80128C3C("mainBE");
    BeginLoad__8GameFlow(this);
}

void fn_800B7918(register GameFlow *this)
{
    EndLoad__8GameFlow(this);
    fn_8002F884(lbl_8052F060, 3);
    SetCommand__8GameFlowi(this, 0);
    fn_8043323C(lbl_80571EA4, 0);
}

void fn_800B797C(register GameFlow *this)
{
    fn_8043AB30();
    fn_801127E0();

    if (fn_80430050(lbl_8052F060)) {
        fn_8002D760(lbl_8052F060, fn_80430050(lbl_8052F060));
    }

    fn_8002DBD0(lbl_8052F060);
    EndLoad__8GameFlow(this);
    SetCommand__8GameFlowi(this, 0);
}

void fn_800B7A0C(register GameFlow *this)
{
    this->unk140 = 1;
    this->unk15C = 0;

    if (fn_80430050(lbl_8052F060)) {
        fn_8002D760(lbl_8052F060, fn_80430050(lbl_8052F060));
    }

    fn_8002DBD0(lbl_8052F060);
    EndLoad__8GameFlow(this);
    SetCommand__8GameFlowi(this, 0);
}

void fn_800B7AA4(register GameFlow *this)
{
    fn_804317F4(lbl_80552110, 0);
    fn_8043181C(lbl_80552110, 0);

    if (fn_80431E08(lbl_8052F060)) {
        fn_8002CA58(lbl_8052F060);
    }

    fn_8002F884(lbl_8052F060, 2);
    SetCommand__8GameFlowi(this, 1);
}

void fn_800B7B34(register GameFlow *this)
{
    fn_801AF754(lbl_80593BE8);
    fn_8002F884(lbl_8052F060, 5);
    SetCommand__8GameFlowi(this, 0x40);
    SetCommand__8GameFlowi(this, 0);
}

void fn_800B7B98(register GameFlow *this)
{
    SetCommand__8GameFlowi(this, 0);
}

void fn_800B7BD4(register GameFlow *this)
{
    fn_8002A418();

    if (fn_801B6A44(lbl_8066B698)) {
        OpenScreen__8GameFlowii(this, 0x16, 1);
        SetCommand__8GameFlowi(this, 0);
    } else {
        SetCommand__8GameFlowi(this, 0x26);
        this->unk1BC = 0x2D;
    }
}

void fn_800B7C50(register GameFlow *this)
{
    fn_8002FA70(lbl_8052F060);
    SetCommand__8GameFlowi(this, 0);
}

void fn_800B7C98(register GameFlow *this)
{
    BeginLoad__8GameFlow(this);
    fn_8002A354();

    if (fn_80431E08(lbl_8052F060)) {
        fn_8002CA58(lbl_8052F060);
    }

    fn_8002F884(lbl_8052F060, 2);
    fn_804463F8(this);
    SetCommand__8GameFlowi(this, 0);
    fn_80128C3C("main");
}

void fn_800B7D28(register GameFlow *this)
{
    fn_80446094(this, 8);
    fn_800B7C98(this);
}

void fn_800B7D6C(register GameFlow *this)
{
    fn_80446094(this, 3);
    fn_800B7C98(this);
}

void fn_800B7DB0(register GameFlow *this)
{
    fn_80446094(this, 6);
    fn_800B7C98(this);
}

void fn_800B7DF4(register GameFlow *this)
{
    fn_80446094(this, 0xA);
    fn_800B7C98(this);
}

void fn_800B7E38(register GameFlow *this)
{
    if (fn_8042D444(lbl_8054ED80)) {
        fn_80446094(this, 5);
    } else {
        fn_80446094(this, 4);
    }

    fn_800B7C98(this);
}

void fn_800B7EA4(register GameFlow *this)
{
    fn_804323E4(lbl_8066B690, !fn_804323B4(lbl_8066B690));
    SetCommand__8GameFlowi(this, 0);
}

void fn_800B7F04(register GameFlow *this)
{
    fn_8043236C(lbl_8066B690, !fn_8043233C(lbl_8066B690));
    SetCommand__8GameFlowi(this, 0);
}

void fn_800B7F64(register GameFlow *this)
{
    fn_804462C0(lbl_8066B690, !fn_80446290(lbl_8066B690));
    SetCommand__8GameFlowi(this, 0);
}

void fn_800B7FC4(register GameFlow *this)
{
    fn_80446338(lbl_8066B690, !fn_80446308(lbl_8066B690));
    SetCommand__8GameFlowi(this, 0);
}

void fn_800B8024(register GameFlow *this)
{
    fn_804322F0(lbl_8066B690, !fn_804322C0(lbl_8066B690));
    SetCommand__8GameFlowi(this, 0);
}

void fn_800B8084(register GameFlow *this)
{
    char buf[0x200];

    if (lbl_8066B690) {
        fn_80446380(lbl_8066B690);
        fn_8002B04C(lbl_8066B690, buf);
    }

    SetCommand__8GameFlowi(this, 0);
}

void fn_800B80E0(register GameFlow *this)
{
    void *p;
    char buf[0x200];
    unsigned int n;

    p = lbl_8066B690;

    if (p) {
        n = fn_8043242C(p) + 1;

        if (n > 1) {
            n = 0;
        }

        fn_8002AA5C(p, n);
        fn_8002B0A0(p, buf);
    }

    SetCommand__8GameFlowi(this, 0);
}

void fn_800B8174(register GameFlow *this, int a)
{
    char *p = fn_801B5D3C(lbl_8066B698, this->unk1C4);

    fn_804463C0(p, a);
    SetCommand__8GameFlowi(this, 0x18);
}

void fn_800B81D0(register GameFlow *this)
{
    this->unk144 = 0;
    fn_800871A8();
    fn_8002A418();
}

void fn_800B8210(register GameFlow *this)
{
    fn_800B81D0(this);

    if (fn_801B6A44(lbl_8066B698) == 0) {
        SetCommand__8GameFlowi(this, 0x26);
        this->unk1BC = 0x10;
    } else {
        OpenScreen__8GameFlowii(this, 0x12, 1);
        SetCommand__8GameFlowi(this, 0);
    }
}

int fn_800B8290(register GameFlow *this)
{
    if (lbl_8066B694) {
        fn_8043206C(lbl_8066B694);
        lbl_8066B694 = 0;
    } else if (lbl_8066B690) {
        fn_8043206C(lbl_8066B690);
        lbl_8066B690 = 0;
    } else {
        SetCommand__8GameFlowi(this, 0x23);
        return 0;
    }

    return 1;
}

void fn_800B831C(register GameFlow *this)
{
    if (lbl_8066B694) {
        SetCommand__8GameFlowi(this, 0x25);
    } else if (lbl_8066B690) {
        if (fn_801B6A44(lbl_8066B698) > 1) {
            OpenScreen__8GameFlowii(this, 0x14, 1);
            SetCommand__8GameFlowi(this, 0);
        } else {
            SetCommand__8GameFlowi(this, 0x26);
        }

        this->unk1BC = 0x2C;
    } else {
        if (fn_801B6A44(lbl_8066B698)) {
            OpenScreen__8GameFlowii(this, 0x14, 1);
            SetCommand__8GameFlowi(this, 0);
        } else {
            SetCommand__8GameFlowi(this, 0x26);
        }

        this->unk1BC = 0x2C;
    }
}

void fn_800B8408(register GameFlow *this)
{
    if (lbl_8066B694) {
        SetCommand__8GameFlowi(this, 0x24);
    } else if (lbl_8066B690) {
        if (fn_801B6A44(lbl_8066B698) > 1) {
            OpenScreen__8GameFlowii(this, 0x13, 1);
            SetCommand__8GameFlowi(this, 0);
        } else {
            SetCommand__8GameFlowi(this, 0x26);
        }

        this->unk1BC = 0x2A;
    } else {
        if (fn_801B6A44(lbl_8066B698)) {
            OpenScreen__8GameFlowii(this, 0x13, 1);
            SetCommand__8GameFlowi(this, 0);
        } else {
            SetCommand__8GameFlowi(this, 0x26);
        }

        this->unk1BC = 0x2A;
    }
}

void fn_800B84F4(register GameFlow *this)
{
    if (lbl_8066B690) {
        fn_8002ABCC(lbl_8066B690);
    }

    SetCommand__8GameFlowi(this, 0xB);
}

void fn_800B8544(register GameFlow *this)
{
    if (lbl_8066B690) {
        fn_8002ABCC(lbl_8066B690);
    }

    SetCommand__8GameFlowi(this, 0x44);
}

// 65535 is GCC 2.95's default init priority.
static void GameFlowCmdStaticInit(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            lbl_8066D6BC = 320.0f - lbl_8066BA38 * 0.5f;
            lbl_8066D6C0 = lbl_8066D6BC + lbl_8066BA38 * 0.5f;
            lbl_8066D6C4 = 240.0f - lbl_8066BA3C * 0.5f;
            lbl_8066D6C8 = lbl_8066BA3C * 0.5f + lbl_8066D6C4 - 12.0f;
        } else {
        }
    }
}

static void GameFlowCmdGlobalInit(void)
{
    GameFlowCmdStaticInit(1, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = GameFlowCmdGlobalInit;
