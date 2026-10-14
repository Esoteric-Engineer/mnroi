// Fetches the fm_* cutscene name (PLAYER field 206 + `other`'s body class) of the actor in `slot` and hands it to fn_80057894 with `value`; docs/versus.md row 20.

extern void *fn_8042FF2C(void *slot); // slot+0x28, the slot's actor
extern int fn_8009AC68(void *actor);
extern int fn_800ACD20(void *actor, int id);
extern void fn_80057894(int a, int b);

void fn_80096460(register void *slot, void *other, int value)
{
    register void *actor = fn_8042FF2C(slot);

    fn_80057894(fn_800ACD20(actor, fn_8009AC68(other) + 0xCE), value);
}
