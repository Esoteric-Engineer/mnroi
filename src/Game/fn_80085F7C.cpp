// The ACTOR_ABILITIES accessors (actor+0x308, bits in docs/characters.md section 3). Each is a method of the actor class; the labels give them their fn_ names.

class Actor
{
public:
    char pad0[0x308];
    unsigned int abilities; // +0x308
    int a80085F7C();
    int a80085FAC();
    int a80085FDC();
    int a8008600C();
    int a8008603C();
    int a8008606C();
    int a8008609C();
    int a800860CC();
    int a800860FC();
    int a8008612C();
    int a8008615C();
    int a8008618C();
    int a800861BC();
    int a800861EC();
    int a8008621C();
    int a8008624C();
    int a8008627C();
    int a800862AC();
    int a800862DC();
    int a80086314();
    int a80086344();
    int a80086374();
};

inline int sn_return_decl(int a) { return a; }

__asm__(".text\n\t.globl fn_80085F7C\n\t.type fn_80085F7C,@function\nfn_80085F7C:");
int Actor::a80085F7C()
{
    return abilities & 1;
}
__asm__(".size fn_80085F7C, 0x30");

__asm__(".text\n\t.globl fn_80085FAC\n\t.type fn_80085FAC,@function\nfn_80085FAC:");
int Actor::a80085FAC()
{
    return abilities & 0x100000;
}
__asm__(".size fn_80085FAC, 0x30");

__asm__(".text\n\t.globl fn_80085FDC\n\t.type fn_80085FDC,@function\nfn_80085FDC:");
int Actor::a80085FDC()
{
    return abilities & 0x200;
}
__asm__(".size fn_80085FDC, 0x30");

__asm__(".text\n\t.globl fn_8008600C\n\t.type fn_8008600C,@function\nfn_8008600C:");
int Actor::a8008600C()
{
    return abilities & 0x400000;
}
__asm__(".size fn_8008600C, 0x30");

__asm__(".text\n\t.globl fn_8008603C\n\t.type fn_8008603C,@function\nfn_8008603C:");
int Actor::a8008603C()
{
    return abilities & 0x2;
}
__asm__(".size fn_8008603C, 0x30");

__asm__(".text\n\t.globl fn_8008606C\n\t.type fn_8008606C,@function\nfn_8008606C:");
int Actor::a8008606C()
{
    return abilities & 0x80;
}
__asm__(".size fn_8008606C, 0x30");

__asm__(".text\n\t.globl fn_8008609C\n\t.type fn_8008609C,@function\nfn_8008609C:");
int Actor::a8008609C()
{
    return abilities & 0x20000;
}
__asm__(".size fn_8008609C, 0x30");

__asm__(".text\n\t.globl fn_800860CC\n\t.type fn_800860CC,@function\nfn_800860CC:");
int Actor::a800860CC()
{
    return abilities & 0x40;
}
__asm__(".size fn_800860CC, 0x30");

__asm__(".text\n\t.globl fn_800860FC\n\t.type fn_800860FC,@function\nfn_800860FC:");
int Actor::a800860FC()
{
    return abilities & 0x2000;
}
__asm__(".size fn_800860FC, 0x30");

__asm__(".text\n\t.globl fn_8008612C\n\t.type fn_8008612C,@function\nfn_8008612C:");
int Actor::a8008612C()
{
    return abilities & 0x4000000;
}
__asm__(".size fn_8008612C, 0x30");

__asm__(".text\n\t.globl fn_8008615C\n\t.type fn_8008615C,@function\nfn_8008615C:");
int Actor::a8008615C()
{
    return abilities & 0x8;
}
__asm__(".size fn_8008615C, 0x30");

__asm__(".text\n\t.globl fn_8008618C\n\t.type fn_8008618C,@function\nfn_8008618C:");
int Actor::a8008618C()
{
    return abilities & 0x8000;
}
__asm__(".size fn_8008618C, 0x30");

__asm__(".text\n\t.globl fn_800861BC\n\t.type fn_800861BC,@function\nfn_800861BC:");
int Actor::a800861BC()
{
    return abilities & 0x1000;
}
__asm__(".size fn_800861BC, 0x30");

__asm__(".text\n\t.globl fn_800861EC\n\t.type fn_800861EC,@function\nfn_800861EC:");
int Actor::a800861EC()
{
    return abilities & 0x2000000;
}
__asm__(".size fn_800861EC, 0x30");

__asm__(".text\n\t.globl fn_8008621C\n\t.type fn_8008621C,@function\nfn_8008621C:");
int Actor::a8008621C()
{
    return abilities & 0x10;
}
__asm__(".size fn_8008621C, 0x30");

__asm__(".text\n\t.globl fn_8008624C\n\t.type fn_8008624C,@function\nfn_8008624C:");
int Actor::a8008624C()
{
    return abilities & 0x20;
}
__asm__(".size fn_8008624C, 0x30");

__asm__(".text\n\t.globl fn_8008627C\n\t.type fn_8008627C,@function\nfn_8008627C:");
int Actor::a8008627C()
{
    return abilities & 0x1000000;
}
__asm__(".size fn_8008627C, 0x30");

__asm__(".text\n\t.globl fn_800862AC\n\t.type fn_800862AC,@function\nfn_800862AC:");
int Actor::a800862AC()
{
    return abilities & 0x100;
}
__asm__(".size fn_800862AC, 0x30");

__asm__(".text\n\t.globl fn_800862DC\n\t.type fn_800862DC,@function\nfn_800862DC:");
int Actor::a800862DC()
{
    return ((abilities >> 27) ^ 1) & 1;
}
__asm__(".size fn_800862DC, 0x38");

__asm__(".text\n\t.globl fn_80086314\n\t.type fn_80086314,@function\nfn_80086314:");
int Actor::a80086314()
{
    return abilities & 0x10000000;
}
__asm__(".size fn_80086314, 0x30");

__asm__(".text\n\t.globl fn_80086344\n\t.type fn_80086344,@function\nfn_80086344:");
int Actor::a80086344()
{
    return abilities & 0x20000000;
}
__asm__(".size fn_80086344, 0x30");

__asm__(".text\n\t.globl fn_80086374\n\t.type fn_80086374,@function\nfn_80086374:");
int Actor::a80086374()
{
    return abilities & 0x810004;
}
__asm__(".size fn_80086374, 0x38");
