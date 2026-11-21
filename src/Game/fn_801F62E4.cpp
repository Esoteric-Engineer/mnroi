// cCameraEvent: clone and the overrides of slots 51 and 54 (docs/story.md row 8, section 4.1).

inline int sn_return_decl(int a) { return a; }

struct cScript {
    char d[0x24];
    char *vptr; // +0x24
};

struct cCameraEvent : cScript { // 0x30
    int handle; // +0x28
    int active; // +0x2C
    cCameraEvent() __asm__("fn_80469C20");
};

struct Ent;

extern char lbl_80552110[]; // the game-state object G
extern char lbl_80571F34[];
extern char lbl_80572278[];
extern char lbl_8057230C[];

extern "C" {

void fn_80216E48(int on);
int fn_80130718();
void fn_8043323C(void *p, int on);
void fn_80428EEC(void *p, int handle);
Ent *fn_800ACFA8(int handle);
int fn_80095608(Ent *e);
int fn_80426AB0(void *g);

cScript *fn_801F62E4(register cCameraEvent *self)
{
    cCameraEvent *p = new cCameraEvent;

    p->handle = 0;
    p->active = 0;
    return p;
}

void fn_801F6354(register cCameraEvent *self, int a, int kind, int c, float x, float y, float z) // slot 51
{
    switch (kind) {
    case 0:
        if (self->active)
            fn_80216E48(0);
        break;
    case 3:
        if (self->active) {
            fn_80216E48(1);
            self->active = 0;
        }
        break;
    }
    return;
}

void fn_801F63F8(register cCameraEvent *self, float a, unsigned int event, int c) // slot 54
{
    switch (event) {
    case 0x309:
        if (fn_80130718())
            fn_8043323C(lbl_80572278, 1);
        else
            fn_80428EEC(lbl_80571F34, self->handle);
        break;
    case 0x14D:
        if (fn_80130718())
            fn_8043323C(lbl_80572278, 0);
        else
            fn_80428EEC(lbl_80571F34, self->handle);
        break;
    case 0x63: {
        Ent &e = *fn_800ACFA8(self->handle);

        if (&e && fn_80095608(&e) && fn_80426AB0(lbl_80552110))
            fn_8043323C(lbl_8057230C, 1);
        else
            fn_8043323C(lbl_8057230C, 0);
        break;
    }
    default:
        break;
    }
}

}
