// Record-table factories, actor checks and record setups over the 0x60-byte `lbl_80567760` table
// (guessed class names `Obj90`..`ObjH`); docs/versus.md section 5, row 2.

struct Slot
{
    void *owner;
    char pad0[0x1C];
    int source; // +0x20
    int state24; // +0x24
    char pad1[4];
    int handle2C; // +0x2C
    char pad2a[4];
    int handle34; // +0x34
    int id38; // +0x38
    char pad2b[0xC];
    int free48; // +0x48
    char pad2c[4];
    void *node; // +0x50
    char pad2[0xC];
} __attribute__((aligned(8)));

extern Slot lbl_80567760[];
extern int lbl_804CF638[];
extern "C" void *fn_800ACFA8(int handle);
extern "C" void *fn_800B1568(void *actor);
extern "C" unsigned int fn_8009ABEC(void *entity);
extern int lbl_8066BD60;

struct Node
{
    int check() __asm__("fn_8039CFE4");
};

struct Obj
{
    int get(int id) __asm__("fn_800ACD20");
    void *attach(int a, int b) __asm__("fn_80393A60");
    Node *find(void *n) __asm__("fn_80393B28");
};

struct Sub : Obj
{
    int pad;
};

extern "C" Sub *fn_800B14C8(void *actor);

class Obj90
{
public:
    char data[0x14];
    Obj90(register int a, register int b, register int c, register int d);
    void *operator new(unsigned size) __asm__("fn_8045C458");
};

class Obj92
{
public:
    char data[0x14];
    Obj92(register int a, register int b, register int c, register int d);
    void *operator new(unsigned size) __asm__("fn_8045C5F0");
};

extern "C" Obj90 *fn_804580CC(register int handle, register int index)
{
    int value = 0;
    void *actor = fn_800ACFA8(lbl_80567760[index].source);
    if (actor != 0) {
        value = lbl_804CF638[fn_8009ABEC(fn_800B1568(actor))];
    }
    return new Obj90(0, 100, value, 1);
}

extern "C" int fn_804581A0(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    if (lbl_80567760[index].node == 0) {
        void *a = fn_800ACFA8(lbl_80567760[index].source);
        if (a != 0) {
            lbl_80567760[index].node = fn_800B14C8(a)->attach(fn_800B14C8(a)->get(0x65), 0);
        }
    }
    {
        Node *n = (Node *)lbl_80567760[index].node;
        n = fn_800B14C8(actor)->find(n);
        register unsigned int found = 0;
        if (n != 0) {
            if (n->check()) {
                found = 1;
            }
        }
        return found;
    }
}

extern "C" void fn_80112214(void *rec, int handle, int flag);
extern "C" int fn_80118C64(int v);
extern "C" int fn_80118C3C(int v);
extern "C" void fn_8045C38C(void *self, int v);
extern "C" void fn_8045C33C(void *self, int v);
extern "C" void fn_8045C414(void *self, int v);
extern int lbl_8066F06C;
extern int lbl_8066F068;
extern char lbl_80567770[];

extern "C" void fn_804582F0(register void *self, register int unused, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045C38C(self, fn_80118C64(lbl_8066F06C));
    fn_8045C33C(self, fn_80118C3C(lbl_8066F068));
    if (lbl_80567760[index].state24 > 0x257) {
        fn_8045C414(self, 1);
    } else {
        fn_8045C414(self, 0);
    }
}

extern "C" Obj92 *fn_804583C8(register int handle, register int index)
{
    int value = 0;
    void *actor = fn_800ACFA8(lbl_80567760[index].source);
    if (actor != 0) {
        value = lbl_804CF638[fn_8009ABEC(fn_800B1568(actor))];
    }
    return new Obj92(0, 50, 900, value);
}

extern "C" int fn_800B0C1C(void *actor);
extern "C" void *fn_80085954(void *entity);
extern "C" int fn_800CCA08(void *p);
extern int lbl_8066BD30;

extern "C" int fn_8045849C(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    if (fn_800B0C1C(actor)) {
        register void *p;
        register unsigned int found = 0;
        if (lbl_8066BD30 != 0 || (p = fn_80085954(fn_800B14C8(actor)), fn_800CCA08(p))) {
            found = 1;
        }
        int result = found;
        return result;
    }
    return 0;
}

extern "C" void fn_8045C524(void *self, int v);
extern "C" void fn_8045C4D4(void *self, int v);
extern "C" void fn_8045C568(void *self, int v);

extern "C" void fn_8045855C(register void *self, register int unused, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045C524(self, fn_80118C64(lbl_8066F06C));
    fn_8045C4D4(self, fn_80118C3C(lbl_8066F068));
    fn_8045C568(self, 0x384);
}

class ObjC
{
public:
    char data[0xC];
    ObjC(register int a, register int b);
    void *operator new(unsigned size) __asm__("fn_8045D2E8");
};

extern "C" ObjC *fn_80458608(register int handle, register int index)
{
    return new ObjC(0, 0);
}

struct Pos
{
    float pad[2];
    float z; // +0x8
};

extern "C" int fn_8005ABF0(void *actor);
extern "C" float fn_800670CC(void *actor);
extern "C" unsigned int fn_8010C7EC(void *obj, int a, int b);
extern "C" Pos *fn_800B1724(void *actor);
extern char lbl_8066D808[8];

extern "C" int fn_8045866C(register void *actor, register int index)
{
    register unsigned int found = 0;
    if (fn_8005ABF0(actor)) {
        register float height = fn_800670CC(actor);
        if (height > (float)fn_8010C7EC(lbl_8066D808, 1, 0x65)) {
            if (fn_800B1724(actor)->z > -30.0f) {
                found = 1;
            }
        }
    }
    return found;
}

extern "C" void fn_8045D2A4(void *self, int v);
extern "C" void fn_8045D254(void *self, int v);

extern "C" void fn_8045873C(register void *self, register int unused, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045D2A4(self, fn_80118C64(lbl_8066F06C));
    fn_8045D254(self, fn_80118C3C(lbl_8066F068));
}

class ObjD
{
public:
    char data[0x10];
    ObjD(register int a, register int b, register int c);
    void *operator new(unsigned size) __asm__("fn_8045B474");
};

extern "C" ObjD *fn_804587DC(register int handle, register int index)
{
    int value = 0;
    void *actor = fn_800ACFA8(lbl_80567760[index].source);
    if (actor != 0) {
        value = lbl_804CF638[fn_8009ABEC(fn_800B1568(actor))];
    }
    return new ObjD(0, 50, value);
}

extern "C" int fn_800CCA88(void *p);

extern "C" int fn_804588AC(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    if (actor != 0 && fn_800B0C1C(actor)) {
        register void *p = fn_80085954(fn_800B14C8(actor));
        return fn_800CCA88(p) != 0 ? 1 : 0;
    }
    return 0;
}

struct Setting;
extern "C" void fn_8045B430(Setting *self, int v);
extern "C" void fn_8045B3E0(Setting *self, int v);

extern "C" void fn_8045895C(register void *self, register int unused, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045B430((Setting *)self, fn_80118C64(lbl_8066F06C));
    fn_8045B3E0((Setting *)self, fn_80118C3C(lbl_8066F068));
}

class ObjE
{
public:
    char data[8];
    ObjE(register int a);
    void *operator new(unsigned size) __asm__("fn_8045D140");
};

extern "C" ObjE *fn_804589FC(register int handle, register int index)
{
    return new ObjE(0);
}

extern "C" int fn_800CCAB8(void *p);
extern "C" float fn_80086730(void *entity);
extern "C" float fn_8008677C(void *entity);

extern "C" int fn_80458A5C(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    if (actor != 0 && fn_800B0C1C(actor)) {
        register void *p;
        register unsigned int found = 0;
        p = fn_80085954(fn_800B14C8(actor));
        if (fn_800CCAB8(p) != 0) {
            register float a = fn_80086730(fn_800B14C8(actor));
            if (a < fn_8008677C(fn_800B14C8(actor))) {
                found = 1;
            }
        }
        return found;
    }
    return 0;
}

extern "C" void fn_8045D0FC(void *self, int v);

extern "C" void fn_80458B4C(register void *self, register void *actor, register int index)
{
    int value = 0;
    if (actor != 0 && fn_800B0C1C(actor)) {
        register float a = fn_80086730(fn_800B14C8(actor));
        value = (int)(a * 1000.0f / fn_8008677C(fn_800B14C8(actor)));
    }
    fn_8045D0FC(self, value);
}

class ObjF
{
public:
    char data[0x14];
    ObjF(register int a, register int b, register int c, register int d);
    void *operator new(unsigned size) __asm__("fn_8045CD4C");
};

extern "C" int fn_8010DDAC(int handle);

extern "C" ObjF *fn_80458C18(register int handle, register int index)
{
    int value = fn_8010DDAC(handle);
    return new ObjF(0, 0, 50, value);
}

extern "C" int fn_80458C94(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    return 1;
}

extern "C" void fn_8045CD04(void *self, int v);
extern "C" void fn_8045CCB4(void *self, int v);

extern "C" void fn_80458CDC(register void *self, register int unused, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045CD04(self, fn_80118C64(lbl_8066F06C));
    fn_8045CCB4(self, fn_80118C3C(lbl_8066F068));
}

class ObjG
{
public:
    char data[0x1C];
    ObjG(register int a, register int b, register int c, register int d, register int e, register int f);
    void *operator new(unsigned size) __asm__("fn_8045C9F8");
};

extern "C" int fn_8010D3C4(int handle);

extern "C" ObjG *fn_80458D7C(register int handle, register int index)
{
    int value = fn_8010D3C4(handle);
    if (lbl_80567760[index].handle34 == -1) {
        lbl_80567760[index].handle34 = 0;
    }
    return new ObjG(0, 0, 50, 0, value, lbl_80567760[index].handle34);
}

extern int lbl_8066BDF8;
extern int lbl_8066BE04;

extern "C" int fn_80458E48(register void *actor, register int index)
{
    if (lbl_80567760[index].handle2C == 0x108 && lbl_8066BDF8 == 0x30 && lbl_8066BE04 == 1) {
        return 0;
    }
    if (lbl_80567760[index].handle2C == 0x204 && lbl_80567760[index].handle34 == 1) {
        return 0;
    }
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    return 1;
}

extern "C" void fn_8045C9B0(void *self, int v);
extern "C" void fn_8045C960(void *self, int v);

extern "C" void fn_80458F0C(register void *self, register int unused, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    int v = fn_80118C64(lbl_8066F06C);
    fn_8045C9B0(self, v);
    fn_8045C960(self, fn_80118C3C(lbl_8066F068));
}

class ObjH
{
public:
    char data[0x10];
    ObjH(register int a, register int b, register int c);
    void *operator new(unsigned size) __asm__("fn_8045C208");
};

extern "C" ObjH *fn_80458FB0(register int handle, register int index)
{
    return new ObjH(0, 0, 50);
}

extern "C" int fn_80459018(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    return 1;
}

extern "C" void fn_8045C17C(void *self, int v);
extern "C" void fn_8045C12C(void *self, int v);
extern "C" void fn_8045C1C4(void *self, int v);

extern "C" void fn_80459060(register void *self, register void *actor, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045C17C(self, fn_80118C64(lbl_8066F06C));
    fn_8045C12C(self, fn_80118C3C(lbl_8066F068));
    float h = fn_800670CC(actor);
    int value = (int)(h * 200.0f);
    if (value < 0) {
        value = 0;
    }
    if (value > 1000) {
        value = 1000;
    }
    fn_8045C1C4(self, value);
}

class ObjI
{
public:
    char data[0x14];
    ObjI(register int a, register int b, register int c, register int d);
    void *operator new(unsigned size) __asm__("fn_8045D4E8");
};

extern "C" ObjI *fn_80459168(register int handle, register int index)
{
    int value = 0;
    void *actor = fn_800ACFA8(lbl_80567760[index].source);
    if (actor != 0) {
        value = fn_8010D3C4(fn_8009ABEC(fn_800B1568(actor)));
    }
    return new ObjI(0, 0, 0, value);
}

struct Obj2
{
    int get() __asm__("fn_800B1138");
};

struct Sub2 : Obj2
{
    int pad;
};

extern "C" Sub2 *fn_800B1478(void *actor);
extern "C" int fn_800B0CC0(void *actor);

extern "C" int fn_80459230(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    if (fn_800B0CC0(actor)) {
        int v = fn_800B1478(actor)->get();
        return v == 0;
    }
    return 0;
}

extern "C" void fn_8045D45C(void *self, int v);
extern "C" void fn_8045D40C(void *self, int v);
extern "C" void fn_8045D4A4(void *self, int v);

extern "C" void fn_804592D0(register void *self, register void *actor, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045D45C(self, fn_80118C64(lbl_8066F06C));
    fn_8045D40C(self, fn_80118C3C(lbl_8066F068));
    fn_8045D4A4(self, lbl_80567760[index].state24);
}

class ObjJ
{
public:
    char data[0x14];
    ObjJ(register int a, register int b, register int c, register int d);
    void *operator new(unsigned size) __asm__("fn_8045B820");
};

extern "C" int fn_800B0C58(void *actor);

extern "C" ObjJ *fn_8045938C(register int handle, register int index)
{
    void *actor = fn_800ACFA8(lbl_80567760[index].source);
    int value = 0;
    if (actor != 0 && fn_800B0C58(actor)) {
        value = lbl_804CF638[fn_8009ABEC(fn_800B1568(actor))];
    }
    return new ObjJ(0, 0, 1000, value);
}

struct ActorInfo
{
    unsigned int getA() __asm__("fn_8009B04C");
    unsigned int getB() __asm__("fn_8009AFC8");
};

struct ActorInfoSub : ActorInfo
{
    int pad;
};

extern "C" ActorInfoSub *fn_800B14A0(void *actor);
extern "C" int fn_800B13D8(void *actor);

extern "C" int fn_80459474(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    if (actor != 0 && fn_800B0C58(actor)) {
        if (lbl_80567760[index].id38 == -1) {
            int v = fn_800B14A0(actor)->getA();
            if (v == 0) {
                v = fn_800B14A0(actor)->getB();
            }
            lbl_80567760[index].id38 = v;
            for (unsigned int i = 0; i <= 0x2F; i++) {
                if (i == index) {
                    continue;
                }
                if (lbl_80567760[i].free48 != 0 && lbl_80567760[i].handle2C == 0x39
                    && lbl_80567760[i].source == fn_800B13D8(actor)) {
                    return 0;
                }
            }
        }
        int w = fn_800B14A0(actor)->getA();
        if (w == 0) {
            w = fn_800B14A0(actor)->getB();
        }
        return lbl_80567760[index].id38 == w;
    }
    return 0;
}

extern "C" void fn_8045B7D8(void *self, int v);
extern "C" void fn_8045B788(void *self, int v);

extern "C" void fn_80459670(register void *self, register void *actor, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045B7D8(self, fn_80118C64(lbl_8066F06C));
    fn_8045B788(self, fn_80118C3C(lbl_8066F068));
}

class ObjK
{
public:
    char data[0x14];
    ObjK(register int a, register int b, register int c, register int d);
    void *operator new(unsigned size) __asm__("fn_8045BFE8");
};

extern "C" ObjK *fn_80459710(register int handle, register int index)
{
    void *actor = fn_800ACFA8(lbl_80567760[index].source);
    int value = 0;
    if (actor != 0 && fn_800B0C58(actor)) {
        value = lbl_804CF638[fn_8009ABEC(fn_800B1568(actor))];
    }
    return new ObjK(0, 0, 1000, value);
}

extern "C" int fn_804597F8(register void *actor, register int index)
{
    if (actor != 0 && fn_800B0C58(actor)) {
        if (lbl_80567760[index].id38 == -1) {
            int v = fn_800B14A0(actor)->getA();
            if (v == 0) {
                v = fn_800B14A0(actor)->getB();
            }
            lbl_80567760[index].id38 = v;
            for (unsigned int i = 0; i <= 0x2F; i++) {
                if (i == index) {
                    continue;
                }
                if (lbl_80567760[i].free48 != 0 && lbl_80567760[i].handle2C == 0x3A
                    && lbl_80567760[i].source == fn_800B13D8(actor)) {
                    return 0;
                }
            }
        }
        int w = fn_800B14A0(actor)->getA();
        if (w == 0) {
            w = fn_800B14A0(actor)->getB();
        }
        return lbl_80567760[index].id38 == w;
    }
    return 0;
}

extern "C" void fn_8045BFA0(void *self, int v);
extern "C" void fn_8045BF50(void *self, int v);

extern "C" void fn_804599E0(register void *self, register void *actor, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045BFA0(self, fn_80118C64(lbl_8066F06C));
    fn_8045BF50(self, fn_80118C3C(lbl_8066F068));
}

class ObjL
{
public:
    char data[0x18];
    ObjL(register int a, register int b, register int c, register int d, register int e);
    void *operator new(unsigned size) __asm__("fn_8045BB98");
};

extern "C" ObjL *fn_80459A80(register int handle, register int index)
{
    void *actor = fn_800ACFA8(lbl_80567760[index].source);
    int value = 0;
    if (actor != 0 && fn_800B0C58(actor)) {
        value = lbl_804CF638[fn_8009ABEC(fn_800B1568(actor))];
    }
    return new ObjL(0, 0, 0x32, value, 0);
}

extern "C" int fn_80459B6C(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    return 1;
}

extern "C" void fn_8045BB0C(void *self, int v);
extern "C" void fn_8045BABC(void *self, int v);
extern "C" void fn_8045BB54(void *self, int v);

extern "C" void fn_80459BB4(register void *self, register void *actor, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045BB0C(self, fn_80118C64(lbl_8066F06C));
    fn_8045BABC(self, fn_80118C3C(lbl_8066F068));
    float h = fn_800670CC(actor);
    int value = (int)(h * 200.0f);
    if (value < 0) {
        value = 0;
    }
    if (value > 1000) {
        value = 1000;
    }
    fn_8045BB54(self, value);
}

inline int sn_return_decl(int a) { return a; }

struct Level
{
    int pad0;
    int value; // +0x4
    int value2; // +0x8
    int value3; // +0xC
};

extern "C" void fn_80459CBC(register Level *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 100) {
        v = 100;
    }
    self->value = v;
}

extern "C" void fn_80459D00(register Level *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 100) {
        v = 100;
    }
    self->value2 = v;
}

extern "C" void fn_80459D44(register Level *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 100) {
        v = 100;
    }
    self->value3 = v;
}

extern "C" void fn_802460AC(void *p);

extern "C" void fn_80459D88(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_80459DC0(register Level *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 10) {
        v = 10;
    }
    self->value = v;
}

extern "C" void fn_80459E04(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_80459E3C(register void *self)
{
    fn_802460AC(self);
}

struct Setting
{
    int pad0;
    int f4; // +0x4
    int f8; // +0x8
    int fC; // +0xC
    int f10; // +0x10
    int f14; // +0x14
    int f18; // +0x18
    int f1C; // +0x1C
    int f20; // +0x20
};

extern "C" void fn_80459E74(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_80459EC4(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_80459F0C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_80459F50(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 50) {
        v = 50;
    }
    self->f10 = v;
}

extern "C" void fn_80459F94(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 4) {
        v = 4;
    }
    self->f14 = v;
}

extern "C" void fn_80459FD8(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1) {
        v = 1;
    }
    self->f18 = v;
}

extern "C" void fn_8045A01C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 300) {
        v = 300;
    }
    self->f1C = v;
}

extern "C" void fn_8045A060(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0x7FFF) {
        v = 0x7FFF;
    }
    self->f20 = v;
}

extern "C" void fn_8045A0A4(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045A0DC(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045A12C(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045A174(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045A1B8(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 150) {
        v = 150;
    }
    self->f10 = v;
}

extern "C" void fn_8045A1FC(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045A234(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045A284(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045A2CC(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045A310(register Setting *self, register int v)
{
    if (v < 1) {
        v = 1;
    } else if (v > 4) {
        v = 4;
    }
    self->f10 = v;
}

extern "C" void fn_8045A354(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 20) {
        v = 20;
    }
    self->f14 = v;
}

extern "C" void fn_8045A398(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0x7FFF) {
        v = 0x7FFF;
    }
    self->f18 = v;
}

extern "C" void fn_8045A3DC(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045A414(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045A464(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045A4A8(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 40) {
        v = 40;
    }
    self->fC = v;
}

extern "C" void fn_8045A4EC(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045A524(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045A574(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045A5B8(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 40) {
        v = 40;
    }
    self->fC = v;
}

extern "C" void fn_8045A5FC(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045A634(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045A684(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045A6CC(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045A710(register Setting *self, register int v)
{
    if (v < 1) {
        v = 1;
    } else if (v > 40) {
        v = 40;
    }
    self->f10 = v;
}

extern "C" void fn_8045A754(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0x7FFF) {
        v = 0x7FFF;
    }
    self->f14 = v;
}

extern "C" void fn_8045A798(register Setting *self, register int v)
{
    if (v < 1) {
        v = 1;
    } else if (v > 6) {
        v = 6;
    }
    self->f18 = v;
}

extern "C" void fn_8045A7DC(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045A814(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045A864(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045A8AC(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045A8F0(register Setting *self, register int v)
{
    if (v < 1) {
        v = 1;
    } else if (v > 40) {
        v = 40;
    }
    self->f10 = v;
}

extern "C" void fn_8045A934(register Setting *self, register int v)
{
    if (v < 1) {
        v = 1;
    } else if (v > 6) {
        v = 6;
    }
    self->f14 = v;
}

extern "C" void fn_8045A978(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045A9B0(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045AA00(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045AA48(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045AA8C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 40) {
        v = 40;
    }
    self->f10 = v;
}

extern "C" void fn_8045AAD0(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f14 = v;
}

extern "C" void fn_8045AB14(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045AB4C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045AB9C(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045ABE4(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045AC28(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 40) {
        v = 40;
    }
    self->f10 = v;
}

extern "C" void fn_8045AC6C(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045ACA4(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045ACF4(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045AD3C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045AD80(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 100) {
        v = 100;
    }
    self->f10 = v;
}

extern "C" void fn_8045ADC4(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 50) {
        v = 50;
    }
    self->f14 = v;
}

extern "C" void fn_8045AE08(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045AE40(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045AE90(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045AED8(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045AF1C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 41) {
        v = 41;
    }
    self->f10 = v;
}

extern "C" void fn_8045AF60(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f14 = v;
}

extern "C" void fn_8045AFA4(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0x7FFF) {
        v = 0x7FFF;
    }
    self->f18 = v;
}

extern "C" void fn_8045AFE8(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045B020(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045B070(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045B0B8(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045B0FC(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 40) {
        v = 40;
    }
    self->f10 = v;
}

extern "C" void fn_8045B140(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 50) {
        v = 50;
    }
    self->f14 = v;
}

extern "C" void fn_8045B184(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 4) {
        v = 4;
    }
    self->f18 = v;
}

extern "C" void fn_8045B1C8(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0x7FFF) {
        v = 0x7FFF;
    }
    self->f1C = v;
}

extern "C" void fn_8045B20C(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045B244(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045B294(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045B2DC(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045B320(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 50) {
        v = 50;
    }
    self->f10 = v;
}

extern "C" void fn_8045B364(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0x7FFF) {
        v = 0x7FFF;
    }
    self->f14 = v;
}

extern "C" void fn_8045B3A8(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045B3E0(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045B430(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}


extern "C" int fn_8024606C(void *p);

extern "C" int fn_8045B474(register void *self)
{
    return fn_8024606C(self);
}

extern "C" void fn_8045B4B8(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045DEFC(void *self, int v);
extern "C" int fn_802465B0(void *table, void *key, void *self);
extern "C" void fn_80245CBC(void *table, void *name);
extern char lbl_8066D89C[8];
extern char lbl_8066BBF0[8];

ObjD::ObjD(register int a, register int b, register int c)
{
    int r;
    fn_8045B3E0((Setting *)this, a);
    fn_8045B430((Setting *)this, b);
    fn_8045DEFC(this, c);
    r = fn_802465B0(lbl_8066D89C, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D89C, lbl_8066BBF0);
        r = fn_802465B0(lbl_8066D89C, (char *)this + 4, this);
    }
}

extern "C" void fn_8045B5A8(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045B5F8(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045B640(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045B684(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 19) {
        v = 19;
    }
    self->f10 = v;
}

extern "C" void fn_8045B6C8(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 10) {
        v = 10;
    }
    self->f14 = v;
}

extern "C" void fn_8045B70C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 20) {
        v = 20;
    }
    self->f18 = v;
}

extern "C" void fn_8045B750(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045B788(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    ((Setting *)self)->f4 = v;
}

extern "C" void fn_8045B7D8(register void *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    ((Setting *)self)->f8 = v;
}

extern "C" int fn_8045B820(register void *self)
{
    return fn_8024606C(self);
}

extern "C" void fn_8045B864(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045DF40(void *self, int v);
extern "C" void fn_8045DF84(void *self, int v);
extern char lbl_8066D8AC[8];
extern char lbl_8066BC00[8];

ObjJ::ObjJ(register int a, register int b, register int c, register int d)
{
    int r;
    fn_8045B788(this, a);
    fn_8045B7D8(this, b);
    fn_8045DF40(this, c);
    fn_8045DF84(this, d);
    r = fn_802465B0(lbl_8066D8AC, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D8AC, lbl_8066BC00);
        r = fn_802465B0(lbl_8066D8AC, (char *)this + 4, this);
    }
}

extern "C" void fn_8045B964(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045B9B4(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045B9FC(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045BA40(register Setting *self, register int v)
{
    if (v < 1) {
        v = 1;
    } else if (v > 40) {
        v = 40;
    }
    self->f10 = v;
}

extern "C" void fn_8045BA84(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045BABC(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    ((Setting *)self)->f4 = v;
}

extern "C" void fn_8045BB0C(register void *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    ((Setting *)self)->f8 = v;
}

extern "C" void fn_8045BB54(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    ((Setting *)self)->f14 = v;
}

extern "C" int fn_8045BB98(register void *self)
{
    return fn_8024606C(self);
}

extern "C" void fn_8045BBDC(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045DFC8(void *self, int v);
extern "C" void fn_8045E00C(void *self, int v);
extern char lbl_8066D8BC[8];
extern char lbl_8066BC10[8];

ObjL::ObjL(register int a, register int b, register int c, register int d, register int e)
{
    int r;
    fn_8045BABC(this, a);
    fn_8045BB0C(this, b);
    fn_8045DFC8(this, c);
    fn_8045E00C(this, d);
    fn_8045BB54(this, e);
    r = fn_802465B0(lbl_8066D8BC, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D8BC, lbl_8066BC10);
        r = fn_802465B0(lbl_8066D8BC, (char *)this + 4, this);
    }
}

extern "C" void fn_8045BCEC(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045BD3C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045BD80(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 40) {
        v = 40;
    }
    self->fC = v;
}

extern "C" void fn_8045BDC4(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045BDFC(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045BE4C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045BE90(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 40) {
        v = 40;
    }
    self->fC = v;
}

extern "C" void fn_8045BED4(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 100) {
        v = 100;
    }
    self->f10 = v;
}

extern "C" void fn_8045BF18(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045BF50(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    ((Setting *)self)->f4 = v;
}

extern "C" void fn_8045BFA0(register void *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    ((Setting *)self)->f8 = v;
}

extern "C" int fn_8045BFE8(register void *self)
{
    return fn_8024606C(self);
}

extern "C" void fn_8045C02C(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045E050(void *self, int v);
extern "C" void fn_8045E094(void *self, int v);
extern char lbl_8066D8DC[8];
extern char lbl_8066BC28[8];

ObjK::ObjK(register int a, register int b, register int c, register int d)
{
    int r;
    fn_8045BF50(this, a);
    fn_8045BFA0(this, b);
    fn_8045E050(this, c);
    fn_8045E094(this, d);
    r = fn_802465B0(lbl_8066D8DC, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D8DC, lbl_8066BC28);
        r = fn_802465B0(lbl_8066D8DC, (char *)this + 4, this);
    }
}

extern "C" void fn_8045C12C(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    ((Setting *)self)->f4 = v;
}

extern "C" void fn_8045C17C(register void *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    ((Setting *)self)->f8 = v;
}

extern "C" void fn_8045C1C4(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    ((Setting *)self)->fC = v;
}

extern "C" int fn_8045C208(register void *self)
{
    return fn_8024606C(self);
}

extern "C" void fn_8045C24C(register void *self)
{
    fn_802460AC(self);
}

extern char lbl_8066D8E4[8];
extern char lbl_8066BC30[8];

ObjH::ObjH(register int a, register int b, register int c)
{
    int r;
    fn_8045C12C(this, a);
    fn_8045C17C(this, b);
    fn_8045C1C4(this, c);
    r = fn_802465B0(lbl_8066D8E4, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D8E4, lbl_8066BC30);
        r = fn_802465B0(lbl_8066D8E4, (char *)this + 4, this);
    }
}

extern "C" void fn_8045C33C(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    ((Setting *)self)->f4 = v;
}

extern "C" void fn_8045C38C(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    ((Setting *)self)->f8 = v;
}

extern "C" void fn_8045C3D0(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 50) {
        v = 50;
    }
    self->fC = v;
}

extern "C" void fn_8045C414(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1) {
        v = 1;
    }
    ((Setting *)self)->f10 = v;
}

extern "C" int fn_8045C458(register void *self)
{
    return fn_8024606C(self);
}

extern "C" void fn_8045C49C(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045C4D4(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    ((Setting *)self)->f4 = v;
}

extern "C" void fn_8045C524(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    ((Setting *)self)->f8 = v;
}

extern "C" void fn_8045C568(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    ((Setting *)self)->fC = v;
}

extern "C" void fn_8045C5AC(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 50) {
        v = 50;
    }
    self->f10 = v;
}

extern "C" int fn_8045C5F0(register void *self)
{
    return fn_8024606C(self);
}

extern "C" void fn_8045C634(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045C66C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045C6BC(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045C704(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045C748(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 50) {
        v = 50;
    }
    self->f10 = v;
}

extern "C" void fn_8045C78C(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045C7C4(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045C814(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045C85C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045C8A0(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 7) {
        v = 7;
    }
    self->f10 = v;
}

extern "C" void fn_8045C8E4(register Setting *self, register int v)
{
    if (v < 1) {
        v = 1;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f14 = v;
}

extern "C" void fn_8045C928(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045C960(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    ((Setting *)self)->f4 = v;
}

extern "C" void fn_8045C9B0(register void *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    ((Setting *)self)->f8 = v;
}

extern "C" int fn_8045C9F8(register void *self)
{
    return fn_8024606C(self);
}

extern "C" void fn_8045CA3C(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045E0D8(void *self, int v);
extern "C" void fn_8045E11C(void *self, int v);
extern "C" void fn_8045E160(void *self, int v);
extern "C" void fn_80456478(void *self, int v);
extern char lbl_8066D924[8];
extern char lbl_8066BC58[8];

ObjG::ObjG(register int a, register int b, register int c, register int d, register int e, register int f)
{
    int r;
    fn_8045C960(this, a);
    fn_8045C9B0(this, b);
    fn_8045E0D8(this, c);
    fn_8045E11C(this, d);
    fn_8045E160(this, e);
    fn_80456478(this, f);
    r = fn_802465B0(lbl_8066D924, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D924, lbl_8066BC58);
        r = fn_802465B0(lbl_8066D924, (char *)this + 4, this);
    }
}

extern "C" void fn_8045CB5C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045CBAC(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045CBF4(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045CC38(register Setting *self, register int v)
{
    if (v < 1) {
        v = 1;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f10 = v;
}

extern "C" void fn_8045CC7C(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045CCB4(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    ((Setting *)self)->f4 = v;
}

extern "C" void fn_8045CD04(register void *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    ((Setting *)self)->f8 = v;
}

extern "C" int fn_8045CD4C(register void *self)
{
    return fn_8024606C(self);
}

extern "C" void fn_8045CD90(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045E1A4(void *self, int v);
extern "C" void fn_8045E1E8(void *self, int v);
extern char lbl_8066D934[8];
extern char lbl_8066BC68[8];

ObjF::ObjF(register int a, register int b, register int c, register int d)
{
    int r;
    fn_8045CCB4(this, a);
    fn_8045CD04(this, b);
    fn_8045E1A4(this, c);
    fn_8045E1E8(this, d);
    r = fn_802465B0(lbl_8066D934, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D934, lbl_8066BC68);
        r = fn_802465B0(lbl_8066D934, (char *)this + 4, this);
    }
}

extern "C" void fn_8045CE90(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 100) {
        v = 100;
    }
    self->f4 = v;
}

extern "C" void fn_8045CED4(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045CF0C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 30) {
        v = 30;
    }
    self->f4 = v;
}

extern "C" void fn_8045CF50(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045CF88(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 30) {
        v = 30;
    }
    self->f4 = v;
}

extern "C" void fn_8045CFCC(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045D004(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 30) {
        v = 30;
    }
    self->f4 = v;
}

extern "C" void fn_8045D048(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045D080(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 30) {
        v = 30;
    }
    self->f4 = v;
}

extern "C" void fn_8045D0C4(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045D0FC(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    ((Setting *)self)->f4 = v;
}

extern "C" int fn_8045D140(register void *self)
{
    return fn_8024606C(self);
}

extern "C" void fn_8045D184(register void *self)
{
    fn_802460AC(self);
}

extern char lbl_8066D964[8];
extern char lbl_8066BC98[8];

ObjE::ObjE(register int a)
{
    int r;
    fn_8045D0FC(this, a);
    r = fn_802465B0(lbl_8066D964, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D964, lbl_8066BC98);
        r = fn_802465B0(lbl_8066D964, (char *)this + 4, this);
    }
}

extern "C" void fn_8045D254(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    ((Setting *)self)->f4 = v;
}

extern "C" void fn_8045D2A4(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    ((Setting *)self)->f8 = v;
}

extern "C" int fn_8045D2E8(register void *self)
{
    return fn_8024606C(self);
}

extern "C" void fn_8045D32C(register void *self)
{
    fn_802460AC(self);
}

extern char lbl_8066D9C4[8];
extern char lbl_8066BCA0[8];

ObjC::ObjC(register int a, register int b)
{
    int r;
    fn_8045D254(this, a);
    fn_8045D2A4(this, b);
    r = fn_802465B0(lbl_8066D9C4, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D9C4, lbl_8066BCA0);
        r = fn_802465B0(lbl_8066D9C4, (char *)this + 4, this);
    }
}

extern "C" void fn_8045D40C(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    ((Setting *)self)->f4 = v;
}

extern "C" void fn_8045D45C(register void *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    ((Setting *)self)->f8 = v;
}

extern "C" void fn_8045D4A4(register void *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    ((Setting *)self)->fC = v;
}

extern "C" int fn_8045D4E8(register void *self)
{
    return fn_8024606C(self);
}

extern "C" void fn_8045D52C(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045E22C(void *self, int v);
extern char lbl_8066D9CC[8];
extern char lbl_8066BCA8[8];

ObjI::ObjI(register int a, register int b, register int c, register int d)
{
    int r;
    fn_8045D40C(this, a);
    fn_8045D45C(this, b);
    fn_8045D4A4(this, c);
    fn_8045E22C(this, d);
    r = fn_802465B0(lbl_8066D9CC, (char *)this + 4, this);
    if (r < 0) {
        fn_80245CBC(lbl_8066D9CC, lbl_8066BCA8);
        r = fn_802465B0(lbl_8066D9CC, (char *)this + 4, this);
    }
}

extern "C" void fn_8045D62C(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045D664(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045D69C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045D6EC(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045D734(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045D778(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1) {
        v = 1;
    }
    self->f10 = v;
}

extern "C" void fn_8045D7BC(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045D7F4(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_8045D82C(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 0xFFFF) {
        v = 0xFFFF;
    }
    self->f4 = v;
}

extern "C" void fn_8045D87C(register Setting *self, register int v)
{
    if (v < -1000) {
        v = -1000;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f8 = v;
}

extern "C" void fn_8045D8C4(register Setting *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 1000) {
        v = 1000;
    }
    self->fC = v;
}

extern "C" void fn_8045D908(register Setting *self, register int v)
{
    if (v < 1) {
        v = 1;
    } else if (v > 1000) {
        v = 1000;
    }
    self->f10 = v;
}

extern "C" void fn_8045D94C(register void *self)
{
    fn_802460AC(self);
}
