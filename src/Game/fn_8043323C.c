// Calls fn_80433884 on the Link of every entry of the list at r3 (Entry layout: Game/fn_80433058.cpp).

extern int fn_801B6A44(void *list);
extern void *fn_801B5D3C(void *list, int index);
extern void fn_80433884(void *link, int flag);

typedef struct Entry {
    void *link; // +0x0
    int value;  // +0x4
} Entry;

void fn_8043323C(register void *list, register int flag)
{
    Entry *e;
    int i = 0;
    while (i < fn_801B6A44(list)) {
        e = (Entry *)fn_801B5D3C(list, i);
        fn_80433884(e->link, flag);
        i++;
    }
}
