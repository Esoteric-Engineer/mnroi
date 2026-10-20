// The entity event dispatcher: passes an event from the target's controller (fn_800E1788, or its virtual handler), then handles the effect, sound, hit and weapon events itself.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct State {
    char pad[0x75C];
};

struct Ent {
    char pad0[0x30];
    unsigned int f30;
};

struct ActBase : Ent {
    char d[0x198 - 0x34];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20();
    virtual int s21(); // +0xB0
};

struct Act : ActBase {
    char pad19C[0x3DC - 0x19C];
    int f3DC;
};

struct Handle {
    char d[0xC8];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); // +0x1B8
    virtual void s55();
    virtual void s56(); // +0x1C8
};

struct Src {
    char pad0[0x2C];
    char f2C[0x214 - 0x2C];
    int f214; // handle of the entity
    char pad218[0x220 - 0x218];
    unsigned int f220;
};

struct EObj {
    char pad0[0x3AC];
};

struct EBase : EObj {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(Src *from, int type, unsigned int value, int extra); // +0x20
    virtual void s4();
    virtual void s5(int state); // +0x30
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void *s22(); // +0xB8
};

struct Obj : EBase {
    int pad;
};

struct Mgr {
    char pad0[0x78];
    int f78;
    char pad7C[0x88 - 0x7C];
    void *f88;
};

extern State lbl_80552110; // the game-state object G
extern int lbl_8066F05C;

extern "C" {
Ent *fn_800ACFA8(int handle);
int fn_800B0C1C(void *e);
Act *fn_800B14C8(void *e);
Obj *fn_80085954(void *p);
int fn_800CD7D4(void *c);
int fn_800E1788(void *c, Src *from, int type, unsigned int value, int extra);
int fn_800B0DDC(void *e);
void *fn_800B1540(void *e);
void fn_800A3488(void *p, Src *from, int type, unsigned int value);
int fn_800B0C58(void *e);
int fn_8043B1CC(void *p);
void *fn_800B1568(void *e);
void fn_8003E3AC(void *p, Src *to, Src *from, int type, float f, unsigned int value, int extra);
void fn_8003372C(void *e, int v);
int fn_800B0F0C(void *e);
void fn_8010E304(void *e, int v);
void *fn_80085928(void *e);
int fn_800CC96C(void *p);
unsigned int fn_80086EDC(void *e);
void fn_801118A4(int id, void *e, int *a, int *b, int *c);
void fn_8010CDCC(void *p, int id, void *e, int a, int b, int c, int d);
int fn_800B0DA0(void *e);
void *fn_800B14F0(void *e);
int fn_800A0E64(void *p);
void fn_8009F010(void *p, int v);
int fn_8005A534(unsigned int v);
int fn_800ACD20(Ent &e, int id);
Handle *fn_80393D0C(Ent &e, int id, int a, int b);
Handle *fn_80393A60(Ent &e, int id, int a);
int fn_800B1858(void *e);
Ent *fn_800C9FD0(void *c);
Mgr *fn_800531AC();
int fn_80426AB0(State *g);
int fn_8008582C(void *e);
const Ent *fn_80432924(State *g);
void fn_800CD364(EObj &c, int v);
void fn_8007F7A0(void *e, int v, float f);
void fn_8007F8C8(void *p, void *e, float f, unsigned int value, int extra);
Vector *fn_800B1724(Ent &e);
void fn_80429038(Vector *out, Vector *a, Vector *b);
void fn_8042F76C(Vector *v);
void fn_80429090(Vector *out, Vector *a, Vector *b, float s);
float fn_804290F8(Vector *a, Vector *b);
int fn_800B24AC(Ent &e);
int fn_80048EBC(void *a, Vector *v, int b, int c, int d, float f, int e);
void fn_800C7FF4(EObj &c, Vector *v, float f);
void fn_8005A828(Ent &e, Vector *p);
void fn_8042DC84(Vector *dst, Vector *src);
void *fn_800B14A0(void *e);
int fn_800CD0EC(EObj &c);
void fn_80030930(void *a, int b, int c, int d, float f1, int e, int f, int g, int h, float f2);
void *fn_80085AF0(void *e);
int fn_8043B2C8(void *p);
int fn_8043B31C(void *p);
void fn_801AA414(unsigned short id, float a, float b, int extra, int z);
void *fn_8043289C(State *g);
void fn_8003DBF0(void *p, int extra, float f, int z);
void fn_80086410(void *e);
void fn_8008643C(void *e);
void *fn_8009AD80(void *e);
void fn_8043B244(void *p, unsigned char v);
void fn_8043B284(void *p, unsigned char v);
}

extern "C" void fn_80058C94(Src *from, Src *to, int type, float f, unsigned int value, int extra)
{
    Ent *f20;
    Ent *f24 = 0;
    int f28;
    f20 = fn_800ACFA8(to->f214);
    if (!f20)
        return;
    if (fn_800B0C1C(f20) && fn_800B14C8(f20)->f3DC) {
        Obj *f2C = fn_80085954(fn_800B14C8(f20));
        if (fn_800CD7D4(f2C))
            fn_800E1788(f2C, from, type, value, extra);
        else
            f2C->s3(from, type, value, extra);
    }
    if (fn_800B0DDC(f20))
        fn_800A3488(fn_800B1540(f20), from, type, value);
    if (fn_800B0C58(f20))
        f24 = f20;
    if (from == to && fn_8043B1CC(to->f2C)) {
        switch (type) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 7:
        case 9:
        case 0xB:
        case 0xC:
        case 0x13:
        case 0x17:
            return;
        default:
            break;
        }
    }
    switch (type) {
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
    case 0x6E:
    case 0x6F:
    case 0x70:
    case 0x71:
        fn_8003E3AC(fn_800B1568(f20), from, to, type, f, value, extra);
        break;
    case 0x29:
    case 0x2A:
        if (!f24)
            break;
        if (type == 0x2A)
            fn_8003372C(f24, 0x22);
        else
            fn_8003372C(f24, 0x21);
        break;
    case 0:
    case 1:
    case 0x35:
    case 0x36:
        if (!f24)
            break;
        if (type != 0x35 && type != 0x36) {
            if (type == 1)
                fn_8003372C(f24, 6);
            else
                fn_8003372C(f24, 5);
        }
        break;
    case 2:
    case 3:
    case 0x37:
    case 0x38:
        if (!f24)
            break;
        if (type != 0x37 && type != 0x38) {
            if (type == 2)
                fn_8003372C(f24, 9);
            else
                fn_8003372C(f24, 0xA);
        }
        break;
    case 7:
        if (f24)
            fn_8003372C(f24, 0x10);
        break;
    case 0x17:
        if (fn_800B0F0C(f20)) {
            int f2C = value;
            if (f2C == 0x10) {
                if (f24)
                    fn_8010E304(f24, 1);
                break;
            }
            f28 = 0xE;
            if (f24) {
                if (fn_800CC96C(fn_80085928(f24)))
                    f28 = lbl_8066F05C;
                else
                    f28 = fn_80086EDC(f24);
            }
            int f30 = 0x1F4;
            int f34 = extra;
            fn_801118A4(f2C, f20, &f28, &f30, &f34);
            fn_8010CDCC(fn_800B1568(f20), f2C, f20, f28, f30, f34, 0);
        }
        break;
    case 5:
        if (fn_800B0DA0(f20) && fn_800A0E64(fn_800B14F0(f20)))
            fn_8009F010(fn_800B14F0(f20), 0);
        break;
    case 0x66:
        if (value)
            to->f220 &= ~4;
        else
            to->f220 |= 4;
        break;
    case 0x48: {
        Handle *f34 = fn_80393D0C(*f20, fn_800ACD20(*f20, fn_8005A534(value)), 0xFF, 0xFF);
        if (f34)
            f34->s56();
        break;
    }
    case 0x49: {
        Handle *f34 = fn_80393A60(*f20, fn_800ACD20(*f20, fn_8005A534(value)), 0);
        if (f34)
            f34->s54();
        break;
    }
    case 0x5D:
    case 0x5E: {
        if (!fn_800B0C1C(f20) || !fn_80085954(fn_800B14C8(f20)) || !fn_800B1858(f20))
            break;
        Handle *f34;
        Ent *f30 = fn_800C9FD0(fn_80085954(fn_800B14C8(f20)));
        if (!f30) {
            Mgr *f2C = fn_800531AC();
            if (fn_80426AB0(&lbl_80552110) && fn_8008582C(fn_800B14C8(f20)) && f2C && f2C->f78)
                f30 = (Ent *)fn_80432924(&lbl_80552110);
        }
        if (!f30)
            break;
        if (type == 0x5D) {
            f34 = fn_80393D0C(*f30, fn_800ACD20(*f20, fn_8005A534(value)), 0xFF, 0xFF);
            if (f34)
                f34->s56();
        } else {
            f34 = fn_80393A60(*f30, fn_800ACD20(*f20, fn_8005A534(value)), 0);
            if (f34)
                f34->s54();
        }
        break;
    }
    case 0x61:
    case 0x62: {
        if (!fn_800B0C1C(f20) || !fn_80085954(fn_800B14C8(f20)) || !fn_800B1858(f20))
            break;
        Handle *f34;
        Ent *f30 = fn_800C9FD0(fn_80085954(fn_800B14C8(f20)));
        if (!f30 || !fn_800B1858(f30))
            break;
        if (type == 0x61) {
            f34 = fn_80393D0C(*f20, fn_800ACD20(*f30, fn_8005A534(value)), 0xFF, 0xFF);
            if (f34)
                f34->s56();
        } else {
            f34 = fn_80393A60(*f20, fn_800ACD20(*f30, fn_8005A534(value)), 0);
            if (f34)
                f34->s54();
        }
        break;
    }
    case 0x54:
        if (fn_800B0C1C(f20) && fn_80085954(fn_800B14C8(f20)))
            fn_800CD364(*fn_80085954(fn_800B14C8(f20)), 1);
        break;
    case 0xD:
    case 0xE:
    case 0xF: {
        fn_8007F7A0(f20, type - 0xD, f);
        Mgr *f34 = fn_800531AC();
        if (f34 && f34->f78 && f34->f88)
            fn_8007F8C8(f34->f88, f20, f, value, extra);
        break;
    }
    case 0x10:
        break;
    case 0x14:
        break;
    case 0x52:
        if (value)
            f20->f30 &= ~2;
        else
            f20->f30 |= 2;
        break;
    case 0x5B: {
        Vector v38;
        Vector v48;
        if (!fn_800B0C1C(f20) || !fn_80085954(fn_800B14C8(f20)))
            break;
        Ent *f34 = fn_800C9FD0(fn_80085954(fn_800B14C8(f20)));
        if (!f34)
            break;
        if (!fn_800B0C58(f34))
            break;
        fn_80429038(&v38, fn_800B1724(*f34), fn_800B1724(*f20));
        v38.z = 0.0f;
        fn_8042F76C(&v38);
        fn_80429090(&v48, fn_800B1724(*f34), &v38, -((float)value * 0.01f));
        v48.z += (float)extra * 0.01f;
        if (fn_804290F8(&v48, fn_800B1724(*f20)) > 3.0f)
            break;
        Vector v58;
        fn_80429090(&v58, fn_800B1724(*f34), &v38, -((float)value * 0.005f));
        v58.z += (float)extra * 0.005f;
        if (fn_80048EBC(fn_80085954(fn_800B14C8(f20))->s22(), &v58, 0, fn_800B24AC(*f34), fn_800B14C8(f20)->s21(), -0.11f, 0))
            break;
        if (fn_80048EBC(fn_80085954(fn_800B14C8(f20))->s22(), &v48, 0, fn_800B24AC(*f34), fn_800B14C8(f20)->s21(), -0.11f, 0))
            break;
        fn_800C7FF4(*fn_80085954(fn_800B14C8(f20)), &v48, 0.1f);
        break;
    }
    case 0x5F: {
        Vector v38;
        Vector v48;
        if (!fn_800B0C1C(f20) || !fn_80085954(fn_800B14C8(f20)))
            break;
        Ent *f34 = fn_800C9FD0(fn_80085954(fn_800B14C8(f20)));
        if (!f34)
            break;
        fn_8005A828(*f20, fn_800B1724(*f34));
        break;
    }
    case 0x5C: {
        Vector v38;
        if (!fn_800B0C1C(f20) || !fn_80085954(fn_800B14C8(f20)))
            break;
        Ent *f34 = fn_800C9FD0(fn_80085954(fn_800B14C8(f20)));
        if (!f34)
            break;
        fn_8042DC84(&v38, fn_800B1724(*f20));
        v38.z = fn_800B1724(*f34)->z + (float)value * 0.001f;
        if (fn_804290F8(&v38, fn_800B1724(*f20)) > 1.0f)
            break;
        if (fn_80048EBC(fn_80085954(fn_800B14C8(f20))->s22(), &v38, 0, fn_800B24AC(*f34), fn_800B14C8(f20)->s21(), -0.11f, 0))
            break;
        fn_800C7FF4(*fn_80085954(fn_800B14C8(f20)), &v38, 0.1f);
        break;
    }
    case 0x68:
        if (f20 && fn_800B0C58(f20)) {
            if (fn_80085954(fn_800B14A0(f20)) && fn_800CD0EC(*fn_80085954(fn_800B14A0(f20))))
                fn_80085954(fn_800B14A0(f20))->s5(2);
            fn_80030930(fn_800B14A0(f20), 0, 0, 0, 0.0f, 0, 0, 0, 1, 0.0f);
        }
        break;
    case 0x69:
        if (f20 && fn_800B0C1C(f20) && fn_80085AF0(fn_800B14C8(f20)) && fn_8043B2C8(fn_80085AF0(fn_800B14C8(f20))))
            fn_801AA414((unsigned short)fn_8043B31C(fn_80085AF0(fn_800B14C8(f20))),
                        (float)value / 100.0f < 1.0f ? (float)value / 100.0f : 1.0f, 0.0f, extra, 0);
        break;
    case 0x6A:
        if (f20 && fn_800B0C1C(f20) && fn_80085AF0(fn_800B14C8(f20)) && fn_8043B2C8(fn_80085AF0(fn_800B14C8(f20))))
            fn_801AA414((unsigned short)fn_8043B31C(fn_80085AF0(fn_800B14C8(f20))), 0.0f,
                        (float)value / 100.0f < 1.0f ? (float)value / 100.0f : 1.0f, extra, 0);
        break;
    case 0x6B:
        if (fn_8043289C(&lbl_80552110))
            fn_8003DBF0(fn_8043289C(&lbl_80552110), extra, (float)value / 100.0f, 0);
        break;
    case 0x72:
        if (fn_800B0C1C(f20)) {
            if (value)
                fn_80086410(fn_800B14C8(f20));
            else
                fn_8008643C(fn_800B14C8(f20));
        }
        break;
    case 0x6C:
        if (f20 && fn_800B0F0C(f20) && fn_8009AD80(fn_800B1568(f20)))
            fn_8043B244(fn_8009AD80(fn_800B1568(f20)), value);
        break;
    case 0x6D:
        if (f20 && fn_800B0F0C(f20) && fn_8009AD80(fn_800B1568(f20)))
            fn_8043B284(fn_8009AD80(fn_800B1568(f20)), value);
        break;
    default:
        break;
    }
}
