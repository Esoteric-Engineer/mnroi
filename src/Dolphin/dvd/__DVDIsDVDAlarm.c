extern char lbl_8057D290[];
extern char AlarmForTimeout[];
extern char lbl_8057D3D8[];

int __DVDIsDVDAlarm(void* alarm)
{
    if (alarm == lbl_8057D3D8) {
        return 1;
    }
    if (alarm == AlarmForTimeout) {
        return 1;
    }
    return 0;
}
