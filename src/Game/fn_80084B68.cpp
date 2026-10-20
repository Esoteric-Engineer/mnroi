// Actor test: true unless a timed gate (+0x324 against the argument and a PLAYER tuning value) rejects it.

struct Actor {
    char pad0[0x324];
    float f324; // +0x324
};

extern "C" {
int fn_80086B6C(void *actor);
int fn_80086908(void *actor);
int fn_8008582C(void *actor);
int fn_8008618C(void *actor);
float fn_800B1884(void *actor, int id);
unsigned int fn_80435904(void);
}

extern "C" int fn_80084B68(register Actor *self, float f)
{
    if (fn_80086B6C(self) || fn_80086908(self)) {
        return 1;
    }
    if (self->f324 < f) {
        return 0;
    }
    if (fn_8008582C(self) && fn_8008618C(self)) {
        float t = fn_800B1884(self, 0xDE);
        if (self->f324 - f < t) {
            if (fn_80435904() % 100 == 0) {
            } else {
                return 0;
            }
        }
    }
    return 1;
}
