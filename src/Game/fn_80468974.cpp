// Prototype constructors of 101 script classes (cHelpText's is at 0x802116B0) (docs/story.md row 7).
// Class sizes are in Game/fn_801BEE2C.cpp; member constructors run at this + offset.

struct cScript {
    char d[0x24];
    char *vptr; // +0x24
};

struct cCutscenePlay : cScript {};
struct cParticleToggle : cScript {};
struct cDummyProjectile : cScript {};
struct cEffectSpawn : cScript {};
struct cCrystalDetonate : cScript {};
struct cEndMission : cScript {};
struct cCountDown : cScript {};
struct cRegionDamage : cScript {};
struct cRegionTrigger : cScript {};
struct cRegionSound : cScript {};
struct cRegionSuck : cScript {};
struct cRegionDefend : cScript {};
struct cRegionLightProbeSwap : cScript {};
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
struct cSoundEvent : cScript {};
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
struct cRingOut : cScript {};
struct cCameraEvent : cScript {};
struct cPowerPlant_HumanTorchSAC : cScript {};
struct cPowerPlant_ElektraSAC : cScript {};
struct cPowerPlant_IronMan_3 : cScript {};
struct cPowerPlant_Venom_3 : cScript {};
struct cPowerPlant_CoilToggle : cScript {};
struct cPowerPlant_CoilArc : cScript {};
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
struct cAvengersMansion_ParadoxBoss : cScript {};
struct cAvengersMansion_IM1_Start : cScript {};
struct cAvengersMansion_IronManSAC : cScript {};
struct cAvengersMansion_HideSkirt : cScript {};
struct cDailyBugle_VenomBoss : cScript {};
struct cDailyBugle_SpidermanSac : cScript {};
struct cDailyBugle_LetterEffects : cScript {};
struct cDailyBugle_DaredevilBoss : cScript {};
struct cRoekelFacility_StormBoss : cScript {};
struct cRoekelFacility_ThingBoss : cScript {};
struct cRoekelFacility_RockBomb : cScript {};
struct cRoekelFacility_BlastDoor : cScript {};
struct cRoekelFacility_RoekelBoss : cScript {};
struct cRoekelFacility_PlasmaMine : cScript {};
struct cRoekelFacility_Lasers : cScript {};
struct cNYCStreets_DaredevilBoss : cScript {};
struct cNYCStreetsMP_SegmentControl : cScript {};
struct cNYCStreets_ThingBoss : cScript {};
struct cNYCStreets_TorchBoss : cScript {};
struct cGrandCentral_VenomBoss : cScript {};
struct cGrandCentral_OhmBoss : cScript {};
struct cGrandCentral_HazmatBoss : cScript {};
struct cGrandCentral_MagnetoBoss : cScript {};
struct cGrandCentral_RockBomb : cScript {};

extern "C" {

void fn_80441FAC(cScript *self);
void __6Vector(void *self);
void fn_8042D7B0(void *self);
void fn_8046B530(void *self);
void fn_8046B560(void *self, int value);
void fn_8046B5A8(void *self, int value);
void fn_8046B5F0(void *self, int value);
void fn_8046B638(void *self, int value);

extern char lbl_804FE5D0[];
extern char lbl_804FEDF0[];
extern char lbl_804FEBE8[];
extern char lbl_804FE9E0[];
extern char lbl_804FE7D8[];
extern char lbl_80503558[];
extern char lbl_80503148[];
extern char lbl_80502D10[];
extern char lbl_80502B08[];
extern char lbl_80502900[];
extern char lbl_805026D0[];
extern char lbl_805024C8[];
extern char lbl_805022C0[];
extern char lbl_805020B8[];
extern char lbl_80501EB0[];
extern char lbl_80501CA8[];
extern char lbl_80501AA0[];
extern char lbl_80501898[];
extern char lbl_80501690[];
extern char lbl_80501488[];
extern char lbl_80501280[];
extern char lbl_80501078[];
extern char lbl_80500E70[];
extern char lbl_80500C68[];
extern char lbl_80500A60[];
extern char lbl_80500858[];
extern char lbl_80500650[];
extern char lbl_80500448[];
extern char lbl_80500240[];
extern char lbl_80500038[];
extern char lbl_804FFE30[];
extern char lbl_804FFC28[];
extern char lbl_804FFA20[];
extern char lbl_804FF818[];
extern char lbl_804FF610[];
extern char lbl_804FF408[];
extern char lbl_804FF200[];
extern char lbl_804FEFF8[];
extern char lbl_80503760[];
extern char lbl_804FE1C0[];
extern char lbl_804FDFB8[];
extern char lbl_804FDDB0[];
extern char lbl_804FDBA8[];
extern char lbl_804FD9A0[];
extern char lbl_804FD798[];
extern char lbl_804FD590[];
extern char lbl_804FD388[];
extern char lbl_804FD180[];
extern char lbl_804FCF78[];
extern char lbl_804FCD70[];
extern char lbl_804FCB68[];
extern char lbl_804FC960[];
extern char lbl_804FC758[];
extern char lbl_804FC550[];
extern char lbl_804FC348[];
extern char lbl_804FC140[];
extern char lbl_804FBF38[];
extern char lbl_80502F40[];
extern char lbl_804FE3C8[];
extern char lbl_804FAEF8[];
extern char lbl_804FACF0[];
extern char lbl_804FAAE8[];
extern char lbl_804FA8E0[];
extern char lbl_804FA6D8[];
extern char lbl_804FA4D0[];
extern char lbl_804F8860[];
extern char lbl_804F8658[];
extern char lbl_804F8450[];
extern char lbl_804F8248[];
extern char lbl_804F8040[];
extern char lbl_804F7E38[];
extern char lbl_804F7C30[];
extern char lbl_804F7A28[];
extern char lbl_804F7820[];
extern char lbl_804F7618[];
extern char lbl_804F7410[];
extern char lbl_804F7208[];
extern char lbl_804F7000[];
extern char lbl_804F6DF8[];
extern char lbl_804F6BF0[];
extern char lbl_804F69E8[];
extern char lbl_804F9080[];
extern char lbl_804F8E78[];
extern char lbl_804F8C70[];
extern char lbl_804F8A68[];
extern char lbl_804FBD30[];
extern char lbl_804FBB28[];
extern char lbl_804FB920[];
extern char lbl_804FB718[];
extern char lbl_804FB510[];
extern char lbl_804FB308[];
extern char lbl_804FB100[];
extern char lbl_804FA2C8[];
extern char lbl_804FA0C0[];
extern char lbl_804F9EB8[];
extern char lbl_804F9CB0[];
extern char lbl_804F9AA8[];
extern char lbl_804F98A0[];
extern char lbl_804F9698[];
extern char lbl_804F9490[];
extern char lbl_804F9288[];

cCutscenePlay *fn_80468974(register cCutscenePlay *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FE5D0;
    return self;
}

cParticleToggle *fn_804689C0(register cParticleToggle *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FEDF0;
    return self;
}

cDummyProjectile *fn_80468A0C(register cDummyProjectile *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FEBE8;
    __6Vector((char *)self + 0x30);
    __6Vector((char *)self + 0x40);
    return self;
}

cEffectSpawn *fn_80468A70(register cEffectSpawn *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FE9E0;
    return self;
}

cCrystalDetonate *fn_80468ABC(register cCrystalDetonate *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FE7D8;
    return self;
}

cEndMission *fn_80468B08(register cEndMission *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80503558;
    return self;
}

cCountDown *fn_80468B54(register cCountDown *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80503148;
    return self;
}

cRegionDamage *fn_80468BA0(register cRegionDamage *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80502D10;
    fn_8046B530((char *)self + 0x54);
    return self;
}

cRegionTrigger *fn_80468BF8(register cRegionTrigger *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80502B08;
    return self;
}

cRegionSound *fn_80468C44(register cRegionSound *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80502900;
    return self;
}

cRegionSuck *fn_80468C90(register cRegionSuck *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_805026D0;
    return self;
}

cRegionDefend *fn_80468CDC(register cRegionDefend *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_805024C8;
    return self;
}

cRegionLightProbeSwap *fn_80468D28(register cRegionLightProbeSwap *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_805022C0;
    return self;
}

cObjectExplosion *fn_80468D74(register cObjectExplosion *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_805020B8;
    return self;
}

cObjectSetCollision *fn_80468DC0(register cObjectSetCollision *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80501EB0;
    return self;
}

cObjectMove *fn_80468E0C(register cObjectMove *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80501CA8;
    return self;
}

cObjectRumbleShake *fn_80468E58(register cObjectRumbleShake *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80501AA0;
    return self;
}

cTimerTrigger *fn_80468EA4(register cTimerTrigger *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80501898;
    return self;
}

cTriggerOnAction *fn_80468EF0(register cTriggerOnAction *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80501690;
    return self;
}

cTriggerRelay *fn_80468F3C(register cTriggerRelay *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80501488;
    return self;
}

cSetAnimFrame *fn_80468F88(register cSetAnimFrame *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80501280;
    return self;
}

cDebrisFall *fn_80468FD4(register cDebrisFall *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80501078;
    return self;
}

cVehicleBreak *fn_80469020(register cVehicleBreak *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80500E70;
    fn_8046B560((char *)self + 0x28, 0);
    return self;
}

cVehicleBarrier *fn_8046907C(register cVehicleBarrier *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80500C68;
    __6Vector((char *)self + 0x30);
    return self;
}

cGenBreakProp *fn_804690D4(register cGenBreakProp *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80500A60;
    return self;
}

cDamagePropOnTrigger *fn_80469120(register cDamagePropOnTrigger *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80500858;
    return self;
}

cPortalControl *fn_8046916C(register cPortalControl *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80500650;
    return self;
}

cPropRespawn *fn_804691B8(register cPropRespawn *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80500448;
    return self;
}

cRemoveObjects *fn_80469204(register cRemoveObjects *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80500240;
    return self;
}

cCrystalBreak *fn_80469250(register cCrystalBreak *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80500038;
    return self;
}

cCrystalBreak_Phase2 *fn_8046929C(register cCrystalBreak_Phase2 *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FFE30;
    return self;
}

cCameraMPToggle *fn_804692E8(register cCameraMPToggle *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FFC28;
    return self;
}

cLabConsole *fn_80469334(register cLabConsole *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FFA20;
    return self;
}

cWieldableToggle *fn_80469380(register cWieldableToggle *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FF818;
    return self;
}

cReverseWallRenderToggle *fn_804693CC(register cReverseWallRenderToggle *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FF610;
    return self;
}

cPropGroupFade *fn_80469418(register cPropGroupFade *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FF408;
    return self;
}

cMP_MatchTrigger *fn_80469464(register cMP_MatchTrigger *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FF200;
    return self;
}

cCameraSet *fn_804694B0(register cCameraSet *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FEFF8;
    return self;
}

cSoundEvent *fn_804694FC(register cSoundEvent *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80503760;
    return self;
}

cPathnodeToggle *fn_80469548(register cPathnodeToggle *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FE1C0;
    return self;
}

cActorMoveToPos *fn_80469594(register cActorMoveToPos *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FDFB8;
    __6Vector((char *)self + 0x30);
    __6Vector((char *)self + 0x40);
    __6Vector((char *)self + 0x50);
    __6Vector((char *)self + 0x60);
    return self;
}

cActorWalk *fn_80469610(register cActorWalk *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FDDB0;
    fn_8046B5A8((char *)self + 0x38, 0);
    return self;
}

cActorAIPause *fn_8046966C(register cActorAIPause *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FDBA8;
    return self;
}

cActorControlState *fn_804696B8(register cActorControlState *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FD9A0;
    return self;
}

cSpawnPeon *fn_80469704(register cSpawnPeon *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FD798;
    fn_8046B530((char *)self + 0x38);
    fn_8046B5A8((char *)self + 0x40, 0);
    __6Vector((char *)self + 0x90);
    return self;
}

cSpawnGroup *fn_80469778(register cSpawnGroup *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FD590;
    fn_8046B530((char *)self + 0x28);
    fn_8046B530((char *)self + 0x30);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    fn_8046B530((char *)self + 0x60);
    return self;
}

cSpawnController *fn_80469824(register cSpawnController *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FD388;
    return self;
}

cActorPlayPath *fn_80469870(register cActorPlayPath *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FD180;
    return self;
}

cAIRangedAttacker *fn_804698BC(register cAIRangedAttacker *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FCF78;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B530((char *)self + 0x30);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    return self;
}

cBossRingOut *fn_80469954(register cBossRingOut *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FCD70;
    return self;
}

cActorSetHealth *fn_804699A0(register cActorSetHealth *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FCB68;
    return self;
}

cPlayerBonusMissions *fn_804699EC(register cPlayerBonusMissions *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FC960;
    return self;
}

cGlobalPeonCounter *fn_80469A38(register cGlobalPeonCounter *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FC758;
    return self;
}

cAITeleportationToggle *fn_80469A84(register cAITeleportationToggle *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FC550;
    return self;
}

cAIEnemyVictoryScene *fn_80469AD0(register cAIEnemyVictoryScene *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FC348;
    fn_8046B5A8((char *)self + 0x2c, 0);
    return self;
}

cTemporaryAIPossession *fn_80469B2C(register cTemporaryAIPossession *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FC140;
    fn_8046B5A8((char *)self + 0x28, 0);
    return self;
}

cAISetTeleportDistance *fn_80469B88(register cAISetTeleportDistance *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FBF38;
    return self;
}

cRingOut *fn_80469BD4(register cRingOut *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_80502F40;
    return self;
}

cCameraEvent *fn_80469C20(register cCameraEvent *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FE3C8;
    return self;
}

cPowerPlant_HumanTorchSAC *fn_80469C6C(register cPowerPlant_HumanTorchSAC *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FAEF8;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B530((char *)self + 0x30);
    fn_8046B530((char *)self + 0x38);
    fn_8046B638((char *)self + 0x40, 0);
    return self;
}

cPowerPlant_ElektraSAC *fn_80469CF0(register cPowerPlant_ElektraSAC *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FACF0;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B638((char *)self + 0x30, 0);
    fn_8046B530((char *)self + 0x38);
    return self;
}

cPowerPlant_IronMan_3 *fn_80469D68(register cPowerPlant_IronMan_3 *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FAAE8;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B530((char *)self + 0x30);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    fn_8046B530((char *)self + 0x60);
    fn_8046B530((char *)self + 0x68);
    fn_8046B530((char *)self + 0x70);
    fn_8046B530((char *)self + 0x78);
    return self;
}

cPowerPlant_Venom_3 *fn_80469E3C(register cPowerPlant_Venom_3 *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FA8E0;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B530((char *)self + 0x30);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    fn_8046B530((char *)self + 0x60);
    fn_8046B530((char *)self + 0x68);
    fn_8046B530((char *)self + 0x70);
    fn_8046B530((char *)self + 0x78);
    fn_8046B530((char *)self + 0x80);
    fn_8046B530((char *)self + 0x88);
    fn_8046B530((char *)self + 0x90);
    fn_8046B530((char *)self + 0x98);
    fn_8046B530((char *)self + 0xa0);
    fn_8046B530((char *)self + 0xa8);
    fn_8046B530((char *)self + 0xb0);
    return self;
}

cPowerPlant_CoilToggle *fn_80469F64(register cPowerPlant_CoilToggle *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FA6D8;
    __6Vector((char *)self + 0x30);
    return self;
}

cPowerPlant_CoilArc *fn_80469FBC(register cPowerPlant_CoilArc *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FA4D0;
    fn_8046B530((char *)self + 0x28);
    fn_8046B530((char *)self + 0x30);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    fn_8046B530((char *)self + 0x60);
    return self;
}

cBrooklynBridge_heliCrash *fn_8046A068(register cBrooklynBridge_heliCrash *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F8860;
    fn_8046B530((char *)self + 0x28);
    fn_8046B530((char *)self + 0x30);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    return self;
}

cBB_ArenaShutoff *fn_8046A0E4(register cBB_ArenaShutoff *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F8658;
    return self;
}

cBrooklynBridge_ArenaBarrier *fn_8046A130(register cBrooklynBridge_ArenaBarrier *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F8450;
    fn_8046B530((char *)self + 0x2c);
    return self;
}

cBrooklynBridge_AftershockBoss *fn_8046A188(register cBrooklynBridge_AftershockBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F8248;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B638((char *)self + 0x30, 0);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    fn_8046B530((char *)self + 0x60);
    fn_8046B530((char *)self + 0x68);
    fn_8046B530((char *)self + 0x70);
    fn_8046B530((char *)self + 0x78);
    fn_8046B530((char *)self + 0x80);
    fn_8046B530((char *)self + 0x88);
    fn_8042D7B0((char *)self + 0xc4);
    fn_8042D7B0((char *)self + 0x104);
    return self;
}

cBrooklynBridge_VM2_Start *fn_8046A290(register cBrooklynBridge_VM2_Start *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F8040;
    fn_8046B530((char *)self + 0x28);
    fn_8046B530((char *)self + 0x30);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    fn_8046B530((char *)self + 0x60);
    fn_8046B530((char *)self + 0x68);
    return self;
}

cBrooklynBridge_SegmentControl *fn_8046A348(register cBrooklynBridge_SegmentControl *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F7E38;
    return self;
}

cBrooklynBridge_BruteFight *fn_8046A394(register cBrooklynBridge_BruteFight *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F7C30;
    return self;
}

cBrooklynBridge_WolverineSAC *fn_8046A3E0(register cBrooklynBridge_WolverineSAC *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F7A28;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B530((char *)self + 0x30);
    return self;
}

cBrooklynBridge_RockBomb *fn_8046A448(register cBrooklynBridge_RockBomb *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F7820;
    fn_8046B5F0((char *)self + 0x28, 0);
    fn_8046B5A8((char *)self + 0x30, 0);
    fn_8046B530((char *)self + 0x38);
    __6Vector((char *)self + 0x50);
    fn_8042D7B0((char *)self + 0x60);
    return self;
}

cBrooklynBridge_FlameWall *fn_8046A4D8(register cBrooklynBridge_FlameWall *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F7618;
    fn_8046B530((char *)self + 0x2c);
    return self;
}

cBrooklynBridge_HazmatBoss *fn_8046A530(register cBrooklynBridge_HazmatBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F7410;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B638((char *)self + 0x30, 0);
    return self;
}

cBrooklynBridge_AltStormBoss *fn_8046A59C(register cBrooklynBridge_AltStormBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F7208;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B638((char *)self + 0x30, 0);
    return self;
}

cAvengersMansion_ParadoxBoss *fn_8046A608(register cAvengersMansion_ParadoxBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F7000;
    fn_8046B638((char *)self + 0x28, 0);
    fn_8046B5A8((char *)self + 0x30, 0);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    fn_8046B530((char *)self + 0x60);
    fn_8046B530((char *)self + 0x68);
    fn_8046B530((char *)self + 0x70);
    fn_8046B530((char *)self + 0x78);
    fn_8046B530((char *)self + 0x80);
    fn_8046B530((char *)self + 0x88);
    fn_8046B530((char *)self + 0x90);
    fn_8046B530((char *)self + 0x98);
    return self;
}

cAvengersMansion_IM1_Start *fn_8046A710(register cAvengersMansion_IM1_Start *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F6DF8;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B5A8((char *)self + 0x30, 0);
    fn_8046B5A8((char *)self + 0x38, 0);
    fn_8046B5A8((char *)self + 0x40, 0);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    fn_8046B530((char *)self + 0x60);
    fn_8046B530((char *)self + 0x68);
    fn_8046B530((char *)self + 0x70);
    fn_8046B530((char *)self + 0x78);
    fn_8046B530((char *)self + 0x80);
    fn_8046B530((char *)self + 0x88);
    fn_8046B530((char *)self + 0x90);
    fn_8046B530((char *)self + 0x98);
    fn_8046B530((char *)self + 0xa0);
    fn_8046B530((char *)self + 0xa8);
    fn_8046B530((char *)self + 0xb0);
    fn_8046B530((char *)self + 0xb8);
    fn_8046B530((char *)self + 0xc0);
    fn_8046B530((char *)self + 0xc8);
    return self;
}

cAvengersMansion_IronManSAC *fn_8046A868(register cAvengersMansion_IronManSAC *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F6BF0;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B530((char *)self + 0x30);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    return self;
}

cAvengersMansion_HideSkirt *fn_8046A90C(register cAvengersMansion_HideSkirt *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F69E8;
    return self;
}

cDailyBugle_VenomBoss *fn_8046A958(register cDailyBugle_VenomBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F9080;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B638((char *)self + 0x30, 0);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    fn_8046B530((char *)self + 0x60);
    return self;
}

cDailyBugle_SpidermanSac *fn_8046AA0C(register cDailyBugle_SpidermanSac *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F8E78;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B530((char *)self + 0x30);
    return self;
}

cDailyBugle_LetterEffects *fn_8046AA74(register cDailyBugle_LetterEffects *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F8C70;
    return self;
}

cDailyBugle_DaredevilBoss *fn_8046AAC0(register cDailyBugle_DaredevilBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F8A68;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B530((char *)self + 0x30);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    fn_8046B530((char *)self + 0x60);
    fn_8046B530((char *)self + 0x68);
    return self;
}

cRoekelFacility_StormBoss *fn_8046AB7C(register cRoekelFacility_StormBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FBD30;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B638((char *)self + 0x30, 0);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8042D7B0((char *)self + 0x68);
    return self;
}

cRoekelFacility_ThingBoss *fn_8046AC0C(register cRoekelFacility_ThingBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FBB28;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B638((char *)self + 0x30, 0);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    fn_8046B530((char *)self + 0x60);
    fn_8046B530((char *)self + 0x68);
    fn_8046B530((char *)self + 0x70);
    fn_8046B530((char *)self + 0x78);
    fn_8046B530((char *)self + 0x80);
    fn_8046B530((char *)self + 0x88);
    fn_8046B530((char *)self + 0x90);
    fn_8046B530((char *)self + 0x98);
    fn_8046B530((char *)self + 0xa0);
    __6Vector((char *)self + 0xd0);
    __6Vector((char *)self + 0xe0);
    fn_8042D7B0((char *)self + 0xf0);
    return self;
}

cRoekelFacility_RockBomb *fn_8046AD44(register cRoekelFacility_RockBomb *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FB920;
    fn_8046B5F0((char *)self + 0x28, 0);
    fn_8046B5A8((char *)self + 0x30, 0);
    __6Vector((char *)self + 0x40);
    fn_8042D7B0((char *)self + 0x50);
    return self;
}

cRoekelFacility_BlastDoor *fn_8046ADC8(register cRoekelFacility_BlastDoor *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FB718;
    fn_8046B5F0((char *)self + 0x28, 0);
    return self;
}

cRoekelFacility_RoekelBoss *fn_8046AE24(register cRoekelFacility_RoekelBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FB510;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B5A8((char *)self + 0x30, 0);
    fn_8046B5A8((char *)self + 0x38, 0);
    fn_8046B638((char *)self + 0x40, 0);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    fn_8046B530((char *)self + 0x60);
    fn_8042D7B0((char *)self + 0x68);
    __6Vector((char *)self + 0xe0);
    __6Vector((char *)self + 0xf0);
    return self;
}

cRoekelFacility_PlasmaMine *fn_8046AF04(register cRoekelFacility_PlasmaMine *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FB308;
    fn_8046B530((char *)self + 0x28);
    fn_8046B530((char *)self + 0x30);
    fn_8046B5A8((char *)self + 0x38, 0);
    __6Vector((char *)self + 0x50);
    __6Vector((char *)self + 0x60);
    return self;
}

cRoekelFacility_Lasers *fn_8046AF90(register cRoekelFacility_Lasers *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FB100;
    return self;
}

cNYCStreets_DaredevilBoss *fn_8046AFDC(register cNYCStreets_DaredevilBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FA2C8;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B638((char *)self + 0x30, 0);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    fn_8046B530((char *)self + 0x60);
    return self;
}

cNYCStreetsMP_SegmentControl *fn_8046B090(register cNYCStreetsMP_SegmentControl *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804FA0C0;
    return self;
}

cNYCStreets_ThingBoss *fn_8046B0DC(register cNYCStreets_ThingBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F9EB8;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B530((char *)self + 0x30);
    fn_8046B638((char *)self + 0x38, 0);
    return self;
}

cNYCStreets_TorchBoss *fn_8046B154(register cNYCStreets_TorchBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F9CB0;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B638((char *)self + 0x30, 0);
    return self;
}

cGrandCentral_VenomBoss *fn_8046B1C0(register cGrandCentral_VenomBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F9AA8;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B530((char *)self + 0x30);
    fn_8046B638((char *)self + 0x38, 0);
    return self;
}

cGrandCentral_OhmBoss *fn_8046B238(register cGrandCentral_OhmBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F98A0;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B638((char *)self + 0x30, 0);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    fn_8046B530((char *)self + 0x60);
    fn_8046B530((char *)self + 0x68);
    fn_8046B5F0((char *)self + 0x70, 0);
    fn_8046B5F0((char *)self + 0x78, 0);
    fn_8042D7B0((char *)self + 0xb0);
    return self;
}

cGrandCentral_HazmatBoss *fn_8046B324(register cGrandCentral_HazmatBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F9698;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B530((char *)self + 0x30);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    return self;
}

cGrandCentral_MagnetoBoss *fn_8046B3A4(register cGrandCentral_MagnetoBoss *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F9490;
    fn_8046B5A8((char *)self + 0x28, 0);
    fn_8046B638((char *)self + 0x30, 0);
    fn_8046B530((char *)self + 0x38);
    fn_8046B530((char *)self + 0x40);
    fn_8046B530((char *)self + 0x48);
    fn_8046B530((char *)self + 0x50);
    fn_8046B530((char *)self + 0x58);
    fn_8046B530((char *)self + 0x60);
    fn_8046B530((char *)self + 0x68);
    fn_8046B530((char *)self + 0x70);
    fn_8046B530((char *)self + 0x78);
    fn_8046B530((char *)self + 0x80);
    fn_8046B530((char *)self + 0x88);
    fn_8046B530((char *)self + 0x90);
    return self;
}

cGrandCentral_RockBomb *fn_8046B4A0(register cGrandCentral_RockBomb *self)
{
    fn_80441FAC(self);
    self->vptr = lbl_804F9288;
    fn_8046B5F0((char *)self + 0x28, 0);
    fn_8046B5A8((char *)self + 0x30, 0);
    fn_8046B530((char *)self + 0x38);
    __6Vector((char *)self + 0x50);
    fn_8042D7B0((char *)self + 0x60);
    return self;
}

}
