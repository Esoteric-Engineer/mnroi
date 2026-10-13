// Walks a node chain for the last kind-2 payload (default 4) and hands it to fn_801210F8 (docs/versus.md section 5, row 18).
typedef struct Node
{
    int kind; // +0x0
    int value; // +0x4
    struct Node *next; // +0x8
} Node;

extern char lbl_804995B0[];
extern void *fn_801210F8(void *self, char *name, int value);

void *fn_8045FB10(register void *unused, register void *target, register Node *head)
{
    int value = 4;
    Node *n = head;
    while (n) {
        if (n->kind == 2) {
            value = n->value;
        }
        n = n->next;
    }
    return fn_801210F8(target, lbl_804995B0, value);
}
