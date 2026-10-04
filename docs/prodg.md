# prodg.md

How the build compiles the code SN Systems ProDG built, and what is known about its flags.

For more info on why the project uses two compilers, see [`baseline.md`](baseline.md)

## Which code is ProDG

The Dolphin SDK is Nintendo's prebuilt MWCC output, and `configure.py` builds it with MWCC. Everything else in the DOL was compiled by SN ProDG, a GCC 2.95 build: the game's C++, Newlib/libgcc, the VM library and SN's debug stub.<br />
MWCC can't reproduce GCC's code (frame pointer in `r31`, LR saved after the frame is made, `mr.`/`addic.` code selection, GCC's C++ ABI), so this code is matched with ProDG or not at all.

The evidence: 11,679 of the game's 16,181 functions set up a GCC frame pointer (`mr r31,r1` in their first 16 instructions), and no Dolphin SDK function does; `__start` is SN's crt0 and calls SN's debug stub; the C library is Newlib, not MSL; and small data is addressed only through `r13`. `GameGC.elf` names no compiler version.

## Building a ProDG unit

`mw_version` names a folder under `build/compilers`. A `ProDG/` folder selects SN's `ngccc` (`build/compilers/ProDG/<release>/ngccc.exe`, shipped in the standard compilers download) instead of `mwcceppc`.

| In `configure.py` | Use |
|---|---|
| `PRODG_VERSION` | Release for every ProDG unit, provisionally `ProDG/3.9.3` (see [Release](#release)) |
| `cflags_prodg_game` | Game code, the `Game` library |
| `cflags_prodg_lib` | SN's prebuilt Newlib/libgcc |
| `ProDGLibObject(...)` | One ProDG object inside a library whose other objects are still MWCC asm (`Runtime.PPCEABI.H/strlen.c`) |

The `prodg` rule in `tools/project.py`:

- **`SN_NGC_PATH`:** `ngccc` refuses to start unless this points at the folder holding its `sn.ini`. The rule sets it.
- **Language:** `ngccc` picks C or C++ from the extension (`.c`, `.cpp`), so no `-lang` flag is added.
- **Dependencies:** `-MD`, not `-MMD`: GCC 2.95's `-MMD` leaves out every `<...>` include.
- **Small data:** `dtk elf bake-sda` runs afterwards, as for MWCC objects (see [`baseline.md`](baseline.md#small-data-r13-problem)). `.sdata`/`.sbss` references stay `R_PPC_EMB_SDA21` relocations, which mwld resolves through `r13` like SN's linker did.
- **MWCC-only options:** `shift_jis` is ignored, and `extab_padding` is an error.
- **decomp.me:** ProDG units get scratches with the `prodg_35` .. `prodg_393` compilers.
- **Unknown options are discarded.** `ngccc` forwards only what it recognises, so game code reaches
  `cc1plus` as plain `-O0 -quiet`: `-W`, `-Wall` and most `-f` options never arrive. Run `CPP.exe`
  and `cc1plus.exe` by hand (`ngccc -v` prints the exact command lines) when testing a flag.

`ngccc` ships without headers. `include/gcc` has freestanding `stddef.h` and `limits.h`, and the ProDG flags put it on the include path. There is no `stdarg.h` yet: this GCC has no `__builtin_va_list`, and the DOL calls a `__va_arg` function, so SN's header was not GCC's. Reconstruct it when the first varargs function is matched.

Plain `char` is signed. `cc1` sign-extends it (`extsb`), even though `ngccc`'s preprocessor step defines `__CHAR_UNSIGNED__`; `include/gcc/limits.h` follows the code.

## Flags

**Newlib/libgcc: `-O2`.** Newlib 1.11's `atoi`, `strlen`, `strcat`, `strchr`, `strcmp` and `copysign` compile identically at `-O2` on every release, and are linked that way.

**Game code: `-O0` so far.** Every game function checked has `-O0`'s shape:

- arguments stored to the frame and reloaded through `r31` (`stw r4,0x8(r31)` / `lwz r4,0x8(r31)`);
- `this` kept in `r30` (GCC 2.95 treats `this` as a register variable even at `-O0`), which is where the `stmw r30` prologues come from;
- a doubled branch to the epilogue (`b .L` / `b .L`), which `-O1` and above remove.

`-O2 -fno-omit-frame-pointer` gives the same prologue but not the doubled branch or the spills. Checked on `fn_8000923C`, `fn_80009280` (member calls through `this+0x39C0`) and the static initializer in `Game/fn_800092CC.cpp`.

**The doubled branch only shows up through `cc1plus`.** A plain C leaf function (no calls) compiled at `-O0` with `register` on its parameters and any never-reassigned local keeps them in registers for the whole function (no frame slot, no `stw`/`lwz` round-trip) and emits exactly one `b` per `return`. The same source compiled as C++ (even `extern "C"`) adds a redundant second `b .Lepilogue` after each `return`'s branch (both relocated `R_PPC_REL24`/`_REL14` to the same target) and spills every parameter to the frame regardless of `register`. Symptom: a `NonMatching` unit stuck a few instructions over size with otherwise-perfect fuzzy%. Fix: if the function has no class/this and no C++-only construct, give its unit a `.c` extension instead of `.cpp`. Confirmed on `fn_80431CCC` (0x80431CCC, roster accessor, [`characters.md`](characters.md#2-roster-table)).

**Not everything is `-O0`.** The colour constructor `__5ColorUcUcUcUc` (0x80426EC4) keeps its arguments in registers, and about half the functions in 0x80196884-0x803FF3B0 have no frame pointer: some files, perhaps a middleware library, used other flags. Give those units their own flags when they come up.

### Release

All five releases (3.5, 3.5b140, 3.7, 3.8.1, 3.9.3) give the same output for everything compiled so far: the six Newlib functions, the `-O0` member functions and the static initializer. `PRODG_VERSION` stays at 3.9.3 until some function compiles differently on two releases; then pin it to the release that matches.

### The function-end branch pair

`cc1plus` closes a C++ function with two unreachable branches to the epilogue (`b .L5` / `b .L4` / `.L5:` /
`.L4:`) unless an earlier function **in the same translation unit** left a flag set. The flag explains both
shapes in the DOL, and one compiler produces both. It is not an option, and the release doesn't matter.

**The code.** GCC 2.95.3's `finish_function` (`cp/decl.c`) creates `no_return_label`, and with it the pair, when

```c
return_label != NULL_RTX && current_function_return_value == NULL_TREE
    && ! DECL_NAME (DECL_RESULT (current_function_decl))
```

and then emits `goto no_return_label` / `emit_jump (return_label)` / `no_return_label:`. -O0's
`jump_optimize` only marks dead insns, so both jumps reach the output. SN's build has the stock code
(v1.76 `cc1plus.exe`, `finish_function` at 0x428B10):

| Address | What |
|---|---|
| 0x429223 | `cmp %ebp,0x659ce0`: `return_label` |
| 0x42922B | `mov 0x65b248,%eax`: `current_function_return_value` |
| 0x429234 | `DECL_NAME (DECL_RESULT (fndecl))` |
| 0x42924A | `build_decl (LABEL_DECL, 0, 0)` (`no_return_label`) |
| 0x42928D, 0x4292EF, 0x4292FC | `expand_goto`, `emit_jump (return_label)`, `expand_label` |

`return_label` is never null at expand time: `expand_function_start` (0x4F82F5) clears it only if
`HAVE_return`, and rs6000's `direct_return` (0x401610) is false before reload. No option, environment
variable, `sn.ini` setting or pragma touches the other two values.

**The state.** `current_function_return_value` is set by `c_expand_return` (`cp/typeck.c`, binary
0x46F816) when the returned expression is a declaration and the `return` is not inside an `if`, loop or
`switch`. **Nothing resets it at the start of a function.** Only `define_label` and `define_case_label`
clear it (0x41D11B, 0x41D24D): a user label, or a `case`/`default`. So it carries over from one function
to the next, including inline functions that emit no code:

- **Set by:** any constructor definition (`finish_ctor` returns `this`, a `PARM_DECL`), including an unused
  in-class inline one in a header such as `B() : y(1) {}`, and one the compiler synthesizes mid-file for a
  `new`. Also set by a top-level `return this;`, `return <param>;`, `return <local>;` or
  `return <global>;`, in an inline function too.
- **Not set by:** a destructor, `return this->x;` or any other expression, a nested `return`, an enumerator,
  or a `static const` that folds.
- **Cleared by:** a `switch` with `case`/`default` labels, or a user `label:`, in the function being compiled.
- A function with the flag set loses the pair and keeps one branch per `return`. A constructor never has
  the pair, because it sets the flag itself.

**The DOL agrees.** -O0 compiles a switch to a compare chain, and a B function (void, no trailing
`return`) can't set the flag again after its own `case` labels. So no B function should contain a switch.
**2 of 1,666 B functions do** (`Global_PlayFEStream` and `Cheat_Enable`, whose C-style names suggest C
functions with a `register` first parameter, which `pair_map.py` can't tell from methods). **390 of 2,629 A
functions do.** After a constructor, the next classed function is B 93 times and A 12 times, against a 39%
B baseline, and 7 of those 12 contain a switch.

**Matching a pair-less unit without `strip_fn_end_pair`.** Put a flag-setter ahead of the unit's first
function, for example `inline int sn_return_decl(int a) { return a; }` or a header class's in-class
constructor. It emits no code. With that line, plain `ngccc` gives `Game/fn_800887AC.cpp` and
`Game/handlers/characterselect.cpp` the same `.text` bytes and relocations as their matched
`strip_fn_end_pair` objects. Without it each is 8 bytes over. Order matters inside a unit: a function
that comes before the first setter, or after a `switch`/label, keeps the pair.

**Pair map.** `python3 tools/pair_map.py` classes every GCC function by its epilogue, and
`python3 tools/pair_map.py 0x80103BAC` says which run an address is in. A = carries the pair (flag clear);
B = a method (`this` in r30) with no trailing branch at all (flag set). What it shows:

- 2,629 functions are A and 1,666 are B, in 467 runs. B is undercounted, because a pair-less free function
  with no `return` can't be told from C, so read the totals as "both are common", not as a ratio.
- A and B alternate through the whole `.text`, 153 of the runs being one or two functions long: the
  flag follows each file's headers and function order.
- B dominates the tail, 0x80440000-0x80480000 (80% of classed functions), where most of the versus-mode
  work lives. A dominates 0x800C0000-0x800F0000 (89%) and 0x80200000-0x80240000 (84%).
- It reproduces every boundary stated above (0x80024C60-0x8002623C and 0x800B5BC4-0x800B7094 are A, 0x80027D58
  starts A again, 0x80443908-0x804439E8 is A between B runs) and agrees with every unit already flagged
  `strip_fn_end_pair`.

A quick way to tell a function's state before claiming anything: look at the instructions just before its
last label. Two identical branches to it means the flag was clear; none means it was set. A single branch
is a `return` (in C, or in C++ with the flag set) or a constructor, so it does not settle the question by
itself.

## C++

- **Mangling** is GCC 2.95's: `Color::Color(unsigned char, unsigned char, unsigned char, unsigned char)` is `__5ColorUcUcUcUc`. When a unit calls a function that is still asm, rename dtk's `fn_` symbol in `symbols.txt` to the mangled name so the two sides link.
- **`__6Vector` (0x80428F74) is `Vector::Vector()`**, the default constructor of the game's 16-byte
  vector; it sets only `w`, to 1.0f, and returns `this`. `class Vector { public: float x, y, z, w;
  Vector(); } __attribute__((aligned(8)));` with `Vector::Vector() { w = 1.0f; }` compiles byte for
  byte to it, which is what confirms both the name and the 8-byte alignment. 1696 call sites use it,
  so most game units that touch a vector need the class. Its 4-byte `.rodata` pool at 0x80482CC8
  cannot be claimed on its own: `dtk dol split` reports a cyclic link-order dependency, so the
  function stays unclaimed for now.
- **`new T` calls `__builtin_new`, not `operator new`, and `fn_801ACED4` (0x801ACED4) is it.** GCC
  2.95 emits `bl __builtin_new` for the allocation and `bl __<len><Class>` for the constructor, so
  `rec = new NameTable;` on a 0x5C8-byte class compiles to `li r3, 0x5c8` / `bl __builtin_new` /
  three register copies / `bl __9NameTable`. All 329 of `fn_801ACED4`'s call sites in the DOL have
  that shape and no other callee in the DOL does, so every one of them is a `new` expression and the
  file holding it is C++. Both symbols are renamed in `symbols.txt`.
- **A destructor mangles as `_._<len><Class>` and calls `__builtin_delete` (`fn_801ACF9C`).** GCC
  2.95 gives every destructor an implicit second parameter, `__in_chrg`, and appends
  `if (__in_chrg & 1) __builtin_delete(this);` after the body, so a two-argument call to a
  destructor-shaped function is the compiler's, not the source's. Both symbols are renamed in
  `symbols.txt`; the dots in the name mean a `.c` unit has to reach it through an `__asm__` label
  (`Game/fn_800B7094.c`).
- **A member function mangles as `<name>__<len><Class>`, with no `v` for an empty parameter list**
  (a free function's is `__Fv`): `void GameFlow::RunCommand()` is `RunCommand__8GameFlow`
  (0x800B5BC4). Don't guess a mangling: register the unit `NonMatching`, compile it, read the name
  out of `build/GVLE69/src/<unit>.o` with `readelf -sW`, and put that in `symbols.txt`.
- **Declare the sibling methods a matched method calls as `extern "C"` taking the object pointer.**
  A non-virtual member call at `-O0` is `mr r3, r30`, the arguments, then `bl`, which is exactly a
  free call with `this` as the first argument, so the asm side keeps its `fn_` name and nothing has to
  be renamed. `Game/fn_800B5BC4.cpp` calls 50 of its own class's methods that way.
- **Static initialization.** For a file with global objects that have constructors, GCC 2.95 emits a local `__static_initialization_and_destruction_0(int initialize, int priority)` and a local `_GLOBAL_.I.<first global's name>` that calls it with `(1, 0xFFFF)`, at the end of the file's `.text`. A `_GLOBAL_.I` function in the DOL therefore marks the end of a file. In `symbols.txt`, give both their GCC names with `scope:local`. A global with a *destructor* adds a third function, `_GLOBAL_.D.<same name>`, calling it with `(0, 0xFFFF)` and listed in `.dtors`; the initializer's own branches are `if (priority == 0xFFFF) { if (initialize) ... else ... }`. A file can be nothing but these three (`Game/fn_800B7094.c`), and [`matching_notes.md`](matching_notes.md) has how to write all three by hand when the generated ones cannot be used.
- **`T x = T(...);`, not `T x(...);`:** copy-initialization keeps the constructor's returned `this` (`mr r0,r3` after each call), which the game's static initializers have.
- **A class passed or returned by value travels through memory.** The caller puts it in a stack temp
  and passes the address, so a by-value parameter looks like a pointer one; the hidden return pointer
  arrives in r3 and stays in r30 for the whole function, which pushes `this` to r29. Plain C structs
  use the same convention (checked on a three-deep call chain), so C and C++ call sites look alike.
  What separates them is the temps: C++ allocates a fresh one per statement in statement order, and
  never reuses the ones whose address a reference parameter binds to.
- **Exceptions and RTTI:** no exception tables have shown up yet. Settle the flags when the first unit needs them.

## Constructor and destructor lists

`GameGC.elf`'s section headers show the original layout, and its bytes are identical to `main.dol`'s:

| Section | Address | Contents |
|---|---|---|
| `.ctors` | 0x804825A0, 0x2B4 | -1, 171 constructors, 0 |
| `.dtors` | 0x80482860, 0x9C | -1, 37 destructors, 0 |

The DOL stores both in one section (0x804825A0, 0x360). `__do_global_ctors` counts from `__CTOR_LIST__` (the -1) to the null and calls the entries last to first. Nothing reads `.dtors`, so destructors never run.

How the build reproduces it:

- **Splitting:** the dtk fork splits the DOL section into `.ctors` and `.dtors` when it reads the DOL, so `splits.txt` and the linker script have both. dtk gives each entry to the unit holding its function. A unit claiming the `.text` of a file with a `_GLOBAL_.I` function gets that file's `.ctors` word automatically, with no `splits.txt` line for it, and the ProDG object's own `.ctors` section takes its place in link order.
- **The -1 entries** are `__CTOR_LIST__` and `__DTOR_LIST__`. The fork keeps the units holding them first in link order.
- **The nulls** come from mwld, which ends `.ctors` and `.dtors` with a null pointer as SN's linker did. dtk treats the trailing zeros as linker-generated.
- **Alignment:** `.dtors` and `.rodata` are `align:32` in `splits.txt`, as in SN's link, which leaves the zero padding between the lists.
- **The DOL:** the fork's `elf2dol` merges `.dtors` into the `.ctors` DOL section when `.ctors` starts with -1.
- **`force_active`:** mwld refuses to link a non-empty `.ctors` or `.dtors` unless `_ctors`/`_dtors` (its names for their starts) are live, and drops the unreferenced `__DTOR_LIST__`. `config.yml` keeps all three.

**Modding:** mwld drops an object nothing references, together with its `.ctors` entry. A mod file that only registers itself through a global constructor needs `FORCEFILES { mod.o }` in the linker script, or a reference from code that is linked. `FORCEACTIVE` doesn't help, because `_GLOBAL_.I` functions are local. A kept file's constructor lands at its link-order place in `.ctors`, before the null, and `__do_global_ctors` calls it.

## MWCC units and `.rodata`

Most of the read-only data the SDK clusters own belongs to GCC-built runtime code that this project wrote as MWCC units. MWCC gives its own `.rodata` a fixed 8-byte alignment, which would pad every claim that starts 4-mod-8. So MWCC units keep their read-only data in `.rodata.1` (`#pragma section R ".rodata.1"` plus `__declspec(section ".rodata.1")` on each object), and `tools/fold_rodata.py` renames it to `.rodata` after each MWCC compile. The data then links in order with the ProDG objects' `.rodata`, at its contents' alignment.

## Open questions

- Which release (above).
- Which files use flags other than `-O0`, and what they are.
- File boundaries: a `_GLOBAL_.I` function ends a file, but most files have none. `Game/fn_800092CC.cpp` may start before 0x800092CC.
- Uninitialized C globals become COMMON symbols (`-fno-common` or the rules in [`common_bss.md`](common_bss.md)).
- SN's `stdarg.h`.
