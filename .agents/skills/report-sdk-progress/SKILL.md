---
name: report-sdk-progress
description: Report how close the SDK decomp is to done, and whether the project is ready to move on to game code. Use when asked about SDK progress, what SDK work remains, or whether SDK is finished.
---

# Report SDK progress

`python3 configure.py progress` is **not** enough on its own. It only counts units registered in
`configure.py`, so "SDK Code 100%" just means every *registered* SDK file matches, and
"Game Code 100% (0 / 0)" means no game files are registered. Its SDK percentage leaves out all
unsplit library code, which can be a third of the total. Judge completion from the steps below.

"Library code" here means everything that isn't game code: the Dolphin SDK, Newlib libc/libm, the
compiler runtime and the SN Systems ProDG debug stub (see `docs/sdk_libraries.md`).

## Steps

1. **Build and progress report.** Run `ninja`, then `python3 configure.py progress`. Note the SDK
   Code and Data lines. The script in step 2 reads `build/GVLE69/report.json` from this build.
2. **Remaining work.** Run `python3 .agents/skills/report-sdk-progress/sdk_remaining.py` (add
   `--list` for every gap and every anonymous function). It takes its ranges and library labels from
   `tools/sdk_scout.py` (`RANGES`, `LIBS`) and reports:
   - unsplit `.text` in both library clusters **by address**, per cluster and per library. This
     includes code that has only `lbl_` symbols, which a function count would miss;
   - *label-only runs*: code with no `type:function` symbol. It needs function boundaries in
     `symbols.txt` before it can be split;
   - named unsplit functions and named labels (e.g. `__cvt_fp2unsigned`);
   - unsplit `.init` (`__start` and its helpers);
   - library data **by run**: every run in `DATA_RANGES` (`tools/sdk_scout.py`; both clusters, every
     data section, mapped in "Library data runs" in `docs/sdk_libraries.md`) with its split and
     unsplit bytes. Unsplit bytes are *queued* (covered by an `open`/`stalled` data row), *padding*
     (no symbol covers them: alignment gaps the linker inserts, never queued) or *not queued*
     (library data with no row, printed as `NOT QUEUED`). Queued bytes are also summed per library
     from the rows. A library unit's data split outside every run is printed too, since it means a
     run is mis-mapped;
   - the whole-library code and data percentages (the correct denominator for "how far along");
   - every registered library unit that doesn't fully match, code **or** data, from `report.json`.
     Cross-check against the `NonMatching` objects in `configure.py`.
3. **Work queue.** Summarize `docs/sdk_queue.tsv` by status, confidence and library, e.g.
   `tail -n+2 docs/sdk_queue.tsv | cut -f4,5,7 | sort | uniq -c`. Report the counts of
   `open`/`matched`/`stalled`/`wrong-name`/`not-sdk`, how many `open` rows are `unidentified`, and how
   many are `libc` or `sn`. Hand-added rows cover label-only regions, `.init` (library `init`) and a
   `stalled` row per registered `NonMatching` function (see "Work queue" in `docs/sdk_libraries.md`).
   Data rows (`notes` start with `data <section>:`, one per owning unit per section) are counted
   apart: `grep -P '\tdata \.' docs/sdk_queue.tsv | cut -f4,5,7 | sort | uniq -c`.
   If the queue looks stale (e.g. a function unsplit in step 2 has no row), run
   `python3 tools/sdk_scout.py queue` before trusting it. It keeps hand-added rows and statuses.
   It never touches data rows; `NOT QUEUED` data in step 2 needs rows added by hand.
4. **Boundaries.** `docs/sdk_libraries.md` records every library range: the first cluster
   0x80168770-0x80196884 (SN stub, runtime, libc, OS, ... OdemuExi2) and the second cluster
   0x803FF3B0-0x804114EC (libm/libc, VM, OS, MTX, AR, ARQ, AX, DSP, CARD, GX display lists,
   texPalette). Use it instead of re-deriving bounds, and update it (and `LIBS` in
   `tools/sdk_scout.py`) if you learn something. Code outside those ranges is game or middleware;
   check its code before counting it.
5. **Report.** Give:
   - the progress-report SDK percentage **and** the whole-library percentage from step 2, and say
     which is which;
   - registered units not fully matched (count and list, code vs data);
   - unsplit `.text` bytes per library, the label-only runs, named unsplit symbols, anonymous count;
   - unsplit `.init`;
   - library data: split vs unsplit bytes per run and in total, queued bytes per library, padding,
     and any `NOT QUEUED` bytes or splits outside a run;
   - the queue summary, with the data rows (`notes` starting `data <section>:`) counted separately;
   - a verdict.

## Verdict

The SDK decomp is done only when **all** of these hold. It covers the Dolphin SDK, libc, the
runtime, `.init` and the SN debug stub (in scope since 2026-09-24):

- no registered library unit is below 100% code or data, and no SDK object is `NonMatching`;
- no unsplit `.text` bytes remain in the SDK libraries of either cluster, **including label-only
  runs**. Judge by bytes, not by function count;
- `.init` is split and matched;
- the queue has no `open` or `stalled` rows, at any confidence and in any library (`sn` included).
  `unidentified` rows are unfinished work too. If you deliberately defer some, say which and why;
- AR, ARQ, AX, DSP and CARD are registered or deliberately excluded;
- data: every run in `DATA_RANGES` is split, i.e. its only unsplit bytes are padding, nothing is
  `NOT QUEUED`, and no library split lies outside a run. The runs must cover both clusters in every
  data section, as "Library data runs" in `docs/sdk_libraries.md` records.

Only then is the project ready to move on to game code. Otherwise, say what remains.

## Caveats

- Library ranges are approximate to the function; `LIBS` in `tools/sdk_scout.py` is the source.
- The data figures are only as good as the runs in `DATA_RANGES`. They were mapped from relocations and
  `r13` loads, but a few run edges next to game data rest on position (noted in `docs/sdk_libraries.md`).
  Linker-built tables are outside every run and never counted: the GCC constructor list (all of
  `.rodata`) and the empty `.ctors`/`.dtors` lists at `.data` 0x804DCD84.
- The per-library data split follows the queue rows' `library`, i.e. `LIBS`. Where `LIBS` is wrong
  (0x8017A5CC-0x8017A800 is GCC's C++ runtime and SN syscall stubs, labelled `os`), so is the split.
- "Matched" means byte-identical, not decompiled to C. Many units (most of `Runtime.PPCEABI.H`)
  are `nofralloc` asm transcriptions. That doesn't block the verdict, but mention it if asked about
  "decompiled".
- The script is read-only.
