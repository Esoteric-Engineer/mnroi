// The game.nfx loader: one `<type> <name>` header per block, whose keys fn_803A3578 reads; docs/characters.md "Effects".
// The real name is unknown, so the symbol stays extern "C".

struct EffectCache
{
    void *head;     // +0x0
    void *tail;     // +0x4
    char pad8[8];
    void *buffer;   // +0x10
    int count;      // +0x14
    char pad18[4];
    int loaded;     // +0x1C
};

extern char lbl_8064E470[0x200];
extern const char lbl_804BC654[];
extern const char lbl_804BC65C[];
extern const char lbl_804BC674[];
extern const char lbl_804BC680[];

extern "C" {
void *fn_801AC988(unsigned size, const char *tag, int line, int align);
void *fn_801A8368(const char *name, const char *mode, int flags);
void fn_801A953C(void *file);
int fn_801A8C84(void *file);
int fn_801A8C08(char *buf, int size, void *file);
void fn_801A875C(void *file);
char *strtok(char *s, const char *delim);
int fn_80480344(const char *name);
void *fn_803A3224(EffectCache *self, const char *name, int type);
int fn_803A3578(EffectCache *self, void *file, int a, int b);
}

extern "C" int fn_803A38DC(register EffectCache *self)
{
    int line;
    char *tok;
    int type;
    int ok;
    void *file;

    if (self->loaded) {
        return 1;
    }
    line = -1;
    ok = 1;
    self->count = 0;
    if (self->buffer == 0) {
        self->buffer = fn_801AC988(300000, lbl_804BC65C, 0xEDE, 2);
    }
    file = fn_801A8368(lbl_804BC674, lbl_804BC680, 9);
    if (file == 0) {
        return 0;
    }
    fn_801A953C(file);
    while (!fn_801A8C84(file)) {
        line++;
        if (fn_801A8C08(lbl_8064E470, 0x1FF, file) == 0) {
            break;
        }
        if (lbl_8064E470[0] == ';') {
            continue;
        }
        tok = strtok(lbl_8064E470, lbl_804BC654);
        if (tok == 0) {
            continue;
        }
        type = fn_80480344(tok);
        if (type < 0) {
            continue;
        }
        tok = strtok(0, lbl_804BC654);
        if (tok == 0) {
            continue;
        }
        fn_803A3224(self, tok, type);
        fn_803A3578(self, file, 0, 0);
    }
    fn_801A875C(file);
    self->loaded = 1;
    return 1;
}
