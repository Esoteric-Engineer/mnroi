# Story Mode Map

Where the story-mode code and the level script system it runs on are, how they are layered, and the order to decompile them in (section 6).

See also:
- The per-function loop: [`workflow.md`](workflow.md).
- How the frontend loads an `.nsc` record (`GameFlow` commands 0x25E-0x35E): [`versus.md`](versus.md#6-the-gameflow-command-dispatcher) section 6.
- The `.nsc` mission record and its fields: [`characters.md`](characters.md) section 4, "The script record".
- The AI that the actor script classes drive: [`ai.md`](ai.md).

**This is a reference, not a narrative: read the section you need.** `configure.py` is the authority on which units are matched, and a matched function's source is the authority on what it does; this file records what the source can't say. **The script class names (`cSpawnPeon`...) are the DOL's**: `fn_801BEE2C` registers each class under that string. They are probably the C++ names too, but that is unconfirmed, so script symbols stay `fn_` and `extern "C"`, and the names are used only as struct type names in source. The base class has no name in the DOL.

---

## 1. Entry Points

- **Startup.** `fn_8002F3A8` calls `fn_8007C8B0`, which creates the class table (`fn_8007891C`) and then registers all 102 classes (`fn_801BEE2C`, section 4.2).
- **Story frontend.** The APT handlers in `Game/handlers/mission.cpp` (registered as [`versus.md`](versus.md) section 1 describes) call the chronicle (0x80087040, section 4.4) and the save profile `fn_8011CA74`.
- **Mission start.** `fn_8008856C` (chronicle file) creates the record's master script (`+0x2A0`, the 4th `MISSION` argument) through `fn_800789DC`. No mission in `clashsp.nsc` or `clashMP.nsc` names one.
- **Level load.** `fn_8002CE78` (`Game/fn_8002CE78.cpp`) calls:
  - `fn_800777C4("global", 1)` and `fn_800777C4(scene, 0)`, which open `<name>.nhg`;
  - `fn_800A4DF8(name, level, 0)`, the `.nsd` scene reader (allocator tags `Game:Scene:tScene`, `tPlayerStart`, `tInterestSpot`).
- **Instances.** `fn_800789DC(name, flag)` finds a class (`fn_80078994`) and clones its prototype (slot 2, section 4.1). Its callers:
  - the entity property 0x10 `SCRIPT` (`fn_8007CA10`, [`characters.md`](characters.md) section 3);
  - mission start, above;
  - the versus setup `fn_800916BC`, which creates `cRingOut` and `cCameraEvent`, the two classes no scene places.

---

## 2. File Map

All of it is `-O0` game code. A `.ctors` entry (`_GLOBAL_.I`) ends a file that has static constructors; a `_GLOBAL_.D` can follow it.

| Range | Contents | Row |
|---|---|---|
| 0x80074814-0x8007A3A0 | **Script base file**, one `.ctors` file. It has an inner edge near 0x8007608C: the pair-carrying run ends at 0x80076004, a pair-less run starts at 0x8007608C, and a second `"invalid"` (0x80487BE8) ends the first part's `.rodata` (the debris names `deb_*`, `cel_ConcreteChunk_*`). From 0x8007608C: Havok and `ShapeRepository`, the `.nhg` loader `fn_800777C4`. From 0x8007891C: the class table and the base class (section 4.1). Then static init `fn_800796A4`, the base class's inline virtuals ([`prodg.md`](prodg.md#inline-functions-and-the-tail-of-text)), `_GLOBAL_.I` 0x8007A318 and `_GLOBAL_.D` 0x8007A35C | 4, 22 |
| 0x8007A3A0-0x80081E08 | **Script command files**, four of them (edges below): the AI script API and handle commands (`Game/fn_8007A3A0.cpp`); script init, the `SCRIPT` property, `Scripts:Params`, entity links and the message queue (`Game/fn_8007C8B0.cpp`); the broadcasts to live scripts and the entity event hooks, among them the `cAIMessages` targets (`Game/fn_8007DC60.cpp`); more handle commands and the static init `fn_80081D00` (`Game/fn_800808D0.cpp`) | 5 |
| 0x80087040-0x8008995C | **Chronicle file**, `Game/fn_80087040.cpp`, with the `.nsc` parser and the static init `fn_80089854` that constructs both tables. Start edge: the two functions before it work on entity fields, and its `.rodata` opens with `GAME:CHRONS` right after the entity code's pool (0x80488758, read by `fn_80086C80`) | 2 |
| 0x800A3588-0x800A90B0 | Three files, not one ([`versus.md`](versus.md) section 5's template file is wider than one `.ctors` file). **Prop file** to 0x800A473C, `Game/fn_800A3588.cpp`: its `.rodata` ends with the debris-header tail (`deb_*` ... `"invalid"`, 0x8048B2EC-0x8048B4E4, unclaimed), and its accessors from 0x800A3E54 are the deferred inlines whose pools sit in that tail. **Kind-3 class file** 0x800A473C-0x800A4DF8, `Game/fn_800A473C.cpp`, from its constructor (vtable `lbl_804F5080`). **Scene reader file** 0x800A4DF8 to `_GLOBAL_.I` 0x800A90B0: `fn_800A4DF8` (0x1D30) and its helpers `fn_800A7208`, `fn_800A7A0C`, `fn_800A82B8`; `.rodata` from `CAsyncLoader:Instance` 0x8048B508 | 14 |
| 0x80107244-0x8010A448 | `Game/handlers/memcard.cpp`: 66 handlers, mostly wrappers over the save profile. Static init 0x801099E8, `_GLOBAL_.I` 0x8010A40C | 23 |
| 0x8010A448-0x8010BED8 | `Game/handlers/mission.cpp`: 16 handlers and the static init | 1 |
| 0x8011C55C-0x8011EDE0 | **Save profile**, `Game/fn_8011C55C.cpp`. Start: every caller of the empty `fn_8011C55C` is a profile function, and the save-buffer constructor `fn_8011C578` sets the pair flag for the pair-less run after it; the previous file's `.rodata` ends at 0x804993D4 with its own copy of the memory-card header strings. End: the memory-card manager follows (singleton `lbl_8066BE2C`, init `fn_8011EDE0`, vtable 0x804F59B8), and its `.rodata` (from 0x80499568) repeats the strings that end the profile's. The profile's 0x80499430-0x80499568 (ten floats, then `MemCard:General` ... `EAS SansCondensed`) is read by no code and stays unclaimed: probably header inlines (a guess). The memory-card file runs to `_GLOBAL_.I` 0x8012D9F0, the APT glue (`Game/HUD/glueApt.cpp`) from about 0x80126F0C | 3 |
| 0x801BEE2C-0x801C55F8 | `fn_801BEE2C`, the class registration (section 4.2) | 6 |
| 0x80468974-0x8046DCD4 | Linkonce tail: the prototype constructors, then accessors and destructors that only vtables reach, mixed with other headers' inline functions; render code follows | 7 |

**The class files**, in address order:

| Range | Classes | Row |
|---|---|---|
| 0x801C55F8-0x801CA72C | `cAvengersMansion_ParadoxBoss`, `_IM1_Start`, `_IronManSAC`, `_HideSkirt` | 17 |
| 0x801CA72C-0x801D1BFC | `cBrooklynBridge_heliCrash`, `cBB_ArenaShutoff`, `cBrooklynBridge_ArenaBarrier`, `_AftershockBoss`, `_VM2_Start`, `_SegmentControl`, `_BruteFight`, `_WolverineSAC`, `_RockBomb`, `_FlameWall`, `_HazmatBoss`, `_AltStormBoss` | 20 |
| 0x801D1BFC-0x801D5320 | `cDailyBugle_VenomBoss`, `_SpidermanSac`, `_LetterEffects`, `_DaredevilBoss` | 16 |
| 0x801D5320-0x801DB2BC | `cGrandCentral_VenomBoss`, `_OhmBoss`, `_HazmatBoss`, `_MagnetoBoss`, `_RockBomb` | 18 |
| 0x801DB2BC-0x801DD29C | `cNYCStreets_DaredevilBoss`, `cNYCStreetsMP_SegmentControl`, `cNYCStreets_ThingBoss`, `_TorchBoss` | 15 |
| 0x801DD29C-0x801E4870 | `cPowerPlant_HumanTorchSAC`, `_ElektraSAC`, `_IronMan_3`, `_Venom_3`, `_CoilToggle`, `_CoilArc` | 21 |
| 0x801E4870-0x801EAA38 | `cRoekelFacility_StormBoss`, `_ThingBoss`, `_RockBomb`, `_BlastDoor`, `_RoekelBoss`, `_PlasmaMine`, `_Lasers` | 19 |
| 0x801EAA38-0x801F62E4 | `cPathnodeToggle`, `cActorMoveToPos`, `cActorWalk`, `cActorAIPause`, `cActorControlState`, `cSpawnPeon`, `cSpawnGroup`, `cSpawnController`, `cActorPlayPath`, `cAIRangedAttacker`, `cBossRingOut`, `cActorSetHealth`, `cPlayerBonusMissions`, `cGlobalPeonCounter`, `cAITeleportationToggle`, `cAIEnemyVictoryScene`, `cTemporaryAIPossession`, `cAISetTeleportDistance` | 11 |
| 0x801F62E4-0x801F654C | `cCameraEvent` | 8 |
| 0x801F654C-0x801FBD90 | `cCutscenePlay`, its per-character cutscene-name table `fn_801F7C68` and its 81 parameter accessors (0x48 bytes each) | 13 |
| 0x801FBD90-0x801FCEBC | `cParticleToggle`, `cDummyProjectile`, `cEffectSpawn`, `cCrystalDetonate` | 9 |
| 0x801FCEBC-0x8020C28C | `cObjectExplosion`, `cObjectSetCollision`, `cTriggerRelay`, `cObjectMove`, `cObjectRumbleShake`, `cTimerTrigger`, `cTriggerOnAction`, `cSetAnimFrame`, `cDebrisFall`, `cVehicleBreak`, `cVehicleBarrier`, `cGenBreakProp`, `cDamagePropOnTrigger`, `cPortalControl`, `cPropRespawn`, `cRemoveObjects`, `cCrystalBreak`, `cCrystalBreak_Phase2`, `cCameraMPToggle`, `cLabConsole`, `cWieldableToggle`, `cReverseWallRenderToggle`, `cPropGroupFade`, `cMP_MatchTrigger`, `cCameraSet` | 12 |
| 0x8020C28C-0x80211334 | `cRegionDamage`, `cRegionTrigger`, `cRegionSound`, `cRegionSuck`, `cRegionDefend`, `cRegionLightProbeSwap` | 10 |
| 0x80211334-0x80211494 | `cRingOut` | 8 |
| 0x80211494-0x802126F8 | `cEndMission`, `cHelpText`, `cCountDown`; static init `fn_80212380`, `_GLOBAL_.I` 0x80212670, `_GLOBAL_.D` 0x802126B4 | 8 |
| 0x802126F8-0x80212970 | `cSoundEvent`. End: `fn_80212970` and `fn_80212994` are called only from graphics code (0x80219BB8, 0x801A0168), while everything before is reached from the vtable `lbl_80503760` or the class's own methods; the file has no `.rodata` | 8 |

**How the class-file edges were found.** `.ctors` has no entry between `_GLOBAL_.I` 0x801BEDE8 and 0x80212670, so the edges come from the vtables:
- Each prototype constructor stores its class's vtable, and the vtable names the class's methods. Each group above fills one address range.
- Each group's vtables are contiguous in `.data`, 0x208 bytes apart, in reverse text order (one exception, `cTriggerRelay`). The groups themselves ascend in `.data` in text order. That makes one translation unit per group.
- The functions left between two groups are called only from the earlier group, so a file ends where the next group's first method starts.

**How the script command file edges were found.** One header's static block (ten words: 1.2, 0.8, 2.0, 0.5, 0.8, 0.8, 1.0, 1.25, 0.75, 2000) is written after the pools of every file that includes it (the base file's ends at 0x80487CD4, the profile's at 0x80499430). In 0x80487E88-0x80488758 it sits at 0x80487F5C, 0x80488048 and 0x80488118, with the font names (`UI/eafont0`...) after the first one:
- 0x8007C8B0: the edge is after `fn_8007C594` (last literal 0x80487F18) and at or before `fn_8007CABC` (first literal `"Scripts:Params"` 0x80488028). 0x8007C8B0, script init, is a guess within that range.
- 0x8007DC60: after `fn_8007D404` (0x80488038) and at or before `fn_8007E698` (0x80488070). The guess is where the queue code ends.
- 0x800808D0: confirmed. `fn_800808D0` is a byte-for-byte copy of the static helper `fn_80080300`, and the pool resumes at 0x80488190 after the third block.

Still open: whether `fn_801BEE2C` opens the Avengers Mansion file (its name pool ends at 0x8049F5F5; 0x8049F5F8-0x8049F617 is unreferenced, `0.0, 1.0, 1.0, 1.0, 0.5, 1.5, "invalid"`; `fn_801C55F8`'s pool starts at 0x8049F618, `"PARADOX"`).

---

## 3. Layers

```
Frontend (APT)          mission.cpp, memcard.cpp handlers
  chronicle             the .nsc mission tables, the current mission, mission start
  save profile          story progress and settings (fn_8011CA74)
Level load              <name>.nhg, then the .nsd scene: entities with a SCRIPT property
Class table             "ScriptClasses": name -> 0x28-byte entry -> prototype
  base class            64 virtual slots, the parameter readers (script base file)
  102 classes           17 files: generic ones used everywhere, then one file per level
Script command file     helpers the classes call, the AI script API (ai.md)
```

---

## 4. Data

### 4.1 Base class

- **Layout.** 0x28 bytes: 0x24 bytes of members, then the vptr at +0x24, because GCC 2.95 places the vptr after the data members ([`matching_notes.md`](matching_notes.md), the virtual-call entry). Derived fields start at +0x28. The base constructor `fn_80441FAC` (`Game/fn_80441D78.cpp`) stores the base vtable `lbl_804F4810`. 17 classes add no fields; the largest prototype is `cBrooklynBridge_AftershockBoss`, 0x144 bytes. The source calls the base `cScript` (a guess; no string names it).

  | Offset | Field |
  |---|---|
  | +0x0 | class entry (section 4.2) |
  | +0x4 | instance ID, from the counter `lbl_8066D61C` (starts at 1) |
  | +0x8 | what `fn_80078FDC` was given (guess: the owning entity); `fn_800797D4` returns it |
  | +0xC, +0x10 | parameter count (unsigned) and array of 8-byte `{type, value}` |
  | +0x14 | messages queued for this script (`fn_8007D594` increments, delivery decrements) |
| +0x18, +0x1C | count and list of the entity links this script owns (`ScriptNode`, below) |
| +0x20 | flags; bit 0: gets slot 63 every frame (`fn_8007DFC4`) |
- **Parameters.** Types: 1 int, 2 float, 7-9 string (owned, freed on destroy), 3, 5 and 10-13 a scene index that `fn_80078E28` turns into a handle (`fn_800B13D8`; -1 and -2 become 0). Readers `(this, i)`: `fn_80079068` int, `fn_800791C8` unsigned, `fn_8007935C` float, `fn_800794FC` string (numbers printed into the shared buffer `lbl_8054DD54`). Past the count they return 0, 0.0f or `"Invalid Param"`.
- **Vtable.** 0x208 bytes: an 8-byte header, then 64 entries of 8 bytes, so slot `n` is the entry at `vt + 8n`; slot 64 is null. Slot 2's base is `fn_80078DD4`; slots 1 and 3-63 are 0x8007975C-0x8007A2A0 in slot order, all stubs but the destructor (plus `fn_800797D4` after slot 3, not virtual).
- **Known slots.** The callers are in `Game/fn_8007DC60.cpp`. "Hook" means the call goes to the entity's own script with value 0, then to each linked script with its link value. `h` is an entity handle.

  | Slot | Signature | Called |
  |---|---|---|
  | 1, 2 | destructor, clone | |
  | 3 | `()` | by `fn_80078FDC` once the instance is registered (guess: on start) |
  | 4, 5, 6 | `()` | all live scripts, at level load (`fn_8002D110`), on the first frame after it (`fn_8002BD34`), and from `fn_8002D5F8` (guess: unload; `cRegionSuck` frees in 6 what it allocates in 3) |
  | 8 | `(unsigned char kind, float, float, float, float, int)` | a delivered script message (`fn_8007E0C0`); `kind` is what `fn_8007D404` queued (`cCountDown` queues 10 for its 1-second tick) |
  | 12, 13 | `(h)`, `(h, value)` | hooks; 12 only for the entity's own script |
  | 14-16, 18, 30, 38 | `(h, h other, value)` | hooks; the region classes treat 14 as `other` entering `h`'s region and 15 as it leaving |
  | 20 | `(h, h other, int, int, float, value)` returning int | hook; a 0 stops the chain and the caller gets 0 (`fn_8007E84C`) |
  | 21 | `(h, h other, int, int, float, int, value)` returning float | hook; the float goes on to the next script, and below 0 the result is 0 (`fn_8007E698`). A damage filter: `cPlayerBonusMissions` passes `"damage"` to `fn_80081470` when `h` is the player |
  | 22 | `(h, h other, int, int, float, value)` | hook, then the script of entity `lbl_8066B894`; `cSpawnPeon` treats it as its peon `h` dying to `other`, the float as the damage (guess) |
  | 23 | `(int, int, int kind, float x4, value)` | hook without handles; `cEndMission` acts on kinds 0, 7, 13, 17-19, `cCountDown` on 0, 7, 999; the region classes toggle on 0 and switch off on 7 |
  | 24, 31-33 | `(int, int, int, float x4)`, `()` | all live scripts (callers not traced) |
  | 17 | `(h, h other, value)` returning int | not traced; `cTriggerOnAction` fires on it |
  | 19 | `(h, value)` | hook (`fn_800801F0`) |
  | 25 | `(h, int node, value)` | not traced; `cObjectMove` takes it as its object `h` reaching path node `node` (guess) |
  | 27, 29 | `(h, h other, int, int, value)`, `(h, int, int, int, value)` | hooks (`fn_8007EE5C`, `fn_8007FC00`). `cVehicleBreak` reads 27's first `int` as a hit record whose `float +0x18` is the force, and 29's second as the break stage (0-1) |
  | 37 | `(h, int, value)` returning float | hook for `cAIMessages` kind 0. The base returns -1.0f; the caller keeps the minimum, and any 0 wins. `cActorWalk` takes the `int` as the path node actor `h` reached |
  | 43 | `(h, int, value)` | hook for `cAIMessages` kind 2 (kind 1 goes to slot 38) |
  | 47, 48 | `(h, value)` returning int | hooks that stop at the first 0 |
  | 51 | `(int, int kind, int, float x3)` | not traced; `cRingOut` acts on kinds 3-4, `cCameraEvent` on 0 and 3, `cCutscenePlay` on 3-4, 8 and 10-11 |
  | 53 | `(int, float, int event, int)` | not traced; `cCutscenePlay` looks `event` up in its 20 event-to-hook parameter triples, as for slot 54 |
  | 54 | `(float, unsigned event, int)` | not traced; `cCameraEvent` acts on 0x63, 0x14D and 0x309, `cCutscenePlay` on 0x309 and its event triples |
  | 60 | `(h)` | all live scripts, from `fn_800ED448` with the actor's handle (guess: an actor is defeated) |
  | 63 | `()` | every frame after message delivery, for scripts with +0x20 bit 0 |
- **Entity links.** Entity +0x14C is its own script, +0x150 the list of 0x1C-byte nodes `{script, entity, value, entity prev/next, script prev/next}` that tie other scripts to it. `fn_8007CF00(script, handle, value)` adds or updates a node, `fn_8007D070` removes one.
- **Spawn counters.** `cSpawnPeon` counts peons spawned in `lbl_8066C72C` and killed in `lbl_8066C728`; while `lbl_8066C730` is set it passes both to `fn_80131724`.
- **Script messages.** 128 slots of 0x20 bytes at `lbl_8054DD80`, kept in a time-sorted list by byte index (+0x1D prev, +0x1E next, +0x1F in use; head `lbl_8066B8B0`, 0xFF = none). `fn_8007D404(script, seconds, kind, 4 floats, int)` and `fn_8007D4F4` (milliseconds) queue one, at most 600 s ahead. `fn_8007D7C4(script, kind)` cancels a kind, and `fn_8007C910` delivers the due ones each frame.
- **Which slots the classes override** (count out of 102):

  | Slots | Overridden by |
  |---|---|
  | 1 (the destructor), 2 (clone: `new` of the class size plus its prototype constructor, e.g. `fn_801CA648`) | 102 |
  | 8, 23 | 66, 65 |
  | 5, 4, 21, 22 | 53, 51, 40, 37 |
  | 3, 20, 14, 15, 37 | 29, 25, 21, 17, 13 |
  | 22 more slots | 6 or fewer each |
  | the other 29 slots | none |
- **The outside functions the class files call most:**
  - from the base: `fn_800797D4` (440 calls, +0x8), the parameter readers `fn_800791C8` (398), `fn_80079068` (220), `fn_8007935C` (93);
  - from the command files: `fn_8007D404` (351, queue a message), `fn_80080B34` (175, the handle of `fn_80432924`'s entity; guess: the player), `fn_8007CF00` (124, link to an entity), `fn_8007D7C4` (104, cancel messages), `fn_800809CC` (92) and `fn_8007C034` (83, handle to actor);
  - from the entity code: `fn_80082AFC` (270).

### 4.2 Class table and prototypes

- **Registration.** `fn_801BEE2C` fills `lbl_8054D154[lbl_8066B890]` (`.bss`, 256 slots) with one 0x28-byte entry `{char name[0x20]; void *prototype; int count}` per class and adds it to the table. Its source lists each class's size and prototype constructor.
- **The table.** `lbl_8066D614` is a hash with 0x3F buckets, named `"ScriptClasses"`. `fn_8007891C` creates it (`fn_801B4284`; flag `lbl_8066B898`). `fn_80078994` finds a class (`fn_801B48AC`).
- **Creating an instance.** `fn_800789DC` calls the prototype's slot 2, then `fn_8007A2F0(copy, entry)` and `fn_80078FDC(copy)`. `cAISetTeleportDistance`'s slot 2 builds a `cTemporaryAIPossession` (0x30), so that class's own slots never run.
- **Live instances.** `fn_80078C58` adds an instance to `lbl_8054D554` (512 slots, count `lbl_8066D618`) and increments its entry's `+0x24`; `fn_80078CE0` undoes both. Destroying an instance is `fn_80078B10`.

### 4.3 Missions and scenes

- **Missions.** `Misc/clashsp.nsc` lists 62 missions over 8 level files (`BrooklynBridge` 12, `NYCStreets` 11, `GrandCentral` 9, `AvengersMansion` 8, `DailyBugle` 8, `RoekelFacility` 7, `PowerPlant` 6, `NYCStreets2` 1). Its header documents the keywords, `MISSION nlsName levelFile sceneFile [masterScript]`. `Misc/clashMP.nsc` lists the 7 versus arenas, whose scenes are `<Level>_MP`.
- **`FLAGS` bits** (the file's header; record `+0x464`, testers `fn_804432D8`-`fn_80443488`):

  | Bit | Name | Bit | Name |
  |---|---|---|---|
  | 1 | `SACRIFICE` | 64 | `BOSS` |
  | 2 | `TRIGGERSACRIFICE` | 128 | `TRIGGERFINISH` (the game is finished) |
  | 4 | `FLASHBACK` | 256 | `TRIGGERNEXTMISSION` (next mission instead of mission select) |
  | 8 | `TRIGGERFLASHBACK` | 512 | `USEALTCOSTUME` |
  | 16 | `FORCESACRIFICE` | 1024 | `NODISINTEGRATEFM` (finishing moves don't disintegrate) |
  | 32 | `TRIGGERFORCESACRIFICE` | 2048 | `MARCHMISSION` |
- **Scene files.** A scene is `Levels/<scene>.nsd`, `.npd` (the path-node graph, [`ai.md`](ai.md) section 4.7) and `.ncl`; the level itself is `Levels/<level>.ngl`. `.nsd` is binary, and its entity records name their class as a NUL-terminated string. The first four bytes vary, so there is no fixed magic. No tool reads it yet (row 14).
- **Which scenes use which classes** (the 118 `Levels/*.nsd` in `CLASH.BIG`):
  - `cEndMission` and `cCutscenePlay` are in all 62 story scenes.
  - The 7 arena scenes use 24 classes: `cPathnodeToggle`, `cActorPlayPath`, `cBossRingOut`, `cParticleToggle`, `cObjectRumbleShake`, `cObjectSetCollision`, `cRegionDamage`, `cRegionSuck`, `cTimerTrigger`, `cTriggerOnAction`, `cTriggerRelay`, `cDebrisFall`, `cVehicleBreak`, `cGenBreakProp`, `cDamagePropOnTrigger`, `cPortalControl`, `cPropRespawn`, `cWieldableToggle`, `cReverseWallRenderToggle`, `cMP_MatchTrigger`, `cBrooklynBridge_FlameWall`, `cDailyBugle_LetterEffects`, `cPowerPlant_CoilArc`, `cRoekelFacility_Lasers`.
  - No scene uses `cAIEnemyVictoryScene`, `cCrystalDetonate`, `cObjectMove`, `cRegionSound`, `cSetAnimFrame`, `cCrystalBreak_Phase2`, `cBrooklynBridge_heliCrash` or `cRoekelFacility_PlasmaMine`.
  - Most per-level classes are used by one scene.

### 4.4 Chronicle and save profile

- **Chronicle.** Two `.nsc` tables (layout in [`characters.md`](characters.md) section 4): `lbl_8054ED80` holds `clashsp.nsc`, `lbl_8054EF38` `clashMP.nsc`. [`ai.md`](ai.md) section 3 reads the AI settings from an entry of the story list.
- **Save profile.** `fn_8011CA74` returns the 0x2E0-byte profile (`lbl_8066BE20`), `new`ing it on the first call. Two save buffers `{cursor, base, size}` at +0x0 (settings, 0x30 bytes) and +0xC (progress, 0x280 bytes). `fn_801300B4` fills the progress fields from the game state and the chronicle; the meanings below come from it.

  | Offset | Field |
  |---|---|
  | +0x18 | flag, mirrored in `lbl_8066C640` |
  | +0x1C, +0x20, +0x24 | volumes 0-10, scaled to 0-127 for `fn_80119224` channels 2, 1, 0 |
  | +0x28 | rumble (guess: goes to the pad manager `fn_80122228`) |
  | +0x30 | sound mode -1-2 (`fn_80118F18`) |
  | +0x34 | 0-2, `fn_80131878` |
  | +0x38-+0x58 | snapshot of +0x18-+0x34 and the pad setting, for cancelling an options screen |
  | +0x5C | bitmask over the 20 roster characters (`fn_8044B48C`) |
  | +0x60 | bitmask over 7 entries (`fn_8044D58C`), probably the versus arenas |
  | +0x64 | `lbl_8066BF0C` |
  | +0x78, +0x80 | chronicle flag word (`fn_804435A4`), `fn_8046120C` of the chronicle |
  | +0x84, +0x88 | the chronicle's current record, and a record ID or 0 |
  | +0x8C | `int[65]`, one per chronicle record (`fn_80461144`); a story reset clears bits 0xC000 |
  | +0x190 | `char[4]`, the chronicle's four character slots |
  | +0x194 | save date, YYYYMMDD |
  | +0x198, +0x19C | play time in seconds, and the tick its timer started at (`clashMission_Start` starts it, `clashMission_CompleteMission` adds the elapsed time) |
  | +0x1A0 | `int[80]` saved as bools: 25 from `fn_8044D4F0`, 43 from `fn_8044D454` at +25, 9 of 12 from `fn_8044D3B8` at +68. A story reset keeps them when asked |

---

## 5. Notes

(None yet.)

---

## 6. Target Order

Work the rows in order and skip whatever is done; `configure.py` is the authority on unit status. Within a file, take the next function after the unit's current `.text` end, so that the unit grows as one contiguous range from the file's first function. If a function is stuck, record it in [`nonmatching.md`](nonmatching.md) and move on to the next row rather than leave a gap. Name a unit after its file's first function (`Game/fn_8007891C.cpp`), except the handler files, which keep their source paths. Rows are numbered once; unit headers cite them (`docs/story.md row N`), so don't renumber.

| # | Target | Range | Unit | Next action |
|---|---|---|---|---|
| 1 | Story handlers | 0x8010A448-0x8010BED8 | `Game/handlers/mission.cpp` | Done |
| 2 | Chronicle | 0x80087040-0x8008995C | `Game/fn_80087040.cpp` | Done |
| 3 | Save profile | 0x8011C55C-0x8011EDE0 | `Game/fn_8011C55C.cpp` | Done |
| 4 | Class table and base class | 0x8007891C-0x8007A3A0 | `Game/fn_8007891C.cpp` | Done |
| 5 | Rest of the script command files | 0x8007C034-0x80081E08 | `Game/fn_8007A3A0.cpp`, `Game/fn_8007C8B0.cpp`, `Game/fn_8007DC60.cpp`, `Game/fn_800808D0.cpp` | Done |
| 6 | Class registration | 0x801BEE2C-0x801C55F8 | `Game/fn_801BEE2C.cpp` | Done |
| 7 | Script inline functions | 0x80468974-0x8046DCD4 | `Game/fn_80468974.cpp`, `Game/fn_8046B530.cpp`, `Game/fn_8046B738.cpp`, `Game/fn_8046D6C0.cpp` | Done. 0x8046DCD4 on is render code |
| 8 | Small class files | `cRingOut` 0x80211334, `cCameraEvent` 0x801F62E4, mission classes 0x80211494, `cSoundEvent` 0x802126F8 (section 2) | one unit per file | Done |
| 9 | Effects | 0x801FBD90-0x801FCEBC | `Game/fn_801FBD90.cpp` | Done |
| 10 | Regions | 0x8020C28C-0x80211334 | `Game/fn_8020C28C.cpp` | Done |
| 11 | Actor and AI classes | 0x801EAA38-0x801F62E4 | `Game/fn_801EAA38.cpp` | Done |
| 12 | Objects, props and triggers | 0x801FCEBC-0x8020C28C | `Game/fn_801FCEBC.cpp` | Done |
| 13 | Cutscene play | 0x801F654C-0x801FBD90 | `Game/fn_801F654C.cpp` | Done |
| 14 | Scene loader | 0x800A4DF8-0x800A90B0 | extend `Game/fn_800A4DF8.cpp` (section 2) | 13 functions from `fn_800A6B28` (the section readers `fn_800A7208`, `fn_800A7A0C`, the finisher `fn_800A82B8`), then the static init and `_GLOBAL_.I` 0x800A90B0. Then record the `.nsd` format in a `tools/nsdtool.py` (`dump`, `check`) like `tools/nottool.py` |
| 15 | NYC Streets classes | 0x801DB2BC-0x801DD29C | `Game/fn_801DB2BC.cpp` | 45 functions |
| 16 | Daily Bugle classes | 0x801D1BFC-0x801D5320 | `Game/fn_801D1BFC.cpp` | 61 functions |
| 17 | Avengers Mansion classes | 0x801C55F8-0x801CA72C | `Game/fn_801C55F8.cpp` | 79 functions; check the edge with row 6 |
| 18 | Grand Central classes | 0x801D5320-0x801DB2BC | `Game/fn_801D5320.cpp` | 96 functions |
| 19 | Roekel Facility classes | 0x801E4870-0x801EAA38 | `Game/fn_801E4870.cpp` | 120 functions |
| 20 | Brooklyn Bridge classes | 0x801CA72C-0x801D1BFC | `Game/fn_801CA72C.cpp` | 139 functions |
| 21 | Power Plant classes | 0x801DD29C-0x801E4870 | `Game/fn_801DD29C.cpp` | 122 functions |
| 22 | Rest of the script base file | 0x8007608C-0x8007891C | `Game/fn_8007608C.cpp` | Identify the edges first (section 2). Havok, `ShapeRepository`, the `.nhg` loader `fn_800777C4`; merge with row 4's unit if it is one file |
| 23 | Memory-card handlers | 0x80107244-0x8010A448 | `Game/handlers/memcard.cpp` | 68 functions, 58 of them 0x80 bytes or less, over row 3's profile. Whole file, like row 1 |

Out of scope: `Game/handlers/feonline.cpp` (online only), the memory-card I/O from 0x8011F2B0, the APT glue, the entity code 0x80081E08-0x80087040 that the classes call (unless a row needs a callee's meaning), and third-party code.

---

## 7. Open Questions

- What does `<name>.nhg` hold? No loose `.nhg` is in `CLASH.BIG`.
- Is `fn_801BEE2C` a file of its own, or the start of the Avengers Mansion file?
- Where are the edges inside 0x80074814-0x8007891C?
- What do the slots with no caller traced do (7, 9-11, 17, 25, 26, 28, 34-36, 39-42, 44-46, 50, 51, 55-58, 62)? Look at the overrides: the base stubs' copies undercount their parameters ([`matching_notes.md`](matching_notes.md)).
- Where exactly are the edges at 0x8007C8B0 and 0x8007DC60 (section 2)?
- Are the tables the profile saves at +0x1A0 (`fn_8044D4F0`, `fn_8044D454`, `fn_8044D3B8`) the ones the `REWARDS` setters (`fn_8044374C`, `fn_80443608`, `fn_80443640`) write?
