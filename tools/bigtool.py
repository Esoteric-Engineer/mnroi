#!/usr/bin/env python3
"""List, extract and repack the game's CLASH.BIG archive and its CLASH.BH index.

Usage (from repo root):
  python3 tools/bigtool.py list [substring]
  python3 tools/bigtool.py get NAME OUT_FILE
  python3 tools/bigtool.py repack OUT_BIG OUT_BH [--set NAME=FILE ...] [--add NAME=FILE ...]

`repack` with no changes reproduces both original files byte for byte. It never writes under orig/.

CLASH.BIG:  "BIG4", u32 LE total size, u32 BE entry count, u32 BE index size, then per entry
            {u32 BE offset, u32 BE size, NUL-terminated name}, then an 8-byte "L272" tag. The
            padding after the index holds "Buy ERTS" (not counted in the index size). File data
            is aligned to 0x20 and stored in index order.
CLASH.BH:   "Viv4", u32 LE size of the .BH, u32 BE entry count, u32 BE size of the .BH again,
            then 16 bytes per entry in .BIG order {u32 BE offset, u32 BE size, u32 BE unpacked
            size, u32 BE name hash}, then a 16-byte terminator {u32 BE total .BIG size, 0, 0, 0}.
            The unpacked size is 0 for a stored entry and the RefPack output size for a
            compressed one (data starts 10 FB; only the nested .big UI archives are compressed).
            The hash is djb2 (h = 5381; h = h * 33 + c) over the lowercased path.
"""
import struct
import sys

BIG = "orig/GVLE69/files/CLASH.BIG"
BH = "orig/GVLE69/files/CLASH.BH"
ALIGN = 0x20


class Entry:
    def __init__(self, offset, size, name):
        self.offset, self.size, self.name = offset, size, name
        self.hash = name_hash(name)
        self.usize = 0    # .BH unpacked size
        self.data = None  # replacement contents, or None to copy from the original


def name_hash(name):
    h = 5381
    for c in name.lower().encode("latin-1"):
        h = (h * 33 + c) & 0xFFFFFFFF
    return h


def unpacked_size(data):
    """RefPack header 10 FB + 24-bit BE unpacked size; 0 for stored data."""
    if len(data) >= 5 and data[0] == 0x10 and data[1] == 0xFB:
        return int.from_bytes(data[2:5], "big")
    return 0


def read_big_index(path=BIG):
    """Return (entries, tail, slack): the index, the tag after it, and the non-zero padding before the first file."""
    with open(path, "rb") as f:
        head = f.read(16)
        if head[:4] != b"BIG4":
            raise SystemExit("not a BIG4 archive: %r" % head[:4])
        count, index_size = struct.unpack(">II", head[8:16])
        rest = f.read(index_size - 16)
        slack = f.read(0x40)
    entries, p = [], 0
    for _ in range(count):
        off, size = struct.unpack_from(">II", rest, p)
        end = rest.index(b"\0", p + 8)
        entries.append(Entry(off, size, rest[p + 8:end].decode("latin-1")))
        p = end + 1
    if entries:
        slack = slack[:max(0, entries[0].offset - index_size)].rstrip(b"\0")
    return entries, rest[p:], slack


def read_bh(path=BH):
    """Return the .BH rows as (offset, size, unpacked size, hash)."""
    d = open(path, "rb").read()
    if d[:4] != b"Viv4":
        raise SystemExit("not a Viv4 index: %r" % d[:4])
    count = struct.unpack_from(">I", d, 8)[0]
    return [struct.unpack_from(">IIII", d, 16 + 16 * i) for i in range(count)]


def find(entries, name):
    for e in entries:
        if e.name.lower() == name.lower():
            return e
    raise SystemExit("no entry %s" % name)


def read_entry(name, path=BIG):
    e = find(read_big_index(path)[0], name)
    with open(path, "rb") as f:
        f.seek(e.offset)
        return f.read(e.size)


def cmd_list(sub=None):
    for e in read_big_index()[0]:
        if sub is None or sub.lower() in e.name.lower():
            print("%08X %8X %s" % (e.offset, e.size, e.name))


def cmd_repack(out_big, out_bh, sets, adds):
    entries, tail, slack = read_big_index()
    rows = read_bh()
    if len(rows) != len(entries):
        raise SystemExit("CLASH.BH has %d rows, CLASH.BIG %d entries" % (len(rows), len(entries)))
    for e, r in zip(entries, rows):
        if (r[0], r[1]) != (e.offset, e.size):
            raise SystemExit("CLASH.BH disagrees with CLASH.BIG at %s" % e.name)
        e.usize, e.hash = r[2], r[3]
    for name, path in sets:
        e = find(entries, name)
        e.data = open(path, "rb").read()
        e.usize = unpacked_size(e.data)
    for name, path in adds:
        if any(e.name.lower() == name.lower() for e in entries):
            raise SystemExit("--add: entry exists: %s" % name)
        e = Entry(0, 0, name)
        e.data = open(path, "rb").read()
        e.usize = unpacked_size(e.data)
        entries.append(e)

    index_size = 16 + sum(8 + len(e.name) + 1 for e in entries) + len(tail)
    pos = (index_size + len(slack) + ALIGN - 1) & ~(ALIGN - 1)
    plan = []
    for e in entries:
        size = len(e.data) if e.data is not None else e.size
        plan.append((e, pos, size))
        pos = (pos + size + ALIGN - 1) & ~(ALIGN - 1)
    total = pos

    with open(BIG, "rb") as src, open(out_big, "wb") as dst:
        dst.write(b"BIG4" + struct.pack("<I", total) + struct.pack(">II", len(entries), index_size))
        for e, off, size in plan:
            dst.write(struct.pack(">II", off, size) + e.name.encode("latin-1") + b"\0")
        dst.write(tail + slack)
        for e, off, size in plan:
            dst.write(b"\0" * (off - dst.tell()))
            if e.data is not None:
                dst.write(e.data)
                continue
            src.seek(e.offset)
            left = size
            while left:
                chunk = src.read(min(left, 1 << 22))
                if not chunk:
                    raise SystemExit("short read in %s" % e.name)
                dst.write(chunk)
                left -= len(chunk)
        dst.write(b"\0" * (total - dst.tell()))

    bh_size = 16 + 16 * len(entries) + 16
    with open(out_bh, "wb") as f:
        f.write(b"Viv4" + struct.pack("<I", bh_size) + struct.pack(">II", len(entries), bh_size))
        for e, off, size in plan:
            f.write(struct.pack(">IIII", off, size, e.usize, e.hash))
        f.write(struct.pack(">IIII", total, 0, 0, 0))
    print("wrote %s (%d entries, 0x%X bytes) and %s" % (out_big, len(entries), total, out_bh))


def main(argv):
    cmd = argv[1] if len(argv) > 1 else ""
    if cmd == "list" and len(argv) <= 3:
        cmd_list(argv[2] if len(argv) > 2 else None)
    elif cmd == "get" and len(argv) == 4:
        open(argv[3], "wb").write(read_entry(argv[2]))
    elif cmd == "repack" and len(argv) >= 4 and len(argv) % 2 == 0:
        sets, adds = [], []
        for kind, spec in zip(argv[4::2], argv[5::2]):
            if kind not in ("--set", "--add") or "=" not in spec:
                raise SystemExit(__doc__)
            (sets if kind == "--set" else adds).append(spec.split("=", 1))
        for out in argv[2:4]:
            if out.replace("\\", "/").startswith("orig/"):
                raise SystemExit("refusing to write under orig/: %s" % out)
        cmd_repack(argv[2], argv[3], sets, adds)
    else:
        raise SystemExit(__doc__)


if __name__ == "__main__":
    main(sys.argv)
