// String helpers and the string hash table stdVar keeps its variables in (docs/core.md row 10).

extern "C" const char _ctype_[];

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_801ACB7C(void *dst, int c, int n);

struct Node
{
    int hash;
    void *value;
    Node *next;
    const char *key;
};

struct Table
{
    int mask;
    int seed;
    int owned;
    Node *nodes;
    Node **buckets;
    Node *free;
};

extern "C" Table *fn_801B753C(void *mem, int bytes, int n);
extern "C" int fn_801B7670(int n, int *count);
extern "C" Node *fn_801B7900(Table *t, const char *key, int *hp);
extern "C" Node *fn_801B79E0(Table *t);

extern "C" void fn_801B738C(char *s)
{
    while (*s != 0) {
        *s = ({ int x = *s; ((_ctype_ + 1)[x] & 1) ? x - 'A' + 'a' : x; });
        s++;
    }
}

extern "C" int fn_801B741C(const char *s, int seed)
{
    int h = seed;
    int c;
    const unsigned char *p = (const unsigned char *)s;

    for (;;) {
        c = *p++;
        h = (h << 5) + h + c;
        if (c == 0) {
            break;
        }
    }
    return h;
}

extern "C" Table *fn_801B74AC(int count, int unused)
{
    void *mem;
    int bytes;
    int n;
    Table *t;

    bytes = fn_801B7670(count, &n);
    mem = new char[bytes];
    t = fn_801B753C(mem, bytes, n);
    t->owned = 1;
    return t;
}

extern "C" Table *fn_801B753C(void *mem, int bytes, int n)
{
    Table *t;
    int size = fn_801B7670(n, 0);
    fn_801ACB7C(mem, 0, bytes);
    t = (Table *)mem;
    t->mask = n - 1;
    t->nodes = (Node *)((char *)mem + sizeof(Table));
    t->buckets = (Node **)((char *)mem + (n * sizeof(Node) + sizeof(Table)));
    t->free = t->nodes;
    int i = 0;
    while (i < n - 1) {
        t->nodes[i].next = &t->nodes[i + 1];
        i++;
    }
    t->seed = 0x1505;
    return t;
}

extern "C" int fn_801B7670(int n, int *count)
{
    int size;
    int p = 1;

    while (p < n) {
        p <<= 1;
    }
    size = p * sizeof(Node) + sizeof(Table) + p * sizeof(Node *);
    if (count != 0) {
        *count = p;
    }
    return size;
}

extern "C" int fn_801B7708(Table *t, const char *key, void *value)
{
    Node *e;
    int h;

    e = fn_801B7900(t, key, &h);
    if (e == 0) {
        e = fn_801B79E0(t);
        if (e == 0) {
            return 2;
        }
        e->next = t->buckets[h & t->mask];
        t->buckets[h & t->mask] = e;
        e->key = key;
        e->hash = h;
        e->value = value;
        return 1;
    } else {
        e->value = value;
        return 0;
    }
}

extern "C" void *fn_801B782C(Table *t, const char *key)
{
    Node *e;
    int h;

    h = fn_801B741C(key, t->seed);
    e = t->buckets[h & t->mask];
    while (e != 0 && h != e->hash) {
        e = e->next;
    }
    if (e == 0) {
        return 0;
    }
    return e->value;
}

extern "C" Node *fn_801B7900(Table *t, const char *key, int *hp)
{
    Node *e;
    int h;

    if (hp == 0) {
        hp = &h;
    }
    *hp = fn_801B741C(key, t->seed);
    e = t->buckets[*hp & t->mask];
    while (e != 0 && *hp != e->hash) {
        e = e->next;
    }
    return e;
}

extern "C" Node *fn_801B79E0(Table *t)
{
    Node *e = t->free;
    if (t->free != 0) {
        t->free = t->free->next;
    }
    e->next = 0;
    return e;
}
