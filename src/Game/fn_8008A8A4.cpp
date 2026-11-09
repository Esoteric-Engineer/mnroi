// fn_8008A8A4: motion system boot: the flag names, the motion id -> state name and default flags tables, and the base motion sets.
// Owns .rodata 0x804889D4-0x8048A16C. "" (lbl_804889B8) precedes it, so it stays extern.

typedef struct FlagName
{
    unsigned int value; // +0x00
    char *name;         // +0x04
} FlagName;

extern "C" void *memset(void *dst, int c, unsigned n);
extern "C" unsigned int fn_800908CC(char *str); // ORs the flags named in a space-separated string
extern "C" void *fn_801B4284(int capacity, char *name);
extern "C" void *fn_8008F470(char *name, int a, int b);

extern int lbl_8066B8F0; // the init-done flag
extern int lbl_8066C660;
extern char *lbl_8054F1F0[0x174];        // motion-state names, by motion id
extern unsigned int lbl_8054F7C0[0x174]; // default flags, by motion id
extern FlagName lbl_8054FD90[16];        // flag names
extern unsigned int lbl_8066D630;        // lbl_8054FD90's count
extern char lbl_805520F0[0x20];
extern char lbl_804889B8[]; // ""
extern void *lbl_8066B8F4; // the motion-set registry
extern void *lbl_8066B8F8; // male.nms
extern void *lbl_8066B8FC; // female.nms
extern void *lbl_8066B900; // brute.nms
extern void *lbl_8066B904; // female2.nms
extern void *lbl_8066B908; // humanpeon.nms
extern void *lbl_8066B90C; // brutepeon.nms

#define FLAG(n, v)                         \
    lbl_8054FD90[lbl_8066D630].name = (n); \
    lbl_8054FD90[lbl_8066D630++].value = (v);

#define STATE(id, n, f)     \
    lbl_8054F1F0[id] = (n); \
    lbl_8054F7C0[id] = fn_800908CC(f)

inline int sn_return_decl(int a) { return a; }

extern "C" int fn_8008A8A4(void)
{
    if (lbl_8066B8F0)
        return 1;

    lbl_8066C660 = 1;
    memset(lbl_8054F1F0, 0, sizeof(lbl_8054F1F0));
    memset(lbl_8054FD90, 0, sizeof(lbl_8054FD90));
    memset(lbl_805520F0, 0, sizeof(lbl_805520F0));

    lbl_8066D630 = 0;
    FLAG("noloop", 0x1)
    FLAG("noframereset", 0x2)
    FLAG("resetmotion", 0x4)
    FLAG("opt", 0x8)
    FLAG("endpause", 0x10)
    FLAG("endtag", 0x20)
    FLAG("variable", 0x100)
    FLAG("special", 0x400)
    FLAG("nofadeout", 0x80)
    FLAG("nofadein", 0x40)
    FLAG("fidget", 0x2000)
    FLAG("add", 0x4000)
    FLAG("mix", 0x8000)
    FLAG("shockwave", 0x1000000)

    STATE(0x1, "Walk", "noframereset");
    STATE(0x2, "Run", "noframereset");
    STATE(0x3, "SuperRun", "noframereset");
    STATE(0x4, "Stand", " ");
    STATE(0x5, "Idle", "noloop endtag opt");
    STATE(0x6, "Jump", "noloop endtag");
    STATE(0x7, "RunJump", "noloop endtag");
    STATE(0x8, "SuperJump", "noloop endtag");
    STATE(0x9, "SuperRunJump", "noloop endtag");
    STATE(0xa, "DoubleJump", "opt");
    STATE(0xb, "Fall", lbl_804889B8);
    STATE(0xc, "Flail", lbl_804889B8);
    STATE(0xd, "FlailLand", "noloop nofadein");
    STATE(0xe, "Land", "noloop");
    STATE(0xf, "RunLand", "noloop");
    STATE(0x10, "WalkLand", "noloop");
    STATE(0x11, "SuperLand", "noloop");
    STATE(0x12, "SuperRunLand", "noloop");
    STATE(0x13, "Turn180", "noloop");
    STATE(0x14, "TurnLeft", "opt");
    STATE(0x15, "TurnRight", "opt");
    STATE(0x16, "StrafeLeft", lbl_804889B8);
    STATE(0x17, "StrafeRight", lbl_804889B8);
    STATE(0x18, "StrafeBack", lbl_804889B8);
    STATE(0x19, "ProneIdle", lbl_804889B8);
    STATE(0x1a, "ProneGetup", "endpause endtag");
    STATE(0x1b, "PowerOn", "noloop opt");
    STATE(0x1c, "PowerOff", "noloop opt");
    STATE(0x1d, "PowerStand", lbl_804889B8);
    STATE(0x1e, "FlyUp", "opt noframereset");
    STATE(0x1f, "FlyDown", "opt noframereset");
    STATE(0x20, "FlyIdle", "opt noframereset");
    STATE(0x21, "FlyTakeoff", "noloop endtag opt");
    STATE(0x22, "StandToRun", "noloop");
    STATE(0x23, "StandToRunLeft", "noloop");
    STATE(0x24, "StandToRunRight", "noloop");
    STATE(0x25, "StandToRunBack", "noloop");
    STATE(0x26, "LowEnergyStun", "noloop opt");
    STATE(0x27, "Attack1", "noloop");
    STATE(0x28, "Attack2", "noloop");
    STATE(0x29, "Attack3", "noloop");
    STATE(0x2a, "Attack4", "noloop opt");
    STATE(0x2b, "AttackFar", "noloop");
    STATE(0x2c, "AttackStomp", "noloop");
    STATE(0x2d, "LowAttack", "noloop");
    STATE(0x2e, "RiseAttack", "noloop");
    STATE(0x2f, "SuperAttack1", "noloop");
    STATE(0x30, "SuperAttack2", "noloop");
    STATE(0x31, "SuperAttack3", "noloop");
    STATE(0x32, "SuperAttack4", "noloop opt");
    STATE(0x33, "SuperAttackFar", "noloop");
    STATE(0x34, "SuperAttackStomp", "noloop");
    STATE(0x35, "SuperLowAttack", "noloop");
    STATE(0x36, "SuperRiseAttack", "endpause");
    STATE(0x37, "JumpAttackPeak", "endpause");
    STATE(0x38, "JumpAttackPeak2", "endpause");
    STATE(0x39, "JumpAttackDesc", "noloop");
    STATE(0x3a, "JumpAttackDescLand", "noloop");
    STATE(0x3b, "SuperJumpAttack", "endpause");
    STATE(0x3c, "SuperJumpAttackDesc", "noloop");
    STATE(0x3d, "SuperJumpAttackDescLand", "noloop");
    STATE(0x3e, "AirAttack", "endpause opt");
    STATE(0x3f, "AirAttackFar", "noloop opt");
    STATE(0x40, "SuperAirAttack", "noloop opt");
    STATE(0x42, "WallAttackStart", "endpause opt");
    STATE(0x43, "WallAttackEnd", "endpause opt");
    STATE(0x44, "WallAttackLoop", "opt");
    STATE(0x45, "SuperWallAttackStart", "endpause opt");
    STATE(0x46, "SuperWallAttackEnd", "endpause opt");
    STATE(0x47, "SuperWallAttackLoop", "opt");
    STATE(0x48, "SwingAttack", "noloop");
    STATE(0x49, "SuperSwingAttack", "noloop");
    STATE(0x4a, "WireAttack", "noloop");
    STATE(0x4b, "SuperWireAttack", "noloop");
    STATE(0x4c, "Block", lbl_804889B8);
    STATE(0x4d, "BlockStart", "endpause endtag");
    STATE(0x4e, "BlockEnd", "endpause");
    STATE(0x4f, "BlockHardRedirect", "endpause");
    STATE(0x50, "BlockSoftRedirect", "endpause");
    STATE(0x51, "BlockBreakZero", "endpause");
    STATE(0x52, "BlockBreakLight", "endpause");
    STATE(0x53, "BlockBreakMedium", "endpause");
    STATE(0x54, "BlockBreakLarge", "endpause");
    STATE(0x55, "SuperBlock", "noloop");
    STATE(0x56, "DodgeForward", "endpause");
    STATE(0x57, "DodgeForwardLoop", "endpause opt");
    STATE(0x58, "DodgeLeft", "endpause");
    STATE(0x59, "DodgeRight", "endpause");
    STATE(0x5a, "DodgeBack", "endpause");
    STATE(0x5b, "DodgeBackLoop", "endpause opt");
    STATE(0x5c, "DodgeExitAttack", "noloop");
    STATE(0x5d, "DodgeExitSuperAttack", "noloop");
    STATE(0x5e, "AttackHardRedirect", "noloop");
    STATE(0x5f, "AttackSoftRedirect", "noloop");
    STATE(0x60, "RangedAttack", "noloop opt");
    STATE(0x61, "SuperRangedAttack", "noloop opt");
    STATE(0x62, "AirRangedAttack", "noloop opt");
    STATE(0x63, "SuperAirRangedAttack", "noloop opt");
    STATE(0x64, "WallClimbRangedAttack", "noloop opt");
    STATE(0x65, "HitReactStab", "endpause");
    STATE(0x66, "HitReactGroin", "endpause");
    STATE(0x67, "HitReactFire", "endpause");
    STATE(0x68, "HitReactShock", "endpause");
    STATE(0x69, "HitReactLight", "endpause");
    STATE(0x6a, "HitReactLightLeft", "endpause");
    STATE(0x6b, "HitReactLightRight", "endpause");
    STATE(0x6c, "HitReactMedium", "endpause");
    STATE(0x6d, "HitReactMediumLeft", "endpause");
    STATE(0x6e, "HitReactMediumRight", "endpause");
    STATE(0x6f, "HitReactLarge", "endpause");
    STATE(0x70, "HitReactLargeLeft", "endpause");
    STATE(0x71, "HitReactLargeRight", "endpause");
    STATE(0x72, "HitReactUp", "endpause");
    STATE(0x73, "HitReactCrush", "endpause");
    STATE(0x74, "HitReactInPlace", "endpause");
    STATE(0x75, "LowReactMedium", "endpause");
    STATE(0x76, "LowReactLarge", "endpause");
    STATE(0x77, "BlockreactZero", "noloop");
    STATE(0x78, "BlockreactLight", "noloop");
    STATE(0x79, "BlockreactMedium", "noloop");
    STATE(0x7a, "BlockReactLarge", "noloop");
    STATE(0x7b, "AirReactMedium", "endpause");
    STATE(0x7c, "AirReactLarge", "endpause");
    STATE(0x7d, "ProneReactMedium", "endpause endtag");
    STATE(0x7e, "ProneReactLarge", "endpause endtag");
    STATE(0x7f, "HugeReact", "noloop endtag");
    STATE(0x86, "HugeReactLoop", lbl_804889B8);
    STATE(0x87, "HugeReactLoopDesc", lbl_804889B8);
    STATE(0x94, "HugeReactFloor", "noloop endtag");
    STATE(0x95, "HugeReactFloorRecover", "noloop endtag");
    STATE(0x96, "HugeReactWall", "noloop endtag");
    STATE(0x97, "HugeReactWallRecover", "noloop endtag");
    STATE(0x98, "HugeReactAirRecover", "noloop endtag");
    STATE(0x80, "HugeReact2", "noloop endtag");
    STATE(0x88, "HugeReactLoop2", lbl_804889B8);
    STATE(0x89, "HugeReactLoop2Desc", lbl_804889B8);
    STATE(0x81, "HugeReact3", "noloop endtag opt");
    STATE(0x8a, "HugeReactLoop3", "opt");
    STATE(0x8b, "HugeReactLoop3Desc", "opt");
    STATE(0x82, "HugeReact4", "noloop endtag opt");
    STATE(0x8c, "HugeReactLoop4", "opt");
    STATE(0x8d, "HugeReactLoop4Desc", "opt");
    STATE(0x83, "HugeReact5", "noloop endtag opt");
    STATE(0x8e, "HugeReactLoop5", "opt");
    STATE(0x8f, "HugeReactLoop5Desc", "opt");
    STATE(0x84, "HugeReactUp", "noloop endtag opt");
    STATE(0x90, "HugeReactUpLoop", "opt");
    STATE(0x91, "HugeReactUpLoopDesc", "opt");
    STATE(0x85, "HugeReactAir", "noloop endtag opt");
    STATE(0x92, "HugeReactAirLoop", "opt");
    STATE(0x93, "HugeReactAirLoopDesc", "opt");
    STATE(0x99, "HugeReactFloor3", "noloop endtag");
    STATE(0x9a, "HugeReactFloor4", "noloop endtag");
    STATE(0x9b, "HugeReactFloor5", "noloop endtag");
    STATE(0x9c, "HugeReactWall3", "noloop endtag");
    STATE(0x9d, "HugeReactWall4", "noloop endtag");
    STATE(0x9e, "HugeReactWall5", "noloop endtag");
    STATE(0x9f, "Throw", "endpause");
    STATE(0xa0, "ThrowFemale", "endpause");
    STATE(0xa1, "ThrowBrute", "endpause");
    STATE(0xa2, "SuperThrow", "endpause");
    STATE(0xa3, "SuperThrowFemale", "endpause");
    STATE(0xa4, "SuperThrowBrute", "endpause");
    STATE(0xa5, "ThrowMiss", "noloop");
    STATE(0xa6, "ThrowVictim", "endpause");
    STATE(0xa7, "ThrowVictimFemale", "endpause");
    STATE(0xa8, "ThrowVictimBrute", "endpause");
    STATE(0xa9, "SuperThrowVictim", "endpause");
    STATE(0xaa, "SuperThrowVictimFemale", "endpause");
    STATE(0xab, "SuperThrowVictimBrute", "endpause");
    STATE(0xac, "AirThrow", "endpause opt");
    STATE(0xad, "AirThrowFemale", "endpause opt");
    STATE(0xae, "AirThrowBrute", "endpause opt");
    STATE(0xaf, "AirThrowVictim", "endpause opt");
    STATE(0xb0, "AirThrowVictimFemale", "endpause opt");
    STATE(0xb1, "AirThrowVictimBrute", "endpause opt");
    STATE(0xb2, "AirThrowVictimFlyer", "endpause opt");
    STATE(0xb3, "SuperAirThrow", "endpause opt");
    STATE(0xb4, "SuperAirThrowFemale", "endpause opt");
    STATE(0xb5, "SuperAirThrowBrute", "endpause opt");
    STATE(0xb6, "SuperAirThrowVictim", "endpause opt");
    STATE(0xb7, "SuperAirThrowVictimFemale", "endpause opt");
    STATE(0xb8, "SuperAirThrowVictimBrute", "endpause opt");
    STATE(0xb9, "SuperAirThrowVictimFlyer", "endpause opt");
    STATE(0xba, "FinishingMove", "endpause");
    STATE(0xbb, "FinishingMoveFemale", "endpause");
    STATE(0xbc, "FinishingMoveBrute", "endpause");
    STATE(0xbd, "FinishingMoveVictim", "endpause");
    STATE(0xbe, "FinishingMoveVictimFemale", "endpause");
    STATE(0xbf, "FinishingMoveVictimBrute", "endpause");
    STATE(0xc0, "DeathQuick", "endpause opt");
    STATE(0xc1, "DeathDramatic", "endpause opt");
    STATE(0xc2, "DeathProne", "endpause opt");
    STATE(0xc3, "DeathFall", "endpause opt");
    STATE(0xc4, "CarryLiftSmall", "endpause");
    STATE(0xc5, "CarryIdleSmall", lbl_804889B8);
    STATE(0xc6, "CarryWalkSmall", "noframereset");
    STATE(0xc7, "CarryRunSmall", "noframereset");
    STATE(0xc8, "CarryTossSmall", "endpause");
    STATE(0xc9, "CarryFallSmall", lbl_804889B8);
    STATE(0xca, "CarryLandSmall", "noloop");
    STATE(0xcb, "CarryJumpSmall", "noloop endtag");
    STATE(0xcc, "CarryRunJumpSmall", "noloop endtag");
    STATE(0xcd, "CarryRunJumpLandSmall", "noloop");
    STATE(0xce, "CarryJumpThrowSmall", "noloop");
    STATE(0xcf, "CarryLiftLarge", "endpause opt");
    STATE(0xd0, "CarryIdleLarge", "opt");
    STATE(0xd1, "CarryWalkLarge", "noframereset opt");
    STATE(0xd2, "CarryRunLarge", "noframereset opt");
    STATE(0xd3, "CarryTossLarge", "endpause opt");
    STATE(0xd4, "CarryFallLarge", "opt");
    STATE(0xd5, "CarryLandLarge", "noloop opt");
    STATE(0xd6, "CarryJumpLarge", "noloop endtag opt");
    STATE(0xd7, "CarryRunJumpLarge", "noloop endtag opt");
    STATE(0xd8, "CarryRunJumpLandLarge", "noloop opt");
    STATE(0xd9, "CarryJumpThrowLarge", "noloop opt");
    STATE(0xda, "FlyCarryTossSmall", "noloop opt");
    STATE(0xdb, "FlyCarrySmall", "opt");
    STATE(0xdc, "FlyCarryTakeoffSmall", "noloop endtag opt");
    STATE(0xdd, "FlyCarryTossLarge", "noloop opt");
    STATE(0xde, "FlyCarryLarge", "opt");
    STATE(0xdf, "FlyCarryTakeoffLarge", "noloop endtag opt");
    STATE(0xe0, "CatchObject", "noloop");
    STATE(0xe1, "CatchObjectLarge", "noloop opt");
    STATE(0xe2, "CatchObjectFly", "noloop opt");
    STATE(0xe3, "SwatObject", "noloop");
    STATE(0xe4, "RedirectObject", "noloop opt");
    STATE(0xe5, "RedirectObjectLarge", "noloop opt");
    STATE(0xe6, "CarryLiftMiss", "noloop opt");
    STATE(0xe7, "CarryTossSmash", "endpause opt");
    STATE(0xe8, "WieldLiftMiss", "noloop opt");
    STATE(0xe9, "WieldPickupWall", "noloop");
    STATE(0xea, "WieldPickupFloor", "noloop");
    STATE(0xeb, "WieldStand", lbl_804889B8);
    STATE(0xec, "WieldSwing", "noloop");
    STATE(0xed, "WieldSwing2", "noloop opt");
    STATE(0xee, "WieldThrow", "noloop");
    STATE(0xef, "WieldJump", "noloop");
    STATE(0xf0, "WieldJumpAttack", "noloop");
    STATE(0xf1, "WieldStomp", "noloop");
    STATE(0xf2, "WieldWalk", lbl_804889B8);
    STATE(0xf3, "WieldRun", lbl_804889B8);
    STATE(0xf4, "WieldRunJump", "endpause");
    STATE(0xf5, "WieldRunJumpLand", "endpause");
    STATE(0xf6, "WieldFly", "opt");
    STATE(0xf7, "WieldFlySwing", "noloop opt");
    STATE(0xf8, "WieldTakeOff", "noloop endtag opt");
    STATE(0xf9, "WieldFall", lbl_804889B8);
    STATE(0xfa, "WieldLand", "noloop");
    STATE(0xfb, "WieldStandLarge", lbl_804889B8);
    STATE(0xfc, "WieldSwingLarge", "noloop");
    STATE(0xfd, "WieldSwing2Large", "noloop opt");
    STATE(0xfe, "WieldThrowLarge", "noloop");
    STATE(0xff, "WieldJumpLarge", "noloop");
    STATE(0x100, "WieldJumpAttackLarge", "noloop");
    STATE(0x101, "WieldStompLarge", "noloop");
    STATE(0x102, "WieldWalkLarge", lbl_804889B8);
    STATE(0x103, "WieldRunLarge", lbl_804889B8);
    STATE(0x104, "WieldRunJumpLarge", "endpause");
    STATE(0x105, "WieldRunJumpLandLarge", "endpause");
    STATE(0x106, "WieldFlyLarge", "opt");
    STATE(0x107, "WieldFlySwingLarge", "noloop opt");
    STATE(0x108, "WieldTakeOffLarge", "noloop endtag opt");
    STATE(0x109, "WieldFallLarge", lbl_804889B8);
    STATE(0x10a, "WieldLandLarge", "noloop");
    STATE(0x10c, "WallRunLeft", "endpause opt");
    STATE(0x10d, "WallRunRight", "endpause opt");
    STATE(0x10e, "WallRunUp", "endpause opt");
    STATE(0x10f, "WallJumpOff", "endpause opt");
    STATE(0x110, "WallJumpToWall", "endpause opt");
    STATE(0x111, "WallRunJumpOff", "endpause opt");
    STATE(0x112, "WireExtend", "endpause opt");
    STATE(0x113, "WireExtendUp", "endpause opt");
    STATE(0x114, "WireExtendAngle", "endpause opt");
    STATE(0x115, "WirePull", "noloop endtag opt");
    STATE(0x116, "WirePullFly", "noloop endtag opt");
    STATE(0x117, "WireRelease", "noloop endtag opt");
    STATE(0x118, "WireSwing", "noloop endtag opt");
    STATE(0x119, "WireSwingJump", "noloop endtag opt");
    STATE(0x11a, "PullUp", "noloop");
    STATE(0x11b, "LedgeGrab", "endpause");
    STATE(0x11c, "LedgeHang", "opt");
    STATE(0x11d, "WireSlide", "opt");
    STATE(0x11e, "WallClimbDown", "noloop endtag opt");
    STATE(0x11f, "WallClimbUp", "noloop endtag opt");
    STATE(0x120, "WallClimbLeft", "noloop endtag opt");
    STATE(0x121, "WallClimbRight", "noloop endtag opt");
    STATE(0x122, "WallClimbStand", "opt");
    STATE(0x123, "WallClimbRightToLeft", "noloop endtag opt");
    STATE(0x124, "WallClimbLeftToRight", "noloop endtag opt");
    STATE(0x125, "RagdollRecover_Up", "opt");
    STATE(0x126, "RagdollRecover_Down", "opt");
    STATE(0x127, "RagdollRecover_UpToStand", "opt");
    STATE(0x128, "RagdollRecover_DownToStand", "opt");
    STATE(0x129, "ConstraintPose", "opt");
    STATE(0x12a, "IKHeadLeft", "opt");
    STATE(0x12b, "IKHeadRight", "opt");
    STATE(0x12c, "IKHeadUp", "opt");
    STATE(0x12d, "IKHeadDown", "opt");
    STATE(0x12e, "IKAimUp", "opt");
    STATE(0x12f, "IKAimDown", "opt");
    STATE(0x130, "IKTurnLeft", "opt");
    STATE(0x131, "IKTurnRight", "opt");
    STATE(0x132, "IKFlyLeft", "opt");
    STATE(0x133, "IKFlyRight", "opt");
    STATE(0x134, "IKFlyForward", "opt");
    STATE(0x135, "IKFlyBack", "opt");
    STATE(0x136, "IKBack", "opt");
    STATE(0x137, "IKClaws", "opt");
    STATE(0x138, "scanstand", "opt");
    STATE(0x139, "scanwalk", "opt");
    STATE(0x13a, "focuswalk", "opt");
    STATE(0x13b, "curious", "opt");
    STATE(0x13c, "perkup", "opt");
    STATE(0x13d, "victory", "opt");
    STATE(0x13e, "surprise", "opt");
    STATE(0x13f, "cower", "opt");
    STATE(0x140, "idle_attack", "opt");
    STATE(0x141, "idle_fight", "opt");
    STATE(0x142, "confused", "opt");
    STATE(0x143, "sneak", "opt");
    STATE(0x144, "hurt", "opt");
    STATE(0x145, "talk", "opt");
    STATE(0x146, "listen", "opt");
    STATE(0x147, "create", "opt");
    STATE(0x148, "transform", "opt");
    STATE(0x149, "untransform", "opt");
    STATE(0x14a, "gesture1", "noloop opt");
    STATE(0x14b, "gesture2", "noloop opt");
    STATE(0x14c, "gesture3", "noloop opt");
    STATE(0x14d, "gesture4", "noloop opt");
    STATE(0x14e, "action1", "noloop opt");
    STATE(0x14f, "action2", "noloop opt");
    STATE(0x150, "action3", "noloop opt");
    STATE(0x151, "action4", "noloop opt");
    STATE(0x152, "action5", "noloop opt");
    STATE(0x153, "action6", "noloop opt");
    STATE(0x154, "action7", "noloop opt");
    STATE(0x155, "action8", "noloop opt");
    STATE(0x156, "action9", "noloop opt");
    STATE(0x157, "action10", "noloop opt");
    STATE(0x158, "special1", "opt");
    STATE(0x159, "special2", "opt");
    STATE(0x15a, "special3", "opt");
    STATE(0x15b, "special4", "opt");
    STATE(0x15c, "special5", "opt");
    STATE(0x15d, "special6", "opt");
    STATE(0x15e, "special7", "opt");
    STATE(0x15f, "special8", "opt");
    STATE(0x160, "special9", "opt");
    STATE(0x161, "special10", "opt");
    STATE(0x162, "hitReaction_body", "noloop opt");
    STATE(0x163, "hitReaction_head", "noloop opt");
    STATE(0x164, "hitReaction_burrow", "noloop opt");
    STATE(0x165, "hitReaction_leftarm", "noloop opt");
    STATE(0x166, "hitReaction_rightarm", "noloop opt");
    STATE(0x167, "hitReaction_leftleg", "noloop opt");
    STATE(0x168, "hitReaction_rightleg", "noloop opt");
    STATE(0x169, "hitReaction_gun", "noloop opt");
    STATE(0x16a, "hitReaction_user0", "noloop opt");
    STATE(0x16b, "hitReaction_user1", "noloop opt");
    STATE(0x16c, "hitReaction_user2", "noloop opt");
    STATE(0x16d, "hitReaction_user3", "noloop opt");
    STATE(0x16e, "hitReaction_user4", "noloop opt");
    STATE(0x16f, "hitReaction_user5", "noloop opt");
    STATE(0x170, "hitReaction_user6", "noloop opt");
    STATE(0x171, "hitReaction_user7", "noloop opt");
    STATE(0x172, "hitReaction_user8", "noloop opt");
    STATE(0x173, "hitReaction_user9", "noloop opt");

    lbl_8066B8F4 = fn_801B4284(0x100, "gameMotion");
    if (lbl_8066B8F4 == 0) {
        lbl_8066C660 = 0;
        return 0;
    }

    lbl_8066B8F8 = fn_8008F470("male.nms", 1, 0);
    lbl_8066B8FC = fn_8008F470("female.nms", 1, 0);
    lbl_8066B900 = fn_8008F470("brute.nms", 1, 0);
    lbl_8066B904 = fn_8008F470("female2.nms", 1, 0);
    lbl_8066B908 = fn_8008F470("humanpeon.nms", 1, 0);
    lbl_8066B90C = fn_8008F470("brutepeon.nms", 1, 0);

    lbl_8066B8F0 = 1;
    lbl_8066C660 = 0;
    return 1;
}
