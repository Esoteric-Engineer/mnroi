// CTask, the system monitor's base class (docs/core.md row 15, section 4.7).
// Owns the .rodata pools 0x8049E8F8-0x8049E920; the first word is the tail of Game/fn_801B6AF0.cpp's last string.

struct CTask
{
    unsigned char flags;
    char text[0x48] __attribute__((aligned(4)));
    char buf[0x28]; // +0x4C
    void *cb;       // +0x74
};

extern "C" {
void fn_800FE6AC(void *text, int n);
void fn_800FE7E0(void *text, int inChrg);
void *fn_800FE284(int id);
void fn_80426E88(void *text, void *font);
void fn_80101188(void *text, float size);
void fn_80100CAC(void *text, const char *s);
unsigned int fn_80100514(void *text, float scale);
void fn_8042AC20(void *text, float x, float y);
void fn_800FEB38(void *text, int a, int b, float c, int d, int e, int f, int g);
int fn_8046859C(CTask *self);
int fn_804685D0(CTask *self);
void fn_8023E850(void *cb, int a, int b, int c);
void fn_8023E930(void *cb);
void __builtin_delete(void *p);

void fn_801B6EC0(register CTask *self);
void fn_801B6F24(register CTask *self);
void fn_801B6F78(register CTask *self);
}

__asm__(".section .rodata\n\t.4byte 0x64000000\n\t.text");

extern "C" {
CTask *fn_801B6D8C(register CTask *self)
{
    self->flags = 0;
    fn_800FE6AC(self->text, 0xC8);
    return self;
}
}

__asm__(".text\n\t.globl _._5CTask\n\t.type _._5CTask,@function\n_._5CTask:");
extern "C" void fn_801B6DDC(register CTask *self, int inChrg)
{
    fn_801B6EC0(self);
    fn_800FE7E0(self->text, 2);
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}
__asm__(".size _._5CTask, 0x68");

extern "C" {
void fn_801B6E44(register CTask *self, void *cb)
{
    if (!fn_8046859C(self)) {
        self->cb = cb;
        fn_8023E850(cb, 0, 0, 0);
        self->flags |= 1;
        fn_801B6F24(self);
    }
}

void fn_801B6EC0(register CTask *self)
{
    if (fn_8046859C(self)) {
        fn_801B6F78(self);
        fn_8023E930(self->cb);
        self->flags &= ~1;
    }
}

void fn_801B6F24(register CTask *self)
{
    if (!fn_804685D0(self)) {
        self->flags |= 2;
    }
}

void fn_801B6F78(register CTask *self)
{
    if (fn_804685D0(self)) {
        self->flags &= ~2;
    }
}

void fn_801B6FCC(register CTask *self, const char *s, float *w, float *h)
{
    const char *p = s;
    char *dst = self->buf;
    int lines = 0;
    int width = 0;
    int maxw = 0;
    float height = 0.0f;
    int done;

    fn_80426E88(self->text, fn_800FE284(3));
    fn_80101188(self->text, 26.0f);
    done = 0;
    while (!done) {
        if (*p == '\n' || *p == 0) {
            *dst = 0;
            fn_80100CAC(self->text, self->buf);
            width = fn_80100514(self->text, 0.0f);
            if (maxw < width) {
                maxw = width;
            }
            lines++;
            dst = self->buf;
            done = *p == 0;
            p++;
        } else {
            *dst++ = *p++;
        }
    }
    height = lines * 26 * 1.3f;
    *w = maxw;
    *h = height;
}

void fn_801B71EC(register CTask *self, float x, float y, float z, const char *s)
{
    const char *p = s;
    char *dst = self->buf;
    int done;

    fn_80426E88(self->text, fn_800FE284(3));
    fn_80101188(self->text, 26.0f);
    done = 0;
    while (!done) {
        if (*p == '\n' || *p == 0) {
            *dst = 0;
            fn_80100CAC(self->text, self->buf);
            fn_8042AC20(self->text, x, y);
            fn_800FEB38(self->text, 0, 0xC, 0.0f, 0, -1, 0, 0);
            dst = self->buf;
            y += 33.8f;
            done = *p == 0;
            p++;
        } else {
            *dst++ = *p++;
        }
    }
}
}
