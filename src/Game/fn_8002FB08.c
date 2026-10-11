// The static initializer of the FrameCtx file (docs/versus.md section 5, row 9d): screen-edge floats, then the FrameCtx at lbl_8052F060.
// fn_8002FC00 packs a float triple into 0xRRGGBBFF-style bytes through the 1.5 * 2^23 trick.

extern float lbl_8066B6B4; // .sdata, screen width
extern float lbl_8066B6B8; // .sdata, screen height

float lbl_8066D598 __attribute__((section(".sbss")));
float lbl_8066D59C __attribute__((section(".sbss")));
float lbl_8066D5A0 __attribute__((section(".sbss")));
float lbl_8066D5A4 __attribute__((section(".sbss")));

extern char lbl_8052F060[]; // the FrameCtx instance

extern void __8FrameCtx(char *ctx);                    // FrameCtx::FrameCtx()
extern void FrameCtxDtor(char *ctx, int inChrg) __asm__("_._8FrameCtx");

static void FrameCtxStaticInit(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            lbl_8066D598 = 320.0f - lbl_8066B6B4 * 0.5f;
            lbl_8066D59C = lbl_8066D598 + lbl_8066B6B4 * 0.5f;
            lbl_8066D5A0 = 240.0f - lbl_8066B6B8 * 0.5f;
            lbl_8066D5A4 = lbl_8066B6B8 * 0.5f + lbl_8066D5A0 - 12.0f;
            __8FrameCtx(lbl_8052F060);
        } else {
            FrameCtxDtor(lbl_8052F060, 2);
        }
    }
}

static const float sOne __attribute__((section(".rodata"))) = 1.0f; // 0x8048592C, between the two pools

int fn_8002FC00(register float *p)
{
    union {
        float f;
        int i;
    } u;
    int t;
    int c;

    c = 0xff;
    u.f = p[0] + 12582912.0f;
    t = (u.i & 0x7FFFFF) - 0x400000;
    c |= t << 16;
    u.f = p[1] + 12582912.0f;
    t = (u.i & 0x7FFFFF) - 0x400000;
    c |= t << 8;
    u.f = p[2] + 12582912.0f;
    t = (u.i & 0x7FFFFF) - 0x400000;
    c |= t;
    return c;
}

static void FrameCtxGlobalInit(void)
{
    FrameCtxStaticInit(1, 65535);
}

static void FrameCtxGlobalDest(void)
{
    FrameCtxStaticInit(0, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = FrameCtxGlobalInit;
static void (*const sDtorEntry)(void) __attribute__((section(".dtors"))) = FrameCtxGlobalDest;
