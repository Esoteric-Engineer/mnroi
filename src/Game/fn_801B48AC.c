// Registry lookup by key, 0 when absent; docs/characters.md section 3.

typedef struct Node
{
    struct Node *next; // +0x0
    struct Node *prev; // +0x4
    void *key;         // +0x8
    int pad;           // +0xC
    void *value;       // +0x10
} Node;

typedef struct Registry
{
    char name[0x20];
    int count;       // +0x20
    int bucketCount; // +0x24
    Node **buckets;  // +0x28
} Registry;

extern int fn_801B4CA0(void *key, int bucketCount);
extern Node *fn_801B4E84(Registry *reg, void *key, int hash);

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
