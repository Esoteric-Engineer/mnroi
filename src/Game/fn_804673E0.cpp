// The Game:Hashtables registry's inline function (docs/core.md row 18).

struct Node {
    Node *next;
    int f4;
};

extern "C" {
extern int lbl_8066C6E0;
extern Node *lbl_8066C6E4;

void fn_804673E0(register Node *node)
{
    node->next = lbl_8066C6E4;
    node->f4 = 0;
    lbl_8066C6E4 = node;
    lbl_8066C6E0++;
}
}
