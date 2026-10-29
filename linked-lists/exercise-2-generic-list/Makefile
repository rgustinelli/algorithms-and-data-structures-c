CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Iinclude
SANITIZE = -fsanitize=address,undefined -g

BIN = linked_list
TEST_BIN = test_linked_list

SRC = src/element.c src/linked_list.c
MAIN = src/main.c
TEST_SRC = tests/test_linked_list.c

.PHONY: all test clean

all: $(BIN)

$(BIN): $(MAIN) $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(MAIN) $(SRC)

test: $(TEST_SRC) $(SRC)
	$(CC) $(CFLAGS) $(SANITIZE) -o $(TEST_BIN) $(TEST_SRC) $(SRC)
	./$(TEST_BIN)

clean:
	rm -f $(BIN) $(TEST_BIN)
