// Effect system init: creates the "MC:EFF" heap and registers the 32 effect classes; a class's index is its game.nfx type word.
// fn_8039DAA0 puts {factory, size} at lbl_8066B0E0[n] and the name in the "effectclass" registry; docs/characters.md "Effects".
// The real name is unknown, so the symbol stays extern "C".

inline int sn_return_decl(int a) { return a; }

struct EffectSystem
{
    char pad0[0x610];
    char f610[0x2F0]; // +0x610
    char f900[0x30E0]; // +0x900
    int f39E0; // +0x39E0
};

extern int lbl_8066CC48;
extern int lbl_8066C660;
extern void *lbl_8066CC5C;
extern const char lbl_804BC118[];
extern const char lbl_804BC120[];

extern const char lbl_804BC12C[];
extern const char lbl_804BC138[];
extern const char lbl_804BC140[];
extern const char lbl_804BC148[];
extern const char lbl_804BC154[];
extern const char lbl_804BC160[];
extern const char lbl_804BC16C[];
extern const char lbl_804BC174[];
extern const char lbl_804BC180[];
extern const char lbl_804BC188[];
extern const char lbl_804BC194[];
extern const char lbl_804BC1A0[];
extern const char lbl_804BC1AC[];
extern const char lbl_804BC1BC[];
extern const char lbl_804BC1C8[];
extern const char lbl_804BC1D0[];
extern const char lbl_804BC1E0[];
extern const char lbl_804BC1EC[];
extern const char lbl_804BC1F8[];
extern const char lbl_804BC208[];
extern const char lbl_804BC214[];
extern const char lbl_804BC21C[];
extern const char lbl_804BC228[];
extern const char lbl_804BC238[];
extern const char lbl_804BC240[];
extern const char lbl_804BC24C[];
extern const char lbl_804BC258[];
extern const char lbl_804BC260[];
extern const char lbl_804BC268[];
extern const char lbl_804BC270[];
extern const char lbl_804BC280[];
extern const char lbl_804BC288[];

extern "C" {
int fn_801AC3B4(const char *name, int size, int flags);
void fn_8038AEB8(void *p);
void fn_803CB1F0(void *p);
void *fn_801B4284(int capacity, const char *name);
void fn_8039DAA0(const char *name, void *(*factory)(), int size);
void *fn_803F61D0();
void *fn_803DD070();
void *fn_803CDA10();
void *fn_803CDDE8();
void *fn_803CDE94();
void *fn_803CDF80();
void *fn_80387F50();
void *fn_803CE168();
void *fn_803CE31C();
void *fn_803AA4CC();
void *fn_803D9D68();
void *fn_803E21BC();
void *fn_803E220C();
void *fn_803CE5B4();
void *fn_803CE444();
void *fn_803A9F98();
void *fn_803DFB48();
void *fn_803EE32C();
void *fn_803FE66C();
void *fn_8038DBA8();
void *fn_803FEEF4();
void *fn_803F62D4();
void *fn_803DFA70();
void *fn_80392448();
void *fn_80392764();
void *fn_803928B0();
void *fn_80392860();
void *fn_803F64DC();
void *fn_803CE604();
void *fn_803DFE50();
void *fn_803E479C();
void *fn_8039D98C();
}

extern "C" void fn_8039E22C(register EffectSystem *self)
{
    if (lbl_8066CC48 == -99) {
        lbl_8066CC48 = fn_801AC3B4(lbl_804BC118, 0x6400, 1);
    }
    lbl_8066C660 = 1;
    fn_8038AEB8(self->f610);
    lbl_8066C660 = 1;
    fn_803CB1F0(self->f900);
    self->f39E0 = 1;
    lbl_8066CC5C = fn_801B4284(0x80, lbl_804BC120);
    fn_8039DAA0(lbl_804BC12C, fn_803F61D0, 0xF0); // controller
    fn_8039DAA0(lbl_804BC138, fn_803DD070, 0x120); // trail
    fn_8039DAA0(lbl_804BC140, fn_803CDA10, 0x290); // partsys
    fn_8039DAA0(lbl_804BC148, fn_803CDDE8, 0x2A0); // partsysdam
    fn_8039DAA0(lbl_804BC154, fn_803CDE94, 0x2A0); // partsubfx
    fn_8039DAA0(lbl_804BC160, fn_803CDF80, 0x2A0); // partmodel
    fn_8039DAA0(lbl_804BC16C, fn_80387F50, 0x130); // glow
    fn_8039DAA0(lbl_804BC174, fn_803CE168, 0x2B0); // constraint
    fn_8039DAA0(lbl_804BC180, fn_803CE31C, 0x2D0); // cloth
    fn_8039DAA0(lbl_804BC188, fn_803AA4CC, 0x160); // shockwave
    fn_8039DAA0(lbl_804BC194, fn_803D9D68, 0x2B0); // psishield
    fn_8039DAA0(lbl_804BC1A0, fn_803E21BC, 0xF0); // billboard
    fn_8039DAA0(lbl_804BC1AC, fn_803E220C, 0xF0); // billboardomni
    fn_8039DAA0(lbl_804BC1BC, fn_803CE5B4, 0x1D0); // volumefog
    fn_8039DAA0(lbl_804BC1C8, fn_803CE444, 0x8C0); // rain
    fn_8039DAA0(lbl_804BC1D0, fn_803A9F98, 0x1C0); // partcylinder
    fn_8039DAA0(lbl_804BC1E0, fn_803DFB48, 0x130); // actorglow
    fn_8039DAA0(lbl_804BC1EC, fn_803EE32C, 0x190); // energybeam
    fn_8039DAA0(lbl_804BC1F8, fn_803FE66C, 0x140); // lasertripwire
    fn_8039DAA0(lbl_804BC208, fn_8038DBA8, 0x160); // gibomatic2k
    fn_8039DAA0(lbl_804BC214, fn_803FEEF4, 0x1F0); // dyngeom
    fn_8039DAA0(lbl_804BC21C, fn_803F62D4, 0x140); // ctrldamage
    fn_8039DAA0(lbl_804BC228, fn_803DFA70, 0x130); // radiuseffect
    fn_8039DAA0(lbl_804BC238, fn_80392448, 0x180); // light
    fn_8039DAA0(lbl_804BC240, fn_80392764, 0x320); // projectcube
    fn_8039DAA0(lbl_804BC24C, fn_803928B0, 0x420); // boxproject
    fn_8039DAA0(lbl_804BC258, fn_80392860, 0x410); // project
    fn_8039DAA0(lbl_804BC260, fn_803F64DC, 0x130); // spawner
    fn_8039DAA0(lbl_804BC268, fn_803CE604, 0x2A0); // glass
    fn_8039DAA0(lbl_804BC270, fn_803DFE50, 0x100); // meshtypeflash
    fn_8039DAA0(lbl_804BC280, fn_803E479C, 0x160); // damage
    fn_8039DAA0(lbl_804BC288, fn_8039D98C, 0xF0); // worldfx
    lbl_8066C660 = 0;
}
