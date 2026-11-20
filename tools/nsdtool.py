#!/usr/bin/env python3
"""Print and round-trip the level scene files Levels/*.nsd (docs/story.md row 14).

Usage (from repo root):
  python3 tools/nsdtool.py list [substring]          Every .nsd in CLASH.BIG with its counts
  python3 tools/nsdtool.py dump NAME                  One scene: header, objects, player starts, tail
  python3 tools/nsdtool.py dump -f FILE               The same from an extracted or edited file
  python3 tools/nsdtool.py check                      Parse every .nsd to its last byte and rebuild it

As a module, parse() and build() turn a file into a Scene and back.

Little-endian on disc; the reader fn_800A4DF8 (Game/fn_800A4DF8.cpp) byte-swaps every word.
All 118 shipped files are version 12, which takes the reader's non-11 branch; the version-11
sections (fn_800A7A0C's sectors and point sounds, interest spots, a third record array) are
never read and this tool does not handle them.
  u32  word                 read and ignored; not a constant (14 values across the files)
  u32  version              the reader rejects <= 10
  char[0x20], char[0x20]    scene +0x2C, +0x4C ("temp description" in the test levels)
  u32                       scene +0x4
  u32 n; n * char[0x20]     template files, each loaded with fn_800FCF50 (scene +0x174)
  u32 n; n objects          fn_800A7208, at most one entity each:
        u32 n; n * {u32 id; u8 value[0x20]}   1-0x80 template properties, as Misc/Global.not
                            (tools/nottool.py); the value is swapped by the id's type
        u32 n; n * 0x30     thing frames (fn_800A85F8): f32[4], f32[4], u16, 14 bytes. menu.nsd
                            and 0_Test_Look.nsd hold 0x24-byte frames from an older exporter: the
                            reader loses sync there and fn_800A7208 fails, which fn_800A4DF8
                            ignores, so this tool keeps those files raw from the first such object
        u32 n; n params     the entity's script parameters (fn_8007CABC): u32 type, then a
                            u32 (types 1, 3-5, 10-13), an f32 (2), u32 len + len bytes (7-9),
                            or nothing
        u32 m               0, 1 or 2 embedded models (fn_800A6F80, the second is +0x234):
                            each a 0x70-byte .nod header (fn_801A0FA4) and its body
                            (fn_80220D54 with flag 0x200), see MODEL below
        u32 n; n * u32      things (level +0x12C, 0x1C0 each) the entity joins (fn_800A87A4)
        u16 f               1: a camera region follows (fn_800A8A30; read only for a kind-3
                            object, and every shipped object with the flag is one):
                            u32, u32 flags, [f32 x3 if flags & 0x10000], u32 n, n * 0x60
        u16 n; n * {u32 c; c * u32}   per-mesh word lists (fn_800A837C, fn_80222B8C)
  u32 n; n * 0x3C           player starts: u32, f32[3] x4 (the last is the position), u32, u32
  tail, 0x10C bytes; 20 files stop short or carry extra bytes, and the reader ignores
  short reads here, so build() writes it back as stored:
        f32[4] x4, f32, f32 (scene +0xC0), u32 (+0x70), f32[4] (+0x80), f32 (+0x90), f32 (+0x94),
        char model[0x20] (+0xCC), char anim[0x20] (its clip, +0xD0), f32[4] pos (+0x104),
        f32[4] rot (+0xD4), char[0x20], char[0x20], f32 (default 0), f32 (default -14)

MODEL, the embedded .nod (little-endian):
  0x70 header: u32 bounds[8]; u32 version; u8 parts, nodes, streams, meshes; u32 flags;
        u32 indices; {u32 type; u32 count}[4] per stream; u32[4]; 16 bytes
  parts * char[0x20]        material names
  nodes * 0x60
  per stream: count * STRIDE[type] bytes (lbl_80670800), and count * 0x24 more if type > 2
  indices * u16
  meshes * 0x40             fn_8019FEE0
  u32 n; n * 0x50           attachments
  u16, u16                  model +0x158, +0x15A
  u32 n; n * f32[4]         planes (fn_801A0FA4)
"""
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import bigtool  # noqa: E402
import nottool  # noqa: E402

STRIDE = (0x20, 0x24, 0x30, 0x20, 0x24, 0x30)  # lbl_80670800, bytes per vertex by stream type
TAIL_SIZE = 0x10C
WORD_PARAMS = (1, 3, 4, 5, 10, 11, 12, 13)
STRING_PARAMS = (7, 8, 9)


class Reader:
    def __init__(self, data):
        self.data = data
        self.off = 0

    def take(self, fmt):
        vals = struct.unpack_from("<" + fmt, self.data, self.off)
        self.off += struct.calcsize("<" + fmt)
        return vals if len(vals) > 1 else vals[0]

    def raw(self, n):
        if self.off + n > len(self.data):
            raise ValueError("record at 0x%X runs past the end of the file" % self.off)
        v = self.data[self.off:self.off + n]
        self.off += n
        return v


class Object:
    def __init__(self):
        self.props = []      # (id, 0x20-byte value)
        self.frames = b""    # n * 0x30, raw
        self.params = []     # (type, value): int, float, bytes or None
        self.models = []     # raw embedded .nod blobs
        self.things = []     # u32 thing indices
        self.camera = None   # raw camera region (after the u16 flag), or None
        self.lists = []      # per-mesh word lists: lists of u32


class Scene:
    def __init__(self):
        self.word = 0
        self.version = 12
        self.desc = (b"\0" * 0x20, b"\0" * 0x20)
        self.u4 = 0
        self.templates = []  # raw char[0x20]
        self.objects = []
        self.object_count = 0  # as stored; more than len(objects) when rest is set
        self.rest = b""     # raw, from the first object that does not parse to the end
        self.starts = []     # raw 0x3C records
        self.tail = b""


def model_size(data, off):
    """Length of the embedded .nod at off."""
    r = Reader(data)
    r.off = off
    h = r.raw(0x70)
    parts, nodes, streams, meshes = h[0x24:0x28]
    indices = struct.unpack_from("<I", h, 0x2C)[0]
    pairs = struct.unpack_from("<8I", h, 0x30)
    r.raw(parts * 0x20 + nodes * 0x60)
    for i in range(streams):
        kind, count = pairs[2 * i], pairs[2 * i + 1]
        r.raw(count * STRIDE[kind] + (count * 0x24 if kind > 2 else 0))
    r.raw(indices * 2 + meshes * 0x40)
    r.raw(r.take("I") * 0x50 + 4)
    r.raw(r.take("I") * 0x10)
    return r.off - off


def parse_object(r):
    o = Object()
    n = r.take("I")
    if not 1 <= n <= 0x80:
        raise ValueError("object at 0x%X: %d properties" % (r.off - 4, n))
    for _ in range(n):
        o.props.append((r.take("I"), r.raw(0x20)))
    o.frames = r.raw(r.take("I") * 0x30)
    for _ in range(r.take("I")):
        kind = r.take("I")
        if kind in WORD_PARAMS:
            o.params.append((kind, r.take("I")))
        elif kind == 2:
            o.params.append((kind, r.take("f")))
        elif kind in STRING_PARAMS:
            o.params.append((kind, r.raw(r.take("I"))))
        else:
            o.params.append((kind, None))
    models = r.take("I")
    for _ in range(2 if models == 2 else 1 if models else 0):
        o.models.append(r.raw(model_size(r.data, r.off)))
    n = r.take("I")
    o.things = list(struct.unpack("<%dI" % n, r.raw(n * 4)))
    if r.take("H") == 1:
        start = r.off
        r.take("I")
        flags = r.take("I")
        if flags & 0x10000:
            r.raw(12)
        r.raw(r.take("I") * 0x60)
        o.camera = r.data[start:r.off]
    for _ in range(r.take("H")):
        c = r.take("I")
        o.lists.append(list(struct.unpack_from("<%dI" % c, r.raw(c * 4))))
    return o


def parse(data):
    r = Reader(data)
    s = Scene()
    s.word, s.version = r.take("II")
    if s.version <= 10:
        raise ValueError("version %d: the reader rejects it" % s.version)
    if s.version == 11:
        raise ValueError("version 11 sections are not handled")
    s.desc = (r.raw(0x20), r.raw(0x20))
    s.u4 = r.take("I")
    s.templates = [r.raw(0x20) for _ in range(r.take("I"))]
    s.object_count = r.take("I")
    for _ in range(s.object_count):
        start = r.off
        try:
            s.objects.append(parse_object(r))
        except (ValueError, struct.error):
            s.rest = data[start:]
            return s
    s.starts = [r.raw(0x3C) for _ in range(r.take("I"))]
    s.tail = data[r.off:]
    return s


def build(s):
    out = bytearray(struct.pack("<II", s.word, s.version))
    out += s.desc[0] + s.desc[1] + struct.pack("<II", s.u4, len(s.templates))
    out += b"".join(s.templates)
    out += struct.pack("<I", s.object_count if s.rest else len(s.objects))
    for o in s.objects:
        out += struct.pack("<I", len(o.props))
        for pid, v in o.props:
            out += struct.pack("<I", pid) + v
        out += struct.pack("<I", len(o.frames) // 0x30) + o.frames
        out += struct.pack("<I", len(o.params))
        for kind, v in o.params:
            out += struct.pack("<I", kind)
            if kind in WORD_PARAMS:
                out += struct.pack("<I", v)
            elif kind == 2:
                out += struct.pack("<f", v)
            elif kind in STRING_PARAMS:
                out += struct.pack("<I", len(v)) + v
        out += struct.pack("<I", len(o.models)) + b"".join(o.models)
        out += struct.pack("<I%dI" % len(o.things), len(o.things), *o.things)
        out += struct.pack("<H", 1 if o.camera is not None else 0) + (o.camera or b"")
        out += struct.pack("<H", len(o.lists))
        for words in o.lists:
            out += struct.pack("<I%dI" % len(words), len(words), *words)
    if s.rest:
        return bytes(out + s.rest)
    out += struct.pack("<I", len(s.starts)) + b"".join(s.starts)
    return bytes(out + s.tail)


def cstr(b):
    return b.split(b"\0")[0].decode("latin-1")


def model_name(blob):
    """The embedded .nod has no name: its part count and first material."""
    parts = blob[0x24]
    return "%d parts %s" % (parts, cstr(blob[0x70:0x90]) if parts else "")


def dump(s):
    print("version %d  word 0x%08X  %r %r  +0x4 %d" % (s.version, s.word, cstr(s.desc[0]), cstr(s.desc[1]), s.u4))
    for t in s.templates:
        print("template %s" % cstr(t))
    for i, o in enumerate(s.objects):
        extra = []
        if o.frames:
            extra.append("%d frames" % (len(o.frames) // 0x30))
        if o.models:
            extra.append("models: " + ", ".join(model_name(m) for m in o.models))
        if o.things:
            extra.append("things %s" % o.things)
        if o.camera is not None:
            extra.append("camera region %d bytes" % len(o.camera))
        if o.lists:
            extra.append("%d mesh lists" % len(o.lists))
        print("[%d] %s" % (i, "  ".join(extra)))
        for pid, v in o.props:
            print("    0x%02X %-18s %s" % (pid, nottool.PROPS.get(pid, ("?",))[0], nottool.fmt_value(pid, v)))
        for kind, v in o.params:
            print("    param %2d %r" % (kind, v))
    if s.rest:
        print("objects %d to %d and the rest of the file kept raw: %d bytes" % (len(s.objects), s.object_count - 1, len(s.rest)))
    for i, rec in enumerate(s.starts):
        print("start %d  position (%g, %g, %g)  %d %d" % ((i,) + struct.unpack_from("<3f", rec, 0x28) + struct.unpack_from("<II", rec, 0x34)))
    t = s.tail
    if len(t) >= 0xA4:
        print("tail  model %r  anim %r" % (cstr(t[0x64:0x84]), cstr(t[0x84:0xA4])))
    print("tail  %d bytes (full 0x%X)" % (len(t), TAIL_SIZE))


def nsd_entries(sub=None):
    for e in bigtool.read_big_index()[0]:
        if e.name.lower().endswith(".nsd") and (sub is None or sub.lower() in e.name.lower()):
            yield e


def read(e, f):
    f.seek(e.offset)
    return f.read(e.size)


def main(argv):
    if len(argv) < 2 or argv[1] not in ("list", "dump", "check"):
        raise SystemExit(__doc__)
    cmd, args = argv[1], argv[2:]
    if cmd == "dump":
        if args[:1] == ["-f"] and len(args) == 2:
            data = open(args[1], "rb").read()
        elif len(args) == 1:
            data = bigtool.read_entry(args[0] if "/" in args[0] else "Levels/" + args[0])
        else:
            raise SystemExit(__doc__)
        nottool.load_prop_table()
        dump(parse(data))
        return
    bad = 0
    count = 0
    partial = 0
    with open(bigtool.BIG, "rb") as f:
        for e in nsd_entries(args[0] if cmd == "list" and args else None):
            data = read(e, f)
            count += 1
            try:
                s = parse(data)
            except (ValueError, struct.error) as ex:
                print("%s: %s" % (e.name, ex))
                bad += 1
                continue
            partial += bool(s.rest)
            if cmd == "list":
                print("%-40s %4d objects %3d models %2d starts  tail %d%s" % (
                    e.name, s.object_count, sum(len(o.models) for o in s.objects), len(s.starts), len(s.tail),
                    "  (raw from object %d)" % len(s.objects) if s.rest else ""))
            elif build(s) != data:
                print("%s: round trip differs" % e.name)
                bad += 1
    if cmd == "check":
        print("%d files, %d round trips identical, %d with a raw remainder" % (count, count - bad, partial))
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main(sys.argv)
