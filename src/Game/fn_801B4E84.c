// Registry bucket scan: the node in bucket <hash> whose key matches <key> (case-insensitive, 0x80 characters), 0 if none; docs/characters.md section 3.

typedef struct Node
{
    struct Node *next; // +0x0
    struct Node *prev; // +0x4
    char *key;         // +0x8
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
