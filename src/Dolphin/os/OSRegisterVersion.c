extern void OSReport(const char* msg, ...);
extern char lbl_8066C3C4[4];

#pragma peephole off
void OSRegisterVersion(const char* version)
{
    OSReport(lbl_8066C3C4, version);
}
