// A player's chosen character: its entity name with fallbacks, its localised display name, and
// the local player's entity name. Field meanings are in docs/versus.md and docs/characters.md.

extern char lbl_80552110[];  // the game-state object G
extern char lbl_8054ED80[];  // the object fn_804326B4 turns into a tuning record
extern char lbl_8049A56C[];  // "plr_wolverine"

extern int fn_80130718(void);             // a match is running
extern void *fn_804317BC(void *g, int i); // &G.slots[i]
extern int fn_80443BF4(void *slot);       // slot+0x34 bit 0, the slot is in use
extern char *fn_80443BC8(void *slot);     // slot+0x4, the chosen character's entity name
extern void *fn_804326B4(void *obj);
extern char *fn_80461174(void *record);   // record+0x320

char *fn_80131060(int player)
{
    char *name;

    if (player > 1) {
        return lbl_8049A56C;
    }

    if (fn_80130718()) {
        if (fn_80443BF4(fn_804317BC(lbl_80552110, player))) {
            name = fn_80443BC8(fn_804317BC(lbl_80552110, player));
            return name;
        } else {
            if (fn_804326B4(lbl_8054ED80) && *fn_80461174(fn_804326B4(lbl_8054ED80)) != '\0') {
                return fn_80461174(fn_804326B4(lbl_8054ED80));
            } else {
                return lbl_8049A56C;
            }
        }
    } else {
        name = fn_80443BC8(fn_804317BC(lbl_80552110, player));
        return name;
    }
}

extern char lbl_8049A57C[]; // "plr_alt"

extern char *strstr(const char *haystack, const char *needle);
extern char *fn_80461288(char *name, int alt); // entity name -> the roster's localisation key
extern void *fn_80427400(void);
extern char *fn_8012F32C(void *table, const char *key);

const char *fn_801311C0(int player)
{
    char *name;
    int alt;
    const char *key;
    const char *localised;

    name = fn_80131060(player);
    alt = 0;
    if (strstr(name, lbl_8049A57C)) {
        alt = 1;
    }

    key = fn_80461288(name, alt);
    if (key != 0 && *key == '~') {
        localised = fn_8012F32C(fn_80427400(), key + 1);
        return localised;
    }
    return key;
}

extern char lbl_8049A52C[]; // ""
extern int lbl_8066B59C;

extern int fn_80130A1C(void);
extern void *fn_800ACFA8(int handle);
extern char *fn_800FC3DC(char *name);

const char *fn_80131294(void)
{
    register char *tmp;
    char *actor;

    if (!fn_80130A1C()) {
        return lbl_8049A52C;
    }
    tmp = fn_800ACFA8(lbl_8066B59C);
    actor = tmp;
    return fn_800FC3DC(actor + 0xFC); // +0xFC, the entity name
}
