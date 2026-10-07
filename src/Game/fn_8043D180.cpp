// Stub, constructors, Mat4 diagonal setter and Vec4 forwarders (docs/versus.md, row 8).
// Class names are guesses; the constructors carry GCC 2.95 mangled symbol names.

inline int sn_return_decl(int a)
{
    return a;
}

extern "C" {
void fn_8043C84C(void *self);
void fn_8043F69C(void *self);
void fn_8043B9AC(void *self);
void fn_80434988(void *self);
void fn_80435300(void *self, float x, float y, float z, float w);
void fn_8043632C(void *self, const void *src);
void fn_8043F718(void *self, int a);
void fn_8043F6D0(void *self, int a);
void fn_80436370(void *self, const void *src);
float *fn_80438360(float *p, int i);
float *fn_8043BAA0(void *self, int row);
extern char lbl_804F4438[];

void fn_8043D180(register int a, register int b)
{
}
}

class Holder
{
public:
    const void *vptr; // +0x0
    short pad;        // +0x4
    short n;          // +0x6
    Holder();
};

Holder::Holder()
{
    fn_8043F69C(this);
    vptr = lbl_804F4438;
    n = 1;
}

class Frame
{
public:
    char data[0x30];
    char sub[0x10]; // +0x30
    Frame();
};

Frame::Frame()
{
    fn_8043B9AC(this);
    fn_80434988(sub);
}

class Vec4
{
public:
    float x, y, z, w;
    Vec4(register float x, register float y, register float z, register float w);
};

Vec4::Vec4(register float x, register float y, register float z, register float w)
    : x(x), y(y), z(z), w(w)
{
}

extern "C" {
float *fn_8043D28C(register void *self, register int col, register int row)
{
    return fn_80438360(fn_8043BAA0(self, row), col);
}

void fn_8043D2EC(register void *self, register float x, register float y, register float z)
{
    fn_8043C84C(self);
    *fn_8043D28C(self, 0, 0) = x;
    *fn_8043D28C(self, 1, 1) = y;
    *fn_8043D28C(self, 2, 2) = z;
}
}

class Quat
{
public:
    char data[0x10];
    Quat(register float x, register float y, register float z, register float w);
};

Quat::Quat(register float x, register float y, register float z, register float w)
{
    fn_80434988(this);
    fn_80435300(this, x, y, z, w);
}

extern "C" {
void fn_8043D424(register void *self, register const void *src)
{
    fn_8043632C(self, src);
}

void fn_8043D464(register char *self, register const void *src)
{
    fn_8043632C(self + 0x30, src);
}

void fn_8043D4A8(register void *self, register int a)
{
    fn_8043F718(self, a);
}
}

class Rig
{
public:
    char data[0x30];
    char sub[0x10]; // +0x30
    Rig(register int a, register const void *b);
};

Rig::Rig(register int a, register const void *b)
{
    fn_8043F6D0(this, a);
    fn_80436370(sub, b);
}
