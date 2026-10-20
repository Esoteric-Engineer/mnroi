// Tuning record lookup for an entity kind and name, and the record pool.

inline int sn_return_decl(int a) { return a; }

extern "C" {
int fn_801B301C(char *a, char *b);
extern char lbl_8049E524[]; // "PLAYER"
extern char lbl_8049E52C[];
void *fn_801AC988(int size, char *tag, int line, int flags);
}

struct Pool
{
    int size;    // +0x0
    char *base;  // +0x4
    char *cur;   // +0x8
    unsigned int left; // +0xC
};

extern "C" int fn_801B308C(unsigned int kind, char *name)
{
    char *prefix = 0;
    switch (kind) {
    case 0:
    case 2:
    case 7:
        prefix = lbl_8049E524;
        break;
    default:
        break;
    }
    if (prefix == 0)
        return 0;
    if (name == 0 || *name == 0)
        return 0;
    return fn_801B301C(prefix, name);
}

inline int sn_return_decl2(int a) { return a; }

extern "C" void fn_801B3168(register Pool *pool, int size)
{
    int n = (size + 3) & ~3;
    pool->size = n;
    pool->left = n;
    pool->base = (char *)fn_801AC988(n, lbl_8049E52C, 0x1B8, 2);
    pool->cur = pool->base;
}

extern "C" char *fn_801B31E4(register Pool *pool, int size)
{
    int n = (size + 3) & ~3;
    if (pool->left < (unsigned int)n)
        return 0;
    pool->left -= n;
    char *p = pool->cur;
    pool->cur += n;
    return p;
}

extern "C" {
unsigned int strlen(const char *s);
void *memcpy(void *d, const void *s, unsigned int n);
}

struct TuningSrc
{
    int type;    // +0x0
    char pad[0x1C];
    char *data;  // +0x20
};

struct TuningClass;

struct TuningOwner
{
    char pad[0x20];
    int count;            // +0x20
    struct TuningField *fields; // +0x24
    TuningClass *cls;     // +0x28
    Pool pool;            // +0x2C
};

struct TuningField
{
    int type;       // +0x0
    char pad[4];
    char *slot[6];  // +0x8
    char *data;     // +0x20
};

extern "C" void fn_801B3264(register TuningField *self, TuningOwner *owner, TuningSrc *src)
{
    self->type = src->type;
    int size = 4;
    switch (self->type) {
    case -0x2775:
        size = 4;
        break;
    case -0x2776:
        size = 4;
        break;
    case -0x2777:
    case -0x277B:
    case -0x277C:
        size = strlen(src->data) + 1;
        break;
    case -0x2778:
        size = 4;
        break;
    case -0x2779:
        size = 0x10;
        break;
    case -0x277A:
        size = 4;
        break;
    }
    self->data = fn_801B31E4(&owner->pool, size);
    memcpy(self->data, src->data, size);
    for (unsigned int i = 0; i <= 5; i++)
        self->slot[i] = self->data;
}

struct TuningClass
{
    char name[0x40];
    int count;           // +0x40
    int unk;             // +0x44
    TuningSrc *fields;   // +0x48
    int fileSize;        // +0x4C
};

extern "C" {
char *strcpy(char *d, const char *s);
extern Pool lbl_80593CF0;
}

extern "C" void fn_801B33EC(register TuningClass *self, char *name, int count, int unk)
{
    strcpy(self->name, name);
    self->count = count;
    self->fields = (TuningSrc *)fn_801B31E4(&lbl_80593CF0, count * 0x24);
    self->unk = unk;
}

extern "C" TuningSrc *fn_801B346C(register TuningClass *self, int i)
{
    if (i < 0 || i >= self->count)
        return 0;
    return self->fields + i;
}

extern "C" void fn_801B34D8(register TuningOwner *self, TuningClass *cls)
{
    fn_801B3168(&self->pool, cls->fileSize * 3);
    self->count = cls->count;
    self->fields = (TuningField *)fn_801B31E4(&self->pool, self->count * 0x24);
    for (int i = 0; i < self->count; i++)
        fn_801B3264(&self->fields[i], self, &cls->fields[i]);
    self->cls = cls;
}

extern "C" TuningField *fn_801B35CC(register TuningOwner *self, int i)
{
    if (i < 0 || i >= self->count)
        return 0;
    return self->fields + i;
}
