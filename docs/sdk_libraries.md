# SDK library boundaries (`.text`, GVLE69)

Derived by aligning function sizes and order against the sibling `../ac-decomp` (same Dolphin SDK
build; most sizes match exactly) and by which hardware registers each function touches
(`0xCC00xxxx`: VI 0x2000, DSP/AR 0x5000, DVD 0x6000, SI 0x6400, EXI 0x6800, AI 0x6C00, FIFO 0x8000).
Boundaries are approximate to the function; confirm when you claim something near an edge.

The sibling `../CFTKK-Decomp` (`config/GQ4E78/symbols.txt`) names *every* SDK library in this
build (OS incl. OSExec/OSFont, DVD, VI, AI, AR/ARQ/AX/DSP/CARD, GX incl. getters, EXI), not just libc,
and its sizes match ours far more often than ac-decomp's (which is a newer SDK and lacks the older
functions). Align against it first, then read the ac-decomp source for the body.

| Range | Library | Notes |
|---|---|---|
| 0x80169134-0x80169164 | os | two tiny functions |
| 0x8016D000-0x8017A5CC | libc: Newlib + fdlibm + libgcc | **Not MSL.** The libm part starts before 0x8016D000 (see "Boundary problem" below). Newlib stdio/string/scanf, fdlibm float math, libgcc 64-bit division. Code source is upstream Newlib/fdlibm/libgcc; names come from CFTKK-Decomp (see below) |
| 0x8017A5CC-0x80181708 | os | interrupts, memory protection, reset, SRAM, system call, threads, mutexes (`OSLockMutex`..`__OSUnlockAllMutex` at `0x801814F4-0x80181708`; the queue once had these as exi) |
| 0x80181708-0x80183070 | si | |
| 0x80183070-0x8018315C | db | |
| 0x8018315C-0x80187B3C | dvd | includes `DVDLow*` |
| 0x80187B3C-0x80189C10 | vi | |
| 0x80189C10-0x8018B624 | pad | registered (`Dolphin/pad/`, first unit `PADSetSamplingCallback`); starts at `UpdateOrigin` |
| 0x8018B624-0x8018BF08 | ai | |
| 0x8018BF08-0x80193E54 | gx | starts at the GX attribute code, before the first split (0x8018C820) |
| 0x80193E54-0x80195440 | exi | `SetExiInterruptMask` through `EXIUnlock`; ac-decomp and doldecomp/mkdd have the source. Earlier labelled libc by mistake |
| 0x80195440-0x80195E04 | exi | `EXIGetID`, `InitializeUART`, `WriteUARTN` (the exi library is in two clusters) |
| 0x80195E04-0x80196194 | odenotstub | `DBOpen`/`DBClose`/`DBWrite`/`DBRead`/`DBQueryData` |
| 0x80196194-0x80196884 | OdemuExi2 | |
| 0x80196884-0x80197000+ | game code | **Not SDK.** The first cluster of SDK code ends at 0x80196884 (end of `DBGEXIImm`). Everything after it is GCC-style C++ (frame pointer `mr r31, r1`, `stmw r30`) calling unnamed functions at 0x8042xxxx/0x8046xxxx and called from game code below 0x80169000: a 0x300-byte camera-like class (ctor `0x80196884`, factory `0x801969CC`, setters, update `0x80196CE4`). The old `0x80197000` upper bound in `sdk_scout.py` / `report-sdk-progress` was arbitrary and is now `0x80196884` |

## Second SDK cluster (found 2026-09-23, not split or named yet)

More SDK code sits far above the first cluster, inside the game's `.text`. It was found by aligning
function sizes and order against CFTKK-Decomp (`config/GQ4E78/symbols.txt`, same SDK build for these
libraries): long exact runs, e.g. `0x80404BB0` (0x17F4) = `__ARChecksize`, and a 60-function AX run.
Not confirmed by callees yet; treat the ranges as approximate.

| Range | Library | First functions |
|---|---|---|
| 0x804048CC-0x80404BB0 | ar | `ARRegisterDMACallback` 0x804048CC, `ARGetDMAStatus` 0x80404910, `ARStartDMA` 0x8040494C, `ARInit` 0x80404A3C, `ARGetSize` 0x80404B00, `__ARHandler` 0x80404B08, `__ARClearInterrupt` 0x80404B80, `__ARChecksize` 0x80404BB0 |
| 0x804063A4-0x80406740 | arq | `__ARQServiceQueueLo` 0x804063A4, `__ARQCallbackHack` 0x804064A4, `__ARQInterruptServiceRoutine` 0x804064A8, `ARQInit` 0x80406574, `ARQPostRequest` 0x804065E4 |
| 0x80406828-0x8040962C | ax | `AXInit` 0x80406828 ... `__AXGetCurrentProfile` 0x804095E4 |
| 0x8040962C-0x8040A190 | dsp | `DSPCheckMailToDSP` 0x8040962C ... `__DSP_remove_task` 0x8040A0FC |
| 0x8040A190-0x80410C48 | card | `__CARDDefaultApiCallback` 0x8040A190 ... `DoneCallback` 0x80410924 |

The 0x8040250C-0x80404074 functions that touch VI/PI/EXI registers are not from this run of matches
(the sizes do not line up with CFTKK); they are probably game code.

## Not found yet

Nothing further is known about SDK code outside the two clusters above; `.rodata` version strings for
the libraries linked into the game are the way to check for more.

## Work queue

`docs/sdk_queue.tsv` lists every unsplit function in the range above with a library, a proposed
name and a confidence. See the `decomp-next` skill for how it is used.

## libc reference (research, 2026-09-21)

- Our libc is Newlib (BSD libc), not MSL C, built with GC/1.2.5n. That is why ac-decomp and other
  MSL-based decomps can't name it (e.g. our `strcat` is 0x90, MSL's is 0x2C).
- Best name source: [LivewireCB/CFTKK-Decomp](https://github.com/LivewireCB/CFTKK-Decomp)
  (GQ4E78, CC0, symbols and splits only, no C). It carries the same prebuilt Newlib libc,
  fdlibm-style math and libgcc. All our already-named libc functions have CFTKK's sizes, and the
  order matches for the stdio, string and libgcc runs. Use its `config/GQ4E78/symbols.txt` for
  names and layout, and upstream Newlib/fdlibm/libgcc source for the code.
- "Exact" in the queue means equal size and matching neighbour order, not byte-verified.
- Version drift: CFTKK's build differs from ours in places (`atan2f` 0x238 vs our `__ieee754_atan2f`
  0x220, `powf` 0x730 vs our 0x6F4, `sqrtf` 0x10C vs our 0xF8, `__kernel_cosf` 0xE8 vs our 0xF4,
  `__kernel_tanf` 0x224 vs our 0x214, `_mbtowc_r` 0x31C vs our 0x32C; `_vfprintf_r`/`_vfiprintf_r`
  0x1440/0x12F4 vs our 0x17F0/0x167C). Expect to adjust the source. The direction of the drift is not
  established: our stdio layer uses the old signatures (`fp->_data`, `_read_r(fp->_data, ...)`),
  `_mbtowc_r` compares `_current_locale` against `C-SJIS`/`C-EUCJP`/`C-JIS` (Newlib 1.14-1.16 era) and our
  `gmtime_r`/`mktime` are the old tzcode-style ones, so the stdio/time parts look *older* than current
  `newlib-cygwin`. Compare against old-Newlib shapes, not the modern source (modern `gmtime_r` uses
  civil_from_days; ours loops over years). The atan2f/powf/sqrtf size gaps are the missing `w_*` wrappers:
  ours are the bare `__ieee754_*` bodies, called directly by game code.
- Some CFTKK names are project-local rather than upstream (`strround`, `strrev`, `itoa`,
  `memcpyalpha`, `snstd`, `lflush`, `fftoa`). Treat them as labels.
- `memcmp`, `stricmp`, `strspn`, `tolower`, `div`, `fopen`, `vsnprintf` and `__register_atexit` have no
  CFTKK counterpart.
- Identified without CFTKK (fdlibm/Newlib code shape, 2026-09-23): the *double* libm pieces
  (`__kernel_cos` 0x8016DFF8, `__ieee754_rem_pio2` 0x8016E198, `__kernel_rem_pio2` 0x8016EC68 (double sibling of
  the float one at 0x8016F4F0), `scalbn` 0x8016FE3C, `copysign` 0x8016FF90, `floor` 0x801773E4,
  `__ieee754_fmod` 0x80177558, `__ieee754_log` 0x801778B4, `__ieee754_log10` 0x80177BB0), `bsearch`
  0x8017123C, `qsort` 0x80171600, `strncmp` 0x80172904, the time functions (`asctime_r` 0x80172CEC,
  `gmtime_r` 0x80172DA0, `validate_structure` 0x80172FF8, `mktime` 0x8017334C; the `asctime`/`gmtime`
  wrappers are the matched `fn_80172CC4`/`fn_80172D78`), `strtod` 0x8017703C and the FILE trio
  `__sfp` 0x80178424 / `_fopen_r` 0x80178568 / `_fseek_r` 0x801786AC (`__sflags` 0x80178F54 and `_open_r`
  0x80178E48 are the matched `fn_` units next to them). All `guess` in the queue: no CFTKK size to compare.
- printf: `_vfprintf_r` 0x80173D8C (float variant, calls `fftoa` 0x801736F8, `__ieee754_log10`, `fmod`,
  `floor`) and `_vfiprintf_r` 0x801757D8 (integer variant). `_vfwrite` is a CFTKK-local buffered writer, two
  copies (0x80173BE0 and 0x80175704); the second is named `_vfiwrite` here to keep names unique.
  0x8017557C (0x188) is a `,` digit-grouping helper used by both bodies; it is neither Newlib nor in CFTKK,
  so it stays `unidentified`.
- Boundary problem: 0x8016D000 (0x64) is not a function. It is the tail of a 0x24C function that starts at
  0x8016CE18 (asin/acos family: p/q polynomial plus the sqrt at 0x8016D978), inside the unsplit
  `pad_01_8016B5AC_text` region (0x8016B5AC-0x8016D000), which is more libm (e.g. the `floor`-like callee at
  0x8016CBDC). The libm start is earlier than 0x8016D000; split that region before naming.
- Ruled out as references: every MSL_C-based project (melee, sms, ttyd, pikmin 1/2, tp, tww, prime,
  mkdd, ...). mkdd is useful only for EXI.

### Still under `fn_` names (guesses)

Matched, but the name is only a guess (equal size and neighbour order, no byte-level confirmation), so they keep their `fn_` names until confirmed:

| Address | Guessed name | Confidence |
|---|---|---|
| 0x80178684 | `_cleanup_r` | guess |
| 0x80179138 | `__divdi3` | guess |
