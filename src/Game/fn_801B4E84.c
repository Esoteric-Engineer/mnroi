// Registry bucket scans and the bucket-count prime search; docs/characters.md section 3.

typedef struct Node
{
    struct Node *next; // +0x0
    struct Node *prev; // +0x4
    char *key;         // +0x8
    int id;            // +0xC
    void *value;       // +0x10
} Node;

typedef struct Registry
{
    char name[0x20];
    int count;       // +0x20
    int bucketCount; // +0x24
    Node **buckets;  // +0x28
} Registry;

extern int strnicmp(const char *a, const char *b, int n);

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
