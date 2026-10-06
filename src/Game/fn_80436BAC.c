// Clips a segment against a plane set; the .rodata float pool is read through extern_pool.

typedef struct Plane
{
    float x, y, z, d;
} Plane;

typedef struct PlaneSet
{
    char pad0[0x17];
    unsigned char count; // +0x17
    char pad1[8];
    Plane *planes;       // +0x20
} PlaneSet;

extern float fn_8042EBF4(void *a, void *b);
extern void fn_8042FE08(void *a, void *b, float t);

int fn_80436BAC(register PlaneSet *self, register void *a, register void *b, register float *t)
{
    float da;
    float db;
    unsigned int i = 0;
    float s;
    while (i < self->count)
    {
        da = fn_8042EBF4(&self->planes[i], a) - self->planes[i].d;
        db = fn_8042EBF4(&self->planes[i], b);
        if (da < 0.0f)
        {
            if (db <= 0.0f || *t * db < -da)
                return 0;
            s = -da / db;
            fn_8042FE08(a, b, s);
            *t = *t - s;
        }
        else if (db < 0.0f)
        {
            if (-db * *t > da)
                *t = da / -db;
        }
        i++;
    }
    return 1;
}
