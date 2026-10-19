// HUD overlay names: copies each overlay's name and puts both players' template names, without their
// plr_/plr_alt prefix, in overlays 3 and 4; see docs/versus.md section 4.4.

inline int sn_return_decl(int a) { return a; }

class Hud
{
public:
    char pad[0x418C];
    int versus; // +0x418C
};

struct OverlayInfo
{
    int f0;
    const char *name; // +0x4
    char buf[0x70];   // +0x8
};

extern "C" {
char *strcpy(char *dst, const char *src);
char *strstr(const char *s, const char *find);
char *fn_80131060(int player);
void fn_801B738C(char *name);
void fn_80006450(Hud *self, const char *name);
}

extern OverlayInfo lbl_8050F820[13];

extern "C" void fn_800061CC(register Hud *self)
{
    int i;
    char *name0;
    char *name1;

    for (i = 0; i <= 12; i++) {
        strcpy(lbl_8050F820[i].buf, lbl_8050F820[i].name);
    }
    name0 = fn_80131060(0);
    name1 = fn_80131060(1);
    if (strstr(name0, "plr_alt")) {
        name0 += 7;
    } else {
        name0 += 4;
    }
    if (strstr(name1, "plr_alt")) {
        name1 += 7;
    } else {
        name1 += 4;
    }
    strcpy(lbl_8050F820[3].buf, name0);
    strcpy(lbl_8050F820[4].buf, name1);
    fn_801B738C(lbl_8050F820[3].buf);
    fn_801B738C(lbl_8050F820[4].buf);
    fn_80006450(self, "overlay1");
    if (self->versus) {
        fn_80006450(self, "overlay2");
    }
}
