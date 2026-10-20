// The last-selection module: the previous menu choices, kept for clashCharSelect_GetPrevCharList.
// Field meanings are in docs/versus.md section 4.2.

extern "C" {

extern int lbl_8066F178;
extern int lbl_8066F17C;
extern int lbl_8066F180;
extern int lbl_8066F184;
extern int lbl_8066F188;
extern int lbl_8066F18C;
extern int lbl_8066F190;
extern int lbl_8066F194;
extern int lbl_8066F198;
extern int lbl_8066F19C;
extern int lbl_8066F1A0;
extern int lbl_8066F1A4;

extern int lbl_8066BEF4;
extern int lbl_8066BEF8;
extern int lbl_8066BEFC;
extern int lbl_8066BF00;
extern int lbl_8066BF04;
extern int lbl_8066BF08;
extern int lbl_8066BF0C;
extern int lbl_8066BF10;
extern int lbl_8066BF14;

extern void fn_8012FEF0(int n);

inline int sn_return_decl(int a) { return a; }

void fn_801317D8(int v) { lbl_8066F178 = v; }
int fn_80131800(void) { return lbl_8066F178; }
void fn_80131828(int v) { lbl_8066F17C = v; }
int fn_80131850(void) { return lbl_8066F17C; }
void fn_80131878(int v) { lbl_8066F180 = v; }
int fn_801318A0(void) { return lbl_8066F180; }
void fn_801318C8(int v) { lbl_8066F184 = v; }
int fn_801318F0(void) { return lbl_8066F184; }

void fn_80131918(int player, int v)
{
    switch (player) {
    case 0:
        lbl_8066F188 = v;
        break;
    case 1:
        lbl_8066F194 = v;
        break;
    }
}

int fn_80131974(int player)
{
    switch (player) {
    case 0:
        return lbl_8066F188;
    case 1:
        return lbl_8066F194;
    default:
        return -1;
    }
}

void fn_801319D4(int player, int v)
{
    switch (player) {
    case 0:
        lbl_8066F18C = v;
        break;
    case 1:
        lbl_8066F198 = v;
        break;
    default:
        return;
    }
}

int fn_80131A34(int player)
{
    switch (player) {
    case 0:
        return lbl_8066F18C;
    case 1:
        return lbl_8066F198;
    default:
        return -1;
    }
}

void fn_80131A94(int player, int v)
{
    switch (player) {
    case 0:
        lbl_8066F190 = v;
        break;
    case 1:
        lbl_8066F19C = v;
        break;
    default:
        return;
    }
}

int fn_80131AF4(int player)
{
    switch (player) {
    case 0:
        return lbl_8066F190;
    case 1:
        return lbl_8066F19C;
    default:
        return -1;
    }
}

void fn_80131B54(int player, int v)
{
    switch (player) {
    case 0:
        lbl_8066F1A0 = v;
        break;
    case 1:
        lbl_8066F1A4 = v;
        break;
    default:
        return;
    }
}

int fn_80131BB4(int player)
{
    switch (player) {
    case 0:
        return lbl_8066F1A0;
    case 1:
        return lbl_8066F1A4;
    default:
        return -1;
    }
}


void fn_80131C14(int player)
{
    switch (player) {
    case 0:
        lbl_8066BF0C++;
        lbl_8066BEF4++;
        fn_8012FEF0(lbl_8066BF0C);
        break;
    case 1:
        lbl_8066BEF8++;
        break;
    default:
        return;
    }
}

void fn_80131C9C(int player)
{
    switch (player) {
    case 0:
        lbl_8066BF0C++;
        lbl_8066BEFC++;
        fn_8012FEF0(lbl_8066BF0C);
        break;
    case 1:
        lbl_8066BF00++;
        break;
    default:
        return;
    }
}

void fn_80131D24(int player)
{
    switch (player) {
    case 0:
        lbl_8066BF0C++;
        lbl_8066BF04++;
        fn_8012FEF0(lbl_8066BF0C);
        break;
    case 1:
        lbl_8066BF08++;
        break;
    default:
        return;
    }
}

int fn_80131DAC(void)
{
    int old = lbl_8066BF10;
    lbl_8066BF10 = 0;
    return old;
}

int fn_80131DE4(void)
{
    int old = lbl_8066BF14;
    lbl_8066BF14 = 0;
    return old;
}

void fn_80131E1C(void)
{
    lbl_8066F178 = -1;
    lbl_8066F17C = -1;
    lbl_8066F184 = -1;
    lbl_8066F188 = -1;
    lbl_8066F18C = -1;
    lbl_8066F190 = -1;
    lbl_8066F194 = -1;
    lbl_8066F198 = -1;
    lbl_8066F19C = -1;
    lbl_8066F1A0 = -1;
    lbl_8066F1A4 = -1;
}

}
