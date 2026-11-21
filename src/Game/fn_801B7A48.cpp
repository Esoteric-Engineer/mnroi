// stdVar: named int, float and string variables loaded from text files (docs/core.md row 10).
// .rodata 0x8049E97C-0x8049E9A8.

extern "C" {
unsigned int strlen(const char *s);
char *strcpy(char *dst, const char *src);
char *strcat(char *dst, const char *src);
int sscanf(const char *s, const char *fmt, ...);
void *fn_801A89C0(const char *path, int *size, const char *tag, int a, int b);
void fn_801ACC0C(void *p);
}

struct Table;

extern "C" {
Table *fn_801B74AC(int count, int unused);
int fn_801B7708(Table *t, const char *key, void *value);
void *fn_801B782C(Table *t, const char *key);
}

class Var
{
public:
    int type; // 0 string, 1 int, 2 float
    union {
        char *s;
        int i;
        float f;
    };
    Var() __asm__("fn_80468688");
};

class StdVar
{
public:
    int ready;
    Table *table;
    char *buf;
    char *end;
    char *cur;
    StdVar() __asm__("fn_80468638");
};

inline int sn_return_decl(int a) { return a; }

extern "C" {
void fn_801B7B40(register StdVar *self, const char *name, const Var *v);
char *fn_801B7E24(register StdVar *self, const char *name);
char *fn_801B8654(register StdVar *self, int n);
char *fn_801B86CC(register StdVar *self, const char *s);
char *fn_801B873C(register StdVar *self, char *s);
void fn_801B884C(register StdVar *self, char *s);
int fn_801B88EC(register StdVar *self, const char *text, int len, int pos, char *section, char *key, char *val);
}

static int sCount = 0;

extern "C" StdVar *fn_801B7A48(void)
{
    static StdVar inst;
    return &inst;
}

extern "C" void fn_801B7AA0(register StdVar *self, int n, int bytes, int x)
{
    if (self->ready != 0) {
        return;
    }
    self->table = fn_801B74AC(n * 2, x);
    self->buf = new char[bytes];
    self->end = self->buf + bytes;
    self->cur = self->buf;
    self->ready = 1;
}

extern "C" void fn_801B7B40(register StdVar *self, const char *name, const Var *v)
{
    Var *p;
    Var *q;
    char *key;

    if (self->ready == 0) {
        return;
    }
    p = (Var *)fn_801B782C(self->table, name);
    if (p != 0) {
        *p = *v;
    } else {
        q = (Var *)fn_801B8654(self, sizeof(Var));
        *q = *v;
        key = fn_801B86CC(self, name);
        fn_801B884C(self, key);
        fn_801B7708(self->table, key, q);
        p = q;
    }
}

extern "C" void fn_801B7C20(register StdVar *self, const char *name, const char *s)
{
    char *cur;
    Var *e;

    cur = fn_801B7E24(self, name);
    if (cur != 0) {
        e = (Var *)fn_801B782C(self->table, name);
        if (strlen(s) <= strlen(cur)) {
            strcpy(cur, s);
            return;
        }
    }
    Var v;
    v.type = 0;
    v.s = fn_801B86CC(self, s);
    fn_801B7B40(self, name, &v);
}

extern "C" void fn_801B7CF4(register StdVar *self, const char *name, int i)
{
    Var v;
    v.type = 1;
    v.i = i;
    fn_801B7B40(self, name, &v);
}

extern "C" void fn_801B7D5C(register StdVar *self, const char *name, float f)
{
    Var v;
    v.type = 2;
    v.f = f;
    fn_801B7B40(self, name, &v);
}

extern "C" int fn_801B7DC4(register StdVar *self, const char *name)
{
    if (fn_801B782C(self->table, name) != 0) {
        return 1;
    } else {
        return 0;
    }
}

extern "C" char *fn_801B7E24(register StdVar *self, const char *name)
{
    Var *e;

    if (0) {
        sCount++;
    }
    e = (Var *)fn_801B782C(self->table, name);
    if (e != 0) {
        return e->s;
    }
    return 0;
}

extern "C" int fn_801B7E9C(register StdVar *self, const char *name)
{
    Var *e;

    e = (Var *)fn_801B782C(self->table, name);
    if (e != 0) {
        return e->i;
    }
    return 0;
}

extern "C" void fn_801B7F04(register StdVar *self, const char *name, const char *value)
{
    int neg = 0;
    int hex = 0;
    int numeric = 1;
    int dot = 0;
    const char *lp = 0;
    const char *rp = 0;
    const char *mark = 0;
    const char *p = name;
    char after[0x100];
    char before[0x100];

    while (*p != 0) {
        mark = p;
        if (*p == ':') {
            p++;
            int i = 0;
            while (*p != 0) {
                after[i] = *p;
                p++;
                i++;
            }
            after[i] = 0;
            p = name;
            i = 0;
            while (p < mark) {
                before[i] = *p;
                p++;
                i++;
            }
            before[i] = 0;
            fn_801B7F04(self, before, value);
            return;
        }
        p++;
    }
    p = fn_801B873C(self, (char *)value);
    if (*p == '-') {
        neg = 1;
        p++;
    } else if (*p == '0' && *(p + 1) == 'x') {
        hex = 1;
        p += 2;
    } else if (strlen(p) == 0) {
        numeric = 0;
    }
    while (*p != 0) {
        if (*p == '(') {
            lp = p;
        } else if (lp != 0 && *p == ')') {
            rp = p;
        } else if (dot == 0 && *p == '.') {
            dot = 1;
        } else if (hex != 0) {
            int ok = (*p >= '0' && *p <= '9') || (*p >= 'a' && *p <= 'f') || (*p >= 'A' && *p <= 'F');
            if (ok == 0) {
                numeric = 0;
            }
        } else {
            int ok = *p >= '0' && *p <= '9';
            if (ok == 0) {
                numeric = 0;
            }
        }
        p++;
    }
    if (numeric != 0) {
        int iv;
        float fv;
        if (dot != 0) {
            sscanf(value, "%f", &fv);
            fn_801B7D5C(self, name, fv);
        } else if (hex != 0) {
            sscanf(value, "0x%x", &iv);
            fn_801B7CF4(self, name, iv);
        } else {
            sscanf(value, "%d", &iv);
            fn_801B7CF4(self, name, iv);
        }
    } else {
        fn_801B7C20(self, name, value);
    }
}

inline const char *sn_float_format() { return "%.4f"; }

extern "C" int fn_801B83A8(register StdVar *self, const char *text, int len, const char *prefix)
{
    int count = 0;
    int pos;
    char section[0x100];
    char full[0x100];
    char key[0x100];
    char val[0x400];

    if (text == 0) {
        return 0;
    }
    section[0] = 0;
    pos = 0;
    while (pos < len) {
        pos = fn_801B88EC(self, text, len, pos, section, key, val);
        if (pos < 0) {
            break;
        }
        full[0] = 0;
        if (prefix != 0) {
            strcat(full, prefix);
            strcat(full, "/");
        }
        if (section[0] != 0) {
            strcat(full, section);
            strcat(full, "/");
        }
        strcat(full, key);
        fn_801B884C(self, full);
        fn_801B7F04(self, full, val);
        count++;
    }
    return count;
}

extern "C" int fn_801B8530(register StdVar *self, const char *path, const char *prefix)
{
    int count = 0;
    int size = 0;
    char *buf;

    buf = (char *)fn_801A89C0(path, &size, "Game:stdVar", 1, 0x10);
    if (buf != 0) {
        if (buf[0] == (char)0xEF && *(buf + 1) == (char)0xBB && *(buf + 2) == (char)0xBF) {
            buf[0] = '\r';
            *(buf + 1) = '\r';
            *(buf + 2) = '\r';
        }
        count = fn_801B83A8(self, buf, size, prefix);
        fn_801ACC0C(buf);
    }
    return count;
}

inline const char *sn_prefix_format() { return "%s/"; }

extern "C" char *fn_801B8654(register StdVar *self, int n)
{
    char *p = 0;

    n = (n + 3) & ~3;
    if (self->cur + n < self->end) {
        p = self->cur;
        self->cur = self->cur + n;
    }
    return p;
}

extern "C" char *fn_801B86CC(register StdVar *self, const char *s)
{
    char *d = fn_801B8654(self, strlen(s) + 1);
    strcpy(d, s);
    return d;
}

extern "C" char *fn_801B873C(register StdVar *self, char *s)
{
    while (*s != 0 && (*s == ' ' || *s == '\t')) {
        s++;
    }
    char *e = s + strlen(s) - 1;
    while (e >= s && (*e == ' ' || *e == '\t')) {
        *e-- = 0;
    }
    return s;
}

extern "C" void fn_801B884C(register StdVar *self, char *s)
{
    if (s == 0) {
        return;
    }
    while (*s != 0) {
        if (*s >= 'a' && *s <= 'z') {
            *s = *s - 0x20;
        }
        s++;
    }
}

extern "C" int fn_801B88EC(register StdVar *self, const char *text, int len, int pos, char *section, char *key, char *val)
{
    key[0] = 0;
    val[0] = 0;
    if (pos >= len) {
        return -1;
    }
    int state;
    int n;
    int quoted;
    n = 0;
    quoted = 0;
    state = 0;
    while (pos < len && state != 5) {
        switch (text[pos]) {
        case '\r':
            break;
        case '\n':
            if (state == 3) {
                val[n] = 0;
                state = 5;
            } else {
                state = 0;
            }
            if (text[pos + 1] == '\n') {
                pos++;
            }
            break;
        case '[':
            if (state == 0) {
                state = 1;
            } else if (state == 3) {
                val[n] = text[pos];
                n++;
            }
            break;
        case ']':
            if (state == 1) {
                section[n] = 0;
                n = 0;
                state = 0;
            } else if (state == 3) {
                val[n] = text[pos];
                n++;
            }
            break;
        case '/':
            if (text[pos + 1] == '/') {
                if (state == 3) {
                    val[n] = 0;
                    state = 5;
                    pos--;
                } else {
                    state = 4;
                }
            } else if (state == 3) {
                val[n] = text[pos];
                n++;
            } else if (state == 1) {
                section[n] = text[pos];
                n++;
            }
            break;
        case '\t':
        case ' ':
            if (state == 3 && (n > 0 || quoted != 0)) {
                val[n] = text[pos];
                n++;
            }
            break;
        case '"':
            if (state == 3) {
                quoted ^= 1;
            }
            break;
        case '=':
            if (state == 2) {
                key[n] = 0;
                n = 0;
                state = 3;
            } else if (state == 3) {
                val[n] = text[pos];
                n++;
            }
            break;
        default:
            switch (state) {
            case 1:
                section[n] = text[pos];
                n++;
                break;
            case 2:
                key[n] = text[pos];
                n++;
                break;
            case 3:
                val[n] = text[pos];
                n++;
                break;
            case 4:
                break;
            case 0:
                state = 2;
                key[n] = text[pos];
                n++;
                break;
            default:
                break;
            }
            break;
        }
        pos++;
    }
    if (state == 3) {
        val[n] = 0;
    }
    if (strlen(key) == 0) {
        return -1;
    }
    return pos;
}
