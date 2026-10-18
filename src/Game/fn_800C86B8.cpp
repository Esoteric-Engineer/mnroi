// Queues an fn_8003DBF0 entry from GLOBALS 44-47 by the switch on its second argument; docs/versus.md row 21.

extern "C" {
extern char lbl_80552110[0x10]; // the game-state object G
extern void *lbl_8066C6C8;
int fn_800CE5B0(void *self);
void *fn_800CE5F4(void *self);
int fn_80426AB0(void *g);
void *fn_8043289C(void *g);
int fn_80433D70(void *record, int id, int slot);
float fn_80433D20(void *record, int id, int slot);
void fn_8003DBF0(void *p, int a, float f, int b);
void fn_8003D9C4(void *p, float f, float g, int a, int b, int c);
}

extern "C" void fn_800C86B8(register void *self, int kind)
{
    void *p;

    if (!fn_800CE5B0(self))
        return;
    p = fn_80426AB0(lbl_80552110) ? fn_800CE5F4(self) : fn_8043289C(lbl_80552110);
    if (!p)
        return;
    switch (kind) {
    case 0x6C:
    case 0x6D:
    case 0x6E:
    case 0x75:
    case 0x7D:
        fn_8003DBF0(p, fn_80433D70(lbl_8066C6C8, 0x2C, 0), fn_80433D20(lbl_8066C6C8, 0x2D, 0), 1);
        break;
    case 0x66:
    case 0x6F:
    case 0x70:
    case 0x71:
    case 0x73:
    case 0x76:
    case 0x7E:
    case 0x80:
    case 0x81:
    case 0x82:
    case 0x83:
    case 0x84:
        fn_8003DBF0(p, fn_80433D70(lbl_8066C6C8, 0x2E, 0), fn_80433D20(lbl_8066C6C8, 0x2F, 0), 1);
        break;
    case 0x72:
    case 0x7F:
        fn_8003DBF0(p, fn_80433D70(lbl_8066C6C8, 0x2E, 0), fn_80433D20(lbl_8066C6C8, 0x2F, 0), 1);
        fn_8003D9C4(p, 200.0f, 0.0f, 300, -1, 0);
        break;
    default:
        fn_8003DBF0(p, 100, 0.2f, 1);
        break;
    }
}
