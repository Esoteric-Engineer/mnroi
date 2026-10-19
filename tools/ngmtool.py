#!/usr/bin/env python3
"""Print the headers of the model bundles Bundles/<name>.ngm (docs/characters.md section 4).

Usage (from repo root):
  python3 tools/ngmtool.py list [substring]   Header and first model record of every bundle
  python3 tools/ngmtool.py check              Check every bundle's header against the reader

Only the header and the first record's prefix are known: the model body that follows each prefix
is read by fn_80221C08, not yet matched, so `check` cannot reach a bundle's last byte yet.

Big-endian on disc (the reader fn_801A2108 does no byte swap):
  +0x0  u32 version              5; the reader rejects any other value
  +0x4  u32                      read and ignored; 0 in character bundles, hash-like in levels
  +0x8  u32                      read and ignored; likewise
  +0xC  u32 model count          bundle +0x28
  +0x10 u32 entry count          bundle +0x30; allocates entry count * 8 bytes at bundle +0x2C
  +0x14 u32 data size            bundle +0x24; 0 loads no model
  then per model:
        s32 index                -1, or passed to fn_801A27D4 with the model
        u8  a, b, c              passed to fn_801A3ECC as (b, c, a)
        u16 d                    fn_801A3ECC's last argument
        the model body (fn_80221C08)
"""

import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nvbtool import read_big_index, read_entry  # noqa: E402

HEADER = ">6I"
RECORD = ">iBBBH"


def parse(data):
    head = struct.unpack_from(HEADER, data, 0)
    rec = None
    if head[3]:
        rec = struct.unpack_from(RECORD, data, struct.calcsize(HEADER))
    return head, rec


def ngm_entries(index, sub=None):
    names = sorted(n for n in index if n.endswith(".ngm"))
    if sub:
        names = [n for n in names if sub.lower() in n]
    return names


def cmd_list(index, sub):
    print("%-36s %3s %8s %8s %6s %7s %8s  %s" % ("bundle", "ver", "+0x4", "+0x8", "models",
                                                 "entries", "data", "first record"))
    for name in ngm_entries(index, sub):
        head, rec = parse(read_entry(index, name))
        print("%-36s %3d %8x %8x %6d %7d %8x  %s" % (name, head[0], head[1], head[2], head[3],
                                                     head[4], head[5], rec if rec else "-"))


def cmd_check(index):
    ok = True
    entries = ngm_entries(index)
    for name in entries:
        data = read_entry(index, name)
        head, _ = parse(data)
        bad = []
        if head[0] != 5:
            bad.append("version %d" % head[0])
        if head[3] and not head[5]:
            bad.append("models but no data size")
        if bad:
            print("%-36s %s" % (name, ", ".join(bad)))
            ok = False
    print("%d model bundles, headers %s" % (len(entries), "valid" if ok else "INVALID"))
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
