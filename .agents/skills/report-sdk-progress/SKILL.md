---
name: report-sdk-progress
description: Report how close the SDK decomp is to done, and whether the project is ready to move on to game code. Use when asked about SDK progress, what SDK work remains, or whether SDK is finished.
---

# Report SDK progress

`python configure.py progress` is **not** enough on its own. It only counts units registered in
`configure.py`, so "SDK Code 100%" just means every *registered* SDK file matches, and
"Game Code 100% (0 / 0)" means no game files are registered. Judge completion from the steps below.

## Steps

1. **Progress report.** Run `python configure.py progress` (needs a prior `ninja`).
   Note the `All` line (matched functions / total) and the SDK/Game categories.
2. **Registered vs. unmatched.** In `configure.py`, list `config.libs` entries and any
   `NonMatching` objects. Those are registered SDK units that don't match yet.
3. **Unsplit SDK functions.** Run `python .claude/skills/report-sdk-progress/sdk_remaining.py`.
   It compares `config/<version>/symbols.txt` against the `.text` ranges in `splits.txt` and
   reports functions in the SDK address range that no split covers:
   - *named* unsplit functions (e.g. `OSReport`, `GXInit`) are known SDK code still to be split;
   - anonymous `fn_XXXXXXXX` are unidentified and need library boundaries worked out.
   Add `--list` for the full anonymous list.
4. **Verify the range.** The defaults (`--lo 0x80169000 --hi 0x801B0000`) are a heuristic:
   the first split starts at `0x80169134`, named SDK symbols stop around `0x80192xxx`, and the
   upper bound is a guess. Check where named SDK symbols end (`grep -vE "^(fn|lbl)_"
   config/*/symbols.txt`) and adjust `--hi`. Anonymous functions past the last named symbol
   may be SDK, middleware, or game code; check their code before counting them.
5. **Report.** Give: matched / total functions, registered-but-`NonMatching` files, count and
   list of named unsplit SDK functions, count of anonymous functions in range, and a verdict:
   SDK is done only when no named SDK functions are unsplit, the range has no unidentified
   functions left, and no SDK object is `NonMatching`. Otherwise say what remains.

## Caveats

- Sizes come from `symbols.txt` (`size:0x..`); functions without a size count as 0 bytes.
- Only `.text` is checked. Data/rodata/bss splits are not compared.
- The script is read-only.
