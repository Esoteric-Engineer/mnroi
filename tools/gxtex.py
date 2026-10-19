#!/usr/bin/env python3
"""Decode and encode GameCube textures, read and write TPL files and PNG images, and name a texture
the way Dolphin's texture packs do.

Usage (from repo root):
  python3 tools/gxtex.py list [substring]                Every image of every .tpl: size, format, mipmaps
  python3 tools/gxtex.py decode NAME IMAGE OUT.png       One image of a .tpl in CLASH.BIG (NAME: bundles/wolverine.tpl)
  python3 tools/gxtex.py decode -f FILE IMAGE OUT.png    The same from an extracted or edited file
  python3 tools/gxtex.py set IN OUT IMAGE=PNG ...        Write a copy of the TPL IN with images re-encoded
  python3 tools/gxtex.py hash NAME|-f FILE IMAGE         Dolphin's texture-pack name of an image
  python3 tools/gxtex.py check                           Rebuild every .tpl and re-encode its lossless images

`set` keeps each image's size and format and drops its mipmaps (it sets min and max LOD to 0); the
PNG must have the image's size. It never writes under orig/. As a module, read_tpl() and build_tpl()
turn a TPL into a list of Image objects and back, and decode()/encode() convert pixel data.

TPL, big-endian:
  +0x0  u32 0x0020AF30
  +0x4  u32 image count
  +0x8  u32 offset of the image table: 0xC, or after the data in 12 files of ui/
  image table: per image {u32 image header offset; u32 palette header offset (0 in every file)}
  image header, 0x24 bytes: u16 height; u16 width; u32 format; u32 data offset; u32 wrap s; u32 wrap t;
        u32 min filter; u32 mag filter; f32 LOD bias; u8 edge LOD; u8 min LOD; u8 max LOD; u8 unpacked
  The headers follow the table back to back; each image's data starts 0x20-aligned, in image order,
  every mipmap level from max(w, h) down to max LOD, each level half the last (at least one block).
  With the table after the data, the one image header is at 0xC and its data at 0x40.

Formats (`decode` reads them all; `encode` writes all but C4, C8 and the palette):
  0 I4, 1 I8, 2 IA4, 3 IA8, 4 RGB565, 5 RGB5A3, 6 RGBA8 (AR and GB halves of a 4x4 block),
  8 C4, 9 C8 (indices into a palette of RGB5A3 colours here), 14 CMPR.
  The pixels are stored in blocks (8x8 for 4-bit formats, 8x4 for 8-bit, 4x4 for 16- and 32-bit),
  the blocks row by row. CMPR: 8x8 blocks of four 4x4 DXT1 sub-blocks (top left, top right, bottom
  left, bottom right), each two big-endian RGB565 colours c0, c1 and four bytes of 2-bit indices,
  one byte per row, the leftmost pixel in the top bits. c0 > c1 gives four colours, otherwise three
  and transparent. The TPLs in CLASH.BIG use 14 (3,838 images), 5 (499), 3 (72) and 6 (10).

Dolphin names a texture-pack image tex1_<w>x<h>_<hash>_<format>.png, the hash being XXH64 (seed 0)
of the base level's data. The name was checked in the game for a CMPR image without mipmaps;
Dolphin may add more to the name for a mipmapped or paletted texture.
"""

import os
import struct
import sys
import zlib

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nvbtool import read_big_index, read_entry  # noqa: E402

TPL_MAGIC = 0x0020AF30
I4, I8, IA4, IA8, RGB565, RGB5A3, RGBA8, C4, C8, CMPR = 0, 1, 2, 3, 4, 5, 6, 8, 9, 14
FORMAT_NAMES = {I4: "I4", I8: "I8", IA4: "IA4", IA8: "IA8", RGB565: "RGB565", RGB5A3: "RGB5A3",
                RGBA8: "RGBA8", C4: "C4", C8: "C8", CMPR: "CMPR"}
BLOCK = {I4: (8, 8, 4), I8: (8, 4, 8), IA4: (8, 4, 8), IA8: (4, 4, 16), RGB565: (4, 4, 16),
         RGB5A3: (4, 4, 16), RGBA8: (4, 4, 32), C4: (8, 8, 4), C8: (8, 4, 8), CMPR: (8, 8, 4)}
HEADER = ">HHIIIIIIfBBBB"
M64 = (1 << 64) - 1


def data_size(fmt, w, h):
    bw, bh, bits = BLOCK[fmt]
    return -(-w // bw) * -(-h // bh) * bw * bh * bits // 8


def levels(w, h, count):
    """(width, height) of each of count mipmap levels."""
    out = []
    for _ in range(count):
        out.append((w, h))
        w, h = max(1, w // 2), max(1, h // 2)
    return out


# Colours

def rgb565(c):
    r, g, b = c >> 11 & 31, c >> 5 & 63, c & 31
    return (r << 3 | r >> 2, g << 2 | g >> 4, b << 3 | b >> 2, 255)


def rgb5a3(c):
    if c & 0x8000:
        r, g, b = c >> 10 & 31, c >> 5 & 31, c & 31
        return (r << 3 | r >> 2, g << 3 | g >> 2, b << 3 | b >> 2, 255)
    a = c >> 12 & 7
    return ((c >> 8 & 15) * 17, (c >> 4 & 15) * 17, (c & 15) * 17, a << 5 | a << 2 | a >> 1)


def to_rgb565(p):
    return (p[0] * 31 + 127) // 255 << 11 | (p[1] * 63 + 127) // 255 << 5 | (p[2] * 31 + 127) // 255


def to_rgb5a3(p):
    r, g, b, a = p
    if a >= 224:
        return 0x8000 | r >> 3 << 10 | g >> 3 << 5 | b >> 3
    return a >> 5 << 12 | r >> 4 << 8 | g >> 4 << 4 | b >> 4


def gray(p):
    return (p[0] * 299 + p[1] * 587 + p[2] * 114 + 500) // 1000


def to_colour(fmt, p):
    """The 16-bit value of an RGBA tuple in IA8, RGB565 or RGB5A3 (the palette formats)."""
    if fmt == IA8:
        return p[3] << 8 | gray(p)
    return to_rgb565(p) if fmt == RGB565 else to_rgb5a3(p)


# Pixel data

def blocks(fmt, w, h):
    """Yield (x, y) of every pixel in storage order, including the padding outside the image."""
    bw, bh, _ = BLOCK[fmt]
    for ty in range(0, h, bh):
        for tx in range(0, w, bw):
            for y in range(ty, ty + bh):
                for x in range(tx, tx + bw):
                    yield x, y


def texel_values(fmt, data, w, h):
    """The raw value of every texel in storage order (CMPR excluded)."""
    _, _, bits = BLOCK[fmt]
    n = data_size(fmt, w, h)
    if bits == 4:
        return [v for b in data[:n] for v in (b >> 4, b & 15)]
    if bits == 8:
        return list(data[:n])
    if bits == 16:
        return list(struct.unpack_from(">%dH" % (n // 2), data))
    out = []  # RGBA8: per 4x4 block, 16 AR pairs then 16 GB pairs
    for p in range(0, n, 64):
        for i in range(16):
            out.append(data[p + 2 * i] << 24 | data[p + 2 * i + 1] << 16 | data[p + 32 + 2 * i] << 8 | data[p + 33 + 2 * i])
    return out


def texel(fmt, v, palette):
    if fmt == I4:
        return (v * 17,) * 3 + (255,)
    if fmt == I8:
        return (v, v, v, 255)
    if fmt == IA4:
        return ((v & 15) * 17,) * 3 + ((v >> 4) * 17,)
    if fmt == IA8:
        return (v & 255,) * 3 + (v >> 8,)
    if fmt == RGB565:
        return rgb565(v)
    if fmt == RGB5A3:
        return rgb5a3(v)
    if fmt == RGBA8:
        return (v >> 16 & 255, v >> 8 & 255, v & 255, v >> 24)
    return palette[v] if v < len(palette) else (0, 0, 0, 0)


def decode_cmpr(data, w, h, px):
    p = 0
    for ty in range(0, h, 8):
        for tx in range(0, w, 8):
            for sub in range(4):
                c0, c1 = struct.unpack_from(">HH", data, p)
                a, b = rgb565(c0), rgb565(c1)
                if c0 > c1:
                    pal = (a, b, tuple((2 * a[i] + b[i]) // 3 for i in range(4)),
                           tuple((a[i] + 2 * b[i]) // 3 for i in range(4)))
                else:
                    pal = (a, b, tuple((a[i] + b[i]) // 2 for i in range(4)), (0, 0, 0, 0))
                bx, by = tx + (sub & 1) * 4, ty + (sub >> 1) * 4
                for row in range(4):
                    bits = data[p + 4 + row]
                    for col in range(4):
                        x, y = bx + col, by + row
                        if x < w and y < h:
                            px[y * w + x] = pal[bits >> (6 - 2 * col) & 3]
                p += 8


def decode(fmt, data, w, h, palette=None):
    """RGBA bytes of the base level. palette: RGBA tuples for C4 and C8."""
    px = [(0, 0, 0, 0)] * (w * h)
    if fmt == CMPR:
        decode_cmpr(data, w, h, px)
    elif fmt in BLOCK:
        for (x, y), v in zip(blocks(fmt, w, h), texel_values(fmt, data, w, h)):
            if x < w and y < h:
                px[y * w + x] = texel(fmt, v, palette)
    else:
        raise ValueError("GX format %d is not supported" % fmt)
    return b"".join(map(bytes, px))


def encode_block(pixels):
    """16 RGBA tuples of a 4x4 CMPR sub-block, row by row, as 8 bytes: endpoints on the colours'
    principal axis, four-colour mode. Alpha is ignored."""
    mean = [sum(p[i] for p in pixels) / 16 for i in range(3)]
    d = [[p[i] - mean[i] for i in range(3)] for p in pixels]
    cov = [[sum(v[i] * v[j] for v in d) for j in range(3)] for i in range(3)]
    axis = [1.0, 1.0, 1.0]
    for _ in range(6):
        nxt = [sum(cov[i][j] * axis[j] for j in range(3)) for i in range(3)]
        norm = max(abs(x) for x in nxt) or 1.0
        axis = [x / norm for x in nxt]
    proj = [sum(v[i] * axis[i] for i in range(3)) for v in d]
    lo, hi = min(proj), max(proj)
    if hi - lo < 1e-6:
        lo = hi = 0.0
    ends = [tuple(max(0, min(255, round(mean[i] + axis[i] * t))) for i in range(3)) for t in (lo, hi)]
    a, b = sorted((to_rgb565(ends[0]), to_rgb565(ends[1])), reverse=True)
    if a == b:  # four-colour mode needs c0 > c1
        if a < 0xFFFF:
            a += 1
        else:
            b -= 1
    ca, cb = rgb565(a), rgb565(b)
    pal = (ca, cb, tuple((2 * ca[i] + cb[i]) // 3 for i in range(3)), tuple((ca[i] + 2 * cb[i]) // 3 for i in range(3)))
    out = bytearray(struct.pack(">HH", a, b))
    for row in range(4):
        byte = 0
        for col in range(4):
            p = pixels[row * 4 + col]
            best = min(range(4), key=lambda j: sum((p[i] - pal[j][i]) ** 2 for i in range(3)))
            byte |= best << (6 - 2 * col)
        out.append(byte)
    return bytes(out)


def encode(fmt, rgba, w, h):
    """The base level of an image from RGBA bytes (w * h * 4)."""
    def pixel(x, y):
        i = (min(y, h - 1) * w + min(x, w - 1)) * 4
        return tuple(rgba[i:i + 4])
    if fmt == CMPR:
        out = bytearray()
        for ty in range(0, h, 8):
            for tx in range(0, w, 8):
                for sub in range(4):
                    bx, by = tx + (sub & 1) * 4, ty + (sub >> 1) * 4
                    out += encode_block([pixel(bx + c, by + r) for r in range(4) for c in range(4)])
        return bytes(out)
    if fmt == I4:
        vals = [gray(pixel(x, y)) >> 4 for x, y in blocks(fmt, w, h)]
    elif fmt == I8:
        vals = [gray(pixel(x, y)) for x, y in blocks(fmt, w, h)]
    elif fmt == IA4:
        vals = [pixel(x, y)[3] >> 4 << 4 | gray(pixel(x, y)) >> 4 for x, y in blocks(fmt, w, h)]
    elif fmt in (IA8, RGB565, RGB5A3):
        vals = [to_colour(fmt, pixel(x, y)) for x, y in blocks(fmt, w, h)]
    elif fmt == RGBA8:
        out = bytearray()
        pos = list(blocks(fmt, w, h))
        for b in range(0, len(pos), 16):
            ps = [pixel(*xy) for xy in pos[b:b + 16]]
            out += bytes(c for p in ps for c in (p[3], p[0]))
            out += bytes(c for p in ps for c in (p[1], p[2]))
        return bytes(out)
    else:
        raise ValueError("cannot encode GX format %d" % fmt)
    bits = BLOCK[fmt][2]
    if bits == 4:
        return bytes(vals[i] << 4 | vals[i + 1] for i in range(0, len(vals), 2))
    if bits == 8:
        return bytes(vals)
    return struct.pack(">%dH" % len(vals), *vals)


# TPL

class Image:
    def __init__(self, header, data, pad=b""):
        self.header = list(header)  # the 13 fields of HEADER; the data offset is set by build_tpl
        self.data = data            # every mipmap level
        self.pad = pad              # the bytes before the data when they are not zero (two ui/ fonts)

    height = property(lambda self: self.header[0])
    width = property(lambda self: self.header[1])
    format = property(lambda self: self.header[2])
    mipmaps = property(lambda self: self.header[11] + 1)

    def size(self):
        return sum(data_size(self.format, w, h) for w, h in levels(self.width, self.height, self.mipmaps))

    def base(self):
        return self.data[:data_size(self.format, self.width, self.height)]


def read_tpl(data):
    """(images, table offset) of a TPL file. An image whose data runs past the end of the file
    keeps what there is (two files of 64 bytes have a header and no data)."""
    magic, count, table = struct.unpack_from(">III", data, 0)
    if magic != TPL_MAGIC:
        raise ValueError("not a TPL file")
    images = []
    end = 0xC + 8 * count + 0x24 * count if table == 0xC else 0x30
    for i in range(count):
        head, palette = struct.unpack_from(">II", data, table + 8 * i)
        if palette:
            raise ValueError("image %d has a palette" % i)
        h = struct.unpack_from(HEADER, data, head)
        im = Image(h, b"", data[end:h[3]].strip(b"\0") and data[end:h[3]])
        im.data = data[h[3]:h[3] + im.size()]
        end = h[3] + len(im.data)
        images.append(im)
    return images, table


def build_tpl(images, table_last=False):
    """A TPL file laid out as the game's are (see the module docstring)."""
    n = len(images)
    if table_last and n != 1:
        raise ValueError("a table after the data holds one image")
    heads = [0xC] if table_last else [0xC + 8 * n + 0x24 * i for i in range(n)]
    pos = heads[-1] + 0x24
    out = bytearray()
    offsets = []
    for im in images:
        pos += -pos % 0x20
        offsets.append(pos)
        pos += len(im.data)
    table = pos if table_last else 0xC
    out = bytearray(struct.pack(">III", TPL_MAGIC, n, table))
    if not table_last:
        out += b"".join(struct.pack(">II", h, 0) for h in heads)
    for im, off in zip(images, offsets):
        out += struct.pack(HEADER, *im.header[:3], off, *im.header[4:])
    for im, off in zip(images, offsets):
        gap = off - len(out)
        out += (im.pad if len(im.pad) == gap else bytes(gap)) + im.data
    if table_last:
        out += struct.pack(">II", heads[0], 0)
    return bytes(out)


# PNG

def write_png(w, h, rgba):
    def chunk(kind, body):
        return struct.pack(">I", len(body)) + kind + body + struct.pack(">I", zlib.crc32(kind + body))
    rows = b"".join(b"\0" + rgba[y * w * 4:(y + 1) * w * 4] for y in range(h))
    return (b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 6, 0, 0, 0)) +
            chunk(b"IDAT", zlib.compress(rows, 9)) + chunk(b"IEND", b""))


def read_png(data):
    """(width, height, RGBA bytes) of an 8-bit, non-interlaced PNG of any colour type."""
    if data[:8] != b"\x89PNG\r\n\x1a\n":
        raise ValueError("not a PNG file")
    p, idat, plte, trns = 8, b"", b"", b""
    while p < len(data):
        n, kind = struct.unpack_from(">I4s", data, p)
        body = data[p + 8:p + 8 + n]
        if kind == b"IHDR":
            w, h, depth, ctype, _, _, interlace = struct.unpack(">IIBBBBB", body)
        elif kind == b"PLTE":
            plte = body
        elif kind == b"tRNS":
            trns = body
        elif kind == b"IDAT":
            idat += body
        p += 12 + n
    if depth != 8 or interlace:
        raise ValueError("only 8-bit, non-interlaced PNGs are read")
    chans = {0: 1, 2: 3, 3: 1, 4: 2, 6: 4}[ctype]
    raw, stride = zlib.decompress(idat), w * chans
    rows, prev = [], bytearray(stride)
    for y in range(h):
        f, line = raw[y * (stride + 1)], bytearray(raw[y * (stride + 1) + 1:(y + 1) * (stride + 1)])
        for i in range(stride):
            a = line[i - chans] if i >= chans else 0
            b, c = prev[i], prev[i - chans] if i >= chans else 0
            if f == 1:
                line[i] = (line[i] + a) & 255
            elif f == 2:
                line[i] = (line[i] + b) & 255
            elif f == 3:
                line[i] = (line[i] + (a + b) // 2) & 255
            elif f == 4:
                pa, pb, pc = abs(b - c), abs(a - c), abs(a + b - 2 * c)
                line[i] = (line[i] + (a if pa <= pb and pa <= pc else b if pb <= pc else c)) & 255
        rows.append(line)
        prev = line
    out = bytearray()
    for line in rows:
        for x in range(w):
            v = line[x * chans:(x + 1) * chans]
            if ctype == 0:
                out += bytes((v[0], v[0], v[0], 255))
            elif ctype == 2:
                out += v + b"\xff"
            elif ctype == 3:
                out += plte[3 * v[0]:3 * v[0] + 3] + bytes((trns[v[0]] if v[0] < len(trns) else 255,))
            elif ctype == 4:
                out += bytes((v[0], v[0], v[0], v[1]))
            else:
                out += v
    return w, h, bytes(out)


# Dolphin's texture hash

_P1, _P2, _P3, _P4, _P5 = (11400714785074694791, 14029467366897019727, 1609587929392839161,
                           9650029242287828579, 2870177450012600261)


def _rol(x, r):
    return (x << r | x >> (64 - r)) & M64


def _round(acc, v):
    return _rol((acc + v * _P2) & M64, 31) * _P1 & M64


def xxh64(d):
    n, p = len(d), 0
    if n >= 32:
        v = [(_P1 + _P2) & M64, _P2, 0, -_P1 & M64]
        while p <= n - 32:
            for k in range(4):
                v[k] = _round(v[k], struct.unpack_from("<Q", d, p)[0])
                p += 8
        h = (_rol(v[0], 1) + _rol(v[1], 7) + _rol(v[2], 12) + _rol(v[3], 18)) & M64
        for k in range(4):
            h = ((h ^ _round(0, v[k])) * _P1 + _P4) & M64
    else:
        h = _P5
    h = (h + n) & M64
    while p + 8 <= n:
        h ^= _round(0, struct.unpack_from("<Q", d, p)[0])
        h = (_rol(h, 27) * _P1 + _P4) & M64
        p += 8
    if p + 4 <= n:
        h ^= struct.unpack_from("<I", d, p)[0] * _P1 & M64
        h = (_rol(h, 23) * _P2 + _P3) & M64
        p += 4
    while p < n:
        h ^= d[p] * _P5 & M64
        h = _rol(h, 11) * _P1 & M64
        p += 1
    h ^= h >> 33
    h = h * _P2 & M64
    h ^= h >> 29
    h = h * _P3 & M64
    return h ^ h >> 32


def dolphin_name(image):
    return "tex1_%dx%d_%016x_%d" % (image.width, image.height, xxh64(image.base()), image.format)


# Commands

def tpl_entries(index, sub=None):
    names = sorted(n for n in index if n.endswith(".tpl"))
    return [n for n in names if sub.lower() in n] if sub else names


def load(index, args):
    """The TPL bytes named by args (NAME or -f FILE) and the rest of args."""
    if args and args[0] == "-f" and len(args) > 1:
        return open(args[1], "rb").read(), args[2:]
    if args:
        name = args[0].lower()
        if name not in index and name + ".tpl" in index:
            name += ".tpl"
        if name not in index:
            raise SystemExit("no %s in CLASH.BIG (python3 tools/gxtex.py list)" % args[0])
        return read_entry(index, name), args[1:]
    raise SystemExit(__doc__)


def cmd_list(index, sub):
    for name in tpl_entries(index, sub):
        images, _ = read_tpl(read_entry(index, name))
        for i, im in enumerate(images):
            print("%-48s %2d %4dx%-4d %-6s mipmaps %d" % (name, i, im.width, im.height,
                                                          FORMAT_NAMES.get(im.format, im.format), im.mipmaps))


def cmd_set(src, dst, edits):
    if dst.replace("\\", "/").startswith("orig/"):
        raise SystemExit("refusing to write under orig/: %s" % dst)
    data = open(src, "rb").read()
    images, table = read_tpl(data)
    for edit in edits:
        if "=" not in edit:
            raise SystemExit(__doc__)
        i, path = edit.split("=", 1)
        im = images[int(i, 0)]
        w, h, rgba = read_png(open(path, "rb").read())
        if (w, h) != (im.width, im.height):
            raise SystemExit("%s is %dx%d, image %s is %dx%d" % (path, w, h, i, im.width, im.height))
        im.data = encode(im.format, rgba, w, h)
        im.header[10] = im.header[11] = 0
    open(dst, "wb").write(build_tpl(images, table != 0xC))
    print("wrote %s" % dst)


def cmd_check(index):
    ok = True
    # XXH64 of the empty string, and Dolphin's name for Daredevil's body texture (seen in the game)
    if xxh64(b"") != 0xEF46DB3751D8E999:
        print("xxh64 is wrong")
        ok = False
    dd = read_tpl(read_entry(index, "bundles/daredevil.tpl"))[0][0]
    if dolphin_name(dd) != "tex1_256x256_7963c218a4ea694d_14":
        print("dolphin_name of bundles/daredevil.tpl image 0 is %s" % dolphin_name(dd))
        ok = False
    entries = tpl_entries(index)
    count = lossless = empty = 0
    for name in entries:
        data = read_entry(index, name)
        try:
            images, table = read_tpl(data)
        except (ValueError, struct.error) as e:
            print("%-48s %s" % (name, e))
            ok = False
            continue
        if build_tpl(images, table != 0xC) != data:
            print("%-48s rebuilt file differs" % name)
            ok = False
        for i, im in enumerate(images):
            count += 1
            if len(im.data) < im.size():
                empty += 1
                continue
            if im.format == CMPR:
                continue
            for lw, lh in levels(im.width, im.height, im.mipmaps)[:1]:
                if encode(im.format, decode(im.format, im.base(), lw, lh), lw, lh) != im.base():
                    print("%-48s image %d (%s) does not re-encode" % (name, i, FORMAT_NAMES[im.format]))
                    ok = False
            lossless += 1
    print("%d TPL files, %d images (%d re-encoded, %d with no data), %s" % (
        len(entries), count, lossless, empty, "all rebuilt byte for byte" if ok else "INVALID"))
    sys.exit(0 if ok else 1)


def main(argv):
    cmd = argv[1] if len(argv) > 1 else ""
    if cmd == "set" and len(argv) >= 5:
        cmd_set(argv[2], argv[3], argv[4:])
        return
    if cmd not in ("list", "decode", "hash", "check"):
        raise SystemExit(__doc__)
    index = read_big_index()
    if cmd == "check":
        cmd_check(index)
    elif cmd == "list":
        cmd_list(index, argv[2] if len(argv) > 2 else None)
    else:
        data, rest = load(index, argv[2:])
        if len(rest) != (2 if cmd == "decode" else 1):
            raise SystemExit(__doc__)
        im = read_tpl(data)[0][int(rest[0], 0)]
        if cmd == "hash":
            print(dolphin_name(im))
            return
        if rest[1].replace("\\", "/").startswith("orig/"):
            raise SystemExit("refusing to write under orig/: %s" % rest[1])
        open(rest[1], "wb").write(write_png(im.width, im.height, decode(im.format, im.base(), im.width, im.height)))


if __name__ == "__main__":
    main(sys.argv)
