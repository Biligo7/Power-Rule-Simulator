CXX := g++
CXXFLAGS := -O2 -std=c++17 -Iinclude -I.
LDFLAGS := -Llib -lsgg -lGL -lGLEW -lSDL2 -lSDL2_mixer -lfreetype

SRC := src/main.cpp
TARGET := ./power_rule_simulator

.PHONY: all run clean debug

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

DEBUG_TARGET := ./power_rule_simulator_dbg

debug:
	$(CXX) -Og -g -std=c++17 -Iinclude -I. $(SRC) -o $(DEBUG_TARGET) -Llib -lsggd -lGL -lGLEW -lSDL2 -lSDL2_mixer -lfreetype

clean:
	rm -rf ./power_rule_simulator
	rm -rf ./power_rule_simulator_dbg
