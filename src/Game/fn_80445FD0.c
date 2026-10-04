// Retries fn_804460F4 on lbl_80628B00 after fn_80446214, plus small methods; the queue is lbl_80628B00.

typedef struct
{
    float x, y, z;
    int pad0;
    float w;
    unsigned int color;
    int pad1[2];
} __attribute__((aligned(8))) QueueEntry; // 0x20 bytes

typedef struct
{
    QueueEntry e[128];
    unsigned int count; // +0x1000
} Queue;

extern Queue lbl_80628B00;

extern int fn_804460F4(Queue *self, float x, float y, int a);
extern void fn_80446214_int(int a) __asm__("fn_80446214");
extern void fn_80445F00(char *self);

void fn_80445FD0(register float x, register float y, register int a, register int b)
{
    if (fn_804460F4(&lbl_80628B00, x, y, a) != 0)
    {
        fn_80446214_int(b);
        fn_80445F00((char *)&lbl_80628B00);
        fn_804460F4(&lbl_80628B00, x, y, a);
    }
}

void fn_8044606C(register char *self)
{
    *(int *)(self + 0x1DC) = 0;
}

void fn_80446094(register char *self, register int a)
{
    *(int *)(self + 0x17C) = a;
}

int fn_804460BC(register char *self)
{
    return *(int *)(self + 4) == 3;
}

extern float lbl_8066F4DC;
extern float lbl_8066F4E0;
extern const float lbl_8048BF20[];
extern const float lbl_8048BF24[];

int fn_804460F4(register Queue *self, register float x, register float y, register int a)
{
    if (self->count > 127)
    {
        return 1;
    }
    self->e[self->count].x = x * lbl_8066F4DC;
    self->e[self->count].y = y * lbl_8066F4E0;
    self->e[self->count].z = lbl_8048BF20[0];
    self->e[self->count].w = lbl_8048BF24[0];
    self->e[self->count].color = a;
    self->e[self->count].color = (self->e[self->count].color << 8) | (unsigned char)(self->e[self->count].color >> 24);
    self->count = self->count + 1;
    return 0;
}

extern void fn_8022A0D0(char *self);
extern void fn_8022A214(char *self);
extern void fn_8022A358(char *self);

void fn_80446214(register unsigned char flags)
{
    if (flags & 1)
    {
        fn_8022A0D0((char *)&lbl_80628B00);
    }
    else if (flags & 2)
    {
        fn_8022A358((char *)&lbl_80628B00);
    }
    else
    {
        fn_8022A214((char *)&lbl_80628B00);
    }
}

int fn_80446290(register char *self)
{
    return *(int *)(self + 0x248) & 8;
}

void fn_804462C0(register char *self, register int a)
{
    if (a)
    {
        *(int *)(self + 0x248) |= 8;
    }
    else
    {
        *(int *)(self + 0x248) &= ~8;
    }
}

int fn_80446308(register char *self)
{
    return *(int *)(self + 0x448) & 1;
}

void fn_80446338(register char *self, register int a)
{
    if (a)
    {
        *(int *)(self + 0x448) |= 1;
    }
    else
    {
        *(int *)(self + 0x448) &= ~1;
    }
}

void fn_80446380(register char *self)
{
    if (++*(int *)(self + 0x450) == 9)
    {
        *(int *)(self + 0x450) = 0;
    }
}

void fn_804463C0(register char *self, register unsigned int a)
{
    register unsigned int v = a;
    if (v > 2)
    {
        v = 2;
    }
    *(unsigned int *)(self + 0x44C) = v;
}

void fn_804463F8(register char *self)
{
    *(int *)(self + 0x1DC) = 1;
}

extern void fn_8043AC1C(char *self, int a);

void fn_80446420(register char *self, register int a)
{
    fn_8043AC1C(self, a);
}

void fn_80446460(register char *self, register int a)
{
    if (a)
    {
        *(int *)(self + 0x2D8) &= ~1;
    }
    else
    {
        *(int *)(self + 0x2D8) |= 1;
    }
}

extern const float lbl_8048CD14 __attribute__((section(".rodata")));

void fn_804464A8(register float *self)
{
    self[3] = self[5]; // +0xC = +0x14
    self[6] = lbl_8048CD14; // +0x18
}
