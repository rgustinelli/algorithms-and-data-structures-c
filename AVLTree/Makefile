CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Iinclude
BUILD_DIR = build

SRC = src/avl.c src/element.c

.PHONY: all test clean

# Builds the example demo binary (build/avl_demo).
all: $(BUILD_DIR)/avl_demo

$(BUILD_DIR)/avl_demo: $(SRC) examples/example_1.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Builds and runs the automated test suite.
test: $(BUILD_DIR)/test_avl
	./$(BUILD_DIR)/test_avl

$(BUILD_DIR)/test_avl: $(SRC) tests/test_avl.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
