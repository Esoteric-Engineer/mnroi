// Voice: plays an actor's voice event (fn_8010CDCC) and the target-less variant (fn_8010D050). docs/characters.md section 5.

extern char lbl_80567720[];
extern int lbl_8066F04C;
extern int lbl_8066F050;
extern int lbl_8066F054;
extern int lbl_8066F058;
extern int lbl_8066F060;
extern int lbl_8066F064;

int fn_800B1168(void *self);
int fn_8009ABEC(void *self);
int fn_801155A8(int bank);
int fn_801154D8(int bank, int event);
void fn_80115308(int bank, int event, int arg);
int fn_800B13D8(void *self);
int fn_80114950(int a, int b);
int fn_800B0F0C(void *c);
int fn_800B0C1C(void *c);
void *fn_800B1568(void *c);
void *fn_800B14C8(void *c);
void *fn_80085954(void *p);
int fn_800CCA08(void *p);
int fn_800CCA88(void *p);
int fn_800CC9D8(void *p);
void fn_80115154(int bank, int event);
void fn_800B0958(void *self, void *rec);

int fn_8010CDCC(register void *self, int event, void *target, int a3, int a4, int a5, int a6)
{
    int dead = 0;
    int voice;
    void *p;

    if (fn_800B1168(self)) {
        return 0;
    }
    if (event == 0 && fn_801155A8(fn_8009ABEC(self))) {
        voice = fn_80114950(fn_800B13D8(self), fn_8009ABEC(self));
    }
    if (!fn_801154D8(fn_8009ABEC(self), event)) {
        return 1;
    }
    voice = fn_8009ABEC(self);
    if (target && fn_800B0F0C(target)) {
        if (fn_800B0C1C(target) && fn_8009ABEC(fn_800B1568(target)) == 0x11) {
            p = fn_80085954(fn_800B14C8(target));
            if (fn_800CCA08(p) || fn_800CCA88(p)) {
                lbl_8066F060 = 0;
            }
        } else if (fn_8009ABEC(self) == 0x11) {
            voice = 4;
        }
    } else if (fn_8009ABEC(self) == 0x11) {
        voice = 4;
    }
    lbl_8066F04C = fn_800B13D8(self);
    fn_800B0958(self, lbl_80567720);
    lbl_8066F058 = a3;
    lbl_8066F054 = 0;
    lbl_8066F050 = voice;
    lbl_8066F064 = a4;
    if (target && fn_800B0F0C(target)) {
        lbl_8066F054 = fn_8009ABEC(fn_800B1568(target));
    }
    fn_80115308(fn_8009ABEC(self), event, a5);
    return 1;
}

int fn_8010D050(register void *self, int event, int bank, int a2, int a3, void *target, int a5)
{
    int dead = 0;
    void *p;

    if (fn_800B1168(self)) {
        return 0;
    }
    if (!fn_801154D8(bank, event)) {
        return 1;
    }
    lbl_8066F04C = fn_800B13D8(self);
    fn_800B0958(self, lbl_80567720);
    lbl_8066F058 = a3;
    lbl_8066F064 = a2;
    lbl_8066F054 = 0;
    lbl_8066F050 = fn_8009ABEC(self);
    lbl_8066F060 = 0;
    if (target && fn_800B0F0C(target)) {
        lbl_8066F054 = fn_8009ABEC(fn_800B1568(target));
        if (fn_800B0C1C(target)) {
            p = fn_80085954(fn_800B14C8(target));
            if (fn_800CCA08(p) && lbl_8066F054 != 0x11) {
                lbl_8066F060 = 3;
            } else if (fn_800CC9D8(p)) {
                lbl_8066F060 = 1;
            } else if (fn_800CCA88(p) && lbl_8066F054 != 0x11) {
                lbl_8066F060 = 2;
            }
        }
    }
    fn_80115154(bank, event);
    return 1;
}
