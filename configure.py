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
            Object(NonMatching, "Runtime.PPCEABI.H/global_destructor_chain.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
            Object(Matching, "Runtime.PPCEABI.H/fabsf.c"),
            Object(Matching, "Runtime.PPCEABI.H/fabs.c"),
            Object(Matching, "Runtime.PPCEABI.H/copysignf.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_801700B8.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80171F8C.c"),
            Object(Matching, "Runtime.PPCEABI.H/tolower.c"),
            Object(Matching, "Runtime.PPCEABI.H/isdigit.c"),
            Object(Matching, "Runtime.PPCEABI.H/isspace.c"),
            Object(Matching, "Runtime.PPCEABI.H/runtime.c"),
            Object(Matching, "Runtime.PPCEABI.H/lshrdi3.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80177CF8.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80177D24.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80177E04.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80177E24.c"),
            Object(Matching, "Runtime.PPCEABI.H/ungetc.c"),
            Object(Matching, "Runtime.PPCEABI.H/div.c"),
            Object(Matching, "Runtime.PPCEABI.H/memchr.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80178224.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80178318.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80178D20.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80178D48.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80178D98.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80178DF0.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80178E48.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80178EA4.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80178EFC.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80178F54.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80178FF0.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80179080.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_80179138.c"),
            Object(Matching, "Runtime.PPCEABI.H/fn_801796FC.c"),
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
            Object(NonMatching, "Dolphin/ai/AIInit.c"),
            Object(Matching, "Dolphin/ai/__AISHandler.c"),
            Object(Matching, "Dolphin/ai/__AIDHandler.c"),
            Object(Matching, "Dolphin/ai/__AICallbackStackSwitch.c"),
            Object(Matching, "Dolphin/ai/__AI_SRC_INIT.c"),
            Object(NonMatching, "Dolphin/gx/GXClearVtxDesc.c"),
            Object(Matching, "Dolphin/gx/GXSetArray.c"),
            Object(Matching, "Dolphin/gx/GXInvalidateVtxCache.c"),
            Object(Matching, "Dolphin/gx/GXSetNumTexGens.c"),
            Object(NonMatching, "Dolphin/gx/GXSetCullMode.c"),
            Object(Matching, "Dolphin/gx/GXInitLightAttn.c"),
            Object(Matching, "Dolphin/gx/GXInitLightPos.c"),
            Object(Matching, "Dolphin/gx/GXInitLightDir.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(Matching, "Dolphin/gx/GXInit.c"),
            Object(Matching, "Dolphin/gx/GXAttr.c"),
            Object(Matching, "Dolphin/gx/GXTexture.c"),
            Object(NonMatching, "Dolphin/gx/GXLoadTexObjPreLoaded.c"),
            Object(Matching, "Dolphin/gx/GXLoadTexObj.c"),
            Object(Matching, "Dolphin/gx/GXInitTlutObj.c"),
            Object(Matching, "Dolphin/gx/GXGetTlutObjAll.c"),
            Object(Matching, "Dolphin/gx/GXGetTlutObjData.c"),
            Object(Matching, "Dolphin/gx/GXLoadTlut.c"),
            Object(Matching, "Dolphin/gx/GXInitTexCacheRegion.c"),
            Object(Matching, "Dolphin/gx/GXSetTexRegionCallback.c"),
            Object(Matching, "Dolphin/gx/GXSetTlutRegionCallback.c"),
            Object(NonMatching, "Dolphin/gx/GXSetSUTexRegs.c"),
            Object(Matching, "Dolphin/gx/GXSetNumIndStages.c"),
            Object(Matching, "Dolphin/gx/GXSetTevDirect.c"),
            Object(Matching, "Dolphin/gx/GXSetTevIndRepeat.c"),
            Object(Matching, "Dolphin/gx/GXSetIndirectMask.c"),
            Object(NonMatching, "Dolphin/gx/GXFlushTextureState.c"),
            Object(Matching, "Dolphin/gx/GXSetTevColorIn.c"),
            Object(Matching, "Dolphin/gx/GXSetTevAlphaIn.c"),
            Object(NonMatching, "Dolphin/gx/GXSetTevColorOp.c"),
            Object(NonMatching, "Dolphin/gx/GXSetTevAlphaOp.c"),
            Object(NonMatching, "Dolphin/gx/GXSetTevColor.c"),
            Object(NonMatching, "Dolphin/gx/GXSetTevKColor.c"),
            Object(NonMatching, "Dolphin/gx/GXSetTevKColorSel.c"),
            Object(NonMatching, "Dolphin/gx/GXSetTevKAlphaSel.c"),
            Object(Matching, "Dolphin/gx/GXSetTevSwapMode.c"),
            Object(Matching, "Dolphin/gx/GXSetTevSwapModeTable.c"),
            Object(NonMatching, "Dolphin/gx/GXSetAlphaCompare.c"),
            Object(NonMatching, "Dolphin/gx/GXSetZTexture.c"),
            Object(NonMatching, "Dolphin/gx/GXSetTevOrder.c"),
            Object(Matching, "Dolphin/gx/GXSetNumTevStages.c"),
            Object(Matching, "Dolphin/gx/GXSetColorUpdate.c"),
            Object(Matching, "Dolphin/gx/GXSetAlphaUpdate.c"),
            Object(Matching, "Dolphin/gx/GXSetZMode.c"),
            Object(Matching, "Dolphin/gx/GXSetZCompLoc.c"),
            Object(NonMatching, "Dolphin/gx/GXSetPixelFmt.c"),
            Object(Matching, "Dolphin/gx/GXSetDither.c"),
            Object(Matching, "Dolphin/gx/GXSetDstAlpha.c"),
            Object(NonMatching, "Dolphin/gx/GXSetFieldMask.c"),
            Object(Matching, "Dolphin/gx/GXSetFieldMode.c"),
            Object(NonMatching, "Dolphin/gx/GXTransform.c"),
            Object(Matching, "Dolphin/gx/GXLoadPosMtxImm.c"),
            Object(Matching, "Dolphin/gx/GXLoadNrmMtxImm.c"),
            Object(Matching, "Dolphin/gx/GXSetCurrentMtx.c"),
            Object(Matching, "Dolphin/gx/GXLoadTexMtxImm.c"),
            Object(NonMatching, "Dolphin/gx/GXSetViewport.c"),
            Object(Matching, "Dolphin/gx/GXSetScissor.c"),
            Object(NonMatching, "Dolphin/gx/GXSetScissorBoxOffset.c"),
            Object(NonMatching, "Dolphin/gx/__GXSetMatrixIndex.c"),
            Object(Matching, "Dolphin/gx/GXInitFifoBase.c"),
            Object(Matching, "Dolphin/gx/__GXFifoInit.c"),
            Object(Matching, "Dolphin/gx/__GXFifoReadEnable.c"),
            Object(Matching, "Dolphin/gx/__GXFifoReadDisable.c"),
            Object(Matching, "Dolphin/gx/GXSetMisc.c"),
            Object(Matching, "Dolphin/gx/GXFlush.c"),
            Object(Matching, "Dolphin/gx/GXResetWriteGatherPipe.c"),
            Object(Matching, "Dolphin/gx/GXPokeAlphaMode.c"),
            Object(Matching, "Dolphin/gx/GXPokeAlphaRead.c"),
            Object(Matching, "Dolphin/gx/GXPokeAlphaUpdate.c"),
            Object(Matching, "Dolphin/gx/GXPokeColorUpdate.c"),
            Object(Matching, "Dolphin/gx/GXPokeDstAlpha.c"),
            Object(Matching, "Dolphin/gx/GXPokeBlendMode.c"),
            Object(Matching, "Dolphin/gx/GXPokeDither.c"),
            Object(Matching, "Dolphin/gx/GXPokeZMode.c"),
        ],
    ),
    DolphinLib(
        "si",
        [
            Object(Matching, "Dolphin/si/SIBios.c"),
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
        ],
    ),
    DolphinLib(
        "os",
        [
            Object(Matching, "Dolphin/os/fn_8017A620.c"),
            Object(Matching, "Dolphin/os/fn_8017A70C.c"),
            Object(Matching, "Dolphin/os/fn_8017A6CC.c"),
            Object(Matching, "Dolphin/os/PPCArch.c"),
            Object(Matching, "Dolphin/os/fn_80169134.c"),
            Object(Matching, "Dolphin/os/fn_80169150.c"),
            Object(Matching, "Dolphin/os/__OSGetDIConfig.c"),
            Object(Matching, "Dolphin/os/OSRegisterVersion.c"),
            Object(Matching, "Dolphin/os/fn_8017B444.c"),
            Object(Matching, "Dolphin/os/OSCache.c"),
            Object(Matching, "Dolphin/os/fn_8017FB84.c"),
            Object(Matching, "Dolphin/os/OSInterrupt.c"),
            Object(Matching, "Dolphin/os/OSGetSaveRegion.c"),
            Object(Matching, "Dolphin/os/OSRegisterResetFunction.c"),
            Object(Matching, "Dolphin/os/OSAlarm.c"),
            Object(Matching, "Dolphin/os/__OSSetAlarmState.c"),
            Object(Matching, "Dolphin/os/fn_8017FD64.c"),
            Object(Matching, "Dolphin/os/fn_8017FD74.c"),
            Object(Matching, "Dolphin/os/fn_8017FD80.c"),
            Object(Matching, "Dolphin/os/OSThread.c"),
            Object(Matching, "Dolphin/os/OSYieldThread.c"),
            Object(Matching, "Dolphin/os/OSTime.c"),
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
