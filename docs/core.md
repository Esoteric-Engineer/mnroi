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
- **System monitor.** `fn_801AD6F0` registers `fn_801AD768` as its `CTask` callback (section 4.7), which polls the reset button (`fn_801AEAE8`) and the drive (`fn_801AD7BC`). `fn_801AEBFC` polls the reset button alone, for the memory-card manager (0x8011F270).

---

## 2. File Map

All of it is `-O0` game code. A `.ctors` entry (`_GLOBAL_.I`) ends a file that has static constructors; edges marked "identify" are not settled yet (section 6 says which row settles each).

| Range | Contents | Row |
|---|---|---|
| 0x801A6390-0x801A7BF8 | Not core: graphics. Two `.ctors` files ending at 0x801A6904 and 0x801A6C40, then the `Graphics:Terrain` segment classes (vtables 0x804F67A0, 0x804F67B8, `__7Segment`). They call the model code before them and the render code at 0x8021xxxx-0x8023xxxx | |
| 0x801A7BF8-0x801A9974 | **File layer**. Start: the empty stubs `fn_801A7BF8` (startup calls it after the file layer's empty `fn_801A9564`) and `fn_801A7C14` (a per-frame hook), like the layer's other stubs `fn_801A9334`, `fn_801A953C`, `fn_801A9564`; the graphics file ends with the `Segment` destructor. `.rodata` 0x8049D6C4-0x8049D8C4 (`"bf:"` to `"."`); the `Memcard:*` header strings before it close the graphics file's. End: `fn_801A9748` (`DVDReadDir`); the card file's `"MemUnit:Buffer"` starts 0x8049D8C8, six bytes past `"."`, a section edge. Holds the stdio-style layer (section 4.1), the search folders (4.2), the `CLASH.BIG` mount and `stdFile:Find` over `DVDOpenDir`. The allocation line numbers run 475 to 2227 in `.text` order, then 87 in `fn_801A9584`: the three `stdFile:Find` functions are probably another source file included at the end (a guess) | 3 |
| 0x801A9974-0x801AA1E8 | **Memory-card device** (section 4.5). `.rodata` 0x8049D8C8-0x8049D8F0: `"MemUnit:Buffer"`, then the pools of the tail inlines `fn_80466694` (0x8049D8D8) and `fn_80466764` (0x8049D8E0, 512.0f), which round a size up to a sector. Ends at `_GLOBAL_.I` 0x801AA1AC | 4 |
| 0x801AA1E8-0x801ABA18 | **Pad manager**: init, read, reset, rumble (`PADControlMotor`), stick math (`__ieee754_sqrtf`). `.rodata` 0x8049D8F0-0x8049D960, ending with the button-bit table 0x8049D950 | 12 |
| 0x801ABA18-0x801AD588 | **Memory manager** (section 4.3). Starts at `fn_801ABA18`, the empty callback the init passes to `VMSetLogStatsCallback` and its only reference. `.rodata` 0x8049D960-0x8049DAF0, ending with `"new[]"`; the rest of the file reads none | 2 |
| 0x801AD588-0x801AF394 | **System monitor** (`CSysMon`, `Game/fn_801AD588.cpp`). `.rodata` 0x8049DAF0-0x8049E308: first 0x148 bytes of strings no code reads (`"cMoviePlayer:Instance"`, `"Memcard:Thread"`, font names; inline functions' tags, a guess), then the localized drive messages that `.data` 0x804D39AC (`[4 languages][6]`) points to, then the pools; 0x8049E304 is padding before the time file's 8-aligned pool. The memory manager's `.data` 0x804D398C (0x20) sits just before. `_GLOBAL_.I` 0x801AF358 | 13 |
| 0x801AF394-0x801AFEC0 | **Frame clock** `lbl_80593BE8` (section 4.8). One file: it starts after the system monitor's `_GLOBAL_.I` and ends with its own at 0x801AFE84, which runs the constructor `fn_801AF394`; no function-end pairs, since the constructor sets the flag. `.rodata` 0x8049E308-0x8049E3AC: its pools to 0x8049E350, then `fn_8042CE28`'s pool copy and five `"Memcard:*"` tags that no code reads (left unclaimed: an 8-aligned 0xA4 section, which ngcas would pad to 0xA8) | 14 |
| 0x801AFEC0-0x801B0B40 | **File back end**, its own file: the open-file record's methods. No `.rodata`. Start: the time file's `_GLOBAL_.I` `fn_801AFE84` ends the file before. End: `Std/BufferAllocator.cpp` asserts at line 140 in its third function `fn_801B0C90`, which leaves no room for these 0xC80 bytes ahead of it; the back end reaches the allocator only through the `.sdata` pointer `lbl_8066C6B8` (set by `fn_801AFEC0`) with virtual calls | 5 |
| 0x801B0B40-0x801B104C | **`Std/BufferAllocator.cpp`** (the default allocation path in `fn_801B0C90`). `.rodata` 0x8049E3AC-0x8049E3F4. The object is `lbl_80593C58` (`.bss`, 0x18), which the file layer's init hands to the back end | 5 |
| 0x801B104C-0x801B2620 | **`Std/stdBigHashedVFS.cpp`** (assert paths in `fn_801B1270` and `fn_801B1D74`). `.rodata` 0x8049E3F4-0x8049E4DC, from its own `"bf:"` (the constructor's, emitted first) to `"Decompession Buffer"` | 6 |
| 0x801B2620-0x801B26DC | **`stdBitmap`** (`.rodata` 0x8049E4DC, the registry name; the DOL gives no path). Its class table `lbl_80593C70` (`.bss`, 32 slots, count `lbl_8066C6CC`) is filled by the tuning init `Game/fn_801B26DC.cpp`, which follows | 7 |
| 0x801B26DC-0x801B50BC | Tuning ([`characters.md`](characters.md) section 4), then two C files. **Path-string helpers** 0x801B3E6C-0x801B4284 are called game-wide and by neither neighbour; their only `.rodata` is the `"."` at 0x8049E55C, between the NVB loader's strings and the registry's tag, so they are taken as their own file. **`Game:Hashtables` registry** 0x801B4284-0x801B50BC, `.rodata` 0x8049E560-0x8049E620 (tag, two unread dump formats, the bucket-count primes) | 16 |
| 0x801B50BC-0x801B5BA8 | **`KVList` and `KSList`** (`Game:KVList` `fn_801B5400`, `Game:KSList` `fn_801B59F0`). `.rodata` 0x8049E620-0x8049E660. Starts at the `KVList` constructor: 0x801B4F40-0x801B50BC are registry C (`register` parameters, called only from the registry at 0x801B4764-0x801B4D7C) | 8 |
| 0x801B5BA8-0x801B6AF0 | **`Game:List`** (`fn_801B5E38`), a growable pointer array. `.rodata` 0x8049E660-0x8049E680 | 9 |
| 0x801B6AF0-0x801B6D8C | **Small-object allocator wrapper** over the tail's SOA class (0x80467494-0x8046859C, `Game/fn_80467494.cpp`), built only by the APT glue (0x8011D244-0x8011EDE0) from one of the two 13-bin tables `lbl_8049E680` and `lbl_8049E71C` (`{u32 size; u16 ?, count, ?}`). `.rodata` 0x8049E680-0x8049E8FC: the tables, then unread SOA stats formats, `"[CPUSPAM]"`, a 1.0f, and the recurring font-name header block (`"UI/eafont0"` to `"EAS SansCondensed"`), which closes a file's `.rodata`. So `CTask`'s pool at 0x8049E8FC starts the next file. The empty startup stub `fn_801B6D70` is pair-less on either side; it is put at this file's end (a guess) | 15 |
| 0x801B6D8C-0x801B738C | **`CTask`**, `CSysMon`'s base class (section 4.7). `.rodata` from 0x8049E8FC: its pools to 0x8049E920, then `"Utils:Strings"`, `"rb"` and floats to 0x8049E97C that no code reads | 15 |
| 0x801B738C-0x801B7A48 | **String helpers and the string hash table**: in-place lowercase `fn_801B738C` and the seeded djb2 hash `fn_801B741C` (both called game-wide), then a table that only `stdVar` uses. No `.rodata`. The edge with `stdVar` is a guess from the code: before it, free functions over a table parameter; from it, `stdVar`'s singleton and methods, the first code to touch file data. `.rodata`, the pair map and the language (C++ on both sides) do not separate them | 10 |
| 0x801B7A48-0x801B8E78 | **`stdVar`**, a singleton of named int, float and string variables read from INI-style text (`[section]`, `key = value`, `//` comments, `"` quoting; keys become `PREFIX/SECTION/KEY`, uppercased). Init `fn_801B8530` loads a file under the tag `"Game:stdVar"`. `.rodata` 0x8049E97C-0x8049E9A8; the floats before it, to 0x8049E8FC, are row 15's (read from 0x801B7018-0x801B7308) | 10 |
| 0x801B8E78-0x801BA090 | **View frustum**, called from the renderer (0x8039xxxx-0x803Bxxxx). `.rodata` 0x8049E9A8-0x8049E9B8, its last two zero words unread | 11 |
| 0x801BA090-0x801BC9DC | **Geometry tests** on `Vector`, called from game code (0x8004xxxx, 0x8014xxxx); `_GLOBAL_.I` 0x801BC9A0. Starts a file: `fn_801BA090` opens a pair-carrying run right after `fn_801B9D78`, a pair-less function with no branches (so no `case` or label cleared the flag). `.rodata` 0x8049E9B8-0x8049EA68: its pool holds a double, so it starts 8-aligned, one word before the first literal. The unread words 0x8049EA68-0x8049EA8F are this file's or the trajectory file's, whose pool starts at 0x8049EA94 | 11 |
| 0x801BC9DC-0x801BEE2C | **Math**, C++ files whose `.rodata` stays with dtk (`extern_pool`). Edges from the pools: each file's pools are closed by words no code reads (its linkonce copies) or by the font-name header block: trajectory solves 0x801BC9DC (pool 0x8049EA94), quaternions 0x801BCE6C (0x8049EAC0), Euler and rotate 0x801BD38C (0x8049EAE8), vector packing 0x801BD7B4 (0x8049EB14), degree trig 0x801BD9C4-0x801BEA34 (0x8049EB30; runs of pool words with no code also sit between its functions). The last file starts at 0x801BEA34, where the function-end pairs start, and ends with `_GLOBAL_.I` 0x801BEDE8 and the font block before 0x8049ED7C. The pow helper, the angle stepper `fn_801BE840` and the vector helpers `fn_801BE948`/`fn_801BE9C8` read no pool, so their file is a guess (the trig one) | 17 |
| 0x80426A2C-0x80431788 | **Linkonce tail, start.** Mixed: generic class inlines (`Color` 0x80426EC4, the localization singleton's getter `fn_80427400` (`Loc:Instance`), five list-wrapper classes 0x80428314-0x80428F74 (section 4.4), `Vector` 0x80428F74, the vector and matrix operations), and inlines only the HUD or render code calls (section 5) | 1, 9, 19 |
| 0x80465F68-0x80468888 | **Std inline functions** in the linkonce tail, one run per first-emitting file in the rows above, from `fn_8046655C` (the file layer) to `fn_804687D8` (geometry). Before 0x8046655C every caller is the model, graphics or render code (0x8019F02C-0x801A7BF8, 0x8022xxxx, 0x803Bxxxx-0x803Dxxxx), so those are out of scope. 0x80466A44-0x80466BA0 and `fn_80467380` are the RealCore file system base's default virtuals (vtable 0x804F6888), and they keep the function-end pair | 18 |

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

`Game/fn_801A7BF8.cpp`. An `.sbss` pointer to 12 records of 0x158 bytes (`new[]` with a cookie, constructor `fn_801AFEE8`). A handle is a record's index + 1, and 0 is failure. The back end `Game/fn_801AFEC0.cpp` declares the whole record; what the file layer reads:

| Offset | What |
|---|---|
| +0x00 | `int *` to the open flag +0x118; the slot is free when `*f0 == 0` |
| +0x04, +0x08 | `int *`, both to the device handle +0x14 that the RealCore calls take (`fn_80244538`, `fn_802444A8`); the formatted write `fn_801A8E54` writes only when `*f8 != 0` |
| +0x0C | `char *` to the path +0x18, with the root prefix (`fn_801A7C30`) stripped |
| +0x10 | `unsigned *` to the file size +0x128 |
| +0x12C | read position; the end test compares it with +0x128 |

The calls callers need: open `fn_801A8500(path, mode)`, open through the search folders `fn_801A8368(name, mode, type)` (23 calling functions), close `fn_801A875C(handle)`, read `fn_801A8B60(ptr, size, count, handle)`, line read `fn_801A8C08(buf, n, handle)`, formatted write `fn_801A8E54(handle, fmt, ...)`, exists `fn_801A8088(path)`. The mode string sets 0x11 for `r` and 0x6 for `w` (`fn_801A7CD8`).

### 4.2 Search folders (`lbl_805864B0`)

35 entries of `{ int count; char *paths[64]; }` (0x104 bytes), indexed by file type; `fn_801A8FC4` lists the folders of each type.

### 4.3 Memory manager

`Game/fn_801ABA18.cpp`. The argument order its callers need (the size comes first, then the tag string such as `"Graphics:Terrain"`):

| Entry | Arguments |
|---|---|
| `fn_801AC9EC` (26 calling functions) | `(size, tag, line, kind, align, ?)`; `line` is the caller's source line; `kind` 1 adds heap flag 0x100 |
| `fn_801AC988` (48) | `(size, tag, line, kind)`, the above with `align` 0; `operator new` passes `(size, "new", 0, 2)` |
| `fn_801AD37C`, `fn_801AD324` | ARAM: `(size, tag, line, align)` and `(size, tag, line)` |
| `fn_801ACC7C` | realloc: `(p, size, tag, kind)` |
| `fn_801ACC0C` (68), `fn_801ACC44` | free: `(p)` |

### 4.4 Vtables

| Vtable | Class | Constructor |
|---|---|---|
| 0x804F67D0 (`_vt.15BufferAllocator`) | BufferAllocator, a `Sink` (base vtable 0x804F5868, all four slots `__pure_virtual`). Slots: `+0x8` alloc(size, attrs), `+0x10` free(p, attrs), `+0x18` add a reference, `+0x20` release, `+0x28` destructor. The alloc attributes are RealCore `Attr` entries `{key, value, next}`: 1 tag, 2 alignment, 3 the fourth `fn_8023F2D4` argument, 4 heap flag 0x100 when positive, 5 file, 6 line | `fn_801B0B40` |
| 0x804F6808 (`_vt.15stdBigHashedVFS`, the class name a guess) | the VFS, a RealCore file system: base constructor `fn_802407A8(this, prefix)`, base vtable 0x804F6888, base destructor the tail inline `fn_80467100`; vptr at `+0x10`. Slots: `+0x20` open(path, mode, `int *dev`), `+0x28` close(h), `+0x30` read(h, buf, size, dev, devh), `+0x40` seek(h, `s64` off, whence, dev, devh), `+0x48` size(h), `+0x50` disc position(h); the rest are the base's tail inlines. `dev` is the file system that holds the archive | `fn_801B24A0` |
| 0x804F6978 | `KVList`, a `Game:List` of `{char *key, void *value}` nodes (vptr `+0x20`, object 0x24). Slots: `+0x10`-`+0x20` the List's, stubbed to return -1; `+0x28` set(key, value); `+0x30` remove(key) | `fn_801B50BC(this, n, grow)` |
| 0x804F6908 | `KSList` : `KVList`, string values. Adds `+0x38` set(key, string), then setters that format and call it: `+0x40` float, `+0x48` unsigned, `+0x50` int, `+0x58` vector (`"%f %f %f"`), `+0x60` bool (`"1"`/`"0"`). Its destructor is the tail inline `_._5Sub24` (0x80467428) | `fn_801B54E8(this, n, grow)` |
| 0x804F69B8 | `Game:List`, 0x24 bytes: items `+0x0`, growth factor `+0x4`, capacity `+0x8`, count `+0xC`, flags `+0x10` (bit 0 sorted), item callback `+0x14` (`(op, item)`, op 0 added, 1 removed), match `+0x18` (`(item, key)`), compare `+0x1C`, vptr `+0x20`. Slots: `+0x10` add(item), `+0x18` insert(i, item), `+0x20` remove(item) | `fn_801B5BA8(this, capacity, grow)` |
| 0x804F2DE0-0x804F2E40 | Five callback handles `{Impl *impl; vptr}`, one virtual slot each (the destructor). Placeholder names, shared with the other units that build them: 0x804F2DE0 `HandleD`, 0x804F2DF8 `HandleG`, 0x804F2E10 `Cue`, 0x804F2E28 `HandleA`, 0x804F2E40 `HandleC`; destructors `_._7HandleD` etc. The 0x18-byte impl is built from (owner, a pointer to member `{0, 0xFFFF, fn}`); `+0x0` is a reference count (1 at construction; at 0 the impl deletes itself through the vtable's destructor), `+0x14` the key `(owner % 0x10000) << 16 | word0 % 0x10000`. Impl vtables 0x804F2E58-0x804F2F20: `+0x8` destructor, `+0x10` get (the list key), `+0x18` invoke, which calls the entry `{short delta; short index; fn}` at `+0xC` on `owner + delta` (`+0x8`) with no index check | 0x80428314, then every 0x108 bytes to 0x80428734; `fn_8042883C` is a second `HandleA` constructor |


### 4.5 Memory-card slots (`lbl_80589260`)

`Game/fn_801A9974.cpp`. A 0x40-byte object: two 0x18-byte slots, then 0x10 bytes nothing in the file touches. Its constructor is the tail inline `fn_804665F0`, the slot constructor `fn_80466664`, the slot accessor `fn_80431E9C`. Callers are the save code at 0x8002AC34-0x8002B490.

| Offset | What |
|---|---|
| +0x00 | channel |
| +0x04 | `u16` flags: 1 present (probe), 2 and 4 the mount results -6 and -13, 8 mounted |
| +0x08, +0x0C | memory size and sector size, from `CARDProbeEx` |
| +0x10 | 64-bit serial number |

### 4.6 Pad records (`lbl_805932A0`)

Four 0x19C-byte records, one per channel; game code reads them through the current-pad pointer `lbl_8066C63C`. The frame counter is `lbl_8066C638`, rumble is enabled by `lbl_8066C640`, and `lbl_8066C644`/`lbl_8066C648` are the disconnect and connect callbacks `(u16 chan)`.

| Offset | What |
|---|---|
| +0x00 | connected |
| +0x08 | `u32` frame time the motor runs until, 0 when stopped |
| +0x0C-+0x18 | stick x, y (y negated) over 56; C-stick x, y over 44 |
| +0x1C | 16 key slots of 0x18: value (0-1), press frame, press time, release frame, release time, held time. Keys: 1 A, 2 B, 3 X, 4 Y, 5 Z, 6 and 7 the analog L and R, 8 L, 9 R, 10 Start, 11-14 left, right, up, down |

### 4.7 `CTask`, the system monitor's base (row 15)

Only `CSysMon` (0xA0 bytes, `lbl_80593B48`) derives from it; the name is a guess. Layout of the base, 0x78 bytes:

| Offset | What |
|---|---|
| +0x00 | `u8` flags: 1 registered, 2 set on registering (read by the tail getter `fn_804685D0`); the monitor adds 4 reset pressed, 8 reset requested, 0x10 halted on a drive error |
| +0x04 | text object (0x48), built by `fn_800FE6AC(p, 0xC8)`, destroyed by `fn_800FE7E0(p, 2)`; font `fn_800FE284(3)` at size 26 |
| +0x4C | 0x28-byte line buffer for the text measure and draw |
| +0x74 | the callback, added to the list at `lbl_8062D680` by `fn_8023E850(cb, 0, 0, 0)` and removed by `fn_8023E930(cb)` |

The monitor uses the base's text measure and draw in place of its own font code when `lbl_8066BB0C` and the tail getter `fn_804668A4` are set.

### 4.8 Frame clock (`lbl_80593BE8`)

0x70 bytes, ticked once a frame by `fn_801AF790` from the ms counter `fn_8023EA4C` (the timer `fn_8023D994(1000)` starts). It has two counter blocks of 0x20, *real* at +0x20 and *game* at +0x40, each holding frames, `int` ms, `float` s, `unsigned` delta ms (clamped to 1-1000), `float` delta s, 1 / delta s, a `float` scale and an `int` pause count. The game block accumulates seconds rather than ms, and its scale ramps toward the target. Readers in the tail: `fn_8042EFF8` +0x44, `fn_8042F024` +0x4C, `fn_8043B3B0` +0x54, `fn_804669A4` +0x38, `fn_80435650` +0x58; `fn_80466828`/`fn_80466850` write +0x3C and `fn_804325CC` writes +0x5C.

| Offset | What |
|---|---|
| +0x00 | started, set by `fn_801AF6C4` |
| +0x04 | frames ticked |
| +0x08 | `int` ms times the scale; `fn_8046697C` sets it |
| +0x0C | the real block's delta before the clamp |
| +0x10 | fixed step in ms, used instead of the measured delta when nonzero |
| +0x14 | `float` scale on the measured delta |
| +0x18 | `s64` last tick |
| +0x60, +0x64 | `float` target game scale and its ramp rate per second (`fn_801AFC50(scale, seconds)`) |
| +0x68, +0x6C | flag, `float` fixed delta in seconds that replaces the measured delta in both blocks |

---

## 5. Notes

- **The tail is ordered by the first file that emitted each inline** ([`prodg.md`](prodg.md#inline-functions-and-the-tail-of-text)), so a tail run is not one class. 0x80426A2C-0x80428FE0 has its pools in the first kilobyte of `.rodata` (the HUD files at 0x80003808 on): it holds HUD-only inlines (`fn_80426F94` and `fn_80427214` call `fn_800098CC`, `fn_80426AB0` tests `G+0x770`) next to `Color`, `Vector` and the list wrappers. Claim a tail function for this map only if its callers are spread across the game or are in the rows above; leave the rest for the branch that owns their callers.
- **The most-called generic inline still open** is the localization getter `fn_80427400` (31 calling functions, row 19).
- **Call counts in this file are calling functions, not call sites**, counted once per function. `build/GVLE69/asm/` holds stale copies of split files, so a raw `grep -c` over it double-counts.

---

## 6. Target Order

Work the rows in order and skip whatever is done; `configure.py` is the authority on unit status. Within a file, take the next function after the unit's current `.text` end, so that the unit grows as one contiguous range from the file's first function. If a function is stuck, record it in [`nonmatching.md`](nonmatching.md) and move on to the next row rather than leave a gap. Name a unit after its file's first function (`Game/fn_801ABA18.cpp`), or after its source path once it is known (`Std/BufferAllocator.cpp`). Rows are numbered once; unit headers cite them (`docs/core.md row N`), so don't renumber.

| # | Target | Range | Next action |
|---|---|---|---|
| 1 | Generic tail inlines, first run | `fn_80426A2C`, `fn_80426A54`, `__5ColorUcUcUcUc`, `__6Vector`, `fn_80428FA8` | Done |
| 2 | Memory manager | 0x801ABA18-0x801AD588 | Done |
| 3 | File layer | 0x801A7BF8-0x801A9974 | Done |
| 4 | Memory-card device | 0x801A9974-0x801AA1E8 | Done |
| 5 | BufferAllocator and the file back end | 0x801B0B40-0x801B104C, then 0x801AFEC0-0x801B0B40 | Done |
| 6 | VFS | 0x801B104C-0x801B2620 | Done |
| 7 | `stdBitmap` | 0x801B2620-0x801B26DC | Done |
| 8 | `KVList` and `KSList` | 0x801B4F40-0x801B5BA8 | Done |
| 9 | `Game:List` and the list wrappers | 0x801B5BA8-0x801B6AF0, then the tail's 0x80428314-0x80428F74 | Done |
| 10 | String utilities and `stdVar` | 0x801B738C-0x801B8E78 | Done |
| 11 | Geometry | 0x801B8E78-0x801BC9DC | Done |
| 12 | Pad manager | 0x801AA1E8-0x801ABA18 | Done |
| 13 | System monitor | 0x801AD588-0x801AF394 | Done |
| 14 | Frame clock | 0x801AF394-0x801AFEC0 | Done |
| 15 | SOA wrapper and `CTask` | 0x801B6AF0-0x801B6D8C, then 0x801B6D8C-0x801B738C | Done |
| 16 | Tuning-area gaps | 0x801B3E6C-0x801B4F40, the unclaimed functions | Done |
| 17 | Math gaps | 0x801BC9DC-0x801BEE2C, the unclaimed functions | Done |
| 18 | Std inline functions | 0x8046655C-0x80468888 | Done; 0x80465F68-0x8046655C is the model's and graphics' (section 2) |
| 19 | Rest of the generic tail inlines | the unclaimed functions in 0x8042A7D8-0x80431788 | Class each by its callers (section 5), match the generic ones. 0x804291A4-0x804293F4 is render- and HUD-only, 0x8042A858-0x8042D324 HUD-only (callers at 0x8000xxxx) apart from the claimed units and `fn_8042D0A8` (one more caller at 0x80132838, unclassed); `fn_8042D474`, `fn_8042D4A0` and `fn_8042D558` are called only from the file of the 0x1820-byte singleton `lbl_8066B54C` (constructor `fn_80015248`); its +0xF8 getter `fn_8042D52C` (callers across the game) is the next generic one, then the +0x218 getter `fn_8042D584` (`Locale_GetLanguage` among its callers; its object is unchecked) |
| 20 | Rename pass | the functions section 4 describes | Names only where section 4 records what a function does; leaf accessors keep `fn_` |

---

## 7. Open Questions

- What the 100 (0x64) that the file layer passes to close, open and the RealCore reads and writes means (a timeout or a priority: a guess).
