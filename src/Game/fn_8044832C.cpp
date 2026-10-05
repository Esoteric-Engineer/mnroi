// Tests bit 0x4 of the flags word at +0x10; the unit's first function leaves the C++ end-branch pair set.
struct GxState
{
    char pad[0x10];
    unsigned int flags; // +0x10
    int fn_8044832C();
};

int GxState::fn_8044832C()
{
    return flags & 4;
}
