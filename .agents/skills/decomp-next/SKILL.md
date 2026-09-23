---
name: decomp-next
description: Pick the next best function to decompile in this GameCube decomp (mnroi, GVLE69) and byte-match it end to end. Use when asked to run "/decomp-next", decomp/match/reconstruct the next function or unit, work the next candidate off the list, or debug why a unit or main.dol stopped matching.
---

# decomp-next: pick and match the next function

Human-facing references (read the relevant one instead of guessing):

- `docs/workflow.md` — the per-function loop, commands, and how to choose targets.
- `docs/matching_notes.md` — compiler/linker gotchas and matching techniques. **Read it before
  your first iteration on a function**, and again whenever a function stalls short of 100%.
- `docs/nonmatching.md` — functions stuck as `NonMatching`, with everything already tried. Check it
  before starting a function, and don't re-guess what it lists.
- `docs/baseline.md` — why the build is set up the way it is (toolkit fork, r13 small data).

## Preconditions

- `build/tools/dtk-dev` exists and `build.ninja` was configured with `--dtk build/tools/dtk-dev`.
  If `ninja` downloads stock dtk or `main.dol` stops matching on a clean tree, reconfigure with
  that flag (see README "Building"). Never "fix" this by editing `config.yml`.
- Run `ninja` once and confirm it ends with `build/GVLE69/main.dol: OK` **before** changing
  anything. If it doesn't, stop and report; don't start matching against a broken baseline.
- **`main.dol: OK` is not printed on every run — this is normal, don't investigate it.** The
  message comes from the `CHECK` step (`dtk shasum -c`, output `build/GVLE69/ok`), which ninja
  reruns only when `main.dol`, `config/GVLE69/build.sha1` or `dtk-dev` is newer than it. Ninja's
  default target is `progress`, which never writes a file and so always reruns: on an up-to-date
  tree `ninja` prints just `[1/1] PROGRESS` plus the progress table and exits 0, with no `OK`
  line. You will never see ninja's `no work to do`, so its absence means nothing.
  - **Pass:** exit status 0. Independently, `build/GVLE69/ok` newer than `main.dol` means the
    last check passed — a failed check never creates or touches that file.
  - **Fail:** `build/GVLE69/main.dol: FAILED` followed by
    `WARNING: 1 computed checksum(s) did NOT match`, and exit status 1.
  - To force the check to run and print, `rm build/GVLE69/ok && ninja`.

## Loop

1. **Choose.** Take the next `open` row in `docs/sdk_queue.tsv`. Prefer, in order: `known`
   (already named in `symbols.txt`), `exact` (size matches the reference), then `guess`, and within a
   tier the smallest size. Skip `unidentified` rows (they need scouting, not matching) and anything listed in
   `docs/nonmatching.md`. Library ranges are in `docs/sdk_libraries.md`. If the user named a specific function or unit instead, work that one.
   `tools/find_candidates.py` (small leaf functions only) is a fallback, not the main chooser.
   `python3 tools/sdk_scout.py info <addr>` shows a function's callees, callers and hardware
   registers, which helps confirm an identity.
   - **Out of queue:** if no `open` row of tier `known`/`exact`/`guess` is left, stop. Tell the
     user the queue is exhausted (counts by status/library, what remains) and that the next step is
     a planning session (re-scout the range, find AR/ARQ/DSP/CARD, decide on game code).
     Don't start game code or invent targets.
2. **Research first.** Find the reference by the row's `library`, and read it before writing code:
   - Dolphin SDK libraries (`os`, `exi`, `si`, `db`, `dvd`, `vi`, `pad`, `ai`, `gx`, `odemuexi2`,
     `odenotstub`): search `../ac-decomp` (`src/static/dolphin/`, `include/dolphin/`) by apparent
     purpose, constants, or struct offsets. `../mkdd` (doldecomp/mkdd) is a second source for EXI.
   - `libc` rows (string, stdio, scanf, math, libgcc division): **Newlib, not MSL**, so ac-decomp
     and the other MSL decomps do not help. Use upstream Newlib/fdlibm/libgcc source; names come
     from CFTKK-Decomp (see `docs/sdk_libraries.md`, which also lists the known version drift). This
     libc lives in the existing `Runtime.PPCEABI.H` library (`cflags_runtime`); name the unit after the
     function (like `strcat.c`).
   If the reference clone is missing (`../ac-decomp`; `../newlib-cygwin` for libc, which is not cloned yet), say so rather than
   skipping this step silently.
   **Verify the name.** Queue names for `exact`/`guess` rows come from size and order only. Confirm
   in the reference that the code shape and callees agree before renaming. If it doesn't, don't force it:
   set the row's `status` to `wrong-name` and note what it looks like instead.
3. **Claim.** Compute `end = start + size` from `config/GVLE69/symbols.txt`. In one edit: add
   the range to `splits.txt` (tab-indented), and rename `fn_XXXXXXXX` to the real name in
   `symbols.txt`.
4. **Register** as `Object(NonMatching, "<unit>")` in `configure.py`. The name must equal the
   `splits.txt` unit name exactly.
   - **New library** (e.g. `pad`, not registered yet): add a `DolphinLib("pad", [Object(...)])`
     entry to `config.libs`, in link order (address order: `pad` goes after `vi` and before `ai`),
     with units named `Dolphin/pad/<unit>.c` in both `splits.txt` and `src/`. `DolphinLib` supplies
     `GC/1.2.5n` and `cflags_base`. The SDK libraries were built at different dates (PAD Aug 2003,
     DVD Sep 2003, the rest Apr 2003), so if the first function matches poorly in an
     unexplained, uniform way, suspect the flags or compiler version before the source. Record
     what you find in `docs/matching_notes.md`.
5. **Write** `src/<unit>` and run `ninja`. Inspect remaining differences with
   `python3 tools/objdiff_mismatches.py <unit-without-.c> <function>`; it shows relocation
   types, which byte diffs don't. Form a hypothesis from `docs/matching_notes.md` instead of
   random reshaping; switch to asm transliteration for control-flow-sensitive functions.
6. **Verify.** Flip to `Matching`, run `ninja`, and require **both** `main.dol: OK` and 100%
   linked. Flipping a unit relinks, so `CHECK` does run here and the `OK` line should appear; if
   it somehow doesn't, use the Preconditions criteria rather than assuming a break. If `main.dol` breaks, run `python3 tools/diff_dol.py` to locate the bytes; consider
   `force_active` only if the diff shows the function was dropped/shifted.

## Rules

- Leave the unit `NonMatching` if it isn't at 100%. Never flip a partial match.
- Prefer referencing existing (unclaimed) dtk symbols over declaring fresh data or claiming
  data ranges; override `scope:local` → `scope:global` in `symbols.txt` when needed.
- Don't `git add -f` anything ignored, and don't commit unless asked.
- When you learn a new, reusable gotcha, add it to `docs/matching_notes.md` (concise, with the
  symptom and the fix); when you confirm a non-match, add it to `docs/nonmatching.md`. Not to this skill.

## Queue upkeep

Update the row in `docs/sdk_queue.tsv` in the same change: `status` -> `matched` (100% and
`main.dol: OK`), `stalled` (left `NonMatching`; note the blocker), or `wrong-name`. If matching
reveals the identity of neighbouring functions (or that a library boundary is off), fix those rows
and `docs/sdk_libraries.md`. After a batch of matches, run `python3 tools/sdk_scout.py queue` to
re-guess the `unidentified` rows with the new anchors; it keeps curated rows and statuses.

## Report

Finish with: functions matched (name + address), the unit's final state (`Matching` /
`NonMatching` + fuzzy %), whether `main.dol: OK` holds, any blocker worth recording, and the queue
rows you changed.

Suggest a single-line commit message for the user to use (don't commit it yourself), e.g.
`Match <FunctionName> (<unit path>)`.
