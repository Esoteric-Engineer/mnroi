---
name: report-sdk-progress
description: Report how close the SDK decomp is to done, and whether the project is ready to move on to game code. Use when asked about SDK progress, what SDK work remains, or whether SDK is finished.
---

# Report SDK progress

`python3 configure.py progress` is **not** enough on its own. It only counts units registered in
`configure.py`, so "SDK Code 100%" just means every *registered* SDK file matches, and
"Game Code 100% (0 / 0)" means no game files are registered. Judge completion from the steps below.

## Steps

1. **Progress report.** Run `python3 configure.py progress` (needs a prior `ninja`).
   Note the `All` line (matched functions / total) and the SDK/Game categories.
2. **Registered vs. unmatched.** In `configure.py`, list `config.libs` entries and any
   `NonMatching` objects. Those are registered SDK units that don't match yet.
3. **Unsplit SDK functions.** Run `python3 .agents/skills/report-sdk-progress/sdk_remaining.py`.
   It compares `config/<version>/symbols.txt` against the `.text` ranges in `splits.txt` and
   reports functions in the SDK address range that no split covers:
   - *named* unsplit functions (e.g. `OSReport`, `GXInit`) are known SDK code still to be split;
   - anonymous `fn_XXXXXXXX` are unidentified and need library boundaries worked out.
   Add `--list` for the full anonymous list.
4. **Work queue.** Summarize `docs/sdk_queue.tsv` by status and by confidence tier (columns
   `confidence`, `status`; e.g. `cut -f4,5,7 docs/sdk_queue.tsv | sort | uniq -c`). Report how many
   rows are `open`/`matched`/`stalled`/`wrong-name`, and how many `open` rows are still
   `unidentified` (they need scouting), and how many are `libc` (Newlib, see `docs/sdk_libraries.md`). If the queue looks
   stale (its unsplit count differs a lot from step 3), run `python3 tools/sdk_scout.py queue`
   (it keeps curated rows and statuses) before trusting it.
5. **Verify the range.** The script's default upper bound (`--hi 0x80196884`) is the end of the
   first cluster of confirmed SDK code (0x80169000-0x80196884), not the end of the SDK: everything
   from 0x80196884 to 0x80197000 is game code. `docs/sdk_libraries.md` records the library
   boundaries, including a second, unconfirmed SDK cluster (AR, ARQ, AX, DSP, CARD around
   0x804048CC-0x80410C48) that this script does not scan. Use that doc instead of re-deriving the
   bound, and update it if you learn something. Anonymous functions outside the range may be SDK,
   middleware or game code; check their code before counting them.
6. **Report.** Give: matched / total functions, registered-but-`NonMatching` files (count and
   list), count and list of named unsplit SDK functions, count of anonymous functions in range, the
   queue summary, and a verdict. SDK is done only when **all** of these hold:
   - no named SDK functions are unsplit and no SDK object is `NonMatching`;
   - the queue has no `open` rows of tier known/exact/guess (libc included; if you deliberately defer the
     unidentified libc rows, say so);
   - AR, ARQ, AX, DSP and CARD are located and either registered or deliberately excluded;
   - no unidentified functions remain in the confirmed range;
   - SDK data is complete: the progress report's `SDK Code` **Data** line is 100%, and any SDK data
     not yet split is accounted for. Only `.text` is checked by `sdk_remaining.py`, so report the
     data percentage and unmatched data bytes from step 1 explicitly.
   Otherwise say what remains.

## Caveats

- Sizes come from `symbols.txt` (`size:0x..`); functions without a size count as 0 bytes.
- Only `.text` is checked. Data/rodata/bss splits are not compared.
- The script is read-only.
