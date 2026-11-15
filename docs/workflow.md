# Decomp Workflow

Commands, per-function loop, how to choose what to work on.

See also:
- First-time setup: [`README.md`](../README.md#building).
- Compiler/linker gotchas: [`matching_notes.md`](matching_notes.md).
- Functions stuck as `NonMatching`: [`nonmatching.md`](nonmatching.md).

`configure.py`'s object list is the source of truth for what is currently matched.

---

## 0. Guiding Rule

**The build must always end with `main.dol: OK`.**

That line means the built DOL is byte-for-byte identical to the original. If it ever stops saying `OK`, stop and fix that before doing anything else.

The workflow is designed so this is hard to break; see the `NonMatching` safety net in section 2.

---

## 1. Everyday Commands

| Command | What it does |
|---|---|
| `ninja` | Build everything. Prints progress %. |
| `python3 configure.py progress` | Print progress without building |
| `rm -rf build/GVLE69 && ninja` | Full rebuild from scratch (a few seconds; keeps downloaded tools) |
| `python3 configure.py --dtk build/tools/dtk-dev` | Re-configure by hand (after editing `configure.py`) |
| `python3 tools/diff_dol.py` | Byte-diff the built DOL against the original, broken down by segment |
| `python3 tools/objdiff_mismatches.py <unit> <function>` | Print only the instructions that still differ |

The `--dtk` argument is recorded in `build.ninja`, so plain `ninja` re-runs `configure.py` with it automatically. If you ever run a bare `python3 configure.py`, it falls back to downloading stock dtk and the build stops matching. Re-run it with `--dtk build/tools/dtk-dev`.

Use `tools/diff_dol.py` when `main.dol: OK` stops being OK. It maps each differing byte back to a virtual address, which usually lands directly on the bad instruction.

---

## 2. Per-Function Loop

### Step 1: Pick a function and find its bounds

See section 4 for how to choose *which* function. Look it up in `config/GVLE69/symbols.txt`:

```
fn_8000923C = .text:0x8000923C; // type:function size:0x44
```

Following the format of `end` = `start + size`:<br />
`0x8000923C + 0x44` = `0x80009280`.

### Step 2: Claim the address range in `splits.txt`

Add a unit to `config/GVLE69/splits.txt` (blank line between units, tab-indented body):

```
Game/fn_8000923C.cpp:
	.text       start:0x8000923C end:0x80009280
```

The unit's ranges must cover whole functions. dtk preserves hand-added units when it regenerates the file.<br />
Multiple functions from one source file go in as multiple lines, or one wider range if they're contiguous.<br />
Game source file names aren't known, so name a game unit after its first function (`Game/fn_8000923C.cpp`) and rename it once the real name turns up.

> **Also rename the placeholder symbol in `symbols.txt`, in the same edit:** If the function is still named `fn_801834FC` and you're extending a file already flagged `Matching`, the link breaks immediately with `undefined: 'fn_801834FC', referenced from '…'`. This means some other still-unclaimed caller is referencing the old name.

Reference: [`splits.md`](splits.md)

### Step 3: Register the object in `configure.py`

Add it to the `Game` library's `objects` in `config.libs`, which compiles with ProDG at `-O0`. A function in one of the middleware ranges (check with `python3 tools/flavor_map.py <address>`; they have no frame pointer) goes in the `Middleware` library instead, which compiles at `-O2`, and a function in the `-fno-strength-reduce -G0` block adds `cflags=cflags_prodg_middleware_g0` to its `Object`. Name middleware units `RealCore/`, `CSIS/`, `Apt/`, `Havok/` and so on, after the function, and write them as `.c` unless they need classes or `new` (at `-O2`, `cc1` and `cc1plus` agree for anything without classes). `RealCore/fn_8023DAA0.c`, `CSIS/fn_80246024.c`, `Apt/fn_8026799C.c` and `Havok/fn_802E8348.c` are the first matched examples.

```python
        "objects": [
            Object(Matching, "Game/fn_800092CC.cpp"),
            Object(NonMatching, "Game/fn_8000923C.cpp"),
        ],
```

A function whose float literals the original keeps in another file's `.rodata` (anything in the tail of `.text` whose pool `dtk dol split` calls cyclic when claimed) takes `extern_pool=<address of its first literal>` on its `Object` instead of a `.rodata` line in `splits.txt`; [`prodg.md`](prodg.md#inline-functions-and-the-tail-of-text) explains why.

> **The `Object` name must be character-for-character identical to the `splits.txt` unit name:** If they differ, the build silently ignores your source. `configure.py` prints `Missing configuration for <name>` when a unit has no matching object.

**`NonMatching` vs `Matching`:**

| Flag | Compiles your source? | What gets **linked** |
|---|---|---|
| `NonMatching` | Yes (so objdiff can compare) | The **original extracted** object |
| `Matching` | Yes | **Your** compiled object |

Always start `NonMatching`. The DOL stays byte-perfect no matter how wrong your source is. Only flip to `Matching` once you're at 100%.<br />
Once a file is flagged `Matching`, adding a new function to it breaks `main.dol` until that function matches too.

### Step 4: Write the source and iterate

Create the source file at `src/<unit name>` (e.g. `src/Game/fn_8000923C.cpp`), then run `ninja` and read the progress line for your category:

```
Game Code: 65.36% fuzzy, 0.00% matched, 0.00% linked (0 / 1 files)
```

Compare the two disassemblies, adjust (see [`matching_notes.md`](matching_notes.md), and [`nonmatching.md`](nonmatching.md) if it is a known stall), and repeat until:

```
Game Code: 100.00% fuzzy, 100.00% matched
```

### Step 5: Flip to `Matching` and verify

Change `NonMatching` to `Matching` in `configure.py`, run `ninja`, and confirm both:

```
build/GVLE69/main.dol: OK          <- the DOL still matches
Game Code: 100.00% ... 100.00% linked
```

**On `force_active`:** a newly-matched function with no visible caller may get dropped by `mwld`'s `-code_merging`, shifting everything after it. The fix is adding its name to `force_active` in `config/GVLE69/config.yml`. Most matches need no entry, so only add one if `main.dol: OK` breaks.

---

## 3. Reading the diff

`build/GVLE69/src/...` is yours, `build/GVLE69/obj/...` is the original.

### objdiff GUI (primary)

Download from [encounter/objdiff](https://github.com/encounter/objdiff), set *Project directory* to this repo. It reads `objdiff.json` and rebuilds automatically on file changes.<br />
Unit names are prefixed with `main/`, e.g. `main/Game/fn_800092CC`. Auto-generated units (everything not yet decompiled) are hidden by default.

### objdump (fast)

binutils isn't downloaded by a normal build; fetch it once with `ninja build/binutils`.

```bash
build/binutils/powerpc-eabi-objdump -d --no-show-raw-insn build/GVLE69/src/Game/fn_800092CC.o
build/binutils/powerpc-eabi-objdump -d --no-show-raw-insn build/GVLE69/obj/Game/fn_800092CC.o
```

### `tools/objdiff_mismatches.py` (exact per-instruction diff)

For an unlinked object, raw objdump output is noisy. This tool wraps the bundled `build/tools/objdiff-cli` and prints only the instructions that differ.

```bash
python3 tools/objdiff_mismatches.py Game/fn_800092CC __static_initialization_and_destruction_0
```

It is stricter than the progress numbers. `report.json` runs objdiff with the default `functionRelocDiffs=none`, which flags a relocation only when the other side has none, so a reloc to the wrong symbol or addend still counts as 100% there. After renaming, splitting or resizing a symbol that matched units reference, check those units with this tool, or run `build/tools/objdiff-cli report generate --config functionRelocDiffs=all -o <file>` and look for anything below 100%.

### Decoding a data constant before you use it

When a function references a string or table you intend to reproduce, read the original bytes first rather than guessing:

1. Find the auto-generated data object covering the address (`build/GVLE69/obj/auto_*`).
2. `objdump -h` it to get the section's base VMA (also encoded in the filename).
3. `objdump -s` at the byte offset and decode.

---

## 4. Choosing what to work on

The SDK, libc, compiler runtime and SN debug stub are fully matched, so what remains is game code. Its `.text` ranges are in [`baseline.md`](baseline.md#memory-map). It is C++ built with SN ProDG (GCC 2.95), and its units go in the `Game` library in `configure.py` (middleware goes in `Middleware`, see step 3). [`prodg.md`](prodg.md) has the flags found so far, the C++ conventions and how static constructors link. `Game/fn_800092CC.cpp` is the first matched example.

Most of the 17,161 functions are still `fn_XXXXXXXX`. Naming is a large part of the work ahead.

- **Work outward from a matched unit.** Pick the unclaimed function right before or after one you've matched, which keeps each unit's range contiguous. A `_GLOBAL_.I.<name>` function marks the end of a source file ([`prodg.md`](prodg.md#c)).
- **Expect `-O0` first.** Game code has `-O0`'s shape: arguments spilled through `r31` and `this` kept in `r30`. A function with no frame pointer is middleware (RealCore, Apt, Havok, ...), built at `-O2`: [`prodg.md`](prodg.md#flags) has the ranges and `python3 tools/flavor_map.py <address>` classifies one. For a C++ unit that is 8 bytes over per function, see the function-end branch pair in [`prodg.md`](prodg.md#the-function-end-branch-pair) and `python3 tools/pair_map.py <address>`.
- **Enemy AI next.** [`ai.md`](ai.md) maps the AI code and gives a target order (section 6). With no function named, take the first unfinished row there.
- **Versus mode is mapped.** [`versus.md`](versus.md) maps the versus code, and [`characters.md`](characters.md) the character data it loads.
- **Name as you go.** C++ symbols use GCC 2.95 mangling (`__5ColorUcUcUcUc`). Rename the `fn_` symbol in `symbols.txt` once you know what a function is.

---

## 5. Files you edit

| File | What it holds |
|---|---|
| `src/**` | Your reconstructed C/C++ |
| `include/**` | Your reconstructed headers |
| `config/GVLE69/splits.txt` | Which address ranges belong to which source file |
| `config/GVLE69/symbols.txt` | Symbol names, addresses, sizes, scope |
| `configure.py` | Object registry, compiler flags, `Matching` status |
| `config/GVLE69/config.yml` | `force_active`, `skip_cfa_ranges`, relocation fixups |

**On regeneration:** dtk rewrites `symbols.txt` and `splits.txt` on every build.
- Hand-named symbols, hand-set attributes and hand-added splits **are preserved**.
- Auto-generated `fn_*` / `lbl_*` names are **not preserved**.
