#!/usr/bin/env python3
"""Print an APT UI movie with its ActionScript turned into statements (a rough decompiler).

Usage (from repo root):
  python3 tools/aptdecomp.py dump NAME                     One movie of CLASH.BIG (NAME: screens/clashCharSelect)
  python3 tools/aptdecomp.py dump -f FILE.apt FILE.const   The same from extracted or edited files
  python3 tools/aptdecomp.py check                         Decompile every movie in CLASH.BIG
"""

import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import aptdump as A  # noqa: E402


class Sym(str):
    """An expression (as opposed to a string literal)."""


def lit(v):
    if isinstance(v, Sym):
        return v
    if isinstance(v, str):
        return Sym(repr(v))
    if isinstance(v, bool):
        return Sym("true" if v else "false")
    if isinstance(v, float):
        return Sym("%g" % v)
    return Sym(str(v))


def name_of(v):
    """A popped name operand as an identifier where possible."""
    if isinstance(v, Sym):
        return "[" + v + "]"
    return str(v)


def member(obj, m):
    if isinstance(m, Sym) or not isinstance(m, str) or not m.replace("_", "a").isalnum() or m[:1].isdigit():
        return Sym("%s[%s]" % (obj, lit(m)))
    return Sym("%s.%s" % (obj, m))


def var(n):
    if isinstance(n, Sym):
        return Sym("eval(%s)" % n)
    return Sym(str(n))


BIN = {0x0A: "+", 0x0B: "-", 0x0C: "*", 0x0D: "/", 0x0E: "==", 0x0F: "<", 0x10: "&&", 0x11: "||",
       0x13: "eq", 0x21: "add", 0x29: "lt", 0x3F: "%", 0x47: "+", 0x48: "<", 0x49: "==", 0x60: "&",
       0x61: "|", 0x62: "^", 0x63: "<<", 0x64: ">>", 0x65: ">>>", 0x66: "===", 0x67: ">", 0x68: "gt",
       0x54: "instanceof"}
SIMPLE = {0x04: "nextFrame()", 0x05: "prevFrame()", 0x06: "play()", 0x07: "stop()", 0x09: "stopAllSounds()"}


class Decomp:
    def __init__(self, r, consts, out):
        self.r, self.consts, self.out = r, consts, out
        self.pool = []
        self.unknown = 0

    def cval(self, idx):
        k, v = self.consts[idx]
        if k == "pool":
            return self.cval(self.pool[v])
        if k == "reg":
            return Sym("r%d" % v)
        if k == "none":
            return Sym("none")
        return v

    def pconst(self, i):
        return self.cval(self.pool[i])

    def run(self, p, end=None, ind="    "):
        r, d = self.r, self.r.d
        st = []
        emit = lambda at, s: self.out.append("%s%06X  %s" % (ind, at, s))

        def pop():
            return st.pop() if st else Sym("<?>")

        def args():
            n = pop()
            try:
                n = int(n)
            except (TypeError, ValueError):
                return "<%s args>" % n
            return ", ".join(lit(pop()) for _ in range(n))

        while end is None or p < end:
            at = p
            op = d[p]
            p += 1
            if op == 0x00:
                if end is None:
                    break
                continue
            if op == 0x96:
                p = A.al4(p)
                n, ptr = r.u32(p), r.u32(p + 4)
                p += 8
                for i in range(n):
                    st.append(self.cval(r.u32(ptr + 4 * i)))
            elif op == 0x88:
                p = A.al4(p)
                n, ptr = r.u32(p), r.u32(p + 4)
                p += 8
                self.pool = [r.u32(ptr + 4 * i) for i in range(n)]
            elif op == 0x1C:
                st.append(var(pop()))
            elif op == 0x1D:
                v, n = pop(), pop()
                emit(at, "%s = %s" % (name_of(n), lit(v)))
            elif op == 0x3C:
                v, n = pop(), pop()
                emit(at, "var %s = %s" % (name_of(n), lit(v)))
            elif op == 0x41:
                emit(at, "var %s" % name_of(pop()))
            elif op == 0x4E:
                m, o = pop(), pop()
                st.append(member(lit(o), m))
            elif op == 0x4F:
                v, m, o = pop(), pop(), pop()
                emit(at, "%s = %s" % (member(lit(o), m), lit(v)))
            elif op in (0x3D, 0x5C, 0x5B):
                n = pop()
                e = Sym("%s(%s)" % (name_of(n), args()))
                if op == 0x5B:
                    emit(at, e)
                else:
                    st.append(e)
            elif op in (0x52, 0x5E, 0x5D):
                m, o = pop(), pop()
                e = Sym("%s(%s)" % (member(lit(o), m), args()))
                if op == 0x5D:
                    emit(at, e)
                else:
                    st.append(e)
            elif op == 0x40:
                n = pop()
                st.append(Sym("new %s(%s)" % (name_of(n), args())))
            elif op == 0x53:
                m, o = pop(), pop()
                st.append(Sym("new %s(%s)" % (member(lit(o), m), args())))
            elif op == 0x42:
                st.append(Sym("[" + args() + "]"))
            elif op == 0x43:
                n = int(pop())
                items = []
                for _ in range(n):
                    v, k = pop(), pop()
                    items.append("%s: %s" % (name_of(k), lit(v)))
                st.append(Sym("{" + ", ".join(items) + "}"))
            elif op == 0x17:
                v = pop()
                if isinstance(v, Sym) and ("(" in v):
                    emit(at, v)
            elif op in BIN:
                b, a = pop(), pop()
                st.append(Sym("(%s %s %s)" % (lit(a), BIN[op], lit(b))))
            elif op == 0x12:
                st.append(Sym("!%s" % lit(pop())))
            elif op == 0x50:
                st.append(Sym("(%s + 1)" % lit(pop())))
            elif op == 0x51:
                st.append(Sym("(%s - 1)" % lit(pop())))
            elif op == 0x4C:
                v = pop()
                st.append(v)
                st.append(v)
            elif op == 0x4D:
                a, b = pop(), pop()
                st.append(a)
                st.append(b)
            elif op in (0x4A, 0x4B, 0x18, 0x44, 0x45):
                f = {0x4A: "Number", 0x4B: "String", 0x18: "int", 0x44: "typeof", 0x45: "targetPath"}[op]
                st.append(Sym("%s(%s)" % (f, lit(pop()))))
            elif op in (0x14, 0x33):
                st.append(Sym("%s(%s)" % ("length" if op == 0x14 else "chr", lit(pop()))))
            elif op == 0x2B:
                o, c = pop(), pop()
                st.append(Sym("cast(%s, %s)" % (lit(o), lit(c))))
            elif op == 0x69:
                sup, sub = pop(), pop()
                emit(at, "%s extends %s" % (lit(sub), lit(sup)))
            elif op == 0x2C:
                c = pop()
                emit(at, "%s implements %s" % (lit(c), args()))
            elif op == 0x3E:
                emit(at, "return %s" % lit(pop()))
            elif op == 0x26:
                emit(at, "trace(%s)" % lit(pop()))
            elif op == 0x3A:
                m, o = pop(), pop()
                st.append(Sym("delete(%s)" % member(lit(o), m)))
            elif op == 0x3B:
                st.append(Sym("delete(%s)" % name_of(pop())))
            elif op == 0x87:
                p = A.al4(p)
                n = r.i32(p)
                p += 4
                v = pop()
                emit(at, "r%d = %s" % (n, lit(v)))
                st.append(Sym("r%d" % n))
            elif op in (0x99, 0x9D, 0xB8):
                p = A.al4(p)
                off = r.i32(p)
                p += 4
                if op == 0x99:
                    emit(at, "goto %06X" % (p + off))
                elif op == 0x9D:
                    emit(at, "if (%s) goto %06X" % (lit(pop()), p + off))
                else:
                    emit(at, "if (!%s) goto %06X" % (lit(pop()), p + off))
            elif op in (0x9B, 0x8E):
                p = A.al4(p)
                if op == 0x9B:
                    fname, nargs, ap, size = r.s(r.u32(p)), r.u32(p + 4), r.u32(p + 8), r.i32(p + 12)
                    p += 24
                    an = [str(r.s(r.u32(ap + 4 * i))) for i in range(nargs)]
                else:
                    fname, nargs = r.s(r.u32(p)), r.u32(p + 4)
                    ap, size = r.u32(p + 12), r.i32(p + 16)
                    p += 28
                    an = ["r%d:%s" % (r.u32(ap + 8 * i), r.s(r.u32(ap + 8 * i + 4))) for i in range(nargs)]
                self.out.append("%s%06X  function %s(%s) {" % (ind, at, fname or "", ", ".join(an)))
                self.run(p, p + size, ind + "    ")
                self.out.append("%s}" % ind)
                p += size
                if not fname:
                    st.append(Sym("<function@%06X>" % at))
            elif op in SIMPLE:
                emit(at, SIMPLE[op])
            elif op == 0x81:
                p = A.al4(p)
                emit(at, "gotoFrame(%d)" % r.i32(p))
                p += 4
            elif op == 0x8C:
                p = A.al4(p)
                emit(at, "gotoLabel(%r)" % r.s(r.u32(p)))
                p += 4
            elif op == 0x8B:
                p = A.al4(p)
                emit(at, "setTarget(%r)" % r.s(r.u32(p)))
                p += 4
            elif op == 0x9F:
                p = A.al4(p)
                fl = r.i32(p)
                p += 4
                emit(at, "gotoFrame2(%s, play=%d)" % (lit(pop()), fl))
            elif op == 0x94:
                p = A.al4(p)
                p += 4
                emit(at, "with (%s)" % lit(pop()))
            elif op == 0x83:
                p = A.al4(p)
                emit(at, "getURL(%r, %r)" % (r.s(r.u32(p)), r.s(r.u32(p + 4))))
                p += 8
            elif op == 0x9A:
                t, u = pop(), pop()
                emit(at, "getURL2(%s, %s)" % (lit(u), lit(t)))
            elif op == 0x22:
                i, t = pop(), pop()
                st.append(Sym("getProperty(%s, %s)" % (lit(t), lit(i))))
            elif op == 0x23:
                v, i, t = pop(), pop(), pop()
                emit(at, "setProperty(%s, %s, %s)" % (lit(t), lit(i), lit(v)))
            elif op == 0x24:
                dp, t, s = pop(), pop(), pop()
                emit(at, "duplicateMovieClip(%s, %s, %s)" % (lit(s), lit(t), lit(dp)))
            elif op == 0x25:
                emit(at, "removeMovieClip(%s)" % lit(pop()))
            elif op == 0x20:
                emit(at, "setTarget2(%s)" % lit(pop()))
            elif op in (0x46, 0x55):
                st.append(Sym("enumerate(%s)" % lit(pop())))
            elif op == 0x30:
                st.append(Sym("random(%s)" % lit(pop())))
            elif op == 0x34:
                st.append(Sym("getTimer()"))
            elif op == 0x56:
                st.append(Sym("this"))
            elif op == 0x58:
                st.append(Sym("_global"))
            elif op == 0x59:
                st.append(0)
            elif op == 0x5A:
                st.append(1)
            elif op == 0x73:
                st.append(True)
            elif op == 0x74:
                st.append(False)
            elif op == 0x75:
                st.append(Sym("null"))
            elif op == 0x76:
                st.append(Sym("undefined"))
            elif op == 0x70:
                st.append(member(Sym("this"), pop()))
            elif op == 0x71:
                st.append(member(Sym("_global"), pop()))
            elif op == 0xA1:
                p = A.al4(p)
                st.append(r.s(r.u32(p)))
                p += 4
            elif op == 0xA4:
                p = A.al4(p)
                st.append(var(r.s(r.u32(p))))
                p += 4
            elif op == 0xA5:
                p = A.al4(p)
                st.append(member(lit(pop()), r.s(r.u32(p))))
                p += 4
            elif op == 0xA6:
                p = A.al4(p)
                emit(at, "%s = %s" % (r.s(r.u32(p)), lit(pop())))
                p += 4
            elif op == 0xA7:
                p = A.al4(p)
                v, o = pop(), pop()
                emit(at, "%s = %s" % (member(lit(o), r.s(r.u32(p))), lit(v)))
                p += 4
            elif op == 0xA2:
                st.append(self.pconst(d[p]))
                p += 1
            elif op == 0xA3:
                st.append(self.pconst(r.u16(p)))
                p += 2
            elif op == 0xAE:
                st.append(var(self.pconst(d[p])))
                p += 1
            elif op == 0xAF:
                st.append(member(lit(pop()), self.pconst(d[p])))
                p += 1
            elif op in (0xB0, 0xB1):
                e = Sym("%s(%s)" % (name_of(self.pconst(d[p])), args()))
                p += 1
                if op == 0xB0:
                    emit(at, e)
                else:
                    st.append(e)
            elif op in (0xB2, 0xB3):
                o = pop()
                e = Sym("%s(%s)" % (member(lit(o), self.pconst(d[p])), args()))
                p += 1
                if op == 0xB2:
                    emit(at, e)
                else:
                    st.append(e)
            elif op == 0xB4:
                p = A.al4(p)
                st.append(r.f32(p))
                p += 4
            elif op == 0xB5:
                st.append(d[p])
                p += 1
            elif op == 0xB6:
                st.append(r.u16(p))
                p += 2
            elif op == 0xB7:
                p = A.al4(p)
                st.append(r.u32(p))
                p += 4
            elif op == 0xB9:
                st.append(Sym("r%d" % d[p]))
                p += 1
            else:
                emit(at, "<%s>" % A.OPS.get(op, "op %02X" % op))
                self.unknown += 1
        return p


if __name__ == "__main__":
    A.main(sys.argv, Decomp, "decompiled")
