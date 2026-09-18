#!/usr/bin/env python3
"""Print only the instructions of one function that objdiff reports as different.

Usage (from repo root, after a build):  python3 tools/objdiff_mismatches.py <unit> <function>
  e.g.  python3 tools/objdiff_mismatches.py Dolphin/dvd/dvdfs DVDConvertPathToEntrynum

Runs the bundled objdiff-cli and filters its JSON output.
left = original, right = yours.
"""
import json
import os
import subprocess
import sys
import tempfile

OBJDIFF = "build/tools/objdiff-cli"


def describe(row):
    """Format one objdiff instruction row, including its relocation type if any."""
    ins = row.get("instruction")
    if not ins:
        return "(missing)"
    text = "%5s: %s" % (ins.get("address", "0"), ins.get("formatted", ""))
    reloc = ins.get("relocation")
    if reloc:
        text += "    [%s]" % reloc.get("type_name", reloc.get("type"))
    return text


def main():
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    unit, function = sys.argv[1], sys.argv[2]
    if not unit.startswith("main/"):
        unit = "main/" + unit
    if not os.path.exists(OBJDIFF):
        sys.exit("Missing %s (build first with `ninja`)" % OBJDIFF)

    with tempfile.TemporaryDirectory() as tmp:
        out = os.path.join(tmp, "diff.json")
        subprocess.run([OBJDIFF, "diff", "-p", ".", "-u", unit, "-o", out,
                        "--format", "json-pretty", function],
                       check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        with open(out) as f:
            data = json.load(f)

    found = False
    total = 0
    for side in ("left", "right"):
        for sym in data.get(side, {}).get("symbols", []):
            if sym.get("name") != function:
                continue
            found = True
            print("== %s (%s): %s%% match, size %s ==" % (
                side, "original" if side == "left" else "yours",
                sym.get("match_percent", "?"), sym.get("size", "?")))
            for i, row in enumerate(sym.get("instructions", [])):
                if row.get("diff_kind", "DIFF_NONE") == "DIFF_NONE":
                    continue
                total += 1
                print("  #%-3d %-18s %s" % (i, row["diff_kind"], describe(row)))
    if not found:
        sys.exit("Function %s not found in %s" % (function, unit))
    if total == 0:
        print("No differing instructions.")


if __name__ == "__main__":
    main()
