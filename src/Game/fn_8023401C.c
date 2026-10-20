// Shader setup: creates the "shaders" and "shaderclass" registries and registers each shader name with its class factory; docs/characters.md "Models". glossenvcharlight is fn_80239258.

extern void *lbl_8066C84C;
extern void *lbl_8066C850;
extern const char lbl_804A31F0[];
extern const char lbl_804A31F8[];
extern const char lbl_804A3204[];
extern const char lbl_804A2B28[];
extern const char lbl_804A320C[];
extern const char lbl_804A2B44[];
extern const char lbl_804A3168[];
extern const char lbl_804A2B64[];
extern const char lbl_804A3218[];
extern const char lbl_804A3220[];
extern const char lbl_804A3224[];
extern const char lbl_804A3230[];
extern const char lbl_804A3238[];
extern const char lbl_804A3244[];
extern const char lbl_804A3250[];
extern const char lbl_804A325C[];
extern const char lbl_804A3264[];
extern const char lbl_804A3270[];
extern const char lbl_804A3280[];
extern const char lbl_804A328C[];
extern const char lbl_804A3298[];
extern const char lbl_804A3048[];
extern const char lbl_804A32A0[];
extern const char lbl_804A32A8[];
extern const char lbl_804A32B0[];
extern const char lbl_804A32BC[];
extern const char lbl_804A32CC[];
extern const char lbl_804A32E0[];
extern const char lbl_804A32EC[];
extern const char lbl_804A32F8[];
extern const char lbl_804A3304[];

extern void *fn_801B4284(int capacity, const char *name);
extern void fn_8023431C(const char *name, void *(*factory)());
extern void *fn_8022B520();
extern void *fn_8022B5E4();
extern void *fn_8022E5B4();
extern void *fn_8022E60C();
extern void *fn_8022E664();
extern void *fn_8022FC30();
extern void *fn_8022FC80();
extern void *fn_8022FD38();
extern void *fn_8022FFC8();
extern void *fn_80230118();
extern void *fn_80231814();
extern void *fn_80231980();
extern void *fn_80238EE0();
extern void *fn_80239028();
extern void *fn_802390E4();
extern void *fn_802391A4();
extern void *fn_80239258();
extern void *fn_8023930C();
extern void *fn_8023D11C();
extern void *fn_8023D1C4();
extern void *fn_8023D39C();
extern void *fn_8023D3EC();
extern void *fn_8023D514();
extern void *fn_8023D5C8();
extern void *fn_8023D684();
extern void *fn_8023D738();
extern void *fn_8023D7E8();
extern void *fn_8023D8B8();
extern void *fn_80472680();

int fn_8023401C(void)
{
    lbl_8066C84C = fn_801B4284(0x53, lbl_804A31F0);
    lbl_8066C850 = fn_801B4284(0x1F, lbl_804A31F8);
    fn_8023431C(lbl_804A3204, fn_8022FC30); // default
    fn_8023431C(lbl_804A2B28, fn_802390E4); // envmap
    fn_8023431C(lbl_804A320C, fn_802391A4); // glossenvmap
    fn_8023431C(lbl_804A2B44, fn_80231814); // glow
    fn_8023431C(lbl_804A3168, fn_80238EE0); // glass
    fn_8023431C(lbl_804A2B64, fn_8022B520); // alpha
    fn_8023431C(lbl_804A3218, fn_8022B5E4); // masked
    fn_8023431C(lbl_804A3220, fn_8022FC80); // add
    fn_8023431C(lbl_804A3224, fn_8022FD38); // fullbright
    fn_8023431C(lbl_804A3230, fn_8023D11C); // sight
    fn_8023431C(lbl_804A3238, fn_8023930C); // metalenvmap
    fn_8023431C(lbl_804A3244, fn_8023D39C); // ghostsuit
    fn_8023431C(lbl_804A3250, fn_80230118); // silhouette
    fn_8023431C(lbl_804A325C, fn_8022FFC8); // lava
    fn_8023431C(lbl_804A3264, fn_8022E664); // animlayer
    fn_8023431C(lbl_804A3270, fn_80239028); // etchedmasked
    fn_8023431C(lbl_804A3280, fn_80231980); // lightvolume
    fn_8023431C(lbl_804A328C, fn_8022E5B4); // pageflip
    fn_8023431C(lbl_804A3298, fn_8023D3EC); // cloak
    fn_8023431C(lbl_804A3048, fn_8022E60C); // video
    fn_8023431C(lbl_804A32A0, fn_8023D1C4); // shield
    fn_8023431C(lbl_804A32A8, fn_8023D514); // mirror
    fn_8023431C(lbl_804A32B0, fn_80472680); // fakemirror
    fn_8023431C(lbl_804A32BC, fn_8023D684); // alphamultiply
    fn_8023431C(lbl_804A32CC, fn_80239258); // glossenvcharlight
    fn_8023431C(lbl_804A32E0, fn_8023D5C8); // charlight
    fn_8023431C(lbl_804A32EC, fn_8023D738); // heatwave
    fn_8023431C(lbl_804A32F8, fn_8023D7E8); // humantorch
    fn_8023431C(lbl_804A3304, fn_8023D8B8); // defcon
    return 1;
}
