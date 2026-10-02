extern char lbl_8057D290[];
extern int __DVDIsDVDAlarm(void* alarm);

int fn_80186590(void* alarm)
{
    if (alarm == lbl_8057D290) {
        return 1;
    }
    return __DVDIsDVDAlarm(alarm);
}
