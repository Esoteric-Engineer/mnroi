// Destructor of the shape whose constructor is in Game/fn_80435E68.cpp (hand-written C, docs/matching_notes.md).

extern void fn_80436EBC(void *self, int chrg);
extern void fn_80436DD0(void *self);

void fn_80435F1C(register void *self, register int chrg)
{
    fn_80436EBC(self, 0);
    if (chrg & 1) {
        fn_80436DD0(self);
    }
}
