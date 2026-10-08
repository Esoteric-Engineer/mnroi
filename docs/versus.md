# Versus Mode Map

Where the versus-mode code is, what it touches, and the order to decompile it in. `decomp-versus` picks its targets from section 5.

See also:
- The per-function loop: [`workflow.md`](workflow.md).
- C++ naming, mangling and static initialization: [`prodg.md`](prodg.md#c).

**This is a reference, not a narrative: read the section you need, not the file.** Section 5 alone is
enough to pick a target and know its blocker; the rest answers questions as they come up. What a
matched function does is in its source file, and `configure.py` is the authority on which units are
matched, so neither is repeated here.

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

**The handler names are provisional.** They are the script-visible strings, not confirmed C++ symbols. A C++ unit emits GCC 2.95-mangled names (`Control_SetMatchInfo__Fiiii`), so when you match a handler, either rename it in `symbols.txt` to the mangled name you've worked out, or declare it `extern "C"` if that's what matches. The first one claimed came out as
`clashCharSelect_GetCharList__Fv`: a no-argument handler that returns the APT object it fills in.

---

## 2. File Map

A `_GLOBAL_.I` function in `.ctors` ends each file ([`prodg.md`](prodg.md#c)). Its suffix is the file's first global symbol, so it stays `fn_` until that symbol is known.

| File | `.text` range | Handlers | Static init / `_GLOBAL_.I` | Notes |
|---|---|---|---|---|
| ? | ..0x801021A0 | | `fn_80102164` (`_GLOBAL_.I`) | |
| ? (APT script variables) | 0x801021A0-0x801037B0 | | | Engine code, not characterselect: `fn_80102E60`, `fn_80102F10`, `fn_80102FD0`, `fn_8010329C` and `fn_80103080` are called from `0x8044B694`/`0x8044B758` in another file. See below. |
| `Game/handlers/characterselect.cpp` | 0x801037B0-0x801040F4 | 2 | 0x80103FF4 / 0x801040B8 | Confirmed: the `__LINE__` arguments in the static initializer put `GetCharList` at line 41, `GetPrevCharList` at 95 and `fn_80103FC4` at 100, so nothing precedes the first handler. |
| `Game/handlers/control.cpp` | 0x801040F4-0x80106B34 | 64 | 0x8010611C / 0x80106AF8 | Handlers only, lines 48-1057. Every handler is matched; the units are listed in section 5, row 5. |
| `Game/handlers/feonline.cpp` | 0x80106B34-0x801070FC | 17 | 0x80106D80 / 0x801070C0 | Online only (`Online_*`). |
| ? | 0x801070FC-0x80107244 | | 0x8010718C / 0x80107208 | Unidentified. |
| `Game/handlers/memcard.cpp` | 0x80107244-0x8010A448 | 66 | 0x801099E8 / 0x8010A40C | Save/load. |
| `Game/handlers/mission.cpp` | 0x8010A448-0x8010BED8 | 16 | 0x8010BB80 / 0x8010BE9C | Story mode. |
| `Game/handlers/venuetable.cpp` | 0x8010BED8-0x8010C528 | 6 | 0x8010C338 / 0x8010C4EC | Handlers only, lines 45-140. |
| ? | 0x8010C528-0x8010CA44 | | / 0x8010CA08 | |

### The APT script-variable classes

Two engine classes carry every value a handler hands to the UI. Layout and signatures come from the
code; **the class and member names are guesses**, so renaming them means redoing every mangled symbol
below.

| Class | Size | Members | Symbol |
|---|---|---|---|
| `AptObject` | 8 | ctor / copy ctor / dtor | `__9AptObject` (0x8044B608), `__9AptObjectRC9AptObject` (0x8044B568), `_._9AptObject` (0x8044B510) |
| | | `operator[](const char *name)` -> `AptRef` | `__vc__9AptObjectPCc` (0x80102E60) |
| `AptRef` | 12 | `+0x0` owning object, `+0x4` property name, `+0x8` element index (-1 for the property itself) | |
| | | `operator[](int index)` -> `AptRef` | `__vc__6AptRefi` (0x8044B5B0) |
| | | `operator=(char *const &)` | `__as__6AptRefRCPc` (0x8044B694) |
| | | `operator=(const int &)` | `__as__6AptRefRCi` (0x8044B758) |
| | | four more `operator=` overloads, value types unknown (three take the value in a register, one through a pointer) | 0x8044E9D4, 0x8044EA98, 0x8044EB5C, 0x8044EC20 |

So `list["aIntel"][i - 1] = value;` compiles to the four-call chain the handlers are built from. The
assignment operators take a reference, which is why each assigned value gets its own stack temp.
`fn_80102F10` hashes a property name (djb2, seed 0x1505) and looks it up in the object's table at
`+0x50`, with `+0xAD0` as the count.

Other source paths in the DOL (assert strings), for later: `Game/HUD/glueAEMS.cpp` (`fn_80111BB8`), `Game/Sim/simCutPlayer.cpp` (`fn_80438FAC`), `Std/BufferAllocator.cpp` (`fn_801B0C90`), `Std/stdBigHashedVFS.cpp` (`fn_801B1270`, `fn_801B1D74`), `DirectGC/directTexture.cpp` (`fn_802338A8`), `ExternalGC/nsiAllocator.cpp` (`fn_8016840C`).

---

## 3. Match Setup Flow

The versus setup screens (`clashLoadscreenVersus.big` and the `VERSUS MODE SETUP` screen in `CLASH.BIG`) call, roughly in this order:

| Handler | Address | Size | What it does |
|---|---|---|---|
| `clashCharSelect_GetCharList` | 0x801037B0 | 0x3FC | Builds the character list for the select screen. |
| `clashCharSelect_GetPrevCharList` | 0x80103BAC | 0x418 | Restores the previous selection. It is the only reader of the last-selection module (section 4.2). |
| `Control_SetSelectInfo` | 0x80104710 | 0x308 | `(charId0, live0, cusType0, charId1, live1, cusType1, venue)`. Saves the picks in the last-selection module, spawns each player's record (`fn_80443678(clamp(charId + 1, 1, 18), 1, cusType)`, `fn_800944C0(G, record, player)`), passes `live` to `fn_8044D600(G, player, live)` only when `G+0x75C == 2` (else 1), copies the `venue` object's name into `G+0x59C` (default `lbl_80490528`, terminator at `+0x5BB`), then looks it up in the name table and selects it (`fn_8008856C`). |
| `Control_BindController` | 0x80105334 | 0x4C | Binds a controller to a player (last-selection `lbl_8066F1A0`/`A4`). |
| `clashVenue_GetVenueList` / `ChooseOption` / `StartLevel` | 0x8010BED8 / 0x8010C090 / 0x8010BFFC | | Venue select over the venue table ([`characters.md`](characters.md) section 3). `StartLevel(String)` writes the level name and `+0x61C`, and `ChooseOption(n)` looks up venue `n - 1` in the name table, selects it (`fn_8008856C`), writes `+0x75C = 2` and puts the venue's `fn_804426AC` name in `G+0x5DC` (terminator `+0x5FB`). |
| `Control_SetMatchInfo` | 0x80104564 | 0x1AC | Sets the match type, timer and slot roles. See below. |
| `Control_StartLoad` / `Control_StartGame` | 0x80104A18 / 0x80104B34 | 0x48 each | Starts the match. |
| `Control_EndOfMatch` | 0x80104B7C | 0xA8 | Post-match path. |

**`Control_SetMatchInfo(int matchType, int timed, int unused, int seconds)`**, where `this` is the game-state object `G` (section 4.1):

- It saves `matchType`, `timed` and `seconds` in the last-selection module (`fn_801317D8`, `fn_80131828`, `fn_801318C8`).
- It switches on `matchType`, assigning the role indices at `G+0x770`, `G+0x774` and `G+0x590` through tiny setters (`fn_804317F4`, `fn_8043181C`, `fn_80431844`):
  - `0`: `+0x774=0`, `+0x770=1`, `+0x590=2`.
  - `1`: `+0x770=0`, `+0x590=2`, `+0x774=1`. It also takes slot 1 (`fn_804317BC(G, 1)`) and calls `fn_80431788` on it, which ORs `slot+0x34` with `4` and sets `slot+0x3C = 99`. That marks the slot as CPU-controlled: `GameFlow`'s pad-unplugged handler skips slots with the bit set.
  - `2`: `G+0x61C = 1`, `+0x774=0`.
- `timed == 0` sets `G+0x75C = 2`. Otherwise it sets `G+0x75C = 1` and `G+0x764 = seconds * 1000`.
- For players 0 and 1 it calls `fn_80443CCC(G, player, fn_801318A0())`, which forwards to a method on slot `player` (`fn_804428E0`).

---

## 4. Data

### 4.1 Game-state object `G` (`lbl_80552110`, `.bss`)

This is a C++ singleton that 211 functions reference, so it is the whole game state, not just the match. dtk split it into several labels (`lbl_80552110`, `lbl_80552120` size 0x58C, `lbl_805526AC`...). Methods called on it most often: `fn_8043289C`, `fn_80432924`, `fn_80432870`, `fn_80432844`, `fn_80094630`, `fn_80426AB0`, `fn_804317BC`, `fn_800945E4`.

| Offset | Type | Meaning (guess) | Written by | Read by |
|---|---|---|---|---|
| +0x10 | `Slot[8]`, stride 0xB0 | Player slots (dtk's `lbl_80552120`). `fn_804317BC(G, i)` returns `&slot[i]`, and `fn_8042FF2C(slot)` returns the slot's actor. Known fields: `+0x0` int player index, `+0x4` `char[0x20]` entity name, `+0x30` int, `+0x34` int flags (bit 0 = in use, bit 1 = unknown, tested by `fn_8044272C` with a null check; bit 2 = CPU-controlled), `+0x38` int, `+0x3E` `unsigned short` the controller port the slot plays on (the pad hotplug handlers match it against the SI port), `+0x3C` int, `+0x40` float. The 0xB0 stride is now confirmed from the source side: `fn_80443CCC` only matches with `Slot` padded to 0xB0. | | |
| +0x590 | int | Number of active player slots, not a role index: `fn_80023010` (matched) loops `p` from 0 while `p < G+0x590` and reads slot `p` each time, and `fn_80443D44` (matched) uses it as the bound on `slots` when looking a player up. `SetMatchInfo` setting it to 2 for match types 0 and 1 fits a 2-player match. | `fn_80431844` | `fn_80434900` (getter), `fn_80023010`, `fn_80114420`, `fn_80443D44`, `fn_80096B98`, `fn_80096D6C` |
| +0x598 | int | Index into `slots`: `fn_80443DBC` uses it to set `+0x744`. A plain setter, no getter found. Both are **matched** (`Game/fn_80443B70.c`), which confirms the field is a plain `int` slot index. | `fn_80443D1C` | `fn_80443DBC` |
| +0x59C, +0x5BC, +0x5DC, +0x5FC | `char[0x20]` x4 | Level/venue name buffers. `+0x59C` is dtk's `lbl_805526AC` (0x80552110 + 0x59C), which confirms the 0x20 size, and `GameFlow`'s command 0x14 (`fn_800B76C0`, section 6) is what loads the level it names. Writers store the terminator at `+0x5BB` and so on. | `Control_SetSelectInfo`, `clashMission_StartLevel`, `clashVenue_StartLevel`, `clashVenue_ChooseOption`, `fn_80028BAC`, `fn_8008856C` | `fn_800B76C0`, `fn_80114420` (`strcmp` against `"0_Test_Arena"`, which confirms `+0x59C` holds the level name) |
| +0x61C | int | Set to 1 for match type 2 and by both `StartLevel` handlers | `Control_SetMatchInfo`, `clashMission_StartLevel`, `clashVenue_StartLevel` | `fn_8002BD34` |
| +0x744 | `Slot *` | The current slot, `&G->slots[G+0x598]`. Confirmed as a pointer: `fn_80443DBC` is **matched** as `g->curSlot = &g->slots[g->curIndex]; return 1;` (the `1` is a constant, not a success test). | `fn_80443DBC` | `fn_80095100`, `fn_800950E8` |
| +0x750 | `Slot *` | Slot iteration cursor: `fn_804427FC(G)` resets it to `&slots[G+0x598]` and returns 1, `fn_804427D0(G)` reads it, and `fn_80094A9C(G)` (unmatched) advances it and returns nonzero while slots remain. | `fn_804427FC`, `fn_80094A9C` | `fn_804427D0` |
| +0x75C | int | Timer mode: 1 = timed, 2 = untimed | `Control_SetMatchInfo`, `clashVenue_ChooseOption`, `fn_80028BAC` | `Control_SetSelectInfo`, `fn_8011A94C`, `fn_8011AB34` |
| +0x760 | int | Written by 14 functions; probably a game phase or state | `fn_8002D90C`, `fn_80092550`... | `fn_80018290`... |
| +0x764 | int | Time limit in ms | `Control_SetMatchInfo`, `fn_80028BAC` | `fn_80131434` |
| +0x770, +0x774 | int | Role indices (see `SetMatchInfo`). `fn_80114420` treats "either one nonzero" as "a match is running", which holds for match types 0 and 1 but not 2. | `fn_804317F4`, `fn_8043181C` | `fn_80432844` (+0x770) and `fn_80432870` (+0x774), the getters; `fn_80114420` |
| +0x7BC | int | A flag, zeroed by `G`'s constructor `fn_80091174`; its only reader bumps a counter at `G+0x78` when it is 0. | `fn_80091174` | `fn_80443CA0` (getter, matched), `fn_80096884` |

`fn_80028BAC` writes most of these fields, along with `+0x74`-`+0x7C` and `+0x620`-`+0x62C`. It looks like a "set up the match from settings" or reset function, and is a good early target.

`fn_80091174` is `G`'s constructor: it zeroes the fields above, sets `+0x75C = 3` and `+0x764 = 0x1993E0`, and seeds slots 0 and 1 with `plr_wolverine` through `fn_80443B70`. So `+0x75C = 3` is a third, pre-match value of the timer mode, not one of `SetMatchInfo`'s two.

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
| all of the above except `lbl_8066F180` | `fn_80131E1C` (reset to -1) | `fn_80103FC4` (in `characterselect.cpp`) |

The range also holds three per-player counter bumpers (`fn_80131C14`, `fn_80131C9C`, `fn_80131D24`: `.sdata` `lbl_8066BF0C` is a shared running total, passed to `fn_8012FEF0`, plus one counter per player) and two read-and-clear accessors (`fn_80131DAC`, `fn_80131DE4`: `lbl_8066BF10`, `lbl_8066BF14`). Their meaning is unknown.

---

## 5. Target Order

Work these in order and skip whatever is already matched. `configure.py` is the authority on unit
status; this table gives the order and the blockers, not a changelog. Name each unit after its real
source file when it is known (section 2) and grow it as one contiguous `.text` range from the file's
first function, so the unit becomes the whole file once it is finished; otherwise use decomp-next's
`Game/fn_XXXXXXXX.cpp` naming. The character code comes first because adding characters is the first
mod the community wants ([`characters.md`](characters.md)).

| # | Target | Next action / blocker |
|---|---|---|
| 1 | `characterselect.cpp`, 0x801037B0-0x801040F4 | Done: the whole file, static initializer included. |
| 2 | Character roster ([`characters.md`](characters.md) section 2) | **Current step.** Accessors done; the roster *data* (`lbl_804CA51C`, `lbl_804CAB0C`, `lbl_804CB0FC`) is left. It sits among the APT registration constructors at 0x8044BBC8-0x8044EE3C, so work out those file boundaries before claiming anything. The registrars (`Game/fn_8044AE3C.cpp`, 0x8044AE3C-0x8044B1D4) come in groups of four per handler return type (call thunk, its forwarder, the thunk's table entry, the constructor): the constructor appends `{name, thunk, handler}` to the 0xC-byte entries at `lbl_805663A4` (count `lbl_8066D6FC`, stops storing past 0x170) and passes file and line to the empty stub `fn_8044B4EC`. Next unclaimed function: `fn_8045895C` (0xA0, the `fn_8045873C` analog over `fn_8045B430`/`fn_8045B3E0`; `Game/fn_804580CC.cpp` ends before it, reads its float pool from 0x80497A18 through `extern_pool`, and holds the 0xD4, 0x150, 0xD8, 0xD4, 0xC0, 0xAC, 0x64, 0xD0, 0xA0 and 0xD0 members, the last a `new ObjD(0, 50, value)` factory like the `Obj92` one (0x10 bytes), the 0x64 one a `new ObjC(0, 0)` factory (guessed name; 0xC bytes, `new` is `fn_8045D2E8`), the 0xAC one a `(self, unused, index)` setup like the 0x150 one with a fixed 0x384 in place of the `+0x24` test; the two 0xD4 ones are the same factory over `Obj90`/`Obj92`, each with its own `operator new`, the last being a `(self, unused, index)` setup that feeds `fn_80112214` the record's `+0x2C` handle and sets a flag on `self` from `+0x24 > 0x257`: an `Obj90` factory (`new` through the class `operator new` `fn_8045C458`, a `fn_8024606C(size)` front) and `fn_804581A0`, which caches a node handle at record `+0x50`; `Game/fn_80457688.cpp` ends before that and holds `WordTriple` (three zeroed words, called from 0x801189FC), `RecArr`, whose 0x40-byte `Rec` layout is in its source, and `HandleA`/`HandleB`/`HandleC`, the shape of the 0x68 members: vptr `lbl_804F2E28` at `+0x4`, `new` of a 0x10-byte impl into `+0x0`, the impl constructor `fn_8045DB68` taking the name, `HandleB`/`HandleC` are the same over `lbl_804F3148`/`fn_8045DBD4` and `lbl_804F2E40`/`fn_8045DC40`; sizes run 0x68, 0x68, 0x40, 0xD4, ...; the allocator front before a 0x88 constructor such as `Obj115` is `fn_8024606C(size)`, called by the handler at 0x80113E14 with 8; and the 0x4C one is the release method, `if (*self) fn_802467D0(*self, &self[1])`; the 0x5C ones are destructors of the `Game/fn_80456AA4.c` shape over their own `fn_8045D...` delete; the 0x98-0xE8 members are constructors over N setters (one for 0x98) then the `lbl_8066D9xx` lookup, the 0x5C pair destructor and one more, 0x4C the release method; destructors are the `Game/fn_8045489C.c` shape; unchecked); the handler at 0x801104BC `new`s an `Obj8B`; the handler at 0x8010D220 keeps its `Obj8` in `lbl_8066BD34`). The handlers at 0x8010D220, 0x8010E6C8 and 0x801129EC each allocate and construct one of these handle objects (`Obj8`, `Levels` (0x10 bytes), `Level` (8 bytes)); the setters `fn_80459CBC`/`fn_80459D00`/`fn_80459D44` (clamp 0-100 at `+0x4`/`+0x8`/`+0xC`), `fn_80459DC0` (0-10 at `+0x4`) and `Obj8B`'s eight (`fn_80459E74`-`fn_8045A060`) are still unmatched; the six-function groups are done through the twelfth, and the run changed shape at 0x80454340, whose sizes are 0x44 (`Record::Record`, done), 0x58 (`fn_80454384`, done: the player-slot accessor `fn_804326B4(lbl_8054ED80)` + 0x4A4 + slot*0x20, slots 0-8, called from 0x801141AC, so it is not part of the table), 0x44 (done), 0xB8 (done), 0x5C, 0x44, 0x98, ...; check callers before assuming a member belongs to the table; each 0x334 member was `fn_804500EC` over that group's own callees). The run repeated the six-function group 0xA4, 0xC4, 0x54, 0xB0, 0xB0, 0x334 per record table over the same `lbl_80567760`, each group with its own callee set (the second group releases through `fn_8044FDD0`/`fn_80455758`; its 0x334 member `fn_804500EC` is `fn_8044FA9C` with `fn_804588AC`, `fn_804587DC`, `fn_8045895C` and `fn_804557B4` for `fn_804581A0`, `fn_804580CC`, `fn_804582F0` and `fn_80456064`), so check each member's callees and field offsets, not the shape. The 0x60-byte table `lbl_80567760` (its `symbols.txt` size of 0x10 is wrong; 48 records, constructed by the loop at 0x80118994 in the static initializer) has `+0x0` an owner pointer, `+0x20` a source handle, `+0x24` a count compared with 0x257, `+0x2C` a handle, `+0x30` a state (0 idle, 1 created, 3 release), a live count at `+0x3C`, words at `+0x48`/`+0x4C` (`+0x4C` is a free flag: `fn_8044F8E8` releases a record and sets it to 1, callers test it for 0); `lbl_80568DB0+0x14` is the current record index; `lbl_8066BD1C` is a counter that `fn_8044F824` decrements; `Record` needs `aligned(8)` for the DOL's `add` + `lwz` shape. `AptRef`'s `operator=(const unsigned &)` and the `String` fronts `fn_8044F5A4`/`fn_8044F614` of the int-to-`String` builder `Game/fn_8044F4BC.c` precede it. `Game/fn_8044EEF4.c` is the menu-object leaf run (flags at `+0x1AC`, the `lbl_804CB16C` name table, `lbl_804CB0FC` a 20-int id table); `Game/fn_8044F1D4.cpp` starts the int-to-`String` group, whose `String` converter is `fn_8044F1D4`. The groups before it: the roster-table accessors `Game/fn_8044D328.c` (`lbl_804CBE94` is 9 ints; `lbl_804CB328` (43), `lbl_804CBEB8` (25) and `lbl_804CB14C` are arrays of 0x44-byte records with an int at `+0x40`, which accessors read and fill-loops set; its tail reaches the digit test `fn_8044D650`) and the menu-object accessors `Game/fn_8044D74C.c`, `Game/fn_8044D84C.c` (the object keeps 0xB0-byte slots from `+0x10`, a list owner at `+0x24`, and `fn_8044D84C` adds a 0x10-byte `Listener` entry to it) and `Game/fn_8044D934.cpp`; more registrar groups sit in the run (`Game/fn_8044D118.cpp` is the `int`-handler-returning-`int` one; `Game/fn_8044CEFC.cpp` is the `AptObject`-returning-handler one, converter `fn_8044D6A0` = `String f(const AptObject &)`; the `String`-to-`int` groups, `Game/fn_8044C054.cpp`, `Game/fn_8044C414.cpp`, `Game/fn_8044C6EC.cpp` (seven ints) and `Game/fn_8044CA9C.cpp` (two), share the parser chain `fn_8044C054`/`fn_8044C1B4`; its digit test `fn_8044D650` sits later in the run); the groups repeat per handler return type to 0x80457F54 and are pair-less. A group's converter (the `String` one is `fn_8044D6E8`, `String f(String)`) may sit later in the run, so declare it with `__asm__` rather than waiting for it. `AptObject`'s payload is a reference-counted pointer at `+0x0` (count in the pointee's first word; `fn_8044B950` increments, `fn_8044A108` releases), so `fn_8044B81C` (`__9AptObjectPv`) just stores it. |
| 3 | Character type ([`characters.md`](characters.md) sections 1, 5) | Done. `fn_8002623C` is matched (`Game/fn_8002623C.cpp`), which unblocks the rest of its file, to 0x80027D58. |
| 4 | Selection to spawn ([`characters.md`](characters.md) section 3) | Matched from 0x80448A28 to 0x8044AE3C. `fn_804436D4`, `fn_80445E50`, `fn_80445F70` and `fn_804464DC` are matched in units of their own. Notes on the run: `Game/fn_80448A28.cpp` holds two of the `String`-to-`String` helpers (these, `fn_80448FD0`, `fn_8044AA94` and `fn_8044AAE0` return a `String` by value; they are not constructors), then `Game/fn_80448B24.c`, `Game/fn_80448C18.cpp`, `Game/fn_80448CB0.cpp` (`String(int, char)`, the fill constructor), `Game/fn_80448DA0.cpp` (`IntToString`) and `Game/fn_80448FD0.cpp`; `Game/fn_80449084.cpp` to `Game/fn_8044ACEC.c` follow, with the constructors `String(const char *)`, `String(const String &)` and `String()` in `Game/fn_804493A0.cpp`, `Game/fn_804496F4.cpp` and `Game/fn_804498C8.cpp` (`Game/fn_80449EEC.cpp`, `Game/fn_8044A2D8.cpp` and `Game/fn_8044A5F4.cpp` leave their float pool in the original's `.rodata` through `extern_pool`, [`prodg.md`](prodg.md#inline-functions-and-the-tail-of-text); `Game/fn_8044A928.cpp` is the const `begin`/`end` pair and `Game/fn_8044A980.cpp` a pair-carrying file start; `Game/fn_8044AA94.cpp` holds the `const char *` helpers); the string code ends at 0x8044AE3C, where the APT registrars start (section 5 row 2) (the string class's destructor is `_._6String`, 0x80449298, hand-written C in `Game/fn_804491DC.c`; its layout is length `+0x0`, a second length `+0x4`, a 0x40-byte inline buffer at `+0x8` and the data pointer at `+0x48`, so an iterator is a `char *`; the iterator pair class is `{char *first; char *last}` with a ctor `fn_8044A61C`, symbol `__4IterPcT1`, `Iter` being a guessed name; the owner `fn_8044A880` holds a string at `+0x4`, a sub-object at `+0xC8` and 0x4C-byte strings at `+0xD0` (to `+0xA50`)); `Game/fn_80448364.c` is the glyph-quad layout `fn_80448364` and sprite quad `fn_804485AC`, with its pool 0x8048FCD8-0x8048FD18 left in place through `extern_pool`; `Game/fn_8044832C.cpp`, one `.cpp` method on the GX cache object, sits after `Game/fn_8044802C.c`; that one is the GX render-state cache setters, `self+0x4` Z-mode id, `+0x9` TEV stages, `+0xA` texgens, `+0xB` channels, `+0x12` indirect stages, `+0x44` color-update). No unit in the run is parked any more. The float pool at 0x8048CD14-0x8048CD74 cannot be claimed (it sits in another file's `.rodata`), so the older units read it through `extern`s and `Game/fn_804464DC.c`, `Game/fn_8044655C.cpp` and `Game/fn_80446ACC.c` through `extern_pool`. Past 0x80447378 the language varies per function: pair-carrying `.cpp` ones are `fn_80449B80` (a file start; its unit puts the setter line *after* it), `fn_8044A5B4` and `fn_8044A980` (file starts too); the rest are pair-less. A constructor ending `mr r3, r30` then `b .L` is a `.cpp` one and needs a mangled symbol name; a function ending `b .L` then `.L: mr r3, r30` is not a constructor: it returns a class by value ([`matching_notes.md`](matching_notes.md)); a destructor with the in-charge flag in `r30` is `.c` ([`matching_notes.md`](matching_notes.md)). `if (c) return 1; else return 0;` shows the `b`/`b` pair mid-function and is `.c`, not a pair-carrying file. The pool 0x8048E498-0x8048E4C8 is cyclic to claim too (`extern` literals, or `extern_pool` as in `Game/fn_80447A18.c`). `lbl_80628B00` is a 0x1010-byte queue of 0x20-byte entries with its count at `+0x1000`; its entry's `+0x8` and `+0x10` floats come from the unclaimed pool at 0x8048BF20-0x8048BF28. 0x804441A0-0x804457F4 is the same family: small pair-less `.c` methods (a delegate `{obj +0x8, delta +0xC, pfn +0x10}`, a slot object with flags at `+0x4`, mask at `+0x40`, id at `+0xE8`; a second object type has `unsigned short` flags words at `+0x4` and `+0x2C` (`+0x2C` bits 0x4, 0x70-0x3FF0, 0x400, 0x2000 seen; the `+0x4` word's 0x10-0x1000 bits are separate flags), `unsigned short` pair at `+0x24`/`+0x26` (0xFFFF = unset), a short at `+0x20`, bytes at `+0x22`, `+0x2A`, and a u16 at `+0x28` that indexes the 0x30-byte array at `fn_80430050(lbl_8052F060)+0x158`; a table at `+0x24` of 0x24-byte entries holds an `int[7]` at entry `+0x8`; another type keeps u16 indexes at `+0x0`, `+0x2` into a 0x60-byte array at `+0x154` of an object passed in or taken from `fn_80430050`). The Euler-angle matrix builder `fn_80445590` reads its literals (degrees-to-radians double, 0.0f, 1.0f at 0x8048B678-0x8048B688) from another unit's pool: claiming them is a cyclic dependency, so they are `extern`s. |
| 5 | `control.cpp`, 0x801040F4-0x80106B34 | Done. `Control_ChangeScreen`, `Locale_GetString`, `Global_PlayUISound`, `Global_PlayFEStream` and `Cheat_Enable`, which take a `String` by value, are units of their own in the file's run (they were parked until the hand-written destructor got its `_._6String` name), the rest is `Game/handlers/control.cpp` and `Game/fn_8010*.cpp`. The static initializer is `Game/fn_8010611C.cpp`. |
| 6 | `venuetable.cpp`, 0x8010BED8-0x8010C528 | Done: `Game/handlers/venuetable.cpp` (`GetVenueList`), `Game/fn_8010C090.cpp` (the other handlers) and `Game/fn_8010C338.cpp` (static initializer). `clashVenue_StartLevel` is `Game/fn_8010BFFC.cpp`, a unit of its own for the same reason as row 5's. |
| 7 | Last-selection module, 0x801317D8-0x80131E90 | Done: `Game/fn_801317D8.cpp`, the whole range. |
| 8 | `G`'s other methods | Done. 0x80431788-0x80435E28 is matched in units `Game/fn_80431788.c` .. `Game/fn_80435A00.c` (past 0x80433D20 pair-less `.c` Vector/matrix helpers and flag accessors; each run's float pool is read through `extern_pool`, and the pools are not contiguous, so each pool is its own unit: `fn_80433D20.c`, `fn_804340B8.c`, `fn_80434420.cpp`, `fn_80434864.c`; `fn_80434420` and `fn_80434BA4` are `.cpp` units because they dereference call results, ordinary C++ methods are not implied) (C++ handle classes `Link` and `Cue`, vtables `lbl_804F3148` and `lbl_804F2E10`, names guessed; `Link` is `{impl +0x0, vptr +0x4}`, its implementation's vtable slots 1 and 2 (offsets 0x10, 0x18) are `Link::get` and `Link::release`; the implementation constructors `LinkImpl`, `LinkImplB`, `CueImpl` have the shape of `Impl` in `Game/fn_80444034.cpp`, each over its own base constructor `__8LinkBase`/`__7CueBase`; `LinkImpl`/`LinkImplB` hold `owner` at `+0x8` and a member-function pointer `{short delta; short index; void *pfn}` at `+0xC`, which their `invoke` calls on `owner + delta`, and the result of `fn_8042A400` at `+0x14`). The 0x14-byte list entry `ListEntry` (`__9ListEntry`, over `__9EntryBase`) keeps its vptr at `+0xC` and its value at `+0x10`; `CueImpl`'s `+0x8` word is called as a function pointer by its slot-2 method, so it is a callback, not a name. `fn_80433B94` and `fn_80433CF0` are vtable destructors (`fn_80433B94` ignores its flag and calls `fn_80433CF0(self, 0)`, which stores `EntryBase`'s vptr `lbl_804F31F8` at `+0xC`); `fn_80433BD4` (`__8LoadList`, guessed name) is the constructor of the 0x38-byte object at `CAsyncLoader+0x8`, with a subobject at `+0x1C` (`fn_8023E144`/`fn_8023E2FC`). `Placement` (`__9Placement`, guessed name; `Game/fn_80434DB4.cpp`) has Vectors at `+0x10` and `+0x20` and a handle at `+0x30` that `fn_80435340` reads; the accessors after it (`Game/fn_80434E0C.c`) are not all on `Placement`: a float and a flags word both at `+0x4` (bits 0x1, 0x40-0x100, 0x200 inverted, 0x10000-0x200000 tested), and `+0x2A0` pointing at an object with floats at `+0x10`-`+0x18`. `Game/fn_80435280.c` starts with a 4x4 float matrix element accessor and the quaternion `{x,y,z,w}` element accessor and setter (`fn_804352C8`, `fn_80435300`; used by `fn_804467B0`). `Game/fn_804353CC.cpp` holds three constructors with guessed class names: `Locator` (Vector at `+0x20`), `Pose` (`__4Pose`, 0xD0 bytes, `fn_8042D7B0` object at `+0x10`, Vectors at `+0x50`, `+0x60`; array-constructed 256 times) and `VectorPair` (`__10VectorPair`, 0x30 bytes, Vectors at `+0x0`, `+0x10`; array-constructed 8 times). `Game/fn_804354B8.c` onward holds Vector/`Mat4` helpers (row-vector 4x4 product `fn_80435A00`; `fn_804358A4`/`fn_80435904` step the LCG seed `lbl_8066C710`, a 0xC-byte `.sdata` object; getters at `+0x470`, `+0x474`, `+0x778` of an object not yet identified; its float pools are read through `extern_pool`, one unit per pool). `Game/fn_80435E68.cpp` to `Game/fn_80435F70.cpp` hold constructors with guessed class names (`Shape` over `ShapeBase`, whose base keeps a float at `+0x0` and vptr `lbl_804F3318` at `+0x4`; `Shape`'s vptr is `lbl_804F3240`, with `fn_80434988` objects at `+0x20`, `+0x30`, `+0x50`; the destructor `fn_80435F1C` is hand-written C; `Segment` is a Vector pair like `VectorPair`, called from `fn_80445C98`). `Game/fn_80436000.c` to `Game/fn_80436BAC.c` (0x80436000-0x80436D5C) are pair-less Vec4/quaternion/box helpers; `fn_80436878` is the one `.cpp` unit (store through call result). The class at `fn_80436AE8` has a plane array pointer at `+0x20` (16-byte `{x,y,z,d}`) and a `u8` count at `+0x17`; `fn_804369DC`/`fn_80436A54` index a table of 8-byte entries at `+0x2C` (3 pointers), a 12-byte point array at `+0x38` and an int array at `+0x40`. The plane-set methods end at `fn_80436BAC`, a segment clip that shortens `*t` against each plane. `Game/fn_80436D88.cpp` (0x80436D88-0x80436EBC) holds `ShapeData` (`__9ShapeData`, guessed name; constructs a `fn_80434988` object at `+0x0`, then `fn_804384D8`), `ShapeBase`'s `operator delete` `fn_80436DD0` (calls vtable slot 5, entry `+0x30`, of the object `fn_802E29A8` returns, with `(p, 8, 0x1C)`; that object's vptr is at `+0x3C`) and `ShapeBase` (`float` `+0x0` set to FLT_MAX by `fn_80436E44`, vptr `+0x4`); its destructor is `Game/fn_80436EBC.c`. `Game/fn_80436F10.c` .. `Game/fn_80437378.cpp` (0x80436F10-0x80437B60) are matched: a `ShapeBase`-family destructor `fn_80436F3C` (vptr `lbl_804F32F8`, pool 0x80486864), the `Body` family (`Body` `fn_80438630`, a 0x88-byte object copied from a pointer, then `BodyA`/`BodyB`/`BodyC` set their vptr at `+0x88` and a `Placement` at `+0x90` (`BodyC`: `+0xA0`); `BodyC` has two setters at `+0x90`/`+0x94` and a word at `+0xE0`; all guessed names), the 0x30-byte `Entry` queue at `+0x40` of an object with its count at `+0x1840` (limit 0x80, overflow goes to `fn_8004E3C4`) and `lbl_8066B7D0`, an `.sdata` word that `fn_804378CC` bumps and a stamp at `+0xD8` of each 0x1C0-byte slot copies. `Game/fn_80437B60.cpp` (0x80437B60-0x80437E50) is matched: it reads an actor object `A` (`fn_8032A228(A)` returns a derived-class pointer to the sub-object at `A+0x14`, whose base has a `+0x8` word read by `fn_80436728`; `fn_80435340` of it is the handle object, vptr at `+0x0`, vtable entries `+0x18` (returns the kind, 0x18 / 4 seen), `+0x30` (variadic, returns an 8-byte result by value) and `+0x38`), a `Body` (vptr `+0x88`, entries `+0x8` and `+0x18`), a 0x30-byte `ShapeDataPair` and a 0x20-byte `ShapeData`; `fn_804385B0` is the 0x40-byte `Placement` constructor (`__9PlacementPvN21ii`). `fn_80437E50` (0x1F4: handle object's entry `+0x18` tested against 4, a radius from `fn_802EA5D8` squared against `fn_804341BC` of a Vector from `fn_80318E90`, then a `ShapeData`/`Placement` pair as in `fn_80437B60`, which it tail-calls with flag 0) is claimed in `Game/fn_80437B60.cpp` at 99.0%, stuck on register numbers ([`nonmatching.md`](nonmatching.md)); the unit's range stops at 0x80438044. `Game/fn_80438044.cpp` has the pair set only after its first function; its skip filter `fn_8043810C` reads `G+0x28` flags (bits 0x4, 0x200, 0x400, 0x800 tested), a handle at `+0x30` and the `+0x1848` mask by `fn_800B0BEC` index. `Game/fn_80438044.cpp` runs on to 0x804390AC (pool 0x80486894 through `extern_pool`; `fn_804384A8` a `char` at `+0x4`, `fn_804384D8` stores 1.0f at `+0x14` of `ShapeData`; `ShapeBaseB` (`__10ShapeBaseB`, guessed name) is `ShapeBase`'s sibling with vptr `lbl_804F32F8`, its float at `+0x0` set by `fn_80436F94`; `G+0x28` bits 0x100 and 0x1000 are tested by `fn_80438550`/`fn_80438580`). The unit ends with the 0x40-byte `Placement` constructor `fn_804385B0` (calls `fn_80437210` on it; parameters need `register`) and `Body` `fn_80438630`: two 0x40-byte copies of `*src` at `+0x0`/`+0x40`, words at `+0x80`/`+0x84` cleared, vptr `lbl_804F3338` at `+0x88`. The `Body` accessors that follow (`fn_80438780`-`fn_80438900`) read `+0x80`/`+0x84` (flag and result words), `+0x90`/`+0xA0` placements and `+0xE0`; for `BodyC`, `+0x90` is a callback `int (*)(self, v, +0x94 arg, int *a, int *b)` that `fn_80438B5C` calls (`+0x80` set to 1, result to `+0x84`, `v` copied to `+0xA0` if `*a`), and `fn_80438A54`/`fn_804389A8` copy a 0x40-byte chunk to `+0x90`. A 0x30-byte-stride `Vector` triple at `+0x0`/`+0x10`/`+0x20` with a float at `+0x30` is set by `fn_80438928`/`fn_80438D94` (calling `fn_80429090`); `+0x40` is a sub-object whose `+0x30` float `fn_80438D68` reads. `fn_80438CC8` is a reciprocal square root, the pool 0x804868A0-0x804868A8 (0.0, 0.5, 3.0). `fn_80438EA4` byte-swaps a `{u32; u16[4]}` header. `Attr` (`__4Attrii`/`__4AttriPCc`, `chain__C4AttrRC4Attr`; names guessed; `Game/fn_80439AB4.cpp`) is a 12-byte `{a, b, link}` descriptor chained into a list; `fn_80438FAC` builds four and passes the chain to `fn_801B0C90`. `Streamer` (`__8Streamer`, guessed name; `Game/fn_80438044.cpp` ends with its constructor at 0x804390AC) owns a 0x72A8-byte buffer at `+0x30` (`fn_80439DCC` allocates it, `fn_80439E3C` frees it, both adjusting the `.sdata` total `lbl_8066B7FC`), two 0x14-byte `Slot`s at `+0x34` (`__4Slot`, `Game/fn_80439AB4.cpp`, five zeroed words; `+0xC`/`+0x10` point at `+0x28`/`+0x2C`), and ints at `+0x5C`-`+0x74` (`+0x6C` starts 1, `+0x70` is polled by the update method; meanings guessed). `Game/fn_804391E0.c` (0x804391E0-0x804396F8) holds its destructor, teardown, update method `fn_804392C0` and the cutscene-load helpers, hand-written C. `self+0x28` is a file handle (`fn_80439390` returns while it is set), `+0x30` the 0x72A8-byte buffer, whose header has a count at `+0x8`, a second count at `+0xC` and a table pointer at `+0x18C`; `+0x5C`/`+0x60` count the two slots' refills; `+0x6C`/`+0x70`/`+0x74` are the start, done and ready flags (guessed). The load path is built from `"Cutscenes/%s"` of `self+0xC` plus `"cut"`; the queues are `lbl_805431EC`/`..208`/`..224`/`..240`. `fn_804396F8` (`Game/fn_804396F8.c`) is `NonMatching` ([`nonmatching.md`](nonmatching.md)). `Game/fn_80439778.c` (the load-complete step, 0x80439778-0x80439AB4; `self+0x8` is the read handle, cleared at the end) lays out the buffer after its 0x198-byte header: `a` words at `+0x18C` (byte-swapped here; each must be <= 0x4B001), `b` 0x90-byte records at `+0x190`, a second `a`-word table at `+0x194`; the header's `+0x0` is the magic 0x2715. `fn_80439AB4` (`Game/fn_80439AB4.cpp`) is a `Cue`-vtable handle that owns a 0x18-byte implementation, `fn_8043A0A4` (vptr `lbl_804F3360`, owner `+0x8`, name `+0xC`, result `+0x14`; both guessed names, symbols renamed). `fn_80439C24` (calls `fn_8043A348` then `fn_8043A278` on a `Slot`) is the per-slot teardown that the teardown `fn_80439230` runs over both slots. The unit's pair flag is cleared by `fn_80439C64`'s `case`, so `fn_80439D2C` (the `Slot` setup the update method runs) carries the pair; `fn_80439D88` (`Streamer`'s `operator delete`) is pair-less, so it is a `.c` unit of its own, as are the buffer allocate/free methods after it (`Game/fn_80439DCC.c` is the allocator; its file string is `lbl_80486C78`, left unclaimed). `fn_80439E94` (`Game/fn_80439E94.c`) takes the cutscene path from `fn_80439390`; the handle it stores at `+0x4` is a request that `fn_80241C58` gets a completion callback for. `fn_80439F7C` (`Game/fn_80439E94.c`) is the teardown wait: it releases the handle at `+0x4`, waits out the file at `+0x8`, spins on the `+0x70` done flag while `+0x6C` is 0, then calls `fn_8023E5E4(queue, self)` on the four queues until one returns nonzero (guess: remove). `OwnedCueImpl` is `Game/fn_8043A0A4.cpp` (constructor, destructor `fn_8043A120`, an `extern "C"` function taking `register` parameters like `fn_8043392C`), over `CueBase` (`__7CueBase`, whose `+0x0` word the base sets); its slots 1 and 2 are `Game/fn_8043A16C.cpp`, a new file start (pair-carrying, no `sn_return_decl`; `invoke` has an explicit `return;`), and `name` is a `Pmf` there, like `LinkImpl`'s. `Slot` (`+0x0` read handle, `+0x4` buffer, `+0x8` its size, `+0xC`/`+0x10` pointers to the owner's source-offset and running-total ints) is allocated, freed, read-started and released (`fn_8043A348`, waits out the handle at `+0x0`) by `Game/fn_8043A20C.c` (pair-less; string `lbl_80486C18` left unclaimed). `Game/fn_8043A3BC.cpp` holds the 0x50-byte `Element` constructor and `ElementSet` (`__10ElementSet`, guessed name: base constructor `fn_8042D7B0` over a 0xB0-byte base, 64 `Element`s at `+0xB0`; the base is `Root` with the constructor aliased by `__asm__` since `Element` and `Pose` call it by its C name). `Mat4`'s copy constructor (`__4Mat4RC4Mat4`, 0x40-byte `memcpy`; callers copy at `+0x50` of 0x90-byte records) and `Vec4` (`__4Vec4`, guessed name: `{1, 0, 0, 0}`; pool 0x80486F70-0x80486F78 through `extern_pool`) close it. `Marker` (`__6Marker`, guessed name) is a `Root`-based constructor with two `Vector`s at `+0x60`, `+0x70`, an int at `+0x40`, floats 0.0 at `+0x44` and 30.0 at `+0x50`. 0x8043A71C is a new file start (its first function has the pair, the run before it does not): `Game/fn_8043A71C.cpp` (0x8043A71C-0x8043AB4C) is flag-bit getters on three object types (flags words at `+0x4` and `+0x464`, a halfword at `+0x7E`; guesses, not `G`) and empty stubs, then `Movie` (guessed name; 0x2C bytes, callback `fn_801022E4` at `+0x24`, id at `+0x10`, constructor in the same unit, destructor hand-written C in `Game/fn_8043ABD0.c`). 0x8043AC1C-0x8043C134 is one pair-less run of `.c` units (Vec4/flag accessors) with two `.cpp` units inside it for a class returned by value (`Game/fn_8043B3DC.cpp`) and stores through call results (`Game/fn_8043BC48.cpp`); the float pool from 0x804873AC is read through `extern_pool`, one unit per run of literals. `Game/fn_8043A3BC.cpp`'s six methods before the concat act on classes of unknown identity. 0x8043C134-0x8043C1EC are two `if`/`else` forwarders on `.sdata` words `lbl_8066B834`/`lbl_8066B840`, the end of the pair-less run; 0x8043C1EC is a file start (pair-carrying, `Game/fn_8043C1EC.cpp`). `Game/fn_8043C1EC.cpp` runs to 0x8043CCAC (the file's constructors set the return flag, so the accessors after them are pair-less; `fn_8043CA98` carries the pair again, so the setter line sits after it; its pool 0x804873B4 is read through `extern_pool`, and `fn_8043CCAC`'s literal at 0x804873D0 is a unit of its own, `Game/fn_8043CCAC.c`). Layouts seen: `fn_8043C3C0` reads a kind byte from a table at `+0x4` of an object (0x18-byte records from `+0x20`, byte `+0xB`, indexed by the byte at `+0x3D`); `ObjA`/`ObjB` (`__4ObjA`/`__4ObjB`, guessed names, 0xFC/0x120 bytes, `new`ed by `fn_8043C514`/`fn_8043C5A4`) set a table pointer at `+0x58` and an int at `+0x5C` over a base constructor each; `fn_8043CA98` tests whether a handle's slot-2 result is 2, 12, 13 or 16. `Game/fn_8043CD50.c` (0x8043CD50-0x8043CFDC) is the next pair-less run. `Game/fn_8043CFDC.cpp` (0x8043CFDC-0x8043D120) holds `Byte1(char)` and an allocate/free pair through slots 4 and 5 of the heap object `fn_802E29A8` returns (block header: `u16` size at `+0x4`, alignment 0x12); `Game/fn_8043D120.c` is a hand-written-C destructor that frees through it. `Game/fn_8043D180.cpp` (0x8043D180-0x8043D544) is one pair-less file whose first function is an empty stub, so `sn_return_decl` goes at the very top; `__6Holder` stores the vptr `lbl_804F4438` that `fn_8043D120`'s destructor resets, over the base constructor `fn_8043F69C` (vptr `lbl_804F4510` at `+0x0`); `fn_8043D28C(self, col, row)` returns the address of a 4x4 float matrix element and `fn_8043D2EC` sets its diagonal after `fn_8043C84C`. `Game/fn_8043D544.c` (0x8043D544-0x8043D65C) is the last pair-less run before a new file: 0x8043D65C carries the pair again (file start, `.cpp`). 0x8043D65C-0x80442010 is the growable-array family and the heap blocks it frees: an array is `{data +0x0, count +0x4, capacity +0x8}`, capacity starts at 0x80000000 (bit 31 set = storage not owned, low 30 bits = capacity), and blocks are freed through slot 5 (`+0x30`) of the heap object `fn_802E29A8` returns, with a size tag (0x12, 0x14, 0x24, 0x25, 0x26 seen, one per class). Pair resets, so file starts, at 0x8043D65C, 0x8043F490, 0x80440148, 0x804408F8, 0x80441AD8 and 0x80441C54. Only `fn_8043E148` is `NonMatching` ([`nonmatching.md`](nonmatching.md)); row 8 is otherwise done, up to the string code of row 4. Before the first unit, `fn_80431728` clears the word at `+0x40` of seven 0x44-byte entries at `lbl_804CB14C`. Layout so far (object not confirmed to be `G`; guesses): `+0x1848` is a bit mask (`fn_80434CDC` clears bit n, `fn_80434C88` sets all), `+0x590` the active slot count (confirmed for `G`), `+0x750` an object tested before `fn_8042FF2C`; `lbl_8066C63C` points at a table with `float f[][2]` at `+0xC`. |
| 9 | Readers of the match fields | `fn_80028BAC`, `fn_8002BD34`, `fn_80131434`, `fn_8011A94C`, `fn_8011AB34`, and what they lead to. This is where the game leaves the menus. |

Out of scope for versus: `memcard.cpp` (except whether saves depend on the roster size,
[`characters.md`](characters.md) section 2), `feonline.cpp`, `mission.cpp`, and third-party code
(Havok `hk*`, RealCore, RealGraph).

### Step 4: files and boundaries

Only what costs disassembly to re-derive. What a matched function *does* is in its source file.

- **0x80442010-0x80443E9C** is a long run of leaf accessors with `register` parameters: plain C
  despite acting on a slot, so the branch pair mostly does not block this step. It is not one source
  file — 0x80443908-0x804439E8 carries the pair between two pair-less runs — so let each function's
  trailing-branch count pick the language ([`matching_notes.md`](matching_notes.md)). Forwards it
  stops at 0x80443E9C, where a run of C++ handle classes starts: a constructor that stores a vptr
  (+0x4) and `new`s a 0x18-byte implementation object into +0x0, the implementation's constructor
  `fn_80444034` and more of the same. Between them sit pair-less `.c` units (list-broadcast loops,
  then the vtable-slot-2 forwarders `fn_804440B0` and `fn_8044412C`, whose 8-byte entries are
  written as a hand-made `VEntry` struct since a `.c` unit has no `virtual`), so the `.cpp` handle
  unit is interleaved with `.c` ones. `fn_8042841C` is an identical instantiation
  for another type, sharing the vtable `lbl_804F2E28`. `fn_804436D4` is
  `Game/fn_804436D4.cpp`, a `.cpp` unit because it binds its records to reference locals.
- **What those accessors act on**, in address order: a 0x30-byte descriptor `fn_8008A010` builds on
  its stack; the globals object `lbl_80593BE8` (two RNG seeds at +0x4 and +0x8, frame time in ms at
  +0xC, loading flag at +0x5C); the object `fn_8009AD80` returns for an actor; the name table at
  `fn_804326B4(lbl_8054EF38)`, whose layout is [`characters.md`](characters.md) section 4; then the
  player slots and `G`. That name-table object is filled from an `.nsc` script by `fn_800887AC`, not
  from a `.nvb` record, and the object that *owns* those records keeps its own int flags at `+0x1AC`
  (not the `actor+0x1AC` of [`characters.md`](characters.md) section 5).
- **`GameFlow` is split across four source files.** The pair's flag resets at each file edge, which fixes every
  boundary below to the instruction ([`nonmatching.md`](nonmatching.md)):

  | Range | Pair? | Unit | Left to do |
  |---|---|---|---|
  | 0x800B43F0-0x800B5BC4 | pair-less | `Game/fn_800B43F0.cpp`, `Game/fn_800B46B0.c`, `Game/fn_800B4AB8.cpp`, `Game/fn_800B4CF8.c` | Done. `fn_800B4AB8` (`OnPadRemoved`) is a `.cpp` unit with the setter line, as are the constructor and destructor; the rest is the `.c` workaround. Pair-less is settled for the whole file: no function in it has more than one trailing branch except `fn_800B47C0`, whose two are two `return;` statements. |
  | 0x800B5BC4-0x800B7094 | carries it | `Game/fn_800B5BC4.cpp` | Done. |
  | 0x800B7094-0x800B7204 | pair-less | `Game/fn_800B7094.c` | Done; globals only. |
  | 0x800B7204-0x800B869C | pair-less | `Game/fn_800B7204.c` | Done; 40 per-command methods. |

  Two `.rodata` facts about that first file: the nine floats at 0x8048BD44-0x8048BD68 belong to no
  function in it, so one was dead-stripped between the destructor and `fn_800B47C0`; and
  `Game/fn_800B46B0.c` has to define `fn_800B5124`'s format string at 0x8048BD9C to keep its own
  claim 8-aligned ([`matching_notes.md`](matching_notes.md)), so `Game/fn_800B4CF8.c` references it
  as an `extern` and claims only the float pool after it (0x8048BDB8-0x8048BDC4).

  0x800B43F0 is a confirmed file *start*: `fn_800B43AC` is the previous file's `_GLOBAL_.I`, with its
  `.ctors` word at 0x80482624. The first file is where the entity name should lead to the model, motion set and NVB loads.

## 6. The `GameFlow` Command Dispatcher

`RunCommand__8GameFlow` (0x800B5BC4) is a per-frame command dispatcher, called from `fn_800B5988`
once a frame. The single instance is `lbl_80552920` (`.bss`), which `fn_8002B9F0`'s main loop drives
directly. It runs only while `fn_8012D470()` (the `lbl_8066BE94` flag) is set and `this+0x158` is
clear, then switches on the pending command at `this+0x20` (`unsigned`): 71 case values in 0-0x5B
plus an empty `default`, most arms one call on `this`. So the class owns some 50 per-command methods
in 0x800B6AA4-0x800B869C, and that `switch` is the command-to-method map.

Two of them carry 20 of the arms: `fn_800B6B34(this, n, 1)` with `n` in 1-0x21, followed by `fn_800B6E44(this, 0)`. They read as "open screen `n`" and "go to state `n`", which would make the second argument of each a screen or state id rather than a command.

**The commands that name data are debug commands**, which is what identifies the object:

| Command | What it does |
|---|---|
| 0x50, 0x51 | `fn_8009543C(G, this+0x280, "plr_wolverine"` / `"plr_ironman")`, then `fn_80096268` on the entity's actor: spawn a player |
| 0x52-0x55 | `fn_8002D7A8(lbl_8052F060, name, 8, 0, 0, 0)` for `"powerplant"`, `"0_Test_Clash"`, `"0_Test_Arena"`, `"0_Test_Look"`: load a level |
| 0x56, 0x57 | `fn_80128C3C("example1"` / `"example2")` |
| 0x58 | `fn_8002DB78(lbl_8052F060)` |

`"0_Test_Arena"` is the level name `fn_80114420` tests `G+0x59C` against ([`characters.md`](characters.md#5-code-that-lists-characters)), so `lbl_8052F060` (`.bss`, 0x3E0) is the level or world object and `fn_8002D7A8` loads a level by name. These two are a way into the load path without going through the menus.

Ahead of the switch, five command **ranges** go to one handler each, so the id space is wider than the menu: 0x34-0x38 to `fn_800B7204`; 0x39-0x3D to `fn_800B6B34(this, 4, 1)` with `this+0x1BC = command - 5`; 0x2F-0x33 to `fn_800B7268`; and 0x25E-0x35E, 0x35F-0x45F, 0x460-0x560 and 0x561-0x661 to `fn_800B7584`, `fn_800B743C`, `fn_800B74C4` and `fn_800B73C4`.

`Update__8GameFlow` (0x800B678C) is the flow's per-frame tick, not part of the dispatcher: the
main loop calls it on `lbl_80552920` once a frame (0x8002C0C8), gated on `+0x68` of its own object.
It runs the paused path while `+0x1C & 1` is set, then `fn_800B5124(this)` (which ends the frame when
it returns nonzero), `DrawFrameRate` when `+0x1E0 == 1`, and `fn_800B47C0(this)`.

Three more of the class's methods, same unit: `DrawFrameRate__8GameFlow` (0x800B689C) draws the FPS
readout from the globals object's frame time at `lbl_80593BE8+0xC`, and
`SetLoadProgress__8GameFlowfi` (0x800B69D4) forwards to `DrawLoadProgress__8GameFlowii`
(0x800B6A30), whose body the release stripped. The level loader calls `SetLoadProgress(fraction, 1)`
with 0.0, 0.05, 0.5 and 1.0 as a level loads (0x8002C6F0 onwards, plus 0x8009B6A4 and 0x800B2A50),
so the progress bar `Control_StartProgressBar` sets up is driven from here.

`lbl_8066D6DC` (`.sbss`) is the overlay text object every one of these prints through: `fn_80426E88`
swaps its font at `+0x18` and returns the old one, `fn_80101188` sets its height at `+0x40`, and
`fn_800B92DC(&lbl_8066D6DC, text, x, y)` positions it, sets the string and draws. The debug overlay
at 0x80132480 uses the same object the same way.

### The command queue and the load path

Fourteen more of the class's methods are **matched** in the same unit. They are the queue `RunCommand` drains and the level-load entry points:

| Method | Address | What it does |
|---|---|---|
| `SetCommand(int)` | 0x800B6E44 | Sets `+0x180 = 0xFF`, calls `Stub6E1C`, `fn_8012873C` and `fn_801284D4`, then stores the command at `+0x20`. Returns 0 for command 0; otherwise pushes the command onto the history at `+0x1A0` (unless it is 6) and returns 1. **113 call sites**, `control.cpp` among them, so this is how the whole game queues a command. |
| `SetCommandBlocking(int)` | 0x800B6F24 | `SetCommand` plus `+0x158 = 1` (which blocks dispatch) and `fn_8043323C(lbl_805722E8, 1)`. `control.cpp` picks it over `SetCommand` for commands 1, 2 and 8. |
| `GetHistory(unsigned char)` | 0x800B6F90 | Returns `history[index]`. |
| `ClearCommandHistory()` | 0x800B6D74 | Zeroes `history[0..4]` and the 34 ints at `+0x1F8`. |
| `OpenScreen(int, int)` | 0x800B6B34 | `+0x28 = screen`, then `ClearPendingScreen()` when `fn_80432D74(this)` is set or the second argument is 0. 29 call sites, 20 of them `RunCommand` arms. |
| `ClearPendingScreen()` | 0x800B6AF8 | Zeroes `+0x28` if it is set. |
| `BeginLoad()` | 0x800B6A60 | `+0x1C = 3`, then `fn_801AA368()`. The head of both load paths. |
| `EndLoad()` | 0x800B6AA4 | `fn_8044606C(this)` (`+0x1DC = 0`), `+0x1C = 4`, then clears the globals' loading flag (`fn_804325CC(lbl_80593BE8)`). |
| `LoadLevel(char *)` | 0x800B6BA8 | `BeginLoad()`, sets the loading flag, `fn_8002F884(lbl_8052F060, 5)`, copies the name into `+0x2C` (empties it when the argument is null), then `SetCommand(0x42)`. |
| `LoadFrontend()` | 0x800B6C3C | The same without a name: `SetCommand(8)` then `fn_8012D400(0)`. |
| `EndLevel(int)` | 0x800B6CAC | `fn_8002D90C(lbl_8052F060, "LATER")`, which sets `G+0x760 = 0xF` after a 3000 ms timer; the other mode string is at `lbl_80485888`. Its argument is unused. |
| `Stub6CFC(int, void *)` | 0x800B6CFC | `return index >= 0;`. The caller passes `command - 0x561` and `lbl_805526AC`, so the body the release stripped indexed something by command. |
| `Stub6D48()`, `Stub6E1C()` | 0x800B6D48, 0x800B6E1C | Empty; both stripped. `SetCommand` calls `Stub6E1C` first. |

Fields of the class, types confirmed, meanings guessed. The instance `lbl_80552920` is 0x2A0 bytes:
`+0xC` int (the default result of `fn_800B4FC0`, which forces 0 or 1 from other state), `+0x14` int (set to 1 by command 0x3E, cleared by 0x43 and 0x4A), `+0x1C` `unsigned char` of
single-bit flags (bits 0x1, 0x2, 0x4 and 0x8 are each tested on their own, 0x1 by `Update`), though
`BeginLoad` and `EndLoad` assign it the whole values 3 and 4, so it may be a small state instead (`fn_800B5930` tests `& 4`, the bit `EndLoad` sets, before it starts the 0x3E frontend load; guess: "not loading"),
`+0x20` the command, `+0x28` int the pending screen, `+0x2C` `char[0x100]` the level name,
`+0x12C` int zeroed on every call, `+0x134` int, `+0x138` int handle (created lazily by `fn_801969CC`, ticked by `fn_80196BF0` every `Update`), `+0x158` int that blocks
dispatch, `+0x180` int set to 0xFF by `SetCommand`, `+0x1A0` `int[5]` the command history with the
most recent first, `+0x1BC` int, `+0x1C0` int (read by `fn_80432D74`), `+0x1DC` int (zeroed by
`fn_8044606C`), `+0x1E0` int compared against 1, `+0x1F8` `int[0x22]`, `+0x280` int (the second
argument of the player spawn), `+0x4` int set while any pad is unplugged, `+0x8` int set alongside `fn_801AF754(globals)`, `+0x160` int, the pad port `fn_800B56DC` records for the slot it picks (`fn_80442624(slot)`, the value `fn_800B4CF8` compares against the inserted port), `+0x164` that slot's index (`fn_800B56DC` zeroes `+0x13C` and calls `fn_800B5930`), `+0x284` int count and `int[2]` at `+0x288` the player indices whose pad is unplugged (-1 when empty; the constructor and `fn_800B4F50` fill it).
`GameFlow` and every method name above are **this project's names**: they are not in the DOL, so
renaming any of them means redoing the mangled symbol. `Stub<addr>` marks a method whose body the
release build stripped.

### The constructor, destructor and teardown (0x800B43F0-0x800B47C0)

`__8GameFlow` and `_._8GameFlow` are the class's own field list, so between them they settle the
types of 50 fields; the assignments themselves are `src/Game/fn_800B43F0.cpp`. All are `int` except
`+0x0` and `+0x18` (floats set to -1.0f; `+0x0` is the timer `fn_800B5A08` drains by the frame time, `fn_8042E998(lbl_80593BE8)`, and zeroes on pad input), `+0x184`/`+0x188` (floats set to 0.0f) and `+0x1F4`
(`unsigned char`). `+0x18C`-`+0x19C` is a member subobject constructed through `fn_80430728`, whose
body is empty, so this unit never has to name its class; `+0x19C` is an `int` handle that `fn_800B5548`
releases through `fn_80232B78` like `+0x16C`. Only the static initializer of
`Game/fn_800B7094.c` constructs or destroys the object, the destructor as `(&obj, 2)`.

The four teardown methods after them are `Game/fn_800B46B0.c`; `fn_800B4764` is called from
0x800B590C rather than from the destructor. Fields they settle, all `int`: `+0x10` a flag
`fn_800B4764` gates the loading-flag clear on, `+0x16C` a handle `fn_80232B78` releases, `+0x178` a
flag paired with the globals' loading flag (`fn_804325CC(lbl_80593BE8)`, the same call `EndLoad`
makes), and `+0x1D8` a flag the teardown zeroes. `+0x170` and `+0x174` are **pointers** to the two
players' loading-screen images (`u16` width at `+0x58`, height at `+0x5A`), so the constructor's
zeroes there are null pointers rather than ints; `fn_800B47C0` is that screen's per-frame draw and
runs only while `+0x178` and both images are set.

### The per-command methods (0x800B7204-0x800B869C)

The file after the globals file is **matched** in full as `Game/fn_800B7204.c`: 40 of the methods
`RunCommand` dispatches to, plus the file's `__static_initialization_and_destruction_0` and its
`_GLOBAL_.I`. It is pair-less C++ with nothing C++-only in it, so the whole file matches as one
`.c` unit with `this` as a `register` first parameter ([`matching_notes.md`](matching_notes.md)).
dtk's `fn_800B8594` / `fn_800B8660` are renamed `GameFlowCmdStaticInit` / `GameFlowCmdGlobalInit`.
The other 40 keep their `fn_` names: they are `GameFlow` methods, but nothing in the DOL names them.

The command-to-method map, completing the switch above (`N` after a name is the value the method
passes to `fn_80446094`, which sets `this+0x17C`):

| Command | Method | What it does |
|---|---|---|
| 0x01, 0x02, 0x04, 0x05 | `fn_800B7D6C` (3), `fn_800B7DB0` (6), `fn_800B7D28` (8), `fn_800B7DF4` (0xA) | `fn_80446094(this, N)` then the shared `fn_800B7C98` |
| 0x08 | `fn_800B7E38` | the same with N = 5 or 4, on `fn_8042D444` of the script table |
| 0x06, 0x4F | `fn_800B84F4`, `fn_800B8544` | `fn_8002ABCC(lbl_8066B690)`, then command 0xB / 0x44 |
| 0x10 | `fn_800B72B4` | if any of ports 0-4 answers `fn_8002B2C4`, open screen 0x1C; else replay history |
| 0x14 | `fn_800B76C0` | **the level load** (below) |
| 0x15 | `fn_800B7C50` | `fn_8002FA70(level)` |
| 0x18 | `fn_800B7654` | command 0x1A when `+0x1F4 != 0xFF`, else 0x14 |
| 0x1C-0x22 | `fn_800B7EA4`, `fn_800B7F04`, `fn_800B80E0`, `fn_800B7F64`, `fn_800B7FC4`, `fn_800B8024`, `fn_800B8084` | option toggles on `lbl_8066B690`: each reads a getter and writes `!it` back through the matching setter |
| 0x27 | `fn_800B81D0` | `+0x144 = 0`, `fn_800871A8()`, `fn_8002A418()` |
| 0x28 | `fn_800B8210` | `fn_800B81D0` then screen 0x12, or command 0x26 with `+0x1BC = 0x10` |
| 0x29, 0x2B | `fn_800B8290` | releases `lbl_8066B694` then `lbl_8066B690` through `fn_8043206C`, one per call; returns 0 (and queues 0x23) when both are already null |
| 0x2A, 0x2C | `fn_800B8408`, `fn_800B831C` | screen 0x13 / 0x14 and `+0x1BC = 0x2A` / `0x2C`, gated on `lbl_8066B694`, `lbl_8066B690` and `fn_801B6A44(lbl_8066B698)` |
| 0x2D | `fn_800B7BD4` | `fn_8002A418()`, then screen 0x16 or command 0x26 with `+0x1BC = 0x2D` |
| 0x2E | `fn_800B7514` | `fn_8002A7D0` on item `+0x1C4` of `lbl_8066B698`, then the command at history slot 3 |
| 0x2F-0x33 | `fn_800B7268` | `+0x1F4 = command - 0x2F`, then command 0x18 |
| 0x34-0x38 | `fn_800B7204` | `fn_8002B27C(lbl_8066B690, command - 0x34)`, `fn_8002ABCC`, then command 0x40 |
| 0x3E, 0x3F, 0x42 | `fn_800B7894` (0, 1, 2) | **the frontend load**: `fn_8043323C(lbl_80571EA4, 1)`, `BeginLoad`, the loading flag, `fn_8002F884(level, 5)`, command 0x40, then `fn_80128C3C("mainBE")` and `BeginLoad` again |
| 0x43 | `fn_800B7918` | `EndLoad`, `fn_8002F884(level, 3)`, command 0, `fn_8043323C(lbl_80571EA4, 0)` |
| 0x45, 0x46 | `fn_800B7A0C`, `fn_800B797C` | `EndLoad` paths; `fn_800B797C` also runs `fn_8043AB30()` and `fn_801127E0()` first |
| 0x4A | `fn_800B7AA4` | clears the two role indices (`fn_804317F4`/`fn_8043181C` on `G`), `fn_8002F884(level, 2)`, command 1 |
| 0x4B | `fn_800B7B34` | the loading flag, `fn_8002F884(level, 5)`, commands 0x40 then 0 |
| 0x4D | `fn_800B7B98` | command 0 |
| 0x59, 0x5A, 0x5B | `fn_800B8174` (0, 1, 2) | `fn_804463C0` on item `+0x1C4` of `lbl_8066B698`, then command 0x18 |
| 0x25E-0x35E | `fn_800B7584` | `+0x24 = command - 0x25E`, `+0x12C = fn_804332C4(lbl_8054ED80, +0x24)`, **clears `G+0x59C`**, then command 0x19 / 0x18 / 9 |
| 0x35F-0x45F | `fn_800B743C` | `+0x1C4 = command - 0x35F`, then `fn_8002A58C`/`fn_8002A5D8` and `fn_8002A984` on item `+0x1C4` of `lbl_8066B698`, then the command saved in `+0x1BC` |
| 0x460-0x560 | `fn_800B74C4` | `+0x1C4 = command - 0x460`, `+0x1B4 = +0x1B8`, command 0xA |
| 0x561-0x661 | `fn_800B73C4` | `Stub6CFC(command - 0x561, G+0x59C)`, then command 0 or 0x18 |

`fn_800B7C98`, the tail five of those arms share, is `BeginLoad`, `fn_8002A354()`,
`fn_8002CA58(level)` when `fn_80431E08(level)` is set, `fn_8002F884(level, 2)`, `+0x1DC = 1`,
command 0, then `fn_80128C3C("main")`.

**`fn_800B76C0` is the versus load path.** It is the one place the level name the setup handlers
write actually loads a level, and it forks on whether that name is set:

- `G+0x59C` non-empty: `fn_8002D7A8(lbl_8052F060, G+0x59C, 8, 0, 0, 0)` when
  `fn_804329E0(lbl_8052F060)` is set, otherwise `fn_8002C690(lbl_8052F060, G+0x59C, 0, 0x1008)`.
  `fn_8002D7A8` is the same call the debug commands 0x52-0x55 make with a literal level name.
- `G+0x59C` empty: `fn_8008856C(lbl_8054ED80, +0x24, 1)` runs the `.nsc` record at `+0x24`, and the
  name comes from `fn_80432688(fn_804332C4(lbl_8054ED80, fn_80431DB0(lbl_8054ED80)))` instead,
  loaded through `fn_8002C690` or `fn_8002CB7C` depending on `fn_80431E08(lbl_8052F060)` and
  `fn_80431DDC(this)`. It then calls `fn_800949FC(G, 0)`.

Either way it ends with the loading flag, `fn_8002F884(lbl_8052F060, 5)`, command 0x1B and
`+0x130 = 0`. So `clashVenue_StartLevel` -> `G+0x59C` -> `SetCommand(0x14)` -> `fn_800B76C0` is the
whole menu-to-level chain.

`lbl_805526AC` (dtk, `.bss`, 0x20) **is `G+0x59C`**: 0x80552110 + 0x59C = 0x805526AC. dtk named it
separately because a relocation pointed inside `G`'s blob, which confirms the level-name buffer's
0x20 size from the code side.

Fields this file adds to section 6's list, all `int` unless marked: `+0x24` the `.nsc` record index,
`+0x12C` a **pointer** to the record `fn_804332C4` returns (not an int, as first guessed; `RunCommand`
nulls it every call), `+0x140` and `+0x15C` set to 1 and 0 together by the three load entry points,
`+0x144`, `+0x17C` the load mode `fn_80446094` writes, `+0x1B4`/`+0x1B8` a one-deep command save
(`+0x1B4 = +0x1B8; +0x1B8 = 0x10`), `+0x1C4` an index into the `lbl_8066B698` collection, `+0x1DC`
set by `fn_804463F8` and cleared by `fn_8044606C`, and `+0x1F4` (`unsigned char`) `command - 0x2F`.

Three `.sdata` pointers drive most of the arms: `lbl_8066B690` and `lbl_8066B694`, two objects
`fn_8043206C` releases, and `lbl_8066B698`, a collection `fn_801B5D3C` indexes and `fn_801B6A44`
counts. `lbl_80571EA4` is whatever `fn_8043323C` gates during a frontend load.

The file's own globals are four `.sbss` floats at 0x8066D6BC-0x8066D6CC: the same screen-derived
rectangle `Game/fn_800B7094.c` builds, computed from a second width/height pair
(`lbl_8066BA38`/`lbl_8066BA3C` instead of `lbl_8066BA24`/`lbl_8066BA28`). Nothing outside the file
reads them.

### The globals file (0x800B7094-0x800B7204) and the pad hooks

`Game/fn_800B7094.c` is a whole source file with no functions of its own: GCC's
`__static_initialization_and_destruction_0` (named `GameFlowStaticInit` here, because `symbols.txt`
already carries seven locals under the GCC name), its `_GLOBAL_.I`/`_GLOBAL_.D` wrappers, and two
globals. The first is `lbl_80552920`, the `GameFlow` instance, which nothing else in the DOL
constructs or destroys. The second is four `.sbss` floats at 0x8066D6AC-0x8066D6BC, a rectangle
derived from the screen size in `.sdata` (`lbl_8066BA24` width, `lbl_8066BA28` height); only
`lbl_8066D6B4` has another reader, `fn_800B5124` at 0x800B5218.

`OnPadRemoved__FUs` (0x800B6FE4) and `OnPadInserted__FUs` (0x800B703C) are free functions, not
methods, and each forwards an SI port to a `GameFlow` method on the instance (`fn_800B4AB8` removed,
`fn_800B4CF8` inserted). They are hotplug notifications, so the argument is a port and not a mask:
`fn_801AA5E4` registers them once through `fn_80445F28`/`fn_80445F4C` into the `.sdata` callback
slots `lbl_8066C644`/`lbl_8066C648`, then polls `SIProbe` on ports 0-3 each pass, keeping a per-port
state word at `lbl_805932A0 + port * 0x19C`: a probe type of 0x8B100000 or 0x09000000 with the state
clear means a new pad (`PADReset`, set the state, fire `lbl_8066C648`), and a failed probe with the
state set clears it and fires `lbl_8066C644`. They needed no `force_active`, because that
registration takes their addresses and the relocation keeps them alive.

## 7. Open Questions

- What do the role indices at `+0x770`/`+0x774` mean, and what are match types 0, 1 and 2? `fn_80114420` only gates on whether either is nonzero, so it narrows this to "nonzero means a versus match" without naming the values. (`+0x590` is settled: the active slot count, section 4.1.)
- What is the rest of the `Slot` layout? The 0xB0 size is confirmed (section 4.1), and `+0x0`,
  `+0x4`, `+0x34`, `+0x38` (int), `+0x3C` (int) and `+0x40` (float) are settled as *types*. The
  meanings of the last three are not: `fn_800956D4` sets `+0x3C = 1` then `+0x38 = 0` on a slot it
  has just filled, `fn_80431788` sets `+0x3C = 99` for the CPU slot in match type 1, and
  `fn_800B5124` sets it from a `u16`, so `+0x3C` is a small number per slot rather than a flag.
  `+0x24`-`+0x33` and everything from `+0x44` on are still unknown.
- What is `SetMatchInfo`'s unused third argument?
- What are the `GameFlow` command ids (section 6)? `SetCommand` treats command 6 specially by
  keeping it out of the history, and `control.cpp` routes 1, 2 and 8 through `SetCommandBlocking`
  instead of `SetCommand`. The menu uses 0-0x5B, but four wide ranges in
  0x25E-0x661 get a handler each, and `+0x1BC` takes `command - 5` for 0x39-0x3D, so part of the id
  space is structured rather than a flat enum. The per-command methods settle what several of them
  *do* (section 6's map) without naming them; the four wide ranges are now clearly index spaces,
  each arm subtracting its base into `+0x24` or `+0x1C4`.
- What is in the unidentified files at 0x801070FC and 0x8010C528?
- What is the rectangle at 0x8066D6AC for (section 6)? It is built from the screen size at static
  init, but only `fn_800B5124` reads any of it, so its purpose is a guess. The per-command file
  builds a second one at 0x8066D6BC from a different width/height pair, and *nothing* reads that
  one, so both are probably debug-overlay bounds the release build no longer draws.
- What are `lbl_8066B690`, `lbl_8066B694` and `lbl_8066B698` (section 6)? Fifteen of the
  per-command methods drive them, so they are the subsystem the debug menu's option screens edit,
  but nothing matched so far constructs them.
- Which class owns the member subobject at `GameFlow+0x18C`, and what is in it? Its constructor
  `fn_80430728` has an empty body, and nothing matched so far reads `+0x18C`-`+0x19C`.
- Which file holds the `AptObject`/`AptRef` methods at 0x801021A0-0x801037B0 and 0x8044B4EC-0x8044B81C, and what are the classes really called?
- Character questions are in [`characters.md`](characters.md) (sections 3 and 5).
