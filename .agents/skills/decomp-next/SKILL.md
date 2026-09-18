---
name: decomp-next
description: Pick the next best function to decompile in this GameCube decomp (mnroi, GVLE69) and byte-match it end to end. Use when asked to run "/decomp-next", decomp/match/reconstruct the next function or unit, work the next candidate off the list, or debug why a unit or main.dol stopped matching.
---

# decomp-next: pick and match the next function

Human-facing references (read the relevant one instead of guessing):

- `docs/workflow.md` — the per-function loop, commands, and how to choose targets.
- `docs/matching_notes.md` — compiler/linker gotchas and confirmed non-matches. **Read it before
  your first iteration on a function**, and again whenever a function stalls short of 100%.
- `docs/baseline.md` — why the build is set up the way it is (toolkit fork, r13 small data).

## Preconditions

- `build/tools/dtk-dev` exists and `build.ninja` was configured with `--dtk build/tools/dtk-dev`.
  If `ninja` downloads stock dtk or `main.dol` stops matching on a clean tree, reconfigure with
  that flag (see README "Building"). Never "fix" this by editing `config.yml`.
- Run `ninja` once and confirm it ends with `build/GVLE69/main.dol: OK` **before** changing
  anything. If it doesn't, stop and report; don't start matching against a broken baseline.

## Loop

1. **Choose.** No target is given up front — decide it yourself: `python3 tools/find_candidates.py`,
   or take the next unclaimed function after a recently matched one in `config/GVLE69/splits.txt`.
   If the user named a specific function or unit instead, work that one. Skip anything in the
   "Confirmed non-matches" list in `docs/matching_notes.md`.
2. **Research first.** For SDK/runtime addresses (`0x80169000`+), search `../ac-decomp`
   (`src/static/dolphin/`, `include/dolphin/`) by apparent purpose, constants, or struct
   offsets before writing any code. If the sibling clone is missing, say so rather than
   skipping this step silently.
3. **Claim.** Compute `end = start + size` from `config/GVLE69/symbols.txt`. In one edit: add
   the range to `splits.txt` (tab-indented), and rename `fn_XXXXXXXX` to the real name in
   `symbols.txt`.
4. **Register** as `Object(NonMatching, "<unit>")` in `configure.py`. The name must equal the
   `splits.txt` unit name exactly.
5. **Write** `src/<unit>` and run `ninja`. Inspect remaining differences with
   `python3 tools/objdiff_mismatches.py <unit-without-.c> <function>`; it shows relocation
   types, which byte diffs don't. Form a hypothesis from `docs/matching_notes.md` instead of
   random reshaping; switch to asm transliteration for control-flow-sensitive functions.
6. **Verify.** Flip to `Matching`, run `ninja`, and require **both** `main.dol: OK` and 100%
   linked. If `main.dol` breaks, run `python3 tools/diff_dol.py` to locate the bytes; consider
   `force_active` only if the diff shows the function was dropped/shifted.

## Rules

- Leave the unit `NonMatching` if it isn't at 100%. Never flip a partial match.
- Prefer referencing existing (unclaimed) dtk symbols over declaring fresh data or claiming
  data ranges; override `scope:local` → `scope:global` in `symbols.txt` when needed.
- Don't `git add -f` anything ignored, and don't commit unless asked.
- When you learn a new, reusable gotcha or confirm a non-match, add it to
  `docs/matching_notes.md` (concise, with the symptom and the fix), not to this skill.

## Report

Finish with: functions matched (name + address), the unit's final state (`Matching` /
`NonMatching` + fuzzy %), whether `main.dol: OK` holds, and any blocker worth recording.

Suggest a single-line commit message for the user to use (don't commit it yourself), e.g.
`Match <FunctionName> (<unit path>)`.
