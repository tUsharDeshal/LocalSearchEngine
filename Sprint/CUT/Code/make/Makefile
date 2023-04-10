SRC_DIR=../src
INC_DIR=../inc
OBJ_DIR=../obj
BIN_DIR=../bin

EXE := $(BIN_DIR)/LSE
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp= $(OBJ_DIR)/%.o)

CC := g++
CIFLAGS := -I $(INC_DIR)
CFLAGS := -c -g
LDFLAGS := -Llib
LDLIDS := -lm

all: $(EXE)

$(EXE) : $(OBJ) | $(BIN_DIR)
			$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ 

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
			$(CC) $(CIFLAGS) $(CFLAGS) $< -o $@

$(BIN_DIR) $(OBJ_DIR) :
			mkdir -p $@

clean:
			@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)


