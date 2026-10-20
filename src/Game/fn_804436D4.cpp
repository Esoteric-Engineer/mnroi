// The roster unlock setter: sets `unlocked` on both the base and the alternate record of a character.
// The records are bound to reference locals, which is what puts each call result in a call-saved register first.
struct CharacterRecord
{
    char entityName[0x20];
    char nameKey[0x20];
    signed char stats[6];
    signed char unk46[2];
    int unlocked; // +0x48
};

extern "C" CharacterRecord &fn_80431CCC(int index, int remap, int alt);

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_804436D4(register int index, register int unlocked, register int remap)
{
    CharacterRecord &base = fn_80431CCC(index, remap, 0);
    CharacterRecord &alt = fn_80431CCC(index, remap, 1);

    base.unlocked = unlocked;
    alt.unlocked = unlocked;
}
