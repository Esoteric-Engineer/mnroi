// Sets lbl_8066D5C0 to f when it lies within GLOBALS fields 15-16.

extern float fn_80433D20(void *record, int id, int slot);
extern void *lbl_8066C6C8;
extern float lbl_8066D5C0;

void fn_8007C830(float f)
{
    if (f > fn_80433D20(lbl_8066C6C8, 0x10, 0) || f < fn_80433D20(lbl_8066C6C8, 0xF, 0))
        return;
    lbl_8066D5C0 = f;
}
