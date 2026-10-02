extern unsigned char* lbl_8066F988;

void VMBASESetPageLocked(unsigned long page, int locked)
{
    if (locked) {
        lbl_8066F988[page] = 1;
    } else {
        lbl_8066F988[page] = 0;
    }
}
