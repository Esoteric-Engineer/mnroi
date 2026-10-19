// Music: puts the music object lbl_8066BE10 into state 0x22 when it is in 0x16, then into 0x10 or 0xF by its field +0x2DC. Called by both timer-mode readers (docs/versus.md section 5, row 27).

extern void *lbl_8066BE10;

extern "C" {
int fn_80457368(void *self);
void fn_8011C008(void *obj, int a);
int Get2DC(void *obj) __asm__("Get2DC__4Host");

void fn_8011A824()
{
    if (fn_80457368(lbl_8066BE10) == 0x16) {
        fn_8011C008(lbl_8066BE10, 0x22);
    }
    switch (Get2DC(lbl_8066BE10)) {
    case 0xE:
    case 0x1D:
        fn_8011C008(lbl_8066BE10, 0x10);
        break;
    default:
        fn_8011C008(lbl_8066BE10, 0xF);
        break;
    }
}
}
