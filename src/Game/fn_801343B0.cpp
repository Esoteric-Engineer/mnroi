// Reads 22 PLAYER tuning fields (ids 0x8B-0xA4, 0xF6, 0xF7) into the float block at +0x598.

struct Ent {
    int pad;
};
struct PlayerEnt : Ent { // matching_notes 44
    int x;
};

struct AiObj {
    char pad0[0x598];
    float f[22]; // +0x598
};

extern "C" PlayerEnt *fn_80442080(AiObj *o);
extern "C" float fn_800B1884(Ent &e, int id);
extern "C" int fn_800B18EC(Ent &e, int id);
extern "C" float fn_8042CE28(int v);

extern "C" void fn_801343B0(register AiObj *self)
{
    self->f[0] = fn_800B1884(*fn_80442080(self), 0x8B);
    self->f[1] = fn_800B1884(*fn_80442080(self), 0x8C);
    self->f[2] = fn_8042CE28(fn_800B18EC(*fn_80442080(self), 0xA4));
    self->f[3] = fn_8042CE28(fn_800B18EC(*fn_80442080(self), 0x8D));
    self->f[4] = fn_800B1884(*fn_80442080(self), 0x8E);
    self->f[5] = fn_800B1884(*fn_80442080(self), 0x8F);
    self->f[6] = fn_800B1884(*fn_80442080(self), 0x90);
    self->f[7] = fn_800B1884(*fn_80442080(self), 0x91);
    self->f[8] = fn_800B1884(*fn_80442080(self), 0x92);
    self->f[9] = fn_800B1884(*fn_80442080(self), 0x9F);
    self->f[10] = fn_800B1884(*fn_80442080(self), 0x93);
    self->f[11] = fn_800B1884(*fn_80442080(self), 0x94);
    self->f[12] = fn_800B1884(*fn_80442080(self), 0x95);
    self->f[13] = fn_800B1884(*fn_80442080(self), 0x96);
    self->f[14] = fn_800B1884(*fn_80442080(self), 0x97);
    self->f[15] = fn_800B1884(*fn_80442080(self), 0x98);
    self->f[16] = fn_800B1884(*fn_80442080(self), 0x99);
    self->f[17] = fn_800B1884(*fn_80442080(self), 0x9A);
    self->f[18] = fn_800B1884(*fn_80442080(self), 0x9B);
    self->f[19] = fn_800B1884(*fn_80442080(self), 0x9C);
    self->f[20] = fn_800B1884(*fn_80442080(self), 0xF7);
    self->f[21] = fn_800B1884(*fn_80442080(self), 0xF6);
}
