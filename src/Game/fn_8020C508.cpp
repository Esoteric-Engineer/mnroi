// Event method of the class that plays "tripwireDamFX": fires once per object (+0x30) for an actor event, else records the event (+0x40/+0x44).
// Float pool through extern_pool at 0x804A1BB8; the "tripwireDamFX" string stays dtk's lbl_804A1BA4.

inline int sn_return_decl(int a) { return a; }

struct Obj {
    char pad0[0x28];
    int unk28; // +0x28
    int unk2C; // +0x2C
    int fired; // +0x30
    char pad34[0xC];
    int unk40; // +0x40
    int unk44; // +0x44
    int unk48; // +0x48
    int unk4C; // +0x4C
};

extern char lbl_80552110[]; // the game-state object G
extern char lbl_80571FA0[];
extern char lbl_804A1BA4[]; // "tripwireDamFX"
extern int lbl_8066C724;

extern "C" {
void fn_8046B638(void *ev, int x);
int fn_8046CBB8(void *ev);
int fn_8046C96C(void *ev);
int fn_800809CC(void *ev);
int fn_80080A44(void *ev);
void fn_80082E90(void *ev, char *name, int a, int b);
int fn_8021044C(Obj *self);
float fn_802101EC(Obj *self);
int fn_802103BC(Obj *self);
int fn_80210524(Obj *self);
void fn_8020D31C(Obj *self, int x, int y);
int fn_80426AB0(void *g);
int fn_80432844(void *g);
int fn_80432870(void *g);
int fn_80443D44(void *g, int player);
int fn_8043B31C(int x);
void fn_8046B838(void *g, int x);
void fn_80081918(int x);
int fn_80085AF0(int actor);
int fn_80085EEC(int actor);
int fn_80085F1C(int actor);
int fn_80085954(int actor);
int fn_80085928(int actor);
int fn_80085D3C(int actor);
void fn_80086CDC(int actor, int on);
int fn_800CD064(int x);
int fn_800CE1B0(int x);
int fn_800CC70C(int x);
int fn_800C9FD0(int x);
int fn_800CD0EC(int x);
int fn_800CDA20(int x);
void fn_800F9754(int x);
int fn_800B14C8(int x);
int fn_800B0C1C(int x);
int fn_800B13D8(int actor);
int fn_80171F8C(void);
void fn_800528EC(void);
int fn_800ACD20(int actor, int id);
void fn_800578E4(int a, Obj *self, int b, int actor, int flags, int c, int d);
void fn_80432DF8(void *x);
void fn_800964D0(int x);

void fn_8020C508(register Obj *self, int a, int id, int c)
{
    char ev[8];

    fn_8046B638(ev, id);
    if (!fn_8046CBB8(ev))
        return;
    if (fn_8021044C(self) > 0 && !fn_8046C96C(ev)) {
        int actor = fn_800809CC(ev);
        if (!actor)
            return;
        if (fn_8021044C(self) == 2 && !fn_80080A44(ev))
            return;
        if (fn_80426AB0(lbl_80552110) && lbl_8066C724) {
            fn_80081918(id);
            return;
        }
        if (fn_80432844(lbl_80552110) || fn_80432870(lbl_80552110)) {
            if (fn_80085AF0(actor)) {
                int other = fn_80443D44(lbl_80552110, 1 - fn_8043B31C(fn_80085AF0(actor)));
                if (other) {
                    if (fn_80085EEC(other) || fn_80085F1C(other))
                        return;
                }
            }
        }
        fn_80086CDC(actor, 1);
        if (fn_80085EEC(actor))
            return;
        int x = fn_80085954(actor);
        if (x && fn_800CD064(x) && fn_800CE1B0(x) && !fn_800CC70C(x)) {
            int rider = fn_800B14C8(fn_800C9FD0(x));
            if (rider && fn_800B0C1C(rider) && fn_80085928(rider) && fn_800CD0EC(fn_80085928(rider))) {
                if ((fn_80426AB0(lbl_80552110) && fn_80085D3C(rider)) || fn_80085AF0(rider)) {
                    fn_80086CDC(actor, 0);
                    self->unk4C = fn_800B13D8(actor);
                    actor = rider;
                    fn_80086CDC(actor, 1);
                }
            }
        }
        if (self->fired)
            return;
        self->fired = 1;
        if (self->unk4C)
            fn_80081918(self->unk4C);
        if (fn_80426AB0(lbl_80552110)) {
            int flags = 0x200210;
            float r = fn_80171F8C() * 4.6566128730773926e-10f;
            if (r < 0.33f)
                flags |= 0x80;
            else if (r < 0.66f)
                flags |= 0x100;
            int y = fn_80085928(actor);
            if (y && fn_800CDA20(y))
                fn_800F9754(y);
            fn_800528EC();
            fn_800578E4(fn_800ACD20(actor, 0xdc), self, 0, actor, flags, 0, 999);
            fn_80432DF8(lbl_80571FA0);
            self->unk48 = fn_800B13D8(actor);
            fn_8046B838(lbl_80552110, 0);
        } else {
            if (fn_80085AF0(fn_800809CC(ev)))
                fn_800964D0(fn_80085AF0(actor));
        }
    } else {
        if (fn_80080A44(ev)) {
            self->unk2C = 1;
            if (self->unk40 == 0)
                self->unk40 = id;
            else if (self->unk44 == 0)
                self->unk44 = id;
        }
        if (self->unk28 == 0)
            return;
        if (fn_802101EC(self) > 0.0f || (fn_802101EC(self) < 0.0f && fn_80210524(self))) {
            if (fn_802103BC(self) == 5)
                fn_80082E90(ev, lbl_804A1BA4, 0xff, 0xff);
            fn_8020D31C(self, id, 0);
        }
    }
}
}
