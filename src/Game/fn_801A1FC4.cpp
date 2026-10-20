// Loads Bundles/<name>.ngm into a free model-bundle slot (2-5) unless already loaded.

struct ModelBundle {
    char name[0x20];
    void *data; // +0x20
    char pad24[0x38 - 0x24];
};

extern "C" {
char *strncpy(char *dst, const char *src, unsigned n);
int stricmp(const char *a, const char *b);
void fn_801B4094(char *path, const char *ext);
int fn_804660DC(ModelBundle *bundle);
int fn_801A2108(const char *name, unsigned char slot);
extern const char lbl_8049D49C[];
extern ModelBundle lbl_8057E110[];
}

extern "C" int fn_801A1FC4(const char *name)
{
    char path[0x20];
    int freeSlot;
    int i;

    strncpy(path, name, 0x20);
    fn_801B4094(path, lbl_8049D49C);
    freeSlot = -1;
    for (i = 2; i <= 5; i++) {
        if (!fn_804660DC(&lbl_8057E110[i])) {
            if (freeSlot == -1)
                freeSlot = i;
        } else if (stricmp(path, lbl_8057E110[i].name) == 0) {
            return 1;
        }
    }
    if (freeSlot == -1)
        return 0;
    return fn_801A2108(name, freeSlot);
}
