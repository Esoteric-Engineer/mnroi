// KVList and KSList, the string-keyed Game:List subclasses, and their nodes; docs/core.md row 8.
// Owns the .rodata from 1.0f (0x8049E620).

inline int sn_return_decl(int a) { return a; }

class VList {
public:
    char data[0x20];
    virtual ~VList();                       // +0x08
    virtual int add(void *item);            // +0x10
    virtual int v18(void *a, void *b);      // +0x18
    virtual int v20(void *a);               // +0x20
    virtual int set(char *key, void *val);  // +0x28
    virtual int remove(char *key);          // +0x30
    virtual int setStr(char *key, char *s); // +0x38
};

struct KV {
    char data[0x20];
    const void *vptr;
};

struct KVNode {
    char *key;
    void *value;
};

struct KSNode {
    char *key;
    char *value;
};

class NewKV {
public:
    char b[8];
    NewKV(char *key, void *value) __asm__("fn_801B5400");
};

class NewKS {
public:
    char b[8];
    NewKS(char *key, char *value) __asm__("fn_801B59F0");
};

extern "C" {
extern char lbl_804F6978[]; // KVList
extern char lbl_804F6908[]; // KSList
void fn_801B5BA8(KV *list, int cap, float grow);
void fn_801B5C74(KV *list, int inChrg);
void fn_801B5E38(KV *list, int n);
int fn_801B6040(KV *list, void *item);
void fn_801B60F4(KV *list);
void fn_801B6130(KV *list, int i);
int fn_801B686C(KV *list, char *key, int start);
void fn_801B6950(KV *list, int on);
void fn_801B69E4(KV *list, void (*fn)(int, void *));
void fn_801B6A0C(KV *list, float grow);
void fn_801B6A70(KV *list, int (*fn)(void *, char *));
void fn_801B6A98(KV *list, int (*fn)(void *, void *));
void *fn_801AC988(unsigned int size, const char *tag, int line, int kind);
char *fn_80467468(void *node);
float *fn_8042FB28(void *v);
void fn_free(void *p) __asm__("realloc"); // SN's free stub (docs/prodg.md)
void __builtin_delete(void *p);
int strcmp(const char *a, const char *b);
unsigned int strlen(const char *s);
char *strcpy(char *d, const char *s);
int sprintf(char *buf, const char *fmt, ...);

void fn_801B52DC(int op, void *node);
int fn_801B5338(void *a, void *b);
int fn_801B539C(void *node, char *key);
void fn_801B5484(register KVNode *self, int inChrg);
void fn_801B5994(int op, void *node);
void fn_801B5AA8(register KSNode *self, int inChrg);

KV *fn_801B50BC(register KV *self, int n, float grow)
{
    fn_801B5BA8(self, 4, 1.0f);
    self->vptr = lbl_804F6978;
    fn_801B5E38(self, n);
    fn_801B6A0C(self, grow);
    fn_801B69E4(self, fn_801B52DC);
    fn_801B6A98(self, fn_801B5338);
    fn_801B6950(self, 1);
    fn_801B6A70(self, fn_801B539C);
    return self;
}

void fn_801B5170(register KV *self, int inChrg)
{
    self->vptr = lbl_804F6978;
    fn_801B60F4(self);
    fn_801B5C74(self, inChrg);
}

int fn_801B51C4(register KV *self, char *key, void *value)
{
    ((VList *)self)->remove(key);
    void *node = new NewKV(key, value);
    return fn_801B6040(self, node);
}

int fn_801B5268(register KV *self, char *key)
{
    int i = fn_801B686C(self, key, 0);
    if (i != -1)
        fn_801B6130(self, i);
    return i;
}

void fn_801B52DC(int op, void *node)
{
    if (op == 1 && node != 0)
        fn_801B5484((KVNode *)node, 3);
    else
    {
    }
}

int fn_801B5338(void *a, void *b)
{
    return strcmp(fn_80467468(a), fn_80467468(b));
}

int fn_801B539C(void *node, char *key)
{
    return strcmp(fn_80467468(node), key) == 0;
}

KVNode *fn_801B5400(register KVNode *self, char *key, void *value)
{
    self->key = (char *)fn_801AC988(strlen(key) + 1, "Game:KVList", 209, 1);
    strcpy(self->key, key);
    self->value = value;
    return self;
}

void fn_801B5484(register KVNode *self, int inChrg)
{
    if (self->key)
        fn_free(self->key);
    if (inChrg & 1)
        __builtin_delete(self);
    else
    {
    }
}

KV *fn_801B54E8(register KV *self, int n, float grow)
{
    fn_801B50BC(self, n, grow);
    self->vptr = lbl_804F6908;
    fn_801B69E4(self, fn_801B5994);
    return self;
}

int fn_801B5554(register KV *self, char *key, char *value)
{
    if (key == 0 || value == 0)
        return -1;
    ((VList *)self)->remove(key);
    void *node = new NewKS(key, value);
    return fn_801B6040(self, node);
}

int fn_801B561C(register KV *self, char *key, float value)
{
    char buf[0x50];
    sprintf(buf, "%f", value);
    return ((VList *)self)->setStr(key, buf);
}

int fn_801B56BC(register KV *self, char *key, unsigned int value)
{
    char buf[0x50];
    sprintf(buf, "%u", value);
    return ((VList *)self)->setStr(key, buf);
}

int fn_801B5754(register KV *self, char *key, int value)
{
    char buf[0x50];
    sprintf(buf, "%d", value);
    return ((VList *)self)->setStr(key, buf);
}

int fn_801B57EC(register KV *self, char *key, void *value)
{
    char buf[0x50];
    sprintf(buf, "%f %f %f", fn_8042FB28(value)[0], fn_8042FB28(value)[1], fn_8042FB28(value)[2]);
    return ((VList *)self)->setStr(key, buf);
}

int fn_801B58D8(register KV *self, char *key, int value)
{
    char buf[0x50];
    if (value)
        sprintf(buf, "1");
    else
        sprintf(buf, "0");
    return ((VList *)self)->setStr(key, buf);
}

void fn_801B5994(int op, void *node)
{
    if (op == 1 && node != 0)
        fn_801B5AA8((KSNode *)node, 3);
    else
    {
    }
}

inline const char *sn_empty() { return ""; }

KSNode *fn_801B59F0(register KSNode *self, char *key, char *value)
{
    self->key = (char *)fn_801AC988(strlen(key) + 1, "Game:KSList", 428, 1);
    strcpy(self->key, key);
    self->value = (char *)fn_801AC988(strlen(value) + 1, "Game:KSList", 431, 1);
    strcpy(self->value, value);
    return self;
}

void fn_801B5AA8(register KSNode *self, int inChrg)
{
    if (self->key)
        fn_free(self->key);
    if (self->value)
        fn_free(self->value);
    if (inChrg & 1)
        __builtin_delete(self);
    else
    {
    }
}

int fn_801B5B20(register void *self, register void *a)
{
    return -1;
}

int fn_801B5B4C(register void *self, register void *a, register void *b)
{
    return -1;
}

int fn_801B5B7C(register void *self, register void *a)
{
    return -1;
}
}
