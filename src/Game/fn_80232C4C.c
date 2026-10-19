// Loads a texture's <name>.tpl bundle into its GXTexObj; docs/versus.md row 22.
// The float pool is dtk's lbl_804A2888-lbl_804A288C (extern_pool).

typedef struct Texture {
    unsigned short refs;  // +0x0
    char pad2[0x8 - 0x2];
    char obj[0x20];       // +0x8, a GXTexObj
    char pad28[0x34 - 0x28];
    void *tpl;            // +0x34
    char name[0x20];      // +0x38
    unsigned short width; // +0x58
    unsigned short height; // +0x5A
    unsigned int fmt;     // +0x5C
    unsigned int size;    // +0x60
} Texture;

char *strncpy(char *dst, const char *src, unsigned n);
void OSReport(const char *fmt, ...);
int fn_801A8088(const char *name);
int fn_801B3FBC(char *path, const char *ext);
int fn_80233810(char *name, int kind, char *path);
void fn_80233B9C(void **tpl, char *path);
void TEXGetGXTexObjFromPalette(void *pal, void *obj, unsigned int id);
unsigned short GXGetTexObjWidth(void *obj);
unsigned short GXGetTexObjHeight(void *obj);
unsigned int GXGetTexObjFmt(void *obj);
unsigned char GXGetTexObjMipMap(void *obj);
unsigned int GXGetTexBufferSize(unsigned short width, unsigned short height, unsigned int format,
                                unsigned char mipmap, unsigned char max_lod);
float GXGetTexObjMinLOD(void *obj);
void GXInitTexObjLOD(void *obj, unsigned int min_filt, unsigned int mag_filt, float min_lod,
                     float max_lod, float lod_bias, unsigned int bias_clamp,
                     unsigned int do_edge_lod, unsigned int max_aniso);
extern const char lbl_804A2868[];
extern const char lbl_804A286C[];
extern int lbl_8066FB34;
extern int lbl_8066FB38;

int fn_80232C4C(register Texture *tex, unsigned int fmt, const char *name)
{
    char path[0x80];
    void *tpl;
    int mip;
    float lod;

    tpl = 0;
    if (name != 0) {
        if (fn_801A8088(name)) {
            strncpy(path, name, 0x80);
            path[0x7F] = 0;
        } else {
            return 0;
        }
    } else if (!fn_80233810(tex->name, 1, path) && !fn_80233810(tex->name, 4, path)) {
        return 0;
    }
    fn_801B3FBC(path, lbl_804A2868);
    OSReport(lbl_804A286C, path);
    fn_80233B9C(&tpl, path);
    if (tpl == 0)
        return 0;
    tex->tpl = tpl;
    TEXGetGXTexObjFromPalette(tpl, tex->obj, 0);
    tex->width = GXGetTexObjWidth(tex->obj);
    tex->height = GXGetTexObjHeight(tex->obj);
    tex->fmt = GXGetTexObjFmt(tex->obj);
    mip = GXGetTexObjMipMap(tex->obj) != 0;
    tex->size = GXGetTexBufferSize(tex->width, tex->height, tex->fmt, mip, 100);
    lod = GXGetTexObjMinLOD(tex->obj);
    GXInitTexObjLOD(tex->obj, mip ? 5 : 1, 1, 0.0f, lod, -0.5f, 1, 1, 0);
    lbl_8066FB38++;
    lbl_8066FB34 += tex->size;
    return 1;
}
