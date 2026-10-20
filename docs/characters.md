# Characters

How the game defines, selects and loads playable characters, and what a new character needs. The decompilation order for this code is in [`versus.md`](versus.md#5-target-order).

Facts come from the disassembly and `CLASH.BIG` unless a unit is named. What a matched function does is in its source, so this file keeps only what a modder or the next decompilation needs. **Tested** marks what was seen running in Dolphin in modded builds: a 19th character built from existing assets (2026-10-12), and characters 19 and 20 with their own assets (2026-10-17).

---

## 1. Two Character IDs

Don't mix these up.

| ID | Where | Values |
|---|---|---|
| **Roster index** | The roster table (section 2), the select screen, `G`'s player slots | 1-18 playable. 0 and 19 are filler records (copies of Wolverine and the Thing). |
| **Type ID** | Effects, sound and other gameplay code switch on it | 1-18 playable (in a different order from the roster), 21-38 the alternate costumes (`type + 20`), 100-103 NPCs (human, brute, flier, civilian). **19 and 20 are unused.** |

Two functions give a type ID, each from its own template property (section 3):

- `fn_80020E60(actor)` (`Game/fn_80020E60.c`) turns the `CASTID` name (property 0x14, which `fn_800AC750` lowercases into `actor+0xDC`) into an ID with a `strcmp` chain, and caches it at `actor+0x3D4` (0 not looked up yet, -1 not a character). Its callers are the aura code `fn_8001C258` and `fn_80023010`, and `fn_8002623C`, which passes the ID on to `fn_8001DCE0`.
- `fn_8009ABEC(actor)` returns `actor+0x1AC`, which `OBJECT_SOUNDID` (property 0x70) sets. The SFX banks (`fn_80114420`) and voices (`fn_8010CDCC`) read it. `actor+0x1AC` also holds values that are not characters (`fn_80098D30` tests 70-76, 100, 102, 104, 119, 125, 157, 160, 173, 195, 506 and 515; meanings unknown).

The alternate costumes keep the base ID in 0x70 while their `CASTID` is `ALT_<name>`, so an alternate gets its own aura (`type + 20`) and the base character's sounds.

| ID | Name | ID | Name | ID | Name |
|---|---|---|---|---|---|
| 1 | `wolverine` | 7 | `storm` | 13 | `defcon` |
| 2 | `ironman` | 8 | `humantorch` | 14 | `paradox` |
| 3 | `spiderman` | 9 | `daredevil` | 15 | `aftershock` |
| 4 | `venom` | 10 | `thing` | 16 | `johnnyohm` |
| 5 | `magneto` | 11 | `roekel` | 17 | `biohazard` |
| 6 | `elektra` | 12 | `megalith` | 18 | `heatwave` |

`alt_<name>` maps to `id + 20`. `human1`-`3` map to 100, `brute1`-`3` to 101, `flier1`-`3` to 102, and eleven civilians (`businessmana` ... `cop`) to 103. The chain also has `Human`, which never matches because the name is lowercased first. The names are codenames: `roekel` is Van Roekel, and `defcon`, `megalith`, `aftershock`, `biohazard` and `heatwave` are the Imperfects.

---

## 2. Roster Table

`Game/unlockables.c` is a data-only unit. It holds `lbl_804CA51C` (normal costumes) and `lbl_804CAB0C` (alternate costumes), each a `CharacterRecord[20]` of 0x4C-byte records, and `lbl_804CB0FC`, an `int[20]` from select-screen order to roster index. `fn_80431CCC(index, remap, alt)` returns `&table[index]`, going through the order table when `remap` is set and using the alternate table when `alt == 1`. Callers take `alt` from the `plr_alt` prefix of the entity name (`fn_801311C0`); it is not stored anywhere.

| Offset | Type | Meaning | Wolverine |
|---|---|---|---|
| +0x00 | `char[0x20]` | Entity name | `plr_wolverine` (`plr_altWolverine` in the alt table) |
| +0x20 | `char[0x20]` | Localisation key for the hero name. A plain string is shown as is (**tested**), so a new name needs no string-table entry | `~kT_WOLVERINE` |
| +0x40 | `s8[6]` | Select-screen stats: intel, strength, speed, durability, energy, skill. Only shown: no gameplay code was found reading them | 2, 4, 2, 4, 1, 7 |
| +0x46 | `s8[2]` | Always 0 | |
| +0x48 | int | Unlocked at start (Daredevil's is 0) | 1 |

Rows 0 and 2 are both Wolverine, and 19 repeats the Thing; the order table starts and ends with 0. The alternate table repeats the normal one except for the entity name and, in rows 1, 6, 9, 11, 13, 14 and 16, some stats.

Readers: the per-field accessors `fn_8044B1D4`-`fn_8044B48C` that `clashCharSelect_GetCharList` calls (`Game/fn_8044B1D4.c`), `fn_80443678` (the whole record), `fn_804436D4` (writes `+0x48` in *both* tables, so unlocking a character unlocks its alternate costume), `fn_80461288(name, alt)` (name to localisation key, or the name itself when there is no match), `fn_804316B0`, and `fn_8044F070` (`Game/fn_8044EEF4.c`), the inverse of the order table, which searches `i <= 0x13`.

The same unit holds three more arrays of `{char name[0x20]; char key[0x20]; int unlocked}`: 0x804CB14C `Rec[7]` venues (`BrooklynBridge` to `RoekelFacility`, the first three unlocked), 0x804CB328 `Rec[43]` cards and 0x804CBEB8 `Rec[25]` comics, all locked. 0x804CBE94 is an `int[9]` of zeros (meaning unknown).

**Saves.** No `memcard.cpp` function reads the roster tables, and only `clashMemcard_ResetStoryMode` reaches them through one more call, so the save does not appear to store the records (guess: unlocks are rebuilt from story progress; access through a stored pointer is unchecked).

**`clashCharSelect_GetCharList` loops `for (i = 1; i <= 18; i++)`**: the roster size is a literal in the code. It fills nine script arrays, the names a UI mod has to keep: `aHeroName`, `aIntel`, `aStr`, `aSpd`, `aDur`, `aEng`, `aSkl`, `aIsUnLocked1` and `aIsUnLocked2` (`+0x48` of the normal and the alternate record).

---

## 3. Selection to Spawn

- **Player slots.** A slot of `G` ([`versus.md`](versus.md#41-game-state-object-g-lbl_80552110-bss) section 4.1) stores the character by **entity name** at `slot+0x4` (`char[0x20]`, always terminated; `fn_80443B70(slot, name, player)` writes it, `fn_80443BC8` reads it). `slot+0x64` is the CPU difficulty: `min(v, 2)` with `v` unsigned, from `fn_801318A0()`, the value the UI gets as `nDiffLevel`. It picks the tuning slot (section 4, "Tuning records"). `fn_80443D44(G, player)` returns a player's actor, or NULL when `player` is out of range of `G+0x590`.
- **Names for a player.** `fn_80131060(player)` returns the slot's name while a match runs (`fn_80130718`), and `"plr_wolverine"` otherwise or for `player > 1`. An empty slot in a running match falls back to the mission's `boss` (the script record's `+0x320`, section 4). `fn_801311C0(player)` is the display name: `fn_80461288(name, strstr(name, "plr_alt") != 0)`, localised when the key starts with `~`.
- **The debug path to a spawn.** `GameFlow` commands 0x50 and 0x51 call `fn_8009543C(G, id, "plr_wolverine")`, which finds the template with `fn_800FD5FC(name, 0)` (no create, so the name must be registered) and fills the slot with `fn_8009613C` ([`versus.md`](versus.md#6-the-gameflow-command-dispatcher) section 6).
- **An actor is built from a property list.** `fn_800FD5FC(name, flag)` finds a template by name (lowercased, in the hashed registry `lbl_8066BAE4`). `fn_800AC37C(object, property, arg)` applies one property `{int id; value}`: it looks the id up in the 120-entry table `lbl_8048E748` (`{char name[0x20]; int kind; int type}`, the `Global.not` property names; `type` 0 string, 2 float, 3 int, 4 vector) and dispatches on `kind`, the component that owns the property. A gated kind returns 0 when its gate fails, so the property is ignored on an object of another class.

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
  | 3 (`WEAPON_*`), 1, 12 | 0x4F-0x59 | nothing (returns 0) |
  | 5, 6, 0x63 | no table entry uses them | `fn_800AEB90` |

- **The templates are `Misc/Global.not`**, the only `.not` in `CLASH.BIG`, loaded by `fn_800FCF50`. `tools/nottool.py` holds the format; `dump <name>` prints a template with its property names, and `parse()`/`build()` rewrite the file byte for byte. The loader reads the records sequentially, so they must stay in index order and back to back, and it reads each note into a 0x200-byte stack buffer without a check (the longest is 398 bytes). Property 0 names the parent: `plr_Wolverine` is just `{0: act_Wolverine, 5: 7, 0xB: 0, 0x1A: 2}`, and `act_Wolverine` (parent `_superhero`) holds the character. `plr_alt<Name>` has the same parent and overrides the models (0x0A, 0x0F, 0x75), 0x14, 0x30 and 0x1A. `act_Wolverine` and `act_Daredevil` differ only in 0x0A, 0x0F, 0x13, 0x14, 0x15, 0x2E, 0x32, 0x70, 0x75 and 0x28, which only Daredevil sets.

  | Id | Name | `act_Wolverine` | Effect (`fn_80097750` unless noted) |
  |---|---|---|---|
  | 0x0A | `MODEL` | `Wolverine.nod` | The model, at `actor+0x1BC`. The bundle loaded is named after this value, not the template: `Daredevil.nod` opens `Bundles/Daredevil.*` (**tested**) |
  | 0x0B, 0x0C | `MODELFLAGS`, `MODELSCALE` | | ORed into the model's `+0x4` flags; the model scale. Both ignored with no model |
  | 0x0E | `MODELOFFSET` | | Vector, `actor+0x1D0` |
  | 0x0F | `PHYSMODEL` | `Wolverine_phys.nod` | (`fn_800AE534`) `+0x174`; hit regions and ragdoll parts (its materials are `hitRegion_*` and `ragdoll_*`) |
  | 0x12 | `SOUNDTYPE` | 16 | `actor+0x1A8` |
  | 0x13 | `MOTIONSET` | `wolverine.nms` | The motion set, `actor+0x1C0`. Loads `Bundles/<name>.ngb` and the `-t<n>` variant, where `n` is the other player's 0x27 (section 4) |
  | 0x14 | `CASTID` | `WOLVERINE` (`ALT_WOLVERINE` on the alt) | (`fn_800AC750`) Lowercased into `+0xDC`: the name `fn_80020E60` turns into the type ID (section 1) |
  | 0x15 | `DESCRIPTIONID` | `WOLVERINE` | (`fn_800AE534`) `+0xFC`. Names the tuning record `PLAYER_<value>` (section 4); otherwise only AI debug text and a story-mode lookup read it |
  | 0x19 | `DAMAGESCALE` | | Float, `actor+0x214` |
  | 0x24 | `DESTROY_TEMPLATE` | | Template into `+0x1A0`, else an effect into `+0x1A4` |
  | 0x27 | `SKELETONID` | Storm: 1 | `actor+0x200`, the body class: 0 male (the default), 1 female (Aftershock, DefCon, Elektra, Heatwave, Paradox, Storm), 2 brute (the Thing, Venom, Megalith, Roekel, the brutes). The opponent's value picks this character's `-t<n>` animation bundle and the tuning fields 206 + class |
  | 0x28-0x2B | `EFFECT1`-`EFFECT4` | Storm: `strmHair` | (`fn_800AE534`) An effect created and attached to the actor (`ddFX`, `htBodyFire`...). 0x2C `EFFECT5` does nothing |
  | 0x2E | `ACTOR_AI` | `AI_WOLVERINE` | (`fn_80084498`) AI profile: the name's index in `lbl_804CF8E8`, a short at `+0x384`; an unknown name gives 0, `AI_DEFAULT` |
  | 0x30 | `ACTOR_FLAGS` | 0x108200 | (`fn_80084498`) `+0x300`. Bit 0x80 (`fn_80085DCC`) is the alternate costume (`plr_altWolverine` has 0x108280) and picks tuning slot 5; bit 0x200 (`fn_80085D3C`, meaning unknown) can pick slot 4 |
  | 0x32 | `ACTOR_ABILITIES` | 0x05400602 | (`fn_80084498`) `+0x308`, the bits below |
  | 0x33, 0x34 | `ACTOR_HEALTH`, `ACTOR_MAXHEALTH` | 100, 100 | (`fn_80084498`) Floats `+0x31C`/`+0x32C` and `+0x320` |
  | 0x35, 0x36 | `ACTOR_ENERGY`, `ACTOR_MAXENERGY` | | (`fn_80084498`) `+0x324`, `+0x328`. Moves cost energy (tuning fields 30, 31, 35, 225, 230) |
  | 0x37, 0x38 | `ACTOR_WALKSPEED`, `ACTOR_RUNSPEED` | 1.7, 6.0 | (`fn_80084498`) `+0x33C`, `+0x340` |
  | 0x6C-0x6E | `HAVOKBREAK_MODEL`, `HAVOKBREAK_TEMPLATE`, `HAVOKCHUNK_TEMPLATE` | | `+0x20C`, `+0x208`, `+0x210` |
  | 0x70 | `OBJECT_SOUNDID` | 1 (Storm: 7) | **Type ID**, `actor+0x1AC` (section 1) |
  | 0x75 | `SHADOWMODEL` | `Wolverine_shadow.nod` | `+0x22C` |

  The other `ACTOR_*` properties and the kind-0 entity properties (`ORIENTATION`, `POSITION`, `SECTORID`, `TIMER`, `MOVETYPE`, `COLLIDETYPE`, `RADIUS`, `HEIGHT`, `THINGFLAGS`, `RENDERFLAGS`, `DROPITEM`, ...) are not character-specific; `Game/fn_80084498.cpp` and `Game/fn_800AE534.cpp` say where each goes. The editor's 5 and 0x1A-0x1E are accepted and ignored.

- **`ACTOR_ABILITIES` bits** (`actor+0x308`). One accessor per bit at 0x80085FAC-0x80086374 (`Game/fn_80085F7C.cpp`, each a one-line `abilities & mask`). The meanings come from reading their callers and from tests in modded builds; `nottool.py dump act_<Name>` gives each character's value.

  | Bit | Read by | Meaning |
  |---|---|---|
  | 0x10, 0x20 | `fn_8008621C`, `fn_8008624C`, both only from `fn_8008572C(actor, object)` | Lifting: anyone lifts light objects, 0x10 or 0x20 medium ones, 0x20 heavy ones (`fn_800A43A0`/`fn_800A4408`/`fn_800A4438` classify the object) |
  | 0x80 | `fn_8008606C`, from the air states `fn_800C509C`, `fn_800C5A84` and 22 more | The wire swing for Daredevil and Spider-Man: R held and jump pressed again in the air, if energy covers tuning field 30 (**tested**). Biohazard, DefCon, Paradox and Venom have the bit too |
  | 0x4000 | `fn_800DDCB4`, reading `+0x308` itself | The super attack's far version (`SuperAttackFar`) with no target, straight ahead |
  | 0x20000 | `fn_8008609C`, from the dodge state `fn_800F3384` and two more | Unknown |
  | 0x20000000 | `fn_80086344`, only from `fn_800E7A4C` | A hit landed in motion 0x33 or 0x36 skips the animation ahead to its event 0x53: the thrown weapon comes back (Daredevil only) |

  The other accessors, meanings unknown: 0x2 `fn_8008603C`, 0x8 `fn_8008615C`, 0x40 `fn_800860CC`, 0x100 `fn_800862AC`, 0x200 `fn_80085FDC`, 0x1000 `fn_800861BC`, 0x2000 `fn_800860FC`, 0x8000 `fn_8008618C`, 0x100000 `fn_80085FAC`, 0x400000 `fn_8008600C`, 0x1000000 `fn_8008627C`, 0x2000000 `fn_800861EC`, 0x4000000 `fn_8008612C` and 0x10000000 `fn_80086314`. `fn_800862DC` is true when 0x8000000 is *clear*, and `fn_80086374` tests the mask 0x810004.

- **The registries have no fixed capacity** (`Game/fn_801B4284.c` seeds and takes nodes, `Game/fn_801B4CA0.c` hashes, `Game/fn_801B4E84.c` scans a bucket). A registry is a chained hash table, hashed by the sum of `(i + 1) * tolower(key[i])` over the first 127 characters, whose bucket count is the first prime of `lbl_8049E5A0` above a size hint, and every registry takes its 0x14-byte nodes from one shared free list that grows by 0x200 whenever it is empty. A duplicate name is dropped (`fn_801B4628` returns 0). There is no limit on properties per template either (`fn_800FD9A0`). The limits that exist are the 64 loaded `.NOT` files (`lbl_80565860`) and the 0x200-byte note buffer. 839 templates load and work (**tested**).

- **Attached entities inherit the type.** `fn_800A22CC` spawns entities from an actor's 0x5C-byte attachment records (default template `prp_propbust`) and sets each child's `+0x1AC` to the record's type; a type of 400 means "take the parent's". Only that, property 0x70 and the constructor `fn_800974B4` (which zeroes it) write `+0x1AC`.

---

## 4. Per-Character Data in `CLASH.BIG`

`CLASH.BIG` is an EA `BIG4` archive with the `CLASH.BH` index beside it; `python3 tools/bigtool.py` lists, extracts and repacks both (layouts in its header). The game accepts a repacked archive with entries moved and one added (**tested**). Only the 709 nested `.big` UI archives are RefPack-compressed (`tools/refpack.py`, `tools/nbig.py`; "UI archives" below). Each character has these files (Wolverine shown):

| File | Format | Contents |
|---|---|---|
| `Misc/Global.not` | Binary, little-endian | Entity templates `act_Wolverine`, `plr_Wolverine`, `plr_altWolverine` (section 3). |
| `Misc/nvblist.txt` | Text | One line per tuning file (`PLAYER WOLVERINE`). `fn_801B3C4C` skips lines starting with a space or `/`, takes the first two tokens (delimiters ` \t\r\n/;`) of each other line, and ignores a line with fewer. The pairs go into one 0x200-byte buffer as `a\|b\|`, 458 bytes for the shipped list, so the whole list is limited to that size. It also lists a `PLAYER Footballguy` with no file. |
| `Misc/PLAYER_WOLVERINE.nvb` | Binary, little-endian | The character's tuning: the fields that differ from the defaults ("Tuning records" below). |
| `Misc/defaults.ndb` | Binary, little-endian | One file for the game: the tuning schema, every field's type and default. |
| `Motions/wolverine.nms` | Text | The motion set (below). |
| `Bundles/wolverine.ngb` | Binary, big-endian | The 158 `.nad` animations (below). |
| `Bundles/wolverine.ngm` | Binary, big-endian | The models `Wolverine.nod`, `Wolverine_phys.nod` and `Wolverine_shadow.nod` (below). |
| `Bundles/wolverine.ngt` | Text | The names of the images of `Bundles/wolverine.tpl`, in order (`Wolverine`, `GE_env_WinkOnyx`, `WolverineHair`, `ge_charlight`, `GE_PAR_ElectricParticles`). |
| `Bundles/wolverine.tpl`, `Materials/Models/Wolverine*.tpl` | GameCube TPL | Textures (`tools/gxtex.py` decodes, encodes and rebuilds them, and gives Dolphin's texture-pack name). `fn_80232C4C` reads image 0 only. The loose `WolverineHair.tpl` is 128x128 and the bundle's 64x256; which one the game draws is not traced (`tools/ngmexport.py` uses the bundle's). |
| `Materials/Shaders/shaders.nsa` | Text | The material library, one for the game: a block per material name (a model's part name) giving its `shader` (`charlight`, `masked`, `envmap`...), `texture`, `texture2`, `envmap` and options. `{ps2` and `{xbox` sub-blocks override for those platforms. |
| `Bundles/wolverine-t0/t1/t2.ngb` | Binary | The animations against an opponent of body class 0, 1 or 2 (`SKELETONID`, section 3): the throws and the victim's side of them. |
| `Bundles/wolverine_alt.*` | | The alternate costume. A second bundle per costume works (**tested**). |
| `HUD/hud<LANG>.1.gsh` (`eng`, `fra`, `ger`, `ita`) | Image bank | The in-match portraits, one bank for all characters (section 6, step 5). |
| `Apt/clash/portraits/c1_p0.big` | APT | Select-screen portrait, named by select-screen id (section 5; Wolverine is 1). |
| `Apt/clash/portraits/cvs1.big`, `cvs1_alt.big` | APT | Versus loading-screen portraits for the two costumes. |
| `Apt/clash/portraits/wolverine_blue.big` | APT | Story-mode portrait: only `screens/clashStoryMode.big` loads it. |

`Misc/clashMP.nsc` lists the versus arenas, with their level, intro, win and lose cutscenes ("The script record" below).

The loaders take a name and have nothing character-specific in them: `fn_8019E9DC`, `fn_8019EA38`, `fn_8019EBF8` (animations), `fn_801A0814` and `fn_801A1FC4` (models), `fn_80232C4C` (textures) and the tuning functions below.

### Models (`.ngm`)

The layout is in `tools/ngmtool.py`'s docstring; `check` parses all 114 bundles to their last byte and rebuilds them byte for byte, and its `read()`/`build()` write a new one. `tools/ngmexport.py` writes a bundle's models as glTF and `tools/gltf.py` reads glTF back. What a new model needs to know:

- **Four by-name model bundles at most are resident** (`lbl_8057E110`, slots 2-5; slot 0 is `global`). `MODEL` skips a bundle already loaded and loads nothing when all four slots are full.
- **The skeleton** ("nodes") has no rotations: each node is an offset from its parent and the negated bind position, so the inverse bind matrix is a translation. A type 2 stream is skinned on the CPU, three weights and three nodes per vertex. A mesh names at most 20 nodes. Normals are indices into the shared `Misc/NormalTable.ngn` (2609 vectors).
- **Attachments** are `{u8 node, u8 kind, u16 index, 4x4 matrix}` (Wolverine's render model has 52, Johnny Ohm's 84). They are the points effects spawn at (a `Misc/game.nfx` effect's `markertype` is the kind and `marker_index` the index) and the ends of the attack volumes. `fn_800F43D4` (`Game/fn_800F43D4.cpp`) sets up the 7 attack volumes, 0x80 bytes each at `ctrl+0x580`, each between two attachments:

  | Volume | From (kind, index) | To (kind, index) |
  |---|---|---|
  | 0, 1 | 3, 1 / 3, 2 | 5, 1 / 5, 2 |
  | 2, 3 | 21, 2 / 21, 1 | 23, 2 / 23, 1 |
  | 4, 5 | 40, 1 / 40, 2 | 42, 1 / 42, 2 |
  | 6 | 43, 0 | 44, 0 |

  Animation events 0x56/0x57 switch volume 6 on and off; only `Daredevil_RangedAttack` and `Daredevil_SuperRiseAttack` use them, with kinds 43 and 44 on his club. A volume moving more than about a metre a frame passes targets between frames (**tested**).
- **The header's data size** must cover what `fn_801A3ECC` carves for each model; every shipped bundle holds that sum plus 52 bytes per mesh plus 0 to 1,008 bytes, for something not traced. `ngmtool.data_size()` adds 0x200, which the two mod characters loaded with (**tested**).
- A model missing from every loaded bundle falls back to a loose `<name>.nod` (`fn_801A0814`, `fn_801A09F0`; version 10). None ships, so the fallback is untested.

### Animations (`.ngb`) and motion sets (`.nms`)

The `.ngb` layout is in `tools/ngbtool.py`'s docstring; `check` parses all 139 bundles (12,742 animations) to their last byte and rebuilds them byte for byte. It also decodes and encodes keys, and `pose` evaluates an animation on a model's skeleton. An animation is a run of tracks `{bone, channel, key count, keys}` with keys `{f32 frame; s16 a, b, c, d}`. Channel 0 is a rotation (`w = a / 16384`, `(x, y, z) = -(c, d, b) / 16384`, worked out from the data). Channel 1 is a translation, `(a, b, c) / d` with `d` unsigned (`unpack__6Packed`, `Game/fn_80447830.cpp`), added to the node's offset from its parent. Then come the events `{f32 frame; u16 type; u16 param; u32 value}` and the 0x50-byte extra records, which are not understood.

- **Event types** are the cases of the animation event handler `fn_800E1788` (`Game/fn_800E1788.cpp`); a type it does not handle returns 0 to the dispatcher `fn_80058C94` (`Game/fn_80058C94.cpp`), which handles the rest itself: 0x17 plays sound event `value` (`fn_801118A4`, then `fn_8010CDCC`; 0x10 goes to `fn_8010E304` instead), 0x48/0x49 start and stop the effect named by `fn_8005A534(value)` on the entity, 0x5D/0x5E and 0x61/0x62 the same with the target, 0x0D-0x0F go to `fn_8007F7A0` with `type - 0xD`. Attack volumes: `fn_800E8768(n)` switches volume `n` on and `fn_800E880C(n)` off; 0x18/0x19 are volume 0 and 0x39/0x3A volume 1 while controller flag `+0x18` 0x1000 is set (events 0x40/0x41 set and clear it along with the `IKClaws` clip 0x137), volumes 2 and 3 otherwise; 0x3C/0x3D volume 4, 0x3E/0x3F volume 5, 0x56/0x57 volume 6. 0x04 spawns the projectile named by tuning field 90 (`fn_800F0C70`); 0x23 field 168's effect, 3 units ahead and 10 up; 0x63 sets controller flag `+0x10` 0x2000 (a value of 0 clears it). 0x1A, 0x1B and 0x1C pick a value from a table by the event's value (`+0x3FC`, `+0x3F8` from fields 22-26, `+0x400`). 0x53 is the frame a hit skips to (ability 0x20000000). An effect field's id also works as an event type: `daredevil_superThrow.nad` shows field 81's effect from event 0x51 at frame 20 to 71. Types above 0x72 fall to the default of `fn_80058C94`.
- **A thrown weapon's flight is the animation.** Daredevil's club is node 39's translation keys in `Daredevil_RangedAttack.nad`, 8 m out and back; no code moves it. The game aims only by turning the actor at the target before the motion (`fn_800DDCB4`) (**tested**).
- **Two by-name animation bundles at most are resident**, in slots 2 and 6 of `lbl_8057DCA0` (guess: the two fighters'), each with its `-t<n>` variant in the next slot (3 and 7). `fn_8019EA38` loads nothing and returns 0 when both slots hold other names.
- **Motion sets** live in the registry `lbl_8066B8F4`. The six base sets `male.nms` ... `brutepeon.nms` are made at boot; they are the `basedon` targets, and a set inherits the states it leaves out. The text format is in `tools/nmstool.py`'s docstring (`check` parses all 47). A line maps a state name to a `.nad`; the state's index is its position in the DOL's name list at 0x80488A58 (`SuperAttack1` 0x2F, `SuperAttackFar` 0x33, `AirAttack` 0x3E). A set has at most 6 overlays. A state name the game does not know (`fn_8008F3B8` in `Game/fn_8008F470.c`: a case-insensitive scan of the 0x174-entry table `lbl_8054F1F0`, 0 on a miss), a `.nad` not in a loaded bundle, and a last line with no newline are all dropped silently. `dist -1` on `SuperThrow` is the long-range grab (Daredevil's cable, Spider-Man's web).

### UI archives (APT, `.gsh`, `.geo`)

The menus, the HUD overlays and the portraits are EA APT movies, Flash compiled to EA's format. Each is a nested archive `Apt/<path>.big`, a RefPack-compressed `BIGF` file (`tools/nbig.py`, `tools/refpack.py`) holding up to four files named after the archive:

| File | Contents | Tool |
|---|---|---|
| `.apt` | The movie: its characters (sprites, shapes, images, text, buttons), frames and ActionScript bytecode. Every pointer is an absolute file offset. Version 7 (677 movies) or 6 (32). | `aptdump.py` disassembles, `aptdecomp.py` turns the bytecode into statements, `aptpatch.py` edits by appending |
| `.const` | The constants the bytecode indexes, and the offset of the root movie in the `.apt`. | the same |
| `.geo` | The SHAPE characters' geometry, one record per character id: fill styles (solid, line, or a `.gsh` image with a texture matrix), triangles and lines. | `gshtool.py geo` |
| `.gsh` | The images (664 archives have a bank), C8 or C4 with an RGB5A3 or IA8 palette. An IMAGE character and a texture fill name one by its entry name (`"36"`). | `gshtool.py` |

The loose banks `HUD/hud<LANG>.1.gsh`, `.2.gsh` and `HUD/splash.gsh` have the same format. Each tool's docstring holds its layout, and its `check` rebuilds every file of its kind in `CLASH.BIG` byte for byte (`aptdecomp.py check` decompiles all 709 movies). What the game needs from an edited movie (**tested**):

- **Nothing reachable twice.** A copied sprite that shared the original's frame items and action blocks broke both copies, so a copy duplicates every frame item, action block and `PushData`/`ConstantPool` index array. Why is not traced (guess: the loader fixes up each pointer it reaches, so a shared record is fixed up twice).
- An action block keeps its address modulo 4, since operand padding depends on it.
- The archive is really compressed and its files renamed after it (`nbig.py pack` and `rename` do both; section 5, "Select-screen UI").

### Effects (`Misc/game.nfx`)

`fn_803A38DC` (unmatched) opens `game.nfx` and splits it with `strtok` on ` \r\t\n`. The file is CRLF text with `;` comments: 2,067 blocks of `<type> <name>`, one `<key> <value>` per line, and `end`. No tool reads it yet.

- **Types.** `fn_8039E22C` (unmatched) turns a type word into an effect class: `controller`, `trail`, `partsys`, `partsysdam`, `partsubfx`, `partmodel`, `glow`, `constraint`, `cloth`, `shockwave`, `psishield`, `billboard`, `billboardomni`, `volumefog`, `rain`, `partcylinder`, `actorglow`, `energybeam`, `lasertripwire`, `gibomatic2k`, `dyngeom`, `ctrldamage`, `radiuseffect`, `light`, `projectcube`, `boxproject`, `project`, `spawner`, `glass`, `meshtypeflash`, `damage`, `worldfx`. The file uses 26, most of all `partsys` (773 blocks) and `controller` (696).
- **Keys.** `fn_803944A4` looks a key up, ignoring case, in the 140 names of `lbl_804DC2F0` (`invalid`, `end`, `material`, ... `childflag`) and returns its index. Every key in the file is in the list.
- **Names.** A tuning field of type effect names a block (378 of the 382 names the `.nvb` files use exist), and so do animation events of an effect field's id (section 4, "Animations").
- **Markers.** `markertype` and `marker_index` are the kind and index of a model attachment (see "Models" above). `endmarker` and `endmarker_id` give a second point, in `constraint`, `cloth`, `controller`, `trail`, `energybeam` and `partsys` blocks; for a grab line it is on the victim (from the mod tests).
- **A controller** lists its child effects with `effectname`; the keys after each one (its own `markertype`, `marker_index`) belong to that child.
- `Misc/defaults.nfx` has one block per type, named after the type, with default values. The DOL does not name that file, so whether the game reads it is not known.
- Blocks appended to the file load, and a recoloured copy of a controller in tuning field 0x51 drew the grab line in the new colour (**tested**). A `partmodel` draws a model of a loaded bundle (Magneto's `MetalBall.nod` is a fourth model in `magneto.ngm`).

### Tuning records

`python3 tools/nvbtool.py` prints, compares and edits these files and holds their layouts (`check` rebuilds all 29 `.nvb` files and the `.ndb` byte for byte). Field meanings are in its `FIELD_NAMES`, which it prints.

- **Schema.** `Misc/defaults.ndb` has three classes: `AI` (6 fields, no tuning file uses it), `GLOBALS` (82) and `PLAYER` (251). A field id is the field's index in its class, and the class gives its type and default. `fn_801B26DC` loads it at boot, then the files `Misc/nvblist.txt` names, and keeps the `GLOBALS_Globals` record in `.sdata` `lbl_8066C6C8`.

  | Type | Tool name | Values |
  |---|---|---|
  | `0xFFFFD88A`, `0xFFFFD88B` | float, int | 169 and 21 of the `PLAYER` fields |
  | `0xFFFFD889` | string | 10: cutscene names (`mp_wl_int_1`, `ro_male_1.cut`) |
  | `0xFFFFD885` | effect | 43: effect names (`WolvClwsTrlL`, `wolvSuperBlock`) |
  | `0xFFFFD884` | template | 8: projectile template names (`proj_bioHazBlob`) |
  | `0xFFFFD886`, `0xFFFFD887`, `0xFFFFD888` | d886, vector, d888 | `AI` only |

- **A file lists only what differs from the defaults**, as groups of `{slot, type, value}` records per field. After a group's first record the loader (`fn_801B3638`) copies slot 0 over slots 1-5, whichever slot that record named. So a group that starts with slot 0 sets every slot and then the exceptions; a group that starts with another slot loses its first record, which 138 groups in the shipped files do.
- **Slots.** `fn_800ACB7C` binds the record to the entity (`+0x16C`) by its `DESCRIPTIONID` and stores the slot at `+0x170`:

  | Slot | Used for |
  |---|---|
  | 1, 2, 3 | In a versus match (`G+0x774` set), an actor whose player slot has the CPU bit (`slot+0x34` bit 2). `slot+0x64` picks: 0 gives slot 1, 2 gives slot 3, anything else slot 2 |
  | 4 | Otherwise, an actor with no player slot pointer (`fn_80085AF0`, `+0x2FC`) and `ACTOR_FLAGS` bit 0x200 |
  | 5 | Otherwise, `ACTOR_FLAGS` bit 0x80, the alternate costume |
  | 0 | Everything else, a human player's character included |

  The text getter `fn_800ACD20` ignores that slot for an alternate costume and always reads slot 5, which is where the files keep its names (`altWolvSuperBlock`, `mp_a_wl_int_1`).
- **Readers.** `fn_800B1884(entity, id)` returns a float field (386 call sites), `fn_800B18EC` an int (33) and `fn_800ACD20` an effect or string field's text (54). `GLOBALS` fields are read from `lbl_8066C6C8` with `fn_80433D20`/`fn_80433D70(record, id, 0)` (103 call sites). `python3 tools/nvbreaders.py CLASS` lists the readers. 150 of the `PLAYER` fields and 62 of the `GLOBALS` ones are read with a constant id, and 32 more `PLAYER` call sites read `base + i` from 18 bases (46, 49, 79, 90, 94, 110-125 in threes, 129, 134, 170, 173, 175, 206, 214). Of the 101 fields with no constant-id reader, 16 are set by no shipped file (58, 62, 69-71, 176-182, 197, 198, 217, 245).
- **Field names.** The DOL and the schema hold none. Junk after the NUL in the `.nvb` name buffers keeps fragments of the exporter's text (`DEFINE_FIELD(FID_PLAYER_EFFECT14, ...`, `// Rage points for superattack (Type: FLOAT Default: 14.000 ...)`), which matched three ids (47, 170, 192).

### The script record (`.nsc`)

`fn_800887AC` (`Game/fn_800887AC.cpp`) parses an `.nsc` mission or arena script (`Misc/clashMP.nsc` is the versus arena list) into 0x5C8-byte records, one per `mission` ... `endmission` block; the accessors are `Game/fn_804428E0.c`. Every `char[0x20]` field is `strncpy`'d with 0x20 and terminated by hand.

| Offset | Type | Keyword | Accessors |
|---|---|---|---|
| +0x00 | `char[0x20]` | `mission` arg 1, the record's name | `fn_80442918` |
| +0x20 | `char[0x200]` | `description` | `fn_80442964` |
| +0x240 | `char[0x20]` | `objective` arg 2 | `fn_80442C3C` |
| +0x260 | `char[0x20]` | `mission` arg 2 | `fn_80442A04` |
| +0x280 | `char[0x20]` | `mission` arg 3 | `fn_804429B4` |
| +0x2A0 | `char[0x20]` | `mission` arg 4 | `fn_80442A80`, getter `fn_80442A54` |
| +0x2C0 | `char[0x20]` | `loadscreen` arg 1 | `fn_80442B20` |
| +0x2E0 | `char[0x20]` | `loadscreen` arg 2, or arg 1 again when the line has only one | `fn_80442AD0` |
| +0x300 | `char[0x20]` | `loadtext`, and `objective` arg 1 | `fn_80442B70` |
| +0x320 | `char[0x20]` | `boss`, as `plr_<name>` or `plr_alt<name>` | `fn_804430AC` |
| +0x340, +0x3A0, +0x400 | `char[3][0x20]` each | `intro`, `extro`, `fail`; at most three each (counts at +0x47B-+0x47D) | `fn_80442C8C`, `fn_80442D24`, `fn_80442DBC` append; `fn_80443A2C`-`fn_80443B40` pick one at random |
| +0x460 | int | none: the record's own index | `fn_80442EA8`, getter `fn_80442E7C` |
| +0x464 | int | `flags`, low 16 bits (testers `fn_804432D8`-`fn_80443488`) | `fn_80442E54` |
| +0x468 | float | `teleportdist` | `fn_80442ED0` |
| +0x46C | int | `teleportdelay` | `fn_80442EF8` |
| +0x470 | int | `replayfrequency` | `fn_80442F20` |
| +0x474 | int | `replaydelay` | `fn_80442F48` |
| +0x478 | `unsigned char` | `character`, rejected unless <= 19 (a roster index) | `fn_80442F98`, getter `fn_80442FC4` |
| +0x479 | `unsigned char` | `unlockchar`, rejected unless <= 18 | `fn_80442FF4`, getter `fn_80443020` |
| +0x47A | `unsigned char` | `sacrifice`, rejected unless <= 19 | `fn_80443050`, getter `fn_8044307C` |
| +0x480 | `int[4]` | `rewards` | `fn_80442BC0`, `fn_80442C00(record, i)` |
| +0x4A4-+0x5A4 | `char[0x20]` x9 | `soundbanks`, up to nine | `fn_804430FC` |
| +0x5C4 | int | `maxblessed` | `fn_80442F70` |

`precutscene`, `postcutscene`, `unlocked` and `unlock` parse and do nothing. `profileid` (clamped to 0-5) and `gametype` are file-level settings on the owning table. Lines starting with `;`, `#` or `//` are comments. The owning table is `{profileid +0x0, gametype +0x4, count +0x8, records +0xC, current index +0x1A4}`; its int flags at `+0x1AC` (`fn_80443518`-`fn_804435A4`) are not `actor+0x1AC`.

**Physics** is Havok (`hk*`, the `hkRagdollConstraintData` ragdolls, `RagdollRecover_*`). No character-specific physics code has turned up; per-character physical tuning is most likely in the tuning fields.

---

## 5. Code That Lists Characters

Every function that references four or more character-name strings, plus the data tables and literals that bound the roster. A new character needs an entry in each, or a check that the default is acceptable.

| Where | What |
|---|---|
| `clashCharSelect_GetCharList` | Loop bound 18, and the nine script array names (section 2). |
| `Control_SetSelectInfo` (`Game/fn_80104504.cpp`) | Clamps each selected id: `charId + 1 > 0x12 ? 0x12 : charId + 1`, once per player. A 19th entry turns into the 18th unless both 0x12s are raised, in the compare and in the result (**tested**). |
| `fn_8044F070` (`Game/fn_8044EEF4.c`) | The inverse order-table search, `i <= 0x13`: one less than the table's length. |
| Roster tables `lbl_804CA51C`, `lbl_804CAB0C`, order table `lbl_804CB0FC` | `Record[20]` and `int[20]`; indices 0 and 19 are filler. |
| Select-screen UI data | Literal 18s and per-id file names in the APT scripts ("Select-screen UI" below). |
| `fn_80020E60` | Name to type ID (section 1). |
| `fn_8001C258` (0x2C0) | Turns the aura on or off ("Auras" below). |
| `fn_80023010` (0x638) | Looks up all 19 effect keys and spawns the two flame auras. |
| `fn_80114420` (0x3B4) | Per-character SFX banks ("SFX banks" below). |
| `lbl_804CF8E8` | AI profile names, `char*[31]` with a NULL end: `AI_DEFAULT`, the 18 characters alphabetically, then NPCs. An unlisted name gets `AI_DEFAULT`, so a new character works without an entry. |
| `fn_80099228`, `fn_8010CDCC`, `fn_8010D050` | Special-case type 17 (Biohazard) only, around the voice value `fn_8010CDCC` stores in `.sbss` `lbl_8066F050` and the `.sdata` `lbl_8066F060` (guess: voice handling). |
| `fn_801155A8`, `fn_801154D8`, `fn_80115308`, `fn_80115154` | Sound events, keyed `(bank << 9) \| event` in the registry `lbl_80568DB0`, with bank 2000 as the fallback. `fn_8010CDCC` passes the **type ID as the bank**, so a new type ID needs voice events under its own bank, or it has no voice. |
| `fn_801BEE2C`, `fn_801F7C68` | Story-mode boss and level lists. Not needed for versus. |

`fn_80020E60` has 3 callers and `fn_8009ABEC` 21; the table holds those that treat characters differently. The rest pass the ID on (the `Obj*` factories at 0x804580CC-0x80459A80, `fn_8010D050`, `fn_80428EEC`, `fn_80446F10`; `fn_8009EA20` through `fn_8009FF54` to `fn_800A0488` and `fn_800A0B48`, which never read it), test it against 0, or switch on values that are not characters (`fn_80098D30`). The game has only 20 jump tables, so a `switch` on the type is a compare chain, and a character with no `case` just takes the default. **Not checked yet:** code that reads `actor+0x1AC` without the getter.

### Select-screen UI

The UI is ActionScript in EA's APT format (big-endian here), in the nested `.big` archives under `Apt/clash/`. Nothing in it reads the roster size from the game. A 19th entry (id 18) was added by changing the rows below (**tested**), and a 20th (id 19) the same way (**tested**).

| Where | What |
|---|---|
| Select-screen id | 0-17, the order table's index minus one: Thing, Wolverine, Paradox, Elektra, Johnny Ohm, Spider-Man, Daredevil, Storm, Aftershock, Venom, Heatwave, Human Torch, Iron Man, Megalith, Magneto, Biohazard, DefCon, Van Roekel. Every row below is indexed by it. |
| `main.big`, `mainBE.big` | `_global.kGlobal_Max_NumChar = 18`: `CDataHub.CS_SetCharacter` ignores an id at or above it, and the select screen then stays on READY with no error. Also `g_aTable_HeroName` (18 keys: the name on the versus loading screen; a plain string works) and `oGlobal_oColourList.aAtribCol` (18 name colours). From boot to the versus select screen `main`'s values are the ones in effect (`fn_800B7C98` loads it); when `mainBE` (`fn_800B7894`) is used is unknown. |
| `screens/clashCharSelect.big` | The frame-0 script's literal arrays: `g_oLayOutList.aObject` (clip names `thumb0`-`thumb17`), `aCharObject` (18 slots), `g_aCharacterOrder` (0-17) and `g_aCharacterAudio` (18 `FE_SFX_*` names; a missing entry only loses the "ready" voice). The grid is `new CMenu(aCharObject, players, ..., 9)`: 9 columns and `floor(length / 9)` rows with empty slots skipped, so 19 entries need a 27-slot array to be reachable. The cursor is drawn at the thumbnail clip's own position. |
| `screens/clashCharSelect_thumbs.big` | The `thumb<n>` clip instances, and one exported sprite `char<id>` per thumbnail picture (`attachMovie('char' + id)`). |
| `portraits/c<id>_p0.big` | Select-screen portrait. Its REST, READY and READYALT poses are placed separately, so a picture meant to stay put needs an offset per pose. `c18_p0`, `cvs18` and `csm18` exist as placeholders; `cvs18_alt` and everything for id 19 do not. What loads `csm<id>` is not traced. |
| `portraits/cvs<id>.big`, `cvs<id>_alt.big` | Versus loading-screen portraits. The files inside a portrait archive are named after the archive. |
| `gamelib/bg_main.big` | Background tint: `gotoAndStop(id + 2)` on a 23-frame clip, so ids 18 and 19 land on existing frames. |

A RefPack stream that is not smaller than its output still loads, but the game prints `Target buffer is not large enough for inplace decompression!` (`tools/refpack.py` compresses properly). The game's `OSReport` text shows in Dolphin's log with the `OSREPORT` log type on.

### SFX banks

`fn_80114420` preloads one sound bank per active player, chosen by a `switch` on the actor's `actor+0x1AC` type ID, with no `default:`: an unlisted type loads no bank. It runs only in a match (`G+0x770` or `G+0x774` nonzero) or on the level `0_Test_Arena`. The banks line up with `fn_80020E60`'s numbering, which is what shows the two IDs share one space. A neighbouring function at 0x801140E8 uses `SFX_generic`, probably the NPCs' bank.

| ID | Bank | ID | Bank | ID | Bank |
|---|---|---|---|---|---|
| 1 | `SFX_Wolv1` | 7 | `SFX_Storm` | 13 | `SFX_DefCon` |
| 2 | `SFX_Iron2` | 8 | `SFX_Torch` | 14 | `SFX_Wink` (Paradox) |
| 3 | `SFX_Spidey` | 9 | `SFX_Devil` | 15 | `SFX_AfterShk` |
| 4 | `SFX_Venom` | 10 | `SFX_Thing` | 16 | `SFX_Ohm` |
| 5 | `SFX_Magneto` | 11 | `SFX_Roekel` | 17 | `SFX_Hazmat` (Biohazard) |
| 6 | `SFX_Elektra` | 12 | `SFX_Brigade` (Megalith) | 18 | `SFX_Heatwave` |

### Auras

The aura code keys off an **aura index**, not the type ID. `fn_80023010`'s `switch` names all 19: 0-2 are explosions, 3-10 the eight base auras and 11-18 the alternates, always base + 8. `fn_8001C258` switches indices 3, 5, 6, 7 and 8 (and their alternates) on and off per actor; `fn_80023010` spawns 4 and 10 (and their alternates) for the players in the match; nothing found so far uses 9/17. A character with no `case` simply has no aura.

| Index | Key | Character | Type ID |
|---|---|---|---|
| 0, 1, 2 | `KEY_SMALL_EXPLOSION`, `KEY_MED_EXPLOSION`, `KEY_LARGE_EXPLOSION` | | |
| 3 | `KEY_JOHNNYOHM_AURA` | `johnnyohm` | 16 |
| 4 | `KEY_HUMANTORCH_AURA` | `humantorch` | 8 |
| 5 | `KEY_IRONMAN_AURA` | `ironman` | 2 |
| 6 | `KEY_STORM_AURA` | `storm` | 7 |
| 7 | `KEY_BRIGADE_AURA` | `megalith` | 12 |
| 8 | `KEY_ROEKEL_AURA` | `roekel` | 11 |
| 9 | `KEY_HAZMAT_AURA` | `biohazard` | 17 |
| 10 | `KEY_SOLARA_AURA` | `heatwave` | 18 |

The alternate keys are `KEY_ALT<name>_AURA`. Brigade, Hazmat and Solara are codenames the roster doesn't use; the matching of those three to characters is a guess from the index order. Both functions look the keys up in the two effect managers' definition tables (`fn_80022EC8()` and `fn_80022F00()`, both in `.bss` `lbl_80515030`), caching which definition and which manager in `lbl_805200A0`/`lbl_805200EC` (-1: the key isn't loaded), and spawn the aura with `fn_8002298C`.

---

## 6. Adding a Character

**Tested**, in versus mode only: on 2026-10-12, a 19th character that reused Daredevil's model and Wolverine's motion set, type ID, cast and tuning, picked from its own tile by player 1 and by the CPU, mirror match and alternate costume included; and on 2026-10-17, characters 19 and 20 with their own model, textures, motion set, animations, tuning and portraits. Not tested: a human player 2 picking a new character, a new type ID (both mod characters reuse one), new voices, story mode, saves.

1. **Templates:** `act_<Name>`, `plr_<Name>` and `plr_alt<Name>` appended to `Misc/Global.not` (section 3; `tools/nottool.py`), then `CLASH.BIG` and `CLASH.BH` repacked (`tools/bigtool.py`). A character that reuses existing assets needs no other data: the bundles follow `MODEL` and `MOTIONSET`, and the tuning and sounds follow the reused `DESCRIPTIONID`, `CASTID` and type ID. One character's motion set drove another's model of the same body class without distortion, but a prop that the model carries and the motion set does not animate (Daredevil's club) floats.
2. **Roster (DOL):** record 19 in both roster tables and entry 19 of the order table (section 2), the loop bound in `clashCharSelect_GetCharList`, and the clamp in `Control_SetSelectInfo` (section 5). These are same-size edits in matched source. Record 19 is the last free one. For a 20th character, grow all three tables in `Game/unlockables.c` to 21 entries, pad the unit's `.data` growth to 0x200 bytes (the audio fault under "Shifted Builds" in [`baseline.md`](baseline.md)), and raise `fn_8044F070`'s bound to 0x14, the loop bound to 20 and the clamp to 0x14 (**tested**).
3. **Select-screen UI:** the APT data in section 5 ("Select-screen UI"). An `.apt`'s pointers are file offsets, so these edits can be made by appending new arrays and records to the file and redirecting a count and pointer to them (`tools/aptpatch.py`; section 4, "UI archives"). `tools/nbig.py rename` copies a portrait archive under a new id and `tools/gshtool.py set` redraws its images.
4. **Type ID (untested):** add the name to `fn_80020E60` with the free ID 19 or 20 (the alternate at `+20`), and set the same ID with property 0x70 in `act_<Name>`. `CASTID` gives the ID the auras use, and `OBJECT_SOUNDID` the one the SFX and voices use (section 1), so set both. In a test that swapped Johnny Ohm's `CASTID`, `EFFECT1` and `ACTOR_FLAGS` between the two costumes, the aura colours followed. In the code, `CASTID` picks the aura key, `ACTOR_FLAGS` bit 0x80 picks tuning slot 5 (the alternate's effect and cutscene names), and `EFFECT1` is an effect of the template's own.
5. **Per-character code and data:** handle the new type in the aura and SFX code, give it voice events under its type ID's sound bank, and name an AI profile with property 0x2E (or get `AI_DEFAULT`). Put its own model, motion set, animation bundle and textures under new names. Its own tuning needs a `PLAYER_<DESCRIPTIONID>.nvb` and a line in `Misc/nvblist.txt` (section 4; the list's buffer has 53 bytes free, and a line costs its two names plus 2). Recheck section 5's "Not checked yet". **The in-match HUD portrait** is an image named after the player template, lowercased: `plr_<name>`, `plr_<name>_rage`, `plr_alt<name>` and `plr_alt<name>_rage`, in each `HUD/hud<LANG>.1.gsh`. `fn_8000394C` (`Game/fn_80003808.cpp`) loads `hud%s.1` and looks the images up as `%s` and `%s_rage` of `fn_80131060(player)`, lowercased by `fn_801B738C`. Before that, `fn_800061CC` puts the two players' names, minus `plr_` (or everything up to the end of `plr_alt`) and lowercased, in two of the `hud<LANG>.2` overlay records ([`versus.md`](versus.md) section 4.4), so a template name must start with `plr_`; what the overlays do with the name is not known. A missing name shows the 8x8 image `x`, a white square with a grey X (**tested**). `gshtool.add_images()` adds the four images to a bank, copying an existing record of the same size.
6. **Saves:** probably unaffected (section 2): the save code does not read the roster tables. The tests ran without a memory card.
