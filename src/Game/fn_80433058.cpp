// Removes the list entry whose value equals arg.get() and deletes its Link; the by-value Link is destroyed here.
// Class names are guesses; see docs/versus.md section 5.

extern "C" void *fn_801B5D3C(void *list, int index);
extern "C" int fn_801B6A44(void *list);
extern "C" void fn_801B6768(void *list, void *entry);

inline int sn_return_decl(int a) { return a; }

class LinkImpl;

class Link
{
public:
    LinkImpl *impl; // +0x0, the vptr follows at +0x4
    Link(const Link &other);
    virtual ~Link();
    int get();
};

struct Entry
{
    Link *link; // +0x0
    int value;  // +0x4
};

void fn_80433058(register void *list, Link arg)
{
    int key = arg.get();
    Entry *e = (Entry *)fn_801B5D3C(list, 0);
    int i = 0;
    while (i < fn_801B6A44(list)) {
        e = (Entry *)fn_801B5D3C(list, i);
        if (e->value == key) {
            break;
        }
        i++;
    }
    if (e == 0) {
        return;
    }
    Link *link = e->link;
    fn_801B6768(list, e);
    delete e;
    Link *dead = link;
    delete dead;
}
