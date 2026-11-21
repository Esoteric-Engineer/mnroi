// cRingOut: clone and the overrides of slots 51 and 54 (docs/story.md row 8, section 4.1).

inline int sn_return_decl(int a) { return a; }

struct cScript {
    char d[0x24];
    char *vptr; // +0x24
};

struct cRingOut : cScript { // 0x2C
    int player; // +0x28, passed to fn_80443D44 and fn_80428EEC
    cRingOut() __asm__("fn_80469BD4");
};

struct Sub {
    char d[0x30];
    unsigned int flags; // +0x30
};

extern char lbl_80552110[]; // the game-state object G
extern char lbl_80571F7C[];

extern "C" {

Sub *fn_80443D44(void *g, int player);
void fn_80093D48(void *g, Sub *p, int a, int b);
void fn_80428EEC(void *p, int player);

cScript *fn_80211334(register cRingOut *self)
{
    return new cRingOut;
}

void fn_80211388(register cRingOut *self, float a, int b, int c) // slot 54
{
    fn_80428EEC(lbl_80571F7C, self->player);
}

void fn_802113D4(register cRingOut *self, int a, int kind, int c, float x, float y, float z) // slot 51
{
    switch (kind) {
    case 3:
    case 4: {
        Sub *p = fn_80443D44(lbl_80552110, self->player);

        if (p == 0)
            return;
        fn_80093D48(lbl_80552110, p, 1, 1);
        p->flags |= 2;
        break;
    }
    }
}

}
