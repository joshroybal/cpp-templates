CC = g++
CFLAGS = -g
LFLAGS =
BIN = bin/bst
OBJ = obj/main.o

$(BIN): $(OBJ)
	$(CC) $(LFLAGS) -o $@ $^

$(OBJ): src/main.cpp src/bst.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY : clean
clean:
	$(RM) $(BIN) $(OBJ)
