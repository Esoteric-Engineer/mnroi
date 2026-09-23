# Matching Notes

Compiler/linker behavior and techniques learned while matching functions in this game. Helpful to review when a function is stuck short of 100%. Functions that are stuck for now live in [`nonmatching.md`](nonmatching.md).

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

- **MWCC pools each translation unit's `.data` -- strings *and* file statics -- into one object addressed from a single base register.** This is the default (ac-decomp disables it per-file with `-pool off`). The giveaway is a `lis`/`addi` pair that materializes one `.data` address into a saved register, followed by bare `addi rX, base, imm` with **no relocation** for every string and static in the unit. dtk merges the whole run into one `lbl_XXXXXXXX` object, so the pool boundary is also the TU boundary: anything reachable by immediate offset from that base belongs to the same source file.

  Two consequences for matching:
  - **The pool's contents fix every offset**, so a function can only match once *all* of its TU's other pool users are in the same unit. Pulling one function out early gives the right instructions with the wrong immediates.
  - **Addresses materialized from the pool base are not hoisted out of loops**, because the `addi` is late address materialization rather than a frontend expression. Standing in for the pool with `extern u8 blob[]` plus explicit offsets *is* frontend arithmetic, so LICM lifts each `blob + off` into its own saved register -- which grows the frame and renumbers every saved register. If a function is instruction-perfect but has extra hoisted `addi`s and an off-by-N `stmw`, look for a pool.

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

- **`#pragma peephole off` fixes several distinct symptoms; try it early** (the original's state comes from an `asm` function earlier in its real translation unit, see above):
  - Redundant `b <next instruction>` branches at loop/branch join points (often two or three in a row, so translate them literally), plus a separate `cmplwi`/`blt` where ours folds the compare. In a loop-heavy function this is worth far more than the symptom suggests: `GXInit` 84.7% -> 99.2% in one change, restoring ~18 instructions across six loops. A `static asm` stub at the top of the file produces byte-identical output, so prefer the pragma, which emits no extra function.
  - `stwu` before `mr r4,r3` (arg copy after frame setup) in a tiny wrapper. Default codegen emits the copy first (63%); `scheduling off` alone gets 76-82% and misorders `li`/`crclr`. Matched `OSRegisterVersion` (`0x8017B3C0`).
  - `clrlwi` separate from a following `slwi` (indexing a table by a `u8` param), where ours emits a merged `clrlslwi`. Took `__OSSetExceptionHandler`/`__OSGetExceptionHandler` (`0x8017B234`/`0x8017B250`) from 66-75% to 100%.
  - Early `return 0;` compiles to a bare `blr` where the original branches to the shared exit (`b .L_end`) in a tiny pointer-returning function. Restructuring into a single `r` result variable has no effect. Matched `__GXDefaultTlutRegionCallback` (`0x80190580`).

- **Align-up arithmetic gets reassociated (`add size, a` first) when written with plain `unsigned long` temps:** use the SDK's shape instead: a `ROUNDUP(x, a)` macro `(((unsigned long)(x) + (a)-1) & ~((a)-1))`, with `unsigned char*` locals for the pointer add (`(u8*)ptr + size`). Took `OSAllocFromArenaLo` (`0x8017BBE4`) from 98% to 100%.

- **Loop tail emits `bne top; b exit` where ours emits `beq exit; b top`:** write the back-edge as `if (x != 0) { continue; } break;` instead of `if (x == 0) { break; }`. Took `OSCancelThread`'s inlined `UpdatePriority` loop from 99.86% to 100%.

- **Inlined `UpdatePriority` loop (`OSSetThreadPriority`, `0x80180DEC`) with `priority`/`enabled` in swapped saved registers (r30/r31, 94.6%):** declare the loop cursor `OSThread* t;` at function scope *before* `int enabled;`, not inside the `if`. This game's version has no asserts and ends with `if (RunQueueHint != 0) SelectThread(0)` instead of `__OSReschedule`.
- **Inlined `__OSGetEffectivePriority` loop gets the wrong registers (priority in r4, blocked thread in r5) and the frame comes out 8 bytes too big:** write it as a `static inline` helper, read the blocked thread's priority once into a local inside `if (b) { long bp = b->priority; if (bp < priority) priority = bp; }`, and assign straight to `thread->priority = EffPrio(thread)` with no function-scope temps. Took `OSResumeThread` (`0x80180804`) from 99% to 100%.

- **A base address hoisted into a saved register once (`lis`/`addi r31,RunQueue`), with later `r31+offset` uses (`addi r3,r31,0x730`):** keep a local `OSThreadQueue* rq = RunQueue;` and derive every use from `rq`. Referencing the global directly re-emits `lis`/`addi` at each use (89%). If two uses share the same `(u8*)rq + off` expression they get CSE'd into an extra saved register; write the second as `rq + 230` (pointer arithmetic, same address) instead. Also inline `OSGetCurrentThread` as a `static inline` reading `__gCurrentThread : 0x800000E4` (declare-at-address) to get the original's extra `addi r3,rX,0` copy. Matched `SelectThread` (`0x801800E8`).

- **CP counter reads (`GXReadGPMetric`): use the SDK's own `inline u32 __GXReadCPCounterU32(u32 regAddrL, u32 regAddrH)` from `GXRegs.h`, taking register *indices*, plus `#pragma scheduling off`.** With scheduling on, MWCC swaps the two volatile loads in each retry loop and hoists the next counter's setup above the previous one's `slwi`/`or`. A hand-written helper that takes two pointers only reached 91%, with or without scheduling off. The SDK form with scheduling off is exact (0x80193C74).
- **`EXIBios.c` functions need `#pragma scheduling off`:** `EXIGetState` (0x80195440) went from 64% to 100% with it, and `UnlockedHandler` (below) needs it too. The original unit was probably built that way, so try it first for other `EXIBios` functions.
- **A callee that the original inlined needs a `static inline` copy of its body in the same unit (`EXIAttach`, `0x801948E8`).** The original inlined `EXIProbe` (result discarded) and the static `__EXIAttach` into `EXIAttach`, while `EXIProbe` also exists as its own function at `0x801947B4`. Write both as `static inline`/`static` in the unit that claims only `EXIAttach`, calling `__EXIProbe`/`EXIGetID` as externs (`__EXIProbe`/`fn_80195480`). Without `#pragma scheduling off` it was 73.7% (arg setup and `mr r29,r3` shuffled); with it, 100%.

- **Stack frame too small with no stack locals to account for it: look for an SDK inline helper that has its own pointer local.** MWCC reserves an 8-byte frame slot for an inlined function's local that stays live across a call inside that function, even when the local is register-allocated. An inline with no locals, or a local not live across a call, adds nothing, and the same local written at function level adds nothing either. `__GXCleanGPFifo` (0x80191F5C) matched only once it used the SDK's real `GXInitFifoPtrs` and `GXGetFifoBase` as `inline` functions, each with its `__GXFifoObj* realFifo = (__GXFifoObj*)fifo;` cast local. That moved the frame from `-0x98` to `-0xa8` and `dummyFifo` from `0x8(r1)` to `0x14(r1)`. A non-static `inline` that ends up uncalled is not emitted, so the unit's `.text` stays the same size.
- **`addi rD,rS,0` where ours has `mr rD,rS` comes from the peephole pass:** with `-opt nopeephole` every copy is `mr`, while normal builds turn some copies into `addi`. Parameter copies into saved registers ahead of an early-return branch come out as `addi`, and so does a copy emitted next to another copy. How the address is spelled has no effect: `&t->ctx`, `(C*)t`, `&t[0].ctx` and a `ctx` local all give the same instruction. So treat this as a scheduling/peephole-context difference, not as missing `+0` address arithmetic (`OSCreateThread`, `GXSetScissorBoxOffset`).
- **A caller-less `asm` function (`__OSLoadFPUContext`, `0x8017C2DC`) is dropped by the linker once `Matching`:** `main.dol` comes out short by exactly its size (0x124). Add it to `force_active` in `config/GVLE69/config.yml`.
- **Clearing a bit in a `volatile u8` (`x &= 0xBF`) gives `andi. r0,r0,0xbf`; the original's `rlwinm r0,r0,0,26,24` comes from `x &= ~0x40`** (a full-width mask). `#pragma peephole off` makes it worse (90%: loses the record-form `rlwinm.` test). Matched `__PADDisableRecalibration` (`0x8018B5A8`), with `volatile u8 x : 0x800030E3;` declare-at-address.
- **Original uses `stmw`/`lmw` for a 3-register save where ours emits individual `stw`/`lwz` (same `-use_lmw_stmw on`): the unit was built for size, add `#pragma optimize_for_size on`.** Checked on `stricmp` (`0x801724AC`): only `-O4,s` (or the pragma) yields `stmw r29`; `-O4,p` never does, on any compiler version. Also the `extsb r3,r0` + separate `cmpwi r3,0` needs `#pragma peephole off`, and `tolower(*s1) == tolower(*s2)` evaluates the right call first unless the two results are named locals assigned in a comma expression.

- **Runtime (`GC/1.3.2`) `vsprintf`/`vsnprintf` (`0x80171088`/`0x801710E4`): plain C stalls at 37%.** The original has an 8-aligned `-0x68` frame (ours rounds to `-0x70`) and uses r9-r11 as temps; both are compiler-version behaviour, not source shape. Written as `nofralloc` asm: 100%.

- **Frame 8 bytes too small when the original inlined `__OSLockSram` (`OSGetSoundMode`, `0x8017F79C`): wrap the shared `LockSram(offset)` inline in a second `static inline OSSram* __OSLockSramI(void)` and call that.** Calling `LockSram(0)` directly is 99.84% (every instruction right, frame `-0x18` vs `-0x20`); the extra inline level supplies the 8-byte slot (same mechanism as the inline-local note above). Siblings `OSGetProgressiveMode`/`OSSetProgressiveMode`/`OSGetWirelessID` should use the same shape (`Scb` at `0x8057C5C0`, `flags` at `OSSram+0x13`, unlock is `fn_8017F2E4(commit, offset)`). For the setter `OSSetSoundMode` (`0x8017F81C`) the wrapper must also hold its result in a *named local* (`OSSram* sram = LockSram(0); return sram;`); a bare `return LockSram(0);` wrapper is 99.83% with the frame `-0x18` vs `-0x20`, and a third nesting level breaks the inlining (60%).

- **`lis`/`addi` of a `.bss` array emitted at the top of the function (base kept live, one more saved register than ours) while ours re-materializes it late (94%): take `u16* regs = lbl_XXXX;` as the first local and index through it.** Matched `setVerticalRegs` (`0x801888B0`, 100% first try after that); `regs[54] & 1` picks the 480p `c`/`d` multipliers here, not ac-decomp's `equ >= 10`. The `volatile u64 changed |= bit` is a single 8-byte `.sbss` symbol (merge the split `lbl_8066F3A8`/`AC` in `symbols.txt`).

- **Inlined static callee's locals supply the frame and the register order (`EXISync`, `0x80194330`):** writing EXI's `CompleteTransfer` by hand inside `EXISync` gave 98.2% (frame `-0x28` vs `-0x30`, `exi`/`regs` in r29/r31 instead of r31/r29). Moving the body into a `static inline void CompleteTransfer(s32 chan)` with its own locals (`exi`, `buf`, `data`, `i`, `len`) and calling it fixed both, 100% first try.

- **`for (i = 0; i < n; ++i)` compiles to `cmpwi n,0` where the original has `li i,0` / `cmpw i,n`: check the type of `n`.** With `typedef int s32` the compiler folds the first test against the known zero start; with the SDK's `typedef long s32` on the parameter it emits the original's un-folded `cmpw` and matches (96.2% -> 100%). Both unrolled-by-8 loops in `DBGEXIImm` (`0x801965EC`) came out right with no other change.

- **Inlining:** A function may contain the inlined body of a method from a not-yet-reconstructed header. A `static` helper with a single caller can be inlined with no separate `bl`, which is why an original may have no call where a reference decomp appears to have one.

- **A hardware-register read where the original keeps `lis`/`addi 0x3000`/`lwz 0x24(r3)` (base add not folded into the displacement), plus `cmpwi` and a `b` to a shared `blr`: `#pragma peephole off`, and use a signed `int` for the flag.** The declare-at-address `__PIRegs` form is still right; peephole off only stops the displacement folding (`lwz 0x3024`). Matched `OSGetResetCode` (`0x8017EBB4`).

- **Tiny wrapper where the original emits `stwu` before `li r4,0`/`addi r5,r1,N` (arg setup after frame setup), and ours hoists `li`/`addi` above `stwu` (74%): `#pragma scheduling off`.** `peephole off` alone only swaps the two arg setups (88%); scheduling off alone is 100%. Matched `UnlockedHandler` (`0x80195458`, `EXIGetID(chan, 0, &id)` wrapper).

- **A loop that re-reads a struct field the loop condition already loaded (original has `lwz` in the cond and again in the body) needs enum-typed fields, not `int`:** `int` lets MWCC reuse the cond load (97.5%); `enum` fields on the list struct and inline helper params matched the codegen (`GXSetVtxAttrFmtv`, 99.9%).

- **An inlined `SetTimeoutAlarm(OSTime)` (saves r30/r31, alarm base loaded before the tick math) needs a `static` helper taking the `s64` timeout as a parameter,** not the `OSCreateAlarm`/`OSSetAlarm` calls written inline (60.9%). Call it as `SetTimeoutAlarm((s64)((*(u32*)0x800000F8 / 4) * 10))`. Matched `DVDLowStopMotor` (`0x80187660`); the same shape should fit its `DVDLowRequestError`-style siblings. Claiming it made dtk-dev auto-name `OSCreateAlarm`/`AlarmForTimeout`/`AlarmHandlerForTimeout` (set the last two `scope:global`, update other units' `extern`s).

- **A `dont_inline` helper kept for its own address can't be called from a later function that inlined it in the original:** `stateReady` (`0x80184E2C`) shows `lis`/`addi cbForStateMotorStopped` + `bl DVDLowWaitCoverClose` inline (and `executing` in r4), where calling `stateMotorStopped()` gives `bl stateMotorStopped` (95%). Write the helper's body out at the call site. `stateCoverClosed` (not `dont_inline`) does inline into it.

- **Claiming a jump table forces you to claim the strings before it (`.data` must be contiguous), and a named global array is emitted before string literals:** `char lbl_804D2184[] = "..."` put the string ahead of `"load fst\n"` and shifted `.data` (60 bytes differ, function still 100%). Write the string inline at each use so first-use order applies. `stateBusy` (`0x8018505C`); note the original has a `length == 0` early finish that ac-decomp lacks.

- **Alarm-queue walk with `next` cached (`alarm ? alarm->next : 0` before and at the end of each iteration) plus stray `b <next>` branches:** write `next = alarm ? alarm->next : 0;` ahead of a `while (alarm)` loop and again at the loop tail, with `#pragma peephole off`. A `for` loop with the null check at the head is 58%. Matched `fn_8017BB24` (`0x8017BB24`).

- **A variadic `OSPanic`-style function needs `__builtin_va_info(&args)` (as in `OSReport`) and its string literals claimed as `.data`:** the strings sit in one blob whose symbol dtk sized too big (`@13` 0x16 plus one 0x2C6 `lbl_`), so split the blob in `symbols.txt` at the claimed end (`ends within symbol` error otherwise). A string another unclaimed function still references (`@13_804D0EF8` undefined at link) must be renamed to a real global and *defined* in the source as `char Name[] = "..."` used at its first use; it lands in place. Matched `OSPanic` (`0x8017CBFC`); `OSSetErrorHandler` and `__OSUnhandledException` share that `.data` blob.

- **A u64 field split as `u32 pad; u32 lo;` in a struct can change register allocation vs. `*((u32*)&u64f + 1)` casts:** `OSSetErrorHandler` (`0x8017CD28`) sat at 99.1% with only the thread-walk pointer in r7 instead of r6 until `fpscr` was declared as `u32 fpscr_pad; u32 fpscr;` and accessed by name. This game's version also toggles the FPE enable bits (MSR FE0/FE1, FPSCR) across `__OSActiveThreadQueue` (head at `0x800000DC`), unlike ac-decomp's plain table swap.

- **A string blob shared by several units: claim from the first string (8-aligned), define that first string as a global `char X[]`, and use plain literals for the rest.** `__OSCacheInit`/`DMAErrorHandler` (`0x8017C1E8`/`0x8017C088`) share `.data 0x804D0AF0` with the already-matched asm `L2GlobalInvalidate`, whose `>>> L2 INVALIDATE` string sits first. Starting the claim at the 4-mod-8 `0x804D0B1C` shifted `main.dol` by +32 (per-function fuzzy was still ~99%). Starting at `0x804D0AF0` and defining `char L2InvalidateStr[] = "..."` (renamed from `@69`, `scope:global`, `OSCache.c` `extern` updated) matched. Also: inlined `L2Disable`/`L2Init` `sync`s are `asm { sync }` blocks, and `#pragma peephole off` is needed for the non-record `rlwinm`/`cmplwi` pairs.

- **A string-only `.data` claim starting 4-mod-8 also shifts `main.dol` (+32 here), not just jump tables:** `__OSContextInit`'s `"FPU-unavailable handler installed\n"` (`0x804D0ED4`) failed as its own unit at 100% per-function. Merge it into the neighbouring unit whose `.data` ends there (`OSDumpContext.c`, one original `OSContext.c`). The asm `OSSwitchFPUContext` before it means `#pragma peephole on` must *not* be added: keep peephole off, or `lis` hoists above the prologue.

- **A caller that inlines several public SDK functions (`__DVDPrepareResetAsync`, `0x80186474`, inlining `DVDCancelAllAsync` + `DVDPause` + `DVDResume`): write each as its own `static inline` with the SDK's locals and call them, don't flatten the bodies by hand.** Flat hand-inlining gets the instructions (96.5%) but not the saved-register numbering (callback/enabled rotated), and no declaration order fixes it; the nested `static inline` helpers gave 100% first try. `executing` must be non-`volatile` (volatile doubles the loads) and the `Canceling` flag (`lbl_8066F2E0`) `volatile unsigned long` (`cmplwi`).

- **A `static` helper inlined into its caller (`PopWaitingQueuePrio` in `__DVDPopWaitingQueue`, `0x80186668`) gives a frame 8 bytes too big (`-0x18` vs `-0x10`):** its local (`tmp`) stays live across the `OSRestoreInterrupts` call. Delete the helper and write its body inline in the caller's loop (re-calling `OSDisableInterrupts` there, as the original does). 99.875% -> 100%.

- **Inlined `ReadDiscBlocking`-style helper (`u8 block[0x30]`, `DVDReadAbsAsyncPrio` + status loop) with the frame 8 bytes short (`-0x40` vs `-0x48`):** write it as a `static inline` taking `void* addr`, with an extra `void* p = addr;` local and a trailing `(void)p;` (no other locals). Plain body-inline or a `DVDCommandBlock* b` local don't help (99.9% / 87%). Also use `s32` for the sbss cache and `0x800030F4` test (`cmpwi`, not `cmplwi`). Matched `fn_8017D4A4` (`0x8017D4A4`).

- **`PauseFlag`/`PausingFlag` (dvd `.sbss`) must be `volatile` too:** without it the `lwz PausingFlag` hoists above the `stw PauseFlag` (87%, plus an `addi`/`mr` r31 swap that follows from it). Same family as the `Canceling`/`ResumeFromHere` note below. Matched `DVDResume` (`0x80185FD8`).

- **C++ class layout must be exact:** One wrong member offset breaks matching in that class, and vtable order must match the original virtual declaration order.

### Newlib / libgcc / tiny runtime functions are GCC output: write them as `nofralloc` asm

Scope: everything in `Runtime.PPCEABI.H` that comes from Newlib or libgcc (string, stdio glue, scanf/printf, libm floats, `atoi`, `__pure_virtual`), plus the small runtime wrappers around them. These were compiled by GCC, not MWCC, and MWCC C never reaches them. Each one attempted as asm matched (mostly first try); C stalled at 7-84% on all of them. **Go straight to `nofralloc` asm; don't spend iterations on C.** Ignore the queue names for this range where noted: they come from size and order only.

**Tells** (any one is enough):

| Tell | What MWCC does instead |
| --- | --- |
| `stwu r1,-N` first, then `mflr r0`, then `stw r0,N+4(r1)` (LR saved *after* the frame is made), incl. the `-8` frame of tiny wrappers | `mflr` / `stw r0,4(r1)` before `stwu`; a `-8` frame is never emitted (`__pure_virtual` C/C++ gives 99.5% with `-0x10`; `atof`/`atoi` with `scheduling off` + `peephole off` 99.6%, frame still `-0x10`) |
| `mr. r3,r3` after a call; `addic.` / `subic.` loop counters; `stmw rN` *before* `stw r0` | `cmpwi`; `cmplwi`; the reverse order |
| Word-at-a-time null test: `andi. r0,rX,3` / `lwz` / `subis -0x101` / `subi -0x101` / `andc` / `and.`, with `lis`+`ori 0x8080` emitted twice; `cmplwi r5,3` / `ble` for `TOO_SMALL_LITTLE_BLOCK` | `clrlwi.`, one `lis 0x8081` constant, no peeled first-word check (27%) |
| Varargs prologue that saves only the *unnamed* args (`stw r5..r10`, r3/r4 never stored), `lis rX,0x200` va_list header, `bne cr1` skipping `stfd f1..f8` | `__builtin_va_info` saves r3-r10 with `mflr` first, on every compiler version `GC/1.0`-`3.0a5.2` (7-35%); the va_list is also copied to a temp before the call (pass-by-value struct) |
| Unprototyped indirect call as `mtlr rN` / `crclr 6` / `blrl` | `mtctr` / `bctrl` |
| Temps allocated high to low (r9-r11 first), args never copied, shared `subi r3,r4,1; blr` exit, `stbu` in loops | r5-r7 plus copies, `stbx`, per-path epilogues |
| Float code via stack `stfs`/`lwz` (`GET_FLOAT_WORD`), `lis`+`ori`+`cmpw` constants, `clrlslwi` | (libm `tanf`) |

**Asm mechanics:**

- Frameless functions (`strncpy`, string routines) use only r0/r3-r5/r8-r11 and save nothing, so the asm has no prologue.
- Reference `.sdata` floats by bare name in MWCC inline asm (`lfs f2, lbl_8066C17C`); `@sda21(r0)` is a syntax error.
- Reference unclaimed `.data` as `extern char lbl_804D02A8[]` and use `@ha`/`@l` (like `isdigit`'s `lbl_8049C6A1`).
- A second entry inside a unit is defined with `entry` after a forward `extern` (`terminate` inside `fn_8017A5CC.c`).
- Calls to real functions are plain `bl name`; other units' callers reference renamed functions by name in their own asm, so a rename means grepping `src/` for the old `fn_` name.
- `char` is signed on this target (`extsb`), so Newlib's `u_char` is `char`.

**Old Newlib signatures:** stdio glue has no `reent` argument; `fp->_data` (`0x5C`) is the reent passed on. `FILE` is 0x60 bytes: `_p` `0x0`, `_flags` `0xC` (`lha`/`lhz`), `_file` `0xE`, `_bf._base` `0x10`, `_bf._size` `0x14`, `_seek` `0x28`, `_nbuf` `0x4A`, `_blksize` `0x54`, `_offset` `0x58`, `_data` `0x5C`. `__sglue` is at `reent+0x1D8` (`_next` 0, `_niobs` 4, `_iobs` 8).

**Per function** (only what isn't covered above):

- `strlen` (`0x80172780`), `strcat`, `strrchr`, `strcmp` (`0x80172654`: word loop, then `extsb` byte loop), `strcpy`, `strncpy` (`0x801729E4`: the non-size-optimised body, aligned word loop with `DETECT_NULL`, byte loop, then `count-- > 0` zero-pad). Queue names here are by size only: `0x801727EC` (0x6C) is a lowercase-in-place loop calling `tolower`, not `strlen`.
- `strnicmp` (`0x80172858`) and `stricmp` (`0x801724AC`): C gets the loop layout but never the frame. Best C for `strnicmp` (78.5%) was `for (; n-- != 0 && (c1 = tolower(*s1), c2 = tolower(*s2), c1 == c2) && n != 0 && (int)*(unsigned char*)s1 != 0 && (int)*(unsigned char*)s2 != 0; s1++, s2++) {}` (increments as the `for` update reproduce the jump-into-condition layout; the casts give `lbz`/`cmpwi` without `extsb`), but the frame is `-0x20` with `stw r0` before `stmw` (original `-0x18`, after). `optimize_for_size`, `scheduling off`, `register`, local order and `while`/`break` shapes changed nothing. `stricmp` should get the same asm treatment (see `nonmatching.md`).
- `sprintf` (`0x8016FFE0`), `sscanf` (`0x801700C0`), `fn_8017A75C` (varargs-looking, never uses the va_list).
- `__sccl` (`0x80170FB4`, scanf `%[` table builder): C with `optimize_for_size` gets the descending `bdnz` fill loop but none of the allocation above. `register`, `if` vs `switch` and every `opt_*` pragma did nothing.
- `itoa` (`0x8017367C`): `__utoa` inlined (`divwu`/`mullw`/`subf` digit loop, `lbzx` from the `0123456789abcdefghijklmnopqrstuvwxyz` table at `0x804D02A8`, `-` appended, then `strrev` as a plain `bl`). Digits are emitted least-significant first and the terminator is stored from the (zero) quotient register; the function returns `str` from r3.
- `_fwalk` (`0x80178A90`): `addic. r29,r3,0x1d8` null-checks `&ptr->__sglue`. Signature `_fwalk(reent, func)` with `func(fp)`. Callers `__srefill`/`fflush`/`fn_80178684` reference it by name.
- `__sread` (`0x80178BE8`): arg shuffle `mr r0,r4` / `mr r31,r3` / `mr r6,r5`; passes `fp->_data` and `_file` to `_read_r` (`0x80178EA4`).
- `__smakebuf` (`0x80178B10`): `_flags & __SNBF` uses `_nbuf` with size 1; otherwise `_fstat_r` (stat buf at `r1+8`, `st_mode` at `r1+0xC`), and `S_IFREG` + `_seek == __sseek` sets `_blksize` = 0x400 and `__SOPT`, else `__SNPT`. It always ends unbuffered (no malloc). Keep the `li r0,0; ori r0,r0,0x8000` pair for the `S_IFREG` compare verbatim.
- `_strtoul_r` (`0x80172028`; `_strtol_r` `0x80176E54`, matched as asm, is its signed twin: neg flag in r7, `cutoff` limit picked from `0x7fffffff`/`0x80000000` by that flag, and only r31 saved): old Newlib, `reent` first. `_ctype_ + 1` is `lbl_8049C6A1`; flag bits are `8` space, `4` digit, `3` alpha, `1` upper. Use it for any inlined `isspace`/`isdigit`/`isalpha`.
- `atof` (`0x801711F0`, `strtod(s, 0)`), `atoi` (`0x80171214`, `strtol(s, 0, 10)`), `fn_8017A6CC`/`fn_8017A6EC`: bare wrappers with argument `li`s between the `stw` and the `bl`.
- `__pure_virtual` (`0x80179C30`): calls `terminate` (`0x8017A5DC`).
- `tanf` (`0x8016DE5C`) and the rest of libm.
- `__ieee754_rem_pio2f` (`0x8016E8E4`): straight transliteration of Newlib `ef_rem_pio2.c` output (`stmw` before `stw r0`, `mfcr r30`/`mtcrf 128` around the `while(tx[nx-1]==zero)` loop, `fmadds`/`fmsubs`). Its tables are `.sdata2` objects (`two_over_pi` `0x8066FE44`, `npio2_hw` `0x8067015C`), which the original reaches as `subi rX,r13,N`. Use `la rX, sym` with the extern declared **`extern const char sym[4];`**: with the real size (`[0x84]`) the compiler treats it as far data and emits `li rX,0 [R_PPC_ADDR16]` (99.9%), while a small `const` size gives the sda21 reloc that bakes to the `r13` form (100%). Matched first try otherwise.

---

## Data, symbols, and relocations

- **Fresh anonymous data doesn't reliably land at the original's address:**

  A plain-C `static` local or a fresh string literal can report 100% fuzzy, but the linker places it wherever, so the address computation bakes in the wrong small-data offset and `main.dol` breaks by a byte or two.

  The fix is to reference dtk's auto-detected symbol instead. dtk sometimes names these with a compiler-internal disambiguator such as `cmdTypeAndStatus$371`. `$` is not valid in this compiler, so rename it to a plain identifier in `symbols.txt` with `scope:global`, leave the range unclaimed in `splits.txt`, and use a plain `extern`.

- **dtk only preserves a hand-set symbol name if it doesn't look auto-generated:**

  Renaming a compiler literal (`@267 = .sdata2:0x8067078C`) to `lbl_8067078C` is silently reverted on the next build, because `lbl_*`/`fn_*` are dtk's own naming patterns and get regenerated. The rename also never reaches `build/GVLE69/sda_bake.json`, so your `extern` keeps an unbaked `R_PPC_EMB_SDA21` relocation where the original object has a plain `r13` offset. This is visible in `tools/objdiff_mismatches.py` as a `DIFF_REPLACE` on the `lfs`/`lwz`, not as a byte diff.

  Give it a real name instead (`GXInitZScaleConst`). That survives regeneration, lands in the bake list, and the relocation resolves. Same rule as the `cmdTypeAndStatus$371` case above.

- **Claiming a function can make dtk-dev rename symbols, and unclaimed callers then fail to link (`undefined: '<name>'`).** Keep the new name, set it `scope:global` in `symbols.txt`, and update the `extern`s in sibling units. Cases seen:
  - `.sbss` symbols the function touches (`lbl_8066F330` -> `StopAtNextInt`, `scope:local`): `DVDLowWaitCoverClose` (`Callback`, `StopAtNextInt`, `WaitingCoverClose`). The next `ninja` rewrites `symbols.txt` and every other unit's `extern lbl_...` breaks.
  - A `.bss` static: dtk renames `lbl_XXXXXXXX` to `<Name>` (`scope:local`). Also add a `.bss start:.. end:..` line to the unit's split and define it non-`static` in the source (`__DVDClearWaitingQueue` / `WaitingQueue`).
  - A still-`fn_` function (`OSWakeupThread`, `0x80180CE8`): update the `extern`s in already-matched units too.
  - Two SDK statics with the same name (`AlarmHandler` in `SIBios.c` and `dvd.c`): dtk-dev renames the second to `AlarmHandler_<addr>`. Rename it that way (`scope:global`) and define the function non-`static` under that name.
  - A `static` function claimed while its caller is still unclaimed (`cb` in `fstload.c`, `0x80186A80`): rename it `cb_<addr>` and define it non-`static` under that name (self-references in the source too). `tools/objdiff_mismatches.py` needs the full unit path (`Dolphin/dvd/fstload`) and the function name as linked (`cb_80186A80`).

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

- **`bl lbl_XXXX` vs `bl __shr2u`/`__shl2i` (u64 shifts) is a symbol-name diff, not a code diff:** the runtime helpers are anonymous `type:label` entries in `symbols.txt` (`0x8016B59C` = `__shr2u`, `0x8016B5A4` = `__shl2i`). Rename them as `type:function size:0x4 scope:global` (like `__div2i`) so objdiff resolves the call. The same goes for an 8-byte `.sbss` u64 that dtk split into two 4-byte symbols (`lbl_8066F3B8`/`BC`): merge into one `size:0x8`, else the low-word access shows as `lbl+0x4` vs `lbl_..BC`.

- **Base of a `.bss` table hoisted to the prologue (`lis`/`addi r31`, used later with `0x78(rX)`/`0x144(r31)` displacements): take `u8* tbl = table;` as the first local, pass it to the inline helpers, and index as `((u16*)(tbl + 0x78))[i]`.** Without the local the `lis`/`addi` is emitted out of line at the tail (89%). `*(u16*)(tbl + i * 2 + 0x78)` and `((u16*)tbl)[i + 0x3C]` leave a stray `addi`/`lhzx`. `__VIRetraceHandler` (`0x80187B3C`) 89% -> 100%. A sized extern (`u8 q[8]`) gives the `li rX, sym@sda21` form for a queue address.

- **`lis`/`addi r31` to one `.bss` object, then `addi rX,r31,0x20` / `addi rX,r31,0` to reach the object *after* it, means pooled data, not a pointer local:** MWCC addresses objects defined in the same unit off one base (`...bss.0`), and the `+0` form stays an `addi`, never `mr`. No `extern`/local-pointer form reproduces it (`stateCheckID` stalled at 97.7%). Claim the unit's `.bss` range and *define* the objects in the source. Keep them non-`static` so unclaimed asm still links (globals pool too). Layout rules: `static`s follow declaration order; globals go referenced-first in **first-use order**, then unreferenced ones in reverse declaration order. A discarded `(void)obj;` counts as a use and emits nothing, so it can pin the order. Place it where nothing else is live (at the end of `stateReadingFST` it stretched the pool base's lifetime, 73%). `stateCheckID` (`0x80184688`, `dvd.c` `.bss 0x8057D220-0x8057D2B8`) 97.7% -> 100%.

- **Pooled `.bss` owned by another unit: declare it as one extern struct plus a local base pointer.** `__DVDInterruptHandler` (`Dolphin/dvd/__DVDInterruptHandler.c`) addresses `CommandList`/`AlarmForTimeout`/`Prev`/`Curr` (defined in `DVDLowRead.c`) off one saved register (`lis`+`addi r30`, hoisted to the prologue). Separate externs give a `lis`/`addi` per symbol (84%). Mirroring the layout in a `DVDLowBss` struct, `extern DVDLowBss CommandList;` (the first symbol, so relocs stay `CommandList@ha/@l`), plus `DVDLowBss* bss = &CommandList;` as a local declared last, gets the hoisted base and the extra `stmw r27`. Pass `bss` into the inlined `ProcessNextCommand` too, or it re-materializes the address (96.8% -> 100%). No need to merge the TUs. The `(void)` trick from `DVDLowRead` only fixes pool order for *defined* symbols.

- **Claiming a function whose caller is already in the same unit can make MWCC inline it** (`-inline auto`): the caller shrinks (`AlarmHandler_80184B70` 0x44 -> 0x40), every later unit shifts 4 bytes, and `main.dol` breaks with ~48% of bytes differing even though each function reports 100% on its own. Wrap the definition in `#pragma dont_inline on` / `reset`. If the caller loads an argument (`lwz r3,executing`) the original callee takes an unused parameter; keep it in the prototype (`stateReadingID`, `0x80184C80`).

- **String literals for a unit live in three places -- claim them all with the unit or `main.dol` shifts:** `__fstLoad` (`0x80186B58`) has its long `OSReport` strings pooled in `.data` (`0x804D2810-0x804D2880`, 8-aligned, addressed off one `r31` base) but the 1-3 char ones (`"\n"`, `"OFF"`, `"ON"`) in `.sdata` (`0x8066C470-0x8066C480`, `li rX, lit@sda21`). Claim `.data`, `.sdata`, and the `.bss` of its `static` locals in `splits.txt`, and write the literals inline; matched 100% first try. The function-local `static block` (`block$16`) and file-static `bb2Buf` become plain `static` arrays in the unit. The unused `switch` on the drive state in ac-decomp's version compiles to nothing (empty loop `bne`), so omit it.

- **`.sdata2` symbols in compiled C are fine:** the `sda2_via_r13` option bakes those accesses as `r13` offsets (see [`baseline.md`](baseline.md#small-data-r13-problem)), so write them as ordinary C.<br />
  If `Range Error for small data relocation` appears, check that `build.ninja` was generated with the fork's `dtk-dev` and that `build/GVLE69/sda_bake.json` exists.

- **Struct fields of a pooled `.bss` static reached through a pointer/extern lose MWCC's hoisted address temps: `sth rX,0x106(base)` followed by `addi r11,base,0x106` (reused later as `lhz rY,0(r11)`) needs real defined objects.** `VIConfigurePan` (`0x80189278`): `extern` array + `HorVer` cast macro, and one extern struct with a base local passed to the inline helpers, gave 71-85%; claiming the pool and defining `regs`/`shdwRegs`/`HorVer` as globals (pinned with `(void)` uses) gave 94% with all displacements right. Define the *whole* pool including the neighbouring object that precedes the struct, or the base and every offset shift.

---

## General tactics

- Comments and whitespace do not affect output, except for `__LINE__`/`__FILE__` and whitespace inside string literals.
- Register allocation differences usually indicate a different expression shape or variable lifetime. Try reordering locals or introducing/removing a temporary.
- Instruction scheduling differences often come from the compiler hoisting a constant. Match the source structure rather than the instruction order directly.
- `__OSDoHotReset` (`0x8017E96C`): the original is `lis`/`addi r3,r3,0x2000` then `sth r0,2(r3)`, i.e. a hardware base register with a separate offset. Every C form of `__VIRegs[1] = 0` (address-declared array, cast local, `register`, `vi + 1`) folds the offset into the store (`sth 0x2002(r3)`) and tops out at 91%. Written as an `asm` function instead (same approach as `fn_8017A6EC`).
- **Loads that stay below an earlier store to a different global mean those globals are `volatile`.** MWCC reorders ordinary global loads above stores to other globals freely. If the original keeps a `lwz` pinned after a `stw` to an unrelated global (e.g. `lwz executing` after `stw ResumeFromHere`), `volatile` is the fix. It has to go on *all* the involved globals at once; single ones don't help. In `dvd.c` these are `Canceling` (`lbl_8066F2E0`), `ResumeFromHere` and `NumInternalRetry` (later-SDK declarations). That took the inlined `CheckCancel` in `cbForStateGettingError` (`0x80184174`) from 97.2% to 100%. To test a hypothesis like this, compile another function that inlines the same helper (here `cbForStateCheckID3`) and diff it too.
- If you're stuck around 95% on register choice, [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) can brute-force equivalent C forms.

- **Inlined `EXIClearInterrupts` in an interrupt handler with an `OSContext` local on the stack (`EXIIntrruptHandler`, `0x80194CEC`): `#pragma scheduling off`, a `static inline` copy of the helper, and declare the context as `long long ctx[0x2c8 / 8]`.** A `char[0x2c8]` local is 4-aligned (context at `0x14(r1)`, frame `-0x2f0`); the real `OSContext` is 8-aligned (`0x18(r1)`, `-0x2f8`). With scheduling on, saved-register order is wrong (chan/context/callback rotated). The handler must be non-`static` (`scope:global` in `symbols.txt`) because `EXIInit` still references it. `EXTIntrruptHandler` (`0x80194FCC`) matched with exactly this shape (no inline helper; the `0x500000U` literal must be unsigned or the shift becomes `sraw`). `TCIntrruptHandler` (`0x80194DB4`) matched 100% first try with the same shape plus a `static inline` copy of `CompleteTransfer` (its `immBuf` byte-store loop unrolls by 8 in the original too) and `EXIClearInterruptsI(chan, 0, 1, 0)`; `__OSMaskInterrupts(0x80000000U >> interrupt)` takes the raw `short`.

- **Naming a function can make dtk-dev rename its neighbours and re-scope symbols (`EXIInit`, `0x8019509C`):** renaming `fn_8019509C` re-derived `Ecb`, `EXIImm`, `EXISync`, `EXIGetID`, `__OSEnableBarnacle`, `__OSInIPL`, `IDSerialPort1`, `memmove`, ... in `symbols.txt`, and `Ecb`/`TCIntrruptHandler`/`IDSerialPort1` came back `scope:local`, so every existing unit that still said `lbl_8057DBE0` failed to link. Fix: `sed` the old names across `src/`, and flip the shared ones to `scope:global`. The build passing `main.dol: OK` afterwards confirms nothing moved. The EXI control regs are `__EXIRegs[5 * chan + 3]` (`0xC`/`0x20`/`0x34` off the base), not stride 4.

- **Pooled `.data` owned by another (asm) unit, where a struct-pointer local gets the base right but the wrong reload shape (`CompleteTransfer`, `0x80181764`, 98.97%): take `u8* b = lbl_804D1B78;` (the pool's first object) and reach each object as `((SIControl*)(b + 0x44))->x` / `((u32*)(b + 0x58))[i]`.** The original hoists `addi r6,r31,0x4c` (`&Si.inputBytes`) for the second read; an `extern SIData` struct with a `SIData* d` local, a `u32*` local, or macros on the extern itself all miss it (94-99%). The byte-offset form emits it. `SIClearTCInterrupt` is a `static inline`; `XferTime` (`lbl_8057D150`) and `TypeTime` are plain `.bss` externs, only `.data` is pooled.

- **A compare against an enum field (`FBMode == VI_XFBMODE_SF`) that comes out `cmplwi` where the original has `cmpwi`: type the struct field and the inline helper param as `int` (enum is signed).** `setFbbRegs` (`0x801885DC`) matched with `SomeVIStruct` copied from ac-decomp `vi.c` (offsets agree with this game), `calcFbbs` as two `static inline` calls, and `regs` as a `u16* regs = lbl_8057D418` local; the first attempt with `u32` was 99.34%.

- **A function that reaches several pooled statics through one base plus `u8*` byte-offset locals can stall at ~99.8% on saved-register numbering no declaration order fixes: claim the pool and define the real objects instead (`SIInterruptHandler`, `0x80181A60`).** With `u8* b`/`u8* bss` bases the shape was right but params landed in r21/r22 instead of r30/r31, `Si.poll` was reloaded after every volatile load (needed a `poll` local), and a hill-climb over declaration order topped out at 99.81% (last two hoisted temps swapped). Defining `Si`, `Type`, `Packet`, `Alarm`, `RDSTHandler`, `InputBufferVcount`... as real objects in the unit (claim `.data` from the pool's 8-aligned first object and the pool's `.bss`, keep them non-`static`, pin the order with `(void)obj;` at the top) matched 100% with **plain ac-decomp source, no hacks**: distinct objects also fix the aliasing, so non-volatile loads survive volatile ones. Test it cheaply first: paste the SDK source with `static` objects into the unit and diff (relocs and `+0x44` displacements differ, registers must not). The `.data` string that starts the pool (`<< Dolphin SDK - SI ... >>`) is the SDK version string; define it as a global `char lbl_804D1B78[] = "..."` first. Two more lessons: an inlined `static` helper (`SITransferNext`, `SIIsChanBusy`) must be `static inline` with its own locals (`i`, `packet`), or `i` is shared with later loops and the allocation changes; renaming the split `.bss` symbols means updating `extern`s and the `lbl_` names in the asm of sibling units (`SIBios.c`).

- **Two locals swap saved registers (`r28`/`r29`): sweep declaration order.** In `PADTypeAndStatusCallback` (`chan` copied from a global, `chanBit` derived from it) declaring the `chan` local *first* gave the original's `chan`->`r29`, `chanBit`->`r28`; the other four locals didn't matter. Also, assign it inside the first expression (`0x80000000 >> (c = global)`): a plain `int c = global;` loads into a temp and adds `addi r28,r7,0`. 5 locals is only 120 builds, so script it.

