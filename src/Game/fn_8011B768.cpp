// Maps the level's track index (fn_80442E7C, 0-61) to 1-8; a random 1-8 in versus (docs/versus.md section 4.3). Its caller fn_8011C008 passes it to fn_801196F0.

extern "C" {

extern int fn_80432844(void *g);             // G+0x770
extern int fn_80432870(void *g);             // G+0x774
extern unsigned int fn_80435904(void);
extern void *fn_804326B4(void *table);
extern unsigned int fn_80442E7C(void *obj);

extern char lbl_80552110[]; // the game-state object G
extern char lbl_8054ED80[]; // the story/menu resource list

int fn_8011B768(void)
{
    int n = 1;

    if (fn_80432844(lbl_80552110) || fn_80432870(lbl_80552110))
        return fn_80435904() % 8 + 1;
    int track = fn_80442E7C(fn_804326B4(lbl_8054ED80));
    switch (track) {
    case 0:
        n = 4;
        break;
    case 1:
        n = 2;
        break;
    case 2:
        n = 1;
        break;
    case 3:
        n = 2;
        break;
    case 4:
        n = 8;
        break;
    case 5:
        n = 5;
        break;
    case 6:
        n = 3;
        break;
    case 7:
        n = 1;
        break;
    case 8:
        n = 1;
        break;
    case 9:
        n = 2;
        break;
    case 10:
        n = 2;
        break;
    case 11:
        n = 2;
        break;
    case 12:
        n = 5;
        break;
    case 13:
        n = 3;
        break;
    case 14:
        n = 3;
        break;
    case 15:
        n = 5;
        break;
    case 16:
        n = 1;
        break;
    case 17:
        n = 6;
        break;
    case 18:
        n = 3;
        break;
    case 19:
        n = 4;
        break;
    case 20:
        n = 7;
        break;
    case 21:
        n = 2;
        break;
    case 22:
        n = 2;
        break;
    case 23:
        n = 5;
        break;
    case 24:
        n = 3;
        break;
    case 25:
        n = 1;
        break;
    case 26:
        n = 2;
        break;
    case 27:
        n = 4;
        break;
    case 28:
        n = 3;
        break;
    case 29:
        n = 1;
        break;
    case 30:
        n = 1;
        break;
    case 31:
        n = 3;
        break;
    case 32:
        n = 6;
        break;
    case 33:
        n = 6;
        break;
    case 34:
        n = 3;
        break;
    case 35:
        n = 4;
        break;
    case 36:
        n = 6;
        break;
    case 37:
        n = 5;
        break;
    case 38:
        n = 3;
        break;
    case 39:
        n = 2;
        break;
    case 40:
        n = 8;
        break;
    case 41:
        n = 3;
        break;
    case 42:
        n = 4;
        break;
    case 43:
        n = 8;
        break;
    case 44:
        n = 7;
        break;
    case 45:
        n = 5;
        break;
    case 46:
        n = 2;
        break;
    case 47:
        n = 6;
        break;
    case 48:
        n = 1;
        break;
    case 49:
        n = 2;
        break;
    case 50:
        n = 6;
        break;
    case 51:
        n = 7;
        break;
    case 52:
        n = 4;
        break;
    case 53:
        n = 6;
        break;
    case 54:
        n = 7;
        break;
    case 55:
        n = 5;
        break;
    case 56:
        n = 4;
        break;
    case 57:
        n = 6;
        break;
    case 58:
        n = 8;
        break;
    case 59:
        n = 1;
        break;
    case 60:
        n = 3;
        break;
    case 61:
        n = 8;
        break;
    }
    return n;
}
}
