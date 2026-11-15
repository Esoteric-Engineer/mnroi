# Characters

How the game defines, selects and loads playable characters, and what a new character needs.

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

- **`ACTOR_ABILITIES` bits** (`actor+0x308`). One accessor per bit at 0x80085F7C-0x80086374 (`Game/fn_80085F7C.cpp`, each a one-line `abilities & mask`). The meanings come from reading their callers and from tests in modded builds; only rows marked **tested** were run. `nottool.py dump act_<Name>` gives each character's value. The AI (`0x80132480`-`0x80158BBC`) reads most of these bits too, and its callers were not all read.

  | Bit | Read by | Meaning |
  |---|---|---|
  | 0x1 | `fn_80085F7C`, from `fn_800CBF20`, the AI (`0x80132480`-`0x80158BBC`) and about 20 more | A flyer: Johnny Ohm, Storm, Heatwave, Human Torch, Iron Man, Magneto and Roekel have it. Lets the actor take off (below) unless `fn_800CDA20` holds |
  | 0x2 | `fn_8008603C`, from `fn_800D01A4`, `fn_800CF584`, `fn_800D25CC`, `fn_800D4F20`, `fn_800EEE48` | Wall climbing (below): Aftershock, DefCon, Elektra, Spider-Man, Venom, Wolverine. The state updates `fn_800D25CC` (at `0x800D2820`) and `fn_800D4F20` (at `0x800D51FC`) use it to hand off to WallClimb on action 7 |
  | 0x8 | `fn_8008615C`, from `fn_800D5FEC`, `fn_800D6AFC`, `fn_800E5B2C`, `fn_800F66C8` | Telekinesis (guess at the name), Magneto only. Lets the actor take props its lift class would refuse (`fn_8008572C`): any object for `WirePickup`, and with `fn_800CCA88` a catch and a full lift (`fn_800F66C8` plays motion 0xCF `CarryLiftLarge`, not 0xE6 `CarryLiftMiss`). Only with this bit does action 2 or 0xA in `WirePickup` throw the object on (`fn_800D6AFC`) |
  | 0x10, 0x20 | `fn_8008621C`, `fn_8008624C`, both only from `fn_8008572C(actor, object)` | Lifting: anyone lifts light objects, 0x10 or 0x20 medium ones, 0x20 heavy ones (`fn_800A43A0`/`fn_800A4408`/`fn_800A4438` classify the object) |
  | 0x40 | `fn_800860CC`, from `fn_800C0F48`, `fn_800DDCB4` | The zipline: DefCon, Paradox, Spider-Man, Venom. On the ground, action 9 with energy for tuning field 196 enters WallClimb if a wall allows it, else state 0x21 `Zipline` (`fn_800D572C`). With 0x80 as well and the virtual at `+0x1D0` true, the super attack ignores action 0xD (`fn_800DDCB4`) |
  | 0x80 | `fn_8008606C`, from the air states `fn_800C509C`, `fn_800C5A84` and 22 more | The wire swing for Daredevil and Spider-Man: R held and jump pressed again in the air, if energy covers tuning field 30 (**tested**). Biohazard, DefCon, Paradox and Venom have the bit too |
  | 0x100 | `fn_800862AC`, only from the Melee exit `fn_800E1570` and the Prone enter `fn_800F30E8` (`Game/fn_800F30E8.cpp`) | Both clear flag 0x8 at `+0x4` of the actor's `fn_8009AD80` object (`fn_80446784`); without the bit the flag stays. Only `fn_804661D4`, called from `fn_803D96A8` and `fn_803D9770`, sets that flag, so what it does is still unknown |
  | 0x200 | `fn_80085FDC`, from `fn_800C0F48` | The energy run: Aftershock, Biohazard, Daredevil, Elektra, Megalith, Niles, the Thing, Wolverine. On the ground with action 0xD held, the actor runs (clip 3) while energy covers tuning field 30 per step, and drops back to the walk when it does not |
  | 0x1000 | `fn_800861BC`, from `fn_800E44DC`, `fn_800E5308`, `fn_800E592C` | Always SuperBlock, for the grunts `brute3` and `human3`. Block goes straight to state 0x16 (`fn_800E44DC`), which costs no energy, needs only action 0 held, and stops effect field 0x51 on exit (`fn_800E5308`, `fn_800E592C`) |
  | 0x2000 | `fn_800860FC`, from `fn_800C0F48`, `fn_800D3DC0`, the AI | Ranged pickup: Biohazard, Magneto, Spider-Man, Venom. Action 4 with `fn_800CCA88`, on the ground or flying, calls `fn_800D5FEC` for `WirePickup` (below). The AI (`Task_FindThrowable_Update`) reaches for objects to tuning field 240 rather than 210 |
  | 0x4000 | `fn_800DDCB4`, reading `+0x308` itself | The super attack's far version (`SuperAttackFar`) with no target, straight ahead |
  | 0x8000 | `fn_8008618C`, from `fn_80084B68`, `fn_800C0F48` and 13 more | The low-energy lockout, Megalith only. Below tuning field 222 of energy the actor plays motion 0x26 `LowEnergyStun` when standing (`fn_800C0F48`), `fn_800CB7A0` and Block's `fn_800E4268` return 0, and `fn_800DD3F8` drops to Stand. While `fn_8008582C` holds, `fn_80084B68` refuses any cost that would drop energy into that window, except on a 1-in-100 roll. Not all 15 callers were read |
  | 0x20000 | `fn_8008609C`, from the dodge state `fn_800F3384` and two more | Unknown |
  | 0x100000 | `fn_80085FAC`, only from `fn_800CBF20` | Flight: the actor can take off. Every flyer but Johnny Ohm has it; clearing it and 0x1 grounds all seven (**tested** on Storm, Heatwave and Johnny Ohm) |
  | 0x400000 | `fn_8008600C`, only from `fn_8009D818` | Health regeneration: Wolverine (field 43 is 0.3). `plr_Magneto` has the bit too (`act_Magneto` does not), but `PLAYER_MAGNETO` leaves field 43 at the default 0, so it does nothing there. Each frame, unless `fn_800CCA88` holds, health moves by field 43 times the frame step while energy is at least field 31, up to the maximum. A negative rate has no such ceiling, and at 0 health it calls `fn_80030930` |
  | 0x1000000 | `fn_8008627C`, from `fn_8002FD50`, `fn_800E5308`, `fn_800E6D54` | SuperBlock hits back; every named character's template has it and no grunt's does. Every fourth frame in state 0x16, actors within 1.5 get motion 0x6F `HitReactLarge` (`fn_800E5308`). A kind-1 hit from an actor taken in that state calls `fn_80031434` on the attacker (`fn_8002FD50`), and a stopped hit in the same case calls the attacker's virtual at `+0x138` (`fn_800E6D54`) |
  | 0x2000000 | `fn_800861EC`, from `fn_800CBF20`, `fn_800D2CF8` and 47 more | A hover flyer, for `act_flyer1` and `civ_flyer3`; no named character has it. The actor takes off into state 0x25 `Hover` rather than 0x17 `Flying` (`fn_800C5A84`, `fn_800EE060`), and take-off skips the energy check on field 41 (`fn_800D2CF8`). Not all 49 callers were read |
  | 0x4000000 | `fn_8008612C`, from `fn_800C0F48`, `fn_800C509C`, `fn_800C5A84`, `fn_800D01A4`, `fn_800D05BC` | The wall run: Aftershock, Biohazard, Daredevil, Elektra, Niles, Wolverine. Action 8 held enters `WallRunHoriz` or `WallRunVert` by `fn_800D14F0`'s result (1 or 2). It also moves WallClimb's hold from action 8 to 7 (below) |
  | 0x10000000 | `fn_80086314`, from `fn_800D01A4`, `fn_800D05BC` | WallClimb holds on action 7 rather than 8, without the wall run. DefCon only |
  | 0x20000000 | `fn_80086344`, only from the hit handler `fn_800E7A4C` (`Game/fn_800E7A4C.cpp`) | A hit landed in motion 0x33 or 0x36 skips the animation ahead to its event 0x53, if that event is not already behind the current time: the thrown weapon comes back (Daredevil only). Only a hit on a kind-2 object (`fn_800B0CC0`, the kind the `PROP_*`/`CONTAINER_*` properties need) gets there. A hit on a kind-7 object (`fn_800B0C1C`, which `fn_800B0C58` also accepts for `ACTOR_*`) goes to `fn_800E6D54` and returns first, and so does a hit with no object. A character opponent never triggers the return, whether a CPU or a human controls it |

  `fn_800862DC` is true when 0x8000000 is *clear*. `fn_80086374` tests the mask 0x810004; in WallClimb's update, action 2 starts motion 0x64 `WallClimbRangedAttack` only when it and `fn_800CCA88` hold.

  **Climbing a wall** (state 8, `WallClimb`, `Game/fn_800D0084.cpp`) needs `fn_800D01A4(controller)`: ability 0x2, `fn_800CC440` false, the hold action or action 0x18 held, and a ray from 0.25 above the actor along its facing, twice `fn_800B2670` long, that hits a surface `fn_800D0084` accepts. The hold action is 7 with ability 0x4000000 or 0x10000000 and 8 otherwise. The action ids index the controller's array (`fn_800FA4E8`); for a player, the 18 combo records at `lbl_804CC810` (`Combo` in `Game/fn_800FA34C.cpp`) set them from pad-button sequences. In the update `fn_800D05BC`, releasing the hold or losing the wall falls (state 5); a second ray from 2.1 above the actor that misses is the top of the wall, which pulls up (state 0xA) if `fn_800C8CCC` allows, else leaves through `fn_800CF7E8`. Climbing takes half of tuning field 30 per step, and action 5 without action 0x18 also leaves through `fn_800CF7E8`.

  **Taking off** (state 0x17, `Flying`, registered at `0x800BBB88`) needs `fn_800CBF20(controller)`: true when ability 0x100000 is set, or when `fn_800CDA20` does not hold and 0x1 or 0x2000000 is. Every way into the state checks it along with button 9 (`fn_800CC148`) and `fn_800D2CF8`: the air states at `0x800C5438` and `0x800C5BC0`, `fn_800C0F48` and `fn_800CFD2C`.

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

  The hit test, read from the code, not run (`Game/fn_800E8768.cpp`, `Game/fn_800F43D4.cpp`, `Game/fn_801A479C.cpp`, `Game/fn_801A1908.cpp`):

  - **Lookup.** `fn_801A5104` takes a model instance, kind and index and writes the attachment's world position; `fn_801A4F78` writes its world matrix. `fn_801A51F4` and `fn_801A4EBC` are the same by kind alone, the first match. The search covers the instance's own model, then up to 4 sub-instances at `+0x10`. The attachment's matrix is applied to its node's matrix from the frame's pose; a non-null last argument rebuilds the pose first, and the volume code passes 0.
  - **A missing attachment kind.** The lookup returns 0 and the test returns 0 at once, before its query and before it stores the ends. A volume whose model lacks either kind does nothing, without an error: no target hits and no world hit. Switching it on still pays the motion's energy (`fn_800E8768`: `+0x414`, once, guarded by flag `+0x10` 0x1000).
  - **A linked entity.** While the controller's handle `+0xF0` is live (`fn_800CDA20`, `fn_800CD9B0`) and that entity has flag `+0x290` 0x80000 (`fn_800A4130`), the volume's ends are looked up on that entity's model, with its byte `+0x205` (`fn_8009AB64`) as the index for both ends. Probably a carried object, going by the handle's other callers; the flag's meaning is not known.
  - **A volume has no radius of its own.** It is a line between the two ends. The only radius is the query's, a sphere around the line's midpoint (`fn_8004E4B4`) that picks candidates: the line's length for the per-frame sweep and twice that for a one-shot. The query's mask starts with every bit set and has bits 0, 2, 7 and 8 cleared (`fn_80434C88`, `fn_80434CDC`; what the bits select is not traced), and the owner is passed through `fn_80434D18`, which other units name as the entity to ignore. It runs only if `fn_8004DCA0` returns nonzero for the midpoint (unread).
  - **One-shot** (`fn_800F46D8`). Every candidate in the sphere is hit, with no line test, at the midpoint. It returns whether any was hit.
  - **Per frame** (`fn_800E8884`). Each switched-on volume runs `fn_800F4B58`, and switching one off runs it a last time (`fn_800E880C`). For each candidate it tests this frame's line. If that misses and an earlier test stored the ends, it tests lines joining the last frame's volume to this frame's, every 0.3 units along the length, from the far end to the start. A target is only tested if it is in this frame's sphere, which fits the tested limit above.
  - **Repeat hits.** A volume keeps 12 targets per activation (`+0x30`, count `+0x60`) and skips them. A 13th and later target isn't recorded, so it can be hit again.
  - **World hits.** When no target was hit and the cooldown `+0x64` has run out, a ray from the actor toward the midpoint, at the midpoint's z and 0.2 units longer than that distance, goes to `fn_8004A758`. A hit lands through `fn_800E7A4C`, passing a 16-bit value from `fn_8008A624` (unread) when the surface's virtual `+0x18` returns 0x18, and 0 otherwise. It sets the cooldown to 0.05 and counts up `+0x6A`.

  Events 0x05, 0x1F, 0x20 and 0x21 are one-shot hits with volumes 0, 1, 4 and 5 (`fn_800E6B44`, `Game/fn_800E6B44.cpp`). In a `Melee` motion 0x9F-0xBC (`fn_800CD064`) the hit lands on the target at once, at attachment (21, 1), (21, 2), (19, 2) or (19, 1); in any other motion the volume is tested once (`fn_800F46D8`). A hit on an actor (`fn_800E6D54`, same unit) on a target in reaction motion 0x7D/0x7E, or with controller flag `+0x18` 0x8000 (`fn_800CCC28`), lands only from attacker motions 0x2C, 0x2D, 0x33-0x35, 0x39, 0x3A, 0x3C, 0x3D, 0x42, 0x45, 0x48-0x4B and 0xF1, so `SuperAttackFar` (0x33) is one of them. A blocking target (flag `+0x18` 0x100) in `SuperBlock` stops every hit. In `Block`, facing the attacker (dot of the facings below -0.56), in motion 0x4D and with flag `+0x10` 0x1, it redirects the hit: the blocker starts attack motion 0x50 (`SoftRedirect`, when the attacker has flag `+0x10` 0x2000) or 0x4F (`HardRedirect`) through `fn_800DDCB4`. Otherwise a block stops a hit from within its guard cone unless the hit strength (`+0x3F8`) beats PLAYER field 0x81 + reaction (`BlockBroken`). Read from the disassembly, not run.
- **The header's data size** must cover what `fn_801A3ECC` (`Game/fn_801A3ECC.c`) carves for each model, and nothing else uses the buffer: the model bodies go to the heap, and the unload `fn_801A2588` only tests whether a model lies in it. Every shipped bundle holds 52 bytes per mesh plus 0 to 1,008 bytes more, which is unused. `ngmtool.data_size()` gives the carved sum plus 15 for the first model's alignment (the heap block's alignment is not traced); the two mod characters loaded with 52 bytes per mesh and 0x200 more (**tested**), but the exact size is not tested in the game.
- **Shaders.** A part's material (`shaders.nsa`) names its `shader`. `fn_8023401C` (`Game/fn_8023401C.c`) registers the 29 shader names, each with a factory. The shader object keeps its textures at `+0x14 + 4n`. `glossenvmap`'s draw method binds textures 1 and 0. `glossenvcharlight` (`fn_80239258`, draw `fn_80238BDC`) binds 1, 0 and 2, and lights the third stage (`fn_8021C7E4`). The shipped materials match this: every `glossenvmap` gives `texture` and `envmap` (43), every `glossenvcharlight` adds `texture2 ge_charlight` (11), and `charlight` gives `texture` and `texture2` (`ge_charlight`, or a per-character `ge_charlight_elektra`, `_thing` or `_venom`). The parser `fn_80234F44` puts `texture` in slot 0 for every shader and hands each other key (index in `lbl_804D7A24`, 112 names) to the shader's virtual at vtable `+0x90`, so the rest depends on the shader: `glossenvmap` (`fn_80237D78`) puts `envmap` in slot 1, `glossenvcharlight` (`fn_80238ABC`) `envmap` in 1 and `texture2` in 2, and `charlight` (`fn_8023BB44`) `texture2` in 1. A part's material comes from `shaders.nsa` (loaded by `fn_802349A0`), else `<part>.nas`, else a texture named after the part on the `default` shader, else `dflt` (`Game/fn_80234628.c`).
- **The mesh record's three bytes** (mesh `+0x3E`-`+0x40`, `ngmtool.py`): copy them from a shipped character mesh. `+0x40` selects which meshes draw when the model instance has a group set (not traced for characters); the draw loop `fn_80223E38` reads none of the three.
- A model missing from every loaded bundle falls back to a loose `<name>.nod` (`fn_801A0814`, `fn_801A09F0`; version 10). None ships, so the fallback is untested.

### Animations (`.ngb`) and motion sets (`.nms`)

The `.ngb` layout is in `tools/ngbtool.py`'s docstring; `check` parses all 139 bundles (12,742 animations) to their last byte and rebuilds them byte for byte. It also decodes and encodes keys, and `pose` evaluates an animation on a model's skeleton. An animation is a run of tracks `{bone, channel, key count, keys}` with keys `{f32 frame; s16 a, b, c, d}`. Channel 0 is a rotation (`w = a / 16384`, `(x, y, z) = -(c, d, b) / 16384`, worked out from the data). Channel 1 is a translation, `(a, b, c) / d` with `d` unsigned (`unpack__6Packed`, `Game/fn_80447830.cpp`), added to the node's offset from its parent. Then come the events `{f32 frame; u16 type; u16 param; u32 value}` and the cameras, 0x50 bytes each: a placement relative to the animated entity, a mask of modes, an id and a field of view in degrees. Event 0x44 (`fn_80042378`) moves the game camera to one whose mask has its value's bit and whose id fits its param; `tools/ngbtool.py`'s docstring has the matching rules.

- **Event types** are the cases of the animation event handler `fn_800E1788` (`Game/fn_800E1788.cpp`); a type it does not handle returns 0 to the dispatcher `fn_80058C94` (`Game/fn_80058C94.cpp`), which handles the rest itself: 0x17 plays sound event `value` (`fn_801118A4`, then `fn_8010CDCC`; 0x10 goes to `fn_8010E304` instead), 0x48/0x49 start and stop the effect named by `fn_8005A534(value)` on the entity, 0x5D/0x5E and 0x61/0x62 the same with the target, 0x0D-0x0F go to `fn_8007F7A0` with `type - 0xD`. Attack volumes: `fn_800E8768(n)` switches volume `n` on and `fn_800E880C(n)` off; 0x18/0x19 are volume 0 and 0x39/0x3A volume 1 while controller flag `+0x18` 0x1000 is set (events 0x40/0x41 set and clear it along with the `IKClaws` clip 0x137), volumes 2 and 3 otherwise; 0x3C/0x3D volume 4, 0x3E/0x3F volume 5, 0x56/0x57 volume 6. 0x04 spawns the projectile named by tuning field 90 (`fn_800F0C70`); 0x23 field 168's effect, 3 units ahead and 10 up; 0x24 (`fn_800D5514`) starts that effect's handle if it is not running, plays its slots 20 and 44 and, when the actor has a body at `+0x180` (`fn_800B24AC`), sets slot 22 to that body's position (`fn_80067050`); the states `Swing`, `Zipline` and `WirePickup` handle 0x23 and 0x24 themselves, and `WirePickup`'s 0x23 differs (below); 0x05 goes to the dispatcher, which for a kind-4 prop target with flag `+0x290` 0x8000 calls `fn_8009F010(prop, 0)` (sets flag 0x400000 once, spawns the template or effect named at `+0x2B0`); 0x63 sets controller flag `+0x10` 0x2000 (a value of 0 clears it). 0x1A, 0x1B and 0x1C pick a value from a table by the event's value (`+0x3FC`, `+0x3F8` from fields 22-26, `+0x400`). 0x53 is the frame a hit skips to (ability 0x20000000). An effect field's id also works as an event type: `daredevil_superThrow.nad` shows field 81's effect from event 0x51 at frame 20 to 71. Types above 0x72 fall to the default of `fn_80058C94`.
- **A thrown weapon's flight is the animation.** Daredevil's club is node 39's translation keys in `Daredevil_RangedAttack.nad`, 8 m out and back; no code moves it. The game aims by turning the actor at the target before the motion (`fn_800DDCB4`) (**tested**), and `SuperAttackFar` at a far target also pitches the throw (the aim pose, under "From clip to skinned vertex" below).

- **The ranged pickup is state 0x22, `WirePickup`** (registered with the name string `lbl_8048C85C` in the state-table code at `0x800BCAB0`; enter `fn_800D6974`, update `fn_800D6AFC`, exit `fn_800D7370`, events `fn_800D73F0`). Read from the disassembly, not run; the update and event handlers are matched (`Game/fn_800D6AFC.cpp`, `Game/fn_800D73F0.cpp`). `fn_800D5FEC` is called from the `Flying` state's update `fn_800D3DC0` (at `0x800D423C`); `fn_800BD52C` (at `0x800BD7D8`) is the other function that sets the target.
  - **Choosing the object** is `fn_800D5FEC(controller, mode)` (`Game/fn_800D5FEC.cpp`), which also enters the state. It fails (returns 0) while `fn_800CDA20` holds. With `mode` set it takes the object it is handed: the lock-on's (`fn_8008588C`, when `fn_800CC60C` holds) or the controller's stored target (`fn_800CE0FC`), which must be a prop (`fn_800B0CC0`). Otherwise it queries the neighbours of the actor within tuning field 240 (default 10, Magneto 15) with `fn_8004E4B4` / `fn_8004E334` and takes the first that passes every test: a prop (`fn_800B0CC0`, `fn_800B0E54`), reachable (`fn_800F5CC8`, tested twice), not one `fn_800A4130` rejects, not the entity `fn_8008529C` returns for the actor, with either `fn_8008572C` or `fn_8008615C` true, no ray hit between the two (`fn_8004AC84`, mask 0x55, from 0.5 above the actor to 0.2 above the prop), the actor's height inside the prop's vertical extent (the prop's bounding box through `fn_80447218`, extent x 0.3, at least 0.3, taken down by half the actor's `fn_800B2620` height when `fn_800664C0` holds; skipped in the `Flying` state), and in front of the actor (dot product of the direction to the prop with the actor's facing at least field 239, default 0.5). I saw no scoring between candidates. The winner is stored at controller `+0x424` (`fn_800CE158`). Then, with `mode` clear, `fn_80084A60` with tuning field 196 must succeed; the actor turns to the prop (`fn_8005A828`); `fn_800CCA58` picks the clip: when it holds the state is entered (`+0x30` slot with 0x22), controller flag `+0x10` bit 0 is set and `WirePullFly` (motion 0x116) plays, otherwise the state's own enter plays `WirePull` (motion 0x115, or 0x4D when controller flag `+0x18` 0x08000000 is set).
  - **Event 0x23 here ends the wire at the object**: `fn_800B1724(object)`, the object's position when the event fires, through handle slot 28; with no object it falls back to 10 ahead of the actor and 3 up (`Swing` and the generic handler use 3 ahead and 10 up). This is why the line ends at the object in the game.
  - **Events 0x05 and 0x14 launch the object at the actor.** It gets the actor's team (`fn_8009AD04`, `fn_8009AD58`), a velocity from `fn_801BCB08` (a ballistic solve from the object's position to the actor's, at speed tuning field 113 + k, 35 for all but Iron Man's 40; k is the prop's class, `fn_800A4468`) set with `fn_80065CB0`, and the state timer is set from the flight (`fn_800BD2D0`). A prop for which `fn_800A4160` holds is hit by the actor instead (`fn_8002FD50`). Nothing reels the object in along the wire.
  - **The update** throws it on: with the action 2 or 0xA pressed it picks an opponent (`fn_800E9630`, range field 49 + k), solves a launch at them the same way (speed field 113) or, with none, throws it ahead, then sends event 0x22 and leaves for state 2 or 0x17.
  - So the reach to the object is the distance from the actor to the object at event 0x23, at most field 240 (10 m).
- **Two by-name animation bundles at most are resident**, in slots 2 and 6 of `lbl_8057DCA0` (guess: the two fighters'), each with its `-t<n>` variant in the next slot (3 and 7). `fn_8019EA38` loads nothing and returns 0 when both slots hold other names.
- **Motion sets** live in the registry `lbl_8066B8F4`. The six base sets `male.nms` ... `brutepeon.nms` are made at boot; they are the `basedon` targets, and a set inherits the states it leaves out. The text format is in `tools/nmstool.py`'s docstring (`check` parses all 47). A line maps a state name to a `.nad`; the state's index is the motion id `fn_8008A8A4` (`Game/fn_8008A8A4.cpp`) registers it under in `lbl_8054F1F0` (`SuperAttack1` 0x2F, `SuperAttackFar` 0x33, `SuperRiseAttack` 0x36, `AirAttack` 0x3E), and `lbl_8054F7C0` holds the same id's default flags. Don't count strings to get an id: option strings are mixed into the pool at 0x80488A58, the `HugeReact` block is out of id order, and 0x0, 0x41 and 0x10B have no state. A set has at most 6 overlays. A state name the game does not know (`fn_8008F3B8` in `Game/fn_8008F470.c`: a case-insensitive scan of the 0x174-entry table `lbl_8054F1F0`, 0 on a miss), a `.nad` not in a loaded bundle, and a last line with no newline are all dropped silently. `dist -1` on `SuperThrow` is the long-range grab (Daredevil's cable, Spider-Man's web).
  - **Looking a state up** is `fn_8008FC18(set, state, &flags, &speed, overlay, f)` (`Game/fn_8008F8EC.cpp`): the overlay's entry, or overlay 0's when the overlay has none (an overlay index past the set's count means 0). A run of consecutive lines for one state, none with `special` (0x400), is a set of variants: `f` in [0, 1) picks entry `f × count`, a negative `f` a random one (`fn_80171F8C`). `fn_8008FCEC` is the same returning only the clip. `fn_8008FD58` (`dist`, default 0), `fn_8008FDF0` (speed, default 30) and `fn_8008FE88` read overlay 0 only.
  - **`move` is a playback rate, not root motion.** `fn_8008FE88(set, state, v)` returns `v × clip length / move` (default 30), and `fn_80097EC4` / `fn_80098008` (`Game/fn_80097750.cpp`) use it as the clip's speed, so `move <d>` is the distance one cycle of the clip covers, and the clip plays faster the faster the actor moves.
  - **The flags act in the channel update** `fn_8019B2D4(channel, dt, animator, quiet)` (`Game/fn_8019B2D4.cpp`), which advances the time by `dt × speed`. It sends each event whose frame the time passes to the handler `lbl_8066C58C`; a handler that changes the clip or the time stops the scan. A channel fading out (flag 0x400000) loses `dt × rate` of weight first and ends at 0 (`fn_8019DACC`); flag 0x200000 or `quiet` mutes events. At the clip's end:
    - `endpause` holds the last frame and sets channel flag 0x1000, which stops all later updates; with `endtag` it sends event 0x14 once.
    - `noloop` clamps to the last frame (sending 0x14 first with `endtag`); on the animator's second channel (`+0x2C`) it also calls `fn_8019C408`. With `resetmotion` or `fidget` (0x2004) it puts the first channel back to time 0 (`fn_8019DB24`). It returns 1.
    - Otherwise the clip loops: event 0x1E per wrap, the per-track state cleared, then the events from frame 0 up to the new time.
    - The update moves nothing itself, and the generic dispatcher `fn_80058C94` ignores 0x14 and has no case for 0x1E.
  - **The pose builder takes the root motion out** (`fn_8019BA58(animator, force, root, noTargets)`, `Game/fn_8019BA58.cpp`). Once per frame (frame stamp `+0x218`) it resets one rotation and one translation per node (`+0x84`, `+0x88`, count `+0x210`) and fills them from the channels: the second channel alone, or the first under it (flag 0x8000: both added by `fn_8019D128`; flag 0x4000: the second through `fn_8019CEA0`), or the first alone. A third channel (`+0x58`) with weight above 0 is evaluated into its own arrays (`+0x8C`, `+0x90`) with its node 0 cleared, then blended in by that weight (`fn_80465728` for rotations, `fn_804304FC` for translations). Unless `noTargets` is set, the six targets at `+0x94`-`+0x120` (0x1C bytes each, `fn_8019C75C`) bend the pose; `+0xCC` is skipped while animator flag `+0x220` 0x4 is set. Then the root:
    - The root position is node 0's translation plus that of the node behind the model's attachment of kind 0x11 (`fn_801A4C58`, byte `+0x40`), which is also taken off node 1 and off the node of attachment kind 0x16.
    - The animator keeps the change since last frame at `+0x1F0` (the position itself at `+0x1C0`) and node 0's yaw change in degrees at `+0x208` (yaw `fn_801BCF14`, kept at `+0x1D8`). Flag `+0x220` 0x1 zeroes both changes for one frame.
    - Node 0's translation is then zeroed and, with more than one node, its rotation reset, so the skeleton is drawn at the entity's origin. The root movement and turn are read through the accessors in `Game/fn_8019C3AC.cpp`: `fn_8019C3AC(animator, out, noTargets)` builds the pose if stale and copies `+0x1F0`, `fn_8019C48C` copies the turn (`+0x200`, yaw change in `z`), `fn_8019C434` and `fn_8019C4D0` copy node 0's position (`+0x1C0`) and rotation (`+0x1D0`, yaw in `z`), and `fn_8019C408` sets flag 0x1.
    - **Nothing applies root motion on its own.** A state's update calls one of the appliers in `Game/fn_800BDE44.cpp`, so a state without that call stays put however far its clip's node 0 moves. Each reads the step through `fn_8019C3AC`; "velocity" is `fn_80065CB0` with the step turned into the world by the actor's matrix (`fn_800B1668`) and scaled by the clock's rate (`fn_8043B3B0(lbl_80593BE8)`); `fn_80067050` reads the current velocity back.

      | Applier | Does | Called by (state update) |
      |---|---|---|
      | `fn_800BDE44` | position += step (actor matrix `+0x78`) | Animscrub |
      | `fn_800BDF20` | velocity = step | WallClimb, LedgeHang, PullUp, WallRunHoriz, Flying, DiveAttack, Block, Ranged, both Prone states, Dodge, PickUpObject |
      | `fn_800BDFFC` | turn by the yaw step (`apply__5ActorPCv`), then velocity = step taken out of node 0's rotation (`fn_8019C4D0`, negated); nothing while `fn_8019E2CC` holds | Melee (6 calls), Swing, Zipline, HitReaction, HugeReaction, WallClimb, Replay, Animtest, PlayAnim |
      | `fn_800BE228` | turn only | Replay, HitReaction |
      | `fn_800BE2F8(self, up)` | as `fn_800BDFFC`, with the step laid in the plane normal to `up` and the current speed along `up` kept, up to 1 | Melee |
      | `fn_800BE638` | velocity = step, keeping the vertical velocity | Flying, Hover, Melee, ThrowObject |
      | `fn_800BE740` | vertical velocity = the step's | none |
  - **From clip to skinned vertex.** Read from the code; the frame order below is not traced in a running game.
    - **Sampling** (`fn_8019D128(channel, rot, pos)`, `Game/fn_8019C75C.cpp`) runs over the first `min(tracks, channel +0x24)` tracks and overwrites the node's rotation or translation. A track's bone word picks the node: with a high half of 0 the low half is the node; a high half equal to the model's `+0x158` gives node `+0x15A` + low half; a high half above 0x100 falls back to the low half; any other high half skips the track, as does a node above `channel +0x24`. Each track keeps its current key in `channel +0x20` (cleared by `fn_8019DB24`), and the next key wraps, `(k + 1) % count`. With `f = (time - k0) / (k1 - k0)`, an `f` below 0.001 takes key 0 as it is. Otherwise a translation is a linear blend, and a rotation is **a normalized lerp, not a slerp** (`fn_80465728`): `normalize(a + f (b - a))`, with `a` negated only when `dot(a, b) < -0.7`, so a pair whose dot is between -0.7 and 0 blends the long way round.
    - **Quaternions** come from keys unchanged, `(a, b, c, d) / 16384` (`fn_80465C9C`), and the first component is `w`: `fn_801BD1C0` is the Hamilton product in that order, and `fn_801BD530` rotates a vector and returns `w` = 1. `fn_801BCF14` is the yaw, in radians, from where that rotation sends the x axis.
    - **The second channel under flag 0x4000** (`fn_8019CEA0`) adds instead: no interpolation, each track's current key is added to the translation or multiplied onto the rotation, and it does nothing at time 0. It uses the raw bone word, with no chain handling.
    - **Targets** (`fn_8019C75C`, 0x1C bytes: clip `+0x0`, clip `+0x4` used while the time is negative, flags `+0x8`, time `+0xC`, model `+0x10`) find their keys by scanning from key 1, keep no state, and skip a track with a high half other than the model's `+0x158`. Flag 0x1 replaces the pose; without it they add. The interpolated add multiplies by `rot[t->bone]`, the raw bone word rather than the mapped node.
    - **The aim pose** is the target at animator `+0x94`, playing states 0x12E `IKAimUp` and 0x12F `IKAimDown`. Only `daredevil.nms` maps them (`Daredevil_PowerIKpitchUP.nad`, `Daredevil_PowerIKpitchDW.nad`), and `fn_800DDCB4` skips the aim for a set without both. It is set only when that function picks `SuperAttackFar` (0x33) for a target further than PLAYER field 1. Read from the code and worked out from the clips, not run.
      - **Elevation.** The direction to the target is `normalize(target - self)`, and its `z` goes through `fn_801BE3C4`, an arcsine in degrees. If the target has controller flag `+0x18` 0x8000 (`fn_800CCC28`) and `self.z >= target.z - 0.4`, the target's `z` is lowered by 0.8 first. Only elevation is aimed; the turn at the target handles the rest.
      - **Time.** `fn_804470BC` gets elevation / 45 with rate 0, and `fn_8044655C` clamps that to [-1, 1] and multiplies by the length of `IKAimUp`. Both clips are 45 frames, so **the frame is the elevation in degrees, up to 45**. A negative time plays `IKAimDown`.
      - **Bend.** Each clip has two rotation keys on nodes 4 (chest), 5 (head) and 22 (the throwing shoulder), from identity at frame 0 to the full angle at frame 45, blended with `fn_80465728`. A level target therefore adds nothing. The full angles are 41.1, 20.1 and 48.2 degrees up, and 16.4, 13.5 and 45.1 degrees down. The add is mode 0, so each result is `aim * rot`.
      - **Effect on the throw.** The club's chain is 39, 38, 26-22, 3, 2, 1, 0, so only node 22 moves it; nodes 4 and 5 only make the body follow. Forward kinematics of `Daredevil_RangedAttack` at its furthest frame (19) puts the club from the chest at -44.5, -30.1, -15.2, -0.5, 15.3, 31.3 and 47.0 degrees for targets at -45, -30, -15, 0, 15, 30 and 45. Its distance stays 8.76-8.92 m, against 8.84 m with no aim, and it drifts sideways up to 4 degrees at the extremes.
      - **Clearing.** Nothing at the end of the attack clears it, so the bend looks set to last into later motions until another aimed `SuperAttackFar` replaces it. The only calls that clear it are the flight state's enter (`fn_800D7CDC`) and `fn_8019E0B4`, which clears all six targets and is called from `fn_8005B1B0` and `fn_80070EF4` (not traced).
    - **Node matrices** (`fn_801A479C(instance, world, force)`, `Game/fn_801A479C.cpp`) are built once per frame (stamp `+0x3C`), unless `force`; instance flag 0x400000 freezes them. `base` is `world`, scaled by instance `+0x20` when flag 0x800 is set (`fn_804602CC`). With an animator (`+0xB0`), `fn_8019D5E0(instance, base, force)` builds the pose, calls `+0xF4(animator, +0xF8)` if set, so that hook can still edit the pose, and for each node makes `local` from the rotation and `offset + pos[i]`, then `fn_8043570C(&matrices[i], parent matrix or base, &local)`. The node's position is copied out at this point (`fn_80441334`), and a second pass applies the unbind translation (`fn_80440F30`, node `+0x10`), so the array at `+0x64` holds skinning matrices, not node placements. Without an animator the same happens with identity rotations. `+0xEC(instance, +0xF0)` is called last. What installs the two hooks is not traced.
    - **Drawing** (`fn_801A4290(instance, world, flags, root, mode)`) builds the matrices of `root` (the instance itself when 0), culls against `+0xB0` of the model, and `fn_80220980(root)` makes them the palette `lbl_8066C810` and stores them transposed as the 3x4 matrices at `lbl_8062AA70` (0x30 each, room for 128). Points transform as row vectors: `x' = m00 x + m10 y + m20 z + m30` (`fn_804708F8`).
    - **CPU skinning** (`fn_802244BC(instance, stream)`) runs once per frame per stream (stamp `+0x10C`), for stream types 1, 2, 4 and 5, from `fn_8022362C`, the mesh dispatcher, which has no direct caller. Type 1 and 4 vertices take one matrix. Type 2 and 5 take `w0 (v M0) + w1 (v M1) + w2 (v M2)`, and the weights are not normalized. **A render vertex's normal uses the rotation of the vertex's first node only**, and is not renormalized. The result goes to a 0x80000-byte scratch buffer (`lbl_80595280`): `count + render vertices` entries of 0x10 bytes plus 0x20 bytes per stream, and running out logs a message and restarts at the buffer's start, so it can overwrite streams skinned earlier in the frame. `fn_80223B50` and `fn_80223CC4` point GX at it: positions at the start, normals after `count` entries.
- **States** are registered by the code at 0x800BCAB0 through `fn_800CDDD8(id, ...)` into `lbl_8066A160`, 0x54 bytes each: pointers to member for enter `+0x10`, update `+0x8`, exit `+0x18`, events `+0x20` and contact `+0x28` (Melee's `fn_800E2788`), with a shared handler at `+0x0` (`fn_800C72B0`, `fn_800C753C` on the walls). By id: 0x01 Dead, 0x02 Stand, 0x03 Walk, 0x04 Run, 0x05 Fall, 0x06 Flail, 0x07 Jump, 0x08 WallClimb, 0x09 LedgeHang, 0x0A PullUp, 0x0B Melee, 0x0C HitReaction, 0x0D HugeReaction, 0x0E Strafe, 0x0F and 0x1D Prone, 0x11 DiveAttack, 0x12 ThrowObject, 0x13 PickUpObject, 0x14 MoveToPickUp, 0x15 Block, 0x16 SuperBlock, 0x17 Flying, 0x18 Ranged, 0x19 WallRunHoriz, 0x1A WallRunVert, 0x1B Wallflip, 0x1C Dodge, 0x1E Swing, 0x1F Animtest, 0x20 Animscrub, 0x21 Zipline, 0x22 WirePickup, 0x23 Replay, 0x24 PlayAnim, 0x25 Hover. A state switch is the controller's virtual slot 5 (`self->s5(id)`).
- **Clip end (0x14) and loop wrap (0x1E) reach the state.** `fn_80058C94` passes an event to the controller: Melee, DiveAttack and Ranged go straight to `fn_800E1788`, the rest through virtual slot 3, `fn_800CDF84`, which calls the state's event handler and, when it is missing or returns 0, the fallback `fn_800BD86C` (only 0x12 and 0x51). So the two events do nothing in a state whose handler ignores them. Where they do something:
  - Jump, Fall, Flail (`fn_800C5618`): clip end switches to Fall (5).
  - HugeReaction (`fn_800EE060`): clip end gives the actor the clip's root velocity at its end (`fn_80199FC8(clip, time, &v)`, turned into the world), then knockdowns 0x7F-0x85 chain to 0x86-0x92 (`fn_80097CE8`) and the get-ups switch state by motion: Prone (0xF), Flail (6), or Dead (1) when `fn_80085EEC` holds and otherwise Stand (2), WallClimb (8), Fall (5), Flying (0x17) or Hover (0x25).
  - Prone 0x0F (`fn_800F31BC`), Block and SuperBlock (`fn_800E4FCC`): clip end stops the second channel (`fn_8009AEC8(actor, 0)`, which resets the root and fades it out through `fn_8019A8C0`).
  - WallClimb (`fn_800D10D0`): both set flag 0x1 (and clip end calls `fn_800CC3A4`). Flying and the wall runs (`fn_800D4970`) take clip end only while flag 0x1 is set: they clear it and call `fn_80066604`; Hover's handler `fn_800D8DF8` (not matched) does the same with motion 4.
  - Wallflip (`fn_800D0020`) and Strafe (`fn_800F257C`, 0x1E only) take them and do nothing; Swing, Zipline and WirePickup handle 0x14 in their matched handlers; Melee, DiveAttack and Ranged (`fn_800E1788`) ignore both.
  - Event 0x10 is the hold-loop in Block and WallClimb/Flying: back to the clip's tag 0x11 (`fn_80199F24`, `fn_8019DB24`), in WallClimb only while the stick pushes the way the climb motion (0x11E-0x121) goes.

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

The file is CRLF text with `;` comments: 2,067 blocks of `<type> <name>`, one `<key> <value>` per line, and `end`. `python3 tools/nfxtool.py` lists and shows the blocks; its docstring holds the syntax, the value kinds and the loader's limits, and `check` rebuilds both `.nfx` files byte for byte and checks a file (`-f`) against those limits.

- **Limits that matter for a mod.** A block holds at most 28 records (an unchecked scratch table; the largest shipped block has 27). Everything shares a 300,000-byte cache, and `game.nfx` uses 290,971 bytes of it (computed from the allocator, not measured), so new blocks have about 9 KB. A block whose name is already used is loaded but never found: the first one wins. Names and type words ignore case.

- **Types.** A type word's class index is its registration order in `fn_8039E22C`: `controller`, `trail`, `partsys`, `partsysdam`, `partsubfx`, `partmodel`, `glow`, `constraint`, `cloth`, `shockwave`, `psishield`, `billboard`, `billboardomni`, `volumefog`, `rain`, `partcylinder`, `actorglow`, `energybeam`, `lasertripwire`, `gibomatic2k`, `dyngeom`, `ctrldamage`, `radiuseffect`, `light`, `projectcube`, `boxproject`, `project`, `spawner`, `glass`, `meshtypeflash`, `damage`, `worldfx`. The file uses 26, most of all `partsys` (773 blocks) and `controller` (696).
- **Keys.** `nfxtool.py keys` lists the 140 keys and their value kinds. Every key in the file is in the list.
- **Names.** A tuning field of type effect names a block (378 of the 382 names the `.nvb` files use exist), and so do animation events of an effect field's id (section 4, "Animations").
- **Markers.** `markertype` and `marker_index` are the kind and index of a model attachment (see "Models" above). `endmarker` and `endmarker_id` give a second point, in `constraint`, `cloth`, `controller`, `trail`, `energybeam` and `partsys` blocks; for a grab line it is on the victim (from the mod tests).
- **A `constraint`'s end point** (`Game/fn_803BF77C.cpp`, read from the code, not run). Slot 28 (`fn_803BA210`) copies a position into +0x110 and sets flag 0x2000000, and the update doesn't rewrite it, so that end stays fixed in the world while +0x164 follows the distance to it. With a target actor id at +0x2A8 (slot 31; slot 30 takes an actor), `fn_803BF874` rewrites +0x110 every frame from the target's `endmarker` attachment, or the target's position when that fails, so that end is carried, and it overrides anything slot 28 stored. `fn_8039453C` sets the target at effect start to the owner's controller target (`fn_800C9FD0`, +0x420) when bit 0x4 at effect +0x8C is set and `fn_800B0C58(owner)` holds; what sets that bit isn't known. The update also resolves both markers on the owner each frame (`fn_8039A230`) and passes them to the chain code (`fn_803BF1AC`, `fn_803BEC3C`, both unread). Slot 22 (`fn_803BE6BC`) isn't a setter: it adds a scaled vector to each chain point.
- **A controller** lists its child effects with `effectname`; the keys after each one (its own `markertype`, `marker_index`) belong to that child.
- `Misc/defaults.nfx` has one block per type, named after the type, with default values. The game never reads it: the effect cache opens only the literal `game.nfx` (`fn_803A38DC`), and no string in the DOL and no file in `CLASH.BIG` names `defaults.nfx`.
- Blocks appended to the file load, and a recoloured copy of a controller in tuning field 0x51 drew the grab line in the new colour (**tested**). A `partmodel` draws a model of a loaded bundle (Magneto's `MetalBall.nod` is a fourth model in `magneto.ngm`).
- **The cache size** is loaded twice with a `lis`/`ori` pair: by `fn_803A38DC` for the allocation (file offset 0x3A092C, `3C600004 606393E0`) and by its allocator `fn_803A3460` for the limit check (0x3A048C, `3D200004 612993E0`). Raising both together works: 327,680 and 311,296 bytes booted and played (**tested**). The cache comes out of the memory a match loads into, though, and what a match can spare depends on the models: with custom models and copied projectile templates, caches grown by 8,224 bytes (Johnny Ohm, Human Torch, mirror matches) and 11,296 (Johnny Ohm, mirror) loaded, while 10,272 (a custom Iron Man against Wolverine) and 27,680 made the match crash while loading (the next item).
- **Out of memory at match load** shows as a write to 0x0000000C at 0x8023F35C (Dolphin's "Invalid write"). `fn_8023F378` creates a heap and writes its first block header (`fn_8023F358`) at the start of the memory it is given, which is NULL when the allocation for that heap failed.
- **One effect, several fields.** A character's tuning can name the same block in more than one effect field, and the ids double as animation event types (section 4), so redirecting an effect means changing every field that names it: Johnny Ohm's 87/88 name `jOhmPwrStand`/`jOhmPowerOn` like 98/99 and are started by his power-up animation (Storm's 86 and Iron Man's 242 repeat their 98). Recoloured copies of all of them, and of every effect field and projectile whose slot 5 differs from slot 0, showed in the new colours (**tested** on Johnny Ohm and Daredevil).
- **A projectile's effects are named by templates**, not tuning: template field 90 (91, 92) names `proj_jOhmRangeAttL`, whose property 0x23 names the explosion template `exp_jOhmRangeAttL`, whose `EFFECT1` (0x28) is the effect `jOhmRangeAttL`. A `damage` block in that tree puts its `effect0` (`victimElecStd`, `altVictimElecStd`) on whoever it hits, so the zap left on the victim is the attacker's. Storm's and Iron Man's projectiles have the same shape (Storm's ball and Iron Man's repulsor also set 0x28 on the projectile). Copies of the two templates under new names, pointing at copied effects, worked (**tested**); no character projectile name appears in `main.dol`.

### Cutscenes (`.cut`)

`python3 tools/cuttool.py` lists a cutscene; its docstring holds the format, and `check` rebuilds all 388 playable `.cut` files byte for byte. A cutscene is a header with its audio stream names (`.asf`), the actors (name and placement matrix), and chunks streamed one at a time. Each chunk holds one `.ngb`-format animation and event list per actor. `Game/fn_80057AE8.c` swaps and lays them out.

- **Versus intros** are `mp_<xx>_int_1` and `_2` (`mp_a_<xx>_int_*` for the alternate), named by a string tuning field (section 4, "Tuning records"). Each has two cameras, `nis_camera` and `nis_camera2`, and one actor named after the character (`wolverine`), with the streams `MP_<XX>_INT_1.asf` and `_2`. The actor's name does not pick the character: `fn_800939C4` starts the intro with the character as the cutscene's target and flag 0x10000 set, so every actor not named `nis_camera*` plays on that character (the `.cut` header flags in `tools/cuttool.py`). Without that flag an actor named `victim` gets the target and any other the entity whose lowercased `CASTID` (`+0xDC`) is its name, through the `simCastList` map (`fn_80048628`).
- **Limits.** `cCutPlayer` queues a file only if its magic is 0x2715 and every chunk is at most 0x4B001 bytes. 17 shipped files fail the magic and 6 have a larger chunk (`check` lists them).

### Tuning records

`python3 tools/nvbtool.py` prints, compares and edits these files and holds their layouts (`check` rebuilds all 29 `.nvb` files and the `.ndb` byte for byte). Field meanings are in its `FIELD_NAMES`, which it prints.

- **Schema.** `Misc/defaults.ndb` has three classes: `AI` (6 fields, no tuning file uses it), `GLOBALS` (82) and `PLAYER` (251). A field id is the field's index in its class, and the class gives its type and default. `fn_801B26DC` loads it at boot, then the files `Misc/nvblist.txt` names, and keeps the `GLOBALS_Globals` record in `.sdata` `lbl_8066C6C8`.
- **Memory per tuning file.** For each `nvblist.txt` line, `fn_801B3638` gives the record a pool of three times the size of `defaults.ndb` (`fn_801B34D8`; 4,118 bytes, so 12,354) before it opens the file, so a line whose file is missing (`PLAYER Footballguy`) still costs the pool. A template uses `DESCRIPTIONID` `footballguy`.

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
| `fn_801155A8`, `fn_801154D8`, `fn_80115308`, `fn_80115154`, `fn_8011574C` | Sound events: `fn_8011574C` (`Game/fn_8011574C.cpp`) registers a callback per `(bank << 9) \| event` in `lbl_80568DB0+0x0` (134 keys) and `+0x4` (53 keys, event 1 of a record's bank, played by `fn_80114E2C`). Lookups in `+0x0` fall back to bank 2000, which has 31 events (`+0x4` has no bank 2000). `fn_8010CDCC` passes the **type ID as the bank**. Of banks 0-40 only 3, 4, 17 and 21-29 have their own `+0x0` callbacks, so a new type ID still finds bank 2000's. What plays without an SFX bank preloaded for the type (`fn_80114420`) is untested. |
| `lbl_804CF638`, via `fn_80118CB4` and `fn_80118D0C` | The voice callbacks (`Game/fn_8010FE34.cpp`) pass the speaker's type ID, and the target's when there is one, through this table: 30 words, 0-18 remap the 19 characters, 19 and 20 are 0, 21-29 are 30-32. The lookups return 0 outside 0-40, and read ids 30-40 from the next object, `lbl_804CF6B0`. **A new type ID 19 or 20 gets 0, type 0's value.** Some callbacks also pick a variant from the bank (200-249) and the speaker's type ID (4, 14, 17, 21 and 24 in bank 200; 1, 6 and 13 in bank 201). |
| `fn_801BEE2C`, `fn_801F7C68` | Story-mode boss and level lists. Not needed for versus. |

`fn_80020E60` has 3 callers and `fn_8009ABEC` 21; the table holds those that treat characters differently. The rest pass the ID on (the `Obj*` factories at 0x804580CC-0x80459A80, `fn_8010D050`, `fn_80428EEC`, `fn_80446F10`; `fn_8009EA20` through `fn_8009FF54` to `fn_800A0488` and `fn_800A0B48`, which never read it), test it against 0, or switch on values that are not characters (`fn_80098D30`). The game has only 20 jump tables, so a `switch` on the type is a compare chain, and a character with no `case` just takes the default. No code reads `actor+0x1AC` without the getter: the other loads at that offset are frame locals, fields of other classes, and the flag word of the script record `lbl_8054ED80` (its accessors at 0x8042D444, 0x804434B8-0x804435A4 and 0x8044EF70-0x8044EFD0, used by `fn_80087938` and the `clashMission_*` handlers).

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
5. **Per-character code and data:** handle the new type in the aura and SFX code, give it voice events under its type ID's sound bank, and name an AI profile with property 0x2E (or get `AI_DEFAULT`). Put its own model, motion set, animation bundle and textures under new names. Its own tuning needs a `PLAYER_<DESCRIPTIONID>.nvb` and a line in `Misc/nvblist.txt` (section 4; the list's buffer has 53 bytes free, and a line costs its two names plus 2). **The in-match HUD portrait** is an image named after the player template, lowercased: `plr_<name>`, `plr_<name>_rage`, `plr_alt<name>` and `plr_alt<name>_rage`, in each `HUD/hud<LANG>.1.gsh`. `fn_8000394C` (`Game/fn_80003808.cpp`) loads `hud%s.1` and looks the images up as `%s` and `%s_rage` of `fn_80131060(player)`, lowercased by `fn_801B738C`. Before that, `fn_800061CC` puts the two players' names, minus `plr_` (or everything up to the end of `plr_alt`) and lowercased, in two of the `hud<LANG>.2` overlay records ([`versus.md`](versus.md) section 4.4), so a template name must start with `plr_`. In versus, `fn_80006450` packs the image `ovr_<name><LANG>` (`ovr_wolverineENG`, the character's name banner) from each `HUD/hud<LANG>.2.gsh` into the `overlay2` texture; without one the banner is left out. A missing name shows the 8x8 image `x`, a white square with a grey X (**tested**). `gshtool.add_images()` adds the four images to a bank, copying an existing record of the same size.
6. **Saves:** probably unaffected (section 2): the save code does not read the roster tables. The tests ran without a memory card.
