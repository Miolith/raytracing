# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Files
SRC = scene.cpp renderer.cpp main.cpp
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