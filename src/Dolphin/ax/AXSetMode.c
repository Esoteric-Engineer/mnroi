extern unsigned long lbl_8066FA58;

void AXSetMode(unsigned long mode)
{
    if (lbl_8066FA58 != mode) {
        lbl_8066FA58 = mode;
    }
}
