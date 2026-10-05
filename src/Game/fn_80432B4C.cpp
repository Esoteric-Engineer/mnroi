// Three "X:Instance" singleton getters: log the name, `new` the object once, log "".
// Pair-less C++, so sn_return_decl comes first (docs/prodg.md). The strings are externs: the pool is cyclic to claim.

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_801ACE74(const char *name);

extern char lbl_80485520[]; // lbl_80485520
extern char lbl_80485538[]; // ""
extern char lbl_8048553C[]; // lbl_8048553C
extern char lbl_80485554[]; // lbl_80485554

class CAsyncLoader { public: CAsyncLoader(); char data[0x40]; };
class cMoviePlayer { public: cMoviePlayer(); char data[0x104]; };
class cAttractMovie { public: cAttractMovie(); char data[0x18]; };

extern CAsyncLoader *lbl_8066BEE4;
extern cMoviePlayer *lbl_8066BF94;
extern cAttractMovie *lbl_8066BF98;

extern "C" {

CAsyncLoader *fn_80432B4C()
{
    if (lbl_8066BEE4 == 0)
    {
        fn_801ACE74(lbl_80485520);
        lbl_8066BEE4 = new CAsyncLoader;
        fn_801ACE74(lbl_80485538);
    }
    return lbl_8066BEE4;
}

cMoviePlayer *fn_80432BC4()
{
    if (lbl_8066BF94 == 0)
    {
        fn_801ACE74(lbl_8048553C);
        lbl_8066BF94 = new cMoviePlayer;
        fn_801ACE74(lbl_80485538);
    }
    return lbl_8066BF94;
}

cAttractMovie *fn_80432C3C()
{
    if (lbl_8066BF98 == 0)
    {
        fn_801ACE74(lbl_80485554);
        lbl_8066BF98 = new cAttractMovie;
        fn_801ACE74(lbl_80485538);
    }
    return lbl_8066BF98;
}

}
