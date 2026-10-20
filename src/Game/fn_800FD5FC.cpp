// Template lookup by name in the registry; docs/versus.md section 5, row 11.

struct Template;

extern "C" {
extern char *strncpy(char *dst, const char *src, unsigned n);
extern char *strlwr(char *s);
extern const Template *fn_801B48AC(void *registry, char *name);

extern void *lbl_8066BAE4;
}

extern "C" Template *fn_800FD5FC(const char *name, int flag)
{
    Template *tmpl;
    char key[0x20];

    strncpy(key, name, 0x20);
    key[0x1F] = 0;
    strlwr(key);
    tmpl = (Template *)fn_801B48AC(lbl_8066BAE4, key);
    if (!tmpl) {
        if (!flag) {
        }
        return 0;
    }
    return tmpl;
}
