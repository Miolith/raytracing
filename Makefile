# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23 -g -Wno-unused-parameter -Wno-missing-field-initializers

# Files
SRC = scene.cpp sphere.cpp renderer.cpp camera.cpp ground.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
EXE = main

# Default target
all: $(EXE)

# Linking
$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compiling
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleaning up
clean:
	rm -f $(OBJ) $(EXE)

.PHONY: all clean