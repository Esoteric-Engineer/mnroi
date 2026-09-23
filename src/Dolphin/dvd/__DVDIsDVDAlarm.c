extern char lbl_8057D290[];
extern char AlarmForTimeout[];
extern char AlarmForBreak[];

int __DVDIsDVDAlarm(void* alarm)
{
    if (alarm == AlarmForBreak) {
        return 1;
    }
    if (alarm == AlarmForTimeout) {
        return 1;
    }
    return 0;
}
