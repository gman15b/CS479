SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
FACE_DIR := eigenFaces

TARGET := $(BIN_DIR)/proj3


SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CXX_FLAGS := -Iinclude -std=c++17 -g
CC := g++

LDFLAGS  := -Llib
LDLIBS   := -lm

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ_DIR)/proj3.o | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CXX_FLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -r $(BIN_DIR) $(OBJ_DIR) $(FACE_DIR)/*.pgm

-include $(OBJ:.o=.d)
