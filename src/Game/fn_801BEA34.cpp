// Random point in the unit ball, two matrix wrappers, and the axis vectors' static init (docs/core.md row 17).
// Defines lbl_80593DC0-lbl_80593E00 (+X, +Y, +Z, -Z, zero; w = 1) and the Vec2 lbl_8066F528.

struct Vector
{
    float x, y, z, w;
};

struct Vec2
{
    float x, y;
};

class Mat
{
public:
    float m[16];
    Mat() __asm__("fn_8042D7B0");
};

extern "C" {
float *fn_8042FB28(Vector *v);
int fn_80171F8C(void);
float fn_8042EC54(Vector *v);
void fn_804342EC(Mat *m, void *src);
void fn_80434368(void *a, void *b, Mat *m);
void fn_80435754(void *a, Mat *m);
void fn_8042D768(Vector *v, float x, float y, float z, float w);
void fn_8042ACC0(Vec2 *v, float x, float y);

Vector lbl_80593DC0;
Vector lbl_80593DD0;
Vector lbl_80593DE0;
Vector lbl_80593DF0;
Vector lbl_80593E00;
Vec2 lbl_8066F528;

void fn_801BEA34(Vector *v)
{
again:
    fn_8042FB28(v)[0] = (float)fn_80171F8C() * 4.656613e-10f * 2.0f - 1.0f;
    fn_8042FB28(v)[1] = (float)fn_80171F8C() * 4.656613e-10f * 2.0f - 1.0f;
    fn_8042FB28(v)[2] = (float)fn_80171F8C() * 4.656613e-10f * 2.0f - 1.0f;
    if (fn_8042EC54(v) > 1.0)
        goto again;
}

void fn_801BEBBC(void *a, void *b, void *src)
{
    Mat m;
    fn_804342EC(&m, src);
    fn_80434368(a, b, &m);
}

void fn_801BEC2C(void *a, void *src)
{
    Mat m;
    fn_804342EC(&m, src);
    fn_80435754(a, &m);
}
}

__asm__(".section .rodata\n"
        "\t.long 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068, 0x6F727068\n"
        "\t.long 0x6F727068\n"
        "\t.text"); // 0x8049EC98-0x8049ECBC, linkonce pool copies

static void __static_initialization_and_destruction_0(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            fn_8042D768(&lbl_80593DC0, 1.0f, 0.0f, 0.0f, 1.0f);
            fn_8042D768(&lbl_80593DD0, 0.0f, 1.0f, 0.0f, 1.0f);
            fn_8042D768(&lbl_80593DE0, 0.0f, 0.0f, 1.0f, 1.0f);
            fn_8042D768(&lbl_80593DF0, 0.0f, 0.0f, -1.0f, 1.0f);
            fn_8042D768(&lbl_80593E00, 0.0f, 0.0f, 0.0f, 1.0f);
            fn_8042ACC0(&lbl_8066F528, 0.0f, 0.0f);
        } else {
        }
    }
}

extern "C" {
void fn_801BEDE8(void)
{
    __static_initialization_and_destruction_0(1, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_801BEDE8;
}
