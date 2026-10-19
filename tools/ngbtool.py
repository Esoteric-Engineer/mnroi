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
  +0x28 f32 length               the last key's frame (all but one of the 12,742 animations)
  +0x2C u32 track count
  +0x30 ptr tracks               -> track count * 0x10
  +0x34 u32
  +0x38 u32                      cleared by the loader
  +0x3C u32 event count
  +0x40 ptr events               -> event count * 0xC
  +0x44 u32 extra count
  +0x48 ptr extra records        -> extra count * 0x50
  +0x4C u32
  then the tracks, 0x10 each:
        u32 bone                 a node of the model's skeleton in the low halfword; the high
                                 halfword is 1-6 in 19,104 of the 708,362 tracks (meaning unknown)
        u32 channel              0 rotation, 1 translation
        u32 key count
        ptr keys
  then each track's keys in track order, 0xC each: f32 frame; s16 a, b, c, d
        channel 0: the quaternion w = a / 16384, (x, y, z) = -(c, d, b) / 16384 (worked out
                   from the data, not from code)
        channel 1: (a, b, c) / d with d unsigned (unpack__6Packed, Game/fn_80447830.cpp),
                   added to the node's offset from its parent
  then the events, 0xC each: f32 frame; u16 type; u16 param; u32 value. The handler is
        fn_800E1788 (unmatched; types in docs/characters.md section 4)
  then the extra records, 0x50 each: a 4x4 f32 matrix and three words (not understood).
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
            print("    %-32s flags %8x  length %8g  tracks %3d  keys %5d  events %3d  extra %3d" %
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
