// Small leaf methods of the run after BaseF (docs/versus.md section 5): field resets, a vptr store, a getter, forwarders. Names are guesses.
class Quad
{
public:
    int a; // +0x0
    int b; // +0x4
    int c; // +0x8
    int d; // +0xC
    Quad *reset();
};

Quad *Quad::reset()
{
    a = -1;
    b = 0;
    c = -1;
    d = 0;
    return this;
}

extern "C" char lbl_804F5A60[];

class Vt
{
public:
    const void *vptr; // +0x0
    Vt *setVptr();
};

Vt *Vt::setVptr()
{
    vptr = lbl_804F5A60;
    return this;
}

class Big
{
public:
    char pad[0x7D8];
    int field; // +0x7D8
    int getField();
};

int Big::getField()
{
    return field;
}

class Chain
{
public:
    Chain *setup();
};

extern "C" void fn_8045F86C(Chain *self);

Chain *Chain::setup()
{
    fn_8045F86C(this);
    return this;
}

class Pair
{
public:
    int a; // +0x0
    int b; // +0x4
    Pair *clear();
};

Pair *Pair::clear()
{
    a = 0;
    b = 0;
    return this;
}

class Tail
{
public:
    int a; // +0x0
    int b; // +0x4
    Tail *clearB();
};

Tail *Tail::clearB()
{
    b = 0;
    return this;
}

class Fwd
{
public:
    Fwd *forward(int a, int b);
};

extern "C" Fwd *fn_801210F8(Fwd *self, int a, int b);

Fwd *Fwd::forward(register int a, register int b)
{
    return fn_801210F8(this, a, b);
}
