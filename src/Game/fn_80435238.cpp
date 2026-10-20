// Forwards its argument to a list-broadcast call on self (first function of a pair-carrying file).

extern "C" void fn_80428EEC(void *self, int v);

extern "C" void fn_80435238(register void *self, register int v)
{
    fn_80428EEC(self, v);
}
