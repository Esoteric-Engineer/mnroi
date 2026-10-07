// Listener entry (guessed name) registered by fn_8044D84C; EntryBase and its vtable pair are in Game/fn_80433588.cpp.

extern "C" char lbl_804F5798[];

class EntryBase
{
public:
    void *x[3]; // +0x0; the real constructor also stores its own vptr at +0xC
    EntryBase();
};

class Listener : public EntryBase
{
public:
    const void *vptr; // +0xC
    Listener();
};

Listener::Listener() : vptr(lbl_804F5798) {}

extern "C" void fn_80433CF0(register void *self, register int inChrg);

extern "C" void fn_8044D980(register void *self, register int inChrg)
{
    fn_80433CF0(self, 0);
}
