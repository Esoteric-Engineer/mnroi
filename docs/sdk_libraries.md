# SDK library boundaries (`.text`, GVLE69)

Derived by aligning function sizes and order against the sibling `../ac-decomp` (same Dolphin SDK
build; most sizes match exactly) and by which hardware registers each function touches
(`0xCC00xxxx`: VI 0x2000, DSP/AR 0x5000, DVD 0x6000, SI 0x6400, EXI 0x6800, AI 0x6C00, FIFO 0x8000).
Boundaries are approximate to the function; confirm when you claim something near an edge.

| Range | Library | Notes |
|---|---|---|
| 0x80169134-0x80169164 | os | two tiny functions |
| 0x8016D000-0x8017A5CC | C runtime / MSL libc | exceptions, `__div2u`, memmove, printf, strtol, sin, atan2. **Not** in ac-decomp's MSL version; no reference yet |
| 0x8017A5CC-0x801814F4 | os | interrupts, memory protection, reset, SRAM, system call, threads |
| 0x801814F4-0x80181708 | exi | |
| 0x80181708-0x80183070 | si | |
| 0x80183070-0x8018315C | db | |
| 0x8018315C-0x80187B3C | dvd | includes `DVDLow*` |
| 0x80187B3C-0x80189C10 | vi | |
| 0x80189C10-0x8018B624 | pad | **not registered yet**; starts at `UpdateOrigin` |
| 0x8018B624-0x8018BF08 | ai | |
| 0x8018BF08-0x80193E54 | gx | starts at the GX attribute code, before the first split (0x8018C820) |
| 0x80193E54-0x80195440 | MSL libc / math | strcmp, strcpy, wcstombs, vprintf, atan, cos, ldexp, modf |
| 0x80195440-0x80195E04 | exi | `EXIGetID`, `InitializeUART`, `WriteUARTN` |
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
