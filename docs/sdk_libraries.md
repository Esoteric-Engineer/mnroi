# SDK library boundaries (`.text`, GVLE69)

Derived by aligning function sizes and order against the sibling `../ac-decomp` (same Dolphin SDK
build; most sizes match exactly) and by which hardware registers each function touches
(`0xCC00xxxx`: VI 0x2000, DSP/AR 0x5000, DVD 0x6000, SI 0x6400, EXI 0x6800, AI 0x6C00, FIFO 0x8000).
Boundaries are approximate to the function; confirm when you claim something near an edge.

| Range | Library | Notes |
|---|---|---|
| 0x80169134-0x80169164 | os | two tiny functions |
| 0x8016D000-0x8017A5CC | libc: Newlib + fdlibm + libgcc | **Not MSL.** Newlib stdio/string/scanf, fdlibm float math, libgcc 64-bit division. Code source is upstream Newlib/fdlibm/libgcc; names come from CFTKK-Decomp (see below) |
| 0x8017A5CC-0x801814F4 | os | interrupts, memory protection, reset, SRAM, system call, threads |
| 0x801814F4-0x80181708 | exi | |
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
| 0x80196884-? | unknown | not identified |

## Not found yet

AR, ARQ, AX, DSP and CARD have SDK version strings in `.rodata` (after EXI), so their code is
probably past 0x80197000. The end of the SDK range is open-ended; the `0x801B0000` upper bound in
`report-sdk-progress` is a guess.

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
- Version drift: CFTKK's build differs from ours in places (`asinf` 0x22C vs our 0x220, `powf`
  0x730 vs 0x6F4, `sqrtf` 0x10C vs 0xF8, `__kernel_cosf` 0xE8 vs 0xF4; `_vfprintf_r`/`_vfiprintf_r`
  0x1440/0x12F4 vs our 0x17F0/0x167C, so our Newlib is probably newer). Expect to adjust the source.
- Some CFTKK names are project-local rather than upstream (`strround`, `strrev`, `itoa`,
  `memcpyalpha`, `snstd`, `lflush`, `fftoa`). Treat them as labels.
- Not identified: 0x8016EC68 (0x888), 0x8016F4F0 (0x884), 0x80171600 (0x98C). `__kernel_rem_pio2f`
  (CFTKK 0x88C) is a guess for the first. `memcmp`, `stricmp`, `strspn`, `tolower`, `div`, `fopen`,
  `vsnprintf` and `__register_atexit` have no CFTKK counterpart.
- Ruled out as references: every MSL_C-based project (melee, sms, ttyd, pikmin 1/2, tp, tww, prime,
  mkdd, ...). mkdd is useful only for EXI.

### Still under `fn_` names (guesses)

Matched, but the name is only a guess (equal size and neighbour order, no byte-level confirmation), so they keep their `fn_` names until confirmed:

| Address | Guessed name | Confidence |
|---|---|---|
| 0x80178684 | `_cleanup_r` | guess |
| 0x80179138 | `__divdi3` | guess |
