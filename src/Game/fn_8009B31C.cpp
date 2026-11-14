// Path-node graph: unload step and the .npd loader (docs/ai.md row 15, section 4.7).

#define SWAP16(x) ((((x) & 0xFF) << 8) | ((unsigned short)(x) >> 8))

inline int sn_return_decl(int a) { return a; }

struct Sector // a level sector, found by position (fn_8004DD38)
{
    char pad0[0x11C];
    unsigned short firstNode; // +0x11C
    unsigned short nNodes;    // +0x11E
};

struct Node
{
    char pad[0x60];
};

struct Link
{
    char pad[0x30];
};

struct Level
{
    char pad0[0x28];
    unsigned short nNodes; // +0x28
    unsigned short nLinks; // +0x2A
    char name[0x20];       // +0x2C (only the part from +0x30 is the file name; see below)
    char pad50[0x154 - 0x4C];
    Node *nodes; // +0x154
    Link *links; // +0x158
};

extern "C" {
char *strncpy(char *dst, const char *src, unsigned n);
void fn_8009CF44(void *graph);
void fn_801B4094(char *path, const char *ext);
void *fn_801A8368(const char *path, const char *mode, int flags);
void fn_801A953C(void *file);
int fn_801A8B60(void *dst, int size, int count, void *file);
void fn_801A875C(void *file);
void *fn_801AC988(unsigned size, const char *tag, int line, int align);
void SetLoadProgress__8GameFlowfi(void *self, float f, int a);
void fn_8009CB38(Node *node, void *file, int version);
void fn_8009CDE4(Link *link, Level *lv, void *file);
void *fn_80444688(Node *node);
Sector *fn_8004DD38(Level *lv, void *pos);
void fn_804446B4(Node *node, Sector *s);
void fn_8044256C(void *out, const char *fmt, ...);
extern char lbl_80552920[];       // the GameFlow instance
extern void *lbl_8066B56C;
extern unsigned short lbl_8066B97C;

int fn_8009B31C(void *graph)
{
    fn_8009CF44(graph);
    return 1;
}

int fn_8009B35C(Level *lv, char *h)
{
    char path[0x80];
    void *file;
    unsigned short version;
    int old;
    Node *node;
    Sector *s;
    unsigned short i;
    int missing;
    lbl_8066B97C = 0;
    if (h)
        strncpy(path, h + 0xC, 0x80);
    else
        strncpy(path, (char *)lv + 0x30, 0x80);
    fn_801B4094(path, "npd");
    file = fn_801A8368(path, "rb", 3);
    if (!file)
        return 0;
    fn_801A953C(file);
    fn_801A8B60(&version, 2, 1, file);
    version = SWAP16(version);
    if (version != 3 && version != 2 && version != 1)
        return 0;
    old = version == 1;
    fn_801A8B60(&lv->nNodes, 2, 1, file);
    lv->nNodes = SWAP16(lv->nNodes);
    fn_801A8B60(&lv->nLinks, 2, 1, file);
    lv->nLinks = SWAP16(lv->nLinks);
    if (!old) {
        fn_801A8B60(&lbl_8066B97C, 2, 1, file);
        lbl_8066B97C = SWAP16(lbl_8066B97C);
    }
    lv->nodes = (Node *)fn_801AC988(lv->nNodes * 0x60, "Game:Pathing", 0x9E, 2);
    lv->links = (Link *)fn_801AC988(lv->nLinks * 0x30, "Game:Pathing", 0x9F, 2);
    missing = 0;
    for (i = 0; i < lv->nNodes; i++) {
        SetLoadProgress__8GameFlowfi(lbl_80552920, (float)i / (float)(int)lv->nNodes, 1);
        node = lv->nodes + i;
        fn_8009CB38(node, file, version);
        s = fn_8004DD38(lv, fn_80444688(node));
        fn_804446B4(node, s);
        if (!s) {
            missing++;
        } else if (s->firstNode > i) {
            s->firstNode = i;
            s->nNodes = 1;
        } else {
            s->nNodes++;
        }
    }
    for (i = 0; i < lv->nLinks; i++)
        fn_8009CDE4(lv->links + i, lv, file);
    if (missing)
        fn_8044256C(lbl_8066B56C, "PATH WARNING!  %d nodes have no sector.\n", missing);
    fn_801A875C(file);
    return 1;
}
}
