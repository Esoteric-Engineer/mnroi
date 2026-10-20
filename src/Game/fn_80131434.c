// The match clock: time left in the match, split into whole minutes and seconds.
// Field meanings are in docs/versus.md (section 5, row 9a).

typedef struct {
    char pad[0x764];
    int timeLimit; // +0x764
    int startTime; // +0x768 (guess)
} State;

extern State lbl_80552110; // the game-state object G
extern char lbl_80593BE8[]; // the globals object of Game/fn_80443908.cpp

extern int fn_8042EFF8(void *obj);
extern int fn_8042F024(void *obj);
extern void fn_801AFD14(int total, int *units, unsigned *a, unsigned *b, int *carry);

void fn_80131434(unsigned *a, unsigned *b)
{
    int units;
    int carry;
    int total;

    total = lbl_80552110.startTime + lbl_80552110.timeLimit - fn_8042EFF8(lbl_80593BE8) - fn_8042F024(lbl_80593BE8);
    if (total > 0) {
        fn_801AFD14(total, &units, a, b, &carry);
        *a = *a + units * 0x3C;
        if (carry != 0) {
            (*b)++;
            if (*b > 0x3B) {
                *b = 0;
                (*a)++;
            }
        }
    } else {
        *a = 0;
        *b = 0;
    }
}
