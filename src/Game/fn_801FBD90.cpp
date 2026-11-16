// The effect classes cParticleToggle, cDummyProjectile, cEffectSpawn and cCrystalDetonate (docs/story.md row 9).
// Pool read from 0x804A15A8 (extern_pool).

inline int sn_return_decl(int a) { return a; }

struct cScript {
    char d[0x24];
    char *vptr; // +0x24
};

struct Ref8 {
    int unk0;
    int value; // +0x4
};

struct SVector {
    float x, y, z, w;
};

struct cParticleToggle : cScript { // 0x4C
    char effect[0x20]; // +0x28
    float cur;         // +0x48, toggled between params 3 and 4
    cParticleToggle() __asm__("fn_804689C0");
};

struct cDummyProjectile : cScript { // 0x50
    char pad28[8];
    SVector from; // +0x30
    SVector to;   // +0x40
    cDummyProjectile() __asm__("fn_80468A0C");
};

struct cEffectSpawn : cScript { // 0x28
    cEffectSpawn() __asm__("fn_80468A70");
};

struct cCrystalDetonate : cScript { // 0x2C
    int fired; // +0x28
    cCrystalDetonate() __asm__("fn_80468ABC");
};

struct SObj {
    int unk0;
    void fn_800B1FA8(int v) __asm__("fn_800B1FA8");
};

struct SActor : SObj {
    int pad;
};

extern "C" {

int stricmp(const char *a, const char *b);
char *strncpy(char *dst, const char *src, unsigned n);
int fn_800797D4(cScript *self);
int fn_80079068(cScript *self, unsigned int i);
unsigned int fn_800791C8(cScript *self, unsigned int i);
float fn_8007935C(cScript *self, unsigned int i);
char *fn_800794FC(cScript *self, unsigned int i);
void fn_8007D404(cScript *self, float seconds, int kind, float a, float b, float c, float d, int e);
void fn_8046B6C8(Ref8 *ev, int x);
void fn_8046B5A8(Ref8 *ev, int x);
void fn_8046CE70(Ref8 *ev, int x);
int fn_8046CBB8(Ref8 *ev);
int fn_8046CC28(Ref8 *ev);
void fn_8046CC94(Ref8 *ev);
int fn_8046CD30(Ref8 *ev);
void fn_8046CDB4(Ref8 *ev, float a, float b);
void fn_80082E90(Ref8 *ev, char *name, int a, int b);
char *fn_80082CC8(Ref8 *ev, int i);
void fn_80083428(Ref8 *ev, int a);
void fn_80082E24(Ref8 *ev, char *name);
void fn_800830A0(Ref8 *ev, int a);
void fn_80082440(Ref8 *ev, SVector *out);
int fn_80080C88(char *name, SVector *from, SVector *to, float speed, int handle);
int fn_80080C20(Ref8 *ev);
SActor *fn_80080BA8(Ref8 *ev);
int fn_80171F8C();
void fn_80133988(int h);
void fn_801339C8(int h);

int fn_801FC894(cParticleToggle *self);
float fn_801FC8DC(cParticleToggle *self);
int fn_801FC924(cParticleToggle *self);
float fn_801FC96C(cParticleToggle *self);
float fn_801FC9B4(cParticleToggle *self);
int fn_801FC9FC(cParticleToggle *self);
char *fn_801FCA54(cParticleToggle *self);
char *fn_801FCA9C(cParticleToggle *self);
int fn_801FCB38(cDummyProjectile *self);
char *fn_801FCB7C(cDummyProjectile *self);
unsigned int fn_801FCBC4(cDummyProjectile *self);
float fn_801FCC0C(cDummyProjectile *self);
float fn_801FCC54(cDummyProjectile *self);
float fn_801FCC9C(cDummyProjectile *self);
int fn_801FCCE4(cDummyProjectile *self);
unsigned int fn_801FCD90(cEffectSpawn *self);
char *fn_801FCDD8(cEffectSpawn *self);
int fn_801FCE20(cEffectSpawn *self);

cScript *fn_801FBD90(register cParticleToggle *self)
{
    return new cParticleToggle;
}

void fn_801FBDE4(register cParticleToggle *self) // slot 4
{
    Ref8 ev;

    fn_8046B6C8(&ev, fn_800797D4(self));
    if (fn_801FC924(self))
        self->cur = fn_801FC96C(self);
    if (fn_801FC894(self) == 0)
        fn_8046CC94(&ev);
    else if (stricmp(fn_801FCA54(self), "ffRoekel") == 0 || stricmp(fn_801FCA54(self), "ffRoekelGrn") == 0)
        fn_80082E90(&ev, fn_801FCA54(self), 0xff, 0xff);
    else if (fn_801FC8DC(self) != 0.0f)
        fn_8007D404(self, fn_801FC8DC(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    if (stricmp("", fn_801FCA54(self)) == 0)
        strncpy(self->effect, fn_80082CC8(&ev, 0), 0x20);
    else
        strncpy(self->effect, fn_801FCA54(self), 0x20);
}

void fn_801FBFB4(register cParticleToggle *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    Ref8 ev;

    fn_8046B6C8(&ev, fn_800797D4(self));
    if (fn_8046CC28(&ev) == 0 && fn_801FC9FC(self) == 0)
        return;
    switch (kind) {
    case 0:
    case 2:
        if (stricmp(fn_801FCA54(self), "ffRoekel") == 0 || stricmp(fn_801FCA54(self), "ffRoekelGrn") == 0) {
            if (fn_8046CD30(&ev)) {
                fn_80083428(&ev, 0);
                if (stricmp(fn_801FCA9C(self), "") != 0 && stricmp(fn_801FCA9C(self), "Invalid Param") != 0)
                    fn_80082E90(&ev, fn_801FCA9C(self), 0xff, 0xff);
            } else {
                fn_80082E90(&ev, fn_801FCA54(self), 0xff, 0xff);
            }
            return;
        }
        if (fn_801FC9FC(self)) {
            if (fn_8046CD30(&ev))
                fn_80083428(&ev, 0);
            else
                fn_80082E24(&ev, self->effect);
        } else {
            if (fn_8046CD30(&ev))
                fn_80083428(&ev, 0);
            else
                fn_800830A0(&ev, 0);
        }
        if (fn_801FC8DC(self) != 0.0f)
            fn_8007D404(self, fn_801FC8DC(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    case 17:
        if (self->cur == fn_801FC96C(self)) {
            self->cur = fn_801FC9B4(self);
            fn_8046CDB4(&ev, self->cur, -1.0f);
            break;
        } else if (self->cur == fn_801FC9B4(self)) {
            self->cur = fn_801FC96C(self);
            fn_8046CDB4(&ev, self->cur, -1.0f);
            break;
        }
    }
}

void fn_801FC320(register cParticleToggle *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10: {
        Ref8 ev;

        fn_8046B6C8(&ev, fn_800797D4(self));
        fn_8046CC94(&ev);
        break;
    }
    }
}

}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0.2f, 0.25f, 20.0f, "proj_flare", "redFlare", 1.0f, 0.3f, -0.5f

extern "C" {

void fn_801FC3B4(register cDummyProjectile *self) // slot 4
{
    Ref8 a;
    Ref8 b;

    fn_8007D404(self, fn_801FCC54(self) + fn_80171F8C() * 4.656612873077392578125e-10f * fn_801FCC9C(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    fn_8046B6C8(&a, fn_801FCB38(self));
    fn_80082440(&a, &self->from);
    fn_8046B6C8(&b, fn_801FCBC4(self));
    fn_80082440(&b, &self->to);
}

void fn_801FC4D8(register cDummyProjectile *self, unsigned char kind, float a, float b, float c, float d, int e) // slot 8
{
    switch (kind) {
    case 10:
        fn_80080C88(fn_801FCB7C(self), &self->from, &self->to, fn_801FCC0C(self), fn_800797D4(self));
        if (fn_801FCCE4(self) == 0)
            fn_8007D404(self, fn_801FCC54(self) + fn_80171F8C() * 4.656612873077392578125e-10f * fn_801FCC9C(self), 10, 0.0f, 0.0f, 0.0f, 0.0f, 0);
        break;
    }
}

void fn_801FC630(register cEffectSpawn *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (fn_801FCE20(self) != 1)
        return;
    switch (kind) {
    case 0: {
        Ref8 ev;

        fn_8046B6C8(&ev, fn_801FCD90(self));
        fn_80082E90(&ev, fn_801FCDD8(self), 0xff, 0xff);
        break;
    }
    }
}

void fn_801FC6F4(register cCrystalDetonate *self) // slot 3
{
    self->fired = 0;
}

void fn_801FC724(register cCrystalDetonate *self, int h) // slot 12
{
    fn_80133988(h);
}

void fn_801FC768(register cCrystalDetonate *self, int h, int value) // slot 13
{
    fn_801339C8(h);
}

void fn_801FC7B0(register cCrystalDetonate *self, int h, int other, int value) // slot 16
{
    Ref8 o;
    Ref8 t;
    Ref8 u;

    fn_8046B5A8(&o, other);
    if (fn_8046CBB8(&o) == 0)
        return;
    fn_8046CE70(&t, h);
    if (fn_80080C20(&t) == other)
        return;
    if (self->fired != 0)
        return;
    self->fired = 1;
    fn_8046CE70(&u, h);
    fn_80080BA8(&u)->fn_800B1FA8(100);
}

}

inline int sn_return_decl2(int a) { return a; }

extern "C" {

int fn_801FC894(register cParticleToggle *self)
{
    return fn_80079068(self, 0);
}

float fn_801FC8DC(register cParticleToggle *self)
{
    return fn_8007935C(self, 1);
}

int fn_801FC924(register cParticleToggle *self)
{
    return fn_80079068(self, 2);
}

float fn_801FC96C(register cParticleToggle *self)
{
    return fn_8007935C(self, 3);
}

float fn_801FC9B4(register cParticleToggle *self)
{
    return fn_8007935C(self, 4);
}

int fn_801FC9FC(register cParticleToggle *self)
{
    return fn_80079068(self, 5) != 0;
}

char *fn_801FCA54(register cParticleToggle *self)
{
    return fn_800794FC(self, 6);
}

char *fn_801FCA9C(register cParticleToggle *self)
{
    return fn_800794FC(self, 7);
}

cScript *fn_801FCAE4(register cDummyProjectile *self)
{
    return new cDummyProjectile;
}

int fn_801FCB38(register cDummyProjectile *self)
{
    return fn_800797D4(self);
}

char *fn_801FCB7C(register cDummyProjectile *self)
{
    return fn_800794FC(self, 0);
}

unsigned int fn_801FCBC4(register cDummyProjectile *self)
{
    return fn_800791C8(self, 1);
}

float fn_801FCC0C(register cDummyProjectile *self)
{
    return fn_8007935C(self, 2);
}

float fn_801FCC54(register cDummyProjectile *self)
{
    return fn_8007935C(self, 3);
}

float fn_801FCC9C(register cDummyProjectile *self)
{
    return fn_8007935C(self, 4);
}

int fn_801FCCE4(register cDummyProjectile *self)
{
    return fn_80079068(self, 5) != 0;
}

cScript *fn_801FCD3C(register cEffectSpawn *self)
{
    return new cEffectSpawn;
}

unsigned int fn_801FCD90(register cEffectSpawn *self)
{
    return fn_800791C8(self, 0);
}

char *fn_801FCDD8(register cEffectSpawn *self)
{
    return fn_800794FC(self, 1);
}

int fn_801FCE20(register cEffectSpawn *self)
{
    return fn_80079068(self, 2);
}

cScript *fn_801FCE68(register cCrystalDetonate *self)
{
    return new cCrystalDetonate;
}

}
