// WallClimb state's event handler.

class Vector
{
public:
    float x, y, z, w;
    Vector();
};

struct Clip;

struct Channel {
    char pad0[0x1C];
    Clip *clip;            // +0x1C
};

struct Ent {
    int pad;
};

struct PEnt : Ent {
    int x;
};

struct Obj {
    char pad0[0x10];
    unsigned int flags;    // +0x10
    char pad14[0x409 - 0x14];
    unsigned char b409;    // +0x409
    unsigned char b40A;    // +0x40A
    unsigned char b40B;    // +0x40B
    unsigned char b40C;    // +0x40C
};

extern "C" {
extern char lbl_80552110[];
double fabs(double x);
extern float fabsf(float x);
PEnt *Entity_GetActor(void *self);
void fn_800CC3A4(void *self);
void fn_800CD77C(void *self);
void fn_800F0C70(void *self, int a, int b, int c, int d);
float fn_800CC1D4(void *self, int id, Vector *stick);
Vector *fn_800B1750(Ent &actor);
char *fn_8043289C(char *g);
float fn_8042EBF4(Vector *a, void *b);
int fn_8009B04C(Ent &actor);
float fn_80199F24(Clip *clip, int tag);
void fn_8019DB24(Channel *ch, float time);
void *fn_8009AF80(Ent &actor);
void fn_8019C408(void *anim);
float fn_804442BC(Clip *clip, float frame);
void fn_800BD2D0(void *self, unsigned int ms);

int fn_800D10D0(register Obj *self, Channel *ch, int type, int value, int extra)
{
    switch (type) {
    case 0x14:
        self->flags |= 1;
        fn_800CC3A4(self);
        break;
    case 0x4F:
        self->b40B = value;
        if (extra)
            self->b40C = extra;
        else
            self->b40C = 0x15;
        break;
    case 0x50:
        self->b40A = (unsigned int)(value - 1) < 3 ? (unsigned int)(value - 1) : 3;
        break;
    case 0x4E:
        self->b409 = (unsigned int)(value - 1) < 3 ? (unsigned int)(value - 1) : 3;
        break;
    case 0x12:
        fn_800CD77C(self);
        break;
    case 0x4:
        fn_800F0C70(self, 0, 1, 1, 0);
        break;
    case 0x10: {
        Vector stick;
        float mag = fn_800CC1D4(self, 7, &stick);
        float up = stick.z;
        float side = stick.x;
        int go = 0;
        if (fn_8042EBF4(fn_800B1750(*Entity_GetActor(self)), fn_8043289C(lbl_80552110) + 0x370) < -0.2f)
            side = -side;
        switch (fn_8009B04C(*Entity_GetActor(self))) {
        case 0x120:
            if (fabsf(side) > fabs(up) && side > 0.1f)
                go = 1;
            break;
        case 0x121:
            if (fabsf(side) > fabs(up) && side < -0.1f)
                go = 1;
            break;
        case 0x11F:
            if (fabsf(up) > fabs(side) && up > 0.1f)
                go = 1;
            break;
        case 0x11E:
            if (fabsf(up) > fabs(side) && up < -0.1f)
                go = 1;
            break;
        }
        if (go) {
            fn_8019DB24(ch, fn_80199F24(ch->clip, 0x11));
            fn_8019C408(fn_8009AF80(*Entity_GetActor(self)));
            fn_800BD2D0(self, (unsigned int)(fn_804442BC(ch->clip, 30.0f) * 1000.0f));
            self->flags |= 1;
        }
        break;
    }
    case 0x1E:
        self->flags |= 1;
        break;
    }
    return 1;
}
}
