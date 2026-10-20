// Scales GLOBALS 22 and 23 by two getters and the frame delta into the actor's body.

extern "C" {
extern void *lbl_8066C6C8;
extern char lbl_80593BE8[];
float fn_800BB078(void *self);
float fn_800BB158(void *self);
void *fn_800CE5F4(void *self);
float fn_80433D20(void *record, int id, int slot);
float fn_8042E998(char *globals);
void fn_80446D88(void *p, float v);
void fn_80446D28(void *p, float v);
void fn_8003B268(void *p);
void fn_8003C69C(void *p);
}

extern "C" void fn_800C7AD4(register void *self)
{
    float a;
    float b;

    a = fn_800BB078(self);
    b = fn_800BB158(self);
    fn_80446D88(fn_800CE5F4(self), fn_80433D20(lbl_8066C6C8, 0x16, 0) * a * fn_8042E998(lbl_80593BE8));
    fn_80446D28(fn_800CE5F4(self), fn_80433D20(lbl_8066C6C8, 0x17, 0) * b * fn_8042E998(lbl_80593BE8));
    fn_8003B268(fn_800CE5F4(self));
    fn_8003C69C(fn_800CE5F4(self));
}
