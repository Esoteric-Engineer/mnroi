# SDK scout findings: the second SDK cluster (2026-09-23)

Research for "where is the rest of the Dolphin SDK" (AR, ARQ, AX, DSP, CARD and anything else).
Nothing here is renamed or split yet; the proposals table at the end is for a later agent to apply
to `config/GVLE69/symbols.txt` and `docs/sdk_queue.tsv`. Library boundaries are summarised in
`docs/sdk_libraries.md`.

## Summary

All five libraries are found, in one contiguous block of `.text` at **0x804048CC-0x80411208**. The
block is part of a larger non-game region, **0x80400544-0x804114EC** (about 0x10FA8 bytes, ~260
functions), that also holds a second GCC Newlib cluster, the VM (ARAM virtual memory) library, more
OS (OSAlloc, OSFatal, OSFont, OSMessage, OSSemaphore), MTX, the GX display-list unit and probably
texPalette. Everything between 0x80196884 and 0x80400544 is game or middleware code.

| Library | Found | Range | Functions | Confidence |
|---|---|---|---|---|
| AR | yes | 0x804048CC-0x804063A4 | 9 | high: `ARInit` loads `__ARVersion`; AR registers 0xCC0050xx |
| ARQ | yes | 0x804063A4-0x80406828 | 6 | high: `ARQInit` loads `__ARQVersion` |
| AX | yes | 0x80406828-0x8040962C | 61 | high: `AXInitEx` loads `__AXVersion`; 33+8+9-function exact CFTKK runs |
| DSP | yes | 0x8040962C-0x8040A190 | 15 | high: `DSPInit` loads `__DSPVersion`; DSP mailbox registers; 23-function exact run into CARD |
| CARD | yes | 0x8040A190-0x80411208 | 97 | high: `CARDInit` loads `__CARDVersion` and calls `DSPInit`; EXI callers |

## Method and evidence

### 1. Version strings and the `*Init` functions (hard evidence)

`OSRegisterVersion` (0x8017B3C0) takes a pointer to the `<< Dolphin SDK - ... >>` string. Each
library keeps that pointer in `.sdata` (`__XXVersion`), loaded via r13 (`_SDA_BASE_` = 0x806734E0).
Scanning `.text` for loads of those `.sdata` words gives each library's init function directly.

| Library | String (.data) | Build date | Pointer (.sdata) | Loaded in | Next call |
|---|---|---|---|---|---|
| OS | 0x804D0680 | Nov 10 2004 | 0x8066C3B8 | (first cluster) | |
| SI | 0x804D1B78 | Apr 17 2003 | 0x8066C3E8 | (first cluster) | |
| DVD | 0x804D2130 | Sep 16 2003 | 0x8066C410 | (first cluster) | |
| VI | 0x804D2880 | Apr 17 2003 | 0x8066C488 | (first cluster) | |
| PAD | 0x804D2C50 | Aug 6 2003 | 0x8066C498 | (first cluster) | |
| AI | 0x804D2CA8 | Apr 17 2003 | 0x8066C4B8 | (first cluster) | |
| GX | 0x804D3340 | Nov 10 2004 | 0x8066C518 | (first cluster) | |
| EXI | 0x804D3880 | Apr 17 2003 | 0x8066C520 | (first cluster) | |
| **AR** | 0x804EEEF8 | Apr 17 2003 | 0x8066CEC8 | 0x80404A70 in `fn_80404A3C` (0xC4) = `ARInit` | `OSRegisterVersion` |
| **ARQ** | 0x804EEF40 | Apr 17 2003 | 0x8066CED0 | 0x80406590 in `fn_80406574` (0x70) = `ARQInit` | `OSRegisterVersion` |
| **AX** | 0x804EEF88 | Jul 29 2003 | 0x8066CED8 | 0x80406860 in `fn_8040684C` (0x4C) = `AXInitEx` | `OSRegisterVersion`, `__AXAllocInit`, `__AXVPBInit` |
| **DSP** | 0x804F29C0 | Apr 17 2003 | 0x8066CEE8 | 0x804096B0 in `fn_80409678` (0xC4) = `DSPInit` | `OSRegisterVersion` |
| **CARD** | 0x804F2B80 | Apr 17 2003 | 0x8066CEF0 | 0x8040B044 in `fn_8040B004` (0xAC) = `CARDInit` | `OSRegisterVersion`, `DSPInit`, `OSInitAlarm` |

These are the only 13 `<< Dolphin SDK` strings in `main.dol`, so no other versioned SDK library is
linked. Libraries that do not register a version (VM, MTX, OSAlloc/OSFont/OSFatal, texPalette,
GX display lists) had to be found by alignment and callees.

The data layout backs up the link order: the second cluster's strings sit in a separate `.data`
block (0x804EEEF8+) and its `.sdata` pointers start at 0x8066CEC8, straight after `__OSCurrHeap`
(0x8066CEA8, written by `OSInitAlloc` at 0x80402054), which is also in the second cluster.

### 2. Hardware fingerprints

A scan of every function above 0x80196884 for `lis rX,0xCC00/0xCC01` + load/store found:

- DSP/AR registers (0xCC0050xx) only in 0x80404910-0x8040990C: `ARGetDMAStatus`, `ARStartDMA`,
  `ARInit`, `__ARHandler`, `__ARClearInterrupt`, `__ARGetInterruptStatus`, `__ARChecksize` and the
  DSP mailbox functions, `DSPInit`, `DSPAssertTask`, `__DSPHandler`. Nothing else in the game
  touches 0xCC005000.
- VI/PI in 0x8040250C-0x80404074: `ConfigureVideo`, `OSFatal`, and the OSFont functions that inline
  the `OSGetFontEncode` check of VI register 0x6E. The old note calling these "probably game code" was
  wrong.
- `__CARDFormatRegionAsync` (0x8040D69C) loads the 0xCC00 base once (a VI register); not examined
  further.
- FIFO (0xCC008000) writes in small game functions at 0x801AF2A4, 0x802137xx, 0x80216978..,
  0x80224CFC.., 0x8022A8D4..: these are inlined `GXPosition*`/`GXColor*` helpers emitted out of line
  in game code (GCC frame pointer), not SDK.
- `GXCallDisplayList` (0x80411398) writes the FIFO directly.

CARD's EXI traffic goes through the already-named `EXILock` / `EXISelect` / `EXIImmEx` / `EXIDma` /
`EXIDeselect` / `EXIUnlock`, called from `Retry`, `__CARDStart`, `__CARDReadSegment`,
`__CARDWritePage` and `__CARDEraseSector`.

### 3. Size/order alignment against CFTKK and ac-decomp

A search for runs of consecutive equal function sizes between our `.text` and each reference
(`config/GQ4E78/symbols.txt`, `config/GAFE01_00/symbols.txt`) gives these exact runs in the
second cluster, against CFTKK unless noted:

| Our range | Length | Reference names |
|---|---|---|
| 0x80400CEC-0x8040130C | 12 | `__VMGetPageToReplace` .. `__VMAllocARAMToVirtualLUT` |
| 0x80402DC0-0x80403430 | 4 | `GetFontCode` .. `ReadFont` |
| 0x80404148-0x8040434C | 3 | `OSInitMessageQueue` .. `OSReceiveMessage` (ac-decomp too) |
| 0x804048CC-0x80404B08 | 5 | `ARRegisterDMACallback` .. |
| 0x80404B08-0x80406740 | 9 | `__ARHandler` .. `ARQPostRequest` |
| 0x80406828-0x80407958 | 33 | `AXInit` .. `AXSetMode` |
| 0x80407960-0x80408128 | 8 | `__AXOutNewFrame` .. `__AXOutQuit` |
| 0x80408128-0x80408FC8 | 9 | `__AXGetStudio` .. `__AXGetPBs` |
| 0x8040962C-0x8040A694 | 23 | `DSPCheckMailToDSP` .. `__CARDReadStatus` |
| 0x8040A190-0x8040B004 | 16 | `__CARDDefaultApiCallback` .. `__CARDEraseSector` (ac-decomp) |
| 0x8040B4C8-0x8040CA44 | 16 | `__CARDGetFatBlock` .. `CARDCheckExAsync` (both) |
| 0x8040CA44-0x8040DCF4 | 11 | `CARDCheck` .. `__CARDFormatRegionAsync` (ac-decomp) |
| 0x8040F9A0-0x80410C48 | 7 | .. `__CARDUnlock`, `InitCallback`, `DoneCallback` |

Where a size did not match, the name was settled by callees (e.g. each 0x48 CARD sync wrapper calls
its `...Async` function then `__CARDSync`). All 227 `exact` rows have an equal size in a reference
and sit in the same neighbour order; the 35 `guess` rows are named from callees/position only.

Four-function runs elsewhere (0x802420A8 "VI", 0x802CBFC4 "GXGetTexObj*", 0x80440490 "GXLoadPosMtxIndx",
0x8042706C "DBPrintf/PSMTXCopy", 0x8042DB20 "GXSetScissor", 0x8044BD90 "PAD*", 0x8045F6D4 "PSMTXMultVec")
are chance size matches: those functions use the GCC frame pointer (`mr r31,r1`) and call game code.

## Second cluster layout (link order)

| Range | Library / unit | Fns | Notes |
|---|---|---|---|
| 0x803FF3B0-0x80400544 | unclassified | 9 | no frame pointer, call `fabs`/`fabsf`/`__ieee754_sqrtf` and 0x8016C790 (unsplit libm region); called only from game code. Not matched by any reference; could be libm pieces or game math. Before 0x803FF3B0 is GCC frame-pointer game code |
| 0x80400544-0x804009C4 | libc (GCC Newlib, 2nd cluster) | 8 | `tolower`, `fclose`, `fprintf`, `printf`, `snprintf`, `vprintf`, `strncat`, libgcc `__floatdisf`. Same GCC-compiled Newlib objects CFTKK has at 0x80313A98 (`tolower`, `printf`, `vprintf`) |
| 0x804009C4-0x80401EB0 | vm (VM + VMBASE) | 28 + asm | `VMInit` .. `__VMBASEISIServiceException`. 0x80401550-0x80401E00 is VMBASE assembly still carved into `lbl_` labels (exception handlers, TLB/page-table setup), not separate functions yet |
| 0x80401EB0-0x80401F48 | runtime | 2 | `__save_gpr` / `__restore_gpr` (already named) |
| 0x80401F48-0x80402130 | os: OSAlloc | 4 | `OSAllocFromHeap`, `OSSetCurrentHeap`, `OSInitAlloc`, `OSCreateHeap` (`OSFreeToHeap`/`DLInsert` stripped) |
| 0x80402130-0x80402DC0 | os: OSFatal | 4 | `ScreenReport`, `ConfigureVideo`, `OSFatal`, `Halt` |
| 0x80402DC0-0x80404148 | os: OSFont | 11 | `GetFontCode` .. `OSGetFontWidth`; `OSGetFontEncode` (0x804030A8) is called by `CARDInit` |
| 0x80404148-0x8040434C | os: OSMessage | 3 | no `OSJamMessage` |
| 0x8040434C-0x804044C8 | os: OSSemaphore | 4 | |
| 0x804044C8-0x804048CC | mtx | 8 | `PSMTXIdentity` .. `C_MTXOrtho`; used by game (e.g. 0x80196884 calls `PSMTXIdentity`) |
| 0x804048CC-0x804063A4 | **ar** | 9 | `ARGetSize`, `ARAlloc`, `ARFree` stripped; the 0x8 getter is `ARGetBaseAddress` (`li r3,0x4000`) |
| 0x804063A4-0x80406828 | **arq** | 6 | adds `ARQRemoveRequest` (not in CFTKK) |
| 0x80406828-0x8040962C | **ax** | 61 | AX core, AXAux, AXCL, AXOut, AXSPB, AXVPB, AXProf. No AXFX / MIX / AXART / SYN / SEQ linked (CFTKK has them); the game has its own sound engine at 0x8024xxxx that calls `AXSetVoice*` |
| 0x8040962C-0x8040A190 | **dsp** | 15 | full `dsp.c` + `dsp_task.c` + `dsp_debug.c` |
| 0x8040A190-0x80411208 | **card** | 97 | CARDBios, CARDBlock, CARDDir, CARDCheck, CARDMount, CARDFormat, CARDOpen, CARDCreate, CARDRead, CARDWrite, CARDDelete, CARDStat, CARDNet, CARDUnlock, **then** CARDRdwr (0x80410C48) and CARDStatEx (0x80410EC8). CARDRdwr/StatEx come after CARDUnlock here, unlike ac-decomp/CFTKK. No `CARDRename`, `CARDGetResultCode`, `CARDCheckAsync`, `CARDFormatAsync`, `CARDGetFastMode` |
| 0x80411208-0x80411408 | gx: GXDisplayList | 3 | `GXBeginDisplayList`, `GXEndDisplayList`, `GXCallDisplayList` (not in the first-cluster GX) |
| 0x80411408-0x804114EC | texPalette (unconfirmed) | 2 | `TEXGet`, `TEXGetGXTexObjFromPalette` by code shape |
| 0x804114EC- | game / middleware | | thunks (0x20) and large routines calling `fn_80475994`, reached from game code at 0x8031xxxx-0x8036xxxx; the only SDK/libc calls are `vsnprintf`, `strstr`, `strlen`, `OSGetTime`, `OSPanic` |

### Corrections to earlier notes

- `AXInit` is the 0x24 wrapper at 0x80406828; the function that registers the version is `AXInitEx`
  at 0x8040684C.
- 0x80404B00 is `ARGetBaseAddress`, not `ARGetSize` (`ARGetSize` is stripped).
- DSP starts at 0x8040962C with `DSPCheckMailToDSP`, then `DSPCheckMailFromDSP` at 0x8040963C (both present).
- CARD ends at 0x80411208, not 0x80410C48: CARDRdwr and CARDStatEx follow `DoneCallback`.
- 0x8040250C-0x80404074 is SDK OS (OSFatal, OSFont), not game code.
- The second cluster starts well before AR: at 0x80400544 (libc), or 0x80401F48 for the OS part.

## The 8 functions at 0x80196884-0x80197000

Not SDK, confirmed. All eight use the GCC frame pointer (`mr r31,r1`, `stmw`), are called from game
code (0x80015248, 0x80033AB0, 0x800B5594, ...) and call game functions at 0x8042xxxx/0x8046xxxx. They
also call second-cluster MTX (`PSMTXIdentity` from 0x80196884, `C_MTXPerspective` from 0x80196CE4),
i.e. they are game code that *uses* the SDK, not part of it. The first cluster ends at 0x80196884 (`DBGEXIImm`).

## Upper bound

The SDK is not one range any more, so raising the single upper bound would sweep in about 2.5 MB of
game code (0x80196884-0x80400544). Suggested instead (not changed):

- Keep `HI = 0x80196884` in `tools/sdk_scout.py` for the first cluster. (Update: both scripts now scan
  both clusters by default.)
- Add a second range: **0x80400544-0x804114EC** (or 0x80401F48-0x80411408 for Dolphin SDK only,
  excluding libc, VM, the runtime helpers and the unconfirmed texPalette). In `sdk_scout.py` that means
  making `LO, HI` a list of ranges and adding LIBS rows for the table above; `sdk_remaining.py`
  can be run a second time with `--lo 0x80400544 --hi 0x804114EC` until it accepts several ranges.

## Could not determine

- 0x803FF3B0-0x80400544 (9 functions, no frame pointer, float math): libm, middleware or game.
- Exact names of the three 0x28 VMBASE getters (0x80401488, 0x804014B0, 0x804014D8): CFTKK has four
  0x28 functions in that file and ours has three; the proposals follow callers but the order is a guess.
- VMBASE's assembly (0x80401550-0x80401E00) has not been cut into functions.
- texPalette: shape fits, but no reference project places it here.
- The paired-single functions at 0x802DF3F0-0x802E013C (no direct callers, called through pointers)
  match no SDK reference; most likely engine math, not MTX.
- Whether the libc cluster at 0x80400544 is Newlib built the same way as the first cluster: it is
  GCC code (CFTKK marks the same objects `gcc2_compiled.`), so it will not match with MWCC.

## Proposed names (for a later rename pass)

`exact` = equal size in CFTKK or ac-decomp and matching neighbour order, plus a callee check where
noted; `guess` = name from callees / position only. Static names repeat across CARD files
(`WriteCallback`, `EraseCallback`, `OnReset`, `DoneCallback`); give them file-local names when
splitting. `OnReset` also exists in the first cluster (PAD/OS).

| Address | Size | Current | Proposed name | Confidence | Evidence |
|---|---|---|---|---|---|
| 0x80400544 | 0x1C | `fn_80400544` | `tolower` | exact | CFTKK size 0x1C (GCC Newlib); ctype _U test +0x20; called by DVD 0x80183194 |
| 0x80400560 | 0xB8 | `fn_80400560` | `fclose` | guess | CHECK_INIT/__sinit, __SWR -> fflush; Newlib |
| 0x80400618 | 0x94 | `fn_80400618` | `fprintf` | guess | varargs -> vfprintf(fp, fmt, ap) |
| 0x804006AC | 0xAC | `fn_804006AC` | `printf` | exact | CFTKK size 0xAC, followed by vprintf as in CFTKK |
| 0x80400758 | 0xDC | `fn_80400758` | `snprintf` | guess | string FILE (flags 0x208), size arg -> vfprintf |
| 0x80400868 | 0xAC | `fn_80400868` | `strncat` | guess | word-at-a-time end scan, copies n bytes, NUL-terminates |
| 0x80400914 | 0xB0 | `fn_80400914` | `__floatdisf` | guess | libgcc s64 -> float, 0x1FFFFF/0x7FF rounding guard |
| 0x804009C4 | 0xE8 | `fn_804009C4` | `VMInit` | guess | CFTKK 0x9C; calls OSGetArenaHi/PPCHalt/VMBASEInit; precedes VMSetLogStatsCallback |
| 0x80400AAC | 0x8 | `fn_80400AAC` | `VMSetLogStatsCallback` | exact | CFTKK 0x8, first of four 0x8 VM getters after VMInit |
| 0x80400AB4 | 0x8 | `fn_80400AB4` | `__VMGetNumPagesInMRAM` | exact | CFTKK 0x8; called by the page-replacement functions |
| 0x80400ABC | 0x8 | `fn_80400ABC` | `VMGetARAMSize` | exact | CFTKK 0x8; called by VMAlloc |
| 0x80400AC4 | 0x8 | `fn_80400AC4` | `VMGetARAMBase` | exact | CFTKK 0x8; called by VMAlloc |
| 0x80400ACC | 0x30 | `fn_80400ACC` | `__VMAllocMRAMSwapSpace` | exact | CFTKK size run of 5 |
| 0x80400AFC | 0x1F0 | `fn_80400AFC` | `__VMSwapPageIn` | guess | CFTKK 0x1FC; calls __VMGetPageToReplace, VMBASE helpers |
| 0x80400CEC | 0x44 | `fn_80400CEC` | `__VMGetPageToReplace` | exact | CFTKK size run of 12 |
| 0x80400D30 | 0x1D0 | `fn_80400D30` | `__VMPageReplacementLRU` | exact | CFTKK size run of 12 |
| 0x80400F00 | 0x94 | `fn_80400F00` | `__VMPageReplacementRandom` | exact | CFTKK size run of 12 |
| 0x80400F94 | 0x6C | `fn_80400F94` | `__VMPageReplacementFIFO` | exact | CFTKK size run of 12 |
| 0x80401000 | 0x100 | `fn_80401000` | `VMAlloc` | exact | CFTKK size run of 12 |
| 0x80401100 | 0x40 | `fn_80401100` | `__VMTranslateVMPageToARAMPage` | exact | CFTKK size run of 12 |
| 0x80401140 | 0x20 | `fn_80401140` | `__VMDoesMappingExist` | exact | CFTKK size run of 12 |
| 0x80401160 | 0x38 | `fn_80401160` | `__VMMappingErrorAlert` | exact | CFTKK size run of 12 |
| 0x80401198 | 0x18 | `fn_80401198` | `__VMSetARAMPageAsDirty` | exact | CFTKK size run of 12 |
| 0x804011B0 | 0x14 | `fn_804011B0` | `__VMIsARAMPageDirty` | exact | CFTKK size run of 12 |
| 0x804011C4 | 0xA8 | `fn_804011C4` | `__VMAllocVirtualToARAMLUT` | exact | CFTKK size run of 12 |
| 0x8040126C | 0xA0 | `fn_8040126C` | `__VMAllocARAMToVirtualLUT` | exact | CFTKK size run of 12 |
| 0x8040130C | 0xA4 | `fn_8040130C` | `VMBASEInit` | guess | CFTKK 0xCC; calls the __VMBASEInit*/Setup* asm labels |
| 0x804013B0 | 0x6C | `fn_804013B0` | `VMBASESetPageTableEntry` | guess | CFTKK 0x94; DCStoreRange |
| 0x8040141C | 0x6C | `fn_8040141C` | `VMBASEClearPageTableEntry` | guess | CFTKK 0x8C; DCStoreRange |
| 0x80401488 | 0x28 | `fn_80401488` | `VMBASEIsPageReferenced` | guess | 0x28 getter called by __VMPageReplacementLRU (3 same-size getters; order unconfirmed) |
| 0x804014B0 | 0x28 | `fn_804014B0` | `VMBASEIsPageDirty` | guess | 0x28 getter called by __VMPageReplacementLRU |
| 0x804014D8 | 0x28 | `fn_804014D8` | `VMBASESetPageLocked` | guess | 0x28; called by __VMSwapPageIn and LRU |
| 0x80401500 | 0x50 | `fn_80401500` | `__VMBASEDSIServiceExceptionPrep` | exact | CFTKK size 0x50 |
| 0x80401E00 | 0x4C | `fn_80401E00` | `__VMBASEISIServiceExceptionPrep` | exact | CFTKK size 0x4C |
| 0x80401E4C | 0x64 | `fn_80401E4C` | `__VMBASEISIServiceException` | guess | CFTKK 0x58 (DSI one is 0x64); OSClearContext/OSSetCurrentContext/OSLoadContext |
| 0x80401F48 | 0xFC | `fn_80401F48` | `OSAllocFromHeap` | exact | ac/CFTKK 0xFC; HeapArray walk, 32-byte rounding |
| 0x80402044 | 0x10 | `fn_80402044` | `OSSetCurrentHeap` | exact | CFTKK 0x10 |
| 0x80402054 | 0x70 | `fn_80402054` | `OSInitAlloc` | exact | ac/CFTKK 0x70; sets __OSCurrHeap (0x8066CEA8) = -1 |
| 0x804020C4 | 0x6C | `fn_804020C4` | `OSCreateHeap` | exact | CFTKK 0x6C |
| 0x80402130 | 0x3DC | `fn_80402130` | `ScreenReport` | guess | OSFatal.c; calls OSGetFontTexel |
| 0x8040250C | 0xFC | `fn_8040250C` | `ConfigureVideo` | guess | OSFatal.c; VIGetTvFormat/VIConfigure/VIConfigurePan |
| 0x80402608 | 0x1D8 | `fn_80402608` | `OSFatal` | exact | stops audio, VIInit, reset callbacks, EXI release, GXAbortFrame, arena 0x81400000, OSSwitchStack to Halt |
| 0x804027E0 | 0x5E0 | `fn_804027E0` | `Halt` | guess | OSFatal.c; target of OSSwitchStack; OSLoadFont, strlen, OSAllocFromArenaLo |
| 0x80402DC0 | 0x174 | `fn_80402DC0` | `GetFontCode` | exact | CFTKK size run of 4 |
| 0x80402F34 | 0x174 | `fn_80402F34` | `Decode` | exact | CFTKK size run of 4 |
| 0x804030A8 | 0x64 | `fn_804030A8` | `OSGetFontEncode` | exact | CFTKK size run of 4 |
| 0x8040310C | 0x324 | `fn_8040310C` | `ReadFont` | exact | CFTKK size run of 4 |
| 0x80403430 | 0x140 | `fn_80403430` | `OSLoadFont` | guess | calls ReadFont; called from Halt |
| 0x80403570 | 0x13C | `fn_80403570` | `ParseStringS` | exact | CFTKK 0x13C; calls GetFontCode |
| 0x804036AC | 0x2A0 | `fn_804036AC` | `OSGetFontTexel` | guess | called from ScreenReport; between ParseStringS and ExpandFontSheet |
| 0x8040394C | 0x3AC | `fn_8040394C` | `ExpandFontSheet` | exact | CFTKK size run of 3 |
| 0x80403CF8 | 0x20C | `fn_80403CF8` | `OSInitFont` | exact | CFTKK size run of 3 |
| 0x80403F04 | 0x170 | `fn_80403F04` | `OSGetFontTexture` | exact | CFTKK size run of 3 |
| 0x80404074 | 0xD4 | `fn_80404074` | `OSGetFontWidth` | guess | last OSFont function; VI font-encode check inline |
| 0x80404148 | 0x60 | `fn_80404148` | `OSInitMessageQueue` | exact | CFTKK size run of 3 |
| 0x804041A8 | 0xC8 | `fn_804041A8` | `OSSendMessage` | exact | CFTKK size run of 3 |
| 0x80404270 | 0xDC | `fn_80404270` | `OSReceiveMessage` | exact | CFTKK size run of 3 |
| 0x8040434C | 0x58 | `fn_8040434C` | `OSInitSemaphore` | exact | CFTKK 0x58; OSInitThreadQueue |
| 0x804043A4 | 0x70 | `fn_804043A4` | `OSWaitSemaphore` | exact | CFTKK 0x70; OSSleepThread |
| 0x80404414 | 0x54 | `fn_80404414` | `OSTryWaitSemaphore` | guess | 0x54 between OSWaitSemaphore and OSSignalSemaphore |
| 0x80404468 | 0x60 | `fn_80404468` | `OSSignalSemaphore` | exact | CFTKK 0x60; OSWakeupThread |
| 0x804044C8 | 0x2C | `fn_804044C8` | `PSMTXIdentity` | exact | ac/CFTKK 0x2C |
| 0x804044F4 | 0xCC | `fn_804044F4` | `PSMTXConcat` | exact | ac 0xCC, paired-single |
| 0x804045C0 | 0x50 | `fn_804045C0` | `PSMTXTranspose` | guess | 0x50 paired-single, between Concat and Inverse |
| 0x80404610 | 0xF8 | `fn_80404610` | `PSMTXInverse` | exact | ac 0xF8 |
| 0x80404708 | 0x34 | `fn_80404708` | `PSMTXTrans` | exact | ac 0x34 |
| 0x8040473C | 0x28 | `fn_8040473C` | `PSMTXScale` | exact | ac 0x28 |
| 0x80404764 | 0xD0 | `fn_80404764` | `C_MTXPerspective` | guess | 0xD0, calls tanf |
| 0x80404834 | 0x98 | `fn_80404834` | `C_MTXOrtho` | exact | ac/CFTKK 0x98 |
| 0x804048CC | 0x44 | `fn_804048CC` | `ARRegisterDMACallback` | exact | CFTKK size run of 5 |
| 0x80404910 | 0x3C | `fn_80404910` | `ARGetDMAStatus` | exact | CFTKK size run of 5 |
| 0x8040494C | 0xF0 | `fn_8040494C` | `ARStartDMA` | exact | CFTKK size run of 5 |
| 0x80404A3C | 0xC4 | `fn_80404A3C` | `ARInit` | exact | CFTKK size run of 5 |
| 0x80404B00 | 0x8 | `fn_80404B00` | `ARGetBaseAddress` | exact | li r3,0x4000; ARGetSize is stripped |
| 0x80404B08 | 0x78 | `fn_80404B08` | `__ARHandler` | exact | CFTKK size run of 10 |
| 0x80404B80 | 0x20 | `fn_80404B80` | `__ARClearInterrupt` | exact | CFTKK size run of 10 |
| 0x80404BA0 | 0x10 | `fn_80404BA0` | `__ARGetInterruptStatus` | exact | CFTKK size run of 10 |
| 0x80404BB0 | 0x17F4 | `fn_80404BB0` | `__ARChecksize` | exact | CFTKK size run of 10 |
| 0x804063A4 | 0x100 | `fn_804063A4` | `__ARQServiceQueueLo` | exact | CFTKK size run of 10 |
| 0x804064A4 | 0x4 | `fn_804064A4` | `__ARQCallbackHack` | exact | CFTKK size run of 10 |
| 0x804064A8 | 0xCC | `fn_804064A8` | `__ARQInterruptServiceRoutine` | exact | CFTKK size run of 10 |
| 0x80406574 | 0x70 | `fn_80406574` | `ARQInit` | exact | CFTKK size run of 10 |
| 0x804065E4 | 0x15C | `fn_804065E4` | `ARQPostRequest` | exact | CFTKK size run of 10 |
| 0x80406740 | 0xE8 | `fn_80406740` | `ARQRemoveRequest` | guess | 0xE8; unlinks one request pointer from both ARQ queues |
| 0x80406828 | 0x24 | `fn_80406828` | `AXInit` | exact | CFTKK 0x24; wrapper before AXInitEx |
| 0x8040684C | 0x4C | `fn_8040684C` | `AXInitEx` | exact | CFTKK 0x4C; loads __AXVersion and calls OSRegisterVersion |
| 0x80406898 | 0x34 | `fn_80406898` | `AXQuit` | exact | CFTKK size run of 33 |
| 0x804068CC | 0x18 | `fn_804068CC` | `__AXGetStackHead` | exact | CFTKK size run of 33 |
| 0x804068E4 | 0x74 | `fn_804068E4` | `__AXServiceCallbackStack` | exact | CFTKK size run of 33 |
| 0x80406958 | 0xB4 | `fn_80406958` | `__AXAllocInit` | exact | CFTKK size run of 33 |
| 0x80406A0C | 0xB4 | `fn_80406A0C` | `__AXAllocQuit` | exact | CFTKK size run of 33 |
| 0x80406AC0 | 0x20 | `fn_80406AC0` | `__AXPushFreeStack` | exact | CFTKK size run of 33 |
| 0x80406AE0 | 0x10 | `fn_80406AE0` | `__AXPushCallbackStack` | exact | CFTKK size run of 33 |
| 0x80406AF0 | 0x1C | `fn_80406AF0` | `__AXPopCallbackStack` | exact | CFTKK size run of 33 |
| 0x80406B0C | 0x94 | `fn_80406B0C` | `__AXRemoveFromStack` | exact | CFTKK size run of 33 |
| 0x80406BA0 | 0x80 | `fn_80406BA0` | `AXFreeVoice` | exact | CFTKK size run of 33 |
| 0x80406C20 | 0x174 | `fn_80406C20` | `AXAcquireVoice` | exact | CFTKK size run of 33 |
| 0x80406D94 | 0xE4 | `fn_80406D94` | `__AXAuxInit` | exact | CFTKK size run of 33 |
| 0x80406E78 | 0x10 | `fn_80406E78` | `__AXAuxQuit` | exact | CFTKK size run of 33 |
| 0x80406E88 | 0x34 | `fn_80406E88` | `__AXGetAuxAInput` | exact | CFTKK size run of 33 |
| 0x80406EBC | 0x20 | `fn_80406EBC` | `__AXGetAuxAInputDpl2` | exact | CFTKK size run of 33 |
| 0x80406EDC | 0x1C | `fn_80406EDC` | `__AXGetAuxAOutput` | exact | CFTKK size run of 33 |
| 0x80406EF8 | 0x20 | `fn_80406EF8` | `__AXGetAuxAOutputDpl2R` | exact | CFTKK size run of 33 |
| 0x80406F18 | 0x20 | `fn_80406F18` | `__AXGetAuxAOutputDpl2Ls` | exact | CFTKK size run of 33 |
| 0x80406F38 | 0x20 | `fn_80406F38` | `__AXGetAuxAOutputDpl2Rs` | exact | CFTKK size run of 33 |
| 0x80406F58 | 0x34 | `fn_80406F58` | `__AXGetAuxBInput` | exact | CFTKK size run of 33 |
| 0x80406F8C | 0x1C | `fn_80406F8C` | `__AXGetAuxBOutput` | exact | CFTKK size run of 33 |
| 0x80406FA8 | 0x1C | `fn_80406FA8` | `__AXGetAuxBForDPL2` | exact | CFTKK size run of 33 |
| 0x80406FC4 | 0x1C | `fn_80406FC4` | `__AXGetAuxBOutputDPL2` | exact | CFTKK size run of 33 |
| 0x80406FE0 | 0x23C | `fn_80406FE0` | `__AXProcessAux` | exact | CFTKK size run of 33 |
| 0x8040721C | 0xC | `fn_8040721C` | `AXRegisterAuxACallback` | exact | CFTKK size run of 33 |
| 0x80407228 | 0x8 | `fn_80407228` | `__AXGetCommandListCycles` | exact | CFTKK size run of 33 |
| 0x80407230 | 0x3C | `fn_80407230` | `__AXGetCommandListAddress` | exact | CFTKK size run of 33 |
| 0x8040726C | 0x6B0 | `fn_8040726C` | `__AXNextFrame` | exact | CFTKK size run of 33 |
| 0x8040791C | 0x24 | `fn_8040791C` | `__AXClInit` | exact | CFTKK size run of 33 |
| 0x80407940 | 0x4 | `fn_80407940` | `__AXClQuit` | exact | CFTKK size run of 33 |
| 0x80407944 | 0x14 | `fn_80407944` | `AXSetMode` | exact | CFTKK size run of 33 |
| 0x80407958 | 0x8 | `AXSetCompressor` | `AXSetCompressor` | known | setter, not a getter; confirmed against the SDK's AXCL.c. Dead-stripped in CFTKK |
| 0x80407960 | 0x1B8 | `fn_80407960` | `__AXOutNewFrame` | exact | CFTKK size run of 8 |
| 0x80407B18 | 0xBC | `fn_80407B18` | `__AXOutAiCallback` | exact | CFTKK size run of 8 |
| 0x80407BD4 | 0xC | `fn_80407BD4` | `__AXDSPInitCallback` | exact | CFTKK size run of 8 |
| 0x80407BE0 | 0x58 | `fn_80407BE0` | `__AXDSPResumeCallback` | exact | CFTKK size run of 8 |
| 0x80407C38 | 0x2C | `fn_80407C38` | `__AXDSPDoneCallback` | exact | CFTKK size run of 8 |
| 0x80407C64 | 0xCC | `fn_80407C64` | `__AXOutInitDSP` | exact | CFTKK size run of 8 |
| 0x80407D30 | 0x3A0 | `fn_80407D30` | `__AXOutInit` | exact | CFTKK size run of 8 |
| 0x804080D0 | 0x58 | `fn_804080D0` | `__AXOutQuit` | exact | CFTKK size run of 8 |
| 0x80408128 | 0xC | `fn_80408128` | `__AXGetStudio` | exact | CFTKK size run of 9 |
| 0x80408134 | 0x3F8 | `fn_80408134` | `__AXPrintStudio` | exact | CFTKK size run of 9 |
| 0x8040852C | 0x2C | `fn_8040852C` | `__AXSPBInit` | exact | CFTKK size run of 9 |
| 0x80408558 | 0x4 | `fn_80408558` | `__AXSPBQuit` | exact | CFTKK size run of 9 |
| 0x8040855C | 0x94 | `fn_8040855C` | `__AXDepopVoice` | exact | CFTKK size run of 9 |
| 0x804085F0 | 0x8 | `fn_804085F0` | `__AXGetNumVoices` | exact | CFTKK size run of 9 |
| 0x804085F8 | 0x74C | `fn_804085F8` | `__AXServiceVPB` | exact | CFTKK size run of 9 |
| 0x80408D44 | 0x278 | `fn_80408D44` | `__AXSyncPBs` | exact | CFTKK size run of 9 |
| 0x80408FBC | 0xC | `fn_80408FBC` | `__AXGetPBs` | exact | CFTKK size run of 9 |
| 0x80408FC8 | 0x40 | `fn_80408FC8` | `__AXSetPBDefault` | guess | CFTKK 0x44 |
| 0x80409008 | 0x200 | `fn_80409008` | `__AXVPBInit` | guess | CFTKK 0x204; called from AXInitEx, DCFlushRange |
| 0x80409208 | 0x4 | `fn_80409208` | `__AXVPBQuit` | exact | CFTKK size run of 3 |
| 0x8040920C | 0xC4 | `fn_8040920C` | `AXSetVoiceSrcType` | exact | CFTKK size run of 3 |
| 0x804092D0 | 0x5C | `fn_804092D0` | `AXSetVoiceState` | exact | CFTKK size run of 3 |
| 0x8040932C | 0x110 | `fn_8040932C` | `AXSetVoiceAddr` | exact | CFTKK size run of 4 |
| 0x8040943C | 0xA4 | `fn_8040943C` | `AXSetVoiceAdpcm` | exact | CFTKK size run of 4 |
| 0x804094E0 | 0x98 | `fn_804094E0` | `AXSetVoiceSrc` | exact | CFTKK size run of 4 |
| 0x80409578 | 0x6C | `fn_80409578` | `AXSetVoiceAdpcmLoop` | exact | CFTKK size run of 3 |
| 0x804095E4 | 0x48 | `fn_804095E4` | `__AXGetCurrentProfile` | exact | CFTKK 0x48; called by __AXOutNewFrame |
| 0x8040962C | 0x10 | `fn_8040962C` | `DSPCheckMailToDSP` | exact | CFTKK size run of 23 |
| 0x8040963C | 0x10 | `fn_8040963C` | `DSPCheckMailFromDSP` | exact | CFTKK size run of 23 |
| 0x8040964C | 0x18 | `fn_8040964C` | `DSPReadMailFromDSP` | exact | CFTKK size run of 23 |
| 0x80409664 | 0x14 | `fn_80409664` | `DSPSendMailToDSP` | exact | CFTKK size run of 23 |
| 0x80409678 | 0xC4 | `fn_80409678` | `DSPInit` | exact | CFTKK size run of 23 |
| 0x8040973C | 0x8 | `fn_8040973C` | `DSPCheckInit` | exact | CFTKK size run of 23 |
| 0x80409744 | 0x70 | `fn_80409744` | `DSPAddTask` | exact | CFTKK size run of 23 |
| 0x804097B4 | 0x40 | `fn_804097B4` | `DSPCancelTask` | exact | CFTKK size run of 23 |
| 0x804097F4 | 0xC8 | `fn_804097F4` | `DSPAssertTask` | exact | CFTKK size run of 23 |
| 0x804098BC | 0x50 | `fn_804098BC` | `__DSP_debug_printf` | exact | CFTKK size run of 23 |
| 0x8040990C | 0x424 | `fn_8040990C` | `__DSPHandler` | exact | CFTKK size run of 23 |
| 0x80409D30 | 0x1A0 | `fn_80409D30` | `__DSP_exec_task` | exact | CFTKK size run of 23 |
| 0x80409ED0 | 0x18C | `fn_80409ED0` | `__DSP_boot_task` | exact | CFTKK size run of 23 |
| 0x8040A05C | 0xA0 | `fn_8040A05C` | `__DSP_insert_task` | exact | CFTKK size run of 23 |
| 0x8040A0FC | 0x94 | `fn_8040A0FC` | `__DSP_remove_task` | exact | CFTKK size run of 23 |
| 0x8040A190 | 0x4 | `fn_8040A190` | `__CARDDefaultApiCallback` | exact | CFTKK size run of 23 |
| 0x8040A194 | 0x34 | `fn_8040A194` | `__CARDSyncCallback` | exact | CFTKK size run of 23 |
| 0x8040A1C8 | 0xD8 | `fn_8040A1C8` | `__CARDExtHandler` | exact | CFTKK size run of 23 |
| 0x8040A2A0 | 0x118 | `fn_8040A2A0` | `__CARDExiHandler` | exact | CFTKK size run of 23 |
| 0x8040A3B8 | 0xA8 | `fn_8040A3B8` | `__CARDTxHandler` | exact | CFTKK size run of 23 |
| 0x8040A460 | 0x84 | `fn_8040A460` | `__CARDUnlockedHandler` | exact | CFTKK size run of 23 |
| 0x8040A4E4 | 0xC0 | `fn_8040A4E4` | `__CARDEnableInterrupt` | exact | CFTKK size run of 23 |
| 0x8040A5A4 | 0xF0 | `fn_8040A5A4` | `__CARDReadStatus` | exact | CFTKK size run of 23 |
| 0x8040A694 | 0xAC | `fn_8040A694` | `__CARDClearStatus` | exact | CFTKK size run of 3 |
| 0x8040A740 | 0xA4 | `fn_8040A740` | `TimeoutHandler` | exact | CFTKK size run of 3 |
| 0x8040A7E4 | 0x22C | `fn_8040A7E4` | `Retry` | exact | ac 0x22C (CFTKK 0x2A0) |
| 0x8040AA10 | 0x110 | `fn_8040AA10` | `UnlockedCallback` | exact | ac-decomp size run of 16 |
| 0x8040AB20 | 0x1B4 | `fn_8040AB20` | `__CARDStart` | exact | ac 0x1B4 |
| 0x8040ACD4 | 0x134 | `fn_8040ACD4` | `__CARDReadSegment` | exact | ac-decomp size run of 16 |
| 0x8040AE08 | 0x11C | `fn_8040AE08` | `__CARDWritePage` | exact | ac 0x11C |
| 0x8040AF24 | 0xE0 | `fn_8040AF24` | `__CARDEraseSector` | exact | ac 0xE0 |
| 0x8040B004 | 0xAC | `fn_8040B004` | `CARDInit` | exact | CFTKK size run of 6 |
| 0x8040B0B0 | 0x8 | `fn_8040B0B0` | `__CARDGetFontEncode` | exact | CFTKK size run of 6 |
| 0x8040B0B8 | 0x38 | `fn_8040B0B8` | `__CARDSetDiskID` | exact | CFTKK size run of 6 |
| 0x8040B0F0 | 0xB8 | `fn_8040B0F0` | `__CARDGetControlBlock` | exact | CFTKK size run of 6 |
| 0x8040B1A8 | 0x64 | `fn_8040B1A8` | `__CARDPutControlBlock` | exact | CFTKK size run of 6 |
| 0x8040B20C | 0x150 | `fn_8040B20C` | `CARDFreeBlocks` | exact | CFTKK size run of 6 |
| 0x8040B35C | 0x84 | `fn_8040B35C` | `CARDGetSectorSize` | exact | ac 0x84 |
| 0x8040B3E0 | 0x98 | `fn_8040B3E0` | `__CARDSync` | exact | ac-decomp size run of 4 |
| 0x8040B478 | 0x50 | `fn_8040B478` | `OnReset` | exact | ac-decomp size run of 4 |
| 0x8040B4C8 | 0x8 | `fn_8040B4C8` | `__CARDGetFatBlock` | exact | CFTKK size run of 16 |
| 0x8040B4D0 | 0xD4 | `fn_8040B4D0` | `WriteCallback` | exact | CFTKK size run of 16 |
| 0x8040B5A4 | 0xC8 | `fn_8040B5A4` | `EraseCallback` | exact | CFTKK size run of 16 |
| 0x8040B66C | 0x118 | `fn_8040B66C` | `__CARDAllocBlock` | exact | CFTKK size run of 16 |
| 0x8040B784 | 0x9C | `fn_8040B784` | `__CARDFreeBlock` | exact | CFTKK size run of 16 |
| 0x8040B820 | 0xAC | `fn_8040B820` | `__CARDUpdateFatBlock` | exact | CFTKK size run of 16 |
| 0x8040B8CC | 0x8 | `fn_8040B8CC` | `__CARDGetDirBlock` | exact | CFTKK size run of 16 |
| 0x8040B8D4 | 0xD0 | `fn_8040B8D4` | `WriteCallback` | exact | CFTKK size run of 16 |
| 0x8040B9A4 | 0xC8 | `fn_8040B9A4` | `EraseCallback` | exact | CFTKK size run of 16 |
| 0x8040BA6C | 0xC4 | `fn_8040BA6C` | `__CARDUpdateDir` | exact | CFTKK size run of 16 |
| 0x8040BB30 | 0x1B0 | `fn_8040BB30` | `__CARDCheckSum` | exact | CFTKK size run of 16 |
| 0x8040BCE0 | 0x284 | `fn_8040BCE0` | `VerifyID` | exact | CFTKK size run of 16 |
| 0x8040BF64 | 0x240 | `fn_8040BF64` | `VerifyDir` | exact | CFTKK size run of 16 |
| 0x8040C1A4 | 0x284 | `fn_8040C1A4` | `VerifyFAT` | exact | CFTKK size run of 16 |
| 0x8040C428 | 0x8C | `fn_8040C428` | `__CARDVerify` | exact | CFTKK size run of 16 |
| 0x8040C4B4 | 0x590 | `fn_8040C4B4` | `CARDCheckExAsync` | exact | CFTKK size run of 16 |
| 0x8040CA44 | 0x54 | `fn_8040CA44` | `CARDCheck` | exact | ac 0x54; CARDCheckExAsync + __CARDSync |
| 0x8040CA98 | 0xCC | `fn_8040CA98` | `IsCard` | exact | ac-decomp size run of 11 |
| 0x8040CB64 | 0x17C | `fn_8040CB64` | `CARDProbeEx` | exact | ac-decomp size run of 11 |
| 0x8040CCE0 | 0x410 | `fn_8040CCE0` | `DoMount` | exact | ac 0x410 (CFTKK 0x454) |
| 0x8040D0F0 | 0x138 | `fn_8040D0F0` | `__CARDMountCallback` | exact | ac-decomp size run of 11 |
| 0x8040D228 | 0x1A0 | `fn_8040D228` | `CARDMountAsync` | exact | ac-decomp size run of 11 |
| 0x8040D3C8 | 0x48 | `fn_8040D3C8` | `CARDMount` | exact | 0x48 sync wrapper of CARDMountAsync |
| 0x8040D410 | 0x9C | `fn_8040D410` | `DoUnmount` | exact | CFTKK size run of 4 |
| 0x8040D4AC | 0xAC | `fn_8040D4AC` | `CARDUnmount` | exact | CFTKK size run of 4 |
| 0x8040D558 | 0x144 | `fn_8040D558` | `FormatCallback` | exact | CFTKK size run of 4 |
| 0x8040D69C | 0x658 | `fn_8040D69C` | `__CARDFormatRegionAsync` | exact | CFTKK size run of 4 |
| 0x8040DCF4 | 0x54 | `fn_8040DCF4` | `CARDFormat` | exact | ac 0x54; __CARDGetFontEncode + __CARDFormatRegionAsync + __CARDSync |
| 0x8040DD48 | 0x68 | `fn_8040DD48` | `__CARDCompareFileName` | exact | CFTKK size run of 4 |
| 0x8040DDB0 | 0x94 | `fn_8040DDB0` | `__CARDAccess` | exact | CFTKK size run of 4 |
| 0x8040DE44 | 0x134 | `fn_8040DE44` | `__CARDIsWritable` | exact | CFTKK size run of 4 |
| 0x8040DF78 | 0xF4 | `fn_8040DF78` | `__CARDIsReadable` | exact | CFTKK size run of 4 |
| 0x8040E06C | 0x150 | `fn_8040E06C` | `__CARDGetFileNo` | exact | ac 0x150; called by CARDDeleteAsync |
| 0x8040E1BC | 0x104 | `fn_8040E1BC` | `CARDFastOpen` | guess | ac 0x160; control block + dir block + __CARDIsWritable |
| 0x8040E2C0 | 0x11C | `fn_8040E2C0` | `CARDOpen` | exact | CFTKK size run of 5 |
| 0x8040E3DC | 0x54 | `fn_8040E3DC` | `CARDClose` | exact | CFTKK size run of 5 |
| 0x8040E430 | 0x8 | `fn_8040E430` | `__CARDIsOpened` | exact | CFTKK size run of 5 |
| 0x8040E438 | 0x130 | `fn_8040E438` | `CreateCallbackFat` | exact | CFTKK size run of 5 |
| 0x8040E568 | 0x220 | `fn_8040E568` | `CARDCreateAsync` | exact | CFTKK size run of 5 |
| 0x8040E788 | 0x48 | `fn_8040E788` | `CARDCreate` | exact | 0x48 sync wrapper of CARDCreateAsync |
| 0x8040E7D0 | 0x1B8 | `fn_8040E7D0` | `__CARDSeek` | exact | CFTKK size run of 3 |
| 0x8040E988 | 0x130 | `fn_8040E988` | `ReadCallback` | exact | CFTKK size run of 3 |
| 0x8040EAB8 | 0x144 | `fn_8040EAB8` | `CARDReadAsync` | exact | CFTKK size run of 3 |
| 0x8040EBFC | 0x48 | `fn_8040EBFC` | `CARDRead` | exact | 0x48 sync wrapper of CARDReadAsync |
| 0x8040EC44 | 0x170 | `fn_8040EC44` | `WriteCallback` | exact | CFTKK size run of 3 |
| 0x8040EDB4 | 0xB0 | `fn_8040EDB4` | `EraseCallback` | exact | CFTKK size run of 3 |
| 0x8040EE64 | 0x114 | `fn_8040EE64` | `CARDWriteAsync` | exact | CFTKK size run of 3 |
| 0x8040EF78 | 0x48 | `fn_8040EF78` | `CARDWrite` | exact | 0x48 sync wrapper of CARDWriteAsync |
| 0x8040EFC0 | 0xA4 | `fn_8040EFC0` | `DeleteCallback` | exact | ac-decomp size run of 6 |
| 0x8040F064 | 0x12C | `fn_8040F064` | `CARDFastDeleteAsync` | exact | CFTKK 0x12C; wrapped by CARDFastDelete |
| 0x8040F190 | 0x48 | `fn_8040F190` | `CARDFastDelete` | exact | 0x48 sync wrapper of CARDFastDeleteAsync |
| 0x8040F1D8 | 0x110 | `fn_8040F1D8` | `CARDDeleteAsync` | exact | ac 0x110 |
| 0x8040F2E8 | 0x48 | `fn_8040F2E8` | `CARDDelete` | exact | 0x48 sync wrapper of CARDDeleteAsync |
| 0x8040F330 | 0x1F8 | `fn_8040F330` | `UpdateIconOffsets` | exact | CFTKK size run of 4 |
| 0x8040F528 | 0x114 | `fn_8040F528` | `CARDGetStatus` | exact | CFTKK size run of 4 |
| 0x8040F63C | 0x174 | `fn_8040F63C` | `CARDSetStatusAsync` | exact | CFTKK size run of 4 |
| 0x8040F7B0 | 0x48 | `fn_8040F7B0` | `CARDSetStatus` | exact | CFTKK size run of 4 |
| 0x8040F7F8 | 0xC4 | `fn_8040F7F8` | `CARDGetSerialNo` | guess | 0xC4; control block get/put only (CARDNet.c) |
| 0x8040F8BC | 0xE4 | `fn_8040F8BC` | `CARDSetAttributesAsync` | guess | 0xE4; __CARDGetStatusEx + __CARDSetStatusExAsync |
| 0x8040F9A0 | 0x48 | `fn_8040F9A0` | `CARDSetAttributes` | guess | 0x48 sync wrapper of the above |
| 0x8040F9E8 | 0x16C | `fn_8040F9E8` | `bitrev` | exact | CFTKK size run of 7 |
| 0x8040FB54 | 0x144 | `fn_8040FB54` | `ReadArrayUnlock` | exact | CFTKK size run of 7 |
| 0x8040FC98 | 0xC4 | `fn_8040FC98` | `DummyLen` | exact | CFTKK size run of 7 |
| 0x8040FD5C | 0xB58 | `fn_8040FD5C` | `__CARDUnlock` | exact | CFTKK size run of 7 |
| 0x804108B4 | 0x70 | `fn_804108B4` | `InitCallback` | exact | CFTKK size run of 7 |
| 0x80410924 | 0x324 | `fn_80410924` | `DoneCallback` | exact | CFTKK size run of 7 |
| 0x80410C48 | 0xDC | `fn_80410C48` | `BlockReadCallback` | exact | ac 0xDC (CARDRdwr.c, linked after CARDUnlock) |
| 0x80410D24 | 0x64 | `fn_80410D24` | `__CARDRead` | exact | ac 0x64; called by CARDReadAsync/DoMount |
| 0x80410D88 | 0xDC | `fn_80410D88` | `BlockWriteCallback` | exact | ac 0xDC |
| 0x80410E64 | 0x64 | `fn_80410E64` | `__CARDWrite` | exact | ac 0x64 |
| 0x80410EC8 | 0xA4 | `fn_80410EC8` | `__CARDGetStatusEx` | guess | ac 0xBC; CARDStatEx.c |
| 0x80410F6C | 0x29C | `fn_80410F6C` | `__CARDSetStatusExAsync` | guess | ac 0x254; __CARDIsWritable, memcmp |
| 0x80411208 | 0xCC | `fn_80411208` | `GXBeginDisplayList` | exact | CFTKK 0xCC |
| 0x804112D4 | 0xC4 | `fn_804112D4` | `GXEndDisplayList` | exact | CFTKK 0xC4 |
| 0x80411398 | 0x70 | `fn_80411398` | `GXCallDisplayList` | exact | CFTKK 0x70 |
| 0x80411408 | 0x10 | `fn_80411408` | `TEXGet` | guess | `&pal->descriptorArray[id]` (load +8, index * 8); texPalette.c, unconfirmed |
| 0x80411418 | 0xD4 | `fn_80411418` | `TEXGetGXTexObjFromPalette` | guess | GXInitTexObj + GXInitTexObjLOD, header min/max LOD at 0x21/0x22; texPalette.c, unconfirmed |
