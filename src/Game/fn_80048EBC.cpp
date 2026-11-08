// fn_80048EBC moves a Havok collision object (fn_80322470) to a point and runs the collision query fn_80049474 there.

class Vector4
{
public:
    float v[4];
    Vector4(void *v) __asm__("fn_804362D4"); // (x, y, z, 0)
} __attribute__((aligned(8)));

inline int sn_return_decl(int a) { return a; }

extern "C" {
int fn_80436964(void);
void fn_80322470(void *body, const Vector4 &pos, float t);
int fn_80049474(void *body, int a, int b, int c, float f, int d);
}

extern "C" int fn_80048EBC(void *body, void *pos, int a, int b, int c, float f, int d)
{
    if (fn_80436964())
        return 0;
    fn_80322470(body, Vector4(pos), 0.0f);
    return fn_80049474(body, a, b, c, f, d);
}
