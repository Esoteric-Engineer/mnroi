// fn_80020E60: the actor -> character type ID lookup.
//
// Built at -O0, and plain C: every return emits a single branch to the epilogue.
// The source file's real name and bounds are unknown.

// The actor info object fn_800B14A0 returns. Only two fields are used here, so the rest is padding; the name's length is a guess.
typedef struct ActorInfo
{
    char unk0[0xDC];
    char name[0x20];   // +0xDC entity name
    char unkFC[0x2D8];
    int typeId;        // +0x3D4 cached type ID, 0 until the first lookup
} ActorInfo;

extern int fn_800B0C58(void *actor);
extern ActorInfo *fn_800B14A0(void *actor);

extern char *strcpy(char *dst, const char *src);
extern char *strlwr(char *s);
extern int strlen(const char *s);
extern int strcmp(const char *a, const char *b);

// The character-name literals still belong to the auto-generated .rodata.
extern char lbl_804846B8[]; // "wolverine"
extern char lbl_804846C4[]; // "ironman"
extern char lbl_804846CC[]; // "spiderman"
extern char lbl_804846D8[]; // "venom"
extern char lbl_804846E0[]; // "magneto"
extern char lbl_804846E8[]; // "elektra"
extern char lbl_804846F0[]; // "storm"
extern char lbl_804846F8[]; // "humantorch"
extern char lbl_80484704[]; // "daredevil"
extern char lbl_80484710[]; // "thing"
extern char lbl_80484718[]; // "roekel"
extern char lbl_80484720[]; // "megalith"
extern char lbl_8048472C[]; // "defcon"
extern char lbl_80484734[]; // "paradox"
extern char lbl_8048473C[]; // "aftershock"
extern char lbl_80484748[]; // "johnnyohm"
extern char lbl_80484754[]; // "biohazard"
extern char lbl_80484760[]; // "heatwave"
extern char lbl_8048476C[]; // "alt_wolverine"
extern char lbl_8048477C[]; // "alt_ironman"
extern char lbl_80484788[]; // "alt_spiderman"
extern char lbl_80484798[]; // "alt_venom"
extern char lbl_804847A4[]; // "alt_magneto"
extern char lbl_804847B0[]; // "alt_elektra"
extern char lbl_804847BC[]; // "alt_storm"
extern char lbl_804847C8[]; // "alt_humantorch"
extern char lbl_804847D8[]; // "alt_daredevil"
extern char lbl_804847E8[]; // "alt_thing"
extern char lbl_804847F4[]; // "alt_roekel"
extern char lbl_80484800[]; // "alt_megalith"
extern char lbl_80484810[]; // "alt_defcon"
extern char lbl_8048481C[]; // "alt_paradox"
extern char lbl_80484828[]; // "alt_aftershock"
extern char lbl_80484838[]; // "alt_johnnyohm"
extern char lbl_80484848[]; // "alt_biohazard"
extern char lbl_80484858[]; // "alt_heatwave"
extern char lbl_80484868[]; // "human1"
extern char lbl_80484870[]; // "human2"
extern char lbl_80484878[]; // "human3"
extern char lbl_80484880[]; // "brute1"
extern char lbl_80484888[]; // "brute2"
extern char lbl_80484890[]; // "brute3"
extern char lbl_80484898[]; // "flier1"
extern char lbl_804848A0[]; // "flier2"
extern char lbl_804848A8[]; // "flier3"
extern char lbl_804848B0[]; // "Human"
extern char lbl_804848B8[]; // "businessmana"
extern char lbl_804848C8[]; // "businessmanb"
extern char lbl_804848D8[]; // "businesswomana"
extern char lbl_804848E8[]; // "businesswomanb"
extern char lbl_804848F8[]; // "securityguard"
extern char lbl_80484908[]; // "scientist"
extern char lbl_80484914[]; // "scientist1"
extern char lbl_80484920[]; // "scientist2"
extern char lbl_8048492C[]; // "scientist3"
extern char lbl_80484938[]; // "cop"

int fn_80020E60(void *actor)
{
    ActorInfo *info;
    char name[0x20];

    if (actor == 0 || fn_800B0C58(actor) == 0) {
        return -1;
    }

    info = fn_800B14A0(actor);
    if (info->typeId != 0) {
        return info->typeId;
    }

    strcpy(name, info->name);
    strlwr(name);

    if (strlen(name) == 0) {
        info->typeId = -1;
    }
    else if (strcmp(name, lbl_804846B8) == 0) {
        info->typeId = 1;
    }
    else if (strcmp(name, lbl_804846C4) == 0) {
        info->typeId = 2;
    }
    else if (strcmp(name, lbl_804846CC) == 0) {
        info->typeId = 3;
    }
    else if (strcmp(name, lbl_804846D8) == 0) {
        info->typeId = 4;
    }
    else if (strcmp(name, lbl_804846E0) == 0) {
        info->typeId = 5;
    }
    else if (strcmp(name, lbl_804846E8) == 0) {
        info->typeId = 6;
    }
    else if (strcmp(name, lbl_804846F0) == 0) {
        info->typeId = 7;
    }
    else if (strcmp(name, lbl_804846F8) == 0) {
        info->typeId = 8;
    }
    else if (strcmp(name, lbl_80484704) == 0) {
        info->typeId = 9;
    }
    else if (strcmp(name, lbl_80484710) == 0) {
        info->typeId = 10;
    }
    else if (strcmp(name, lbl_80484718) == 0) {
        info->typeId = 11;
    }
    else if (strcmp(name, lbl_80484720) == 0) {
        info->typeId = 12;
    }
    else if (strcmp(name, lbl_8048472C) == 0) {
        info->typeId = 13;
    }
    else if (strcmp(name, lbl_80484734) == 0) {
        info->typeId = 14;
    }
    else if (strcmp(name, lbl_8048473C) == 0) {
        info->typeId = 15;
    }
    else if (strcmp(name, lbl_80484748) == 0) {
        info->typeId = 16;
    }
    else if (strcmp(name, lbl_80484754) == 0) {
        info->typeId = 17;
    }
    else if (strcmp(name, lbl_80484760) == 0) {
        info->typeId = 18;
    }
    else if (strcmp(name, lbl_8048476C) == 0) {
        info->typeId = 21;
    }
    else if (strcmp(name, lbl_8048477C) == 0) {
        info->typeId = 22;
    }
    else if (strcmp(name, lbl_80484788) == 0) {
        info->typeId = 23;
    }
    else if (strcmp(name, lbl_80484798) == 0) {
        info->typeId = 24;
    }
    else if (strcmp(name, lbl_804847A4) == 0) {
        info->typeId = 25;
    }
    else if (strcmp(name, lbl_804847B0) == 0) {
        info->typeId = 26;
    }
    else if (strcmp(name, lbl_804847BC) == 0) {
        info->typeId = 27;
    }
    else if (strcmp(name, lbl_804847C8) == 0) {
        info->typeId = 28;
    }
    else if (strcmp(name, lbl_804847D8) == 0) {
        info->typeId = 29;
    }
    else if (strcmp(name, lbl_804847E8) == 0) {
        info->typeId = 30;
    }
    else if (strcmp(name, lbl_804847F4) == 0) {
        info->typeId = 31;
    }
    else if (strcmp(name, lbl_80484800) == 0) {
        info->typeId = 32;
    }
    else if (strcmp(name, lbl_80484810) == 0) {
        info->typeId = 33;
    }
    else if (strcmp(name, lbl_8048481C) == 0) {
        info->typeId = 34;
    }
    else if (strcmp(name, lbl_80484828) == 0) {
        info->typeId = 35;
    }
    else if (strcmp(name, lbl_80484838) == 0) {
        info->typeId = 36;
    }
    else if (strcmp(name, lbl_80484848) == 0) {
        info->typeId = 37;
    }
    else if (strcmp(name, lbl_80484858) == 0) {
        info->typeId = 38;
    }
    else if (strcmp(name, lbl_80484868) == 0) {
        info->typeId = 100;
    }
    else if (strcmp(name, lbl_80484870) == 0) {
        info->typeId = 100;
    }
    else if (strcmp(name, lbl_80484878) == 0) {
        info->typeId = 100;
    }
    else if (strcmp(name, lbl_80484880) == 0) {
        info->typeId = 101;
    }
    else if (strcmp(name, lbl_80484888) == 0) {
        info->typeId = 101;
    }
    else if (strcmp(name, lbl_80484890) == 0) {
        info->typeId = 101;
    }
    else if (strcmp(name, lbl_80484898) == 0) {
        info->typeId = 102;
    }
    else if (strcmp(name, lbl_804848A0) == 0) {
        info->typeId = 102;
    }
    else if (strcmp(name, lbl_804848A8) == 0) {
        info->typeId = 102;
    }
    else if (strcmp(name, lbl_804848B0) == 0) {
        info->typeId = 103;
    }
    else if (strcmp(name, lbl_804848B8) == 0) {
        info->typeId = 103;
    }
    else if (strcmp(name, lbl_804848C8) == 0) {
        info->typeId = 103;
    }
    else if (strcmp(name, lbl_804848D8) == 0) {
        info->typeId = 103;
    }
    else if (strcmp(name, lbl_804848E8) == 0) {
        info->typeId = 103;
    }
    else if (strcmp(name, lbl_804848F8) == 0) {
        info->typeId = 103;
    }
    else if (strcmp(name, lbl_80484908) == 0) {
        info->typeId = 103;
    }
    else if (strcmp(name, lbl_80484914) == 0) {
        info->typeId = 103;
    }
    else if (strcmp(name, lbl_80484920) == 0) {
        info->typeId = 103;
    }
    else if (strcmp(name, lbl_8048492C) == 0) {
        info->typeId = 103;
    }
    else if (strcmp(name, lbl_80484938) == 0) {
        info->typeId = 103;
    }
    else {
        info->typeId = -1;
    }

    return info->typeId;
}
