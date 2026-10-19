#!/usr/bin/env python3
"""Print the animation bundles Bundles/<name>.ngb (docs/characters.md section 4).

Usage (from repo root):
  python3 tools/ngbtool.py list [substring]   Every animation of every bundle, with its counts
  python3 tools/ngbtool.py check              Parse every bundle to its last byte

Big-endian on disc, no file header: the reader fn_8019EBF8 loads the whole file and calls
fn_8019E7D4 until the end, which fixes the pointers of one animation in place and registers it
in lbl_8066C584 by its name. Pointer fields hold stale exporter addresses on disc. Per animation:
  +0x0  char name[0x20]          "Wolverine_Walk.nad", the registry key
  +0x20 u32 flags                0x10000 on disc; the loader ORs in 0x110000
  +0x24 u32                      set to 1 by the loader
  +0x28 f32                      16.0 in Wolverine_Walk (guess: frame rate or length)
  +0x2C u32 track count
  +0x30 ptr tracks               -> track count * 0x10
  +0x34 u32
  +0x38 u32                      cleared by the loader
  +0x3C u32 n3C
  +0x40 ptr                      -> n3C * 0xC
  +0x44 u32 n44
  +0x48 ptr                      -> n44 * 0x50
  +0x4C u32
  then the track array, each track 0x10:
        +0x0 u32, +0x4 u32, +0x8 u32 key count, +0xC ptr keys
  then each track's keys in track order, key count * 0xC each,
  then the n3C array, then the n44 array.
"""

import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nvbtool import read_big_index, read_entry  # noqa: E402

ANIM = ">32sIIfIIIIIIIII"
TRACK = ">IIII"


def parse_anim(data, off):
    """One animation at off: (name, header fields, key total, next offset)."""
    if off + 0x50 > len(data):
        raise ValueError("header at 0x%x runs past the end of the file" % off)
    h = struct.unpack_from(ANIM, data, off)
    name = h[0].split(b"\0")[0].decode("latin-1")
    tracks, n3c, n44 = h[4], h[8], h[10]
    off += 0x50
    keys = 0
    for i in range(tracks):
        keys += struct.unpack_from(TRACK, data, off + i * 0x10)[2]
    off += tracks * 0x10 + keys * 0xC + n3c * 0xC + n44 * 0x50
    if off > len(data):
        raise ValueError("%s runs past the end of the file" % name)
    return name, h, keys, off


def parse(data):
    anims = []
    off = 0
    while off < len(data):
        name, h, keys, off = parse_anim(data, off)
        anims.append((name, h, keys))
    return anims, off


def ngb_entries(index, sub=None):
    names = sorted(n for n in index if n.endswith(".ngb"))
    if sub:
        names = [n for n in names if sub.lower() in n]
    return names


def cmd_list(index, sub):
    for name in ngb_entries(index, sub):
        anims, _ = parse(read_entry(index, name))
        print("%s: %d animations" % (name, len(anims)))
        for anim, h, keys in anims:
            print("    %-32s flags %8x  +0x28 %8g  tracks %3d  keys %5d  n3C %3d  n44 %3d" %
                  (anim, h[1], h[3], h[4], keys, h[8], h[10]))


def cmd_check(index):
    ok = True
    entries = ngb_entries(index)
    total = 0
    for name in entries:
        data = read_entry(index, name)
        try:
            anims, end = parse(data)
            total += len(anims)
            if end != len(data):
                raise ValueError("parse ends at 0x%x of 0x%x" % (end, len(data)))
        except (ValueError, struct.error) as e:
            print("%-36s %s" % (name, e))
            ok = False
    print("%d animation bundles, %d animations, %s" %
          (len(entries), total, "all parsed to the last byte" if ok else "INVALID"))
    sys.exit(0 if ok else 1)


def main(argv):
    if len(argv) < 2 or argv[1] not in ("list", "check"):
        raise SystemExit(__doc__)
    index = read_big_index()
    if argv[1] == "check":
        cmd_check(index)
    cmd_list(index, argv[2] if len(argv) > 2 else None)


if __name__ == "__main__":
    main(sys.argv)
