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
| 0x80168770-0x8016B554, 0x8016B6AC-0x8016C514 | sn: SN Systems ProDG debug stub | **Not Dolphin SDK and not game code, but part of the SDK decomp** (decided 2026-09-24; `SN` library in `configure.py`, units `SN/<name>.c`). The debug monitor from SN's ProDG toolchain (the same toolchain explains the GCC-style game code and Newlib libc). It provides the MetroTRK hooks the OS calls (`EnableMetroTRKInterrupts` 0x801688E8; `fn_8016894C` is called from `__start` and patches exception vectors); strings `snPause() : Stopped.`, `*** FS CMD READ ERROR ***`, `Comms Error` at 0x804CFD58+. Two function tables: 0x804CFD00 (command dispatch; `fn_80168CC4` is the `blr` stub for unsupported slots) and 0x804CFCC8 (DB comm replacements 0x8016AB30-0x8016B0AC, same slots as the `DBInitComm`..`DBOpen` table next to it). Function boundaries for the former label-only runs 0x8016900C-0x80169134 and 0x80169164-0x8016B554 were set on 2026-09-24 by reachability (bl/b targets, table pointers, code after terminators), and every piece is now an `fn_` symbol with a queue row. The comm layer 0x8016AB30-0x8016B24C (`SNInitComm`..`SNWrite32`) matches CFTKK-Decomp's SN symbols by size and order; the rest of this SN build differs from CFTKK's and keeps `fn_` names. Hand-written asm blobs keep jump targets as `entry` labels: `lbl_80169CCC` (in `fn_80169BF8`), `lbl_8016A0EC` (in `fn_8016A094`) and the dispatch targets `lbl_8016A8F4`/`lbl_8016A948`/`lbl_8016A95C` (in `fn_8016A7E0`). A second SN run, 0x8016B6AC-0x8016C514, follows the runtime helpers: file I/O and EXI debug comms, compiled C plus an asm DSI handler. `fn_80169134` (writes the PI reset register 0xCC003024 and spins) and `fn_80169150` are in the dispatch table; they were first matched as `Dolphin/os/` and now live in `SN/`. Game code ends at 0x80168768 (last GCC frame-pointer function); 0x80168768-0x80168770 is zero padding |
| 0x8016B554-0x8016B6AC | runtime | `__cvt_fp2unsigned` 0x8016B554 (0x48, 30 callers), then the 4-byte `__shr2u`/`__div2i`/`__shl2i`/`__mod2i`/`__shr2i` (registered as `Dolphin/os/`), `__div2u` 0x8016B5B0, `__mod2u` 0x8016B5B4 and `__va_arg` 0x8016B5B8 (0xF4), in CFTKK's order |
| 0x8016C514-0x8017A5CC | libc: Newlib + fdlibm + libgcc | **Not MSL.** The libm part starts at `__ieee754_acos` 0x8016C514 (see "Boundary fixed" below). Newlib stdio/string/scanf, fdlibm float math, libgcc 64-bit division. Code source is upstream Newlib/fdlibm/libgcc; names come from CFTKK-Decomp (see below) |
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

## Second SDK cluster (0x80400544-0x804114EC, confirmed 2026-09-23, not split or named yet)

More SDK code sits far above the first cluster, inside the game's `.text`. Every `*Init` of AR, ARQ,
AX, DSP and CARD is pinned by its `__XXVersion` load before `OSRegisterVersion`; the rest comes from
exact size/order runs against CFTKK-Decomp and ac-decomp plus callee checks. Full evidence and a
262-row name-proposal table: `docs/sdk_scout_findings.md`.

| Range | Library | Notes |
|---|---|---|
| 0x803FF3B0-0x80400544 | libc (Newlib libm, 2nd cluster) | 8 functions (not 9; sizes sum to 0x1194): `__ieee754_asin` 0x803FF3B0, `__ieee754_exp` 0x803FF60C, `__ieee754_fmod` 0x803FF888, `__ieee754_asinf` 0x803FFBE0, `__ieee754_expf` 0x803FFE0C, `__ieee754_fmodf` 0x80400038, `__ieee754_logf` 0x80400200, `ceilf` 0x80400480. Same fdlibm/Newlib code and MWCC code style as the first-cluster libm; they sit directly in front of the second libc cluster. See "Second-cluster libm" below |
| 0x80400544-0x804009C4 | libc (GCC Newlib, 2nd cluster) | `tolower`, `fclose`, `fprintf`, `printf`, `snprintf`, `vprintf`, `strncat`, `__floatdisf`. GCC-compiled, as in CFTKK |
| 0x804009C4-0x80401EB0 | vm | VM + VMBASE (ARAM virtual memory). `VMInit` 0x804009C4; VMBASE 0x8040130C-0x80401EB0 follows CFTKK-Decomp's VMBASE in order, mostly at equal sizes (boundaries set 2026-09-24). `__VMBASEISIServiceExceptionPrep` starts at 0x80401DFC (the ISI handler's rfi target), not 0x80401E00 |
| 0x80401EB0-0x80401F48 | runtime | `__save_gpr` / `__restore_gpr` |
| 0x80401F48-0x80402130 | os | OSAlloc: `OSAllocFromHeap`, `OSSetCurrentHeap`, `OSInitAlloc`, `OSCreateHeap` |
| 0x80402130-0x80402DC0 | os | OSFatal: `ScreenReport`, `ConfigureVideo`, `OSFatal` 0x80402608, `Halt` |
| 0x80402DC0-0x80404148 | os | OSFont: `GetFontCode` .. `OSGetFontWidth` (`OSGetFontEncode` 0x804030A8) |
| 0x80404148-0x804044C8 | os | OSMessage (3), OSSemaphore (4) |
| 0x804044C8-0x804048CC | mtx | `PSMTXIdentity` .. `C_MTXOrtho` (8) |
| 0x804048CC-0x804063A4 | ar | `ARInit` 0x80404A3C (version string); 9 functions |
| 0x804063A4-0x80406828 | arq | `ARQInit` 0x80406574 (version string); 6 functions incl. `ARQRemoveRequest` |
| 0x80406828-0x8040962C | ax | `AXInit` 0x80406828, `AXInitEx` 0x8040684C (version string); 61 functions. No AXFX/MIX/AXART |
| 0x8040962C-0x8040A190 | dsp | `DSPInit` 0x80409678 (version string); 15 functions |
| 0x8040A190-0x80411208 | card | `CARDInit` 0x8040B004 (version string); 97 functions. CARDRdwr (0x80410C48) and CARDStatEx (0x80410EC8) are linked after CARDUnlock |
| 0x80411208-0x80411408 | gx | GXDisplayList: `GXBeginDisplayList`, `GXEndDisplayList`, `GXCallDisplayList` |
| 0x80411408-0x804114EC | texPalette (unconfirmed) | `TEXGet`, `TEXGetGXTexObjFromPalette` by code shape |

### Second-cluster libm (0x803FF3B0-0x80400544)

Verdict: **all 8 are Newlib/fdlibm libm, i.e. SDK-side libc, not game code and not middleware.** Evidence:

- Bodies match upstream Newlib `e_asin.c`, `e_exp.c`, `e_fmod.c`, `ef_asin.c`, `ef_exp.c`, `ef_fmod.c`,
  `ef_log.c`, `sf_ceil.c` (branch thresholds and, for the double ones, the `.sdata2` constants read back and
  compared: asin pio2/pS/qS tables, exp o_threshold 709.78 / u_threshold -745.13 / invln2 / P1-P5 / twom1000).
  They are the bare `__ieee754_*` bodies with no `w_*` errno wrapper, exactly like the first-cluster
  `__ieee754_atan2f`/`__ieee754_powf`/`__ieee754_sqrtf`, and are called straight from game code (one to three callers each).
- Callees are the first-cluster libm: `fabs` 0x8016E4FC, `fabsf` 0x8016DD5C, `__ieee754_sqrtf` 0x8016D978 and the
  double sqrt `__ieee754_sqrt` 0x8016C790. Nothing in the range calls game code.
- Sizes agree with CFTKK (same Newlib build): `asinf` 0x22C = ours 0x22C, `__ieee754_logf` 0x280 = ours 0x280.
  `ceilf` is 0xD8 there vs our 0xC4, the usual version drift.
- The neighbours are not libm: before 0x803FF3B0 is GCC-style game code (frame pointer r31), after 0x80400544 is the
  second libc cluster. So the libm pieces were linked in between, apart from the first-cluster libm (0x8016xxxx).
- `__ieee754_fmod` 0x803FF888 (0x358) is a **second copy** of the first-cluster `__ieee754_fmod` 0x80177558 (0x35C);
  the copies differ by 4 bytes, so they were not built identically. Keep both.
- No caller-side or hardware hints of middleware; nothing is game code, so no row is `not-sdk`.

Confidence: `__ieee754_asinf` and `__ieee754_logf` are `exact` (CFTKK size plus code shape). The rest are `guess`
(code shape and constants match Newlib, no CFTKK counterpart). The queue rows are `open`, library `libc`. Nothing was
split or renamed. The double sqrt at 0x8016C790 and `__ieee754_asin`'s use of it are worth a look when the first-cluster
libm region gets split. `sdk_scout.py`'s `LIBS` now labels this range `libc`; `queue` now scans the whole second cluster (RANGES starts at 0x803FF3B0), and the rows here were added by hand and survive a refresh.

Between 0x80196884 and 0x803FF3B0, and from 0x804114EC on, the code is game or middleware. The earlier
note that 0x8040250C-0x80404074 was "probably game code" was wrong: it is OSFatal/OSFont.

## Not found yet

- All 13 `<< Dolphin SDK - ... >>` version strings in `main.dol` (OS, SI, DVD, VI, PAD, AI, GX, EXI,
  AR, ARQ, AX, DSP, CARD) are now accounted for, so no other *versioned* SDK library is linked.
- Unversioned SDK pieces could still hide in game `.text`. Checked and ruled out: the chance size runs
  at 0x802420A8, 0x802CBFC4, 0x8042706C, 0x8042DB20, 0x80440490 (GCC frame-pointer game code), the
  inline GX FIFO helpers in game code, and the paired-single block 0x802DF3F0-0x802E013C (no
  reference match; probably engine math). Unresolved: texPalette (0x803FF3B0-0x80400544 is libm, see above).
- `sdk_scout.py` (`RANGES`: 0x80168770-0x80196884 and 0x803FF3B0-0x804114EC) and
  `report-sdk-progress/sdk_remaining.py` both scan the two clusters by default; `sdk_remaining.py` imports
  `RANGES` and `LIBS` from `sdk_scout.py`, so change them there. New second-cluster
  queue rows take their name and confidence from the proposal table in `docs/sdk_scout_findings.md`.

## Beyond `.text`

- `.init` (0x80003100-0x800034A0, 928 bytes) is boot/runtime code: `__start` is split and matched; the six helpers
  are queued (library `init`).
- Data: inside the address span that library data splits already cover there are unsplit gaps
  (2026-09-24: `.data` 7136, `.bss` 2600, `.sbss` 300, `.sdata` 216, `.sdata2` 132 bytes). Being between
  library units, they are probably library data. The second cluster's data (AX, CARD, VM, OSFont, ...) has not
  been located at all. `sdk_remaining.py` reports both; its data figure is a floor, not a total.

## Work queue

`docs/sdk_queue.tsv` lists every unsplit function in the first cluster, plus every function of the
second cluster (0x803FF3B0-0x804114EC: libm/libc, VM, OS, MTX, AR, ARQ, AX, DSP, CARD, GX display lists,
texPalette), with a library, a proposed
name and a confidence. Second-cluster names and evidence come from `docs/sdk_scout_findings.md`; an
`exact` row there needs an equal-size same-name function in CFTKK or ac-decomp (or, for the `*Init`
functions, the `__XXVersion` pointer load), otherwise it is `guess`. See the `decomp-next` skill for how it is used.

Hand-added rows that the `queue` command keeps but would not generate:

- Label-only code (no `type:function` symbol, so the scan can't see it): none left since 2026-09-24. If more turns
  up, add one row per region sized to the region; once function symbols are added, the refresh adds per-function
  rows and the region row can go.
- `.init` (library `init`): `__start` and six helpers at 0x80003100-0x800034A0. The scan only reads `.text`.
  `__check_pad3` 0x800032C0 and `__init_hardware` 0x80003468 match ac-decomp; the other four are inline code in
  ac-decomp's `__start` and keep `fn_` names.
- `known` rows with an `fn_` name: identity settled, but no reference names the function (the `sn` rows, the four
  unnamed `.init` helpers, the second `floor` copy). The loop works them under the `fn_` name.
- `stalled` rows for every registered `NonMatching` function (details in `docs/nonmatching.md`).

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
  0x8017557C (0x188) is a `,` digit-grouping helper for the `'` printf flag (0x200, hard-coded comma, no
  locale); it is neither Newlib nor in CFTKK. Split and matched as `__group_digits` (invented name, nofralloc asm) in `Runtime.PPCEABI.H/__group_digits.c`.
- Boundary fixed: the old `fn_8016D000` (0x64) was the tail of `__ieee754_acosf` 0x8016CE18 (0x24C, Newlib
  ef_acos.c; CFTKK `acosf` 0x250), which dtk had cut at the end of the pad region. It is split out and matched. The old
  label-only region 0x8016B5B0-0x8016CE18 was *not* all libm (2026-09-24): 0x8016B5B0-0x8016B6AC is runtime
  (`__div2u`, `__mod2u`, `__va_arg`), 0x8016B6AC-0x8016C514 is SN, and the libm starts at 0x8016C514 with six double
  functions: `__ieee754_acos` 0x8016C514 (loads pi), `__ieee754_sqrt` 0x8016C790, `ceil` 0x8016C9A4, `cos` 0x8016CAFC,
  a second `s_floor.c` copy 0x8016CBDC (0x15C, `.sdata` constants; kept as `fn_8016CBDC` because `floor` 0x801773E4
  holds the name) and `sin` 0x8016CD38.
- Ruled out as references: every MSL_C-based project (melee, sms, ttyd, pikmin 1/2, tp, tww, prime,
  mkdd, ...). mkdd is useful only for EXI.

### Still under `fn_` names (guesses)

Matched, but the name is only a guess (equal size and neighbour order, no byte-level confirmation), so they keep their `fn_` names until confirmed:

| Address | Guessed name | Confidence |
|---|---|---|
| 0x80178684 | `_cleanup_r` | guess |
| 0x80179138 | `__divdi3` | guess |
