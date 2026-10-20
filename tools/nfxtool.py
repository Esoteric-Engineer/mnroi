#!/usr/bin/env python3
"""Read the effect definitions (Misc/game.nfx) and check a file against what the loader accepts.

Usage (from repo root):
  python3 tools/nfxtool.py list [TYPE] [-f FILE]     The blocks: type, name, records, cache bytes
  python3 tools/nfxtool.py show NAME ... [-f FILE]   A block's records as the game parses them
  python3 tools/nfxtool.py keys                      The 140 keys and their value kinds
  python3 tools/nfxtool.py check [-f FILE]           Rebuild both .nfx files in CLASH.BIG byte for byte
                                                     and check game.nfx (or FILE) against the loader

Without -f the file is Misc/game.nfx in CLASH.BIG. As a module, read_nfx()/build_nfx() parse and
rebuild a file losslessly, Block.records() parses a block's values, and cache_use() runs the loader's
allocations. Misc/defaults.nfx has the same syntax, but the game never reads it (fn_803A38DC opens
only game.nfx).

The file, as fn_803A38DC (Game/fn_803A38DC.cpp) reads it: CRLF text, at most 0x1FF bytes a line,
split on " \\r\\t\\n" with strtok. A line starting with ';' is a comment.
  header   <type> <name>    type is one of the 32 effect classes (TYPES), name any token; a line
                            whose first token is not a type is skipped. Both are looked up ignoring
                            case, and a duplicate name loses to the first block of that name.
  key      <key> <value>    one per line until "end" or the end of the file; fn_803944A4 finds the
                            key, ignoring case, in KEYS (lbl_804DC2F0); an unknown key's line is
                            skipped. Only the first token after the key is read, so a value has no
                            spaces.
  end
Value kinds (lbl_804DC520, KINDS), parsed by fn_803A2F48:
  0 int     atoi                      3 vector  sscanf "(%f,%f,%f)", 12 bytes in the cache
  1 float   atof                      4 colour  sscanf "(%f,%f,%f,%f)" = (a,r,g,b), packed by
  2 string  31 characters at most,              fn_8047FB84 to 0xAARRGGBB, each value rounded
            strlen + 1 bytes in the cache       and not masked to 8 bits
                                      5 hex     sscanf "%x"
Key 103, "cache", is not a record: atoi of its value goes to the block's +0x11 byte.

Loader limits:
  - A block's values go through a scratch table of 28 entries (lbl_8064E670) with no bounds check,
    so a block holds at most 28 records (game.nfx's largest has 27).
  - Everything is allocated from one 300,000-byte cache (fn_803A3460). Over it, the allocator
    prints "FXCACHE_MEM_SIZE needs to be..." and returns null, which the loader writes through.
    An allocation whose size is a multiple of 4 is first aligned to 4 (the cache base is taken as
    4-aligned). Per block, in order: the name (strlen + 1), the 28 32-byte scratch strings (once,
    for the file's first record), the records (8 bytes each: u32 key, u32 value or pointer), then
    each vector and string value. The block's own 0x18-byte node is on the heap.
Effect class n is the n-th registration in fn_8039E22C (Game/fn_8039E22C.cpp); fn_8039DAA0 keeps
{factory, size} at lbl_8066B0E0[n], and fn_80480344 turns a type word into n.
"""

import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nvbtool import read_big_index, read_entry  # noqa: E402

GAME = "misc/game.nfx"
FILES = (GAME, "misc/defaults.nfx")
CACHE_SIZE = 300000
SCRATCH = 28
LINE_MAX = 0x1FF
DELIMS = " \r\t\n"

TYPES = (
    "controller", "trail", "partsys", "partsysdam", "partsubfx", "partmodel", "glow", "constraint",
    "cloth", "shockwave", "psishield", "billboard", "billboardomni", "volumefog", "rain",
    "partcylinder", "actorglow", "energybeam", "lasertripwire", "gibomatic2k", "dyngeom",
    "ctrldamage", "radiuseffect", "light", "projectcube", "boxproject", "project", "spawner", "glass",
    "meshtypeflash", "damage", "worldfx",
)

INT, FLOAT, STRING, VECTOR, COLOUR, HEX = range(6)
KIND_NAMES = ("int", "float", "string", "vector", "colour", "hex")

# (key, kind) in index order
_KEYS = """
invalid 0 end 0 material 2 material2 2 startsize 1 endsize 1 sampledelay 1 startcol 4 endcol 4
startcol2 4 endcol2 4 startcolor 5 endcolor 5 startcolor2 5 endcolor2 5 flags 5 markertype 0
marker_index 0 endmarker 0 endmarker_id 0 spawn_delay 1 max_particles 0 max_particles2 0
max_particles3 0 part_life 1 part_size0 1 part_size1 1 maxsize 1 minspread 1 maxspread 1 mindist 1
maxdist 1 effect0 2 effect1 2 effect2 2 effect3 2 change_speed 1 rotate_speed 1 type_flags 5
type_flags2 5 constflags 5 clothflags 5 modflags 5 modsize 3 effectname 2 scale 1 scale2 1 zoffset 1
radius0 1 radius1 1 duration 1 duration_rnd 1 velocity_x 1 velocity_y 1 velocity_z 1 size 1
minsize 1 model 2 force 1 priority 0 turbulence 1 width 1 height 1 velocity 3 faderate 1
lightstyle 0 damagemin 1 damagemax 1 area_type 0 area 3 area_x 1 area_y 1 area_z 1 renderradius 1
type 0 gravity 1 speed 1 width0 1 width1 1 height0 1 height1 1 spin 1 fadein 1 fadeout 1
partfadein 1 partfadeout 1 flashtime 1 intensity 1 warp 1 fov 1 falloff 1 respawn 1 lerpin 1
lerpout 1 angle 1 lerpspeed 1 lerpspeed2 1 decal 0 decalscale 1 fov2 1 source 0 loddist 1
turnspeed 1 cache 0 fieldpos 3 anim 1 delay 1 tile 1 ratio 1 drag 1 mass 1 anim0 1 anim1 1
intensity0 1 intensity1 1 seed 0 axis 0 soundid 0 length0 1 primitive 0 fieldforce 1 radiusb0 1
radiusb1 1 length1 1 rendermax 1 rendermin 1 fieldshape 0 offset 3 ratio2 1 collision0 0 flags2 5
target 3 tile2 1 uvtype 0 coltype 0 postype 0 pos2type 0 rotatetype 0 template 2 childflag 5
""".split()
KEYS = tuple(_KEYS[0::2])
KINDS = tuple(int(k) for k in _KEYS[1::2])
KEY_INDEX = {k: i for i, k in enumerate(KEYS)}
END = 1
CACHE_KEY = 103


# C library parsing, as the loader calls it

_INT = re.compile(r"[ \t\n\v\f\r]*([+-]?\d+)")
_FLOAT = re.compile(r"[ \t\n\v\f\r]*([+-]?(?:\d+\.?\d*|\.\d+)(?:[eE][+-]?\d+)?)")
_HEX = re.compile(r"[ \t\n\v\f\r]*([+-]?)(?:0[xX])?([0-9a-fA-F]+)")


def atoi(s):
    m = _INT.match(s)
    return int(m.group(1)) if m else 0


def atof(s):
    m = _FLOAT.match(s)
    return float(m.group(1)) if m else 0.0


def f32(x):
    return struct.unpack(">f", struct.pack(">f", x))[0]


def scan_floats(s, count):
    """sscanf(s, "(%f,%f,...)"): the floats read, possibly fewer than count."""
    out = []
    if not s.startswith("("):
        return out
    p = 1
    for i in range(count):
        m = _FLOAT.match(s, p)
        if not m:
            break
        out.append(f32(float(m.group(1))))
        p = m.end()
        sep = "," if i < count - 1 else ")"
        if s[p:p + 1] != sep:
            break
        p += 1
    return out


def scan_hex(s):
    m = _HEX.match(s)
    if not m:
        return None
    v = int(m.group(2), 16) & 0xFFFFFFFF
    return (-v) & 0xFFFFFFFF if m.group(1) == "-" else v


def pack_colour(a, r, g, b):
    """fn_8047FB84: round each value to an int (the 1.5 * 2^23 trick) and OR them unmasked."""
    def rnd(x):
        return int(round(x)) & 0xFFFFFFFF
    return ((rnd(a) << 24) | (rnd(r) << 16) | (rnd(g) << 8) | rnd(b)) & 0xFFFFFFFF


# The file

def tokens(line):
    return [t for t in re.split("[" + re.escape(DELIMS) + "]", line) if t]


class Record:
    def __init__(self, key, text):
        self.key = key            # index in KEYS
        self.text = text          # the value token, "" if none
        self.kind = KINDS[key]
        self.value, self.error = self._parse()

    def _parse(self):
        t, kind = self.text, self.kind
        if kind == INT:
            return atoi(t), None
        if kind == FLOAT:
            return f32(atof(t)), None
        if kind == STRING:
            return t[:31], "longer than 31 characters" if len(t) > 31 else None
        if kind in (VECTOR, COLOUR):
            n = 3 if kind == VECTOR else 4
            vals = scan_floats(t, n)
            if len(vals) < n:
                return vals, "not (%s)" % ",".join(["%f"] * n)
            return (tuple(vals) if kind == VECTOR else pack_colour(*vals)), None
        v = scan_hex(t)
        return (0, "not hex") if v is None else (v, None)

    def cache_sizes(self):
        if self.kind == VECTOR:
            return [12]
        if self.kind == STRING:
            return [len(self.value) + 1]
        return []

    def show(self):
        if self.kind == COLOUR and self.error is None:
            v = "0x%08X" % self.value
        elif self.kind == HEX:
            v = "0x%X" % self.value
        elif self.kind == VECTOR and self.error is None:
            v = "(%g, %g, %g)" % self.value
        elif self.kind == FLOAT:
            v = "%g" % self.value
        else:
            v = repr(self.value) if self.kind == STRING else str(self.value)
        return v + ("   ! " + self.error if self.error else "")


class Block:
    def __init__(self, type_, name, lines, ended):
        self.type = type_         # index in TYPES
        self.name = name
        self.lines = lines        # raw lines, the header first and "end" last if ended
        self.ended = ended

    def records(self):
        """The records the loader keeps, the unknown keys it skips, and the cache key's value."""
        recs, unknown, cache = [], [], None
        for line in self.lines[1:len(self.lines) - self.ended]:
            if line.startswith(";"):
                continue
            t = tokens(line[:LINE_MAX - 1])
            if not t:
                continue
            key = KEY_INDEX.get(t[0].lower(), 0)
            if key == 0:
                unknown.append(t[0])
            elif key == CACHE_KEY:
                cache = atoi(t[1]) & 0xFF if len(t) > 1 else 0
            else:
                recs.append(Record(key, t[1] if len(t) > 1 else ""))
        return recs, unknown, cache


def read_nfx(data):
    """[str | Block]: the lines outside blocks as they are, and the blocks."""
    lines = data.decode("latin-1").split("\r\n")
    items = []
    i = 0
    while i < len(lines):
        line = lines[i]
        t = [] if line.startswith(";") else tokens(line[:LINE_MAX - 1])
        if len(t) < 2 or t[0].lower() not in TYPES:
            items.append(line)
            i += 1
            continue
        j = i + 1
        ended = False
        while j < len(lines):
            u = [] if lines[j].startswith(";") else tokens(lines[j][:LINE_MAX - 1])
            j += 1
            if u and u[0].lower() == "end":
                ended = True
                break
        items.append(Block(TYPES.index(t[0].lower()), t[1], lines[i:j], ended))
        i = j
    return items


def build_nfx(items):
    out = []
    for it in items:
        out.extend(it.lines if isinstance(it, Block) else [it])
    return "\r\n".join(out).encode("latin-1")


def blocks(items):
    return [it for it in items if isinstance(it, Block)]


def cache_use(items):
    """[(block, bytes)] in file order and the total, as fn_803A3460 allocates them."""
    used = 0
    scratch = False
    out = []

    def alloc(size):
        nonlocal used
        start = used
        used += size
        if size % 4 == 0:
            used += -start % 4
        return used - start

    for b in blocks(items):
        n = alloc(len(b.name) + 1)
        recs = b.records()[0]
        if recs and not scratch:
            scratch = True
            n += sum(alloc(32) for _ in range(SCRATCH))
        if recs:
            n += alloc(8 * len(recs))
            for r in recs:
                n += sum(alloc(s) for s in r.cache_sizes())
        out.append((b, n))
    return out, used


def problems(items):
    """What the loader would get wrong in a file, and the duplicate names (the shipped file has one)."""
    out = []
    dups = []
    seen = {}
    for b in blocks(items):
        where = "%s %s" % (TYPES[b.type], b.name)
        recs, unknown, _ = b.records()
        if not b.ended:
            out.append("%s: no end" % where)
        if len(recs) > SCRATCH:
            out.append("%s: %d records, the scratch table holds %d" % (where, len(recs), SCRATCH))
        for k in unknown:
            out.append("%s: unknown key %s" % (where, k))
        for r in recs:
            if r.error:
                out.append("%s: %s %s: %s" % (where, KEYS[r.key], r.text, r.error))
        if b.name.lower() in seen:
            dups.append("%s: name already used by a %s block, which wins" % (where, TYPES[seen[b.name.lower()]]))
        else:
            seen[b.name.lower()] = b.type
    for it in items:
        if isinstance(it, str) and len(it) > LINE_MAX - 1:
            out.append("line longer than %d bytes: %s..." % (LINE_MAX - 1, it[:40]))
    total = cache_use(items)[1]
    if total > CACHE_SIZE:
        out.append("cache: %d bytes, over %d" % (total, CACHE_SIZE))
    return out, dups


# Commands

def load(index, args):
    if "-f" in args:
        i = args.index("-f")
        if i + 1 >= len(args):
            raise SystemExit(__doc__)
        return open(args[i + 1], "rb").read(), args[:i] + args[i + 2:]
    return read_entry(index, GAME), args


def cmd_list(items, want):
    sizes = dict((id(b), n) for b, n in cache_use(items)[0])
    for b in blocks(items):
        if want and TYPES[b.type] != want.lower():
            continue
        print("%-14s %-32s %3d records  %5d bytes" % (TYPES[b.type], b.name, len(b.records()[0]), sizes[id(b)]))


def cmd_show(items, names):
    byname = {}
    for b in blocks(items):
        byname.setdefault(b.name.lower(), b)
    for name in names:
        b = byname.get(name.lower())
        if b is None:
            raise SystemExit("no block %s" % name)
        recs, unknown, cache = b.records()
        print("%s %s (class %d)" % (TYPES[b.type], b.name, b.type))
        for r in recs:
            print("  %-3d %-14s %-6s %-24s %s" % (r.key, KEYS[r.key], KIND_NAMES[r.kind], r.text, r.show()))
        if cache is not None:
            print("  cache byte %d" % cache)
        for k in unknown:
            print("  skipped: %s" % k)


def cmd_keys():
    for i, (k, kind) in enumerate(zip(KEYS, KINDS)):
        print("%3d  %-14s %s" % (i, k, KIND_NAMES[kind]))


def cmd_check(index, args):
    ok = True
    for name in FILES:
        data = read_entry(index, name)
        items = read_nfx(data)
        same = build_nfx(items) == data
        ok &= same
        print("%-18s %4d blocks, %s" % (name, len(blocks(items)), "rebuilt byte for byte" if same else "REBUILT FILE DIFFERS"))
    data, _ = load(index, args)
    items = read_nfx(data)
    if build_nfx(items) != data:
        print("rebuilt file differs")
        ok = False
    bad, dups = problems(items)
    for p in bad + dups:
        print("  " + p)
    ok &= not bad
    sizes, total = cache_use(items)
    most = max((len(b.records()[0]) for b in blocks(items)), default=0)
    print("%s: %d blocks, at most %d records a block, cache %d of %d bytes, %s" % (
        args[args.index("-f") + 1] if "-f" in args else GAME, len(sizes), most, total, CACHE_SIZE,
        "loads" if not bad else "%d problems" % len(bad)))
    sys.exit(0 if ok else 1)


def main(argv):
    cmd = argv[1] if len(argv) > 1 else ""
    if cmd == "keys":
        cmd_keys()
        return
    if cmd not in ("list", "show", "check"):
        raise SystemExit(__doc__)
    index = read_big_index()
    if cmd == "check":
        cmd_check(index, argv[2:])
        return
    data, rest = load(index, argv[2:])
    items = read_nfx(data)
    if cmd == "list":
        cmd_list(items, rest[0] if rest else None)
    else:
        if not rest:
            raise SystemExit(__doc__)
        cmd_show(items, rest)


if __name__ == "__main__":
    main(sys.argv)
