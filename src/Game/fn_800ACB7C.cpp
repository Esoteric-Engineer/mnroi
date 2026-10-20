// Binds the tuning record and picks the slot role.

extern "C" {
void *fn_801B308C(int kind, void *name);
int fn_800B0C58(void *self);
void *fn_800B14A0(void *self);
int fn_80432870(void *g);
void *fn_800946D4(void *g, void *actor);
int fn_80442774(void *slot);
void *fn_80085AF0(void *actor);
int fn_804428B4(void *slot);
int fn_80095608(void *self);
int fn_80085D3C(void *actor);
int fn_80085DCC(void *actor);
void fn_800B1950(void *self, int role);
extern char lbl_80552110[0x10]; // the game-state object G
}

struct Ent {
    unsigned char kind; // +0x0
    char pad[0xFB];
    char name[1]; // +0xFC
    char pad2[0x6F];
    void *rec; // +0x16C
};

extern "C" int fn_800ACB7C(register Ent *self)
{
    self->rec = fn_801B308C(self->kind, self->name);
    if (fn_800B0C58(self)) {
        void *actor = fn_800B14A0(self);
        int role = 2;
        if (fn_80432870(lbl_80552110) && fn_800946D4(lbl_80552110, actor) && fn_80442774(fn_800946D4(lbl_80552110, actor))) {
            switch (fn_804428B4(fn_80085AF0(actor))) {
            case 0:
                role = 1;
                break;
            case 2:
                role = 3;
                break;
            default:
                role = 2;
                break;
            }
        } else {
            if (!fn_80095608(self) && fn_80085D3C(actor))
                role = 4;
            else if (fn_80085DCC(actor))
                role = 5;
            else
                role = 0;
        }
        fn_800B1950(self, role);
    }
    return 1;
}
