# Power-Law-Simulator
**A Power law simulator written in C++, using the sgg library.**

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
- Run from the project root so `assets/...` paths resolve (using the Makefile's make run you should be at project root anyway). Thats also why the binary file is created in the project root. You can re-run it without any problems.
- The whole project was developed using vscode on windows 11 wsl

## Credits
- SGG library: https://github.com/cgaueb/sgg
- course/university: a project for the course "Computer Programming with C++" at AUEB
- contributors: Vasileios Grigoropoulos, Ifigeneia Rapti