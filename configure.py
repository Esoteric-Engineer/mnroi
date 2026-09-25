#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "GVLE69",  # 0
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--ninja",
    metavar="BINARY",
    type=Path,
    help="path to ninja binary (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--warn",
    dest="warn",
    type=str,
    choices=["all", "off", "error"],
    help="how to handle warnings",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-2"
config.compilers_tag = "20251118"
config.dtk_tag = "v1.8.3"
config.objdiff_tag = "v3.6.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.3"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    "-multibyte",  # For Wii compilers, replace with `-enc SJIS`
    "-i include",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Warning flags
if args.warn == "all":
    cflags_base.append("-W all")
elif args.warn == "off":
    cflags_base.append("-W off")
elif args.warn == "error":
    cflags_base.append("-W error")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
]

# REL flags
cflags_rel = [
    *cflags_base,
    "-sdata 0",
    "-sdata2 0",
]

config.linker_version = "GC/1.3.2"


# Helper function for Dolphin libraries
def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": objects,
    }


# Helper function for REL script objects
def Rel(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3.2",
        "cflags": cflags_rel,
        "progress_category": "game",
        "objects": objects,
    }


Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "sdk",  # str | List[str]
        "objects": [
            Object(Matching, "Runtime.PPCEABI.H/__ieee754_acosf.c"),
            Object(Matching, "Runtime.PPCEABI.H/atan2f.c"),
            Object(Matching, "Runtime.PPCEABI.H/__ieee754_powf.c"),
            Object(Matching, "Runtime.PPCEABI.H/__ieee754_sqrtf.c"),
            Object(Matching, "Runtime.PPCEABI.H/atanf.c"),
            Object(Matching, "Runtime.PPCEABI.H/cosf.c"),
            Object(Matching, "Runtime.PPCEABI.H/fabsf.c"),
            Object(Matching, "Runtime.PPCEABI.H/sinf.c"),
            Object(Matching, "Runtime.PPCEABI.H/tanf.c"),
            Object(Matching, "Runtime.PPCEABI.H/scalbnf.c"),
            Object(Matching, "Runtime.PPCEABI.H/__kernel_cos.c"),
            Object(Matching, "Runtime.PPCEABI.H/__kernel_sin.c"),
            Object(Matching, "Runtime.PPCEABI.H/__ieee754_rem_pio2.c"),
            Object(Matching, "Runtime.PPCEABI.H/fabs.c"),
            Object(Matching, "Runtime.PPCEABI.H/__kernel_cosf.c"),
            Object(Matching, "Runtime.PPCEABI.H/__kernel_sinf.c"),
            Object(Matching, "Runtime.PPCEABI.H/__kernel_tanf.c"),
            Object(Matching, "Runtime.PPCEABI.H/__ieee754_rem_pio2f.c"),
            Object(Matching, "Runtime.PPCEABI.H/__kernel_rem_pio2.c"),
            Object(Matching, "Runtime.PPCEABI.H/__kernel_rem_pio2f.c"),
            Object(Matching, "Runtime.PPCEABI.H/floorf.c"),
            Object(Matching, "Runtime.PPCEABI.H/scalbn.c"),
            Object(Matching, "Runtime.PPCEABI.H/copysign.c"),
            Object(Matching, "Runtime.PPCEABI.H/copysignf.c"),
            Object(Matching, "Runtime.PPCEABI.H/sprintf.c"),
            Object(Matching, "Runtime.PPCEABI.H/eofread.c"),
            Object(Matching, "Runtime.PPCEABI.H/sscanf.c"),
            Object(Matching, "Runtime.PPCEABI.H/__svfscanf.c"),
            Object(Matching, "Runtime.PPCEABI.H/__sccl.c"),
            Object(Matching, "Runtime.PPCEABI.H/vsprintf.c"),
            Object(Matching, "Runtime.PPCEABI.H/__register_atexit.c"),
            Object(Matching, "Runtime.PPCEABI.H/atof.c"),
            Object(Matching, "Runtime.PPCEABI.H/atoi.c"),
            Object(Matching, "Runtime.PPCEABI.H/bsearch.c"),
            Object(Matching, "Runtime.PPCEABI.H/_mbtowc_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/qsort.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80171F8C.c"),
            Object(Matching, "Runtime.PPCEABI.H/free.c"),
            Object(Matching, "Runtime.PPCEABI.H/realloc.c"),
            Object(Matching, "Runtime.PPCEABI.H/_strtoul_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/strtoul.c"),
            Object(Matching, "Runtime.PPCEABI.H/memcmp.c"),
            Object(Matching, "Runtime.PPCEABI.H/memcpy.c"),
            Object(Matching, "Runtime.PPCEABI.H/memmove.c"),
            Object(Matching, "Runtime.PPCEABI.H/memset.c"),
            Object(Matching, "Runtime.PPCEABI.H/stricmp.c"),
            Object(Matching, "Runtime.PPCEABI.H/strcat.c"),
            Object(Matching, "Runtime.PPCEABI.H/strchr.c"),
            Object(Matching, "Runtime.PPCEABI.H/strcmp.c"),
            Object(Matching, "Runtime.PPCEABI.H/strcpy.c"),
            Object(Matching, "Runtime.PPCEABI.H/strlen.c"),
            Object(Matching, "Runtime.PPCEABI.H/strlwr.c"),
            Object(Matching, "Runtime.PPCEABI.H/strnicmp.c"),
            Object(Matching, "Runtime.PPCEABI.H/strncmp.c"),
            Object(Matching, "Runtime.PPCEABI.H/strncpy.c"),
            Object(Matching, "Runtime.PPCEABI.H/strrchr.c"),
            Object(Matching, "Runtime.PPCEABI.H/strspn.c"),
            Object(Matching, "Runtime.PPCEABI.H/strstr.c"),
            Object(Matching, "Runtime.PPCEABI.H/strtok.c"),
            Object(Matching, "Runtime.PPCEABI.H/strtok_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80172CC4.c"),
            Object(Matching, "Runtime.PPCEABI.H/asctime_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80172D78.c"),
            Object(Matching, "Runtime.PPCEABI.H/gmtime_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/mktime.c"),
            Object(Matching, "Runtime.PPCEABI.H/strround.c"),
            Object(Matching, "Runtime.PPCEABI.H/strrev.c"),
            Object(Matching, "Runtime.PPCEABI.H/itoa.c"),
            Object(Matching, "Runtime.PPCEABI.H/fftoa.c"),
            Object(Matching, "Runtime.PPCEABI.H/_vfwrite.c"),
            Object(Matching, "Runtime.PPCEABI.H/vfprintf.c"),
            Object(Matching, "Runtime.PPCEABI.H/_vfprintf_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/__group_digits.c"),
            Object(Matching, "Runtime.PPCEABI.H/_vfiwrite.c"),
            Object(Matching, "Runtime.PPCEABI.H/_vfiprintf_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/_strtol_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/strtol.c"),
            Object(Matching, "Runtime.PPCEABI.H/strtod.c"),
            Object(Matching, "Runtime.PPCEABI.H/tolower.c"),
            Object(Matching, "Runtime.PPCEABI.H/tolower2.c"),
            Object(Matching, "Runtime.PPCEABI.H/printf.c"),
            Object(Matching, "Runtime.PPCEABI.H/vprintf.c"),
            Object(Matching, "Runtime.PPCEABI.H/isdigit.c"),
            Object(Matching, "Runtime.PPCEABI.H/isspace.c"),
            Object(Matching, "Runtime.PPCEABI.H/runtime.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_801796B8.c"),
            Object(Matching, "Runtime.PPCEABI.H/lshrdi3.c"),
            Object(Matching, "Runtime.PPCEABI.H/__errno.c"),
            Object(Matching, "Runtime.PPCEABI.H/_localeconv_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/localeconv.c"),
            Object(Matching, "Runtime.PPCEABI.H/floor.c"),
            Object(Matching, "Runtime.PPCEABI.H/__ieee754_fmod.c"),
            Object(Matching, "Runtime.PPCEABI.H/__ieee754_log.c"),
            Object(Matching, "Runtime.PPCEABI.H/__ieee754_log10.c"),
            Object(Matching, "Runtime.PPCEABI.H/memcpyalpha.c"),
            Object(Matching, "Runtime.PPCEABI.H/fread.c"),
            Object(Matching, "Runtime.PPCEABI.H/lflush.c"),
            Object(Matching, "Runtime.PPCEABI.H/__srefill.c"),
            Object(Matching, "Runtime.PPCEABI.H/ungetc.c"),
            Object(Matching, "Runtime.PPCEABI.H/div.c"),
            Object(Matching, "Runtime.PPCEABI.H/memchr.c"),
            Object(Matching, "Runtime.PPCEABI.H/fflush.c"),
            Object(Matching, "Runtime.PPCEABI.H/snstd.c"),
            Object(Matching, "Runtime.PPCEABI.H/__sinit.c"),
            Object(Matching, "Runtime.PPCEABI.H/__sfp.c"),
            Object(Matching, "Runtime.PPCEABI.H/_fopen_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/fopen.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80178684.c"),
            Object(Matching, "Runtime.PPCEABI.H/_fseek_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/_fwalk.c"),
            Object(Matching, "Runtime.PPCEABI.H/__smakebuf.c"),
            Object(Matching, "Runtime.PPCEABI.H/__sread.c"),
            Object(Matching, "Runtime.PPCEABI.H/__swrite.c"),
            Object(Matching, "Runtime.PPCEABI.H/__sseek.c"),
            Object(Matching, "Runtime.PPCEABI.H/__sclose.c"),
            Object(Matching, "Runtime.PPCEABI.H/_close_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/_fstat_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/_lseek_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80178E48.c"),
            Object(Matching, "Runtime.PPCEABI.H/_read_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/_write_r.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80178F54.c"),
            Object(Matching, "Runtime.PPCEABI.H/__do_global_ctors.c"),
            Object(Matching, "Runtime.PPCEABI.H/__main.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80179138.c"),
            Object(Matching, "Runtime.PPCEABI.H/__moddi3.c"),
            Object(Matching, "Runtime.PPCEABI.H/__pure_virtual.c"),
            Object(Matching, "Runtime.PPCEABI.H/__udivdi3.c"),
            Object(Matching, "Runtime.PPCEABI.H/__umoddi3.c"),
            Object(Matching, "Runtime.PPCEABI.H/__save_gpr.c"),
            Object(Matching, "Runtime.PPCEABI.H/__restore_gpr.c"),
        ],
    },
    {
        # SN Systems ProDG debug stub (0x80168770-0x8016B554), see docs/sdk_libraries.md
        "lib": "SN",
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "SN/fn_801687E8.c"),
            Object(Matching, "SN/EnableMetroTRKInterrupts.c"),
            Object(Matching, "SN/fn_80168B9C.c"),
            Object(Matching, "SN/fn_80168C9C.c"),
            Object(Matching, "SN/fn_80168CC4.c"),
            Object(Matching, "SN/fn_80169134.c"),
            Object(Matching, "SN/fn_80169150.c"),
            Object(Matching, "SN/fn_80169164.c"),
            Object(Matching, "SN/fn_8016918C.c"),
            Object(Matching, "SN/fn_801691A4.c"),
            Object(Matching, "SN/fn_801694B8.c"),
            Object(Matching, "SN/fn_8016A060.c"),
            Object(Matching, "SN/fn_8016A078.c"),
            Object(Matching, "SN/fn_8016A1A4.c"),
            Object(Matching, "SN/fn_8016AAD0.c"),
            Object(Matching, "SN/fn_8016AAD8.c"),
            Object(Matching, "SN/fn_8016AAE0.c"),
            Object(Matching, "SN/fn_8016AAE8.c"),
            Object(Matching, "SN/fn_8016AAF0.c"),
            Object(Matching, "SN/fn_8016AAF8.c"),
            Object(Matching, "SN/fn_8016AB00.c"),
            Object(Matching, "SN/fn_8016AB08.c"),
            Object(Matching, "SN/fn_8016AB10.c"),
            Object(Matching, "SN/fn_8016AB18.c"),
            Object(Matching, "SN/fn_8016AB20.c"),
            Object(Matching, "SN/fn_8016AB28.c"),
            Object(Matching, "SN/fn_8016B6AC.c"),
            Object(Matching, "SN/fn_8016BEE4.c"),
            Object(Matching, "SN/fn_8016BF04.c"),
            Object(Matching, "SN/fn_8016C074.c"),
            Object(Matching, "SN/fn_8016C134.c"),
            Object(Matching, "SN/fn_8016C3BC.c"),
        ],
    },
    DolphinLib(
        "ai",
        [
            Object(Matching, "Dolphin/ai/AIRegisterDMACallback.c"),
            Object(Matching, "Dolphin/ai/AIInitDMA.c"),
            Object(Matching, "Dolphin/ai/AIStartDMA.c"),
            Object(Matching, "Dolphin/ai/AIStopDMA.c"),
            Object(Matching, "Dolphin/ai/AISetStreamPlayState.c"),
            Object(Matching, "Dolphin/ai/AIGetStreamPlayState.c"),
            Object(Matching, "Dolphin/ai/AISetDSPSampleRate.c"),
            Object(Matching, "Dolphin/ai/AIGetDSPSampleRate.c"),
            Object(Matching, "Dolphin/ai/__AI_set_stream_sample_rate.c"),
            Object(Matching, "Dolphin/ai/AIGetStreamSampleRate.c"),
            Object(Matching, "Dolphin/ai/AISetStreamVolLeft.c"),
            Object(Matching, "Dolphin/ai/AIGetStreamVolLeft.c"),
            Object(Matching, "Dolphin/ai/AISetStreamVolRight.c"),
            Object(Matching, "Dolphin/ai/AIGetStreamVolRight.c"),
            Object(Matching, "Dolphin/ai/AIInit.c"),
            Object(Matching, "Dolphin/ai/__AISHandler.c"),
            Object(Matching, "Dolphin/ai/__AIDHandler.c"),
            Object(Matching, "Dolphin/ai/__AICallbackStackSwitch.c"),
            Object(Matching, "Dolphin/ai/__AI_SRC_INIT.c"),
            Object(Matching, "Dolphin/gx/GXSetVtxDesc.c"),
            Object(Matching, "Dolphin/gx/GXSetVtxDescv.c"),
            Object(Matching, "Dolphin/gx/__GXSetVCD.c"),
            Object(Matching, "Dolphin/gx/__GXCalculateVLim.c"),
            Object(Matching, "Dolphin/gx/GXGetVtxDesc.c"),
            Object(Matching, "Dolphin/gx/GXGetVtxDescv.c"),
            Object(Matching, "Dolphin/gx/GXClearVtxDesc.c"),
            Object(Matching, "Dolphin/gx/GXGetVtxAttrFmt.c"),
            Object(Matching, "Dolphin/gx/GXSetVtxAttrFmt.c"),
            Object(Matching, "Dolphin/gx/__GXSetVAT.c"),
            Object(Matching, "Dolphin/gx/GXSetNumTexGens.c"),
            Object(Matching, "Dolphin/gx/__GXSetDirtyState.c"),
            Object(Matching, "Dolphin/gx/GXBegin.c"),
            Object(Matching, "Dolphin/gx/__GXSendFlushPrim.c"),
            Object(Matching, "Dolphin/gx/GXSetLineWidth.c"),
            Object(Matching, "Dolphin/gx/GXSetPointSize.c"),
            Object(Matching, "Dolphin/gx/GXEnableTexOffsets.c"),
            Object(Matching, "Dolphin/gx/GXSetCullMode.c"),
            Object(Matching, "Dolphin/gx/GXSetCoPlanar.c"),
            Object(Matching, "Dolphin/gx/__GXSetGenMode.c"),
            Object(Matching, "Dolphin/gx/GXInitLightAttn.c"),
            Object(Matching, "Dolphin/gx/GXInitLightAttnK.c"),
            Object(Matching, "Dolphin/gx/GXInitLightSpot.c"),
            Object(Matching, "Dolphin/gx/GXInitLightPos.c"),
            Object(Matching, "Dolphin/gx/GXInitLightDir.c"),
            Object(Matching, "Dolphin/gx/GXInitLightColor.c"),
            Object(NonMatching, "Dolphin/gx/GXLoadLightObjImm.c"),
            Object(Matching, "Dolphin/gx/GXSetChanAmbColor.c"),
            Object(Matching, "Dolphin/gx/GXSetChanMatColor.c"),
            Object(Matching, "Dolphin/gx/GXSetNumChans.c"),
            Object(Matching, "Dolphin/gx/GXSetChanCtrl.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(Matching, "Dolphin/gx/GXInitTlutRegion.c"),
            Object(Matching, "Dolphin/gx/GXInit.c"),
            Object(Matching, "Dolphin/gx/__GXGetTexTileShift.c"),
            Object(Matching, "Dolphin/gx/GXAttr.c"),
            Object(Matching, "Dolphin/gx/GXTexture.c"),
            Object(Matching, "Dolphin/gx/GXLoadTexObjPreLoaded.c"),
            Object(Matching, "Dolphin/gx/GXLoadTexObj.c"),
            Object(Matching, "Dolphin/gx/GXInitTlutObj.c"),
            Object(Matching, "Dolphin/gx/GXGetTlutObjAll.c"),
            Object(Matching, "Dolphin/gx/GXGetTlutObjData.c"),
            Object(Matching, "Dolphin/gx/GXLoadTlut.c"),
            Object(Matching, "Dolphin/gx/GXInitTexCacheRegion.c"),
            Object(Matching, "Dolphin/gx/GXSetTexRegionCallback.c"),
            Object(Matching, "Dolphin/gx/GXSetTlutRegionCallback.c"),
            Object(NonMatching, "Dolphin/gx/GXSetSUTexRegs.c"),
            Object(Matching, "Dolphin/gx/__GXSetTmemConfig.c"),
            Object(Matching, "Dolphin/gx/GXSetTevIndirect.c"),
            Object(Matching, "Dolphin/gx/GXSetIndTexMtx.c"),
            Object(Matching, "Dolphin/gx/GXSetIndTexCoordScale.c"),
            Object(Matching, "Dolphin/gx/GXSetIndTexOrder.c"),
            Object(Matching, "Dolphin/gx/GXSetNumIndStages.c"),
            Object(Matching, "Dolphin/gx/GXSetTevDirect.c"),
            Object(Matching, "Dolphin/gx/GXSetTevIndRepeat.c"),
            Object(Matching, "Dolphin/gx/GXUpdateBPMask.c"),
            Object(Matching, "Dolphin/gx/GXSetIndirectMask.c"),
            Object(Matching, "Dolphin/gx/GXFlushTextureState.c"),
            Object(Matching, "Dolphin/gx/GXSetTevOp.c"),
            Object(Matching, "Dolphin/gx/GXSetTevColorIn.c"),
            Object(Matching, "Dolphin/gx/GXSetTevAlphaIn.c"),
            Object(Matching, "Dolphin/gx/GXSetTevColorOp.c"),
            Object(Matching, "Dolphin/gx/GXSetTevAlphaOp.c"),
            Object(NonMatching, "Dolphin/gx/GXSetTevColor.c"),
            Object(Matching, "Dolphin/gx/GXSetTevKColor.c"),
            Object(Matching, "Dolphin/gx/GXSetTevKColorSel.c"),
            Object(Matching, "Dolphin/gx/GXSetTevKAlphaSel.c"),
            Object(Matching, "Dolphin/gx/GXSetTevSwapMode.c"),
            Object(Matching, "Dolphin/gx/GXSetTevSwapModeTable.c"),
            Object(Matching, "Dolphin/gx/GXSetAlphaCompare.c"),
            Object(Matching, "Dolphin/gx/GXSetZTexture.c"),
            Object(Matching, "Dolphin/gx/GXSetTevOrder.c"),
            Object(Matching, "Dolphin/gx/GXSetNumTevStages.c"),
            Object(Matching, "Dolphin/gx/GXSetFog.c"),
            Object(Matching, "Dolphin/gx/GXSetFogRangeAdj.c"),
            Object(Matching, "Dolphin/gx/GXSetBlendMode.c"),
            Object(Matching, "Dolphin/gx/GXSetColorUpdate.c"),
            Object(Matching, "Dolphin/gx/GXSetAlphaUpdate.c"),
            Object(Matching, "Dolphin/gx/GXSetZMode.c"),
            Object(Matching, "Dolphin/gx/GXSetZCompLoc.c"),
            Object(Matching, "Dolphin/gx/GXSetPixelFmt.c"),
            Object(Matching, "Dolphin/gx/GXSetDither.c"),
            Object(Matching, "Dolphin/gx/GXSetDstAlpha.c"),
            Object(Matching, "Dolphin/gx/GXSetFieldMask.c"),
            Object(Matching, "Dolphin/gx/GXSetFieldMode.c"),
            Object(NonMatching, "Dolphin/gx/GXTransform.c"),
            Object(Matching, "Dolphin/gx/GXLoadPosMtxImm.c"),
            Object(Matching, "Dolphin/gx/GXLoadNrmMtxImm.c"),
            Object(Matching, "Dolphin/gx/GXSetCurrentMtx.c"),
            Object(Matching, "Dolphin/gx/GXLoadTexMtxImm.c"),
            Object(NonMatching, "Dolphin/gx/GXSetViewport.c"),
            Object(Matching, "Dolphin/gx/GXSetScissor.c"),
            Object(NonMatching, "Dolphin/gx/GXSetScissorBoxOffset.c"),
            Object(Matching, "Dolphin/gx/GXSetClipMode.c"),
            Object(Matching, "Dolphin/gx/__GXSetMatrixIndex.c"),
            Object(Matching, "Dolphin/gx/__GXDefaultTexRegionCallback.c"),
            Object(Matching, "Dolphin/gx/__GXDefaultTlutRegionCallback.c"),
            Object(Matching, "Dolphin/gx/__GXShutdown.c"),
            Object(Matching, "Dolphin/gx/__GXInitRevisionBits.c"),
            Object(Matching, "Dolphin/gx/GXCPInterruptHandler.c"),
            Object(Matching, "Dolphin/gx/GXInitFifoBase.c"),
            Object(Matching, "Dolphin/gx/GXInitFifoPtrs.c"),
            Object(Matching, "Dolphin/gx/GXInitFifoLimits.c"),
            Object(Matching, "Dolphin/gx/GXSetCPUFifo.c"),
            Object(Matching, "Dolphin/gx/GXSetGPFifo.c"),
            Object(Matching, "Dolphin/gx/GXSaveCPUFifo.c"),
            Object(NonMatching, "Dolphin/gx/__GXSaveCPUFifoAux.c"),
            Object(Matching, "Dolphin/gx/GXSetBreakPtCallback.c"),
            Object(Matching, "Dolphin/gx/__GXFifoInit.c"),
            Object(Matching, "Dolphin/gx/__GXFifoReadEnable.c"),
            Object(Matching, "Dolphin/gx/__GXFifoReadDisable.c"),
            Object(Matching, "Dolphin/gx/__GXFifoLink.c"),
            Object(Matching, "Dolphin/gx/__GXWriteFifoIntEnable.c"),
            Object(Matching, "Dolphin/gx/__GXWriteFifoIntReset.c"),
            Object(Matching, "Dolphin/gx/__GXCleanGPFifo.c"),
            Object(Matching, "Dolphin/gx/GXGetCPUFifo.c"),
            Object(Matching, "Dolphin/gx/GXGetGPFifo.c"),
            Object(Matching, "Dolphin/gx/GXSetMisc.c"),
            Object(Matching, "Dolphin/gx/GXFlush.c"),
            Object(Matching, "Dolphin/gx/GXResetWriteGatherPipe.c"),
            Object(NonMatching, "Dolphin/gx/__GXAbort.c"),
            Object(NonMatching, "Dolphin/gx/GXAbortFrame.c"),
            Object(Matching, "Dolphin/gx/GXDrawDone.c"),
            Object(Matching, "Dolphin/gx/GXFlushTextureStateDup.c"),
            Object(Matching, "Dolphin/gx/GXPokeAlphaMode.c"),
            Object(Matching, "Dolphin/gx/GXPokeAlphaRead.c"),
            Object(Matching, "Dolphin/gx/GXPokeAlphaUpdate.c"),
            Object(Matching, "Dolphin/gx/GXPokeColorUpdate.c"),
            Object(Matching, "Dolphin/gx/GXPokeDstAlpha.c"),
            Object(Matching, "Dolphin/gx/GXPokeBlendMode.c"),
            Object(Matching, "Dolphin/gx/GXPokeDither.c"),
            Object(Matching, "Dolphin/gx/GXPokeZMode.c"),
            Object(Matching, "Dolphin/gx/GXSetDrawSyncCallback.c"),
            Object(Matching, "Dolphin/gx/GXTokenInterruptHandler.c"),
            Object(Matching, "Dolphin/gx/GXSetDrawDoneCallback.c"),
            Object(Matching, "Dolphin/gx/GXFinishInterruptHandler.c"),
            Object(Matching, "Dolphin/gx/GXPEInit.c"),
            Object(Matching, "Dolphin/gx/GXSetDispCopySrc.c"),
            Object(Matching, "Dolphin/gx/GXSetTexCopySrc.c"),
            Object(Matching, "Dolphin/gx/GXSetDispCopyDst.c"),
            Object(NonMatching, "Dolphin/gx/GXSetTexCopyDst.c"),
            Object(Matching, "Dolphin/gx/GXSetDispCopyFrame2Field.c"),
            Object(Matching, "Dolphin/gx/GXSetCopyClamp.c"),
            Object(Matching, "Dolphin/gx/GXSetDispCopyYScale.c"),
            Object(Matching, "Dolphin/gx/GXSetCopyClear.c"),
            Object(Matching, "Dolphin/gx/GXSetCopyFilter.c"),
            Object(Matching, "Dolphin/gx/GXSetDispCopyGamma.c"),
            Object(Matching, "Dolphin/gx/GXCopyDisp.c"),
            Object(Matching, "Dolphin/gx/GXCopyTex.c"),
            Object(Matching, "Dolphin/gx/GXClearBoundingBox.c"),
            Object(Matching, "Dolphin/gx/GXSetGPMetric.c"),
            Object(Matching, "Dolphin/gx/GXClearGPMetric.c"),
            Object(Matching, "Dolphin/gx/GXPerfStubs.c"),
        ],
    ),
    DolphinLib(
        "si",
        [
            Object(Matching, "Dolphin/si/SIBusy.c"),
            Object(Matching, "Dolphin/si/SIIsChanBusy.c"),
            Object(Matching, "Dolphin/si/CompleteTransfer.c"),
            Object(Matching, "Dolphin/si/SIInterruptHandler.c"),
            Object(Matching, "Dolphin/si/SIEnablePollingInterrupt.c"),
            Object(Matching, "Dolphin/si/SIRegisterPollingHandler.c"),
            Object(Matching, "Dolphin/si/SIUnregisterPollingHandler.c"),
            Object(Matching, "Dolphin/si/SIInit.c"),
            Object(Matching, "Dolphin/si/SIBios.c"),
        ],
    ),
    DolphinLib(
        "exi",
        [
            Object(Matching, "Dolphin/exi/SetExiInterruptMask.c"),
            Object(Matching, "Dolphin/exi/EXIImm.c"),
            Object(Matching, "Dolphin/exi/EXIImmEx.c"),
            Object(Matching, "Dolphin/exi/EXIDma.c"),
            Object(Matching, "Dolphin/exi/EXISync.c"),
            Object(Matching, "Dolphin/exi/EXIClearInterrupts.c"),
            Object(Matching, "Dolphin/exi/EXISetExiCallback.c"),
            Object(Matching, "Dolphin/exi/__EXIProbe.c"),
            Object(Matching, "Dolphin/exi/EXIProbe.c"),
            Object(Matching, "Dolphin/exi/EXIProbeEx.c"),
            Object(Matching, "Dolphin/exi/EXIAttach.c"),
            Object(Matching, "Dolphin/exi/EXIDetach.c"),
            Object(Matching, "Dolphin/exi/EXISelect.c"),
            Object(Matching, "Dolphin/exi/EXIDeselect.c"),
            Object(Matching, "Dolphin/exi/EXIIntrruptHandler.c"),
            Object(Matching, "Dolphin/exi/TCIntrruptHandler.c"),
            Object(Matching, "Dolphin/exi/EXTIntrruptHandler.c"),
            Object(Matching, "Dolphin/exi/EXIInit.c"),
            Object(Matching, "Dolphin/exi/EXILock.c"),
            Object(Matching, "Dolphin/exi/EXIUnlock.c"),
            Object(Matching, "Dolphin/exi/EXIGetState.c"),
            Object(Matching, "Dolphin/exi/UnlockedHandler.c"),
            Object(Matching, "Dolphin/exi/EXIGetID.c"),
            Object(Matching, "Dolphin/exi/ProbeBarnacle.c"),
            Object(Matching, "Dolphin/exi/__OSEnableBarnacle.c"),
            Object(Matching, "Dolphin/exi/InitializeUART.c"),
            Object(Matching, "Dolphin/exi/WriteUARTN.c"),
            Object(Matching, "Dolphin/OdemuExi2/DBInitInterrupts.c"),
            Object(Matching, "Dolphin/OdemuExi2/DBInitComm.c"),
            Object(Matching, "Dolphin/OdemuExi2/DBGHandler.c"),
            Object(Matching, "Dolphin/OdemuExi2/DBGReadStatus.c"),
            Object(Matching, "Dolphin/OdemuExi2/DBGWrite.c"),
            Object(Matching, "Dolphin/OdemuExi2/DBGRead.c"),
            Object(Matching, "Dolphin/OdemuExi2/DBGReadMailbox.c"),
            Object(Matching, "Dolphin/OdemuExi2/DBGEXIImm.c"),
            Object(Matching, "Dolphin/OdemuExi2/DBOpen.c"),
            Object(Matching, "Dolphin/OdemuExi2/DBClose.c"),
            Object(Matching, "Dolphin/OdemuExi2/DBWrite.c"),
            Object(Matching, "Dolphin/OdemuExi2/DBRead.c"),
            Object(Matching, "Dolphin/OdemuExi2/DBQueryData.c"),
        ],
    ),
    DolphinLib(
        "db",
        [
            Object(Matching, "Dolphin/db/db.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            Object(Matching, "Dolphin/dvd/dvdfs.c"),
            Object(Matching, "Dolphin/dvd/dvd.c"),
            Object(Matching, "Dolphin/dvd/DVDGetDriveStatus.c"),
            Object(Matching, "Dolphin/dvd/DVDSetAutoInvalidation.c"),
            Object(Matching, "Dolphin/dvd/DVDResume.c"),
            Object(Matching, "Dolphin/dvd/DVDCancelAsync.c"),
            Object(Matching, "Dolphin/dvd/__DVDPrepareResetAsync.c"),
            Object(Matching, "Dolphin/dvd/fn_80186590.c"),
            Object(Matching, "Dolphin/dvd/dvdqueue.c"),
            Object(Matching, "Dolphin/dvd/dvderror.c"),
            Object(Matching, "Dolphin/dvd/DVDCompareDiskID.c"),
            Object(Matching, "Dolphin/dvd/DVDLowWaitCoverClose.c"),
            Object(Matching, "Dolphin/dvd/__DVDPrintFatalMessage.c"),
            Object(Matching, "Dolphin/dvd/fstload.c"),
            Object(Matching, "Dolphin/dvd/__DVDInitWA.c"),
            Object(Matching, "Dolphin/dvd/__DVDInterruptHandler.c"),
            Object(Matching, "Dolphin/dvd/AlarmHandler_80186FE0.c"),
            Object(Matching, "Dolphin/dvd/AlarmHandlerForTimeout.c"),
            Object(Matching, "Dolphin/dvd/DVDLowRead.c"),
            Object(Matching, "Dolphin/dvd/DVDLowSeek.c"),
            Object(Matching, "Dolphin/dvd/DVDLowReadDiskID.c"),
            Object(Matching, "Dolphin/dvd/DVDLowStopMotor.c"),
            Object(Matching, "Dolphin/dvd/DVDLowRequestError.c"),
            Object(Matching, "Dolphin/dvd/DVDLowInquiry.c"),
            Object(Matching, "Dolphin/dvd/DVDLowAudioStream.c"),
            Object(Matching, "Dolphin/dvd/DVDLowRequestAudioStatus.c"),
            Object(Matching, "Dolphin/dvd/DVDLowAudioBufferConfig.c"),
            Object(Matching, "Dolphin/dvd/DVDLowReset.c"),
            Object(Matching, "Dolphin/dvd/DVDLowBreak.c"),
            Object(Matching, "Dolphin/dvd/DVDLowClearCallback.c"),
            Object(Matching, "Dolphin/dvd/__DVDLowSetWAType.c"),
            Object(Matching, "Dolphin/dvd/__DVDIsDVDAlarm.c"),
            Object(Matching, "Dolphin/vi/__VIRetraceHandler.c"),
            Object(Matching, "Dolphin/dvd/DVDLowSetCoverCallback.c"),
            Object(Matching, "Dolphin/dvd/DVDLowSetResetCoverCallback.c"),
            Object(Matching, "Dolphin/vi/getTiming.c"),
            Object(Matching, "Dolphin/vi/__VIInit.c"),
            Object(NonMatching, "Dolphin/vi/VIInit.c"),
            Object(Matching, "Dolphin/vi/VIWaitForRetrace.c"),
            Object(Matching, "Dolphin/vi/setFbbRegs.c"),
            Object(Matching, "Dolphin/vi/setVerticalRegs.c"),
            Object(Matching, "Dolphin/vi/VIConfigure.c"),
            Object(NonMatching, "Dolphin/vi/VIConfigurePan.c"),
            Object(Matching, "Dolphin/vi/VIFlush.c"),
            Object(Matching, "Dolphin/vi/VISetNextFrameBuffer.c"),
            Object(Matching, "Dolphin/vi/VISetBlack.c"),
            Object(Matching, "Dolphin/vi/VIGetRetraceCount.c"),
            Object(Matching, "Dolphin/vi/getCurrentFieldEvenOdd.c"),
            Object(Matching, "Dolphin/vi/VIGetCurrentLine.c"),
            Object(Matching, "Dolphin/vi/VIGetTvFormat.c"),
            Object(Matching, "Dolphin/vi/__VIDisplayPositionToXY.c"),
            Object(Matching, "Dolphin/vi/__VIGetCurrentPosition.c"),
        ],
    ),
    DolphinLib(
        "pad",
        [
            Object(Matching, "Dolphin/pad/UpdateOrigin.c"),
            Object(Matching, "Dolphin/pad/PADOriginCallback.c"),
            Object(Matching, "Dolphin/pad/PADOriginUpdateCallback.c"),
            Object(Matching, "Dolphin/pad/PADProbeCallback.c"),
            Object(Matching, "Dolphin/pad/PADTypeAndStatusCallback.c"),
            Object(Matching, "Dolphin/pad/PADReceiveCheckCallback.c"),
            Object(Matching, "Dolphin/pad/PADReset.c"),
            Object(Matching, "Dolphin/pad/PADRecalibrate.c"),
            Object(Matching, "Dolphin/pad/PADInit.c"),
            Object(Matching, "Dolphin/pad/PADRead.c"),
            Object(Matching, "Dolphin/pad/PADControlAllMotors.c"),
            Object(Matching, "Dolphin/pad/PADControlMotor.c"),
            Object(Matching, "Dolphin/pad/PADSetSpec.c"),
            Object(Matching, "Dolphin/pad/SPEC0_MakeStatus.c"),
            Object(Matching, "Dolphin/pad/SPEC1_MakeStatus.c"),
            Object(NonMatching, "Dolphin/pad/SPEC2_MakeStatus.c"),
            Object(Matching, "Dolphin/pad/OnReset.c"),
            Object(Matching, "Dolphin/pad/SamplingHandler.c"),
            Object(Matching, "Dolphin/pad/PADSetSamplingCallback.c"),
            Object(Matching, "Dolphin/pad/__PADDisableRecalibration.c"),
        ],
    ),
    DolphinLib(
        "os",
        [
            Object(Matching, "Dolphin/os/__start.c"),
            Object(Matching, "Dolphin/os/fn_80003254.c"),
            Object(Matching, "Dolphin/os/__check_pad3.c"),
            Object(Matching, "Dolphin/os/fn_80003300.c"),
            Object(Matching, "Dolphin/os/fn_80003464.c"),
            Object(Matching, "Dolphin/os/__init_hardware.c"),
            Object(Matching, "Dolphin/os/fn_8017A5CC.c"),
            Object(Matching, "Dolphin/os/fn_8017A620.c"),
            Object(Matching, "Dolphin/os/fn_8017A67C.c"),
            Object(Matching, "Dolphin/os/fn_8017A70C.c"),
            Object(Matching, "Dolphin/os/fn_8017A6CC.c"),
            Object(Matching, "Dolphin/os/fn_8017A6EC.c"),
            Object(Matching, "Dolphin/os/fn_8017A71C.c"),
            Object(Matching, "Dolphin/os/fn_8017A73C.c"),
            Object(Matching, "Dolphin/os/fn_8017A75C.c"),
            Object(Matching, "Dolphin/os/PPCArch.c"),
            Object(Matching, "Dolphin/os/OS.c"),
            Object(Matching, "Dolphin/os/__cvt_fp2unsigned.c"),
            Object(Matching, "Dolphin/os/__shr2u.c"),
            Object(Matching, "Dolphin/os/__div2i.c"),
            Object(Matching, "Dolphin/os/__shl2i.c"),
            Object(Matching, "Dolphin/os/__mod2i.c"),
            Object(Matching, "Dolphin/os/__shr2i.c"),
            Object(Matching, "Dolphin/os/__div2u.c"),
            Object(Matching, "Dolphin/os/__mod2u.c"),
            Object(Matching, "Dolphin/os/OSInitAlarm.c"),
            Object(Matching, "Dolphin/os/fn_8017B444.c"),
            Object(Matching, "Dolphin/os/InsertAlarm.c"),
            Object(Matching, "Dolphin/os/OSSetAlarm.c"),
            Object(Matching, "Dolphin/os/OSSetPeriodicAlarm.c"),
            Object(Matching, "Dolphin/os/OSCancelAlarm.c"),
            Object(Matching, "Dolphin/os/OSDecrementer.c"),
            Object(Matching, "Dolphin/os/fn_8017BB24.c"),
            Object(Matching, "Dolphin/os/OSArena.c"),
            Object(Matching, "Dolphin/os/OSAudioSystem.c"),
            Object(Matching, "Dolphin/os/OSCache.c"),
            Object(Matching, "Dolphin/os/__OSCacheInit.c"),
            Object(Matching, "Dolphin/os/__OSLoadFPUContext.c"),
            Object(Matching, "Dolphin/os/__OSSaveFPUContext.c"),
            Object(Matching, "Dolphin/os/OSSaveFPUContext.c"),
            Object(Matching, "Dolphin/os/OSSetCurrentContext.c"),
            Object(Matching, "Dolphin/os/OSGetCurrentContext.c"),
            Object(Matching, "Dolphin/os/OSSaveContext.c"),
            Object(Matching, "Dolphin/os/OSLoadContext.c"),
            Object(Matching, "Dolphin/os/OSGetStackPointer.c"),
            Object(Matching, "Dolphin/os/OSSwitchStack.c"),
            Object(Matching, "Dolphin/os/OSClearContext.c"),
            Object(Matching, "Dolphin/os/OSInitContext.c"),
            Object(Matching, "Dolphin/os/OSDumpContext.c"),
            Object(Matching, "Dolphin/os/OSReport.c"),
            Object(Matching, "Dolphin/os/OSPanic.c"),
            Object(NonMatching, "Dolphin/os/PackArgs.c"),
            Object(Matching, "Dolphin/os/WriteSramCallback.c"),
            Object(Matching, "Dolphin/os/WriteSram.c"),
            Object(Matching, "Dolphin/os/__OSInitSram.c"),
            Object(Matching, "Dolphin/os/OSLockSram.c"),
            Object(NonMatching, "Dolphin/os/OSUnlockSram.c"),
            Object(Matching, "Dolphin/os/__OSSyncSram.c"),
            Object(Matching, "Dolphin/os/__OSReadROM.c"),
            Object(Matching, "Dolphin/os/OSGetSoundMode.c"),
            Object(Matching, "Dolphin/os/OSSetSoundMode.c"),
            Object(Matching, "Dolphin/os/OSGetLanguage.c"),
            Object(Matching, "Dolphin/os/OSGetWirelessID.c"),
            Object(Matching, "Dolphin/os/OSSetWirelessID.c"),
            Object(Matching, "Dolphin/os/OSGetGbsMode.c"),
            Object(Matching, "Dolphin/os/OSSetGbsMode.c"),
            Object(Matching, "Dolphin/os/OSSync.c"),
            Object(Matching, "Dolphin/os/OSInterrupt.c"),
            Object(Matching, "Dolphin/os/__OSSetInterruptHandler.c"),
            Object(Matching, "Dolphin/os/__OSGetInterruptHandler.c"),
            Object(Matching, "Dolphin/os/__OSInterruptInit.c"),
            Object(Matching, "Dolphin/os/SetInterruptMask.c"),
            Object(Matching, "Dolphin/os/OSInterruptMask.c"),
            Object(Matching, "Dolphin/os/__OSDispatchInterrupt.c"),
            Object(Matching, "Dolphin/os/ExternalInterruptHandler.c"),
            Object(Matching, "Dolphin/os/__OSModuleInit.c"),
            Object(Matching, "Dolphin/os/OSSetCurrentHeap.c"),
            Object(Matching, "Dolphin/os/OSInitSemaphore.c"),
            Object(Matching, "Dolphin/os/OSMemory.c"),
            Object(Matching, "Dolphin/os/RealMode.c"),
            Object(Matching, "Dolphin/os/__OSInitMemoryProtection.c"),
            Object(Matching, "Dolphin/os/fn_8017E6E4.c"),
            Object(Matching, "Dolphin/os/OSGetSaveRegion.c"),
            Object(Matching, "Dolphin/os/OSRegisterResetFunction.c"),
            Object(Matching, "Dolphin/os/CallResetFunctions.c"),
            Object(Matching, "Dolphin/os/Reset.c"),
            Object(Matching, "Dolphin/os/KillThreads.c"),
            Object(Matching, "Dolphin/os/__OSDoHotReset.c"),
            Object(Matching, "Dolphin/os/OSResetSystem.c"),
            Object(Matching, "Dolphin/os/OSGetResetCode.c"),
            Object(Matching, "Dolphin/os/__OSResetSWInterruptHandler.c"),
            Object(Matching, "Dolphin/os/OSGetResetButtonState.c"),
            Object(Matching, "Dolphin/os/fn_8017D3B0.c"),
            Object(Matching, "Dolphin/os/fn_8017D464.c"),
            Object(Matching, "Dolphin/os/fn_8017D4A4.c"),
            Object(Matching, "Dolphin/os/__OSBootDolSimple.c"),
            Object(Matching, "Dolphin/os/__OSBootDol.c"),
            Object(Matching, "Dolphin/os/OSAlarm.c"),
            Object(Matching, "Dolphin/os/ReadDiscBlocking.c"),
            Object(Matching, "Dolphin/os/__OSSetAlarmState.c"),
            Object(Matching, "Dolphin/os/DefaultSwitchThreadCallback.c"),
            Object(Matching, "Dolphin/os/__OSThreadInit.c"),
            Object(Matching, "Dolphin/os/OSInitThreadQueue.c"),
            Object(Matching, "Dolphin/os/fn_8017FD74.c"),
            Object(Matching, "Dolphin/os/fn_8017FD80.c"),
            Object(Matching, "Dolphin/os/OSThread.c"),
            Object(Matching, "Dolphin/os/SelectThread.c"),
            Object(Matching, "Dolphin/os/OSYieldThread.c"),
            Object(NonMatching, "Dolphin/os/OSCreateThread.c"),
            Object(Matching, "Dolphin/os/OSExitThread.c"),
            Object(Matching, "Dolphin/os/OSCancelThread.c"),
            Object(Matching, "Dolphin/os/OSResumeThread.c"),
            Object(Matching, "Dolphin/os/OSSuspendThread.c"),
            Object(Matching, "Dolphin/os/OSSleepThread.c"),
            Object(Matching, "Dolphin/os/OSWakeupThread.c"),
            Object(Matching, "Dolphin/os/OSSetThreadPriority.c"),
            Object(Matching, "Dolphin/os/OSClearStack.c"),
            Object(Matching, "Dolphin/os/OSTime.c"),
            Object(Matching, "Dolphin/os/fn_801813D4.c"),
            Object(Matching, "Dolphin/os/_ExitProcess.c"),
            Object(Matching, "Dolphin/os/OSMutex.c"),
        ],
    ),
    DolphinLib(
        "vm",
        [
            Object(Matching, "Dolphin/vm/VMSetLogStatsCallback.c"),
            Object(Matching, "Dolphin/vm/__VMGetNumPagesInMRAM.c"),
            Object(Matching, "Dolphin/vm/VMGetARAMSize.c"),
            Object(Matching, "Dolphin/vm/VMGetARAMBase.c"),
            Object(Matching, "Dolphin/vm/__VMAllocMRAMSwapSpace.c"),
            Object(Matching, "Dolphin/vm/__VMSetARAMPageAsDirty.c"),
            Object(Matching, "Dolphin/vm/__VMIsARAMPageDirty.c"),
            Object(Matching, "Dolphin/vm/__VMGetPageToReplace.c"),
            Object(Matching, "Dolphin/vm/VMAlloc.c"),
            Object(Matching, "Dolphin/vm/__VMTranslateVMPageToARAMPage.c"),
            Object(Matching, "Dolphin/vm/__VMDoesMappingExist.c"),
            Object(Matching, "Dolphin/vm/__VMMappingErrorAlert.c"),
            Object(Matching, "Dolphin/vm/__VMBASEISIServiceExceptionPrep.c"),
        ],
    ),
    DolphinLib(
        "mtx",
        [
            Object(Matching, "Dolphin/mtx/PSMTXIdentity.c"),
            Object(Matching, "Dolphin/mtx/PSMTXTrans.c"),
            Object(Matching, "Dolphin/mtx/PSMTXScale.c"),
        ],
    ),
    DolphinLib(
        "ar",
        [
            Object(Matching, "Dolphin/ar/ARRegisterDMACallback.c"),
            Object(Matching, "Dolphin/ar/ARGetDMAStatus.c"),
            Object(Matching, "Dolphin/ar/ARGetBaseAddress.c"),
            Object(Matching, "Dolphin/ar/__ARClearInterrupt.c"),
            Object(Matching, "Dolphin/ar/__ARGetInterruptStatus.c"),
        ],
    ),
    DolphinLib(
        "arq",
        [
            Object(Matching, "Dolphin/arq/__ARQServiceQueueLo.c"),
            Object(Matching, "Dolphin/arq/__ARQCallbackHack.c"),
        ],
    ),
    DolphinLib(
        "ax",
        [
            Object(Matching, "Dolphin/ax/AXInit.c"),
            Object(Matching, "Dolphin/ax/AXInitEx.c"),
            Object(Matching, "Dolphin/ax/AXQuit.c"),
            Object(Matching, "Dolphin/ax/__AXGetStackHead.c"),
            Object(Matching, "Dolphin/ax/__AXGetNumVoices.c"),
            Object(Matching, "Dolphin/ax/__AXPushFreeStack.c"),
            Object(Matching, "Dolphin/ax/__AXPushCallbackStack.c"),
            Object(Matching, "Dolphin/ax/__AXPopCallbackStack.c"),
            Object(Matching, "Dolphin/ax/__AXAuxQuit.c"),
            Object(Matching, "Dolphin/ax/__AXGetCommandListCycles.c"),
            Object(Matching, "Dolphin/ax/__AXGetCommandListAddress.c"),
            Object(Matching, "Dolphin/ax/__AXClInit.c"),
            Object(Matching, "Dolphin/ax/__AXClQuit.c"),
            Object(Matching, "Dolphin/ax/__AXSPBInit.c"),
            Object(Matching, "Dolphin/ax/__AXSPBQuit.c"),
            Object(Matching, "Dolphin/ax/__AXVPBQuit.c"),
            Object(Matching, "Dolphin/ax/AXRegisterAuxACallback.c"),
            Object(Matching, "Dolphin/ax/AXSetMode.c"),
            Object(Matching, "Dolphin/ax/AXSetVoiceAddr.c"),
            Object(Matching, "Dolphin/ax/__AXDSPInitCallback.c"),
            Object(Matching, "Dolphin/ax/__AXGetStudio.c"),
            Object(Matching, "Dolphin/ax/__AXGetPBs.c"),
            Object(Matching, "Dolphin/ax/__AXGetAuxBOutputDPL2.c"),
            Object(Matching, "Dolphin/ax/__AXGetAuxBForDPL2.c"),
            Object(Matching, "Dolphin/ax/__AXGetAuxBInput.c"),
            Object(Matching, "Dolphin/ax/__AXGetAuxBOutput.c"),
            Object(Matching, "Dolphin/ax/__AXGetAuxAOutput.c"),
            Object(Matching, "Dolphin/ax/__AXGetAuxAOutputDpl2Rs.c"),
            Object(Matching, "Dolphin/ax/__AXGetAuxAOutputDpl2Ls.c"),
            Object(Matching, "Dolphin/ax/__AXGetAuxAOutputDpl2R.c"),
            Object(Matching, "Dolphin/ax/__AXGetAuxAInput.c"),
            Object(Matching, "Dolphin/ax/__AXGetAuxAInputDpl2.c"),
            Object(Matching, "Dolphin/ax/__AXDSPDoneCallback.c"),
            Object(Matching, "Dolphin/ax/__AXGetCurrentProfile.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            Object(Matching, "Dolphin/dsp/DSPCheckMailToDSP.c"),
            Object(Matching, "Dolphin/dsp/DSPCheckMailFromDSP.c"),
            Object(Matching, "Dolphin/dsp/DSPReadMailFromDSP.c"),
            Object(Matching, "Dolphin/dsp/DSPCheckInit.c"),
            Object(Matching, "Dolphin/dsp/DSPSendMailToDSP.c"),
            Object(Matching, "Dolphin/dsp/DSPCancelTask.c"),
            Object(Matching, "Dolphin/dsp/__DSP_debug_printf.c"),
        ],
    ),
    DolphinLib(
        "card",
        [
            Object(Matching, "Dolphin/card/__CARDDefaultApiCallback.c"),
            Object(Matching, "Dolphin/card/__CARDSyncCallback.c"),
            Object(Matching, "Dolphin/card/UnlockedCallback.c"),
            Object(Matching, "Dolphin/card/__CARDWritePage.c"),
            Object(Matching, "Dolphin/card/__CARDGetFontEncode.c"),
            Object(Matching, "Dolphin/card/__CARDSetDiskID.c"),
            Object(Matching, "Dolphin/card/__CARDGetFatBlock.c"),
            Object(Matching, "Dolphin/card/__CARDAllocBlock.c"),
            Object(Matching, "Dolphin/card/__CARDGetDirBlock.c"),
            Object(Matching, "Dolphin/card/CARDMount.c"),
            Object(Matching, "Dolphin/card/__CARDIsOpened.c"),
            Object(Matching, "Dolphin/card/CARDWrite.c"),
            Object(Matching, "Dolphin/card/CARDDeleteAsync.c"),
            Object(Matching, "Dolphin/card/__CARDExiHandler.c"),
            Object(Matching, "Dolphin/card/CARDWriteAsync.c"),
            Object(Matching, "Dolphin/card/CARDDelete.c"),
            Object(Matching, "Dolphin/card/CARDGetStatus.c"),
            Object(Matching, "Dolphin/card/CARDSetStatus.c"),
            Object(Matching, "Dolphin/card/CARDRead.c"),
            Object(Matching, "Dolphin/card/CARDCreate.c"),
            Object(Matching, "Dolphin/card/CARDClose.c"),
            Object(Matching, "Dolphin/card/CARDOpen.c"),
        ],
    ),
    DolphinLib(
        "texPalette",
        [
            Object(Matching, "Dolphin/texPalette/TEXGet.c"),
        ],
    ),
]


# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects


# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("sdk", "SDK Code"),
]
config.progress_each_module = args.verbose
# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    # Marks relocations as mismatching if the target value is different
    # Default is "functionRelocDiffs=none", which is most lenient
    # "--config functionRelocDiffs=data_value",
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
