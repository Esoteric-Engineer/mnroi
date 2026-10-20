// Method of a class whose objects hold an actor handle at +0x48 and a value at +0x50; picks what to do with the handle by role index.

struct Obj {
    char pad0[0x48];
    int unk48; // +0x48
    char pad4C[0x4];
    int unk50; // +0x50
};

struct State {
    char pad[0x75C];
};

extern State lbl_80552110; // the game-state object G

extern "C" {
int fn_80426AB0(State *g);
int fn_802105C4(Obj *self);
int fn_80080B34();
int fn_80432870(State *g);
int fn_80432844(State *g);
int fn_800817DC(int x);
void fn_800816A0(int x);
void fn_80081AD0(int x);
void fn_8046B5A8(void *out, int x);
void fn_80082F30(void *x);

void fn_8020D104(register Obj *self)
{
    char tmp[8];

    if ((fn_80426AB0(&lbl_80552110) != 0 && fn_802105C4(self) == 0) || (fn_802105C4(self) != 0 && self->unk48 == fn_80080B34())) {
        if (fn_80432870(&lbl_80552110) != 0 || fn_80432844(&lbl_80552110) != 0) {
            if (fn_800817DC(self->unk48) == 0) {
                fn_800816A0(self->unk48);
            }
        } else {
            fn_800816A0(self->unk48);
        }
        fn_80081AD0(self->unk48);
    } else if (fn_802105C4(self) != 0) {
        fn_8046B5A8(tmp, self->unk50);
        fn_80082F30(tmp);
    }
}
}
