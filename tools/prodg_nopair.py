#!/usr/bin/env python3

###
# Compiles a C++ unit with SN ProDG's ngccc and deletes the function-end branch pair from the assembly before assembling it.
#
# The bundled cc1plus closes every C++ function that is not a constructor with two unreachable branches to the epilogue:
#
#       b .L5          # goto no_return_label
#       b .L4          # goto return_label
#   .L5:
#   .L4:
#       <epilogue>
#
# Most of the DOL's C++ functions do not have them (see docs/nonmatching.md), and no cc1plus option drops them. Units in such files set
# `strip_fn_end_pair` in configure.py, which runs this script in place of ngccc. A `return` in the body keeps its own single branch.
#
# Usage:
#   python3 tools/prodg_nopair.py <wrapper|-> <ngccc.exe> <ngccc flags...> -MD -c in.cpp -o out.o
###

import os
import re
import subprocess
import sys

BRANCH = re.compile(r"^\s*b\s+(\.L\w+)\s*$")
LABEL = re.compile(r"^(\.L\w+):\s*$")
# Debug builds put stabs directives between the labels
SKIPPABLE = re.compile(r"^\s*\.stab[nsd]\b")


def strip_pair(lines: list[str]) -> tuple[list[str], int]:
    out: list[str] = []
    removed = 0
    i = 0
    while i < len(lines):
        first = BRANCH.match(lines[i])
        second = BRANCH.match(lines[i + 1]) if first and i + 1 < len(lines) else None
        if first and second:
            # The two targets must be the first labels after the branches, in either order, with nothing else between
            wanted = {first.group(1), second.group(1)}
            j = i + 2
            seen: set[str] = set()
            while j < len(lines):
                label = LABEL.match(lines[j])
                if label:
                    seen.add(label.group(1))
                elif not SKIPPABLE.match(lines[j]):
                    break
                j += 1
            if wanted <= seen:
                i += 2
                removed += 2
                continue
        out.append(lines[i])
        i += 1
    return out, removed


def run(cmd: list[str]) -> None:
    result = subprocess.run(cmd)
    if result.returncode != 0:
        sys.exit(result.returncode)


def main() -> None:
    wrapper, ngccc, *args = sys.argv[1:]
    prefix = [] if wrapper == "-" else [wrapper]
    cc = prefix + [ngccc]

    # ngccc's dependency file is written next to its output, so put the assembly where ninja expects the .d
    out = args[args.index("-o") + 1]
    stem = os.path.splitext(out)[0]
    asm = stem + ".s"
    src = args[args.index("-c") + 1]
    flags = [a for a in args if a not in ("-c", "-o", "-MD", out, src)]

    run(cc + flags + ["-MD", "-S", src, "-o", asm])
    with open(asm) as f:
        lines = f.read().split("\n")
    lines, removed = strip_pair(lines)
    with open(asm, "w") as f:
        f.write("\n".join(lines))
    run(cc + flags + ["-c", asm, "-o", out])
    os.remove(asm)


if __name__ == "__main__":
    main()
