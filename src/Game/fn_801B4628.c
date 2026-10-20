// Registry add (drops a duplicate key); docs/characters.md section 3.

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
extern Node *fn_801B43D8(void);

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
