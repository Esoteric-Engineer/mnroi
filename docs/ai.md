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
| 0x8007A3A0-0x80081E08 | Script command file. 0x8007A3A0-0x8007C034 is the **AI script API**, 41 `-O0` functions called by the script node classes at 0x801C5E0C-0x801DFED8. From `fn_8007C034` (another resolver) on, the file is other script code | Starts after the previous file's `_GLOBAL_.D` `fn_8007A35C` (in `.dtors`); `_GLOBAL_.I` 0x80081DCC | `Game/fn_8007A3A0.cpp` |
| 0x800FA34C-0x800FC1F8 | **Actor controller input**, three classes. Base (vtable `lbl_804F5708`, 0x5C0 bytes): 26 action states, this frame `+0x8` and last frame `+0xC`, and 10 analog axes of 0x30 bytes at `+0xE0`/`+0xE4`, all double-buffered. Pad subclass (`lbl_804F5678`, 0x8F0): sets the actions from the pad through the combo table `lbl_804CC810`. AI subclass (`lbl_804F55E8`, 0x5C4): `+0x5C0` is the actor's `AIObject`, and its update copies the AI's actions (`fn_8013741C`) and axes 0, 7 and 9 (`fn_80137298`) | Inside the template registry file 0x800F9F88-0x80101A00 ([`versus.md`](versus.md) section 5, rows 10-12) | `Game/fn_800FA34C.cpp` |
| 0x80131E90-0x80132480 | Not AI: a static initializer building `Color`s in `.sbss` 0x8066F0B4..., and `_GLOBAL_.I` 0x80132444. It probably closes the file that holds the last-selection module | `_GLOBAL_.I` 0x80132444 | |
| 0x80132480-0x80137F2C | **AI manager and `AIObject`** (section 3) | Static init `fn_80137D98`, `_GLOBAL_.I` 0x80137EB4, `_GLOBAL_.D` 0x80137EF0. The static init constructs `lbl_80569890` (0xDC bytes, ctor `fn_80461430`, dtor `fn_804614F8`) and `lbl_8056996C[16]` (ctor `fn_804619C8`, dtor `fn_804619F0`), so both are this file's globals | `Game/fn_80132480.cpp` |
| 0x80137F2C-0x80145CB0 | **Behaviors**: the registry (0x80137F2C-0x80138E10) and the 42 handlers (0x80138E10-0x80145B74, section 4.3) | Static init `fn_80145B74` (256 records of 0x70 at `lbl_8056A7F0`, the pool `lbl_805717F0`), `_GLOBAL_.I` 0x80145C38, `_GLOBAL_.D` 0x80145C74 | `Game/fn_80137F2C.cpp` (registry, then the handlers from `IDLE`), `Game/fn_80142558.cpp` (`AVOID_ACTORS`) |
| 0x80145CB0-0x80147DE4 | **Volume registry** `lbl_80569890` (section 4.5), one whole file | Its `.rodata` (0x8049B088-0x8049B204) ends like the behaviors file's, with linkonce pool words and a header's font-name strings up to `"invalid"`, so 0x8049B204 (`fn_80147DE4`'s 0.0) opens the next file | `Game/fn_80145CB0.cpp` |
| 0x80147DE4-0x80149554 | **Encounter record** methods (the 0xDC-byte record, `AiObj` in the unit) and the spot search around a target, one whole file | `.rodata` 0x8049B204-0x8049B2A0 ends in linkonce pool words and the header strings up to `"invalid"` | `Game/fn_80147DE4.cpp` |
| 0x80149554-0x8014A3B4 | **`cAIMessages`** (section 3), one whole file | `.rodata` 0x8049B2A0-0x8049B3C4: its two `OSReport` strings, then the header's font names up to `"invalid"`. `fn_8014A3B4`'s 0.0f at 0x8049B3C4 opens the next file | `Game/fn_80149554.cpp` |
| 0x8014A3B4-0x80164460 | **The rest of the AI**, at least one file. In order: the **Mover** `AIObject+0x210` (0x8014A3B4-0x8014BC7C, one whole file: its `.rodata` 0x8049B3C0-0x8049B468 ends in linkonce pool words, 2000 and `"invalid"`, like the encounter file's), the **path** at Mover `+0x20` (section 4.6; 0x8014BC7C-0x8014DDD4, one whole file: `fn_8014D928` is the last function that reads its `.rodata` 0x8049B468-0x8049B520, which ends in linkonce pool words and `"invalid"`. 0x8014DDD4-0x8014E288 reads no `.rodata` and the pair map has no reset there, so the `.text` edge at 0x8014DDD4 is a guess; `fn_8014E288`'s pool opens the next file at 0x8049B520), the **`+0xD0` target list** (0x8014DDD4 on into 0x801500C4: `Game/fn_801500C4.cpp`'s `Finder` is the same class, so the file does not end at 0x801500C4; the two units stay separate until the edge between its methods and the brain bases is found), brain and task base classes (0x801500C4-0x80152AE8; the first 0x6B0 bytes are the `+0xD0` record's methods and the AI_NONE brain's factory and task), the task classes (0x80152AE8-0x8015D950), their constructors (0x8015D950-0x8015E2FC), shared helpers (0x8015E2FC-0x80160428), the per-profile brains and their special tasks (0x80160428-0x80164460) | Edges unknown, except the brains' end: `fn_80164460` and `fn_801644EC` are called only from 0x80164930 and 0x80164EB4, so they open the file that `_GLOBAL_.I` 0x80164EF0 ends, 0x80164460-0x80164F2C, which is not AI (called from level load and the HUD). The brains' start fits the return flag ([`prodg.md`](prodg.md#the-function-end-branch-pair)): `fn_801603CC` leaves it clear (it carries the pair) and `fn_80160428` has no pair, so a setter, most likely a new file's header, comes between them | `Game/fn_8014A3B4.cpp`, `Game/fn_8014BC7C.cpp`, `Game/fn_8014DDD4.cpp`, `Game/fn_801500C4.cpp`, `Game/fn_80152AE8.cpp`, `Game/fn_8015D950.cpp`, `Game/fn_8015E2FC.cpp`, `Game/fn_80160428.cpp` |
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
Script API (0x8007A3A0) and actor component (0x800FA34C) call in from outside
```

- **Manager.** `fn_80132480` (init): shuts down a previous run if the initialised flag `lbl_8066BF4C` is set, clears the registry `lbl_8056A72C[0x30]` and its count `lbl_8066BF1C`, registers the behaviors (`fn_80137F2C`), inits `lbl_80569890` (`fn_80145D8C`) and the messages (`fn_80149554`), sets `lbl_8066BF20 = 1` (AI enabled; `fn_80133658`/`fn_8013367C` set and clear it), and reads settings from an entry of the resource list `lbl_8054ED80` (`fn_804326B4`). `fn_80132AAC` (shutdown) deletes each `AIObject` (`fn_80447DBC(ai, 3)`) and undoes the rest. `fn_80132B88` and `fn_80132CDC` run `fn_80134028` / `fn_80134280` on every AI. `fn_801336F0` is a pass from the main loop. The **encounter list** (`"Encounter:"` in the debug draw) is up to 16 records of 0xDC bytes at `lbl_8056996C`, count `lbl_8066F1A8`, one per actor id (`fn_80461A3C`; layout `AiObj` in `Game/fn_80147DE4.cpp`); add `fn_80132FE4`, remove `fn_80133078`, find `fn_80132F00`. A record lists the AIs near its owner and lets at most `lbl_8066BF50` of them (a setting, `fn_804616E8`) be engaged at once, rotating to the least recently engaged (`fn_80148B08`). `fn_80133078` reads its last record as `lbl_80569890 + count * 0xDC`, which works only because the 0xDC-byte volume registry `lbl_80569890` sits right before it; the two are unrelated. `fn_8013726C(ai)` returns the registry.
- **Creation.** `fn_80133E5C(ai, profile)` builds the brain (`fn_80136AC8`), loads the tuning (`fn_801343B0`) and registers the AI (`fn_80133444`). `fn_80133FA0` unregisters it (`fn_801334B0`).
- **Brain.** `fn_80136AC8` switches on the profile (section 4.2) and `new`s a 0x274-byte brain. The base class (constructor `fn_801507C0`, vtable `lbl_804F5CB0`) has one virtual, the task factory `fn_80150AA8(id)`. Each profile's class overrides it with a 0x78-byte method that adds its own tasks and falls back to the base.
- **Tasks.** `fn_8015105C(brain, id)` starts task `id` (callers: the script API, `fn_80134028`). `fn_80151BCC(brain)` returns the current task, and `fn_804423E8(task)` its id. Every task class derives from the base at vtable `lbl_804F5CC8` (constructor `fn_8015294C`, 0xC4) and overrides three virtuals: update (vtable `+0x1C`), enter (`+0x24`) and exit (`+0x2C`), defined in the order enter, exit, update. The update returns nonzero when done, after `fn_804643C8(task, 1)`.
- **Behaviors.** `fn_80137FBC(id, name, update, enter, exit)` fills the 0x1C-byte record `lbl_80571814[id]` (`fn_80138C04`: id `+0`, started flag `+4`, name `+0xC`, then the three functions); the table is `fn_80138030`. Only `IDLE` has enter and exit functions. A handler is `(ai, record)` and returns an *action* or 0: a 0x70-byte record from the pool `lbl_805717F0` over `lbl_8056A7F0[256]` (`fn_80138738(kind, a, b)` takes one, `fn_8013880C` frees it, `fn_80138AE0` sets kind `+0x2C`, position `+0x30` and `+0x40`). `fn_801385A0(ai)` runs every behavior in the AI's enabled set (`fn_80462780(ai)`) and passes each action to `fn_80135D64`; `fn_80138868` is the "Behaviors" debug list. `fn_80138584` is the empty shutdown.
- **Messages.** `cAIMessages` is a ring of 64 message pointers `lbl_80571CB0`, with count `lbl_8066F1AC`, write index `lbl_8066F1B0` and read index `lbl_8066F1B4`. Tasks (0x8015AB3C-0x8015BEA0) post with `fn_80149A6C(kind, fmt, target, ...)`, where `fmt` is a format string for the arguments (`"%udl %udl"` for kinds 0 and 1, `"%udl"` for kind 2) that is only tested for null. A message is kind `+0`, target actor id `+4` and, for kinds 0 and 1, a word `+8`. Delivery calls the unmatched script functions on the target actor: kind 0 `fn_8007EFE0(actor, word)`, kind 1 `fn_8007F184(actor, actor of word)`, kind 2 `fn_8007F2C4(actor, 0)`.

---

## 4. Data

### 4.1 `AIObject` (`actor+0x380`)

From `Game/fn_80442010.c` (whose `Obj` is this class) and `Game/fn_80132480.cpp`. Size 0x5F0: `fn_800FBA70` allocates it and stores it at its own `+0x5C0`. Constructor `fn_80133C8C(ai, entity)`.

| Offset | Type | Meaning (guess) |
|---|---|---|
| +0x0 | handle | The entity passed to `fn_80133E5C` (init) |
| +0x8 | `float` | 1.0 after construction and init |
| +0xC, +0x14 | bit sets | Of 0x41 and 0x20 bits (`fn_80461828` sizes them). `+0xC` takes the conditions the `+0xD0` update `fn_8014E648` sets (target range bands 5-10 against tuning 209-213, encounter 3/4, target state 0x25-0x31, rays 0x12-0x18, and more). `+0x14` holds event bits 1-10: `fn_8013646C(ai, event, src, other)` sets one, `fn_80136678` clears it when its tick expires; 7 and 8 last one update |
| +0x1C, +0x20, +0x24 | handles | Resolved through `fn_800ACFA8` by accessors the behavior handlers call; `fn_80442010` returns `&+0x20`. `+0x1C` is the last event's source, `+0x20` / `+0x24` the other actor of event 2 / 6 |
| +0x28-+0x40 | `int` | Cleared by reset `fn_80134280`. `+0x28` is `fn_8009B04C(src)` of event 4; `+0x2C`, `+0x30`, `+0x34`, `+0x38`, `+0x3C`, `+0x40` the ticks of events 1, 6, 4, 2, 9, 10, which expire after 3000 (1, 6, 2) or 1000 ticks |
| +0x44 | `int[26]` | Cleared by the constructor and every update; `fn_8013741C` copies it out |
| +0xAC | list | `fn_801B5BA8(4, 1.0f)`, then `fn_801B5E38(0x2B)`. The queued actions (section 3, Behaviors); `fn_804621DC(action)` is its behavior id, which the debug display names from `lbl_80571814` |
| +0xD0 | subobject | Constructor `fn_80461904` (a bit set at its `+0xFC`); `fn_804420D8`. Not the encounter record (other layout). Its methods, in `Game/fn_8014DDD4.cpp` and `Game/fn_801500C4.cpp`: owner `AIObject *` `+0x0`, count `+0x4` and handles `[16]` `+0x8` of the actors within 10 of the owner (`fn_8014FAF4`, query bits 0 and 7), count `+0x48`, handles `[16]` `+0x4C` and query slot `+0x20` floats `[16]` `+0x8C` (guess: distances) of the actors within 10 that `fn_8015ED50` sees (`fn_8014FD94`, query bits 2 and 8), target handle `+0xE4` (`fn_801501AC` sets, `fn_80150200` resolves, `fn_80150258` validates and clears; `fn_80134870` reads it), best target handle `+0xCC` (`fn_8014F8BC`, every 1000 ticks), copied to `+0xD8` on its own 1000-tick timer, nearby-actor handles `+0xE8` and `+0xEC` (`fn_8015F7A4` modes 2 and 1, every 3000 ticks; while held they set `AIObject+0xC` bits 11 and 13), `unsigned` ms the target has been in (`+0xD0`) and out of (`+0xD4`) `fn_8015EE34(ai, target)` (guess: line of sight), hit handles `+0xF0`-`+0xF8` of the three 2.0 rays `fn_8014E648` casts every 500-1000 ticks (`+0x130`), the target's `fn_800B13D8` id `+0x104`, a 200 ms `unsigned` countdown `+0x108` started when the target's `fn_80086B6C` turns on (previous and current value `+0x10C`, `+0x110`), timers `+0x114`-`+0x130` on the clock `lbl_80593BE8` (reset `fn_8014DEB8` staggers them by `fn_8015EA18(250)`) |
| +0x204 | `AIBrain *` | `fn_80442104` |
| +0x210 | Mover | 0x2F0 bytes, constructor `fn_80461A68`, methods 0x8014A3B4-0x8014BC7C. `AIObject *` `+0x0`, its entity (`fn_80442080`) `+0x4`, dest-thing handle `+0x8` (mode `DEST_THING`), last path rebuild tick `+0xC` and rebuild interval `+0x10` (2000), path `+0x20` (section 4.6; `Pathing: YES` when set, `fn_80461B58`), `int` `+0xD0`, `Vector` `+0xE0` the mean of the first `+0x274` entries of the ring `Vector[24]` `+0xF0` (`fn_8014B420(mover, point)` writes at index `+0x270`), a flag `+0x27C` and point `+0x280` (`fn_80461BF8` sets), a flag `+0x294` and point `+0x2A0` (`fn_80463410` sets), `float` `+0x278` (seconds below flat speed 1.5 while not steering; guess: stuck timer), waypoint index `+0x290` (script waypoint list; -1 none, which `fn_8014B518` leaves unchanged), `int`s `+0x2B0`, `+0x2C4`, `Vector` `+0x2E0`, `Vector` `+0x2A0`, `Vector` `+0x2D0` (look-ahead: position plus `+0xE0` times speed, dt and 30), `int` `+0x2B8` (a flag set while the actor is within reach of and above its target, held 3000 ticks by the countdown `+0x2BC`), `int` `+0x2C0`. `fn_804420AC`, passed to `fn_8014BB4C` |
| +0x510-+0x51C | `int`, `int`, `unsigned` x2 | `+0x510` is 1 after construction and reset. Reset sets `+0x518`, `+0x51C` to `fn_8015EA18(8000) + 15000`. The update counts down `+0x518` while `+0x514` is set and `+0x51C` while it is clear, and flips `+0x514` when one runs out, reloading it from `fn_80461F3C` (0-100); `fn_801368B8` and `fn_801369B0` read `+0x514` |
| +0x500 | bit set | AI state bits, 42 of them: `fn_80442130` sets, `fn_80442174` clears |
| +0x508 | bit set | 42 bits. `fn_80463994(ai, n)` tests one; bits 0-3, 5 and 6 switch on parts of `fn_8014E648` (range bands, the `+0xE8`/`+0xEC` searches, bit 15, target state, `fn_8014E044`) |
| +0x52C | handle | The actor; `fn_8044203C` resolves it (`fn_800CD834`) |
| +0x530 | entity | The owner entity whose PLAYER tuning fields are read (`fn_80442080`). Its `+0x304` bit 0x20000000 is set by a teleport and makes the next update play `peonTeleQuick`; its `+0x308` bit 0x4000 makes SEARCH use tuning field 211 for 212 and 213. Its vptr is at `+0x198`; PRONE tests slot `+0x1D0` (`int (float)`, called with 0.15) |
| +0x524, +0x528, +0x590, +0x594 | `int` | Each with a getter and a setter; +0x520, +0x538, +0x560, +0x564 are `int`s too. `+0x520` counts down to 0; when `+0x524` runs out the update flips `+0x528` and reloads `+0x524` from `fn_800B18EC(actor, 0xB9)` (to 1) or `0xB8` (to 0) |
| +0x53C | `unsigned` | Teleport cooldown end tick, 0 when not armed (`lbl_8066BF38` ticks) |
| +0x550, +0x554 | `int` | Handles from `fn_80393D0C(actor, "peonTeleQuick", 0xFF, 0xFF)` (guess: a sound) |
| +0x564 | `int` | Latch for `fn_80135668` (teleport task 0xB target) |
| +0x568, +0x570 | `int`, `Vector` | A flag and a point, set together by `fn_80461E58` |
| +0x558, +0x55C | `unsigned` | End ticks of two timers on the clock `lbl_80593BE8` (`fn_8042EFF8` ticks); `fn_80464230`/`fn_804642B8` return 1 once reached. Reset sets them to `fn_8015EA18(7000)` plus 15000 and 20000. Guess: cooldowns |
| +0x540, +0x580 | `Vector` | |
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
| 13 | `AI_ROEKEL` | `fn_80163E78` | 29 | `AI_NONE` | `fn_80151CB8` (vtable `lbl_804F5C98`, factory `fn_801506B4`: id 1 is the null task, constructor `fn_80151D0C`, vtable `lbl_804F5C60` with three methods returning 1; other ids use the base) |
| 14 | `AI_SPIDERMAN` | `fn_80163F44` | 30 | `AI_FOOTBALLGUY` | `fn_80162AD0` |
| 15 | `AI_STORM` | `fn_80164010` | other | | `fn_801507C0` |

Base `AIBrain` layout (0x274 bytes, `Game/fn_801500C4.cpp`): `AIObject *` `+0x0`, its `+0x530` entity `+0x4`, `fn_80085954(entity)` `+0x8`, `+0xC` (cleared on start, otherwise unknown), current task `+0x10` (top of the stack), task timer end tick `+0x14` (unsigned, `fn_8042EFF8` ticks; 0 when off) and length `+0x18`, a `BitSet` `+0x1C` (`fn_80151C8C`; the special tasks alternate bits 0 and 1 on the task timer), task stack count `+0x24` and tasks `[16]` `+0x28` (`fn_8015105C` pushes, `fn_8015123C` pops; index 0 is never popped), history ring of 64 `{task id, start tick}` pairs `+0x70` with used count `+0x68` and next index `+0x6C`, vtable `+0x270`. Task id is `fn_804423E8(task)`.

A task's vtable is at `+0x24`. Slot `+0x18` runs every frame on every task in the stack, top first (update); `+0x20` runs on a task when it becomes the top, pushed or uncovered by a pop; `+0x28` runs on the top task when it is covered or popped. The names enter/exit for the last two are guesses. `fn_80463AF4(task)` nonzero means the task is finished and gets popped.

A brain's factory handles its own task ids and passes the rest to its base's factory. Most named-character profiles derive from an intermediate brain with no tasks of its own (ctor `fn_80164274`, vtable `lbl_804F66C0`, factory `fn_801641FC`); BRUTE1-3, HUMAN1-3, FLYER1 and PEON derive from the base, FLYER2/3 from FLYER1. Special tasks replace base ids: BRUTE3 and HUMAN3 id 3, FLYER1 ids 1, 3 and 9.

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

`fn_80150AA8(id)` constructs task `id` 0-0x1B with the constructors `fn_8015D950`...`fn_8015E2A4` in address order (`Game/fn_8015D950.cpp`). Task `id`'s vtable is `lbl_804F62E8 - 0x38 * id`, and only MOVETO (0xB) constructs a member, a `Vector` at `+0x30`. Each vtable is 14 words: the two base slots `fn_80463AB4`/`fn_80463AD4`, then the class's three methods in the order update, enter, exit. The methods are in id order, except that GOGETANDTHROWAT's follow GETANDTHROWAT's and MOBILITYCHARGE's (`fn_8015D12C`...) come before POWERSTAND's. List them with a script over `.data` 0x804F5D00-0x804F6320 rather than copying them here.

Task names, from the `char *` table `lbl_804CFB58[id]` (`TASK_` prefix dropped): 0 SLEEP, 1 SEARCH, 2 MELEE, 3 RANGED, 4 FINDTHROWABLE, 5 FINDWIELDABLE, 6 POSSESS, 7 CARRYTHROWABLE, 8 WIELDING, 9 ATTACKTHING, 0xA BUZZPLAYER, 0xB MOVETO, 0xC FORCECONTROL, 0xD STOP, 0xE ENSLAVE, 0xF FORCEJUMP, 0x10 SWING, 0x11 GETANDTHROWAT, 0x12 WALLCLIMB, 0x13 PLAYANIM, 0x14 RANGEDONLY, 0x15 CLIMBATTACK, 0x16 FORCESUPERBLOCK, 0x17 FORCEPOWERSTAND, 0x18 HOVERANDFIRE, 0x19 POWERSTAND, 0x1A GOGETANDTHROWAT, 0x1B MOBILITYCHARGE. AI_NONE's id 1 is its null task, not SEARCH.

Base task layout (0x28 bytes, `fn_8015294C`): `AIObject *` `+0x0`, its brain (`AIObject+0x204`) `+0x4`, saved target handle `+0x8` (`fn_80152A10` copies the AI's target in when the task becomes the top; `fn_80152A78` writes it back to the `+0xD0` record when the task is covered or popped), name `+0xC`, `BitSet` `+0x10` (the AI's state bits `+0x500`, saved by `fn_80463B20` and restored by `fn_80463B60`), id `+0x18` (`fn_804423E8`), done flag `+0x1C` (`fn_804643C8`), `int` `+0x20` (`fn_80442414` writes, `fn_804643F0` reads: SEARCH sets it on a MELEE it starts under state bit 0x2E, and MELEE update clears it and reweighs its choices), both zeroed, vtable `+0x24`.

RANGED's enter and exit clear its `int` `+0x28`. Task members the script API sets right after starting a task: RANGEDONLY `+0x28` (script handle of the target, 0 for the current enemy; then it calls slot `+0x20`); GETANDTHROWAT and GOGETANDTHROWAT `+0x28` and `+0x2C` (script handles: the thing, the target); PLAYANIM `+0x28` (anim id) and `+0x2C` (loop: replay when the animation ends, else finish); HOVERANDFIRE `+0x28` (set to 1, it keeps the task from ending; enter clears it).

Deleting a task is deferred: `fn_80463C24` queues up to 16 in `lbl_80571DB0` (count `lbl_8066BF80`), and `fn_80463C9C` deletes them all.

### 4.5 Volume registry (`lbl_80569890`)

Volumes the scripts register by entity handle, through the manager wrappers `fn_8013379C`-`fn_801339C8`. Six lists (`fn_801B6040` add, `fn_801B686C` find, `fn_801B6768` remove) at `+0x4 + 0x24 * n`. A volume is a 0x330-byte base (base constructor `fn_8046303C`): handle `+0x0`, centre `+0x10`, edge count `+0x20`, then 16 edge starts `+0x30`, ends `+0x130` and normals (a guess) `+0x230`. `fn_80146ED0` builds the edges from the entity's collision hull (`fn_8009AD80`), in world space.

| List | Adds / removes | Kind | Read by |
|---|---|---|---|
| 0 `+0x4` | `fn_801477B0` / `fn_80147884` | 0x340, owner `+0x330` | teleport spot test `fn_80134940` (rejects spots inside, `fn_801464E4`); `fn_801600DC` (a path crossing one, `fn_80146A88`, is blocked); `AVOID_HAZARDS` |
| 1 `+0x28` | `fn_80147968` / `fn_80147A20` | 0x340, actor id `+0x330` | `fn_80147ACC(actor)` finds the actor's volume; `fn_80134BE0` keeps the AI inside it |
| 2 `+0x4C` | `fn_80147B88` | 0x330 | `fn_801475D8`: a point inside any one's hull; `AVOID_HAZARDS`, only while `fn_800CE4D0` holds |
| 3 `+0x70` | `fn_80147C40` | 0x330 | |
| 4 `+0x94` | `fn_80147CF8` / `fn_80147D68` | bare handles | `AVOID_HAZARDS` steers away from those within 6 |
| 5 `+0xB8` | `fn_8014601C` | path links that climb more than 1 | `fn_8014630C`, called by tasks `fn_801549D0` and CLIMBATTACK enter `fn_8015C8BC` |

### 4.6 Path (`Mover+0x20`)

0xB0 bytes; methods 0x8014BC7C-0x8014DDD4, linkonce accessors from 0x804623BC (is-built) to 0x804637BC. Build to an actor `fn_8014BC7C` or a point `fn_8014BE08`, rebuild `fn_8014C31C`, update `fn_8014D034`, reset `fn_8014C660`, waypoint arrival test `fn_8014C6D8`.

| Offset | Type | Meaning (guess) |
|---|---|---|
| +0x0, +0x4 | `unsigned`, `void *[18]` | Spot count and spots |
| +0x4C | `int` | `fn_80463204(ai)` at each build |
| +0x50 | spot | Next spot |
| +0x54 | `unsigned short` | Flags: 3 on build, reset clears 1, reaching a spot clears 2, 8 from the build's flag argument, 0x20 when the route query returns 1; the update sets 0x80 and 0x8000 and clears 0xC0 |
| +0x58 | spot | Current spot |
| +0x5C | `AIObject *` | |
| +0x60, +0x70, +0x74 | `Vector`, handle, world | Destination point, actor (`fn_800B13D8`; 0 for a point) and its world |
| +0x80, +0x90 | `Vector`, waypoint | Goal point and current waypoint, read by the arrival test |
| +0x94 | `unsigned` | Rebuild deadline: clock (`lbl_80593BE8`) + 5000 |
| +0x98 | `int` | Selects the arrival test's waypoint branch |
| +0x9C | `unsigned` | Spot search mask (`fn_801370B0`) |

---

## 5. Notes

- **`Game/fn_80442010.c`'s `Obj` is the `AIObject`.** Its comment says only "not G". Give it the class name when a unit next needs it.
- **Teleport globals.** `lbl_8066BF54` is the actor being teleported while `fn_8009C55C` runs, read by the spot test `fn_80134940`; `lbl_8066BF3C` is the spot's minimum distance from the target point and `lbl_8066BF40` the chance to accept a spot that fails `fn_801B9324` (guess: a camera view test); an AI farther than `lbl_8066BF30` from its target point may teleport. `fn_801370B0` builds the spot search mask from the actor's movement flags.
- **The float and string pools** of the AI files are in `.rodata` 0x8049A5xx-0x8049BAxx. Check `extern_pool` (used by `Game/fn_80147DE4.cpp`) before claiming one.

---

## 6. Target Order

Work the rows in order and skip whatever is done; `configure.py` is the authority on unit status. Within a file, take the next function after the unit's current `.text` end, so that the unit grows as one contiguous range from the file's first function. If a function is stuck, record it in [`nonmatching.md`](nonmatching.md) and move on to the next row rather than leave a gap. Name a unit after its file's first function (`Game/fn_80132480.cpp`). Rows are numbered once; unit headers cite them (`docs/ai.md row N`), so don't renumber.

| # | Target | Range | Next action |
|---|---|---|---|
| 1 | AI manager | 0x80132480-0x80133C8C, unit `Game/fn_80132480.cpp` | Done |
| 2 | Behavior registry | 0x80137F2C-0x80138E10, unit `Game/fn_80137F2C.cpp` | Done. The 42 handlers keep their `fn_` names until row 13 renames them (section 4.3) |
| 3 | Brain and task bases | 0x801500C4-0x80152AE8, unit `Game/fn_801500C4.cpp`, then 0x8015D950-0x8015E2FC, unit `Game/fn_8015D950.cpp` | Done |
| 4 | Per-profile brains | 0x80160428-0x80164460, unit `Game/fn_80160428.cpp` | Done, with the special tasks |
| 5 | AI inline functions | 0x80461430-0x804644B4 | Done. Units split where the `.rodata` pool changes (`extern_pool` in `configure.py`) |
| 6 | Rest of the `AIObject` file | 0x80133C8C-0x80137F2C, extending row 1's unit | Done to 0x80137D98. Static init `fn_80137D98`, `_GLOBAL_.I`, `_GLOBAL_.D` are blocked on class names ([`nonmatching.md`](nonmatching.md)) |
| 7 | Actor-side AI component | 0x800FA34C-0x800FC1F8, unit `Game/fn_800FA34C.cpp` | Done |
| 8 | AI script API | 0x8007A3A0-0x8007C034, unit `Game/fn_8007A3A0.cpp` | Done |
| 9 | Shared helpers | 0x8015E2FC-0x80160428, unit `Game/fn_8015E2FC.cpp` | Done |
| 10 | Perception and messages | 0x80145CB0-0x8014A3B4 | Done, three files (section 2) |
| 11 | Mover, path and target list | 0x8014A3B4-0x80150000, three files (section 2) | Done |
| 12 | Task methods | 0x80152AE8-0x8015D950, unit `Game/fn_80152AE8.cpp` (pair-less: needs the flag-setter) | Done. `.rodata` 0x8049B9C8-0x8049B9E0 (floats 1, 0, 176, -0, 0, 1) has no reader in `.text` and stays unclaimed |
| 13 | Behavior handlers | 0x80138E10-0x80145CB0, extending row 2's unit | Unit reaches 0x80141D78, its `.rodata` 0x8049AF40 (8-aligned, no pad needed). 17 unclaimed handler functions (0x35C4 bytes), next `DEFEND_REGIONS` `fn_80141D78` (0x33C), then static init `fn_80145B74`, `_GLOBAL_.I`, `_GLOBAL_.D` |
| 14 | Rename pass | Task methods in row 12's unit; accessors in `Game/fn_80442010.c` and row 5's units | After row 13. One area per run, each one `symbols.txt` edit plus a rename across `src/`, checked by `main.dol: OK`. Task methods take their `TASK_` string: `Task_ClimbAttack_Enter`, `_Exit`, `_Update`. Accessors get a name (`AI_GetMover`, no class prefix) only where section 4 records what they return; the rest keep `fn_`. Symbols stay `extern "C"` |

Out of scope for AI: the general script code in 0x8007C034-0x80081E08 and the script node classes at 0x801C5E0C-0x801DFED8 (unless a row needs a caller's meaning), the video player from 0x80164F2C, and third-party code.

---

## 7. Open Questions

- How do tasks choose behaviors (`lbl_80571814`), and what reads the profile's tuning floats at `+0x598`?
- Which of the script node classes at 0x801C5E0C-0x801DFED8 are AI commands, and what are their script names (`cSpawnPeon`, `cAIEnemyVictoryScene`, `cGlobalPeonCounter` in `.rodata` 0x8049EDD0-0x8049EE90)?
