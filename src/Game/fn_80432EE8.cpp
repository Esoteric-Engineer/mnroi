// Pushes a new {Link copy, Link::get()} entry onto the list; the by-value Link is destroyed here.
// Class names are guesses.

extern "C" void *fn_801B6040(void *list, void *entry);

inline int sn_return_decl(int a) { return a; }

class LinkImpl;

class Link
{
public:
    LinkImpl *impl;   // +0x0
    const void *vptr; // +0x4
    Link(const Link &other);
    ~Link();
    int get();
};

struct Entry
{
    Link *link; // +0x0
    int value;  // +0x4
};

void fn_80432EE8(register void *list, Link arg)
{
    Entry *e = new Entry;
    register Entry *q = e;
    q->link = new Link(arg);
    e->value = arg.get();
    fn_801B6040(list, e);
}
