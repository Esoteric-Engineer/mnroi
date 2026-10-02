typedef enum { A_NULL = 0xFF, A_MAX = 0x7FFFFFFF } GXAttr;
typedef enum { T_NONE = 0, T_MAX = 0x7FFFFFFF } GXAttrType;
typedef struct {
    GXAttr attr;
    GXAttrType type;
} GXVtxDescList;

extern void GXGetVtxDesc(GXAttr attr, GXAttrType* type);

void GXGetVtxDescv(GXVtxDescList* vcd)
{
    GXAttr attr;

    for (attr = 0; attr <= 20; attr++) {
        vcd[attr].attr = attr;
        GXGetVtxDesc(attr, &vcd[attr].type);
    }
    vcd[attr].attr = 25;
    GXGetVtxDesc(25, &vcd[attr].type);
    attr++;
    vcd[attr].attr = A_NULL;
}
