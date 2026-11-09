// Attack volumes (7 of 0x80 bytes at ctrl+0x580): setup picks the two attachment (kind, index) pairs a volume spans by its number 1-7. docs/characters.md section 4.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
    Vector(float a, float b, float c, float d) __asm__("fn_8042D768");
} __attribute__((aligned(8)));

class Volume
{
public:
    void *owner;     // +0x00
    unsigned int number; // +0x04, 1-7
    unsigned int started; // +0x08, time of the last test; 0 until the first
    int padC;
    Vector lastFrom; // +0x10
    Vector lastTo;   // +0x20
    int hits[12];    // +0x30, targets already hit this activation
    unsigned short hitCount; // +0x60
    float cooldown;  // +0x64, until the next world hit
    unsigned short flags; // +0x68, 1 on
    unsigned char worldHits; // +0x6A
    int fromKind;    // +0x6C
    int toKind;      // +0x70
    int fromIndex;   // +0x74
    int toIndex;     // +0x78
    void Setup(void *a, int b);
};

__asm__(".text\n\t.globl fn_800F43D4\n\t.type fn_800F43D4,@function\nfn_800F43D4:");
void Volume::Setup(void *a, int b)
{
    owner = a;
    number = b;
    switch (number) {
    case 1:
        fromKind = 3;
        fromIndex = 1;
        toKind = 5;
        toIndex = 1;
        break;
    case 2:
        fromKind = 3;
        fromIndex = 2;
        toKind = 5;
        toIndex = 2;
        break;
    case 3:
        fromKind = 0x15;
        fromIndex = 2;
        toKind = 0x17;
        toIndex = 2;
        break;
    case 4:
        fromKind = 0x15;
        fromIndex = 1;
        toKind = 0x17;
        toIndex = 1;
        break;
    case 5:
        fromKind = 0x28;
        fromIndex = 1;
        toKind = 0x2A;
        toIndex = 1;
        break;
    case 6:
        fromKind = 0x28;
        fromIndex = 2;
        toKind = 0x2A;
        toIndex = 2;
        break;
    case 7:
        fromKind = 0x2B;
        fromIndex = 0;
        toKind = 0x2C;
        toIndex = 0;
        break;
    default:
        break;
    }
}
__asm__(".size fn_800F43D4, 0x18C");

struct Slot {
    char d[0x30];
};

struct Query {
    char pad0[0x40];
    Slot slot[0x80];    // +0x40
    unsigned int count; // +0x1840
    char pad1844[0xC];
};

class Placement
{
public:
    Vector d[4];
    Placement();
};

class Segment
{
public:
    Vector d[4];
    Segment() __asm__("fn_80446A74");
};

class ObjEx
{
public:
    char d[0xD0];
    ObjEx();
} __attribute__((aligned(8)));

class Body
{
public:
    char d[0x10];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void Sweep(ObjEx *o, int mask, int z); // vtable +0x20
};

class Surface
{
public:
    virtual void s0();
    virtual void s1();
    virtual int Kind(); // vtable +0x18
};

extern "C" {
extern int lbl_8066BA84;
extern char lbl_80552110[];
extern char lbl_80593BE8[];

void *Entity_GetActor(void *self);
int fn_800CE554(void *self);
float fn_800CE584(void *self);
int fn_800CDA20(void *self);
void *fn_800CD9B0(void *self);
void *fn_800B1478(void *a);
int fn_800A4130(void *a);
void *fn_8009AD80(void *a);
unsigned char fn_8009AB64(void *a);
int fn_801A5104(void *model, unsigned char kind, unsigned short index, Vector *out, void *world);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float fn_8042EC54(Vector *v);
void fn_80429090(Vector *out, Vector *a, Vector *b, float s);
void fn_8004E9C8(Query *q);
void fn_80434C88(Query *q);
void fn_80434CDC(Query *q, int bit);
void fn_80434D18(Query *q, void *ignore);
void fn_80434CB0(Query *q);
void *fn_800B1CC8(void *a);
int fn_8004DCA0(void *a, Vector *b);
void fn_8004E4B4(Query *q, Vector *pos, float r, void *world);
void *fn_80434C2C(Slot *s);
int fn_800B13D8(void *a);
void fn_800E7A4C(void *self, void *a, Vector *b, Vector *c, int d, unsigned char e, int f, int g, int h, int i);
void fn_8042DC84(Vector *dst, Vector *src);
unsigned int fn_8042EFF8(void *g);
int fn_80095BC4(void *g);
void fn_80438928(Segment *s, Vector *a, Vector *b, float f);
void fn_80447670(Segment *s, Vector *a, Vector *b);
void fn_80447504(ObjEx *o, Segment *s);
int fn_804373A4(ObjEx *o);
Placement *fn_804374E8(ObjEx *o);
Body *fn_800690DC(void *a);
void *fn_800B24AC(void *a);
void fn_80437B60(void *body, ObjEx *o, int z);
int fn_800B0F0C(void *a);
void *fn_800B1568(void *a);
int fn_8009ABC0(void *a);
int fn_800B0C58(void *a);
void *fn_800B14A0(void *a);
void *fn_80085928(void *a);
int fn_800CCC28(void *a);
float fn_800B2670(void *a);
Vector *fn_800B1724(void *a);
void fn_8042D854(Vector *a, Vector *b);
Vector *fn_804471A8(void *p);
Vector *fn_80437168(void *p);
int fn_80437194(void *p);
int fn_80447724(Volume *v);
void fn_8042F76C(Vector *v);
float fn_80426A84(void *g);
void fn_800B16D8(void *a, Vector *out);
int fn_8004A758(Vector *a, Vector *b, float r, int c, Placement *p, void *d, int e, int f, int g);
void *fn_80048A74(Placement *p);
Surface *fn_804471D4(Placement *p);
void *fn_80434ED0(Surface *s);
int *fn_80434E7C(Placement *p);
void fn_8008A624(void *a, int b, unsigned short *out);
void fn_800A2F94(void *a, void *b, int c, int d, float e, Vector *f, Vector *g, float h, int i);
int fn_800B1078(void *a);
void *fn_800B1590(void *a);
void fn_800F880C(void *a, void *b, int c, int d);

int fn_800F4560(register Volume *self, int target)
{
    unsigned int i;
    for (i = 0; i < self->hitCount; i++) {
        if (self->hits[i] == target)
            return 1;
    }
    return 0;
}

int fn_800F45EC(register Volume *self, int target)
{
    if (self->hitCount > 0xB)
        return 0;
    self->hits[self->hitCount++] = target;
    return 1;
}

void fn_800F4664(register Volume *self, Vector *from, Vector *to)
{
    fn_8042DC84(&self->lastFrom, from);
    fn_8042DC84(&self->lastTo, to);
    self->started = fn_8042EFF8(lbl_80593BE8);
}

int fn_800F46D8(register Volume *self)
{
    void *actor = Entity_GetActor(self->owner);
    Vector from;
    Vector to;
    unsigned char tier = fn_800CE554(self->owner);
    if (fn_800CDA20(self->owner) && fn_800A4130(fn_800B1478(fn_800CD9B0(self->owner)))) {
        void *held = fn_800B1478(fn_800CD9B0(self->owner));
        if (!fn_801A5104(fn_8009AD80(held), self->fromKind, fn_8009AB64(held), &from, 0))
            return 0;
        if (!fn_801A5104(fn_8009AD80(held), self->toKind, fn_8009AB64(held), &to, 0))
            return 0;
    } else {
        if (!fn_801A5104(fn_8009AD80(actor), self->fromKind, self->fromIndex, &from, 0))
            return 0;
        if (!fn_801A5104(fn_8009AD80(actor), self->toKind, self->toIndex, &to, 0))
            return 0;
    }
    Vector dir;
    fn_80429038(&dir, &to, &from);
    float len = fn_8042EC54(&dir);
    Vector mid;
    fn_80429090(&mid, &from, &dir, len * 0.5f);
    Query q;
    fn_8004E9C8(&q);
    fn_80434C88(&q);
    fn_80434CDC(&q, 0);
    fn_80434CDC(&q, 7);
    fn_80434CDC(&q, 8);
    fn_80434CDC(&q, 2);
    fn_80434D18(&q, actor);
    fn_80434CB0(&q);
    int world = fn_8004DCA0(fn_800B1CC8(actor), &mid);
    if (!world)
        return 0;
    fn_8004E4B4(&q, &mid, 2.0f * len, fn_800B1CC8(actor));
    int hit = 0;
    if (q.count) {
        unsigned int i;
        for (i = 0; i < q.count; i++) {
            void *target = fn_80434C2C(&q.slot[i]);
            if (!target)
                continue;
            if (fn_800F4560(self, fn_800B13D8(target)))
                continue;
            fn_800E7A4C(self->owner, target, &mid, &dir, tier, 0, 1, self->fromKind, self->fromIndex, 0);
            fn_800F45EC(self, fn_800B13D8(target));
            hit = 1;
            continue;
        }
    }
    return hit;
}

int fn_800F4B58(register Volume *self)
{
    void *actor = Entity_GetActor(self->owner);
    void *held = 0;
    int tier = fn_800CE554(self->owner);
    if (tier > 4)
        tier = 0;
    Vector from;
    Vector to;
    if (fn_800CDA20(self->owner) && fn_800CD9B0(self->owner) && fn_800A4130(fn_800B1478(fn_800CD9B0(self->owner)))) {
        held = fn_800B1478(fn_800CD9B0(self->owner));
        if (!fn_801A5104(fn_8009AD80(held), self->fromKind, fn_8009AB64(held), &from, 0))
            return 0;
        if (!fn_801A5104(fn_8009AD80(held), self->toKind, fn_8009AB64(held), &to, 0))
            return 0;
    } else {
        if (!fn_801A5104(fn_8009AD80(actor), self->fromKind, self->fromIndex, &from, 0))
            return 0;
        if (!fn_801A5104(fn_8009AD80(actor), self->toKind, self->toIndex, &to, 0))
            return 0;
    }
    Vector dir;
    fn_80429038(&dir, &to, &from);
    float len = fn_8042EC54(&dir);
    Vector mid;
    fn_80429090(&mid, &from, &dir, len * 0.5f);
    Query q;
    fn_8004E9C8(&q);
    fn_80434C88(&q);
    fn_80434CDC(&q, 0);
    fn_80434CDC(&q, 7);
    fn_80434CDC(&q, 8);
    fn_80434CDC(&q, 2);
    fn_80434D18(&q, actor);
    fn_80434CB0(&q);
    int world = fn_8004DCA0(fn_800B1CC8(actor), &mid);
    if (!world)
        return 0;
    fn_8004E4B4(&q, &mid, len, fn_800B1CC8(actor));
    int hit = 0;
    Placement best;
    if (q.count || fn_80095BC4(lbl_80552110)) {
        Body *body = 0;
        Segment seg;
        ObjEx res;
        Vector a;
        Vector b;
        Vector c;
        float t;
        unsigned int count = q.count;
        if (!count && fn_80095BC4(lbl_80552110))
            count = 1;
        unsigned int i;
        for (i = 0; i < count; i++) {
            void *target = 0;
            if (q.count) {
                target = fn_80434C2C(&q.slot[i]);
                if (!target)
                    continue;
            }
            if (target) {
                if (fn_800F4560(self, fn_800B13D8(target)))
                    continue;
                body = fn_800690DC(target);
                if (!body && !fn_800B24AC(target))
                    continue;
            }
            fn_80438928(&seg, &from, &dir, len);
            fn_80447504(&res, &seg);
            if (fn_804373A4(&res)) {
            } else {
            }
            if (body && !lbl_8066BA84) {
                body->Sweep(&res, 0x100000, 0);
            } else if (target) {
                fn_80437B60(fn_800B24AC(target), &res, 0);
            }
            if (target && fn_804373A4(&res)) {
                int data = 0;
                if (fn_800B0F0C(target))
                    data = fn_8009ABC0(fn_800B1568(target));
                if (fn_800B0C58(target) && fn_800CCC28(fn_80085928(fn_800B14A0(target)))) {
                    Vector normal(0.0f, 0.0f, 1.0f, 1.0f);
                    Vector offset(0.0f, 0.0f, fn_800B2670(target), 1.0f);
                    Vector pos;
                    fn_8042DC84(&pos, fn_800B1724(target));
                    fn_8042D854(&pos, &offset);
                    fn_800E7A4C(self->owner, target, &pos, &normal, tier, 0, 1, self->fromKind, self->fromIndex, data);
                } else {
                    fn_800E7A4C(self->owner, target, fn_804471A8(fn_804374E8(&res)), fn_80437168(fn_804374E8(&res)), tier, 0, 1, self->fromKind, self->fromIndex, data);
                }
                fn_800F45EC(self, fn_800B13D8(target));
                hit = 1;
                best = *fn_804374E8(&res);
                continue;
            }
            if (!fn_80447724(self)) {
                fn_80429038(&c, &self->lastTo, &self->lastFrom);
                fn_8042F76C(&c);
                for (t = len; t > 0.0f; t -= 0.3f) {
                    fn_80429090(&a, &self->lastFrom, &c, t);
                    fn_80429090(&b, &from, &dir, t);
                    fn_80447670(&seg, &a, &b);
                    fn_80447504(&res, &seg);
                    if (body && !lbl_8066BA84) {
                        body->Sweep(&res, 0x100000, 0);
                    } else if (target) {
                        fn_80437B60(fn_800B24AC(target), &res, 0);
                    }
                    if (fn_804373A4(&res)) {
                    } else {
                    }
                    if (target && fn_804373A4(&res)) {
                        int data = 0;
                        if (fn_800B0F0C(target))
                            data = fn_8009ABC0(fn_800B1568(target));
                        if (fn_800B0C58(target) && fn_800CCC28(fn_80085928(fn_800B14A0(target)))) {
                            Vector normal(0.0f, 0.0f, 1.0f, 1.0f);
                            Vector offset(0.0f, 0.0f, fn_800B2670(target), 1.0f);
                            Vector pos;
                            fn_8042DC84(&pos, fn_800B1724(target));
                            fn_8042D854(&pos, &offset);
                            fn_800E7A4C(self->owner, target, &pos, &normal, tier, 0, fn_80437194(fn_804374E8(&res)), self->fromKind, self->fromIndex, data);
                        } else {
                            fn_800E7A4C(self->owner, target, fn_804471A8(fn_804374E8(&res)), fn_80437168(fn_804374E8(&res)), tier, 0, fn_80437194(fn_804374E8(&res)), self->fromKind, self->fromIndex, data);
                        }
                        fn_800F45EC(self, fn_800B13D8(target));
                        hit = 1;
                        best = *fn_804374E8(&res);
                        break;
                    }
                }
            }
        }
    }
    if (self->cooldown > 0.0f) {
        self->cooldown = self->cooldown - fn_80426A84(lbl_80593BE8);
    } else if (!hit && self->cooldown <= 0.0f) {
        Placement p;
        Vector unused0;
        Vector unused1;
        Vector start;
        fn_800B16D8(actor, &start);
        start.z = mid.z;
        Vector ray;
        fn_80429038(&ray, &mid, &start);
        ray.z = 0.0f;
        float r = fn_8042EC54(&ray) + 0.2f;
        int found = fn_8004A758(&start, &ray, r, 1, &p, fn_800B24AC(actor), 0, 0, 10);
        if (found) {
            void *target = fn_80048A74(&p);
            unsigned short value = 0;
            if (fn_804471D4(&p)->Kind() == 0x18) {
                fn_8008A624(fn_80434ED0(fn_804471D4(&p)), *fn_80434E7C(&p), &value);
            } else {
                value = 0;
            }
            fn_800E7A4C(self->owner, target, fn_804471A8(&p), fn_80437168(&p), tier, self->worldHits, 1, self->fromKind, self->fromIndex, value);
            hit = 1;
            best = p;
            self->cooldown = 0.05f;
            self->worldHits++;
        }
    }
    if (hit && held) {
        fn_800A2F94(held, actor, 7, tier, fn_800CE584(self->owner), fn_804471A8(&best), fn_80437168(&best), 0.0f, 0);
        if (fn_800B1078(held))
            fn_800F880C(self->owner, fn_800B1590(held), 1, 0);
    }
    fn_800F4664(self, &from, &to);
    return hit;
}
}
