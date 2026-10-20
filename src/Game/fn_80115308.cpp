// Voice: plays the sound event (bank, event) with an extra argument unless throttled. docs/characters.md section 5.

struct Banks {
    void *fallback; // +0x0
    void *events;   // +0x4
    int bank;       // +0x8
    int event;      // +0xC
    int arg;        // +0x10
    char pad[0x4];
};

extern Banks lbl_80568DB0;
extern char lbl_80567720[];
extern char lbl_80593BE8[]; // the globals object of Game/fn_80443908.cpp
extern int lbl_8066B63C;
extern int lbl_8066BD04;
extern int lbl_8066BD0C;
extern int lbl_8066BD10;
extern int lbl_8066BD18;
extern int lbl_8066BD90;
extern void *lbl_8066F050;
extern int lbl_8066F070;

extern "C" {
int fn_80114EEC(int bank, int event);
void fn_80112214(void *rec, int bank, int flag);
int fn_800419AC(void);
void fn_80041074(void *obj, void *rec, int bank, int event, int flag);
int fn_8042EFF8(void *g);
unsigned int fn_801B4938(void *registry, unsigned int key);

void fn_80115308(int bank, int event, int arg)
{
    int result;

    if (lbl_8066B63C == 0) {
        return;
    }
    if (lbl_8066BD04 == 0) {
        return;
    }
    if (lbl_8066BD0C != 0 || lbl_8066BD10 != 0) {
        return;
    }
    if (bank == 0) {
        return;
    }
    if (fn_80114EEC(bank, event) != 0) {
        return;
    }
    if (lbl_8066BD18 != 0) {
        result = fn_8042EFF8(lbl_80593BE8) - lbl_8066BD90;
        if (result <= 2499 && result >= 0) {
            return;
        }
    }
    lbl_80568DB0.bank = bank;
    lbl_80568DB0.event = event;
    lbl_80568DB0.arg = arg;
    lbl_8066F070 = arg;
    fn_80112214(lbl_80567720, bank, 0);
    result = fn_801B4938(lbl_80568DB0.fallback, (bank << 9) | event);
    if (result == 0) {
        result = fn_801B4938(lbl_80568DB0.fallback, event | 0xFA000);
    }
    if (result != 0) {
        ((void (*)())result)();
    }
    if (fn_800419AC() != 0) {
        fn_80041074(lbl_8066F050, lbl_80567720, bank, event, arg);
    }
}
}
