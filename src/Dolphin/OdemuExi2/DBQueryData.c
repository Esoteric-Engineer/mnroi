typedef unsigned long u32;
typedef unsigned char u8;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL enabled);
extern void DBGReadStatus(u32* status);
extern void DBGReadMailbox(u32* mail);

extern u32 lbl_8066F4C8;
extern int lbl_8066F4CC;
extern u8 lbl_8066F4D4;

static void CheckMailBox(void)
{
    u32 mail[2];

    DBGReadStatus(mail);
    if (mail[0] & 1) {
        DBGReadMailbox(mail);
        mail[0] &= ~0xE0000000;
        if ((mail[0] & 0x1F000000) == 0x1F000000) {
            lbl_8066F4C8 = mail[0];
            lbl_8066F4CC = mail[0] & 0x7FFF;
            lbl_8066F4D4 = 1;
        }
    }
}

u32 DBQueryData(void)
{
    BOOL enable;

    lbl_8066F4D4 = 0;
    if (lbl_8066F4CC == 0) {
        enable = OSDisableInterrupts();
        CheckMailBox();
        OSRestoreInterrupts(enable);
    }
    return lbl_8066F4CC;
}
