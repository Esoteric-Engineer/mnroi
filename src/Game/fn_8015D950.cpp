// The 28 task constructors, task ids 0-27 in order: base task fn_8015294C, then the task's vtable (docs/ai.md row 3).

struct TaskSelf {
    char d[0x24];
    void *vtable; // +0x24
};

extern "C" {
TaskSelf *fn_8015294C(TaskSelf *self, void *ai, int id);
void fn_80428F74(void *v) __asm__("__6Vector");
extern char lbl_804F62E8[];
extern char lbl_804F62B0[];
extern char lbl_804F6278[];
extern char lbl_804F6240[];
extern char lbl_804F6208[];
extern char lbl_804F61D0[];
extern char lbl_804F6198[];
extern char lbl_804F6160[];
extern char lbl_804F6128[];
extern char lbl_804F60F0[];
extern char lbl_804F60B8[];
extern char lbl_804F6080[];
extern char lbl_804F6048[];
extern char lbl_804F6010[];
extern char lbl_804F5FD8[];
extern char lbl_804F5FA0[];
extern char lbl_804F5F68[];
extern char lbl_804F5F30[];
extern char lbl_804F5EF8[];
extern char lbl_804F5EC0[];
extern char lbl_804F5E88[];
extern char lbl_804F5E50[];
extern char lbl_804F5E18[];
extern char lbl_804F5DE0[];
extern char lbl_804F5DA8[];
extern char lbl_804F5D70[];
extern char lbl_804F5D38[];
extern char lbl_804F5D00[];
}

extern "C" TaskSelf *fn_8015D950(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 0);
    self->vtable = (void *)lbl_804F62E8;
    return self;
}

extern "C" TaskSelf *fn_8015D9A8(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 1);
    self->vtable = (void *)lbl_804F62B0;
    return self;
}

extern "C" TaskSelf *fn_8015DA00(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 2);
    self->vtable = (void *)lbl_804F6278;
    return self;
}

extern "C" TaskSelf *fn_8015DA58(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 3);
    self->vtable = (void *)lbl_804F6240;
    return self;
}

extern "C" TaskSelf *fn_8015DAB0(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 4);
    self->vtable = (void *)lbl_804F6208;
    return self;
}

extern "C" TaskSelf *fn_8015DB08(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 5);
    self->vtable = (void *)lbl_804F61D0;
    return self;
}

extern "C" TaskSelf *fn_8015DB60(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 6);
    self->vtable = (void *)lbl_804F6198;
    return self;
}

extern "C" TaskSelf *fn_8015DBB8(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 7);
    self->vtable = (void *)lbl_804F6160;
    return self;
}

extern "C" TaskSelf *fn_8015DC10(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 8);
    self->vtable = (void *)lbl_804F6128;
    return self;
}

extern "C" TaskSelf *fn_8015DC68(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 9);
    self->vtable = (void *)lbl_804F60F0;
    return self;
}

extern "C" TaskSelf *fn_8015DCC0(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 10);
    self->vtable = (void *)lbl_804F60B8;
    return self;
}

extern "C" TaskSelf *fn_8015DD18(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 11);
    self->vtable = (void *)lbl_804F6080;
    fn_80428F74((char *)self + 0x30); // Vector member
    return self;
}

extern "C" TaskSelf *fn_8015DD7C(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 12);
    self->vtable = (void *)lbl_804F6048;
    return self;
}

extern "C" TaskSelf *fn_8015DDD4(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 13);
    self->vtable = (void *)lbl_804F6010;
    return self;
}

extern "C" TaskSelf *fn_8015DE2C(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 14);
    self->vtable = (void *)lbl_804F5FD8;
    return self;
}

extern "C" TaskSelf *fn_8015DE84(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 15);
    self->vtable = (void *)lbl_804F5FA0;
    return self;
}

extern "C" TaskSelf *fn_8015DEDC(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 16);
    self->vtable = (void *)lbl_804F5F68;
    return self;
}

extern "C" TaskSelf *fn_8015DF34(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 17);
    self->vtable = (void *)lbl_804F5F30;
    return self;
}

extern "C" TaskSelf *fn_8015DF8C(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 18);
    self->vtable = (void *)lbl_804F5EF8;
    return self;
}

extern "C" TaskSelf *fn_8015DFE4(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 19);
    self->vtable = (void *)lbl_804F5EC0;
    return self;
}

extern "C" TaskSelf *fn_8015E03C(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 20);
    self->vtable = (void *)lbl_804F5E88;
    return self;
}

extern "C" TaskSelf *fn_8015E094(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 21);
    self->vtable = (void *)lbl_804F5E50;
    return self;
}

extern "C" TaskSelf *fn_8015E0EC(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 22);
    self->vtable = (void *)lbl_804F5E18;
    return self;
}

extern "C" TaskSelf *fn_8015E144(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 23);
    self->vtable = (void *)lbl_804F5DE0;
    return self;
}

extern "C" TaskSelf *fn_8015E19C(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 24);
    self->vtable = (void *)lbl_804F5DA8;
    return self;
}

extern "C" TaskSelf *fn_8015E1F4(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 25);
    self->vtable = (void *)lbl_804F5D70;
    return self;
}

extern "C" TaskSelf *fn_8015E24C(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 26);
    self->vtable = (void *)lbl_804F5D38;
    return self;
}

extern "C" TaskSelf *fn_8015E2A4(register TaskSelf *self, register void *ai)
{
    fn_8015294C(self, ai, 27);
    self->vtable = (void *)lbl_804F5D00;
    return self;
}
