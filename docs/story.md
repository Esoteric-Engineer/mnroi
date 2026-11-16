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
  - `fn_800A4DF8(scene, level, 0)`, the `.nsd` scene reader (allocator tags `Game:Scene:tScene`, `tPlayerStart`, `tInterestSpot`).
- **Instances.** `fn_800789DC(name, flag)` finds a class (`fn_80078994`) and clones its prototype (slot 2, section 4.1). Its callers:
  - the entity property 0x10 `SCRIPT` (`fn_8007CA10`, [`characters.md`](characters.md) section 3);
  - mission start, above;
  - the versus setup `fn_800916BC`, which creates `cRingOut` and `cCameraEvent`, the two classes no scene places.

---

## 2. File Map

All of it is `-O0` game code. A `.ctors` entry (`_GLOBAL_.I`) ends a file that has static constructors; a `_GLOBAL_.D` can follow it.

| Range | Contents | Row |
|---|---|---|
| 0x80074814-0x8007A3A0 | **Script base file**, one `.ctors` file. It has an inner edge near 0x8007608C: the pair-carrying run ends at 0x80076004, a pair-less run starts at 0x8007608C, and a second `"invalid"` (0x80487BE8) ends the first part's `.rodata` (the debris names `deb_*`, `cel_ConcreteChunk_*`). From 0x8007608C: Havok and `ShapeRepository`, the `.nhg` loader `fn_800777C4`. From 0x8007891C: the class table and the base class (section 4.1). It ends with static init `fn_800796A4`, `_GLOBAL_.I` 0x8007A318 and `_GLOBAL_.D` 0x8007A35C | 4, 22 |
| 0x8007A3A0-0x80081E08 | **Script command file**: the AI script API (`Game/fn_8007A3A0.cpp`, to 0x8007C034), script init `fn_8007C8B0`, the `SCRIPT` property `fn_8007CA10`, `Scripts:Params` `fn_8007CABC`, the helpers the classes call (section 4.1), and the `cAIMessages` delivery targets ([`ai.md`](ai.md) section 3). `Game/fn_8007C830.c` is matched inside. Static init `fn_80081D00`, `_GLOBAL_.I` 0x80081DCC | 5 |
| 0x80087040-0x8008995C | **Chronicle file**, `Game/fn_80087040.cpp`, with the `.nsc` parser and the static init `fn_80089854` that constructs both tables. Start edge: the two functions before it work on entity fields, and its `.rodata` opens with `GAME:CHRONS` right after the entity code's pool (0x80488758, read by `fn_80086C80`) | 2 |
| 0x800A3810-0x800A90B0 | Rest of the template file ([`versus.md`](versus.md) section 5, rows 10-12): the scene reader `fn_800A4DF8` (0x1D30) and its helpers `fn_800A7208`, `fn_800A7A0C`, `fn_800A82B8` | 14 |
| 0x80107244-0x8010A448 | `Game/handlers/memcard.cpp`: 66 handlers, mostly wrappers over the save profile. Static init 0x801099E8, `_GLOBAL_.I` 0x8010A40C | 23 |
| 0x8010A448-0x8010BED8 | `Game/handlers/mission.cpp`: 16 handlers and the static init | 1 |
| 0x8011C55C-0x8011EDE0 | **Save profile**, `Game/fn_8011C55C.cpp`. Start: every caller of the empty `fn_8011C55C` is a profile function, and the save-buffer constructor `fn_8011C578` sets the pair flag for the pair-less run after it; the previous file's `.rodata` ends at 0x804993D4 with its own copy of the memory-card header strings. End: the memory-card manager follows (singleton `lbl_8066BE2C`, init `fn_8011EDE0`, vtable 0x804F59B8), and its `.rodata` (from 0x80499568) repeats the strings that end the profile's. The profile's 0x80499430-0x80499568 (ten floats, then `MemCard:General` ... `EAS SansCondensed`) is read by no code and stays unclaimed: probably header inlines (a guess). The memory-card file runs to `_GLOBAL_.I` 0x8012D9F0, the APT glue (`Game/HUD/glueApt.cpp`) from about 0x80126F0C | 3 |
| 0x801BEE2C-0x801C55F8 | `fn_801BEE2C`, the class registration (section 4.2) | 6 |
| 0x80468974-~0x8046DF18 | Linkonce tail: the prototype constructors (0x80468974-0x8046B530; `cHelpText`'s, `fn_802116B0`, is in the mission-classes file), then accessors and destructors that only vtables reach, mixed with other files' tail functions | 7 |

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
| 0x801F654C-0x801FBD90 | `cCutscenePlay`, its cutscene-name tables (`fn_801F7C68`, 0x2CDC) and about 90 0x58-byte functions they call | 13 |
| 0x801FBD90-0x801FCEBC | `cParticleToggle`, `cDummyProjectile`, `cEffectSpawn`, `cCrystalDetonate` | 9 |
| 0x801FCEBC-0x8020C28C | `cObjectExplosion`, `cObjectSetCollision`, `cTriggerRelay`, `cObjectMove`, `cObjectRumbleShake`, `cTimerTrigger`, `cTriggerOnAction`, `cSetAnimFrame`, `cDebrisFall`, `cVehicleBreak`, `cVehicleBarrier`, `cGenBreakProp`, `cDamagePropOnTrigger`, `cPortalControl`, `cPropRespawn`, `cRemoveObjects`, `cCrystalBreak`, `cCrystalBreak_Phase2`, `cCameraMPToggle`, `cLabConsole`, `cWieldableToggle`, `cReverseWallRenderToggle`, `cPropGroupFade`, `cMP_MatchTrigger`, `cCameraSet` | 12 |
| 0x8020C28C-0x80211334 | `cRegionDamage`, `cRegionTrigger`, `cRegionSound`, `cRegionSuck`, `cRegionDefend`, `cRegionLightProbeSwap`. `Game/fn_8020C508.cpp` and `Game/fn_8020D104.cpp` are matched inside | 10 |
| 0x80211334-0x80211494 | `cRingOut` | 8 |
| 0x80211494-0x802126F8 | `cEndMission`, `cHelpText`, `cCountDown`; static init `fn_80212380`, `_GLOBAL_.I` 0x80212670, `_GLOBAL_.D` 0x802126B4 | 8 |
| 0x802126F8-~0x802129FC | `cSoundEvent` | 8 |

**How the class-file edges were found.** `.ctors` has no entry between `_GLOBAL_.I` 0x801BEDE8 and 0x80212670, so the edges come from the vtables:
- Each prototype constructor stores its class's vtable, and the vtable names the class's methods. Each group above fills one address range.
- Each group's vtables are contiguous in `.data`, 0x208 bytes apart, in reverse text order (one exception, `cTriggerRelay`). The groups themselves ascend in `.data` in text order. That makes one translation unit per group.
- The functions left between two groups are called only from the earlier group, so a file ends where the next group's first method starts.

Still open: whether `fn_801BEE2C` opens the Avengers Mansion file, and where `cSoundEvent`'s file ends (graphics code with `Graphics:PushBuffer` starts at 0x802129FC).

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

- **Layout.** 0x28 bytes: 0x24 bytes of members, then the vptr at +0x24, because GCC 2.95 places the vptr after the data members ([`matching_notes.md`](matching_notes.md), the virtual-call entry). Derived fields start at +0x28. The base constructor `fn_80441FAC` (`Game/fn_80441D78.cpp`) stores the base vtable `lbl_804F4810`. 17 classes add no fields; the largest prototype is `cBrooklynBridge_AftershockBoss`, 0x144 bytes.
- **Vtable.** 0x208 bytes: an 8-byte header, then 64 entries of 8 bytes, so slot `n` is the entry at `vt + 8n`. The base methods are 0x80078DD4-0x8007A318, nearly all stubs.
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
  - from the base: `fn_800797D4` (440 calls), `fn_800791C8` (398; `(this, i)`, guess: parameter `i`), `fn_80079068` (220), `fn_8007935C` (93);
  - from the command file: `fn_8007D404` (351), `fn_80080B34` (175), `fn_8007CF00` (124), `fn_8007D7C4` (104), `fn_800809CC` (92), `fn_8007C034` (83);
  - from the entity code: `fn_80082AFC` (270).

### 4.2 Class table and prototypes

- **Registration.** For each class, `fn_801BEE2C`:
  1. `new`s a 0x28-byte entry `{char name[0x20]; void *prototype; int zero}` into `lbl_8054D154[lbl_8066B890]` (`.bss`, 256 slots);
  2. copies the name (`strncpy` 0x20, byte 0x1F cleared);
  3. sets `+0x20` to `new(size)` run through the class's prototype constructor;
  4. adds the entry to the table with `fn_801B4628(lbl_8066D614, name, entry)`, then clears `+0x24`.
- **The table.** `lbl_8066D614` is a hash with 0x3F buckets, named `"ScriptClasses"`. `fn_8007891C` creates it (`fn_801B4284`; flag `lbl_8066B898`). `fn_80078994` finds a class (`fn_801B48AC`).
- **Creating an instance.** `fn_800789DC` calls the prototype's slot 2, then `fn_8007A2F0(copy, entry)` and `fn_80078FDC(copy)`.

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
| 4 | Class table and base class | 0x8007891C-0x8007A3A0 | `Game/fn_8007891C.cpp` | Table init `fn_8007891C`, find `fn_80078994`, create `fn_800789DC`, then the base methods (73 functions in 0x80078DD4-0x8007A318, 66 small), static init `fn_800796A4`, `_GLOBAL_.I`, `_GLOBAL_.D`. Record what each slot does in section 4.1 |
| 5 | Rest of the script command file | 0x8007C034-0x80081E08 | extend `Game/fn_8007A3A0.cpp` | 121 functions: `fn_8007C8B0`, `fn_8007CA10`, `fn_8007CABC`, the helpers in section 4.1, the `cAIMessages` targets `fn_8007EFE0`/`fn_8007F184`/`fn_8007F2C4`, static init, `_GLOBAL_.I`. Absorb `Game/fn_8007C830.c` |
| 6 | Class registration | 0x801BEE2C-0x801C55F8 | `Game/fn_801BEE2C.cpp` | One function of 102 identical blocks (section 4.2). Declare the prototype constructors `extern` |
| 7 | Script inline functions | 0x80468974-~0x8046DF18 | small units per run | The prototype constructors, then the accessors and destructors. One small unit per run of neighbours, split where the `.rodata` pool changes, like [`ai.md`](ai.md) row 5 |
| 8 | Small class files | `cRingOut` 0x80211334, `cCameraEvent` 0x801F62E4, mission classes 0x80211494, `cSoundEvent` 0x802126F8 (section 2) | one unit per file | In that order. The mission classes (`cEndMission`, `cHelpText`, `cCountDown`) run in every story scene. Confirm where `cSoundEvent`'s file ends |
| 9 | Effects | 0x801FBD90-0x801FCEBC | `Game/fn_801FBD90.cpp` | 4 classes, 32 functions |
| 10 | Regions | 0x8020C28C-0x80211334 | `Game/fn_8020C28C.cpp` | 6 classes, 101 functions. Absorb `Game/fn_8020C508.cpp` and `Game/fn_8020D104.cpp`. `cRegionDamage` uses the damage volumes ([`ai.md`](ai.md) section 4.5) |
| 11 | Actor and AI classes | 0x801EAA38-0x801F62E4 | `Game/fn_801EAA38.cpp` | 18 classes, 250 functions, 185 of them 0x80 bytes or less. AI facts go in [`ai.md`](ai.md) |
| 12 | Objects, props and triggers | 0x801FCEBC-0x8020C28C | `Game/fn_801FCEBC.cpp` | 25 classes, 382 functions, 293 of them 0x80 bytes or less; most of the arena classes |
| 13 | Cutscene play | 0x801F654C-0x801FBD90 | `Game/fn_801F654C.cpp` | `cCutscenePlay`, the name tables and their 0x58-byte functions (97 functions). The player it drives is `cCutPlayer` ([`versus.md`](versus.md) section 5, row 8) |
| 14 | Scene loader | 0x800A3810-0x800A90B0 | extend `Game/fn_800A3588.cpp` | 72 functions, among them `fn_800A4DF8`. Then record the `.nsd` format in a `tools/nsdtool.py` (`dump`, `check`) like `tools/nottool.py` |
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
- What do the base slots other than 1 and 2 do?
- Are the tables the profile saves at +0x1A0 (`fn_8044D4F0`, `fn_8044D454`, `fn_8044D3B8`) the ones the `REWARDS` setters (`fn_8044374C`, `fn_80443608`, `fn_80443640`) write?
- What are the 0x58-byte functions in the cutscene file?
