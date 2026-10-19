#!/usr/bin/env python3
"""Print an APT UI movie: its characters, frames and ActionScript bytecode.

Usage (from repo root):
  python3 tools/aptdump.py dump NAME                     One movie of CLASH.BIG (NAME: screens/clashCharSelect)
  python3 tools/aptdump.py dump -f FILE.apt FILE.const   The same from extracted or edited files
  python3 tools/aptdump.py check                         Disassemble every movie in CLASH.BIG

tools/aptdecomp.py prints the same with the bytecode turned into statements, and tools/aptpatch.py
edits a movie. A movie is the .apt and .const of a nested archive (tools/nbig.py); the .geo and
.gsh beside them are its shapes and images (tools/gshtool.py). The layout below is EA's APT as
OpenSAGE documents it for the PC games, with big-endian words; the opcodes are Flash's, plus EA's.

.const:
  +0x0  "Apt constant file\\x1a\\0\\0"
  +0x14 u32 offset of the root movie in the .apt
  +0x18 u32 item count
  +0x1C u32 item offset (0x20)
  items {u32 type; u32 value}, then the strings. Types: 1 string (value: its offset in the
  .const), 3 none, 4 register, 5 boolean, 6 float (the bits), 7 int, 8 an index into the constant
  pool of the running action block (how a PushData pushes a string)

.apt: "Apt Data:7\\x1a\\0" ("Apt Data:6" in 32 movies). Every pointer is an absolute file offset.
  movie, at the offset the .const gives:
        u32 type (9); u32 0x09876543; u32 frame count; ptr frames; ptr; u32 character count;
        ptr characters; u32 screen width; u32 screen height; u32; u32 import count; ptr imports
        {ptr movie name; ptr name; u32 character; ptr}; u32 export count; ptr exports {ptr name;
        u32 character}; u32
  character: u32 type; u32 0x09876543; then by type
        1 SHAPE      f32 bounds[4]; u32 geometry (its .geo record)
        2 EDITTEXT   f32 bounds[4]; u32 font; u32 alignment; u32 colour; f32 height; u32 read only;
                     u32 multiline; u32 word wrap; ptr text; ptr variable
        3 FONT       ptr name; u32 glyph count; ...
        4 BUTTON     u32; f32 bounds[4]; u32 triangles; u32 vertices; ...; u32 record count; ptr;
                     u32 action count; ptr actions {u32 flags; ptr action block}
        5 SPRITE     u32 frame count; ptr frames
        7 IMAGE      u32 texture: the name of a .gsh entry
        9 MOVIE      character 0 is the movie itself
  frame: {u32 item count; ptr items}; an item is a pointer to {u32 type; ...}:
        1 action     ptr action block
        2 label      ptr name; u32 flags; u32 frame
        3 place      u32 flags; s32 depth; s32 character; f32 matrix[6]; u32 colour; u32; f32 ratio;
                     ptr name; s32 clip depth; ptr clip actions {u32 count; ptr records
                     {u32 flags; u32 flags; ptr action block}}
        4 remove     s32 depth
        5 background u32 colour
        8 init action u32 sprite; ptr action block
  action block: bytecode, one opcode byte each, ended by 0x00. An operand that is a pointer or a
        32-bit value is 4-aligned after the opcode. ConstantPool and PushData take {u32 count;
        ptr u32 const item indices}; DefineFunction and DefineFunction2 hold their body inline.
"""

import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import nbig  # noqa: E402
from nvbtool import read_big_index  # noqa: E402

CONST_MAGIC = b"Apt constant file\x1a\0\0"

OPS = {
    0x00: "End", 0x04: "NextFrame", 0x05: "PrevFrame", 0x06: "Play", 0x07: "Stop", 0x08: "ToggleQuality",
    0x09: "StopSounds", 0x0A: "Add", 0x0B: "Subtract", 0x0C: "Multiply", 0x0D: "Divide", 0x0E: "Equals",
    0x0F: "LessThan", 0x10: "And", 0x11: "Or", 0x12: "Not", 0x13: "StringEquals", 0x14: "StringLength",
    0x15: "SubString", 0x17: "Pop", 0x18: "ToInteger", 0x1C: "GetVariable", 0x1D: "SetVariable",
    0x20: "SetTarget2", 0x21: "StringConcat", 0x22: "GetProperty", 0x23: "SetProperty", 0x24: "CloneSprite",
    0x25: "RemoveSprite", 0x26: "Trace", 0x27: "StartDrag", 0x28: "StopDrag", 0x29: "StringCompare",
    0x2A: "Throw", 0x2B: "CastOp", 0x2C: "ImplementsOp", 0x30: "Random", 0x31: "MBLength", 0x32: "Ord",
    0x33: "Chr", 0x34: "GetTime", 0x35: "MBSubString", 0x36: "MBOrd", 0x37: "MBChr", 0x3A: "Delete",
    0x3B: "Delete2", 0x3C: "DefineLocal", 0x3D: "CallFunction", 0x3E: "Return", 0x3F: "Modulo",
    0x40: "NewObject", 0x41: "Var", 0x42: "InitArray", 0x43: "InitObject", 0x44: "TypeOf", 0x45: "TargetPath",
    0x46: "Enumerate", 0x47: "NewAdd", 0x48: "NewLessThan", 0x49: "NewEquals", 0x4A: "ToNumber",
    0x4B: "ToString", 0x4C: "Dup", 0x4D: "Swap", 0x4E: "GetMember", 0x4F: "SetMember", 0x50: "Increment",
    0x51: "Decrement", 0x52: "CallMethod", 0x53: "NewMethod", 0x54: "InstanceOf", 0x55: "Enumerate2",
    0x56: "EA_PushThis", 0x58: "EA_PushGlobal", 0x59: "EA_PushZero", 0x5A: "EA_PushOne",
    0x5B: "EA_CallFuncPop", 0x5C: "EA_CallFunc", 0x5D: "EA_CallMethodPop", 0x5E: "EA_CallMethod",
    0x60: "BitAnd", 0x61: "BitOr", 0x62: "BitXor", 0x63: "Shl", 0x64: "Shr", 0x65: "UShr",
    0x66: "StrictEquals", 0x67: "Greater", 0x68: "StringGreater", 0x69: "Extends",
    0x70: "EA_PushThisVar", 0x71: "EA_PushGlobalVar", 0x72: "EA_ZeroVar", 0x73: "EA_PushTrue",
    0x74: "EA_PushFalse", 0x75: "EA_PushNull", 0x76: "EA_PushUndefined", 0x77: "TraceStart",
    0x81: "GotoFrame", 0x83: "GetUrl", 0x87: "SetRegister", 0x88: "ConstantPool", 0x8A: "WaitForFrame",
    0x8B: "SetTarget", 0x8C: "GotoLabel", 0x8D: "WaitForFrameExpr", 0x8E: "DefineFunction2", 0x8F: "Try",
    0x94: "With", 0x96: "PushData", 0x99: "BranchAlways", 0x9A: "GetUrl2", 0x9B: "DefineFunction",
    0x9D: "BranchIfTrue", 0x9E: "CallFrame", 0x9F: "GotoFrame2",
    0xA1: "EA_PushString", 0xA2: "EA_PushConstByte", 0xA3: "EA_PushConstWord", 0xA4: "EA_GetStringVar",
    0xA5: "EA_GetStringMember", 0xA6: "EA_SetStringVar", 0xA7: "EA_SetStringMember",
    0xAE: "EA_PushValueOfVar", 0xAF: "EA_GetNamedMember", 0xB0: "EA_CallNamedFuncPop",
    0xB1: "EA_CallNamedFunc", 0xB2: "EA_CallNamedMethodPop", 0xB3: "EA_CallNamedMethod",
    0xB4: "EA_PushFloat", 0xB5: "EA_PushByte", 0xB6: "EA_PushShort", 0xB7: "EA_PushLong",
    0xB8: "EA_BranchIfFalse", 0xB9: "EA_PushRegister",
}

STR_OPS = (0x8B, 0x8C, 0xA1, 0xA4, 0xA5, 0xA6, 0xA7)  # a pointer to a string
I32_OPS = (0x81, 0x87, 0x94, 0x9F)
BR_OPS = (0x99, 0x9D, 0xB8)                          # a signed offset from the next opcode
CONST_BYTE_OPS = (0xA2, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3)  # a constant pool index

CHAR_TYPES = {1: "SHAPE", 2: "EDITTEXT", 3: "FONT", 4: "BUTTON", 5: "SPRITE", 6: "SOUND", 7: "IMAGE",
              8: "MORPH", 9: "MOVIE", 10: "STATICTEXT", 11: "NONE", 12: "VIDEO"}


def al4(p):
    return (p + 3) & ~3


class R:
    def __init__(self, d):
        self.d = d

    def u32(self, o):
        return struct.unpack_from(">I", self.d, o)[0]

    def i32(self, o):
        return struct.unpack_from(">i", self.d, o)[0]

    def f32(self, o):
        return struct.unpack_from(">f", self.d, o)[0]

    def u16(self, o):
        return struct.unpack_from(">H", self.d, o)[0]

    def s(self, o):
        if o == 0:
            return None
        return self.d[o:self.d.index(b"\0", o)].decode("latin-1")


def read_const(d):
    """(root movie offset, [(kind, value)]) of a .const file."""
    if d[:len(CONST_MAGIC)] != CONST_MAGIC:
        raise ValueError("not an APT constant file: %r" % d[:20])
    r = R(d)
    movie, count, items = r.u32(0x14), r.u32(0x18), r.u32(0x1C)
    consts = []
    for i in range(count):
        t, v = r.u32(items + 8 * i), r.u32(items + 8 * i + 4)
        if t == 1:
            consts.append(("str", r.s(v)))
        elif t == 5:
            consts.append(("bool", bool(v)))
        elif t == 6:
            consts.append(("float", struct.unpack(">f", struct.pack(">I", v))[0]))
        elif t == 7:
            consts.append(("int", v - (1 << 32) if v & 0x80000000 else v))
        elif t == 8:
            consts.append(("pool", v))
        elif t == 4:
            consts.append(("reg", v))
        elif t == 3:
            consts.append(("none", v))
        else:
            consts.append(("t%d" % t, v))
    return movie, consts


class Dis:
    """Disassembles action blocks into out, one line per instruction."""

    def __init__(self, r, consts, out):
        self.r, self.consts, self.out = r, consts, out
        self.pool = []
        self.unknown = 0

    def const(self, i):
        idx = self.pool[i] if i < len(self.pool) else None
        if idx is None or idx >= len(self.consts):
            return "<pool %d?>" % i
        return self.raw_const(idx) if self.consts[idx][0] != "pool" else "<pool->pool>"

    def raw_const(self, idx):
        if idx >= len(self.consts):
            return "<const %d?>" % idx
        k, v = self.consts[idx]
        if k == "pool":
            return self.const(v)
        if k == "reg":
            return "r%d" % v
        if k == "none":
            return "none"
        return repr(v) if k in ("str", "int", "bool") else "%g" % v if k == "float" else "%s:%s" % (k, v)

    def run(self, p, end=None, ind="      "):
        """Disassemble from p to End (or to end, for a function body); the address after it."""
        r, d = self.r, self.r.d
        while end is None or p < end:
            at = p
            op = d[p]
            p += 1
            name = OPS.get(op, "?%02X" % op)
            arg = ""
            if op in STR_OPS:
                p = al4(p)
                arg = repr(r.s(r.u32(p)))
                p += 4
            elif op in I32_OPS:
                p = al4(p)
                arg = str(r.i32(p))
                p += 4
            elif op in BR_OPS:
                p = al4(p) + 4
                arg = "-> %X" % (p + r.i32(p - 4))
            elif op in CONST_BYTE_OPS:
                arg = self.const(d[p])
                p += 1
            elif op == 0xA3:
                arg = self.const(r.u16(p))
                p += 2
            elif op == 0xB4:
                p = al4(p)
                arg = "%g" % r.f32(p)
                p += 4
            elif op == 0xB5:
                arg = str(d[p])
                p += 1
            elif op == 0xB6:
                arg = str(r.u16(p))
                p += 2
            elif op == 0xB7:
                p = al4(p)
                arg = str(r.u32(p))
                p += 4
            elif op == 0xB9:
                arg = "r%d" % d[p]
                p += 1
            elif op == 0x83:
                p = al4(p)
                arg = "%r %r" % (r.s(r.u32(p)), r.s(r.u32(p + 4)))
                p += 8
            elif op == 0x88:
                p = al4(p)
                n, ptr = r.u32(p), r.u32(p + 4)
                p += 8
                self.pool = [r.u32(ptr + 4 * i) for i in range(n)]
                arg = "%d constants @%X" % (n, ptr)
            elif op == 0x96:
                p = al4(p)
                n, ptr = r.u32(p), r.u32(p + 4)
                p += 8
                arg = ", ".join(self.raw_const(r.u32(ptr + 4 * i)) for i in range(n))
            elif op == 0x9B:
                p = al4(p)
                fname, nargs, args, size = r.s(r.u32(p)), r.u32(p + 4), r.u32(p + 8), r.i32(p + 12)
                p += 24
                an = [r.s(r.u32(args + 4 * i)) for i in range(nargs)]
                self.out.append("%s%06X  DefineFunction %r(%s) size=%d {" % (ind, at, fname, ", ".join(map(str, an)), size))
                self.run(p, p + size, ind + "    ")
                self.out.append("%s}" % ind)
                p += size
                continue
            elif op == 0x8E:
                p = al4(p)
                fname, nargs = r.s(r.u32(p)), r.u32(p + 4)
                nregs, flags = d[p + 8], int.from_bytes(d[p + 9:p + 12], "big")
                args, size = r.u32(p + 12), r.i32(p + 16)
                p += 28
                an = ["r%d:%s" % (r.u32(args + 8 * i), r.s(r.u32(args + 8 * i + 4))) for i in range(nargs)]
                self.out.append("%s%06X  DefineFunction2 %r(%s) regs=%d flags=%X size=%d {" % (
                    ind, at, fname, ", ".join(an), nregs, flags, size))
                self.run(p, p + size, ind + "    ")
                self.out.append("%s}" % ind)
                p += size
                continue
            self.out.append("%s%06X  %s %s" % (ind, at, name, arg))
            if op == 0x00 and end is None:
                break
            if name.startswith("?"):
                self.out.append("%s  !! unknown opcode, stopping" % ind)
                self.unknown += 1
                break
        return p


def dump_frames(r, walker, out, nframes, frames, ind="  "):
    for f in range(nframes):
        n, items = r.u32(frames + 8 * f), r.u32(frames + 8 * f + 4)
        out.append("%sframe %d: %d items @%X" % (ind, f, n, items))
        for i in range(n):
            it = r.u32(items + 4 * i)
            t = r.u32(it)
            if t == 1:
                out.append("%s  ACTION @%X" % (ind, r.u32(it + 4)))
                walker.run(r.u32(it + 4), None, ind + "      ")
            elif t == 2:
                out.append("%s  FRAMELABEL %r flags=%X frame=%d" % (ind, r.s(r.u32(it + 4)), r.u32(it + 8), r.u32(it + 12)))
            elif t == 3:
                flags, depth, ch = r.u32(it + 4), r.i32(it + 8), r.i32(it + 12)
                m = [r.f32(it + 16 + 4 * k) for k in range(6)]
                color, ratio = r.u32(it + 40), r.f32(it + 48)
                name, clip, poa = r.s(r.u32(it + 52)), r.i32(it + 56), r.u32(it + 60)
                out.append("%s  PLACE @%X flags=%X depth=%d char=%d xform=[%s] color=%08X ratio=%g name=%r clipdepth=%d actions=%X" % (
                    ind, it, flags, depth, ch, " ".join("%g" % x for x in m), color, ratio, name, clip, poa))
                if poa:
                    cnt, recs = r.u32(poa), r.u32(poa + 4)
                    for k in range(cnt):
                        fl, fl2, ab = r.u32(recs + 12 * k), r.u32(recs + 12 * k + 4), r.u32(recs + 12 * k + 8)
                        out.append("%s    clip action flags=%X/%X @%X" % (ind, fl, fl2, ab))
                        walker.run(ab, None, ind + "        ")
            elif t == 4:
                out.append("%s  REMOVE depth=%d" % (ind, r.i32(it + 4)))
            elif t == 5:
                out.append("%s  BGCOLOR %08X" % (ind, r.u32(it + 4)))
            elif t == 8:
                out.append("%s  INITACTION sprite=%d @%X" % (ind, r.u32(it + 4), r.u32(it + 8)))
                walker.run(r.u32(it + 8), None, ind + "      ")
            else:
                out.append("%s  item type %d @%X" % (ind, t, it))


def dump(apt, const, walker_class=Dis):
    """(lines, walker) of a movie, the action blocks run through walker_class."""
    if apt[:9] != b"Apt Data:":
        raise ValueError("not an APT movie: %r" % apt[:12])
    m, consts = read_const(const)
    r = R(apt)
    out = []
    walker = walker_class(r, consts, out)
    out.append("header %r  movie @%X  %d constants" % (apt[:12], m, len(consts)))
    t, sig = r.u32(m), r.u32(m + 4)
    nframes, frames = r.u32(m + 8), r.u32(m + 12)
    nchars, chars = r.u32(m + 20), r.u32(m + 24)
    sx, sy, unk = r.u32(m + 28), r.u32(m + 32), r.u32(m + 36)
    nimp, imps, nexp, exps = r.u32(m + 40), r.u32(m + 44), r.u32(m + 48), r.u32(m + 52)
    if (t, sig) != (9, 0x09876543):
        raise ValueError("no movie at 0x%X" % m)
    out.append("MOVIE frames=%d chars=%d screen=%dx%d unk=%X imports=%d exports=%d" % (
        nframes, nchars, sx, sy, unk, nimp, nexp))
    for i in range(nimp):
        o = imps + 16 * i
        out.append("  import movie=%r name=%r char=%d" % (r.s(r.u32(o)), r.s(r.u32(o + 4)), r.u32(o + 8)))
    for i in range(nexp):
        o = exps + 8 * i
        out.append("  export name=%r char=%d" % (r.s(r.u32(o)), r.u32(o + 4)))
    for i in range(nchars):
        c = r.u32(chars + 4 * i)
        if c == 0:
            continue
        ct = r.u32(c)
        if i == 0:
            out.append("char 0 @%X = the movie; frames:" % c)
            dump_frames(r, walker, out, nframes, frames)
        elif ct == 5:
            nf, fr = r.u32(c + 8), r.u32(c + 12)
            out.append("char %d @%X SPRITE frames=%d" % (i, c, nf))
            dump_frames(r, walker, out, nf, fr)
        elif ct == 2:
            b = ["%g" % r.f32(c + 8 + 4 * k) for k in range(4)]
            font, align, color, h = r.u32(c + 24), r.u32(c + 28), r.u32(c + 32), r.f32(c + 36)
            ro, ml, ww = r.u32(c + 40), r.u32(c + 44), r.u32(c + 48)
            out.append("char %d @%X EDITTEXT bounds=[%s] font=%d align=%d color=%08X h=%g ro=%d ml=%d ww=%d text=%r var=%r" % (
                i, c, " ".join(b), font, align, color, h, ro, ml, ww, r.s(r.u32(c + 52)), r.s(r.u32(c + 56))))
        elif ct == 1:
            b = ["%g" % r.f32(c + 8 + 4 * k) for k in range(4)]
            out.append("char %d @%X SHAPE bounds=[%s] geometry=%d" % (i, c, " ".join(b), r.u32(c + 24)))
        elif ct == 7:
            out.append("char %d @%X IMAGE texture=%d" % (i, c, r.u32(c + 8)))
        elif ct == 3:
            out.append("char %d @%X FONT name=%r glyphs=%d" % (i, c, r.s(r.u32(c + 8)), r.u32(c + 12)))
        elif ct == 4:
            b = ["%g" % r.f32(c + 12 + 4 * k) for k in range(4)]
            nrec, nact, acts = r.u32(c + 44), r.u32(c + 52), r.u32(c + 56)
            out.append("char %d @%X BUTTON bounds=[%s] records=%d actions=%d" % (i, c, " ".join(b), nrec, nact))
            for k in range(nact):
                o = acts + 8 * k
                out.append("    button action flags=%X @%X" % (r.u32(o), r.u32(o + 4)))
                walker.run(r.u32(o + 4), None, "        ")
        else:
            out.append("char %d @%X %s" % (i, c, CHAR_TYPES.get(ct, "?%d" % ct)))
    return out, walker


def movie_files(files):
    """(apt, const) bytes of a nested archive's files."""
    get = lambda ext: next(d for n, d in files if n.lower().endswith(ext))
    return get(".apt"), get(".const")


def load(args):
    """(apt, const) bytes named by args: NAME, or -f FILE.apt FILE.const."""
    if len(args) == 3 and args[0] == "-f":
        return open(args[1], "rb").read(), open(args[2], "rb").read()
    if len(args) == 1:
        return movie_files(nbig.get(read_big_index(), args[0]))
    raise SystemExit(__doc__)


def movies():
    """Yield (archive name, apt, const) for every movie in CLASH.BIG."""
    from nvbtool import read_entry
    index = read_big_index()
    for name in nbig.archives(index):
        yield (name,) + movie_files(nbig.load(read_entry(index, name)))


def check(walker_class, what):
    ok = True
    count = lines = 0
    for name, apt, const in movies():
        try:
            out, walker = dump(apt, const, walker_class)
            if walker.unknown:
                raise ValueError("%d unknown opcodes" % walker.unknown)
            lines += len(out)
        except (ValueError, IndexError, struct.error) as e:
            print("%-56s %s" % (name, e))
            ok = False
        count += 1
    print("%d movies, %d lines, %s" % (count, lines, ("all " + what) if ok else "INVALID"))
    sys.exit(0 if ok else 1)


def main(argv, walker_class=Dis, what="disassembled"):
    if len(argv) == 2 and argv[1] == "check":
        check(walker_class, what)
    if len(argv) < 3 or argv[1] != "dump":
        raise SystemExit(sys.modules[walker_class.__module__].__doc__)
    print("\n".join(dump(*load(argv[2:]), walker_class)[0]))


if __name__ == "__main__":
    main(sys.argv)
