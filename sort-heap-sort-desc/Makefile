CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Isrc/heap-sort-desc

HEAP_SORT_SRC = src/heap-sort-desc/heap_sort.c
SHARED_SRC = src/shared/element.c
MAIN = src/heap-sort-desc/main.c
TEST_SRC = tests/test_heap_sort.c

BIN = heap_sort_demo
TEST_BIN = test_heap_sort

.PHONY: all test clean

all: $(BIN)

$(BIN): $(MAIN) $(HEAP_SORT_SRC) $(SHARED_SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(MAIN) $(HEAP_SORT_SRC) $(SHARED_SRC)

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(HEAP_SORT_SRC) $(SHARED_SRC)
	$(CC) $(CFLAGS) -o $(TEST_BIN) $(TEST_SRC) $(HEAP_SORT_SRC) $(SHARED_SRC)

clean:
	rm -f $(BIN) $(TEST_BIN)
