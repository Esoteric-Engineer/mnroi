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
| `Object(..., extern_pool=0x8048DEA8)` | A unit whose float pool has to stay in the original's `.rodata` (see [Inline functions](#inline-functions-and-the-tail-of-text)) |

The `prodg` rule in `tools/project.py`:

- **`SN_NGC_PATH`:** `ngccc` refuses to start unless this points at the folder holding its `sn.ini`. The rule sets it.
- **Language:** `ngccc` picks C or C++ from the extension (`.c`, `.cpp`), so no `-lang` flag is added.
- **Dependencies:** `-MD`, not `-MMD`: GCC 2.95's `-MMD` leaves out every `<...>` include.
- **Small data:** `dtk elf bake-sda` runs afterwards, as for MWCC objects (see [`baseline.md`](baseline.md#small-data-r13-problem)). `.sdata`/`.sbss` references stay `R_PPC_EMB_SDA21` relocations, which mwld resolves through `r13` like SN's linker did.
- **Literal pool:** a unit registered with `extern_pool=<address>` goes through `tools/extern_pool.py` between the compile and `bake-sda` (the `prodg_pool` rule).
- **MWCC-only options:** `shift_jis` is ignored, and `extab_padding` is an error.
- **decomp.me:** ProDG units get scratches with the `prodg_35` .. `prodg_393` compilers.
- **Options reach the compiler.** `ngccc` passes every `-O`, `-f`, `-m`, `-W` and `-G` option on to
  `cc1`/`cc1plus` unchanged, including ones `cc1plus` doesn't know (`ngccc -v` prints the exact command
  lines), so per-unit flags such as `-fno-strength-reduce -G0` work through the normal rule on every
  release. Game code reaches `cc1plus` as `-O0 -quiet`.

`-d` options reach the compiler too: `ngccc -O0 -dr -dg -c file.cpp` leaves `<temp name>.rtl` (the RTL as generated) and `<temp name>.greg` (after register allocation) in the current directory, so run it outside the repository.

`ngccc` ships without headers. `include/gcc` has freestanding `stddef.h` and `limits.h`, and the ProDG flags put it on the include path. There is no `stdarg.h` yet: this GCC has no `__builtin_va_list`, and the DOL calls a `__va_arg` function, so SN's header was not GCC's. Reconstruct it when the first varargs function is matched.

Plain `char` is signed. `cc1` sign-extends it (`extsb`), even though `ngccc`'s preprocessor step defines `__CHAR_UNSIGNED__`; `include/gcc/limits.h` follows the code.

## Flags

**Newlib/libgcc: `-O2`.** Newlib 1.11's `atoi`, `strlen`, `strcat`, `strchr`, `strcmp` and `copysign` compile identically at `-O2` on every release, and are linked that way.

**Game code: `-O0` so far.** Every game function checked has `-O0`'s shape:

- arguments stored to the frame and reloaded through `r31` (`stw r4,0x8(r31)` / `lwz r4,0x8(r31)`);
- `this` kept in `r30` (GCC 2.95 treats `this` as a register variable even at `-O0`), which is where the `stmw r30` prologues come from;
- a doubled branch to the epilogue (`b .L` / `b .L`), which `-O1` and above remove.

`-O2 -fno-omit-frame-pointer` gives the same prologue but not the doubled branch or the spills. Checked on `fn_8000923C`, `fn_80009280` (member calls through `this+0x39C0`) and the static initializer in `Game/fn_800092CC.cpp`.

**The doubled branch only shows up through `cc1plus`.** A plain C leaf function (no calls) compiled at `-O0` with `register` on its parameters and any never-reassigned local keeps them in registers for the whole function (no frame slot, no `stw`/`lwz` round-trip) and emits exactly one `b` per `return`. The same source compiled as C++ (even `extern "C"`) adds a redundant second `b .Lepilogue` after each `return`'s branch (both relocated `R_PPC_REL24`/`_REL14` to the same target). `register` parameters stay in registers in C++ too: `fn_80431CCC`'s source compiled as C++ has no spills, and so does `__5ColorUcUcUcUc` below. Symptom: a `NonMatching` unit stuck a few instructions over size with otherwise-perfect fuzzy%. Fix: if the function has no class/this and no C++-only construct, give its unit a `.c` extension instead of `.cpp`. Confirmed on `fn_80431CCC` (0x80431CCC, roster accessor, [`characters.md`](characters.md#2-roster-table)).

**The colour constructor is `-O0`.** `__5ColorUcUcUcUc` (0x80426EC4) keeps its arguments in registers
because they are declared `register`: `Color::Color(register unsigned char r_, ...) { r = r_; g = g_;
b = b_; a = a_; }` compiles byte for byte to it at `-O0` as C++, and without `register` it spills them.

**Middleware: `-O2`, and one block with `-fno-strength-reduce -G0`.** Every function without a frame
pointer in the game ranges is middleware: EA's RealCore, Apt, RealGraph/EAGL, an AV/MAD video player,
Refpack, and Havok. All of `c:/Clash/mainline` is `-O0`: the 14 source paths under it are referenced from
`-O0` code, and the 4 RealCore/RealGraph paths from optimized code. The optimized code sits in three runs
with nothing `-O0` inside them, and the `-O0` ranges have no function without a frame pointer except
the `__restore_fpr` tail of `fn_800350F4` ([`baseline.md`](baseline.md#shifted-builds)).

| Range | Flags | Functions | Contents |
|---|---|---|---|
| 0x8023D994-0x80243F94 | `-O2` | 189 | RealCore 6.27 (file system, DVD, threads) |
| 0x80243F94-0x8026D828 | `-O2 -fno-strength-reduce -G0` | 816 | CSIS allocator, audio, the core of the Apt runtime |
| 0x8026D828-0x803864CC | `-O2` | 2,980 | Apt, memory card, RealGraph/EAGL, AV/MAD video, Refpack, Havok |
| 0x804114EC-0x80426A2C | `-O2` | 160 | wrappers around RealCore, Havok shapes, GX display lists |
| 0x80472F34-0x8047EED8 | `-O2` | 352 | Havok |

`python3 tools/flavor_map.py` prints this table with the evidence counted from the DOL, and
`python3 tools/flavor_map.py 0x80246024` says which class and flag set a function belongs to. The
middle block's edges are only known to within the functions that carry no evidence: it starts after
0x80243EC0 (RealCore's last use of `r13`) and by 0x80246024 (first function proven `-G0`), and ends
before 0x8026D828 (first use of `r13`).

The proof is 40 functions matched in throwaway units, the same on all five releases (each name
below is the function's DOL address). Seven of them are now real units in the `Middleware` library, which
confirms both flag sets through linking: `RealCore/fn_8023DAA0.c` and `Havok/fn_802E8348.c` (`-O2`,
`cflags_prodg_middleware`), `CSIS/fn_80246024.c` and `Apt/fn_8026799C.c` (`cflags_prodg_middleware_g0`):

- **`-O2`:** RealCore `fn_8023DAA0`, `fn_8023DAE0` (a loop over 8 function pointers), `fn_8023DB6C` (a
  7-case switch), `fn_8023DC08`, `fn_8023DC84`; Apt `fn_8026F77C`, `fn_8026F7AC`, `fn_8026F7D0`,
  `fn_8026F7DC`, `fn_8026F7E4`, `fn_802AFD6C` (allocates with `new int[n]` and fills it); Havok
  `fn_802E8348`, `fn_802E8350`, `fn_80416B08` (`hkVector4` member copies), `fn_80473620`, `fn_80475994`,
  `fn_8047534C` (an `hkBool` returned by value), `fn_80474FF0`; `fn_80419AF8`, `fn_80419B1C` (display-list
  writes) and `fn_80413E78`, `fn_80413EA4`.
- **`-O2 -fno-strength-reduce -G0`:** `fn_80246024`, `fn_8024606C`, `fn_802460AC`, `fn_802460E4`,
  `fn_80246130` (the CSIS allocator), `fn_802456C8` (table CRC-16), `fn_8024CD8C`, `fn_8025B34C` (`y[i] +=
  a * x[i]`), `fn_8024D32C` (quarter-wave sine table), `fn_8025882C`/`fn_80258838`, `fn_80267834`,
  `fn_8026788C` and five accessors at 0x8026799C-0x802679BC.

What tells the sets apart, and what each proof rules out:

- **Not `-O1`:** `-O1` doesn't schedule (`-fschedule-insns`, `-fschedule-insns2`), which reorders loads
  and stores in nearly every proof. `-O2 -fno-schedule-insns` breaks `fn_802E8350`, `fn_80416B08`, `fn_80473620` and
  `fn_802AFD6C`; `-fno-schedule-insns2` breaks those and the display-list writes and wrappers too.
- **Not `-Os`:** `-Os` keeps loops and addresses differently (`fn_8023DAE0`, `fn_802456C8`, `fn_802AFD6C`,
  `fn_80473620` all differ), as it does for Newlib's `strlen`.
- **Not `-O3`:** `-O3`'s `-finline-functions` inlines a small function into a caller later in the same
  file, and the DOL doesn't: `fn_8023DC08` calls `fn_8023DB6C`, `fn_80258838` calls `fn_8025882C` (both
  checked by compiling), `fn_8026F7EC` calls `fn_8026F7D0`, `fn_802EEDA4` calls three two-instruction
  getters, and `fn_80412858` calls `fn_80412838`.
- **Strength reduction:** with it, a counted loop becomes a `mtctr`/`bdnz` loop over a pointer; without
  it, the loop keeps its counter and indexes with `slwi` + `lwzx`/`stwx`/`lfsx`. The middle block has
  81 functions with such indexed loops and no `bdnz` loop (except `fn_80260AEC`, below), and
  `fn_802456C8`, `fn_8024CD8C` and `fn_8025B34C` only match with `-fno-strength-reduce`. The `-O2`
  ranges have 159 functions with `bdnz` loops, and `fn_8023DAE0` and `fn_802AFD6C` only match with it on.
- **`-G0`:** no small data, so every global is reached through `lis`/`addi`. The middle block's 816
  functions never use `r13`. `fn_80267BC4` reads RealCore's 4-byte `.sdata` variable `lbl_8066C884`
  through `lis`/`lwz`, where RealCore's own code uses `@sda21`. That is only possible from a `-G0`
  unit, unless the header declared the variable as an incomplete array. The CSIS functions and
  `fn_80267834` need `-G0` to match, and RealCore's `fn_8023DAA0` and Apt's `fn_8026F7AC` stop matching
  with it.
- **No effect on the proofs:** `-fno-defer-pop`, `-ffast-math`, `-f[no-]strict-aliasing`, `-fno-regmove`,
  `-fno-gcse`, `-fno-caller-saves`, `-mcpu=750`, `-fno-rtti` and `-fno-exceptions` (the last two are
  `cc1plus`'s defaults here), so they are undetermined. `-fno-inline`, `-finline-functions`,
  `-funroll-loops` and `-fno-omit-frame-pointer` each break some.

At `-O2` the C++ pair is gone and `cc1` and `cc1plus` give the same code for anything without
classes, so the language of an optimized unit follows its content: vtable calls or `new` make it
C++.

**Not compiler output:** `fn_802DF3F0` to `fn_802E0038` (12 functions, 0xD0C bytes, in the video
code) use paired-single instructions (`psq_l`, `ps_madd`, ...), which GCC 2.95 never emits:
hand-written assembly. Havok's `mftb` (150 functions) is inline assembly inside compiled functions,
so those are still `-O2` output. Two optimized functions keep a frame pointer because they call
`alloca` (`fn_802424F8`, `fn_802C8DD8`, with `stwux r11,r1,r0`). `tools/flavor_map.py` classes them
as `asm` and `alloca`.

**Telling a function's flags apart before claiming it:**

1. `mr r31,r1` in the prologue (and no `stwux`) means `-O0` with the game flags; check the branch pair
   with `pair_map.py`.
2. No frame pointer means middleware: `python3 tools/flavor_map.py <address>` gives the range's flags.
3. Inside the optimized ranges, `r13` access rules out `-G0`, a `lis` access into `.sdata`/`.sbss`
   requires it, a `bdnz` loop rules out `-fno-strength-reduce`, and call-free loops that index with
   `slwi` point to it.
4. A function at the edge of a range, or one whose evidence contradicts its range, decides its own
   file's flags: compile it both ways.

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

**Matching a pair-less unit.** Put a flag-setter ahead of the unit's first function, for example
`inline int sn_return_decl(int a) { return a; }` or a header class's in-class constructor. It emits no code.
`Game/fn_800887AC.cpp`, `Game/handlers/characterselect.cpp` and `Game/fn_8002623C.cpp` use that line, and
without it each is 8 bytes over per function. Order matters inside a unit: a function that comes before the
first setter, or after a `switch`/label, keeps the pair, so use a real constructor or header function when
the original's is known.

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
  starts A again, 0x80443908-0x804439E8 is A between B runs) and agrees with the matched pair-less units.

A quick way to tell a function's state before claiming anything: look at the instructions just before its
last label. Two identical branches to it means the flag was clear; none means it was set. A single branch
is a `return` (in C, or in C++ with the flag set) or a constructor, so it does not settle the question by
itself.

### Inline functions and the tail of `.text`

`cc1plus` emits every function defined in a class body, every `inline` function and every template
instantiation into a section of its own, `.gnu.linkonce.t.<mangled name>`, with a weak symbol; only
ordinary functions go to `.text`. Compiling `class V { public: float x; float half() { return x * 0.5f; } };`
with a caller gives `.text` (the caller) and `.gnu.linkonce.t.half__1V`. The function's float pool does
**not** follow it: all pools go to the file's one `.rodata`, in the order the compiler wrote the functions
out, and it writes the linkonce ones last.

A linker keeps one copy of each linkonce function, and SN's placed them after the ordinary `.text`. The
game's shared classes are there, from `Color` and `Vector` (0x80426EC4, 0x80428F74) through the `String` class
(0x80448xxx-0x8044Axxx). The DOL shows it three ways:

- **Their float pools sit in the middle of other files' `.rodata`.** `unpack__6Packed` (0x80447830) reads its
  two doubles from 0x8048DEA8, between the float pool and the `"deb_big0"` strings of a 0x800Dxxxx file.
  `fn_80445E50` reads 0x8048BEDC, between the pools of `Game/fn_800B7094.c` and `Game/fn_800B7204.c`.
  `__6Vector` reads its 1.0f from 0x80482CC8, in the first kilobyte of `.rodata`.
- **The pools are there once per file that used the function, the code once.** `fn_80445E50`'s pool (6.0f and
  the 2^31 double) is in `.rodata` three times: at 0x8048BEDC, which the code reads, and unreferenced at
  0x804A2468 and 0x804BEC10; the function is called from 0x8022xxxx and 0x803E83xx. The 0.0f, -1.0f, 1.0f of
  `fn_8044655C` is at 0x8048CD1C and again, unreferenced, at 0x8048DEB8, right behind `unpack__6Packed`'s
  doubles, in the file that calls it from 0x800D3Dxx. This is where dtk's oversized `lbl_`s with one
  referenced word in front come from.
- **The function-end pair is mostly absent there** ([above](#the-function-end-branch-pair)), which fits
  functions written out at the end of a file, after its constructors have set the flag.

**Such a pool cannot be claimed.** A unit with `.text` at 0x80447830 and `.rodata` at 0x8048DEA8 has to link
after `Game/fn_8010611C.cpp` by `.text` and before it by `.rodata`, and mwld has one link order. That is the
"cyclic dependency" `dtk dol split` reports.

**`extern_pool`.** A unit that holds such a function keeps its literals in the source and is registered as
`Object(Matching, "Game/fn_80447830.cpp", extern_pool=0x8048DEA8)`, the address of its first literal in the
original. `tools/extern_pool.py` then runs on the compiled object: it checks the object's literals against
the original DOL from that address on, retargets each relocation against the pool to the `lbl_<address>`
symbol dtk gave that literal, and empties the section. The literals stay in dtk's unclaimed `.rodata`, the
code is what the literal form compiles to, and the relocations equal the original's. A literal that does not
match the original fails the build with its offset and the two values.

The two copies of a pool need not be laid out alike: a double is 8-aligned, so a pool that starts 4 bytes off
an 8-byte boundary in the original has its padding in other places than the object's, which always starts on
one (`Game/fn_80445E50.c`: 6.0f, padding, double here; 6.0f, double there). So the tool takes each literal's
size from the `lfs` or `lfd` that loads it, lays the original out again from the address with the same
alignment rule, and compares literal by literal. Whatever in the object's `.rodata` no `lfs` or `lfd` loads
has to be zero padding, so a unit with a string literal or a table in `.rodata` is rejected: `extern_pool`
is for float pools only.

The pool addresses of consecutive functions are consecutive when the original file wrote them out together,
so several functions can share a unit and one address (`Game/fn_80448364.c`). When they are not, give each
function its own unit. A unit that owns its `.rodata` for real (strings, a file's ordinary functions) claims
it in `splits.txt` as before; `extern_pool` is for the linkonce functions.

Faithful would be one object per original file, with its inline functions in linkonce sections. That needs the
whole file matched and a linker that places those sections, which mwld does not.

### Register allocation at `-O0`

Only `register` variables, parameters declared `register`, `this` and compiler temporaries live in
registers at `-O0`. GCC 2.95's `stupid.c` allocates them in one pass:

- **Order:** longest lifetime first, then fewest references, then the order the compiler created them. Each
  takes the first free register of its kind: `r30` downwards if its lifetime spans a call, else `r0`, `r9`,
  `r11`, `r10`...; floats `f0`, `f13`, `f12`, `f11`... or `f31` downwards.
- **A `register` parameter** lives from its entry copy to a `use` at the very end. All of them tie, so the one
  with the fewest references gets the first register, and equal ones go in declaration order. That is why a
  seldom-used parameter can sit above `this`.
- **A `register` local** lives from its declaration to the end of its block, which is always shorter than a
  parameter, so it comes after every `register` parameter.
- **A value the compiler saves** (`SAVE_EXPR`: the initializer of a C++ reference local, an operand `fold`
  evaluates once for several uses) lives from just after the parameters' entry copies to just after their
  final `use`s, and the lifetimes nest: with `n` of them, the `k`-th created lives `n - 2k` steps longer than
  a parameter. One is a step shorter than the parameters. With two, the first ties with the parameters and
  wins on reference count, and the second comes last: `fn_804436D4` has `r30` for the first reference,
  `r29`-`r27` for the parameters, `r26` for the second. So a saved value that sits *above* the parameters
  counts the ones created after it: `fn_80437E50` has five (`r30`, `r29`, parameters, `r25`-`r23`).
- **What makes one, and in which order:** a virtual call on a call result makes two, the vtable entry
  address first and the receiver second; a derived-to-base conversion of a call result used as `this` makes
  one per conversion, the outer conversion first.
- **Other temporaries** live from their set to their last use and take whatever is free.

`-dr -dg` (above) shows all of it: in the `.rtl` file the `(use (reg N))` insns after `NOTE_INSN_FUNCTION_BEG`
and before `NOTE_INSN_FUNCTION_END` bound each lifetime, and the `.greg` file's `Register dispositions` line
gives the hard register of each pseudo.

## C++

- **Mangling** is GCC 2.95's: `Color::Color(unsigned char, unsigned char, unsigned char, unsigned char)` is `__5ColorUcUcUcUc`. When a unit calls a function that is still asm, rename dtk's `fn_` symbol in `symbols.txt` to the mangled name so the two sides link.
- **`__6Vector` (0x80428F74) is `Vector::Vector()`**, the default constructor of the game's 16-byte
  vector; it sets only `w`, to 1.0f, and returns `this`. `class Vector { public: float x, y, z, w;
  Vector(); } __attribute__((aligned(8)));` with `Vector::Vector() { w = 1.0f; }` compiles byte for
  byte to it, which is what confirms both the name and the 8-byte alignment. 1696 call sites use it,
  so most game units that touch a vector need the class. Its 4-byte `.rodata` pool at 0x80482CC8
  cannot be claimed (`dtk dol split` reports a cyclic link-order dependency), so the function is
  still unclaimed; `extern_pool=0x80482CC8` should be what it needs
  ([Inline functions](#inline-functions-and-the-tail-of-text)), which has not been tried.
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
- The exact edges of the `-fno-strength-reduce -G0` block (see [Flags](#flags)), and `fn_80260AEC`
  inside it: its two loops are `bdnz` loops, so its file was built with strength reduction on. It
  doesn't use small data, so `-O2 -G0` is the likely set; compile it to find out.
- The `-O2` ranges have 22 functions whose call-free loops still index with `slwi` (`fn_803372F0`, a
  search loop with its first iteration peeled, is the smallest). Strength reduction can leave a loop
  like that, but none has been matched, so a few `-fno-strength-reduce` files in Havok or Apt are not
  ruled out.
- Region C (0x80472F34-0x8047EED8) has no caller of a small earlier function, so `-O3` is ruled out
  there only by analogy with the rest of Havok.
- `-fno-defer-pop`, `-ffast-math`, strict aliasing, `-mcpu` and the other options that changed none
  of the proofs.
- Which file each tail function's pool belongs to, and so which inline functions each file used ([Inline functions](#inline-functions-and-the-tail-of-text)).
- File boundaries: a `_GLOBAL_.I` function ends a file, but most files have none. `Game/fn_800092CC.cpp` may start before 0x800092CC.
- Uninitialized C globals become COMMON symbols (`-fno-common` or the rules in [`common_bss.md`](common_bss.md)).
- SN's `stdarg.h`.
