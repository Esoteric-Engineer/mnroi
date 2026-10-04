// GameFlow methods of 0x800B4CF8-0x800B5BC4: pad checks, slot pick, load start, the per-frame tick and its state stage.
// A .c unit: `this` is a register first parameter. docs/versus.md section 6 has the class.

typedef struct GameFlow
{
    float timer;               // +0x0
    int unk4;                  // +0x4
    int unk8;                  // +0x8
    int unkC;                  // +0xC
    int unk10;                 // +0x10
    int unk14;                 // +0x14
    char unk18[4];
    unsigned char unk1C;       // +0x1C
    char unk1D[7];
    int unk24;                 // +0x24
    char unk28[0x110];
    int unk138;                // +0x138
    int unk13C;                // +0x13C
    char unk140[0x20];
    int unk160;                // +0x160
    int unk164;                // +0x164
    char unk168[0x34];
    int unk19C;                // +0x19C
    char unk1A0[0xE4];
    int numUnplugged;          // +0x284
    int unplugged[2];          // +0x288
} GameFlow;

extern char lbl_80552110[]; // the game-state object G
extern char lbl_8052F060[]; // the level/world object

extern void fn_80232B78(int handle);
extern void fn_800B86CC(void **text);
extern int fn_801969CC(float f1, float f2, float f3, float f4, unsigned short a, unsigned short b);
extern int fn_80196BF0(int handle);
extern int SetCommand__8GameFlowi(GameFlow *p, int command);
extern void BeginLoad__8GameFlow(GameFlow *p);
extern void EndLoad__8GameFlow(GameFlow *p);
extern void fn_80445F28(void (*hook)(unsigned short));
extern void fn_80445F4C(void (*hook)(unsigned short));
extern void OnPadRemoved__FUs(unsigned short port);
extern void OnPadInserted__FUs(unsigned short port);
extern void *lbl_8066D6DC; // the overlay text object (docs/versus.md section 6)
extern int lbl_8066C660;
typedef struct PadInfo
{
    char unk0[0x78];
    unsigned short unk78; // +0x78
    unsigned short unk7A; // +0x7A
} PadInfo;

extern PadInfo lbl_8057E430;
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
extern int fn_804439A4(char *globals);
extern void fn_801AF754(char *globals);
extern void fn_80432D00(char *flow, int a);
extern int sprintf(char *dst, const char *fmt, ...);
extern int fn_8012D4AC(int a);
extern int fn_80427400(void);
extern int fn_8012F32C(int a, char *name);
extern void fn_800189E0(float x, float y, float w, float h, int image, float alpha);
extern void fn_804325CC(char *globals);
extern int fn_80432764(int a, unsigned short *port);
extern float fn_8042E998(char *globals);
extern int fn_8005287C(void);
extern void fn_801A7C14(void);
extern void *fn_804317BC(void *g, int i); // &G.slots[i]
extern int fn_80434900(void *g);          // G+0x590, the active slot count
extern void fn_801AA570(int a);
extern int fn_80445F70(int a);
extern int fn_80432DCC(GameFlow *flow);
extern int fn_8044272C(char *slot);
extern int fn_80442774(char *slot);
extern int fn_80432708(int a);
extern void fn_800B4764(GameFlow *flow);
extern void fn_800B5930(GameFlow *flow);
extern void fn_80443C4C(char *slot, int port);
extern void fn_80128358(int a);
extern void Stub6D48__8GameFlow(GameFlow *p);
extern void RunCommand__8GameFlow(GameFlow *p);
extern void fn_80112B2C(int a);
extern void fn_8011C284(void *obj, int a);
extern int fn_801AA368(void);
extern char lbl_80593BE8[]; // the globals object of Game/fn_80443908.cpp
extern char lbl_80552920[]; // the GameFlow instance
extern const char lbl_8048BD9C[]; // "kT_INSERT_CONTROLLER%d_NGC", defined in Game/fn_800B46B0.c
extern float lbl_8066BA24; // .sdata, screen width
extern float lbl_8066BA28; // .sdata, screen height
extern float lbl_8066D6B4;
extern void *lbl_8066BE10;

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

int fn_800B5124(register GameFlow *this)
{
    char name[0x30];
    int image;
    int found = 0;
    int flag = 1;
    int paused;
    unsigned short port;
    char *first;
    int matched;
    int player;

    if (this->unk4 == 0) {
        return 0;
    }
    paused = fn_800B4FC0(this);
    if (paused) {
        if (fn_804439A4(lbl_80593BE8) == 0) {
            this->unk8 = 1;
            fn_801AF754(lbl_80593BE8);
            fn_80432D00(lbl_80552920, 1);
        }
        sprintf(name, lbl_8048BD9C, fn_8012D4AC(this->unplugged[0]));
        image = fn_8012F32C(fn_80427400(), name);
        fn_800189E0(320.0f - lbl_8066BA24 * 0.5f, lbl_8066D6B4, lbl_8066BA24, lbl_8066BA28, image, 255.0f);
    } else {
        if (fn_804439A4(lbl_80593BE8)) {
            this->unk8 = 0;
            fn_804325CC(lbl_80593BE8);
        }
    }
    port = -1;
    if (flag) {
        if (fn_80432764(1, &port) || fn_80432764(10, &port)) {
            first = 0;
            matched = 0;
            if (fn_804329E0(lbl_8052F060)) {
                if (fn_804427FC(lbl_80552110)) {
                    do {
                        if (fn_8043B31C(fn_804427D0(lbl_80552110)) == this->unplugged[0]) {
                            if (fn_80442624(fn_804427D0(lbl_80552110)) != port) {
                                return 1;
                            }
                            if (first == 0) {
                                first = fn_804427D0(lbl_80552110);
                            }
                            matched = 1;
                            break;
                        } else {
                            if (fn_80442624(fn_804427D0(lbl_80552110)) == port) {
                                return 1;
                            }
                        }
                    } while (fn_80094A9C(lbl_80552110));
                }
            } else {
                player = fn_8012D63C(port);
                if (player == this->unplugged[0] || found != 0) {
                    matched = 1;
                }
            }
            if (matched) {
                if (first) {
                    fn_80443C4C(first, port);
                }
                this->unplugged[0] = this->unplugged[1];
                this->unplugged[1] = -1;
                this->numUnplugged--;
                if (this->numUnplugged == 0) {
                    this->unk4 = 0;
                    if (this->unk8 != 0 && fn_804439A4(lbl_80593BE8) && this->unk14 == 0) {
                        fn_804325CC(lbl_80593BE8);
                        if (fn_804329E0(lbl_8052F060) && this->unk14 == 0) {
                            fn_80112B2C(0);
                            fn_8011C284(lbl_8066BE10, 0);
                        }
                        this->unk8 = 0;
                    }
                }
            }
        }
    }
    if (paused) {
        fn_801AA368();
    }
    return paused;
}

void fn_800B5524(register GameFlow *this)
{
    return;
}

void fn_800B5548(register GameFlow *this)
{
    if (this->unk19C != 0) {
        fn_80232B78(this->unk19C);
        this->unk19C = 0;
    }
}

void fn_800B5594(register GameFlow *this, int begin)
{
    fn_800B86CC(&lbl_8066D6DC);
    lbl_8066C660 = 1;
    if (this->unk138 == 0) {
        this->unk138 = fn_801969CC(80.0f, 0.01f, 300.0f, 1.0f,
                                   lbl_8057E430.unk7A, lbl_8057E430.unk78);
    }
    fn_80196BF0(this->unk138);
    lbl_8066C660 = 0;
    SetCommand__8GameFlowi(this, 0x13);
    this->unk24 = 0;
    if (begin != 0) {
        BeginLoad__8GameFlow(this);
    } else {
        EndLoad__8GameFlow(this);
    }
    fn_80445F28(OnPadRemoved__FUs);
    fn_80445F4C(OnPadInserted__FUs);
}

void fn_800B5694(register GameFlow *this)
{
}

int fn_800B56B4(register GameFlow *this)
{
    return 0;
}

int fn_800B56DC(register GameFlow *this)
{
    unsigned int i;
    unsigned int j;
    void *slot;
    int level;

    for (i = 0; i < fn_80434900(lbl_80552110); i++) {
        fn_801AA570(fn_80442624(fn_804317BC(lbl_80552110, i)));
        if (fn_80445F70(3) && fn_80445F70(4) && fn_80445F70(10)) {
            return 0;
        }
    }
    if (fn_80432DCC(this) == 0 && fn_804439A4(lbl_80593BE8) == 0) {
        for (j = 0; j < fn_80434900(lbl_80552110); j++) {
            slot = fn_804317BC(lbl_80552110, j);
            if (fn_8044272C(slot) != 0 || fn_80442774(slot) != 0) {
                continue;
            }
            fn_801AA570(fn_80442624(slot));
            level = 0;
            if (fn_800531AC()) {
                level = fn_80430024(fn_800531AC());
            }
            if (fn_80432708(10) != 0 && level == 0) {
                this->unk160 = fn_80442624(fn_804317BC(lbl_80552110, j));
                this->unk164 = j;
                this->unk13C = 0;
                fn_800B5930(this);
                return 1;
            }
        }
    } else {
        if (fn_80432764(15, 0)) {
            fn_800B4764(this);
        }
    }
    return 0;
}

void fn_800B5930(register GameFlow *this)
{
    if (this->unk1C & 4) {
        SetCommand__8GameFlowi(this, 0x3e);
        BeginLoad__8GameFlow(this);
    }
}

int fn_800B5988(register GameFlow *this)
{
    register int found = 0;

    if (this->unk4 != 0) {
        if (fn_804460BC(fn_80432BC4()) == 0) {
            found = 1;
        }
    }
    fn_80128358(found);
    Stub6D48__8GameFlow(this);
    RunCommand__8GameFlow(this);
    return 0;
}

int fn_800B5A08(register GameFlow *this)
{
    if (fn_80432764(1, 0) || fn_80432764(10, 0)) {
        this->timer = 0.0f;
    }
    this->timer -= fn_8042E998(lbl_80593BE8);
    if (this->timer <= 0.0f && fn_8005287C()) {
        this->unk13C = 0;
        BeginLoad__8GameFlow(this);
        SetCommand__8GameFlowi(this, 0x42);
    }
    if (this->timer < 4.0f) {
        return 0;
    }
    return 1;
}

void fn_800B5AFC(register GameFlow *this)
{
    if (this->timer > 0.0f && fn_800B5A08(this)) {
        return;
    }
    fn_800B5524(this);
    if ((this->unk1C & 8) && fn_800B56B4(this)) {
        return;
    }
    if ((this->unk1C & 4) && fn_800B56DC(this)) {
        return;
    }
    fn_801A7C14();
    fn_800B5988(this);
}
