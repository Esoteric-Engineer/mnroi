// Wallflip state's event handler.

extern "C" int fn_800D0020(register void *self, int ch, int type, int value, int extra)
{
    switch (type) {
    case 0x14:
    case 0x1E:
        break;
    default:
        return 0;
    }
    return 1;
}
