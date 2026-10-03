extern float lbl_8066BA24; // .sdata, screen width
extern float lbl_8066BA28; // .sdata, screen height

// 0x8066D6AC-0x8066D6BC. Defining them here is what keeps mwld from dead-stripping the object:
// lbl_8066D6B4 is the only symbol in it anything outside references.
float lbl_8066D6AC __attribute__((section(".sbss")));
float lbl_8066D6B0 __attribute__((section(".sbss")));
float lbl_8066D6B4 __attribute__((section(".sbss")));
float lbl_8066D6B8 __attribute__((section(".sbss")));

extern char lbl_80552920[]; // the GameFlow instance

extern void fn_800B43F0(char *flow);             // GameFlow::GameFlow()
extern void fn_800B4634(char *flow, int inChrg); // GameFlow::~GameFlow()

static void GameFlowStaticInit(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            lbl_8066D6AC = 320.0f - lbl_8066BA24 * 0.5f;
            lbl_8066D6B0 = lbl_8066D6AC + lbl_8066BA24 * 0.5f;
            lbl_8066D6B4 = 240.0f - lbl_8066BA28 * 0.5f;
            lbl_8066D6B8 = lbl_8066BA28 * 0.5f + lbl_8066D6B4 - 12.0f;
            fn_800B43F0(lbl_80552920);
        } else {
            fn_800B4634(lbl_80552920, 2);
        }
    }
}

// 65535 is GCC 2.95's default init priority.
static void GameFlowGlobalInit(void)
{
    GameFlowStaticInit(1, 65535);
}

static void GameFlowGlobalDest(void)
{
    GameFlowStaticInit(0, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = GameFlowGlobalInit;
static void (*const sDtorEntry)(void) __attribute__((section(".dtors"))) = GameFlowGlobalDest;
