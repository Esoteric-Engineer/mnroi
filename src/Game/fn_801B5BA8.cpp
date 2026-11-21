// Game:List, the growable pointer array under KVList and the list wrappers; docs/core.md row 9.
// Owns the .rodata from 0.0f (0x8049E660).

inline int sn_return_decl(int a) { return a; }

typedef void (*ItemFn)(int op, void *item);
typedef int (*CmpFn)(void *a, void *b);

class VList {
public:
    char data[0x20];
    virtual ~VList();                       // +0x08
    virtual int add(void *item);            // +0x10
    virtual int insert(int i, void *item);  // +0x18
    virtual int remove(void *item);         // +0x20
};

struct List {
    void **items;
    float grow;      // +0x04
    int cap;         // +0x08
    int count;       // +0x0C
    unsigned flags;  // +0x10, bit 0 sorted
    ItemFn onItem;   // +0x14, op 0 added, 1 removed
    CmpFn match;     // +0x18
    CmpFn cmp;       // +0x1C
    const void *vptr;
};

extern "C" {
extern char lbl_804F69B8[];
void fn_801ACC0C(void *p);
void *fn_801ACC7C(void *p, unsigned int size, const char *name, int flags);
void __builtin_delete(void *p);
double ceil(double x);
void *memset(void *d, int c, unsigned int n);
void *memcpy(void *d, const void *s, unsigned int n);
void *memmove(void *d, const void *s, unsigned int n);

void fn_801B5E38(register List *self, int n);
void fn_801B6240(register List *self, int start, int len);
void fn_801B67D8(register List *self, CmpFn cmp);
int fn_801B6AC0(register List *self);

List *fn_801B5BA8(register List *self, int n, float grow)
{
    self->vptr = lbl_804F69B8;
    self->grow = grow > 0.0f ? grow : 4.0f;
    self->cap = 0;
    self->count = 0;
    self->flags = 0;
    self->onItem = 0;
    self->match = 0;
    self->cmp = 0;
    self->items = 0;
    fn_801B5E38(self, n > 0 ? n : 0x40);
    return self;
}

void fn_801B5C74(register List *self, int inChrg)
{
    self->vptr = lbl_804F69B8;
    fn_801B5E38(self, 0);
    if (inChrg & 1)
        __builtin_delete(self);
    else
    {
    }
}

void fn_801B5CDC(register List *self, int op, void *item)
{
    if (self->onItem)
        self->onItem(op, item);
}

void *fn_801B5D3C(register List *self, int i)
{
    return self->items[i];
}

void fn_801B5D80(register List *self)
{
    int n = self->cap + (int)(float)ceil((float)self->cap * self->grow);
    if (n <= 3)
        fn_801B5E38(self, 4);
    else
        fn_801B5E38(self, n);
}

void fn_801B5E38(register List *self, int n)
{
    int i;

    if (n == self->cap)
        return;
    if (self->onItem)
    {
        for (i = n; i < self->count; i++)
            fn_801B5CDC(self, 1, self->items[i]);
    }
    if (n)
        self->items = (void **)fn_801ACC7C(self->items, n * sizeof(void *), "Game:List", 2);
    else
    {
        fn_801ACC0C(self->items);
        self->items = 0;
    }
    if (n > self->cap)
        memset(&self->items[self->cap], 0, (n - self->cap - 1) * sizeof(void *));
    self->cap = n;
    if (self->count > n)
        self->count = n;
}

void fn_801B5F94(register List *self, int n)
{
    if (n == self->count)
        return;
    if (n > self->cap)
        fn_801B5E38(self, n);
    if (n > 0 && n < self->count)
        fn_801B6240(self, n - 1, self->count - n);
    self->count = n;
}

int fn_801B6040(register List *self, void *item)
{
    if (self->count == self->cap)
        fn_801B5D80(self);
    self->items[self->count] = item;
    self->count++;
    if (fn_801B6AC0(self))
        fn_801B67D8(self, 0);
    fn_801B5CDC(self, 0, item);
    return self->count - 1;
}

void fn_801B60F4(register List *self)
{
    fn_801B5F94(self, 0);
}

void *fn_801B6130(register List *self, int i)
{
    void *item;

    if (i >= self->count)
        return 0;
    item = self->items[i];
    if (i < self->count - 1)
        memcpy(&self->items[i], &self->items[i + 1], (self->count - i) * sizeof(void *));
    self->count--;
    self->items[self->count] = 0;
    fn_801B5CDC(self, 1, item);
    return item;
}

void fn_801B6240(register List *self, int start, int len)
{
    int i;
    int end;

    if (start >= self->count)
        return;
    end = start + len;
    if (self->onItem)
    {
        for (i = start; i < end && i < self->count; i++)
            fn_801B5CDC(self, 1, self->items[i]);
    }
    if (end < self->count)
        memcpy(&self->items[start], &self->items[end], (self->count - end) * sizeof(void *));
    else
        end = start;
    self->count = end + 1;
}

int fn_801B6380(register List *self, void *item)
{
    int i;

    for (i = 0; i < self->count; i++)
    {
        if (self->items[i] == item)
            return i;
    }
    return -1;
}

int fn_801B6408(register List *self, int i, void *item)
{
    if (i >= self->count || fn_801B6AC0(self))
        return ((VList *)self)->add(item);
    if (i < 0)
        i = 0;
    if (self->count == self->cap)
        fn_801B5D80(self);
    memmove(&self->items[i + 1], &self->items[i], (self->count - i) * sizeof(void *));
    self->items[i] = item;
    self->count++;
    fn_801B5CDC(self, 0, item);
    return i;
}

void fn_801B6564(register List *self, int lo, int hi, CmpFn cmp)
{
    int i;
    int j;
    void *pivot;
    void *t;

    do
    {
        i = lo;
        j = hi;
        pivot = self->items[(lo + hi) >> 1];
        do
        {
            while (cmp(self->items[i], pivot) < 0)
                i++;
            while (cmp(self->items[j], pivot) > 0)
                j--;
            if (i <= j)
            {
                t = self->items[i];
                self->items[i] = self->items[j];
                self->items[j] = t;
                i++;
                j--;
            }
        } while (i <= j);
        if (lo < j)
            fn_801B6564(self, lo, j, cmp);
        lo = i;
    } while (i < hi);
}

int fn_801B6768(register List *self, void *item)
{
    int i = fn_801B6380(self, item);
    if (i > -1)
        fn_801B6130(self, i);
    return i;
}

void fn_801B67D8(register List *self, CmpFn cmp)
{
    if (self->count > 1)
    {
        if (cmp)
            fn_801B6564(self, 0, self->count - 1, cmp);
        else if (self->cmp)
            fn_801B6564(self, 0, self->count - 1, self->cmp);
    }
}

int fn_801B686C(register List *self, void *key, CmpFn match)
{
    CmpFn fn = match;
    int i;

    if (fn == 0)
        fn = self->match;
    if (fn == 0)
        return -1;
    for (i = 0; i < self->count; i++)
    {
        if (fn(self->items[i], key))
            return i;
    }
    return -1;
}

void fn_801B6950(register List *self, int on)
{
    if (on == fn_801B6AC0(self))
        return;
    if (on == 0)
        self->flags &= ~1;
    else
    {
        if (self->cmp == 0)
            return;
        self->flags |= 1;
        fn_801B67D8(self, self->cmp);
    }
}

void fn_801B69E4(register List *self, register ItemFn fn)
{
    self->onItem = fn;
}

void fn_801B6A0C(register List *self, register float grow)
{
    if (grow > 0.0f)
        self->grow = grow;
}

int fn_801B6A44(register List *self)
{
    return self->count;
}

void fn_801B6A70(register List *self, register CmpFn fn)
{
    self->match = fn;
}

void fn_801B6A98(register List *self, register CmpFn fn)
{
    self->cmp = fn;
}

int fn_801B6AC0(register List *self)
{
    return self->flags & 1;
}
}
