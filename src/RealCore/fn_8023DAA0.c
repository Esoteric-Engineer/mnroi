// RealCore 6.27: the file system's shutdown, which cancels its alarm.
// Built at -O2 (docs/prodg.md, "Middleware").

extern void OSCancelAlarm(void *alarm);
extern void fn_8023DFB8(void);

extern unsigned char lbl_8066C869; // 1 while the alarm is armed
extern char lbl_8062C2A0[];        // OSAlarm

void fn_8023DAA0(void)
{
    if (lbl_8066C869) {
        lbl_8066C869 = 0;
        OSCancelAlarm(lbl_8062C2A0);
        fn_8023DFB8();
    }
}
