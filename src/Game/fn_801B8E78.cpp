// View frustum: built from a camera matrix, tested against boxes and spheres (docs/core.md row 11).
// .rodata 0x8049E9A8-0x8049E9B8.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

class Mat4
{
public:
    Vector row[4];
    Mat4() __asm__("fn_8042D7B0");
};

struct Box
{
    Vector v[2]; // min, max
};

struct Rect
{
    float x0;
    float y0;
    float x1;
    float y1;
};

class Frustum
{
public:
    Vector pts[5]; // eye, then the far corners
    char pad[0x30];
    Vector planes[6]; // +0x80, w the distance
};

extern "C" {
float fn_8042EBF4(Vector *a, Vector *b);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_8042D80C(Vector *dst, Vector *src);
void fn_8042D854(Vector *dst, Vector *src);
void fn_80429090(Vector *out, Vector *a, Vector *b, float s);
void fn_8042FDBC(Vector *out, Vector *v, float s);
void fn_8042FE08(Vector *a, Vector *b, float s);
void fn_8042F984(Vector *out, Vector *a, Vector *b);
void fn_8042F76C(Vector *v);
void fn_80435530(Vector *v, float s);
void fn_80434368(Vector *out, Vector *v, Mat4 *m);
void fn_80434420(Mat4 *dst, Mat4 *src);
void fn_80436100(Vector *v, Mat4 *m);
}

inline int sn_return_decl(int a) { return a; }

extern "C" unsigned char fn_801B8E78(register Frustum *self, Box *box)
{
    unsigned char result = 0x40;
    Vector *pl = self->planes;
    Box *b = box;
    Vector unused;
    Vector p;
    Vector n;
    unsigned int i;

    for (i = 0; i < 6; i++, pl++) {
        int s = pl->x > 0.0f;
        p.x = b->v[s].x;
        n.x = b->v[s ? 0 : 1].x;
        s = pl->y > 0.0f;
        p.y = b->v[s].y;
        n.y = b->v[s ? 0 : 1].y;
        s = pl->z > 0.0f;
        p.z = b->v[s].z;
        n.z = b->v[s ? 0 : 1].z;
        if (fn_8042EBF4(pl, &p) < pl->w) {
            return 0;
        }
        if (fn_8042EBF4(pl, &n) < pl->w) {
            result = 0x3F;
        }
    }
    return result;
}

extern "C" unsigned char fn_801B90A8(register Frustum *self, Box *box, Mat4 *m)
{
    unsigned char result = 0x40;
    Mat4 inv;
    fn_80434420(&inv, m);
    Vector *pl = self->planes;
    Box *b = box;
    Vector nrm;
    Vector p;
    Vector n;
    unsigned int i;

    for (i = 0; i < 6; i++, pl++) {
        fn_80434368(&nrm, pl, &inv);
        int s = nrm.x > 0.0f;
        p.x = b->v[s].x;
        n.x = b->v[s ? 0 : 1].x;
        s = nrm.y > 0.0f;
        p.y = b->v[s].y;
        n.y = b->v[s ? 0 : 1].y;
        s = nrm.z > 0.0f;
        p.z = b->v[s].z;
        n.z = b->v[s ? 0 : 1].z;
        fn_80436100(&p, m);
        if (fn_8042EBF4(pl, &p) < pl->w) {
            return 0;
        }
        fn_80436100(&n, m);
        if (fn_8042EBF4(pl, &n) < pl->w) {
            result = 0x3F;
        }
    }
    return result;
}

extern "C" int fn_801B9324(register Frustum *self, Vector *c, float r)
{
    Vector *pl = self->planes;
    unsigned int i;

    for (i = 0; i < 6; i++, pl++) {
        if (fn_8042EBF4(pl, c) + r < pl->w) {
            return 0;
        }
    }
    return 1;
}

extern "C" void fn_801B93D0(register Frustum *self, Mat4 *cam, float dist, float hw, float hh, float near, float far)
{
    Vector eye;
    fn_8042DC84(&eye, &cam->row[3]);
    fn_8042DC84(&self->planes[0], &cam->row[1]);
    self->planes[0].w = fn_8042EBF4(&self->planes[0], &eye) + near;
    fn_8042D80C(&self->planes[1], &self->planes[0]);
    self->planes[1].w = fn_8042EBF4(&self->planes[1], &eye) - far;

    Vector c;
    Vector a;
    Vector b;
    Vector d;
    Vector e;
    fn_8042FDBC(&c, &cam->row[1], dist);
    fn_80429090(&a, &c, &cam->row[2], hw);
    fn_80429090(&b, &c, &cam->row[2], -hw);
    fn_80429090(&d, &c, &cam->row[0], -hh);
    fn_80429090(&e, &c, &cam->row[0], hh);

    fn_8042F984(&self->planes[2], &d, &cam->row[2]);
    fn_8042F76C(&self->planes[2]);
    self->planes[2].w = fn_8042EBF4(&self->planes[2], &eye);
    fn_8042F984(&self->planes[3], &cam->row[2], &e);
    fn_8042F76C(&self->planes[3]);
    self->planes[3].w = fn_8042EBF4(&self->planes[3], &eye);
    fn_8042F984(&self->planes[4], &a, &cam->row[0]);
    fn_8042F76C(&self->planes[4]);
    self->planes[4].w = fn_8042EBF4(&self->planes[4], &eye);
    fn_8042F984(&self->planes[5], &cam->row[0], &b);
    fn_8042F76C(&self->planes[5]);
    self->planes[5].w = fn_8042EBF4(&self->planes[5], &eye);

    fn_8042DC84(&self->pts[0], &eye);
    fn_80429090(&self->pts[1], &a, &cam->row[0], hh);
    fn_8042F76C(&self->pts[1]);
    fn_80435530(&self->pts[1], far / fn_8042EBF4(&self->pts[1], &cam->row[1]));
    fn_8042D854(&self->pts[1], &eye);
    fn_80429090(&self->pts[2], &a, &cam->row[0], -hh);
    fn_8042F76C(&self->pts[2]);
    fn_80435530(&self->pts[2], far / fn_8042EBF4(&self->pts[2], &cam->row[1]));
    fn_8042D854(&self->pts[2], &eye);
    fn_80429090(&self->pts[3], &b, &cam->row[0], hh);
    fn_8042F76C(&self->pts[3]);
    fn_80435530(&self->pts[3], far / fn_8042EBF4(&self->pts[3], &cam->row[1]));
    fn_8042D854(&self->pts[3], &eye);
    fn_80429090(&self->pts[4], &b, &cam->row[0], -hh);
    fn_8042F76C(&self->pts[4]);
    fn_80435530(&self->pts[4], far / fn_8042EBF4(&self->pts[4], &cam->row[1]));
    fn_8042D854(&self->pts[4], &eye);
}

extern "C" void fn_801B9888(register Frustum *self, Mat4 *cam, float dist, float hw, float hh, const Rect *rect, float near, float far)
{
    Vector eye;
    fn_8042DC84(&eye, &cam->row[3]);
    fn_8042DC84(&self->planes[0], &cam->row[1]);
    self->planes[0].w = fn_8042EBF4(&self->planes[0], &eye) + near;
    fn_8042D80C(&self->planes[1], &self->planes[0]);
    self->planes[1].w = fn_8042EBF4(&self->planes[1], &eye) - far;

    Vector c;
    Vector a;
    Vector b;
    Vector d;
    Vector e;
    fn_8042FDBC(&c, &cam->row[1], dist);
    fn_80429090(&a, &c, &cam->row[2], hw - rect->y0);
    fn_80429090(&b, &c, &cam->row[2], hw - rect->y1);
    fn_80429090(&d, &c, &cam->row[0], -(hh - rect->x0));
    fn_80429090(&e, &c, &cam->row[0], rect->x1 - hh);

    fn_8042F984(&self->planes[2], &d, &cam->row[2]);
    fn_8042F76C(&self->planes[2]);
    self->planes[2].w = fn_8042EBF4(&self->planes[2], &eye);
    fn_8042F984(&self->planes[3], &cam->row[2], &e);
    fn_8042F76C(&self->planes[3]);
    self->planes[3].w = fn_8042EBF4(&self->planes[3], &eye);
    fn_8042F984(&self->planes[4], &a, &cam->row[0]);
    fn_8042F76C(&self->planes[4]);
    self->planes[4].w = fn_8042EBF4(&self->planes[4], &eye);
    fn_8042F984(&self->planes[5], &cam->row[0], &b);
    fn_8042F76C(&self->planes[5]);
    self->planes[5].w = fn_8042EBF4(&self->planes[5], &eye);

    fn_8042DC84(&self->pts[0], &eye);
    fn_80429090(&self->pts[1], &a, &cam->row[0], hh);
    fn_8042F76C(&self->pts[1]);
    fn_80435530(&self->pts[1], far / fn_8042EBF4(&self->pts[1], &cam->row[1]));
    fn_8042D854(&self->pts[1], &eye);
    fn_80429090(&self->pts[2], &a, &cam->row[0], -hh);
    fn_8042F76C(&self->pts[2]);
    fn_80435530(&self->pts[2], far / fn_8042EBF4(&self->pts[2], &cam->row[1]));
    fn_8042D854(&self->pts[2], &eye);
    fn_80429090(&self->pts[3], &b, &cam->row[0], hh);
    fn_8042F76C(&self->pts[3]);
    fn_80435530(&self->pts[3], far / fn_8042EBF4(&self->pts[3], &cam->row[1]));
    fn_8042D854(&self->pts[3], &eye);
    fn_80429090(&self->pts[4], &b, &cam->row[0], -hh);
    fn_8042F76C(&self->pts[4]);
    fn_80435530(&self->pts[4], far / fn_8042EBF4(&self->pts[4], &cam->row[1]));
    fn_8042D854(&self->pts[4], &eye);
}

extern "C" void fn_801B9D78(register Frustum *self, Mat4 *cam, float far, float hw, float hh)
{
    Vector eye;
    fn_8042DC84(&eye, &cam->row[3]);
    fn_8042DC84(&self->planes[0], &cam->row[1]);
    self->planes[0].w = fn_8042EBF4(&self->planes[0], &eye);
    fn_8042D80C(&self->planes[1], &self->planes[0]);
    self->planes[1].w = fn_8042EBF4(&self->planes[1], &eye) - far;
    fn_8042DC84(&self->planes[2], &cam->row[0]);
    self->planes[2].w = fn_8042EBF4(&self->planes[2], &eye) - hw;
    fn_8042D80C(&self->planes[3], &cam->row[0]);
    self->planes[3].w = fn_8042EBF4(&self->planes[3], &eye) - hw;
    fn_8042D80C(&self->planes[4], &cam->row[2]);
    self->planes[4].w = fn_8042EBF4(&self->planes[4], &eye) - hh;
    fn_8042DC84(&self->planes[5], &cam->row[2]);
    self->planes[5].w = fn_8042EBF4(&self->planes[5], &eye) - hh;

    fn_80429090(&self->pts[0], &eye, &cam->row[2], hh);
    fn_8042FE08(&self->pts[0], &cam->row[0], hw);
    fn_80429090(&self->pts[1], &eye, &cam->row[2], hh);
    fn_8042FE08(&self->pts[1], &cam->row[0], -hw);
    fn_80429090(&self->pts[2], &eye, &cam->row[2], -hh);
    fn_8042FE08(&self->pts[2], &cam->row[0], -hw);
    fn_80429090(&self->pts[3], &eye, &cam->row[2], -hh);
    fn_8042FE08(&self->pts[3], &cam->row[0], hw);
    fn_8042FE08(&self->pts[3], &cam->row[1], far);
    fn_80429090(&self->pts[4], &eye, &cam->row[2], hh);
    fn_8042FE08(&self->pts[4], &cam->row[0], hw);
    fn_8042FE08(&self->pts[4], &cam->row[1], far);
}

__asm__(".section .rodata\n\t.float 0.0\n\t.float 0.0\n\t.text");
