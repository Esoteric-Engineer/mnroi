// Caches PLAYER tuning fields 43-45 and a GLOBALS value into the entity; docs/versus.md rows 20-21.

typedef struct Fighter {
    char pad[0x3C4];
    float f3C4; // +0x3C4
    float f3C8; // +0x3C8
    float f3CC; // +0x3CC
    float f3D0; // +0x3D0
} Fighter;

extern float fn_800B1884(void *e, int id);
extern float fn_80433D20(void *record, int id, int slot);
extern void *lbl_8066C6C8;

void fn_8009D71C(register Fighter *self)
{
    self->f3CC = fn_800B1884(self, 0x2D);
    self->f3C4 = fn_800B1884(self, 0x2B);
    self->f3C8 = fn_800B1884(self, 0x2C);
    self->f3D0 = fn_80433D20(lbl_8066C6C8, 0x39, 0) * self->f3CC;
}
