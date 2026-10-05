// c:/Clash/mainline/Code/Game/handlers/control.cpp, from PAL60_IsRequested (0x80106028); see Game/fn_80104E88.cpp.

extern "C" {
void *fn_80427400();
int fn_8042D584(void *locale);
}

// This file's pair state is clear here (the previous function's switch), so there is no sn_return_decl.
int PAL60_IsRequested()
{
    return 0;
}

void PAL60_Enable(int on)
{
}

void QuitDemo()
{
}

int GetRunMode()
{
    return -1;
}

int clashControl_GetLanguage()
{
    return fn_8042D584(fn_80427400());
}
