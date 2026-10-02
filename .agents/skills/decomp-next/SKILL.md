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
   (already named in `symbols.txt`, or an `fn_` row whose note says no reference names it: `sn`, some `init`,
   the second `floor`; keep the `fn_` name for the unit and symbol), `exact` (size matches the reference), then `guess`, and within a
   tier the smallest size. Skip `unidentified` rows (they need scouting, not matching) and anything listed in
   `docs/nonmatching.md`. Library ranges are in `docs/sdk_libraries.md`. If the user named a specific function or unit instead, work that one.
   `tools/find_candidates.py` (small leaf functions only) is a fallback, not the main chooser.
   `python3 tools/sdk_scout.py info <addr>` shows a function's callees, callers and hardware
   registers, which helps confirm an identity.
   - **Data rows** (`notes` start with `data <section>:`) come after every function row. Group the
     `open` data rows by `name`. Rank each group by its weakest row (`known` before `guess`), then by
     total size, smallest first. Work the whole group as one run of "Data rows" below instead of steps 2-6.
   - **Out of queue:** if no `open` function or data row of tier `known`/`exact`/`guess` is left, stop. Tell the
     user the queue is exhausted (counts by status/library, what remains) and that the next step is
     a planning session (add function boundaries to the label-only regions, scout the `unidentified`
     rows, review the `stalled` data rows and any `NOT QUEUED` data that
     `.agents/skills/report-sdk-progress/sdk_remaining.py` prints, then decide on game code).
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
   - `runtime` and `init` rows (`__cvt_fp2unsigned`, `__save_gpr`, `__start` and the other `.init`
     code): compiler runtime and boot code. Search ac-decomp by name. A row whose symbol is only a
     label (see its note) needs a `type:function` symbol with a size in `symbols.txt` first.
   - `sn` rows: SN Systems' ProDG debug stub. It isn't Dolphin SDK, but it is part of the SDK decomp.
     No public source is known, so work from the disassembly and what `docs/sdk_libraries.md`
     records. Much of it is hand-written asm (`mtsprg`, `psq_st`, SPR saves); transcribe that as
     `nofralloc` asm, like the existing `SN/` units.
   If the reference clone is missing (`../ac-decomp`; `../newlib-cygwin` for libc), say so rather than
   skipping this step silently.
   **Verify the name.** Queue names for `exact`/`guess` rows come from size and order only. Confirm
   in the reference that the code shape and callees agree before renaming. If it doesn't, don't force it:
   set the row's `status` to `wrong-name` and note what it looks like instead.
3. **Claim.** Compute `end = start + size` from `config/GVLE69/symbols.txt`. In one edit: add
   the range to `splits.txt` (tab-indented), and rename `fn_XXXXXXXX` to the real name in
   `symbols.txt`. For an `init` row the split line is `.init start:... end:...`, not `.text`.
4. **Register** as `Object(NonMatching, "<unit>")` in `configure.py`. The name must equal the
   `splits.txt` unit name exactly. Where each library's units go:
   - `runtime`: the `Runtime.PPCEABI.H` library (`cflags_runtime`), unit `Runtime.PPCEABI.H/<name>.c`.
   - `init`: the library ac-decomp uses for the same function. `__start`, `__init_registers` and
     `__init_data` go in `os`; `__init_hardware` and `__flush_cache` also go in `os`
     (`__ppc_eabi_init` there); `memset`, `__fill_mem` and `memcpy` go in `Runtime.PPCEABI.H`
     (`__mem.c` there). Identify each `fn_` helper by size and code shape against those first.
     Keep one unit per function, named after it.
   - `sn`: the `SN` library entry, unit `SN/<name>.c` (`GC/1.2.5n`, `cflags_base`).
   - **New library** (e.g. `pad`, not registered yet): add a `DolphinLib("pad", [Object(...)])`
     entry to `config.libs`, in link order (address order: `pad` goes after `vi` and before `ai`),
     with units named `Dolphin/pad/<unit>.c` in both `splits.txt` and `src/`. `DolphinLib` supplies
     `GC/1.2.5n` and `cflags_base`. The SDK libraries were built at different dates (PAD Aug 2003,
     DVD Sep 2003, the rest Apr 2003), so if the first function matches poorly in an
     unexplained, uniform way, suspect the flags or compiler version before the source. If you
     confirm a flag/version difference, record it per "Recording notes" below.
5. **Write** `src/<unit>` and run `ninja`. Inspect remaining differences with
   `python3 tools/objdiff_mismatches.py <unit-without-.c> <function>`; it shows relocation
   types, which byte diffs don't. Form a hypothesis from `docs/matching_notes.md` instead of
   random reshaping; switch to asm transliteration for control-flow-sensitive functions.
6. **Verify.** Flip to `Matching`, run `ninja`, and require **both** `main.dol: OK` and 100%
   linked. Flipping a unit relinks, so `CHECK` does run here and the `OK` line should appear; if
   it somehow doesn't, use the Preconditions criteria rather than assuming a break. If `main.dol` breaks, run `python3 tools/diff_dol.py` to locate the bytes; consider
   `force_active` only if the diff shows the function was dropped/shifted.

## Data rows

A data row moves an unsplit data range into the unit named in `name`, which then defines that data
byte-for-byte. A mistake shifts everything after it in `main.dol`, so do one unit per run. Read "Data,
symbols, and relocations" in `docs/matching_notes.md` first; it has the alignment, padding,
`force_active` and pool-order rules. The row's note flags the ones it expects, and gives dtk's symbols
and the SDK/CFTKK names.

1. **Claim** every `open` row with the same `name` together. Add each range to that unit in
   `splits.txt`, in the section order the header lists (`.text`, `.rodata`, `.data`, `.bss`,
   `.sdata`, `.sbss`, `.sdata2`). If the range starts where the unit's existing line of that section
   ends, extend that line instead. For a new data-only unit, add a `splits.txt` entry without `.text`,
   register it next to its neighbours in `configure.py`, and create the source file.
2. **Symbols.** Where a reference gives a name (the note's SDK/CFTKK name), rename dtk's `lbl_` symbol
   in `symbols.txt`. Split or shrink merged blobs where the note says to. Keep `scope:global` on
   anything another unit still reads.
3. **Define** the data in the unit's source instead of declaring it `extern`: byte-exact initializers,
   declaration order as in the original, and the SDK's alignment attributes. Then update the other
   units' `extern`s to the new names.
4. **Verify** with `ninja`: `main.dol: OK`, and the unit at 100% data in `build/GVLE69/report.json`
   (`main/<unit without .c>`: `measures.matched_data_percent`, per-section `sections[]`). If `main.dol`
   breaks, `python3 tools/diff_dol.py` shows where.
5. **Queue.** Mark the rows `matched`, or `stalled` with the blocker in the note (for example "needs a
   TU merge" when the owner can't define the data without its sibling units). An existing unit keeps
   its `Matching`/`NonMatching` status. A new data-only unit starts `NonMatching` and flips to `Matching`
   once its data is at 100%.
6. **Commit message** to suggest, naming the sections claimed: `Split .bss/.sbss data into <unit path>`,
   or `Split .data into <unit path>` for one section.

## Rules

- Leave the unit `NonMatching` if it isn't at 100%. Never flip a partial match.
- On a function row, prefer referencing existing (unclaimed) dtk symbols over declaring fresh data or
  claiming data ranges; override `scope:local` → `scope:global` in `symbols.txt` when needed. Data is
  claimed through data rows.
- Don't `git add -f` anything ignored, and don't commit unless asked.
- Record what you learn per "Recording notes" below. Notes never go in this skill.

## Recording notes

Two files, two jobs. Decide which one (or neither) before writing anything.

**`docs/matching_notes.md` is a lookup table of reusable rules for a future agent stuck on a
*different* function.** It is read in full before every function, so every line costs every future
session. Add an entry only if **all** of these hold:

- **Reusable:** it is a compiler/linker/dtk/objdiff behaviour or source-shape rule likely to apply
  to other functions, not a fact about this one function. Ask: "would this change what I'd try on
  some other function?" If not, don't add it.
- **Actionable:** it states a symptom the reader can recognise in a diff (an instruction pattern,
  a frame-size gap, a `main.dol` shift, a link error) and the fix to apply.
- **Verified:** the fix actually reached 100% / `main.dol: OK` (or the claim was measured in a
  scratch TU). No hypotheses, no "might be".

Write it as one bullet, in this shape: **bold symptom or rule**, then 1-3 sentences: cause, fix,
and at most one example function (`Name`, address). Add a code block only when the exact source
form is the whole point. Update the existing entry instead of appending a near-duplicate: `grep` the
file for the symptom, the pragma, or the function's neighbours first. If a note turns out wrong or
superseded, fix or delete it.

Do **not** put any of these in `matching_notes.md`:

- What you did or how it went: attempt counts, "tried N variants", percentage progressions
  ("68% -> 100%"), what broke along the way, "first try", "now matched", session or date narrative.
- A per-function write-up: what the function does, its full source shape, or every register and
  offset in it. The source in `src/` and git history are that record. Only the part that
  generalises belongs, as the example under a rule.
- Failed approaches. A dead end that is a *common trap* (an agent would naturally try it and lose
  an hour) may be one short "doesn't help:" clause on the relevant rule. Everything else goes in
  `nonmatching.md`, and only if the function is still unmatched.
- Anything for a function that is still `NonMatching`. That is `nonmatching.md`.
- Queue status, SDK identity or library-boundary findings (`docs/sdk_queue.tsv`,
  `docs/sdk_libraries.md`), or how the tools/build work (`docs/workflow.md`, `docs/baseline.md`).
- Praise for a technique, opinions, or reference-decomp trivia that doesn't change what you'd write.

If you are unsure whether something qualifies, leave it out and mention it in your report instead.
Two lines that a future agent will act on beat ten paragraphs it has to skim.

**`docs/nonmatching.md`** takes the per-function detail: for a unit you leave `NonMatching`, its
fuzzy %, what is left, and what you tried (so nobody repeats it). Longer entries are fine there. When
a unit later flips to `Matching`, delete its entry and move only the general lesson, if any, to
`matching_notes.md` under the rules above.

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
`Match <FunctionName> (<unit path>)`. Always put it alone in a fenced code block (no
surrounding text or inline backticks) so the terminal offers a copy button:

````
```
Match <FunctionName> (<unit path>)
```
````
