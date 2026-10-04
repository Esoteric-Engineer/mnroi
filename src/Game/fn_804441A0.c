// Small methods of the handle-class family after fn_804440B0; class names and layouts are guesses.

extern char lbl_804F4C80[];
extern const float lbl_8048A830[]; // 0.0f, in another unit's .rodata pool

extern void fn_8042A514(void *self, void *name);
extern void fn_80428FA8(void *v, float x, float y, float z);
extern void fn_800ACA34(void *self, int a);
extern void fn_804443E8(void *self, int a);
extern int fn_800B0C58(void *p);
extern void *fn_800B14A0(void *p);
extern int fn_80085E8C(void *p);
extern int fn_80444544(char *p);
extern int fn_80426AB0(void *g);
extern int fn_80444CA4(void *p);
extern int lbl_8066B664;
extern char lbl_8052F060[];
extern char lbl_80552110[]; // G

typedef struct GameState
{
    char pad[0x640];
    int field640;
} GameState;

void fn_804441A0(register char *self, register void *name)
{
    *(char **)(self + 4) = lbl_804F4C80;
    fn_8042A514(self, name);
}

int fn_804441EC(register char *self)
{
    return *(int *)(self + 0x14);
}

void fn_80444218(register char *self, register int a)
{
    ((void (*)(void *, int))(*(void **)(self + 0x10)))(*(char **)(self + 8) + *(short *)(self + 0xC), a);
    return;
}

void fn_8044427C(register void *self, register int a)
{
    fn_804443E8(self, a);
}

float fn_804442BC(register char *self, register float x)
{
    return *(float *)(self + 0x28) / x;
}

void fn_804442F0(register char *self, register float s)
{
    fn_80428FA8(self + 0x20, s, s, s);
    if (s != lbl_8048A830[0])
        *(unsigned int *)(self + 4) |= 0x800;
    else
        *(unsigned int *)(self + 4) &= ~0x800;
}

int fn_80444370(register char *self, register char slot)
{
    if (*(int *)(self + 0xE8) != -1)
        return slot == *(int *)(self + 0xE8);
    if ((1 << slot) & *(unsigned int *)(self + 0x40))
        return 0;
    return 1;
}

void fn_804443E8(register void *self, register int a)
{
    fn_800ACA34(self, a);
}

float fn_80444428(register char *self)
{
    return *(float *)(self + 0x2C);
}

int fn_80444454(register void *p)
{
    if (lbl_8066B664 == 0)
        return 0;
    if (!fn_800B0C58(p) || !fn_80085E8C(fn_800B14A0(p)))
        return 0;
    if (fn_80444544(lbl_8052F060))
        return 1;
    if (fn_80426AB0(lbl_80552110)) {
        return ((GameState *)lbl_80552110)->field640 != -1;
    } else {
        return 1;
    }
}

int fn_80444544(register char *self)
{
    return *(int *)(self + 0x3D0);
}

int fn_80444570(register char *self)
{
    return *(unsigned short *)(self + 4) & 0x10;
}

int fn_804445A4(register char *self)
{
    return *(unsigned short *)(self + 4) & 0x200;
}

int fn_804445D8(register char *self)
{
    return *(unsigned short *)(self + 4) & 0x400;
}

char *fn_8044460C(register char *self)
{
    return self + 0x10;
}

void fn_80444638(register char *self, register int on)
{
    if (on)
        *(unsigned short *)(self + 4) |= 0x1000;
    else
        *(unsigned short *)(self + 4) &= ~0x1000;
}

char *fn_80444688(register char *self)
{
    return self + 0x10;
}

void fn_804446B4(register char *self, register void *p)
{
    if (p)
        *(short *)(self + 0x20) = fn_80444CA4(p);
    else
        *(short *)(self + 0x20) = -1;
}

int fn_80444710(register char *self)
{
    return *(unsigned char *)(self + 0x22);
}

int fn_80444740(register char *self)
{
    return *(unsigned char *)(self + 0x2A);
}
