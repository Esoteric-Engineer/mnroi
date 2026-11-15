// Resolves a marker on the effect's owner to a world position.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Effect {
    char pad0[0x80];
    void *owner; // +0x80
};

extern "C" {
int fn_800B0F0C(void *actor);
void *fn_800B1568(void *actor);
void *fn_8009AD80(void *player);
void *fn_800B1668(void *actor);
int fn_801A5104(void *model, unsigned char kind, unsigned short id, Vector *out, void *world);
int fn_801A51F4(void *model, unsigned char kind, Vector *out, void *world);

int fn_8039A230(register Effect *self, Vector *out, unsigned char kind, unsigned char id)
{
    if (!self->owner || !fn_800B0F0C(self->owner) || !fn_8009AD80(fn_800B1568(self->owner)) || kind == 0xFF)
        return 0;
    if (id != 0xFF && fn_801A5104(fn_8009AD80(fn_800B1568(self->owner)), kind, id, out, fn_800B1668(self->owner)))
        return 1;
    if (fn_801A51F4(fn_8009AD80(fn_800B1568(self->owner)), kind, out, fn_800B1668(self->owner)))
        return 1;
    return 0;
}
}
