// Leaf accessors on small engine objects (docs/versus.md section 4.1).

typedef struct Handle
{
    int unk0;
    int unk4;
} Handle;

typedef struct Node
{
    Handle *handle; // +0x0
    int key;        // +0x4
} Node;

extern int lbl_8066BE48;

extern int fn_801B6A44(void *list);
extern const Node *fn_801B5D3C(void *list, int i);
extern void fn_80433588(Handle *h) __asm__("release__4Link");

void fn_80432CB4(register int v)
{
    lbl_8066BE48 = v;
}

void fn_80432CD8(register char *self)
{
    *(int *)(self + 0x130) = 0;
}

void fn_80432D00(register char *self, register int v)
{
    *(int *)(self + 0xC) = v;
}

void fn_80432D28(register int a, register float b, register float c)
{
}

void fn_80432D50(register int a, register float b)
{
}

int fn_80432D74(register char *self)
{
    return *(int *)(self + 0x1C0) == 13 || *(int *)(self + 0x1C0) == 14 || *(int *)(self + 0x1C0) == 15;
}

int fn_80432DCC(register char *self)
{
    return *(int *)(self + 0x178);
}

void fn_80432DF8(register void *list)
{
    Node *node;
    int i = 0;
    while (i < fn_801B6A44(list)) {
        node = fn_801B5D3C(list, i);
        fn_80433588(node->handle);
        i++;
    }
}
