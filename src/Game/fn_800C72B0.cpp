// Scales GLOBALS 22, 23, 19 and 67 into the actor's body and sets its flags by type.
// Owns the .rodata pool 0x8048CB40-0x8048CB48 (0.0f, 15.0f).

extern "C" {
extern void *lbl_8066C6C8;
extern char lbl_80593BE8[];
float fn_800BB078(void *self);
float fn_800BB158(void *self);
void *fn_800CE5F4(void *self);
int fn_800CC4E8(void *self);
int fn_800CC514(void *self);
int fn_800CC73C(void *self);
int fn_800CC7CC(void *self);
int fn_800CDA20(void *self);
float fn_80433D20(void *record, int id, int slot);
float fn_8042E998(char *globals);
void fn_80446C30(void *p, float v);
void fn_80446D88(void *p, float v);
void fn_80446D28(void *p, float v);
void fn_80446DE8(void *p, float v);
void fn_800396A8(void *p, int flags, float f);
void fn_8003C69C(void *p);
}

extern "C" void fn_800C72B0(register void *self)
{
    float a;
    float b;
    int flags;

    fn_80446C30(fn_800CE5F4(self), 0.0f);
    a = fn_800BB078(self);
    b = fn_800BB158(self);
    fn_80446D88(fn_800CE5F4(self), fn_80433D20(lbl_8066C6C8, 0x16, 0) * a * fn_8042E998(lbl_80593BE8));
    fn_80446D28(fn_800CE5F4(self), fn_80433D20(lbl_8066C6C8, 0x17, 0) * b * fn_8042E998(lbl_80593BE8));
    flags = 0;
    if ((fn_800CC4E8(self) & 1) || (fn_800CC514(self) & 0x40))
        flags |= 0x9004;
    if (*((unsigned char *)self + 8) == 7 || *((unsigned char *)self + 8) == 5) // +0x08 type
        flags |= 0x3020;
    if (*((unsigned char *)self + 8) == 1)
        flags |= 0x400000;
    if (*((unsigned char *)self + 8) == 7)
        flags |= 0x40;
    if (fn_800CC73C(self) && !fn_800CC7CC(self))
        flags |= 0x40000;
    if (fn_800CDA20(self)) {
        fn_80446DE8(fn_800CE5F4(self), fn_80433D20(lbl_8066C6C8, 0x13, 0) * fn_80433D20(lbl_8066C6C8, 0x43, 0));
        flags |= 0x2000200;
    }
    fn_800396A8(fn_800CE5F4(self), flags, 15.0f);
    fn_8003C69C(fn_800CE5F4(self));
}
