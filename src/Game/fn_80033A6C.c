// Resets lbl_8066D5C0 to GLOBALS field 20; docs/versus.md rows 20-21.

extern float fn_80433D20(void *record, int id, int slot);
extern void *lbl_8066C6C8;
extern float lbl_8066D5C0;

void fn_80033A6C(void)
{
    lbl_8066D5C0 = fn_80433D20(lbl_8066C6C8, 0x14, 0);
}
