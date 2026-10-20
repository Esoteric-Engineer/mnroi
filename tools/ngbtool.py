#!/usr/bin/env python3
"""Print the animation bundles Bundles/<name>.ngb (docs/characters.md section 4).

Usage (from repo root):
  python3 tools/ngbtool.py list [substring]             Every animation of every bundle, with its counts
  python3 tools/ngbtool.py dump BUNDLE ANIM [NODE ...]   One animation's keys, decoded, and events
  python3 tools/ngbtool.py pose BUNDLE ANIM FRAME [MODEL]
                                                       Each node's position at a frame, in model space
  python3 tools/ngbtool.py check                         Parse every bundle to its last byte and rebuild
                                                       it byte for byte

BUNDLE is a .ngb in CLASH.BIG (wolverine); `pose` takes the skeleton from the .ngm of the same name
(its first model, or MODEL). As a module, read() and build() turn a bundle into Anim objects and back,
rotation()/translation() decode a key and encode_rotation()/encode_translation() make one, and pose()
evaluates an animation on a skeleton from tools/ngmtool.py.

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
  +0x44 u32 camera count
  +0x48 ptr cameras              -> camera count * 0x50 ("Animation:Cameras", fn_801991FC)
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
  then the cameras, 0x50 each. Event 0x44 (fn_80042378, from fn_8003E3AC) picks one of those
        whose mask and id fit its value and param, and puts the game camera there:
        f32 matrix[16]           the camera's placement relative to the entity playing the
                                 animation (fn_80043EA4)
        u32 modes                bit n: the record serves an event whose value (the mode) is n, 0-2
        u32 id                   equal to the event's param, or within 10 above a base: for mode 2,
                                 a param of 40, 50, 60, 70 or 80 (lbl_80486748) is the base; any
                                 other param reads the word before that table, so ids 4-13 also
                                 match it. A param of 0xFFFF becomes the entity's id (fn_80042EBC)
        f32 fov                  degrees, clamped to 0-360 (fn_8003C9B0)
        u32                      0xCDCDCDCD in every record, unset by the exporter; the .nad reader
                                 does not swap it

pose() applies a node's rotation and then its offset from its parent plus its translation key,
parent first, with keys interpolated linearly in their raw values. A node with no rotation track
keeps the bind orientation, which has no rotation. Tracks whose bone word has a high halfword are
left out.
"""

import math
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


class Anim:
    def __init__(self, name, head, tracks, events, extra):
        self.name = name
        self.head = list(head)  # ANIM's fields after the name; the counts are set by build()
        self.tracks = tracks    # (bone word, channel, pointer, [(frame, (a, b, c, d))])
        self.events = events    # (frame, type, param, value)
        self.extra = extra      # cameras, 0x50 bytes each


def read(data):
    anims, off = [], 0
    while off < len(data):
        h = struct.unpack_from(ANIM, data, off)
        name = h[0].split(b"\0")[0].decode("latin-1")
        table = [struct.unpack_from(TRACK, data, off + 0x50 + 0x10 * i) for i in range(h[4])]
        p = off + 0x50 + 0x10 * h[4]
        tracks = []
        for bone, channel, count, ptr in table:
            keys = []
            for _ in range(count):
                v = struct.unpack_from(">f4h", data, p)
                keys.append((v[0], v[1:]))
                p += 0xC
            tracks.append((bone, channel, ptr, keys))
        events = [struct.unpack_from(">fHHI", data, p + 0xC * i) for i in range(h[8])]
        p += 0xC * h[8]
        extra = [data[p + 0x50 * i:p + 0x50 * (i + 1)] for i in range(h[10])]
        off = p + 0x50 * h[10]
        if off > len(data):
            raise ValueError("%s runs past the end of the file" % name)
        anims.append(Anim(name, h[1:], tracks, events, extra))
    return anims


def build(anims):
    out = bytearray()
    for a in anims:
        h = a.head[:]
        h[3], h[7], h[9] = len(a.tracks), len(a.events), len(a.extra)
        out += struct.pack(ANIM, a.name.encode("latin-1"), *h)
        out += b"".join(struct.pack(TRACK, bone, ch, len(keys), ptr) for bone, ch, ptr, keys in a.tracks)
        for _, _, _, keys in a.tracks:
            out += b"".join(struct.pack(">f4h", frame, *v) for frame, v in keys)
        out += b"".join(struct.pack(">fHHI", *e) for e in a.events)
        out += b"".join(a.extra)
    return bytes(out)


def rotation(v):
    """A channel-0 key as a unit quaternion (w, x, y, z)."""
    w, b, c, d = (x / 16384.0 for x in v)
    q = (w, -c, -d, -b)
    n = math.sqrt(sum(x * x for x in q)) or 1.0
    return tuple(x / n for x in q)


def encode_rotation(q):
    w, x, y, z = q
    return tuple(max(-32768, min(32767, int(round(k * 16384)))) for k in (w, -z, -x, -y))


def translation(v):
    """A channel-1 key as (x, y, z)."""
    a, b, c, d = v
    k = 1.0 / (d & 0xFFFF)
    return (a * k, b * k, c * k)


def encode_translation(t):
    """d = -32768 (1/32768) when the values fit, else the largest d that does."""
    m = max(abs(x) for x in t)
    if m * 32768 < 32767:
        return tuple(int(round(x * 32768)) for x in t) + (-32768,)
    d = int(32767 // m)
    if d < 1:
        raise ValueError("translation too large to encode: %r" % (t,))
    return tuple(int(round(x * d)) for x in t) + (d,)


def sample(keys, t):
    if t <= keys[0][0]:
        return keys[0][1]
    for (t0, a), (t1, b) in zip(keys, keys[1:]):
        if t0 <= t <= t1:
            f = (t - t0) / (t1 - t0) if t1 > t0 else 0.0
            return tuple(x + (y - x) * f for x, y in zip(a, b))
    return keys[-1][1]


def matrix(q):
    w, x, y, z = q
    return [[1 - 2 * (y * y + z * z), 2 * (x * y - z * w), 2 * (x * z + y * w)],
            [2 * (x * y + z * w), 1 - 2 * (x * x + z * z), 2 * (y * z - x * w)],
            [2 * (x * z - y * w), 2 * (y * z + x * w), 1 - 2 * (x * x + y * y)]]


def pose(model, anim, t):
    """[(3x3 rotation, position)] of every node of a ngmtool.Model at frame t; anim None: the bind pose."""
    rot, move = {}, {}
    for bone, ch, _, keys in anim.tracks if anim else []:
        if bone < len(model.nodes) and keys:
            if ch == 0:
                rot[bone] = matrix(rotation(sample(keys, t)))
            else:
                move[bone] = translation(sample(keys, t))
    ident = [[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]
    out = []
    for i, (a, _, parent, _) in enumerate(model.nodes):
        r = rot.get(i, ident)
        d = move.get(i, (0.0, 0.0, 0.0))
        local = tuple(a[k] + d[k] for k in range(3))
        if parent < 0:
            out.append((r, local))
            continue
        pr, pt = out[parent]
        out.append(([[sum(pr[i][k] * r[k][j] for k in range(3)) for j in range(3)] for i in range(3)],
                    tuple(pt[i] + sum(pr[i][k] * local[k] for k in range(3)) for i in range(3))))
    return out


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
            if build(read(data)) != data:
                raise ValueError("rebuilt bundle differs")
        except (ValueError, struct.error) as e:
            print("%-36s %s" % (name, e))
            ok = False
    print("%d animation bundles, %d animations, %s" %
          (len(entries), total, "all parsed to the last byte and rebuilt" if ok else "INVALID"))
    sys.exit(0 if ok else 1)


def find_anim(index, bundle, name):
    entry = "bundles/%s.ngb" % bundle.lower()
    if entry not in index:
        raise SystemExit("no %s in CLASH.BIG (python3 tools/ngbtool.py list)" % entry)
    for a in read(read_entry(index, entry)):
        if a.name.lower() in (name.lower(), name.lower() + ".nad"):
            return a
    raise SystemExit("no animation %s in %s" % (name, entry))


def cmd_dump(anim, nodes):
    print("%s: length %g, %d tracks, %d events, %d extra" % (
        anim.name, anim.head[2], len(anim.tracks), len(anim.events), len(anim.extra)))
    for bone, ch, _, keys in anim.tracks:
        if nodes and bone & 0xFFFF not in nodes:
            continue
        decode = rotation if ch == 0 else translation
        print("node %d%s %s" % (bone & 0xFFFF, " (high %d)" % (bone >> 16) if bone >> 16 else "",
                                "rotation (w, x, y, z)" if ch == 0 else "translation"))
        for frame, v in keys:
            print("    %7.2f  %s" % (frame, " ".join("%8.4f" % x for x in decode(v))))
    for e in anim.events:
        print("event %7.2f type 0x%02X param 0x%02X value %d" % e)


def cmd_pose(index, bundle, anim, frame, model_name):
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import ngmtool
    models = ngmtool.read(read_entry(index, "bundles/%s.ngm" % bundle.lower()))[1]
    model = models[0]
    if model_name:
        model = next((m for m in models if m.name.lower() in (model_name.lower(), model_name.lower() + ".nod")), None)
        if model is None:
            raise SystemExit("no model %s in bundles/%s.ngm" % (model_name, bundle))
    for i, (_, pos) in enumerate(pose(model, anim, frame)):
        print("node %3d  %9.4f %9.4f %9.4f" % ((i,) + pos))


def main(argv):
    cmd = argv[1] if len(argv) > 1 else ""
    if cmd not in ("list", "dump", "pose", "check") or (cmd == "dump" and len(argv) < 4) or \
            (cmd == "pose" and len(argv) not in (5, 6)):
        raise SystemExit(__doc__)
    index = read_big_index()
    if cmd == "check":
        cmd_check(index)
    elif cmd == "dump":
        cmd_dump(find_anim(index, argv[2], argv[3]), {int(n) for n in argv[4:]})
    elif cmd == "pose":
        cmd_pose(index, argv[2], find_anim(index, argv[2], argv[3]), float(argv[4]), argv[5] if len(argv) > 5 else None)
    else:
        cmd_list(index, argv[2] if len(argv) > 2 else None)


if __name__ == "__main__":
    main(sys.argv)
