Marvel Nemesis: Rise of the Imperfects
[![Build Status]][actions]
=============

[![Discord Badge]][discord]

[Build Status]: https://github.com/Esoteric-Engineer/mnroi/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/Esoteric-Engineer/mnroi/actions/workflows/build.yml
[Discord Badge]: https://img.shields.io/discord/727908905392275526?color=%237289DA&logo=discord&logoColor=%23FFFFFF
[discord]: https://discord.gg/VhcevnY7cV

A work-in-progress decompilation of Marvel Nemesis: Rise of the Imperfects for GameCube.

This repository does **not** contain any game assets or assembly whatsoever. An existing copy of the game is required.

Known supported versions:

- `GVLE69`: Rev 0 (USA)

Documentation
=============

- [`docs/workflow.md`](docs/workflow.md): the day-to-day decomp reference.
- [`docs/matching_notes.md`](docs/matching_notes.md): compiler/linker gotchas and matching techniques.
- [`docs/nonmatching.md`](docs/nonmatching.md): functions stuck as `NonMatching`, with what has already been tried.
- [`docs/baseline.md`](docs/baseline.md): why the build is configured the way it is.
- [`docs/prodg.md`](docs/prodg.md): the SN ProDG (GCC 2.95) compile path for game and runtime code, and how static constructors link.

> **Note:** this project requires a local build of the decomp-toolkit fork, [`Esoteric-Engineer/mnroi-decomp-toolkit`](https://github.com/Esoteric-Engineer/mnroi-decomp-toolkit), not the released dtk. See [Building](#building).

Dependencies
============

Windows
--------

On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.  
When running under WSL, [objdiff](#diffing) is unable to get filesystem notifications for automatic rebuilds.

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

macOS
------

- Install [ninja](https://formulae.brew.sh/formula/ninja):

  ```sh
  brew install ninja
  ```

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Linux
------

- Install [ninja](https://ninja-build.org/) from your distribution's package manager:

  ```sh
  sudo apt install ninja-build   # Debian/Ubuntu
  sudo dnf install ninja-build   # Fedora
  sudo pacman -S ninja           # Arch
  ```

  Alternatively, download a binary from the [ninja releases](https://github.com/ninja-build/ninja/releases) and put it on your `PATH`.

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Building
========

- Clone the repository:

  ```sh
  git clone https://github.com/Esoteric-Engineer/mnroi.git
  ```

- Clone and build the decomp-toolkit fork as a sibling of this repo (requires
  [Rust](https://rustup.rs/)). The stock released dtk will **not** produce a matching build
  (see [`docs/baseline.md`](docs/baseline.md)):

  ```sh
  git clone https://github.com/Esoteric-Engineer/mnroi-decomp-toolkit.git
  cd mnroi-decomp-toolkit
  cargo build --release
  cd ../mnroi
  mkdir -p build/tools
  cp ../mnroi-decomp-toolkit/target/release/dtk build/tools/dtk-dev
  ```

  Repeat the build and copy after pulling fork changes.

- Copy your game's disc image to `orig/GVLE69`.
  - Supported formats: ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ, TGC
  - After the initial build, the disc image can be deleted to save space.

- Configure:

  ```sh
  python3 configure.py --dtk build/tools/dtk-dev
  ```

  To use a version other than `GVLE69` (USA), specify it with `--version`.

  The `--dtk` argument is remembered by `build.ninja`, so later `ninja` runs reuse it.<br />
  If you ever run a bare `python3 configure.py`, it falls back to stock dtk and the build stops matching.

- Build:

  ```sh
  ninja
  ```

  A successful build ends with `build/GVLE69/main.dol: OK`. The `WARN` lines from the split step and mwld's `_SDA2_BASE_` warning are expected.

Diffing
=======

Once the initial build succeeds, an `objdiff.json` should exist in the project root.

Download the latest release from [encounter/objdiff](https://github.com/encounter/objdiff). Under project settings, set `Project directory`. The configuration should be loaded automatically.

Select an object from the left sidebar to begin diffing. Changes to the project will rebuild automatically: changes to source files, headers, `configure.py`, `splits.txt` or `symbols.txt`.

![](assets/objdiff.png)
