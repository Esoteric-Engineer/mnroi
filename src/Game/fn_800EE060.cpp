// HugeReaction state's event handler.

class Vector
{
public:
    float x, y, z, w;
    Vector();
};

struct Clip;
struct Channel;

struct Ent {
    int pad;
};

struct PEnt : Ent {
    int x;
};

struct EObj {
    char pad0[0x3AC];
};

struct Obj : EObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int state); // +0x30
};

struct Mat4;

extern "C" {
PEnt *Entity_GetActor(void *self);
Clip *fn_804355C0(Channel *ch);
float fn_80447434(Channel *ch);
void fn_80199FC8(Clip *clip, float time, Vector *vel);
Mat4 *fn_800B1668(Ent &actor);
void fn_80435754(Vector *v, Mat4 *m);
int fn_8009B04C(Ent &actor);
void fn_80097CE8(Ent &actor, int motion, int a, float b, int c, float d, float e);
void fn_80065CB0(Ent &actor, Vector *vel);
void fn_800CC3A4(void *self);
void fn_80065AF8(Ent &actor, int a, int b);
void fn_80066604(Ent &actor);
int fn_80085EEC(void *actor);
int fn_800D01A4(void *self);
void fn_8009AEC8(Ent &actor, int v);
int fn_800861EC(void *actor);
void fn_800CD77C(void *self);

int fn_800EE060(register Obj *self, Channel *ch, int type, int value, int extra)
{
    switch (type) {
    case 0x14: {
        Vector vel;
        fn_80199FC8(fn_804355C0(ch), fn_80447434(ch), &vel);
        fn_80435754(&vel, fn_800B1668(*Entity_GetActor(self)));
        switch (fn_8009B04C(*Entity_GetActor(self))) {
        case 0x7F:
            fn_80097CE8(*Entity_GetActor(self), 0x86, 0, 30.0f, 0, 7.5f, -1.0f);
            fn_80065CB0(*Entity_GetActor(self), &vel);
            fn_800CC3A4(self);
            break;
        case 0x80:
            fn_80097CE8(*Entity_GetActor(self), 0x88, 0, 30.0f, 0, 7.5f, -1.0f);
            fn_80065CB0(*Entity_GetActor(self), &vel);
            fn_800CC3A4(self);
            break;
        case 0x81:
            fn_80097CE8(*Entity_GetActor(self), 0x8A, 0, 30.0f, 0, 7.5f, -1.0f);
            fn_80065CB0(*Entity_GetActor(self), &vel);
            fn_800CC3A4(self);
            break;
        case 0x82:
            fn_80097CE8(*Entity_GetActor(self), 0x8C, 0, 30.0f, 0, 7.5f, -1.0f);
            fn_80065CB0(*Entity_GetActor(self), &vel);
            fn_800CC3A4(self);
            break;
        case 0x83:
            fn_80097CE8(*Entity_GetActor(self), 0x8E, 0, 30.0f, 0, 7.5f, -1.0f);
            fn_80065CB0(*Entity_GetActor(self), &vel);
            fn_800CC3A4(self);
            break;
        case 0x84:
            fn_80097CE8(*Entity_GetActor(self), 0x90, 0, 30.0f, 0, 7.5f, -1.0f);
            fn_80065CB0(*Entity_GetActor(self), &vel);
            fn_800CC3A4(self);
            break;
        case 0x85:
            fn_80097CE8(*Entity_GetActor(self), 0x92, 0, 30.0f, 0, 7.5f, -1.0f);
            fn_80065CB0(*Entity_GetActor(self), &vel);
            fn_800CC3A4(self);
            break;
        case 0x94:
        case 0x99:
        case 0x9A:
        case 0x9B:
            fn_80065AF8(*Entity_GetActor(self), 1, 0);
            fn_80066604(*Entity_GetActor(self));
            self->s5(0xF);
            break;
        case 0x95:
            fn_80065AF8(*Entity_GetActor(self), 1, 0);
            fn_80066604(*Entity_GetActor(self));
            if (fn_80085EEC(Entity_GetActor(self)))
                self->s5(1);
            else
                self->s5(2);
            break;
        case 0x97:
            if (fn_80085EEC(Entity_GetActor(self)))
                self->s5(1);
            else if (fn_800D01A4(self))
                self->s5(8);
            else
                self->s5(5);
            break;
        case 0x98:
            if (fn_80085EEC(Entity_GetActor(self))) {
                self->s5(1);
                break;
            }
            fn_8009AEC8(*Entity_GetActor(self), 0);
            fn_80066604(*Entity_GetActor(self));
            if (fn_800861EC(Entity_GetActor(self)))
                self->s5(0x25);
            else
                self->s5(0x17);
            break;
        case 0x96:
        case 0x9C:
        case 0x9D:
        case 0x9E:
            fn_80065AF8(*Entity_GetActor(self), 1, 0);
            fn_80066604(*Entity_GetActor(self));
            self->s5(6);
            break;
        }
        return 1;
    }
    case 0x12:
        switch (fn_8009B04C(*Entity_GetActor(self))) {
        case 0x94:
        case 0x99:
        case 0x9A:
        case 0x9B:
            fn_80065AF8(*Entity_GetActor(self), 1, 0);
            fn_80066604(*Entity_GetActor(self));
            self->s5(0xF);
            break;
        case 0x95:
        case 0x97:
        case 0x98:
            fn_800CD77C(self);
            break;
        }
        return 1;
    }
    return 0;
}
}
