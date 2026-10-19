// G method: tears down every slot's actor when a match ends (docs/versus.md section 5, row 25).

struct State {
    char pad[0x590];
    unsigned int slotCount; // +0x590
    char pad594[0xA8];
    int unk63C; // +0x63C
};

extern void *lbl_8066D650;
extern void *lbl_8066D654;
extern char lbl_8057E430[];
extern char lbl_805722C4[];
extern int lbl_8066B92C;

extern "C" {
void fn_80078B10(void *x);
void fn_800967A0(void *slot);
void *fn_8042FF2C(void *slot);
int fn_80086B6C(void *actor);
void fn_8009E09C(void *actor);
int fn_80432844(State *g);
void fn_8013367C();
void fn_80431480(void *x, int a);
void fn_80432DF8(void *x);

void fn_800918E0(register State *self)
{
    unsigned int i;
    void *slot;
    void *actor;

    fn_80078B10(lbl_8066D654);
    fn_80078B10(lbl_8066D650);
    for (i = 0; i < self->slotCount; i++) {
        slot = (char *)self + 0x10 + i * 0xB0;
        if (slot != 0) {
            fn_800967A0(slot);
            actor = fn_8042FF2C(slot);
            if (actor != 0 && fn_80086B6C(actor) != 0) {
                fn_8009E09C(actor);
            }
        }
    }
    if (fn_80432844(self) != 0) {
        fn_8013367C();
    }
    self->unk63C = 0;
    fn_80431480(lbl_8057E430, lbl_8066B92C);
    fn_80432DF8(lbl_805722C4);
}
}
