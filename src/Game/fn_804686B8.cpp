// The geometry tests' inline functions (docs/core.md row 18).

inline int sn_return_decl(int a) { return a; }

struct Vector;

struct Matrix {
    float m[16];
};

extern "C" {
float fn_8042EBF4(Vector *a, Vector *b);
void fn_8042FE08(Vector *out, Vector *dir, float t);
void fn_80429090(Vector *out, Vector *a, Vector *b, float s);

int fn_804686B8(register Vector *a, register Vector *b, register Vector *dir, register Vector *n, register float d)
{
    float da;
    float db;
    float t;
    float den;

    da = fn_8042EBF4(a, n);
    db = fn_8042EBF4(b, n);
    if (da > d) {
        if (db > d) {
            return 0;
        }
        den = -fn_8042EBF4(dir, n);
        t = (da - d) / den;
        fn_8042FE08(a, dir, t);
    } else if (db > d) {
        den = fn_8042EBF4(dir, n);
        t = (d - da) / den;
        fn_80429090(b, a, dir, t);
    }
    return 1;
}

Matrix *fn_804687D8(register Matrix *self, register float a, register float b, register float c, register float d,
                    register float e, register float f, register float g, register float h, register float i,
                    register float j, register float k, register float l, register float m, register float n,
                    register float o, register float p)
{
    self->m[0] = a;
    self->m[1] = b;
    self->m[2] = c;
    self->m[3] = d;
    self->m[4] = e;
    self->m[5] = f;
    self->m[6] = g;
    self->m[7] = h;
    self->m[8] = i;
    self->m[9] = j;
    self->m[10] = k;
    self->m[11] = l;
    self->m[12] = m;
    self->m[13] = n;
    self->m[14] = o;
    self->m[15] = p;
    return self;
}
}
