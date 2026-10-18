# Confirmed Non-Matches

Functions claimed as `NonMatching`, with what has already been tried. Don't re-guess these. When a unit flips to `Matching`, delete its entry and move any general lesson to [`matching_notes.md`](matching_notes.md).

One registered unit is `NonMatching` (below), and one compiler behaviour used to park whole files.

## `fn_800C94C8` (`Game/fn_800C94C8.cpp`, 99.84%)

Only register numbers differ: the `fn_80434C2C` result is `mr r26, r3` / `stw r26, 0x1858` in the DOL, and the three `*Entity_GetActor(self)` temporaries in the loop are r25, r24, r23 (ours r26, r25, r24, with the result in r23). Frame layout, size and every other instruction match.

- `cand` is a function-level `void *` with `register void *tmp` declared at the top of the function (so the prefix temporaries land right) and `tmp = f(); cand = tmp;` in the loop. This is the best form.
- `Ent &cand = *f();` inside the loop gives the right registers but puts the slot after the loop's locals (0x1880, frame 8 bytes too big, `best` at 0x1858): the DOL's `cand` slot is the first local, ahead of `best`, so a reference declared in the loop body can't be it.
- `if (!(cand = f()) || ...)`, `cand = &(Ent &)*f()`, `cand = &static_cast<Ent &>(*f())` and a plain `void *cand = f()` give `mr r0, r3` or no copy at all.
- `register PEnt *` locals for the three loop temporaries (declared after `tmp`) move `self` off r27 (97%).

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
