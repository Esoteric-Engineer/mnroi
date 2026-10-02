# Versus Mode Map

Where the versus-mode code is, what it touches, and the order to decompile it in. `decomp-versus` picks its targets from section 5.

See also:
- The per-function loop: [`workflow.md`](workflow.md).
- C++ naming, mangling and static initialization: [`prodg.md`](prodg.md#c).

Everything here comes from reading the disassembly. Names in the "Meaning" columns are guesses until a unit matches; update them when you learn better.

---

## 1. How the Handlers Were Found

The frontend is EA's APT (Flash) UI. Its screens call native functions by name, and each handler file registers them from its static initializer. Each registration constructs one global object, a 1-byte object in `.sbss`, through one of several constructors that differ by the handler's signature (`fn_8044AF58`, `fn_8044B11C`, `fn_8044BBC8` and others in 0x8044AF58-0x8044EE3C):

```
r3 = &registration_object      // lbl_8066D722
r4 = "Control_SetMatchInfo"    // script-visible name
r5 = fn_80104564               // the handler
r6 = __FILE__                  // "c:/Clash/mainline/Code/Game/handlers/control.cpp"
r7 = __LINE__                  // 211
```

That gives 171 handlers across six files, with no duplicate names or shared handlers. In `symbols.txt` each handler is named after its script name, and each file's registering function is `__static_initialization_and_destruction_0` (`scope:local`).

**The handler names are provisional.** They are the script-visible strings, not confirmed C++ symbols. A C++ unit emits GCC 2.95-mangled names (`Control_SetMatchInfo__Fiiii`), so when you match a handler, either rename it in `symbols.txt` to the mangled name you've worked out, or declare it `extern "C"` if that's what matches.

---

## 2. File Map

A `_GLOBAL_.I` function in `.ctors` ends each file ([`prodg.md`](prodg.md#c)). Its suffix is the file's first global symbol, so it stays `fn_` until that symbol is known.

| File | `.text` range | Handlers | Static init / `_GLOBAL_.I` | Notes |
|---|---|---|---|---|
| ? | ..0x801021A0 | | `fn_80102164` (`_GLOBAL_.I`) | |
| `Game/handlers/characterselect.cpp` | **at most** 0x801021A0-0x801040F4 | 2 | 0x80103FF4 / 0x801040B8 | The start is an upper bound: files without global constructors have no end marker, so 0x801021A0-0x801037B0 may hold other files. |
| `Game/handlers/control.cpp` | 0x801040F4-0x80106B34 | 64 | 0x8010611C / 0x80106AF8 | Handlers only, lines 48-1057. |
| `Game/handlers/feonline.cpp` | 0x80106B34-0x801070FC | 17 | 0x80106D80 / 0x801070C0 | Online only (`Online_*`). |
| ? | 0x801070FC-0x80107244 | | 0x8010718C / 0x80107208 | Unidentified. |
| `Game/handlers/memcard.cpp` | 0x80107244-0x8010A448 | 66 | 0x801099E8 / 0x8010A40C | Save/load. |
| `Game/handlers/mission.cpp` | 0x8010A448-0x8010BED8 | 16 | 0x8010BB80 / 0x8010BE9C | Story mode. |
| `Game/handlers/venuetable.cpp` | 0x8010BED8-0x8010C528 | 6 | 0x8010C338 / 0x8010C4EC | Handlers only. |
| ? | 0x8010C528-0x8010CA44 | | / 0x8010CA08 | |

Other source paths in the DOL (assert strings), for later: `Game/HUD/glueAEMS.cpp` (`fn_80111BB8`), `Game/Sim/simCutPlayer.cpp` (`fn_80438FAC`), `Std/BufferAllocator.cpp` (`fn_801B0C90`), `Std/stdBigHashedVFS.cpp` (`fn_801B1270`, `fn_801B1D74`), `DirectGC/directTexture.cpp` (`fn_802338A8`), `ExternalGC/nsiAllocator.cpp` (`fn_8016840C`).

---

## 3. Match Setup Flow

The versus setup screens (`clashLoadscreenVersus.big` and the `VERSUS MODE SETUP` screen in `CLASH.BIG`) call, roughly in this order:

| Handler | Address | Size | What it does |
|---|---|---|---|
| `clashCharSelect_GetCharList` | 0x801037B0 | 0x3FC | Builds the character list for the select screen. |
| `clashCharSelect_GetPrevCharList` | 0x80103BAC | 0x418 | Restores the previous selection. It is the only reader of the last-selection module (section 4.2). |
| `Control_SetSelectInfo` | 0x80104710 | 0x308 | Stores per-player picks, both in the last-selection module and in the game-state object (`+0x5BB`); reads `+0x75C`. |
| `Control_BindController` | 0x80105334 | 0x4C | Binds a controller to a player (last-selection `lbl_8066F1A0`/`A4`). |
| `clashVenue_GetVenueList` / `ChooseOption` / `StartLevel` | 0x8010BED8 / 0x8010C090 / 0x8010BFFC | | Venue select. `StartLevel` writes the level name and `+0x61C`, and `ChooseOption` writes `+0x75C`. |
| `Control_SetMatchInfo` | 0x80104564 | 0x1AC | Sets the match type, timer and slot roles. See below. |
| `Control_StartLoad` / `Control_StartGame` | 0x80104A18 / 0x80104B34 | 0x48 each | Starts the match. |
| `Control_EndOfMatch` | 0x80104B7C | 0xA8 | Post-match path. |

**`Control_SetMatchInfo(int matchType, int timed, int unused, int seconds)`**, where `this` is the game-state object `G` (section 4.1):

- It saves `matchType`, `timed` and `seconds` in the last-selection module (`fn_801317D8`, `fn_80131828`, `fn_801318C8`).
- It switches on `matchType`, assigning the role indices at `G+0x770`, `G+0x774` and `G+0x590` through tiny setters (`fn_804317F4`, `fn_8043181C`, `fn_80431844`):
  - `0`: `+0x774=0`, `+0x770=1`, `+0x590=2`.
  - `1`: `+0x770=0`, `+0x590=2`, `+0x774=1`. It also takes slot 1 (`fn_804317BC(G, 1)`) and calls `fn_80431788` on it, which ORs `slot+0x34` with `4` and sets `slot+0x3C = 99`. That may mark the slot as CPU-controlled.
  - `2`: `G+0x61C = 1`, `+0x774=0`.
- `timed == 0` sets `G+0x75C = 2`. Otherwise it sets `G+0x75C = 1` and `G+0x764 = seconds * 1000`.
- For players 0 and 1 it calls `fn_80443CCC(G, player, fn_801318A0())`, which forwards to a method on slot `player` (`fn_804428E0`).

---

## 4. Data

### 4.1 Game-state object `G` (`lbl_80552110`, `.bss`)

This is a C++ singleton that 211 functions reference, so it is the whole game state, not just the match. dtk split it into several labels (`lbl_80552110`, `lbl_80552120` size 0x58C, `lbl_805526AC`...). Methods called on it most often: `fn_8043289C`, `fn_80432924`, `fn_80432870`, `fn_80432844`, `fn_80094630`, `fn_80426AB0`, `fn_804317BC`, `fn_800945E4`.

| Offset | Type | Meaning (guess) | Written by | Read by |
|---|---|---|---|---|
| +0x10 | `Slot[8]`, stride 0xB0 | Player slots. `fn_804317BC(G, i)` returns `&slot[i]`. | | |
| +0x590 | int | Role index (see `SetMatchInfo`) | `fn_80431844` | `fn_80023010`, `fn_80096B98`, `fn_80096D6C` |
| +0x59C, +0x5BC, +0x5DC, +0x5FC | `char[0x20]` x4 | Level/venue name buffers. Writers store the terminator at `+0x5BB` and so on. | `Control_SetSelectInfo`, `clashMission_StartLevel`, `clashVenue_StartLevel`, `clashVenue_ChooseOption`, `fn_80028BAC`, `fn_8008856C` | `fn_800B76C0` |
| +0x61C | int | Set to 1 for match type 2 and by both `StartLevel` handlers | `Control_SetMatchInfo`, `clashMission_StartLevel`, `clashVenue_StartLevel` | `fn_8002BD34` |
| +0x75C | int | Timer mode: 1 = timed, 2 = untimed | `Control_SetMatchInfo`, `clashVenue_ChooseOption`, `fn_80028BAC` | `Control_SetSelectInfo`, `fn_8011A94C`, `fn_8011AB34` |
| +0x760 | int | Written by 14 functions; probably a game phase or state | `fn_8002D90C`, `fn_80092550`... | `fn_80018290`... |
| +0x764 | int | Time limit in ms | `Control_SetMatchInfo`, `fn_80028BAC` | `fn_80131434` |
| +0x770, +0x774 | int | Role indices (see `SetMatchInfo`) | `fn_804317F4`, `fn_8043181C` | |

`fn_80028BAC` writes most of these fields, along with `+0x74`-`+0x7C` and `+0x620`-`+0x62C`. It looks like a "set up the match from settings" or reset function, and is a good early target.

### 4.2 Last-selection module (0x801317D8-0x80131E90, `.sbss` `lbl_8066F178`-`lbl_8066F1A4`)

These are plain getters and setters around small-data globals. The setup handlers write them and only `clashCharSelect_GetPrevCharList` reads them back, so they remember the previous menu selection rather than drive the match.

| Global | Setter / getter | Written by |
|---|---|---|
| `lbl_8066F178` match type | `fn_801317D8` / `fn_80131800` | `Control_SetMatchInfo` |
| `lbl_8066F17C` timed | `fn_80131828` / `fn_80131850` | `Control_SetMatchInfo` |
| `lbl_8066F180` | `fn_80131878` / `fn_801318A0` | `fn_80028BAC`, `fn_8011D4E4`, `fn_8011E1DC` |
| `lbl_8066F184` seconds | `fn_801318C8` / `fn_801318F0` | `Control_SetMatchInfo` |
| `lbl_8066F188`/`lbl_8066F194` | Per-player: `fn_80131918` / `fn_80131974` | `Control_SetSelectInfo` |
| `lbl_8066F18C`/`lbl_8066F198` | Per-player: `fn_801319D4` / `fn_80131A34` | `Control_SetSelectInfo` |
| `lbl_8066F190`/`lbl_8066F19C` | Per-player: `fn_80131A94` / `fn_80131AF4` | `Control_SetSelectInfo` |
| `lbl_8066F1A0`/`lbl_8066F1A4` | Per-player: `fn_80131B54` / `fn_80131BB4` | `Control_BindController` |
| all of the above | `fn_80131E1C` (reset) | `fn_80103FC4` (in `characterselect.cpp`) |

---

## 5. Target Order

Work these in order and skip whatever is already matched (check `configure.py`). The character code comes first because adding characters is the first mod the community wants ([`characters.md`](characters.md)). Name each unit after its real source file when it is known (section 2), and grow it as one contiguous `.text` range from the file's first function, so that the unit becomes the whole file once it is finished. Where the file is unknown, use decomp-next's `Game/fn_XXXXXXXX.cpp` naming.

1. **`characterselect.cpp`** (unit `Game/handlers/characterselect.cpp`): `clashCharSelect_GetCharList` (the hard-coded 18-character loop), `clashCharSelect_GetPrevCharList`, `fn_80103FC4`, and the static initializer. The file's start is unknown (section 2). Either settle it first, or start the unit at 0x801037B0 and extend it downward later. Its helpers `fn_80102E60`-`fn_80103480` build the APT arrays.
2. **Character roster** ([`characters.md`](characters.md) section 2): `fn_80431CCC`, the per-field accessors `fn_8044B1D4`-`fn_8044B48C`, and the roster data `lbl_804CA51C`, `lbl_804CAB0C` and `lbl_804CB0FC`. The accessors sit among the APT registration constructors at 0x8044AF58-0x8044EE3C, so work out the file boundaries there before claiming anything.
3. **Character type** ([`characters.md`](characters.md) sections 1 and 5): `fn_80020E60` (a long but simple `-O0` `strcmp` chain), then its callers `fn_8001C258`, `fn_80023010` (auras) and `fn_8002623C`, and `fn_80114420` (SFX).
4. **Selection to spawn** ([`characters.md`](characters.md) section 3): the slot methods `fn_80443B70`, `fn_80443BC8`, `fn_80443BF4`, `fn_80443CCC` and `fn_804428E0`, then `fn_80131060`, `fn_800887AC`, `fn_801311C0`, and `fn_800B5BC4` with its helpers. This is where the entity name should lead to the model, motion set and NVB loads.
5. **`control.cpp`** (unit `Game/handlers/control.cpp`, starting at 0x801040F4). The first twelve functions are small getters (`gPALMode` through `gPlatform`). After them come the versus handlers in address order: `Control_ChangeScreen`, `Control_EnableControllerCheck`, `Control_SetMatchInfo`, `Control_SetSelectInfo`, `Control_StartLoad`, `Control_StartProgressBar`, `Control_StartGame` and `Control_EndOfMatch`. Then finish the file (`Control_BindController` is further down), ending with its static initializer.
6. **`venuetable.cpp`** (unit `Game/handlers/venuetable.cpp`): all six handlers.
7. **The last-selection module** (0x801317D8-0x80131E90). These are tiny accessors, so they are quick to match and give names to everything in section 4.2.
8. **`G`'s other methods called by the above:** `fn_80431788`-`fn_80431844`, then the most-called ones in section 4.1.
9. **Readers of the match fields:** `fn_80028BAC`, `fn_8002BD34`, `fn_80131434`, `fn_8011A94C`, `fn_8011AB34`, and then whatever they lead to. This is where the game moves from menus into the match itself.

Out of scope for versus: `memcard.cpp` (except for checking whether saves depend on the roster size, see [`characters.md`](characters.md) section 2), `feonline.cpp`, `mission.cpp`, and third-party code (Havok `hk*`, RealCore, RealGraph).

## 6. Open Questions

- What do the role indices at `+0x590`/`+0x770`/`+0x774` mean, and what are match types 0, 1 and 2?
- What is the `Slot` layout (0xB0 bytes)? Flag `4` at `+0x34` and `99` at `+0x3C` are set for slot 1 in match type 1.
- What is `SetMatchInfo`'s unused third argument?
- What is in the unidentified files at 0x801070FC and 0x8010C528?
- Character questions are in [`characters.md`](characters.md) (sections 3 and 5).
