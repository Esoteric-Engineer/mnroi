# Core Layer Map

Where the engine's shared layer is (the memory manager, the file layer and `CLASH.BIG`, pad input, the system monitor, the containers, `stdVar`, the geometry helpers, and the shared classes' inline functions in the tail of `.text`), how it is laid out, and the order to decompile it in (section 6).

See also:
- The per-function loop: [`workflow.md`](workflow.md).
- Linkonce functions, `extern_pool` and why the tail is ordered as it is: [`prodg.md`](prodg.md#inline-functions-and-the-tail-of-text).
- The `.BIG`/`.BH` archive layout: the docstrings of `tools/bigtool.py` and `tools/nbig.py`.
- The tuning code between the Std files (`Misc/defaults.ndb`, the NVB registry): [`characters.md`](characters.md) section 4.

**This is a reference, not a narrative: read the section you need.** `configure.py` is the authority on which units are matched, and a matched function's source is the authority on what it does; this file records what the source can't say. **Names:** the `Std/` source paths and the allocator tags (`Game:KVList`, `MC:VM`...) are the DOL's; the stdio names (`fopen`, `fread`) and the class names below are this project's guesses. Symbols stay `fn_` and `extern "C"` until a rename pass (row 20).

---

## 1. Entry Points

- **Startup.** `fn_8002F070` calls the memory manager's init `fn_801ABA48`, the file layer's init `fn_801A7DF0` and the `stdVar` init `fn_801B8530`. `fn_801A7DF0` allocates the open-file table (section 4.1), fills the search folders (`fn_801A8FC4`, section 4.2) and mounts `CLASH.BIG` (`fn_801A935C`).
- **Allocation.** `__builtin_new` (295 calling functions), `__builtin_delete` (158), `__builtin_vec_new`, `__builtin_vec_delete`, and the tagged allocator (section 4.3). `__builtin_new` and `__builtin_vec_new` also run the memory init lazily.
- **Files.** `fn_801A8500(path, mode)` opens, `fn_801A875C(handle)` closes (32 calling functions), `fn_801A8B60(ptr, size, count, handle)` reads (46). Callers include the tuning init `fn_801B26DC` and the model loaders.
- **Pad.** `fn_801AA1E8` (`PADInit`, `SISetSamplingRate`) is called from the video and GX init `fn_80219900`.
- **System monitor.** `fn_801AD768` runs `fn_801AD7BC` (drive status, reset, pad motors); `fn_801ADC04` loads the system font (`CSysMon::SysFont`).

---

## 2. File Map

All of it is `-O0` game code. A `.ctors` entry (`_GLOBAL_.I`) ends a file that has static constructors; edges marked "identify" are not settled yet (section 6 says which row settles each).

| Range | Contents | Row |
|---|---|---|
| 0x801A6390-0x801A7BF8 | Not core: graphics. Two `.ctors` files ending at 0x801A6904 and 0x801A6C40, then the `Graphics:Terrain` segment classes (vtables 0x804F67A0, 0x804F67B8, `__7Segment`). They call the model code before them and the render code at 0x8021xxxx-0x8023xxxx | |
| 0x801A7BF8-0x801A9974 | **File layer**, `.ctors` file with the next row. Start: identify (`fn_801A7BF8` and `fn_801A7C14` are 0x1C stubs; `fn_801A7C30` reads `"bf:"`, the first of the file's `.rodata`, 0x8049D6C4). Holds the stdio-style layer (section 4.1), the search folders (4.2), the `CLASH.BIG` mount and `stdFile:Find` over `DVDOpenDir` | 3 |
| 0x801A9974-0x801AA1E8 | **Memory-card device**: `CARDInit`/`CARDMount`/`CARDRead`/`CARDWrite` wrappers and the `MemUnit:Buffer` reads and writes. Edge with the file layer: identify. Ends at `_GLOBAL_.I` 0x801AA1AC | 4 |
| 0x801AA1E8-0x801ABA48 | **Pad manager**: init, read, reset, rumble (`PADControlMotor`), stick math (`__ieee754_sqrtf`). `.rodata` 0x8049D8F0-0x8049D960, ending with the button-bit table 0x8049D950. End: identify (`fn_801ABA18` is an empty 5-argument function) | 12 |
| 0x801ABA48-0x801AD588 | **Memory manager** (section 4.3). `.rodata` from `"MC:VM"` 0x8049D960. `_GLOBAL_.I` 0x801AD510, `_GLOBAL_.D` 0x801AD54C | 2 |
| 0x801AD588-0x801AF394 | **System monitor** (`CSysMon`): drive status, reset button, system font, pad recalibration, language, a 2D text draw (`C_MTXOrtho`, `OSGetFontWidth`). `_GLOBAL_.I` 0x801AF358 | 13 |
| 0x801AF394-0x801AFEC0 | Unknown: `OSGetTime`/`OSTicksToCalendarTime`, calls into 0x8023EA4C. `_GLOBAL_.I` 0x801AFE84 | 14 |
| 0x801AFEC0-0x801B104C | **`Std/BufferAllocator.cpp`** (assert path, `fn_801B0C90`). Vtable 0x804F67D0; constructor `fn_801B0B40` (`"BuffMan"`). Before it, 0x801AFEC0-0x801B0B40 is the file layer's back end (`fn_801B01D4` is the read `fn_801A8B60` calls, `__4Attrii`): same file or not, identify. `_GLOBAL_.I` 0x801B0FD4, `_GLOBAL_.D` 0x801B1010 | 5 |
| 0x801B104C-0x801B2620 | **`Std/stdBigHashedVFS.cpp`** (assert paths in `fn_801B1270` and `fn_801B1D74`). Its `.rodata` starts with its own `"bf:"` at 0x8049E3F4 and ends with `"Decompession Buffer"`. The VFS class: constructor `fn_801B24A0` (vtable 0x804F6808 at `+0x10`, base constructor `fn_802407A8` in RealCore), destructor `fn_801B2530` | 6 |
| 0x801B2620-0x801B26DC | **`stdBitmap`** (`.rodata` 0x8049E4DC). The matched tuning init `Game/fn_801B26DC.cpp` follows | 7 |
| 0x801B26DC-0x801B4F40 | Tuning and the `Game:Hashtables` registry, mostly matched ([`characters.md`](characters.md) section 4); several units are C. Gaps: path-string helpers 0x801B3E6C-0x801B4284 and small ones up to 0x801B4E84 | 16 |
| 0x801B4F40-0x801B5BA8 | **`KVList` and `KSList`** (`Game:KVList` `fn_801B5400`, `Game:KSList` `fn_801B59F0`); vtables 0x804F6908, 0x804F6978. Start: the C unit `Game/fn_801B4E84.c` ends at 0x801B4F40 | 8 |
| 0x801B5BA8-0x801B6AF0 | **`Game:List`** (`fn_801B5E38`), an array container: constructor `fn_801B5BA8` (vtable 0x804F69B8, 26 calling functions), helpers `fn_801B5D3C` (62), `fn_801B6040` (30), `fn_801B6A44` (59) | 9 |
| 0x801B6AF0-0x801B738C | Unknown wrappers (calls into 0x800FE284-0x80101188 and 0x8023E850-0x8023E98C). Its `.rodata` holds two short tables, 0x8049E680 and 0x8049E71C, read only from the APT glue's `fn_80126F0C` | 15 |
| 0x801B738C-0x801B8E78 | **String utilities and `stdVar`**: lowercase copy `fn_801B738C`, parsing (`"0x%x"`, `sscanf`), `Game:stdVar` `fn_801B8530` | 10 |
| 0x801B8E78-0x801BC9DC | **Geometry**: helpers on `Vector` and the tail's vector operations (`__ieee754_sqrt`). `_GLOBAL_.I` 0x801BC9A0 | 11 |
| 0x801BC9DC-0x801BEE2C | Math, mostly matched (quaternions `Game/fn_801BCE6C.cpp`, arcsine `Game/fn_801BE3C4.c`). `_GLOBAL_.I` 0x801BEDE8 | 17 |
| 0x80426A2C-0x80431788 | **Linkonce tail, start.** Mixed: generic class inlines (`Color` 0x80426EC4, the localization singleton's getter `fn_80427400` (`Loc:Instance`), five list-wrapper classes 0x80428314-0x80428F74 (section 4.4), `Vector` 0x80428F74, the vector and matrix operations), and inlines only the HUD or render code calls (section 5) | 1, 9, 19 |
| 0x80465F68-0x80468888 | **Std inline functions** in the linkonce tail. From 0x80466298 they are called almost only from the rows above; before it they mix with the model instance's | 18 |

Out of scope: the model code 0x8019F02C-0x801A6390 and the graphics files above; the render inlines 0x8046DCD4 on and 0x8047EED8-0x804825A0; the memory-card manager and APT glue 0x8011EDE0-0x8012D9F0 (including the getter `fn_80122228`); the gameplay inlines 0x80460334-0x80465C9C; middleware.

---

## 3. Layers

1. **Dolphin SDK** (matched): `DVD`, `CARD`, `PAD`, `SI`, `OS`, `VM`, `GX`.
2. **Middleware** (unmatched, `-O2`): the heap functions 0x8023F2D4-0x8023FE2C and the file functions 0x80242244-0x80245AEC that the memory manager and the file layer sit on ([`baseline.md`](baseline.md#memory-map) has which library each range is).
3. **Std** (this map): memory, files, pad, system monitor, containers, strings, `stdVar`, geometry.
4. **Shared classes** in the linkonce tail: `Vector`, `Color`, the matrix operations, the list wrappers.
5. Everything else calls down into 3 and 4.

---

## 4. Data

### 4.1 Open-file table (`lbl_8066F4EC`)

An `.sbss` pointer to an array of 0x158-byte records, allocated with `new[]` by `fn_801A7DF0`. A handle is a record's index + 1, and 0 is failure; every file function computes `lbl_8066F4EC + (handle - 1) * 0x158`.

| Function | What |
|---|---|
| `fn_801A8500(path, mode)` | Open: builds the path (`"%s\%s"`, `"%s%s"`), returns a handle |
| `fn_801A875C(handle)` | Close, through `fn_801B00AC(record, 0x64)` |
| `fn_801A8B60(ptr, size, count, handle)` | Read: 0 when `size` or `count` is 0, else `fn_801B01D4(record, ptr, size, count)` |
| `fn_801A8C08(…, handle)` | Through `fn_801B0380` (`memchr`): probably a line read (a guess) |
| `fn_801A8E54` | `vsnprintf` to a file: probably a formatted write (a guess) |
| `fn_801A8088(path)` | Exists: opens `"rb"`, closes, returns 1, or 0 when the open fails |

### 4.2 Search folders (`lbl_805864B0`, 0x238C bytes)

`fn_801A8FC4` clears it, then calls `fn_801A7F5C(folder, type, 0)` once per pair below, so a file type can search several folders. `fn_801A8368` (`"%s%c%s"`, 23 calling functions) builds a path from them.

| Type | Folders |
|---|---|
| 0 | `Anims` |
| 1 | `Levels`, `Materials`, `Materials/Effects`, `Materials/Levels`, `Materials/Models`, `Materials/Shaders`, `UI` |
| 2 | `Models` |
| 3, 8, 29, 30, 31 | `Levels` |
| 4 | `UI` |
| 6 | `Motions` |
| 7, 9, 10, 12-16, 20, 21 | `Misc` |
| 11, 24 | `Sound` |
| 18, 19 | `Quests`, `Stores` |
| 23, 25, 26 | `Video`, `Cutscenes`, `Terrains` |
| 32, 33, 34 | `Profiles`, `Bundles`, `AnimTags` |

Types 5, 17, 22, 27 and 28 have no folder.

### 4.3 Memory manager

- **Init** `fn_801ABA48`: `VMInit`, the `MC:VM`, `default` and `MC:SMALL` heaps, `VMSetLogStatsCallback`.
- **Reports**: `fn_801ABDB4` (ARAM classes), `fn_801ABFA4` (`Main Heap`, `Virt Heap`), `fn_801AC1E0` (per class), and the out-of-memory report `fn_801AC72C` (`"MALLOC requested name:%s size:%d"`).
- **Allocate**: `fn_801AC9EC` (6 arguments, 26 calling functions) and its wrapper `fn_801AC988` (4 arguments, passes 0 for the last two, 48 calling functions). The first argument is a tag string such as `"Graphics:Terrain"`; `__builtin_new` and `__builtin_vec_new` use `"new"` and `"new[]"`.
- **Free**: `fn_801ACC0C` (68 calling functions) and `fn_801ACC44`, both through `fn_8023F63C`.

### 4.4 Vtables

| Vtable | Class | Constructor |
|---|---|---|
| 0x804F67D0 | BufferAllocator | `fn_801B0B40` |
| 0x804F6808 | the VFS | `fn_801B24A0` |
| 0x804F6908, 0x804F6978 | `KVList`, `KSList` (which is which: identify) | |
| 0x804F69B8 | `Game:List` | `fn_801B5BA8` |
| 0x804F2DE0-0x804F2E40 | Five list-wrapper classes: the vtable at `+0x4`, a `new`ed object at `+0x0`. Each has a 0x70 constructor, a 0x98 add that appends to a `Game:List` through `fn_801B6040`, and a 0x140 clear at 0x804288AC-0x80428DAC. Called from the HUD, versus and the frontend | 0x80428314, then every 0x108 bytes to 0x80428734; `fn_8042883C` reuses 0x804F2E28 |

---

## 5. Notes

- **The tail is ordered by the first file that emitted each inline** ([`prodg.md`](prodg.md#inline-functions-and-the-tail-of-text)), so a tail run is not one class. 0x80426A2C-0x80428FE0 has its pools in the first kilobyte of `.rodata` (the HUD files at 0x80003808 on): it holds HUD-only inlines (`fn_80426F94` and `fn_80427214` call `fn_800098CC`, `fn_80426AB0` tests `G+0x770`) next to `Color`, `Vector` and the list wrappers. Claim a tail function for this map only if its callers are spread across the game or are in the rows above; leave the rest for the branch that owns their callers.
- **The most-called generic inline still open** is the localization getter `fn_80427400` (31 calling functions, row 19).
- **The two short tables in row 15's `.rodata`** (0x8049E680, 0x8049E71C) sit between `Game:List`'s pool and `fn_801B6FCC`'s, so they belong to that file even though only `fn_80126F0C` reads them.
- **Call counts in this file are calling functions, not call sites**, counted once per function. `build/GVLE69/asm/` holds stale copies of split files, so a raw `grep -c` over it double-counts.

---

## 6. Target Order

Work the rows in order and skip whatever is done; `configure.py` is the authority on unit status. Within a file, take the next function after the unit's current `.text` end, so that the unit grows as one contiguous range from the file's first function. If a function is stuck, record it in [`nonmatching.md`](nonmatching.md) and move on to the next row rather than leave a gap. Name a unit after its file's first function (`Game/fn_801ABA48.cpp`), or after its source path once it is known (`Std/BufferAllocator.cpp`). Rows are numbered once; unit headers cite them (`docs/core.md row N`), so don't renumber.

| # | Target | Range | Next action |
|---|---|---|---|
| 1 | Generic tail inlines, first run | `fn_80426A2C`, `fn_80426A54`, `__5ColorUcUcUcUc`, `__6Vector`, `fn_80428FA8` | Done |
| 2 | Memory manager | 0x801ABA48-0x801AD588 | Identify the start (`fn_801ABA18`), then match |
| 3 | File layer | 0x801A7BF8-0x801A9974 | Identify both edges, then match |
| 4 | Memory-card device | 0x801A9974-0x801AA1E8 | Match; it claims the file's `.ctors` word |
| 5 | BufferAllocator file | 0x801AFEC0-0x801B104C | Identify whether 0x801AFEC0-0x801B0B40 is the same file, then match |
| 6 | VFS | 0x801B104C-0x801B2620 | Match; cross-check the `.BIG`/`.BH` reads against `tools/bigtool.py` |
| 7 | `stdBitmap` | 0x801B2620-0x801B26DC | Match |
| 8 | `KVList` and `KSList` | 0x801B4F40-0x801B5BA8 | Match |
| 9 | `Game:List` and the list wrappers | 0x801B5BA8-0x801B6AF0, then the tail's 0x80428314-0x80428F74 | Match |
| 10 | String utilities and `stdVar` | 0x801B738C-0x801B8E78 | Identify the edge between them, then match |
| 11 | Geometry | 0x801B8E78-0x801BC9DC | Match |
| 12 | Pad manager | 0x801AA1E8-0x801ABA48 | Match |
| 13 | System monitor | 0x801AD588-0x801AF394 | Match |
| 14 | Unknown time file | 0x801AF394-0x801AFEC0 | Identify, then match |
| 15 | Unknown wrappers | 0x801B6AF0-0x801B738C | Identify, then match; claims the two short tables (section 2) |
| 16 | Tuning-area gaps | 0x801B3E6C-0x801B4F40, the unclaimed functions | Extend the neighbouring units or merge into them |
| 17 | Math gaps | 0x801BC9DC-0x801BEE2C, the unclaimed functions | Extend the neighbouring units or merge into them |
| 18 | Std inline functions | 0x80466298-0x80468888, and the ones in 0x80465F68-0x80466268 that the Std rows call | Match; one small unit per run of neighbours |
| 19 | Rest of the generic tail inlines | the unclaimed functions in 0x80429090-0x80431788 | Class each by its callers (section 5), match the generic ones |
| 20 | Rename pass | the functions section 4 describes | Names only where section 4 records what a function does; leaf accessors keep `fn_` |

---

## 7. Open Questions

- Where the file layer starts (`fn_801A7BF8`, `fn_801A7C14`) and where it hands over to the memory-card device.
- Whether `fn_801ABA18` ends the pad manager or starts the memory manager.
- Whether 0x801AFEC0-0x801B0B40 (the file back end, `__4Attrii`) is part of `Std/BufferAllocator.cpp`.
- What the files at 0x801AF394 and 0x801B6AF0 are.
- What the 0x158-byte open-file record holds, and what the 0x64 that close passes means.
