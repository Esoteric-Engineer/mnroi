#!/usr/bin/env python3
"""Print and rewrite the tuning files Misc/<CLASS>_<name>.nvb and their schema Misc/defaults.ndb
(docs/characters.md section 4).

Usage (from repo root):
  python3 tools/nvbtool.py schema [CLASS]                 Every field of a class: id, type, default
  python3 tools/nvbtool.py dump NAME [ID ...]             One tuning file (NAME: Wolverine, or PLAYER_WOLVERINE)
  python3 tools/nvbtool.py dump -f FILE [ID ...]          The same from an extracted or edited file
  python3 tools/nvbtool.py field ID [CLASS]               One field across every tuning file of a class
  python3 tools/nvbtool.py set IN OUT ID[.SLOT]=VALUE ... Write an edited copy of the file IN
  python3 tools/nvbtool.py check                          Parse, rebuild and compare every file byte for byte

IDs are decimal or 0x hex. `set` without a slot replaces the field with the one value (slot 0, which
the loader copies to every slot); with a slot it sets that slot and leaves the others. It never
writes under orig/; put the result in the archive with tools/bigtool.py repack --set.

Both formats are little-endian on disc (the loaders fn_801B26DC and fn_801B3638 byte-swap).

defaults.ndb, the schema:
  +0x0  u32 0xD000D000
  +0x4  u32 0x10001                the loader rejects any other value
  +0x8  u32 file size
  +0xC  u32 class count            AI, GLOBALS, PLAYER
  then per class:
        char name[0x40]
        u32 field count
        u32 slot count             1, or 6 for PLAYER (guess: the six slots a tuning file fills)
        field count * {u32 type; value}   the field's default; a field id is its index here

<CLASS>_<name>.nvb, the values that differ from the defaults:
  +0x0  u32 0xBEEFAD00
  +0x4  u32 0x1000                 read and ignored
  +0x8  u32 file size              read and ignored
  +0xC  char class[0x40]           "PLAYER"; what follows the NUL is leftover text of the exporter
  +0x4C char name[0x40]            "Wolverine"
  +0x8C u32 group count
  then per group:
        u32 field id
        u32 record count
        record count * {u32 slot; u32 type; value}

A value is 0x10 bytes for type VECTOR and 4 for type D888; any other type has a u32 size before
its bytes. After a group's first record the loader copies slot 0 to slots 1-5, so a file lists
slot 0 first and then only the slots that differ from it.
"""
import struct
import sys

BIG = "orig/GVLE69/files/CLASH.BIG"
NDB = "Misc/defaults.ndb"
NVB_MAGIC = 0xBEEFAD00
NDB_MAGIC = 0xD000D000
SLOTS = 6

T_TEMPLATE, T_EFFECT, T_D886, T_VECTOR, T_D888, T_STRING, T_FLOAT, T_INT = range(0xFFFFD884, 0xFFFFD88C)
# float, int, string and effect are the exporter's FLOAT, INTEGER, STRING and EFFECTNAME; template
# is named for its values (proj_bioHazBlob); d888 and d886 only occur in the AI class, which no
# tuning file uses
TYPE_NAMES = {
    T_FLOAT: "float",
    T_INT: "int",
    T_STRING: "string",
    T_EFFECT: "effect",
    T_TEMPLATE: "template",
    T_VECTOR: "vector",
    T_D888: "d888",
    T_D886: "d886",
}
TEXT_TYPES = (T_STRING, T_EFFECT, T_TEMPLATE)

# What each field is, by class and id; `schema`, `dump` and `field` print it. Add a line when a
# reader is decompiled (tools/nvbreaders.py lists them). FID_* names are the exporter's own, from
# the text left in the .nvb name buffers; anything else is what a matched reader does with the value.
# A guess goes in only with its basis stated ("inferred from 47 and 48"); otherwise name the reader.
FIELD_NAMES = {
    "PLAYER": {
        2: "second float argument of fn_800E89B0 for an entity fn_80148178 found near the owner; callers of that not yet decompiled",
        7: "distance below which fn_800F0AA0 adds no scatter to the direction; the scatter then grows with the excess over it",
        8: "distance cap and divisor in the scatter of fn_800F0AA0 (the excess over field 7 is divided by it)",
        9: "second float argument of fn_800E9AF8 (fn_800F0328)",
        10: "first float argument of fn_800E9AF8 (fn_800F0328)",
        16: "converted to unsigned and not used again (fn_800F0328)",
        20: "third float argument of fn_800E9AF8 (fn_800F0328)",
        23: "cached in the entity float at +0x3F8 (with +0x3FC = 0x6C) when fn_800CCA88 is 0 (fn_800E3720)",
        24: "as 23, when fn_800CCA88 is non-zero (+0x3FC = 0x6F, and flag 0x80 set in +0x10) (fn_800E3720)",
        32: "cached in the entity at +0x414; also the argument of fn_80084B68 in the first check (fn_800F0328)",
        35: "second argument of fn_80084B68 when fn_800CCA88 is non-zero; picks clip 0x45 over 0x42 (fn_800E339C)",
        39: "target of the entity float at +0xDC when fn_800CC148 flag 0x10 is set inside the flag-9 branch (fn_800D80B4)",
        40: "negated: target of the float at +0xDC when the flag-9 branch is not taken (fn_800D80B4)",
        42: "read into a local and not used again (fn_800D80B4)",
        41: "second argument of fn_80084B68 in fn_800D2CF8 (reached when fn_800861EC is false); callers not yet decompiled",
        43: "cached in the entity at +0x3C4 (fn_8009D71C)",
        44: "cached in the entity at +0x3C8 (fn_8009D71C)",
        45: "cached in the entity at +0x3CC; times GLOBALS 57 gives +0x3D0 (fn_8009D71C)",
        46: "throw distance, class 1 (inferred from 47 and 48)",
        47: "FID_PLAYER_THROWDIST2",
        48: "throw distance, class 3",
        60: "added to the match clock fn_8042EFF8 and stored in the entity at +0xD4 (fn_800F3AE0)",
        64: "rate multiplier (times the frame step fn_80426A84) of the approach of the float at +0xDC to its target (fn_800D80B4)",
        67: "effect name of the left trail, made with fn_80393D0C when fn_800DA254's flag is 0",
        68: "effect name of the right trail, as 67",
        74: "effect name of the left trail, made with fn_80393D0C when fn_800DA254's flag is non-zero (the blade/claw trail)",
        75: "effect name of the right trail, as 74",
        76: "second float argument of fn_800E89B0 (fn_800E339C)",
        81: "effect name made with fn_80393A60 (flag 0) when fn_800861BC is true (fn_800E592C)",
        103: "returned by the getter fn_80086D9C; callers not yet decompiled",
        104: "returned by the getter fn_80086D54; callers not yet decompiled",
        134: "base of 134 + i, returned by fn_80086C80 as 1.0 minus the value; caller not yet decompiled",
        167: "returned by the getter fn_80086DE4; callers not yet decompiled",
        170: "FID_PLAYER_VICTORY1 (versus victory cutscene 1); base of 170 + G[+0x79C + 4*side], the cutscene name fn_80093C14 hands to fn_800578E4",
        183: "read from the target's entity; half of it is added to the clock as the time stamp stored in the AI object's target list (fn_80148178)",
        189: "rage points for superattack",
        184: "length of the timer fn_80161BDC starts (deadline = now + value, stored at +0x18/+0x14); the owner and the caller of fn_80161BDC (vtable slot) not yet decompiled",
        185: "length of the timer fn_8016216C starts (same shape as 184; deadline stored at +0x18/+0x14), then it calls fn_800E9AF8 with 15, 4, 0.5; the owner and caller (vtable slot) not yet decompiled",
        192: "duration (ms is a guess) added to the game clock (fn_8042EFF8) to give the end time stored as a float at entity +0x334, as 195 (fn_8009DF60); named FID_PLAYER_RAGE_DURATION in the DOL",
        193: "rage penalty, % of base points",
        195: "duration (ms is a guess) added to the game clock (fn_8042EFF8) to give the end time stored as a float at entity +0x334 (fn_8009E144)",
        196: "amount fn_80084A60 takes from the actor's float at +0x324 (it subtracts it if that float is not below it) when the move at clip 0x112 starts (fn_800D579C)",
        203: "effect name made with fn_80393D0C (colour 0xFF, 0xFF) as the entity's first handle at +0x3A4 (fn_800E50AC); the values read as super-block effects",
        204: "effect name made with fn_80393D0C (colour 0xFF, 0xFF), second handle (fn_800E50AC; the handle is not stored)",
        205: "effect name made with fn_80393D0C (colour 0xFF, 0xFF) after fn_80114D70 (fn_800E592C)",
        206: "fm_* cutscene against a male opponent (206 + the opponent's SKELETONID, fn_80096460)",
        207: "fm_* cutscene against a female opponent",
        208: "fm_* cutscene against a brute opponent",
        210: "fn_80142558 gives up when the distance to fn_80134870's entity is at most this; callers not yet decompiled",
        211: "fn_8015F008 is true when the Vector-derived float fn_8015E64C is above it; callers not yet decompiled",
        212: "fn_8015F07C is true when that float is below it; callers not yet decompiled",
        220: "name passed to fn_80057894 with the flags word after a 0.33/0.66 random roll (fn_800965A4); caller fn_80092A84",
        222: "window below the time gate (+0x324 minus the argument) inside which fn_80084B68 passes only on a 1-in-100 roll (fn_80084B68)",
        236: "first float argument of fn_800E89B0 (fn_800E339C)",
        223: "first float argument of fn_800E89B0 for an entity fn_80148178 found near the owner; callers of that not yet decompiled",
    },
    "GLOBALS": {
        57: "multiplier on PLAYER 45, cached in the entity at +0x3D0 (fn_8009D71C)",
    },
}

# fn_801343B0 copies these 22 (ids in this order) to floats at +0x598 + 4*i of the object behind the
# entity accessor, converting the two ints; the files vary them per CPU difficulty (guess: AI weights).
for _i, _fid in enumerate((139, 140, 164, 141, 142, 143, 144, 145, 146, 159, 147, 148, 149, 150, 151,
                           152, 153, 154, 155, 156, 247, 246)):
    FIELD_NAMES["PLAYER"][_fid] = "copied to the object's float at +0x%X (guess: AI weight)" % (0x598 + 4 * _i)


def read_value(d, p, typ):
    """The bytes of one value at p, and the offset after it."""
    if typ == T_VECTOR:
        return d[p:p + 0x10], p + 0x10
    if typ == T_D888:
        return d[p:p + 4], p + 4
    n = struct.unpack_from("<I", d, p)[0]
    return d[p + 4:p + 4 + n], p + 4 + n


def write_value(typ, v):
    if typ in (T_VECTOR, T_D888):
        return v
    return struct.pack("<I", len(v)) + v


class Schema:
    def __init__(self, classes):
        self.classes = classes  # list of (raw name, slot count, [(type, default bytes)])

    def fields(self, cls):
        for raw, _, fields in self.classes:
            if raw.split(b"\0")[0].decode().upper() == cls.upper():
                return fields
        raise SystemExit("no class %s in %s" % (cls, NDB))


def parse_ndb(d):
    magic, version, size, count = struct.unpack_from("<4I", d, 0)
    if magic != NDB_MAGIC or version != 0x10001:
        raise ValueError("bad .ndb header %08X %X" % (magic, version))
    p = 16
    classes = []
    for _ in range(count):
        raw = d[p:p + 0x40]
        nfields, nslots = struct.unpack_from("<II", d, p + 0x40)
        p += 0x48
        fields = []
        for _ in range(nfields):
            typ = struct.unpack_from("<I", d, p)[0]
            v, p = read_value(d, p + 4, typ)
            fields.append((typ, v))
        classes.append((raw, nslots, fields))
    if p != len(d) or size != len(d):
        raise ValueError("trailing data: 0x%X of 0x%X (header says 0x%X)" % (p, len(d), size))
    return Schema(classes)


def build_ndb(schema):
    body = bytearray()
    for raw, nslots, fields in schema.classes:
        body += raw + struct.pack("<II", len(fields), nslots)
        for typ, v in fields:
            body += struct.pack("<I", typ) + write_value(typ, v)
    return struct.pack("<4I", NDB_MAGIC, 0x10001, 16 + len(body), len(schema.classes)) + bytes(body)


class Nvb:
    def __init__(self, word1, raw_class, raw_name, groups):
        self.word1 = word1
        self.raw_class = raw_class  # 0x40 bytes as stored, junk after the NUL included
        self.raw_name = raw_name
        self.groups = groups        # list of [field id, [(slot, type, value bytes)]], in file order

    @property
    def cls(self):
        return self.raw_class.split(b"\0")[0].decode("latin-1")

    @property
    def name(self):
        return self.raw_name.split(b"\0")[0].decode("latin-1")

    def group(self, fid):
        for g in self.groups:
            if g[0] == fid:
                return g
        return None

    def slots(self, fid, default):
        """What the loader leaves in the six slots of a field this file lists, or None."""
        g = self.group(fid)
        if g is None:
            return None
        out = [default] * SLOTS
        for j, (slot, _, v) in enumerate(g[1]):
            out[slot] = v
            if j == 0:
                # the loader copies slot 0 here, whichever slot the first record named
                out[1:] = [out[0]] * (SLOTS - 1)
        return out


def parse_nvb(d):
    magic, word1, size = struct.unpack_from("<3I", d, 0)
    if magic != NVB_MAGIC:
        raise ValueError("bad .nvb magic %08X" % magic)
    count = struct.unpack_from("<I", d, 0x8C)[0]
    p = 0x90
    groups = []
    for _ in range(count):
        fid, nrec = struct.unpack_from("<II", d, p)
        p += 8
        recs = []
        for _ in range(nrec):
            slot, typ = struct.unpack_from("<II", d, p)
            v, p = read_value(d, p + 8, typ)
            recs.append((slot, typ, v))
        groups.append([fid, recs])
    if p != len(d) or size != len(d):
        raise ValueError("trailing data: 0x%X of 0x%X (header says 0x%X)" % (p, len(d), size))
    return Nvb(word1, d[0xC:0x4C], d[0x4C:0x8C], groups)


def build_nvb(nvb):
    body = bytearray(nvb.raw_class + nvb.raw_name + struct.pack("<I", len(nvb.groups)))
    for fid, recs in nvb.groups:
        body += struct.pack("<II", fid, len(recs))
        for slot, typ, v in recs:
            body += struct.pack("<II", slot, typ) + write_value(typ, v)
    return struct.pack("<3I", NVB_MAGIC, nvb.word1, 12 + len(body)) + bytes(body)


def fmt(typ, v):
    if typ == T_FLOAT:
        return "%g" % struct.unpack("<f", v)[0]
    if typ in (T_INT, T_D888, T_D886):
        return "%d" % struct.unpack("<i", v)[0]
    if typ == T_VECTOR:
        return "(%g, %g, %g, %g)" % struct.unpack("<4f", v)
    return '"%s"' % v.split(b"\0")[0].decode("latin-1")


def encode(typ, text):
    if typ == T_FLOAT:
        return struct.pack("<f", float(text))
    if typ in (T_INT, T_D888, T_D886):
        return struct.pack("<i", int(text, 0))
    if typ in TEXT_TYPES:
        return text.encode("latin-1") + b"\0"
    raise SystemExit("cannot set a value of type %s" % TYPE_NAMES.get(typ, hex(typ)))


def read_big_index():
    """{lowercased name: (offset, size)} of CLASH.BIG (BIG4 index: tools/bigtool.py)."""
    out = {}
    with open(BIG, "rb") as f:
        count, index_size = struct.unpack(">II", f.read(16)[8:])
        index = f.read(index_size - 16)
    p = 0
    for _ in range(count):
        off, size = struct.unpack_from(">II", index, p)
        end = index.index(b"\0", p + 8)
        out[index[p + 8:end].decode("latin-1").lower()] = (off, size)
        p = end + 1
    return out


def read_entry(index, name):
    off, size = index[name.lower()]
    with open(BIG, "rb") as f:
        f.seek(off)
        return f.read(size)


def nvb_entries(index, cls=None):
    names = sorted(n for n in index if n.endswith(".nvb"))
    if cls:
        names = [n for n in names if n.startswith("misc/%s_" % cls.lower())]
    return names


def find_nvb(index, name):
    want = name.lower()
    if want.endswith(".nvb"):
        want = want[:-4]
    hits = [n for n in nvb_entries(index) if n[5:-4] == want or n[5:-4].split("_", 1)[1] == want]
    if len(hits) != 1:
        raise SystemExit("%s: %d tuning files match" % (name, len(hits)))
    return hits[0]


def ids(args):
    return [int(a, 0) for a in args]


def label(cls, fid):
    name = FIELD_NAMES.get(cls.upper(), {}).get(fid)
    return "  ; " + name if name else ""


def cmd_schema(schema, args):
    for raw, nslots, fields in schema.classes:
        cls = raw.split(b"\0")[0].decode()
        if args and cls.upper() != args[0].upper():
            continue
        print("%s  (%d fields, %d slots)" % (cls, len(fields), nslots))
        for i, (typ, v) in enumerate(fields):
            print("  %3d 0x%02X %-8s %s%s" % (i, i, TYPE_NAMES.get(typ, hex(typ)), fmt(typ, v), label(cls, i)))


def cmd_dump(schema, nvb, want):
    fields = schema.fields(nvb.cls)
    listed = sum(1 for fid, _ in nvb.groups if fid < len(fields))
    print("%s %s  (%d of %d fields set)" % (nvb.cls, nvb.name, listed, len(fields)))
    for i, (typ, default) in enumerate(fields):
        if want and i not in want:
            continue
        slots = nvb.slots(i, default)
        if slots is None:
            if want:
                print("  %3d %-8s default %s%s" % (i, TYPE_NAMES.get(typ, hex(typ)), fmt(typ, default), label(nvb.cls, i)))
            continue
        text = fmt(typ, slots[0])
        other = ["%d: %s" % (s, fmt(typ, v)) for s, v in enumerate(slots) if s and v != slots[0]]
        if other:
            text += "   [" + ", ".join(other) + "]"
        print("  %3d %-8s %s   (default %s)%s" % (i, TYPE_NAMES.get(typ, hex(typ)), text, fmt(typ, default), label(nvb.cls, i)))


def cmd_field(schema, index, fid, cls):
    typ, default = schema.fields(cls)[fid]
    print("%s field %d, %s, default %s%s" % (cls, fid, TYPE_NAMES.get(typ, hex(typ)), fmt(typ, default), label(cls, fid)))
    for entry in nvb_entries(index, cls):
        nvb = parse_nvb(read_entry(index, entry))
        slots = nvb.slots(fid, default)
        if slots is None:
            continue
        text = fmt(typ, slots[0])
        other = ["%d: %s" % (s, fmt(typ, v)) for s, v in enumerate(slots) if s and v != slots[0]]
        if other:
            text += "   [" + ", ".join(other) + "]"
        print("  %-12s %s" % (nvb.name, text))


def cmd_set(schema, src, dst, edits):
    if dst.replace("\\", "/").startswith("orig/"):
        raise SystemExit("refusing to write under orig/")
    nvb = parse_nvb(open(src, "rb").read())
    fields = schema.fields(nvb.cls)
    for edit in edits:
        key, _, text = edit.partition("=")
        fid_text, _, slot_text = key.partition(".")
        fid = int(fid_text, 0)
        if not 0 <= fid < len(fields):
            raise SystemExit("%s has no field %d" % (nvb.cls, fid))
        typ = fields[fid][0]
        value = encode(typ, text)
        g = nvb.group(fid)
        if not slot_text:
            recs = [(0, typ, value)]
        else:
            slot = int(slot_text, 0)
            if not 0 <= slot < SLOTS:
                raise SystemExit("slot %d: slots are 0-%d" % (slot, SLOTS - 1))
            # slot 0 has to come first: the loader copies the first record over slots 1-5
            recs = list(g[1]) if g else [(0, typ, fields[fid][1])]
            recs = [r for r in recs if r[0] != slot] + [(slot, typ, value)]
            recs.sort(key=lambda r: r[0])
            if recs[0][0] != 0:
                recs.insert(0, (0, typ, fields[fid][1]))
        if g:
            g[1] = recs
        else:
            nvb.groups.append([fid, recs])
    open(dst, "wb").write(build_nvb(nvb))
    print("wrote %s (%s %s)" % (dst, nvb.cls, nvb.name))


def cmd_check(index):
    data = read_entry(index, NDB)
    ok = build_ndb(parse_ndb(data)) == data
    print("%-28s %s" % (NDB, "identical" if ok else "DIFFERS"))
    entries = nvb_entries(index)
    for entry in entries:
        data = read_entry(index, entry)
        same = build_nvb(parse_nvb(data)) == data
        if not same:
            print("%-28s DIFFERS" % entry)
        ok = ok and same
    print("%d tuning files, round trip %s" % (len(entries), "identical" if ok else "DIFFERS"))
    sys.exit(0 if ok else 1)


def main(argv):
    if len(argv) < 2 or argv[1] not in ("schema", "dump", "field", "set", "check"):
        raise SystemExit(__doc__)
    cmd, args = argv[1], argv[2:]
    index = read_big_index()
    if cmd == "check":
        cmd_check(index)
    schema = parse_ndb(read_entry(index, NDB))
    if cmd == "schema":
        cmd_schema(schema, args)
    elif cmd == "dump":
        if not args or (args[0] == "-f" and len(args) < 2):
            raise SystemExit(__doc__)
        if args[0] == "-f":
            data, rest = open(args[1], "rb").read(), args[2:]
        else:
            data, rest = read_entry(index, find_nvb(index, args[0])), args[1:]
        cmd_dump(schema, parse_nvb(data), ids(rest))
    elif cmd == "field":
        if not args:
            raise SystemExit(__doc__)
        cmd_field(schema, index, int(args[0], 0), args[1] if len(args) > 1 else "PLAYER")
    elif cmd == "set":
        if len(args) < 3:
            raise SystemExit(__doc__)
        cmd_set(schema, args[0], args[1], args[2:])


if __name__ == "__main__":
    main(sys.argv)
