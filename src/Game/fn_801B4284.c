// The Game:Hashtables registry, chained hash tables keyed by string or int (docs/characters.md section 3).
// Owns the .rodata 0x8049E560-0x8049E620: the tag, two unread dump formats and the bucket-count primes.

typedef struct Node
{
    struct Node *next;
    struct Node *prev;
    char *key;
    int id;
    void *value;
} Node;

typedef struct Registry
{
    char name[0x20];
    int count;
    int bucketCount;
    Node **buckets;
} Registry;

extern void *fn_801AD324(int size, char *tag, int line);
extern void fn_801ACC44(void *p);
extern void *memset(void *dst, int c, unsigned n);
extern char *strncpy(char *dst, const char *src, unsigned n);
extern int strnicmp(const char *a, const char *b, int n);
extern int lbl_8066C6D8;
extern int lbl_8066C6E0; // nodes on the free list
extern int lbl_8066C6DC; // nodes ever allocated
extern struct Node *lbl_8066C6E4; // the free list
extern void fn_804673E0(void *node);

int fn_801B4DB4(register int hint);
void fn_801B4454(int n);
int fn_801B4CA0(register const char *key, register unsigned int bucketCount);
int fn_801B4D7C(register unsigned int id, register unsigned int bucketCount);
Node *fn_801B4E84(register Registry *reg, register const char *key, register int hash);
Node *fn_801B4F40(register Registry *reg, register int id, register int hash);
int fn_801B4FDC(register int n);

Registry *fn_801B4284(int hint, char *name)
{
    Registry *reg;

    reg = fn_801AD324(0x2C, "Game:Hashtables", 0x5B);
    if (reg == 0) {
        return 0;
    }
    lbl_8066C6D8 += 0x2C;
    memset(reg, 0, 0x2C);
    reg->bucketCount = fn_801B4DB4(hint);
    reg->buckets = fn_801AD324(reg->bucketCount * 4, "Game:Hashtables", 0x68);
    if (reg->buckets == 0) {
        return 0;
    }
    memset(reg->buckets, 0, reg->bucketCount * 4);
    lbl_8066C6D8 += reg->bucketCount * 4;
    strncpy(reg->name, name, 0x20);
    reg->name[0x1F] = 0;
    if (lbl_8066C6E0 == 0) {
        fn_801B4454(0x2000);
    }
    return reg;
}

__asm__(".section .rodata\n"
        "\t.asciz \"Index %d\\t (s) - '%s'\\n\"\n"
        "\t.balign 4\n"
        "\t.asciz \"Index %d\\t (r) - (%d)\\n\"\n"
        "\t.balign 4\n"
        "\t.text");

const int lbl_8049E5A0[32] = {
    23, 53, 79, 101, 151, 211, 251, 307, 353, 401, 457, 503, 557, 601, 653, 701,
    751, 809, 853, 907, 953, 1009, 1103, 1201, 1301, 1409, 1511, 1601, 1709, 1801, 1901, 1999,
};

Node *fn_801B43D8(void)
{
    Node *node;

    if (lbl_8066C6E0 == 0) {
        fn_801B4454(0x200);
    }
    node = lbl_8066C6E4;
    lbl_8066C6E4 = lbl_8066C6E4->next;
    lbl_8066C6E0--;
    memset(node, 0, 0x14);
    return node;
}

void fn_801B4454(int n)
{
    Node *nodes;
    unsigned int i;

    nodes = fn_801AD324(n * 0x14, "Game:Hashtables", 0x98);
    if (nodes == 0) {
        return;
    }
    lbl_8066C6D8 += (n * 0x14 + 0x1F) & ~0x1F;
    lbl_8066C6DC += n;
    for (i = 0; i < n; i++) {
        fn_804673E0(nodes + i);
    }
}

void fn_801B4524(Registry *reg, int check)
{
    unsigned int i;
    Node *node;
    Node *next;

    if (check && reg->count) {
    }
    i = 0;
    while (i < reg->bucketCount) {
        node = reg->buckets[i];
        while (node) {
            next = node->next;
            fn_804673E0(node);
            node = next;
        }
        i++;
    }
    lbl_8066C6D8 -= reg->bucketCount * 4 + 0x2C;
    fn_801ACC44(reg->buckets);
    fn_801ACC44(reg);
}

int fn_801B4628(Registry *reg, void *key, void *value)
{
    int hash;
    Node *head;
    Node *node;

    hash = fn_801B4CA0(key, reg->bucketCount);
    if (fn_801B4E84(reg, key, hash)) {
        return 0;
    }
    node = fn_801B43D8();
    if (node == 0) {
        return 0;
    }
    node->key = key;
    node->value = value;
    head = reg->buckets[hash];
    node->next = head;
    node->prev = 0;
    reg->buckets[hash] = node;
    if (head) {
        head->prev = node;
    }
    reg->count++;
    return 1;
}

int fn_801B4764(Registry *reg, int id, void *value)
{
    int hash;
    Node *head;
    Node *node;

    hash = fn_801B4D7C(id, reg->bucketCount);
    if (fn_801B4F40(reg, id, hash)) {
        return 0;
    }
    node = fn_801B43D8();
    if (node == 0) {
        return 0;
    }
    node->id = id;
    node->key = 0;
    node->value = value;
    head = reg->buckets[hash];
    node->next = head;
    node->prev = 0;
    reg->buckets[hash] = node;
    if (head) {
        head->prev = node;
    }
    reg->count++;
    return 1;
}

void *fn_801B48AC(Registry *reg, void *key)
{
    Node *node;
    int hash;

    hash = fn_801B4CA0(key, reg->bucketCount);
    node = fn_801B4E84(reg, key, hash);
    if (node) {
        return node->value;
    } else {
        return 0;
    }
}

void *fn_801B4938(Registry *reg, int id)
{
    Node *node;
    int hash;

    hash = fn_801B4D7C(id, reg->bucketCount);
    node = fn_801B4F40(reg, id, hash);
    if (node) {
        return node->value;
    } else {
        return 0;
    }
}

int fn_801B49C4(Registry *reg, Node *node, int hash)
{
    if (node == 0) {
        return 0;
    }
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        reg->buckets[hash] = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    fn_804673E0(node);
    reg->count--;
    return 1;
}

int fn_801B4AA8(Registry *reg, void *key)
{
    int hash;
    Node *node;

    hash = fn_801B4CA0(key, reg->bucketCount);
    node = fn_801B4E84(reg, key, hash);
    return fn_801B49C4(reg, node, hash);
}

int fn_801B4B28(Registry *reg, Node *node, void *key)
{
    return fn_801B49C4(reg, node, fn_801B4CA0(key, reg->bucketCount));
}

int fn_801B4B90(Registry *reg, int id)
{
    int hash;
    Node *node;

    hash = fn_801B4D7C(id, reg->bucketCount);
    node = fn_801B4F40(reg, id, hash);
    if (node == 0) {
        return 0;
    }
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        reg->buckets[hash] = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    fn_804673E0(node);
    reg->count--;
    return 1;
}

extern char _ctype_[];

#define TOLOWER(c) ({ int _c = (c); ((_ctype_ + 1)[_c] & 1) ? _c + 0x20 : _c; })

int fn_801B4CA0(register const char *key, register unsigned int bucketCount)
{
    unsigned int sum;
    unsigned int i;

    sum = 0;
    i = 0;
    while (i <= 0x7E && *key != 0) {
        sum += (i + 1) * TOLOWER(*key);
        key++;
        i++;
    }
    sum = sum % bucketCount;
    return sum;
}

int fn_801B4D7C(register unsigned int id, register unsigned int bucketCount)
{
    return id % bucketCount;
}

int fn_801B4DB4(register int hint)
{
    int i;
    int n;

    n = 1;
    for (i = 0; i < 32; i++) {
        if (hint < lbl_8049E5A0[i]) {
            n = lbl_8049E5A0[i];
            break;
        }
    }
    if (hint > lbl_8049E5A0[31]) {
        n = fn_801B4FDC(hint);
    }
    return n;
}

Node *fn_801B4E84(register Registry *reg, register const char *key, register int hash)
{
    Node *node;

    node = reg->buckets[hash];
    node = reg->buckets[hash];
    while (node != 0) {
        if (strnicmp(node->key, key, 0x80) == 0) {
            return node;
        }
        node = node->next;
    }
    return 0;
}

Node *fn_801B4F40(register Registry *reg, register int id, register int hash)
{
    Node *node;

    node = reg->buckets[hash];
    node = reg->buckets[hash];
    while (node != 0) {
        if (node->id == id) {
            return node;
        }
        node = node->next;
    }
    return 0;
}

int fn_801B5044(register int n);

int fn_801B4FDC(register int n)
{
    int i;

    i = n;
    while (fn_801B5044(i) == 0) {
        i++;
    }
    return i;
}

int fn_801B5044(register int n)
{
    int i;

    for (i = 2; i < n - 1; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}
