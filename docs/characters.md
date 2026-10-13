# Characters

How the game defines, selects and loads playable characters, and what a new character would need. The decompilation order for this code is in [`versus.md`](versus.md#5-target-order).

Everything here comes from reading the disassembly and `CLASH.BIG`. Names in the "Meaning" columns are guesses until a unit matches. Facts marked **tested** were seen running in Dolphin on 2026-10-12, in a modded build with a 19th versus character (section 6).

---

## 1. Two Character IDs

The code uses two separate numberings. Don't mix them up.

| ID | Where | Values |
|---|---|---|
| **Roster index** | The roster table (section 2), the select screen, `G`'s player slots | 1-18 for playable characters. 0 and 19 are filler records (copies of Wolverine and the Thing). |
| **Type ID** | `fn_80020E60(actor)` (from the name), and `fn_8009ABEC(actor)`, which returns `actor+0x1AC`, set separately from entity property 0x70, `OBJECT_SOUNDID` (section 3); effects, sound and other gameplay code switch on it | 1-18 playable (a different order from the roster), 21-38 for the alternate costumes (`type + 20`), 100-103 for NPCs (human, brute, flier, civilian). **19 and 20 are unused.** `actor+0x1AC` also holds non-character values (`fn_80098D30` tests 70-76, 100, 102, 104, 119, 125, 157, 160, 173, 195, 506, 515; meanings unknown). |

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

Only three functions call it: `fn_8001C258` (**matched**, `Game/fn_8001C258.cpp`), `fn_80023010` (**matched**, `Game/fn_80023010.c`) and `fn_8002623C` (**matched**, `Game/fn_8002623C.cpp`). `fn_8002623C` only passes the type ID on to `fn_8001DCE0`, so it is not itself a place a new character needs an entry.

---

## 2. Roster Table

`fn_80431CCC(int index, int remap, int alt)` returns `&table[index]`, where the table is `lbl_804CA51C` (normal costumes) or, when `alt == 1`, `lbl_804CAB0C` (alternate costumes). If `remap` is set, `index` first goes through `lbl_804CB0FC`, an `int[20]` that maps select-screen order to roster index. Both tables are `Record[20]`, which is 0x5F0 bytes each (`Record` is 0x4C bytes). **Matched** (`Game/fn_80431CCC.c`); it's plain C, not a C++ method, despite sitting among C++ handler files (see [`prodg.md`](prodg.md#flags)).

| Offset | Type | Meaning | Wolverine |
|---|---|---|---|
| +0x00 | `char[0x20]` | Entity name | `plr_wolverine` (`plr_altWolverine` in the alt table) |
| +0x20 | `char[0x20]` | Localisation key for the hero name. A plain string is shown as is (**tested**), so a new name needs no string-table entry | `~kT_WOLVERINE` |
| +0x40 | `s8[6]` | Select-screen stats: intel, strength, speed, durability, energy, skill | 2, 4, 2, 4, 1, 7 |
| +0x46 | `s8[2]` | Always 0 | |
| +0x48 | int | Unlocked at start | 1 |

The tables are source now (`Game/unlockables.c`, a data-only unit): both `CharacterRecord[20]` arrays, the `int[20]` order table, and three more `Rec` arrays of 0x44 bytes (`char name[0x20]`, `char key[0x20]`, `int unlocked`) beside them:

| Address | Contents |
|---|---|
| 0x804CB14C | `Rec[7]` venues, `BrooklynBridge` to `RoekelFacility`; the first three start unlocked |
| 0x804CB328 | `Rec[43]` cards, `~kT_CARDS<n>` / `~kT_CARDSDESC<n>`, all locked |
| 0x804CBE94 | `int[9]`, all 0; meaning unknown |
| 0x804CBEB8 | `Rec[25]` comics, `~kT_COMIC<n>` / `~kT_COMICDESC<n>`, all locked |

Rows 0 and 2 are both Wolverine, and 19 repeats Thing; the order table starts and ends with 0. The alternate table repeats the normal one except for the entity name and, in rows 1, 6, 9, 11, 13, 14 and 16, some stats.

The table is in `.data`, and `+0x48` probably changes at runtime as characters are unlocked. No `memcard.cpp` function calls a reader of the roster tables, and only `clashMemcard_ResetStoryMode` does so through one more call, so the save does not appear to store the roster records (guess: unlocks are rebuilt from story progress; access through a stored pointer is unchecked).

Accessors, one per field, called by `clashCharSelect_GetCharList`: `fn_8044B1D4` (name key), `fn_8044B234` (intel), `fn_8044B298` (strength), `fn_8044B2FC` (speed), `fn_8044B360` (durability), `fn_8044B3C4` (energy), `fn_8044B428` (skill), and `fn_8044B48C` (unlocked, 5 callers). Each takes `(index, remap, alt)`. The six stat accessors return `char`, not `int`: their caller only matches when they are declared that way, which confirms the stats are `s8`. `fn_8044B1D4` returns `char *` and `fn_8044B48C` returns `int`. Other readers of the table: `fn_804316B0`, `fn_80443678`, `fn_804436D4`, `fn_8044F070` and `fn_80461288`.

Three of those are now known. `fn_80443678(index, remap, alt)` just returns the record (**matched**, `Game/fn_804428E0.c`). `fn_804436D4(index, unlocked, remap)` writes `+0x48` in *both* tables, so unlocking a character unlocks its alternate costume with it; it is **matched** as `Game/fn_804436D4.cpp`, a C++ unit because it binds both records to reference locals. `fn_80461288(name, alt)` is the reverse lookup: it walks all 20 records of one table comparing `name` against `+0x00` and returns that record's `+0x20` localisation key, or `name` itself when nothing matches, which confirms `+0x20` as the key field.

**Confirmed** (`Game/fn_8044B1D4.c`, 0x8044B1D4-0x8044B4EC): each is `fn_80431CCC(index, remap, alt)` followed by one field read, which confirms the `+0x40`-`+0x45` stats order (intel, strength, speed, durability, energy, skill) and the `+0x48` unlocked field. They're plain C like `fn_80431CCC`, not registered as APT handlers themselves. `fn_8044B1D4`'s two callers (0x80103830 in the characterselect range, 0x8010B744 in the mission.cpp range) both call it directly. The surrounding 0x8044AF58-0x8044EE3C region is mostly unrelated: a chain of generic registration-constructor templates (`fn_8044AF58`, `fn_8044B11C`, `fn_8044BBC8`...) that are called from the six *handler* files (section 2), not from this one; this accessor block just happens to be link-adjacent to them. The unit is **matched**; the register shape it was stuck on is in [`matching_notes.md`](matching_notes.md) (a `register` local assigned to a plain one).

**`clashCharSelect_GetCharList` loops `for (i = 1; i <= 18; i++)`**: the roster size is a literal in the code, not read from the data. Each iteration fills nine parallel script arrays, which are the names a UI mod would have to keep: `aHeroName`, `aIntel`, `aStr`, `aSpd`, `aDur`, `aEng`, `aSkl`, `aIsUnLocked1` (`fn_8044B48C(i, 1, 0)`, the normal costume's `+0x48`) and `aIsUnLocked2` (`fn_8044B48C(i, 1, 1)`, the same field in the alternate-costume table). The handler is matched as `Game/handlers/characterselect.cpp`.

---

## 3. Selection to Spawn

- A player slot in `G` (section 4.1 of [`versus.md`](versus.md#41-game-state-object-g-lbl_80552110-bss)) stores the chosen character by **entity name**. `fn_80443B70(slot, name, player)` copies the name into `slot+0x4` with `strncpy(.., 0x20)` and then writes `slot+0x23` itself, so the field is a `char[0x20]` that is always terminated; `player` goes to `slot+0x0` and is the **player index**, not a count (0x80091290 calls it with `(G+0x10, "plr_wolverine", 0)` and `(G+0xC0, "plr_wolverine", 1)`, which also confirms the 0xB0 stride). `fn_80443BC8(slot)` returns `slot+0x4` as `char *`, and `fn_80443BF4(slot)` returns bit 0 of the int at `slot+0x34`, which marks the slot as in use. All three are **matched** (`Game/fn_80443B70.c`). `fn_80443CCC(G, player, v)` is the `G`-level wrapper that forwards to `fn_804428E0(&G->slots[player], v)` and is **matched** in the same unit; `fn_804428E0(slot, v)` itself is **matched** (`Game/fn_804428E0.c`) and stores `min(v, 2)` at `slot+0x64` with `v` unsigned (so a negative `v` clamps to 2, not 0), which is probably the difficulty level (guess: `Control_SetMatchInfo` passes it `fn_801318A0()`, the value `clashCharSelect_GetPrevCharList` returns to the UI as `nDiffLevel`). It is not the `-t<n>` bundle variant, which comes from property 0x27 (below).
- `fn_80443D44(G, player)` is how gameplay code gets a player's actor, and is the most-called of these
  accessors (20+ callers): it returns `fn_8042FF2C(&G->slots[player])`, or NULL when
  `player < 0 || player >= G+0x590`. **Matched** (`Game/fn_80443B70.c`).
- `fn_80131060(player)` returns that player's slot name, or `"plr_wolverine"` if the slot is empty. **Matched** (`Game/fn_80131060.c`), which fills in the rest: it returns `"plr_wolverine"` for any `player > 1`, and only consults the slot's own name (`fn_80443BC8`) while a match is running (`fn_80130718`). For an unused slot in a running match it falls back to the name at `+0x320` of the script record `fn_804326B4(lbl_8054ED80)` holds, which is the `boss` of the running mission (section 4), and to `"plr_wolverine"` if that is empty.
- `fn_800887AC` is the `.nsc` script parser (section 4), and its `plr_%s` / `plr_alt%s` is how a `boss` line names a character. `fn_801311C0` and `fn_800061CC` handle the `plr_alt` prefix. `fn_801311C0(player)` is **matched** (`Game/fn_80131060.c`): it is the display name for a player, `fn_80461288(fn_80131060(player), strstr(name, "plr_alt") != 0)`, and when the key that comes back starts with `~` it is localised through `fn_8012F32C`. So the `alt` flag the roster lookup takes is decided by the `plr_alt` prefix in the entity name, not stored separately.
- `fn_800B5BC4` is **matched** (`Game/fn_800B5BC4.cpp`) and is not the load driver it looked like: it is the debug-menu command dispatcher ([`versus.md`](versus.md#6-the-gameflow-command-dispatcher)). It does reach the load path, through `fn_8002D7A8(lbl_8052F060, level, 8, 0, 0, 0)` and `fn_8009543C(G, id, "plr_wolverine")` (**matched**, `Game/fn_8009543C.c`: `id` 0-4, looks the template up with `fn_800FD5FC(name, 0)`, which does not create one, so the name must already be registered; `fn_8009613C(&G->slots[id], template)` fills the slot and the slot's actor, `slot+0x28`, is returned), which are the two debug commands worth following for how a chosen character becomes a spawned one.
- **An actor is built from a property list.** Entity templates are looked up by name with `fn_800FD5FC(name, flag)` (`strlwr`, then a hashed lookup in the `.sbss` registry `lbl_8066BAE4`). `fn_800AC37C(object, property, arg)` applies one property `{int id +0x0; value +0x4}` (`Game/fn_800AC37C.cpp`). It looks the id up in the 120-entry property table `lbl_8048E748` (0x28-byte entries `{char name[0x20]; int kind; int type}`, `.rodata`; `type` is the value type: 0 string, 2 float, 3 int, 4 vector) and dispatches on `kind`, the component that owns the property (table below). The names in the table are the `Global.not` property names (`MODEL`, `ACTOR_HEALTH`, `PHYSICS_MASS`, ...).

  | Kind | Ids | Handler |
  |---|---|---|
  | 0 | 0-9, 0xF, 0x15, 0x17, 0x1A-0x22, 0x25, 0x26, 0x28-0x2C, 0x67, 0x74, 0x76 (common) | `fn_800AE534` |
  | 2 | 0x10 `SCRIPT` | `fn_8007CA10` |
  | 7 | 0x14 `CASTID` | `fn_800AC750` |
  | 8 | 0x5A-0x63 `PHYSICS_*` | `fn_80067248` |
  | 4, 10 | 0x2D-0x49 `ACTOR_*`/`ARMOR_*`, 0x6F | `fn_80084498`, if `fn_800B0C58(object)` |
  | 9 | 0x23 `EXPLOSION`, 0x4A-0x4E `PROJECT_*` | `fn_8009E6AC`, if `fn_800B0DA0` |
  | 11 | 0x68-0x6A, 0x77 `CONTAINER_*` | `fn_800A39F4(fn_800B1478(object), ..)`, if `fn_800B0CC0` |
  | 13 | 0x64-0x66, 0x71-0x73 `PROP_*` | `fn_800A39F4(object, ..)`, if `fn_800B0CC0` |
  | 14 | 0x6B `SENSOR_FLAGS` | `fn_800A9F90(fn_800B1518(object), ..)`, if `fn_800B0E18` |
  | 15 | 0xA-0xE `MODEL*`, 0x11-0x13, 0x16, 0x18, 0x19, 0x24, 0x27, 0x6C-0x6E, 0x70, 0x75 | `fn_80097750(fn_800B1568(object), ..)`, if `fn_800B0F0C` |
  | 3 (`WEAPON_*`), 1, 12 | 0x4F-0x59 | nothing here (returns 0) |
  | 5, 6, 0x63 | no table entry uses them | `fn_800AEB90` |

  A gated kind returns 0 when its gate fails, so a property of that kind is ignored on an object of another class.

- **The templates are `Misc/Global.not`** (the only `.not` in `CLASH.BIG`), loaded by `fn_800FCF50` (`"global"`, `"NOT"`, `"Game:Templates"`; `fn_800FCE84` creates the registry; source file probably `gameTemplate`). Format, **little-endian** (the loader byte-swaps): magic `"NOT\x10"`, a u32 version (1), the template count (836) at `+0x8`, then index entries `{char name[0x20]; u32 offset}`. A record at `offset` (not aligned) is a u32 property count, then 0x24-byte properties `{u32 id; value[0x20]}`, the value a string, int, float or three floats, then a note: a u32 length and that many bytes of NUL-terminated text (`"\0"` for 813 templates, a designer's comment for 23). The loader reads the records sequentially, so they must stay in index order and back to back, and it reads the note into a 0x200-byte stack buffer unchecked (the longest is 398 bytes). `python3 tools/nottool.py dump <name>` prints a template with its property names; its `parse()` and `build()` rewrite the file byte for byte. Property 0 names the parent template, so `plr_Wolverine` is just `{0: act_Wolverine, 5: 7, 0xB: 0, 0x1A: 2}`, and `act_Wolverine` (parent `_superhero`) holds the character. `plr_alt<Name>` has the same parent and overrides the models (0x0A, 0x0F, 0x75), 0x14, 0x30 and 0x1A, so the alt's property 0x70 is the base type (1 for Wolverine), not `type + 20`.

  | Id | Name (`lbl_8048E748`) | `act_Wolverine` | Effect (`fn_80097750` unless noted) |
  |---|---|---|---|
  | 0x0A | `MODEL` | `Wolverine.nod` | model: `fn_801A1FC4` / `fn_801A2894` / `fn_801A1A84`, result at `actor+0x1BC`. The bundle loaded is named after this value, not after the template: `Daredevil.nod` in a template of another name opens `Bundles/Daredevil.*` (**tested**) |
  | 0x0B | `MODELFLAGS` | | int, ORed into the model's `+0x4` flags; ignored with no model |
  | 0x0C | `MODELSCALE` | | float, `fn_804442F0(model, v)`; ignored with no model |
  | 0x0D | `MODELLODSCALE` | | float, multiplies the `+0x30` float of `fn_8009AD80(actor)` (by name, the LOD scale) |
  | 0x0E | `MODELOFFSET` | | vector, copied to `actor+0x1D0` |
  | 0x0F | `PHYSMODEL` | `Wolverine_phys.nod` | not in `fn_80097750` (kind 0, `fn_800AE534`) |
  | 0x12 | `SOUNDTYPE` | 16 | `actor+0x1A8` |
  | 0x13 | `MOTIONSET` | `wolverine.nms` | motion set: `fn_8019EA38(name, variant)` when `fn_80444454(actor)`, where the `-t<n>` variant is property 0x27 of the template named in the *other* player's slot (`fn_800976C0`; this player's slot index is `G+0x640`), or -1 when `fn_80426AB0(G)`; then `fn_8008F470(name, 0, 1)` into `actor+0x1C0` (the set's `+0x24` is a count; `fn_80097C4C(actor, n)` stores a byte `n` <= that count at `actor+0x204`, called from 0x800C3BC4 and two more sites in the script-command file) |
  | 0x14 | `CASTID` | `WOLVERINE` (`ALT_WOLVERINE` on the alt) | not in `fn_80097750` (guess: the name `fn_80020E60` reads, since `alt_` gives `type + 20` there) |
  | 0x15 | `DESCRIPTIONID` | `WOLVERINE` | not in `fn_80097750` (guess: the NVB name, `PLAYER_WOLVERINE.nvb`) |
  | 0x19 | `DAMAGESCALE` | | float, `actor+0x214` |
  | 0x24 | `DESTROY_TEMPLATE` | | string, template `fn_800FD5FC(name, 1)` into `+0x1A0`, else `fn_803A1AC4(lbl_8064AA80, name)` into `+0x1A4` |
  | 0x27, 0x28 | `SKELETONID`, `EFFECT1` | Storm: 1, `strmHair` | 0x27: `actor+0x200`, a body class: 0 by default (`_actor`), 1 for Aftershock, DefCon, Elektra, Heatwave, Paradox and Storm, 2 for the Thing, Venom, Megalith, Roekel and the brutes. The opponent's value picks this character's `-t<n>` animation bundle (0x13). 0x28: a per-model effect (`ddFX`, `strmHair`, `htBodyFire`...; not followed) |
  | 0x2E | `ACTOR_AI` | `AI_WOLVERINE` | (`fn_80084498`) AI profile: index of the name in `lbl_804CF8E8` (`fn_80137CEC`, `stricmp`), stored as a short at `+0x384`; an unknown name gives 0, `AI_DEFAULT` |
  | 0x2D-0x38, 0x3A, 0x3B, 0x6F | `ACTOR_*`, `SUPERBLOCK_EFFECT` | | (`fn_80084498`, object fields) 0x2D low halfword to short `+0x314`; 0x30 int `+0x300`; 0x31 int `+0x30C`; 0x32 int `+0x308`; 0x33 int as float to `+0x31C` and `+0x32C`; 0x34 int as float to `+0x320`; 0x35, 0x36 floats `+0x324`, `+0x328`; 0x37, 0x38 floats `+0x33C`, `+0x340`; 0x3A low byte to short `+0x316`; 0x3B template lookup into `+0x3B4`, else `fn_803A1AC4(lbl_8064AA80, name)` into `+0x3B0`; 0x6F that lookup into `+0x3C0`. Other ids (0x2F, 0x39, 0x3C-0x49) return 0 |
  | 0x6C | `HAVOKBREAK_MODEL` | | string, `fn_801A1A84` into `+0x20C` |
  | 0x6D, 0x6E | `HAVOKBREAK_TEMPLATE`, `HAVOKCHUNK_TEMPLATE` | | string, template lookup into `+0x208`, `+0x210` |
  | 0x70 | `OBJECT_SOUNDID` | 1 (Storm: 7) | **type ID**, `actor+0x1AC` |
  | 0x75 | `SHADOWMODEL` | `Wolverine_shadow.nod` | `fn_801A1A84` into `+0x22C` (shadow model) |

  Also in `act_Wolverine`, named by the table but not followed further: 0x20 `RENDERFLAGS` (0x01000009), 0x30 `ACTOR_FLAGS` (0x108200), 0x32 `ACTOR_ABILITIES` (0x05400602; differs per character), 0x33/0x34 `ACTOR_HEALTH`/`ACTOR_MAXHEALTH` (100), 0x37/0x38 `ACTOR_WALKSPEED`/`ACTOR_RUNSPEED` (1.7, 6.0), and the editor's 0x1A `EDITORCATEGORY` (4; `plr_` sets 2) and 0x1B/0x1C `EDITORSIZEMINS`/`EDITORSIZEMAXS` (vectors). `act_Wolverine` and `act_Daredevil` differ only in 0x0A, 0x0F, 0x13, 0x14, 0x15, 0x2E, 0x32, 0x70, 0x75 and 0x28, which only Daredevil sets.

- **The registries have no fixed capacity.** This is read from the disassembly: `fn_801B43D8`, `fn_801B4CA0` and `fn_801B4E84` are unmatched (`fn_801B4284`, the add `fn_801B4628` and the lookup `fn_801B48AC` are matched and confirm the header, the node layout and the duplicate drop). `fn_801B4284(hint, name)` builds a chained hash table: a 0x2C header (`name[0x20]`, `+0x20` count, `+0x24` bucket count, `+0x28` buckets) whose bucket count is the first prime of `lbl_8049E5A0` (23, 53, 79, ... 1999) above the hint, so 557 for the templates (hint 0x200) and 53 for the files (0x20). Nodes are 0x14 bytes (`+0x0` next, `+0x4` previous, `+0x8` key, `+0x10` value) from one free list shared by every registry (`lbl_8066C6E0` count, `lbl_8066C6E4` head), seeded with 0x2000 and grown by 0x200 whenever it is empty. `fn_801B4628` adds nothing and returns 0 when `fn_801B4E84` finds the key (`strnicmp`, 0x80), so a duplicate name is dropped. The hash is `sum((i + 1) * lower(c[i]))` over at most 127 characters, modulo the bucket count. Per template, `fn_800FD9A0` (matched) stores the property count at entry `+0x28` and a `count * 0x24` heap array at `+0x2C`, so there is no property limit either. Each property is `{id +0x0; value +0x4}` byte-swapped by its `lbl_8048E748` type (3 int, 2 float, 4 three words, anything else, strings included, untouched). The limits that do exist are the 64 loaded `.NOT` files of `lbl_80565860` and the note buffer above. 839 templates load and work (**tested**).

- **Attached entities inherit the type.** `fn_800A22CC` spawns entities from an actor's 0x5C-byte attachment records (default template `prp_propbust`; record `+0x48` template, `+0x50` type, `+0x54`/`+0x55`/`+0x56` bytes, getters at 0x802365D8-0x80236804) and sets the child's `+0x1AC` to the record's type, or to the parent's when it is 400. That and property 0x70 are the only writers of `+0x1AC` besides the constructor `fn_800974B4`, which zeroes it.

---

## 4. Per-Character Data in `CLASH.BIG`

`CLASH.BIG` is an EA `BIG4` archive (3,511 entries; big-endian offset and size, then a NUL-terminated name) with the `CLASH.BH` index beside it. `CLASH.BH` has 16 bytes per entry in the same order: offset, size, unpacked size (0 unless the entry is RefPack-compressed, which only the 709 nested `.big` UI archives are) and a djb2 hash of the lowercased path. `python3 tools/bigtool.py` lists, extracts and repacks both files (layouts in its header), and the game accepts a repacked archive with entries moved and one added (**tested**). Each character has these files (Wolverine shown):

| File | Format | Contents |
|---|---|---|
| `Misc/Global.not` | Binary, little-endian, magic `NOT\x10` | Entity templates `act_Wolverine`, `plr_Wolverine`, `plr_altWolverine` (format in section 3). |
| `Misc/nvblist.txt` | Text | One line per tuning file (`PLAYER WOLVERINE`). Read by `fn_801B3C4C` (the path is `nvblist.txt`, mode `ra`): lines starting with a space or `/` are skipped, the first two tokens (delimiters ` \t\r\n/;`) of every other line are the two `fn_801B3638` arguments, and a line with fewer than two tokens is ignored. The pairs are collected in one 0x200-byte buffer, so the whole list is limited to that size, and loaded afterwards. It also lists a `PLAYER Footballguy` with no file. |
| `Misc/PLAYER_WOLVERINE.nvb` | Binary, magic `0xBEEFAD00` | Tuning fields loaded through `%s_%s.nvb` (`fn_801B301C`, `fn_801B3638`). Layout (`fn_801B3638`, big-endian): three 4-byte words (guess: the first is the magic), the two 0x40-byte name strings the caller passed (compared, result unused), a group count; each group is a field ID `x` (index into the 0x24-byte entry table at `nvb+0x24`), a record count `y`, then `y` records of slot index, type and value. Type `0xFFFFD888` has a 4-byte value, `0xFFFFD887` a 0x10-byte one (fixed up by `fn_8042FC74`), any other type is followed by a size word; only the first word of the value is byte-swapped (not for `0xFFFFD887`, `0xFFFFD884`/`D885`/`D889`). Slot 0 of the first record is copied to slots 1-5 of the entry (6 slots at entry `+0x8`). Values are floats such as 7.0, 15.0, 70.0, 0.3. It also holds effect names, victory and finisher cutscenes, and claw trails. The DOL contains no field names; they have to come from the code that reads each ID. |
| `Motions/wolverine.nms` | Text | Motion set. Each line maps a fixed animation-state name (`Walk`, `Attack1`, `SuperAttackFar`, `WieldThrow`...) to a `.nad` file, with flags (`noloop`, `fps`, `move`, `endtag`...). `basedon male` inherits states from another set. Loaded by `fn_801A8FC4`. The header has an EA "security" line; check whether anything verifies it before editing these files. |
| `Bundles/wolverine.ngb` | Binary | The 158 `.nad` animations. |
| `Bundles/wolverine.ngm` | Binary | The model (`Wolverine.nod`). |
| `Bundles/wolverine.ngt` | Text | Materials and effects the model uses (`WolverineHair`, `ge_charlight`, `GE_PAR_ElectricParticles`). |
| `Bundles/wolverine.tpl`, `Materials/Models/Wolverine*.tpl` | GameCube TPL | Textures. |
| `Bundles/wolverine-t0/t1/t2.ngb` | Binary | The variant for an opponent whose property 0x27 (`SKELETONID`, section 3) is 0, 1 or 2, loaded through `%s-t%d` (`fn_8019EA38`). |
| `Bundles/wolverine_alt.*` | | The alternate costume. |
| `Apt/clash/portraits/c1_p0.big` | APT | Select-screen portrait, named by select-screen id (section 5; Wolverine is 1). |
| `Apt/clash/portraits/cvs1.big`, `cvs1_alt.big` | APT | Versus loading-screen portraits for the two costumes, by the same id. |
| `Apt/clash/portraits/wolverine_blue.big` | APT | Story-mode portrait: only `screens/clashStoryMode.big` loads it. |

`Misc/clashMP.nsc` is a text file listing the versus arenas, with their level, intro, win and lose cutscenes.

The loaders are generic engine code that takes a name, with nothing character-specific in them: `fn_8019E9DC` (`Bundles/%s`), `fn_8019EA38`, `fn_8019EBF8` (`Animation:Bundles`), `fn_801A0814` (`Model bundle missed`), `fn_801A8FC4` (`Motions`), `fn_80232C4C` (`Texture bundle missed`) and the NVB functions above.

### The Script Record in Memory

0x804428E0-0x80443678 is **matched** (`Game/fn_804428E0.c`): one long run of leaf setters and getters
on a 0x5C8-byte record, plus a few on the object that owns those records. Every `char[0x20]` field is
`strncpy`'d with 0x20 and then terminated by hand at its last byte, like `slot+0x4`
([`versus.md`](versus.md#3-selection-to-spawn)).

The record is **not** the `.nvb` tuning record, as earlier guessed: it is one entry of an `.nsc`
mission/arena script, and the "Keyword" column below is the `.nsc` line that writes each field.
`fn_800887AC` is the parser (0x800887AC-0x80089710, **matched**, `Game/fn_800887AC.cpp`), which reads a text file line by line, lowercases
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
`lbl_804CB14C` is the **venue table**, `Record44[7]`, which `clashVenue_GetVenueList` walks: a name
at `+0x20` (`fn_8044F19C(i)`, 0x20 bytes) and the unlocked flag at `+0x40` (`fn_8044D5C4(i)`). It ends exactly
where `lbl_804CB328` starts, and dtk mis-types it as a 0xF-byte string because each record starts with text.
What the other two tables hold is unknown.

**Physics** is Havok (`hk*`, the `hkRagdollConstraintData` ragdolls, `RagdollRecover_*`). No character-specific physics code has turned up yet. Per-character physical tuning is most likely in the NVB fields.

---

## 5. Code That Lists Characters

These are every function that references four or more character-name strings, plus the one data table that does. A new character needs an entry in each one, or a check that the default branch is acceptable.

| Where | What |
|---|---|
| `clashCharSelect_GetCharList` | Loop bound 18, and nine script array names (section 2). |
| `Control_SetSelectInfo` (`Game/fn_80104504.cpp`) | Clamps each selected id, `charId + 1 > 0x12 ? 0x12 : charId + 1`, once per player. A 19th entry turns into the 18th unless the 0x12 is raised everywhere it appears, which is twice per player, in the compare and in the result (**tested**). |
| Select-screen UI data | Literal 18s and per-id file names in the APT scripts. See "Select-screen UI" below. |
| Roster tables `lbl_804CA51C`, `lbl_804CAB0C`, remap `lbl_804CB0FC` | `Record[20]` and `int[20]`. Indices 0 and 19 are filler. |
| `fn_80020E60` | Name → type ID chain, 56 `strcmp`s in a fixed order (section 1). **Matched**, so a new name is a source edit. |
| `fn_8001C258` (0x2C0) | Turns the aura on or off, `fn_8001C258(actor, 1/0)`. **Matched** (`Game/fn_8001C258.cpp`), so a new character is a source edit. |
| `fn_80023010` (0x638) | Looks up all 19 effect keys and spawns the two flame auras. **Matched** (`Game/fn_80023010.c`), so a new character is a source edit. It also reads `G+0x590`. |
| `fn_80114420` (0x3B4) | Per-character SFX banks. **Matched** (`Game/fn_80114420.cpp`), so a new character is a source edit. See "SFX banks" below. |
| `lbl_804CF8E8` | AI profile names, `char*[31]` with a NULL end: `AI_DEFAULT`, the 18 characters in alphabetical order, then NPCs. Read only by `fn_80137CEC` (name to index, for property 0x2E, section 3); an unlisted name gets `AI_DEFAULT`, so a new character works without an entry. |
| `fn_80099228`, `fn_8010CDCC`, `fn_8010D050` | Special-case type 17 (Biohazard) only: `fn_80099228` sets `.sdata` `lbl_8066F060` to 3 or 2 only when the type is not 17 (1 comes from another test), `fn_8010CDCC` (matched, `Game/fn_8010CDCC.c`) sets the voice value it stores in `.sbss` `lbl_8066F050` to 4 when the actor is type 17 and the target is not, and clears `lbl_8066F060` when the target is type 17 and `fn_800CCA08` or `fn_800CCA88` holds, and `fn_8010D050` (matched, same file; takes the bank as a parameter, not the actor's type) sets `lbl_8066F060` to 3, 1 or 2 from `fn_800CCA08`, `fn_800CC9D8` and `fn_800CCA88` on the target's record, with 3 and 2 only when the target is not type 17. Meaning unknown (guess: voice handling). |
| `fn_801155A8`, `fn_801154D8`, `fn_80115308`, `fn_80115154` | Sound-event lookups keyed `(bank << 9) \| event` through `fn_801B4938` on the registry `lbl_80568DB0`. `fn_8010CDCC` passes the **type ID as the bank** to the first three, so character voices are data keyed by type ID; `fn_801155A8(bank)` (matched) asks whether bank `bank` has event 1: it looks `(bank << 9) \| 1` up in the registry at `lbl_80568DB0+4`, then `0xFA001` (bank 2000, event 1) in the one at `+0`, and returns whether either hit; it returns 0 outright when `.sdata` `lbl_8066B63C` or `lbl_8066BD04` is 0. `fn_801154D8(bank, event)` (matched) is the same test with the event as a parameter, and both lookups go to the registry at `lbl_80568DB0+0`: `(bank << 9) \| event`, then `event \| 0xFA000` (bank 2000). `fn_80115154(bank, event)` and `fn_80115308(bank, event, arg)` (both matched) are the play calls, the second with one extra argument that it records at `lbl_80568DB0+0x10` and `.sbss` `lbl_8066F070` and passes on to `fn_80041074`: they record the pair at `lbl_80568DB0+0x8`/`+0xC`, look the key up as above, and call the hit as a function pointer; a type with no events plays nothing. A new type ID needs voice events under its own bank, or no voice. |
| `fn_801BEE2C`, `fn_801F7C68` | Story mode boss and level lists. Not needed for versus. |

### Select-screen UI

The UI is ActionScript in EA's APT format (big-endian here), in the nested `.big` archives under
`Apt/clash/`. Nothing in it reads the roster size from the game. A 19th entry (id 18) was added by
changing the rows below (**tested**); `gamelib/bg_main.big` needed no change.

| Where | What |
|---|---|
| Select-screen id | 0-17, the order table's index minus one: Thing, Wolverine, Paradox, Elektra, Johnny Ohm, Spider-Man, Daredevil, Storm, Aftershock, Venom, Heatwave, Human Torch, Iron Man, Megalith, Magneto, Biohazard, DefCon, Van Roekel. Every row below is indexed by it. |
| `main.big`, `mainBE.big` | `_global.kGlobal_Max_NumChar = 18`: `CDataHub.CS_SetCharacter` ignores an id at or above it, and the select screen then stays on READY with no error. Also `g_aTable_HeroName` (18 keys: the name on the versus loading screen, where a plain string also works) and `oGlobal_oColourList.aAtribCol` (18 name colours). `fn_800B7C98` loads `main` and `fn_800B7894` loads `mainBE`; from boot to the versus select screen `main`'s values are the ones in effect (patching `mainBE` alone changes nothing). When `mainBE` is used is unknown. |
| `screens/clashCharSelect.big` | The frame-0 script's literal arrays: `g_oLayOutList.aObject` (clip names `thumb0`-`thumb17`), `aCharObject` (18 slots), `g_aCharacterOrder` (0-17) and `g_aCharacterAudio` (18 `FE_SFX_*` names; a missing entry only loses the "ready" voice). Its own name and stat arrays are placeholders that `Init()` replaces with the result of `clashCharSelect_GetCharList`. The grid is `new CMenu(aCharObject, players, ..., 9)`: 9 columns and `floor(length / 9)` rows with empty slots skipped, so 19 entries need a 27-slot array to be reachable. The cursor is drawn at the thumbnail clip's own position. |
| `screens/clashCharSelect_thumbs.big` | The `thumb<n>` clip instances, and one exported sprite `char<id>` per thumbnail picture (`attachMovie('char' + id)`). |
| `portraits/c<id>_p0.big` | Select-screen portrait. `c18_p0`, `cvs18` and `csm18` exist as placeholders; `cvs18_alt` does not. What loads `csm<id>` is not traced. |
| `portraits/cvs<id>.big`, `cvs<id>_alt.big` | Versus loading-screen portraits. The files inside a portrait archive are named after the archive. |
| `gamelib/bg_main.big` | Background tint: `gotoAndStop(id + 2)` on a 23-frame clip, so id 18 lands on an existing frame. |

The nested archives are unpacked in place. A RefPack stream that is not smaller than its output
still loads, but the game prints `Target buffer is not large enough for inplace decompression!`.
The game's `OSReport` text (that line, `Opening file: Bundles/<x>.tpl`, `Texture bundle missed`)
shows in Dolphin's log with the `OSREPORT` log type on.

### SFX banks

`fn_80114420` (**matched**, `Game/fn_80114420.cpp`) preloads one sound bank per active player. It
loops `p` over `G+0x590` (the active slot count), takes slot `p`'s actor (`slot+0x28`), switches on
that actor's type ID and `strcpy`s the bank name into a 32-byte buffer, then calls
`fn_8045777C(lbl_8066BD88, name, 1)` for any name it set. It runs only when `G+0x770` or `G+0x774` is
nonzero, or the level name at `G+0x59C` is `0_Test_Arena`, and does nothing unless `lbl_8066B63C` is
set and `lbl_8066BD10` is clear.

The type ID here does **not** come from `fn_80020E60`: `fn_8009ABEC(actor)` just returns the int at
`actor+0x1AC`. The 18 bank names line up with `fn_80020E60`'s numbering exactly, which is what shows
the two are the same ID space; `actor+0x1AC` comes from entity property 0x70 (section 3), not from
the `info+0x3D4` cache `fn_80020E60` fills. Three banks use a codename the roster doesn't: `SFX_Brigade`
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

### Coverage of this list

Every call site of `fn_80020E60` (3 callers) and `fn_8009ABEC` (21) was checked for what the result
feeds; the table above holds those that treat characters differently. The others pass the ID on (to
the `Obj*` factories at 0x804580CC-0x80459A80, to `fn_8010D050`, or to `fn_80428EEC` on
`lbl_805724F0`, a keyed registry), test it against 0, or switch on non-character values
(`fn_80098D30`); `fn_800BFC60` hands it to `fn_80446F10` (a keyed fan-out over `lbl_80572538`, a list of vtable objects) without testing it; `fn_8009EA20` keeps it in a register and was not followed. The game has only 20 jump tables, so a `switch` on the type is
a compare chain, not a table. `fn_8001C258` ignores the characters with no aura rather than having a
default branch, so a new character needs an entry only if it should glow.

Of the 84 data objects sized 0x48, 0x4C, 0x50 or 0x98 (18, 19, 20 or 38 words), only the aura
table `lbl_805200A0` is read by a function that also reads a character ID or slot name. **Not checked
yet:** code that reads `actor+0x1AC` without the getter, and `fn_8009EA20`.

## 6. Adding a Character

**Tested** on 2026-10-12 in Dolphin, versus mode only: a 19th character that reuses Daredevil's
model and Wolverine's motion set, type ID, cast and tuning. It was picked from its own select-screen
tile by player 1 and for the CPU (the second slot), and played, including a mirror match and the
alternate costume. A human player 2 picking it was not tried. Steps 1 to 3 are what that took. Steps 4 to 6 are still a hypothesis, for a character with
its own type ID and assets. Not tested: the new character winning a match, audio, story mode, saves.

1. **Templates:** `act_<Name>`, `plr_<Name>` and `plr_alt<Name>` appended to `Misc/Global.not` (section 3; `tools/nottool.py`), then `CLASH.BIG` and `CLASH.BH` repacked (`tools/bigtool.py`). A character that reuses existing assets needs no other data: the bundles follow the `MODEL` and `MOTIONSET` values, and the tuning and sounds follow the reused `DESCRIPTIONID`, `CASTID` and type ID. One character's motion set drove another's model of the same body class (property 0x27) without distortion, but a prop that the model carries and the motion set does not animate (Daredevil's club) floats.
2. **Roster (DOL):** record 19 in both tables and entry 19 of the order table (section 2), the loop bound in `clashCharSelect_GetCharList`, and the clamp in `Control_SetSelectInfo` (section 5). All are same-size edits in matched source. Record 19 is the last one free, so a 20th character means growing the tables.
3. **Select-screen UI:** the APT data in section 5 ("Select-screen UI"). An `.apt`'s pointers are file offsets, so these edits can be made by appending new arrays and records to the file and redirecting a count and pointer to them.
4. **Type ID (untested):** add the name to `fn_80020E60` using the free ID 19 or 20, with the alt at `+20`, and set the same ID with property 0x70 in `act_<Name>` (section 3). The two are read by different code, so presumably they should agree for the base character. The existing alternates do not: their 0x70 is the base ID while `fn_80020E60` returns `+20`, so what reads which is not settled.
5. **Per-character code and data (untested):** handle the new type in the aura and SFX code, give it voice events under its type ID's sound bank, and name an AI profile with property 0x2E (or get `AI_DEFAULT`). Its own model, motion set, animation bundle and textures go under new names, and its own tuning needs an NVB and a line in `Misc/nvblist.txt`. Recheck section 5's "Not checked yet" list. With a reused type ID the in-match HUD icon is the reused character's.
6. **Saves:** probably unaffected (section 2): the save code does not read the roster tables. The test ran without a memory card.
