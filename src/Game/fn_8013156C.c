// Timed-match test: the timer mode G+0x75C is 1. See docs/versus.md (section 5, row 9a).

typedef struct {
    char pad[0x75C];
    int timerMode; // +0x75C
} State;

extern State lbl_80552110; // the game-state object G

int fn_8013156C(void)
{
    return lbl_80552110.timerMode == 1;
}

extern char lbl_8049A584[]; // the fallback name
extern char lbl_8054ED80[]; // the object fn_804326B4 turns into a tuning record

extern void *fn_804326B4(void *obj);
extern const char *fn_804426AC(void *record);
extern void *fn_80427400(void);
extern char *fn_8012F32C(void *table, const char *key);

const char *fn_801315A8(void)
{
    char *name;
    const char *localised;

    name = fn_804426AC(fn_804326B4(lbl_8054ED80));
    if (*name == '~') {
        localised = fn_8012F32C(fn_80427400(), name + 1);
        if (localised == 0) {
            return lbl_8049A584;
        }
        return localised;
    }
    return lbl_8049A584;
}
