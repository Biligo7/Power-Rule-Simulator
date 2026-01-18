# Power-Law-Simulator

## Overview

**A C++ forest fire simulator demonstrating power-law behavior, built using the sgg library.**

<img width="1330" height="739" alt="Image" src="https://github.com/user-attachments/assets/86b9887b-8ee2-41b7-8d24-63ae7000c2d8" />

<img width="1585" height="1190" alt="Image" src="https://github.com/user-attachments/assets/8c8b6794-c973-4ad5-8d56-af0844b2b64a" />

## Prerequisites
- Install build tools and dependencies for linux or wsl:
```bash
sudo apt-get update
sudo apt-get install -y build-essential
sudo apt-get install -y libsdl2-dev libsdl2-mixer-dev libglew-dev libfreetype6-dev
```

## Build & Run
**From the project root:**
```bash
make       # builds ./power_law_simulator (Release)
make run   # runs ./power_law_simulator (Release)
make debug # builds ./power_law_simulator_dbg (Debug)
make clean # removes the all the binary
```

## Project Layout
- `src/`: C++ source code.
- `assets/`: Images, fonts, audio used at runtime.
- `include/`: Local SGG headers (`graphics.h`, `scancodes.h`).
- `lib/`: Local SGG static libs (`libsgg.a`, `libsggd.a`).
- `Makefile`: Uses `-Iinclude` and `-Llib` to match standalone SGG setup.

## Notes
- Run from the project root so `assets/...` paths resolve (using the Makefile's `make run` you should be at project root anyway). Thats also why the binary file is created in the project root. You can re-run it without any problems.
- The whole project was developed using vscode on windows 11 wsl

## Credits
- Project inspiration: https://www.youtube.com/watch?v=HBluLfX2F_k
- SGG library: https://github.com/cgaueb/sgg
- course/university: a project for the course "Computer Programming with C++" at AUEB
- contributors: Vasileios Grigoropoulos, Ifigeneia Rapti
