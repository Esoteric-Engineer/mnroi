// c:/Clash/mainline/Code/Game/handlers/control.cpp: the static initializer (0x8010611C), which sets the four screen-edge floats and registers every handler with the APT script engine (docs/versus.md section 1).
//
// Hand-written like Game/handlers/characterselect.cpp (matching_notes.md); the registration objects are empty classes in the original.

// 0x4C-byte string and the APT object, only so the handler declarations below mangle like the originals.
class String {
public:
    char data[0x4C];
    ~String();
};

class AptObject {
public:
    ~AptObject();
    void *unk0;
    int unk4;
};

// Handlers, in other units.
int gPALMode();
int gWidescreenMode();
int gDemoLaunchInto();
String gDebugEnable();
int gArtistBuild();
int gFranchise();
int gE3Demo();
int gMagazineDemo();
int gIsOnline();
String gInGame();
String gBEDisplayScreen();
String gPlatform();
void Control_ChangeScreen(String screen);
void Control_EnableControllerCheck(int on);
void Control_SetMatchInfo(int matchType, int timed, int unused, int seconds);
void Control_SetSelectInfo(int, int, int, int, int, int, void *);
void Control_StartLoad();
void Control_StartProgressBar(int a, int b);
void Control_StartGame();
void Control_EndOfMatch(int result);
void Control_EndOfMission(int result);
int Control_GetNewUnlockable();
int Control_GetNewUnlockableID();
void Control_ToggleLanguage();
String Locale_GetString(String key);
void Global_StartAudio();
void Global_PlayUISound(String name);
void Global_PlayFESound(int id);
void Global_EnableBackgroundMusic(int on);
void Global_PlayFEStream(String name);
void Global_StopFEStream();
int Locale_GetLanguage();
void Control_EnableBackgroundDraw(int on);
AptObject Control_StartScreenFunction(int screen);
int Control_GetControllerStatus(int pad);
void Control_BindController(int pad, int ctrl);
void Movie_Play(int id);
void Movie_Stop();
void Cheat_UnlockAll();
AptObject Reward_GetTrailerInfo();
AptObject Reward_GetCardsInfo();
int Reward_GetNumCards();
AptObject Reward_GetComicsInfo();
int Reward_GetNumComics();
void PauseMenu_SetSFXLevel(int level);
void PauseMenu_SetMusicLevel(int level);
void PauseMenu_SetSpeechLevel(int level);
void PauseMenu_ReturnToGame();
void PauseMenu_Quit();
void *PauseMenu_GetLastPauser();
int PauseMenu_OnlineTimeLeft();
int PauseMenu_OnlineCount();
int PauseMenu_OnlineCountLimit();
void clashPauseMenu_Exit2Game();
void clashPauseMenu_SelectItem(int item, int pauser);
void Timer_Delay(int ms);
void Timer_Stop();
void AttractMode_Enable(int on);
String Cheat_Enable(String code);
int PAL60_IsRequested();
void PAL60_Enable(int on);
void QuitDemo();
int GetRunMode();
int clashControl_GetLanguage();

extern "C" {
void *fn_8044AF58(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044B11C(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044BBC8(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044BD90(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044BF9C(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044C35C(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044C634(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044C9E4(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044CC2C(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044CE44(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044D060(void *reg, const char *name, void *func, const char *file, int line);
void *fn_8044D270(void *reg, const char *name, void *func, const char *file, int line);
}

extern float lbl_8066BB14; // sdata
extern float lbl_8066BB18; // sdata

// Literals still owned by the auto-generated .rodata.
extern char lbl_804905DC[]; // this file's path
extern char lbl_804905D0[]; // "gPALMode"
extern char lbl_80490610[]; // "gWidescreenMode"
extern char lbl_80490620[]; // "gDemoLaunchInto"
extern char lbl_80490630[]; // "gDebugEnable"
extern char lbl_80490640[]; // "gArtistBuild"
extern char lbl_80490650[]; // "gFranchise"
extern char lbl_8049065C[]; // "gE3Demo"
extern char lbl_80490664[]; // "gMagazineDemo"
extern char lbl_80490674[]; // "gIsOnline"
extern char lbl_80490680[]; // "gInGame"
extern char lbl_80490688[]; // "gBEDisplayScreen"
extern char lbl_8049069C[]; // "gPlatform"
extern char lbl_804906A8[]; // "Control_ChangeScreen"
extern char lbl_804906C0[]; // "Control_EnableControllerCheck"
extern char lbl_804906E0[]; // "Control_SetMatchInfo"
extern char lbl_804906F8[]; // "Control_SetSelectInfo"
extern char lbl_80490710[]; // "Control_StartLoad"
extern char lbl_80490724[]; // "Control_StartProgressBar"
extern char lbl_80490740[]; // "Control_StartGame"
extern char lbl_80490754[]; // "Control_EndOfMatch"
extern char lbl_80490768[]; // "Control_EndOfMission"
extern char lbl_80490780[]; // "Control_GetNewUnlockable"
extern char lbl_8049079C[]; // "Control_GetNewUnlockableID"
extern char lbl_804907B8[]; // "Control_ToggleLanguage"
extern char lbl_804907D0[]; // "Locale_GetString"
extern char lbl_804907E4[]; // "Global_StartAudio"
extern char lbl_804907F8[]; // "Global_PlayUISound"
extern char lbl_8049080C[]; // "Global_PlayFESound"
extern char lbl_80490820[]; // "Global_EnableBackgroundMusic"
extern char lbl_80490840[]; // "Global_PlayFEStream"
extern char lbl_80490854[]; // "Global_StopFEStream"
extern char lbl_80490868[]; // "Locale_GetLanguage"
extern char lbl_8049087C[]; // "Control_EnableBackgroundDraw"
extern char lbl_8049089C[]; // "Control_StartScreenFunction"
extern char lbl_804908B8[]; // "Control_GetControllerStatus"
extern char lbl_804908D4[]; // "Control_BindController"
extern char lbl_804908EC[]; // "Movie_Play"
extern char lbl_804908F8[]; // "Movie_Stop"
extern char lbl_80490904[]; // "Cheat_UnlockAll"
extern char lbl_80490914[]; // "Reward_GetTrailerInfo"
extern char lbl_8049092C[]; // "Reward_GetCardsInfo"
extern char lbl_80490940[]; // "Reward_GetNumCards"
extern char lbl_80490954[]; // "Reward_GetComicsInfo"
extern char lbl_8049096C[]; // "Reward_GetNumComics"
extern char lbl_80490980[]; // "PauseMenu_SetSFXLevel"
extern char lbl_80490998[]; // "PauseMenu_SetMusicLevel"
extern char lbl_804909B0[]; // "PauseMenu_SetSpeechLevel"
extern char lbl_804909CC[]; // "PauseMenu_ReturnToGame"
extern char lbl_804909E4[]; // "PauseMenu_Quit"
extern char lbl_804909F4[]; // "PauseMenu_GetLastPauser"
extern char lbl_80490A0C[]; // "PauseMenu_OnlineTimeLeft"
extern char lbl_80490A28[]; // "PauseMenu_OnlineCount"
extern char lbl_80490A40[]; // "PauseMenu_OnlineCountLimit"
extern char lbl_80490A5C[]; // "clashPauseMenu_Exit2Game"
extern char lbl_80490A78[]; // "clashPauseMenu_SelectItem"
extern char lbl_80490A94[]; // "Timer_Delay"
extern char lbl_80490AA0[]; // "Timer_Stop"
extern char lbl_80490AAC[]; // "AttractMode_Enable"
extern char lbl_80490AC0[]; // "Cheat_Enable"
extern char lbl_80490AD0[]; // "PAL60_IsRequested"
extern char lbl_80490AE4[]; // "PAL60_Enable"
extern char lbl_80490AF4[]; // "QuitDemo"
extern char lbl_80490B00[]; // "GetRunMode"
extern char lbl_80490B0C[]; // "clashControl_GetLanguage"

// Emits no code. A top-level `return <parameter>;` makes cc1plus drop the function-end branch pair for every later function in the unit.
inline int sn_return_decl(int a) { return a; }

static float sScreenLeft;
static float sScreenRight;
static float sScreenTop;
static float sScreenBottom;

static char sReg_gPALMode;
static char sReg_gWidescreenMode;
static char sReg_gDemoLaunchInto;
static char sReg_gDebugEnable;
static char sReg_gArtistBuild;
static char sReg_gFranchise;
static char sReg_gE3Demo;
static char sReg_gMagazineDemo;
static char sReg_gIsOnline;
static char sReg_gInGame;
static char sReg_gBEDisplayScreen;
static char sReg_gPlatform;
static char sReg_Control_ChangeScreen;
static char sReg_Control_EnableControllerCheck;
static char sReg_Control_SetMatchInfo;
static char sReg_Control_SetSelectInfo;
static char sReg_Control_StartLoad;
static char sReg_Control_StartProgressBar;
static char sReg_Control_StartGame;
static char sReg_Control_EndOfMatch;
static char sReg_Control_EndOfMission;
static char sReg_Control_GetNewUnlockable;
static char sReg_Control_GetNewUnlockableID;
static char sReg_Control_ToggleLanguage;
static char sReg_Locale_GetString;
static char sReg_Global_StartAudio;
static char sReg_Global_PlayUISound;
static char sReg_Global_PlayFESound;
static char sReg_Global_EnableBackgroundMusic;
static char sReg_Global_PlayFEStream;
static char sReg_Global_StopFEStream;
static char sReg_Locale_GetLanguage;
static char sReg_Control_EnableBackgroundDraw;
static char sReg_Control_StartScreenFunction;
static char sReg_Control_GetControllerStatus;
static char sReg_Control_BindController;
static char sReg_Movie_Play;
static char sReg_Movie_Stop;
static char sReg_Cheat_UnlockAll;
static char sReg_Reward_GetTrailerInfo;
static char sReg_Reward_GetCardsInfo;
static char sReg_Reward_GetNumCards;
static char sReg_Reward_GetComicsInfo;
static char sReg_Reward_GetNumComics;
static char sReg_PauseMenu_SetSFXLevel;
static char sReg_PauseMenu_SetMusicLevel;
static char sReg_PauseMenu_SetSpeechLevel;
static char sReg_PauseMenu_ReturnToGame;
static char sReg_PauseMenu_Quit;
static char sReg_PauseMenu_GetLastPauser;
static char sReg_PauseMenu_OnlineTimeLeft;
static char sReg_PauseMenu_OnlineCount;
static char sReg_PauseMenu_OnlineCountLimit;
static char sReg_clashPauseMenu_Exit2Game;
static char sReg_clashPauseMenu_SelectItem;
static char sReg_Timer_Delay;
static char sReg_Timer_Stop;
static char sReg_AttractMode_Enable;
static char sReg_Cheat_Enable;
static char sReg_PAL60_IsRequested;
static char sReg_PAL60_Enable;
static char sReg_QuitDemo;
static char sReg_GetRunMode;
static char sReg_clashControl_GetLanguage;

// 65535 is GCC 2.95's default init priority.
void ControlStaticInit(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            sScreenLeft = 320.0f - lbl_8066BB14 * 0.5f;
            sScreenRight = sScreenLeft + lbl_8066BB14 * 0.5f;
            sScreenTop = 240.0f - lbl_8066BB18 * 0.5f;
            sScreenBottom = lbl_8066BB18 * 0.5f + sScreenTop - 12.0f;
        fn_8044BBC8(&sReg_gPALMode, lbl_804905D0, (void *)gPALMode, lbl_804905DC, 48);
        fn_8044BBC8(&sReg_gWidescreenMode, lbl_80490610, (void *)gWidescreenMode, lbl_804905DC, 53);
        fn_8044BBC8(&sReg_gDemoLaunchInto, lbl_80490620, (void *)gDemoLaunchInto, lbl_804905DC, 58);
        fn_8044BD90(&sReg_gDebugEnable, lbl_80490630, (void *)gDebugEnable, lbl_804905DC, 69);
        fn_8044BBC8(&sReg_gArtistBuild, lbl_80490640, (void *)gArtistBuild, lbl_804905DC, 78);
        fn_8044BBC8(&sReg_gFranchise, lbl_80490650, (void *)gFranchise, lbl_804905DC, 83);
        fn_8044BBC8(&sReg_gE3Demo, lbl_8049065C, (void *)gE3Demo, lbl_804905DC, 88);
        fn_8044BBC8(&sReg_gMagazineDemo, lbl_80490664, (void *)gMagazineDemo, lbl_804905DC, 93);
        fn_8044BBC8(&sReg_gIsOnline, lbl_80490674, (void *)gIsOnline, lbl_804905DC, 102);
        fn_8044BD90(&sReg_gInGame, lbl_80490680, (void *)gInGame, lbl_804905DC, 108);
        fn_8044BD90(&sReg_gBEDisplayScreen, lbl_80490688, (void *)gBEDisplayScreen, lbl_804905DC, 126);
        fn_8044BD90(&sReg_gPlatform, lbl_8049069C, (void *)gPlatform, lbl_804905DC, 141);
        fn_8044BF9C(&sReg_Control_ChangeScreen, lbl_804906A8, (void *)Control_ChangeScreen, lbl_804905DC, 149);
        fn_8044C35C(&sReg_Control_EnableControllerCheck, lbl_804906C0, (void *)Control_EnableControllerCheck, lbl_804905DC, 157);
        fn_8044C634(&sReg_Control_SetMatchInfo, lbl_804906E0, (void *)Control_SetMatchInfo, lbl_804905DC, 211);
        fn_8044C9E4(&sReg_Control_SetSelectInfo, lbl_804906F8, (void *)Control_SetSelectInfo, lbl_804905DC, 274);
        fn_8044B11C(&sReg_Control_StartLoad, lbl_80490710, (void *)Control_StartLoad, lbl_804905DC, 279);
        fn_8044CC2C(&sReg_Control_StartProgressBar, lbl_80490724, (void *)Control_StartProgressBar, lbl_804905DC, 307);
        fn_8044B11C(&sReg_Control_StartGame, lbl_80490740, (void *)Control_StartGame, lbl_804905DC, 315);
        fn_8044C35C(&sReg_Control_EndOfMatch, lbl_80490754, (void *)Control_EndOfMatch, lbl_804905DC, 332);
        fn_8044C35C(&sReg_Control_EndOfMission, lbl_80490768, (void *)Control_EndOfMission, lbl_804905DC, 350);
        fn_8044BBC8(&sReg_Control_GetNewUnlockable, lbl_80490780, (void *)Control_GetNewUnlockable, lbl_804905DC, 356);
        fn_8044BBC8(&sReg_Control_GetNewUnlockableID, lbl_8049079C, (void *)Control_GetNewUnlockableID, lbl_804905DC, 362);
        fn_8044B11C(&sReg_Control_ToggleLanguage, lbl_804907B8, (void *)Control_ToggleLanguage, lbl_804905DC, 378);
        fn_8044CE44(&sReg_Locale_GetString, lbl_804907D0, (void *)Locale_GetString, lbl_804905DC, 392);
        fn_8044B11C(&sReg_Global_StartAudio, lbl_804907E4, (void *)Global_StartAudio, lbl_804905DC, 419);
        fn_8044BF9C(&sReg_Global_PlayUISound, lbl_804907F8, (void *)Global_PlayUISound, lbl_804905DC, 437);
        fn_8044C35C(&sReg_Global_PlayFESound, lbl_8049080C, (void *)Global_PlayFESound, lbl_804905DC, 447);
        fn_8044C35C(&sReg_Global_EnableBackgroundMusic, lbl_80490820, (void *)Global_EnableBackgroundMusic, lbl_804905DC, 455);
        fn_8044BF9C(&sReg_Global_PlayFEStream, lbl_80490840, (void *)Global_PlayFEStream, lbl_804905DC, 487);
        fn_8044B11C(&sReg_Global_StopFEStream, lbl_80490854, (void *)Global_StopFEStream, lbl_804905DC, 494);
        fn_8044BBC8(&sReg_Locale_GetLanguage, lbl_80490868, (void *)Locale_GetLanguage, lbl_804905DC, 503);
        fn_8044C35C(&sReg_Control_EnableBackgroundDraw, lbl_8049087C, (void *)Control_EnableBackgroundDraw, lbl_804905DC, 508);
        fn_8044D060(&sReg_Control_StartScreenFunction, lbl_8049089C, (void *)Control_StartScreenFunction, lbl_804905DC, 518);
        fn_8044D270(&sReg_Control_GetControllerStatus, lbl_804908B8, (void *)Control_GetControllerStatus, lbl_804905DC, 539);
        fn_8044CC2C(&sReg_Control_BindController, lbl_804908D4, (void *)Control_BindController, lbl_804905DC, 546);
        fn_8044C35C(&sReg_Movie_Play, lbl_804908EC, (void *)Movie_Play, lbl_804905DC, 556);
        fn_8044B11C(&sReg_Movie_Stop, lbl_804908F8, (void *)Movie_Stop, lbl_804905DC, 563);
        fn_8044B11C(&sReg_Cheat_UnlockAll, lbl_80490904, (void *)Cheat_UnlockAll, lbl_804905DC, 578);
        fn_8044AF58(&sReg_Reward_GetTrailerInfo, lbl_80490914, (void *)Reward_GetTrailerInfo, lbl_804905DC, 594);
        fn_8044AF58(&sReg_Reward_GetCardsInfo, lbl_8049092C, (void *)Reward_GetCardsInfo, lbl_804905DC, 606);
        fn_8044BBC8(&sReg_Reward_GetNumCards, lbl_80490940, (void *)Reward_GetNumCards, lbl_804905DC, 619);
        fn_8044AF58(&sReg_Reward_GetComicsInfo, lbl_80490954, (void *)Reward_GetComicsInfo, lbl_804905DC, 632);
        fn_8044BBC8(&sReg_Reward_GetNumComics, lbl_8049096C, (void *)Reward_GetNumComics, lbl_804905DC, 648);
        fn_8044C35C(&sReg_PauseMenu_SetSFXLevel, lbl_80490980, (void *)PauseMenu_SetSFXLevel, lbl_804905DC, 658);
        fn_8044C35C(&sReg_PauseMenu_SetMusicLevel, lbl_80490998, (void *)PauseMenu_SetMusicLevel, lbl_804905DC, 664);
        fn_8044C35C(&sReg_PauseMenu_SetSpeechLevel, lbl_804909B0, (void *)PauseMenu_SetSpeechLevel, lbl_804905DC, 670);
        fn_8044B11C(&sReg_PauseMenu_ReturnToGame, lbl_804909CC, (void *)PauseMenu_ReturnToGame, lbl_804905DC, 676);
        fn_8044B11C(&sReg_PauseMenu_Quit, lbl_804909E4, (void *)PauseMenu_Quit, lbl_804905DC, 697);
        fn_8044BBC8(&sReg_PauseMenu_GetLastPauser, lbl_804909F4, (void *)PauseMenu_GetLastPauser, lbl_804905DC, 702);
        fn_8044BBC8(&sReg_PauseMenu_OnlineTimeLeft, lbl_80490A0C, (void *)PauseMenu_OnlineTimeLeft, lbl_804905DC, 711);
        fn_8044BBC8(&sReg_PauseMenu_OnlineCount, lbl_80490A28, (void *)PauseMenu_OnlineCount, lbl_804905DC, 720);
        fn_8044BBC8(&sReg_PauseMenu_OnlineCountLimit, lbl_80490A40, (void *)PauseMenu_OnlineCountLimit, lbl_804905DC, 729);
        fn_8044B11C(&sReg_clashPauseMenu_Exit2Game, lbl_80490A5C, (void *)clashPauseMenu_Exit2Game, lbl_804905DC, 735);
        fn_8044CC2C(&sReg_clashPauseMenu_SelectItem, lbl_80490A78, (void *)clashPauseMenu_SelectItem, lbl_804905DC, 774);
        fn_8044C35C(&sReg_Timer_Delay, lbl_80490A94, (void *)Timer_Delay, lbl_804905DC, 784);
        fn_8044B11C(&sReg_Timer_Stop, lbl_80490AA0, (void *)Timer_Stop, lbl_804905DC, 789);
        fn_8044C35C(&sReg_AttractMode_Enable, lbl_80490AAC, (void *)AttractMode_Enable, lbl_804905DC, 794);
        fn_8044CE44(&sReg_Cheat_Enable, lbl_80490AC0, (void *)Cheat_Enable, lbl_804905DC, 998);
        fn_8044BBC8(&sReg_PAL60_IsRequested, lbl_80490AD0, (void *)PAL60_IsRequested, lbl_804905DC, 1012);
        fn_8044C35C(&sReg_PAL60_Enable, lbl_80490AE4, (void *)PAL60_Enable, lbl_804905DC, 1028);
        fn_8044B11C(&sReg_QuitDemo, lbl_80490AF4, (void *)QuitDemo, lbl_804905DC, 1044);
        fn_8044BBC8(&sReg_GetRunMode, lbl_80490B00, (void *)GetRunMode, lbl_804905DC, 1052);
        fn_8044BBC8(&sReg_clashControl_GetLanguage, lbl_80490B0C, (void *)clashControl_GetLanguage, lbl_804905DC, 1057);
        } else {
        }
    }
}

void fn_80106AF8(void)
{
    ControlStaticInit(1, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_80106AF8;
