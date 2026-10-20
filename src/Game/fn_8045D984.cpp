// Opens the "Sounds/ASF/<language>/<name>" stream for `name` on a stream handle (docs/versus.md section 5, row 2).
extern "C" unsigned int strlen(const char *s);
extern "C" char *strcpy(char *dst, const char *src);
extern "C" int sprintf(char *dst, const char *fmt, ...);
extern "C" void *fn_80427400(void);
extern "C" int fn_8042D584(void *locale);
extern "C" void fn_8011931C(char *a, char *b);
extern "C" void fn_8045750C(void *self);
extern "C" int fn_8024E4E4(int owner, int a, char *path, int b);
extern "C" void fn_8024D258(void);
extern "C" void fn_8024D298(void);
extern "C" void fn_8024F244(int handle, int a, float f);
extern "C" void fn_8024EECC(int handle, int a);

extern char lbl_804974D0[], lbl_804974D8[], lbl_804974E0[], lbl_804974E8[], lbl_804974F0[];

struct Stream
{
    int pad0;
    int owner; // +0x4
    int handle; // +0x8
};

extern "C" void fn_8045D984(register Stream *self, register char *name, register int flag)
{
    int len = strlen(name);
    char lang[0x20];
    char path[0x40];
    char full[0x40];

    while (len > 0 && name[len - 1] != '/' && name[len - 1] != '\\') {
        len--;
    }
    switch (fn_8042D584(fn_80427400())) {
    case 1:
        strcpy(lang, lbl_804974D0);
        break;
    case 2:
        strcpy(lang, lbl_804974D8);
        break;
    case 4:
        strcpy(lang, lbl_804974E0);
        break;
    case 0:
    default:
        strcpy(lang, lbl_804974E8);
        break;
    }
    sprintf(path, lbl_804974F0, lang, name + len);
    fn_8011931C(path, full);
    fn_8045750C(self);
    self->handle = fn_8024E4E4(self->owner, 0, full, 0);
    if (flag == 0) {
        fn_8024D258();
        fn_8024F244(self->owner, -1, 0.0f);
        fn_8024EECC(self->owner, 0);
        fn_8024D298();
    }
}
