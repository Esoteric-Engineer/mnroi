// The loading-screen singleton's getter (docs/core.md row 19). Class name is a guess.

inline int sn_return_decl(int a) { return a; }

class LoadScreen
{
public:
    char data[0x1820];
    LoadScreen() __asm__("fn_80015248");
};

extern "C" LoadScreen *lbl_8066B54C;

extern "C" LoadScreen *fn_8042D4CC()
{
    if (lbl_8066B54C == 0) {
        lbl_8066B54C = new LoadScreen;
    }
    return lbl_8066B54C;
}
