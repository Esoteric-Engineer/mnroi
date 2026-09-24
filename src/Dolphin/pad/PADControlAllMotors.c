typedef unsigned char u8;
typedef unsigned int u32;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL enabled);
extern u32 SIGetType(int chan);
extern void SISetCommand(int chan, u32 command);
extern void SITransferCommands(void);

extern u32 lbl_8066F3DC;
extern u32 lbl_8066C4A4;
extern u32 lbl_8066C4A8;

u8 __gUnknown800030E3 : 0x800030E3;

void PADControlAllMotors(const u32* commandArray)
{
    BOOL enabled;
    int chan;
    u32 command;
    BOOL commit;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    commit = 0;

    for (chan = 0; chan < 4; chan++, commandArray++) {
        chanBit = 0x80000000 >> chan;
        if ((lbl_8066F3DC & chanBit) && !(SIGetType(chan) & 0x20000000)) {
            command = *commandArray;
            if (lbl_8066C4A8 < 2 && command == 2) {
                command = 0;
            }
            if (__gUnknown800030E3 & 0x20) {
                command = 0;
            }
            SISetCommand(chan, 0x400000 | lbl_8066C4A4 | (command & 3));
            commit = 1;
        }
    }
    if (commit) {
        SITransferCommands();
    }
    OSRestoreInterrupts(enabled);
}
