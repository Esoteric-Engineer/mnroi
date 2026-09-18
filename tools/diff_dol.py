#!/usr/bin/env python3
"""Compare the built main.dol against the original and summarise the diff.

Usage (from repo root):  python3 tools/diff_dol.py

Reports overall match percent, and a per-DOL-section breakdown mapped back to virtual addresses.
Handy for confirming the baseline is still byte-perfect, and for localising a regression if it ever stops being so.
"""
import struct
import sys
from collections import Counter

ORIG = "orig/GVLE69/sys/main.dol"
BUILT = "build/GVLE69/main.dol"


def segments(dol):
    """Return [(file_off, vaddr, size, name), ...] for all non-empty DOL segments."""
    segs = []
    for i in range(7):
        off = struct.unpack(">I", dol[0x00 + i * 4:0x04 + i * 4])[0]
        addr = struct.unpack(">I", dol[0x48 + i * 4:0x4C + i * 4])[0]
        size = struct.unpack(">I", dol[0x90 + i * 4:0x94 + i * 4])[0]
        if size:
            segs.append((off, addr, size, "text%d" % i))
    for i in range(11):
        off = struct.unpack(">I", dol[0x1C + i * 4:0x20 + i * 4])[0]
        addr = struct.unpack(">I", dol[0x64 + i * 4:0x68 + i * 4])[0]
        size = struct.unpack(">I", dol[0xAC + i * 4:0xB0 + i * 4])[0]
        if size:
            segs.append((off, addr, size, "data%d" % i))
    return segs


def main():
    try:
        a = open(ORIG, "rb").read()
        b = open(BUILT, "rb").read()
    except FileNotFoundError as e:
        print("Missing file: %s (build first with `ninja`)" % e.filename)
        return 1

    print("orig size : %d" % len(a))
    print("built size: %d   (delta %+d)" % (len(b), len(b) - len(a)))
    n = min(len(a), len(b))
    diffs = [i for i in range(n) if a[i] != b[i]]
    print("differing bytes: %d of %d  (%.3f%% match)" % (
        len(diffs), n, 100 * (1 - len(diffs) / n)))
    if not diffs:
        print("\n*** BYTE-IDENTICAL over the overlap. Green baseline! ***")
        return 0

    segs = segments(a)

    def f2sec(fo):
        for off, addr, size, name in segs:
            if off <= fo < off + size:
                return name
        return "header/gap"

    # cluster into contiguous ranges
    ranges = []
    s = p = diffs[0]
    for x in diffs[1:]:
        if x == p + 1:
            p = x
        else:
            ranges.append((s, p))
            s = p = x
    ranges.append((s, p))

    by_sec = Counter()
    bytes_by_sec = Counter()
    for s, e in ranges:
        name = f2sec(s)
        by_sec[name] += 1
        bytes_by_sec[name] += e - s + 1
    print("\ndiff ranges + bytes by DOL segment:")
    for name in sorted(by_sec, key=lambda k: -bytes_by_sec[k]):
        print("  %-12s ranges=%-5d bytes=%d" % (name, by_sec[name], bytes_by_sec[name]))
    return 1


if __name__ == "__main__":
    sys.exit(main())
