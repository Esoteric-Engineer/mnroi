// c:/Clash/mainline/Code/Game/handlers/control.cpp, from Global_PlayFESound (0x80104F80); see Game/fn_80104E88.cpp.

extern "C" {
void *fn_80432BC4();
int fn_804460BC(void *x);
void fn_80115308(int a, int b, int c);
void fn_80119AF8(int on);
}

// Emits no code. A top-level `return <parameter>;` makes cc1plus drop the function-end branch pair for every later function in the unit.
inline int sn_return_decl(int a) { return a; }

void Global_PlayFESound(int id)
{
    if (fn_804460BC(fn_80432BC4())) {
        return;
    }
    fn_80115308(0x12c, 0x70, id);
}

void Global_EnableBackgroundMusic(int on)
{
    fn_80119AF8(on);
}
