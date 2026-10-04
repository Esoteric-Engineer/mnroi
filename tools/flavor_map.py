#!/usr/bin/env python3

###
# Maps which flags built each function in the original DOL (see docs/prodg.md, "Flags").
#
# Every function is classed from its prologue:
#   O0      sets up a GCC frame pointer (`mr r31,r1` in its first 24 instructions): -O0 game code
#   opt     no frame pointer: built with optimization (-O2 in every range checked)
#   alloca  optimized code that needs a frame pointer anyway, because it calls alloca (`mr r31,r1` plus `stwux`)
#   asm     uses paired-single instructions, which GCC 2.95 never emits: hand-written assembly
# and every optimized one is tagged with the evidence that separates the flag sets:
#   r13     reaches small data through r13, so it was not built with -G0
#   abs     reaches .sdata/.sbss through lis, which only a -G0 unit does
#   bdnz    has a CTR loop, which only strength reduction emits (so not -fno-strength-reduce)
#   idx     has a call-free loop that still scales its counter (`slwi` + an indexed load/store), which strength reduction removes
#
# Usage:
#   python3 tools/flavor_map.py                   Flag sets with their evidence, then the O0/opt runs
#   python3 tools/flavor_map.py 0x80246024 ...    Class, evidence and flag set of the function at each address
###

import re
import sys
from collections import Counter
from typing import Dict, List, Tuple

from pair_map import DOL, SYMBOLS, load_text

MR_R31_R1 = 0x7C3F0B78
SDA_LO, SDA_HI = 0x8066B4E0, 0x80670980  # .sdata, .sbss, .sdata2
INDEXED = {23, 151, 535, 663, 279, 343, 407, 87, 215, 599, 727}  # lwzx stwx lfsx stfsx lhzx lhax sthx lbzx stbx lfdx stfdx

# The flag sets found so far. A range's ends are only as exact as the evidence: the edge between two flag sets
# lies somewhere between the last function tagged for one and the first tagged for the other.
FLAG_SETS: List[Tuple[int, int, str, str]] = [
    (0x800034A0, 0x80168768, "-O0", "game code"),
    (0x80196884, 0x8023D994, "-O0", "game code"),
    (0x8023D994, 0x80243F94, "-O2", "RealCore 6.27 (file system, DVD, threads)"),
    (0x80243F94, 0x8026D828, "-O2 -fno-strength-reduce -G0", "CSIS allocator, audio, Apt runtime core"),
    (0x8026D828, 0x803864CC, "-O2", "Apt, memory card, EAGL/RealGraph, AV/MAD video, Refpack, Havok"),
    (0x803864CC, 0x803FF3B0, "-O0", "game code"),
    (0x804114EC, 0x80426A2C, "-O2", "RealCore wrappers, Havok shapes, GX display lists"),
    (0x80426A2C, 0x80472F34, "-O0", "game code"),
    (0x80472F34, 0x8047EED8, "-O2", "Havok"),
    (0x8047EED8, 0x80480020, "-O0", "game code"),
]


def sign16(v: int) -> int:
    return v - 0x10000 if v & 0x8000 else v


def classify(segs, symbols_path: str) -> List[Tuple[int, int, str, Counter]]:
    def word(va: int) -> int:
        for addr, size, data in segs:
            if addr <= va < addr + size:
                return int.from_bytes(data[va - addr : va - addr + 4], "big")
        raise KeyError(hex(va))

    pattern = re.compile(r"^\S+ = \.text:0x([0-9A-Fa-f]+); // type:function size:0x([0-9A-Fa-f]+)")
    funcs = []
    for line in open(symbols_path):
        m = pattern.match(line)
        if m:
            funcs.append((int(m.group(1), 16), int(m.group(2), 16)))
    out = []
    for addr, size in sorted(funcs):
        if not 0x800034A0 <= addr < 0x80480020:
            continue
        ws = [word(addr + 4 * i) for i in range(size // 4)]
        ops = [w >> 26 for w in ws]
        ev: Counter = Counter()
        if any(op in (4, 56, 57, 60, 61) for op in ops):
            cls = "asm"
        elif MR_R31_R1 in ws[:24]:
            cls = "alloca" if any(op == 31 and (w >> 1) & 0x3FF == 183 for op, w in zip(ops, ws)) else "O0"
        else:
            cls = "opt"
        if cls != "O0":
            hi: Dict[int, int] = {}
            for op, w in zip(ops, ws):
                rd, ra = (w >> 21) & 31, (w >> 16) & 31
                if op == 15 and ra == 0:
                    hi[rd] = (w & 0xFFFF) << 16
                elif op == 14 or 32 <= op <= 55:
                    if ra == 13:
                        ev["r13"] += 1
                    elif ra in hi and SDA_LO <= (hi[ra] + sign16(w & 0xFFFF)) & 0xFFFFFFFF < SDA_HI:
                        ev["abs"] += 1
            for i, (op, w) in enumerate(zip(ops, ws)):
                if op == 16 and not w & 2:
                    start = i + sign16(w & 0xFFFC) // 4
                elif op == 18 and not w & 3:
                    d = w & 0x03FFFFFC
                    start = i + (d - 0x04000000 if d & 0x02000000 else d) // 4
                else:
                    continue
                if not 0 <= start <= i:
                    continue
                loop = list(zip(ops[start : i + 1], ws[start : i + 1]))
                if op == 16 and ((w >> 21) & 0x14) == 0x10:
                    ev["bdnz"] += 1
                    continue
                if any((o == 18 and x & 1) or (o == 19 and x & 1) for o, x in loop):
                    continue
                counters = {(x >> 21) & 31 for o, x in loop if o == 14 and (x >> 21) & 31 == (x >> 16) & 31 and x & 0xFFFF == 1}
                scaled = set()
                for o, x in loop:
                    sh, mb, me = (x >> 11) & 31, (x >> 6) & 31, (x >> 1) & 31
                    if o == 21 and (x >> 21) & 31 in counters and 1 <= sh <= 4 and mb == 0 and me == 31 - sh:
                        scaled.add((x >> 16) & 31)
                    elif o == 7 and (x >> 16) & 31 in counters:
                        scaled.add((x >> 21) & 31)
                if any(o == 31 and (x >> 1) & 0x3FF in INDEXED and {(x >> 16) & 31, (x >> 11) & 31} & scaled for o, x in loop):
                    ev["idx"] += 1
        out.append((addr, size, cls, ev))
    return out


def flag_set(va: int):
    return next((f for f in FLAG_SETS if f[0] <= va < f[1]), None)


def runs_of(funcs):
    runs = []
    for addr, size, cls, ev in funcs:
        c = "O0" if cls == "O0" else "opt"
        if runs and (runs[-1][0] == c or cls in ("alloca", "asm")):
            runs[-1][2] = addr + size
            runs[-1][3] += 1
        else:
            runs.append([c, addr, addr + size, 1])
    return runs


def tags(ev: Counter) -> str:
    return " ".join(f"{k}={ev[k]}" for k in ("r13", "abs", "bdnz", "idx") if ev[k]) or "no evidence"


def main() -> None:
    funcs = classify(load_text(DOL), SYMBOLS)
    if len(sys.argv) > 1:
        for arg in sys.argv[1:]:
            va = int(arg, 16)
            f = next((f for f in funcs if f[0] <= va < f[0] + f[1]), None)
            if f is None:
                print(f"0x{va:08X}: not in a game-range function")
                continue
            fs = flag_set(f[0])
            where = f"{fs[2]} ({fs[3]}, 0x{fs[0]:08X}-0x{fs[1]:08X})" if fs else "library cluster, not ProDG game flags"
            print(f"0x{va:08X}: function 0x{f[0]:08X} is {f[2]}, {tags(f[3])}; range flags {where}")
        return
    print("Flag sets (functions; then evidence summed over the range's optimized functions):")
    for lo, hi, flags, what in FLAG_SETS:
        inside = [f for f in funcs if lo <= f[0] < hi]
        cls = Counter(f[2] for f in inside)
        fns = Counter()
        for f in inside:
            for k in f[3]:
                fns[k] += 1
        print(f"  0x{lo:08X}-0x{hi:08X} {flags:30s} {sum(cls.values()):5d} fns {dict(cls)}  "
              f"fns with r13={fns['r13']} abs={fns['abs']} bdnz={fns['bdnz']} idx={fns['idx']}  {what}")
    runs = runs_of(funcs)
    print(f"\n{len(runs)} runs of O0 / opt code:")
    for c, lo, hi, n in runs:
        print(f"{c:3s} 0x{lo:08X}-0x{hi:08X} {n}")


if __name__ == "__main__":
    main()
