CC = g++
CFLAGS = -O2
LFLAGS = -s
BIN = bin/wordtest
OBJ = obj/main.o
HDR = src/SinglyLinkedList.hpp src/DoublyLinkedList.hpp \
		src/BinarySearchTree.hpp src/AVLTree.hpp

$(BIN): $(OBJ)
	$(CC) $(LFLAGS) -o $@ $^

$(OBJ): src/main.cpp $(HDR)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY : clean
clean:
	$(RM) $(BIN) $(OBJ)
