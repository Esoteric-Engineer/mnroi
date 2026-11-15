// Switches a controller's attack volumes on and off, and runs the active ones each frame. docs/characters.md section 4.

struct Volume {
    char d[0x80];
};

struct Self {
    char pad0[0x10];
    unsigned int f10;      // +0x10, 0x1000: the attack's energy has been paid
    char pad14[0x400];
    float f414;            // +0x414, energy cost of the motion
    char pad418[0x168];
    Volume volumes[7];     // +0x580
};

extern "C" {
void *Entity_GetActor(void *self);
int fn_80084A60(void *actor, float f);
void fn_8044775C(Volume *v);
int fn_804476F0(Volume *v);
void fn_804477A8(Volume *v);
int fn_800F4B58(Volume *v);

void fn_800E8768(register Self *self, int n)
{
    Volume *v = &self->volumes[n];
    if (!(self->f10 & 0x1000) && self->f414 != 0.0f) {
        fn_80084A60(Entity_GetActor(self), self->f414);
        self->f10 |= 0x1000;
    }
    fn_8044775C(v);
}

void fn_800E880C(register Self *self, int n)
{
    Volume *v = &self->volumes[n];
    if (fn_804476F0(v))
        fn_800F4B58(v);
    fn_804477A8(v);
}

int fn_800E8884(register Self *self)
{
    int hit = 0;
    Volume *v;
    unsigned int i;
    for (i = 0; i <= 6; i++) {
        v = &self->volumes[i];
        if (!fn_804476F0(v))
            continue;
        if (fn_800F4B58(v))
            hit = 1;
    }
    return hit;
}

void fn_800E893C(register Self *self)
{
    unsigned int i;
    for (i = 0; i <= 6; i++)
        fn_804477A8(&self->volumes[i]);
}
}
