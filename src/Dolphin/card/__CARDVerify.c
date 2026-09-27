typedef long s32;

extern s32 VerifyID(void* card);
extern s32 VerifyDir(void* card, s32* outCurrent);
extern s32 VerifyFAT(void* card, s32* outCurrent);

s32 __CARDVerify(void* card)
{
    s32 result;
    int errors;

    result = VerifyID(card);
    if (result < 0)
        return result;

    errors = VerifyDir(card, 0);
    errors += VerifyFAT(card, 0);
    switch (errors) {
    case 0:
        return 0;
    case 1:
        return -6;
    default:
        return -6;
    }
}
