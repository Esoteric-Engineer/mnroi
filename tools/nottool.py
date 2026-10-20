#!/usr/bin/env python3
"""Print and rewrite the entity template file Misc/Global.not (docs/characters.md section 3).

Usage (from repo root):
  python3 tools/nottool.py dump [NAME ...]         All templates, or the named ones, from CLASH.BIG
  python3 tools/nottool.py dump -f FILE [NAME ...] The same from an extracted or edited file
  python3 tools/nottool.py check [-f FILE]         Parse, rebuild and compare byte for byte

As a module, parse() and build() turn the file into a list of Template objects and back.

Layout, little-endian on disc (the loader fn_800FCF50 byte-swaps):
  +0x0  "NOT\\x10"
  +0x4  u32 version (1)
  +0x8  u32 template count
  +0xC  count index entries {char name[0x20]; u32 offset}   offset = file offset of the body then the bodies, in index order and back to back (the loader reads them sequentially):
        u32 property count
        property count * {u32 id; u8 value[0x20]}     a string, int, float or three floats
        u32 n; u8 text[n]                             a NUL-terminated note, "\\0" (n = 1) when empty
"""
import struct
import sys

DOL = "orig/GVLE69/sys/main.dol"
BIG = "orig/GVLE69/files/CLASH.BIG"
ENTRY = "Misc/Global.not"
PROP_TABLE = 0x8048E748  # 120 entries {char name[0x20]; int kind; int type}
MAGIC = b"NOT\x10"

# id -> (name, value type); types: 0 string, 2 float, 3 int, 4 vector
PROPS = {}


def load_prop_table(dol_path=DOL):
    d = open(dol_path, "rb").read()
    offs = struct.unpack_from(">18I", d, 0)
    addrs = struct.unpack_from(">18I", d, 0x48)
    sizes = struct.unpack_from(">18I", d, 0x90)
    for a, o, s in zip(addrs, offs, sizes):
        if s and a <= PROP_TABLE < a + s:
            p = o + PROP_TABLE - a
            for i in range(120):
                name = d[p:p + 0x20].split(b"\0")[0].decode()
                typ = struct.unpack_from(">i", d, p + 0x24)[0]
                PROPS[i] = (name, typ)
                p += 0x28
            return
    raise SystemExit("property table not found in " + dol_path)


class Template:
    def __init__(self, raw_name, props, note):
        self.raw_name = raw_name  # 0x20 bytes as stored (the original has junk after the NUL)
        self.props = props        # list of (id, 0x20-byte value)
        self.note = note          # bytes, including the terminating NUL

    @property
    def name(self):
        return self.raw_name.split(b"\0")[0].decode("latin-1")

    def get(self, pid):
        for i, v in self.props:
            if i == pid:
                return v
        return None

    def set(self, pid, value):
        for k, (i, _) in enumerate(self.props):
            if i == pid:
                self.props[k] = (pid, value)
                return
        self.props.append((pid, value))


def name32(s):
    b = s.encode("latin-1")
    if len(b) > 0x1F:
        raise ValueError("name longer than 31 characters: " + s)
    return b + b"\0" * (0x20 - len(b))


def v_str(s):
    return name32(s)


def v_int(n):
    return struct.pack("<I", n & 0xFFFFFFFF) + b"\0" * 0x1C


def v_float(f):
    return struct.pack("<f", f) + b"\0" * 0x1C


def parse(data):
    if data[:4] != MAGIC:
        raise ValueError("bad magic %r" % data[:4])
    version, count = struct.unpack_from("<II", data, 4)
    if version != 1:
        raise ValueError("version %d" % version)
    index = []
    p = 12
    for _ in range(count):
        index.append((data[p:p + 0x20], struct.unpack_from("<I", data, p + 0x20)[0]))
        p += 0x24
    out = []
    for raw, off in index:
        if off != p:
            raise ValueError("body of %r at 0x%X, expected 0x%X" % (raw, off, p))
        n = struct.unpack_from("<I", data, p)[0]
        p += 4
        props = []
        for _ in range(n):
            props.append((struct.unpack_from("<I", data, p)[0], data[p + 4:p + 0x24]))
            p += 0x24
        tn = struct.unpack_from("<I", data, p)[0]
        note = data[p + 4:p + 4 + tn]
        p += 4 + tn
        out.append(Template(raw, props, note))
    if p != len(data):
        raise ValueError("trailing data: 0x%X of 0x%X" % (p, len(data)))
    return out


def build(templates):
    head = bytearray(MAGIC + struct.pack("<II", 1, len(templates)))
    bodies = bytearray()
    base = 12 + 0x24 * len(templates)
    for t in templates:
        head += t.raw_name + struct.pack("<I", base + len(bodies))
        bodies += struct.pack("<I", len(t.props))
        for pid, v in t.props:
            if len(v) != 0x20:
                raise ValueError("%s: property 0x%X value is not 0x20 bytes" % (t.name, pid))
            bodies += struct.pack("<I", pid) + v
        bodies += struct.pack("<I", len(t.note)) + t.note
    return bytes(head + bodies)


def fmt_value(pid, v):
    typ = PROPS.get(pid, ("", None))[1]
    if typ == 0:
        return repr(v.split(b"\0")[0].decode("latin-1"))
    if typ == 2:
        return "%g" % struct.unpack_from("<f", v)[0]
    if typ == 3:
        n = struct.unpack_from("<I", v)[0]
        return "%d (0x%X)" % (n, n)
    if typ == 4:
        return "(%g, %g, %g)" % struct.unpack_from("<3f", v)
    return v.rstrip(b"\0").hex() or "0"


def dump(templates, names):
    want = {n.lower() for n in names}
    for i, t in enumerate(templates):
        if want and t.name.lower() not in want:
            continue
        note = "" if t.note == b"\0" else "  note=%r" % t.note
        print("[%d] %s  (%d properties)%s" % (i, t.name, len(t.props), note))
        for pid, v in t.props:
            print("    0x%02X %-18s %s" % (pid, PROPS.get(pid, ("?",))[0], fmt_value(pid, v)))


def read_from_big():
    """Misc/Global.not straight out of CLASH.BIG (BIG4 index: tools/bigtool.py)."""
    with open(BIG, "rb") as f:
        count, index_size = struct.unpack(">II", f.read(16)[8:])
        index = f.read(index_size - 16)
        p = 0
        for _ in range(count):
            off, size = struct.unpack_from(">II", index, p)
            end = index.index(b"\0", p + 8)
            if index[p + 8:end].decode("latin-1").lower() == ENTRY.lower():
                f.seek(off)
                return f.read(size)
            p = end + 1
    raise SystemExit("%s not found in %s" % (ENTRY, BIG))


def main(argv):
    args = argv[2:]
    if len(argv) < 2 or argv[1] not in ("dump", "check"):
        raise SystemExit(__doc__)
    if args[:1] == ["-f"]:
        if len(args) < 2:
            raise SystemExit(__doc__)
        data = open(args[1], "rb").read()
        args = args[2:]
    else:
        data = read_from_big()
    templates = parse(data)
    if argv[1] == "dump":
        load_prop_table()
        dump(templates, args)
    else:
        same = build(templates) == data
        print("%d templates, round trip %s" % (len(templates), "identical" if same else "DIFFERS"))
        sys.exit(0 if same else 1)


if __name__ == "__main__":
    main(sys.argv)
