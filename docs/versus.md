# Versus Mode Map

Where the versus-mode code is, what it touches, and the order to decompile it in. `decomp-versus` picks its targets from section 5.

See also:
- The per-function loop: [`workflow.md`](workflow.md).
- C++ naming, mangling and static initialization: [`prodg.md`](prodg.md#c).
- Characters, their data files and what a new one needs: [`characters.md`](characters.md).

**This is a reference, not a narrative: read the section you need, not the file.** Section 5 alone is enough to pick a target and know its blocker. What a matched function does is in its source file, and `configure.py` is the authority on which units are matched, so neither is repeated here. Names in the "Meaning" columns are guesses until a unit matches.

---

## 1. How the Handlers Were Found

The frontend is EA's APT (Flash) UI. Its screens call native functions by name, and each handler file registers them from its static initializer, constructing one 1-byte `.sbss` object per handler through a constructor that depends on the handler's signature (`fn_8044AF58`, `fn_8044B11C`, `fn_8044BBC8` and others in 0x8044AF58-0x8044EE3C):

```
r3 = &registration_object      // lbl_8066D722
r4 = "Control_SetMatchInfo"    // script-visible name
r5 = fn_80104564               // the handler
r6 = __FILE__                  // "c:/Clash/mainline/Code/Game/handlers/control.cpp"
r7 = __LINE__                  // 211
```

That gives 171 handlers across six files. In `symbols.txt` each handler is named after its script name, and each file's registering function is `__static_initialization_and_destruction_0` (`scope:local`).

**The handler names are provisional.** They are the script-visible strings, not C++ symbols. A C++ unit emits GCC 2.95-mangled names (`Control_SetMatchInfo__Fiiii`), so when you match a handler, rename it in `symbols.txt` to the mangled name, or declare it `extern "C"` if that is what matches.

---

## 2. File Map

A `_GLOBAL_.I` function in `.ctors` ends each file ([`prodg.md`](prodg.md#c)). Its suffix is the file's first global symbol, so it stays `fn_` until that symbol is known.

| File | `.text` range | Handlers | Static init / `_GLOBAL_.I` | Notes |
|---|---|---|---|---|
| ? | ..0x801021A0 | | `fn_80102164` (`_GLOBAL_.I`) | |
| ? (APT script variables) | 0x801021A0-0x801037B0 | | | Engine code, called from `0x8044B694`/`0x8044B758` in another file. See below. |
| `Game/handlers/characterselect.cpp` | 0x801037B0-0x801040F4 | 2 | 0x80103FF4 / 0x801040B8 | `GetCharList` is at line 41, so nothing precedes it. |
| `Game/handlers/control.cpp` | 0x801040F4-0x80106B34 | 64 | 0x8010611C / 0x80106AF8 | Handlers only, lines 48-1057. |
| `Game/handlers/feonline.cpp` | 0x80106B34-0x801070FC | 17 | 0x80106D80 / 0x801070C0 | Online only (`Online_*`). |
| ? | 0x801070FC-0x80107244 | | 0x8010718C / 0x80107208 | Unidentified. |
| `Game/handlers/memcard.cpp` | 0x80107244-0x8010A448 | 66 | 0x801099E8 / 0x8010A40C | Save/load. |
| `Game/handlers/mission.cpp` | 0x8010A448-0x8010BED8 | 16 | 0x8010BB80 / 0x8010BE9C | Story mode. |
| `Game/handlers/venuetable.cpp` | 0x8010BED8-0x8010C528 | 6 | 0x8010C338 / 0x8010C4EC | Handlers only, lines 45-140. |
| ? | 0x8010C528-0x8010CA44 | | / 0x8010CA08 | |

Other source paths in the DOL (assert strings), for naming: `Game/HUD/glueAEMS.cpp` (`fn_80111BB8`), `Game/Sim/simCutPlayer.cpp` (`fn_80438FAC`), `Std/BufferAllocator.cpp` (`fn_801B0C90`), `Std/stdBigHashedVFS.cpp` (`fn_801B1270`, `fn_801B1D74`), `DirectGC/directTexture.cpp` (`fn_802338A8`), `ExternalGC/nsiAllocator.cpp` (`fn_8016840C`).

### The APT script-variable classes

Two engine classes carry every value a handler hands to the UI. The layout and signatures come from the code; **the class and member names are guesses**, so renaming them means redoing every mangled symbol below.

| Class | Size | Members | Symbol |
|---|---|---|---|
| `AptObject` | 8 | ctor / copy ctor / dtor; `+0x0` a reference-counted pointer (count in the pointee's first word) | `__9AptObject` (0x8044B608), `__9AptObjectRC9AptObject` (0x8044B568), `_._9AptObject` (0x8044B510) |
| | | `operator[](const char *name)` -> `AptRef` | `__vc__9AptObjectPCc` (0x80102E60) |
| `AptRef` | 12 | `+0x0` owning object, `+0x4` property name, `+0x8` element index (-1 for the property itself) | |
| | | `operator[](int index)` -> `AptRef` | `__vc__6AptRefi` (0x8044B5B0) |
| | | `operator=(char *const &)`, `operator=(const int &)` | `__as__6AptRefRCPc` (0x8044B694), `__as__6AptRefRCi` (0x8044B758) |
| | | four more `operator=` overloads, value types unknown | 0x8044E9D4, 0x8044EA98, 0x8044EB5C, 0x8044EC20 |

So `list["aIntel"][i - 1] = value;` compiles to the four-call chain the handlers are built from, and each assigned value gets its own stack temp because the operators take a reference.

---

## 3. Match Setup Flow

The versus setup screens (`clashLoadscreenVersus.big` and the `VERSUS MODE SETUP` screen in `CLASH.BIG`) call, roughly in this order:

| Handler | Address | What it does |
|---|---|---|
| `clashCharSelect_GetCharList` | 0x801037B0 | Builds the character list for the select screen. |
| `clashCharSelect_GetPrevCharList` | 0x80103BAC | Restores the previous selection; the only reader of the last-selection module (section 4.2). |
| `Control_SetSelectInfo` | 0x80104710 | `(charId0, live0, cusType0, charId1, live1, cusType1, venue)`. Saves the picks, spawns each player's record (`fn_800944C0(G, fn_80443678(clamp(charId + 1, 1, 18), 1, cusType), player)`), passes `live` on only when `G+0x75C == 2`, and copies the venue's name into `G+0x59C` and selects it (`fn_8008856C`). |
| `Control_BindController` | 0x80105334 | Binds a controller to a player. |
| `clashVenue_GetVenueList` / `ChooseOption` / `StartLevel` | 0x8010BED8 / 0x8010C090 / 0x8010BFFC | Venue select over the venue table ([`characters.md`](characters.md) section 2). `ChooseOption(n)` selects venue `n - 1`, writes `+0x75C = 2` and the venue's name into `G+0x5DC`. |
| `Control_SetMatchInfo` | 0x80104564 | Sets the match type, timer and slot roles. See below. |
| `Control_StartLoad` / `Control_StartGame` | 0x80104A18 / 0x80104B34 | Starts the match. |
| `Control_EndOfMatch` | 0x80104B7C | Post-match path. |

**`Control_SetMatchInfo(int matchType, int timed, int unused, int seconds)`**, on the game-state object `G` (section 4.1), saves `matchType`, `timed` and `seconds` in the last-selection module, and then:

| `matchType` | `G+0x770` | `G+0x774` | `G+0x590` | Also | Menu choice |
|---|---|---|---|---|---|
| 0 | 1 | 0 | 2 | | "1P VS 2P" (`kGlobal_CombatType_Vs`) |
| 1 | 0 | 1 | 2 | Slot 1 is CPU-controlled: `fn_80431788` ORs `slot+0x34` with 4 and sets `slot+0x3C = 99` | "1P VS COM" (`kGlobal_CombatType_Com`) |
| 2 | | 0 | | `G+0x61C = 1` | `kGlobal_CombatType_Story`; no shipped screen passes it |

`timed == 0` sets `G+0x75C = 2`; otherwise `G+0x75C = 1` and `G+0x764 = seconds * 1000`. For players 0 and 1 it then stores the CPU difficulty `fn_801318A0()` in the slot (`fn_80443CCC`).

**What the screens pass.** Only `GAME_StartVsGame` (`CDataHub` in `main.apt`, run by `clashLoadscreenVersus` once its transition ends) calls it, as `Control_SetMatchInfo(eCombatType, eMatchType, eDiffLevel, nTimeLimit)`, followed by `Control_SetSelectInfo` and `Control_StartGame`. The `CDataHub` fields are set by two screens:

| Argument | `CDataHub` field | Set by | Values |
|---|---|---|---|
| `matchType` | `m_MT_eCombatType` | `clashMatchType`: the first menu row (`"~kT_1PVSCOM"` or `"~kT_1PVS2P"`) | 0 = 1P VS 2P, 1 = 1P VS COM, 2 = story (never set). The menu's own index is 0 for COM, so `setMenuValues` inverts it. |
| `timed` | `m_MT_eMatchType` | `clashMatchType`: the lives/timed menu (`m_lives`, `m_timed`) | 0 = lives match (`"~kT_LIVES_MATCH"`), 1 = timed. The constructor's default is 0. |
| `unused` | `m_MT_eDiffLevel` | No screen. `clashCharSelect` restores it from `clashCharSelect_GetPrevCharList`, i.e. from `lbl_8066F180`, which only the command line (`-difficulty`) and `fn_8011D4E4`/`fn_8011E1DC` write | 0 = easy by default. The menu has a `"~kT_DIFFICULTY"` header (`kDiff = 2`) with no clip behind it (guess: difficulty selection was cut). The C++ ignores the argument and takes the CPU difficulty from `lbl_8066F180` instead, which is why it is "unused". |
| `seconds` | `m_MT_nTimeLimit` | `clashMatchType`'s timer (`m_timer`): 1 to 99 minutes in steps of 60, starting at 180 | Only used when `timed` is 1. The lives count is not an argument: `clashCharSelect`'s slider feeds `CS_SetLives`, and `Control_SetSelectInfo`'s `live0`/`live1`. |

`clashMatchType` is reached from `clashMainMenu` ("~kT_VERSUS") and from `clashCharSelect` (`PushScreen`). Demo builds (`gIsMagazineDemo`, `gIsE3Demo`) override the match type and time (240 s timed, or 3 lives).

---

## 4. Data

### 4.1 Game-state object `G` (`lbl_80552110`, `.bss`)

A C++ singleton (`GameState`, a guessed name; constructor `Game/fn_80091174.cpp`) that 211 functions reference, so it is the whole game state, not just the match. dtk split it into several labels (`lbl_80552110`, `lbl_80552120` size 0x58C, `lbl_805526AC`...).

| Offset | Type | Meaning (guess) | Written by | Read by |
|---|---|---|---|---|
| +0x10 | `Slot[8]`, stride 0xB0 | Player slots (dtk's `lbl_80552120`). `fn_804317BC(G, i)` returns `&slot[i]`, and `fn_8042FF2C(slot)` returns the slot's actor (`+0x28`). Fields: `+0x0` int player index, `+0x4` `char[0x20]` entity name, `+0x34` int flags (bit 0 in use; bit 1 unknown, tested by `fn_8044272C`; bit 2 CPU-controlled), `+0x38` int, `+0x3C` int (a small number per slot, section 7), `+0x3E` `unsigned short` the controller port, `+0x40` float, `+0x64` int CPU difficulty 0-2 (picks the tuning slot, [`characters.md`](characters.md) section 4), `+0x90` a `Vector`. The slot constructor (`Game/fn_80095BEC.cpp`, `PlayerSlot::PlayerSlot`) constructs the `Vector` and sets `+0x64 = -1`, `+0x80 = 0`. | | |
| +0x590 | int | Number of active player slots | `fn_80431844` | `fn_80434900` (getter), `fn_80023010`, `fn_80114420`, `fn_80443D44`, `fn_80096B98`, `fn_80096D6C` |
| +0x598 | int | Index into `slots`; `fn_80443DBC` uses it to set `+0x744` | `fn_80443D1C` | `fn_80443DBC` |
| +0x59C, +0x5BC, +0x5DC, +0x5FC | `char[0x20]` x4 | Level/venue name buffers. `+0x59C` (dtk's `lbl_805526AC`) is the level name that `GameFlow` command 0x14 loads (section 6) | `Control_SetSelectInfo`, `clashMission_StartLevel`, `clashVenue_StartLevel`, `clashVenue_ChooseOption`, `fn_80028BAC`, `fn_8008856C` | `fn_800B76C0`, `fn_80114420` |
| +0x61C | int | Set to 1 for match type 2 and by both `StartLevel` handlers | `Control_SetMatchInfo`, `clashMission_StartLevel`, `clashVenue_StartLevel` | `fn_8002BD34`, `fn_8002F4A8` |
| +0x620, +0x624, +0x628 | int x3 | Load requests `fn_8002F4A8` tests after `+0x61C`: `+0x620` adds the second name (`+0x5BC`); `+0x624`/`+0x628` load through the script records `lbl_8054ED80`/`lbl_8054EF38` (named by `+0x5DC`) | `fn_80028BAC` | `fn_8002F4A8`, `fn_8002DB78` (`+0x620`) |
| +0x744 | `Slot *` | The current slot, `&slots[+0x598]` | `fn_80443DBC` | `fn_80095100`, `fn_800950E8` |
| +0x750 | `Slot *` | Slot iteration cursor: `fn_804427FC` resets it, `fn_804427D0` reads it, `fn_80094A9C` advances it to the next slot `fn_8043B2C8` accepts and returns nonzero while slots remain | `fn_804427FC`, `fn_80094A9C` | `fn_804427D0` |
| +0x75C | int | Timer mode: 1 timed, 2 untimed, 3 before the first match (the constructor's value) | `Control_SetMatchInfo`, `clashVenue_ChooseOption`, `fn_80028BAC` | `Control_SetSelectInfo`, `fn_8011A94C`, `fn_8011AB34`, `fn_8013156C` (is-timed test) |
| +0x760 | int | Game phase, written by 14 functions. Values seen: `side + 2` (`fn_80093C14`, handover to `side`), 4 after the round reset `fn_80092550` (which runs only from 6 or 10), 0xF at level end (`fn_8002D90C`). `fn_80091C84` switches on it (unsigned) each frame until a phase finishes: 16 → 7, 14 → 4, 3 → 9 with `+0x788 = 2000`, then 9 → 4, 8 → 7 and 13 (`fn_8009717C` on slot `+0x758`) once `+0x788` runs out; 1 and 2 hand over to side 0 and 1 (`fn_80093C14`) | `fn_8002D90C`, `fn_80092550`, `fn_80093C14`, `fn_80091C84`... | `fn_80018290`, `fn_80092550`, `fn_80091C84`... |
| +0x764 | int | Time limit in ms (300000 from the constructor) | `Control_SetMatchInfo`, `fn_80028BAC` | `fn_80131434` |
| +0x768 | int | Added to the time limit in the match clock's total (guess: extra time or a start time). `fn_80091C84` adds `fn_8042F024(lbl_80593BE8)` to it on each frame of phases 8, 9 and 13; also read-modify-written at 0x80094000 and 0x800C0088 | `fn_80091C84` | `fn_80131434` |
| +0x76C | int | Set once phase 0 has run `fn_80092B7C` and `fn_800939C4(G, 0/1)` | `fn_80091C84` | `fn_80091C84` |
| +0x770, +0x774 | int | Role indices (section 3). "Either one nonzero" means a match is running for `fn_80114420`; the command line sets `+0x770` for `-mp` and `+0x774` for `-vs`. What the readers do with them is section 4.3 | `fn_804317F4`, `fn_8043181C` | `fn_80432844` (`+0x770`), `fn_80432870` (`+0x774`), `fn_80114420` |
| +0x77C | int | Set once phase 7, 11 or 12 has started its cue (each runs once) | `fn_80091C84` | `fn_80091C84` |
| +0x780 | int | Nonzero makes `fn_8002D9C4` load the frontend (`fn_8002DB78`) instead of walking the actor list | | `fn_8002D9C4` |
| +0x788 | int | Phase countdown in ms: 2000 from phase 3; phases 8, 9 and 13 subtract `fn_8042F024(lbl_80593BE8)` and finish at 0 | `fn_80091C84` | `fn_80091C84` |
| +0x79C, +0x7A0 | int[2] | Per player side: index added to tuning field 170 (versus cutscene name) by `fn_80093C14`. Written by unmatched code | | `fn_80093C14` |
| +0x7B0, +0x7B4 | int[2] | Per player side: the `fn_800578E4` argument after the actor in `fn_80093C14` | | `fn_80093C14` |
| +0x7BC | int | A flag; its only reader bumps a counter at `G+0x78` when it is 0 | `fn_80091174` | `fn_80443CA0`, `fn_80096884` |

The constructor also sets `+0x748 = +0x754 = +0x640 = -1` (`+0x640` is this player's slot index for the motion-set variant, [`characters.md`](characters.md) section 3). The command-line parser `fn_80028BAC` (`-mp`, `-vs`, `-timed [seconds]`, `-level`, `-scene`, `-mission`, `-mpmission`, `-chron`, `-addthing`) writes the fields above as the menus do.

### 4.2 Last-selection module (0x801317D8-0x80131E90, `.sbss` `lbl_8066F178`-`lbl_8066F1A4`)

Getters and setters around small-data globals. The setup handlers write them and only `clashCharSelect_GetPrevCharList` reads them back, so they remember the previous menu selection rather than drive the match.

| Global | Setter / getter | Written by |
|---|---|---|
| `lbl_8066F178` match type | `fn_801317D8` / `fn_80131800` | `Control_SetMatchInfo` |
| `lbl_8066F17C` timed | `fn_80131828` / `fn_80131850` | `Control_SetMatchInfo` |
| `lbl_8066F180` difficulty (`nDiffLevel`) | `fn_80131878` / `fn_801318A0` | `fn_80028BAC`, `fn_8011D4E4`, `fn_8011E1DC` |
| `lbl_8066F184` seconds | `fn_801318C8` / `fn_801318F0` | `Control_SetMatchInfo` |
| `lbl_8066F188`/`lbl_8066F194`, `lbl_8066F18C`/`lbl_8066F198`, `lbl_8066F190`/`lbl_8066F19C` | Per-player: `fn_80131918`/`fn_80131974`, `fn_801319D4`/`fn_80131A34`, `fn_80131A94`/`fn_80131AF4` | `Control_SetSelectInfo` |
| `lbl_8066F1A0`/`lbl_8066F1A4` | Per-player: `fn_80131B54` / `fn_80131BB4` | `Control_BindController` |
| all of the above except `lbl_8066F180` | `fn_80131E1C` (reset to -1) | `fn_80103FC4` (in `characterselect.cpp`) |

The range also holds three per-player counter bumpers (`fn_80131C14`, `fn_80131C9C`, `fn_80131D24`, with the shared running total `.sdata` `lbl_8066BF0C`) and two read-and-clear accessors (`fn_80131DAC`, `fn_80131DE4`: `lbl_8066BF10`, `lbl_8066BF14`). Their meaning is unknown.

### 4.3 What the role indices change

Matched readers of `G+0x770` (`fn_80432844`) and `G+0x774` (`fn_80432870`). "Versus" means either one is nonzero. Only `fn_80095304` and `fn_80091C84` tell the two apart.

| Reader | Versus | Neither set (story, menus) |
|---|---|---|
| `fn_8013086C`, `fn_801308C0` | Predicates `G+0x774 > 0` and `G+0x770 > 0`; the HUD setup `fn_8000394C` stores "either one" in `Hud+0x418C` | |
| `fn_8000394C`, `fn_80003808`, `fn_800061CC` (HUD setup, section 4.4) | 2 player HUDs; the clock at `text_time`; player 1's name is `fn_801311C0(1)`; overlay `overlay2` too; then `fn_80007624` | 3 player HUDs; the clock at `text_timeStory`; names `fn_80130EF8()` and `"Unknown Peon Name"`; then `fn_80007678` |
| `fn_800916BC` (G method, match start) | Phase `G+0x760 = 0`, then `fn_80095304`; calls `fn_80133658` | Phase 0xE; calls `fn_8013367C` |
| `fn_80095304` (G method) | `+0x774` only: both slots get the last-selected CPU difficulty (section 4.2) | |
| `fn_800BFFC8`, `fn_800BA4D8`, `fn_800BF488` | Round end: `fn_80092550` resets the slots; `fn_800BFFC8` otherwise adds the match clock to `G+0x768` unless the phase is 0xD | |
| `fn_8009717C` | The other player's actor gets flag 0x2 | |
| `fn_8020D104` | Calls `fn_800816A0` on the actor handle only if `fn_800817DC` says no | Always calls it |
| `fn_800DEDB4` | Adds 0x2000 to the flags of the attack it starts | |
| `fn_8003E10C`, `fn_8011406C` | Resource list `lbl_8054EF38` | Resource list `lbl_8054ED80` |
| `fn_8011A94C` | The versus music cues | |
| `fn_8020C508` (the `tripwireDamFX` object's event method) | Ignores the event if the other player's actor (`fn_80443D44(G, 1 - fn_8043B31C(...))`) passes `fn_80085EEC` or `fn_80085F1C` | |
| `fn_8011B768` (for `fn_8011C008`'s `fn_801196F0` call) | Returns `fn_80435904() % 8 + 1` | Maps the level's track (`fn_80442E7C`, 0-61) to 1-8 through a `switch` |
| `fn_8003F6C8` (steps a timed record) | When an expiring record brings `lbl_8066B78C` to 0 and `fn_8009404C(G)` is false, `fn_80092550(G, 0)` resets the slots | |
| `fn_80091C84` (G method, the phase stepper) | Phase 3 also calls `fn_8007FF3C`; phase 4 calls `fn_8009404C(G)`; phase 6 resets the slots (`fn_80092550`) and moves to phase 4; `+0x774` only: phase 9 calls `fn_80132CDC`, `fn_8013367C`, `fn_80132B88` | Phase 6 ends the level, `fn_8002D90C(level, "NOW")` |
| `fn_8011389C` (per frame) | Passes `fn_804304FC` the mean position of every active slot's actor and setting 0xCC / 32767 | Passes it `fn_80432924`'s actor position and setting 0xCB / 32767 (settings read with `fn_8010C7EC(lbl_8066D808, 1, id)`) |
| `fn_8011AC88`, `fn_8011AD44`, `fn_8011AE10`, `fn_8011AE7C`, `fn_8011AEF4`, `fn_80112E88` | | The story/menu music cues (`lbl_8066BDF0` is the cue word, `lbl_8066BDF8` the current track, `lbl_8066BDFC`/`lbl_8066BE00` flags) and `fn_8010E1F4` |
| `fn_80119D64`, `fn_80119E94` | | Pick the music record `lbl_80497D24[track]` (0x5C bytes, 11 cue pairs) for the level's track and start cue 0 |
| `clashMission_StartLevel` | | On `BrooklynBridge`, spawns `plr_thing` for player 0 |

### 4.4 HUD object (`lbl_8066B578`, `.sdata` pointer)

0x4190 bytes, built by `fn_80018198` (`new`, the constructor `fn_800034A0`, then `fn_80003808`); destructor `fn_80003688`. Its file starts the game's `.text` at 0x800034A0. The layout is the `Hud` class in `Game/fn_80003808.cpp`; what the fields are for:

| Offset | Type | Meaning |
|---|---|---|
| +0x0, +0x8 | pointer to member | Two `Hud` methods, chosen by mode in `fn_80003808` |
| +0x10 | text `[3]` | Counter `00/00` at `text_counter` |
| +0x190, +0x4010 | 0x170 bytes each | Counter bar and death bar, from `tex_counterBar`/`pos_counterBar` and `tex_deathBar`/`pos_deathBar` |
| +0x340 | 0x10 bytes | The loaded image bank `HUD/hud<LANG>.N.gsh`: load `fn_80017E3C`, unload `fn_80017F34`, find `fn_80017FB0`, position `fn_8000C274` |
| +0x350 | int | Player HUD count, 2 in versus and 3 otherwise; `+0x354` (0x8BB0 bytes each), `+0x358` and the two image arrays have this many entries |
| +0x3C98 | image `[count * 32]` | Per player, the 32 images named in `lbl_804BF980` (`tex_<name>`; `tex_healthBar_<p/2+1>`; the portraits, [`characters.md`](characters.md) section 6, step 5) |
| +0x3C9C | image `[count * 2]` | Per player, `tex_mainBarContainer_<p/2+1>` and `tex_mainBarBackground_<p/2+1>` |
| +0x3CA0 | image `[13]` | The overlays named in `lbl_804BFA00`, from `hud<LANG>.2` |
| +0x3E2C, +0x3E34 | `Vec2` | Clock and counter positions |
| +0x3E44, +0x3EC4, +0x3F44 | text | The clock at `text_time`: two numbers (`44`) and a colon, laid out left to right as first, colon, second |
| +0x4180, +0x4184 | float | Screen height and width (`lbl_8066F590` `+0x7A`, `+0x78`) |
| +0x418C | int | Versus: either role index set (section 4.3) |

`lbl_8050F820` (`.bss`) is the overlay table: 13 records of 0x78 bytes, `+0x4` a name, `+0x8` a buffer. `fn_800061CC` copies each name into its buffer and puts both players' template names, minus `plr_` or `plr_alt` and lowercased, in records 3 and 4. What reads them there is unmatched (`fn_80006450`).

---

## 5. Target Order

Work the rows in order and skip whatever is done. `configure.py` is the authority on unit status; this table gives the order and each row's next action, not a changelog. Read the notes for the row you land on, not the others. Name a unit after its real source file when it is known (section 2); otherwise use decomp-next's `Game/fn_XXXXXXXX.cpp` naming.

**Rows 1 to 26 are done** (the character select, roster data, type IDs, selection to spawn, `control.cpp`, `venuetable.cpp`, the last-selection module, `G`'s methods, the match clock and timer readers, the command line and main loop, templates, tuning, the model and animation bundles, the setup screens' arguments to `Control_SetMatchInfo`, the role-index readers, section 4.3, and the HUD setup, section 4.4). Unit headers cite these numbers, so they are not reused; the notes still worth having are under "Notes for rows 1 to 23" below. The rows from 27 on cover what a new character still depends on.

| # | Target | Next action / blocker |
|---|---|---|
| 27 | Small pinned functions | Pinned, one unit each, in the order of the list under "Rows 27 and 28". |
| 28 | Movesets: the combat state machines | Pinned, in the order of the list under "Rows 27 and 28". |
| 29 | Character data formats: the code behind what [`characters.md`](characters.md) leaves not understood | Pinned. Each item ends with its format in a tool's docstring and a `check` command, as in ROADMAP section 2. Targets, in order: `fn_803A38DC`, `fn_8039E22C`, `fn_803944A4` (`Misc/game.nfx`: loader, type word to effect class, key lookup in the 140 names of `lbl_804DC2F0`; then `tools/nfxtool.py`); `fn_8010FE34`, `fn_8011063C`, `fn_8011574C` with the small users `fn_80110AA0`, `fn_80110B40`, `fn_80111134`, `fn_801111DC`, `fn_801114A0`, `fn_80114E2C`, `fn_80116C84` (sound banks and voice events, the `(bank << 9) \| event` registry `lbl_80568DB0`); `fn_80057AE8`, `fn_80057FF8` (`.cut` cutscenes, per-record calls of the streamer `fn_80439778`); `fn_8023401C` (the only code naming the `glossenvcharlight` shader); `fn_80223E38` (draws a model's meshes; read the matched loader `fn_80221C08` first for the mesh record's three unknown bytes). |
| 18 | Tail sweep from `fn_8045FAB0` | **Fallback, not a goal:** take it only when every open row above is stuck. Next unclaimed function: `fn_8045FBF0` (0x38); about 850 unclaimed functions (0x13300 bytes) follow up to 0x80472F34, where Havok starts. |

Out of scope for versus: `memcard.cpp` (except whether saves depend on the roster size, [`characters.md`](characters.md) section 2), `feonline.cpp`, `mission.cpp`, and third-party code (Havok `hk*`, RealCore, RealGraph).

### Rows 27 and 28

**These rows pin functions.** Match each in a unit of its own (`Game/fn_XXXXXXXX.c` or `.cpp`, by its own trailing-branch count), without first filling the file up to it. When one closes the gap to a matched neighbour of the same language and pair state, extend that neighbour instead.

**Row 27:** `fn_8009FF54` (0x534) is the one left: the last type-ID consumer not yet checked ([`characters.md`](characters.md) section 5). It takes ten arguments plus a 16-byte structure by value on the stack, and calls `fn_800A0488`, `fn_800A0B48`, `fn_8009E998` and `fn_800A09C0`; match those signatures first.

**Row 28**, then the tuning readers that `tools/nvbreaders.py PLAYER` ranks highest (`fn_800DA884`, 0x140C, adds 13 fields; `fn_800DF03C`, 0x141C, 7). A modded weapon throw went through most of these:

| Function | Size | What it is (from reading its disassembly and callers) |
|---|---|---|
| `fn_800C0F48` | 0x2710 | Input handler; tests actions with `fn_800CC0BC(ctrl, n)`: 1 ranged (`fn_800F0328`), 2 attack (`fn_800DDCB4`), 5 jump (`fn_800C45B0`), 6 grab (`fn_800F8B90`) |
| `fn_800DDCB4` | 0x1100 | Attack: picks the target, splits near from far, chooses `SuperAttackFar` |
| `fn_800E1788` | 0x1000 | Animation event handler |
| `fn_80058C94` | 0x18A0 | Event dispatcher |
| `fn_8002FD50` | 0xB44 | Applies a hit's damage |
| `fn_800F0C70` | 0x9D4 | Spawns the projectile named by tuning field 90 |
| `fn_800E89B0` | 0x6BC | Target search |

After matching a tuning reader, add each field it reads to `FIELD_NAMES` in `tools/nvbtool.py`: what the matched code does with the value, in a few words. A field whose callers are unmatched gets only its getter's name; a guess goes in only with its basis stated. That table is the record, so don't list fields in the docs. Check a meaning against the data first (`python3 tools/nvbtool.py field ID`). An id the tool prints as `206+` is the base of an indexed read `base + i`; the tool counts a base as one field, so name the whole run when its reader matches.

### Notes for rows 1 to 23

Only what costs disassembly to re-derive: file boundaries, unclaimable data, and what is still unknown.

- **Row 2: `Game/unlockables.c`**, `.data` 0x804CA51C-0x804CC55C. Only tail-of-`.text` functions read it (linkonce inline functions, [`prodg.md`](prodg.md#inline-functions-and-the-tail-of-text)), so no unit that uses it can claim it ([`matching_notes.md`](matching_notes.md)). `.data` is in link order, and the block sits between `lbl_804CA504` (read from 0x8004F0BC-0x8004FBA8) and `lbl_804CC55C` (read from 0x800A1444), so its file is linked between those two; no function in that span reads it, so the file is not identified, and the unit sits after `Game/fn_800887AC.cpp` in `splits.txt`.
- **Row 2: the registrar and handle-class run** (0x8044AE3C up to row 18's sweep point). The registrars come in groups of four per handler return type (call thunk, its forwarder, the thunk's table entry, the constructor, which appends `{name, thunk, handler}` to `lbl_805663A4`); the groups repeat per return type to 0x80457F54 and are pair-less. A group's converter may sit later in the run, so declare it with `__asm__` rather than waiting for it. Groups that look alike have their own callee sets: check each member's callees and field offsets, not its shape. The record table `lbl_80567760` is 48 records of 0x60 bytes (its `symbols.txt` size of 0x10 is wrong). `HandleA`-`HandleF`, `ImplA`-`ImplF`, `Obj*` and `Pair2` are placeholder class names.
- **Row 4: 0x80442010-0x8044AE3C.** Not one source file: the language varies per function, so let each function's trailing-branch count pick it ([`matching_notes.md`](matching_notes.md)). Pair-carrying file starts at 0x80449B80, 0x8044A5B4 and 0x8044A980; 0x80443908-0x804439E8 carries the pair between two pair-less runs. The float pools at 0x8048B678-0x8048B688, 0x8048CD14-0x8048CD74 and 0x8048E498-0x8048E4C8 cannot be claimed (a link-order cycle), so units read them as `extern`s or through `extern_pool`.
- **Row 4: `GameFlow` is four source files.** The branch pair's flag resets at each file edge, which fixes the boundaries to the instruction ([`nonmatching.md`](nonmatching.md)): 0x800B43F0-0x800B5BC4 pair-less (a confirmed file start: `fn_800B43AC` is the previous file's `_GLOBAL_.I`), 0x800B5BC4-0x800B7094 pair-carrying, 0x800B7094-0x800B7204 pair-less (globals only), 0x800B7204-0x800B869C pair-less. The nine floats at 0x8048BD44-0x8048BD68 belong to no function of the first file (one was dead-stripped), and `Game/fn_800B46B0.c` defines `fn_800B5124`'s format string at 0x8048BD9C to keep its claim 8-aligned.
- **Row 8: 0x80431788-0x80442010.** Pair resets, so file starts, at 0x8043A16C, 0x8043A71C, 0x8043C1EC, 0x8043D65C, 0x8043F490, 0x80440148, 0x804408F8, 0x80441AD8 and 0x80441C54. The float pools in the range are not contiguous, so each pool is a unit of its own read through `extern_pool`. The class names in these units (`Link`, `Cue`, `ListEntry`, `Placement`, `Body`, `Shape`, `Streamer`, `Movie`, `Holder`...) are guesses. `Streamer` (`Game/fn_80438044.cpp` to `Game/fn_80439E94.c`) streams `Cutscenes/<name>.cut`: a 0x198-byte header whose `+0x0` is the magic 0x2715, then `a` words at `+0x18C` (each <= 0x4B001), `b` 0x90-byte records at `+0x190` and a second `a`-word table at `+0x194`; the format is otherwise not understood.
- **Row 9: the match clock, timer readers, command line and main loop** are whole files. Still unknown: what the HUD methods (section 4.4) at 0x800075EC-0x800077C4 that the clock's wrappers call do; what reads the `-addthing` list (`lbl_8052F060+0x328` count, `+0x32C` names); the meaning of `FrameCtx+0x68`'s phase bits.
- **Rows 10 to 12: templates.** File edges (from `.ctors`): `fn_800AC37C` is in 0x8009E6AC to `_GLOBAL_.I` 0x800A90B0 (130 functions, the attachment spawner `fn_800A22CC` among them); the actor class is 0x800974B4 to `fn_8009B2E0`, done; `fn_80084498`'s file is 0x80081E08 to 0x800898E4; the template registry file (source probably `gameTemplate`) is 0x800F9F88 to 0x80101A00 (93 functions). The tuning loaders at 0x801B301C-0x801B3C4C have no static initializer between 0x801A0000 and 0x801C0000, so their edges are unknown. Actor fields `Game/fn_80097750.cpp` leaves as `fNNN`: `+0x1B0` a handle `fn_800ACFA8` resolves to an actor, `+0x1BC` the model (whose `+0xB0` is the animation object), `+0x218`/`+0x21C` timestamps, `+0x220` the last target's handle, `+0x228` a lock timer (guess).

---

## 6. The `GameFlow` Command Dispatcher

`RunCommand__8GameFlow` (0x800B5BC4) is the frontend's per-frame command dispatcher. The single instance is `lbl_80552920` (`.bss`, 0x2A0 bytes), which the main loop `fn_8002B9F0` drives. It runs while `fn_8012D470()` is set and `+0x158` is clear, and switches on the pending command at `+0x20`. `GameFlow`, its method names (`SetCommand`, `OpenScreen`, `LoadLevel`...) and `Stub<addr>` (a method the release stripped) are **this project's names**, not the DOL's; renaming one means redoing its mangled symbol.

`SetCommand(int)` (0x800B6E44, 113 call sites, `control.cpp` among them) is how the whole game queues a command; it keeps the last five at `+0x1A0`, except command 6. `SetCommandBlocking` also sets `+0x158` and is what `control.cpp` uses for commands 1, 2 and 8. Two methods carry 20 of the switch's arms: `fn_800B6B34(this, n, 1)` (`OpenScreen`) with `n` in 1-0x21, followed by `fn_800B6E44(this, 0)`.

**The versus load path.** `clashVenue_StartLevel` writes `G+0x59C`, and `SetCommand(0x14)` runs `fn_800B76C0`, which loads that level with `fn_8002D7A8` or `fn_8002C690` on `lbl_8052F060`, the level object (`FrameCtx`, a guessed name). With `G+0x59C` empty it runs the `.nsc` record at `+0x24` instead and takes the level name from it.

**The command-to-method map.** The methods keep their `fn_` names. `N` is the load mode a method passes to `fn_80446094` (`+0x17C`).

| Command | Method | What it does |
|---|---|---|
| 0x01, 0x02, 0x04, 0x05 | `fn_800B7D6C` (3), `fn_800B7DB0` (6), `fn_800B7D28` (8), `fn_800B7DF4` (0xA) | `fn_80446094(this, N)`, then the shared `fn_800B7C98` (`BeginLoad`, then `fn_80128C3C("main")`) |
| 0x08 | `fn_800B7E38` | the same with N = 5 or 4 |
| 0x06, 0x4F | `fn_800B84F4`, `fn_800B8544` | `fn_8002ABCC(lbl_8066B690)`, then command 0xB / 0x44 |
| 0x10 | `fn_800B72B4` | screen 0x1C if a pad on ports 0-4 answers `fn_8002B2C4`, else replays the history |
| 0x14 | `fn_800B76C0` | **the level load** (above) |
| 0x15 | `fn_800B7C50` | `fn_8002FA70(level)` |
| 0x18 | `fn_800B7654` | command 0x1A when `+0x1F4 != 0xFF`, else 0x14 |
| 0x1C-0x22 | `fn_800B7EA4`, `fn_800B7F04`, `fn_800B80E0`, `fn_800B7F64`, `fn_800B7FC4`, `fn_800B8024`, `fn_800B8084` | option toggles on `lbl_8066B690` |
| 0x27, 0x28 | `fn_800B81D0`, `fn_800B8210` | `fn_800871A8()`, `fn_8002A418()`; then screen 0x12, or command 0x26 with `+0x1BC = 0x10` |
| 0x29, 0x2B | `fn_800B8290` | releases `lbl_8066B694` then `lbl_8066B690` (`fn_8043206C`), one per call |
| 0x2A, 0x2C | `fn_800B8408`, `fn_800B831C` | screen 0x13 / 0x14 and `+0x1BC = 0x2A` / `0x2C` |
| 0x2D | `fn_800B7BD4` | `fn_8002A418()`, then screen 0x16 or command 0x26 with `+0x1BC = 0x2D` |
| 0x2E | `fn_800B7514` | `fn_8002A7D0` on item `+0x1C4` of `lbl_8066B698`, then the command at history slot 3 |
| 0x2F-0x33 | `fn_800B7268` | `+0x1F4 = command - 0x2F`, then command 0x18 |
| 0x34-0x38 | `fn_800B7204` | `fn_8002B27C(lbl_8066B690, command - 0x34)`, then command 0x40 |
| 0x39-0x3D | (in the switch) | `OpenScreen(4, 1)` with `+0x1BC = command - 5` |
| 0x3E, 0x3F, 0x42 | `fn_800B7894` (0, 1, 2) | **the frontend load**, then `fn_80128C3C("mainBE")` |
| 0x43 | `fn_800B7918` | `EndLoad` and command 0 |
| 0x45, 0x46 | `fn_800B7A0C`, `fn_800B797C` | `EndLoad` paths |
| 0x4A | `fn_800B7AA4` | clears the two role indices on `G`, then command 1 |
| 0x4B, 0x4D | `fn_800B7B34`, `fn_800B7B98` | commands 0x40 then 0; command 0 |
| 0x50, 0x51 | (in the switch) | debug: spawn `"plr_wolverine"` / `"plr_ironman"` (`fn_8009543C(G, +0x280, name)`, then `fn_80096268`) |
| 0x52-0x55 | (in the switch) | debug: load `"powerplant"`, `"0_Test_Clash"`, `"0_Test_Arena"` or `"0_Test_Look"` (`fn_8002D7A8(lbl_8052F060, name, 8, 0, 0, 0)`) |
| 0x56, 0x57, 0x58 | (in the switch) | `fn_80128C3C("example1"` / `"example2")`; `fn_8002DB78(lbl_8052F060)` |
| 0x59, 0x5A, 0x5B | `fn_800B8174` (0, 1, 2) | `fn_804463C0` on item `+0x1C4` of `lbl_8066B698`, then command 0x18 |
| 0x25E-0x35E | `fn_800B7584` | `.nsc` record `command - 0x25E` into `+0x24`, **clears `G+0x59C`**, then command 0x19 / 0x18 / 9 |
| 0x35F-0x45F | `fn_800B743C` | item `command - 0x35F` of `lbl_8066B698` into `+0x1C4`, then the command saved in `+0x1BC` |
| 0x460-0x560 | `fn_800B74C4` | item `command - 0x460` into `+0x1C4`, then command 0xA |
| 0x561-0x661 | `fn_800B73C4` | `Stub6CFC(command - 0x561, G+0x59C)`, then command 0 or 0x18 |

**Fields** (types confirmed, meanings guessed; the matched units name only some): `+0x0` float, a timer drained by the frame time and zeroed on pad input; `+0x4` set while a pad is unplugged; `+0x1C` `unsigned char`, single-bit flags or a small state (`BeginLoad` stores 3, `EndLoad` 4); `+0x20` the command; `+0x24` the `.nsc` record index; `+0x28` the pending screen; `+0x2C` `char[0x100]` the level name; `+0x12C` a pointer to that record; `+0x158` blocks dispatch; `+0x160`/`+0x164` the pad port and slot index `fn_800B56DC` picks; `+0x16C`, `+0x19C` handles released through `fn_80232B78`; `+0x170`/`+0x174` pointers to the two players' loading-screen images (`u16` width `+0x58`, height `+0x5A`), drawn by `fn_800B47C0` while `+0x178` is set; `+0x17C` the load mode; `+0x18C`-`+0x19C` a member subobject of unknown class; `+0x1A0` `int[5]` the command history, most recent first; `+0x1B4`/`+0x1B8` a one-deep command save; `+0x1BC` the command to return to; `+0x1C4` an index into `lbl_8066B698`; `+0x1DC` set by `fn_804463F8`, cleared by `fn_8044606C`; `+0x1E0 == 1` draws the frame rate; `+0x1F4` `unsigned char`, `command - 0x2F`; `+0x284` count and `int[2]` at `+0x288`, the players whose pad is unplugged.

`lbl_8066B690` and `lbl_8066B694` are two objects `fn_8043206C` releases, and `lbl_8066B698` a collection `fn_801B5D3C` indexes and `fn_801B6A44` counts; fifteen of the methods drive them, so they are what the debug menu's option screens edit. `OnPadRemoved__FUs` and `OnPadInserted__FUs` forward an SI port to `fn_800B4AB8`/`fn_800B4CF8`; `fn_801AA5E4` registers them as hotplug callbacks (`lbl_8066C644`/`lbl_8066C648`) and polls `SIProbe` on ports 0-3.

---

## 7. Open Questions

- What is the rest of the `Slot` layout? `+0x3C` is a small number per slot rather than a flag (`fn_800956D4` sets 1 on the second slot, `fn_80431788` 99 on the CPU slot, `fn_800B5124` copies a `u16` into it), and the meanings of `+0x38` and `+0x40` are unknown. `+0x24`-`+0x33` and everything from `+0x44` on, except `+0x64`, `+0x80` and `+0x90`, are unknown. 
- What are the `GameFlow` command ids (section 6)? Commands 1, 2, 6 and 8 are special-cased, and the four wide ranges from 0x25E are index spaces, each subtracting its base into `+0x24` or `+0x1C4`.
- What is in the unidentified files at 0x801070FC and 0x8010C528?
- What are the rectangles at `.sbss` 0x8066D6AC and 0x8066D6BC? Both are built from the screen size at static init; only `fn_800B5124` reads the first and nothing reads the second (guess: debug-overlay bounds the release no longer draws).
- What are `lbl_8066B690`, `lbl_8066B694` and `lbl_8066B698` (section 6)? Nothing matched so far constructs them.
- Which file holds the `AptObject`/`AptRef` methods at 0x801021A0-0x801037B0 and 0x8044B4EC-0x8044B81C, and what are the classes really called?
- Character questions are in [`characters.md`](characters.md) (sections 3 and 5).
