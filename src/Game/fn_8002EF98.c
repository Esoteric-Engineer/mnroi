// Maps the Dolphin language setting to the game's language index; see docs/versus.md section 5, row 9d.

extern unsigned char OSGetLanguage(void);

int fn_8002EF98(void)
{
    int result = 0;
    unsigned char lang = OSGetLanguage();

    switch (lang) {
    case 0:
        result = 0;
        break;
    case 2:
        result = 1;
        break;
    case 1:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    case 4:
        result = 4;
        break;
    default:
        result = 0;
        break;
    }
    return result;
}
