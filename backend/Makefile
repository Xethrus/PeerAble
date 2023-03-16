CC=clang++
PROG=peerable

SRC_DIR=src
OBJ_DIR=build
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

$(PROG): $(OBJ_FILES)
	$(CC) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $< -o $@

run: $(PROG)
	./$(PROG)

clean:
	rm -rf *.o $(PROG)
