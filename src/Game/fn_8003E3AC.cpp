// Routes the thrower events 0x44-0x47 and 0x6E-0x71 (from fn_80058C94) to their handlers, unless fn_80435878(G) holds.

struct State {
    char pad[0x75C];
};

struct Src {
    char pad0[0x1C];
    int f1C;
};

struct Rec {
    char pad0[0x14];
    unsigned int flags; // +0x14
};

extern State lbl_80552110; // the game-state object G

extern "C" {
int fn_80435878(State *g);
int fn_800B13D8(void *e);
int fn_80042378(void *p, int a, unsigned int value, int extra);
int fn_800419AC(void);
Rec *fn_80047B5C(int id);
void fn_8003F014(int id, int a, int b);
void fn_80042984(void);
void fn_80042B94(int a, int id, unsigned int value, int extra);
void fn_80043000(int a, int id, unsigned int value, int extra);
void fn_8004312C(unsigned int value, int extra);
void fn_80043190(unsigned int value, int extra);
void fn_800429B8(int a, int id, unsigned int value, int extra);
void fn_80042CE4(int id, unsigned int value, int extra);
}

extern "C" void fn_8003E3AC(void *p, Src *from, Src *to, int type, float f, unsigned int value, int extra)
{
    if (fn_80435878(&lbl_80552110))
        return;
    int f24 = 0;
    int id = 0;
    if (p)
        id = fn_800B13D8(p);
    switch (type) {
    case 0x44: {
        int ok = fn_80042378(p, from->f1C, value, extra);
        if (extra == 2 && fn_800419AC()) {
            if (ok) {
                Rec *r = fn_80047B5C(fn_800B13D8(p));
                if (r)
                    r->flags |= 0x80;
            } else {
                fn_8003F014(id, 3, 0);
            }
        }
        break;
    }
    case 0x45:
        fn_80042984();
        break;
    case 0x46:
        fn_80042B94(f24, id, value, extra);
        break;
    case 0x47:
        fn_80043000(f24, id, value, extra);
        break;
    case 0x6E:
        fn_8004312C(value, extra);
        break;
    case 0x6F:
        fn_80043190(value, extra);
        break;
    case 0x70:
        fn_800429B8(f24, id, value, extra);
        break;
    case 0x71:
        fn_80042CE4(id, value, extra);
        break;
    }
}
