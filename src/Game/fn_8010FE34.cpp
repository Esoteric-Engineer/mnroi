// Voice-event callbacks: fn_8010FE34 and fn_8011063C pick a variant from the sound bank (lbl_80568DB0+0x8, 200-249) and the speaker's type ID (lbl_8066F050), then send it through an Obj8C/Obj8B/Obj93/Obj8W temporary; docs/characters.md section 5.
// The real names are unknown, so the symbols stay extern "C".

struct Banks
{
    void *fallback; // +0x0
    void *events;   // +0x4
    int bank;       // +0x8
    int event;      // +0xC
};

class Obj8C
{
public:
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    Obj8C(int a, int b, int c, int d);
    ~Obj8C();
};

class Obj8B
{
public:
    int f[9];
    Obj8B(int a, int b, int c, int d, int e, int f, int g, int h);
    ~Obj8B();
};

class Obj8W
{
public:
    int f[5];
    Obj8W(int a, int b, int c, int d);
    ~Obj8W();
};

class Obj8D
{
public:
    int f[7];
    Obj8D(int a, int b, int c, int d, int e, int f);
    ~Obj8D();
};

class Obj8I
{
public:
    int f[6];
    Obj8I(int a, int b, int c, int d, int e);
    ~Obj8I();
};

class Obj122
{
public:
    int f[5];
    Obj122(int a, int b, int c, int d);
    ~Obj122();
};

class Obj8J
{
public:
    int f[6];
    Obj8J(int a, int b, int c, int d, int e);
    ~Obj8J();
};

class Obj8N
{
public:
    int f[8];
    Obj8N(int a, int b, int c, int d, int e, int f, int g);
    ~Obj8N();
};

class Obj8Q
{
public:
    int f[7];
    Obj8Q(int a, int b, int c, int d, int e, int f);
    ~Obj8Q();
};

class Obj8K
{
public:
    int f[5];
    Obj8K(int a, int b, int c, int d);
    ~Obj8K();
};

class Obj8U
{
public:
    int f[4];
    Obj8U(int a, int b, int c);
    ~Obj8U();
};

class Obj8O
{
public:
    int f[6];
    Obj8O(int a, int b, int c, int d, int e);
    ~Obj8O();
};

class Obj8M
{
public:
    int f[7];
    Obj8M(int a, int b, int c, int d, int e, int f);
    ~Obj8M();
};

class Obj8E
{
public:
    int f[4];
    Obj8E(int a, int b, int c);
    ~Obj8E();
};

class Obj95
{
public:
    int f[6];
    Obj95(int a, int b, int c, int d, int e);
    ~Obj95();
};

class Obj98
{
public:
    int f[5];
    Obj98(int a, int b, int c, int d);
    ~Obj98();
};

class Obj93
{
public:
    int f[5];
    Obj93(int a, int b, int c, int d);
    ~Obj93();
};

struct Record
{
    void *obj;      // +0x0
    char pad4[0x1C];
    int actor;      // +0x20
    char pad24[0x10];
    int value;      // +0x34
    char pad38[0x10];
    int active;     // +0x48
    char pad4C[0x14];
} __attribute__((aligned(8))); // matching_notes 42

extern Banks lbl_80568DB0;
extern Record lbl_80567760[48];
extern int lbl_8066F04C;
extern unsigned int lbl_8066F050;
extern unsigned int lbl_8066F054;
extern int lbl_8066F058;
extern int lbl_8066F05C;
extern int lbl_8066F060;
extern int lbl_8066F064;
extern int lbl_8066F068;
extern int lbl_8066F06C;
extern int lbl_8066F070;
extern void *lbl_8066BE10;

extern "C" {
void *fn_800ACFA8(int handle);
int fn_800B0C58(void *actor);
int fn_800B14A0(void *actor);
int fn_8010E498(int v);
int fn_80118C3C(int v);
int fn_80118C64(int v);
int fn_80118C8C(int v);
int fn_80118CB4(unsigned int v);
int fn_80118D0C(unsigned int v);
int fn_80118D64(int v);
int fn_80118DBC();
void fn_8011C4D8(void *p);
int fn_8010D2F0(int event);
int fn_8010D3C4(int bank);
int fn_8010DDAC(int bank);
void fn_8010E620();
void fn_80456478(void *obj, int v);
}

extern "C" void fn_8010FE34()
{
    int alt;
    void *actor;
    int track;

    alt = 0;
    actor = fn_800ACFA8(lbl_8066F04C);
    if (actor != 0 && fn_800B0C58(actor) != 0 && fn_8010E498(fn_800B14A0(actor)) == 1) {
        alt = 1;
    }
    track = 0;
    switch (lbl_80568DB0.bank) {
    case 200:
        switch (lbl_8066F050) {
        case 4:
            track = 11;
            break;
        case 17:
            track = 15;
            break;
        case 14:
            track = alt ? 28 : 27;
            break;
        case 21:
            track = 29;
            break;
        case 24:
            track = 32;
            break;
        default:
            track = 0;
            break;
        }
        break;
    case 210:
        track = 1;
        break;
    case 201:
        switch (lbl_8066F050) {
        case 1:
            track = alt ? 3 : 2;
            break;
        case 13:
            track = alt ? 18 : 17;
            break;
        case 6:
            track = alt ? 21 : 20;
            break;
        default:
            track = 0;
            break;
        }
        break;
    case 202:
        track = 9;
        break;
    case 203:
        track = 10;
        break;
    case 211:
        track = 8;
        break;
    case 206:
        track = 7;
        break;
    case 223:
        track = 12;
        break;
    case 224:
    case 227:
    case 228:
        track = 13;
        break;
    case 212:
        track = 14;
        break;
    case 235:
        track = 15;
        break;
    case 236:
        track = 16;
        break;
    case 237:
        track = 17;
        break;
    case 238:
        track = 18;
        break;
    case 239:
        track = 19;
        break;
    case 240:
        track = 20;
        break;
    case 241:
        track = 21;
        break;
    case 219:
    case 220:
        track = 22;
        break;
    case 221:
    case 222:
        track = 23;
        break;
    case 244:
        track = 24;
        break;
    case 230:
        track = 25;
        break;
    case 232:
        track = 26;
        break;
    case 245:
        track = 27;
        break;
    case 246:
        track = 28;
        break;
    case 248:
        track = 29;
        break;
    case 216:
    case 217:
        track = 30;
        break;
    case 249:
        track = 31;
        break;
    }
    (Obj8C(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118C8C(lbl_8066F064), track));
    if (lbl_8066F054 != 0 && lbl_8066F054 <= 40) {
        int x;
        int y;

        x = 0;
        y = 0;
        switch (lbl_80568DB0.bank) {
        case 102:
        case 202:
        case 203:
        case 205:
        case 206:
        case 211:
        case 212:
        case 215 ... 224:
        case 227 ... 233:
        case 244:
        case 247:
        case 248:
        case 249:
            y = 0;
            x = 1;
            break;
        case 201:
        case 213:
        case 214:
        case 235 ... 241:
        case 245:
        case 246:
            y = 0;
            x = 0;
            break;
        case 200:
            y = 0;
            x = 0;
            break;
        case 210:
            y = 1;
            x = 0;
            break;
        }
        if (alt) {
            y = 4;
            switch (lbl_8066F054) {
            case 2:
            case 11:
                y = 5;
                break;
            case 10:
                y = 6;
                break;
            }
        }
        (Obj8B(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118C8C(lbl_8066F064),
              fn_80118D0C(lbl_8066F054 <= 39 ? lbl_8066F054 : 0), lbl_8066F060, x, y, fn_80118DBC()));
        fn_8011C4D8(lbl_8066BE10);
    } else if (lbl_8066F054 == 0) {
        (Obj93(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118C8C(lbl_8066F064), fn_80118D64(lbl_8066F058)));
    }
}

extern "C" void fn_8011056C()
{
    int x;
    int y;

    x = lbl_8066F070;
    y = 0;
    (Obj8B(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118C8C(lbl_8066F064),
           fn_80118CB4(lbl_8066F050 <= 40 ? lbl_8066F050 : 0), lbl_8066F060, x, y, 0));
}

extern "C" void fn_8011063C()
{
    int track;

    switch (lbl_80568DB0.bank) {
    case 202:
        track = 3;
        break;
    case 203:
        track = 4;
        break;
    case 206:
        if (lbl_8066F050 == 3) {
            track = 5;
        } else {
            track = 8;
        }
        break;
    case 211:
        track = 2;
        break;
    case 223:
        track = 9;
        break;
    case 224:
    case 227:
    case 228:
        track = 10;
        break;
    case 212:
        track = 11;
        break;
    case 236:
        track = 13;
        break;
    case 247:
        track = 14;
        break;
    case 248:
        track = 15;
        break;
    case 239:
    case 240:
        track = 16;
        break;
    case 219:
    case 220:
        track = 17;
        break;
    case 221:
    case 222:
        track = 18;
        break;
    case 244:
        track = 19;
        break;
    case 229:
    case 230:
        track = 20;
        break;
    case 231:
    case 232:
        track = 21;
        break;
    case 233:
        track = 22;
        break;
    case 216:
    case 217:
        track = 23;
        break;
    case 249:
        track = 24;
        break;
    case 205:
        track = 26;
        break;
    default:
        switch (lbl_80568DB0.event) {
        case 47:
            if (lbl_80568DB0.bank == 17) {
                track = 12;
            } else {
                track = 6;
            }
            break;
        case 119:
            track = 7;
            break;
        default:
            track = lbl_8066F070;
            break;
        }
        break;
    }
    (Obj8W(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118CB4(lbl_8066F050 <= 40 ? lbl_8066F050 : 0), track));
}

extern "C" void fn_80110968()
{
    (Obj8D(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118C8C(lbl_8066F064), lbl_8066F070, 0, fn_80118DBC()));
}

extern "C" void fn_801109F8()
{
    (Obj8I(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118C8C(lbl_8066F064),
           fn_80118CB4(lbl_8066F050 <= 40 ? lbl_8066F050 : 0), lbl_8066F070));
}

extern "C" void fn_80110AA0()
{
    int v;

    v = fn_8010D3C4(lbl_80568DB0.bank);
    (Obj122(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118C8C(lbl_8066F064), v));
}

extern "C" void fn_80110B40()
{
    if (lbl_80568DB0.event == 51) {
        (Obj8J(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), 500,
               fn_80118CB4(lbl_8066F050 <= 40 ? lbl_8066F050 : 0), fn_80118D64(lbl_8066F058)));
    } else if (lbl_80568DB0.event == 20) {
        (Obj8J(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), 1000,
               fn_80118CB4(lbl_8066F050 <= 40 ? lbl_8066F050 : 0), fn_80118D64(lbl_8066F058)));
    } else {
        (Obj8J(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), 500,
               fn_80118CB4(lbl_8066F050 <= 40 ? lbl_8066F050 : 0), fn_80118D64(lbl_8066F058)));
    }
}

extern "C" void fn_80110D00()
{
    (Obj8N(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118C8C(lbl_8066F064),
           fn_80118CB4(lbl_8066F050 <= 40 ? lbl_8066F050 : 0), fn_80118D64(lbl_8066F058), lbl_8066F070, fn_80118DBC()));
}

extern "C" void fn_80110DC4()
{
    int a;
    int b;

    a = 0;
    if (lbl_8066F050 == 1) {
        a = 1;
    }
    b = fn_80118D64(lbl_8066F05C);
    (Obj8Q(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118C8C(lbl_8066F064),
           fn_80118CB4(lbl_8066F050 <= 40 ? lbl_8066F050 : 0), a, b));
}

extern "C" void fn_80110EA4()
{
    (Obj8K(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118C8C(lbl_8066F064), lbl_8066F070));
}

extern "C" void fn_80110F24()
{
    (Obj8U(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118CB4(lbl_8066F050 <= 40 ? lbl_8066F050 : 0)));
}

extern "C" void fn_80110FB8()
{
    (Obj8O(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118C8C(lbl_8066F064), fn_80118D64(lbl_8066F058),
           fn_80118DBC()));
}

extern "C" void fn_80111050()
{
    (Obj8M(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118C8C(lbl_8066F064),
           fn_80118CB4(lbl_8066F050 <= 40 ? lbl_8066F050 : 0), fn_80118D64(lbl_8066F058), fn_80118DBC()));
}

extern "C" void fn_80111110()
{
}

extern "C" void fn_80111134()
{
    if (lbl_80568DB0.bank > 20) {
        (Obj8E(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118CB4(lbl_8066F050 <= 40 ? lbl_8066F050 : 0)));
    }
}

extern "C" void fn_801111DC()
{
    int a;
    int b;

    a = fn_8010D2F0(lbl_80568DB0.event);
    b = fn_8010D3C4(lbl_80568DB0.bank);
    (Obj95(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118C8C(lbl_8066F064), a, b));
    int v = -1;
    switch (lbl_80568DB0.event) {
    case 130:
        v = 1;
        break;
    case 135:
        v = 2;
        break;
    case 133:
        v = 3;
        break;
    }
    if (v != -1) {
        unsigned int i;

        for (i = 0; i < 48; i++) {
            if (lbl_80567760[i].active != 0 && lbl_80567760[i].value != -1 && lbl_80567760[i].actor == lbl_8066F04C) {
                void *obj;

                lbl_80567760[i].value = v;
                obj = lbl_80567760[i].obj;
                if (obj != 0) {
                    fn_80456478(obj, lbl_80567760[i].value);
                }
            }
        }
    }
}

extern "C" void fn_801113FC(int event)
{
    switch (event) {
    case 50:
    case 135:
    case 144:
    case 152:
    case 155:
    case 175:
    case 500:
        fn_8010E620();
        break;
    }
}

extern "C" void fn_801114A0()
{
    int v;

    v = fn_8010DDAC(lbl_80568DB0.bank);
    (Obj98(fn_80118C3C(lbl_8066F068), fn_80118C64(lbl_8066F06C), fn_80118C8C(lbl_8066F064), v));
}
