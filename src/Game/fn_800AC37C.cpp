// Entity template property dispatcher: picks a handler by the property's kind (docs/versus.md steps 10 to 12).
struct PropInfo {
    char name[0x20];
    int kind; // +0x20
    int extra; // +0x24
};

extern PropInfo lbl_8048E748[]; // .rodata, 120 entries, indexed by property id

extern "C" {
int fn_800AE534(void *self, int *prop, int arg);
int fn_8007CA10(void *self, int *prop, int arg);
int fn_800B0C58(void *self);
int fn_80084498(void *self, int *prop, int arg);
int fn_80067248(void *self, int *prop, int arg);
int fn_800B0DA0(void *self);
int fn_8009E6AC(void *self, int *prop, int arg);
int fn_800AC750(void *self, int *prop, int arg);
int fn_800B0CC0(void *self);
void *fn_800B1478(void *self);
int fn_800A39F4(void *self, int *prop, int arg);
int fn_800B0E18(void *self);
void *fn_800B1518(void *self);
int fn_800A9F90(void *self, int *prop, int arg);
int fn_800B0F0C(void *self);
void *fn_800B1568(void *self);
int fn_80097750(void *self, int *prop, int arg);
int fn_800AEB90(void *self, int *prop, int arg);
}

extern "C" int fn_800AC37C(void *self, int *prop, int arg)
{
    switch (lbl_8048E748[prop[0]].kind) {
    case 0:
        return fn_800AE534(self, prop, arg);
    case 1:
        return 0;
    case 2:
        return fn_8007CA10(self, prop, arg);
    case 3:
        return 0;
    case 4:
    case 10:
        if (fn_800B0C58(self))
            return fn_80084498(self, prop, arg);
        else
            return 0;
    case 8:
        return fn_80067248(self, prop, arg);
    case 9:
        if (fn_800B0DA0(self))
            return fn_8009E6AC(self, prop, arg);
        else
            return 0;
    case 7:
        return fn_800AC750(self, prop, arg);
    case 11:
        if (fn_800B0CC0(self))
            return fn_800A39F4(fn_800B1478(self), prop, arg);
        else
            return 0;
    case 12:
        return 0;
    case 13:
        if (fn_800B0CC0(self))
            return fn_800A39F4(self, prop, arg);
        else
            return 0;
    case 14:
        if (fn_800B0E18(self))
            return fn_800A9F90(fn_800B1518(self), prop, arg);
        else
            return 0;
    case 15:
        if (fn_800B0F0C(self))
            return fn_80097750(fn_800B1568(self), prop, arg);
        else
            return 0;
    case 5:
    case 6:
    case 99:
        return fn_800AEB90(self, prop, arg);
    default:
        return 0;
    }
}
