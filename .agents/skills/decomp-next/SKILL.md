---
name: decomp-next
description: Pick the next best function to decompile in this GameCube decomp (mnroi, GVLE69) and byte-match it end to end. Use when asked to run "/decomp-next", decomp/match/reconstruct the next function or unit, or debug why a unit or main.dol stopped matching.
---

# decomp-next: pick and match the next function

Human-facing references (read the relevant one instead of guessing):

- `docs/workflow.md`: the per-function loop, commands, and how to choose targets.
- `docs/prodg.md`: the ProDG (GCC 2.95) compile path, flags found so far, C++ conventions and
  static constructors. Game code is built with it.
- `docs/matching_notes.md`: reusable matching rules. **Read it before your first iteration on a
  function**, and again whenever a function stalls short of 100%.
- `docs/nonmatching.md`: functions stuck as `NonMatching`, with everything already tried. Check it
  before starting a function, and don't re-guess what it lists.
- `docs/baseline.md`: why the build is set up the way it is (toolkit fork, r13 small data, memory map).

## Preconditions

- `build/tools/dtk-dev` exists and `build.ninja` was configured with `--dtk build/tools/dtk-dev`.
  If `ninja` downloads stock dtk or `main.dol` stops matching on a clean tree, reconfigure with
  that flag (see README "Building"). Never "fix" this by editing `config.yml`.
- Run `ninja` once and confirm the baseline matches **before** changing anything. If it doesn't,
  stop and report; don't start matching against a broken baseline.
- **`main.dol: OK` is not printed on every run.** It comes from the `CHECK` step, which reruns only
  when `main.dol`, `config/GVLE69/build.sha1` or `dtk-dev` changed. On an up-to-date tree `ninja`
  prints just `PROGRESS` and the progress table.
  - **Pass:** exit status 0. `build/GVLE69/ok` newer than `main.dol` also means the last check
    passed; a failed check never creates or touches that file.
  - **Fail:** `build/GVLE69/main.dol: FAILED` and exit status 1.
  - To force the check to run and print, `rm build/GVLE69/ok && ninja`.

## Loop

1. **Choose.** If the user named a function or unit, work that one. Otherwise follow "Choosing what
   to work on" in `docs/workflow.md`: the unclaimed game function next to an already-matched unit,
   preferring small `-O0` ones. Skip anything listed in `docs/nonmatching.md`.
2. **Research.** No reference decomp exists for the game code, and `GameGC.elf` is stripped. Read
   the function's disassembly (`build/GVLE69/asm/`), its callers and callees, and the data it
   touches. Check `prodg.md` for the flags and C++ conventions that apply, and look for an existing
   class layout in `src/Game/` before declaring a new one.
3. **Claim.** Compute `end = start + size` from `config/GVLE69/symbols.txt`. In one edit, add the
   range to `splits.txt` (tab-indented) and rename `fn_XXXXXXXX` in `symbols.txt` if you know the
   real name (GCC 2.95-mangled for C++). Name a new unit after its first function,
   `Game/fn_XXXXXXXX.cpp`.
4. **Register** as `Object(NonMatching, "<unit>")` in the `Game` library in `configure.py`. The name
   must equal the `splits.txt` unit name exactly.
5. **Write** `src/<unit>` and run `ninja`. Inspect remaining differences with
   `python3 tools/objdiff_mismatches.py <unit-without-extension> <function>`; it shows relocation
   types, which byte diffs don't. Form a hypothesis from `docs/matching_notes.md` and `prodg.md`
   instead of random reshaping. If the function's shape doesn't fit `-O0`, suspect the flags before
   the source.
6. **Verify.** Flip to `Matching`, run `ninja`, and require **both** `main.dol: OK` and 100%
   linked. If `main.dol` breaks, run `python3 tools/diff_dol.py` to locate the bytes. Consider
   `force_active` only if the diff shows the function was dropped or shifted.

## Rules

- Leave the unit `NonMatching` if it isn't at 100%. Never flip a partial match.
- Prefer referencing existing (unclaimed) dtk symbols over declaring fresh data or claiming data
  ranges. Override `scope:local` to `scope:global` in `symbols.txt` when needed.
- Don't `git add -f` anything ignored, and don't commit unless asked.
- Record what you learn per "Recording notes" below. Notes never go in this skill.

## Recording notes

Decide which file, if any, before writing anything.

**`docs/matching_notes.md`** is read in full before every function, so every line costs every
future session. Add an entry only if it is:

- **Reusable:** a compiler/linker/dtk/objdiff behaviour or source-shape rule likely to apply to
  other functions, not a fact about this one.
- **Actionable:** it states a symptom recognisable in a diff (an instruction pattern, a frame-size
  gap, a `main.dol` shift, a link error) and the fix.
- **Verified:** the fix reached 100% and `main.dol: OK`, or was measured in a scratch unit.

Write one bullet: **bold symptom or rule**, then 1-3 sentences with the cause, the fix and at most
one example function. `grep` for an existing entry first and update it rather than adding a
near-duplicate. Leave out narrative (attempt counts, percentage progressions, what broke along the
way), per-function write-ups, and failed approaches. Facts about the ProDG flags or C++ conventions
go in `docs/prodg.md` instead.

**`docs/nonmatching.md`** takes the per-function detail for a unit you leave `NonMatching`: its
fuzzy %, what's left, and what you tried. When it later flips to `Matching`, delete its entry and
move only the general lesson, if any, to `matching_notes.md`.

## Report

Finish with: functions matched (name + address), the unit's final state (`Matching` /
`NonMatching` + fuzzy %), whether `main.dol: OK` holds, and any blocker worth recording.

Suggest a single-line commit message for the user to use (don't commit it yourself), e.g.
`Match <FunctionName> (<unit path>)`. Always put it alone in a fenced code block (no
surrounding text or inline backticks) so the terminal offers a copy button:

````
```
Match <FunctionName> (<unit path>)
```
````
