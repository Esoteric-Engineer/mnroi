#!/usr/bin/env python3

###
# Maps which functions in the original DOL carry the C++ function-end branch pair (see docs/nonmatching.md).
#
# Every GCC-built function is classed from its epilogue:
#   A  carries the pair: two or more branches to the epilogue (the pair, plus one per trailing `return`). A C function almost never
#      has this shape, so it is taken as C++.
#   B  a method (`this` kept in r30) with no branch at all, so it is neither a constructor nor C
# Anything with exactly one trailing branch is a constructor, a destructor, a return, or C, and the same with and without the pair,
# so it is not classed, and neither are free functions without a branch. Runs of the same class are printed in address order.
#
# Usage:
#   python3 tools/pair_map.py                   Summary and every run
#   python3 tools/pair_map.py 0x80103BAC ...    Which class is at, and around, each address
###

import re
import struct
import sys
from collections import Counter
from typing import List, Tuple

DOL = "orig/GVLE69/sys/main.dol"
SYMBOLS = "config/GVLE69/symbols.txt"

MR_R31_R1 = 0x7C3F0B78
MR_R30_R3 = 0x7C7E1B78
LWZ_R11_0_R1 = 0x81610000
BLR = 0x4E800020


def load_text(path: str) -> List[Tuple[int, int, bytes]]:
    dol = open(path, "rb").read()
    segs = []
    for i in range(7):
        off, addr, size = (struct.unpack(">I", dol[b + i * 4 : b + i * 4 + 4])[0] for b in (0, 0x48, 0x90))
        if size:
            segs.append((addr, size, dol[off : off + size]))
    return segs


def classify(segs, symbols_path: str) -> List[Tuple[int, int, str]]:
    def word(va: int) -> int:
        for addr, size, data in segs:
            if addr <= va < addr + size:
                return struct.unpack_from(">I", data, va - addr)[0]
        raise KeyError(hex(va))

    def target(va: int):
        w = word(va)
        if w >> 26 != 18 or w & 3:
            return None
        d = w & 0x03FFFFFC
        return va + (d - 0x04000000 if d & 0x02000000 else d)

    pattern = re.compile(r"^\S+ = \.text:0x([0-9A-Fa-f]+); // type:function size:0x([0-9A-Fa-f]+)")
    funcs = []
    for line in open(symbols_path):
        m = pattern.match(line)
        if m:
            funcs.append((int(m.group(1), 16), int(m.group(2), 16)))
    out = []
    for addr, size in sorted(funcs):
        end = addr + size
        if size < 16 or word(end - 4) != BLR:
            continue
        head = [word(addr + 4 * i) for i in range(min(24, size // 4))]
        if MR_R31_R1 not in head:
            continue
        is_method = MR_R30_R3 in head[:16]
        epi = next((va for va in range(end - 8, max(addr, end - 192), -4) if word(va) == LWZ_R11_0_R1), None)
        if epi is None:
            continue
        branches = 0
        va = epi - 4
        while va >= addr and target(va) == epi:
            branches += 1
            va -= 4
        if branches >= 2:
            out.append((addr, size, "A"))
        elif branches == 0 and is_method:
            out.append((addr, size, "B"))
    return out


def runs_of(funcs):
    runs = []
    for addr, size, cls in funcs:
        if runs and runs[-1][0] == cls:
            runs[-1][2] = addr + size
            runs[-1][3] += 1
        else:
            runs.append([cls, addr, addr + size, 1])
    return runs


def main() -> None:
    funcs = classify(load_text(DOL), SYMBOLS)
    runs = runs_of(funcs)
    if len(sys.argv) > 1:
        for arg in sys.argv[1:]:
            va = int(arg, 16)
            for i, (cls, lo, hi, n) in enumerate(runs):
                if lo <= va < hi:
                    print(f"0x{va:08X}: inside run {cls} 0x{lo:08X}-0x{hi:08X} ({n} methods)")
                    break
                if va < lo:
                    before = runs[i - 1] if i else None
                    b = f"{before[0]} ending 0x{before[2]:08X}" if before else "nothing"
                    print(f"0x{va:08X}: between runs, {b} and {cls} starting 0x{lo:08X}")
                    break
        return
    print(Counter(c for _, _, c in funcs), f"- {len(runs)} runs")
    for cls, lo, hi, n in runs:
        print(f"{cls} 0x{lo:08X}-0x{hi:08X} {n}")


if __name__ == "__main__":
    main()
