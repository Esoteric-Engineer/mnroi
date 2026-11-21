// Geometry tests on points, segments, planes and boxes (docs/core.md row 11).
// .rodata 0x8049E9B8-0x8049EA68.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

class Vec2
{
public:
    float x;
    float y;
    Vec2() __asm__("fn_80426A2C");
};

class Mat16
{
public:
    float m[16];
    Mat16(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13,
          float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) __asm__("fn_804687D8");
};

#define ABS(a) ((a) < 0.0f ? -(a) : (a))
#define WRAP(k) ((k) < 0 ? 3 : ((k) > 3 ? 0 : (k)))

extern "C" {
double __ieee754_sqrt(double x);
float fn_8042EBF4(Vector *a, Vector *b);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_8042D80C(Vector *dst, Vector *src);
void fn_80429090(Vector *out, Vector *a, Vector *b, float s);
float *fn_8042FB28(Vector *v);
float *fn_804304CC(Vector *v);
int fn_804686B8(Vector *a, Vector *b, Vector *dir, Vector *n, float d);
float fn_804290F8(Vector *a, Vector *b);
float fn_80441B0C(Vector *a, Vector *b);
void fn_80429038(Vector *out, Vector *a, Vector *b);
float *fn_8042E7E4(Vec2 *v);
void fn_801BBED0(Vector *n, unsigned char *u, unsigned char *v);
float fn_80440EDC(Vector *v);
void fn_8042FDBC(Vector *out, Vector *v, float s);
void fn_8042F984(Vector *out, Vector *a, Vector *b);
void fn_80428FE0(Vector *out, Vector *a, Vector *b);
void fn_8042DCC0(Vector *m);
float fn_8042EC54(Vector *v);
void fn_8042F76C(Vector *v);
float *fn_8042DC3C(Vector *m, int row, int col);
void *memset(void *dst, int c, unsigned int n);
float fn_80434040(Vector *v);
float fn_801BE3C4(float x);
}

extern Vector lbl_80593DC0;
extern Vector lbl_80593DE0;

extern "C" {
int fn_801BA16C(Vector *start, Vector *dir, float len, Vector *n, float d, float *t);
}

__asm__(".section .rodata\n\t.float 0.0\n\t.text");

extern "C" int fn_801BA090(Vector *start, Vector *dir, float len, Vector *n, Vector *p, float *t)
{
    return fn_801BA16C(start, dir, len, n,
                       n->x * (start->x - p->x) + n->y * (start->y - p->y) + n->z * (start->z - p->z), t);
}

extern "C" int fn_801BA16C(Vector *start, Vector *dir, float len, Vector *n, float d, float *t)
{
    float dd;
    float m;
    float dn;

    dd = ((d < 0.0f ? -d : d) > 1e-5f) ? d : 0.0f;
    if (dd < 0.0f) {
        return 0;
    }
    if (dd > len) {
        return 0;
    }
    dn = -fn_8042EBF4(n, dir);
    if (dn <= 0.0f) {
        return 0;
    }
    if (dd <= 0.0f) {
        *t = 0.0f;
        return 1;
    }
    m = dn * len;
    if (m < dd) {
        return 0;
    }
    *t = dd / dn;
    *t = *t < 0.0f ? 0.0f : *t;
    return 1;
}

extern "C" int fn_801BA328(Vector *start, Vector *dir, float len, Vector *m, Vector *box, float *out)
{
    unsigned char i;
    Vector end;
    Vector cur;
    float d;

    fn_80429090(&end, start, dir, len);
    fn_8042DC84(&cur, start);
    for (i = 0; i < 3; i++) {
        d = fn_8042EBF4(&m[3], &m[i]) + fn_804304CC(&box[1])[i];
        if (fn_804686B8(&cur, &end, dir, &m[i], d) == 0) {
            return 0;
        }
        Vector neg;
        fn_8042D80C(&neg, &m[i]);
        d = fn_8042EBF4(&m[3], &neg) - fn_804304CC(box)[i];
        if (fn_804686B8(&cur, &end, dir, &neg, d) == 0) {
            return 0;
        }
    }
    *out = fn_8042EBF4(&cur, dir) - fn_8042EBF4(start, dir);
    return 1;
}

extern "C" int fn_801BA588(Vector *c, float r, Vector *m, Vector *box, float *dist)
{
    float a;
    float b;
    float e;
    float sum = 0.0f;
    int i;

    for (i = 0; i < 3; i++) {
        a = fn_8042EBF4(c, &m[i]);
        b = fn_8042EBF4(&m[3], &m[i]);
        if ((e = a - (b + fn_8042FB28(box)[i])) < 0.0f) {
            sum += e * e;
        } else if ((e = a - (b + fn_8042FB28(&box[1])[i])) > 0.0f) {
            sum += e * e;
        }
    }
    if (sum <= r * r) {
        if (dist != 0) {
            register float *d = dist;
            *d = __ieee754_sqrt(sum);
        }
        return 1;
    } else {
        return 0;
    }
}

__asm__(".section .rodata\n\t.float 0.0\n\t.text");

extern "C" int fn_801BA784(Vector *c, float r, Vector *m, Vector *box)
{
    float a;
    float b;
    unsigned char i;

    for (i = 0; i < 3; i++) {
        a = fn_8042EBF4(c, &m[i]);
        b = fn_8042EBF4(&m[3], &m[i]);
        if (a - r > b + fn_8042FB28(box)[i]) {
            return 0;
        }
        if (a + r < b + fn_8042FB28(&box[1])[i]) {
            return 0;
        }
    }
    return 1;
}

extern "C" int fn_801BA900(Vector *a, float ra, Vector *b, float rb, float *dist)
{
    float sum = ra + rb;
    float d = fn_804290F8(a, b);

    if (d > sum) {
        return 0;
    }
    if (dist != 0) {
        *dist = d;
    }
    return 1;
}

extern "C" int fn_801BA9A4(Vector *a, float ra, Vector *b, float rb, float hb, float *dist)
{
    float d;

    if (fn_804304CC(a)[2] > fn_804304CC(b)[2] + hb + ra) {
        return 0;
    }
    if (fn_804304CC(a)[2] + ra < fn_804304CC(b)[2]) {
        return 0;
    }
    d = fn_80441B0C(a, b);
    if (d > ra + rb) {
        return 0;
    }
    if (dist != 0) {
        *dist = d;
    }
    return 1;
}

extern "C" int fn_801BAAC4(Vector *a, float ra, Vector *b, float rb, float hb)
{
    if (fn_804304CC(b)[2] + hb < fn_804304CC(a)[2] - ra) {
        return 0;
    }
    if (fn_804304CC(a)[2] + ra - fn_804304CC(b)[2] < hb) {
        return 0;
    }
    if (fn_80441B0C(a, b) + rb > ra) {
        return 0;
    }
    return 1;
}

extern "C" float fn_801BABC8(Vector *q, Vector *s, Vector *e, Vector *out)
{
    Vector se;
    Vector sq;
    float d;
    float l;
    float t;

    fn_80429038(&se, e, s);
    fn_80429038(&sq, q, s);
    d = fn_8042EBF4(&sq, &se);
    if (d <= 0.0f) {
        if (out != 0) {
            fn_8042DC84(out, s);
        }
        return 0.0f;
    }
    l = fn_8042EBF4(&se, &se);
    if (l <= d) {
        if (out != 0) {
            fn_8042DC84(out, e);
        }
        return 1.0f;
    }
    t = d / l;
    if (out != 0) {
        fn_80429090(out, s, &se, t);
    }
    return t;
}

extern "C" int fn_801BAD30(Vector *o, Vector *dir, float maxd, Vector *c, float r, float *t0, float *t1)
{
    const float r2 = r * r;
    Vector oc;
    fn_80429038(&oc, c, o);
    const float b = fn_8042EBF4(&oc, dir);
    const float cc = fn_8042EBF4(&oc, &oc);

    if (b < 0.0f && cc > r2) {
        return 0;
    }
    const float m2 = cc - b * b;
    if (m2 > r2) {
        return 0;
    }
    const float q = __ieee754_sqrt(r2 - m2);
    if (cc > r2) {
        *t0 = b - q;
        if (*t0 > maxd) {
            return 0;
        }
        *t1 = b + q;
        if (*t1 > maxd) {
            *t1 = -1.0f;
        }
    } else {
        *t0 = b + q;
        if (*t0 > maxd) {
            return 0;
        }
        *t1 = -1.0f;
    }
    return 1;
}

extern "C" int fn_801BAF48(Vector *o, Vector *dir, float len, Vector *verts, Vector *n)
{
    float dn;
    float dist;
    float t;
    int crossings;
    int sgn;
    int nsgn;

    dn = fn_8042EBF4(n, dir);
    if (dn < 1e-5f && dn > -1e-5f) {
        return 0;
    }
    dist = -(n->x * (o->x - verts->x) + n->y * (o->y - verts->y) + n->z * (o->z - verts->z));
    if (dist < 1e-5f && dist > -1e-5f) {
        return 0;
    }
    t = dist / dn;
    if (t < 0.0f) {
        return 0;
    }
    static Vec2 pts[4];
    crossings = 0;
    Vector hit;
    fn_80429090(&hit, o, dir, t);
    unsigned char u;
    unsigned char v;
    fn_801BBED0(n, &u, &v);
    register int i;
    register int j;
    for (i = 0; i < 4; i++) {
        fn_8042E7E4(&pts[i])[0] = fn_804304CC(&verts[i])[u] - fn_8042FB28(&hit)[u];
        if (ABS(fn_8042E7E4(&pts[i])[0]) < 1e-5f) {
            fn_8042E7E4(&pts[i])[0] = 0.0f;
        }
        fn_8042E7E4(&pts[i])[1] = fn_804304CC(&verts[i])[v] - fn_8042FB28(&hit)[v];
        if (ABS(fn_8042E7E4(&pts[i])[1]) < 1e-5f) {
            fn_8042E7E4(&pts[i])[1] = 0.0f;
        }
    }
    sgn = fn_8042E7E4(&pts[0])[1] < 0.0f ? -1 : 1;
    float k;
    for (i = 0, j = 1; i < 4; i++, j = WRAP(j + 1)) {
        nsgn = fn_8042E7E4(&pts[j])[1] < 0.0f ? -1 : 1;
        if (sgn != nsgn) {
            if (fn_8042E7E4(&pts[i])[0] >= 0.0f && fn_8042E7E4(&pts[j])[0] >= 0.0f) {
                crossings++;
            } else if (fn_8042E7E4(&pts[i])[0] >= 0.0f || fn_8042E7E4(&pts[j])[0] >= 0.0f) {
                k = fn_804304CC(&verts[WRAP(i + 1)])[v] - fn_804304CC(&verts[i])[v];
                if (ABS(k) < 1e-5f) {
                    k = 0.0f;
                } else {
                    k = (fn_804304CC(&verts[WRAP(i + 1)])[u] - fn_804304CC(&verts[i])[u]) / k;
                }
                if (fn_8042E7E4(&pts[i])[0] - fn_8042E7E4(&pts[i])[1] * k > 0.0f) {
                    crossings++;
                }
            }
        }
        sgn = nsgn;
    }
    return crossings & 1;
}

extern "C" float fn_801BB7EC(Vector *p0, Vector *p1, Vector *q0, Vector *q1, Vector *outP, Vector *outQ)
{
    Vector u;
    fn_80429038(&u, p1, p0);
    Vector v;
    fn_80429038(&v, q1, q0);
    Vector w;
    fn_80429038(&w, p0, q0);
    float a = fn_8042EBF4(&u, &u);
    float b = fn_8042EBF4(&u, &v);
    float c = fn_8042EBF4(&v, &v);
    float d = fn_8042EBF4(&u, &w);
    float e = fn_8042EBF4(&v, &w);
    float D = a * c - b * b;
    float sc, sN, sD = D;
    float tc, tN, tD = D;

    if (D < 1e-5f) {
        sN = 0.0f;
        sD = 1.0f;
        tN = e;
        tD = c;
    } else {
        sN = b * e - c * d;
        tN = a * e - b * d;
        if (sN < 0.0) {
            sN = 0.0f;
            tN = e;
            tD = c;
        } else if (sN > sD) {
            sN = sD;
            tN = e + b;
            tD = c;
        }
    }
    if (tN < 0.0) {
        tN = 0.0f;
        if (-d < 0.0) {
            sN = 0.0f;
        } else if (-d > a) {
            sN = sD;
        } else {
            sN = -d;
            sD = a;
        }
    } else if (tN > tD) {
        tN = tD;
        if (-d + b < 0.0) {
            sN = 0.0f;
        } else if (-d + b > a) {
            sN = sD;
        } else {
            sN = -d + b;
            sD = a;
        }
    }
    sc = ABS(sN) < 1e-5f ? 0.0f : sN / sD;
    tc = ABS(tN) < 1e-5f ? 0.0f : tN / tD;

    Vector cp;
    Vector cq;
    fn_80429090(&cp, p0, &u, sc);
    fn_80429090(&cq, q0, &v, tc);
    if (outP != 0) {
        fn_8042DC84(outP, &cp);
    }
    if (outQ != 0) {
        fn_8042DC84(outQ, &cq);
    }
    return fn_804290F8(&cp, &cq);
}

extern "C" int fn_801BBCBC(Vector *p1, Vector *p2, Vector *outPt, Vector *outDir)
{
    float n11 = fn_80440EDC(p1);
    float n12 = fn_8042EBF4(p1, p2);
    float n22 = fn_80440EDC(p2);
    float det = n11 * n22 - n12 * n12;
    register const float eps = 1.1920929e-7f;

    if (ABS(det) < eps) {
        return 0;
    }
    float inv = 1.0f / det;
    float c1 = (n22 * p1->w - n12 * p2->w) * inv;
    float c2 = (n11 * p2->w - n12 * p1->w) * inv;
    Vector dir;
    fn_8042F984(&dir, p1, p2);
    Vector pt;
    Vector a;
    Vector b;
    fn_8042FDBC(&a, p1, c1);
    fn_8042FDBC(&b, p2, c2);
    fn_80428FE0(&pt, &a, &b);
    fn_8042DC84(outPt, &pt);
    fn_8042DC84(outDir, &dir);
    return 1;
}

__asm__(".section .rodata\n\t.float 1.0\n\t.float 0.0\n\t.float 1.0\n\t.float 0.0\n\t.float 1.0\n\t.text");

static int sOtherAxes[3][2] = { { 2, 1 }, { 0, 2 }, { 1, 0 } };

extern "C" void fn_801BBED0(register Vector *n, register unsigned char *u, register unsigned char *v)
{
    int i;
    float ax = ABS(n->x);
    float ay = ABS(n->y);
    float az = ABS(n->z);

    if (ax > ay) {
        if (ax > az) {
            i = 0;
        } else {
            i = 2;
        }
    } else {
        if (ay > az) {
            i = 1;
        } else {
            i = 2;
        }
    }
    if (fn_804304CC(n)[i] > 0.0f) {
        *u = sOtherAxes[i][0];
        *v = sOtherAxes[i][1];
    } else {
        *u = sOtherAxes[i][1];
        *v = sOtherAxes[i][0];
    }
}

__asm__(".section .rodata\n\t.float 0.0\n\t.float -0.5\n\t.text");

extern "C" void fn_801BC080(Vector *m, Vector *fwd)
{
    fn_8042DCC0(m);
    fn_8042DC84(&m[1], fwd);
    fn_8042F984(m, &m[1], &lbl_80593DE0);
    if (fn_8042EC54(m) == 0.0f) {
        fn_8042F984(&m[2], &lbl_80593DC0, &m[1]);
        fn_8042F76C(&m[2]);
        fn_8042F984(m, &m[1], &m[2]);
    } else {
        fn_8042F984(&m[2], m, &m[1]);
    }
    memset(&m[3], 0, 0x10);
    *fn_8042DC3C(m, 0, 3) = 0.0f;
    *fn_8042DC3C(m, 1, 3) = 0.0f;
    *fn_8042DC3C(m, 2, 3) = 0.0f;
    *fn_8042DC3C(m, 3, 3) = 1.0f;
}

__asm__(".section .rodata\n\t.float 1.0\n\t.float 0.0\n\t.text");

extern "C" void fn_801BC228(Vector *m, Vector *out)
{
    Vector f;
    Vector u;
    Vector r;
    Vector h;
    Vector h2;
    float len;
    float len2;
    float c;
    float ang;

    fn_8042DC84(&f, &m[1]);
    fn_8042DC84(&u, &m[2]);
    fn_8042D80C(&r, m);
    fn_8042FB28(&h)[0] = fn_8042FB28(&f)[0];
    fn_8042FB28(&h)[1] = fn_8042FB28(&f)[1];
    fn_8042FB28(&h)[2] = 0.0f;
    len = fn_80434040(&h);
    if (len < 0.001f) {
        ang = 90.0f - fn_801BE3C4(-fn_8042FB28(&r)[0]);
        if ((fn_8042FB28(&r)[1] > 0.0f && fn_8042FB28(&f)[2] > 0.0f) ||
            (fn_8042FB28(&r)[1] < 0.0f && fn_8042FB28(&f)[2] < 0.0f)) {
            ang = -ang;
        }
        fn_8042FB28(out)[1] = ang;
        fn_8042FB28(out)[2] = 0.0f;
    } else {
        ang = 90.0f - fn_801BE3C4(fn_8042FB28(&h)[1] / len);
        if (fn_8042FB28(&f)[0] > 0.0f) {
            ang = -ang;
        }
        fn_8042FB28(out)[2] = ang;
    }
    if (len < 0.001f) {
        fn_8042FB28(out)[0] = 90.0f;
    } else {
        c = fn_8042EBF4(&h, &f) / len;
        if (c >= 1.0f) {
            fn_8042FB28(out)[0] = 0.0f;
        } else {
            ang = 90.0f - fn_801BE3C4(c);
            fn_8042FB28(out)[0] = ang;
        }
    }
    if (fn_8042FB28(&f)[2] < 0.0f) {
        fn_8042FB28(out)[0] = -fn_8042FB28(out)[0];
    }
    fn_8042FB28(&h2)[0] = -fn_8042FB28(&h)[1];
    fn_8042FB28(&h2)[1] = fn_8042FB28(&h)[0];
    fn_8042FB28(&h2)[2] = 0.0f;
    len2 = fn_80434040(&h2);
    if (len >= 0.001f) {
        c = fn_8042EBF4(&h2, &r) / len2;
        if (c >= 1.0f) {
            fn_8042FB28(out)[1] = 0.0f;
        } else if (c <= -1.0f) {
            fn_8042FB28(out)[1] = 180.0f;
        } else {
            ang = 90.0f - fn_801BE3C4(c);
            fn_8042FB28(out)[1] = ang;
        }
        if (fn_8042FB28(&r)[2] < 0.0f) {
            fn_8042FB28(out)[1] = -fn_8042FB28(out)[1];
        }
    }
}

__asm__(".section .rodata\n\t.float 0.0\n\t.float 0.001\n\t.float 90.0\n\t.text");

Mat16 lbl_80593D34(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
Mat16 lbl_80593D74(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
