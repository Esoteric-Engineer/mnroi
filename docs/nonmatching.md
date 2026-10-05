# Confirmed Non-Matches

Functions claimed as `NonMatching`, with what has already been tried. Don't re-guess these. When a unit flips to `Matching`, delete its entry and move any general lesson to [`matching_notes.md`](matching_notes.md).

---

## The C++ function-end branch pair

`cc1plus` ends a C++ function with two unreachable branches to the epilogue (`b .L5` / `b .L4` / `.L5:` /
`.L4:`) unless an earlier function in the same translation unit set `current_function_return_value`. A
constructor sets it, and so does a top-level `return` of a parameter, local, global or `this`, even
inside an unused inline function. Only a `case`/`default` or a user label clears it. No option changes it.

**Fix:** put `inline int sn_return_decl(int a) { return a; }` ahead of the unit's first function when the
original's flag was already set there (`Game/fn_800887AC.cpp`, `Game/handlers/characterselect.cpp` and
`Game/fn_8002623C.cpp` do). [`prodg.md`](prodg.md#the-function-end-branch-pair) has the code, the evidence
and the ordering rules, and `python3 tools/pair_map.py <address>` says which state a function was in. There
is no build-side workaround: the build used to have a per-unit `strip_fn_end_pair` that deleted the pair from
the assembly, and it was removed because it can't model a file where a `switch` brings the pair back.

---

## `Game/fn_8044655C.c` — axis clamp-and-scale setter

0x8044655C-0x8044667C, 98.75% fuzzy, size matches. The pool (0.0f, -1.0f, 1.0f at 0x8048CD1C-0x8048CD24) is
`extern const float lbl_...[]`, since claiming it is cyclic. Left: only the float register assignment. The
DOL has `t`=f13, `v`=f12, `s`=f11, `c`=f10 (the clamp temp), mine has `v`=f13, `t`=f12. The source uses one
`register float t` for both the clamp temp and the second branch's target. Tried: separate `c`/`s`/`t` in all six
declaration orders (96.7-97.2%); ternaries instead of `if` chains (first branch +4 bytes, second -20).

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

## `fn_80445E50`, `fn_80445F70` and `fn_804464DC` — float literals in another unit's `.rodata` pool (unclaimed)

0x80445E50-0x80445F00 and 0x80445F70-0x80445FD0. The pool 0x8048BED0-0x8048BF44 (`lbl_8048BEDC` 6.0f,
`lbl_8048BEE0` 2^31 double, `lbl_8048BEE8` 0.0f...) is read in `.text` order by this file's functions,
but `Game/fn_800B7204.c` claims 0x8048BF44 and sits *earlier* in `.text`, so claiming any of it fails
with a cyclic link order (`Game/fn_80445E50.c -> auto_04_8048BEE8_rodata -> Game/fn_800B7204.c -> ...`).
Leaving it unclaimed means the literals have to be `extern`s:

- `fn_80445E50(self, float w)`: `if (w != self->w /* +0x4C */) { self->w = w; GXSetLineWidth((unsigned char)(unsigned int)(self->w * 6.0f), 0); }`
  is 95% with the literal form, differing only in the pool relocations (the float-to-unsigned
  conversion's own 2^31 double is an anonymous pool entry, so it cannot be an extern). Hand-writing the
  conversion with `extern const double` and `register` temps gives 82% (extra `fmr`s, wider
  `stmw`/`stfd` range, `bge` where the built-in expansion has `cror un, eq, gt` / `bso`).
- `fn_80445F70(index)`: `lbl_8066C63C != 0 && lbl_8066C63C->entries[index].value > 0.0f` (table at `+0x1C`,
  0x18-byte entries) is 86%: with `lbl_8048BEE8[0]` the `lis` for the 0.0f is emitted *before* the
  `lfsx` of the left operand (the extern's address is legitimised at expansion, a pooled literal's at
  use), and the base/index registers swap. Swapping the operands is worse (78%).
- `fn_804464DC(self)`: `return self[6] != 0.0f && self[3] != self[5];` (floats; pool 0x8048CD18, claiming
  0x8048CD14 onwards is cyclic through `auto_04_8048D080_rodata`) is 89.8%: same `lis`-before-`lfs`
  order. `register float v = self[6];` fixes the order but keeps `v` in `f0` and shifts the later
  float registers; a `volatile` load of the left operand changes nothing.
- `Game/fn_80447A18.c` (`fn_80447A18(index)`, 0x80447A18-0x80447A7C): `lbl_8066C63C != 0 && lbl_8066C63C->e[index].f0 >= 0.9f`
  with the literal is 99.6%, only the pool relocation differs, but the pool (0x8048E498-0x8048E4C8) is
  cyclic to claim, so the unit stays `NonMatching`; with `extern const float lbl_8048E498[]` it is 90.6% (same
  `lis`-before-`lfsx` order, and the pointer/index registers swap); a `volatile` read of the extern changes nothing.

---

## `Game/fn_80448364.c` — glyph-quad layout and sprite quad

0x80448364-0x804488C0 (`fn_80448364`, then the sprite-quad `fn_804485AC`, 99.19%), size matches. Only the pool relocations differ: the pool (0x8048FCD8-0x8048FD18: unsigned-to-float magic double, 0.0f, 0.5f, signed magic double, then `fn_804485AC`'s) is the unit's own, but claiming it is cyclic (`dtk dol split` fails through `auto_04_8048FCF0_rodata`), and the magic doubles are anonymous compiler pool entries, so they cannot be `extern`s either. Prototype order of `fn_800FDFA8` (floats `x`, `y` first, then the four ints, then the scale float) and a block-scoped colour temp sharing slot 0x10 with the later `face` local are what fixed the code.

---

## `Game/fn_80446C80.c` — float setters through `fn_8042FB28(self + 0x80)`

0x80446C80-0x80446DE8, 95.9% fuzzy, size matches: `fn_80446C80`/`fn_80446CD4` store `v` at `[0]`/`[2]` of the returned float array, `fn_80446D28`/`fn_80446D88` store `fn_801BDB9C(v)` there. The DOL source is `*f(...) = v` in C++, which compiles here to `mr r0, r3` / `mr r29, r0` / `stfs 0(r29)` (and, for the call-on-the-right pair, `mr r28, r3` ... `mr r29, r28`), but cc1 emits the call result direct. 18 `.c` shapes tried (register locals, assignment-as-value, casts through `int`/`char *`/`void *`, two locals, `if ((p = f()))`): the closest, `register float *p; *(p = f()) = v;`, is 99.3% for the first two and has the temp in `r9` instead of `r0`; the last two stay at 95.1% (`stmw r29` vs `r28`). No pair in the DOL, so there is no `.cpp` unit for them either.

---

## `Game/fn_80446ACC.c` — dead-zone remap

0x80446ACC-0x80446BD8, 98.43% fuzzy, 4 bytes over size. Only the early `return 0.0f` differs: the DOL loads the literal straight into `f1` (`lfs f1`), ours loads `f13` and copies (`fmr f1, f13`) because the value comes from an `extern const float[]` rather than a literal. `*p`, `(float)p[0]`, `+p[0]` give the same. The pool (0x8048CD34-0x8048CD48) is the unit's own, but claiming it is cyclic (`matching_notes.md`), so the literal form can't be used.

---

## `Game/fn_8002623C.cpp` — the actor's per-frame effect gather

0x8002623C-0x80026B9C, 99.998% fuzzy, size matches (the pair is solved with a setter line, see the first section).
Every instruction, the 0x1c8 frame, the `stmw r25` range, both virtual calls, the 0xA0 and 16-byte struct
copies, the five parallel arrays and the 11-argument call to `fn_8001DCE0` match. What is left:

- **`subi r11, r8, 0x68a4` at +0x508 (0x80026744), which has no relocation.** The original loads from
  0x8066975C; ours bakes 0x8066984C (`subi ... 0x67b4`), 0xF0 higher, so flipping the unit to `Matching`
  breaks `main.dol` by two bytes at 0x80026746-7. This is the load just before the
  `lbl_80515030.managers[...]` access, so find which global that `lis`/`subi` pair addresses in the
  source and why its baked address differs.
- The 16-byte copy out of `lbl_80515030.managers[g].effects[k].pos` relocates against
  `lbl_80515030 + 0x3A0` where dtk's extracted object relocates against `lbl_805153D0 + 0`. Both resolve
  to 0x805153D0, so on its own this is cosmetic; dtk invented `lbl_805153D0` because a relocation pointed
  inside the `.bss` blob.

---

## `Game/fn_800B4AB8.c` — `GameFlow::OnPadRemoved`

0x800B4AB8-0x800B4CF8, 99.97% fuzzy, the right size. One operand differs: the statement
`unplugged[numUnplugged++] = player` has the original copy the loaded count into a call-saved register
and index from *that* (`mr r29, r11` / `mr r10, r29`), where ours indexes from the load (`mr r10, r11`).
It is the cc1plus-only shape of [`matching_notes.md`](matching_notes.md) (`p->arr[p->n++] = x`), in a
file with no function-end pair, so there is no `.cpp` unit that reproduces it either.

`register int n; unplugged[n = numUnplugged++] = player;` gets the `mr r29, r11` and the right
`stmw r29` range, which is the 99.97%, but `n = x++` yields the loaded value rather than `n`. Tried
without effect: `register int n = numUnplugged++` and `n = ...` as a separate statement (both emit the
increment before the store), a comma expression, `register unsigned`, `+ 0`, `-(-n)`, `(unsigned)`,
swapped `(n = ...)[unplugged]`, pointer-arithmetic forms, a second register local, a `?:`, and
`register volatile` (which takes a frame slot).

---

## `Game/fn_804473E8.cpp`, `Game/fn_80447830.cpp` — constructors that end `b .L` / `.L: mr r3, r30`

0x804473E8-0x80447434 (`Dir::Dir(const void *)`, base `Vector(const short *)`) and 0x80447830-0x804479B0 (that `Vector` constructor, a
local `Vector` built from four packed shorts and copied into `*this`), 88.2% and 97.2% fuzzy, size matches. Every instruction
matches except the tail: the DOL has `bl; b .L; .L: mr r3, r30; <epilogue>`, ours has `bl; mr r3, rN; b .L` (the shape that
matched `Game/fn_80444034.cpp` and `Game/fn_80447618.cpp`), so `b` and `mr` are swapped. In `Dir` the parameter registers also
come out `this`=r29, `src`=r30 against the DOL's r30/r29. An explicit `return;` in the constructor body gives `b A` / `mr r3` /
`b END` / `A: mr r3` / `b END`, i.e. the DOL's tail plus 12 dead bytes, so the original is probably that source in the
pair absent (the flag set by an earlier function, [the branch pair](#the-c-function-end-branch-pair)). The same tail is on `fn_80448A28`,
`fn_80448A74`, `fn_80448AC0`, `fn_80448FD0` and `fn_80449020`; a constructor with `mr r3, r30` *before* the `b` is fine. The
`Vector` constructor's two doubles (0x8048DEA8, 0x8048DEB0) are also cyclic to claim.

---

## `RealCore/fn_8023DAE0.c` — the pass over the 8 registered callbacks

0x8023DAE0-0x8023DB48, 84% fuzzy, size matches, `-O2`. The source is a counted loop: `lbl_8066C888++;` then
`for (i = 0; i < 8; i++) { lbl_8066C88C++; if (lbl_804D7D70[i]) lbl_804D7D70[i](); }`. Strength reduction turns
it into the DOL's pointer loop with the signed `cmpw r31, r30`, and the prologue and call sequence match. What
differs is order inside the loop: the DOL does `lwz r9, lbl_8066C88C` / `addi` / `stw`, *then* `lwz r0, 0(r31)`
(the callback) / `addi r31, r31, 4`; ours hoists the callback load above the counter's `addi`/`stw`.

Tried without effect (all give the same schedule): loading the callback into a local first, `x = x + 1`, a table
pointer local, `slot++` pointer iteration (also gives `cmplw`), and `volatile` on either counter or the table
(the table one switches the loop to `lwzx`). In the original the scheduler evidently could not move the load above the
store. The counters are in `.sdata` and the table in `.data`, so they are not one object; what blocks the move is
unknown.
