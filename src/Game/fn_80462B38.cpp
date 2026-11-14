// AI inline functions: AIAction and lbl_80569890 accessors, a Vector-array record, tagged values, the base task destructor, deferred task deletion, BitSet assignment, AIObject and +0x210 accessors.
// docs/ai.md row 5. Pool at 0x8049B054 (extern_pool), in another file's .rodata.

inline int sn_return_decl(int a) { return a; }

struct Vector
{
    float x, y, z, w;
};

extern "C" {
int fn_801B6A44(void *list);
int fn_801B5D3C(void *list, int i);
void *fn_800ACFA8(int id);
void __6Vector(Vector *v);
void *fn_8042E83C(void *p);
float *fn_8042FB28(void *p);
void fn_8042DC84(void *dst, void *src);
void *fn_80444984(void *p, int i);
int fn_80444688(void *p);
void *AI_GetMover(void *ai);
void *AI_GetEntity(void *ai);
int AI_IsMoverAboveTarget(void *p);
int fn_800861EC(void *p);
void AI_SetMoverMoveDest(void *p, void *v);
int fn_80442508(void *set, int bit);
}

// AIAction (Game/fn_80137F2C.cpp), 0x70 bytes
struct AIAction
{
    int i0; // +0x0
    char pad4[0x4];
    int i8; // +0x8
    char padC[0x20];
    int kind; // +0x2C
    Vector pos; // +0x30
    float f; // +0x40
    int i44; // +0x44
    int i48; // +0x48
    int i4C; // +0x4C
    int i50; // +0x50
    int i54; // +0x54
    int i58; // +0x58
    float f5C; // +0x5C
    int i60; // +0x60
};

extern "C" void fn_80462B38(register AIAction *self)
{
    self->i8 = 0;
    self->kind = -1;
    self->i60 = 0;
    self->i0 = -1;
    self->i58 = 2;
    self->f5C = 1.0f;
    self->i48 = 0;
    self->i4C = 0;
    self->i54 = 0;
    self->i50 = 0;
    self->i44 = 1;
}

extern "C" void fn_80462BB4(register AIAction *self, register int v)
{
    self->i58 = v;
}

extern "C" void fn_80462BDC(register AIAction *self, register float v)
{
    self->f5C = v;
}

extern "C" Vector *fn_80462C04(register AIAction *self)
{
    return &self->pos;
}

extern "C" void fn_80462C30(register AIAction *self, register int v)
{
    self->i48 = v;
}

extern "C" void fn_80462C58(register AIAction *self, register int v)
{
    self->i4C = v;
}

extern "C" void fn_80462C80(register AIAction *self, register int v)
{
    *(int *)((char *)self + 0x4) = v;
}

extern "C" void fn_80462CA8(register AIAction *self, register int v)
{
    self->i54 = v;
}

// lbl_80569890 (docs/ai.md row 10): count and entry of its lists at +0x28, +0x4C, +0x70, +0x94
extern "C" int fn_80462CD0(register char *self)
{
    return fn_801B6A44(self + 0x28);
}

extern "C" int fn_80462D18(register char *self, register int i)
{
    return fn_801B5D3C(self + 0x28, i);
}

extern "C" int fn_80462D68(register char *self)
{
    return fn_801B6A44(self + 0x4C);
}

extern "C" int fn_80462DB0(register char *self, register int i)
{
    return fn_801B5D3C(self + 0x4C, i);
}

extern "C" int fn_80462E00(register char *self)
{
    return fn_801B6A44(self + 0x70);
}

extern "C" int fn_80462E48(register char *self, register int i)
{
    return fn_801B5D3C(self + 0x70, i);
}

extern "C" int fn_80462E98(register char *self)
{
    return fn_801B6A44(self + 0x94);
}

extern "C" void *fn_80462EE0(register char *self, register int i)
{
    register void *p = fn_800ACFA8(fn_801B5D3C(self + 0x94, i));
    return p;
}

extern "C" void *fn_8046303C(register char *self);

extern "C" void *fn_80462F3C(register char *self)
{
    fn_8046303C(self);
    return self;
}

extern "C" void *fn_80462F7C(register char *self)
{
    fn_8046303C(self);
    return self;
}

extern "C" void *fn_80462FBC(register char *self)
{
    fn_8046303C(self);
    return self;
}

extern "C" void *fn_80462FFC(register char *self)
{
    fn_8046303C(self);
    return self;
}

// A Vector at +0x10 and three Vector[16] at +0x30, +0x130, +0x230
extern "C" void *fn_8046303C(register char *self)
{
    __6Vector((Vector *)(self + 0x10));
    {
        register Vector *base;
        register int i;
        register Vector *p;
        ({
            base = (Vector *)(self + 0x30);
            p = (Vector *)(self + 0x30);
        });
        i = 15;
        if (i != -1) {
            for (;;) {
                __6Vector(p);
                p++;
                i--;
                if (i == -1)
                    break;
            }
        }
    }
    {
        register Vector *base;
        register int i;
        register Vector *p;
        ({
            base = (Vector *)(self + 0x130);
            p = (Vector *)(self + 0x130);
        });
        i = 15;
        if (i != -1) {
            for (;;) {
                __6Vector(p);
                p++;
                i--;
                if (i == -1)
                    break;
            }
        }
    }
    {
        register Vector *base;
        register int i;
        register Vector *p;
        ({
            base = (Vector *)(self + 0x230);
            p = (Vector *)(self + 0x230);
        });
        i = 15;
        if (i != -1) {
            for (;;) {
                __6Vector(p);
                p++;
                i--;
                if (i == -1)
                    break;
            }
        }
    }
    *(int *)(self + 0x0) = 0;
    *(int *)(self + 0x20) = 0;
    return self;
}

extern "C" void *fn_8046315C(register char *self)
{
    if (*(void **)(self + 0x750)) {
        return fn_8042E83C(*(void **)(self + 0x750));
    } else {
        return 0;
    }
}

extern "C" float fn_804631B8(register char *self)
{
    return fn_8042FB28(self + 0x180)[2];
}

extern "C" int fn_80463204(register int *self)
{
    return self[0];
}

extern "C" int fn_80463230(register int *self)
{
    return self[0];
}

extern "C" int fn_8046325C(register int *self)
{
    return self[1];
}

// A tagged value: kind +0x0 (0, 1 or 2), then one or two words
struct Tagged
{
    int kind; // +0x0
    int a;    // +0x4
    int b;    // +0x8
};

extern "C" Tagged *fn_80463388(register Tagged *self);

extern "C" Tagged *fn_80463288(register Tagged *self, register int a, register int b)
{
    fn_80463388(self);
    self->kind = 0;
    self->a = a;
    self->b = b;
    return self;
}

extern "C" Tagged *fn_804632E0(register Tagged *self, register int a, register int b)
{
    fn_80463388(self);
    self->kind = 1;
    self->a = a;
    self->b = b;
    return self;
}

extern "C" Tagged *fn_80463338(register Tagged *self, register int a)
{
    fn_80463388(self);
    self->kind = 2;
    self->a = a;
    return self;
}

extern "C" Tagged *fn_80463388(register Tagged *self)
{
    return self;
}

// A header of 0x58 bytes or more: count +0x0, entries +0x4, flags +0x54, cursor +0x56
struct Slots
{
    unsigned int count; // +0x0
    void *items[20];    // +0x4
    unsigned short flags; // +0x54
    unsigned short cursor; // +0x56
    char pad58[0x4];
    void *ai; // +0x5C
    char pad60[0x20];
    Vector v80; // +0x80
    int i90; // +0x90
    char pad94[0x4];
    int i98; // +0x98
};

extern "C" int fn_804633B0(register Slots *self)
{
    return (unsigned short)(self->flags & 0x20);
}

extern "C" int fn_804633E4(register int *self)
{
    return self[1];
}

// AIObject+0x210 (docs/ai.md 4.1)
struct Sub210
{
    char pad[0xD0];
    int iD0; // +0xD0
    char padD4[0x1A4];
    float f278; // +0x278
    char pad27C[0x14];
    int i290; // +0x290
    int hasDest; // +0x294
    char pad298[0x8];
    Vector dest; // +0x2A0
    int i2B0; // +0x2B0
    char pad2B4[0x10];
    int i2C4; // +0x2C4
    char pad2C8[0x18];
    Vector v2E0; // +0x2E0
};

extern "C" void AI_SetMoverWaypoint(register Sub210 *self, register void *v)
{
    if (v == 0) {
        self->hasDest = 0;
    } else {
        fn_8042DC84(&self->dest, v);
        self->hasDest = 1;
    }
}

extern "C" void fn_80463470(register Sub210 *self, register int v)
{
    if (v != self->i2B0) {
        self->i2B0 = v;
    }
}

extern "C" void AI_SetMoverSpotKind(register Sub210 *self, register int v)
{
    self->iD0 = v;
}

extern "C" int fn_804634CC(register int *self)
{
    return self[0];
}

extern "C" char *fn_804634F8(register char *self)
{
    return self + 0xAC;
}

extern "C" int fn_80463524(register char *self)
{
    return *(int *)(self + 0x2C);
}

extern "C" int fn_80463550(register char *self)
{
    return (unsigned short)(*(unsigned short *)(self + 0x4) & 0x20);
}

extern "C" int fn_80463584(register char *self)
{
    return (unsigned short)(*(unsigned short *)(self + 0x44) & 0x1);
}

extern "C" int fn_804635B8(register char *self)
{
    return (unsigned short)(*(unsigned short *)(self + 0x44) & 0x2);
}

extern "C" int fn_804635EC(register void *self, register int i)
{
    return fn_80444688(fn_80444984(self, i));
}

extern "C" int fn_80463644(register Slots *self)
{
    return (unsigned short)(self->flags & 0x2);
}

extern "C" int fn_80463678(register Slots *self)
{
    return (unsigned short)(self->flags & 0x8000);
}

extern "C" int fn_804636AC(register Slots *self)
{
    return (unsigned short)(self->flags & 0x8);
}

extern "C" int fn_804636E0(register Slots *self)
{
    return (unsigned short)(self->flags & 0x80);
}

extern "C" void **fn_80463714(register Slots *self)
{
    return self->cursor < self->count ? &self->items[self->cursor] : 0;
}

extern "C" int fn_80463770(register Slots *self)
{
    return ++self->cursor < self->count;
}

extern "C" void fn_804637BC(register Slots *self, register void *v, register int a, register int b)
{
    fn_8042DC84(&self->v80, v);
    self->i90 = a;
    self->i98 = b;
    fn_80463470((Sub210 *)AI_GetMover(self->ai), self->i90);
    if (AI_IsMoverAboveTarget(AI_GetMover(self->ai)))
        return;
    AI_SetMoverWaypoint((Sub210 *)AI_GetMover(self->ai), v);
    if (fn_804633B0(self)) {
        if (!fn_800861EC(AI_GetEntity(self->ai))) {
            AI_SetMoverMoveDest(AI_GetMover(self->ai), &self->v80);
        }
    }
}

extern "C" void *fn_804638B4(register char *self)
{
    return fn_800ACFA8(*(int *)(self + 0xDC));
}

extern "C" void *fn_804638F8(register char *self)
{
    return fn_800ACFA8(*(int *)(self + 0xE0));
}

extern "C" float AI_GetMoverStuckTime(register Sub210 *self)
{
    return self->f278;
}

struct AIObject
{
    char pad[0x44];
    int i44[26]; // +0x44
    char padAC[0x45C];
    char set508[0x8]; // +0x508, bit set
    char pad510[0x10];
    int i520; // +0x520
    char pad524[0x14];
    int i538; // +0x538
};

extern "C" int fn_80463968(register AIObject *self)
{
    return self->i520;
}

extern "C" int fn_80463994(register AIObject *self, register int bit)
{
    return fn_80442508(self->set508, bit);
}

extern "C" void fn_804639E4(register AIObject *self, register int v)
{
    self->i538 = v;
}

extern "C" void fn_80463A0C(register AIObject *self, register int i)
{
    self->i44[i] = 1;
}

extern "C" {
void fn_80463AD4(register void *self);
void fn_80447EAC(void *set, int inChrg);
void __builtin_delete(void *p);
void fn_801ACFD4(void *p) __asm__("__builtin_vec_delete");
void *memcpy(void *dst, const void *src, unsigned int n);
void fn_80150FFC(void *brain, void *task);
extern char lbl_804F5CC8[]; // the base task vtable
extern unsigned int lbl_8066BF80; // tasks in lbl_80571DB0
extern void *lbl_80571DB0[16]; // tasks whose deletion is deferred
}

struct BitSet
{
    unsigned int *words; // +0x0
    unsigned int count;  // +0x4, in bits
};

extern "C" BitSet *fn_80463E14(register BitSet *self, register BitSet *src);

// The base task (docs/ai.md 4.4)
struct AITask
{
    AIObject *ai; // +0x0
    char pad4[0xC];
    BitSet state; // +0x10, the AI's state bits, saved and restored around the task
    char pad18[0x4];
    int i1C; // +0x1C
    char pad20[0x4];
    void *vtbl; // +0x24
};

extern "C" void Task_Base_Destroy(register AITask *self, register int inChrg)
{
    self->vtbl = lbl_804F5CC8;
    fn_80463AD4(self);
    fn_80447EAC(&self->state, 2);
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

extern "C" void fn_80463AB4(register void *self)
{
}

extern "C" void fn_80463AD4(register void *self)
{
}

extern "C" int AI_GetTaskDone(register AITask *self)
{
    return self->i1C;
}

extern "C" void AI_GetStateBits(register AIObject *self, register BitSet *dst);
extern "C" void AI_SetStateBits(register AIObject *self, register BitSet *src);

extern "C" void AI_SaveTaskStateBits(register AITask *self)
{
    AI_GetStateBits(self->ai, &self->state);
}

extern "C" void AI_RestoreTaskStateBits(register AITask *self)
{
    AI_SetStateBits(self->ai, &self->state);
}

extern "C" float fn_80463BA0(register AIAction *self)
{
    return self->f;
}

extern "C" int fn_80463BCC(register AIAction *self)
{
    return self->i58;
}

extern "C" float fn_80463BF8(register AIAction *self)
{
    return self->f5C;
}

// Deletes a task, or defers its deletion while there is room in lbl_80571DB0
extern "C" void AI_DeferTaskDelete(register void *brain, register void *task)
{
    if (lbl_8066BF80 > 15) {
        fn_80150FFC(brain, task);
    } else {
        lbl_80571DB0[lbl_8066BF80++] = task;
    }
}

extern "C" void AI_FlushTaskDeletes(register void *brain)
{
    for (unsigned int i = 0; i < lbl_8066BF80; i++) {
        fn_80150FFC(brain, lbl_80571DB0[i]);
        lbl_80571DB0[i] = 0;
    }
    lbl_8066BF80 = 0;
}

extern "C" void AI_SetStateBits(register AIObject *self, register BitSet *src)
{
    fn_80463E14((BitSet *)((char *)self + 0x500), src);
}

extern "C" void AI_GetStateBits(register AIObject *self, register BitSet *dst)
{
    fn_80463E14(dst, (BitSet *)((char *)self + 0x500));
}

extern "C" int Task_Base_Enter(register void *self)
{
    return 1;
}

extern "C" int Task_Base_Exit(register void *self)
{
    return 1;
}

// BitSet assignment
extern "C" BitSet *fn_80463E14(register BitSet *self, register BitSet *src)
{
    if (!self->words || !src->words || self->count != src->count) {
        if (self->words) {
            if (self->words) {
                fn_801ACFD4(self->words);
            } else {
            }
            self->words = 0;
        }
        self->words = new unsigned int[(src->count >> 5) + 1];
        self->count = src->count;
    }
    memcpy(self->words, src->words, (src->count >> 5) + 4);
    return self;
}

// AIObject+0xD0 (docs/ai.md 4.1)
struct Record
{
    char pad[0xE8];
    int iE8; // +0xE8
    int iEC; // +0xEC
};

extern "C" void fn_80463EF0(register Sub210 *self, register void *v)
{
    if (v) {
        fn_8042DC84(&self->v2E0, v);
    }
}

extern "C" void fn_80463F3C(register Sub210 *self, register int v)
{
    self->i2C4 = v;
}

extern "C" int fn_80463F64(register char *self)
{
    return *(int *)(self + 0x560);
}

extern "C" int fn_80463F90(register Record *self)
{
    return self->iE8;
}

extern "C" int fn_80463FBC(register Record *self)
{
    return self->iEC;
}

extern "C" int AI_GetMoverWaypointIndex(register Sub210 *self)
{
    return self->i290;
}
