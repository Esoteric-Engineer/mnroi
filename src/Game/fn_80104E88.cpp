// c:/Clash/mainline/Code/Game/handlers/control.cpp, Global_StartAudio (0x80104E88); the file is split around its String-parameter handlers, which are units of their own.

extern "C" void fn_80435238(void *audio, int a);

extern char lbl_80572330[];

// Emits no code. A top-level `return <parameter>;` makes cc1plus drop the function-end branch pair for every later function in the unit.
inline int sn_return_decl(int a) { return a; }

void Global_StartAudio()
{
    fn_80435238(lbl_80572330, 0);
}
