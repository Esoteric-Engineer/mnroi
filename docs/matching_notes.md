# Matching Notes

Compiler/linker behavior and techniques learned while matching functions in this game. Helpful to review when a function is stuck short of 100%.

---

## Compiler gotchas

### GX setters: three source-shape levers

Scope: found on `Dolphin/gx` (`GC/1.2.5n`); untested on game code. For a GX setter whose instruction sequence is identical but registers/scheduling differ, sweep `{macro, declare-at-address} x {plain, const} x {gx local, direct}` before anything else (25 units matched this way).

- **`extern __GXDataStruct* const __GXData;`** Without `const`, a late extra `lwz rX,-11608(r13)` appears or `gx` lands a register too high (likely because MWCC assumes stores may alias the pointer). Highest yield.
- **Direct `__GXData->field` over a `gx` local**, once `const` is in. Keep a local only where the original really reloads (`GXCopyDisp`/`GXCopyTex` use both).
- **`volatile GXFifoObj GXWGFifo : 0xCC008000;`** instead of the cast macro. It changes scheduling, not just addressing, and is per-function (`GXSetTevOrder` and `GXSetViewport` prefer the macro).

Smaller findings:

- **`u32 c = *(u32*)&color;`** for a by-value `GXColor`: 68% -> 100% on `GXSetTevKColor`. Declare it at its point of use: in `GXSetFog` an inline `*(u32*)&color` hoists the `rlwimi` a dozen instructions early (91.3% -> 100%).
- **`phyAddr = (u32)dest & 0x3FFFFFFF;` temp** in `GXCopyDisp`/`GXCopyTex`. The mask emits nothing, but inlining `(u32)dest >> 5` drops `GXCopyDisp` from 100% to 47%.
- **`u8` for `GXBool` params** even when only forwarded: `GXSetCoPlanar` 7% -> 100%.
- **Named local for a compound `__rlwimi`** (`GXSetCullMode` `hwMode`), else it lands in `r0`.
- **`fcmpu` operand order follows source order:** `(lbl_80670770 == ptr[0])` matched `GXSetProjectionv`.
- **A local for a reused masked param moves its register, and its slot in the declaration list matters:** `u32 f = format & 0xF;` declared *first* took `GXInitTexObj` 98.6% -> 99.9%; every other slot gives 99.8%.

- **A bare `cntlzw` feeding a one-bit `rlwimi` is a folded `==`:** `x == n` compiles to `subfic`/`cntlzw`/`srwi 5`, and MWCC absorbs that `>> 5` into the insert's rotate (rotate = field shift + 5). Write the comparison at the *unfolded* shift: `SET_REG_FIELD(reg, 1, 11, type == 3)` emits `rlwimi rX,rY,6,20,20`. Hand-writing `__cntlzw(3 - type)` at the folded shift gets the instructions but not the scheduling. `GXSetBlendMode` 90% -> 100%.

- **To stop MWCC sharing `base + i * 4` between two pointers into one table, give each its own byte-offset base:** `(u32*)(base + 20) + i` and `(u32*)(base + 60) + i` off a `u8* base` local are reassociated only *after* CSE, so each gets its own `add` plus a folded `addi`. `&tbl[0][i]` / `&tbl[1][i]` instead yields one CSE temp and a copy. The `u8*` local also hoists the `lis`/`addi` above the branch. `GXSetTevOp` 85.7% -> 93.4%, then 100% with `* const __GXData`.

- **Float constants in an FP-heavy function must be real literals, not `extern const f32`:** an extern loads into a scratch and copies out twice (`lfs f0`; `fmr f3,f0`; `fmr f31,f0`); a literal loads straight into the first destination (`lfs f3`; `fmr f31,f3`). So claim the unit's `.sdata2` literal range in `splits.txt`, plus `#pragma force_active on` (below). MWCC orders the pool by pre-scheduling code order, in which a loop body precedes its condition. `GXSetFog` 89.4% -> 97.4%.

- **Two functions sharing one `.sdata2` pool are one translation unit:** if a split-off function fails to bake with `Symbol '@NN' is in .sdata2, but unit ... has no .sdata2 split`, its literals (float constants, the int-to-float magic double, const-initialised `GXColor` locals) are pooled with a neighbour's. Merge the two into one unit and claim the whole pool. `__GXInitGX` had to join `GXInit`, and even the `__GXData` pointer lives in that pool (defined as a `const` pointer to its `.bss` object).

- **Hoist a shared table base by declaring its pointer local first:** `u8* tbl = lbl_XXXX;` as the *first* local put the `lis`/`addi` in r31 before the first call, and reused it for several `tbl + off` arguments (`__GXInitGX` 99.95% -> 100%). Declaring it in any later slot gave a different register assignment.

- **Stack slot order follows declaration order in reverse for aggregates:** the earlier-declared local got the higher offset. In `__GXInitGX`, declaring `texObj` before `identity_mtx` put the matrix at the lower slot, as the original has it.

- **A `u8` parameter on the callee adds a `clrlwi` after a ternary argument:** if the original passes the `li 1`/`li 0` result straight through, prototype the parameter as `u32` (`GXSetFieldMode`'s second argument).

- **Decode a jump table rather than trusting a reference decomp's case list:** this game's `__GXGetTexTileShift` uses `0x2B`/`0x2C` where ac-decomp has `0x24`/`0x25`.

- **A `switch` whose arms each assign to `*ptr` and `return` gets the store and `blr` tail-duplicated into every arm:** assign a local in the arms and store once after the switch, and the shared `b tail` comes back. `GXGetVtxAttrFmt` 97.9% -> 100%.

- **Dolphin SDK register writes use the CodeWarrior `__rlwimi` intrinsic, not plain C:**

  ```c
  #define SET_REG_FIELD(reg, size, shift, val)                    \
      (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift),      \
                            (32 - (shift) - (size)), (31 - (shift)))
  ```

  A bare `rlwimi` in the original is the giveaway. Plain C like `(reg & ~mask) | ((val & m) << shift)` gets around 65%; dropping the value mask gets around 53%. Only the intrinsic matches.

- **An `asm` function disables peephole optimization for every later function in the same translation unit** on GC/1.2.5n. Usual symptoms are lost displacement folding, lost record-form compares, and early returns turning into branches to the shared epilogue.

  The fix is adding `#pragma peephole on` immediately after the asm function closes. `#pragma scheduling on` is not needed. This matters in any unit that mixes an early asm function with later plain C, since address order often forces the asm function to appear first.

- **CodeWarrior treats an undeclared data symbol in `asm` as a local label:** declaring the existing external object before the asm function is required for `@ha`/`@l` relocations to compile.

- **Hardware-register arrays must use CodeWarrior's declare-at-address form, not a pointer-cast macro:**

  ```c
  volatile u32 __SIRegs[0x100] : 0xCC006400;      /* correct */
  #define __SIRegs ((volatile u32*)0xCC006400)    /* compiles, does NOT match */
  ```

  The macro form folds the index into the base register (`mulli`/`addis`/`stw`) instead of the original separate-index `stwx` form. Reference decomps often carry the `#define` behind an `#ifdef __MWERKS__ ... #else`; that fallback is unwanted.

- **Operand order matters on carry ops:** `ticks + *timeAdjustAddr` compiled to `addc r30,r30,r4` and matched; `*timeAdjustAddr + ticks` produced `addc r30,r4,r30` and also matched. When a function is one instruction off, try reversing the expression first.

- **A `static` helper called from two sites gets inlined unless told otherwise:** if the original keeps the `bl` (function 0% match, prologue lacks `mflr`), wrap the helper in `#pragma dont_inline on` / `#pragma dont_inline reset`. This took `__GXSetSUTexRegs` from 0% to 100%.

- **Register allocation stuck (wrong regs, `li` order) in a tiny GX setter: try the narrower param type.** `u32` vs `u8` for a `GXBool`-style parameter changed the allocation from 77% to 100% in `GXSetDither`, `GXSetColorUpdate` and `GXSetAlphaUpdate`.

- **A full-width `SET_REG_FIELD` (8-bit field at shift 0) loses the original's `clrrwi`, and a `u8` param adds a `clrlwi`:** use a `u32` param and write `__rlwimi((int)(reg & 0xFFFFFF00), (int)vol, 0, 24, 31)` explicitly. Matched `AISetStreamVolLeft` (68% -> 100%).

- **A `clrlwi rX,r3,24` right after a `bl` that the original lacks means the callee's return type is too narrow:** declare the extern as returning `u32` (locals too), even if the real function returns `u8`. Matched `AISetStreamPlayState` (92% -> 100%, alongside `(reg & ~1) | state` and `(reg & ~0x20) | 0x20` in plain C where the original has `clrrwi`/`rlwinm` + `ori` instead of `rlwimi`).

- **`stwu r1,-8` / `mflr` / `stw r0,12(r1)` wrapper with argument `li`s between the `stw` and the `bl`: also `nofralloc` asm.** `scheduling off` + `peephole off` gets 99.6% but the frame stays `-0x10`. Matched `atof` (`0x801711F0`, `strtod(s, 0)`) and `atoi` (`0x80171214`, `strtol(s, 0, 10)`) as asm.
- **Original has `stwu` before `mr r4,r3` (arg copy after frame setup) in a tiny wrapper: add `#pragma peephole off`** before the function. Default codegen emits the copy first (63%); `#pragma scheduling off` alone gets 76-82% and misorders `li`/`crclr`. Peephole off alone is 100% (`OSRegisterVersion`, `0x8017B3C0`).
- **Bare wrapper where the original is `stwu r1,-8` / `mflr r0` / `stw r0,12(r1)` / `bl X` / ... (LR saved *after* the frame is made): plain C can't do it** -- MWCC emits `mflr`/`stw r0,4(r1)` *before* `stwu` (49.9%), and `peephole off` doesn't change that. Write it as an `nofralloc` `asm` function, like `fn_8017A6CC`/`fn_8017A6EC` (`0x8017A6EC`).

- **A variadic-looking function whose prologue is `stwu`/`mflr`/`stmw`/`stw r0` with `stw r5..r10` and `bne cr1` + `stfd f1..f8` skipping the FP saves, but never uses the va_list: plain C with `__builtin_va_info` emits a different frame (`mflr` first, va_list struct stores, 7.8%).** Transliterate as `nofralloc` asm. Matched `fn_8017A75C` (`0x8017A75C`).

- **Original has `clrlwi` separate from a following `slwi` (indexing a table by a `u8` param), where ours emits a merged `clrlslwi`: add `#pragma peephole off`** at the top of the unit. Took `__OSSetExceptionHandler`/`__OSGetExceptionHandler` (`0x8017B234`/`0x8017B250`) from 66-75% to 100%.

- **Redundant `b <next instruction>` branches at every loop head (often two or three in a row), plus a separate `cmplwi`/`blt` where ours folds the compare: `#pragma peephole off`.** In a loop-heavy function this is worth far more than the symptom suggests. It took `GXInit` from 84.7% to 99.2% in one change, restoring ~18 instructions across six loops. The original's peephole-off state comes from an `asm` function earlier in the real translation unit; a `static asm` stub at the top of the file produces byte-identical output to the pragma, so prefer the pragma, which emits no extra function.

- **Align-up arithmetic gets reassociated (`add size, a` first) when written with plain `unsigned long` temps:** use the SDK's shape instead: a `ROUNDUP(x, a)` macro `(((unsigned long)(x) + (a)-1) & ~((a)-1))`, with `unsigned char*` locals for the pointer add (`(u8*)ptr + size`). Took `OSAllocFromArenaLo` (`0x8017BBE4`) from 98% to 100%.

- **Loop tail emits `bne top; b exit` where ours emits `beq exit; b top`:** write the back-edge as `if (x != 0) { continue; } break;` instead of `if (x == 0) { break; }`. Took `OSCancelThread`'s inlined `UpdatePriority` loop from 99.86% to 100%.

- **Inlined `__OSGetEffectivePriority` loop gets the wrong registers (priority in r4, blocked thread in r5) and the frame comes out 8 bytes too big:** write it as a `static inline` helper, read the blocked thread's priority once into a local inside `if (b) { long bp = b->priority; if (bp < priority) priority = bp; }`, and assign straight to `thread->priority = EffPrio(thread)` with no function-scope temps. Took `OSResumeThread` (`0x80180804`) from 99% to 100%.

- **A base address hoisted into a saved register once (`lis`/`addi r31,RunQueue`), with later `r31+offset` uses (`addi r3,r31,0x730`):** keep a local `OSThreadQueue* rq = RunQueue;` and derive every use from `rq`. Referencing the global directly re-emits `lis`/`addi` at each use (89%). If two uses share the same `(u8*)rq + off` expression they get CSE'd into an extra saved register; write the second as `rq + 230` (pointer arithmetic, same address) instead. Also inline `OSGetCurrentThread` as a `static inline` reading `__gCurrentThread : 0x800000E4` (declare-at-address) to get the original's extra `addi r3,rX,0` copy. Matched `SelectThread` (`0x801800E8`).

- **CP counter reads (`GXReadGPMetric`): use the SDK's own `inline u32 __GXReadCPCounterU32(u32 regAddrL, u32 regAddrH)` from `GXRegs.h`, taking register *indices*, plus `#pragma scheduling off`.** With scheduling on, MWCC swaps the two volatile loads in each retry loop and hoists the next counter's setup above the previous one's `slwi`/`or`. A hand-written helper that takes two pointers only reached 91%, with or without scheduling off. The SDK form with scheduling off is exact (0x80193C74).
- **`EXIBios.c` functions need `#pragma scheduling off`:** `EXIGetState` (0x80195440) went from 64% to 100% with it, and `UnlockedHandler` (below) needs it too. The original unit was probably built that way, so try it first for other `EXIBios` functions.

- **Stack frame too small with no stack locals to account for it: look for an SDK inline helper that has its own pointer local.** MWCC reserves an 8-byte frame slot for an inlined function's local that stays live across a call inside that function, even when the local is register-allocated. An inline with no locals, or a local not live across a call, adds nothing, and the same local written at function level adds nothing either. `__GXCleanGPFifo` (0x80191F5C) matched only once it used the SDK's real `GXInitFifoPtrs` and `GXGetFifoBase` as `inline` functions, each with its `__GXFifoObj* realFifo = (__GXFifoObj*)fifo;` cast local. That moved the frame from `-0x98` to `-0xa8` and `dummyFifo` from `0x8(r1)` to `0x14(r1)`. A non-static `inline` that ends up uncalled is not emitted, so the unit's `.text` stays the same size.
- **`addi rD,rS,0` where ours has `mr rD,rS` comes from the peephole pass:** with `-opt nopeephole` every copy is `mr`, while normal builds turn some copies into `addi`. Parameter copies into saved registers ahead of an early-return branch come out as `addi`, and so does a copy emitted next to another copy. How the address is spelled has no effect: `&t->ctx`, `(C*)t`, `&t[0].ctx` and a `ctx` local all give the same instruction. So treat this as a scheduling/peephole-context difference, not as missing `+0` address arithmetic (`OSCreateThread`, `GXSetScissorBoxOffset`).
- **A caller-less `asm` function (`__OSLoadFPUContext`, `0x8017C2DC`) is dropped by the linker once `Matching`:** `main.dol` comes out short by exactly its size (0x124). Add it to `force_active` in `config/GVLE69/config.yml`. It is a plain `nofralloc` asm transliteration with `register unsigned long unused, register OSContext* fpuContext` (context in r4), `mfspr r5, 920` for HID2, and `psq_l fN, off(r4), 0, 0`.
- **Inlining:** A function may contain the inlined body of a method from a not-yet-reconstructed header. A `static` helper with a single caller can be inlined with no separate `bl`, which is why an original may have no call where a reference decomp appears to have one.

- **A hardware-register read where the original keeps `lis`/`addi 0x3000`/`lwz 0x24(r3)` (base add not folded into the displacement), plus `cmpwi` and a `b` to a shared `blr`: `#pragma peephole off`, and use a signed `int` for the flag.** The declare-at-address `__PIRegs` form is still right; peephole off only stops the displacement folding (`lwz 0x3024`). Matched `OSGetResetCode` (`0x8017EBB4`). This game's version differs from ac-decomp's: it reads a `.bss` reset-info struct (`lbl_8057C550[0]`/`[1] | 0x80000000`) rather than `OS_REBOOT_BOOL`.

- **Tiny wrapper where the original emits `stwu` before `li r4,0`/`addi r5,r1,N` (arg setup after frame setup), and ours hoists `li`/`addi` above `stwu` (74%): `#pragma scheduling off`.** `peephole off` alone only swaps the two arg setups (88%); scheduling off alone is 100%. Matched `UnlockedHandler` (`0x80195458`, `EXIGetID(chan, 0, &id)` wrapper).

- **Early `return 0;` compiles to a bare `blr` where the original branches to the shared exit (`b .L_end`) in a tiny pointer-returning function: `#pragma peephole off`.** Restructuring into a single `r` result variable has no effect. Matched `__GXDefaultTlutRegionCallback` (`0x80190580`).

- **A loop that re-reads a struct field the loop condition already loaded (original has `lwz` in the cond and again in the body) needs enum-typed fields, not `int`:** `int` lets MWCC reuse the cond load (97.5%); `enum` fields on the list struct and inline helper params matched the codegen (`GXSetVtxAttrFmtv`, 99.9%).

- **Redundant `b <next instruction>` no-op branches appear at loop/branch join points, sometimes doubled:** Translate literally rather than collapsing them.

- **An inlined `SetTimeoutAlarm(OSTime)` (saves r30/r31, alarm base loaded before the tick math) needs a `static` helper taking the `s64` timeout as a parameter,** not the `OSCreateAlarm`/`OSSetAlarm` calls written inline (60.9%). Call it as `SetTimeoutAlarm((s64)((*(u32*)0x800000F8 / 4) * 10))`. Matched `DVDLowStopMotor` (`0x80187660`); the same shape should fit its `DVDLowRequestError`-style siblings. Claiming it made dtk-dev auto-name `OSCreateAlarm`/`AlarmForTimeout`/`AlarmHandlerForTimeout` (set the last two `scope:global`, update other units' `extern`s).

- **A `dont_inline` helper kept for its own address can't be called from a later function that inlined it in the original:** `stateReady` (`0x80184E2C`) shows `lis`/`addi cbForStateMotorStopped` + `bl DVDLowWaitCoverClose` inline (and `executing` in r4), where calling `stateMotorStopped()` gives `bl stateMotorStopped` (95%). Write the helper's body out at the call site. `stateCoverClosed` (not `dont_inline`) does inline into it.

- **Claiming a jump table forces you to claim the strings before it (`.data` must be contiguous), and a named global array is emitted before string literals:** `char lbl_804D2184[] = "..."` put the string ahead of `"load fst\n"` and shifted `.data` (60 bytes differ, function still 100%). Write the string inline at each use so first-use order applies. `stateBusy` (`0x8018505C`); note the original has a `length == 0` early finish that ac-decomp lacks.

- **Alarm-queue walk with `next` cached (`alarm ? alarm->next : 0` before and at the end of each iteration) plus stray `b <next>` branches:** write `next = alarm ? alarm->next : 0;` ahead of a `while (alarm)` loop and again at the loop tail, with `#pragma peephole off`. A `for` loop with the null check at the head is 58%. Matched `fn_8017BB24` (`0x8017BB24`).

- **A variadic `OSPanic`-style function needs `__builtin_va_info(&args)` (as in `OSReport`) and its string literals claimed as `.data`:** the strings sit in one blob whose symbol dtk sized too big (`@13` 0x16 plus one 0x2C6 `lbl_`), so split the blob in `symbols.txt` at the claimed end (`ends within symbol` error otherwise). A string another unclaimed function still references (`@13_804D0EF8` undefined at link) must be renamed to a real global and *defined* in the source as `char Name[] = "..."` used at its first use; it lands in place. Matched `OSPanic` (`0x8017CBFC`); `fn_8017CD28` (`OSSetErrorHandler` neighbour) and `__OSUnhandledException` share that `.data` blob.

- **A u64 field split as `u32 pad; u32 lo;` in a struct can change register allocation vs. `*((u32*)&u64f + 1)` casts:** `OSSetErrorHandler` (`0x8017CD28`) sat at 99.1% with only the thread-walk pointer in r7 instead of r6 until `fpscr` was declared as `u32 fpscr_pad; u32 fpscr;` and accessed by name. This game's version also toggles the FPE enable bits (MSR FE0/FE1, FPSCR) across `__OSActiveThreadQueue` (head at `0x800000DC`), unlike ac-decomp's plain table swap.

- **A string blob shared by several units: claim from the first string (8-aligned), define that first string as a global `char X[]`, and use plain literals for the rest.** `__OSCacheInit`/`DMAErrorHandler` (`0x8017C1E8`/`0x8017C088`) share `.data 0x804D0AF0` with the already-matched asm `L2GlobalInvalidate`, whose `>>> L2 INVALIDATE` string sits first. Starting the claim at the 4-mod-8 `0x804D0B1C` shifted `main.dol` by +32 (per-function fuzzy was still ~99%). Starting at `0x804D0AF0` and defining `char L2InvalidateStr[] = "..."` (renamed from `@69`, `scope:global`, `OSCache.c` `extern` updated) matched. Also: inlined `L2Disable`/`L2Init` `sync`s are `asm { sync }` blocks, and `#pragma peephole off` is needed for the non-record `rlwinm`/`cmplwi` pairs.

- **A string-only `.data` claim starting 4-mod-8 also shifts `main.dol` (+32 here), not just jump tables:** `__OSContextInit`'s `"FPU-unavailable handler installed\n"` (`0x804D0ED4`) failed as its own unit at 100% per-function. Merge it into the neighbouring unit whose `.data` ends there (`OSDumpContext.c`, one original `OSContext.c`). The asm `OSSwitchFPUContext` before it means `#pragma peephole on` must *not* be added: keep peephole off, or `lis` hoists above the prologue.

- **A `static` helper inlined into its caller (`PopWaitingQueuePrio` in `__DVDPopWaitingQueue`, `0x80186668`) gives a frame 8 bytes too big (`-0x18` vs `-0x10`):** its local (`tmp`) stays live across the `OSRestoreInterrupts` call. Delete the helper and write its body inline in the caller's loop (re-calling `OSDisableInterrupts` there, as the original does). 99.875% -> 100%.

- **Inlined `ReadDiscBlocking`-style helper (`u8 block[0x30]`, `DVDReadAbsAsyncPrio` + status loop) with the frame 8 bytes short (`-0x40` vs `-0x48`):** write it as a `static inline` taking `void* addr`, with an extra `void* p = addr;` local and a trailing `(void)p;` (no other locals). Plain body-inline or a `DVDCommandBlock* b` local don't help (99.9% / 87%). Also use `s32` for the sbss cache and `0x800030F4` test (`cmpwi`, not `cmplwi`). Matched `fn_8017D4A4` (`0x8017D4A4`).

- **`PauseFlag`/`PausingFlag` (dvd `.sbss`) must be `volatile` too:** without it the `lwz PausingFlag` hoists above the `stw PauseFlag` (87%, plus an `addi`/`mr` r31 swap that follows from it). Same family as the `Canceling`/`ResumeFromHere` note below. Matched `DVDResume` (`0x80185FD8`).

- **C++ class layout must be exact:** One wrong member offset breaks matching in that class, and vtable order must match the original virtual declaration order.

---

## Data, symbols, and relocations

- **Fresh anonymous data doesn't reliably land at the original's address:**

  A plain-C `static` local or a fresh string literal can report 100% fuzzy, but the linker places it wherever, so the address computation bakes in the wrong small-data offset and `main.dol` breaks by a byte or two.

  The fix is to reference dtk's auto-detected symbol instead. dtk sometimes names these with a compiler-internal disambiguator such as `cmdTypeAndStatus$371`. `$` is not valid in this compiler, so rename it to a plain identifier in `symbols.txt` with `scope:global`, leave the range unclaimed in `splits.txt`, and use a plain `extern`.

- **dtk only preserves a hand-set symbol name if it doesn't look auto-generated:**

  Renaming a compiler literal (`@267 = .sdata2:0x8067078C`) to `lbl_8067078C` is silently reverted on the next build, because `lbl_*`/`fn_*` are dtk's own naming patterns and get regenerated. The rename also never reaches `build/GVLE69/sda_bake.json`, so your `extern` keeps an unbaked `R_PPC_EMB_SDA21` relocation where the original object has a plain `r13` offset. This is visible in `tools/objdiff_mismatches.py` as a `DIFF_REPLACE` on the `lfs`/`lwz`, not as a byte diff.

  Give it a real name instead (`GXInitZScaleConst`). That survives regeneration, lands in the bake list, and the relocation resolves. Same rule as the `cmdTypeAndStatus$371` case above.

- **Claiming a known SDK function can make dtk-dev rename the `.sbss` symbols it touches (`lbl_8066F330` -> `StopAtNextInt`, `scope:local`):** the next `ninja` rewrites `symbols.txt` and every other unit's `extern lbl_...` fails to link (`undefined: 'lbl_8066F330'`). Keep the new names, set them `scope:global`, and update the `extern`s in sibling units. Seen with `DVDLowWaitCoverClose` (`Callback`, `StopAtNextInt`, `WaitingCoverClose`).

- **Prefer referencing an unclaimed symbol over claiming its range:**

  Claiming even a 4-byte `.sbss` range can repack every other unclaimed symbol in that section.

  The same applies to `.data` statics with cross-object callers. Claiming a range to define `Si` as a true `static` broke the link with `undefined: 'Si_804D1BBC'` from six still-unclaimed functions. Override `scope:local` to `scope:global` in `symbols.txt` and use a plain `extern` instead. Hand-set attributes persist across regeneration.

- **`addi` does not accept the bare-symbol sda21 trick:** "Bare symbol name, no base register" only works for instructions with a real `d(rA)` operand such as `lwz` or `lfd`. For address computations, use `la rD, symbol` and give the symbol a sized declaration such as `extern char lbl_8066C408[8];` rather than `[]`; the size is what fixes the relocation type.

  Getting it wrong produces the wrong relocation, visible via `tools/objdiff_mismatches.py`, not a byte diff.

- **Before hardcoding an address as a raw immediate because the target "isn't split yet", rebuild once and grep `symbols.txt`:** dtk's auto-namer may already have named it. Hardcoded `lis`/`addi` immediates stall around 99% because the original carries real `R_PPC_ADDR16_HA`/`_LO` relocations; switching to `symbol@ha`/`@l` matches immediately.

- **The auto-namer may only tag part of a merged data blob:**
  For example, it may name the first 0x30 bytes of a 0x98-byte blob and leave the rest as a separate `lbl_`. Auto-names also often come back as `scope:local`, and they may need a manual override to `scope:global` before your object can reference them.

- **A switch's jump table is a lone anonymous `.data` object, and MWCC always gives that section 8-byte alignment:** a unit whose claimed `.data` starts 4-mod-8 therefore lands 4 bytes late, and `main.dol` breaks with thousands of scattered diffs (everything after shifts) even though the function's own fuzzy match reports 100%.

  **The fix is to widen the unit until its `.data` is 8-aligned**, i.e. reconstruct the original translation unit. Table addresses mark the object boundaries: tables packed with no gap are one object, a 4-byte gap is the padding before the next. Claim every function from the first table's owner onward and keep the unit's `.text` contiguous, since an object contributes one contiguous `.text` block and functions sitting in between have to come along. This unblocked `GXSetVtxAttrFmtv`, `GXSetTexCoordGen2` and `GXInitTexObj`. Still a blocker where the rest of the original file is unknown (`VIGetTvFormat`, `0x8018992C`).

  **Only the *start* of the claimed range has to be 8-aligned.** A range that *ends* 4-mod-8 is fine, because what follows is one of dtk's own asm objects, which carries the original's 4-byte alignment rather than MWCC's 8. `GXSetGPMetric` was first split alone with `.data 0x804D3738-0x804D3824`, leaving the next jump table (`jumptable_804D3824`, its neighbour `GXReadGPMetric`'s) unclaimed, and `main.dol` stayed `OK`. So a function whose own tables start 8-aligned can be split on its own even when the rest of its translation unit isn't ready. The reverse fails: `GXReadGPMetric`'s own table starts at `0x804D3824`, so it had to join `GXSetGPMetric.c` (`.text 0x8019342C-0x80193E1C`, `.data 0x804D3738-0x804D3880`).

  **A merged-in function with no callers gets dead-stripped once the unit is `Matching`:** the link drops it with its jump table, and `main.dol` comes out shorter. `GXReadGPMetric` was missing from `main.elf` and the DOL was 480 bytes short. Add the function to `force_active` in `config/GVLE69/config.yml`.

- **A `Matching` unit that owns a `.sdata2` range needs `#pragma force_active on`:** `dtk elf bake-sda` turns every `.sdata2` access into a fixed `r13` offset and deletes the relocation, leaving MWCC's anonymous literal pool (`@39`, `@40`, ...) unreferenced for mwld to dead-strip. The symptom is `main.dol` short by exactly the unit's `.sdata2` size, that section repacked from its first byte. (dtk's own objects survive: their literals carry global symbols.) The pragma also keeps any otherwise-uncalled function in the unit. Needed by `GXSetFog` and `__GXGetTexTileShift`.

- **`bl lbl_XXXX` vs `bl __shr2u`/`__shl2i` (u64 shifts) is a symbol-name diff, not a code diff:** the runtime helpers are anonymous `type:label` entries in `symbols.txt` (`0x8016B59C` = `__shr2u`, `0x8016B5A4` = `__shl2i`). Rename them as `type:function size:0x4 scope:global` (like `__div2i`) so objdiff resolves the call. The same goes for an 8-byte `.sbss` u64 that dtk split into two 4-byte symbols (`lbl_8066F3B8`/`BC`): merge into one `size:0x8`, else the low-word access shows as `lbl+0x4` vs `lbl_..BC`. Renaming a still-`fn_` function such as `OSWakeupThread` (`0x80180CE8`) also requires updating the `extern`s in already-matched units, or the link fails with `undefined: 'fn_...'`.

- **Base of a `.bss` table hoisted to the prologue (`lis`/`addi r31`, used later with `0x78(rX)`/`0x144(r31)` displacements): take `u8* tbl = table;` as the first local, pass it to the inline helpers, and index as `((u16*)(tbl + 0x78))[i]`.** Without the local the `lis`/`addi` is emitted out of line at the tail (89%). `*(u16*)(tbl + i * 2 + 0x78)` and `((u16*)tbl)[i + 0x3C]` leave a stray `addi`/`lhzx`. `__VIRetraceHandler` (`0x80187B3C`) 89% -> 100%. A sized extern (`u8 q[8]`) gives the `li rX, sym@sda21` form for a queue address.

- **`lis`/`addi r31` to one `.bss` object, then `addi rX,r31,0x20` / `addi rX,r31,0` to reach the object *after* it, means pooled data, not a pointer local:** MWCC addresses objects defined in the same unit off one base (`...bss.0`), and the `+0` form stays an `addi`, never `mr`. No `extern`/local-pointer form reproduces it (`stateCheckID` stalled at 97.7%). Claim the unit's `.bss` range and *define* the objects in the source. Keep them non-`static` so unclaimed asm still links (globals pool too). Layout rules: `static`s follow declaration order; globals go referenced-first in **first-use order**, then unreferenced ones in reverse declaration order. A discarded `(void)obj;` counts as a use and emits nothing, so it can pin the order. Place it where nothing else is live (at the end of `stateReadingFST` it stretched the pool base's lifetime, 73%). `stateCheckID` (`0x80184688`, `dvd.c` `.bss 0x8057D220-0x8057D2B8`) 97.7% -> 100%.

- **Two SDK statics with the same name (`AlarmHandler` in `SIBios.c` and `dvd.c`) collide:** dtk-dev renames the second to `AlarmHandler_<addr>` at link and unclaimed asm callers fail with `undefined: 'AlarmHandler_80184B70'`. Rename it that way in `symbols.txt` (`scope:global`) and define the function non-`static` under that name.

- **Claiming a function whose caller is already in the same unit can make MWCC inline it** (`-inline auto`): the caller shrinks (`AlarmHandler_80184B70` 0x44 -> 0x40), every later unit shifts 4 bytes, and `main.dol` breaks with ~48% of bytes differing even though each function reports 100% on its own. Wrap the definition in `#pragma dont_inline on` / `reset`. If the caller loads an argument (`lwz r3,executing`) the original callee takes an unused parameter; keep it in the prototype (`stateReadingID`, `0x80184C80`).

- **`.sdata2` symbols in compiled C are fine:** the `sda2_via_r13` option bakes those accesses as `r13` offsets (see [`baseline.md`](baseline.md#small-data-r13-problem)), so write them as ordinary C.<br />
  If `Range Error for small data relocation` appears, check that `build.ninja` was generated with the fork's `dtk-dev` and that `build/GVLE69/sda_bake.json` exists.

---

## General tactics

- Comments and whitespace do not affect output, except for `__LINE__`/`__FILE__` and whitespace inside string literals.
- Register allocation differences usually indicate a different expression shape or variable lifetime. Try reordering locals or introducing/removing a temporary.
- Instruction scheduling differences often come from the compiler hoisting a constant. Match the source structure rather than the instruction order directly.
- `__OSDoHotReset` (`0x8017E96C`): the original is `lis`/`addi r3,r3,0x2000` then `sth r0,2(r3)`, i.e. a hardware base register with a separate offset. Every C form of `__VIRegs[1] = 0` (address-declared array, cast local, `register`, `vi + 1`) folds the offset into the store (`sth 0x2002(r3)`) and tops out at 91%. Written as an `asm` function instead (same approach as `fn_8017A6EC`).
- **Loads that stay below an earlier store to a different global mean those globals are `volatile`.** MWCC reorders ordinary global loads above stores to other globals freely. If the original keeps a `lwz` pinned after a `stw` to an unrelated global (e.g. `lwz executing` after `stw ResumeFromHere`), `volatile` is the fix. It has to go on *all* the involved globals at once; single ones don't help. In `dvd.c` these are `Canceling` (`lbl_8066F2E0`), `ResumeFromHere` and `NumInternalRetry` (later-SDK declarations). That took the inlined `CheckCancel` in `cbForStateGettingError` (`0x80184174`) from 97.2% to 100%. To test a hypothesis like this, compile another function that inlines the same helper (here `fn_80184A74`) and diff it too.
- If you're stuck around 95% on register choice, [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) can brute-force equivalent C forms.

---

### Claiming a function that uses a `.bss` static

dtk renames the referenced `lbl_XXXXXXXX` bss symbol to `<Name>` (`scope:local`) once the function is split, and the build then fails to link if an unclaimed neighbor also references it. Also add a `.bss start:.. end:..` line to the unit's split, set the symbol to `scope:global` in `symbols.txt`, and define it non-`static` in the source (`__DVDClearWaitingQueue` / `WaitingQueue`).

### `__OSInitAudioSystem` (`Dolphin/os/OSAudioSystem.c`)

ac-decomp's version is marked nonmatching but gets 100% here as-is, including the `u8 errFlag = 0;` local and the dead `if (... + 0x7FAC0000U != 0x4348) {}` / `reg16 != 42069;` statements. Those dead statements keep `reg16` live (`clrlwi r5`) and add the 8 bytes of frame; without them it stalls at ~92-96%. `__DSPRegs` is `volatile u16 __DSPRegs[0x20] : 0xCC005000;`. The `DSPInitCode` data symbol needed `scope:global` in `symbols.txt` to be referenced by its real name.

## Confirmed non-matches

Don't re-guess these.

Checked across every entry below, none of these helped: compiler versions `GC/1.0` to `2.0` (`1.2.5n` is best or tied everywhere), `-O4,s`/`-O4`/`-O3`/`-O2`, `-inline off`, `-use_lmw_stmw on`, and `#pragma scheduling off`/`peephole off`/both.

- `GXLoadTexObjPreLoaded` (`0x8018E3A0`): body matches (99.88%, only `@sda21` symbol-name diffs), but the stack frame is `-0x28` vs `-0x40`. No effect: aliasing locals, adding/removing register writes, own TU, `#pragma scheduling on`. Hoisting the `GXTex*Ids[id]` reads makes it worse. Unused `volatile u32` locals close the 24-byte gap exactly, but that's padding, not a reconstruction, so it stays `NonMatching`. An inline wrapper around the `tlutRegionCallback` call adds 8 bytes (see the inline-local frame note above), but no SDK helper is known that would account for all 24. `GX_WRITE_RAS_REG` as an inline function (84.6%) and SDK-style `t`/`r` cast locals at function level do nothing.
- `__SetSURegs` (`0x8018E80C`, `Dolphin/gx/GXSetSUTexRegs.c`): `NonMatching`, 96.85%. Best clean-ish C is 38/40 instructions identical:
  - The single shared `gx + tcoord*4` `add` needs a second alias of the local `g = __GXData` pointer, with the two 16-bit `__rlwimi` inserts *reading* through the alias and writing through `g`.
  - It also needs the artificial `suTs1[w = tcoord]` in the last FIFO write; without it, codegen falls back to 48 diff lines.
  - Remaining: the original allocates the `s_bias` temp to r10 (ours r12) and schedules `li r5,0x61` before the first `clrlwi`. Ours leaves r10/r11 unused, so the `w = tcoord` hack is standing in for some real extra value.
  - No effect: local order, `u8`/`u32`/`int` bias, int casts, which pointer the bias/`tMode0`/`tImage0` reads use, `extern ... * const __GXData`, declare-at-address `GXWGFifo`. Plain-C `SET_REG_FIELD` is much worse.
  - decomp-permuter plateaued at score 35 after ~300k iterations.
- `GXSetTevColor` (`0x8018F480`, `Dolphin/gx/GXSetTevColor.c`): `NonMatching`, 55.83%. The color is one `lwz` word with 8-bit `rlwimi` fields, and the `224/225 + id*2` field is a plain `<< 24` init. The original interleaves the writes (one FIFO write for `regRA`, then `regBG` computed and written three times).
  - Remaining: *ours* has an extra `addi r8,r4,0` accumulator copy after the first `regRA` `rlwimi` (0x64 bytes vs the original's 0x60). The original puts the `slwi` result straight into a fresh register (`slwi r7,r4,24`), while ours computes it in place and copies it later. The sibling `GXSetTevKColor` does have that copy in the original, and our source shape matches it there.
  - No effect: the full product of {inline `*(u32*)&color`, `c` local first or last} x {`<< 24` init, `reg = 0` with the ID field last} x {interleaved or batched writes} x {plain or `* const __GXData`} x {macro or declare-at-address `GXWGFifo`} x {`u32` or `int` `id`}, all at 55.8-56.9%. The SDK form with 11-bit `color.r`/`color.a` fields drops to 10%.
- `GXSetProjection` (`0x8018FF90`, `Dolphin/gx/GXTransform.c`): `NonMatching`, 97.37% at unit level; the unit's other function `GXSetProjectionv` is 100%. Uses the SDK's inline `asm` `WriteProjPS` (`psq_l`/`psq_st`), `int type`, and direct `__GXData->` access for the whole tail (a `gx2` local drops it to 71%).
  - Remaining: the original schedules `lwz r4,__GXData` immediately after `lis r5,0xcc01`, before the `li 0x10`/FIFO writes; ours emits it just before its first use, six instructions later, which rotates r4/r5/r6. No effect: a `mtxp` pointer local, a `projType` temp, reordering `bpSentNot` against the last FIFO write, assigning a `gx2` local after the `u8` write.
- `__GXSetViewport` (`0x80190248`, `Dolphin/gx/GXSetViewport.c`): `NonMatching`, 88.59%. Its caller `GXSetViewport` (`0x801902D8`) is 100%. The game's `__GXData` layout differs from ac-decomp: viewport floats sit at `0x4F4`-`0x508`, then `zOffset` (`0x50C`) and `zScale` (`0x510`), with no jitter/field logic. Needs `#pragma fp_contract off` (otherwise `fmadds`/`fnmsubs` appear) and `extern const f32` for `lbl_80670778` (0.5) / `lbl_8067077C` (342.0) instead of literals.
  - Remaining: FP scheduling and register allocation (the original loads 342.0 late into a reused `f6` and keeps everything inside f0-f9; ours spills into f10/f11). Brute-forced all 120 orderings of the `sy`/`ox`/`oy`/`zmin`/`zmax` statements; no effect from `zmin`/`zmax` locals vs inline.
- `GXSetScissorBoxOffset` (`0x80190398`, `Dolphin/gx/GXSetScissorBoxOffset.c`): `NonMatching`, 92.5%. The best form uses *unshifted* `u32 x = x_off + 342; u32 y = y_off + 342;` locals, with the `>> 1` inside each `SET_REG_FIELD`, plus declare-at-address `GXWGFifo` and direct `__GXData->bpSentNot`. That reproduces the first fold (`rlwimi r4,rX,31,22,31`) *and* the `addi r5,r4,0` copy. Shifted `hx`/`hy` locals fold both shifts but drop the copy. No locals keeps the copy but emits a separate `srwi` (86.25%).
  - Remaining: `x` and `y` get swapped registers (ours x→r0, y→r5; the original x→r5, y→r0). So the copy into r5 clobbers `y`, and the second `>> 1` can't fold (`srwi` plus `rlwimi ...,10,12,21` instead of `rlwimi ...,9,12,21`). No effect: all 144 combinations of {`u32`/`s32`/`int`/`unsigned int`} x declaration order x assignment order x where `reg = 0` goes; `+=` on the params; one reused temp; mixed shifted/unshifted locals; a second accumulator variable.
- `AIInit` (`Dolphin/ai/AIInit.c`): `NonMatching`, 95.05%. The original keeps `ori r0,r0,0` nops where the `vol = 0` inserts fold away (ours emits `rlwimi` or drops them), copies `stack` to r30 (ours r31), and stores the u64 low words via separate `lbl_8066F424`-style symbols (ours reloc as `+4`). Hi/lo `u32` externs fix the relocs but drop to 17%.
- `GXSetTexCopyDst` (`0x801929BC`, `Dolphin/gx/GXSetTexCopyDst.c`): `NonMatching`, 94.41%. Needs `fmt` as `int`, `u16` width/height on the `__GetImageTileCount` prototype, a direct `__rlwimi(cpTex, peTexFmt, 0, 28, 28)`, a `u8 mipmap` param, `extern ... * const __GXData` with direct access up to the call, and a `gx` local reloaded after it.
  - Remaining: the original emits the two argument copies as `addi r5,r7,0` then `addi r4,r8,0`, so `__GXData` can reuse the still-free r4; ours emits them in the opposite order and has to put `__GXData` in r6. No effect: `u32`/`int` `wd`/`ht`, `w`/`h` locals, a `g` local for the `cpTexZ`/`cpTex` block, moving `peTexFmt &= 7`, `#pragma scheduling off` (42%), `#pragma peephole off` (32%).
- `OSCreateThread` (`0x8018037C`, `Dolphin/os/OSCreateThread.c`): `NonMatching`, 99.51%. An unused `u64 fill = -1` local closes the 8-byte frame gap (padding, not reconstruction). Remaining: the original passes `&thread->context` as `addi r3,r31,0`; ours is `mr r3,r31` (a peephole-pass difference, see the `addi`/`mr` note above). No effect: casts, `+ 0`, a `ctx` local, call order, `#pragma peephole off` (87%), chained `fpr`/`psf` store (73%). Also no effect on either the copy or the 8-byte frame gap: `OSInitThreadQueue` (a real function at 0x8017FD64, so in the same TU) as an `inline` for `queueJoin`/`queueMutex`, the enqueue written as an inline helper, `f64 fpr`/`psf` with `*(u64*)&...fpr[i]` stores, and reordering or reshaping the `sp` setup and the two `((u32*)sp)[n] = 0` stores.
- `GXLoadLightObjImm` (`0x8018D8D4`, `Dolphin/gx/GXLoadLightObjImm.c`): `NonMatching`, 92.42%. This game's version takes `light` as a bitmask (`cntlzw`, `31 - n`, `& 7`, `<< 4`, `+ 0x600`), not ac-decomp's `GXLightID` switch. The zero/color/`psq_l`/`stw`/`psq_st` run only inlines via a `static inline` helper with an `asm {}` block (a `static asm` function stays a `bl`).
  - Remaining: the original keeps the `cntlzw` chain in r0, the fifo pointer in r4, and the first `stw` of the address is `stwu` (which also sets the pointer). Ours puts the chain in r4/r5 and emits a plain `stw` plus an `addi r5,r7,-0x8000`. Writing `*fifo = ...` through a `volatile u32*` local produces the `stwu` but shifts registers (92.4% either way). No effect: `idx` temp vs inline expression, `fifo` local ordering, `* const __GXData`, declare-at-address `GXWGFifo`.
- `GXInit` (`0x801908D8`, `Dolphin/gx/GXInit.c`): `NonMatching`, 99.47%. Needs `#pragma peephole off`, `extern __GXDataStruct* const __GXData;` (without `const` the pointer is reloaded between every store in a straight-line block, 61%), `EnableWriteGatherPipe` as `static inline`, and a `GXFifoObj* fifoObj = &FifoObj;` local -- without the local the address is re-materialized at all four uses and the frame loses a saved register (96.4%).
  - Remaining: exactly one instruction. The original materializes the address straight into its saved register (`addi r31,r4,FifoObj@l`); ours routes it through r0 and adds `mr r30,r0`. That swaps r30/r31 for the rest of the function, which accounts for every other diff line.
  - No effect: initializer vs separate assignment statement, declaration order among the locals, `const`/`register`/`void*`/redundant cast on the local, `FifoObj` declared as `GXFifoObj[1]`/`u8[0x80]`/a file-local `static` definition, assigning the local at four different points in the body, mixing `&FifoObj` and the local across the call sites, and a real `static asm` function in place of the pragma. `#pragma scheduling off` is far worse (57%).
