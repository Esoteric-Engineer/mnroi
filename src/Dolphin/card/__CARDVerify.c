typedef long s32;

extern s32 fn_8040BCE0(void* card);
extern s32 fn_8040BF64(void* card, s32* outCurrent);
extern s32 fn_8040C1A4(void* card, s32* outCurrent);

s32 __CARDVerify(void* card)
{
    s32 result;
    int errors;

    result = fn_8040BCE0(card);
    if (result < 0)
        return result;

    errors = fn_8040BF64(card, 0);
    errors += fn_8040C1A4(card, 0);
    switch (errors) {
    case 0:
        return 0;
    case 1:
        return -6;
    default:
        return -6;
    }
}
