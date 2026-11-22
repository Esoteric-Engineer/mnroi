// The VFS's inline functions (docs/core.md row 18).

inline int sn_return_decl(int a) { return a; }

struct Node {
    Node *next;
};

struct List {
    Node *head;
    Node *tail;
    int count;
};

struct Iter {
    Node *p;
    Iter(Node *p) __asm__("fn_80467350");
};

struct Entry {
    int f[4];
};

struct Header {
    int f0;
    int f4;
    unsigned int n;
    int fC;
    Entry e[1];
};

struct Fs {
    char pad[0x10];
    void *vptr;
};

extern "C" {
extern char lbl_804F6888[];
void __builtin_delete(void *p);

void *fn_80466BA0(register void *p, register int align)
{
    return (void *)(((int)p + (align - 1)) & ~(align - 1));
}

int fn_80466BE0(register Header *self)
{
    return self->f0;
}

int fn_80466C0C(register Header *self)
{
    return self->f4;
}

unsigned int fn_80466C38(register Header *self)
{
    return self->n;
}

int fn_80466C64(register Header *self)
{
    return self->fC;
}

Entry *fn_80466C90(register Header *self, register unsigned int i)
{
    unsigned int n = self->n;
    if (i < n) {
        return &self->e[i];
    } else {
        return &self->e[n - 1];
    }
}

unsigned int fn_80466CFC(register Header *self)
{
    return self->n;
}

void fn_80466D28(register List *self, register Node *node)
{
    Node *tail = self->tail;
    node->next = 0;
    self->tail = node;
    self->count++;
    if (tail == 0) {
        self->head = node;
    } else {
        tail->next = node;
    }
}

void fn_80466D88(register List *self, register Node *node)
{
    Node *tail = self->tail;
    node->next = 0;
    self->tail = node;
    self->count++;
    if (tail == 0) {
        self->head = node;
    } else {
        tail->next = node;
    }
}

Node *fn_80466DE8(register List *self)
{
    Node *n = self->head;
    if (n) {
        if (self->head == self->tail) {
            self->tail = 0;
            self->head = 0;
        } else {
            self->head = self->head->next;
        }
        self->count--;
        n->next = 0;
    }
    return n;
}

Iter *fn_80466E70(register Iter *self)
{
    self->p = 0;
    return self;
}

Iter fn_80466EA0(register List *self)
{
    return Iter(self->head);
}

Node *fn_80466EEC(register Iter *self)
{
    return self->p;
}

void fn_80466F18(register Iter *self, register int)
{
    if (self->p) {
        self->p = self->p->next;
    }
}

Node *fn_80466F54(register List *self)
{
    Node *n = self->head;
    if (n) {
        if (self->head == self->tail) {
            self->tail = 0;
            self->head = 0;
        } else {
            self->head = self->head->next;
        }
        self->count--;
        n->next = 0;
    }
    return n;
}

int fn_80466FDC(register List *self, register Node *node, register Node *prev)
{
    int found = 0;
    if (node == self->head) {
        found = 1;
        self->count--;
        if (node == self->tail) {
            self->head = 0;
            self->tail = 0;
        } else {
            self->head = node->next;
        }
    } else if (self->head) {
        if (prev == 0) {
            prev = self->head;
        }
        while (prev->next && prev->next != node) {
            prev = prev->next;
        }
        if (prev->next && prev->next == node) {
            found = 1;
            self->count--;
            prev->next = node->next;
            if (node == self->tail) {
                self->tail = prev;
            }
        }
    }
    if (found) {
        node->next = 0;
    }
    return found;
}

void fn_80467100(register Fs *self, register int inChrg)
{
    self->vptr = lbl_804F6888;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

List *fn_80467158(register List *self)
{
    self->tail = 0;
    self->head = 0;
    self->count = 0;
    return self;
}

void fn_80467198(register List *self, register int inChrg)
{
    Node *n = self->head;
    Node *next = self->head;
    while (n && n->next) {
        next = n->next;
        n->next = 0;
        n = next;
    }
    self->tail = 0;
    self->head = 0;
    self->count = 0;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

List *fn_80467254(register List *self)
{
    self->tail = 0;
    self->head = 0;
    self->count = 0;
    return self;
}

void fn_80467294(register List *self, register int inChrg)
{
    Node *n = self->head;
    Node *next = self->head;
    while (n && n->next) {
        next = n->next;
        n->next = 0;
        n = next;
    }
    self->tail = 0;
    self->head = 0;
    self->count = 0;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

Iter *fn_80467350(register Iter *self, register Node *p)
{
    self->p = p;
    return self;
}
}

inline void sn_label_decl() { clear:; }

extern "C" long long fn_80467380(register Fs *self, register int a) // +0x50
{
    return 0;
}
