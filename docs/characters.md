# Characters

How the game defines, selects and loads playable characters, and what a new character would need. The decompilation order for this code is in [`versus.md`](versus.md#5-target-order).

Everything here comes from reading the disassembly and `CLASH.BIG`. Names in the "Meaning" columns are guesses until a unit matches.

---

## 1. Two Character IDs

The code uses two separate numberings. Don't mix them up.

| ID | Where | Values |
|---|---|---|
| **Roster index** | The roster table (section 2), the select screen, `G`'s player slots | 1-18 for playable characters. 0 and 19 are filler records (copies of Wolverine and the Thing). |
| **Type ID** | `fn_80020E60(actor)`, and `fn_8009ABEC(actor)` which returns the copy at `actor+0x1AC`; effects, sound and other gameplay code switch on it | 1-18 playable (a different order from the roster), 21-38 for the alternate costumes (`type + 20`), 100-103 for NPCs (human, brute, flier, civilian). **19 and 20 are unused.** |

### Type IDs (`fn_80020E60`)

**Matched** (`Game/fn_80020E60.c`, 0x80020E60-0x800219D4; plain C at `-O0`). `fn_80020E60(actor)` returns -1 for a null actor or one `fn_800B0C58` rejects. It then gets an info object with `fn_800B14A0(actor)` and returns the cached ID at `info+0x3D4` whenever that is nonzero, so 0 means "not looked up yet" and -1 means "not a character". On the first call it `strcpy`s the name at `info+0xDC` into a 32-byte stack buffer, lowercases it with `strlwr`, then runs an `else if` chain of 56 `strcmp`s and caches the result; an empty name or no match caches -1.

| ID | Name | ID | Name | ID | Name |
|---|---|---|---|---|---|
| 1 | `wolverine` | 7 | `storm` | 13 | `defcon` |
| 2 | `ironman` | 8 | `humantorch` | 14 | `paradox` |
| 3 | `spiderman` | 9 | `daredevil` | 15 | `aftershock` |
| 4 | `venom` | 10 | `thing` | 16 | `johnnyohm` |
| 5 | `magneto` | 11 | `roekel` | 17 | `biohazard` |
| 6 | `elektra` | 12 | `megalith` | 18 | `heatwave` |

`alt_<name>` maps to `id + 20`. `human1`-`3` map to 100, `brute1`-`3` to 101, `flier1`-`3` to 102, and eleven civilians to 103: `Human`, `businessmana`, `businessmanb`, `businesswomana`, `businesswomanb`, `securityguard`, `scientist`, `scientist1`, `scientist2`, `scientist3`, `cop`. The chain is compared in exactly that order, and `Human` is **dead**: the name is lowercased before the first `strcmp`, so an actor called `Human` falls through to -1. The internal names are codenames, so `roekel` is Van Roekel and `defcon`, `megalith`, `aftershock`, `biohazard` and `heatwave` are the Imperfects.

Only three functions call it: `fn_8001C258` (**matched**, `Game/fn_8001C258.cpp`), `fn_80023010` (**matched**, `Game/fn_80023010.c`) and `fn_8002623C` (claimed, `Game/fn_8002623C.cpp`, **NonMatching** at 95.2%; see [`nonmatching.md`](nonmatching.md)). `fn_8002623C` only passes the type ID on to `fn_8001DCE0`, so it is not itself a place a new character needs an entry.

---

## 2. Roster Table

`fn_80431CCC(int index, int remap, int alt)` returns `&table[index]`, where the table is `lbl_804CA51C` (normal costumes) or, when `alt == 1`, `lbl_804CAB0C` (alternate costumes). If `remap` is set, `index` first goes through `lbl_804CB0FC`, an `int[20]` that maps select-screen order to roster index. Both tables are `Record[20]`, which is 0x5F0 bytes each (`Record` is 0x4C bytes). **Matched** (`Game/fn_80431CCC.c`); it's plain C, not a C++ method, despite sitting among C++ handler files (see [`prodg.md`](prodg.md#flags)).

| Offset | Type | Meaning | Wolverine |
|---|---|---|---|
| +0x00 | `char[0x20]` | Entity name | `plr_wolverine` (`plr_altWolverine` in the alt table) |
| +0x20 | `char[0x20]` | Localisation key for the hero name | `~kT_WOLVERINE` |
| +0x40 | `s8[6]` | Select-screen stats: intel, strength, speed, durability, energy, skill | 2, 4, 2, 4, 1, 7 |
| +0x46 | `s8[2]` | Always 0 | |
| +0x48 | int | Unlocked at start | 1 |

The table is in `.data`, and `+0x48` probably changes at runtime as characters are unlocked. That may tie the record count to the save-file layout; check `memcard.cpp` before changing the count.

Accessors, one per field, called by `clashCharSelect_GetCharList`: `fn_8044B1D4` (name key), `fn_8044B234` (intel), `fn_8044B298` (strength), `fn_8044B2FC` (speed), `fn_8044B360` (durability), `fn_8044B3C4` (energy), `fn_8044B428` (skill), and `fn_8044B48C` (unlocked, 5 callers). Each takes `(index, remap, alt)`. The six stat accessors return `char`, not `int`: their caller only matches when they are declared that way, which confirms the stats are `s8`. `fn_8044B1D4` returns `char *` and `fn_8044B48C` returns `int`. Other readers of the table: `fn_804316B0`, `fn_80443678`, `fn_804436D4`, `fn_8044F070` and `fn_80461288`.

Three of those are now known. `fn_80443678(index, remap, alt)` just returns the record (**matched**, `Game/fn_804428E0.c`). `fn_804436D4(index, unlocked, remap)` writes `+0x48` in *both* tables, so unlocking a character unlocks its alternate costume with it; it is the one function in 0x804428E0-0x804437D8 still unmatched ([`nonmatching.md`](nonmatching.md)). `fn_80461288(name, alt)` is the reverse lookup: it walks all 20 records of one table comparing `name` against `+0x00` and returns that record's `+0x20` localisation key, or `name` itself when nothing matches, which confirms `+0x20` as the key field.

**Confirmed** (`Game/fn_8044B1D4.c`, 0x8044B1D4-0x8044B4EC): each is `fn_80431CCC(index, remap, alt)` followed by one field read, which confirms the `+0x40`-`+0x45` stats order (intel, strength, speed, durability, energy, skill) and the `+0x48` unlocked field. They're plain C like `fn_80431CCC`, not registered as APT handlers themselves. `fn_8044B1D4`'s two callers (0x80103830 in the characterselect range, 0x8010B744 in the mission.cpp range) both call it directly. The surrounding 0x8044AF58-0x8044EE3C region is mostly unrelated: a chain of generic registration-constructor templates (`fn_8044AF58`, `fn_8044B11C`, `fn_8044BBC8`...) that are called from the six *handler* files (section 2), not from this one; this accessor block just happens to be link-adjacent to them. The unit is **matched**; the register shape it was stuck on is in [`matching_notes.md`](matching_notes.md) (a `register` local assigned to a plain one).

**`clashCharSelect_GetCharList` loops `for (i = 1; i <= 18; i++)`**: the roster size is a literal in the code, not read from the data. Each iteration fills nine parallel script arrays, which are the names a UI mod would have to keep: `aHeroName`, `aIntel`, `aStr`, `aSpd`, `aDur`, `aEng`, `aSkl`, `aIsUnLocked1` (`fn_8044B48C(i, 1, 0)`, the normal costume's `+0x48`) and `aIsUnLocked2` (`fn_8044B48C(i, 1, 1)`, the same field in the alternate-costume table). The handler is claimed as `Game/handlers/characterselect.cpp`, `NonMatching` at 99.2% ([`nonmatching.md`](nonmatching.md)).

---

## 3. Selection to Spawn

- A player slot in `G` (section 4.1 of [`versus.md`](versus.md#41-game-state-object-g-lbl_80552110-bss)) stores the chosen character by **entity name**. `fn_80443B70(slot, name, player)` copies the name into `slot+0x4` with `strncpy(.., 0x20)` and then writes `slot+0x23` itself, so the field is a `char[0x20]` that is always terminated; `player` goes to `slot+0x0` and is the **player index**, not a count (0x80091290 calls it with `(G+0x10, "plr_wolverine", 0)` and `(G+0xC0, "plr_wolverine", 1)`, which also confirms the 0xB0 stride). `fn_80443BC8(slot)` returns `slot+0x4` as `char *`, and `fn_80443BF4(slot)` returns bit 0 of the int at `slot+0x34`, which marks the slot as in use. All three are **matched** (`Game/fn_80443B70.c`). `fn_80443CCC(G, player, v)` is the `G`-level wrapper that forwards to `fn_804428E0(&G->slots[player], v)` and is **matched** in the same unit; `fn_804428E0(slot, v)` itself is **matched** (`Game/fn_804428E0.c`) and stores `min(v, 2)` at `slot+0x64` with `v` unsigned (so a negative `v` clamps to 2, not 0), which may be the `-t0`/`-t1`/`-t2` texture variant (section 4).
- `fn_80443D44(G, player)` is how gameplay code gets a player's actor, and is the most-called of these
  accessors (20+ callers): it returns `fn_8042FF2C(&G->slots[player])`, or NULL when
  `player < 0 || player >= G+0x590`. **Matched** (`Game/fn_80443B70.c`).
- `fn_80131060(player)` returns that player's slot name, or `"plr_wolverine"` if the slot is empty. **Matched** (`Game/fn_80131060.c`), which fills in the rest: it returns `"plr_wolverine"` for any `player > 1`, and only consults the slot's own name (`fn_80443BC8`) while a match is running (`fn_80130718`). For an unused slot in a running match it falls back to the name at `+0x320` of the script record `fn_804326B4(lbl_8054ED80)` holds, which is the `boss` of the running mission (section 4), and to `"plr_wolverine"` if that is empty.
- `fn_800887AC` is the `.nsc` script parser (section 4), and its `plr_%s` / `plr_alt%s` is how a `boss` line names a character. `fn_801311C0` and `fn_800061CC` handle the `plr_alt` prefix. `fn_801311C0(player)` is **matched** (`Game/fn_80131060.c`): it is the display name for a player, `fn_80461288(fn_80131060(player), strstr(name, "plr_alt") != 0)`, and when the key that comes back starts with `~` it is localised through `fn_8012F32C`. So the `alt` flag the roster lookup takes is decided by the `plr_alt` prefix in the entity name, not stored separately.
- `fn_800B5BC4` (0xBC8) is a large state machine that looks like the game-flow or load driver. It reads the slots and writes `G`'s level-name buffers.
- **Not found yet:** where the `plr_<name>` entity template is defined and how it points to the model, motion set and NVB. A plain search of `CLASH.BIG` finds `plr_wolverine` only in HUD text, so the definitions are probably in compressed or binary level or global data (`Misc/Global.not`, `Levels/*.nsd`).

---

## 4. Per-Character Data in `CLASH.BIG`

`CLASH.BIG` is an EA `BIG4` archive (3,511 entries; big-endian offset and size, then a NUL-terminated name) with the `CLASH.BH` index beside it. Each character has these files (Wolverine shown):

| File | Format | Contents |
|---|---|---|
| `Misc/nvblist.txt` | Text | One line per tuning file (`PLAYER WOLVERINE`). Read by `fn_801B3C4C`. It also lists a `PLAYER Footballguy` with no file. |
| `Misc/PLAYER_WOLVERINE.nvb` | Binary, magic `0xBEEFAD00` | Tuning fields loaded through `%s_%s.nvb` (`fn_801B301C`, `fn_801B3638`). Each record is roughly a field ID, a type, a 0, `0xFFFFD88A`, a size and a value (floats such as 7.0, 15.0, 70.0, 0.3). It also holds effect names, victory and finisher cutscenes, and claw trails. The DOL contains no field names; they have to come from the code that reads each ID. |
| `Motions/wolverine.nms` | Text | Motion set. Each line maps a fixed animation-state name (`Walk`, `Attack1`, `SuperAttackFar`, `WieldThrow`...) to a `.nad` file, with flags (`noloop`, `fps`, `move`, `endtag`...). `basedon male` inherits states from another set. Loaded by `fn_801A8FC4`. The header has an EA "security" line; check whether anything verifies it before editing these files. |
| `Bundles/wolverine.ngb` | Binary | The 158 `.nad` animations. |
| `Bundles/wolverine.ngm` | Binary | The model (`Wolverine.nod`). |
| `Bundles/wolverine.ngt` | Text | Materials and effects the model uses (`WolverineHair`, `ge_charlight`, `GE_PAR_ElectricParticles`). |
| `Bundles/wolverine.tpl`, `Materials/Models/Wolverine*.tpl` | GameCube TPL | Textures. |
| `Bundles/wolverine-t0/t1/t2.ngb` | Binary | Variants loaded through `%s-t%d` (`fn_8019EA38`). |
| `Bundles/wolverine_alt.*` | | The alternate costume. |
| `Apt/clash/portraits/wolverine_blue.big` | APT | Select-screen portrait. |

`Misc/clashMP.nsc` is a text file listing the versus arenas, with their level, intro, win and lose cutscenes.

The loaders are generic engine code that takes a name, with nothing character-specific in them: `fn_8019E9DC` (`Bundles/%s`), `fn_8019EA38`, `fn_8019EBF8` (`Animation:Bundles`), `fn_801A0814` (`Model bundle missed`), `fn_801A8FC4` (`Motions`), `fn_80232C4C` (`Texture bundle missed`) and the NVB functions above.

### The Script Record in Memory

0x804428E0-0x80443678 is **matched** (`Game/fn_804428E0.c`): one long run of leaf setters and getters
on a 0x5C8-byte record, plus a few on the object that owns those records. Every `char[0x20]` field is
`strncpy`'d with 0x20 and then terminated by hand at its last byte, like `slot+0x4`
([`versus.md`](versus.md#3-selection-to-spawn)).

The record is **not** the `.nvb` tuning record, as earlier guessed: it is one entry of an `.nsc`
mission/arena script, and the "Keyword" column below is the `.nsc` line that writes each field.
`fn_800887AC` is the parser (0x800887AC-0x80089710, claimed as `Game/fn_800887AC.cpp`, **NonMatching**
at 99.8% — see [`nonmatching.md`](nonmatching.md)), which reads a text file line by line, lowercases
the first token and dispatches on it. A `mission` line opens a record (`new NameTable`) and an
`endmission` line stamps its index and appends it, so every other keyword applies to the record
opened last. `Misc/clashMP.nsc` is the versus arena list; the "clashmp.nsc" string sits in the same
unit's string pool.

| Offset | Type | Keyword | Accessors |
|---|---|---|---|
| +0x00 | `char[0x20]` | `mission` arg 1 — the record's name | `fn_80442918` |
| +0x20 | `char[0x200]` | `description` | `fn_80442964`; the one long buffer in the record |
| +0x240 | `char[0x20]` | `objective` arg 2 | `fn_80442C3C` |
| +0x260 | `char[0x20]` | `mission` arg 2 | `fn_80442A04` |
| +0x280 | `char[0x20]` | `mission` arg 3 | `fn_804429B4` |
| +0x2A0 | `char[0x20]` | `mission` arg 4 | `fn_80442A80`, getter `fn_80442A54` |
| +0x2C0 | `char[0x20]` | `loadscreen` arg 1 | `fn_80442B20` |
| +0x2E0 | `char[0x20]` | `loadscreen` arg 2, or arg 1 again when the line has only one | `fn_80442AD0` |
| +0x300 | `char[0x20]` | `loadtext`, and `objective` arg 1 | `fn_80442B70` |
| +0x320 | `char[0x20]` | `boss`, as `plr_<name>` or `plr_alt<name>` | `fn_804430AC` |
| +0x340 | `char[3][0x20]` | `intro` | `fn_80442C8C` appends |
| +0x3A0 | `char[3][0x20]` | `extro` | `fn_80442D24` appends |
| +0x400 | `char[3][0x20]` | `fail` | `fn_80442DBC` appends; `fn_80443A2C`-`fn_80443B40` read one of the three lists at random |
| +0x460 | int | none: `endmission` stamps the record's own index in `records[]` | `fn_80442EA8`, getter `fn_80442E7C` |
| +0x464 | int | `flags`, taken as the low 16 bits (see below) | `fn_80442E54` |
| +0x468 | float | `teleportdist` (`atof`) | `fn_80442ED0` |
| +0x46C | int | `teleportdelay` | `fn_80442EF8` |
| +0x470 | int | `replayfrequency` | `fn_80442F20` |
| +0x474 | int | `replaydelay` | `fn_80442F48` |
| +0x478 | `unsigned char` | `character`, rejected unless <= 19 — a roster index | `fn_80442F98`, getter `fn_80442FC4` |
| +0x479 | `unsigned char` | `unlockchar`, rejected unless <= 18 — a playable roster index | `fn_80442FF4`, getter `fn_80443020` |
| +0x47A | `unsigned char` | `sacrifice`, rejected unless <= 19 — a roster index | `fn_80443050`, getter `fn_8044307C` |
| +0x47B-+0x47D | `unsigned char` | entry count for the list at +0x340, +0x3A0 and +0x400. Each append runs only `if (count <= 2)`, so the lists cap at three |  |
| +0x480 | `int[4]` | `rewards`, four `%d` | `fn_80442BC0` writes all four, `fn_80442C00(record, i)` reads one |
| +0x4A4-+0x5A4 | `char[0x20]` x9 | `soundbanks`, up to nine names; a missing one is `""` | `fn_804430FC`, one 10-argument function that writes all nine |
| +0x5C4 | int | `maxblessed` | `fn_80442F70` |

Four more keywords parse and do nothing: `precutscene`, `postcutscene`, `unlocked` and `unlock`.
`profileid` (clamped to 0-5) and `gametype` go on the owning table, not the record, so they are
file-level settings. Lines starting with `;`, `#` or `//`, blank lines and whitespace-only lines are
skipped.

Nothing in the run touches +0x220 or +0x490-+0x4A3. The flags at +0x464 have one tester each for 0x2,
0x4, 0x8, 0x10, 0x20, 0x80, 0x100, 0x200, 0x800 and 0x4000 (`fn_804432D8`-`fn_80443488`, in no bit
order), `fn_804432AC` sets 0x8000, and `fn_8044324C(record, enable)` sets or clears 0x4000 and returns
the new word.

**The owner object** is separate, and `fn_800876D4` is what tells the two apart: it walks `owner+0xC`
as `ScriptRecord *[100]` and copies bits out of each record's +0x464 into the owner's own int flags at
`+0x1AC` (`fn_80443518` ORs, `fn_80443548` clears, `fn_8044357C` assigns, `fn_804435A4` reads; the
values seen are 1, 4, 8 and 0x200). That `+0x1AC` is **not** `actor+0x1AC`, the type ID `fn_8009ABEC`
returns (section 5) — same offset, different object. `fn_800887AC` fills in the rest of its head:
`+0x0` is `profileid` (`unsigned`, clamped to 0-5), `+0x4` is `gametype` (`unsigned`), `+0x8` is the
number of records and `+0xC` the array of them, and `+0x1A4` is an int the parser zeroes before it
starts reading. `fn_80088740(table, actor, flag)`, just before the parser, is **matched** (`Game/fn_80088740.c`): all that is left of it is the lookup of the record the table is on, `fn_804332C4(table, fn_80431DB0(table))`, whose result it drops, so `+0x1A4` is an index into `records[]` and `fn_80431DB0` its getter. What it did with the actor went out with the diagnostics, like its empty `if (!flag)`.

Four `.data` tables are written by index from the same run: `lbl_804CBE94` as `int[]`
(`fn_804435D0`), and `lbl_804CB14C`, `lbl_804CB328` and `lbl_804CBEB8` as arrays of 0x44-byte records
with an int at `+0x40` (`fn_8044374C` in `Game/fn_8044374C.c`, then `fn_80443608` and `fn_80443640`).
What they hold is unknown. `lbl_804CB14C` is `Record44[7]`: it ends exactly where `lbl_804CB328`
starts, and dtk mis-types it as a 0xF-byte string because each record starts with text.

**Physics** is Havok (`hk*`, the `hkRagdollConstraintData` ragdolls, `RagdollRecover_*`). No character-specific physics code has turned up yet. Per-character physical tuning is most likely in the NVB fields.

---

## 5. Code That Lists Characters

These are every function that references four or more character-name strings, plus the one data table that does. A new character needs an entry in each one, or a check that the default branch is acceptable.

| Where | What |
|---|---|
| `clashCharSelect_GetCharList` | Loop bound 18, and nine script array names (section 2). |
| Roster tables `lbl_804CA51C`, `lbl_804CAB0C`, remap `lbl_804CB0FC` | `Record[20]` and `int[20]`. Indices 0 and 19 are filler. |
| `fn_80020E60` | Name → type ID chain, 56 `strcmp`s in a fixed order (section 1). **Matched**, so a new name is a source edit. |
| `fn_8001C258` (0x2C0) | Turns the aura on or off, `fn_8001C258(actor, 1/0)`. **Matched** (`Game/fn_8001C258.cpp`), so a new character is a source edit. |
| `fn_80023010` (0x638) | Looks up all 19 effect keys and spawns the two flame auras. **Matched** (`Game/fn_80023010.c`), so a new character is a source edit. It also reads `G+0x590`. |
| `fn_80114420` (0x3B4) | Per-character SFX banks. **Matched** (`Game/fn_80114420.cpp`), so a new character is a source edit. See "SFX banks" below. |
| `lbl_804CF8E8` | AI profile names, `char*[31]` with a NULL end: `AI_DEFAULT`, the 18 characters in alphabetical order, then NPCs. |
| `fn_801BEE2C`, `fn_801F7C68` | Story mode boss and level lists. Not needed for versus. |

### SFX banks

`fn_80114420` (**matched**, `Game/fn_80114420.cpp`) preloads one sound bank per active player. It
loops `p` over `G+0x590` (the active slot count), takes slot `p`'s actor (`slot+0x28`), switches on
that actor's type ID and `strcpy`s the bank name into a 32-byte buffer, then calls
`fn_8045777C(lbl_8066BD88, name, 1)` for any name it set. It runs only when `G+0x770` or `G+0x774` is
nonzero, or the level name at `G+0x59C` is `0_Test_Arena`, and does nothing unless `lbl_8066B63C` is
set and `lbl_8066BD10` is clear.

The type ID here does **not** come from `fn_80020E60`: `fn_8009ABEC(actor)` just returns the int at
`actor+0x1AC`. The 18 bank names line up with `fn_80020E60`'s numbering exactly, which is what shows
the two are the same ID space; what writes `actor+0x1AC` hasn't been found, and it is a different
object from the `info+0x3D4` cache `fn_80020E60` fills. Three banks use a codename the roster doesn't: `SFX_Brigade`
is Megalith, `SFX_Hazmat` Biohazard and `SFX_Wink` Paradox (`SFX_Solara` does not exist; Heatwave's
bank is `SFX_Heatwave`).

| ID | Bank | ID | Bank | ID | Bank |
|---|---|---|---|---|---|
| 1 | `SFX_Wolv1` | 7 | `SFX_Storm` | 13 | `SFX_DefCon` |
| 2 | `SFX_Iron2` | 8 | `SFX_Torch` | 14 | `SFX_Wink` |
| 3 | `SFX_Spidey` | 9 | `SFX_Devil` | 15 | `SFX_AfterShk` |
| 4 | `SFX_Venom` | 10 | `SFX_Thing` | 16 | `SFX_Ohm` |
| 5 | `SFX_Magneto` | 11 | `SFX_Roekel` | 17 | `SFX_Hazmat` |
| 6 | `SFX_Elektra` | 12 | `SFX_Brigade` | 18 | `SFX_Heatwave` |

There is no `default:` case, so an unlisted type loads no bank. A neighbouring function at 0x801140E8
uses `SFX_generic`, which is probably that fallback for NPCs.

### Auras

The aura functions key off a shared **aura index**, not the type ID. `fn_80023010`'s `switch`
(**matched**, `Game/fn_80023010.c`) names all 19 of them, so the index space is complete: 0-2 are
explosions, 3-10 are the eight base auras and 11-18 the alts, always base + 8.

| Index | Key | Character | Type ID | Alt index | Alt key |
|---|---|---|---|---|---|
| 0 | `KEY_SMALL_EXPLOSION` | | | | |
| 1 | `KEY_MED_EXPLOSION` | | | | |
| 2 | `KEY_LARGE_EXPLOSION` | | | | |
| 3 | `KEY_JOHNNYOHM_AURA` | `johnnyohm` | 16 | 11 | `KEY_ALTJOHNNYOHM_AURA` |
| 4 | `KEY_HUMANTORCH_AURA` | `humantorch` | 8 | 12 | `KEY_ALTHUMANTORCH_AURA` |
| 5 | `KEY_IRONMAN_AURA` | `ironman` | 2 | 13 | `KEY_ALTIRONMAN_AURA` |
| 6 | `KEY_STORM_AURA` | `storm` | 7 | 14 | `KEY_ALTSTORM_AURA` |
| 7 | `KEY_BRIGADE_AURA` | `megalith` | 12 | 15 | `KEY_ALTBRIGADE_AURA` |
| 8 | `KEY_ROEKEL_AURA` | `roekel` | 11 | 16 | `KEY_ALTROEKEL_AURA` |
| 9 | `KEY_HAZMAT_AURA` | `biohazard` | 17 | 17 | `KEY_ALTHAZMAT_AURA` |
| 10 | `KEY_SOLARA_AURA` | `heatwave` | 18 | 18 | `KEY_ALTSOLARA_AURA` |

So three of the eight auras are named after a codename the roster doesn't use: Brigade is Megalith,
Hazmat is Biohazard and Solara is Heatwave (guessed from the index order, which lines up with
`fn_8001C258`'s `switch` for the five it handles). The two functions split the eight: `fn_8001C258`
switches indices 3, 5, 6, 7, 8 (and their alts) on and off per actor, `fn_80023010` spawns 4 and 10
(and their alts) for the players in the match, and nothing found so far uses 9/17.

### The effect managers

`fn_8002623C` (`Game/fn_8002623C.cpp`) pins down the rest of the `EffectManager` layout that
`fn_8001C258` started, and where the managers live:

| Where | What |
|---|---|
| `lbl_80515030` | One `.bss` object, 0xB050: `EffectManager managers[6]`, 0xF0 of something at +0x9630, then one more `EffectManager` at +0x9720. `fn_8002623C` reaches the last one as an offset from the start of the object, which is what shows they are one global and not two. |
| `lbl_8066B5EC` | int, which entry of `managers` is current. `fn_80022EC8()` returns `&lbl_80515030.managers[lbl_8066B5EC]`; `fn_80022F00()` returns `&lbl_80515030` + 0x9720 (dtk's `lbl_8051E750`). |
| `EffectManager` | 0x1930 bytes. +0x00 int (0 means the manager is not set up), +0x2C `EffectDef *`, +0x30 count, +0x3C a pointer to 0x4C-byte records, +0x44 the name table, +0x390 `Effect effects[64]`, +0x1790 the live count. |
| `Effect` | 0x50 bytes. +0x10 `Vector` (position), +0x28 int, +0x30 the type `fn_8001C258` matches on, +0x34 the owning actor, +0x40 float. |

The index addresses two `.bss` tables, `lbl_805200A0` (0x4C, 19 ints) and `lbl_805200EC` (0x54).
`fn_80023010` fills them: it clears each entry to -1/0, then walks the two effect managers'
definition tables (`fn_80022EC8()` first, then `fn_80022F00()`, records of 0x30 at `+0x2C`, count at
`+0x30`, a name table at `+0x44`) and `strcmp`s each record's name against the key, storing the
record's index in `lbl_805200A0[i]` and which manager it came from (0 or 1) in `lbl_805200EC[i]`. So
-1 means the key isn't loaded, and the pair is "which effect definition, in which manager".

Both functions then spawn the effect with
`fn_8002298C(fn_80022EC8(), lbl_805200A0[i], lbl_805200EC[i], &color, n, actor, 0.0f, 0.0f)`, where
`color` is four floats built by `fn_8042D768` from `fn_800B2620(actor) * 0.5f` as the blue channel,
and `n` is 1 in `fn_80023010` against 2 in `fn_8001C258`. That `n` is the effect's `+0x30` field: to
switch the aura off, `fn_8001C258` walks the effect manager's table (`fn_80022EC8()`, effects at
`+0x390` on a 0x50 stride, count at `+0x1790`) and calls `fn_8002289C` on every entry whose `+0x30`
is 2 and whose `+0x34` is this actor.

Not yet searched for: more code that branches on a numeric type ID or roster index (`switch` jump
tables, `cmpwi` against 1-38), and arrays sized 18, 20 or 38 that are indexed by character.
`fn_8001C258` is the first such `switch` found, and it ignores the 13 characters with no aura rather
than having a default branch, so a new character needs an entry only if it should glow.

## 6. Adding a Character (Working Hypothesis)

1. **Data:** a model, motion set, animation bundle, textures, NVB and portrait under a new name, plus a line in `Misc/nvblist.txt`.
2. **Roster:** grow the tables to 21 records (or reuse filler index 19), raise the select loop bound, and extend the remap table.
3. **Type ID:** add the name to `fn_80020E60` using the free ID 19 or 20, with the alt at `+20`.
4. **Per-character code:** handle the new type in the aura, SFX and AI code, and in anything section 5's "not yet searched" turns up.
5. **Saves:** check whether the unlock state or stats are saved per roster index.

Steps 2-4 are code changes. Each one becomes a small source edit once its function is matched; until then, each is a binary patch.
