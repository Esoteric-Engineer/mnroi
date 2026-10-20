// Music/mode word while no versus role index is set.

struct State {
    char pad[0x75C];
};

extern State lbl_80552110; // the game-state object G
extern void *lbl_8066BE10;
extern int lbl_8066BDF0;
extern int lbl_8066BDF8;
extern int lbl_8066BDFC;
extern int lbl_8066BE00;

extern "C" {
void fn_8011A824();
int fn_80432844(State *g);
int fn_80432870(State *g);
void fn_8011C008(void *obj, int a);

void fn_8011AC88(int a)
{
    if (fn_80432844(&lbl_80552110) || fn_80432870(&lbl_80552110)) {
        return;
    }
    if (lbl_8066BE00 == 0) {
        lbl_8066BE00 = 1;
        if (lbl_8066BDFC == 0) {
            fn_8011A824();
        }
        lbl_8066BDFC = 0;
        if (a != 0) {
            lbl_8066BDF0 = 0x13;
        } else {
            lbl_8066BDF0 = 0x12;
        }
    }
}

void fn_8011AD44(int a)
{
    if (fn_80432844(&lbl_80552110) || fn_80432870(&lbl_80552110)) {
        return;
    }
    if (lbl_8066BDF8 == 0x25) {
        return;
    }
    if (lbl_8066BE00 == 0) {
        lbl_8066BE00 = 1;
        if (lbl_8066BDFC == 0) {
            fn_8011A824();
        }
        lbl_8066BDFC = 0;
        if (a != 0) {
            lbl_8066BDF0 = 0;
        } else {
            lbl_8066BDF0 = 0x12;
        }
    }
}

void fn_8011AE10()
{
    if (fn_80432844(&lbl_80552110) || fn_80432870(&lbl_80552110)) {
        return;
    }
}

void fn_8011AE7C()
{
    if (fn_80432844(&lbl_80552110) || fn_80432870(&lbl_80552110)) {
        return;
    }
    fn_8011A824();
    lbl_8066BDFC = 1;
}

void fn_8011AEF4(int a)
{
    if (fn_80432844(&lbl_80552110) || fn_80432870(&lbl_80552110)) {
        return;
    }
    if (a != 0) {
        switch (lbl_8066BDF8) {
        case 0:
        case 0x32:
        case 0x37:
        case 0x38:
        case 0x39:
            return;
        }
    }
    fn_8011C008(lbl_8066BE10, lbl_8066BDF0);
    lbl_8066BDF0 = 0;
}
}
