// Script class destructors, in link order, and the inline methods between them (docs/story.md row 7).
// fn_8046CDB4 reads -1.0f at 0x804A1670 (extern_pool).

inline int sn_return_decl(int a) { return a; }

struct cScript {
    char d[0x28];
};
struct cAvengersMansion_ParadoxBoss : cScript {};
struct cAvengersMansion_IM1_Start : cScript {};
struct cAvengersMansion_IronManSAC : cScript {};
struct cAvengersMansion_HideSkirt : cScript {};
struct cBrooklynBridge_heliCrash : cScript {};
struct cBB_ArenaShutoff : cScript {};
struct cBrooklynBridge_ArenaBarrier : cScript {};
struct cBrooklynBridge_AftershockBoss : cScript {};
struct cBrooklynBridge_VM2_Start : cScript {};
struct cBrooklynBridge_SegmentControl : cScript {};
struct cBrooklynBridge_BruteFight : cScript {};
struct cBrooklynBridge_WolverineSAC : cScript {};
struct cBrooklynBridge_RockBomb : cScript {};
struct cBrooklynBridge_FlameWall : cScript {};
struct cBrooklynBridge_HazmatBoss : cScript {};
struct cBrooklynBridge_AltStormBoss : cScript {};
struct cDailyBugle_VenomBoss : cScript {};
struct cDailyBugle_SpidermanSac : cScript {};
struct cDailyBugle_LetterEffects : cScript {};
struct cDailyBugle_DaredevilBoss : cScript {};
struct cGrandCentral_VenomBoss : cScript {};
struct cGrandCentral_OhmBoss : cScript {};
struct cGrandCentral_HazmatBoss : cScript {};
struct cGrandCentral_MagnetoBoss : cScript {};
struct cGrandCentral_RockBomb : cScript {};
struct cNYCStreets_DaredevilBoss : cScript {};
struct cNYCStreetsMP_SegmentControl : cScript {};
struct cNYCStreets_ThingBoss : cScript {};
struct cNYCStreets_TorchBoss : cScript {};
struct cPowerPlant_HumanTorchSAC : cScript {};
struct cPowerPlant_ElektraSAC : cScript {};
struct cPowerPlant_IronMan_3 : cScript {};
struct cPowerPlant_Venom_3 : cScript {};
struct cPowerPlant_CoilToggle : cScript {};
struct cPowerPlant_CoilArc : cScript {};
struct cRoekelFacility_StormBoss : cScript {};
struct cRoekelFacility_ThingBoss : cScript {};
struct cRoekelFacility_RockBomb : cScript {};
struct cRoekelFacility_BlastDoor : cScript {};
struct cRoekelFacility_RoekelBoss : cScript {};
struct cRoekelFacility_PlasmaMine : cScript {};
struct cRoekelFacility_Lasers : cScript {};
struct cPathnodeToggle : cScript {};
struct cActorMoveToPos : cScript {};
struct cActorWalk : cScript {};
struct cActorAIPause : cScript {};
struct cActorControlState : cScript {};
struct cSpawnPeon : cScript {};
struct cSpawnGroup : cScript {};
struct cSpawnController : cScript {};
struct cActorPlayPath : cScript {};
struct cAIRangedAttacker : cScript {};
struct cBossRingOut : cScript {};
struct cActorSetHealth : cScript {};
struct cPlayerBonusMissions : cScript {};
struct cGlobalPeonCounter : cScript {};
struct cAITeleportationToggle : cScript {};
struct cAIEnemyVictoryScene : cScript {};
struct cTemporaryAIPossession : cScript {};
struct cAISetTeleportDistance : cScript {};
struct cCameraEvent : cScript {};
struct cCutscenePlay : cScript {};
struct cParticleToggle : cScript {};
struct cDummyProjectile : cScript {};
struct cEffectSpawn : cScript {};
struct cCrystalDetonate : cScript {};
struct cObjectExplosion : cScript {};
struct cObjectSetCollision : cScript {};
struct cObjectMove : cScript {};
struct cObjectRumbleShake : cScript {};
struct cTimerTrigger : cScript {};
struct cTriggerOnAction : cScript {};
struct cTriggerRelay : cScript {};
struct cSetAnimFrame : cScript {};
struct cDebrisFall : cScript {};
struct cVehicleBreak : cScript {};
struct cVehicleBarrier : cScript {};
struct cGenBreakProp : cScript {};
struct cDamagePropOnTrigger : cScript {};
struct cPortalControl : cScript {};
struct cPropRespawn : cScript {};
struct cRemoveObjects : cScript {};
struct cCrystalBreak : cScript {};
struct cCrystalBreak_Phase2 : cScript {};
struct cCameraMPToggle : cScript {};
struct cLabConsole : cScript {};
struct cWieldableToggle : cScript {};
struct cReverseWallRenderToggle : cScript {};
struct cPropGroupFade : cScript {};
struct cMP_MatchTrigger : cScript {};
struct cCameraSet : cScript {};
struct cRegionDamage : cScript {};
struct cRegionTrigger : cScript {};
struct cRegionSound : cScript {};
struct cRegionSuck : cScript {};
struct cRegionDefend : cScript {};
struct cRegionLightProbeSwap : cScript {};

struct Ref8 {
    int unk0;
    int value; // +0x4
};

struct Unk63C {
    char d[0x63C];
    int f63c; // +0x63C
};

struct Obj154 {
    char d[0xC8];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17(float a, float b);
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57(int a);
};

struct Entity {
    char d[0x144];
    void *f144; // +0x144
    char d148[0xC];
    Obj154 *f154; // +0x154
};

extern "C" {

void fn_8007975C(cScript *self, int inChrg);
void fn_8043323C(void *self, int inChrg);
Ref8 *fn_8046B560(Ref8 *self, int value);
Ref8 *fn_8046B680(Ref8 *self, int value);
void fn_8046C230(Ref8 *self, int value);
Entity *fn_80081E6C(cScript *self);
Entity *fn_8007C034(cScript *self);
int fn_800B0C58(Entity *e);
int fn_800B0C1C(Entity *e);
int fn_800B1138(Entity *e);
void *fn_800B1CC8(Entity *e);
int fn_8042F050(void *p);
int fn_80085D3C(Entity *e);
int fn_80095608(Entity *e);
int fn_8039CFE4(Obj154 *p);

extern int lbl_8066B5A0;
extern int lbl_8066B894;
extern int lbl_8066C7DC;

void fn_8046B738(register cAvengersMansion_ParadoxBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046B778(register cAvengersMansion_IM1_Start *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046B7B8(register cAvengersMansion_IronManSAC *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046B7F8(register cAvengersMansion_HideSkirt *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046B838(register Unk63C *self, register int value)
{
    self->f63c = value;
}

void fn_8046B860(register void *self, register int inChrg)
{
    fn_8043323C(self, inChrg);
}

void fn_8046B8A0(register cBrooklynBridge_heliCrash *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046B8E0(register cBB_ArenaShutoff *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046B920(register cBrooklynBridge_ArenaBarrier *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046B960(register cBrooklynBridge_AftershockBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046B9A0(register cBrooklynBridge_VM2_Start *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046B9E0(register cBrooklynBridge_SegmentControl *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BA20(register cBrooklynBridge_BruteFight *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BA60(register cBrooklynBridge_WolverineSAC *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BAA0(register cBrooklynBridge_RockBomb *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BAE0(register cBrooklynBridge_FlameWall *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BB20(register cBrooklynBridge_HazmatBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BB60(register cBrooklynBridge_AltStormBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

Ref8 *fn_8046BBA0(register Ref8 *self, register int value)
{
    fn_8046B680(self, value);
    return self;
}

void fn_8046BBE8()
{
    lbl_8066B5A0 = 1;
}

void fn_8046BC0C()
{
    lbl_8066B5A0 = 0;
}

void fn_8046BC30(register cDailyBugle_VenomBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BC70(register cDailyBugle_SpidermanSac *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BCB0(register cDailyBugle_LetterEffects *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BCF0(register cDailyBugle_DaredevilBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

int fn_8046BD30(register cScript *self)
{
    Entity *e = fn_80081E6C(self);
    return e && fn_800B0C58(e);
}

void fn_8046BDA0(register cGrandCentral_VenomBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BDE0(register cGrandCentral_OhmBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BE20(register cGrandCentral_HazmatBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BE60(register cGrandCentral_MagnetoBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BEA0(register cGrandCentral_RockBomb *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BEE0(register cNYCStreets_DaredevilBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BF20(register cNYCStreetsMP_SegmentControl *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BF60(register cNYCStreets_ThingBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BFA0(register cNYCStreets_TorchBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046BFE0(register cPowerPlant_HumanTorchSAC *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C020(register cPowerPlant_ElektraSAC *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C060(register cPowerPlant_IronMan_3 *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C0A0(register cPowerPlant_Venom_3 *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C0E0(register cPowerPlant_CoilToggle *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C120(register cPowerPlant_CoilArc *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

int fn_8046C160(register cScript *self)
{
    Entity *e = fn_80081E6C(self);
    return e && fn_800B1CC8(e) ? fn_8042F050(fn_800B1CC8(e)) : -1;
}

Ref8 *fn_8046C1E8(register Ref8 *self, register int value)
{
    fn_8046C230(self, value);
    return self;
}

void fn_8046C230(register Ref8 *self, register int value)
{
    self->value = value;
}

void fn_8046C258(register cRoekelFacility_StormBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C298(register cRoekelFacility_ThingBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C2D8(register cRoekelFacility_RockBomb *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C318(register cRoekelFacility_BlastDoor *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C358(register cRoekelFacility_RoekelBoss *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C398(register cRoekelFacility_PlasmaMine *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C3D8(register cRoekelFacility_Lasers *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C418(register cPathnodeToggle *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C458(register cActorMoveToPos *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C498(register cActorWalk *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C4D8(register cActorAIPause *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C518(register cActorControlState *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C558(register cSpawnPeon *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C598(register cSpawnGroup *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C5D8(register cSpawnController *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C618(register cActorPlayPath *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C658(register cAIRangedAttacker *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C698(register cBossRingOut *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C6D8(register cActorSetHealth *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C718(register cPlayerBonusMissions *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C758(register cGlobalPeonCounter *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C798(register cAITeleportationToggle *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C7D8(register cAIEnemyVictoryScene *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C818(register cTemporaryAIPossession *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046C858(register cAISetTeleportDistance *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void *fn_8046C898(register cScript *self)
{
    Entity *e = fn_80081E6C(self);
    return e ? e->f144 : 0;
}

int fn_8046C8FC(register cScript *self)
{
    Entity *e = fn_80081E6C(self);
    return e && fn_800B1138(e);
}

int fn_8046C96C(register cScript *self)
{
    Entity *e = fn_8007C034(self);
    return e && !fn_80085D3C(e) && !fn_80095608(e);
}

void fn_8046C9F0(register int value)
{
    lbl_8066B894 = value;
}

void fn_8046CA14(register cCameraEvent *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046CA54(register cCutscenePlay *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046CA94(register int value)
{
    lbl_8066C7DC = value;
}

void fn_8046CAB8(register cParticleToggle *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046CAF8(register cDummyProjectile *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046CB38(register cEffectSpawn *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046CB78(register cCrystalDetonate *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

int fn_8046CBB8(register cScript *self)
{
    Entity *e = fn_80081E6C(self);
    return e && fn_800B0C1C(e);
}

int fn_8046CC28(register cScript *self)
{
    Entity *e = fn_80081E6C(self);
    return e && e->f154;
}

void fn_8046CC94(register cScript *self)
{
    Entity *e = fn_80081E6C(self);
    if (e && e->f154)
        e->f154->s57(1);
}

int fn_8046CD30(register cScript *self)
{
    Entity *e = fn_80081E6C(self);
    return e && e->f154 && fn_8039CFE4(e->f154);
}

void fn_8046CDB4(register cScript *self, register float a, register float b)
{
    Entity *e = fn_80081E6C(self);
    if (e && e->f154)
        e->f154->s17(a, -1.0f);
}

Ref8 *fn_8046CE70(register Ref8 *self, register int value)
{
    fn_8046B560(self, value);
    return self;
}

void fn_8046CEB8(register cObjectExplosion *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046CEF8(register cObjectSetCollision *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046CF38(register cObjectMove *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046CF78(register cObjectRumbleShake *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046CFB8(register cTimerTrigger *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046CFF8(register cTriggerOnAction *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D038(register cTriggerRelay *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D078(register cSetAnimFrame *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D0B8(register cDebrisFall *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D0F8(register cVehicleBreak *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D138(register cVehicleBarrier *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D178(register cGenBreakProp *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D1B8(register cDamagePropOnTrigger *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D1F8(register cPortalControl *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D238(register cPropRespawn *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D278(register cRemoveObjects *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D2B8(register cCrystalBreak *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D2F8(register cCrystalBreak_Phase2 *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D338(register cCameraMPToggle *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D378(register cLabConsole *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D3B8(register cWieldableToggle *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D3F8(register cReverseWallRenderToggle *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D438(register cPropGroupFade *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D478(register cMP_MatchTrigger *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D4B8(register cCameraSet *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

Ref8 *fn_8046D4F8(register Ref8 *self, register int value)
{
    fn_8046B560(self, value);
    return self;
}

void fn_8046D540(register cRegionDamage *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D580(register cRegionTrigger *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D5C0(register cRegionSound *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D600(register cRegionSuck *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D640(register cRegionDefend *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046D680(register cRegionLightProbeSwap *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

}
