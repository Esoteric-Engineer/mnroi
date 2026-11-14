// AI inline functions: lbl_80569890 and AIObject subobject constructors, a screen projection, a bit set,
// accessors on AIObject, its +0x210 subobject and its +0xD0 record.
// docs/ai.md row 5. Pools at 0x8049AA00 (extern_pool), in the behavior registry file's .rodata.

inline int sn_return_decl(int a) { return a; }

extern "C" {
void fn_801B5BA8(void *list, int capacity, float grow);
void fn_801B5C74(void *list, int flags);
void __builtin_delete(void *p);
void fn_801ACFD4(void *p) __asm__("__builtin_vec_delete");
void *memset(void *p, int c, unsigned int n);
void *fn_80430050(void *level);
void *fn_800ACFA8(int id);
int fn_800B0C58(void *p);
void *fn_800B14A0(void *p);
extern char lbl_8052F060[]; // the level object
extern int lbl_8066C710;
}

// lbl_80569890, the volume registry (docs/ai.md section 4.5): six lists of 0x24 bytes from +0x4
extern "C" void *fn_80461430(register char *self)
{
    fn_801B5BA8(self + 0x4, 4, 1.0f);
    fn_801B5BA8(self + 0x28, 4, 1.0f);
    fn_801B5BA8(self + 0x4C, 4, 1.0f);
    fn_801B5BA8(self + 0x70, 4, 1.0f);
    fn_801B5BA8(self + 0x94, 4, 1.0f);
    fn_801B5BA8(self + 0xB8, 4, 1.0f);
    return self;
}

__asm__(".text\n\t.globl _._7Volumes\n\t.type _._7Volumes,@function\n_._7Volumes:"); // ~Volumes, called by fn_80132480.cpp's static init
extern "C" void fn_804614F8(register char *self, register int inChrg)
{
    fn_801B5C74(self + 0xB8, 2);
    fn_801B5C74(self + 0x94, 2);
    fn_801B5C74(self + 0x70, 2);
    fn_801B5C74(self + 0x4C, 2);
    fn_801B5C74(self + 0x28, 2);
    fn_801B5C74(self + 0x4, 2);
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}
__asm__(".size _._7Volumes, 0xAC");

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x8049AA04-0x8049AA1C, linkonce pool entries

struct Camera
{
    char pad[0x2B8];
    float cx; // +0x2B8
    float cy; // +0x2BC
    float sx; // +0x2C0
    float sy; // +0x2C4
};

struct Vec4
{
    float x, y, z, w;
};

// Projects a view-space point to the screen: the camera's viewport, or a fixed 640x480 one
extern "C" void fn_804615A4(register Camera *cam, register Vec4 *v, register int useCam)
{
    float w = 1.0f / v->w;
    if (useCam) {
        v->x = v->x * cam->sx * w + cam->cx;
        v->y = -cam->sy * v->y * w + cam->cy;
        v->z = w;
    } else {
        v->x = v->x * 320.5f * w + 320.5f;
        v->y = v->y * -240.5f * w + 240.5f;
        v->z = w;
    }
}

struct Entry
{
    char pad[0x468];
    float f468;        // +0x468
    unsigned int u46C; // +0x46C
    char pad470[0x154];
    int i5C4; // +0x5C4
};

extern "C" float fn_80461690(register Entry *e)
{
    return e->f468;
}

extern "C" unsigned int fn_804616BC(register Entry *e)
{
    return e->u46C;
}

extern "C" int fn_804616E8(register Entry *e)
{
    return e->i5C4;
}

struct Record
{
    char data[0x1C0];
};

struct Level
{
    char pad[0x12C];
    Record *records; // +0x12C
};

struct RecordRef
{
    char pad[0x20];
    unsigned short id; // +0x20, 0xFFFF for none
};

// The record a reference names, in the given level or the current one
extern "C" Record *fn_80461714(register RecordRef *self, register Level *level)
{
    register Record *rec;
    if (self->id != 0xFFFF) {
        if (level) {
            rec = &level->records[self->id];
        } else {
            rec = &((Level *)fn_80430050(lbl_8052F060))->records[self->id];
        }
    } else {
        rec = 0;
    }
    return rec;
}

extern "C" void fn_804617CC(register int v)
{
    lbl_8066C710 = v;
}

struct BitSet
{
    unsigned int *words; // +0x0
    unsigned int count;  // +0x4, in bits
};

extern "C" void fn_804618B0(register BitSet *self);

extern "C" BitSet *fn_804617F0(register BitSet *self)
{
    self->words = 0;
    self->count = 0;
    return self;
}

extern "C" void fn_80461828(register BitSet *self, register unsigned int count)
{
    if (self->words) {
        if (self->words) {
            fn_801ACFD4(self->words);
        } else {
        }
    }
    self->count = count;
    self->words = new unsigned int[(self->count >> 5) + 1];
    fn_804618B0(self);
}

extern "C" void fn_804618B0(register BitSet *self)
{
    memset(self->words, 0, ((self->count >> 5) + 1) * sizeof(unsigned int));
}

extern "C" void *fn_80461904(register char *self)
{
    fn_804617F0((BitSet *)(self + 0xFC));
    return self;
}

struct Holder
{
    char pad[0xCC];
    int id;   // +0xCC
    int iD0; // +0xD0
    char padD4[0x4];
    int iD8; // +0xD8
    char padDC[0x14];
    int iF0; // +0xF0
};

extern "C" void *fn_80461948(register Holder *self)
{
    void *p = fn_800ACFA8(self->id);
    if (p && fn_800B0C58(p)) {
        return fn_800B14A0(p);
    } else {
        return 0;
    }
}

extern "C" int fn_804619C8(register int v)
{
    return v;
}

__asm__(".text\n\t.globl _._5AiObj\n\t.type _._5AiObj,@function\n_._5AiObj:"); // ~AiObj, likewise
extern "C" void fn_804619F0(register void *self, register int inChrg)
{
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}
__asm__(".size _._5AiObj, 0x4C");

extern "C" int fn_80461A3C(register Holder *self)
{
    return self->iD0;
}

class Vector
{
public:
    float x, y, z, w;
};

extern "C" {
void __6Vector(Vector *v);
void fn_8042DC84(Vector *dst, const Vector *src);
void fn_8044243C(BitSet *b, unsigned int bit);
void fn_804424A0(BitSet *b, unsigned int bit);
int fn_80442508(BitSet *b, unsigned int bit);
void fn_80447EAC(void *p, int flags);
int fn_801B6A44(void *list);
int fn_801B5D3C(void *list, int index);
void *fn_8046234C(register char *self);
int fn_804623BC(register char *self);
}

// AIObject+0x210: a +0x20 subobject (fn_8046234C), Vectors at +0xE0, +0xF0 [24], +0x280, +0x2A0, +0x2D0, +0x2E0
extern "C" void *fn_80461A68(register char *self)
{
    fn_8046234C(self + 0x20);
    __6Vector((Vector *)(self + 0xE0));
    register Vector *base;
    register int i;
    register Vector *p;
    // the array member's loop, as cc1plus writes it for a member Vector[24]
    ({
        base = (Vector *)(self + 0xF0);
        p = (Vector *)(self + 0xF0);
    });
    i = 23;
    if (i != -1) {
        for (;;) {
            __6Vector(p);
            p++;
            i--;
            if (i == -1)
                break;
        }
    }
    __6Vector((Vector *)(self + 0x280));
    __6Vector((Vector *)(self + 0x2A0));
    __6Vector((Vector *)(self + 0x2D0));
    __6Vector((Vector *)(self + 0x2E0));
    return self;
}

struct Sub210
{
    char pad[0xD0];
    int iD0; // +0xD0
    char padD4[0x1A8];
    int hasPoint; // +0x27C
    Vector point; // +0x280
    char pad290[0x4];
    int i294; // +0x294
    char pad298[0x8];
    Vector v2A0; // +0x2A0
    char pad2B0[0x8];
    int i2B8; // +0x2B8
    char pad2BC[0x4];
    int i2C0; // +0x2C0
    char pad2C4[0xC];
    Vector v2D0; // +0x2D0
};

extern "C" char *AI_GetMoverHeading(register char *self)
{
    return self + 0xE0;
}

extern "C" int AI_HasMoverPath(register char *self)
{
    return fn_804623BC(self + 0x20);
}

extern "C" int AI_HasMoverWaypoint(register Sub210 *self)
{
    return self->i294;
}

extern "C" int AI_HasMoverMoveDest(register Sub210 *self)
{
    return self->hasPoint;
}

extern "C" void AI_SetMoverMoveDest(register Sub210 *self, register const Vector *v)
{
    if (!v) {
        self->hasPoint = 0;
    } else {
        fn_8042DC84(&self->point, v);
        self->hasPoint = 1;
    }
}

struct Flagged
{
    char pad[0x8];
    int i8;      // +0x8
    BitSet bits; // +0xC
};

extern "C" int AI_HasMoverDestThing(register Flagged *self)
{
    return self->i8 != 0;
}

extern "C" int AI_GetMoverDestThing(register Flagged *self)
{
    return self->i8;
}

extern "C" void fn_80461CC0(register Flagged *self, register unsigned int bit)
{
    fn_8044243C(&self->bits, bit);
}

extern "C" void fn_80461D04(register Flagged *self, register unsigned int bit)
{
    fn_804424A0(&self->bits, bit);
}

extern "C" int fn_80461D48(register Flagged *self, register unsigned int bit)
{
    return fn_80442508(&self->bits, bit);
}

extern "C" void fn_80461D98(register Flagged *self)
{
    fn_804618B0(&self->bits);
}

struct AIObject
{
    char pad[0x500];
    BitSet state; // +0x500
    char pad508[0xC];
    int i514; // +0x514
    char pad518[0xC];
    int i524; // +0x524
    int i528; // +0x528
    char pad52C[0x8];
    int i534; // +0x534
    int i538; // +0x538
    char pad53C[0x24];
    int i560; // +0x560
    int i564; // +0x564
    int hasPoint; // +0x568
    char pad56C[0x4];
    Vector point; // +0x570
    Vector v580;  // +0x580
    char pad590[0x4];
    int i594;         // +0x594
    float weight[22]; // +0x598, AI weights (docs/ai.md 4.1)
};

extern "C" char *fn_80461DD4(register char *self)
{
    return self + 0x14;
}

extern "C" int fn_80461E00(register AIObject *self)
{
    return self->i514;
}

extern "C" char *fn_80461E2C(register char *self)
{
    return self + 0x540;
}

extern "C" void fn_80461E58(register AIObject *self, register const Vector *v)
{
    if (v) {
        fn_8042DC84(&self->point, v);
        self->hasPoint = 1;
    } else {
        self->hasPoint = 0;
    }
}

extern "C" int fn_80461EB8(register AIObject *self)
{
    return self->i534;
}

extern "C" float fn_80461EE4(register AIObject *self)
{
    return self->weight[1];
}

extern "C" float fn_80461F10(register AIObject *self)
{
    return self->weight[9];
}

extern "C" float fn_80461F3C(register AIObject *self)
{
    return self->weight[11];
}

extern "C" float fn_80461F68(register AIObject *self)
{
    return self->weight[12];
}

extern "C" float fn_80461F94(register AIObject *self)
{
    return self->weight[17];
}

extern "C" float fn_80461FC0(register AIObject *self)
{
    return self->weight[18];
}

struct Rec
{
    char pad[0x4];
    int i4;       // +0x4
    int i8;       // +0x8
    int arr[14];  // +0xC
    int i44;      // +0x44
    int i48;      // +0x48
    int i4C;      // +0x4C
    int i50;      // +0x50
    int i54;      // +0x54
    char pad58[0x8];
    int i60; // +0x60
};

extern "C" int fn_80461FEC(register Rec *self)
{
    return self->arr[0];
}

extern "C" void fn_80462018(register char *self, register int inChrg)
{
    fn_80447EAC(self + 0x1C, 2);
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

extern "C" int fn_80462074(register Rec *self)
{
    return self->i60;
}

extern "C" void fn_804620A0(register Rec *self, register int v)
{
    self->i60 = v;
}

extern "C" int fn_804620C8(register Rec *self)
{
    return self->i8;
}

extern "C" int fn_804620F4(register Rec *self, register int i)
{
    return self->arr[i];
}

extern "C" void fn_80462130(register Rec *self, register int v)
{
    self->i44 = v;
}

extern "C" int fn_80462158(register Rec *self)
{
    return self->i44;
}

extern "C" int fn_80462184(register Rec *self)
{
    return self->i48;
}

extern "C" int fn_804621B0(register Rec *self)
{
    return self->i4C;
}

extern "C" int fn_804621DC(register Rec *self)
{
    return self->i4;
}

extern "C" int fn_80462208(register Rec *self)
{
    return self->i54;
}

extern "C" int fn_80462234(register Rec *self)
{
    return self->i50;
}

extern "C" void fn_80462260(register Rec *self, register int v)
{
    self->i50 = v;
}

extern "C" int fn_80462288(register Rec *self)
{
    return self->arr[0];
}

extern "C" int fn_804622B4(register char *self)
{
    return fn_801B6A44(self + 0x4);
}

extern "C" int fn_804622FC(register char *self, register int index)
{
    return fn_801B5D3C(self + 0x4, index);
}

// Sub210+0x20; its base (fn_804623F0) is at +0x0
struct Sub230
{
    int i0;              // +0x0
    char pad4[0x40];
    unsigned short s44;  // +0x44
    char pad46[0x2];
    float f48;           // +0x48
    char pad4C[0x4];
    int i50;             // +0x50
    unsigned short flags; // +0x54
    char pad56[0x42];
    int i98; // +0x98
    char pad9C[0x4];
    int iA0; // +0xA0
};

extern "C" void *fn_804623F0(register Sub230 *self);

extern "C" void *fn_8046234C(register char *self)
{
    fn_804623F0((Sub230 *)self);
    __6Vector((Vector *)(self + 0x60));
    __6Vector((Vector *)(self + 0x80));
    ((Sub230 *)self)->flags = 0;
    ((Sub230 *)self)->iA0 = 0;
    ((Sub230 *)self)->i98 = 0;
    return self;
}

extern "C" int fn_804623BC(register char *self)
{
    return (unsigned short)(((Sub230 *)self)->flags & 1);
}

extern "C" void fn_80462430(register Sub230 *self);

extern "C" void *fn_804623F0(register Sub230 *self)
{
    fn_80462430(self);
    return self;
}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x8049AA2C-0x8049AA7C, linkonce pool entries

extern "C" void fn_80462430(register Sub230 *self)
{
    self->i0 = 0;
    self->s44 = 0;
    self->i50 = 0;
    self->f48 = 0.0f;
}

// A Vector at +0x30
extern "C" void *fn_80462474(register char *self)
{
    __6Vector((Vector *)(self + 0x30));
    return self;
}

inline void sn_label_decl() { clear:; } // the pair on fn_804624B8 (prodg.md)

struct Overlay
{
    char pad[0x8];
    int i8; // +0x8
};

extern "C" int fn_804624B8(register Overlay *self)
{
    return self->i8;
}

inline int sn_return_decl2(int a) { return a; }

extern "C" void *fn_804624EC(register Holder *self)
{
    return fn_800ACFA8(self->iF0);
}

extern "C" void *fn_80462530(register Holder *self)
{
    return fn_800ACFA8(self->iD8);
}

extern "C" Vector *AI_GetMoverLookAhead(register Sub210 *self)
{
    return &self->v2D0;
}

extern "C" int fn_804625A0(register Sub210 *self)
{
    return self->i2C0;
}

extern "C" Vector *AI_GetMoverWaypoint(register Sub210 *self)
{
    return &self->v2A0;
}

extern "C" Vector *AI_GetMoverMoveDest(register Sub210 *self)
{
    return &self->point;
}

extern "C" int AI_GetMoverSpotKind(register Sub210 *self)
{
    return self->iD0;
}

extern "C" int AI_IsMoverAboveTarget(register Sub210 *self)
{
    return self->i2B8;
}

struct AIEnt
{
    int i0;
};

struct AIEntSub : AIEnt
{
    int pad;
};

struct AIIds
{
    char pad[0x1C];
    int i1C; // +0x1C
    int i20; // +0x20
    int i24; // +0x24
};

extern "C" int fn_800ACFA8_i(int id) __asm__("fn_800ACFA8");
extern "C" int fn_800B0CC0(void *p);

extern "C" AIEnt *fn_8046267C(register AIIds *self)
{
    AIEnt *p = (AIEnt *)(AIEntSub *)fn_800ACFA8_i(self->i20);
    return (p && fn_800B0CC0(p)) ? p : 0;
}

extern "C" void *fn_804626F0(register AIIds *self)
{
    return fn_800ACFA8(self->i1C);
}

extern "C" AIEnt *fn_80462734(register AIIds *self)
{
    AIEnt *p = (AIEnt *)(AIEntSub *)fn_800ACFA8_i(self->i24);
    return p;
}

extern "C" BitSet *fn_80462780(register AIObject *self)
{
    return &self->state;
}

extern "C" void fn_804627AC(register AIObject *self, register int v)
{
    self->i524 = v;
}

extern "C" int fn_804627D4(register AIObject *self)
{
    return self->i524;
}

extern "C" void fn_80462800(register AIObject *self, register int v)
{
    self->i528 = v;
}

extern "C" int fn_80462828(register AIObject *self)
{
    return self->i528;
}

extern "C" Vector *fn_80462854(register AIObject *self)
{
    return &self->v580;
}

extern "C" int fn_80462880(register AIObject *self)
{
    return self->i538;
}

extern "C" int fn_804628AC(register AIObject *self)
{
    return self->i564;
}

extern "C" void fn_804628D8(register AIObject *self, register int v)
{
    self->i560 = v;
}

extern "C" void fn_80462900(register AIObject *self, register int v)
{
    self->i594 = v;
}

extern "C" int fn_80462928(register AIObject *self)
{
    return self->i594;
}

extern "C" float fn_80462954(register AIObject *self)
{
    return self->weight[2];
}

extern "C" float fn_80462980(register AIObject *self)
{
    return self->weight[3];
}

extern "C" float fn_804629AC(register AIObject *self)
{
    return self->weight[4];
}

extern "C" float fn_804629D8(register AIObject *self)
{
    return self->weight[5];
}

extern "C" float fn_80462A04(register AIObject *self)
{
    return self->weight[7];
}

extern "C" float fn_80462A30(register AIObject *self)
{
    return self->weight[8];
}

extern "C" float fn_80462A5C(register AIObject *self)
{
    return self->weight[13];
}

extern "C" float fn_80462A88(register AIObject *self)
{
    return self->weight[14];
}

extern "C" float fn_80462AB4(register AIObject *self)
{
    return self->weight[19];
}

extern "C" float fn_80462AE0(register AIObject *self)
{
    return self->weight[20];
}

extern "C" float fn_80462B0C(register AIObject *self)
{
    return self->weight[21];
}
