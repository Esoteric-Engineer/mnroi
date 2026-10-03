// GameFlow: the debug-menu command dispatcher, the per-frame update, and the frame-rate and load-progress overlays.
// Owns the string literals and the float pool at 0x8048BDE0-0x8048BE78.

// Offsets are all that is known of the class; its real size is unknown.
class GameFlow
{
public:
    char unk0[0x14];
    int unk14;              // +0x14
    char unk18[0x4];
    unsigned char flags1C;  // +0x1C, single-bit flags
    char unk1D[0x3];
    unsigned int command;   // +0x20
    char unk24[0x108];
    int unk12C;             // +0x12C
    char unk130[0x4];
    int unk134;             // +0x134
    void *unk138;           // +0x138
    char unk13C[0x1C];
    int unk158;             // +0x158
    char unk15C[0x60];
    int unk1BC;             // +0x1BC
    char unk1C0[0x20];
    int unk1E0;             // +0x1E0
    char unk1E4[0x9C];
    int unk280;             // +0x280

    void RunCommand();
    void Update();
    void DrawFrameRate();
    void SetLoadProgress(float progress, int redraw);
    void DrawLoadProgress(int a, int b);
};

// The pad or input object; only its flags word at +0x7E is known.
typedef struct Unk7E
{
    char unk0[0x7E];
    unsigned short flags7E;
} Unk7E;

extern char lbl_80552110[]; // the game-state object G (docs/versus.md section 4.1)
extern char lbl_8052F060[]; // the level/world object
extern char lbl_80593BE8[]; // the globals object of Game/fn_80443908.cpp
extern char lbl_8057E430[];
extern void *lbl_8066BE10;
extern void *lbl_8066D6DC; // the overlay text object (docs/versus.md section 6)

extern "C" {

extern int fn_8012D470(void);
extern int fn_8005287C(void);
extern void fn_8011C008(void *obj, int a);
extern void fn_8002DB78(char *level);
extern void fn_8002D7A8(char *level, const char *name, int a, int b, int c, int d);
extern void fn_80128C3C(const char *name);
extern void *fn_8009543C(char *g, int a, const char *name);
extern int fn_800B0C1C(void *entity);
extern void *fn_80085AF0(void *entity);
extern int fn_80430050(char *level);
extern void fn_80096268(void *actor, int a, int b);
extern void fn_80446094(GameFlow *p, int a);
extern int fn_80431DDC(GameFlow *p);
extern int fn_80431E08(char *level);
extern int fn_80196BF0(void *p);
extern float fn_8042E998(char *globals);
extern void *fn_80432BC4(void);
extern int fn_804460BC(void *p);
extern int fn_8016732C(void *p);
extern void fn_8021A5FC(int a);
extern void fn_801284D4(void);
extern int fn_800B5124(GameFlow *p);
extern void fn_800B47C0(GameFlow *p);

extern int sprintf(char *dst, const char *fmt, ...);
extern unsigned int fn_804324EC(char *globals);
extern int fn_800FE284(int index);
extern int fn_80426E88(void *text, int font);
extern void fn_80101188(void *text, float height);
extern void fn_80100C08(void *text, int a);
extern int fn_800B92DC(void **text, const char *s, float x, float y);

extern void fn_800B6AA4(GameFlow *p);
extern void fn_800B6B34(GameFlow *p, int screen, int a);
extern void fn_800B6E44(GameFlow *p, int state);
extern void fn_800B7204(GameFlow *p);
extern void fn_800B7268(GameFlow *p);
extern void fn_800B72B4(GameFlow *p);
extern void fn_800B73C4(GameFlow *p);
extern void fn_800B743C(GameFlow *p);
extern void fn_800B74C4(GameFlow *p);
extern void fn_800B7514(GameFlow *p);
extern void fn_800B7584(GameFlow *p);
extern void fn_800B7654(GameFlow *p);
extern void fn_800B76C0(GameFlow *p);
extern void fn_800B7894(GameFlow *p);
extern void fn_800B7918(GameFlow *p);
extern void fn_800B797C(GameFlow *p);
extern void fn_800B7A0C(GameFlow *p);
extern void fn_800B7AA4(GameFlow *p);
extern void fn_800B7B34(GameFlow *p);
extern void fn_800B7B98(GameFlow *p);
extern void fn_800B7BD4(GameFlow *p);
extern void fn_800B7C50(GameFlow *p);
extern void fn_800B7D28(GameFlow *p);
extern void fn_800B7D6C(GameFlow *p);
extern void fn_800B7DB0(GameFlow *p);
extern void fn_800B7DF4(GameFlow *p);
extern void fn_800B7E38(GameFlow *p);
extern void fn_800B7EA4(GameFlow *p);
extern void fn_800B7F04(GameFlow *p);
extern void fn_800B7F64(GameFlow *p);
extern void fn_800B7FC4(GameFlow *p);
extern void fn_800B8024(GameFlow *p);
extern void fn_800B8084(GameFlow *p);
extern void fn_800B80E0(GameFlow *p);
extern void fn_800B8174(GameFlow *p, int a);
extern void fn_800B81D0(GameFlow *p);
extern void fn_800B8210(GameFlow *p);
extern int fn_800B8290(GameFlow *p);
extern void fn_800B831C(GameFlow *p);
extern void fn_800B8408(GameFlow *p);
extern void fn_800B84F4(GameFlow *p);
extern void fn_800B8544(GameFlow *p);

}

void GameFlow::RunCommand()
{
    void *entity;
    register void *actor;

    unk12C = 0;

    if (fn_8012D470() == 0 || unk158 != 0) {
        return;
    }

    if (command > 0x33 && command <= 0x38) {
        fn_800B7204(this);
        return;
    }

    if (command > 0x38 && command <= 0x3D) {
        unk1BC = command - 5;
        fn_800B6B34(this, 4, 1);
        fn_800B6E44(this, 0);
        return;
    } else if (command > 0x2E && command <= 0x33) {
        fn_800B7268(this);
    } else if (command > 0x560 && command <= 0x661) {
        fn_800B73C4(this);
    } else if (command > 0x35E && command <= 0x45F) {
        fn_800B743C(this);
    } else if (command > 0x45F && command <= 0x560) {
        fn_800B74C4(this);
    } else if (command > 0x25D && command <= 0x35E) {
        fn_800B7584(this);
    }

    switch (command) {
    case 0x0:
        break;
    case 0x13:
        fn_800B6B34(this, 0x21, 1);
        fn_800B6E44(this, 4);
        break;
    case 0x15:
        fn_800B7C50(this);
        break;
    case 0x16:
        break;
    case 0x19:
        fn_800B6E44(this, 0x4A);
        break;
    case 0x8:
        fn_800B7E38(this);
        fn_8011C008(lbl_8066BE10, 1);
        break;
    case 0x2:
        fn_800B7DB0(this);
        break;
    case 0x1:
        fn_800B7D6C(this);
        break;
    case 0x4:
        fn_800B7D28(this);
        break;
    case 0x5:
        fn_800B7DF4(this);
        break;
    case 0x26:
        fn_800B6E44(this, 0);
        fn_800B6B34(this, 0xC, 1);
        break;
    case 0x27:
        fn_800B81D0(this);
        fn_800B6E44(this, 0x26);
        unk1BC = 0x10;
        break;
    case 0x2E:
        fn_800B7514(this);
        break;
    case 0x1C:
        fn_800B7EA4(this);
        break;
    case 0x1D:
        fn_800B7F04(this);
        break;
    case 0x1E:
        fn_800B80E0(this);
        break;
    case 0x1F:
        fn_800B7F64(this);
        break;
    case 0x20:
        fn_800B7FC4(this);
        break;
    case 0x21:
        fn_800B8024(this);
        break;
    case 0x22:
        fn_800B8084(this);
        break;
    case 0x59:
        fn_800B8174(this, 0);
        break;
    case 0x5A:
        fn_800B8174(this, 1);
        break;
    case 0x5B:
        fn_800B8174(this, 2);
        break;
    case 0x9:
        fn_800B6B34(this, 0x11, 1);
        fn_800B6E44(this, 0);
        break;
    case 0x28:
        fn_800B8210(this);
        break;
    case 0x2B:
        if (fn_800B8290(this) == 0) {
            return;
        }
    case 0x2C:
        fn_800B831C(this);
        break;
    case 0x29:
        if (fn_800B8290(this) == 0) {
            return;
        }
    case 0x2A:
        fn_800B8408(this);
        break;
    case 0xA:
        fn_800B6B34(this, 0x15, 1);
        fn_800B6E44(this, 0);
        break;
    case 0x2D:
        fn_800B7BD4(this);
        break;
    case 0x23:
        fn_800B6B34(this, 0x1B, 1);
        fn_800B6E44(this, 0);
        break;
    case 0x24:
        fn_800B6B34(this, 0x1D, 1);
        fn_800B6E44(this, 0);
        break;
    case 0x25:
        fn_800B6B34(this, 0x1E, 1);
        fn_800B6E44(this, 0);
        break;
    case 0xB:
        fn_800B6B34(this, 0x17, 1);
        fn_800B6E44(this, 0);
        break;
    case 0xD:
        fn_800B6B34(this, 0x18, 1);
        fn_800B6E44(this, 0);
        break;
    case 0x4F:
        fn_800B8544(this);
        break;
    case 0x6:
        fn_800B84F4(this);
        break;
    case 0xE:
        fn_800B6B34(this, 0x19, 1);
        fn_800B6E44(this, 0);
        break;
    case 0xF:
        fn_800B6B34(this, 0x1A, 1);
        fn_800B6E44(this, 0);
        break;
    case 0x11:
        fn_800B6B34(this, 0x1F, 1);
        fn_800B6E44(this, 0);
        break;
    case 0x12:
        fn_800B6B34(this, 0x20, 1);
        fn_800B6E44(this, 0);
        break;
    case 0x17:
        fn_800B6E44(this, 0x18);
        break;
    case 0x10:
        fn_800B72B4(this);
        break;
    case 0x18:
        fn_800B7654(this);
        break;
    case 0x14:
        fn_800B76C0(this);
        break;
    case 0x3E:
        if (fn_8005287C() == 0) {
            fn_800B6E44(this, 0);
            fn_800B6AA4(this);
            break;
        }
        unk14 = 1;
        if ((((Unk7E *)lbl_8057E430)->flags7E & 4) != 0) {
        }
        fn_80446094(this, 0);
        fn_800B7894(this);
        break;
    case 0x3F:
        fn_80446094(this, 1);
        fn_800B7894(this);
        break;
    case 0x42:
        fn_80446094(this, 2);
        fn_800B7894(this);
        break;
    case 0x41:
        fn_800B6B34(this, 0x6, 1);
        fn_800B6E44(this, 0);
        break;
    case 0x40:
        fn_800B6B34(this, 0x1, 1);
        fn_800B6E44(this, 0);
        break;
    case 0x43:
        unk14 = 0;
        fn_800B7918(this);
        break;
    case 0x46:
        fn_800B797C(this);
        break;
    case 0x44:
        fn_800B6B34(this, 0x8, 1);
        fn_800B6E44(this, 0);
        break;
    case 0x45:
        fn_800B7A0C(this);
        break;
    case 0x47:
        fn_800B6B34(this, 0x2, 1);
        fn_800B6E44(this, 0);
        break;
    case 0x48:
        fn_800B6B34(this, 0x3, 1);
        fn_800B6E44(this, 0);
        break;
    case 0x49:
        fn_800B6B34(this, 0x5, 1);
        fn_800B6E44(this, 0);
        break;
    case 0x4A:
        unk14 = 0;
        fn_800B7AA4(this);
        break;
    case 0x58:
        fn_8002DB78(lbl_8052F060);
        break;
    case 0x4B:
        fn_800B7B34(this);
        break;
    case 0x4C:
        fn_800B6B34(this, 0xA, 1);
        fn_800B6E44(this, 0);
        break;
    case 0x50:
        entity = fn_8009543C(lbl_80552110, unk280, "plr_wolverine");
        if (entity != 0 && fn_800B0C1C(entity) != 0) {
            actor = fn_80085AF0(entity);
            fn_80096268(actor, fn_80430050(lbl_8052F060), 0);
        }
        fn_800B6E44(this, 0);
        break;
    case 0x51:
        entity = fn_8009543C(lbl_80552110, unk280, "plr_ironman");
        if (entity != 0 && fn_800B0C1C(entity) != 0) {
            actor = fn_80085AF0(entity);
            fn_80096268(actor, fn_80430050(lbl_8052F060), 0);
        }
        fn_800B6E44(this, 0);
        break;
    case 0x52:
        fn_8002D7A8(lbl_8052F060, "powerplant", 8, 0, 0, 0);
        fn_800B6E44(this, 0);
        break;
    case 0x53:
        fn_8002D7A8(lbl_8052F060, "0_Test_Clash", 8, 0, 0, 0);
        fn_800B6E44(this, 0);
        break;
    case 0x54:
        fn_8002D7A8(lbl_8052F060, "0_Test_Arena", 8, 0, 0, 0);
        fn_800B6E44(this, 0);
        break;
    case 0x55:
        fn_8002D7A8(lbl_8052F060, "0_Test_Look", 8, 0, 0, 0);
        fn_800B6E44(this, 0);
        break;
    case 0x56:
        fn_80128C3C("example1");
        fn_800B6E44(this, 0);
        break;
    case 0x57:
        fn_80128C3C("example2");
        fn_800B6E44(this, 0);
        break;
    case 0x4D:
        fn_800B7B98(this);
        break;
    case 0x4E:
        fn_800B6B34(this, 0xB, 1);
        fn_800B6E44(this, 0);
        break;
    default:
        break;
    }
}

void GameFlow::Update()
{
    float dt;

    if (fn_80431DDC(this) != 0 && fn_80431E08(lbl_8052F060) == 0) {
        return;
    }

    fn_80196BF0(unk138);
    dt = fn_8042E998(lbl_80593BE8);

    if ((flags1C & 1) && fn_804460BC(fn_80432BC4()) == 0) {
        if (unk134 != 0) {
            fn_8021A5FC(-1);
        }
        fn_801284D4();
    }

    fn_8016732C(fn_80432BC4());

    if (fn_800B5124(this) != 0) {
        return;
    }

    if (unk1E0 == 1) {
        DrawFrameRate();
    }
    fn_800B47C0(this);
}

void GameFlow::DrawFrameRate()
{
    float frameTime;
    float fps;
    char unk10[0x18];       // dead locals; only their stack slots survive in the release build
    int oldFont;
    int unk2C;
    char text[0x80];

    frameTime = fn_804324EC(lbl_80593BE8) * 0.001f;
    fps = 1.0f / frameTime;

    oldFont = fn_80426E88(lbl_8066D6DC, fn_800FE284(5));
    if (unk1E0 == 1) {
        fn_80101188(lbl_8066D6DC, 32.0f);
    } else {
        fn_80101188(lbl_8066D6DC, 16.0f);
    }
    fn_80100C08(lbl_8066D6DC, 0);
    sprintf(text, "%.0f", fps);
    fn_800B92DC(&lbl_8066D6DC, text, 555.0f, 30.0f);
    fn_80426E88(lbl_8066D6DC, oldFont);
}

// The loader calls this with a fraction in [0,1]; the drawing itself is stripped in the release.
void GameFlow::SetLoadProgress(float progress, int redraw)
{
    if (redraw != 0) {
        DrawLoadProgress(1, 0);
    }
}

void GameFlow::DrawLoadProgress(int a, int b)
{
}
