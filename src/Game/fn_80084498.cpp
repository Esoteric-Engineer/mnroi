// Actor-class template property handler for kinds 4 and 10 (ACTOR_*/ARMOR_*); ids in docs/characters.md section 3.
struct Prop {
    unsigned int id;
    union {
        int i;
        float f;
        unsigned short h[2];
        unsigned char b[4];
        char s[0x20];
    } v;
};

struct Actor {
    char pad0[0x300];
    int f300; // +0x300
    char pad1[4];
    int f308;
    int f30C;
    char pad2[4];
    short f314;
    short f316;
    char pad3[4];
    float f31C;
    float f320;
    float f324;
    float f328;
    float f32C;
    char pad4[0xC];
    float f33C;
    float f340;
    char pad5[0x40];
    short f384;
    char pad6[0x2A];
    int f3B0;
    int f3B4;
    char pad7[8];
    int f3C0;
};

extern char lbl_8064AA80[];

extern "C" {
int fn_80137CEC(char *name);
int fn_800FD5FC(char *name, int flag);
int fn_803A1AC4(char *tbl, char *name);
}

extern "C" int fn_80084498(register Actor *self, Prop *prop, int arg)
{
    switch (prop->id) {
    case 0x33:
        self->f31C = prop->v.i;
        self->f32C = self->f31C;
        break;
    case 0x34:
        self->f320 = prop->v.i;
        break;
    case 0x37:
        self->f33C = prop->v.f;
        break;
    case 0x38:
        self->f340 = prop->v.f;
        break;
    case 0x2E:
        self->f384 = fn_80137CEC(prop->v.s);
        break;
    case 0x31:
        self->f30C = prop->v.i;
        break;
    case 0x32:
        self->f308 = prop->v.i;
        break;
    case 0x35:
        self->f324 = prop->v.f;
        break;
    case 0x36:
        self->f328 = prop->v.f;
        break;
    case 0x30:
        self->f300 = prop->v.i;
        break;
    case 0x2D:
        self->f314 = prop->v.h[1];
        break;
    case 0x3A:
        self->f316 = prop->v.b[3];
        break;
    case 0x3B:
        self->f3B4 = fn_800FD5FC(prop->v.s, 0);
        if (self->f3B4 == 0) {
            self->f3B0 = fn_803A1AC4(lbl_8064AA80, prop->v.s);
        }
        break;
    case 0x6F:
        self->f3C0 = fn_803A1AC4(lbl_8064AA80, prop->v.s);
        break;
    default:
        return 0;
    }
    return 1;
}
