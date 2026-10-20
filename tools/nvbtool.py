#!/usr/bin/env python3
"""Print and rewrite the tuning files Misc/<CLASS>_<name>.nvb and their schema Misc/defaults.ndb
(docs/characters.md section 4).

Usage (from repo root):
  python3 tools/nvbtool.py schema [CLASS]                 Every field of a class: id, type, default
  python3 tools/nvbtool.py dump NAME [ID ...]             One tuning file (NAME: Wolverine, or PLAYER_WOLVERINE)
  python3 tools/nvbtool.py dump -f FILE [ID ...]          The same from an extracted or edited file
  python3 tools/nvbtool.py field ID [CLASS]               One field across every tuning file of a class
  python3 tools/nvbtool.py set IN OUT ID[.SLOT]=VALUE ... Write an edited copy of the file IN
  python3 tools/nvbtool.py check                          Parse, rebuild and compare every file byte for byte

IDs are decimal or 0x hex. `set` without a slot replaces the field with the one value (slot 0, which
the loader copies to every slot); with a slot it sets that slot and leaves the others. It never
writes under orig/; put the result in the archive with tools/bigtool.py repack --set.

Both formats are little-endian on disc (the loaders fn_801B26DC and fn_801B3638 byte-swap).

defaults.ndb, the schema:
  +0x0  u32 0xD000D000
  +0x4  u32 0x10001                the loader rejects any other value
  +0x8  u32 file size
  +0xC  u32 class count            AI, GLOBALS, PLAYER
  then per class:
        char name[0x40]
        u32 field count
        u32 slot count             1, or 6 for PLAYER (guess: the six slots a tuning file fills)
        field count * {u32 type; value}   the field's default; a field id is its index here

<CLASS>_<name>.nvb, the values that differ from the defaults:
  +0x0  u32 0xBEEFAD00
  +0x4  u32 0x1000                 read and ignored
  +0x8  u32 file size              read and ignored
  +0xC  char class[0x40]           "PLAYER"; what follows the NUL is leftover text of the exporter
  +0x4C char name[0x40]            "Wolverine"
  +0x8C u32 group count
  then per group:
        u32 field id
        u32 record count
        record count * {u32 slot; u32 type; value}

A value is 0x10 bytes for type VECTOR and 4 for type D888; any other type has a u32 size before
its bytes. After a group's first record the loader copies slot 0 to slots 1-5, so a file lists
slot 0 first and then only the slots that differ from it.
"""
import struct
import sys

BIG = "orig/GVLE69/files/CLASH.BIG"
NDB = "Misc/defaults.ndb"
NVB_MAGIC = 0xBEEFAD00
NDB_MAGIC = 0xD000D000
SLOTS = 6

T_TEMPLATE, T_EFFECT, T_D886, T_VECTOR, T_D888, T_STRING, T_FLOAT, T_INT = range(0xFFFFD884, 0xFFFFD88C)
# float, int, string and effect are the exporter's FLOAT, INTEGER, STRING and EFFECTNAME; template
# is named for its values (proj_bioHazBlob); d888 and d886 only occur in the AI class, which no
# tuning file uses
TYPE_NAMES = {
    T_FLOAT: "float",
    T_INT: "int",
    T_STRING: "string",
    T_EFFECT: "effect",
    T_TEMPLATE: "template",
    T_VECTOR: "vector",
    T_D888: "d888",
    T_D886: "d886",
}
TEXT_TYPES = (T_STRING, T_EFFECT, T_TEMPLATE)

# What each field is, by class and id; `schema`, `dump` and `field` print it. Add a line when a
# reader is decompiled (tools/nvbreaders.py lists them). FID_* names are the exporter's own, from
# the text left in the .nvb name buffers; anything else is what a matched reader does with the value.
# A guess goes in only with its basis stated ("inferred from 47 and 48"); otherwise name the reader.
FIELD_NAMES = {
    "PLAYER": {
        1: "near/far split of the super attack: a target farther than this gets motion 0x33 SuperAttackFar, a nearer one 0x2F SuperAttack1 (fn_800DDCB4); in fn_800E906C read into a local and not used again, or 20.0 in its place when the second argument is non-zero (fn_800E906C)",
        2: "target range of the super attack: the range argument of the target search fn_800E89B0 in fn_800DDCB4 (field 223 is its minimum facing); also the second float argument of fn_800E89B0 for an entity fn_80148178 found near the owner; callers of that not yet decompiled; also the search radius of fn_8004E4B4 in fn_800E906C",
        3: "near/far split of the air attack, as 1: farther gets motion 0x3F AirAttackFar, nearer 0x3E AirAttack (fn_800D3DC0)",
        4: "target range of the air attack, as 2 (fn_800E89B0 in fn_800D3DC0)",
        5: "low end of the distance band in which a grab becomes the target's super throw instead (fn_800DEDB4), with 6 the high end (fn_800DF03C, the grab)",
        6: "high end of that band, as 5 (fn_800DF03C, the grab)",
        7: "distance below which fn_800F0AA0 adds no scatter to the direction; the scatter then grows with the excess over it",
        8: "distance cap and divisor in the scatter of fn_800F0AA0 (the excess over field 7 is divided by it)",
        9: "ranged target search: second float argument of fn_800E9AF8 (fn_800F0328, the ranged action; also fn_800DDCB4, fn_800F0C70)",
        10: "ranged target search: first float argument of fn_800E9AF8 (fn_800F0328, fn_800DDCB4, fn_800F0C70); 50 for the characters with a ranged attack, Storm 35, default 20 (guess: the range)",
        13: "second float argument of fn_800E9AF8 when fn_800CC0BC(1) holds (fn_800D875C)",
        14: "first float argument of fn_800E9AF8 (fn_800D875C)",
        16: "converted to unsigned and not used again (fn_800F0328)",
        19: "fn_800DDCB4 drops a target farther than field 1 when fn_8042EBF4(attack direction, flat offset to it) is below this: it calls fn_800C98BC(self, 0, 1) and takes the no-target motion",
        20: "ranged target search: third float argument of fn_800E9AF8 (fn_800F0328, fn_800D875C, fn_800DDCB4, fn_800F0C70)",
        21: "third float argument of fn_800E9AF8 (fn_800F1644)",
        22: "attack strength: cached at +0x3F8, which fn_800E6D54 hands to fn_800D98B0 with the hit (guess: damage); set by fn_800DA884 and fn_800E1788 (the animation event handler); animation event 0x1B with value 0 sets +0x3F8 to it (fn_800E1788); in fn_800DA884, the motion's hit setup: the strength of motion 0x2D",
        23: "attack strength; cached in the entity float at +0x3F8 (with +0x3FC = 0x6C) when fn_800CCA88 is 0 (fn_800E3720); animation event 0x1B with value 1 and any value above 4 sets +0x3F8 to it (fn_800E1788); in fn_800DA884, the motion's hit setup: the default strength, kept by motions 0x27-0x2B, 0x39, 0x3E and 0xAC-0xAE",
        24: "attack strength, as 23, when fn_800CCA88 is non-zero (+0x3FC = 0x6F, and flag 0x80 set in +0x10) (fn_800E3720); animation event 0x1B with value 2 sets +0x3F8 to it (fn_800E1788); in fn_800DA884, the motion's hit setup: the strength of motions 0x2E-0x30, 0x35, 0x37, 0x38, 0x3C, 0x3F, 0x40, 0x48, 0x4A, 0x5C, 0x9F-0xA1, 0xF0 and 0xF1",
        25: "attack strength, cached in the entity float at +0x3F8 when the state is entered (fn_800ED448); animation event 0x1B with value 3 sets +0x3F8 to it (fn_800E1788); in fn_800DA884, the motion's hit setup: the strength of motions 0x2C, 0x31-0x33, 0x3B, 0x42, 0x49, 0x4B, 0x5D, 0xA2-0xA4, 0xB3-0xB5, 0xEC, 0xED and 0xF7",
        26: "attack strength, as 22 (fn_800DA884, fn_800E1788); animation event 0x1B with value 4 sets +0x3F8 to it (fn_800E1788); in fn_800DA884, the motion's hit setup: the strength of motions 0x34, 0x36 and 0x45",
        27: "grab range: the target search radius and the farthest distance a grab reaches (fn_800DF03C, the grab, fn_800E89B0's second argument)",
        28: "grab range when fn_800CCA88 holds and the energy of field 37 is there; above 5.0 a target nearer than 0 falls back to 27 (fn_800DF03C, the grab)",
        30: "energy cost: fn_80084B68 passes only when the actor's energy (+0x324) covers it; the air states fn_800C509C and fn_800C5A84 check it for the wire swing (ACTOR_ABILITIES 0x80), and fn_80084A60 takes it; in fn_800CFD2C the second argument of fn_80084B68 in the flag-9 branch; a hit enters state 0x1E (fn_800CFD2C); in the ground state fn_800C0F48 the run (clip 3) needs fn_80084B68 to pass on it, then takes it times the frame step (fn_80426A84) each frame through fn_80084A60 and drops back to the walk when that fails",
        32: "cached in the entity at +0x414; also the argument of fn_80084B68 in the first check (fn_800F0328)",
        34: "second argument of fn_80084A60 when fn_800CCA88 is set and fn_800CD9B0 is null; a hit sets the walk flag that picks clip 9 or 8 over 7 or 6 (fn_800C45B0)",
        35: "energy cost: fn_80084B68 passes only when the actor's energy (+0x324) covers it (fn_800E2970, fn_800E339C; fn_800DA884 caches it at +0x414); in fn_800E339C the second argument of fn_80084B68 when fn_800CCA88 is non-zero; picks clip 0x45 over 0x42 (fn_800E339C); in fn_800DA884, the motion's hit setup the cost of motion 0x3B",
        36: "energy cost (+0x414) of motion 0x35 (fn_800DA884, the motion's hit setup)",
        37: "energy cost of the powered grab: fn_80084B68 picks fields 241 and 28 for the search, fn_80084A60 takes it for motions +0xA2/+0xA9 (fn_800DF03C, the grab)",
        38: "per-second rate: times the frame time, the amount fn_80084A60 takes from the actor's float at +0x324 each update; 0 when fn_800861BC holds; a failed take ends the state (fn_800E5308)",
        39: "target of the entity float at +0xDC when fn_800CC148 flag 0x10 is set inside the flag-9 branch (fn_800D80B4); in fn_800D3398 the same target when fn_800CC148 flag 0x10 is set or fn_80085300's result is below field 42 (x0.25 if fn_800A4438, x0.5 if fn_800A4408 on fn_800CD9B0's entity)",
        40: "negated: target of the float at +0xDC when the flag-9 branch is not taken (fn_800D80B4); in fn_800D3398 the same target when flag 0x10 is clear and fn_800861EC holds, fn_80085300 fails or +0xDC is at least 1 (x2 if fn_800A4438, x1.5 if fn_800A4408)",
        42: "read into a local and not used again (fn_800D80B4); in fn_800D3398, plus 1.0 is the second float argument of fn_80085300, and a result below it picks clip 0x1F and sets the effect-handle value to 1.0",
        41: "second argument of fn_80084B68 in fn_800D2CF8 (reached when fn_800861EC is false); callers not yet decompiled",
        43: "cached in the entity at +0x3C4 (fn_8009D71C)",
        44: "cached in the entity at +0x3C8 (fn_8009D71C)",
        45: "cached in the entity at +0x3CC; times GLOBALS 57 gives +0x3D0 (fn_8009D71C)",
        46: "throw distance, class 1 (inferred from 47 and 48); 46 + i, i = fn_800A4468 of fn_800B1478 of the object fn_800CD9B0 returns (0 to 2), is the float argument of fn_800E9630 (the target finder) when fn_800CCA88 is 0 (fn_800F97F4)",
        31: "energy cost: fn_80084B68 passes only when the actor's energy (+0x324) covers it, for the super attack (fn_800DDCB4, fn_800DD3F8, fn_800F3384); fn_800DA884 caches it at +0x414; also the threshold the level of fn_80086730 must reach before fn_80084958 gets its step in fn_8009D818; the default an attack motion's cost +0x414 falls back to when its case set none (fn_800DA884, the motion's hit setup)",
        47: "FID_PLAYER_THROWDIST2",
        48: "throw distance, class 3",
        49: "base of 49 + i as 46, when fn_800CCA88 is non-zero (fn_800F97F4)",
        60: "added to the match clock fn_8042EFF8 and stored in the entity at +0xD4 (fn_800F3AE0)",
        61: "acceleration: the ground state caps its target speed at the current speed plus 0.2 times it times the frame step (fn_800C0F48)",
        63: "float argument of fn_800B9D64 with the stick direction at +0x440 in the ground state; a non-zero result there picks state 3 over 2 when stopping and plays the turn clip (fn_800C0F48)",
        64: "rate multiplier (times the frame step fn_80426A84) of the approach of the float at +0xDC to its target (fn_800D80B4)",
        66: "float argument of fn_800B9D64 (the stick-vector mover) when fn_8042EBF4 of the vector and fn_800B1750 is below 1.0 (fn_800D84BC)",
        67: "effect name of the left trail, made with fn_80393D0C when fn_800DA254's flag is 0",
        68: "effect name of the right trail, as 67",
        74: "effect name of the left trail, made with fn_80393D0C when fn_800DA254's flag is non-zero (the blade/claw trail)",
        75: "effect name of the right trail, as 74",
        76: "second float argument of fn_800E89B0 (fn_800E339C)",
        79: "base of 79 + n, n = the byte at entity +0x408 (0 to skip); second argument of fn_8039F4D8 on the table lbl_8064AA80 when flag 8 of fn_800E673C's byte argument is clear (fn_800E673C)",
        81: "effect name made with fn_80393A60 (flag 0) when fn_800861BC is true (fn_800E592C)",
        90: "base of 90 + i, i the byte at +0x409 of the owner object when it is not 4 or 5; projectile template name for fn_800FD5FC (fn_800F1644); the same in the ranged action fn_800F0C70 (animation event 4); animation event 0x4E sets the byte to the event value minus 1, clamped to 0-3 (fn_800E1788)",
        94: "base of 94 + i, i the byte at +0x40A of the owner object; muzzle effect name made with fn_80393D0C, with colour bytes +0x40C and +0x40B (fn_800F1644); the same in fn_800F0C70; animation event 0x50 sets the byte to min(value - 1, 3), and 0x4F sets +0x40B and +0x40C (fn_800E1788)",
        98: "effect name made with fn_80393D0C (colour 0xFF, 0xFF) as the entity's handle at +0x390, started with virtual slot 56 (fn_800BED04); fn_800BED04 replaces it through fn_80393B28 and stops it with slot 54 on the way out",
        99: "effect name made with fn_80393D0C (colour 0xFF, 0xFF), second handle (fn_800BED04; the handle is not stored); stopped with fn_80393798 on the way out",
        101: "effect name made with fn_80393D0C (colour 0xFF, 0xFF) as the entity's handle at +0x3A0, started with virtual slot 56 (fn_800D7CDC)",
        102: "effect name made with fn_80393D0C (colour 0xFF, 0xFF), second handle (fn_800D7CDC; the handle is not stored)",
        103: "returned by the getter fn_80086D9C; callers not yet decompiled; the ground state's walk speed: below stick 0.7 it drives at 103 * (0.5 + 0.5 * stick) (fn_800C0F48)",
        104: "jump speed (guess: fn_800C45B0 is the jump state, action 5 of fn_800C0F48, and the ground state fn_800C0F48 drives at the same values); returned by the getter fn_80086D54; stored to the entity float at +0x514 on each call and, while the steering vector is shorter, its minimum length (fn_800C45B0); the run speed the ground state drives at from stick 0.7 up when not sprinting (fn_800C0F48)",
        105: "jump speed (guess: fn_800C45B0 is the jump state, action 5 of fn_800C0F48, and the ground state fn_800C0F48 drives at the same values); stored to the entity float at +0x514 with clip 0xCC or 0xCB, when fn_800A4130 is clear and fn_800A4468 is 0 (fn_800C45B0); also the cap on the ground speed while carrying (fn_800CDA20) an object for which fn_800A43A0 holds (fn_800C0F48)",
        106: "cap on the ground speed while carrying (fn_800CDA20) an object for which fn_800A4408 holds and fn_800A4130 and fn_800A43A0 do not (fn_800C0F48)",
        107: "jump speed (guess: fn_800C45B0 is the jump state, action 5 of fn_800C0F48, and the ground state fn_800C0F48 drives at the same values); stored to the entity float at +0x514 with clip 0xD7 or 0xD6, when fn_800A4130 is clear and fn_800A4468 is non-zero (fn_800C45B0); also the cap on the ground speed while carrying (fn_800CDA20) an object for which none of fn_800A4130, fn_800A43A0 and fn_800A4408 holds (fn_800C0F48)",
        109: "jump speed (guess: fn_800C45B0 is the jump state, action 5 of fn_800C0F48, and the ground state fn_800C0F48 drives at the same values); stored to the entity float at +0x514 with clip 0xEF, when fn_800A4130 is set (fn_800C45B0); also the cap on the ground speed while carrying (fn_800CDA20) an object for which fn_800A4130 holds (fn_800C0F48)",
        110: "base of 110 + i as 46; length the steering vector is scaled to with fn_80435530 and a float argument of fn_801BCB08, when fn_800CCA88 is 0 (fn_800F97F4)",
        113: "base of 113 + i as 46, as 110 when fn_800CCA88 is non-zero (fn_800F97F4)",
        116: "base of 116 + i, i = fn_800A4468 of the other object (0 to 2); float argument of fn_800E9630 (the target finder; skipped when 0) when fn_800CCA88 is 0 (fn_800E6094)",
        119: "base of 119 + i as 116; length the steering vector is scaled to with fn_80435530 before fn_80065CB0 moves the entity, and a float argument of fn_801BCB08, when fn_800CCA88 is 0 (fn_800E6094)",
        122: "as 116, when fn_800CCA88 is non-zero (fn_800E6094)",
        125: "as 119, when fn_800CCA88 is non-zero (fn_800E6094)",
        129: "base of 129 + i, int: a hit whose strength is above it breaks through (fn_800E673C effect 2, fn_800E8628 0x6F), and it goes to fn_800D98B0 beside the strength (fn_800A0488; fn_80099228 reads i = 0)",
        134: "base of 134 + type, five fields (134-138): damage resistance. fn_80086C80(actor, type) returns 1.0 minus the value, and fn_8002FD50 scales a hit by it",
        157: "jump speed (guess: fn_800C45B0 is the jump state, action 5 of fn_800C0F48, and the ground state fn_800C0F48 drives at the same values); stored to the entity float at +0x514 when fn_800CC6AC is 4 and fn_8009AFC8 is 3 (fn_800C45B0); the ground state's speed while sprinting (clip 3, field 30), in place of 104 (fn_800C0F48)",
        158: "per-second rate: times the frame time (fn_80426A84), the amount fn_80084A60 takes from the actor when fn_800CC148 flag 0x10 is set (fn_800D3398)",
        160: "length the unit direction is scaled to by fn_80435530 before fn_80065CB0 moves the actor toward the target, when the clip type is not 0x45 (fn_800E3934)",
        161: "as 160, when the clip type is 0x45; also the float argument of fn_80040CE0 in the 0x45 case (fn_800E3934)",
        162: "distance below which fn_800DDCB4 picks motion 0x34 (0x2C without the energy of field 31) for a target with fn_800B0C1C and fn_800CCC28 set and under 0.5 apart in height",
        167: "returned by the getter fn_80086DE4; callers not yet decompiled; the ground state's move threshold: at or above this speed states 2 and 3 go to state 4, and state 4 drops to 3 below it while the stick is under 0.7 (fn_800C0F48)",
        168: "effect name, also made by fn_800E1788 (the animation event handler), fn_800D532C, fn_800D5DC8 and fn_800D73F0 (Daredevil: his wire, from the mod tests); in fn_800D5514 made with fn_80393A60 (flag 0); fn_8039D3C0 true attaches it to the actor, then vtable slots 20 and 44 run, and slot 22 when fn_80067050 gives a position (fn_800D5514)",
        169: "byte at +0x3EF for every motion (fn_800DA884, the motion's hit setup); animation event 0x58 overrides it with min(value, 4) (fn_800E1788)",
        170: "FID_PLAYER_VICTORY1 (versus victory cutscene 1); base of 170 + G[+0x79C + 4*side], the cutscene name fn_80093C14 hands to fn_800578E4",
        173: "base of 173 + v, v = random 0..2, the cutscene name fn_8009701C hands to fn_80057894 with 0x42022000 (guess: the mp_*_ext_* strings are an exit/extra cutscene)",
        176: "effect name (176 + n is idx + 175, idx 1 to 7) made with fn_80393D0C and started by vtable slot 58 on the handle at entity +0x394; idx comes from the first 0xC-byte entry of the table behind the actor's animation (fn_8009AF80 + 0x2C, fn_804355C0) whose u16 at +4 maps to one; idx 1 is 5 or 0x18 (fn_800DBC90)",
        177: "as 176, idx 2: u16 0x1F or 0x39",
        178: "as 176, idx 3: u16 0x20 or 0x3C",
        179: "as 176, idx 4: u16 0x21 or 0x3E",
        180: "as 176, idx 5: u16 0x22",
        182: "as 176, idx 7: u16 0x56",
        183: "read from the target's entity; half of it is added to the clock as the time stamp stored in the AI object's target list (fn_80148178)",
        187: "energy cost (+0x414) of motion 0x34 (fn_800DA884, the motion's hit setup)",
        188: "rage points (+0x418) of a motion that is not an attack, when its case set none (fn_800DA884, the motion's hit setup)",
        189: "rage points for superattack; read from a projectile's owner and added to the owner's meter (fn_80086A2C) when the projectile hits (fn_800A0488); also the default +0x418 of an attack motion (fn_800DA884, the motion's hit setup)",
        184: "length of the timer fn_80161BDC starts (deadline = now + value, stored at +0x18/+0x14); the owner and the caller of fn_80161BDC (vtable slot) not yet decompiled",
        185: "length of the timer fn_8016216C starts (same shape as 184; deadline stored at +0x18/+0x14), then it calls fn_800E9AF8 with 15, 4, 0.5; the owner and caller (vtable slot) not yet decompiled",
        190: "rage points (+0x418) of motions 0xEC, 0xED, 0xF0, 0xF1 and 0xF7, whose strength comes from the held object's fn_800A4620 when one is held (fn_800DA884, the motion's hit setup)",
        191: "rage points (+0x418) of motions 0x2D, 0x35 and 0x45 (fn_800DA884, the motion's hit setup)",
        192: "duration (ms is a guess) added to the game clock (fn_8042EFF8) to give the end time stored as a float at entity +0x334, as 195 (fn_8009DF60); named FID_PLAYER_RAGE_DURATION in the DOL",
        193: "rage penalty, % of base points; also the per-second rate the meter at fn_80086A00 drains at (times the frame time, negated) in fn_8009D818",
        195: "duration (ms is a guess) added to the game clock (fn_8042EFF8) to give the end time stored as a float at entity +0x334 (fn_8009E144)",
        196: "amount fn_80084A60 takes from the actor's float at +0x324 (it subtracts it if that float is not below it) when the move at clip 0x112 starts (fn_800D579C); in the ground state, with action 9 and fn_800860CC, fn_80084B68 passing on it lets fn_800D01A4 enter state 8 or fn_800D572C take over (fn_800C0F48)",
        200: "third argument of fn_80138738(9, 200, value), the pooled request it fills (fn_80462CA8 stores it), for the effect fn_8013E99C sends toward a target with a clear path; the second argument is the literal 200",
        201: "scale of the stick vector fn_800CC1D4 returns, times its length, in the velocity handed to fn_80065CB0 (fn_800D84BC)",
        202: "effect name made with fn_80393D0C (colour 0xFF, 0xFF) on every slot's actor in the round reset, handle not stored (fn_80092550); mpTeleport for all 18",
        203: "effect name made with fn_80393D0C (colour 0xFF, 0xFF) as the entity's first handle at +0x3A4 (fn_800E50AC); the values read as super-block effects",
        204: "effect name made with fn_80393D0C (colour 0xFF, 0xFF), second handle (fn_800E50AC; the handle is not stored)",
        205: "effect name made with fn_80393D0C (colour 0xFF, 0xFF) after fn_80114D70 (fn_800E592C)",
        206: "fm_* cutscene against a male opponent (206 + the opponent's SKELETONID, fn_80096460)",
        207: "fm_* cutscene against a female opponent",
        208: "fm_* cutscene against a brute opponent",
        209: "fn_8014A574: scale on the direction from actor to target, when field 211 does not apply",
        210: "fn_80142558 gives up when the distance to fn_80134870's entity is at most this; in fn_80158038, the reach within which the chosen target sets state bit 0x13 (else 0x12); callers not yet decompiled",
        211: "fn_8015F008 is true when the Vector-derived float fn_8015E64C is above it; also fn_8014A574's scale on that direction when fn_800B0C1C and fn_80095608 hold for the target and fn_80085D3C does not for the actor; other callers not yet decompiled",
        212: "fn_8015F07C is true when that float is below it; callers not yet decompiled",
        213: "first float argument of fn_8015F7A4 (the other actor chosen by fn_80134870) when fn_800CD9B0 gives no entity (fn_80158844, which also reads field 210 and discards it for 5.0)",
        214: "base of 214 + i, i the byte at +0x409 of the owner object when it is 4 or 5 (fields 218 and 219: template name for fn_800FD5FC,) (fn_800F1644); the same in fn_800F0C70",
        216: "when the distance fn_8015E8A8 gives to fn_80134870's entity exceeds it, the first float argument of fn_8015F7A4 is 20 instead of 4 (fn_8014E288); in fn_80158038 its last float argument is 0 instead of 0.5",
        220: "name passed to fn_80057894 with the flags word after a 0.33/0.66 random roll (fn_800965A4); caller fn_80092A84",
        221: "effect handle name started (fn_80393D0C) and stopped (fn_80393A60) around the level of 222 in fn_8009D818",
        222: "window below the time gate (+0x324 minus the argument) inside which fn_80084B68 passes only on a 1-in-100 roll (fn_80084B68); also the level of fn_80086730 below which fn_8009D818 starts the effect of 221 and above which it stops it; in the ground state, when fn_8008618C holds and fn_80086730 is below it, fn_800BED04 runs and clip 0x26 plays if the actor's virtual at +0x1D0 (with 0.15) returns non-zero (fn_800C0F48)",
        224: "minimum facing (fn_800E89B0's first argument) of the grab's target search (fn_800DF03C, the grab)",
        227: "energy cost (+0x414) of motion 0x36 (fn_800DA884, the motion's hit setup)",
        228: "energy cost (+0x414) of motion 0x5D (fn_800DA884, the motion's hit setup)",
        229: "energy cost (+0x414) of motions 0xB3-0xB5 (fn_800DA884, the motion's hit setup)",
        236: "first float argument of fn_800E89B0 (fn_800E339C)",
        223: "first float argument of fn_800E89B0 for an entity fn_80148178 found near the owner; callers of that not yet decompiled; also the least value fn_8042EBF4(entity fn_800B1750, offset to the candidate) a target needs when fn_800E906C's second argument is 0; in fn_800DDCB4 the first float argument of fn_800E89B0, field 2 the second",
        240: "replaces field 210 as fn_80158038's reach when fn_800860FC is set on the owner's actor",
        225: "energy cost: fn_80084B68 passes only when the actor's energy (+0x324) covers it (fn_800E2970); fn_800DA884 caches it at +0x414; in fn_800DA884 the cost of motion 0x3C",
        226: "energy cost (guess): fn_800DA884 caches it at +0x414, like 31, 35, 225 and 230; in fn_800DA884 the cost of motion 0x45",
        230: "energy cost: fn_80084B68 passes only when the actor's energy (+0x324) covers it (fn_800E2970); fn_800DA884 caches it at +0x414; in fn_800DA884 the cost of motions 0x49 and 0x4B",
        231: "as 223, when the second argument of fn_800E906C is non-zero",
        241: "minimum facing of the powered grab's target search, as 224 with field 28 (fn_800DF03C, the grab)",
    },
    "GLOBALS": {
        4: "added through fn_80086818 to the actor's float +0x324, clamped to 0..+0x328 (fn_800A0488)",
        6: "added the same way to the entity's actor in fn_800ECA34, after its calls on the actor behind +0xD0",
        7: "added the same way in fn_800E5B2C, when its argument's fn_8009AC94 differs from fn_800B13D8 of the actor; that path then plays clip 0xE0/0xE1/0xE2",
        15: "least value fn_8007C830 accepts for the float lbl_8066D5C0; also the floor of the window fn_800372A8 clamps [0] of fn_8042FB28(+0x180) into",
        16: "greatest value fn_8007C830 accepts for the float lbl_8066D5C0; also the top of fn_800370D0's ramp and of fn_800372A8's window",
        17: "bottom of fn_800370D0's ramp: t = ([0] of fn_8042FB28(+0x180) - 17) / (16 - 17), clamped to 0..1; +0x19C = t * its float argument",
        18: "+0x198 at the top of that ramp, lerped from 1.0 by t (fn_800370D0)",
        19: "target of fn_800393F4's float +0x144 (times +0x198, at least 0.001) unless a flag picks fn_804351DC or +0x170 (guess: speed); its initial value (fn_80033D2C)",
        20: "value fn_80033A6C stores in lbl_8066D5C0 (called from fn_8002F3A8)",
        21: "initial value of +0x90 and +0x94 when fn_80033D2C resets the object fn_80034DB0 updates",
        22: "times fn_800BB078(actor) and the frame delta, set through fn_80446D88 (float [2] of the body's +0x80 subobject; fn_800C7AD4)",
        23: "times fn_800BB158(actor) and the frame delta, set through fn_80446D28 (float [0] of the body's +0x80 subobject; fn_800C7AD4)",
        24: "scale fn_80038B70 applies to +0xC0 to get +0x120 before it probes the heading, then +90, -90 and +180, with fn_80038A2C",
        29: "rate per second at which fn_800393F4 moves +0x144 toward its target",
        30: "that rate when +0x198 < 1.0 (fn_800393F4)",
        31: "rate per second at which fn_800372A8 moves [0] of fn_8042FB28(+0x180) toward lbl_8066D5C0 + +0x194 + +0x214 (32 when its second flags argument has 0x8000)",
        32: "that rate when fn_800372A8's second flags argument has 0x8000",
        44: "time added to the fn_8042E96C clock for the type-3 entry fn_8003DBF0 queues, when fn_800C86B8's second argument is 0x6C-0x6E, 0x75 or 0x7D",
        45: "float of that fn_8003DBF0 entry, same arguments (fn_800C86B8)",
        46: "time of the fn_8003DBF0 entry for the other cases of fn_800C86B8's switch; its default uses 100",
        47: "float of that fn_8003DBF0 entry (fn_800C86B8); its default uses 0.2",
        48: "divisor of fn_80034DB0's ratio: +0x1C0's target is fn_8042EBF4(fn_80067050(+0x1F4), +0x370) / 48, clamped to 0..1",
        49: "times +0x1C0, the last argument of fn_80429090(+0xB0, ...) in fn_80034DB0",
        50: "rate per second at which fn_80034DB0 raises +0x1C0 toward its target",
        51: "rate per second at which fn_80034DB0 lowers +0x1C0 toward its target",
        52: "search radius of fn_8004E4B4 in fn_800ED448",
        54: "times 0.1 (1/30 * 3); fn_80038618 returns early when flags bit 0x800000 is set and fn_801BDE20([2] of fn_8042FB28(+0x180), +0x1C4) exceeds it",
        55: "step, signed by that angle difference, that fn_80038618 hands to fn_800383D8 (then negated); also the limit's first factor",
        56: "int, times field 55: when |difference to +0xC0's heading| is over it, fn_80038618 sets +0x1C4 to that heading, else fn_801BDA3C(heading + 160)",
        57: "multiplier on PLAYER 45, cached in the entity at +0x3D0 (fn_8009D71C)",
        58: "target fn_801A5F8C moves +0x58 toward, at 2.0 per second, on a frame whose +0x4 has 0x2000000 (else back toward 1.0)",
        59: "target fn_801A5F8C moves +0x54 toward, at 2.0 per second, on a frame whose +0x4 has 0x800000 (else back toward 1.0)",
        60: "least value fn_8042EBF4(direction to the candidate, entity fn_800B1750) a candidate needs in fn_800ED448",
        61: "percent, stored * 0.01 in lbl_8053F284[2][2] (a {int, float}[3][3] reset to 0.0; fn_80044E5C)",
        62: "percent, stored * 0.01 in lbl_8053F284[0][2] (fn_80044E5C); fn_800439B0 returns 0 when fn_804358A4() exceeds lbl_8066B7B8 times it, for kind 2",
        63: "percent, stored * 0.01 in lbl_8053F2CC[2][2] (a {int, float}[3][3] reset to 1.0; fn_80044E5C)",
        64: "percent, stored * 0.01 in lbl_8053F2CC[0][2] (fn_80044E5C)",
        65: "third argument of fn_80043000(2, 0, ...) in fn_80044E5C",
        66: "fourth argument of fn_80043000(2, 0, ...) in fn_80044E5C",
        67: "times field 19, stored in the body's +0x170 (fn_80446DE8) when fn_800CDA20(actor); fn_800C72B0 then also passes flags 0x2000200 to fn_800396A8",
        68: "18 instead when fn_800370D0's flags argument has 0x2000000",
        69: "that rate when +0x198 < 1.0 and the first flags argument has 0x2000000 (fn_800393F4)",
        70: "percent, stored * 0.01 in lbl_8053F284[2][1] (fn_80044E5C)",
        71: "percent, stored * 0.01 in lbl_8053F284[0][1] (fn_80044E5C); the same fn_800439B0 limit for kind 1",
        72: "percent, stored * 0.01 in lbl_8053F2CC[2][1] (fn_80044E5C)",
        73: "percent, stored * 0.01 in lbl_8053F2CC[0][1] (fn_80044E5C)",
        74: "third argument of fn_80043000(1, 0, ...) in fn_80044E5C",
        75: "fourth argument of fn_80043000(1, 0, ...) in fn_80044E5C",
        77: "mode for fn_80043190(lbl_8066B75C, mode) when fn_800439B0's fn_800466D8 kind is neither 0 nor 1; only modes 1 and 2 are passed on",
        79: "the same mode when that kind is 1 (fn_800439B0)",
        80: "time added to the fn_8042EFF8 clock for the deadline +0x1C8: until it passes, fn_80034894 keeps returning flag 0x1000000 (the one field 81 tests) while its third argument's word has it",
        81: "added to fn_800393F4's target unless the second flags argument has 0x1000000",
    },
}

# fn_801343B0 copies these 22 (ids in this order) to floats at +0x598 + 4*i of the object behind the
# entity accessor, converting the two ints; the files vary them per CPU difficulty (guess: AI weights).
for _i, _fid in enumerate((139, 140, 164, 141, 142, 143, 144, 145, 146, 159, 147, 148, 149, 150, 151,
                           152, 153, 154, 155, 156, 247, 246)):
    FIELD_NAMES["PLAYER"][_fid] = "copied to the object's float at +0x%X (guess: AI weight)" % (0x598 + 4 * _i)


def read_value(d, p, typ):
    """The bytes of one value at p, and the offset after it."""
    if typ == T_VECTOR:
        return d[p:p + 0x10], p + 0x10
    if typ == T_D888:
        return d[p:p + 4], p + 4
    n = struct.unpack_from("<I", d, p)[0]
    return d[p + 4:p + 4 + n], p + 4 + n


def write_value(typ, v):
    if typ in (T_VECTOR, T_D888):
        return v
    return struct.pack("<I", len(v)) + v


class Schema:
    def __init__(self, classes):
        self.classes = classes  # list of (raw name, slot count, [(type, default bytes)])

    def fields(self, cls):
        for raw, _, fields in self.classes:
            if raw.split(b"\0")[0].decode().upper() == cls.upper():
                return fields
        raise SystemExit("no class %s in %s" % (cls, NDB))


def parse_ndb(d):
    magic, version, size, count = struct.unpack_from("<4I", d, 0)
    if magic != NDB_MAGIC or version != 0x10001:
        raise ValueError("bad .ndb header %08X %X" % (magic, version))
    p = 16
    classes = []
    for _ in range(count):
        raw = d[p:p + 0x40]
        nfields, nslots = struct.unpack_from("<II", d, p + 0x40)
        p += 0x48
        fields = []
        for _ in range(nfields):
            typ = struct.unpack_from("<I", d, p)[0]
            v, p = read_value(d, p + 4, typ)
            fields.append((typ, v))
        classes.append((raw, nslots, fields))
    if p != len(d) or size != len(d):
        raise ValueError("trailing data: 0x%X of 0x%X (header says 0x%X)" % (p, len(d), size))
    return Schema(classes)


def build_ndb(schema):
    body = bytearray()
    for raw, nslots, fields in schema.classes:
        body += raw + struct.pack("<II", len(fields), nslots)
        for typ, v in fields:
            body += struct.pack("<I", typ) + write_value(typ, v)
    return struct.pack("<4I", NDB_MAGIC, 0x10001, 16 + len(body), len(schema.classes)) + bytes(body)


class Nvb:
    def __init__(self, word1, raw_class, raw_name, groups):
        self.word1 = word1
        self.raw_class = raw_class  # 0x40 bytes as stored, junk after the NUL included
        self.raw_name = raw_name
        self.groups = groups        # list of [field id, [(slot, type, value bytes)]], in file order

    @property
    def cls(self):
        return self.raw_class.split(b"\0")[0].decode("latin-1")

    @property
    def name(self):
        return self.raw_name.split(b"\0")[0].decode("latin-1")

    def group(self, fid):
        for g in self.groups:
            if g[0] == fid:
                return g
        return None

    def slots(self, fid, default):
        """What the loader leaves in the six slots of a field this file lists, or None."""
        g = self.group(fid)
        if g is None:
            return None
        out = [default] * SLOTS
        for j, (slot, _, v) in enumerate(g[1]):
            out[slot] = v
            if j == 0:
                # the loader copies slot 0 here, whichever slot the first record named
                out[1:] = [out[0]] * (SLOTS - 1)
        return out


def parse_nvb(d):
    magic, word1, size = struct.unpack_from("<3I", d, 0)
    if magic != NVB_MAGIC:
        raise ValueError("bad .nvb magic %08X" % magic)
    count = struct.unpack_from("<I", d, 0x8C)[0]
    p = 0x90
    groups = []
    for _ in range(count):
        fid, nrec = struct.unpack_from("<II", d, p)
        p += 8
        recs = []
        for _ in range(nrec):
            slot, typ = struct.unpack_from("<II", d, p)
            v, p = read_value(d, p + 8, typ)
            recs.append((slot, typ, v))
        groups.append([fid, recs])
    if p != len(d) or size != len(d):
        raise ValueError("trailing data: 0x%X of 0x%X (header says 0x%X)" % (p, len(d), size))
    return Nvb(word1, d[0xC:0x4C], d[0x4C:0x8C], groups)


def build_nvb(nvb):
    body = bytearray(nvb.raw_class + nvb.raw_name + struct.pack("<I", len(nvb.groups)))
    for fid, recs in nvb.groups:
        body += struct.pack("<II", fid, len(recs))
        for slot, typ, v in recs:
            body += struct.pack("<II", slot, typ) + write_value(typ, v)
    return struct.pack("<3I", NVB_MAGIC, nvb.word1, 12 + len(body)) + bytes(body)


def fmt(typ, v):
    if typ == T_FLOAT:
        return "%g" % struct.unpack("<f", v)[0]
    if typ in (T_INT, T_D888, T_D886):
        return "%d" % struct.unpack("<i", v)[0]
    if typ == T_VECTOR:
        return "(%g, %g, %g, %g)" % struct.unpack("<4f", v)
    return '"%s"' % v.split(b"\0")[0].decode("latin-1")


def encode(typ, text):
    if typ == T_FLOAT:
        return struct.pack("<f", float(text))
    if typ in (T_INT, T_D888, T_D886):
        return struct.pack("<i", int(text, 0))
    if typ in TEXT_TYPES:
        return text.encode("latin-1") + b"\0"
    raise SystemExit("cannot set a value of type %s" % TYPE_NAMES.get(typ, hex(typ)))


def read_big_index():
    """{lowercased name: (offset, size)} of CLASH.BIG (BIG4 index: tools/bigtool.py)."""
    out = {}
    with open(BIG, "rb") as f:
        count, index_size = struct.unpack(">II", f.read(16)[8:])
        index = f.read(index_size - 16)
    p = 0
    for _ in range(count):
        off, size = struct.unpack_from(">II", index, p)
        end = index.index(b"\0", p + 8)
        out[index[p + 8:end].decode("latin-1").lower()] = (off, size)
        p = end + 1
    return out


def read_entry(index, name):
    off, size = index[name.lower()]
    with open(BIG, "rb") as f:
        f.seek(off)
        return f.read(size)


def nvb_entries(index, cls=None):
    names = sorted(n for n in index if n.endswith(".nvb"))
    if cls:
        names = [n for n in names if n.startswith("misc/%s_" % cls.lower())]
    return names


def find_nvb(index, name):
    want = name.lower()
    if want.endswith(".nvb"):
        want = want[:-4]
    hits = [n for n in nvb_entries(index) if n[5:-4] == want or n[5:-4].split("_", 1)[1] == want]
    if len(hits) != 1:
        raise SystemExit("%s: %d tuning files match" % (name, len(hits)))
    return hits[0]


def ids(args):
    return [int(a, 0) for a in args]


def label(cls, fid):
    name = FIELD_NAMES.get(cls.upper(), {}).get(fid)
    return "  ; " + name if name else ""


def cmd_schema(schema, args):
    for raw, nslots, fields in schema.classes:
        cls = raw.split(b"\0")[0].decode()
        if args and cls.upper() != args[0].upper():
            continue
        print("%s  (%d fields, %d slots)" % (cls, len(fields), nslots))
        for i, (typ, v) in enumerate(fields):
            print("  %3d 0x%02X %-8s %s%s" % (i, i, TYPE_NAMES.get(typ, hex(typ)), fmt(typ, v), label(cls, i)))


def cmd_dump(schema, nvb, want):
    fields = schema.fields(nvb.cls)
    listed = sum(1 for fid, _ in nvb.groups if fid < len(fields))
    print("%s %s  (%d of %d fields set)" % (nvb.cls, nvb.name, listed, len(fields)))
    for i, (typ, default) in enumerate(fields):
        if want and i not in want:
            continue
        slots = nvb.slots(i, default)
        if slots is None:
            if want:
                print("  %3d %-8s default %s%s" % (i, TYPE_NAMES.get(typ, hex(typ)), fmt(typ, default), label(nvb.cls, i)))
            continue
        text = fmt(typ, slots[0])
        other = ["%d: %s" % (s, fmt(typ, v)) for s, v in enumerate(slots) if s and v != slots[0]]
        if other:
            text += "   [" + ", ".join(other) + "]"
        print("  %3d %-8s %s   (default %s)%s" % (i, TYPE_NAMES.get(typ, hex(typ)), text, fmt(typ, default), label(nvb.cls, i)))


def cmd_field(schema, index, fid, cls):
    typ, default = schema.fields(cls)[fid]
    print("%s field %d, %s, default %s%s" % (cls, fid, TYPE_NAMES.get(typ, hex(typ)), fmt(typ, default), label(cls, fid)))
    for entry in nvb_entries(index, cls):
        nvb = parse_nvb(read_entry(index, entry))
        slots = nvb.slots(fid, default)
        if slots is None:
            continue
        text = fmt(typ, slots[0])
        other = ["%d: %s" % (s, fmt(typ, v)) for s, v in enumerate(slots) if s and v != slots[0]]
        if other:
            text += "   [" + ", ".join(other) + "]"
        print("  %-12s %s" % (nvb.name, text))


def cmd_set(schema, src, dst, edits):
    if dst.replace("\\", "/").startswith("orig/"):
        raise SystemExit("refusing to write under orig/")
    nvb = parse_nvb(open(src, "rb").read())
    fields = schema.fields(nvb.cls)
    for edit in edits:
        key, _, text = edit.partition("=")
        fid_text, _, slot_text = key.partition(".")
        fid = int(fid_text, 0)
        if not 0 <= fid < len(fields):
            raise SystemExit("%s has no field %d" % (nvb.cls, fid))
        typ = fields[fid][0]
        value = encode(typ, text)
        g = nvb.group(fid)
        if not slot_text:
            recs = [(0, typ, value)]
        else:
            slot = int(slot_text, 0)
            if not 0 <= slot < SLOTS:
                raise SystemExit("slot %d: slots are 0-%d" % (slot, SLOTS - 1))
            # slot 0 has to come first: the loader copies the first record over slots 1-5
            recs = list(g[1]) if g else [(0, typ, fields[fid][1])]
            recs = [r for r in recs if r[0] != slot] + [(slot, typ, value)]
            recs.sort(key=lambda r: r[0])
            if recs[0][0] != 0:
                recs.insert(0, (0, typ, fields[fid][1]))
        if g:
            g[1] = recs
        else:
            nvb.groups.append([fid, recs])
    open(dst, "wb").write(build_nvb(nvb))
    print("wrote %s (%s %s)" % (dst, nvb.cls, nvb.name))


def cmd_check(index):
    data = read_entry(index, NDB)
    ok = build_ndb(parse_ndb(data)) == data
    print("%-28s %s" % (NDB, "identical" if ok else "DIFFERS"))
    entries = nvb_entries(index)
    for entry in entries:
        data = read_entry(index, entry)
        same = build_nvb(parse_nvb(data)) == data
        if not same:
            print("%-28s DIFFERS" % entry)
        ok = ok and same
    print("%d tuning files, round trip %s" % (len(entries), "identical" if ok else "DIFFERS"))
    sys.exit(0 if ok else 1)


def main(argv):
    if len(argv) < 2 or argv[1] not in ("schema", "dump", "field", "set", "check"):
        raise SystemExit(__doc__)
    cmd, args = argv[1], argv[2:]
    index = read_big_index()
    if cmd == "check":
        cmd_check(index)
    schema = parse_ndb(read_entry(index, NDB))
    if cmd == "schema":
        cmd_schema(schema, args)
    elif cmd == "dump":
        if not args or (args[0] == "-f" and len(args) < 2):
            raise SystemExit(__doc__)
        if args[0] == "-f":
            data, rest = open(args[1], "rb").read(), args[2:]
        else:
            data, rest = read_entry(index, find_nvb(index, args[0])), args[1:]
        cmd_dump(schema, parse_nvb(data), ids(rest))
    elif cmd == "field":
        if not args:
            raise SystemExit(__doc__)
        cmd_field(schema, index, int(args[0], 0), args[1] if len(args) > 1 else "PLAYER")
    elif cmd == "set":
        if len(args) < 3:
            raise SystemExit(__doc__)
        cmd_set(schema, args[0], args[1], args[2:])


if __name__ == "__main__":
    main(sys.argv)
