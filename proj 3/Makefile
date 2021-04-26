SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

TARGET1 := $(BIN_DIR)/P2_3a
TARGET2 := $(BIN_DIR)/P2_3b
TARGET3 := $(BIN_DIR)/P2_1

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CXX_FLAGS := -Iinclude -std=c++11 -g
CC := g++
LDFLAGS  := -Llib
LDLIBS   := -lm

.PHONY: all clean

all: $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET1): $(OBJ_DIR)/P2_3a.o | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	
$(TARGET2): $(OBJ_DIR)/P2_3b.o | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	
$(TARGET3): $(OBJ_DIR)/P2_1.o | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CXX_FLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR) Output_1A.ppm Output_3A.ppm Output_6A.ppm Output_1B.ppm Output_3B.ppm Output_6B.ppm 

-include $(OBJ:.o=.d)
