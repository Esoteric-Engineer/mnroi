# Confirmed Non-Matches

Functions claimed as `NonMatching`, with what has already been tried. Don't re-guess these. When a unit flips to `Matching`, delete its entry and move any general lesson to [`matching_notes.md`](matching_notes.md).

---

## The C++ function-end branch pair

Two of the three entries below are the same blocker, and it is not about aggregate returns: **our
`cc1plus` ends every function that is not a constructor with two unreachable branches to the
epilogue, and most of the DOL's C++ functions do not have them.** The generated assembly is literally

```
.L4:
	b .L5          # goto no_return_label
	b .L2          # goto return_label, the cleanup path
.L5:
.L2:
	<epilogue>
```

so both branches are jumps to the immediately following label and GCC's `jump_optimize` — which
2.95 runs only when `optimize > 0` — would delete them. Every unit that needs them gone is therefore
8 bytes over size with an otherwise perfect diff.

The two shapes cluster by file in the DOL, which is what makes this a compiler-configuration problem
rather than a source one: in `.text` order, 0x80024C60-0x8002623C all carry the pair, 0x8002623C-
0x80027D58 all lack it, 0x80027D58-0x8002800C carry it again, and 0x800887AC lacks it.
Both of the project's matched `.cpp` units (`Game/fn_8001C258.cpp`, `Game/fn_800092CC.cpp`) happen
to sit in files that carry it.

Ruled out: all five releases, every source shape tried (`return` early / late / absent, `goto`,
nested blocks, member function, `extern "C"`, non-void return, last statement an `if` / loop /
`switch` / declaration), and 6138 option/form combinations driving `cc1plus.exe` directly (1023
option strings from its own string table in `-f`, `-fno-`, `-W`, `-Wno-`, `-m` and bare form, each
checked for a still-valid compile). `-Wreturn-type` and `-W`, which are what enable `jump_optimize`
at `-O0` in stock GCC 2.95, change nothing here.

So this is the same open question as [`prodg.md`](prodg.md#release): the bundled releases are the
*minority* configuration, and most of the game's C++ needs the other one.

---

## `Game/handlers/characterselect.cpp` — `clashCharSelect_GetCharList`

0x801037B0-0x80103BAC, 99.2% fuzzy. Every instruction matches and the frame layout is identical; the
unit is 8 bytes over size because our build emits **three** branches to the epilogue where the
original has one:

- Original: copy constructor, destructor, `b .L`, then `.L: mr r3, r30` and the epilogue.
- Ours: the same, then `b .L` twice more.

The two extras are the function-end pair described above, so this is not an aggregate-return problem:
returning a class by value is just where it was first noticed. 123 of the DOL's 127 aggregate-return
epilogues have a single branch, and the four with three are in files that carry the pair.
See [`prodg.md`](prodg.md#release).

Also tried, with no effect: all five releases, all five assemblers (plus `ngcasm`), every `-f` option
string in `cc1plus.exe` (1564 candidates in both `-f` and `-fno-` forms; only
`-fprefix-function-name` changed anything, by renaming the symbol), `-fno-exceptions`,
`-fno-rtti`, `-fpcc-struct-return`, `-freg-struct-return`, and `-O1`/`-O2` (which drop the `-O0`
spills the original has). Note that `ngccc` silently discards options it does not recognise, so flag
experiments must drive `CPP.exe` and `cc1plus.exe` directly.

`clashCharSelect_GetPrevCharList` (0x80103BAC) ends with the same copy/destructor/return sequence, so
the rest of the file is blocked the same way.

---

## `Game/fn_800887AC.cpp` — the `.nsc` mission/arena script parser

0x800887AC-0x80089710, 99.80% fuzzy, 8 bytes over size. Every one of the 985 instructions matches,
along with the 0x4e0 frame, the `stmw r27` range, all 98 calls and the 448-byte `.rodata` string
pool the unit claims. The only difference is the C++ function-end branch pair above, which the DOL
does not have.

The unit is C++ rather than C because of the `new NameTable` and the `p->arr[p->n++]` copy pair
([`matching_notes.md`](matching_notes.md)); as `.c` it is instead 8 bytes *short*, missing those two
shapes. 0x800887AC is therefore a pair-less C++ file, and so is whatever else sits between
`_GLOBAL_.I` at 0x80081DCC and the one at 0x800898E4. Nothing else is left to try here: when
[`prodg.md`](prodg.md#release) turns up the configuration that drops the pair, this unit should flip
straight to `Matching`.

---

## `fn_804436D4` — the roster unlock setter (unclaimed)

0x804436D4-0x8044374C, 98.17% fuzzy, and the only gap left in the 0x804428E0-0x804437D8 run, which
is why `Game/fn_804428E0.c` stops at it and the three accessors after it are a separate unit
(`Game/fn_8044374C.c`). The reconstruction is
`fn_804436D4(index, unlocked, remap)`: `fn_80431CCC(index, remap, 0)` and `fn_80431CCC(index, remap, 1)`,
each through the two-local shape of [`matching_notes.md`](matching_notes.md), then `rec->unlocked = unlocked`
(`+0x48`) on both. Every instruction, the 0x28 frame, the `stmw r26` range and both calls match; only
which call-saved register each of the five register variables gets differs:

- Original: first call's temp `r30`, then the three parameters `r29`, `r28`, `r27`, then the second
  call's temp `r26`.
- Ours: parameters `r30`, `r29`, `r28`, then the temps `r27` and `r26`.

So the original allocated the first temp *before* the parameters, which no ordering rule in GCC
2.95's `-O0` allocator (`stupid.c`, which allocates in birth order) explains. The sibling functions
rule out a source fix: `fn_8044B1D4` and `fn_80443678` have the same parameters plus one temp and
match with parameters first, and `fn_80461288` (not claimed) gives its two parameters `r29` and
`r30`, so the DOL's own order is not consistent either. Tried without effect: declaration order of
the two temps (swapping them is worse, 97.83%), splitting declarations from assignments, a nested
block for the second pair, declaring the plain locals first, a fourth `register` parameter to absorb
`r30`, and chaining the second store off the first. Try
[decomp-permuter](https://github.com/simonlindholm/decomp-permuter) next.

---

## `Game/fn_8002623C.cpp` — the actor's per-frame effect gather

0x8002623C-0x80026B9C, 95.2% fuzzy, 8 bytes over size. The reconstruction is otherwise exact: every
instruction, the 0x1c8 frame, the `stmw r25` range, both virtual calls, the 0xA0 and 16-byte struct
copies, the five parallel arrays and the 11-argument call to `fn_8001DCE0` all match. The only
difference is the C++ function-end branch pair above, which the DOL does not have.

One cosmetic non-difference: the 16-byte copy out of `lbl_80515030.managers[g].effects[k].pos`
relocates against `lbl_80515030 + 0x3A0` where dtk's extracted object relocates against
`lbl_805153D0 + 0`. Both resolve to 0x805153D0, so `main.dol` is unaffected and `report.json` scores
it 100%; only `objdiff_mismatches.py` flags it. It is the same object — dtk invented `lbl_805153D0`
because a relocation pointed inside the `.bss` blob — and merging the symbols would need a hand-set
size on an auto-named `lbl_`, which dtk does not preserve.
