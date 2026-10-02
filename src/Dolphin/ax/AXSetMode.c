extern unsigned long __AXClMode;

void AXSetMode(unsigned long mode)
{
    if (__AXClMode != mode) {
        __AXClMode = mode;
    }
}
