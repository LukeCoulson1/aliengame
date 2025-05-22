CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SOURCES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/utils/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/space-invaders.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	if not exist $(subst /,\, $(dir $@)) mkdir $(subst /,\, $(dir $@))
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	if exist $(OBJ_DIR) rmdir /S /Q $(OBJ_DIR)
	if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)

.PHONY: all clean