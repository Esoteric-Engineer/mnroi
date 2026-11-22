// Path-string helpers called game-wide (docs/core.md row 16, section 2).
// Owns the .rodata "." (0x8049E55C).

extern char *strrchr(const char *s, int c);
extern char *strchr(const char *s, int c);
extern char *strcat(char *dst, const char *src);
extern char *strcpy(char *dst, const char *src);
extern char *strncpy(char *dst, const char *src, unsigned n);

char *fn_801B3E6C(char *path)
{
    char *p = strrchr(path, '/');
    if (p == 0) {
        return path;
    }
    for (;;) {
        if (*p != '/') {
            break;
        }
        p++;
    }
    return p;
}

char *fn_801B3F00(char *path)
{
    char *name = fn_801B3E6C(path);
    char *next;
    char *dot = strrchr(name, '.');
    if (dot == 0) {
        return 0;
    }
    for (;;) {
        next = strrchr(dot + 1, '.');
        if (next == 0) {
            break;
        }
        dot = next;
    }
    dot++;
    return dot;
}

int fn_801B3FBC(char *path, const char *ext)
{
    char *e = fn_801B3F00(path);
    if (e == 0) {
        strcat(path, ".");
        strcat(path, ext);
        return 1;
    }
    return 0;
}

void fn_801B4038(char *path)
{
    char *e = fn_801B3F00(path);
    if (e != 0) {
        e[-1] = 0;
    }
}

void fn_801B4094(char *path, const char *ext)
{
    fn_801B4038(path);
    strcat(path, ".");
    strcat(path, ext);
}

void fn_801B40EC(char *path)
{
    char *q;
    char *p = path;
    q = strrchr(p, ':');
    if (q != 0) {
        p = q + 1;
    }
    q = strrchr(p, '/');
    if (q != 0) {
        p = q + 1;
    }
    q = strrchr(p, '.');
    if (q != 0) {
        *q = 0;
    }
    strcpy(path, p);
}

void fn_801B41B4(char *dst, int n, char *path)
{
    strncpy(dst, fn_801B3E6C(path), n);
    dst[n - 1] = 0;
}

void fn_801B4220(char *path)
{
    char *p;
    for (;;) {
        p = strchr(path, '\\');
        if (p == 0) {
            break;
        }
        *p = '/';
    }
}
