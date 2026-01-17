CXX := g++
CXXFLAGS := -O2 -std=c++17 -Iinclude -Isrc -I.
LDFLAGS := -Llib -lsgg -lGL -lGLEW -lSDL2 -lSDL2_mixer -lfreetype

# Compile all C++ sources under src/
SRC := $(shell find src -name "*.cpp")
TARGET := ./power_law_simulator

.PHONY: all run clean debug

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	$(TARGET)

DEBUG_TARGET := ./power_law_simulator_dbg

debug:
	$(CXX) -Og -g -std=c++17 -Iinclude -Isrc -I. $(SRC) -o $(DEBUG_TARGET) -Llib -lsggd -lGL -lGLEW -lSDL2 -lSDL2_mixer -lfreetype

clean:
	rm -rf ./power_law_simulator
	rm -rf ./power_law_simulator_dbg