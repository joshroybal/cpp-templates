CC = g++
CFLAGS = -g
LFLAGS =
BIN = bin/list
OBJ = obj/main.o

$(BIN): $(OBJ)
	$(CC) $(LFLAGS) -o $@ $^

$(OBJ): src/main.cpp src/list.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY : clean
clean:
	$(RM) $(BIN) $(OBJ)
