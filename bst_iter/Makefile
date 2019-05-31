CC = g++
CFLAGS = -g
LFLAGS =
BIN = bin/bst
OBJ = obj/main.obj

$(BIN): $(OBJ)
	$(CC) $(LFLAGS) $^ -o $@

$(OBJ): src/main.cpp src/bst.hpp
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY : clean
clean:
	$(RM) $(BIN) $(OBJ)
