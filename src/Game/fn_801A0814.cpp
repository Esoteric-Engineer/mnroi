// Returns the .nod model <name> from the model registry, loading it on a miss; docs/versus.md row 22.

struct Model {
    char pad0[0x6];
    unsigned short refs; // +0x6
};

extern "C" {
char *strncpy(char *dst, const char *src, unsigned n);
void OSReport(const char *fmt, ...);
int fn_801B3F00(char *path);
int fn_801B3FBC(char *path, const char *ext);
void *fn_801B48AC(void *registry, char *name);
int fn_80465FF4(Model *model);
void fn_801A33E0(Model *model);
void fn_801A8E54(void *file, const char *fmt, ...);
void fn_801A9334(void *file);
void *fn_801A8368(const char *path, const char *mode, int flags);
Model *fn_801A09F0(void *file, char *path, unsigned int flags);
void fn_801A875C(void *file);
extern const char lbl_8049D420[];
extern const char lbl_8049D424[];
extern const char lbl_8049D440[];
extern const char lbl_8049D448[];
extern const char lbl_8049D44C[];
extern void *lbl_8066C5CC;
extern void *lbl_8066C5D8;
}

extern "C" Model *fn_801A0814(const char *name, unsigned int flags)
{
    void *file = 0;
    Model *model = 0;
    char path[0x80];
    int hasExt;

    strncpy(path, name, 0x80);
    path[0x7F] = 0;
    hasExt = fn_801B3F00(path);
    if (!hasExt)
        fn_801B3FBC(path, lbl_8049D420);
    model = (Model *)fn_801B48AC(lbl_8066C5CC, path);
    if (model) {
        model->refs++;
        if (fn_80465FF4(model))
            fn_801A33E0(model);
        return model;
    }
    OSReport(lbl_8049D424, name);
    if (lbl_8066C5D8) {
        if (flags & 0x10)
            fn_801A8E54(lbl_8066C5D8, lbl_8049D440, path);
        else
            fn_801A8E54(lbl_8066C5D8, lbl_8049D448, path);
        fn_801A9334(lbl_8066C5D8);
    }
    file = fn_801A8368(path, lbl_8049D44C, 2);
    if (!file)
        return 0;
    model = fn_801A09F0(file, path, flags);
    if (file)
        fn_801A875C(file);
    return model;
}
