CC = clang++
CFLAGS = -g
LFLAGS =
BIN = bin/tree
OBJ = obj/main.obj

$(BIN): $(OBJ)
	$(CC) $(LFLAGS) $^ -o $@

$(OBJ): src/main.cpp src/bst.hpp src/avl.hpp
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY : clean
clean:
	$(RM) $(BIN) $(OBJ)
