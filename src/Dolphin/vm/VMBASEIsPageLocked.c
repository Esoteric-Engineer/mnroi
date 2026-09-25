extern unsigned char* lbl_8066F988;

unsigned long VMBASEIsPageLocked(unsigned long page)
{
    return lbl_8066F988[page];
}
