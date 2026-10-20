# Enemy AI Map

Where the AI code is, how it is layered, and the order to decompile it in (section 6).

See also:
- The per-function loop: [`workflow.md`](workflow.md).
- The CPU slot, difficulty and match flow that hand an actor to the AI: [`versus.md`](versus.md) sections 3 and 4.1.
- The AI profile property (0x2E) and the per-difficulty tuning slots: [`characters.md`](characters.md) sections 3 and 4.

**This is a reference, not a narrative: read the section you need.** `configure.py` is the authority on which units are matched. **The class names below are this project's guesses** (`AIObject`, `AIBrain`, `AITask`). The only real AI class name in the DOL is `cAIMessages` (an `OSReport` string), so the real names probably follow `cAI*`. Renaming a class means redoing every mangled symbol that uses it.

---

## 1. How the Code Was Found

There are no AI source paths or asserts, so no file is named. The code was found from:

- **Strings.** The AI profile names `AI_DEFAULT`...`AI_FOOTBALLGUY` (0x8049A6D0, table `lbl_804CF8E8`), the behavior names `IDLE`...`POWER_STAND` (0x8049AB24-0x8049AD50), and a debug display (`"Task Stack (%d)"`, `"Mover:'%s'"`, `"Pathing: %s"`, `"Conserve: %s"`, `"Target:'%s' (%d) "`, 0x8049A91C-0x8049A9C0).
- **Matched callers.** `fn_8002C824` (level load and unload) calls the AI init `fn_80132480` and shutdown `fn_80132AAC`. The per-frame `fn_8002E6DC` calls the AI update `fn_80132600`, and `fn_8002E7F4` calls the debug draw `fn_80132838` (`Game/fn_8002E2C0.cpp`). Versus match start calls `fn_80133658`/`fn_8013367C` ([`versus.md`](versus.md) section 4.3).
- **The actor's AI pointer** is `actor+0x380` (`fn_80085980` returns it). The profile index is the short at `actor+0x384` ([`characters.md`](characters.md), property 0x2E).

Everything in the ranges below is `-O0` game code (`tools/flavor_map.py`).

---

## 2. File Map

`_GLOBAL_.I`/`_GLOBAL_.D` addresses come from `.ctors`/`.dtors`. "Edges unknown" means no static initializer marks the inner file boundaries.

| Range | Contents | Edges | Already matched |
|---|---|---|---|
| 0x8007A35C-0x80081E08 | Script command file. 0x8007A35C-0x8007C034 holds the **AI script API**: 42 functions, most of them `-O0` wrappers that resolve a handle to an actor's `AIObject` (`fn_8007A3A0`: `fn_800ACFA8`, `fn_800B0C58`, `fn_800B14A0`, `fn_80085980`), null-check it and forward one call. Their callers are the script node classes at 0x801C5E0C-0x801DFED8. From `fn_8007C034` (another resolver) on, the file is other script code | Starts after `_GLOBAL_.I` 0x8007A318; `_GLOBAL_.I` 0x80081DCC | |
| 0x800FA34C-0x800FC1F8 | **Actor-side AI component**, three classes (vtables `lbl_804F55E8`, `lbl_804F5678`, `lbl_804F5708`). `fn_800FBA70` creates the actor's AI (`fn_80133E5C`), `fn_800FBB30` destroys it (`fn_80133FA0`), and `fn_800FBE4C`/`fn_800FBE90` call into it | Inside the template registry file 0x800F9F88-0x80101A00 ([`versus.md`](versus.md) section 5, rows 10-12) | |
| 0x80131E90-0x80132480 | Not AI: a static initializer building `Color`s in `.sbss` 0x8066F0B4..., and `_GLOBAL_.I` 0x80132444. It probably closes the file that holds the last-selection module | `_GLOBAL_.I` 0x80132444 | |
| 0x80132480-0x80137F2C | **AI manager and `AIObject`** (section 3) | Static init `fn_80137D98`, `_GLOBAL_.I` 0x80137EB4, `_GLOBAL_.D` 0x80137EF0 | `Game/fn_80132480.cpp` (manager, to 0x80133C8C), `Game/fn_801343B0.cpp` (tuning load), `Game/fn_80137CEC.c` (profile lookup) |
| 0x80137F2C-0x80145CB0 | **Behaviors**: the registry (0x80137F2C-0x80138E10) and the 42 handlers (0x80138E10-0x80145B74, section 4.3) | Static init `fn_80145B74` (256 records of 0x70 at `lbl_8056A7F0`, the pool `lbl_805717F0`), `_GLOBAL_.I` 0x80145C38, `_GLOBAL_.D` 0x80145C74 | `Game/fn_80137F2C.cpp` (registry), `Game/fn_8013E99C.cpp` (`ATTACK_RANGED`), `Game/fn_80142558.cpp` (`AVOID_ACTORS`) |
| 0x80145CB0-0x80164544 | **The rest of the AI**, at least one file. In order: an unidentified system on the container `lbl_80569890` (0x80145CB0-0x80148178), perception and messages (0x80148178-0x8014A3B4), an unidentified block (0x8014A3B4-0x80150000; guess: mover and pathing), brain and task base classes (0x80150000-0x80152AE8), the task classes (0x80152AE8-0x8015D950), their constructors (0x8015D950-0x8015E2FC), shared helpers (0x8015E2FC-0x80160000), the per-profile brains and their special tasks (0x80160000-0x80164544) | Edges unknown. `_GLOBAL_.I` 0x80164EF0 ends the file that holds 0x80164544-0x80164F2C, which is not AI (called from level load and the HUD) | `Game/fn_80148178.cpp`, `Game/fn_8014A574.cpp`, `Game/fn_8014E288.cpp`, `Game/fn_80158038.cpp`, `Game/fn_80158844.cpp`, `Game/fn_8015F008.c`, `Game/fn_80161BDC.cpp`, `Game/fn_8016216C.cpp` |
| 0x80461430-0x804644B4 | **AI inline functions** in the linkonce tail ([`prodg.md`](prodg.md#inline-functions-and-the-tail-of-text)): about 190 functions, almost all 0x28-0x2C accessors, and nearly all called only from the ranges above. Includes the task base (`fn_80463A44`, `fn_80463AB4`, `fn_80463AD4`, `fn_80463DC4`, `fn_80463DEC`) and the task "done" setter `fn_804643C8` | Linkonce, so files are found by `.rodata` pools ([`versus.md`](versus.md) section 5, row 8) | |
| 0x80442010-0x80442600 | `AIObject` accessors | | `Game/fn_80442010.c` (section 5) |

Some matched units' header comments call their function a "PLAYER state" step. They are AI behaviors and tasks; fix the comment when you next touch one.

---

## 3. Layers

```
AI manager (globals)          init / update / draw / shutdown, registry of up to 48 AIObjects
  AIObject (actor+0x380)      one per AI-controlled actor; tuning floats, state bits, target list
    AIBrain (0x274 bytes)     one class per AI profile; virtual task factory
      AITask stack            vtable classes; the debug display prints the stack
        behaviors             function-pointer table by behavior id (IDLE ... POWER_STAND)
  shared helpers, perception, cAIMessages queue
Script API (0x8007A35C) and actor component (0x800FA34C) call in from outside
```

- **Manager.** `fn_80132480` (init): shuts down a previous run if the initialised flag `lbl_8066BF4C` is set, clears the registry `lbl_8056A72C[0x30]` and its count `lbl_8066BF1C`, registers the behaviors (`fn_80137F2C`), inits `lbl_80569890` (`fn_80145D8C`) and the messages (`fn_80149554`), sets `lbl_8066BF20 = 1` (AI enabled; `fn_80133658`/`fn_8013367C` set and clear it), and reads settings from an entry of the resource list `lbl_8054ED80` (`fn_804326B4`). `fn_80132AAC` (shutdown) deletes each `AIObject` (`fn_80447DBC(ai, 3)`) and undoes the rest. `fn_80132B88` and `fn_80132CDC` run `fn_80134028` / `fn_80134280` on every AI. `fn_801336F0` is a pass from the main loop. The **encounter list** (`"Encounter:"` in the debug draw) is up to 16 records of 0xDC bytes at `lbl_8056996C`, count `lbl_8066F1A8`, one per actor id (`fn_80461A3C`); add `fn_80132FE4`, remove `fn_80133078`, find `fn_80132F00`. It lies directly after the `lbl_80569890` container's first 0xDC bytes (`fn_80133078` copies its last record from `lbl_80569890 + count * 0xDC`), so `lbl_80569890` is very likely this list's system (rows 10 and 11 hold its code).
- **Creation.** `fn_80133E5C(ai, profile)` builds the brain (`fn_80136AC8`), loads the tuning (`fn_801343B0`) and registers the AI (`fn_80133444`). `fn_80133FA0` unregisters it (`fn_801334B0`).
- **Brain.** `fn_80136AC8` switches on the profile (section 4.2) and `new`s a 0x274-byte brain. The base class (constructor `fn_801507C0`, vtable `lbl_804F5CB0`) has one virtual, the task factory `fn_80150AA8(id)`. Each profile's class overrides it with a 0x78-byte method that adds its own tasks and falls back to the base.
- **Tasks.** `fn_8015105C(brain, id)` starts task `id` (callers: the script API, `fn_80134028`). `fn_80151BCC(brain)` returns the current task, and `fn_804423E8(task)` its id. Every task class derives from the base at vtable `lbl_804F5CC8` (constructor `fn_8015294C`, 0xC4) and overrides three virtuals (guess: update, enter, exit). The update returns nonzero when done, after `fn_804643C8(task, 1)`.
- **Behaviors.** `fn_80137FBC(id, name, update, enter, exit)` fills the 0x1C-byte record `lbl_80571814[id]` (`fn_80138C04`: id `+0`, started flag `+4`, name `+0xC`, then the three functions); the table is `fn_80138030`. Only `IDLE` has enter and exit functions. A handler is `(ai, record)` and returns an *action* or 0: a 0x70-byte record from the pool `lbl_805717F0` over `lbl_8056A7F0[256]` (`fn_80138738(kind, a, b)` takes one, `fn_8013880C` frees it, `fn_80138AE0` sets kind `+0x2C`, position `+0x30` and `+0x40`). `fn_801385A0(ai)` runs every behavior in the AI's enabled set (`fn_80462780(ai)`) and passes each action to `fn_80135D64`; `fn_80138868` is the "Behaviors" debug list. `fn_80138584` is the empty shutdown.

---

## 4. Data

### 4.1 `AIObject` (`actor+0x380`)

From `Game/fn_80442010.c` (whose `Obj` is this class) and `Game/fn_801343B0.cpp`. Size and constructor not yet found.

| Offset | Type | Meaning (guess) |
|---|---|---|
| +0x20 | subobject | `fn_80442010` |
| +0xD0 | subobject | `fn_804420D8`; guess: the perception record `Game/fn_80148178.cpp` fills (target ids `+0x4`, time stamps `+0x24`, owner `+0xD0` of that record) |
| +0x204 | `AIBrain *` | `fn_80442104` |
| +0x210 | subobject | `fn_804420AC`, passed to `fn_8014BB4C` |
| +0x500 | bit set | AI state bits: `fn_80442130` sets, `fn_80442174` clears |
| +0x52C | handle | The actor; `fn_8044203C` resolves it (`fn_800CD834`) |
| +0x530 | entity | The owner entity whose PLAYER tuning fields are read (`fn_80442080`) |
| +0x598 | `float[22]` | PLAYER fields 0x8B-0xA4, 0xF6, 0xF7 per CPU difficulty (`fn_801343B0`; `tools/nvbtool.py` names them "AI weight") |

### 4.2 Profiles and brain classes

The profile is the index of the `ACTOR_AI` name in `lbl_804CF8E8`. `fn_80136AC8` maps it to a brain constructor; each brain vtable is 6 words with one method, the task factory.

| Id | Profile | Brain ctor | Id | Profile | Brain ctor |
|---|---|---|---|---|---|
| 0 | `AI_DEFAULT` | `fn_801507C0` (base) | 16 | `AI_THING` | `fn_801640DC` |
| 1 | `AI_AFTERSHOCK` | `fn_801604A0` | 17 | `AI_VENOM` | `fn_801641A8` |
| 2 | `AI_BIOHAZARD` | `fn_8016056C` | 18 | `AI_WOLVERINE` | `fn_8016440C` |
| 3 | `AI_DAREDEVIL` | `fn_80161298` | 19 | `AI_PEON` | `fn_80163DAC` |
| 4 | `AI_DEFCON` | `fn_80161364` | 20 | `AI_HUMAN1` | `fn_80162C68` |
| 5 | `AI_ELEKTRA` | `fn_80161430` | 21 | `AI_HUMAN2` | `fn_80162D34` |
| 6 | `AI_HEATWAVE` | `fn_80162B9C` | 22 | `AI_HUMAN3` | `fn_8016388C` |
| 7 | `AI_HUMANTORCH` | `fn_801639B0` | 23 | `AI_BRUTE1` | `fn_80160638` |
| 8 | `AI_IRONMAN` | `fn_80163A7C` | 24 | `AI_BRUTE2` | `fn_80160704` |
| 9 | `AI_JOHNNYOHM` | `fn_80163B48` | 25 | `AI_BRUTE3` | `fn_80161174` |
| 10 | `AI_MAGNETO` | `fn_80163C14` | 26 | `AI_FLYER1` | `fn_80162764` |
| 11 | `AI_MEGALITH` | `fn_80163CE0` | 27 | `AI_FLYER2` | `fn_80162938` (derives from FLYER1) |
| 12 | `AI_PARADOX` | `fn_80164340` | 28 | `AI_FLYER3` | `fn_80162A04` (derives from FLYER1) |
| 13 | `AI_ROEKEL` | `fn_80163E78` | 29 | `AI_NONE` | `fn_80151CB8` (one null task, vtable `lbl_804F5C60`) |
| 14 | `AI_SPIDERMAN` | `fn_80163F44` | 30 | `AI_FOOTBALLGUY` | `fn_80162AD0` |
| 15 | `AI_STORM` | `fn_80164010` | other | | `fn_801507C0` |

Five brains add special tasks of their own, with large updates: BRUTE3's factory `fn_80160758` adds vtable `lbl_804F6380`; FLYER1's `fn_80161484` (also used by FLYER2/3) adds `lbl_804F6418`, `lbl_804F6450` and `lbl_804F6488` (the matched `fn_8016216C` and `fn_80161BDC` are theirs); HUMAN3's `fn_80162D88` adds `lbl_804F6568`.

### 4.3 Behaviors

Registered by `fn_80138030`; the handler is the `update` argument. Ids 0x1F and above 0x29 are unused.

| Id | Name | Handler | Id | Name | Handler |
|---|---|---|---|---|---|
| 0x00 | `IDLE` | `fn_80138E10` (+ `fn_8013922C`, `fn_80139258`) | 0x15 | `AVOID_HAZARDS` | `fn_801414C8` |
| 0x01 | `APPROACH` | `fn_801399CC` | 0x16 | `DEFEND_REGIONS` | `fn_80141D78` |
| 0x02 | `APPROACH_RANGED` | `fn_80139284` | 0x17 | `ROOFTOP_REGIONS` | `fn_8014470C` |
| 0x03 | `TOO_CLOSE` | `fn_801397C8` | 0x18 | `HOVER` | `fn_80144E30` |
| 0x04 | `PRONE` | `fn_8013B0F4` | 0x19 | `DODGE` | `fn_801420B4` |
| 0x05 | `MOVE_TO_WAYPOINT` | `fn_8013BCE8` | 0x1A | `AVOID_ACTORS` | `fn_80142558` |
| 0x06 | `AVOID_OBSTACLES` | `fn_8013C1C8` | 0x1B | `JUMP` | `fn_80142B04` |
| 0x07 | `BLOCK` | `fn_8013C3A4` | 0x1C | `AVOID_OBJECTS` | `fn_801426A0` |
| 0x08 | `ATTACK_MELEE` | `fn_8013E0C4` | 0x1D | `EVADE` | `fn_80142F80` |
| 0x09 | `ATTACK_RANGED` | `fn_8013E99C` | 0x1E | `TURN_TOWARDS` | `fn_801435F0` |
| 0x0A | `JUMP_ATTACK` | `fn_8013CD40` | 0x20 | `SWING` | `fn_8014379C` |
| 0x0B | `JUMP_ATTACK_PEAK` | `fn_8013D464` | 0x21 | `WALL_CLIMB` | `fn_80144038` |
| 0x0C | `JUMP_ATTACK_DESCEND` | `fn_8013DA7C` | 0x22 | `WALL_CLIMB_MELEE_ATTACK` | `fn_80144544` |
| 0x0D | `STRAFE` | `fn_8013F08C` | 0x23 | `WALL_CLIMB_RANGED_ATTACK` | `fn_80144628` |
| 0x0E | `FLY` | `fn_8013F438` | 0x24 | `APPROACH_MOBILITY` | `fn_80144970` |
| 0x0F | `SUSPENDED` | `fn_8013F8D0` | 0x25 | `FORCE_SUPER_BLOCK` | `fn_80144CB4` |
| 0x10 | `THROW_OBJECT` | `fn_8013F9F0` | 0x26 | `FORCE_POWER_STAND` | `fn_80144D3C` |
| 0x11 | `BODY_THROW` | `fn_801409D0` | 0x27 | `FORCE_FLY` | `fn_80144DB8` |
| 0x12 | `SWAT` | `fn_80140C10` | 0x28 | `FLYER_MOVE` | `fn_80145200` |
| 0x13 | `PICKUP` | `fn_80140E64` | 0x29 | `POWER_STAND` | `fn_80145AA8` |
| 0x14 | `SUPER_BLOCK_THROWN` | `fn_80141394` | | | |

Rename the handlers when you match them (`AIBehavior_Approach` or similar, a guess); the names are free, since the DOL is stripped.

### 4.4 Tasks

`fn_80150AA8(id)` constructs task `id` 0-0x1B with the constructors `fn_8015D950`...`fn_8015E2A4` in address order (0x58 bytes each). Each vtable is 14 words: the two base slots `fn_80463AB4`/`fn_80463AD4`, then the class's three methods. List them with a script over `.data` 0x804F5D00-0x804F6320 rather than copying them here. The task names are not in the table; the debug display (`fn_80137494`, `"Task Stack (%d)"`) prints them, so read it before you name a task.

---

## 5. Notes

- **`Game/fn_80442010.c`'s `Obj` is the `AIObject`.** Its comment says only "not G". Give it the class name when a unit next needs it.
- **Growing a unit into a matched one.** Rows 1 and 6 grow one unit across `Game/fn_801343B0.cpp` and `Game/fn_80137CEC.c`. Merge the matched source in when you reach it; if `main.dol` breaks, leave both units and carry on after it, and record why here.
- **The float and string pools** of the AI files are in `.rodata` 0x8049A5xx-0x8049BAxx. Check `extern_pool` (used by `Game/fn_80148178.cpp`) before claiming one.

---

## 6. Target Order

Work the rows in order and skip whatever is done; `configure.py` is the authority on unit status. Within a file, take the next function after the unit's current `.text` end, so that the unit grows as one contiguous range from the file's first function. If a function is stuck, record it in [`nonmatching.md`](nonmatching.md) and move on to the next row rather than leave a gap. Name a unit after its file's first function (`Game/fn_80132480.cpp`). Rows are numbered once; unit headers cite them (`docs/ai.md row N`), so don't renumber.

| # | Target | Range | Next action |
|---|---|---|---|
| 1 | AI manager | 0x80132480-0x80133C8C, unit `Game/fn_80132480.cpp` | Done |
| 2 | Behavior registry | 0x80137F2C-0x80138E10, unit `Game/fn_80137F2C.cpp` | Done. The 42 handlers keep their `fn_` names until row 13 renames them (section 4.3) |
| 3 | Brain and task bases | 0x80150000-0x80152AE8, then 0x8015D950-0x8015E2FC | The base brain (`fn_801507C0`, factory `fn_80150AA8`), start-task `fn_8015105C`, `fn_80151BCC`, the task base `fn_8015294C`; 44 functions, 25 small. Then the 28 task constructors, which share one shape |
| 4 | Per-profile brains | 0x80160000-0x80164544 | Each brain's constructor and factory (about 60 functions, mostly identical 0x54/0x78-byte pairs; section 4.2). Skip the special tasks' methods (row 12) |
| 5 | AI inline functions | 0x80461430-0x804644B4 | 195 tail functions, 185 of them 0x80 bytes or less: accessors on `AIObject`, brain and task. One small unit per run, like `Game/fn_80442010.c`; name each field in section 4.1 as it is confirmed |
| 6 | Rest of the `AIObject` file | 0x80133C8C-0x80137F2C, extending row 1's unit | Creation `fn_80133E5C`, destruction `fn_80133FA0`, reset `fn_80134028`, `fn_80134280`, `fn_80134870` (seven outside callers), the brain switch `fn_80136AC8`, per-AI update `fn_8013589C`, the debug display `fn_80137494` (0x858), static init `fn_80137D98`, `_GLOBAL_.I`, `_GLOBAL_.D`. Merge in the two matched units (section 5) |
| 7 | Actor-side AI component | 0x800FA34C-0x800FC1F8 | 39 functions, 20 small: the three classes, their constructors, and the create/destroy/update calls into the AI |
| 8 | AI script API | 0x8007A35C-0x8007C034, unit `Game/fn_8007A35C.cpp` | 42 functions: the `fn_8007A3A0` resolver and the wrappers. Name each wrapper after what it forwards to. Stop at 0x8007C034; the rest of the file is general script code |
| 9 | Shared helpers | 0x8015E2FC-0x80160000 | 28 functions called from over 200 functions in the behaviors and tasks (guesses from their use: target choice `fn_8015F7A4`, float measures `fn_8015E580`/`fn_8015E8A8`, `fn_8015F6CC` fills a `Vector`) |
| 10 | Perception and messages | 0x80145CB0-0x8014A3B4 | First identify `lbl_80569890`'s system (0x80145CB0-0x80148178); then the target list around the matched `fn_80148178`, its debug `fn_80148B50`, and `cAIMessages` (`fn_801498E8`, `fn_80149A6C`) |
| 11 | Unidentified block | 0x8014A3B4-0x80150000 | 47 functions called by tasks, the AI object and the script API (`fn_8014B63C`, `fn_8014D034`). Identify it first (guess: mover and pathing; check against the debug display's `Mover`, `Pathing`, `Conserve` and waypoint fields), then match small to large |
| 12 | Task methods | 0x80152AE8-0x8015D950, then the special tasks in 0x80160000-0x80164544 | Enter and exit methods first (41 functions of 0x80 bytes or less), then the updates. The largest are `fn_801549D0` (0x1E20), `fn_80152F74` (0x173C) and `fn_80156A88` (0x12D0) |
| 13 | Behavior handlers | 0x80138E10-0x80145CB0, extending row 2's unit | 41 unclaimed handler functions (0xC52C bytes), then static init `fn_80145B74`, `_GLOBAL_.I`, `_GLOBAL_.D`. `APPROACH` (`fn_801399CC`, 0x1728) is the largest |

Out of scope for AI: the general script code in 0x8007C034-0x80081E08 and the script node classes at 0x801C5E0C-0x801DFED8 (unless a row needs a caller's meaning), the video player from 0x80164F2C, and third-party code.

---

## 7. Open Questions

- What are the `AIObject`'s size and constructor? Neither `fn_80133E5C` nor `fn_80136AC8` allocates it, so the caller (`fn_800FBA70`'s class) probably does.
- What are the task names and ids above 0x1B? The debug display has the names.
- Is `lbl_80569890` the encounter list's system (section 3; inited and shut down with the AI; `fn_801B60F4` is its container), and what is 0x8014A3B4-0x80150000?
- How do tasks choose behaviors (`lbl_80571814`), and what reads the profile's tuning floats at `+0x598`?
- Which of the script node classes at 0x801C5E0C-0x801DFED8 are AI commands, and what are their script names (`cSpawnPeon`, `cAIEnemyVictoryScene`, `cGlobalPeonCounter` in `.rodata` 0x8049EDD0-0x8049EE90)?
